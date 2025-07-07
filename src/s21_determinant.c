#include "s21_matrix.h"

static void free_minor(matrix_t *minor) {
  if (minor && minor->matrix) {
    for (int i = 0; i < minor->rows; i++) {
      free(minor->matrix[i]);
    }
    free(minor->matrix);
    minor->matrix = NULL;
    minor->rows = 0;
    minor->columns = 0;
  }
}

static int get_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  if (!A || !minor || A->rows <= 1 || A->columns <= 1) {
    return MATRIX_ERROR_CODE;
  }
  minor->rows = A->rows - 1;
  minor->columns = A->columns - 1;
  minor->matrix = (double **)malloc(minor->rows * sizeof(double *));
  if (!minor->matrix) return MATRIX_ERROR_CODE;

  for (int i = 0; i < minor->rows; i++) {
    minor->matrix[i] = (double *)malloc(minor->columns * sizeof(double));
    if (!minor->matrix[i]) {
      for (int j = 0; j < i; j++) free(minor->matrix[j]);
      free(minor->matrix);
      return MATRIX_ERROR_CODE;
    }
  }
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

int s21_determinant(matrix_t *A, double *result) {
  if (!A || !result || A->rows != A->columns) return MATRIX_ERROR_CODE;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }
  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return OK;
  }

  *result = 0;
  for (int j = 0; j < A->columns; j++) {
    matrix_t minor;
    if (get_minor(A, &minor, 0, j) != 0) return MATRIX_ERROR_CODE;

    double minor_det;
    if (s21_determinant(&minor, &minor_det) != 0) {
      free_minor(&minor);
      return MATRIX_ERROR_CODE;
    }
    *result += (j % 2 ? -1 : 1) * A->matrix[0][j] * minor_det;
    free_minor(&minor);
  }
  return OK;
}