#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status =
      SUCCESS;  // инициализирую переменную для вывода результата сравнения

  if (is_mtrx(A) || is_mtrx(B)) status = FAILURE;

  if (!compare_size(A, B)) {  // сверяем количество строк и столбцов матриц

    for (int i = 0; i < A->rows; i++) {  // проверяем значения строк матриц

      for (int j = 0; j < A->columns;
           j++) {  // входим в цикл для проверки значений матриц

        if (round(A->matrix[i][j] * pow(10, 7)) ==
            round(B->matrix[i][j] *
                  pow(10, 7))) {  // проверяем совпадение значений матриц
          status = SUCCESS;  // матрицы не равны если значения элементов Aij и
                             // Bij не равны
          break;
        }
      }
    }
  } else {
    status = FAILURE;
  }

  return status;
}