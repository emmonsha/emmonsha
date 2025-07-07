#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !result || A->rows != A->columns || A->rows < 1) {
    return MATRIX_ERROR_CODE;
  }

  double det = 0.0;
  int status = s21_determinant(A, &det);
  if (status != OK || fabs(det) < 1e-7) {
    return MATRIX_ERROR_CODE;
  }

  if (A->rows == 1) {
    status = s21_create_matrix(1, 1, result);
    if (status != OK) return status;
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
  }

  matrix_t complements = {0};
  matrix_t adjugate = {0};

  status = s21_calc_complements(A, &complements);
  if (status != OK) {
    return status;
  }

  status = s21_transpose(&complements, &adjugate);
  if (status != OK) {
    return status;
  }

  status = s21_create_matrix(adjugate.rows, adjugate.columns, result);
  if (status != OK) {
    s21_remove_matrix(&complements);
    s21_remove_matrix(&adjugate);
    return status;
  }

  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = adjugate.matrix[i][j] / det;
    }
  }

  s21_remove_matrix(&complements);
  s21_remove_matrix(&adjugate);

  return 0;
}