#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = MATRIX_OK;

  if (is_mtrx(A) || is_mtrx(B) || result == NULL) {
    status = MATRIX_FAILURE;
  }

  if (!status) {
    status = compare_sizes_for_mult(A, B);
  }

  if (!status) {
    status = s21_create_matrix(A->rows, B->columns, result);
  }

  if (!status) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return status;
}