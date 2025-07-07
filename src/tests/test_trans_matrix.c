#include "s21_test.h"

START_TEST(transpose_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 10 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 10 + 1;

  matrix_t A = {0};
  matrix_t cntrl_mtrx = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &cntrl_mtrx);
  s21_fill_matrices(1, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      cntrl_mtrx.matrix[j][i] = A.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), 1);

  s21_remove_all_matrices(3, &A, &cntrl_mtrx, &result);
}
END_TEST

START_TEST(transpose_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t A = {0};
  s21_create_matrix(rows, cols, &A);
  matrix_t cntrl_mtrx = {0};
  s21_create_matrix(cols, rows, &cntrl_mtrx);

  matrix_t result = {0};
  ck_assert_int_eq(s21_transpose(&A, &result), 1);

  s21_remove_all_matrices(3, &A, &result, &cntrl_mtrx);
}
END_TEST

START_TEST(transpose_empty_rows_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  srand(rows);
  rows = rand() % 2;
  if (rows != 0) columns = 0;

  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_fill_matrices(1, &A);

  ck_assert_int_eq(s21_transpose(&A, &result), 1);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(transpose_NULL_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  srand(rows);

  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(rows, columns, &A);
  s21_fill_matrices(1, &A);

  ck_assert_int_eq(s21_transpose(&A, NULL), 1);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("matrix_transpose_suite");
  TCase *tc = tcase_create("case_transpose_matrix");

  tcase_add_loop_test(tc, transpose_case, 0, 10);
  tcase_add_loop_test(tc, transpose_matrix2, 0, 10);
  tcase_add_loop_test(tc, transpose_empty_rows_case, 0, 10);
  tcase_add_loop_test(tc, transpose_NULL_case, 0, 3);

  suite_add_tcase(s, tc);
  return s;
}