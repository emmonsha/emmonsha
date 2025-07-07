#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A || !result || A->rows < 1 || A->columns < 1 || !A->matrix) {
    return MATRIX_ERROR_CODE;
  }

  int status = s21_create_matrix(A->columns, A->rows, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}