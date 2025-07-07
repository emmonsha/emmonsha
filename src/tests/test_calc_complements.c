#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(calc_complements_case) {
  srand((unsigned int)time(NULL));
  int rows = 4;
  int columns = 4;

  matrix_t A = {};

  s21_create_matrix(rows, columns, &A);

  A.matrix[0][0] = 34;
  A.matrix[0][1] = 234;
  A.matrix[0][2] = 2;
  A.matrix[0][3] = 1;

  A.matrix[1][0] = 3;
  A.matrix[1][1] = 34;
  A.matrix[1][2] = 5;
  A.matrix[1][3] = 0;

  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 8;
  A.matrix[2][3] = 0;

  A.matrix[3][0] = 3;
  A.matrix[3][1] = 2;
  A.matrix[3][2] = 0;
  A.matrix[3][3] = 0;

  matrix_t result = {};

  matrix_t cntrl_mtrx = {};

  s21_create_matrix(rows, columns, &cntrl_mtrx);

  cntrl_mtrx.matrix[0][0] = 0;
  cntrl_mtrx.matrix[0][1] = 0;
  cntrl_mtrx.matrix[0][2] = 0;
  cntrl_mtrx.matrix[0][3] = -723;

  cntrl_mtrx.matrix[1][0] = 16;
  cntrl_mtrx.matrix[1][1] = -24;
  cntrl_mtrx.matrix[1][2] = 9;
  cntrl_mtrx.matrix[1][3] = 5054;

  cntrl_mtrx.matrix[2][0] = -10;
  cntrl_mtrx.matrix[2][1] = 15;
  cntrl_mtrx.matrix[2][2] = -96;
  cntrl_mtrx.matrix[2][3] = -2978;

  cntrl_mtrx.matrix[3][0] = -237;
  cntrl_mtrx.matrix[3][1] = -6;
  cntrl_mtrx.matrix[3][2] = 183;
  cntrl_mtrx.matrix[3][3] = 9096;

  s21_calc_complements(&A, &result);

  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), 1);

  s21_remove_all_matrices(3, &A, &result, &cntrl_mtrx);
}
END_TEST

