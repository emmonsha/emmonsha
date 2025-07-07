#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = MATRIX_OK;

  status = (is_mtrx(A) || result == NULL)
               ? MATRIX_FAILURE
               : s21_create_matrix(A->columns, A->rows, result);

  if (!status) {
    for (int i = 0; i < result->columns; i++) {
      for (int j = 0; j < result->rows; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return status;
}