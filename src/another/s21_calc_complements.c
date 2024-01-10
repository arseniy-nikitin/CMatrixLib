#include "../s21_matrix.h"

void get_minor(matrix_t *A, matrix_t *M, int32_t row, int32_t col);

int32_t s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !result) return MATRIX_ERR;
  if (A->rows != A->columns) return CALC_ERR;
  if (s21_create_matrix(A->rows, A->columns, result)) return MATRIX_ERR;
  if (A->rows == 1 || A->columns == 1) {
    result->matrix[0][0] = 1;
    return NO_ERR;
  }
  matrix_t minor = {0};
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor)) {
    s21_remove_matrix(result);
    return MATRIX_ERR;
  }
  for (int32_t i = 0; i < A->rows; i++) {
    for (int32_t j = 0; j < A->columns; j++) {
      get_minor(A, &minor, i, j);
      float64_t det = 0;
      if (s21_determinant(&minor, &det)) {
        s21_remove_matrix(result);
        s21_remove_matrix(&minor);
        return CALC_ERR;
      }
      result->matrix[i][j] = det * pow(-1, i + j);
    }
  }
  s21_remove_matrix(&minor);
  return NO_ERR;
}

void get_minor(matrix_t *A, matrix_t *M, int32_t row, int32_t col) {
  int32_t minor_row = 0, minor_col = 0;
  for (int32_t i = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int32_t j = 0; j < A->columns; j++) {
      if (j == col) continue;
      M->matrix[minor_row][minor_col] = A->matrix[i][j];
      minor_col++;
    }
    minor_row++;
    minor_col = 0;
  }
}