START_TEST(different_sizes_matrix_case) {
  int row = 10 + 1;

  int col = 10;

  matrix_t A = {};

  s21_create_matrix(row, col, &A);

  matrix_t result = {};

  ck_assert_int_eq(s21_calc_complements(&A, &result), 2);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(empty_matrix_case) {
  int size = 3;

  matrix_t A = {};
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = 0;
    }
  }

  matrix_t result = {};

  ck_assert_int_eq(s21_calc_complements(&A, &result), 0);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(zero_value_matrix_case) {
  srand((unsigned int)time(NULL));
  static int row = 2;
  static int col = 2;
  matrix_t A = {};

  s21_create_matrix(row, col, &A);
  static int value = 0;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = value;
      if (value == (row + 1) * (col + 1)) {
        value = 0;
      }
    }
  }

  row++;
  col++;

  matrix_t result = {};

  ck_assert_int_eq(s21_calc_complements(&A, &result), 0);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(test_normal) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &cntrl_mtrx);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  cntrl_mtrx.matrix[0][0] = 0;
  cntrl_mtrx.matrix[0][1] = 10;
  cntrl_mtrx.matrix[0][2] = -20;

  cntrl_mtrx.matrix[1][0] = 4;
  cntrl_mtrx.matrix[1][1] = -14;
  cntrl_mtrx.matrix[1][2] = 8;

  cntrl_mtrx.matrix[2][0] = -8;
  cntrl_mtrx.matrix[2][1] = -2;
  cntrl_mtrx.matrix[2][2] = 4;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&cntrl_mtrx);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_all) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t cntrl_mtrx = {};
  matrix_t B = {};

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 3, &cntrl_mtrx);

  int err = 0;

  err = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(MATRIX_FAILURE, err);

  err = s21_calc_complements(&A, &result);
  ck_assert_int_eq(MATRIX_CALC_ERROR, err);

  err = s21_calc_complements(&A, &result);
  ck_assert_int_eq(MATRIX_CALC_ERROR, err);

  s21_create_matrix(3, 3, &B);

  B.matrix[0][0] = 2;
  B.matrix[1][0] = 5;
  B.matrix[2][0] = 3;
  B.matrix[0][1] = 1;
  B.matrix[1][1] = -5;
  B.matrix[2][1] = 3.3;
  B.matrix[0][2] = -1;
  B.matrix[1][2] = 0;
  B.matrix[2][2] = 0.3;
  cntrl_mtrx.matrix[0][0] = -1.5;
  cntrl_mtrx.matrix[0][1] = -1.5;
  cntrl_mtrx.matrix[0][2] = 31.5;
  cntrl_mtrx.matrix[1][0] = -3.6;
  cntrl_mtrx.matrix[1][1] = 3.6;
  cntrl_mtrx.matrix[1][2] = -3.6;
  cntrl_mtrx.matrix[2][0] = -5;
  cntrl_mtrx.matrix[2][1] = -5;
  cntrl_mtrx.matrix[2][2] = -15;

  err = s21_calc_complements(&B, &result);
  ck_assert_int_eq(MATRIX_OK, err);
  err = s21_eq_matrix(&result, &cntrl_mtrx);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  matrix_t result1 = {};

  s21_create_matrix(-3, 3, &result1);
  err = s21_calc_complements(&A, &result1);

  ck_assert_int_eq(MATRIX_CALC_ERROR, err);

  s21_remove_matrix(&A);
  s21_remove_matrix(&cntrl_mtrx);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t A = {};
  matrix_t result = {};
  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t A = {};
  matrix_t result = {};
  int codec = s21_create_matrix(3, 4, &A);
  if (codec == 0) {
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_zero_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    cntrl_mtrx.matrix[0][0] = 0;
    cntrl_mtrx.matrix[0][1] = 0;
    cntrl_mtrx.matrix[0][2] = 0;

    cntrl_mtrx.matrix[1][0] = 0;
    cntrl_mtrx.matrix[1][1] = 0;
    cntrl_mtrx.matrix[1][2] = 0;

    cntrl_mtrx.matrix[2][0] = 0;
    cntrl_mtrx.matrix[2][1] = 0;
    cntrl_mtrx.matrix[2][2] = 0;

    matrix_t result = {};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST
START_TEST(test_identity_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1;
    A.matrix[1][1] = 1;
    A.matrix[2][2] = 1;

    cntrl_mtrx.matrix[0][0] = 1;
    cntrl_mtrx.matrix[0][1] = 0;
    cntrl_mtrx.matrix[0][2] = 0;

    cntrl_mtrx.matrix[1][0] = 0;
    cntrl_mtrx.matrix[1][1] = 1;
    cntrl_mtrx.matrix[1][2] = 0;

    cntrl_mtrx.matrix[2][0] = 0;
    cntrl_mtrx.matrix[2][1] = 0;
    cntrl_mtrx.matrix[2][2] = 1;

    matrix_t result = {};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_symmetric_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;

    A.matrix[1][0] = 2;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    A.matrix[2][0] = 3;
    A.matrix[2][1] = 5;
    A.matrix[2][2] = 6;

    cntrl_mtrx.matrix[0][0] = -1;
    cntrl_mtrx.matrix[0][1] = 3;
    cntrl_mtrx.matrix[0][2] = -2;

    cntrl_mtrx.matrix[1][0] = 3;
    cntrl_mtrx.matrix[1][1] = -3;
    cntrl_mtrx.matrix[1][2] = 1;

    cntrl_mtrx.matrix[2][0] = -2;
    cntrl_mtrx.matrix[2][1] = 1;
    cntrl_mtrx.matrix[2][2] = 0;

    matrix_t result = {0};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST
START_TEST(test_large_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(4, 4, &A);
  int code2 = s21_create_matrix(4, 4, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 4;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 8;
    A.matrix[0][3] = 6;

    A.matrix[1][0] = 1;
    A.matrix[1][1] = 5;
    A.matrix[1][2] = 3;
    A.matrix[1][3] = 9;

    A.matrix[2][0] = 7;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 2;
    A.matrix[2][3] = 4;

    A.matrix[3][0] = 6;
    A.matrix[3][1] = 8;
    A.matrix[3][2] = 1;
    A.matrix[3][3] = 3;

    cntrl_mtrx.matrix[0][0] = -38;
    cntrl_mtrx.matrix[0][1] = 34;
    cntrl_mtrx.matrix[0][2] = 487;
    cntrl_mtrx.matrix[0][3] = -177;

    cntrl_mtrx.matrix[1][0] = -164;
    cntrl_mtrx.matrix[1][1] = 2;
    cntrl_mtrx.matrix[1][2] = -214;
    cntrl_mtrx.matrix[1][3] = 394;

    cntrl_mtrx.matrix[2][0] = 342;
    cntrl_mtrx.matrix[2][1] = -306;
    cntrl_mtrx.matrix[2][2] = -258;
    cntrl_mtrx.matrix[2][3] = 218;

    cntrl_mtrx.matrix[3][0] = 112;
    cntrl_mtrx.matrix[3][1] = 334;
    cntrl_mtrx.matrix[3][2] = 12;
    cntrl_mtrx.matrix[3][3] = -202;

    matrix_t result = {0};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_mixed_values) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = -25.53;
    A.matrix[0][1] = 28.29;
    A.matrix[0][2] = -18.96;

    A.matrix[1][0] = 17.10;
    A.matrix[1][1] = 17.15;
    A.matrix[1][2] = 16.13;

    A.matrix[2][0] = 7.57;
    A.matrix[2][1] = -14.21;
    A.matrix[2][2] = 16.00;

    cntrl_mtrx.matrix[0][0] = 503.6073;
    cntrl_mtrx.matrix[0][1] = -151.4959;
    cntrl_mtrx.matrix[0][2] = -372.8165;

    cntrl_mtrx.matrix[1][0] = -183.2184;
    cntrl_mtrx.matrix[1][1] = -264.9528;
    cntrl_mtrx.matrix[1][2] = -148.626;

    cntrl_mtrx.matrix[2][0] = 781.4817;
    cntrl_mtrx.matrix[2][1] = 87.5829;
    cntrl_mtrx.matrix[2][2] = -921.5985;

    matrix_t result = {0};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_floating_point_values) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(2, 2, &A);
  int code2 = s21_create_matrix(2, 2, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1.5;
    A.matrix[0][1] = 0.2;

    A.matrix[1][0] = 0.8;
    A.matrix[1][1] = 2.0;

    cntrl_mtrx.matrix[0][0] = 2.0;
    cntrl_mtrx.matrix[0][1] = -0.8;

    cntrl_mtrx.matrix[1][0] = -0.2;
    cntrl_mtrx.matrix[1][1] = 1.5;

    matrix_t result = {0};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_singular_matrix) {
  matrix_t A = {0};
  matrix_t cntrl_mtrx = {0};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;

    A.matrix[1][0] = 2.0;
    A.matrix[1][1] = 4.0;
    A.matrix[1][2] = 6.0;

    A.matrix[2][0] = 3.0;
    A.matrix[2][1] = 6.0;
    A.matrix[2][2] = 9.0;

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        cntrl_mtrx.matrix[i][j] = 0.0;
      }
    }

    matrix_t result = {0};
    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("calc_complements_suite");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, calc_complements_case);
  tcase_add_loop_test(tc, different_sizes_matrix_case, 0, 10);
  tcase_add_test(tc, empty_matrix_case);
  tcase_add_test(tc, zero_value_matrix_case);
  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_all);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_incorrect);
  tcase_add_test(tc, test_zero_matrix);
  tcase_add_test(tc, test_identity_matrix);
  tcase_add_test(tc, test_symmetric_matrix);
  tcase_add_test(tc, test_large_matrix);
  tcase_add_test(tc, test_mixed_values);
  tcase_add_test(tc, test_floating_point_values);
  tcase_add_test(tc, test_singular_matrix);

  suite_add_tcase(s, tc);
  return s;
}