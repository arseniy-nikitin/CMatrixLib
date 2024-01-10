#include "../s21_matrix.h"

int32_t gaussian_elimination(matrix_t *A, float64_t *sign);
int32_t get_row(matrix_t *A, int32_t row, int32_t col);
void swap_rows(matrix_t *A, int32_t row1, int32_t row2);

int32_t s21_determinant(matrix_t *A, float64_t *result) {
  if (!A || !result) return MATRIX_ERR;
  if (A->rows != A->columns) return CALC_ERR;
  if (A->rows == 1 || A->columns == 1) {
    *result = A->matrix[0][0];
    return NO_ERR;
  }
  float64_t sign = 1;
  matrix_t buf = {0};
  if (s21_create_matrix(A->rows, A->columns, &buf)) return MATRIX_ERR;
  COPY_MATRIX_PTR(buf, A);
  if (gaussian_elimination(&buf, &sign)) {
    s21_remove_matrix(&buf);
    *result = 0;
    return NO_ERR;
  }
  *result = sign;
  for (int32_t i = 0; i < buf.rows; i++) *result *= buf.matrix[i][i];
  s21_remove_matrix(&buf);
  return NO_ERR;
}

int32_t gaussian_elimination(matrix_t *A, float64_t *sign) {
  for (int32_t i = 0; i < A->rows; i++) {
    for (int32_t j = 0; j <= i; j++) {
      if (A->matrix[i][j] == 0 && i == j) {
        int32_t target = get_row(A, i, j);
        if (target == -1) return CALC_ERR;
        swap_rows(A, i, target);
        i--;
        *sign *= -1;
      } else if (A->matrix[i][j] != 0 && i != j) {
        float64_t actual = A->matrix[i][j];
        for (int32_t k = 0; k < A->columns; k++) {
          float64_t factor = -1 * (A->matrix[j][k] * actual / A->matrix[j][j]);
          A->matrix[i][k] += factor;
        }
      }
    }
  }
  return NO_ERR;
}

int32_t get_row(matrix_t *A, int32_t row, int32_t col) {
  int32_t pivot_row = 0;
  for (pivot_row = ++row; pivot_row < A->rows; pivot_row++)
    if (A->matrix[pivot_row][col]) return pivot_row;
  return -1;
}

void swap_rows(matrix_t *A, int32_t row1, int32_t row2) {
  float64_t *temp = A->matrix[row1];
  A->matrix[row1] = A->matrix[row2];
  A->matrix[row2] = temp;
}