#include "../s21_matrix.h"

int32_t s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B) return MATRIX_ERR;
  if (A->columns != B->rows) return CALC_ERR;
  if (s21_create_matrix(A->rows, B->columns, result)) return MATRIX_ERR;
  for (int32_t i = 0; i < A->rows; i++)
    for (int32_t j = 0; j < B->columns; j++)
      for (int32_t k = 0; k < A->columns; k++)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  return NO_ERR;
}