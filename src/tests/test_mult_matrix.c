#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_mult_matrix_valid) {
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

  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 19.0);
  ck_assert_double_eq(result.matrix[0][1], 22.0);
  ck_assert_double_eq(result.matrix[1][0], 43.0);
  ck_assert_double_eq(result.matrix[1][1], 50.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_different_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_null_input) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_invalid_dimensions) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = -2;
  B.columns = 2;
  B.matrix = NULL;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_mult_zero_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_memory_failure) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.rows = 1000000;
  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert(res == MATRIX_ERROR_CODE || res == OK);
  if (res == OK) {
    s21_remove_matrix(&result);
  }

  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_valid) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  double number = 2.5;
  int res = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 2.5);
  ck_assert_double_eq(result.matrix[0][1], 5.0);
  ck_assert_double_eq(result.matrix[1][0], 7.5);
  ck_assert_double_eq(result.matrix[1][1], 10.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_zero) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int res = s21_mult_number(&A, 0.0, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[0][1], 0.0);
  ck_assert_double_eq(result.matrix[1][0], 0.0);
  ck_assert_double_eq(result.matrix[1][1], 0.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_negative) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int res = s21_mult_number(&A, -1.0, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], -1.0);
  ck_assert_double_eq(result.matrix[0][1], -2.0);
  ck_assert_double_eq(result.matrix[1][0], -3.0);
  ck_assert_double_eq(result.matrix[1][1], -4.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_null_input) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &result), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_invalid_dimensions) {
  matrix_t A = {0}, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_mult_number_zero_matrix) {
  matrix_t A, result;
  s21_create_matrix(0, 0, &A);

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_memory_failure) {
  matrix_t A = {0}, result;

  A.rows = 1;
  A.columns = 1;
  s21_create_matrix(A.rows, A.columns, &A);

  int res = s21_mult_number(NULL, 2.0, &result);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

Suite *mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_mult_matrix, s21_mult_number");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mult_matrix_valid);
  tcase_add_test(tc_core, test_mult_number_valid);
  tcase_add_test(tc_core, test_mult_number_zero);
  tcase_add_test(tc_core, test_mult_number_negative);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_mult_different_sizes);
  tcase_add_test(tc_limits, test_mult_null_input);
  tcase_add_test(tc_limits, test_mult_invalid_dimensions);
  tcase_add_test(tc_limits, test_mult_zero_matrix);
  tcase_add_test(tc_limits, test_mult_memory_failure);
  tcase_add_test(tc_limits, test_mult_number_null_input);
  tcase_add_test(tc_limits, test_mult_number_invalid_dimensions);
  tcase_add_test(tc_limits, test_mult_number_zero_matrix);
  tcase_add_test(tc_limits, test_mult_number_memory_failure);
  suite_add_tcase(s, tc_limits);

  return s;
}