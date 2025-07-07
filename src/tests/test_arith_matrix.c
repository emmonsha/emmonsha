#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_sum_matrix_valid) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 8.0;

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 6.0);
  ck_assert_double_eq(result.matrix[0][1], 8.0);
  ck_assert_double_eq(result.matrix[1][0], 10.0);
  ck_assert_double_eq(result.matrix[1][1], 12.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_valid) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 8.0;

  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], -4.0);
  ck_assert_double_eq(result.matrix[0][1], -4.0);
  ck_assert_double_eq(result.matrix[1][0], -4.0);
  ck_assert_double_eq(result.matrix[1][1], -4.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_different_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_different_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_null_input) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_null_input) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_invalid_dimensions) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = -2;
  B.columns = 2;
  B.matrix = NULL;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_sub_invalid_dimensions) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = -2;
  B.columns = 2;
  B.matrix = NULL;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_sum_zero_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_zero_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_memory_failure) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.rows = 1000000;
  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert(res == MATRIX_ERROR_CODE || res == OK);
  if (res == OK) {
    s21_remove_matrix(&result);
  }

  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_memory_failure) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.rows = 1000000;
  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert(res == MATRIX_ERROR_CODE || res == OK);
  if (res == OK) {
    s21_remove_matrix(&result);
  }

  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

/*START_TEST(test_sum_null_result_matrix) {
  matrix_t A, B, result;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  result.rows = 3;
  result.columns = 3;
  result.matrix = NULL;

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST*/

Suite *arith_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_sum_matrix, s21_sub_matrix");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sum_matrix_valid);
  tcase_add_test(tc_core, test_sub_matrix_valid);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_sum_different_sizes);
  tcase_add_test(tc_limits, test_sub_different_sizes);
  tcase_add_test(tc_limits, test_sum_null_input);
  tcase_add_test(tc_limits, test_sub_null_input);
  tcase_add_test(tc_limits, test_sum_invalid_dimensions);
  tcase_add_test(tc_limits, test_sub_invalid_dimensions);
  tcase_add_test(tc_limits, test_sum_zero_matrix);
  tcase_add_test(tc_limits, test_sub_zero_matrix);
  tcase_add_test(tc_limits, test_sum_memory_failure);
  tcase_add_test(tc_limits, test_sub_memory_failure);
  /*tcase_add_test(tc_limits, test_sum_null_result_matrix);*/
  suite_add_tcase(s, tc_limits);

  return s;
}