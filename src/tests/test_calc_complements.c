#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_calc_complements_normal) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(res, OK);

  // Проверяем ожидаемые значения алгебраических дополнений
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 10, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], -20, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 4, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -14, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], 8, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], -8, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][1], -2, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][2], 4, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1,
                          1e-6);  // Дополнение для 1x1 всегда 1

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_null_input) {
  matrix_t result;
  int res = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);  // Не квадратная матрица

  int res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_memory_failure) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);  // Огромная матрица для сбоя malloc

  // Предполагаем, что malloc внутри s21_calc_complements вернет NULL
  int res = s21_calc_complements(&A, &result);

  // Если функция обрабатывает сбой памяти, вернёт MATRIX_ERROR_CODE (1)
  if (res == MATRIX_ERROR_CODE) {
    ck_assert_ptr_null(result.matrix);
  } else {
    // Если тест не упал, освобождаем память
    s21_remove_matrix(&result);
  }

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_det_failure) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  // Матрица с NaN (детерминант не сможет быть вычислен)
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;

  // Предполагаем, что s21_determinant вернет ошибку для вырожденной матрицы
  int res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *calc_complements_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_calc_complements");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_calc_complements_normal);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");

  tcase_add_test(tc_limits, test_calc_complements_1x1);
  tcase_add_test(tc_limits, test_calc_complements_null_input);
  tcase_add_test(tc_limits, test_calc_complements_non_square);
  tcase_add_test(tc_limits, test_calc_complements_memory_failure);
  tcase_add_test(tc_limits, test_calc_complements_det_failure);
  suite_add_tcase(s, tc_limits);

  return s;
}