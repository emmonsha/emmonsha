#include "s21_matrix.h"

// сравнение размеров уже созданных матриц возвращает 0 если размеры равны и 1
// если нет
int compare_size(matrix_t *A, matrix_t *B) {
  return ((A->rows == B->rows && A->columns == B->columns) ? MATRIX_OK
                                                           : MATRIX_CALC_ERROR);
}
// колонки и строки если больше 0 то возвращает 0 (MATRIX_OK) если нет то
// возвращает 1
//(MATRIX_FAILURE),
int check_rows_columns(int rows, int columns) {
  return ((rows <= 0 || columns <= 0) ? MATRIX_FAILURE : MATRIX_OK);
}

// если матрицы нет возвращает 1, если матрица есть возвращает 0;
int is_mtrx(matrix_t *A) {
  return ((A == NULL || A->matrix == NULL || (A->rows <= 0 || A->columns <= 0))
              ? MATRIX_FAILURE
              : MATRIX_OK);
}
// проверка для функции умножения матриц в случае правильности матриц для
// умножения возвращает 0 в случае ошибки возвращает 2
int compare_sizes_for_mult(matrix_t *A, matrix_t *B) {
  return (A->columns != B->rows) ? MATRIX_CALC_ERROR : MATRIX_OK;
}

// функция для вычисления субматрицы
matrix_t fsub_matrix(matrix_t *A, int row, int col) {
  matrix_t fsub_matrix = {};
  s21_create_matrix(A->rows - 1, A->columns - 1, &fsub_matrix);

  int sub_row = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }
    int sub_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) {
        continue;
      }
      fsub_matrix.matrix[sub_row][sub_col] = A->matrix[i][j];

      sub_col++;
    }

    sub_row++;
  }
  return fsub_matrix;
}

int square_matrix(matrix_t *A) {
  return ((A->rows == A->columns) ? MATRIX_OK : MATRIX_CALC_ERROR);
}

int complement(int row, int col) { return (((row + col) % 2 == 0) ? 1 : -1); }