#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = MATRIX_OK;

  status = (is_mtrx(A) || result == NULL) ? MATRIX_FAILURE : square_matrix(A);

  if (!status) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t buff = fsub_matrix(A, i, j);
        result->matrix[i][j] = complement(i, j) * det_calc(&buff);

        s21_remove_matrix(&buff);
      }
    }
  }

  return status;
}