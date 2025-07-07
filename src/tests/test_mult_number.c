#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(mult_number_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  usleep(150000);
  int number = rand() % 10000 + 1;

  matrix_t A = {0};
  matrix_t cntrl_mtrx = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &cntrl_mtrx);
  s21_fill_matrices(1, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      cntrl_mtrx.matrix[i][j] = A.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), 1);

  s21_remove_all_matrices(3, &A, &cntrl_mtrx, &result);
}

START_TEST(mult_number_empty_rows_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;
  usleep(150000);
  if ((rand() % 2) == 0) rows = 0;
  srand(columns);
  if ((rand() % 2) == 0) columns = 0;

  if (rows != 0 && columns != 0) columns = 0;
  int number = rand() % 10000 + 1;

  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &A);
  s21_fill_matrices(1, &A);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), 1);

  s21_remove_all_matrices(2, &A, &result);
}

Suite *suite_mult_number(void) {
  Suite *s = suite_create("matrix_mult_number_suite");
  TCase *tc = tcase_create("case_mult_number");

  tcase_add_loop_test(tc, mult_number_case, 0, 20);
  tcase_add_loop_test(tc, mult_number_empty_rows_case, 0, 20);

  suite_add_tcase(s, tc);
  return s;
}