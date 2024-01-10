#include "../s21_matrix.h"

uint8_t fequal(float64_t a, float64_t b);

int32_t s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !B) return FAILURE;
  if (A->rows != B->rows) return FAILURE;
  if (A->columns != B->columns) return FAILURE;
  for (int32_t i = 0; i < A->rows; i++)
    for (int32_t j = 0; j < A->columns; j++)
      if (!fequal(A->matrix[i][j], B->matrix[i][j])) return FAILURE;
  return SUCCESS;
}

uint8_t fequal(float64_t a, float64_t b) {
  float64_t diff = fabs(a - b);
  if (a == b)
    return SUCCESS;
  else if (a == 0 && b == 0 && diff < (EPSILON * DBL_MIN))
    return SUCCESS;
  else
    return diff < EPSILON;
}