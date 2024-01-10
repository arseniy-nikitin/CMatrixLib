#include "../s21_matrix.h"

int32_t s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A) return MATRIX_ERR;
  if (s21_create_matrix(A->columns, A->rows, result)) return MATRIX_ERR;
  for (int32_t i = 0; i < A->columns; i++)
    for (int32_t j = 0; j < A->rows; j++)
      result->matrix[i][j] = A->matrix[j][i];
  return NO_ERR;
}