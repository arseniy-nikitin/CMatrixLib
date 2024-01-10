#include "../s21_matrix.h"

int32_t s21_mult_number(matrix_t *A, float64_t number, matrix_t *result) {
  if (!A) return MATRIX_ERR;
  if (s21_create_matrix(A->rows, A->columns, result)) return MATRIX_ERR;
  for (int32_t i = 0; i < result->rows; i++)
    for (int32_t j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  return NO_ERR;
}