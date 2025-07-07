#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  double det;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(det, 5.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  double det;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(det, (1.0 * 4.0 - 2.0 * 3.0));  // 1*4 - 2*3 = -2

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }

  double det;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 0.0,
                          1e-6);  // Определитель вырожденной матрицы = 0

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_not_square) {
  matrix_t A;  // 2x3 — не квадратная
  s21_create_matrix(2, 3, &A);

  double det;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null_matrix) {
  double det;
  int res = s21_determinant(NULL, &det);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
}
END_TEST

START_TEST(test_determinant_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int res = s21_determinant(&A, NULL);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_no_mem_leak) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }

  double det;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(det, 1.0);  // det(I) = 1

  s21_remove_matrix(&A);
}
END_TEST

Suite *determinant_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_determinant");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_3x3);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_determinant_not_square);
  tcase_add_test(tc_limits, test_determinant_null_matrix);
  tcase_add_test(tc_limits, test_determinant_null_result);
  tcase_add_test(tc_limits, test_determinant_no_mem_leak);
  suite_add_tcase(s, tc_limits);

  return s;
}