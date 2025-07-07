#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return MATRIX_ERROR_CODE;
  }

  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return MATRIX_ERROR_CODE;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return MATRIX_ERROR_CODE;
  }

  int status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}