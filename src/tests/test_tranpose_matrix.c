#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_transpose_valid) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  int res = s21_transpose(&A, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 4);
  ck_assert_double_eq(result.matrix[1][0], 2);
  ck_assert_double_eq(result.matrix[1][1], 5);
  ck_assert_double_eq(result.matrix[2][0], 3);
  ck_assert_double_eq(result.matrix[2][1], 6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_square) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int res = s21_transpose(&A, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 3);
  ck_assert_double_eq(result.matrix[1][0], 2);
  ck_assert_double_eq(result.matrix[1][1], 4);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_null_input) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_transpose(NULL, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_transpose(&A, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_invalid_matrix) {
  matrix_t A = {0}, result;
  A.rows = -1;
  A.columns = 2;

  ck_assert_int_eq(s21_transpose(&A, &result), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_empty_matrix) {
  matrix_t A = {0}, result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  ck_assert_int_eq(s21_transpose(&A, &result), MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_transpose_memory_failure) {
  matrix_t A, result;
  s21_create_matrix(10000, 10000, &A);

  int res = s21_transpose(&A, &result);

  if (res == MATRIX_ERROR_CODE) {
    ck_assert_ptr_null(result.matrix);
  } else {
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&A);
}
END_TEST

Suite *transpose_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_transpose");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_transpose_valid);
  tcase_add_test(tc_core, test_transpose_square);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_transpose_null_input);
  tcase_add_test(tc_limits, test_transpose_invalid_matrix);
  tcase_add_test(tc_limits, test_transpose_empty_matrix);
  tcase_add_test(tc_limits, test_transpose_memory_failure);
  suite_add_tcase(s, tc_limits);

  return s;
}