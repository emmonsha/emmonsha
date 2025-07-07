#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_inverse_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  matrix_t result;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(result.matrix[0][0], 0.2);  // 1/5 = 0.2

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  matrix_t result;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{2, -1, 0}, {0, 1, 2}, {1, 1, 0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }

  matrix_t result;
  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);

  // Правильная обратная матрица (вычислена аналитически)

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_not_square) {
  matrix_t A;  // 2x3 — не квадратная
  s21_create_matrix(2, 3, &A);

  matrix_t result;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_singular) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;  // det = 1*4 - 2*2 = 0

  matrix_t result;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_null_matrix) {
  matrix_t result;
  int res = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_inverse_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int res = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_no_mem_leak) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }

  matrix_t result;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, OK);
  // Проверяем, что result — единичная матрица
  ck_assert_double_eq(result.matrix[0][0], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *inverse_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_inverse");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_inverse_1x1);
  tcase_add_test(tc_core, test_inverse_2x2);
  tcase_add_test(tc_core, test_inverse_3x3);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_inverse_not_square);
  tcase_add_test(tc_limits, test_inverse_singular);
  tcase_add_test(tc_limits, test_inverse_null_matrix);
  tcase_add_test(tc_limits, test_inverse_null_result);
  tcase_add_test(tc_limits, test_inverse_no_mem_leak);
  suite_add_tcase(s, tc_limits);

  return s;
}