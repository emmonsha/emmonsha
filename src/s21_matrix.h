#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define S21_MATRIX_SIZE_TYPE int
#define S21_MATRIX_STRUCT_TYPE double

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  int rows;
  int columns;
  double **matrix;
} matrix_t;

// enum {
#define MATRIX_OK 0
#define MATRIX_FAILURE 1
#define MATRIX_CALC_ERROR 2
//} matrix_return;

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// функции из задания
int s21_create_matrix(int row, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// вспомогательные функции
int compare_size(matrix_t *A, matrix_t *B);
int check_rows_columns(int rows, int columns);
int is_mtrx(matrix_t *A);
void s21_fill_matrices(int count, ...);
int float_compare(double a, double b);
int compare_sizes_for_mult(matrix_t *A, matrix_t *B);
int start_position(matrix_t *A);
matrix_t fsub_matrix(matrix_t *A, int row, int col);
double det_calc(matrix_t *A);
int square_matrix(matrix_t *A);
int complement(int row, int col);

#endif