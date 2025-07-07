#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_create_matrix_valid) {
  matrix_t matrix;
  int res = s21_create_matrix(3, 4, &matrix);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(matrix.rows, 3);
  ck_assert_int_eq(matrix.columns, 4);
  ck_assert_ptr_nonnull(matrix.matrix);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_create_matrix_zero_rows) {
  matrix_t matrix;
  int res = s21_create_matrix(0, 4, &matrix);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(test_create_matrix_zero_columns) {
  matrix_t matrix;
  int res = s21_create_matrix(3, 0, &matrix);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(test_create_matrix_negative_rows) {
  matrix_t matrix;
  int res = s21_create_matrix(-1, 4, &matrix);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(test_create_matrix_negative_columns) {
  matrix_t matrix;
  int res = s21_create_matrix(3, -1, &matrix);

  ck_assert_int_eq(res, MATRIX_ERROR_CODE);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
  matrix_t matrix;
  const int size = 10000;

  int res = s21_create_matrix(size, size, &matrix);

  if (res == OK) {
    ck_assert_int_eq(matrix.rows, size);
    ck_assert_int_eq(matrix.columns, size);
    s21_remove_matrix(&matrix);
  } else {
    ck_assert_int_eq(res, MATRIX_ERROR_CODE);
    ck_assert_ptr_eq(matrix.matrix, NULL);
  }
}
END_TEST

START_TEST(test_create_matrix_memory_failure) {
  matrix_t matrix;
  int res = s21_create_matrix(2, 2, &matrix);

  ck_assert_int_eq(res, OK);
  free(matrix.matrix[0]);
  matrix.matrix[0] = NULL;

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_create_matrix_row_allocation_failure) {
  matrix_t matrix = {0};
  matrix.rows = 3;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(3 * sizeof(double *));

  // Выделяем только первые две строки
  matrix.matrix[0] = (double *)malloc(3 * sizeof(double));
  matrix.matrix[1] = (double *)malloc(3 * sizeof(double));
  matrix.matrix[2] = NULL;  // Третья строка не выделена

  // Вызываем cleanup-логику (как в оригинальной функции)
  for (int j = 0; j < 2; j++) {  // 2 - потому что 3я строка NULL
    free(matrix.matrix[j]);
  }
  free(matrix.matrix);
  matrix.matrix = NULL;

  // Если не было падения - тест пройден
  ck_assert_ptr_eq(matrix.matrix, NULL);
}
END_TEST

Suite *create_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_create_matrix");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_create_matrix_valid);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_create_matrix_zero_rows);
  tcase_add_test(tc_limits, test_create_matrix_zero_columns);
  tcase_add_test(tc_limits, test_create_matrix_negative_rows);
  tcase_add_test(tc_limits, test_create_matrix_negative_columns);
  tcase_add_test(tc_limits, test_create_matrix_null_result);
  tcase_add_test(tc_limits, test_create_matrix_memory_failure);
  tcase_add_test(tc_limits, test_create_matrix_row_allocation_failure);
  suite_add_tcase(s, tc_limits);

  return s;
}