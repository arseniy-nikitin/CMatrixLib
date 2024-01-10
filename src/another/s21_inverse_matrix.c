#include "../s21_matrix.h"

int32_t s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !result) return MATRIX_ERR;
  if (A->rows != A->columns) return CALC_ERR;
  if (s21_create_matrix(A->rows, A->columns, result)) return MATRIX_ERR;
  if (A->rows == 1 || A->columns == 1) {
    if (A->matrix[0][0] == 0) {
      s21_remove_matrix(result);
      return CALC_ERR;
    }
    result->matrix[0][0] = 1 / A->matrix[0][0];
    return NO_ERR;
  }
  float64_t det = 0;
  if (s21_determinant(A, &det) || det == 0) return MATRIX_ERR;
  matrix_t com = {0};
  if (s21_calc_complements(A, &com)) {
    s21_remove_matrix(result);
    s21_remove_matrix(&com);
    return CALC_ERR;
  }
  matrix_t tsp = {0};
  if (s21_transpose(&com, &tsp)) {
    s21_remove_matrix(result);
    s21_remove_matrix(&com);
    s21_remove_matrix(&tsp);
    return MATRIX_ERR;
  }
  float64_t int_det = 1 / det;
  for (int32_t i = 0; i < A->rows; i++)
    for (int32_t j = 0; j < A->columns; j++)
      result->matrix[i][j] = tsp.matrix[i][j] * int_det;
  s21_remove_matrix(&com);
  s21_remove_matrix(&tsp);
  return NO_ERR;
}