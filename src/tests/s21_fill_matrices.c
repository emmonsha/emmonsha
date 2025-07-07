#include "../s21_matrix.h"
#include "s21_test.h"

// Функция с неопределенным количеством структур

void s21_fill_matrices(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int k = 0; k < count; k++) {
    matrix_t *current_mtrx = va_arg(args, matrix_t *);

    for (int i = 0; i < current_mtrx->rows; i++) {
      for (int j = 0; j < current_mtrx->columns; j++) {
        double rand_val = get_rand(DBL_MIN, DBL_MAX);
        current_mtrx->matrix[i][j] = rand_val;
      }
    }
  }

  va_end(args);
}

void s21_remove_all_matrices(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int k = 0; k < count; k++) {
    matrix_t *current_mtrx = va_arg(args, matrix_t *);
    s21_remove_matrix(current_mtrx);
  }

  va_end(args);
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}