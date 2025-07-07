#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = MATRIX_OK;

  if ((!is_mtrx(A) && !is_mtrx(B)) || result == NULL) {
    if (!compare_size(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      status = MATRIX_CALC_ERROR;
    }
  } else {
    status = MATRIX_FAILURE;
  }

  return status;
}