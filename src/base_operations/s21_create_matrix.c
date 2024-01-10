#include "../s21_matrix.h"

int32_t s21_create_matrix(int32_t rows, int32_t columns, matrix_t *result) {
  if (result == NULL) return MATRIX_ERR;
  if (rows < 1 || columns < 1) return MATRIX_ERR;
  result->matrix = (float64_t **)calloc(rows, sizeof(float64_t *));
  if (result->matrix == NULL) return MATRIX_ERR;
  result->rows = rows;
  result->columns = columns;
  for (int32_t i = 0; i < rows; i++) {
    result->matrix[i] = (float64_t *)calloc(columns, sizeof(float64_t));
    if (result->matrix[i] == NULL) {
      s21_remove_matrix(result);
      return MATRIX_ERR;
    }
  }
  return NO_ERR;
}