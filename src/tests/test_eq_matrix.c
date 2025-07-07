#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_eq_eq_matrix) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_different_matrix) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.1;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_slighty_different) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0 + EPS / 2;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_different_sizes) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_null_input) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_eq_matrix(NULL, &A), MATRIX_ERROR_CODE);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_null_matrix_data) {
  matrix_t A = {0}, B = {0};
  A.rows = 2;
  A.columns = 2;
  B.rows = 2;
  B.columns = 2;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_empty_matrix) {
  matrix_t A, B;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_eq_matrix");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_eq_eq_matrix);
  tcase_add_test(tc_core, test_eq_different_matrix);
  tcase_add_test(tc_core, test_eq_slighty_different);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_eq_different_sizes);
  tcase_add_test(tc_limits, test_eq_null_input);
  tcase_add_test(tc_limits, test_eq_null_matrix_data);
  tcase_add_test(tc_limits, test_eq_empty_matrix);
  suite_add_tcase(s, tc_limits);

  return s;
}