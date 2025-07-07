#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(mult_valid_matrices_case) {
  srand((unsigned int)time(NULL));
  srand((unsigned int)time(NULL));
  int rows = rand() % 20 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 20 + 1;
  usleep(150000);
  int xcolumns = rand() % 20 + 21;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t cntrl_mtrx = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, xcolumns, &B);
  s21_create_matrix(rows, xcolumns, &cntrl_mtrx);
  s21_fill_matrices(2, &A, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < A.columns; k++) {
        cntrl_mtrx.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), 1);

  s21_remove_all_matrices(4, &A, &B, &cntrl_mtrx, &result);
}

START_TEST(mult_not_equal_sizes_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 20 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 20 + 1;
  usleep(150000);
  int xrows = rand() % 20 + 21;
  usleep(150000);
  int xcolumns = rand() % 20 + 21;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(xrows, xcolumns, &B);
  s21_fill_matrices(2, &A, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 2);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 2);

  s21_remove_all_matrices(3, &A, &B, &result);
}

START_TEST(mult_empty_rows_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  usleep(150000);

  int xcolumns = rand() % 100 + 1;
  srand(rows);
  if ((rand() % 2) == 0) rows = 0;
  srand(columns);
  if ((rand() % 2) == 0) columns = 0;
  srand(columns);
  if (rows != 0 && columns != 0) xcolumns = 0;

  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, xcolumns, &B);
  s21_fill_matrices(2, &A, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 1);

  s21_remove_all_matrices(3, &A, &B, &result);
}

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("matrix_multiplication_suite");
  TCase *tc = tcase_create("case_mult_matrix");

  tcase_add_loop_test(tc, mult_valid_matrices_case, 0, 10);
  tcase_add_loop_test(tc, mult_not_equal_sizes_case, 0, 10);
  tcase_add_loop_test(tc, mult_empty_rows_case, 0, 10);

  suite_add_tcase(s, tc);
  return s;
}