#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    if (result != NULL) {
      result->rows = 0;
      result->columns = 0;
      result->matrix = NULL;
    }
    return MATRIX_ERROR_CODE;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));

  if (result->matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
  } else {
    return MATRIX_ERROR_CODE;
  }
  return OK;
}