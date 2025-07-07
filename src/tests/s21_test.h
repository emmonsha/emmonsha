#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../s21_matrix.h"

Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_matrix(void);
Suite *suite_mult_number(void);
Suite *suite_transpose_matrix(void);
Suite *suite_determinant(void);
Suite *suite_calc_complements(void);
Suite *suite_inverse_matrix(void);

void run_testcase(Suite *testcase);

double get_rand(double min, double max);

void s21_remove_all_matrices(int count, ...);

#endif  // S21_TEST_H
