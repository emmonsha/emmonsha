#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_remove_matrix_valid) {
  matrix_t matrix;
  s21_create_matrix(3, 4, &matrix);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      matrix.matrix[i][j] = i * 3 + j;
    }
  }
  ck_assert_ptr_nonnull(matrix.matrix);

  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(test_remove_null_matrix) {
  matrix_t matrix = {0};
  matrix.rows = 3;
  matrix.columns = 4;
  matrix.matrix = NULL;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(test_remove_null_pointer) {
  s21_remove_matrix(NULL);

  ck_assert(1);
}
END_TEST

START_TEST(test_remove_partially_allocated) {
  matrix_t matrix;
  matrix.rows = 3;
  matrix.columns = 4;

  matrix.matrix = (double **)malloc(3 * sizeof(double *));

  matrix.matrix[0] = (double *)malloc(4 * sizeof(double));

  matrix.matrix[1] = NULL;
  matrix.matrix[2] = NULL;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

Suite *remove_matrix_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("s21_remove_matrix");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_remove_matrix_valid);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_remove_null_matrix);
  tcase_add_test(tc_limits, test_remove_null_pointer);
  tcase_add_test(tc_limits, test_remove_partially_allocated);
  suite_add_tcase(s, tc_limits);

  return s;
}