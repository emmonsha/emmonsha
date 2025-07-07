#include "s21_test.h"

START_TEST(normal) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 2;
    A.matrix[0][1] = 5;
    A.matrix[0][2] = 7;

    A.matrix[1][0] = 6;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;

    A.matrix[2][0] = 5;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = -3;

    cntrl_mtrx.matrix[0][0] = 1;
    cntrl_mtrx.matrix[0][1] = -1;
    cntrl_mtrx.matrix[0][2] = 1;

    cntrl_mtrx.matrix[1][0] = -38;
    cntrl_mtrx.matrix[1][1] = 41;
    cntrl_mtrx.matrix[1][2] = -34;

    cntrl_mtrx.matrix[2][0] = 27;
    cntrl_mtrx.matrix[2][1] = -29;
    cntrl_mtrx.matrix[2][2] = 24;

    matrix_t result = {0};

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(calc_inverse) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  matrix_t result = {};

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), MATRIX_OK);
  ck_assert_ptr_ne(A.matrix, NULL);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &cntrl_mtrx), MATRIX_OK);

  cntrl_mtrx.matrix[0][0] = 0;
  cntrl_mtrx.matrix[0][1] = -0.1;
  cntrl_mtrx.matrix[0][2] = 0.2;
  cntrl_mtrx.matrix[1][0] = -0.25;
  cntrl_mtrx.matrix[1][1] = 0.35;
  cntrl_mtrx.matrix[1][2] = 0.05;
  cntrl_mtrx.matrix[2][0] = 0.5;
  cntrl_mtrx.matrix[2][1] = -0.2;
  cntrl_mtrx.matrix[2][2] = -0.1;

  ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&cntrl_mtrx);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_inverse_hard) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t cntrl_mtrx = {};

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), MATRIX_OK);
  ck_assert_ptr_ne(A.matrix, NULL);
  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_ne(A.matrix[i], NULL);
  }

  A.matrix[0][0] = 72;
  A.matrix[0][1] = 41;
  A.matrix[0][2] = 3.16;
  A.matrix[1][0] = 13.02;
  A.matrix[1][1] = 15;
  A.matrix[1][2] = 900;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 14.009;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &cntrl_mtrx), MATRIX_OK);

  cntrl_mtrx.matrix[0][0] = -6089.8650000000 / -224544.961980;
  cntrl_mtrx.matrix[1][0] = 5217.6028200000 / -224544.961980;
  cntrl_mtrx.matrix[2][0] = 1.1400000000 / -224544.961980;
  cntrl_mtrx.matrix[0][1] = -552.2490000000 / -224544.961980;
  cntrl_mtrx.matrix[1][1] = 989.6880000000 / -224544.961980;
  cntrl_mtrx.matrix[2][1] = -258.0000000000 / -224544.961980;
  cntrl_mtrx.matrix[0][2] = 36852.6000000000 / -224544.961980;
  cntrl_mtrx.matrix[1][2] = -64758.8568000000 / -224544.961980;
  cntrl_mtrx.matrix[2][2] = 546.1800000000 / -224544.961980;

  ck_assert_int_eq(s21_eq_matrix(&cntrl_mtrx, &result), SUCCESS);
  s21_remove_all_matrices(3, &A, &cntrl_mtrx, &result);
}
END_TEST

START_TEST(calc_inverse_edge) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_create_matrix(3, 4, &A), MATRIX_OK);
  ck_assert_ptr_ne(A.matrix, NULL);
  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_ne(A.matrix[i], NULL);
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_CALC_ERROR);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), MATRIX_FAILURE);

  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(zero_det) {
  matrix_t A = {};
  matrix_t result = {};
  int codec = s21_create_matrix(1, 1, &A);
  if (!codec) {
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);

    s21_remove_all_matrices(2, &A, &result);
  }
}
END_TEST

START_TEST(inMATRIX_OK) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_FAILURE);
  s21_remove_all_matrices(2, &A, &result);
}
END_TEST

START_TEST(not_sqare) {
  matrix_t A = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 4, &A);
  if (!codec) {
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);
    s21_remove_all_matrices(2, &A, &result);
  }
}
END_TEST

