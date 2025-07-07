#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(matrix_determinant_case) {
  int rows = 3;
  int columns = 3;

  matrix_t A = {};

  s21_create_matrix(rows, columns, &A);

  A.matrix[0][0] = 34;
  A.matrix[0][1] = 234;
  A.matrix[0][2] = 2;

  A.matrix[1][0] = 3;
  A.matrix[1][1] = 34;
  A.matrix[1][2] = 5;

  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 8;

  double result;
  s21_determinant(&A, &result);

  ck_assert_int_eq(result, 9096);

  s21_remove_all_matrices(1, &A);
}

START_TEST(empty_random_sizes_matrix_case) {
  srand((unsigned int)time(NULL));
  int row = rand() % 100 + 1;
  srand(row);
  int col = rand() % 100 + 1;

  matrix_t A = {};

  s21_create_matrix(row, col, &A);

  double result;

  ck_assert_int_eq(s21_determinant(&A, &result), 2);

  s21_remove_all_matrices(1, &A);
}

START_TEST(zero_determinant_matrix_case) {
  srand((unsigned int)time(NULL));
  static int row = 2;
  static int col = 2;
  matrix_t A = {};

  s21_create_matrix(row, col, &A);
  static int value = 0;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = value;
      if (value == row * col) {
        value = 0;
      }
    }
  }

  row++;
  col++;

  double result;
  s21_determinant(&A, &result);

  ck_assert_int_eq(result, 0);

  s21_remove_all_matrices(1, &A);
}

START_TEST(determinant1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-7);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-7);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant6) {
  const int size = 1;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -5, 1e-6);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant7) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  rows = -rows;
  s21_create_matrix(rows, rows, &m);
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant8) {
  matrix_t m = {0};
  int rows = 4;
  int columns = 5;
  s21_create_matrix(rows, columns, &m);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, 2);

  s21_remove_matrix(&m);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("matrix_determinant_suite");
  TCase *tc = tcase_create("case_matrix_determinant");

  tcase_add_test(tc, matrix_determinant_case);
  tcase_add_loop_test(tc, empty_random_sizes_matrix_case, 0, 5);
  tcase_add_loop_test(tc, zero_determinant_matrix_case, 0, 5);
  tcase_add_test(tc, determinant1);
  tcase_add_test(tc, determinant2);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_loop_test(tc, determinant7, 0, 10);
  tcase_add_test(tc, determinant8);

  suite_add_tcase(s, tc);
  return s;
}