#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(equal_case) {
  srand((unsigned int)time(NULL));
  int rows = rand() % 100 + 1;
  int usleep(__useconds_t usec);
  usleep(150000);
  int columns = rand() % 100 + 1;

  matrix_t A = {0};

  s21_create_matrix(rows, columns, &A);

  s21_fill_matrices(1, &A);

  matrix_t B = {0};
  s21_create_matrix(rows, columns, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = B.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_all_matrices(2, &A, &B);
}
END_TEST

START_TEST(not_equal_case) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int columns1 = rand() % 100 + 1;
  s21_create_matrix(rows1, columns1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < columns1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), 0);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST
END_TEST

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("matrix_eq_suite");
  TCase *tc = tcase_create("case_eq_matrix");

  tcase_add_loop_test(tc, equal_case, 0, 10);
  tcase_add_loop_test(tc, not_equal_case, 0, 10);

  suite_add_tcase(s, tc);
  return s;
}