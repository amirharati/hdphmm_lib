// file: $isip/class/math/matrix/MMatrix/mmat_13.cc
// version: $Id: mmat_13.cc 10675 2009-07-21 01:13:30Z tm334 $
//

// isip include files
//
#include "MMatrix.h"
#include "MMatrixDiagnose.h"

//-----------------------------------------------------------------------------
//
// define the argument matrices
//   (nrows, ncols, elements)
//
// note: imaginary parts are in the second half of the array
//-----------------------------------------------------------------------------

double MMAT_ARG_MATRICES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // matrices with zero imaginary part
  //
  // A: a full 4x4 non-singular matrix
  //
  {4, 4,    3, 4, 7, 2, 3, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // B: a diagonal 4x4 non-singular matrix
  //
  {4, 4,    5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C: a symmetric 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 3, 4, 2, 7, 6, 1, 3, 6, 8, 3, 4, 1, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // D: a lower triangular 4x4 non-singular matrix
  //
  {4, 4,    5, 0, 0, 0, 2, 2, 0, 0, 3, 6, 3, 0, 4, 6, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E: a upper triangular 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 3, 4, 0, 2, 6, 6, 0, 0, 3, 3, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F: a full 4x4 singular matrix
  //
  {4, 4,    3, 4, 3, 2, 5, 7, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18,
            0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  0,  0,  0,  0},

  // G: a full 4x2 matrix
  //
  {4, 2,    4, 5, 7, 2, 3, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H: a full 2x4 matrix
  //
  {2, 4,    4, 7, 3, 2, 5, 2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrices with non-zero imaginary part
  //
  // I: a full 4x4 non-singular matrix
  //
  {4, 4,    2, 9, 1, 4, 3, 5, 8, 1, 8, 4, 9, 3, 4, 8, 7, 2,
            4, 5, 1, 6, 7, 9, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8},

  // J: a diagonal 4x4 non-singular matrix
  //
  {4, 4,    9, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3},

  // K: a symmetric 4x4 non-singular matrix
  //
  {4, 4,    2, 7, 1, 3, 7, 5, 2, 4, 1, 2, 7, 9, 3, 4, 9, 6,
            1, 3, 5, 2, 3, 7, 4, 1, 5, 4, 3, 6, 2, 1, 6, 2},

  // L: a lower triangular 4x4 non-singular matrix
  //
  {4, 4,    2, 0, 0, 0, 4, 1, 0, 0, 6, 7, 9, 0, 4, 2, 3, 8,
            6, 0, 0, 0, 9, 4, 0, 0, 6, 6, 1, 0, 8, 9, 3, 1},

  // M: a upper triangular 4x4 non-singular matrix
  //
  {4, 4,    8, 9, 1, 9, 0, 9, 3, 5, 0, 0, 2, 8, 0, 0, 0, 4,
            3, 7, 5, 6, 0, 6, 3, 7, 0, 0, 3, 8, 0, 0, 0, 1},

  // N: a full 4x4 singular matrix
  //
  {4, 4,    2, 6, 4, 6, 3, 8, 3, 9, 1, 6, 6, 3, 1, 3, 2, 3,
            4, 6, 6, 8, 8, 1, 5, 8, 6, 3, 1, 4, 2, 3, 3, 4},

  // O: a full 4x2 matrix
  //
  {4, 2,    7, 1, 6, 2, 6, 3, 2, 8, 8, 6, 3, 3, 6, 8, 5, 4,
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P: a full 2x4 matrix
  //
  {2, 4,    8, 4, 2, 3, 1, 6, 2, 8, 6, 3, 3, 1, 2, 7, 4, 5,
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//-----------------------------------------------------------------------------
//
// define types of the argument matrices
//
//-----------------------------------------------------------------------------

Integral::MTYPE MMAT_ARG_MAT_TYPES [MMAT_NUM_MATS_TOTAL] = {

  // matrices with zero imaginary part
  //
  // A: a full 4x4 non-singular matrix
  //
  Integral::FULL,

  // B: a diagonal 4x4 non-singular matrix
  //
  Integral::DIAGONAL,

  // C: a symmetric 4x4 non-singular matrix
  //
  Integral::SYMMETRIC,

  // D: a lower triangular 4x4 non-singular matrix
  //
  Integral::LOWER_TRIANGULAR,

  // E: a upper triangular 4x4 non-singular matrix
  //
  Integral::UPPER_TRIANGULAR,

  // F: a full 4x4 singular matrix
  //
  Integral::FULL,

  // G: a full 4x2 matrix
  //
  Integral::FULL,

  // H: a full 2x4 matrix
  //
  Integral::FULL,

  // matrices with non-zero imaginary part
  //
  // I: a full 4x4 non-singular matrix
  //
  Integral::FULL,

  // J: a diagonal 4x4 non-singular matrix
  //
  Integral::DIAGONAL,

  // K: a symmetric 4x4 non-singular matrix
  //
  Integral::SYMMETRIC,

  // L: a lower triangular 4x4 non-singular matrix
  //
  Integral::LOWER_TRIANGULAR,

  // M: a upper triangular 4x4 non-singular matrix
  //
  Integral::UPPER_TRIANGULAR,

  // N: a full 4x4 singular matrix
  //
  Integral::FULL,

  // O: a full 4x2 matrix
  //
  Integral::FULL,

  // P: a full 2x4 matrix
  //
  Integral::FULL,
};

//-----------------------------------------------------------------------------
//
// define the results of operations:
//    F(matrix, scalar) -> scalar
//
//-----------------------------------------------------------------------------

// is the type possible?
//
bool8 MMAT_IS_TYPE_POSSIBLE_RES [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_TYPES] = {

  // can A be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can B be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, true, true, true, true, true},

  // can C be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, true, false, false, true},

  // can D be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGL, UPPER_TRIANGLEE ?
  //
  {true, false, false, true, false, true},

  // can E be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, true, true},

  // can F be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can G be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can H be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can I be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can J be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, true, true, true, true, true},

  // can K be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, true, false, false, true},

  // can L be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGL, UPPER_TRIANGLEE ?
  //
  {true, false, false, true, false, true},

  // can M be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, true, true},

  // can N be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can O be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true},

  // can P be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE ?
  //
  {true, false, false, false, false, true}
};

// is the matrix diagonal?
//
bool8 MMAT_IS_DIAGONAL_RES [MMAT_NUM_MATS_TOTAL] = {

  // can A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P be a DIAG?
  //
  false, true, false, false, false, false, false, false,
  false, true, false, false, false, false, false, false
};

// is the matrx symmetric?
//
bool8 MMAT_IS_SYMMETRIC_RES [MMAT_NUM_MATS_TOTAL] = {

  // can A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P be a SYMMETRIC?
  //
  false, true, true, false, false, false, false, false,
  false, true, true, false, false, false, false, false
};

// is the matrix singular?
//
bool8 MMAT_IS_SINGULAR_RES[MMAT_NUM_MATS_TOTAL] = {

  // is A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P square?
  //
  false, false, false, false, false, true, false, false,
  false, false, false, false, false, true, false, false
};

// is the matrix lower_triangle?
//
bool8 MMAT_IS_LOWERTRIANGULAR_RES [MMAT_NUM_MATS_TOTAL] = {

  // can A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P be a LOWER_TRIANGLE?
  //
  false, true, false, true, false, false, false, false,
  false, true, false, true, false, false, false, false
};

// is the matrix upper_triangle?
//
bool8 MMAT_IS_UPPERTRIANGULAR_RES [MMAT_NUM_MATS_TOTAL] = {

  // can A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P be a UPPER_TRIANGLE?
  //
  false, true, false, false, true, false, false, false,
  false, true, false, false, true, false, false, false
};

float64 MMAT_IDENTITY_MATRICES [MMAT_MAT_SIZE] = {

  // a full 4x4 identity matrix
  //
  4, 4,    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

};

float64 MMAT_ORTHOGONAL_MATRICES [MMAT_MAT_SIZE] = {

  // a full 4x4 orthogonal matrix
  //
  4, 4,    1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1,
           0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0
};

// is the type possible?
//
bool8 MMAT_CHANGE_TYPE_RES [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_TYPES] = {

  // can A be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

  // can B be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, true, true, true, true, true},

  // can C be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGL, UPPER_TRIANGLEE, SPARSE ?
  //
  {true, false, true, false, false, true},

  // can D be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, true, false, true},

  // can E be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, true, true},

  // can F be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, true, true},

  // can G be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

  // can H be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

  // can I be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

  // can J be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, true, true, true, true, true},

  // can K be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGL, UPPER_TRIANGLEE, SPARSE ?
  //
  {true, false, true, false, false, true},

  // can L be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, true, false, true},

  // can M be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, true, true},

  // can N be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, true, true},

  // can O be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

  // can P be a FULL, DIAG, SYMMETRIC, LOWER_TRIANGLE, UPPER_TRIANGLE, SPARSE ?
  //
  {true, false, false, false, false, true},

};

// test nextZero result
//
float64 MMAT_NEXT_ZERO_ARG[MMAT_NEXT_ZERO_SIZE] = {

  // start position
  //
  1, 0,
};

float64 MMAT_NEXT_ZERO_RES[MMAT_NUM_MATS_TOTAL * 2] = {

  // A, row and column index
  //
  -1, -1,

  // B, row and column index
  //
  1, 2,

  // C, row and column index
  //
  -1, -1,

  // D, row and column index
  //
  1, 2,

  // E, row and column index
  //
  2, 0,

  // F, row and column index
  //
  -1, -1,

  // G, row and column index
  //
  -1, -1,

  // H, row and column index
  //
  -1, -1,

  // I, row and column index
  //
  -1, -1,

  // J, row and column index
  //
  1, 2,

  // K, row and column index
  //
  -1, -1,

  // L, row and column index
  //
  1, 2,

  // M, row and column index
  //
  2, 0,

  // N, row and column index
  //
  -1, -1,

  // O, row and column index
  //
  -1, -1,

  // P, row and column index
  //
  -1, -1,
};

// test nextNonZero result
//
float64 MMAT_NEXT_NONZERO_ARG[MMAT_NEXT_NONZERO_SIZE] = {

  // start position
  //
  1, 1,
};

float64 MMAT_NEXT_NONZERO_RES[MMAT_NUM_MATS_TOTAL * 4] = {

  // A
  //
  6, 1, 2, 0,

  // B
  //
  3, 2, 2, 0,

  // C
  //
  6, 1, 2, 0,

  // D
  //
  3, 2, 0, 0,

  // E
  //
  6, 1, 2, 0,

  // F
  //
  8, 1, 2, 0,

  // G
  //
  3, 2, 0, 0,

  // H
  //
  9, 1, 2, 0,

  // I
  //
  8, 1, 2, 5,

  // J
  //
  1, 2, 2, 5,

  // K
  //
  2, 1, 2, 4,

  // L
  //
  6, 2, 0, 6,

  // M
  //
  3, 1, 2, 3,

  // N
  //
  3, 1, 2, 5,

  // O
  //
  6, 2, 0, 6,

  // P
  //
  2, 1, 2, 4,
};

// is the matrix square?
//
bool8 MMAT_IS_SQUARE_RES[MMAT_NUM_MATS_TOTAL] = {

  // is A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P square?
  //
  true, true, true, true, true, true, false, false,
  true, true, true, true, true, true, false, false

};

// a clear matrix
//
float64 MMAT_CLEAR_RES [MMAT_MAT_SIZE] = {
  4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// test changing dimension
//
float64 MMAT_SET_DIM_RES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // matrix A
  //
  {3, 3,   3, 4, 7, 3, 5, 6, 8, 4, 1, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix B
  //
  {3, 3,   5, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix C
  //
  {3, 3,   5, 2, 3, 2, 7, 6, 3, 6, 8, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix D
  //
  {3, 3,   5, 0, 0, 2, 2, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix E
  //
  {3, 3,   5, 2, 3, 0, 2, 6, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix F
  //
  {3, 3,   3, 4, 3, 5, 7, 8, 9, 12, 9, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix G (dummy values)
  //
  {3, 3,   4, 5, 0, 7, 2, 0, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix H (dummy values)
  //
  {3, 3,   4, 7, 3, 5, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix I
  //
  {3, 3,   2, 9, 1,
           3, 5, 8,
           8, 4, 9,

           4, 5, 1,
           7, 9, 5,
           5, 6, 4,

           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix J
  //
  {3, 3,   9, 0, 0,
           0, 4, 0,
           0, 0, 1,
           3, 0, 0,
           0, 2, 0,
           0, 0, 5,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix K
  //
  {3, 3,   2, 7, 1,
           7, 5, 2,
           1, 2, 7,

           1, 3, 5,
           3, 7, 4,
           5, 4, 3,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


  // matrix L
  //
  {3, 3,   2, 0, 0,
           4, 1, 0,
           6, 7, 9,

           6, 0, 0,
           9, 4, 0,
           6, 6, 1,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix M
  //
  {3, 3,   8, 9, 1,
           0, 9, 3,
           0, 0, 2,

           3, 7, 5,
           0, 6, 3,
           0, 0, 3,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix N
  //
  {3, 3,   2, 6, 4,
           3, 8, 3,
	   1, 6, 6,

	   4, 6, 6,
	   8, 1, 5,
	   6, 3, 1,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


  // matrix O
  //
  {3, 3,   7, 1, 0,
	   6, 2, 0,
	   6, 3, 0,

	   8, 6, 0,
	   3, 3, 0,
	   6, 8, 0,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix P
  //
  {3, 3,   8, 4, 2,
	   1, 6, 2,
	   0, 0, 0,

	   6, 3, 3,
	   2, 7, 4,
	   0, 0, 0,

                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

float64 MMAT_SET_CAP_RES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // matrix A
  //
  {3, 3,   3, 4, 7, 3, 5, 6, 8, 4, 1, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix B
  //
  {3, 3,   5, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix C
  //
  {3, 3,   5, 2, 3, 2, 7, 6, 3, 6, 8, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix D
  //
  {3, 3,   5, 0, 0, 2, 2, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix E
  //
  {3, 3,   5, 2, 3, 0, 2, 6, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix F
  //
  {3, 3,   3, 4, 3, 5, 7, 8, 9, 12, 9, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix G (dummy values)
  //
  {3, 2,   4, 5, 7, 2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix H (dummy values)
  //
  {2, 3,   4, 7, 3, 5, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix I
  //
  {3, 3,   3, 4, 7, 3, 5, 6, 8, 4, 1, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix J
  //
  {3, 3,   5, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix K
  //
  {3, 3,   5, 2, 3, 2, 7, 6, 3, 6, 8, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix L
  //
  {3, 3,   5, 0, 0, 2, 2, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix M
  //
  {3, 3,   5, 2, 3, 0, 2, 6, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix N
  //
  {3, 3,   3, 4, 3, 5, 7, 8, 9, 12, 9, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix O (dummy values)
  //
  {3, 2,   4, 5, 7, 2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // matrix P (dummy values)
  //
  {2, 3,   4, 7, 3, 5, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// numEqual key values
//
float64 MMAT_NUM_EQUAL_VAL0 = 4;
float64 MMAT_NUM_EQUAL_VAL1 = 0;
complexdouble MMAT_NUM_EQUAL_VAL2 = complexdouble(9, 6);
complexdouble MMAT_NUM_EQUAL_VAL3 = complexdouble(0, 3);

// the number of elements equal to key0
//   in A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
//
int32 MMAT_NUM_EQUAL_RES0 [MMAT_NUM_MATS_TOTAL] = {
  3, 1, 3, 2, 2, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0
};

// the number of elements equal to key1
//
int32 MMAT_NUM_EQUAL_RES1 [MMAT_NUM_MATS_TOTAL] = {
  0, 12, 0, 6, 6, 0, 0, 0,
  0, 12, 0, 6, 6, 0, 0, 0
};

// the number of elements equal to key2
//
int32 MMAT_NUM_EQUAL_RES2 [MMAT_NUM_MATS_TOTAL] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 2, 0, 2, 0, 0, 0
};

// the number of elements equal to key3
//
int32 MMAT_NUM_EQUAL_RES3 [MMAT_NUM_MATS_TOTAL] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0
};

// numNotEqual key values
//
float64 MMAT_NUM_NOT_EQUAL_VAL0 = 3;
float64 MMAT_NUM_NOT_EQUAL_VAL1 = 0;
complexdouble MMAT_NUM_NOT_EQUAL_VAL2 = complexdouble(6, 6);
complexdouble MMAT_NUM_NOT_EQUAL_VAL3 = complexdouble(6, 3);

// the number of elements not equal to key0
//   in A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
//
int32 MMAT_NUM_NOT_EQUAL_RES0 [MMAT_NUM_MATS_TOTAL] = {
  13, 15, 12, 13, 13, 14, 6, 6,
  16, 16, 16, 16, 16, 16, 8, 8
};

// the number of elements not equal to key1
//   in A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
//
int32 MMAT_NUM_NOT_EQUAL_RES1 [MMAT_NUM_MATS_TOTAL] = {
  16, 4, 16, 10, 10, 16, 8, 8,
  16, 4, 16, 10, 10, 16, 8, 8
};

// the number of elements not equal to key2
//   in A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
//
int32 MMAT_NUM_NOT_EQUAL_RES2 [MMAT_NUM_MATS_TOTAL] = {
  16, 16, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 15, 16, 15, 7, 8
};

// the number of elements not equal to key3
//   in A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
//
int32 MMAT_NUM_NOT_EQUAL_RES3 [MMAT_NUM_MATS_TOTAL] = {
  16, 16, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 16, 15, 7, 8
};

// the relational operators key values
//
float64 MMAT_GT_VAL0 = 0;
float64 MMAT_GT_VAL1 = 1;
float64 MMAT_GE_VAL0 = 0;
float64 MMAT_GE_VAL1 = 2;
float64 MMAT_LT_VAL0 = 0;
float64 MMAT_LT_VAL1 = 9;
float64 MMAT_LE_VAL0 = 0;
float64 MMAT_LE_VAL1 = 8;
float64 MMAT_EQ_VAL0 = 0;
float64 MMAT_EQ_VAL1 = 6;
float64 MMAT_NE_VAL0 = 0;
float64 MMAT_NE_VAL1 = 1;
complexdouble MMAT_GT_VAL2 = complexdouble(0, 1);
complexdouble MMAT_GT_VAL3 = complexdouble(3, 2);
complexdouble MMAT_GE_VAL2 = complexdouble(1, 0);
complexdouble MMAT_GE_VAL3 = complexdouble(2, 4);
complexdouble MMAT_LT_VAL2 = complexdouble(0, 0);
complexdouble MMAT_LT_VAL3 = complexdouble(9, 1);
complexdouble MMAT_LE_VAL2 = complexdouble(0, 3);
complexdouble MMAT_LE_VAL3 = complexdouble(8, 3);
complexdouble MMAT_EQ_VAL2 = complexdouble(4, 0);
complexdouble MMAT_EQ_VAL3 = complexdouble(2, 6);
complexdouble MMAT_NE_VAL2 = complexdouble(0, 4);
complexdouble MMAT_NE_VAL3 = complexdouble(1, 5);

// greater than
//
bool8 MMAT_GT_RES0 [MMAT_NUM_MATS_TOTAL] = {
  true, false, true, false, false, true, true, true, 
  true, false, true, false, false, true, true, true, 
};

bool8 MMAT_GT_RES1 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, true, true, true, 
  true, false, true, false, false, true, true, true, 
};

bool8 MMAT_GT_RES2 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, true, true, true, 
  true, false, true, false, false, true, true, true, 
};

bool8 MMAT_GT_RES3 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

// greater than or equal to
//
bool8 MMAT_GE_RES0 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, true, true, true, 
  true, true, true, true, true, true, true, true, 
};

bool8 MMAT_GE_RES1 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, true, true, true, 
  false, false, true, false, false, true, true, true, 
};

bool8 MMAT_GE_RES2 [MMAT_NUM_MATS_TOTAL] = {
  true, false, true, false, false, true, true, true, 
  true, false, true, false, false, true, true, true, 
};

bool8 MMAT_GE_RES3 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

// less than
//
bool8 MMAT_LT_RES0 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LT_RES1 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LT_RES2 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LT_RES3 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, false, true, true, 
  false, false, false, false, false, false, false, false, 
};

// less than or equal to
//
bool8 MMAT_LE_RES0 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LE_RES1 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LE_RES2 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_LE_RES3 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

// equal to
//
bool8 MMAT_EQ_RES0 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

bool8 MMAT_EQ_RES1 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};
bool8 MMAT_EQ_RES2 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false
};

bool8 MMAT_EQ_RES3 [MMAT_NUM_MATS_TOTAL] = {
  false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false
};

// not equal to
//
bool8 MMAT_NE_RES0 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, true, true, true,
  true, true, true, true, true, true, true, true
};

bool8 MMAT_NE_RES1 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, true, true, true,
  true, true, true, true, true, true, true, true
};

bool8 MMAT_NE_RES2 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, true, true, true,
  true, true, true, true, true, true, true, true
};

bool8   MMAT_NE_RES3 [MMAT_NUM_MATS_TOTAL] = {
  true, true, true, true, true, true, true, true,
  true, true, true, true, true, true, true, true
};

// the minimum values (and locations)
//
double MMAT_MIN_RES [MMAT_NUM_MATS_TOTAL] [4] = {

  // A: row position of min, column position of min, min
  //
  {1, 3, 1, 0},

  // B: row position of min, column position of min, min
  //
  {0, 1, 0, 0},

  // C: row position of min, column position of min, min
  //
  {1, 3, 1, 0},

  // D: row position of min, column position of min, min
  //
  {0, 1, 0, 0},

  // E: row position of min, column position of min, min
  //
  {1, 0, 0, 0},

  // F: row position of min, column position of min, min
  //
  {0, 3, 2, 0},

  // G: row position of min, column position of min, min
  //
  {1, 1, 2, 0},

  // H: row position of min, column position of min, min
  //
  {0, 3, 2, 0},

  // I: row position of min, column position of min, min
  //
  {0, 2, 1, 1},

  // J: row position of min, column position of min, min
  //
  {0, 1, 0, 0},

  // K: row position of min, column position of min, min
  //
  {0, 0, 2, 1},

  // L: row position of min, column position of min, min
  //
  {0, 1, 0, 0},

  // M: row position of min, column position of min, min
  //
  {1, 0, 0, 0},

  // N: row position of min, column position of min, min
  //
  {3, 0, 1, 2},

  // O: row position of min, column position of min, min
  //
  {1, 1, 2, 3},

  // P: row position of min, column position of min, min
  //
  {1, 0, 1, 2}
};

// the maximum values (and locations)
//
float64 MMAT_MAX_RES [MMAT_NUM_MATS_TOTAL] [4] = {

  // A: row position of max, column position of max, max
  //
  {2, 0, 8, 0},

  // B: row position of max, column position of max, max
  //
  {0, 0, 5, 0},

  // C: row position of max, column position of max, max
  //
  {2, 2, 8, 0},

  // D: row position of max, column position of max, max
  //
  {2, 1, 6, 0},

  // E: row position of max, column position of max, max
  //
  {1, 2, 6, 0},

  // F: row position of max, column position of max, max
  //
  {3, 2, 24, 0},

  // G: row position of max, column position of max, max
  //
  {2, 1, 9, 0},

  // H: row position of max, column position of max, max
  //
  {1, 2, 9, 0},

  // I: row position of max, column position of max, max
  //
  {0, 1, 9, 5},

  // J: row position of max, column position of max, max
  //
  {0, 0, 9, 3},

  // K: row position of max, column position of max, max
  //
  {2, 3, 9, 6},

  // L: row position of max, column position of max, max
  //
  {1, 0, 4, 9},

  // M: row position of max, column position of max, max
  //
  {0, 1, 9, 7},

  // N: row position of max, column position of max, max
  //
  {1, 3, 9, 8},

  // O: row position of max, column position of max, max
  //
  {0, 0, 7, 8},

  // P: row position of max, column position of max, max
  //
  {0, 0, 8, 6}
};

// the minimum magnitude values (and locations)
//
float64 MMAT_MINMAG_RES [MMAT_NUM_MATS_TOTAL] [4] = {

  // A: row position of minMag, column position of minMag, minMag
  //
  {1, 3, 1, 0},

  // B: row position of minMag, column position of minMag, minMag
  //
  {0, 1, 0, 0},

  // C: row position of minMag, column position of minMag, minMag
  //
  {1, 3, 1, 0},

  // D: row position of minMag, column position of minMag, minMag
  //
  {0, 1, 0, 0},

  // E: row position of minMag, column position of minMag, minMag
  //
  {1, 0, 0, 0},

  // F: row position of minMag, column position of minMag, minMag
  //
  {0, 3, 2, 0},

  // G: row position of minMag, column position of minMag, minMag
  //
  {1, 1, 2, 0},

  // H: row position of minMag, column position of minMag, minMag
  //
  {0, 3, 2, 0},

  // I: row position of minMag, column position of minMag, minMag
  //
  {0, 2, 1.414214, 0},

  // J: row position of minMag, column position of minMag, minMag
  //
  {0, 1, 0, 0},

  // K: row position of minMag, column position of minMag, minMag
  //
  {0, 0, 2.236068, 0},

  // L: row position of minMag, column position of minMag, minMag
  //
  {0, 1, 0, 0},

  // M: row position of minMag, column position of minMag, minMag
  //
  {1, 0, 0, 0},

  // N: row position of minMag, column position of minMag, minMag
  //
  {3, 0, 2.236068, 0},

  // O: row position of minMag, column position of minMag, minMag
  //
  {1, 1, 3.605551, 0},

  // P: row position of minMag, column position of minMag, minMag
  //
  {1, 0, 2.236068, 0}
};

// the maximum magnitude values (and locations)
//
float64 MMAT_MAXMAG_RES [MMAT_NUM_MATS_TOTAL] [4] = {

  // A: row position of maxMag, column position of maxMag, maxMag
  //
  {2, 0, 8, 0},

  // B: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 0, 5, 0},

  // C: row position of maxMag, column position of maxMag, maxMag
  //
  {2, 2, 8, 0},

  // D: row position of maxMag, column position of maxMag, maxMag
  //
  {2, 1, 6, 0},

  // E: row position of maxMag, column position of maxMag, maxMag
  //
  {1, 2, 6, 0},

  // F: row position of maxMag, column position of maxMag, maxMag
  //
  {3, 2, 24, 0},

  // G: row position of maxMag, column position of maxMag, maxMag
  //
  {2, 1, 9, 0},

  // H: row position of maxMag, column position of maxMag, maxMag
  //
  {1, 2, 9, 0},

  // I: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 1, 10.29563, 0},

  // J: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 0, 9.486833, 0},

  // K: row position of maxMag, column position of maxMag, maxMag
  //
  {2, 3, 10.816654, 0},

  // L: row position of maxMag, column position of maxMag, maxMag
  //
  {1, 0, 9.848858, 0},

  // M: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 1, 11.401754, 0},

  // N: row position of maxMag, column position of maxMag, maxMag
  //
  {1, 3, 12.041595, 0},

  // O: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 0, 10.630146, 0},

  // P: row position of maxMag, column position of maxMag, maxMag
  //
  {0, 0, 10, 0}
};

// the determinants
//
float64 MMAT_DET_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // det(A), det(B), det(C), det(D), det(E), det(F)
  //
  1, 120, 22, 120, 120, 0,

  // det(G), det(H) (dummy values)
  //
  0, 0,

  // det(I), det(J), det(K), det(L), det(M), det(N)
  //
  1, 120, 22, 120, 120, 0,

  // det(O), det(P) (dummy values)
  //
  0, 0,

  // imaginary components of det(A), det(B), det(C), det(D), det(E), det(F)
  //
  0, 0, 0, 0, 0, 0,

  // imaginary components of det(G), det(H) (dummy values)
  //
  0, 0,

  // imaginary components of det(I), det(J), det(K), det(L), det(M), det(N)
  //
  0, 0, 0, 0, 0, 0,

  // imaginary components of det(O), det(P) (dummy values)
  //
  0, 0
};

// the sums
//
float64 MMAT_SUM_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // sum(A), sum(B), sum(C), sum(D), sum(E), sum(F), sum(G), sum(H)
  //
  65, 14, 62, 38, 38, 145, 35, 35,

  // sum(I), sum(J), sum(K), sum(L), sum(M), sum(N), sum(O), sum(P)
  //
  78, 14, 72, 46, 58, 66, 35, 34,

  // imaginary components of
  // sum(A), sum(B), sum(C), sum(D), sum(E), sum(F), sum(G), sum(H)
  //
  0, 0, 0, 0, 0, 0, 0, 0,

  // imaginary components of
  // sum(I), sum(J), sum(K), sum(L), sum(M), sum(N), sum(O), sum(P)
  //
  77, 13, 55, 53, 49, 72, 43, 31

};

// the sumSquare
//
float64 MMAT_SUM_SQUARE_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // sumSquare(A), sumSquare(B), sumSquare(C), sumSquare(D),
  // sumSquare(E), sumSquare(F), sumSquare(G), sumSquare(H),
  //
  333, 54, 304, 164, 164, 1875, 197, 197,

  // sumSquare(I), sumSquare(J), sumSquare(K), sumSquare(L),
  // sumSquare(M), sumSquare(N), sumSquare(O), sumSquare(P)
  //
  67, 51, 189, -81, 139, -46, -56, 49,

  // imaginary components of
  // sumSquare(A), sumSquare(B), sumSquare(C), sumSquare(D),
  // sumSquare(E), sumSquare(F), sumSquare(G), sumSquare(H),
  //
  0, 0, 0, 0, 0, 0, 0, 0,

  // imaginary components of
  // sumSquare(I), sumSquare(J), sumSquare(K), sumSquare(L),
  // sumSquare(M), sumSquare(N), sumSquare(O), sumSquare(P)
  //
  762, 80, 532, 412, 636, 612, 376, 322

};

// the mean
//
float64 MMAT_MEAN_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // mean(A), mean(B), mean(C), mean(D), mean(E), mean(F), mean(G), mean(H)
  //
  4.0625, 0.8750, 3.8750, 2.3750, 2.375, 9.0625, 4.3750, 4.3750,

  // mean(I), mean(J), mean(K), mean(L), mean(M), mean(N), mean(O), mean(P)
  //
  4.875, 0.8750, 4.5, 2.875, 3.625, 4.125, 4.375, 4.25,

  // imaginary components of
  // mean(A), mean(B), mean(C), mean(D), mean(E), mean(F), mean(G), mean(H)
  //
  0, 0, 0, 0, 0, 0, 0, 0,

  // imaginary components of
  // mean(I), mean(J), mean(K), mean(L), mean(M), mean(N), mean(O), mean(P)
  //
  4.8125, 0.8125, 3.4375, 3.3125, 3.0625, 4.5, 5.375, 3.875

};

// the rms
//
float64 MMAT_RMS_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // rms(A), rms(B), rms(C), rms(D), rms(E), rms(F), rms(G), rms(H)
  //
  2.075715238, 1.615355998, 1.996089928, 2.146945505, 2.146945505, 5.9210297879676306, 2.341874249, 2.341874249,

  // rms(I), rms(J), rms(K), rms(L), rms(M), rms(N), rms(O), rms(P)
  //
  2.075715238, 1.615355998, 1.996089928, 2.146945505, 2.146945505, 5.9210297879676306, 2.341874249, 2.341874249,

  // imaginary components of
  // rms(A), rms(B), rms(C), rms(D), rms(E), rms(F), rms(G), rms(H)
  //
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,

  // imaginary components of
  // rms(I), rms(J), rms(K), rms(L), rms(M), rms(N), rms(O), rms(P)
  //
  2.075715238, 1.615355998, 1.996089928, 2.146945505, 2.146945505, 5.9210297879676306, 2.341874249, 2.341874249

};

// the var
//
float64 MMAT_VAR_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // var(A), var(B), var(C), var(D), var(E), var(F), var(G), var(H)
  //
  4.308593750, 2.609375000, 3.984375000, 4.609375000, 4.609375000, 35.05859375, 5.484375000, 5.484375000,

  // var(I), var(J), var(K), var(L), var(M), var(N), var(O), var(P)
  //
  4.308593750, 2.609375000, 3.984375000, 4.609375000, 4.609375000, 35.05859375, 5.484375000, 5.484375000,

  // imaginary components of
  // var(A), var(B), var(C), var(D), var(E), var(F), var(G), var(H)
  //
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,

  // imaginary components of
  // var(I), var(J), var(K), var(L), var(M), var(N), var(O), var(P)
  //
  4.308593750, 2.609375000, 3.984375000, 4.609375000, 4.609375000, 35.05859375, 5.484375000, 5.484375000

};

// the trace
//
float64 MMAT_TRACE_RES[MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // trace(A), trace(B), trace(C), trace(D), trace(E), trace(F),
  // trace(G), trace(H),
  //
  11, 14, 24, 14, 14, 37, false, false,

  // trace(I), trace(J), trace(K), trace(L), trace(M), trace(N),
  // trace(O), trace(P)
  //
  18, 14, 20, 20, 23, 19, false, false,

  // imaginary components of
  // trace(A), trace(B), trace(C), trace(D), trace(E), trace(F)
  // trace(G), trace(H)
  //
  0, 0, 0, 0, 0, 0, false, false,

  // imaginary components of
  // trace(I), trace(J), trace(K), trace(L), trace(M), trace(N),
  // trace(O), trace(P)
  //
  25, 13, 13, 12, 13, 10, false, false

};

// sum by column
//
float64 MMAT_SUM_COLUMN_RES [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_COLS * MMAT_TWO] = {

  // sum along matrix A: col 0, 1, 2, 3
  //
  { 18, 18, 21, 8, 0, 0, 0, 0 },

  // sum along matrix B: col 0, 1, 2, 3
  //
  { 5, 2, 3, 4, 0, 0, 0, 0 },

  // sum along matrix C: col 0, 1, 2, 3
  //
  { 14, 16, 20, 12, 0, 0, 0, 0 },

  // sum along matrix D: col 0, 1, 2, 3
  //
  { 14, 14, 6, 4, 0, 0, 0, 0  },

  // sum along matrix E: col 0, 1, 2, 3
  //
  { 5, 4, 12, 17, 0, 0, 0, 0  },

  // sum along matrix F: col 0, 1, 2, 3
  //
  { 32, 37, 44, 32, 0, 0, 0, 0  },

  // sum along matrix G: col 0, 1, 2, 3 (two dummy values)
  //
  { 16, 19, 0, 0, 0, 0, 0, 0  },

  // sum along matrix H: col 0, 1, 2, 3
  //
  { 9, 9, 12, 5, 0, 0, 0, 0  },

  // sum along matrix I: col 0, 1, 2, 3
  //
  { 17, 26, 25, 10, 19, 25, 12, 21 },

  // sum along matrix J: col 0, 1, 2, 3
  //
  { 9, 4, 1, 0, 3, 2, 5, 3 },

  // sum along matrix K: col 0, 1, 2, 3
  //
  { 13, 18, 19, 22, 11, 15, 18, 11 },

  // sum along matrix L: col 0, 1, 2, 3
  //
  { 16, 10, 12, 8, 29, 19, 4, 1  },

  // sum along matrix M: col 0, 1, 2, 3
  //
  { 8, 18, 6, 26, 3, 13, 11, 22  },

  // sum along matrix N: col 0, 1, 2, 3
  //
  { 7, 23, 15, 21, 20, 13, 15, 24  },

  // sum along matrix O: col 0, 1, 2, 3 (two dummy values)
  //
  { 21, 14, 0, 0, 22, 21, 0, 0  },

  // sum along matrix P: col 0, 1, 2, 3
  //
  { 9, 10, 4, 11, 8, 10, 7, 6  }
};

// sum by row
//
float64 MMAT_SUM_ROW_RES [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_ROWS * MMAT_TWO] = {

  // sum along matrix A: row 0, 1, 2, 3
  //
  { 16, 15, 16, 18, 0, 0, 0, 0 },

  // sum along matrix B: row 0, 1, 2, 3
  //
  { 5, 2, 3, 4, 0, 0, 0, 0 },

  // sum along matrix C: row 0, 1, 2, 3
  //
  { 14, 16, 20, 12, 0, 0, 0, 0 },

  // sum along matrix D: row 0, 1, 2, 3
  //
  { 5, 4, 12, 17, 0, 0, 0, 0 },

  // sum along matrix E: col 0, 1, 2, 3
  //
  { 14, 14, 6, 4, 0, 0, 0, 0 },

  // sum along matrix F: row 0, 1, 2, 3
  //
  { 12, 26, 36, 71, 0, 0, 0, 0 },

  // sum along matrix G: row 0, 1, 2, 3
  //
  { 9, 9, 12, 5, 0, 0, 0, 0 },

  // sum along matrix H: row 0, 1, 2, 3 (two dummy values)
  //
  { 16, 19, 0, 0, 0, 0, 0, 0 },

  // sum along matrix I: row 0, 1, 2, 3
  //
  { 16, 17, 24, 21, 16, 24, 19, 18 },

  // sum along matrix J: row 0, 1, 2, 3
  //
  { 9, 4, 1, 0, 3, 2, 5, 3 },

  // sum along matrix K: row 0, 1, 2, 3
  //
  { 13, 18, 19, 22, 11, 15, 18, 11 },

  // sum along matrix L: row 0, 1, 2, 3
  //
  { 2, 5, 22, 17, 6, 13, 13, 21 },

  // sum along matrix M: col 0, 1, 2, 3
  //
  { 27, 17, 10, 4, 21, 16, 11, 1 },

  // sum along matrix N: row 0, 1, 2, 3
  //
  { 18, 23, 16, 9, 24, 22, 14, 12 },

  // sum along matrix O: row 0, 1, 2, 3
  //
  { 8, 8, 9, 10, 14, 6, 14, 9 },

  // sum along matrix P: row 0, 1, 2, 3 (two dummy values)
  //
  { 17, 17, 0, 0, 13, 18, 0, 0 }

};

//-----------------------------------------------------------------------------
//
// define the results of operations:
//    F(matrix, scalar) -> matrix
//
//-----------------------------------------------------------------------------
float64 MMAT_NEG_RES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // neg(A):
  //
  {4, 4,   -3, -4, -7, -2, -3, -5, -6, -1, -8, -4, -1, -3, -4, -5, -7, -2,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

  // neg(B):
  //
  {4, 4,    -5, 0, 0, 0, 0, -2, 0, 0, 0, 0, -3, 0, 0, 0, 0, -4,
             0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0},

  // neg(C):
  //
  {4, 4,   -5, -2, -3, -4, -2, -7, -6, -1, -3, -6, -8, -3, -4, -1, -3, -4,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

  // neg(D):
  //
  {4, 4,   -5, 0, 0, 0, -2, -2, 0, 0, -3, -6, -3, 0, -4, -6, -3, -4,
            0, 0, 0, 0,  0,  0, 0, 0,  0,  0,  0, 0,  0,  0,  0,  0},

  // neg(E):
  //
  {4, 4,   -5, -2, -3, -4, 0, -2, -6, -6, 0, 0, -3, -3, 0, 0, 0, -4,
            0,  0,  0,  0, 0,  0,  0,  0, 0, 0,  0,  0, 0, 0, 0,  0},

  // neg(F):
  //
  {4, 4,  -3, -4, -3, -2, -5, -7, -8, -6, -9, -12, -9, -6, -15, -14, -24, -18,
           0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,   0,   0,   0,   0},

  // neg(G):
  //
  {4, 2,   -4, -5, -7, -2, -3, -9, -2, -3, 0, 0, 0, 0, 0, 0, 0, 0,
            0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0},

  // neg(H):
  //
  {2, 4,   -4, -7, -3, -2, -5, -2, -9, -3, 0, 0, 0, 0, 0, 0, 0, 0,
            0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0},
  // neg(I):
  //
  {4, 4,    -2, -9, -1, -4, -3, -5, -8, -1, -8, -4, -9, -3, -4, -8, -7, -2,
            -4, -5, -1, -6, -7, -9, -5, -3, -5, -6, -4, -4, -3, -5, -2, -8},

  // neg(J):
  //
  {4, 4,    -9, 0, 0, 0, 0, -4, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0,
           - 3, 0, 0, 0, 0, -2, 0, 0, 0, 0, -5, 0, 0, 0, 0, -3},

  // neg(K):
  //
  {4, 4,    -2, -7, -1, -3, -7, -5, -2, -4, -1, -2, -7, -9, -3, -4, -9, -6,
            -1, -3, -5, -2, -3, -7, -4, -1, -5, -4, -3, -6, -2, -1, -6, -2},

  // neg(L):
  //
  {4, 4,    -2, 0, 0, 0, -4, -1, 0, 0,- 6, -7, -9, 0, -4, -2, -3, -8,
            -6, 0, 0, 0, -9, -4, 0, 0, -6, -6, -1, 0, -8, -9, -3, -1},

  // neg(M):
  //
  {4, 4,    -8, -9, -1, -9, 0, -9, -3, -5, 0, 0, -2, -8, 0, 0, 0, -4,
            -3, -7, -5, -6, 0, -6, -3, -7, 0, 0, -3, -8, 0, 0, 0, -1},

  // neg(N):
  //
  {4, 4,    -2, -6, -4, -6, -3, -8, -3, -9, -1, -6, -6, -3, -1, -3, -2, -3,
            -4, -6, -6, -8, -8, -1, -5, -8, -6, -3, -1, -4, -2, -3, -3, -4},

  // neg(O):
  //
  {4, 2,    -7, -1,
            -6, -2,
            -6, -3,
	    -2, -8,
            -8, -6,
            -3, -3,
            -6, -8,
	    -5, -4,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // neg(P):
  //
  {2, 4,    -8, -4, -2, -3,
	    -1, -6, -2, -8,
            -6, -3, -3, -1,
	    -2, -7, -4, -5,
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


float64 MMAT_ADD_SCAL_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A + 3
  //
  {4, 4,    6, 7, 10, 5, 6, 8, 9, 4, 11, 7, 4, 6, 7, 8, 10, 5,
            0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0},

  // B + 3
  //
  {4, 4,    8, 3, 3, 3, 3, 5, 3, 3, 3, 3, 6, 3, 3, 3, 3, 7,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C + 3
  //
  {4, 4,    8, 5, 6, 7, 5, 10, 9, 4, 6, 9, 11, 6, 7, 4, 6, 7,
            0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},

  // D + 3
  //
  {4, 4,    8, 3, 3, 3, 5, 5, 3, 3, 6, 9, 6, 3, 7, 9, 6, 7,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E + 3
  //
  {4, 4,    8, 5, 6, 7, 3, 5, 9, 9, 3, 3, 6, 6, 3, 3, 3, 7,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F + 3
  //
  {4, 4,   6, 7, 6, 5, 8, 10, 11, 9, 12, 15, 12, 9, 18, 17, 27, 21,
           0, 0, 0, 0, 0,  0,  0, 0,  0,  0,  0, 0,  0,  0,  0,  0},

  // G + 3
  //
  {4, 2,   7, 8, 10, 5, 6, 12, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H + 3
  //
  {2, 4,   7, 10, 6, 5, 8, 5, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0,
           0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I + 3
  //
  {4, 4,    5, 12, 4, 7, 6, 8, 11, 4, 11, 7, 12, 6, 7, 11, 10, 5,
            4, 5, 1, 6, 7, 9, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8},

  // J + 3
  //
  {4, 4,    12, 3, 3, 3, 3, 7, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3},

  // K + 3
  //
  {4, 4,    5, 10, 4, 6, 10, 8, 5, 7, 4, 5, 10, 12, 6, 7, 12, 9,
            1, 3, 5, 2, 3, 7, 4, 1, 5, 4, 3, 6, 2, 1, 6, 2},

  // L + 3
  //
  {4, 4,    5, 3, 3, 3, 7, 4, 3, 3, 9, 10, 12, 3, 7, 5, 6, 11,
            6, 0, 0, 0, 9, 4, 0, 0, 6, 6, 1, 0, 8, 9, 3, 1},

  // M + 3
  //
  {4, 4,    11, 12, 4, 12, 3, 12, 6, 8, 3, 3, 5, 11, 3, 3, 3, 7,
            3, 7, 5, 6, 0, 6, 3, 7, 0, 0, 3, 8, 0, 0, 0, 1},

  // N + 3
  //
  {4, 4,    5, 9, 7, 9, 6, 11, 6, 12, 4, 9, 9, 6, 4, 6, 5, 6,
            4, 6, 6, 8, 8, 1, 5, 8, 6, 3, 1, 4, 2, 3, 3, 4},

  // O + 3
  //
  {4, 2,    10, 4,
            9, 5,
            9, 6,
	    5, 11,

	    8, 6,
	    3, 3,
	    6, 8,
	    5, 4,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P + 3
  //
  {2, 4,    11, 7, 5, 6,
	    4, 9, 5, 11,

            6, 3, 3, 1,
	    2, 7, 4, 5,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

float64 MMAT_MULT_SCAL_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A * 3
  //
  {4, 4,    9, 12, 21, 6, 9, 15, 18, 3, 24, 12, 3, 9, 12, 15, 21, 6,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // B * 3
  //
  {4, 4,    15, 0, 0, 0, 0, 6, 0, 0, 0, 0, 9, 0, 0, 0, 0, 12,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C * 3
  //
  {4, 4,    15, 6, 9, 12, 6, 21, 18, 3, 9, 18, 24, 9, 12, 3, 9, 12,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


  // D * 3
  //
  {4, 4,    15, 0, 0, 0, 6, 6, 0, 0, 9, 18, 9, 0, 12, 18, 9, 12,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E * 3
  //
  {4, 4,    15, 6, 9, 12, 0, 6, 18, 18, 0, 0, 9, 9, 0, 0, 0, 12,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F * 3
  //
  {4, 4,   9, 12, 9, 6, 15, 21, 24, 18, 27, 36, 27, 18, 45, 42, 72, 54,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // G * 3
  //
  {4, 2,   12, 15, 21, 6, 9, 27, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H * 3
  //
  {2, 4,   12, 21, 9, 6, 15, 6, 27, 9, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I * 3
  //
  {4, 4,    6, 27, 3, 12, 9, 15, 24, 3, 24, 12, 27, 9, 12, 24, 21, 6,
            12, 15, 3, 18, 21, 27, 15, 9, 15, 18, 12, 12, 9, 15, 6, 24},

  // J * 3
  //
  {4, 4,    27, 0, 0, 0, 0, 12, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
            9, 0, 0, 0, 0, 6, 0, 0, 0, 0, 15, 0, 0, 0, 0, 9},

  // K * 3
  //
  {4, 4,    6, 21, 3, 9, 21, 15, 6, 12, 3, 6, 21, 27, 9, 12, 27, 18,
            3, 9, 15, 6, 9, 21, 12, 3, 15, 12, 9, 18, 6, 3, 18, 6},

  // L * 3
  //
  {4, 4,    6, 0, 0, 0, 12, 3, 0, 0, 18, 21, 27, 0, 12, 6, 9, 24,
            18, 0, 0, 0, 27, 12, 0, 0, 18, 18, 3, 0, 24, 27, 9, 3},

  // M * 3
  //
  {4, 4,    24, 27, 3, 27, 0, 27, 9, 15, 0, 0, 6, 24, 0, 0, 0, 12,
            9, 21, 15, 18, 0, 18, 9, 21, 0, 0, 9, 24, 0, 0, 0, 3},

  // N * 3
  //
  {4, 4,    6, 18, 12, 18, 9, 24, 9, 27, 3, 18, 18, 9, 3, 9, 6, 9,
            12, 18, 18, 24, 24, 3, 15, 24, 18, 9, 3, 12, 6, 9, 9, 12},

  // O * 3
  //
  {4, 2,    21, 3,
            18, 6,
            18, 9,
	    6, 24,

            24, 18,
            9, 9,
            18, 24,
	    15, 12,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P * 3
  //
  {2, 4,    24, 12, 6, 9,
	    3, 18, 6, 24,

            18, 9, 9, 3,
	    6, 21, 12, 15,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

float64 MMAT_INV_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // inv(A) * det(A)
  //
  {4, 4,   -30, -19, -5, 47, 29, 19, 5, -46, -17, -11, -3, 27, 47, 29, 8, -73,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(B) * det(B)
  //
  {4, 4,   24, 0, 0, 0, 0, 60, 0, 0, 0, 0, 40, 0, 0, 0, 0, 30,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(C) * det(C)
  //
  {4, 4,   45, -23, 21, -55, -23, 23, -21, 33, 21, -21, 23, -33, -55, 33, -33, 77,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(D) * det(D)
  //
  {4, 4,   24, 0, 0, 0, -24, 60, 0, 0, 24, -120, 40, 0, -6, 0, -30, 30,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(E) * det(E)
  //
  {4, 4,   24, -24, 24, -6, 0, 60, -120, 0, 0, 0, 40, -30, 0, 0, 0, 30,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(F) (dummy values)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(G) (dummy values)
  //
  {4, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(H) (dummy values)
  //
  {2, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(I) * det(I)
  //
  {4, 4,   -167, 414, -442, 151, -32, -125, 292, -164, 359, -285, 158, -204, -151, -125, -105, 243, 
           96, -2, 200, -331, 249, 123, -8, -192, -179, 81, -88, 300, 14, -295, 135, 263, 
  },

  // inv(J) * det(J)
  //
  {4, 4,  -66, 0, 0, 0, 0, -144, 0, 0, 0, 0, -90, 0, 0, 0, 0, -120, 
          -18, 0, 0, 0, 0, -18, 0, 0, 0, 0, 90, 0, 0, 0, 0, 180, 
  },

  // inv(K) * det(K)
  //
  {4, 4,  366, -15, -101, -54, -15, -107, -67, 221, -101, -67, -65, 163, -54, 221, 163, -296, 
          -244, 399, 61, -236, 399, -50, -66, -51, 61, -66, -124, 255, -236, -51, 255, -86, 
  },

  // inv(L) * det(L)
  //
  {4, 4,  3, 0, 0, 0, -131, 40, 0, 0, -121, 230, -190, 0, -240, 252, 108, -212, 
          301, 0, 0, 0, -707, 460, 0, 0, 448, -410, 90, 0, 78, -124, 24, 104, 
  },

  // inv(M)* det(M)
  //
  {4, 4,  -39, 53, 111, -308, 0, -2, -27, 31, 0, 0, 141, 168, 0, 0, 0, -117, 
          156, -161, 15, -359, 0, 127, -147, 185, 0, 0, 354, -1032, 0, 0, 0, 312, 
  },

  // inv(N) (dummy values)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(O) (dummy values)
  //
  {4, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // inv(P) (dummy values)
  //
  {2, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

float64 MMAT_TRANS_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // transpose(A)
  //
  {4, 4,    3, 3, 8, 4, 4, 5, 4, 5, 7, 6, 1, 7, 2, 1, 3, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(B)
  //
  {4, 4,    5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(C)
  //
  {4, 4,    5, 2, 3, 4, 2, 7, 6, 1, 3, 6, 8, 3, 4, 1, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(D)
  //
  {4, 4,    5, 2, 3, 4, 0, 2, 6, 6, 0, 0, 3, 3, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(E)
  //
  {4, 4,    5, 0, 0, 0, 2, 2, 0, 0, 3, 6, 3, 0, 4, 6, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(F)
  //
  {4, 4,   3, 5, 9, 15, 4, 7, 12, 14, 3, 8, 9, 24, 2, 6, 6, 18,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(G)
  //
  {2, 4,   4, 7, 3, 2, 5, 2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(H)
  //
  {4, 2,   4, 5, 7, 2, 3, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(I)
  //
  {4, 4,    2, 3, 8, 4, 9, 5, 4, 8, 1, 8, 9, 7, 4, 1, 3, 2,
            4, 7, 5, 3, 5, 9, 6, 5, 1, 5, 4, 2, 6, 3, 4, 8},

  // transpose(J)
  //
  {4, 4,    9, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3},

  // transpose(K)
  //
  {4, 4,    2, 7, 1, 3, 7, 5, 2, 4, 1, 2, 7, 9, 3, 4, 9, 6,
            1, 3, 5, 2, 3, 7, 4, 1, 5, 4, 3, 6, 2, 1, 6, 2},

  // transpose(L)
  //
  {4, 4,    2, 4, 6, 4, 0, 1, 7, 2, 0, 0, 9, 3, 0, 0, 0, 8,
	    6, 9, 6, 8, 0, 4, 6, 9, 0, 0, 1, 3, 0, 0, 0, 1},

  // transpose(M)
  //
  {4, 4,    8, 0, 0, 0, 9, 9, 0, 0, 1, 3, 2, 0, 9, 5, 8, 4,
	    3, 0, 0, 0, 7, 6, 0, 0, 5, 3, 3, 0, 6, 7, 8, 1},

  // transpose(N)
  //
  {4, 4,   2, 3, 1, 1, 6, 8, 6, 3, 4, 3, 6, 2, 6, 9, 3, 3,
	   4, 8, 6, 2, 6, 1, 3, 3, 6, 5, 1, 3, 8, 8, 4, 4},

  // transpose(O) (8 dummy values)
  //
  {2, 4,   7, 6, 6, 2, 1, 2, 3, 8, 8, 3, 6, 5, 6, 3, 8, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // transpose(P) (8 dummy values)
  //
  {4, 2,   8, 1, 4, 6, 2, 2, 3, 8, 6, 2, 3, 7, 3, 4, 1, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

};

float64 MMAT_ASSIGN_TINT_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // B.assign(5)
  //
  {4, 4,   5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // D.assign(5)
  //
  {4, 4,   5, 0, 0, 0, 5, 5, 0, 0, 5, 5, 5, 0, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 0, 5, 5, 5, 0, 0, 5, 5, 0, 0, 0, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // G.assign(5)
  //
  {2, 4,   5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H.assign(5)
  //
  {4, 2,   5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // J.assign(5)
  //
  {4, 4,   5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // K.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // L.assign(5)
  //
  {4, 4,   5, 0, 0, 0, 5, 5, 0, 0, 5, 5, 5, 0, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // M.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 0, 5, 5, 5, 0, 0, 5, 5, 0, 0, 0, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // N.assign(5)
  //
  {4, 4,   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // O.assign(5)
  //
  {2, 4,   5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P.assign(5)
  //
  {4, 2,   5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// the results of block assignment
//
float64 MMAT_BLOCKASSIGN_RES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // A.assign(0, 0, 2, 2, 5)
  //
  {4, 4,    5, 5, 7, 2, 5, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // B.assign(2, 2, 1, 1, 5)
  //
  {4, 4,    5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C.assign(2, 0, 2, 2, 5)
  //
  {4, 4,    5, 2, 5, 5, 2, 7, 5, 5, 5, 5, 8, 3, 5, 5, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // D.assign(2, 0, 2, 3, 5)
  //
  {4, 4,    5, 0, 0, 0, 2, 2, 0, 0, 5, 5, 5, 0, 5, 5, 5, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E.assign(0, 2, 2, 2, 5)
  //
  {4, 4,    5, 2, 5, 5, 0, 2, 5, 5, 0, 0, 5, 5, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F.assign(0, 0, 2, 2, 5)
  //
  {4, 4,    5, 5, 3, 2, 5, 5, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // G.assign(0, 0, 2, 2, 5)
  //
  {4, 2,    5, 5, 5, 5, 3, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H.assign(0, 0, 2, 2, 5)
  //
  {2, 4,    5, 5, 3, 2, 5, 5, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I.assign(0, 0, 2, 2, 5+3j)
  //
  {4, 4,    5, 5, 1, 4, 5, 5, 8, 1, 8, 4, 9, 3, 4, 8, 7, 2,
            3, 3, 1, 6, 3, 3, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8},

  // J.assign(2, 2, 1, 1, 5+3j)
  //
  {4, 4,    9, 0, 0, 0, 0, 4, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3},

  // K.assign(2, 0, 2, 2, 5+3j)
  //
  {4, 4,    2, 7, 5, 5, 7, 5, 5, 5, 5, 5, 7, 9, 5, 5, 9, 6,
            1, 3, 3, 3, 3, 7, 3, 3, 3, 3, 3, 6, 3, 3, 6, 2},

  // L.assign(2, 0, 2, 3, 5+3j)
  //
  {4, 4,    2, 0, 0, 0, 4, 1, 0, 0, 5, 5, 5, 0, 5, 5, 5, 8,
            6, 0, 0, 0, 9, 4, 0, 0, 3, 3, 3, 0, 3, 3, 3, 1},

  // M.assign(0, 2, 3, 2, 5+3j)
  //
  {4, 4,    8, 9, 5, 5, 0, 9, 5, 5, 0, 0, 5, 5, 0, 0, 0, 4,
            3, 7, 3, 3, 0, 6, 3, 3, 0, 0, 3, 3, 0, 0, 0, 1},

  // N.assign(0, 0, 2, 2, 5+3j)
  //
  {4, 4,    5, 5, 4, 6, 5, 5, 3, 9, 1, 6, 6, 3, 1, 3, 2, 3,
            3, 3, 6, 8, 3, 3, 5, 8, 6, 3, 1, 4, 2, 3, 3, 4},

  // O.assign(0, 0, 2, 2, 5+3j)
  //
  {4, 2,    5, 5,
	    5, 5,
	    6, 3,
	    2, 8,

            3, 3,
	    3, 3,
	    6, 8,
	    5, 4,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P.assign(0, 0, 2, 2, 5+3j)
  //
  {2, 4,    5, 5, 2, 3,
	    5, 5, 2, 8,

            3, 3, 3, 1,
	    3, 3, 4, 5,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

float64 MMAT_ASSIGN_ARG [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // A: a full 4x4 non-singular matrix
  //
  {4, 4,    3, 4, 7, 2, 3, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // B: a diagonal 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // C: a symmetric 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 7, 3, 6, 8, 4, 1, 3, 4, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // D: a lower triangular 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 2, 3, 6, 3, 4, 6, 3, 4, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // E: a upper triangular 4x4 non-singular matrix
  //
  {4, 4,    5, 2, 3, 4, 2, 6, 6, 3, 3, 4, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // F: a full 4x4 singular matrix
  //
  {4, 4,   3, 4, 3, 2, 5, 7, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // G: a full 4x2 matrix
  //
  {4, 2,   4, 5, 7, 2, 3, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // H: a full 2x4 matrix
  //
  {2, 4,   4, 7, 3, 2, 5, 2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I: a full 4x4 non-singular matrix
  //
  {4, 4,    2, 9, 1, 4, 3, 5, 8, 1, 8, 4, 9, 3, 4, 8, 7, 2,
            4, 5, 1, 6, 7, 9, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8},

  // J: a diagonal 4x4 non-singular matrix
  //
  {4, 4,    9, 4, 1, 0, 3, 2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // K: a symmetric 4x4 non-singular matrix
  //
  {4, 4,    2,
            7, 5,
            1, 2, 7,
            3, 4, 9, 6,
            1,
            3, 7,
            5, 4, 3,
            2, 1, 6, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // L: a lower triangular 4x4 non-singular matrix
  //
  {4, 4,    2,
            4, 1,
            6, 7, 9,
            4, 2, 3, 8,
            6,
            9, 4,
            6, 6, 1,
	    8, 9, 3, 1,
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // M: a upper triangular 4x4 non-singular matrix
  //
  {4, 4,    8, 9, 1, 9,
	    9, 3, 5,
	    2, 8,
	    4,
            3, 7, 5, 6,
	    6, 3, 7,
	    3, 8,
	    1,
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // N: a full 4x4 singular matrix
  //
  {4, 4,    2, 6, 4, 6,
	    3, 8, 3, 9,
	    1, 6, 6, 3,
	    1, 3, 2, 3,

            4, 6, 6, 8,
	    8, 1, 5, 8,
	    6, 3, 1, 4,
	    2, 3, 3, 4},

  // O: a full 4x2 matrix
  //
  {4, 2,    7, 1,
            6, 2,
            6, 3,
	    2, 8,

            8, 6,
	    3, 3,
	    6, 8,
	    5, 4,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P: a full 2x4 matrix
  //
  {2, 4,    8, 4, 2, 3,
	    1, 6, 2, 8,

            6, 3, 3, 1,
	    2, 7, 4, 5,

	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

const unichar* MMAT_ASSIGN1_ARG [MMAT_NUM_MATS_TOTAL] = {

  // A: a full 4x4 non-singular matrix
  //
  L"3, 4, 7, 2, 3, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2",

  // B: a diagonal 4x4 non-singular matrix
  //
  L"5, 2, 3, 4",

  // C: a symmetric 4x4 non-singular matrix
  //
  L"5, 2, 7, 3, 6, 8, 4, 1, 3, 4",

  // D: a lower triangular 4x4 non-singular matrix
  //
  L"5, 2, 2, 3, 6, 3, 4, 6, 3, 4",

  // E: a upper triangular 4x4 non-singular matrix
  //
  L"5, 2, 3, 4, 2, 6, 6, 3, 3, 4",

  // F: a full 4x4 singular matrix
  //
  L"3, 4, 3, 2, 5, 7, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18",

  // G: a full 4x2 matrix
  //
  L"4, 5, 7, 2, 3, 9, 2, 3",

  // H: a full 2x4 matrix
  //
  L"4, 7, 3, 2, 5, 2, 9, 3",

  // I: a full 4x4 non-singular matrix
  //
  L"2+4j, 9+5j, 1+1j, 4+6j, 3+7j, 5+9j, 8+5j, 1+3j, 8+5j, 4+6j, 9+4j, 3+4j,4+3j, 8+5j, 7+2j, 2+8j",

  // J: a diagonal 4x4 non-singular matrix
  //
  L"9+3j, 4+2j, 1+5j, 0+3j",

  // K: a symmetric 4x4 non-singular matrix
  //
  L"2+1j, 7+3j, 5+7j, 1+5j, 2+4j, 7+3j, 3+2j, 4+1j, 9+6j, 6+2j",

  // L: a lower triangular 4x4 non-singular matrix
  //
  L"2+6j, 4+9j, 1+4j, 6+6j, 7+6j, 9+1j, 4+8j, 2+9j, 3+3j, 8+1j",

  // M: a upper triangular 4x4 non-singular matrix
  //
  L"8+3j, 9+7j, 1+5j, 9+6j, 9+6j, 3+3j, 5+7j, 2+3j, 8+8j, 4+1j",

  // N: a full 4x4 singular matrix
  //
  L"2+4j, 6+6j, 4+6j, 6+8j, 3+8j, 8+1j, 3+5j, 9+8j, 1+6j, 6+3j, 6+1j, 3+4j, 1+2j, 3+3j, 2+3j, 3+4j",

  // O: a full 4x2 matrix
  //
  L"7+8j, 1+6j, 6+3j, 2+3j, 6+6j, 3+8j, 2+5j, 8+4j",

  // P: a full 2x4 matrix
  //
  L"8+6j, 4+3j, 2+3j, 3+1j, 1+2j, 6+7j, 2+4j, 8+5j",
};

// vector multiplication arguments
//
float64 MMAT_VMULT_ARG_REAL [MMAT_NUM_ROWS * MMAT_TWO] = {

  // vector V1
  //
  6, 4, 3, 1, 0, 0, 0, 0,
};

float64 MMAT_MULTV_ARG_REAL [MMAT_NUM_COLS * MMAT_TWO] = {

  // vector V2
  //
  5, 4, 2, 0, 0, 0, 0, 0,
};

float64 MMAT_VMULT_ARG_COMPLEX [MMAT_NUM_ROWS * MMAT_TWO] = {

  // vector V3
  //
  6, 4, 3, 1, 2, 3, 2, 2,
};

float64 MMAT_MULTV_ARG_COMPLEX [MMAT_NUM_COLS * MMAT_TWO] = {

  // vector V4
  //
  5, 4, 2, 0, 3, 1, 3, 4,
};

int32 MMAT_INDEX_VECTOR [MMAT_NUM_ROWS] = {

  // MVector<Long, int32> index_vec
  //
  3, 2, 1, 0
};

// vector multiplication results
//
float64 MMAT_VMULT_RES_REAL [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_ROWS * MMAT_TWO + 1] = {

  // V1 * A = (len, vector)
  //
  {4,    58, 61, 76, 27, 0, 0, 0, 0},

  // V1 * B = (len, vector)
  //
  {4,    30, 8, 9, 4, 0, 0, 0, 0},

  // V1 * C = (len, vector)
  //
  {4,    51, 59, 69, 41, 0, 0, 0, 0},

  // V1 * D = (len, vector)
  //
  {4,    51, 32, 12, 4, 0, 0, 0, 0},

  // V1 * E = (len, vector)
  //
  {4,    30, 20, 51, 61, 0, 0, 0, 0},

  // V1 * F = (len, vector)
  //
  {4,    80, 102, 101, 72, 0, 0, 0, 0},

  // V1 * G = (len, vector), two dummy values
  //
  {2,    63, 68, 0, 0, 0, 0, 0, 0},

  // V1 * H: dummy values
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // V1 * I = (len, vector)
  //
  {4,    52, 94, 72, 39, 70, 89, 40, 68},

  // V1 * J = (len, vector)
  //
  {4,    54, 16, 3, 0, 18, 8, 15, 3},

  // V1 * K = (len, vector)
  //
  {4,    46, 72, 44, 67, 35, 59, 61, 36},

  // V1 * L = (len, vector)
  //
  {4,    50, 27, 30, 8, 98, 43, 6, 1},

  // V1 * M = (len, vector)
  //
  {4,    48, 90, 24, 102, 18, 66, 51, 89},

  // V1 * N = (len, vector)
  //
  {4,    28, 89, 56, 84, 76, 52, 62, 96},

  // V1 * O = (len, vector), two dummy values
  //
  {2,    86, 31, 0, 0, 83, 76, 0, 0},

  // V1 * P: dummy values
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0}
};

// vector multiplication results
//
float64 MMAT_MULTV_RES_REAL [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_COLS * MMAT_TWO + 1] = {

  // A * transpose(V2) = (len, vector)
  //
  {4,    45, 47, 58, 54, 0, 0, 0, 0},

  // B * transpose(V2) = (len, vector)
  //
  {4,    25, 8, 6, 0, 0, 0, 0, 0},

  // C * transpose(V2) = (len, vector)
  //
  {4,    39, 50, 55, 30, 0, 0, 0, 0},

  // D * transpose(V2) = (len, vector)
  //
  {4,    25, 18, 45, 50, 0, 0, 0, 0},

  // E * transpose(V2) = (len, vector)
  //
  {4,    39, 20, 6, 0, 0, 0, 0, 0},

  // F * transpose(V2) = (len, vector)
  //
  {4,    37, 69, 111, 179, 0, 0, 0, 0},

  // G * transpose(V2) : (dummy values)
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // H * transpose(V2) = (len, vector), two dummy values
  //
  {2,    54, 51, 0, 0, 0, 0, 0, 0},

  // I * transpose(V2) = (len, vector)
  //
  {4,    48, 51, 74, 66, 42, 81, 57, 39},

  // J * transpose(V2) = (len, vector)
  //
  {4,    45, 16, 2, 0, 15, 8, 10, 0},

  // K * transpose(V2) = (len, vector)
  //
  {4,    40, 59, 27, 49, 27, 51, 47, 26},

  // L * transpose(V2) = (len, vector)
  //
  {4,    10, 24, 76, 34, 30, 61, 56, 82},

  // M * transpose(V2) = (len, vector)
  //
  {4,    78, 42, 4, 0, 53, 30, 6, 0},

  // N * transpose(V2) = (len, vector)
  //
  {4,    42, 53, 41, 21, 56, 54, 44, 28},

  // O * transpose(V2) : (dummy values)
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // P * transpose(V2) = (len, vector), two dummy values
  //
  {2,    60, 33, 0, 0, 48, 46, 0, 0}
};

float64 MMAT_VMULT_RES_COMPLEX [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_ROWS * MMAT_TWO + 1] = {

  // V3 * A = (len, vector)
  //
  {4,    58, 61, 76, 27, 54, 55, 62, 23},

  // V3 * B = (len, vector)
  //
  {4,    30, 8, 9, 4, 10, 8, 9, 12},

  // V3 * C = (len, vector)
  //
  {4,    51, 59, 69, 41, 39, 53, 63, 33},

  // V3 * D = (len, vector)
  //
  {4,    51, 32, 12, 4, 39, 44, 18, 12},

  // V3 * E = (len, vector)
  //
  {4,    30, 20, 51, 61, 10, 12, 39, 53},

  // V3 * F = (len, vector)
  //
  {4,    80, 102, 101, 72, 98, 114, 137, 100},

  // V3 * G = (len, vector), two dummy values
  //
  {2,    63, 68, 0, 0, 51, 54, 0, 0},

  // V3 * H: dummy values
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // V3 * I = (len, vector)
  //
  {4,    -8, 15, 32, -21, 122, 163, 122, 95},

  // V3 * J = (len, vector)
  //
  {4,    48, 8, -12, -9, 36, 24, 18, 3},

  // V3 * K = (len, vector)
  //
  {4,    11, 23, -9, 35, 79, 111, 119, 103},

  // V3 * L = (len, vector)
  //
  {4,    -40, -34, 18, 5, 148, 74, 42, 25},

  // V3 * M = (len, vector)
  //
  {4,    42, 52, -7, 35, 34, 120, 71, 163},

  // V3 * N = (len, vector)
  //
  {4,    -36, 55, 12, 12, 98, 123, 106, 162},

  // V3 * O = (len, vector), two dummy values
  //
  {2,    25, -29, 0, 0, 145, 119, 0, 0},

  // V3 * P: dummy values
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0}
};

// vector multiplication results
//
float64 MMAT_MULTV_RES_COMPLEX [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_COLS * MMAT_TWO + 1] = {

  // A * transpose(V4) = (len, vector)
  //
  {4,    45, 47, 58, 54, 49, 47, 44, 55},

  // B * transpose(V4) = (len, vector)
  //
  {4,    25, 8, 6, 0, 10, 8, 9, 12},

  // C * transpose(V4) = (len, vector)
  //
  {4,    39, 50, 55, 30, 39, 53, 63, 33},

  // D * transpose(V4) = (len, vector)
  //
  {4,    25, 18, 45, 50, 10, 12, 39, 53},

  // E * transpose(V4) = (len, vector)
  //
  {4,    39, 20, 6, 0, 39, 44, 18, 12},

  // F * transpose(V4) = (len, vector)
  //
  {4,    37, 69, 111, 179, 37, 80, 111, 212},

  // G * transpose(V4) : (dummy values)
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // H * transpose(V4) = (len, vector), two dummy values
  //
  {2,    54, 51, 0, 0, 51, 54, 0, 0},

  // I * transpose(V4) = (len, vector)
  //
  {4,     -1, -23, 16, 10, 97, 134, 125, 106},

  // J * transpose(V4) = (len, vector)
  //
  {4,    39, 8, -13, -9, 33, 24, 13, 0},

  // K * transpose(V4) = (len, vector)
  //
  {4,    5, 10, -26, 17, 71, 103, 105, 93},

  // L * transpose(V4) = (len, vector)
  //
  {4,    -2, -10, 37, -30, 34, 73, 123, 131},

  // M * transpose(V4) = (len, vector)
  //
  {4,    11, -12, -29, -3, 135, 90, 36, 12},

  // N * transpose(V4) = (len, vector)
  //
  {4,    -32, -6, 2, -16, 114, 128, 97, 57},

  // O * transpose(V4) : (dummy values)
  //
  {4,    0, 0, 0, 0, 0, 0, 0, 0},

  // P * transpose(V4) = (len, vector), two dummy values
  //
  {2,    24, -26, 0, 0, 95, 102, 0, 0}
};

//-----------------------------------------------------------------------------
//
// define the results of operations:
//    F(Mat1, Mat2) -> MatRes
//
//-----------------------------------------------------------------------------

// result for matrix addition (real matrices)
//
float64 MMAT_ADD_MAT_RES_REAL [MMAT_NUM_MATS_REAL] [MMAT_NUM_MATS_REAL] [MMAT_MAT_SIZE] = {

  {
    // A + A
    //
    {4, 4,   6, 8, 14, 4, 6, 10, 12, 2, 16, 8, 2, 6, 8, 10, 14, 4,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + B
    //
    {4, 4,   8, 4, 7, 2, 3, 7, 6, 1, 8, 4, 4, 3, 4, 5, 7, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + C
    //
    {4, 4,   8, 6, 10, 6, 5, 12, 12, 2, 11, 10, 9, 6, 8, 6, 10, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + D
    //
    {4, 4,   8, 4, 7, 2, 5, 7, 6, 1, 11, 10, 4, 3, 8, 11, 10, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + E
    //
    {4, 4,   8, 6, 10, 6, 3, 7, 12, 7, 8, 4, 4, 6, 4, 5, 7, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + F
    //
    {4, 4,   6, 8, 10, 4, 8, 12, 14, 7, 17, 16, 10, 9, 19, 19, 31, 20,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // B + A
    //
    {4, 4,   8, 4, 7, 2, 3, 7, 6, 1, 8, 4, 4, 3, 4, 5, 7, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + B
    //
    {4, 4,   10, 0, 0, 0, 0, 4, 0, 0, 0, 0, 6, 0, 0, 0, 0, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + C
    //
    {4, 4,   10, 2, 3, 4, 2, 9, 6, 1, 3, 6, 11, 3, 4, 1, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + D
    //
    {4, 4,   10, 0, 0, 0, 2, 4, 0, 0, 3, 6, 6, 0, 4, 6, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + E
    //
    {4, 4,   10, 2, 3, 4, 0, 4, 6, 6, 0, 0, 6, 3, 0, 0, 0, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + F
    //
    {4, 4,   8, 4, 3, 2, 5, 9, 8, 6, 9, 12, 12, 6, 15, 14, 24, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // C + A
    //
    {4, 4,   8,  6, 10, 6, 5, 12, 12, 2, 11, 10, 9, 6, 8, 6, 10, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + B
    //
    {4, 4,   10, 2, 3, 4, 2, 9, 6, 1, 3, 6, 11, 3, 4, 1, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + C
    //
    {4, 4,   10, 4, 6, 8, 4, 14, 12, 2, 6, 12, 16, 6, 8, 2, 6, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + D
    //
    {4, 4,   10, 2, 3, 4, 4, 9, 6, 1, 6, 12, 11, 3, 8, 7, 6, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + E
    //
    {4, 4,   10, 4, 6, 8, 2, 9, 12, 7, 3, 6, 11, 6, 4, 1, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + F
    //
    {4, 4,   8, 6, 6, 6, 7, 14, 14, 7, 12, 18, 17, 9, 19, 15, 27, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // D + A
    //
    {4, 4,   8, 4, 7, 2, 5, 7, 6, 1, 11, 10, 4, 3, 8, 11, 10, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + B
    //
    {4, 4,   10, 0, 0, 0, 2, 4, 0, 0, 3, 6, 6, 0, 4, 6, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + C
    //
    {4, 4,   10, 2, 3, 4, 4, 9, 6, 1, 6, 12, 11, 3, 8, 7, 6, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + D
    //
    {4, 4,   10, 0, 0, 0, 4, 4, 0, 0, 6, 12, 6, 0, 8, 12, 6, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + E
    //
    {4, 4,   10, 2, 3, 4, 2, 4, 6, 6, 3, 6, 6, 3, 4, 6, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + F
    //
    {4, 4,   8, 4, 3, 2, 7, 9, 8, 6, 12, 18, 12, 6, 19, 20, 27, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // E + A
    //
    {4, 4,   8, 6, 10, 6, 3, 7, 12, 7, 8, 4, 4, 6, 4, 5, 7, 6,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + B
    //
    {4, 4,   10, 2, 3, 4, 0, 4, 6, 6, 0, 0, 6, 3, 0, 0, 0, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + C
    //
    {4, 4,   10, 4, 6, 8, 2, 9, 12, 7, 3, 6, 11, 6, 4, 1, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + D
    //
    {4, 4,   10, 2, 3, 4, 2, 4, 6, 6, 3, 6, 6, 3, 4, 6, 3, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + E
    //
    {4, 4,   10, 4, 6, 8, 0, 4, 12, 12, 0, 0, 6, 6, 0, 0, 0, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + F
    //
    {4, 4,   8, 6, 6, 6, 5, 9, 14, 12, 9, 12, 12, 9, 15, 14, 24, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // F + A
    //
    {4, 4,   6, 8, 10, 4, 8, 12, 14, 7, 17, 16, 10, 9, 19, 19, 31, 20,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + B
    //
    {4, 4,   8, 4, 3, 2, 5, 9, 8, 6, 9, 12, 12, 6, 15, 14, 24, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + C
    //
    {4, 4,   8, 6, 6, 6, 7, 14, 14, 7, 12, 18, 17, 9, 19, 15, 27, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + D
    //
    {4, 4,   8, 4, 3, 2, 7, 9, 8, 6, 12, 18, 12, 6, 19, 20, 27, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + E
    //
    {4, 4,   8, 6, 6, 6, 5, 9, 14, 12, 9, 12, 12, 9, 15, 14, 24, 22,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + F
    //
    {4, 4,   6, 8, 6, 4, 10, 14, 16, 12, 18, 24, 18, 12, 30, 28, 48, 36,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // G + A (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + B (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + C (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + D (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + E (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + F (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + G
    //
    {4, 2,   8, 10, 14, 4, 6, 18, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G + H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // H + A (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + B (dummy values)
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + C (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + D (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + E (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + F (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H + H
    //
    {2, 4,   8, 14, 6, 4, 10, 4, 18, 6, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};

// result for matrix subtraction (real matrices)
//
float64 MMAT_SUB_MAT_RES_REAL[MMAT_NUM_MATS_REAL][MMAT_NUM_MATS_REAL][MMAT_MAT_SIZE] = {

  {
    // A - A
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - B
    //
    {4, 4,   -2, 4, 7, 2, 3, 3, 6, 1, 8, 4, -2, 3, 4, 5, 7, -2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - C
    //
    {4, 4,   -2, 2, 4, -2, 1, -2, 0, 0, 5, -2, -7, 0, 0, 4, 4, -2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - D
    //
    {4, 4,   -2, 4, 7, 2, 1, 3, 6, 1, 5, -2, -2, 3, 0, -1, 4, -2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - E
    //
    {4, 4,   -2, 2, 4, -2, 3, 3, 0, -5, 8, 4, -2, 0, 4, 5, 7, -2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - F
    //
    {4, 4, 0, 0, 4, 0, -2, -2, -2, -5, -1, -8, -8, -3, -11, -9, -17, -16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // B - A
    //
    {4, 4,   2, -4, -7, -2, -3, -3, -6, -1, -8, -4,  2, -3, -4, -5, -7, 2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - B
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - C
    //
    {4, 4,   0, -2, -3, -4, -2, -5, -6, -1, -3, -6, -5, -3, -4, -1, -3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - D
    //
    {4, 4,   0, 0, 0, 0, -2, 0, 0, 0, -3, -6, 0, 0, -4, -6, -3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - E
    //
    {4, 4,   0, -2, -3, -4, 0, 0, -6, -6, 0, 0, 0, -3, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - F
    //
    {4, 4,   2, -4, -3, -2, -5, -5, -8, -6, -9, -12, -6, -6, -15, -14, -24, -14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // C - A
    //
    {4, 4,   2, -2, -4, 2, -1, 2, 0, 0, -5, 2, 7, 0, 0, -4, -4, 2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - B
    //
    {4, 4,   0, 2, 3, 4, 2, 5, 6, 1, 3, 6, 5, 3, 4, 1, 3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - C
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - D
    //
    {4, 4,   0, 2, 3, 4, 0, 5, 6, 1, 0, 0, 5, 3, 0, -5, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - E
    //
    {4, 4,   0, 0, 0, 0, 2, 5, 0, -5, 3, 6, 5, 0, 4, 1, 3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - F
    //
    {4, 4,   2, -2, 0, 2, -3, 0, -2, -5, -6, -6, -1, -3, -11, -13, -21, -14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // D - A
    //
    {4, 4,   2, -4, -7, -2, -1, -3, -6, -1, -5, 2, 2, -3, 0, 1, -4, 2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - B
    //
    {4, 4,   0, 0, 0, 0, 2, 0, 0, 0, 3, 6, 0, 0, 4, 6, 3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - C
    //
    {4, 4,   0, -2, -3, -4, 0, -5, -6, -1, 0, 0, -5, -3, 0, 5, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - D
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - E
    //
    {4, 4,   0, -2, -3, -4, 2, 0, -6, -6, 3, 6, 0, -3, 4, 6, 3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - F
    //
    {4, 4,   2, -4, -3, -2,  -3, -5, -8, -6,  -6, -6, -6, -6,  -11, -8, -21, -14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // E - A
    //
    {4, 4,   2, -2, -4, 2, -3, -3, 0, 5, -8, -4, 2, 0, -4, -5, -7, 2,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - B
    //
    {4, 4,   0, 2, 3, 4, 0, 0, 6, 6, 0, 0, 0, 3, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - C
    //
    {4, 4,   0, 0, 0, 0, -2, -5, 0, 5, -3, -6, -5, 0, -4, -1, -3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - D
    //
    {4, 4,   0, 2, 3, 4, -2, 0, 6, 6, -3, -6, 0, 3, -4, -6, -3, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - E
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - F
    //
    {4, 4,   2, -2, 0, 2, -5, -5, -2, 0, -9, -12, -6, -3, -15, -14, -24, -14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - G
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // F - A
    //
    {4, 4,   0, 0, -4, 0,  2, 2, 2, 5,  1, 8, 8, 3,  11, 9, 17, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - B
    //
    {4, 4,   -2, 4, 3, 2, 5, 5, 8, 6, 9, 12, 6, 6, 15, 14, 24, 14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - C
    //
    {4, 4,   -2, 2, 0, -2, 3, 0, 2, 5,  6, 6, 1, 3, 11, 13, 21, 14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - D
    //
    {4, 4,   -2, 4, 3, 2, 3, 5, 8, 6, 6, 6, 6, 6, 11, 8, 21, 14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - E
    //
    {4, 4,   -2, 2, 0, -2, 5, 5, 2, 0, 9, 12, 6, 3, 15, 14, 24, 14,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - F
    //
    {4, 4,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // G - A (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - B (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - C (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - D (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - E (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - F (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - G
    //
    {4, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G - H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // H - A (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - B (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - C (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - D (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - E (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - F (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H - H
    //
    {2, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  }
};

// results for real matrix multiplication (real matrices)
//
float64 MMAT_MULT_MAT_RES_REAL [MMAT_NUM_MATS_REAL] [MMAT_NUM_MATS_REAL] [MMAT_MAT_SIZE] = {
  {
    // A * A
    //
    {4, 4,  85, 70, 66, 35, 76, 66, 64, 31, 56, 71, 102, 29, 91, 79, 79, 38,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * B
    //
    {4, 4,  15,  8, 21,  8, 15, 10, 18, 4, 40, 8, 3, 12, 20, 10, 21,  8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * C
    //
    {4, 4,  52, 78, 95, 45, 47, 78, 90, 39, 63, 53, 65, 51, 59, 87, 104, 50,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * D
    //
    {4, 4,  52, 62, 27, 8, 47, 52, 21, 4, 63, 32, 12, 12, 59, 64, 27, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * E
    //
    {4, 4,  15, 14, 54, 65, 15, 16, 57, 64, 40, 24, 51, 71, 20, 18, 63, 75,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * F
    //
    {4, 4,   122, 152, 152, 108, 103, 133, 127, 90, 98, 114, 137, 100, 130, 163, 163, 116,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * G
    //
    {4, 2,   65, 92, 67, 82, 69, 66, 76, 99, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // A * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // B * A
    //
    {4, 4,  15, 20, 35, 10,  6, 10, 12,  2, 24, 12,  3,  9, 16, 20, 28,  8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * B
    //
    {4, 4,  25,  0,  0,  0,  0,  4,  0,  0,  0,  0,  9,  0, 0,  0,  0, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * C
    //
    {4, 4,  25, 10, 15, 20,  4, 14, 12,  2,  9, 18, 24,  9, 16,  4, 12, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * D
    //
    {4, 4,  25,  0,  0,  0,  4,  4,  0,  0,  9, 18,  9,  0, 16, 24, 12, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * E
    //
    {4, 4,  25, 10, 15, 20, 0, 4, 12, 12, 0, 0, 9, 9, 0, 0, 0, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * F
    //
    {4, 4,  15, 20, 15, 10, 10, 14, 16, 12, 27, 36, 27, 18, 60, 56, 96, 72,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * G
    //
    {4, 2,   20, 25, 14, 4, 9, 27, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // B * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // C * A
    //
    {4, 4,  61, 62, 78, 29, 79, 72, 69, 31, 103, 89, 86, 42, 55, 53, 65, 26,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * B
    //
    {4, 4,  25,  4,  9, 16, 10, 14, 18, 4, 15, 12, 24, 12, 20,  2,  9, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * C
    //
    {4, 4,  54, 46, 63, 47, 46, 90, 99, 37, 63, 99, 118, 54, 47, 37, 54, 42,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * D
    //
    {4, 4,  54, 46, 21, 16, 46, 56, 21, 4, 63, 78, 33, 12, 47, 44, 21, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * E
    //
    {4, 4,  25, 14, 36, 57, 10, 18, 66, 72, 15, 18, 69, 84, 20, 10, 27, 47,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * F
    //
    {4, 4,  112, 126, 154, 112, 110, 143, 140, 100, 156, 192, 201, 144, 104, 115, 143, 104,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * G
    //
    {4, 2,   51, 68, 77, 81, 84, 108, 40, 61, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // C * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // D * A
    //
    {4, 4,  15, 20, 35, 10, 12, 18, 26, 6, 51, 54, 60, 21, 70, 78, 95, 31,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * B
    //
    {4, 4,  25,  0,  0,  0, 10,  4,  0,  0, 15, 12,  9,  0, 20, 12,  9, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * C
    //
    {4, 4,  25, 10, 15, 20, 14, 18, 18, 10, 36, 66, 69, 27, 57, 72, 84, 47,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * D
    //
    {4, 4,  25,  0,  0,  0, 14,  4,  0,  0, 36, 30, 9, 0, 57, 54, 21, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * E
    //
    {4, 4,  25, 10, 15, 20, 10, 8, 18, 20, 15, 18, 54, 57, 20, 20, 57, 77,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * F
    //
    {4, 4,  15, 20, 15, 10, 16, 22, 22, 16, 66, 90, 84, 60, 129, 150, 183, 134,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * G
    //
    {4, 2,   20, 25, 22, 14, 63, 54, 75, 71, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // D * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
    {
    // E * A
    //
    {4, 4,  61, 62, 78, 29, 78, 64, 60, 32, 36, 27, 24, 15, 16, 20, 28, 8,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * B
    //
    {4, 4,  25, 4, 9, 16, 0, 4, 18, 24, 0, 0, 9, 12, 0, 0, 0, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * C
    //
    {4, 4,  54, 46, 63, 47, 46, 56, 78, 44, 21, 21, 33, 21, 16, 4, 12, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * D
    //
    {4, 4,  54, 46, 21, 16, 46, 76, 36, 24, 21, 36, 18, 12, 16, 24, 12, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * E
    //
    {4, 4,  25, 14, 36, 57, 0, 4, 30, 54, 0, 0, 9, 21, 0, 0, 0, 16,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * F
    //
    {4, 4,  112, 126, 154, 112, 154, 170, 214, 156, 72, 78, 99, 72, 60, 56, 96, 72,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * G
    //
    {4, 2,  51, 68, 44, 76, 15, 36, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // E * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // F * A
    //
    {4, 4,  53, 54, 62, 23, 124, 117, 127, 53, 159, 162, 186, 69, 351, 316, 339, 152,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * B
    //
    {4, 4,  15, 8, 9, 8, 25, 14, 24, 24, 45, 24, 27, 24, 75, 28, 72, 72,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * C
    //
    {4, 4,  40, 54, 63, 33, 87, 113, 139, 75, 120, 162, 189, 99, 247, 290, 375, 218,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * D
    //
    {4, 4,  40, 38, 15, 8, 87, 98, 42, 24, 120, 114, 45, 24, 247, 280, 126, 72,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * E
    //
    {4, 4,  15, 14, 42, 53, 25, 24, 81, 110, 45, 42, 126, 159, 75, 58, 201, 288,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * F
    //
    {4, 4,  86, 104, 116, 84, 212, 249, 287, 208, 258, 312, 348, 252, 601, 698, 805, 582,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * G
    //
    {4, 2,  53, 56, 105, 129, 159, 168, 266, 373, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // F * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // G * A (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * B (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * C (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * D (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * E (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * F (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * G (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // G * H
    //
    {4, 4,   41, 38, 57, 23, 38, 53, 39, 20, 57, 39, 90, 33, 23, 20, 33, 13,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // H * A
    //
    {2, 4,  65, 73, 87, 28, 105, 81, 77, 45, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * B
    //
    {2, 4,  20, 14, 9, 8, 25, 4, 27, 12, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * C
    //
    {2, 4,  51, 77, 84, 40, 68, 81, 108, 61, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * D
    //
    {2, 4,  51, 44, 15, 8, 68, 76, 36, 12, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * E
    //
    {2, 4,  20, 22, 63, 75, 25, 14, 54, 71, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * F
    //
    {2, 4,  104, 129, 143, 104, 151, 184, 184, 130, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * G
    //
    {2, 2,  78, 67, 67, 119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // H * H (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};

// result for matrix addition (comlex matrices)
//
float64 MMAT_ADD_MAT_RES_COMPLEX [MMAT_NUM_MATS_COMPLEX] [MMAT_NUM_MATS_COMPLEX] [MMAT_MAT_SIZE] = {

  {
    // I + I
    //
    {4, 4,   4, 18, 2, 8, 6, 10, 16, 2, 16, 8, 18, 6, 8, 16, 14, 4, 
	     8, 10, 2, 12, 14, 18, 10, 6, 10, 12, 8, 8, 6, 10, 4, 16
    },

    // I + J
    //
    {4, 4,   11, 9, 1, 4, 3, 9, 8, 1, 8, 4, 10, 3, 4, 8, 7, 2, 
	     7, 5, 1, 6, 7, 11, 5, 3, 5, 6, 9, 4, 3, 5, 2, 11
    },

    // I + K
    //
    {4, 4,   4, 16, 2, 7, 10, 10, 10, 5, 9, 6, 16, 12, 7, 12, 16, 8, 
	     5, 8, 6, 8, 10, 16, 9, 4, 10, 10, 7, 10, 5, 6, 8, 10
    },

    // I + L
    //
    {4, 4,   4, 9, 1, 4, 7, 6, 8, 1, 14, 11, 18, 3, 8, 10, 10, 10, 
	     10, 5, 1, 6, 16, 13, 5, 3, 11, 12, 5, 4, 11, 14, 5, 9
    },

    // I + M
    //
    {4, 4,   10, 18, 2, 13, 3, 14, 11, 6, 8, 4, 11, 11, 4, 8, 7, 6, 
	     7, 12, 6, 12, 7, 15, 8, 10, 5, 6, 7, 12, 3, 5, 2, 9
    },

    // I + N
    //
    {4, 4,   4, 15, 5, 10, 6, 13, 11, 10, 9, 10, 15, 6, 5, 11, 9, 5, 
	     8, 11, 7, 14, 15, 10, 10, 11, 11, 9, 5, 8, 5, 8, 5, 12
    },

    // I + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // I + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // J + I
    //
    {4, 4,   11, 9, 1, 4, 3, 9, 8, 1, 8, 4, 10, 3, 4, 8, 7, 2, 
	     7, 5, 1, 6, 7, 11, 5, 3, 5, 6, 9, 4, 3, 5, 2, 11
    },

    // J + J
    //
    {4, 4,   18, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 
	     6, 0, 0, 0, 0, 4, 0, 0, 0, 0, 10, 0, 0, 0, 0, 6
    },

    // J + K
    //
    {4, 4,   11, 7, 1, 3, 7, 9, 2, 4, 1, 2, 8, 9, 3, 4, 9, 6, 
	     4, 3, 5, 2, 3, 9, 4, 1, 5, 4, 8, 6, 2, 1, 6, 5
    },

    // J + L
    //
    {4, 4,   11, 0, 0, 0, 4, 5, 0, 0, 6, 7, 10, 0, 4, 2, 3, 8, 
	     9, 0, 0, 0, 9, 6, 0, 0, 6, 6, 6, 0, 8, 9, 3, 4
    },

    // J + M
    //
    {4, 4,   17, 9, 1, 9, 0, 13, 3, 5, 0, 0, 3, 8, 0, 0, 0, 4, 
	     6, 7, 5, 6, 0, 8, 3, 7, 0, 0, 8, 8, 0, 0, 0, 4
    },

    // J + N
    //
    {4, 4,   11, 6, 4, 6, 3, 12, 3, 9, 1, 6, 7, 3, 1, 3, 2, 3, 
	     7, 6, 6, 8, 8, 3, 5, 8, 6, 3, 6, 4, 2, 3, 3, 7
    },

    // J + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // J + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // K + I
    //
    {4, 4,   4, 16, 2, 7, 10, 10, 10, 5, 9, 6, 16, 12, 7, 12, 16, 8, 
	     5, 8, 6, 8, 10, 16, 9, 4, 10, 10, 7, 10, 5, 6, 8, 10
    },

    // K + J
    //
    {4, 4,   11, 7, 1, 3, 7, 9, 2, 4, 1, 2, 8, 9, 3, 4, 9, 6, 
	     4, 3, 5, 2, 3, 9, 4, 1, 5, 4, 8, 6, 2, 1, 6, 5
    },

    // K + K
    //
    {4, 4,   4, 14, 2, 6, 14, 10, 4, 8, 2, 4, 14, 18, 6, 8, 18, 12, 
	     2, 6, 10, 4, 6, 14, 8, 2, 10, 8, 6, 12, 4, 2, 12, 4
    },

    // K + L
    //
    {4, 4,   4, 7, 1, 3, 11, 6, 2, 4, 7, 9, 16, 9, 7, 6, 12, 14, 
	     7, 3, 5, 2, 12, 11, 4, 1, 11, 10, 4, 6, 10, 10, 9, 3
    },

    // K + M
    //
    {4, 4,   10, 16, 2, 12, 7, 14, 5, 9, 1, 2, 9, 17, 3, 4, 9, 10, 
	     4, 10, 10, 8, 3, 13, 7, 8, 5, 4, 6, 14, 2, 1, 6, 3
    },

    // K + N
    //
    {4, 4,   4, 13, 5, 9, 10, 13, 5, 13, 2, 8, 13, 12, 4, 7, 11, 9, 
	     5, 9, 11, 10, 11, 8, 9, 9, 11, 7, 4, 10, 4, 4, 9, 6
    },

    // K + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // K + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // L + I
    //
    {4, 4,   4, 9, 1, 4, 7, 6, 8, 1, 14, 11, 18, 3, 8, 10, 10, 10, 
	     10, 5, 1, 6, 16, 13, 5, 3, 11, 12, 5, 4, 11, 14, 5, 9
    },

    // L + J
    //
    {4, 4,   11, 0, 0, 0, 4, 5, 0, 0, 6, 7, 10, 0, 4, 2, 3, 8, 
	     9, 0, 0, 0, 9, 6, 0, 0, 6, 6, 6, 0, 8, 9, 3, 4
    },

    // L + K
    //
    {4, 4,   4, 7, 1, 3, 11, 6, 2, 4, 7, 9, 16, 9, 7, 6, 12, 14, 
	     7, 3, 5, 2, 12, 11, 4, 1, 11, 10, 4, 6, 10, 10, 9, 3
    },

    // L + L
    //
    {4, 4,   4, 0, 0, 0, 8, 2, 0, 0, 12, 14, 18, 0, 8, 4, 6, 16, 
	     12, 0, 0, 0, 18, 8, 0, 0, 12, 12, 2, 0, 16, 18, 6, 2
    },

    // L + M
    //
    {4, 4,   10, 9, 1, 9, 4, 10, 3, 5, 6, 7, 11, 8, 4, 2, 3, 12, 
	     9, 7, 5, 6, 9, 10, 3, 7, 6, 6, 4, 8, 8, 9, 3, 2
    },

    // L + N
    //
    {4, 4,   4, 6, 4, 6, 7, 9, 3, 9, 7, 13, 15, 3, 5, 5, 5, 11, 
	     10, 6, 6, 8, 17, 5, 5, 8, 12, 9, 2, 4, 10, 12, 6, 5
    },

    // L + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // L + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // M + I
    //
    {4, 4,   10, 18, 2, 13, 3, 14, 11, 6, 8, 4, 11, 11, 4, 8, 7, 6, 
	     7, 12, 6, 12, 7, 15, 8, 10, 5, 6, 7, 12, 3, 5, 2, 9
    },

    // M + J
    //
    {4, 4,   17, 9, 1, 9, 0, 13, 3, 5, 0, 0, 3, 8, 0, 0, 0, 4, 
	     6, 7, 5, 6, 0, 8, 3, 7, 0, 0, 8, 8, 0, 0, 0, 4
    },

    // M + K
    //
    {4, 4,   10, 16, 2, 12, 7, 14, 5, 9, 1, 2, 9, 17, 3, 4, 9, 10, 
	     4, 10, 10, 8, 3, 13, 7, 8, 5, 4, 6, 14, 2, 1, 6, 3
    },

    // M + L
    //
    {4, 4,   10, 9, 1, 9, 4, 10, 3, 5, 6, 7, 11, 8, 4, 2, 3, 12, 
	     9, 7, 5, 6, 9, 10, 3, 7, 6, 6, 4, 8, 8, 9, 3, 2
    },

    // M + M
    //
    {4, 4,   16, 18, 2, 18, 0, 18, 6, 10, 0, 0, 4, 16, 0, 0, 0, 8, 
	     6, 14, 10, 12, 0, 12, 6, 14, 0, 0, 6, 16, 0, 0, 0, 2
    },

    // M + N
    //
    {4, 4,   10, 15, 5, 15, 3, 17, 6, 14, 1, 6, 8, 11, 1, 3, 2, 7, 
	     7, 13, 11, 14, 8, 7, 8, 15, 6, 3, 4, 12, 2, 3, 3, 5
    },

    // M + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // M + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // N + I
    //
    {4, 4,   4, 15, 5, 10, 6, 13, 11, 10, 9, 10, 15, 6, 5, 11, 9, 5, 
	     8, 11, 7, 14, 15, 10, 10, 11, 11, 9, 5, 8, 5, 8, 5, 12
    },

    // N + J
    //
    {4, 4,   11, 6, 4, 6, 3, 12, 3, 9, 1, 6, 7, 3, 1, 3, 2, 3, 
	     7, 6, 6, 8, 8, 3, 5, 8, 6, 3, 6, 4, 2, 3, 3, 7
    },

    // N + K
    //
    {4, 4,   4, 13, 5, 9, 10, 13, 5, 13, 2, 8, 13, 12, 4, 7, 11, 9, 
	     5, 9, 11, 10, 11, 8, 9, 9, 11, 7, 4, 10, 4, 4, 9, 6
    },

    // N + L
    //
    {4, 4,   4, 6, 4, 6, 7, 9, 3, 9, 7, 13, 15, 3, 5, 5, 5, 11, 
	     10, 6, 6, 8, 17, 5, 5, 8, 12, 9, 2, 4, 10, 12, 6, 5
    },

    // N + M
    //
    {4, 4,   10, 15, 5, 15, 3, 17, 6, 14, 1, 6, 8, 11, 1, 3, 2, 7, 
	     7, 13, 11, 14, 8, 7, 8, 15, 6, 3, 4, 12, 2, 3, 3, 5
    },

    // N + N
    //
    {4, 4,   4, 12, 8, 12, 6, 16, 6, 18, 2, 12, 12, 6, 2, 6, 4, 6, 
	     8, 12, 12, 16, 16, 2, 10, 16, 12, 6, 2, 8, 4, 6, 6, 8
    },

    // N + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // N + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // O + I (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + J (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + K (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + L (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + M (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + N (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + O
    //
    {4, 2,   14, 2, 12, 4, 12, 6, 4, 16, 16, 12, 6, 6, 12, 16, 10, 8, 
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O + P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // P + I (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + J (dummy values)
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + K (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + L (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + M (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + N (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P + P
    //
    {2, 4,   16, 8, 4, 6, 2, 12, 4, 16, 12, 6, 6, 2, 4, 14, 8, 10, 
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};

// result for matrix subtraction (complex matrices)
//
float64 MMAT_SUB_MAT_RES_COMPLEX[MMAT_NUM_MATS_COMPLEX][MMAT_NUM_MATS_COMPLEX][MMAT_MAT_SIZE] = {

  {
    // I - I
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // I - J
    //
    {4, 4,   -7, 9, 1, 4, 3, 1, 8, 1, 8, 4, 8, 3, 4, 8, 7, 2, 
	     1, 5, 1, 6, 7, 7, 5, 3, 5, 6, -1, 4, 3, 5, 2, 5
    },

    // I - K
    //
    {4, 4,   0, 2, 0, 1, -4, 0, 6, -3, 7, 2, 2, -6, 1, 4, -2, -4, 
	     3, 2, -4, 4, 4, 2, 1, 2, 0, 2, 1, -2, 1, 4, -4, 6
    },

    // I - L
    //
    {4, 4,   0, 9, 1, 4, -1, 4, 8, 1, 2, -3, 0, 3, 0, 6, 4, -6, 
	     -2, 5, 1, 6, -2, 5, 5, 3, -1, 0, 3, 4, -5, -4, -1, 7
    },

    // I - M
    //
    {4, 4,   -6, 0, 0, -5, 3, -4, 5, -4, 8, 4, 7, -5, 4, 8, 7, -2, 
	     1, -2, -4, 0, 7, 3, 2, -4, 5, 6, 1, -4, 3, 5, 2, 7
    },

    // I - N
    //
    {4, 4,   0, 3, -3, -2, 0, -3, 5, -8, 7, -2, 3, 0, 3, 5, 5, -1, 
	     0, -1, -5, -2, -1, 8, 0, -5, -1, 3, 3, 0, 1, 2, -1, 4
    },

    // I - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // I - P (dummy valuMs)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // J - I
    //
    {4, 4,   7, -9, -1, -4, -3, -1, -8, -1, -8, -4, -8, -3, -4, -8, -7, -2, 
	     -1, -5, -1, -6, -7, -7, -5, -3, -5, -6, 1, -4, -3, -5, -2, -5
    },

    // J - J
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // J - K
    //
    {4, 4,   7, -7, -1, -3, -7, -1, -2, -4, -1, -2, -6, -9, -3, -4, -9, -6, 
	     2, -3, -5, -2, -3, -5, -4, -1, -5, -4, 2, -6, -2, -1, -6, 1
    },

    // J - L
    //
    {4, 4,   7, 0, 0, 0, -4, 3, 0, 0, -6, -7, -8, 0, -4, -2, -3, -8, 
	    -3, 0, 0, 0, -9, -2, 0, 0, -6, -6, 4, 0, -8, -9, -3, 2
    },

    // J - M
    //
    {4, 4,   1, -9, -1, -9, 0, -5, -3, -5, 0, 0, -1, -8, 0, 0, 0, -4, 
	     0, -7, -5, -6, 0, -4, -3, -7, 0, 0, 2, -8, 0, 0, 0, 2
    },

    // J - N
    //
    {4, 4,   7, -6, -4, -6, -3, -4, -3, -9, -1, -6, -5, -3, -1, -3, -2, -3, 
	    -1, -6, -6, -8, -8, 1, -5, -8, -6, -3, 4, -4, -2, -3, -3, -1
    },

    // J - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // J - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // K - I
    //
    {4, 4,   0, -2, 0, -1, 4, 0, -6, 3, -7, -2, -2, 6, -1, -4, 2, 4, 
	    -3, -2, 4, -4, -4, -2, -1, -2, 0, -2, -1, 2, -1, -4, 4, -6
    },

    // K - J
    //
    {4, 4,   -7, 7, 1, 3, 7, 1, 2, 4, 1, 2, 6, 9, 3, 4, 9, 6, 
	     -2, 3, 5, 2, 3, 5, 4, 1, 5, 4, -2, 6, 2, 1, 6, -1
    },

    // K - K
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // K - L
    //
    {4, 4,   0, 7, 1, 3, 3, 4, 2, 4, -5, -5, -2, 9, -1, 2, 6, -2, 
	     -5, 3, 5, 2, -6, 3, 4, 1, -1, -2, 2, 6, -6, -8, 3, 1
    },

    // K - M
    //
    {4, 4,   -6, -2, 0, -6, 7, -4, -1, -1, 1, 2, 5, 1, 3, 4, 9, 2, 
	     -2, -4, 0, -4, 3, 1, 1, -6, 5, 4, 0, -2, 2, 1, 6, 1
    },

    // K - N
    //
    {4, 4,   0, 1, -3, -3, 4, -3, -1, -5, 0, -4, 1, 6, 2, 1, 7, 3, 
	     -3, -3, -1, -6, -5, 6, -1, -7, -1, 1, 2, 2, 0, -2, 3, -2
    },

    // K - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // K - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // L - I
    //
    {4, 4,   0, -9, -1, -4, 1, -4, -8, -1, -2, 3, 0, -3, 0, -6, -4, 6, 
	     2, -5, -1, -6, 2, -5, -5, -3, 1, 0, -3, -4, 5, 4, 1, -7
    },

    // L - J
    //
    {4, 4,   -7, 0, 0, 0, 4, -3, 0, 0, 6, 7, 8, 0, 4, 2, 3, 8, 
	     3, 0, 0, 0, 9, 2, 0, 0, 6, 6, -4, 0, 8, 9, 3, -2
    },

    // L - K
    //
    {4, 4,   0, -7, -1, -3, -3, -4, -2, -4, 5, 5, 2, -9, 1, -2, -6, 2, 
	     5, -3, -5, -2, 6, -3, -4, -1, 1, 2, -2, -6, 6, 8, -3, -1
    },

    // L - L
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // L - M
    //
    {4, 4,   -6, -9, -1, -9, 4, -8, -3, -5, 6, 7, 7, -8, 4, 2, 3, 4, 
	     3, -7, -5, -6, 9, -2, -3, -7, 6, 6, -2, -8, 8, 9, 3, 0
    },

    // L - N
    //
    {4, 4,   0, -6, -4, -6, 1, -7, -3, -9, 5, 1, 3, -3, 3, -1, 1, 5, 
	     2, -6, -6, -8, 1, 3, -5, -8, 0, 3, 0, -4, 6, 6, 0, -3
    },

    // L - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // L - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },
  },
  {
    // M - I
    //
    {4, 4,   6, 0, 0, 5, -3, 4, -5, 4, -8, -4, -7, 5, -4, -8, -7, 2, 
	     -1, 2, 4, 0, -7, -3, -2, 4, -5, -6, -1, 4, -3, -5, -2, -7
    },

    // M - J
    //
    {4, 4,   -1, 9, 1, 9, 0, 5, 3, 5, 0, 0, 1, 8, 0, 0, 0, 4, 
	     0, 7, 5, 6, 0, 4, 3, 7, 0, 0, -2, 8, 0, 0, 0, -2
    },

    // M - K
    //
    {4, 4,   6, 2, 0, 6, -7, 4, 1, 1, -1, -2, -5, -1, -3, -4, -9, -2, 
	     2, 4, 0, 4, -3, -1, -1, 6, -5, -4, 0, 2, -2, -1, -6, -1
    },

    // M - L
    //
    {4, 4,   6, 9, 1, 9, -4, 8, 3, 5, -6, -7, -7, 8, -4, -2, -3, -4, 
	-    3, 7, 5, 6, -9, 2, 3, 7, -6, -6, 2, 8, -8, -9, -3, 0
    },

    // M - M
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // M - N
    //
    {4, 4,   6, 3, -3, 3, -3, 1, 0, -4, -1, -6, -4, 5, -1, -3, -2, 1, 
	     -1, 1, -1, -2, -8, 5, -2, -1, -6, -3, 2, 4, -2, -3, -3, -3
    },

    // M - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // M - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },
  },
  {
    // N - I
    //
    {4, 4,   0, -3, 3, 2, 0, 3, -5, 8, -7, 2, -3, 0, -3, -5, -5, 1, 
	     0, 1, 5, 2, 1, -8, 0, 5, 1, -3, -3, 0, -1, -2, 1, -4
    },

    // N - J
    //
    {4, 4,   -7, 6, 4, 6, 3, 4, 3, 9, 1, 6, 5, 3, 1, 3, 2, 3, 
	     1, 6, 6, 8, 8, -1, 5, 8, 6, 3, -4, 4, 2, 3, 3, 1
    },

    // N - K
    //
    {4, 4,   0, -1, 3, 3, -4, 3, 1, 5, 0, 4, -1, -6, -2, -1, -7, -3, 
	     3, 3, 1, 6, 5, -6, 1, 7, 1, -1, -2, -2, 0, 2, -3, 2
    },

    // N - L
    //
    {4, 4,   0, 6, 4, 6, -1, 7, 3, 9, -5, -1, -3, 3, -3, 1, -1, -5, 
	     -2, 6, 6, 8, -1, -3, 5, 8, 0, -3, 0, 4, -6, -6, 0, 3
    },

    // N - M
    //
    {4, 4,   -6, -3, 3, -3, 3, -1, 0, 4, 1, 6, 4, -5, 1, 3, 2, -1, 
	     1, -1, 1, 2, 8, -5, 2, 1, 6, 3, -2, -4, 2, 3, 3, 3
    },

    // N - N
    //
    {4, 4,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // N - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },

    // N - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    },
  },
  {
    // O - I (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - J (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - K (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - L (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - M (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - N (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - O
    //
    {4, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // O - P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // P - I (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - J (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - K (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - L (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - M (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - N (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - O (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // P - P
    //
    {2, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};

// results for matrix multiplication (complex matrices)
//
float64 MMAT_MULT_MAT_RES_COMPLEX [MMAT_NUM_MATS_COMPLEX] [MMAT_NUM_MATS_COMPLEX] [MMAT_MAT_SIZE] = {
  {
    // I * I
    //
    {4, 4,  -19, -2, 66, -63, -36, -69, 44, -70,
            18, 29, 83, -27, 15, 8, 93, -56, 
	    143, 230, 154, 111, 183, 265, 207,
            131, 190, 268, 187, 166, 182, 268, 193, 131
    },

    // I * J
    //
    {4, 4,  6, 26, -4, -18, 6, 2, -17, -9,
            57, 4, -11, -12, 27, 22, -3, -24, 
	    42, 38, 6, 12, 72, 46, 45, 3,
            69, 32, 49, 9, 39, 36, 37, 6
    },

    // I * K
    //
    {4, 4,  44, 20, -16, 44, -13, -41, -26, 48,
            11, 29, 21, 91, 33, 30, -2, 80, 
	    104, 156, 148, 104, 151, 193, 152, 181,
            139, 180, 182, 179, 134, 180, 184, 157
    },

    // I * L
    //
    {4, 4,  -61, -56, 2, 26, -99, -30, 61, 5,
            -42, -11, 74, 20, -49, -43, 43, 8, 
	    189, 102, 40, 52, 211, 127, 65, 25,
            236, 139, 66, 35, 224, 127, 55, 66
    },

    // I * M
    //
    {4, 4,  4, 41, -7, 14, 3, -31, -43, -28,
            49, 37, -17, 68, 23, 57, 6, 63, 
	    38, 149, 61, 180, 65, 195, 98, 278,
            64, 179, 110, 274, 36, 148, 87, 238
    },

    // I * N
    //
    {4, 4,  -38, 52, -19, 8, -106, 34, -24, -70,
            -60, 83, 28, 0, -39, 83, 17, 19, 
	    124, 124, 119, 198, 151, 203, 145, 247,
            160, 202, 156, 252, 157, 153, 132, 225
    },

    // I * O
    //
    {4, 2,  -1, -16, -27, -76, 38, -29, 31, -24,
            145, 128, 231, 165, 248, 205, 187, 195,
	    0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    },

    // I * P (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // J * I
    //
    {4, 4,  6, 66, 6, 18, -2, 2,
            22, -2, -17, -26, -11, -17, -9, -15, -6, -24, 
	    42, 72, 12, 66, 34, 46, 36, 14,
            45, 26, 49, 19, 12, 24, 21, 6
    },

    // J * J
    //
    {4, 4,  72, 0, 0, 0, 0, 12, 0, 0,
            0, 0, -24, 0, 0, 0, 0, -9, 
	    54, 0, 0, 0, 0, 16, 0, 0,
            0, 0, 10, 0, 0, 0, 0, 0
    },

    // J * K
    //
    {4, 4,  15, 54, -6, 21, 22, 6, 0, 14, -24, -18, -8, -21, -6, -3, -18, -6, 
	    15, 48, 48, 27, 26, 38, 20, 12, 10, 14, 38, 51, 9, 12, 27, 18
    },

    // J * L
    //
    {4, 4,  0, 0, 0, 0, -2, -4,
            0, 0, -24, -23, 4, 0, -24, -27, -9, -3, 
	    60, 0, 0, 0, 44, 18, 0, 0,
            36, 41, 46, 0, 12, 6, 9, 24
    },

    // J * M
    //
    {4, 4,  63, 60, -6, 63, 0, 24, 6, 6,
            0, 0, -13, -32, 0, 0, 0, -3, 
	    51, 90, 48, 81, 0, 42, 18, 38,
            0, 0, 13, 48, 0, 0, 0, 12
    },

    // J * N
    //
    {4, 4,  6, 36, 18, 30, -4, 30,
            2, 20, -29, -9, 1, -17, -6, -9, -9, -12, 
	    42, 72, 66, 90, 38, 20, 26, 50,
            11, 33, 31, 19, 3, 9, 6, 9
    },

    // J * O
    //
    {4, 2,   39, -9, 18, 2, -24, -37, -15, -12,
            93, 57, 24, 16, 36, 23, 6, 24, 
             0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // J * P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // K * I
    //
    {4, 4,  -11, 9, 48, -27, -23, 21, 37, -16, 19, 10, 94, -57, 63, 66, 123, 0, 
	    130, 154, 131, 87, 148, 198, 150, 130, 150, 235, 163, 157, 166, 198, 149, 145
    },

    // K * J
    //
    {4, 4,  15, 22, -24, -6, 54, 6,
            -18, -3, -6, 0, -8, -18, 21, 14, -21, -6, 
	    15, 26, 10, 9, 48, 38, 14, 12,
            48, 20, 38, 27, 27, 12, 51, 18
    },

    // K * K
    //
    {4, 4,  24, 17, 6, 22, 17, 19, 6, 44,
            6, 6, 49, 84, 22, 44, 84, 97, 
	    68, 102, 119, 95, 102, 136, 139, 118,
            119, 139, 176, 158, 95, 118, 158, 152
    },

    // K * L
    //
    {4, 4,  -29, -40, 7, 22, -51, -34,
            23, 31, -44, -19, 69, 66, 27, 21, 87, 46, 
	    157, 103, 61, 19, 193, 105, 53, 12,
            206, 168, 79, 57, 208, 171, 87, 22
    },

    // K * M
    //
    {4, 4,  13, 56, -4, 4, 47, 45, -22, 20,
            -7, -32, -25, 23, 18, 43, 2, 74, 
	    14, 92, 54, 144, 45, 169, 88, 195,
            43, 100, 55, 198, 25, 72, 71, 203
    },

    // K * N
    //
    {4, 4,  -33, 53, 9, 27, -59, 66, 3, 5,
            -58, 30, -1, -36, -23, 85, 61, 43, 
	    94, 97, 104, 142, 120, 166, 140, 216,
            111, 154, 112, 181, 125, 129, 116, 161
    },

    // K * O
    //
    {4, 2,  11, -20, 25, -20, -21, 8, 46, 15,
            117, 91, 192, 126, 190, 174, 180, 164, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // K * P (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // L * I
    //
    {4, 4,  -20, -12, -4, -28, -53, -40, -17, -49,
            34, 35, 103, 0, -43, -22, 36, -52, 
	    20, 64, 8, 36, 53, 130, 50, 67,
            156, 235, 140, 126, 140, 233, 156, 158
    },

    // L * J
    //
    {4, 4,  0, 0, 0, 0, 9, -4,
            0, 0, 36, 16, 4, 0, 12, -10, -12, -3, 
	    60, 0, 0, 0, 93, 18, 0, 0,
            72, 38, 46, 0, 84, 40, 18, 24
    },

    // L * K
    //
    {4, 4,  -2, -4, -28, -6, -6, -22, -55, -6,
            41, 31, 26, 103, -3, -24, 10, 50, 
	    14, 48, 16, 22, 53, 102, 41, 52,
            127, 177, 110, 124, 126, 157, 141, 137
    },

    // L * L
    //
    {4, 4,  -32, 0, 0, 0, -78, -15, 0, 0,
            -2, 40, 80, 0, -89, -24, 45, 63, 
	    24, 0, 0, 0, 67, 8, 0, 0,
            195, 95, 18, 0, 198, 130, 57, 16
    },

    // L * M
    //
    {4, 4,  -2, -24, -28, -18, 5, -42, -50, -41,
            30, 39, -6, 75, 8, -56, -60, -34, 
	    54, 68, 16, 66, 84, 151, 44, 132,
            66, 192, 104, 249, 76, 193, 76, 215
    },

    // L * N
    //
    {4, 4,  -20, -24, -28, -36, -57, -26, -55, -71,
            -36, 101, 32, 26, -99, 13, -43, -77, 
	    20, 48, 36, 52, 54, 111, 77, 130,
            165, 160, 128, 233, 113, 200, 140, 233
    },

    // L * O
    //
    {4, 2,   -34, -34, -50, -60, 66, -15, -40, -22,
             58, 18, 122, 44, 207, 150, 226, 129, 
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0},

    // L * P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0},
  },
    {
    // M * I
    //
    {4, 4,  -17, 55, 82, -45, -7, -10, 78, -58,
            9, 14, 46, -54, 13, 27, 26, 0, 
	    218, 302, 221, 197, 163, 222, 191, 108,
            90, 128, 107, 97, 16, 28, 15, 34
    },

    // M * J
    //
    {4, 4,  63, 22, -24, -18, 0, 24, -12, -21,
            0, 0, -13, -24, 0, 0, 0, -3, 
	    51, 46, 10, 27, 0, 42, 18, 15,
            0, 0, 13, 24, 0, 0, 0, 12
    },

    // M * K
    //
    {4, 4,  46, 55, 20, 68, 34, 10, 9, 55,
            -5, 16, 29, 32, 10, 15, 30, 22, 
	    136, 190, 239, 167, 118, 144, 171, 130,
            53, 54, 147, 103, 11, 8, 33, 14
    },

    // M * L
    //
    {4, 4,  -65, -78, 13, 66, -54, -65, 18, 33,
            -38, -60, 15, 56, 8, -1, 9, 31, 
	    295, 177, 91, 57, 209, 140, 66, 61,
            126, 121, 77, 72, 36, 38, 15, 12
    },

    // M * M
    //
    {4, 4,  55, 90, -14, 48, 0, 45, 6, 16,
            0, 0, -5, 16, 0, 0, 0, 15, 
	    48, 200, 104, 254, 0, 108, 60, 174,
            0, 0, 12, 80, 0, 0, 0, 8
    },

    // M * N
    //
    {4, 4,  -57, 95, 7, 35, -45, 69, 1, 17,
            -24, 3, 1, -14, 2, 9, 5, 8, 
	    166, 209, 196, 290, 128, 120, 113, 188,
            39, 72, 60, 73, 9, 15, 14, 19
    },

    // M * O
    //
    {4, 2,  29, -2, 11, -3, -30, 14, 3, 28,
            247, 199, 138, 148, 86, 121, 22, 24, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // M * P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // N * I
    //
    {4, 4,  -34, -38, 54, -92, 2, 32, 108, -88,
            18, 4, 91, -47, -17, -19, 27, -46, 
	    194, 272, 222, 150, 201, 311, 190, 190,
            130, 215, 128, 110, 97, 136, 111, 75
    },

    // N * J
    //
    {4, 4,  6, 12, -26, -24, 3, 30, -22, -24,
            -9, 18, 1, -12, 3, 6, -13, -12, 
	    42, 36, 26, 18, 81, 20, 20, 27,
            57, 24, 31, 9, 21, 18, 13, 9
    },

    // N * K
    //
    {4, 4,  0, -10, -14, 36, 40, 44, 14, 59,
            31, 14, 13, 70, 0, -5, -7, 18, 
	    132, 172, 212, 184, 112, 189, 227, 171,
            101, 147, 120, 113, 66, 86, 106, 92
    },

    // N * L
    //
    {4, 4,  -102, -86, 24, 40, -59, -59, 25, 64,
            -27, 0, 50, 20, -51, -43, 12, 20, 
	    238, 166, 100, 70, 262, 183, 99, 73,
            166, 105, 36, 35, 119, 83, 50, 35
    },

    // N * M
    //
    {4, 4,  4, 8, -28, -18, 0, 37, -25, 24,
            -10, 3, -11, 30, 2, 4, -14, -9, 
	    38, 140, 74, 238, 73, 150, 69, 256,
            51, 124, 58, 192, 19, 70, 37, 119
    },

    // N * N
    //
    {4, 4,  -84, 30, -22, -40, -44, 39, -10, 2,
            -33, 45, 0, -5, -42, 15, -11, -20, 
	    132, 180, 150, 224, 144, 172, 169, 232,
            120, 117, 98, 170, 66, 90, 75, 112
    },

    // N * O
    //
    {4, 2,  -40, -48, -32, -23, 2, -14, -20, -24,
            204, 184, 219, 191, 151, 131, 102, 92, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // N * P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    // O * I (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * J (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * K (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * L (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * M (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * N (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * O (dummy values)
    //
    {4, 4,  0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // O * P
    //
    {4, 4,  -3, -32, -32, -9, 26, 6, -5, 16,
            -1, -32, -32, -4, -14, 13, -11, 45, 
            114, 96, 53, 84, 67, 62, 38, 49,
            98, 111, 58, 103, 72, 106, 56, 89
    },
  },
  {
    // P * I
    //
    {2, 4,  -7, 44, 44, -17, -24, -11, 60, -57,
            128, 192, 106, 130, 157, 220, 184, 133, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    },

    // P * J
    //
    {2, 4,  54, 10, -13, -3, 3, 10, -18, -15,
            78, 20, 13, 9, 21, 40, 14, 24, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // P * K
    //
    {2, 4,  23, 40, 0, 41, 17, -3, 19, 48,
            75, 130, 122, 101, 117, 138, 172, 136, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    },

    // P * L
    //
    {2, 4,  -33, -15, 21, 23, -69, -61, 23, 59,
            166, 81, 41, 11, 212, 153, 77, 48, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // P * M
    //
    {2, 4,  46, 48, -24, 38, 2, 7, -20, -11,
            72, 161, 79, 192, 19, 124, 60, 177, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    },

    // P * N
    //
    {2, 4,  -35, 50, 5, 11, -68, 44, -16, -18,
            107, 148, 132, 191, 114, 149, 125, 198, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    },

    // P * O
    //
    {2, 2,  18, -27, -15, -2, 183, 117, 168, 140,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0},

    // P * P (dummy values)
    //
    {4, 4,   0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0},
  }
};

float64 MMAT_CON_ROW_MAT_RES [MMAT_CON_NUM_MATS][MMAT_CON_ROW_MAT_SIZE * MMAT_TWO] = {

  // A concatByRow A
  //
  {8, 4,    3, 4, 7, 2, 3, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2,
            3, 4, 7, 2, 3, 5, 6, 1, 8, 4, 1, 3, 4, 5, 7, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B concatByRow B
  //
  {8, 4,    5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
            5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C concatByRow C
  //
  {8, 4,    5, 2, 3, 4, 2, 7, 6, 1, 3, 6, 8, 3, 4, 1, 3, 4,
            5, 2, 3, 4, 2, 7, 6, 1, 3, 6, 8, 3, 4, 1, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D concatByRow D
  //
  {8, 4,    5, 0, 0, 0, 2, 2, 0, 0, 3, 6, 3, 0, 4, 6, 3, 4,
            5, 0, 0, 0, 2, 2, 0, 0, 3, 6, 3, 0, 4, 6, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E concatByRow E
  //
  {8, 4,    5, 2, 3, 4, 0, 2, 6, 6, 0, 0, 3, 3, 0, 0, 0, 4,
            5, 2, 3, 4, 0, 2, 6, 6, 0, 0, 3, 3, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F concatByRow F
  //
  {8, 4,   3, 4, 3, 2, 5, 7, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18,
           3, 4, 3, 2, 5, 7, 8, 6, 9, 12, 9, 6, 15, 14, 24, 18,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G concatByRow G
  //
  {8, 2,   4, 5, 7, 2, 3, 9, 2, 3, 4, 5, 7, 2, 3, 9, 2, 3,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H concatByRow H
  //
  {4, 4,   4, 7, 3, 2, 5, 2, 9, 3, 4, 7, 3, 2, 5, 2, 9, 3,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I concatByRow I
  //
  {8, 4,   2, 9, 1, 4, 3, 5, 8, 1, 8, 4, 9, 3, 4, 8, 7, 2,
           2, 9, 1, 4, 3, 5, 8, 1, 8, 4, 9, 3, 4, 8, 7, 2,
           4, 5, 1, 6, 7, 9, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8,
           4, 5, 1, 6, 7, 9, 5, 3, 5, 6, 4, 4, 3, 5, 2, 8
  },

  // J concatByRow J
  //
  {8, 4,    9, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	    9, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3,
            3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3
  },

  // K concatByRow K
  //
  {8, 4,    2, 7, 1, 3, 7, 5, 2, 4, 1, 2, 7, 9, 3, 4, 9, 6,
	    2, 7, 1, 3, 7, 5, 2, 4, 1, 2, 7, 9, 3, 4, 9, 6,
            1, 3, 5, 2, 3, 7, 4, 1, 5, 4, 3, 6, 2, 1, 6, 2,
            1, 3, 5, 2, 3, 7, 4, 1, 5, 4, 3, 6, 2, 1, 6, 2
  },

  // L concatByRow L
  //
  {8, 4,    2, 0, 0, 0, 4, 1, 0, 0, 6, 7, 9, 0, 4, 2, 3, 8,
	    2, 0, 0, 0, 4, 1, 0, 0, 6, 7, 9, 0, 4, 2, 3, 8,
            6, 0, 0, 0, 9, 4, 0, 0, 6, 6, 1, 0, 8, 9, 3, 1,
            6, 0, 0, 0, 9, 4, 0, 0, 6, 6, 1, 0, 8, 9, 3, 1
  },

  // M concatByRow M
  //
  {8, 4,    8, 9, 1, 9, 0, 9, 3, 5, 0, 0, 2, 8, 0, 0, 0, 4,
	    8, 9, 1, 9, 0, 9, 3, 5, 0, 0, 2, 8, 0, 0, 0, 4,
            3, 7, 5, 6, 0, 6, 3, 7, 0, 0, 3, 8, 0, 0, 0, 1,
            3, 7, 5, 6, 0, 6, 3, 7, 0, 0, 3, 8, 0, 0, 0, 1
  },

  // N concatByRow N
  //
  {8, 4,    2, 6, 4, 6, 3, 8, 3, 9, 1, 6, 6, 3, 1, 3, 2, 3,
	    2, 6, 4, 6, 3, 8, 3, 9, 1, 6, 6, 3, 1, 3, 2, 3,
            4, 6, 6, 8, 8, 1, 5, 8, 6, 3, 1, 4, 2, 3, 3, 4,
            4, 6, 6, 8, 8, 1, 5, 8, 6, 3, 1, 4, 2, 3, 3, 4
  },

  // O concatByRow O
  //
  {8, 2,   7, 1, 6, 2, 6, 3, 2, 8, 7, 1, 6, 2, 6, 3, 2, 8,
	   8, 6, 3, 3, 6, 8, 5, 4, 8, 6, 3, 3, 6, 8, 5, 4

  },

  // P concatByRow P
  //
  {4, 4,   8, 4, 2, 3, 1, 6, 2, 8, 8, 4, 2, 3, 1, 6, 2, 8,
           6, 3, 3, 1, 2, 7, 4, 5, 6, 3, 3, 1, 2, 7, 4, 5
  }
};

float64 MMAT_CON_COL_MAT_RES [MMAT_CON_NUM_MATS][MMAT_CON_COL_MAT_SIZE * MMAT_TWO] = {

  // A concatByColumn A
  //
  {4, 8,    3, 4, 7, 2, 3, 4, 7, 2, 3, 5, 6, 1, 3, 5, 6, 1,
            8, 4, 1, 3, 8, 4, 1, 3, 4, 5, 7, 2, 4, 5, 7, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B concatByColumn B
  //
  {4, 8,    5, 0, 0, 0, 5, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0,
            0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C concatByColumn C
  //
  {4, 8,    5, 2, 3, 4, 5, 2, 3, 4, 2, 7, 6, 1, 2, 7, 6, 1,
            3, 6, 8, 3, 3, 6, 8, 3, 4, 1, 3, 4, 4, 1, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D concatByColumn D
  //
  {4, 8,    5, 0, 0, 0, 5, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0,
            3, 6, 3, 0, 3, 6, 3, 0, 4, 6, 3, 4, 4, 6, 3, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E concatByColumn E
  //
  {4, 8,    5, 2, 3, 4, 5, 2, 3, 4, 0, 2, 6, 6, 0, 2, 6, 6,
            0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 4, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F concatByColumn F
  //
  {4, 8,    3, 4, 3, 2, 3, 4, 3, 2, 5, 7, 8, 6, 5, 7, 8, 6,
            9, 12, 9, 6, 9, 12, 9, 6, 15, 14, 24, 18, 15, 14, 24, 18,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G concatByColumn G
  //
  {4, 4,   4, 5, 4, 5, 7, 2, 7, 2, 3, 9, 3, 9, 2, 3, 2, 3,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // H concatByColumn H
  //
  {2, 8,   4, 7, 3, 2, 4, 7, 3, 2, 5, 2, 9, 3, 5, 2, 9, 3,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I concatByColumn I
  //
  {4, 8,    2, 9, 1, 4, 2, 9, 1, 4, 3, 5, 8, 1, 3, 5, 8, 1,
	    8, 4, 9, 3, 8, 4, 9, 3, 4, 8, 7, 2, 4, 8, 7, 2,
	    4, 5, 1, 6, 4, 5, 1, 6, 7, 9, 5, 3, 7, 9, 5, 3,
	    5, 6, 4, 4, 5, 6, 4, 4, 3, 5, 2, 8, 3, 5, 2, 8
  },

  // J concatByColumn J
  //
  {4, 8,    9, 0, 0, 0, 9, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0,
	    0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    3, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0,
	    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 0, 3
  },

  // K concatByColumn K
  //
  {4, 8,    2, 7, 1, 3, 2, 7, 1, 3, 7, 5, 2, 4, 7, 5, 2, 4,
	    1, 2, 7, 9, 1, 2, 7, 9, 3, 4, 9, 6, 3, 4, 9, 6,
	    1, 3, 5, 2, 1, 3, 5, 2, 3, 7, 4, 1, 3, 7, 4, 1,
	    5, 4, 3, 6, 5, 4, 3, 6, 2, 1, 6, 2, 2, 1, 6, 2
  },

  // L concatByColumn L
  //
  {4, 8,    2, 0, 0, 0, 2, 0, 0, 0, 4, 1, 0, 0, 4, 1, 0, 0,
	    6, 7, 9, 0, 6, 7, 9, 0, 4, 2, 3, 8, 4, 2, 3, 8,
	    6, 0, 0, 0, 6, 0, 0, 0, 9, 4, 0, 0, 9, 4, 0, 0,
	    6, 6, 1, 0, 6, 6, 1, 0, 8, 9, 3, 1, 8, 9, 3, 1
  },

  // M concatByColumn M
  //
  {4, 8,    8, 9, 1, 9, 8, 9, 1, 9, 0, 9, 3, 5, 0, 9, 3, 5,
	    0, 0, 2, 8, 0, 0, 2, 8, 0, 0, 0, 4, 0, 0, 0, 4,
	    3, 7, 5, 6, 3, 7, 5, 6, 0, 6, 3, 7, 0, 6, 3, 7,
	    0, 0, 3, 8, 0, 0, 3, 8, 0, 0, 0, 1, 0, 0, 0, 1
  },

  // N concatByColumn N
  //
  {4, 8,    2, 6, 4, 6, 2, 6, 4, 6, 3, 8, 3, 9, 3, 8, 3, 9,
	    1, 6, 6, 3, 1, 6, 6, 3, 1, 3, 2, 3, 1, 3, 2, 3,
	    4, 6, 6, 8, 4, 6, 6, 8, 8, 1, 5, 8, 8, 1, 5, 8,
	    6, 3, 1, 4, 6, 3, 1, 4, 2, 3, 3, 4, 2, 3, 3, 4
  },

  // O concatByColumn O
  //
  {4, 4,   7, 1, 7, 1, 6, 2, 6, 2, 6, 3, 6, 3, 2, 8, 2, 8,
	   8, 6, 8, 6, 3, 3, 3, 3, 6, 8, 6, 8, 5, 4, 5, 4,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P concatByColumn P
  //
  {2, 8,   8, 4, 2, 3, 8, 4, 2, 3, 1, 6, 2, 8, 1, 6, 2, 8,
	   6, 3, 3, 1, 6, 3, 3, 1, 2, 7, 4, 5, 2, 7, 4, 5
  }
};

float64 MMAT_REORDER_ROWS_RES [MMAT_NUM_MATS_TOTAL] [MMAT_MAT_SIZE] = {

  // A.reorderRows(index_vec) : a full 4x4 non-singular matrix
  //
  {4, 4,   4, 5, 7, 2, 8, 4, 1, 3, 3, 5, 6, 1, 3, 4, 7, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.reorderRows(index_vec) : a diagonal 4x4 non-singular matrix
  //
  {4, 4,   0, 0, 0, 4, 0, 0, 3, 0, 0, 2, 0, 0, 5, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.reorderRows(index_vec) : a symmetric 4x4 non-singular matrix
  //
  {4, 4,   4, 1, 3, 4, 3, 6, 8, 3, 2, 7, 6, 1, 5, 2, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.reorderRows(index_vec) : a lower triangular 4x4 non-singular matrix
  //
  {4, 4,   4, 6, 3, 4, 3, 6, 3, 0, 2, 2, 0, 0, 5, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.reorderRows(index_vec) : a upper triangular 4x4 non-singular matrix
  //
  {4, 4,   0, 0, 0, 4, 0, 0, 3, 3, 0, 2, 6, 6, 5, 2, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.reorderRows(index_vec) : a full 4x4 singular matrix
  //
  {4, 4,   15, 14, 24, 18, 9, 12, 9, 6, 5, 7, 8, 6, 3, 4, 3, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.reorderRows(index_vec) : dummy value
  //
  {4, 4,   15, 14, 24, 18, 9, 12, 9, 6, 5, 7, 8, 6, 3, 4, 3, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.reorderRows(index_vec) : dummy value
  //
  {4, 4,   15, 14, 24, 18, 9, 12, 9, 6, 5, 7, 8, 6, 3, 4, 3, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I.reorderRows(index_vec) : a full 4x4 non-singular matrix
  //
  {4, 4,   4, 8, 7, 2, 8, 4, 9, 3, 3, 5, 8, 1, 2, 9, 1, 4,
	   3, 5, 2, 8, 5, 6, 4, 4, 7, 9, 5, 3, 4, 5, 1, 6
  },

  // J.reorderRows(index_vec) : a diagonal 4x4 non-singular matrix
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 1, 0, 0, 4, 0, 0, 9, 0, 0, 0,
	   0, 0, 0, 3, 0, 0, 5, 0, 0, 2, 0, 0, 3, 0, 0, 0
  },

  // K.reorderRows(index_vec) : a symmetric 4x4 non-singular matrix
  //
  {4, 4,   3, 4, 9, 6, 1, 2, 7, 9, 7, 5, 2, 4, 2, 7, 1, 3,
	   2, 1, 6, 2, 5, 4, 3, 6, 3, 7, 4, 1, 1, 3, 5, 2
  },

  // L.reorderRows(index_vec) : a lower triangular 4x4 non-singular matrix
  //
  {4, 4,   4, 2, 3, 8, 6, 7, 9, 0, 4, 1, 0, 0, 2, 0, 0, 0,
	   8, 9, 3, 1, 6, 6, 1, 0, 9, 4, 0, 0, 6, 0, 0, 0
  },

  // M.reorderRows(index_vec) : a upper triangular 4x4 non-singular matrix
  //
  {4, 4,   0, 0, 0, 4, 0, 0, 2, 8, 0, 9, 3, 5, 8, 9, 1, 9,
	   0, 0, 0, 1, 0, 0, 3, 8, 0, 6, 3, 7, 3, 7, 5, 6
  },

  // N.reorderRows(index_vec) : a full 4x4 singular matrix
  //
  {4, 4,   1, 3, 2, 3, 1, 6, 6, 3, 3, 8, 3, 9, 2, 6, 4, 6,
	   2, 3, 3, 4, 6, 3, 1, 4, 8, 1, 5, 8, 4, 6, 6, 8
  },

  // O.reorderRows(index_vec) : dummy value
  //
  {4, 4,   0, 0, 0, 4, 0, 0, 3, 3, 0, 2, 6, 6, 5, 2, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P.reorderRows(index_vec) : dummy value
  //
  {4, 4,   15, 14, 24, 18, 9, 12, 9, 6, 5, 7, 8, 6, 3, 4, 3, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

int32 MMAT_GETMINOR_ARG [MMAT_GTMR_ARG_SIZE] = {

  // [0,0] , [0,1] and [1,1]
  0, 0, 0, 1, 1, 1
};

float64 MMAT_GETMINOR_RES [MMAT_GTMR_NUM_MATS] [MMAT_MAT_SIZE] = {

  // A.getMinor(row, col)
  //
  {3, 3,   5, 6, 1, 4, 1, 3, 5, 7, 2, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // A.getMinor(row, col)
  //
  {3, 3,   3, 6, 1, 8, 1, 3, 4, 7, 2, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // A.getMinor(row, col)
  //
  {3, 3,   3, 7, 2, 8, 1, 3, 4, 7, 2, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.getMinor(row, col)
  //
  {3, 3,   2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.getMinor(row, col)
  //
  {3, 3,   0, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.getMinor(row, col)
  //
  {3, 3,   5, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.getMinor(row, col)
  //
  {3, 3,   7, 6, 1, 6, 8, 3, 1, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.getMinor(row, col)
  //
  {3, 3,   2, 6, 1, 3, 8, 3, 4, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.getMinor(row, col)
  //
  {3, 3,   5, 3, 4, 3, 8, 3, 4, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.getMinor(row, col)
  //
  {3, 3,   2, 0, 0, 6, 3, 0, 6, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.getMinor(row, col)
  //
  {3, 3,   2, 0, 0, 3, 3, 0, 4, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.getMinor(row, col)
  //
  {3, 3,   5, 0, 0, 3, 3, 0, 4, 3, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.getMinor(row, col)
  //
  {3, 3,   2, 6, 6, 0, 3, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.getMinor(row, col)
  //
  {3, 3,   0, 6, 6, 0, 3, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.getMinor(row, col)
  //
  {3, 3,   5, 3, 4, 0, 3, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.getMinor(row, col)
  //
  {3, 3,   7, 8, 6, 12, 9, 6, 14, 24, 18, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.getMinor(row, col)
  //
  {3, 3,   5, 8, 6, 9, 9, 6, 15, 24, 18, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.getMinor(row, col)
  //
  {3, 3,   3, 3, 2, 9, 9, 6, 15, 24, 18, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.getMinor(row, col)
  //
  {3, 1,   2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.getMinor(row, col)
  //
  {3, 1,   7, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.getMinor(row, col)
  //
  {3, 1,   4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.getMinor(row, col)
  //
  {1, 3,   2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.getMinor(row, col)
  //
  {1, 3,   5, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.getMinor(row, col)
  //
  {1, 3,   4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I.getMinor(row, col)
  //
  {3, 3,   5, 8, 1, 4, 9, 3, 8, 7, 2, 9, 5, 3, 6, 4, 4, 5,
           2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I.getMinor(row, col)
  //
  {3, 3,   3, 8, 1, 8, 9, 3, 4, 7, 2, 7, 5, 3, 5, 4, 4, 3,
	   2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // I.getMinor(row, col)
  //
  {3, 3,   2, 1, 4, 8, 9, 3, 4, 7, 2, 4, 1, 6, 5, 4, 4, 3,
	   2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // J.getMinor(row, col)
  //
  {3, 3,   4, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0,
	   0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // J.getMinor(row, col)
  //
  {3, 3,   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0,
	   0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // J.getMinor(row, col)
  //
  {3, 3,   9, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 5, 0, 0,
	   0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // K.getMinor(row, col)
  //
  {3, 3,   5, 2, 4, 2, 7, 9, 4, 9, 6, 7, 4, 1, 4, 3, 6, 1,
	   6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // K.getMinor(row, col)
  //
  {3, 3,   7, 2, 4, 1, 7, 9, 3, 9, 6, 3, 4, 1, 5, 3, 6, 2,
	   6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // K.getMinor(row, col)
  //
  {3, 3,   2, 1, 3, 1, 7, 9, 3, 9, 6, 1, 5, 2, 5, 3, 6, 2,
	   6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // L.getMinor(row, col)
  //
  {3, 3,   1, 0, 0, 7, 9, 0, 2, 3, 8, 4, 0, 0, 6, 1, 0, 9,
           3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // L.getMinor(row, col)
  //
  {3, 3,   4, 0, 0, 6, 9, 0, 4, 3, 8, 9, 0, 0, 6, 1, 0, 8,
	   3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // L.getMinor(row, col)
  //
  {3, 3,   2, 0, 0, 6, 9, 0, 4, 3, 8, 6, 0, 0, 6, 1, 0, 8,
	   3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // M.getMinor(row, col)
  //
  {3, 3,   9, 3, 5, 0, 2, 8, 0, 0, 4, 6, 3, 7, 0, 3, 8, 0,
           0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // M.getMinor(row, col)
  //
  {3, 3,   0, 3, 5, 0, 2, 8, 0, 0, 4, 0, 3, 7, 0, 3, 8, 0,
	   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // M.getMinor(row, col)
  //
  {3, 3,   8, 1, 9, 0, 2, 8, 0, 0, 4, 3, 5, 6, 0, 3, 8, 0,
	   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // N.getMinor(row, col)
  //
  {3, 3,   8, 3, 9, 6, 6, 3, 3, 2, 3, 1, 5, 8, 3, 1, 4, 3,
           3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // N.getMinor(row, col)
  //
  {3, 3,   3, 3, 9, 1, 6, 3, 1, 2, 3, 8, 5, 8, 6, 1, 4, 2,
	   3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // N.getMinor(row, col)
  //
  {3, 3,   2, 4, 6, 1, 6, 3, 1, 2, 3, 4, 6, 8, 6, 1, 4, 2,
	   3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


  // O.getMinor(row, col)
  //
  {3, 1,   2,
           3,
	   8,

           3,
           8,
	   4,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // O.getMinor(row, col)
  //
  {3, 1,   6,
           6,
	   2,

           3,
           6,
	   5,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // O.getMinor(row, col)
  //
  {3, 1,   7,
           6,
	   2,

           8,
           6,
	   5,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P.getMinor(row, col)
  //
  {1, 3,   6, 2, 8,

	   7, 4, 5,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P.getMinor(row, col)
  //
  {1, 3,   1, 2, 8,

	   2, 4, 5,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  // P.getMinor(row, col)
  //
  {1, 3,   8, 2, 3,

           6, 3, 1,

	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int32 MMAT_SWAPROWS_ARG [MMAT_SWRW_ARG_SIZE] = {

  // [0,1] , [1,0]
  0, 1, 1, 0,
};

float64 MMAT_SWAPROWS_RES [MMAT_SWRW_NUM_MATS] [MMAT_MAT_SIZE] = {

  // A
  //
  {4, 4,   3, 5, 6, 1, 3, 4, 7, 2, 8, 4, 1, 3, 4, 5, 7, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B
  //
  {4, 4,   0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C
  //
  {4, 4,   2, 7, 6, 1, 5, 2, 3, 4, 3, 6, 8, 3, 4, 1, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D
  //
  {4, 4,   2, 2, 0, 0, 5, 0, 0, 0, 3, 6, 3, 0, 4, 6, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E
  //
  {4, 4,   0, 2, 6, 6, 5, 2, 3, 4, 0, 0, 3, 3, 0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F
  //
  {4, 4,   5, 7, 8, 6, 3, 4, 3, 2, 9, 12, 9, 6, 15, 14, 24, 18,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G
  //
  {4, 2,   7, 2, 4, 5, 3, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H
  //
  {2, 4,   5, 2, 9, 3, 4, 7, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I
  //
  {4, 4,   3, 5, 8, 1, 2, 9, 1, 4, 8, 4, 9, 3, 4, 8, 7, 2,
	   7, 9, 5, 3, 4, 5, 1, 6, 5, 6, 4, 4, 3, 5, 2, 8
  },

  // J
  //
  {4, 4,   0, 4, 0, 0, 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	   0, 2, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3
  },

  // K
  //
  {4, 4,   7, 5, 2, 4, 2, 7, 1, 3, 1, 2, 7, 9, 3, 4, 9, 6,
	   3, 7, 4, 1, 1, 3, 5, 2, 5, 4, 3, 6, 2, 1, 6, 2
  },

  // L
  //
  {4, 4,   4, 1, 0, 0, 2, 0, 0, 0, 6, 7, 9, 0, 4, 2, 3, 8,
	   9, 4, 0, 0, 6, 0, 0, 0, 6, 6, 1, 0, 8, 9, 3, 1
  },

  // M
  //
  {4, 4,   0, 9, 3, 5, 8, 9, 1, 9, 0, 0, 2, 8, 0, 0, 0, 4,
	   0, 6, 3, 7, 3, 7, 5, 6, 0, 0, 3, 8, 0, 0, 0, 1
  },

  // N
  //
  {4, 4,   3, 8, 3, 9, 2, 6, 4, 6, 1, 6, 6, 3, 1, 3, 2, 3,
	   8, 1, 5, 8, 4, 6, 6, 8, 6, 3, 1, 4, 2, 3, 3, 4
  },

  // O
  //
  {4, 2,   6, 2, 7, 1, 6, 3, 2, 8, 3, 3, 8, 6, 6, 8, 5, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P
  //
  {2, 4,   1, 6, 2, 8, 8, 4, 2, 3, 2, 7, 4, 5, 6, 3, 3, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

int32 MMAT_SWAPCOLUMNS_ARG [MMAT_SWCL_ARG_SIZE] = {

  // [0,1] , [1,0]
  0, 1, 1, 0,
};

float64 MMAT_SWAPCOLUMNS_RES [MMAT_SWCL_NUM_MATS] [MMAT_MAT_SIZE] = {

  // A
  //
  {4, 4,   4, 3, 7, 2, 5, 3, 6, 1, 4, 8, 1, 3, 5, 4, 7, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B
  //
  {4, 4,   0, 5, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C
  //
  {4, 4,   2, 5, 3, 4, 7, 2, 6, 1, 6, 3, 8, 3, 1, 4, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D
  //
  {4, 4,   0, 5, 0, 0, 2, 2, 0, 0, 6, 3, 3, 0, 6, 4, 3, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E
  //
  {4, 4,   2, 5, 3, 4, 2, 0, 6, 6, 0, 0, 3, 3, 0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F
  //
  {4, 4,   4, 3, 3, 2, 7, 5, 8, 6, 12, 9, 9, 6, 14, 15, 24, 18,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G
  //
  {4, 2,   5, 4, 2, 7, 9, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H
  //
  {2, 4,   7, 4, 3, 2, 2, 5, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I
  //
  {4, 4,   9, 2, 1, 4, 5, 3, 8, 1, 4, 8, 9, 3, 8, 4, 7, 2,
	   5, 4, 1, 6, 9, 7, 5, 3, 6, 5, 4, 4, 5, 3, 2, 8
  },

  // J
  //
  {4, 4,   0, 9, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
           0, 3, 0, 0, 2, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3
  },

  // K
  //
  {4, 4,   7, 2, 1, 3, 5, 7, 2, 4, 2, 1, 7, 9, 4, 3, 9, 6,
	   3, 1, 5, 2, 7, 3, 4, 1, 4, 5, 3, 6, 1, 2, 6, 2
  },

  // L
  //
  {4, 4,   0, 2, 0, 0, 1, 4, 0, 0, 7, 6, 9, 0, 2, 4, 3, 8,
           0, 6, 0, 0, 4, 9, 0, 0, 6, 6, 1, 0, 9, 8, 3, 1
  },

  // M
  //
  {4, 4,   9, 8, 1, 9, 9, 0, 3, 5, 0, 0, 2, 8, 0, 0, 0, 4,
           7, 3, 5, 6, 6, 0, 3, 7, 0, 0, 3, 8, 0, 0, 0, 1
  },

  // N
  //
  {4, 4,   6, 2, 4, 6, 8, 3, 3, 9, 6, 1, 6, 3, 3, 1, 2, 3,
           6, 4, 6, 8, 1, 8, 5, 8, 3, 6, 1, 4, 3, 2, 3, 4
  },

  // O
  //
  {4, 2,   1, 7, 2, 6, 3, 6, 8, 2, 6, 8, 3, 3, 8, 6, 4, 5,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P
  //
  {2, 4,   4, 8, 2, 3, 6, 1, 2, 8, 3, 6, 3, 1, 7, 2, 4, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

unichar MMAT_ASSIGN_STRING_INPUT [MMAT_NUM_TYPES][MAX_STRING_LENGTH] = {

  // a string containing required data for full matrix A
  //
  L"5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4",

  // a string containing required data for diagonal matrix B
  //
  L"5, 2, 3, 4",

  // a string containing required data for symmetric matrix C
  //
  L"5, 0, 2, 0, 0, 3, 0, 0, 0, 4",

  // a string containing required data for lower triangle matrix D
  //
  L"5, 0, 2, 0, 0, 3, 0, 0, 0, 4",

  // a string containing required data for upper triangle matrix E
  //
  L"5, 0, 0, 0, 2, 0, 0, 3, 0, 4",

  // a string containing required data for sparse matrix B
  //
  L"5, 0, 0, 0,  0, 2, 0, 0,  0, 0, 3, 0,  0, 0, 0, 4"

};

float64 MMAT_DECOMPLU1_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.375, 1, 0, 0,
           0.375, 0.714285714286, 1, 0,
           0.5, 0.85714285714286, 0.643835616438, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.4, 1, 0, 0,
           0.6, 0.774193548, 1, 0,
           0.8, -0.0967741935, 0.428571429, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // D.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.6, 1, 0, 0,
           0.4, 0.3333333333, 1, 0,
           0.8, 1, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // E.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // F.lu(5)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.lu(5) (dummy)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // H.lu(5) (dummy)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.375, 1, 0, 0,
           0.375, 0.714285714286, 1, 0,
           0.5, 0.85714285714286, 0.643835616438, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // J.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // K.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.4, 1, 0, 0,
           0.6, 0.774193548, 1, 0,
           0.8, -0.0967741935, 0.428571429, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // L.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0.6, 1, 0, 0,
           0.4, 0.3333333333, 1, 0,
           0.8, 1, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // M.lu(5)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // N.assign(5)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // O.lu(5) (dummy)
  //
  {4, 4,   1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // P.lu(5) (dummy)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

float64 MMAT_DECOMPLU2_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.lu(5)
  //
  {4, 4,   8, 4, 1, 3,
           0, 3.5, 5.625, -0.125,
           0, 0, 2.607142857, 0.964285714,
           0, 0, 0, -0.0136986301,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // B.lu(5)
  //
  {4, 4,   5, 0, 0, 0,
           0, 2, 0, 0,
           0, 0, 3, 0,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // C.lu(5)
  //
  {4, 4,   5, 2, 3, 4,
           0, 6.2, 4.8, -0.6,
           0, 0, 2.48387097, 1.064516129,
           0, 0, 0, 0.2857142857,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // D.lu(5)
  //
  {4, 4,   5, 0, 0, 0,
           0, 6, 3, 0,
           0, 0, -1, 0,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.lu(5)
  //
  {4, 4,   5, 2, 3, 4,
           0, 2, 6, 6,
           0, 0, 3, 3,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.assign(5)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.lu(5) (dummy)
  //
  {4, 4,   5, 2, 3, 4,
           0, 2, 6, 6,
           0, 0, 3, 3,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.assign(5) (dummy)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // I.lu(5)
  //
  {4, 4,   8, 4, 1, 3,
           0, 3.5, 5.625, -0.125,
           0, 0, 2.607142857, 0.964285714,
           0, 0, 0, -0.0136986301,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // J.lu(5)
  //
  {4, 4,   5, 0, 0, 0,
           0, 2, 0, 0,
           0, 0, 3, 0,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // K.lu(5)
  //
  {4, 4,   5, 2, 3, 4,
           0, 6.2, 4.8, -0.6,
           0, 0, 2.48387097, 1.064516129,
           0, 0, 0, 0.2857142857,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  },

  // L.lu(5)
  //
  {4, 4,   5, 0, 0, 0,
           0, 6, 3, 0,
           0, 0, -1, 0,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // M.lu(5)
  //
  {4, 4,   5, 2, 3, 4,
           0, 2, 6, 6,
           0, 0, 3, 3,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // N.assign(5)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  
  // O.lu(5) (dummy)
  //
  {4, 4,   5, 2, 3, 4,
           0, 2, 6, 6,
           0, 0, 3, 3,
           0, 0, 0, 4,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P.assign(5) (dummy)
  //
  {4, 4,   0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

float64 MMAT_DECOMPCL1_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0, 1.414213562, 0, 0,
           0, 0, 1.732050808, 0, 0, 0, 0, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0.894427191, 2.48997992, 0, 0,
   1.341640786, 1.927726389, 1.576030129, 0,
   1.788854382, -0.240965799, 0.675441484, 0.534522484,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  
  // I.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // J.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0, 1.414213562, 0, 0,
           0, 0, 1.732050808, 0, 0, 0, 0, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // K.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0.894427191, 2.48997992, 0, 0,
   1.341640786, 1.927726389, 1.576030129, 0,
   1.788854382, -0.240965799, 0.675441484, 0.534522484,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // L.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // M.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // N.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // O.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};

float64 MMAT_DECOMPCL2_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0, 1.414213562, 0, 0,
           0, 0, 1.732050808, 0, 0, 0, 0, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.assign(5)
  //
  {4, 4,   2.236067977, 0.894427191, 1.341640786, 1.788854382,
           0, 2.48997992, 1.927726389, -0.240965799,
           0, 0, 1.576030129, 0.675441484, 0, 0, 0, 0.534522484,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // D.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // E.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // F.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // G.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // H.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  // I.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // J.assign(5)
  //
  {4, 4,   2.236067977, 0, 0, 0, 0, 1.414213562, 0, 0,
           0, 0, 1.732050808, 0, 0, 0, 0, 2,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // K.assign(5)
  //
  {4, 4,   2.236067977, 0.894427191, 1.341640786, 1.788854382,
           0, 2.48997992, 1.927726389, -0.240965799,
           0, 0, 1.576030129, 0.675441484, 0, 0, 0, 0.534522484,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // L.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // M.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // N.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // O.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // P.assign(5)
  //
  {4, 4,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
};

float64 MMAT_EIGENVEC_RES[MMAT_NUM_MATS_TOTAL][MMAT_MAT_SIZE] = {

  // A.assign(5)
  //
  {4, 4,   -0.492560679, -0.455534842, -0.495260363, -0.551895967,
           -0.421246797, 0.833241501, -0.357556903, 0.020317441,
           -0.460364328, 0.446940688, -0.26318929, 0.72044438,
           -0.42741676, -0.293962114, 0.798612337, -0.305154919,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // B.assign(5)
  //
  {4, 4,    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // C.assign(5)
  //
  {4, 4,  0.391254558, 0.547608473, 0.66014174, 0.333553164,
          0.591970491, -0.517144842, -0.214753568, 0.579666331,
          0.474765253, 0.564270061, -0.639193460, -0.218240630,
          -0.520661850, 0.338061342, -0.330946382, 0.710704059,
  },

  // D.assign(5)
  //
  {4, 4,  -0.05300403, -0.03533602, -0.185514105, -0.980574554,
          -7.367712109e-16, -6.72295502e-16,  -5.661673929e-15, 1,
          4.3611151861e-15, 1.613648845e-17, 0.316227766, -0.948683298,
          4.390235911e-16, -0.1170411472, 0.702246883, -0.702246883
  },

  // E.assign(5)
  //
  {4, 4,  1, 0, 0, 0,
          -0.9481, 0.3075, 0.0769, 0.0256,
          -0.7767, 0.6213, 0.1036, 0,
          -0.5547, 0.8321, 0, 0
   },

  // F.assign(5)
  //
  {4, 4,   -0.125449518, -0.308399912, -0.376348554, -0.864588734,
           -0.121844456, 0.050191082, -0.556821673, 0.820112437,
           -0.04066354, -0.003498374, 0.608033228, -0.792861799,
            0.163846384, -3.102625098e-14, -0.655385536, 0.737308728
  },

  // G.assign(5)
  //
  {4, 4,  1, 0, 0, 0,
          -0.9481, 0.3075, 0.0769, 0.0256,
          -0.7767, 0.6213, 0.1036, 0,
          -0.5547, 0.8321, 0, 0
   },

  // H.assign(5)
  //
  {4, 4,   -0.125449518, -0.308399912, -0.376348554, -0.864588734,
           -0.121844456, 0.050191082, -0.556821673, 0.820112437,
           -0.04066354, -0.003498374, 0.608033228, -0.792861799,
            0.163846384, -3.102625098e-14, -0.655385536, 0.737308728
  },
  
  // I.assign(5)
  //
  {4, 4,   -0.492560679, -0.455534842, -0.495260363, -0.551895967,
           -0.421246797, 0.833241501, -0.357556903, 0.020317441,
           -0.460364328, 0.446940688, -0.26318929, 0.72044438,
           -0.42741676, -0.293962114, 0.798612337, -0.305154919,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // J.assign(5)
  //
  {4, 4,    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },

  // K.assign(5)
  //
  {4, 4,  0.391254558, 0.547608473, 0.66014174, 0.333553164,
          0.591970491, -0.517144842, -0.214753568, 0.579666331,
          0.474765253, 0.564270061, -0.639193460, -0.218240630,
          -0.520661850, 0.338061342, -0.330946382, 0.710704059,
  },

  // L.assign(5)
  //
  {4, 4,  -0.05300403, -0.03533602, -0.185514105, -0.980574554,
          -7.367712109e-16, -6.72295502e-16,  -5.661673929e-15, 1,
          4.3611151861e-15, 1.613648845e-17, 0.316227766, -0.948683298,
          4.390235911e-16, -0.1170411472, 0.702246883, -0.702246883
  },

  // M.assign(5)
  //
  {4, 4,  1, 0, 0, 0,
          -0.9481, 0.3075, 0.0769, 0.0256,
          -0.7767, 0.6213, 0.1036, 0,
          -0.5547, 0.8321, 0, 0
   },

  // N.assign(5)
  //
  {4, 4,   -0.125449518, -0.308399912, -0.376348554, -0.864588734,
           -0.121844456, 0.050191082, -0.556821673, 0.820112437,
           -0.04066354, -0.003498374, 0.608033228, -0.792861799,
            0.163846384, -3.102625098e-14, -0.655385536, 0.737308728
  },

  // O.assign(5)
  //
  {4, 4,  1, 0, 0, 0,
          -0.9481, 0.3075, 0.0769, 0.0256,
          -0.7767, 0.6213, 0.1036, 0,
          -0.5547, 0.8321, 0, 0
   },

  // P.assign(5)
  //
  {4, 4,   -0.125449518, -0.308399912, -0.376348554, -0.864588734,
           -0.121844456, 0.050191082, -0.556821673, 0.820112437,
           -0.04066354, -0.003498374, 0.608033228, -0.792861799,
            0.163846384, -3.102625098e-14, -0.655385536, 0.737308728
  }
};

float64 MMAT_EIGENVAL_RES [MMAT_NUM_MATS_TOTAL] [MMAT_NUM_ROWS * MMAT_TWO + 1] = {
  // A
  //
  {4,    15.978611783, 0.933034581, -0.011368174, -5.90027819,
         0, 0, 0, 0},

  // B
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // C
  //
  {4,    16.271063123, 6.081329127, 1.499316728, 0.148291021,
         0, 0, 0, 0},

  // D
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // E
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // F
  //
  {4,    35.617285795, 0.691357102, 0.691357102, 2.293838570e-15,
         0, 0, 0, 0
  },

  // G
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // H
  //
  {4,    35.617285795, 0.691357102, 0.691357102, 2.293838570e-15,
         0, 0, 0, 0
  },

  // I
  //
  {4,    15.978611783, 0.933034581, -0.011368174, -5.90027819,
         0, 0, 0, 0},

  // J
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // K
  //
  {4,    16.271063123, 6.081329127, 1.499316728, 0.148291021,
         0, 0, 0, 0},

  // L
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // M
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // N
  //
  {4,    35.617285795, 0.691357102, 0.691357102, 2.293838570e-15,
         0, 0, 0, 0
  },

  // O
  //
  {4,    5, 4, 3, 2,
         0, 0, 0, 0},

  // P
  //
  {4,    35.617285795, 0.691357102, 0.691357102, 2.293838570e-15,
         0, 0, 0, 0
  }
};

float64 MMAT_MAKEDIAG_VEC [MMAT_NUM_ROWS * MMAT_TWO] = {

  // input vector for makeDiag
  //
  5, 2, 4, 3, 8, 9, 5, 8
};

float64 MMAT_MAKEDIAG_RES0 [MMAT_MAT_SIZE] = {

  // a full 4x4 diagonal matrix
  //
  4, 4,    5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 3,
           8, 0, 0, 0, 0, 9, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8
};

float64 MMAT_MAKEDIAG_SCAL = 5;

float64 MMAT_MAKEDIAG_RES1 [MMAT_MAT_SIZE] = {

  // a full 4x4 diagonal matrix
  //
  4, 4,    5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

float64 MMAT_QUADRATIC_VEC_REAL [MMAT_NUM_ROWS] = {

  // real input vector for quadratic test
  //
  5, 2, 4, 3
};

float64 MMAT_QUADRATIC_VEC_COMPLEX [MMAT_NUM_ROWS * MMAT_TWO] = {

  // comlpex input vector for quadratic test
  //
  2, 5, 6, 1,
  2, 4, 3, 3
};

float64 MMAT_QUADRATIC_RES_REAL [MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // result for quadratic() A, B, C, D, E, F, G, H
  //
  825, 217, 777, 477, 477, 1634, false, false,

  // result for quadratic() I, J, K, L, M, N, O, P
  //
  922, 257, 802, 594, 699, 704, false, false,

  // imaginary components for quadratic() A, B, C, D, E, F, G, H
  //
  0, 0, 0, 0, 0, 0, false, false,

  // imaginary components for quadratic() I, J, K, L, M, N, O, P
  //
  855, 190, 659, 659, 578, 900, false, false

};

float64 MMAT_QUADRATIC_RES_COMPLEX [MMAT_NUM_MATS_TOTAL * MMAT_TWO] = {

  // result for quadratic() A, B, C, D, E, F, G, H
  //
  1410, 297, 1599, 818, 818, 3040, false, false,

  // result for quadratic() I, J, K, L, M, N, O, P
  //
  1952, 281, 1506, 1059, 1296, 1689, false, false,

  // imaginary components for quadratic() A, B, C, D, E, F, G, H
  //
  126, 0, 0, 51, -51, 336, false, false,

  // imaginary components for quadratic() I, J, K, L, M, N, O, P
  //
  1888, 361, 1320, 1027, 884, 1230, false, false

};

int32 MMAT_RANK_TEST[MMAT_NUM_MATS_TOTAL] = {
  
  // input data for rank test
  //
  4, 4, 4, 4, 4, 3, 2, 2, 2
  
};




