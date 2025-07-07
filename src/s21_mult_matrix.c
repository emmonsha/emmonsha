#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result) return MATRIX_ERROR_CODE;

  if (A->columns != A->rows || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1) {
    return MATRIX_ERROR_CODE;
  }

  int status = s21_create_matrix(A->rows, B->columns, result);

  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}