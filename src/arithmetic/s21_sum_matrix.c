#include "../s21_matrix.h"

int32_t s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B) return MATRIX_ERR;
  if (A->rows != B->rows) return CALC_ERR;
  if (A->columns != B->columns) return CALC_ERR;
  if (s21_create_matrix(A->rows, A->columns, result)) return MATRIX_ERR;
  for (int32_t i = 0; i < result->rows; i++)
    for (int32_t j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  return NO_ERR;
}