START_TEST(inverse_all) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t cntrl_mtrx = {};
  matrix_t B = {};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 3, &cntrl_mtrx);
  int err = 0;

  err = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(MATRIX_FAILURE, err);
  err = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(MATRIX_FAILURE, err);
  err = s21_inverse_matrix(&A, &result);
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

  cntrl_mtrx.matrix[0][0] = -1.5 / -36;
  cntrl_mtrx.matrix[1][0] = -1.5 / -36;
  cntrl_mtrx.matrix[2][0] = 31.5 / -36;
  cntrl_mtrx.matrix[0][1] = -3.6 / -36;
  cntrl_mtrx.matrix[1][1] = 3.6 / -36;
  cntrl_mtrx.matrix[2][1] = -3.6 / -36;
  cntrl_mtrx.matrix[0][2] = -5. / -36;
  cntrl_mtrx.matrix[1][2] = -5. / -36;
  cntrl_mtrx.matrix[2][2] = -15. / -36;

  err = s21_inverse_matrix(&B, &result);
  ck_assert_int_eq(MATRIX_OK, err);
  err = s21_eq_matrix(&result, &cntrl_mtrx);
  ck_assert_int_eq(SUCCESS, err);

  // cntrl_mtrx.matrix[2][2] = -14. / -36;
  // err = s21_inverse_matrix(&B, &result);
  // ck_assert_int_eq(MATRIX_OK, err);

  // err = s21_eq_matrix(&result, &cntrl_mtrx);
  // ck_assert_int_eq(MATRIX_FAILURE, err);

  // B.matrix[0][2] = 0;
  // B.matrix[1][2] = 0;
  // B.matrix[2][2] = 0;
  // err = s21_inverse_matrix(&B, &result);
  // ck_assert_int_eq(MATRIX_CALC_ERROR, err);

  // matrix_t C = {};
  // s21_create_matrix(-3, 3, &C);
  // err = s21_inverse_matrix(&C, &result);
  // ck_assert_int_eq(MATRIX_FAILURE, err);

  s21_remove_matrix(&A);
  s21_remove_matrix(&cntrl_mtrx);
  s21_remove_matrix(&result);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_identity_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(3, 3, &A);
  int code2 = s21_create_matrix(3, 3, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1;
    A.matrix[1][1] = 1;
    A.matrix[2][2] = 1;

    cntrl_mtrx.matrix[0][0] = 1;
    cntrl_mtrx.matrix[1][1] = 1;
    cntrl_mtrx.matrix[2][2] = 1;

    matrix_t result = {0};
    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }

  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_inverse_random_matrix) {
  matrix_t A = {};
  matrix_t cntrl_mtrx = {};
  int code1 = s21_create_matrix(2, 2, &A);
  int code2 = s21_create_matrix(2, 2, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 1.5;
    A.matrix[0][1] = 0.2;

    A.matrix[1][0] = 0.8;
    A.matrix[1][1] = 2.0;

    cntrl_mtrx.matrix[0][0] = 0.704225;
    cntrl_mtrx.matrix[0][1] = -0.070423;

    cntrl_mtrx.matrix[1][0] = -0.281690;
    cntrl_mtrx.matrix[1][1] = 0.528169;

    matrix_t result = {0};
    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, MATRIX_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), SUCCESS);

    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

START_TEST(test_inverse_singular_matrix) {
  matrix_t A = {};
  matrix_t result = {};
  int code1 = s21_create_matrix(3, 3, &A);

  if (!code1) {
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;

    A.matrix[1][0] = 2.0;
    A.matrix[1][1] = 4.0;
    A.matrix[1][2] = 6.0;

    A.matrix[2][0] = 3.0;
    A.matrix[2][1] = 6.0;
    A.matrix[2][2] = 9.0;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, MATRIX_CALC_ERROR);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_zero_column_matrix) {
  matrix_t A = {};
  matrix_t result = {};
  int code1 = s21_create_matrix(2, 2, &A);

  if (!code1) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 0;

    A.matrix[1][0] = 2;
    A.matrix[1][1] = 0;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, MATRIX_CALC_ERROR);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_one) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t cntrl_mtrx = {0};
  int code1 = s21_create_matrix(1, 1, &A);
  int code2 = s21_create_matrix(1, 1, &cntrl_mtrx);

  if (!code1 && !code2) {
    A.matrix[0][0] = 3;
    cntrl_mtrx.matrix[0][0] = 1.0 / 3.0;
    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &cntrl_mtrx), SUCCESS);
    ck_assert_int_eq(code, MATRIX_OK);
    s21_remove_matrix(&result);
  }
  s21_remove_all_matrices(2, &A, &cntrl_mtrx);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("case_inverse_matrix");
  tcase_add_test(tc, normal);
  tcase_add_test(tc, not_sqare);
  tcase_add_test(tc, zero_det);
  tcase_add_test(tc, inMATRIX_OK);
  tcase_add_test(tc, calc_inverse);
  tcase_add_test(tc, calc_inverse_edge);
  tcase_add_test(tc, calc_inverse_hard);

  tcase_add_test(tc, inverse_all);
  tcase_add_test(tc, test_inverse_identity_matrix);
  tcase_add_test(tc, test_inverse_random_matrix);
  tcase_add_test(tc, test_inverse_singular_matrix);
  tcase_add_test(tc, test_inverse_zero_column_matrix);
  tcase_add_test(tc, test_inverse_one);

  suite_add_tcase(s, tc);
  return s;
}