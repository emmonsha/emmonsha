#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = MATRIX_OK;
  if (is_mtrx(A)) {
    status = MATRIX_FAILURE;
  }

  if (!status) {
    status = square_matrix(A);
  }

  if (!status) {
    *result = det_calc(A);
  }

  return status;
}

double det_calc(matrix_t *A) {
  double matrix_det = 0;

  if (A->rows == 1) {
    matrix_det = A->matrix[0][0];
  } else {
    for (int i = 0; i < A->columns; i++) {
      matrix_t sub_matrix = {};
      sub_matrix = fsub_matrix(A, 0, i);
      matrix_det += complement(0, i) * A->matrix[0][i] * det_calc(&sub_matrix);
      s21_remove_matrix(&sub_matrix);
    }
  }

  if (fabs(matrix_det) < 1e-7) {
    matrix_det = 0.0;
  }
  return matrix_det;
}