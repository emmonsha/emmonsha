#include "s21_matrix.h"

void free_minor(matrix_t *minor) {
  if (minor) {
    s21_remove_matrix(minor);
  }
}

int get_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  if (!A || !minor || !A->matrix) return MATRIX_ERROR_CODE;
  if (A->rows <= 1 || A->columns <= 1) return MATRIX_ERROR_CODE;

  int status = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
  if (status != OK) return status;

  for (int i = 0, mi = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, mj = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor->matrix[mi][mj++] = A->matrix[i][j];
    }
    mi++;
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !result || A->rows != A->columns || A->rows <= 0) {
    return MATRIX_ERROR_CODE;
  }

  for (int i = 0; i < A->rows; i++) {
    if (!A->matrix[i]) return MATRIX_ERROR_CODE;
  }

  if (A->rows == 1) {
    int status = s21_create_matrix(1, 1, result);
    if (status != OK) return status;
    result->matrix[0][0] = 1;
    return OK;
  }

  int status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) return status;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = {0};
      status = get_minor(A, &minor, i, j);
      if (status != OK) {
        s21_remove_matrix(result);
        return status;
      }

      double det = 0;
      status = s21_determinant(&minor, &det);
      free_minor(&minor);
      if (status != OK) {
        s21_remove_matrix(result);
        return status;
      }

      result->matrix[i][j] = ((i + j) % 2 ? -1 : 1) * det;
    }
  }

  return OK;
}