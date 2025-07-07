#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(sum_equal_size_case) {
  srand((unsigned int)time(NULL));
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t cntrl_mtrx = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &cntrl_mtrx);
  s21_fill_matrices(2, &A, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      cntrl_mtrx.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), 1);

  s21_remove_all_matrices(4, &A, &B, &cntrl_mtrx, &result);
}

START_TEST(not_equal_sizes_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  usleep(150000);
  int xrows = rand() % 100 + 1;
  usleep(150000);
  int xcolumns = rand() % 100 + 1;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(xrows, xcolumns, &B);
  s21_fill_matrices(2, &A, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);

  s21_remove_all_matrices(3, &A, &B, &result);
}

START_TEST(empty_rows_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  usleep(150000);
  int xrows = rand() % 100 + 1;
  usleep(150000);
  int xcolumns = rand() % 100 + 1;
  srand(rows);
  if ((rand() % 2) == 0) rows = 0;
  srand(columns);
  if ((rand() % 2) == 0) columns = 0;
  srand(xrows);
  if ((rand() % 2) == 0) xrows = 0;

  if (rows != 0 && columns != 0 && xrows != 0) xcolumns = 0;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(xrows, xcolumns, &B);
  s21_fill_matrices(2, &A, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 1);

  s21_remove_all_matrices(3, &A, &B, &result);
}

Suite *suite_sum_matrix(void) {
  Suite *s = suite_create("matrix_sum_suite");
  TCase *tc = tcase_create("case_sum_matrix");

  for (int i = 0; i < 10; i++) {
    tcase_add_test(tc, sum_equal_size_case);
    tcase_add_test(tc, not_equal_sizes_case);
    tcase_add_test(tc, empty_rows_case);
  }

  suite_add_tcase(s, tc);
  return s;
}