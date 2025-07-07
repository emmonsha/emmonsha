#include "s21_test.h"

int main(void) {
  Suite *list_cases[] = {suite_eq_matrix(),      suite_sum_matrix(),
                         suite_sub_matrix(),     suite_mult_matrix(),
                         suite_mult_number(),    suite_transpose_matrix(),
                         suite_determinant(),    suite_calc_complements(),
                         suite_inverse_matrix(), NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
  return 0;
}

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}
