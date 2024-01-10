#ifndef S21_MATRIX
#define S21_MATRIX

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define NO_ERR 0
#define MATRIX_ERR 1
#define CALC_ERR 2

#define EPSILON 0.0000001
#define MAX_PRECISION 7
#define SUCCESS 1
#define FAILURE 0

#define COPY_MATRIX_PTR(dest, src)                   \
  do {                                               \
    (dest).rows = (src)->rows;                       \
    (dest).columns = (src)->columns;                 \
    for (int32_t i = 0; i < (src)->rows; i++) {      \
      for (int32_t j = 0; j < (src)->columns; j++) { \
        (dest).matrix[i][j] = (src)->matrix[i][j];   \
      }                                              \
    }                                                \
  } while (0)

typedef double float64_t;
typedef struct matrix_struct {
  float64_t **matrix;
  int32_t rows;
  int32_t columns;
} matrix_t;

/*
  BASE OPERATIONS
*/

int32_t s21_create_matrix(int32_t rows, int32_t columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int32_t s21_eq_matrix(matrix_t *A, matrix_t *B);

/*
  ARITHMETIC
*/

int32_t s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int32_t s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int32_t s21_mult_number(matrix_t *A, float64_t number, matrix_t *result);
int32_t s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/*
  ANOTHER
*/

int32_t s21_transpose(matrix_t *A, matrix_t *result);
int32_t s21_calc_complements(matrix_t *A, matrix_t *result);
int32_t s21_determinant(matrix_t *A, float64_t *result);
int32_t s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif