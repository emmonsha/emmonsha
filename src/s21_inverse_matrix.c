#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = MATRIX_OK;

  status = (is_mtrx(A) || result == NULL) ? MATRIX_FAILURE : square_matrix(A);

  if (!status) {
    double determinant = det_calc(A);
    if (determinant != 0) {
      if (A->rows == 1 && A->matrix[0][0]) {
        status = s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      } else {
        matrix_t transposed = {};
        matrix_t complements = {};

        s21_calc_complements(A, &complements);
        s21_transpose(&complements, &transposed);
        s21_mult_number(&transposed, 1.0 / determinant, result);
        s21_remove_matrix(&complements);
        s21_remove_matrix(&transposed);
      }
    } else {
      status = MATRIX_CALC_ERROR;
    }
  }

  return status;
}