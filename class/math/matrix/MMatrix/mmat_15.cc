// file: $isip_ifc/class/math/matrix/MMatrix/mmat_15.cc
// version: $Id: mmat_15.cc 10477 2006-03-13 20:53:26Z srinivas $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: decompositionLU
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MMatrix<TScalar, TIntegral>& l: (output) lower triangle matrix
//  MMatrix<TScalar, TIntegral>& u: (output) upper triangle matrix
//  MVector<Long, int32>& index: (output) index of pivoting
//  int32& sign: (output) indicate the number of row interchanges even or odd
//  float64 stabilize: (input) a stabilization factor
//
// return: a boolean value indicating status
//
// this method constructs the LU decomposition of the input matrix. the
// algorithm used is the right-looking algorithm:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 46-47, 1995.
//
// the algorithm used in the above reference uses "implicit pivoting".
// we slightly modified the algorithm to use "partial pivoting". in
// implicit pivoting, elements of the matrix are scaled by the largest
// element of that row before comparisons are made for pivoting, which is
// computationally less efficient. in partial pivoting, comparisons
// are made on elements without any scaling, which is simpler and
// computationally efficient.
//
template <class TScalar, class TIntegral>
bool8
MMatrixMethods::decompositionLU(const MMatrix<TScalar, TIntegral>& this_a,
				MMatrix<TScalar, TIntegral>& l_a,
				MMatrix<TScalar, TIntegral>& u_a,
				MVector<Long, int32>& index_a,
				int32& sign_a,
				float64 stabilize_a) {

  // this method is defined only for float32 and float64 matrices only
  //
#ifdef ISIP_TEMPLATE_fp
    
  // check arguments: matrices must be square
  //
  if (!this_a.isSquare()) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"decompositionLU()", Error::ARG,
			 __FILE__, __LINE__);
  }

  // initialize sign
  //
  sign_a = 1;
  
  // initialize pivoting index
  //
  index_a.setLength(this_a.getNumRows());
  index_a.ramp(0, 1);
  
  // type: DIAGONAL
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // the lower triangular matrix is an identity matrix
    //
    l_a.makeIdentity(this_a.getNumRows(), Integral::LOWER_TRIANGULAR);

    // the upper triangular matrix is the same as the current matrix
    //
    u_a.assign(this_a, Integral::UPPER_TRIANGULAR);
  }

  // type: UPPER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // the lower triangular matrix is identity matrix
    //    
    l_a.makeIdentity(this_a.getNumRows(), Integral::LOWER_TRIANGULAR);

    // upper triangular matrix is the same as the current matrix
    //    
    u_a.assign(this_a);
  }

  // type: FULL, SYMMETRIC, LOWER_TRIANGULAR, SPARSE
  //
  else {

    // get the number of rows of the matrix
    //
    int32 nrows = this_a.getNumRows();

    // make a copy of the current matrix
    //
    MMatrix<TScalar, TIntegral> a;
    a.assign(this_a, Integral::FULL);

    // process each row in the decomposition
    //
    for (int32 j = 0; j < nrows; j++) {

      // declare local variables
      //
      float64 max = 0;
      int32 imax = j;

      // calculate the elements in the upper triangular matrix
      // iterating over columns. these elements either have the same row
      // indices but smaller column indices, or the same column indices but
      // smaller row indices:
      //
      //    u(i, j) = a(i, j) - sum[l(i, k) * u(k, j)],
      //   				     for (k=1,...,k-1) when i <= j
      //
      for (int32 i = 0; i < j; i++) {
	float64 sum = a(i, j);
	for (int32 k = 0; k < i; k++) {
	  sum -= a(i, k) * a(k, j);
	}
	a.setValue(i, j, sum);
      }

      // calculate the elements in the lower triangular matrix
      // iterating over columns. these elements either have same row indices
      // but smaller column indices, or the same column indices but smaller
      // row indices:
      //
      //    l(i, j) = a(i, j) - sum[l(i, k) * u(k, j)] / u(j, j),
      //					for (k=1,...,k-1) when i > j
      //
      for (int32 i = j; i < nrows; i++) {

	// accumulate the sum
	//
	float64 sum = a(i, j);
	for (int32 k = 0; k < j; k++) {
	  sum -= a(i, k) * a(k, j);
	}
	a.setValue(i, j, sum);

	// find the biggest number in column j and record the row index -
	// this is required for pivoting.
	//
	float64 value = Integral::abs(sum);
	if (value > max) {
	  max = value;
	  imax = i;
	}
      }

      // pivoting: check whether we need to interchange rows. we swap rows
      // if the diagonal element for a particular column is not the maximum
      // magnitude element. record the index of the pivot in the output array.
      //
      if (j != imax) {
	a.swapRows(imax, j);
	int32 k = index_a(j);
	index_a(j) = index_a(imax);
	index_a(imax) = k;
	sign_a = -sign_a;
      }

      // divide by the pivot element: the pivot element will not be zero
      // because the matrix is not singular. or it should be substituted
      // with stabilization factor
      //
      max = a(j, j);
      if ((max == 0) && (stabilize_a != 0)) {
	max = stabilize_a;
	a.setValue(j, j, (TIntegral)stabilize_a);
      }

      if (max != 0) {
	if (j != (nrows - 1)) {
	  TIntegral dum = 1.0 / a(j, j);
	  for (int32 i = j + 1; i < nrows; i++) {
	    a.setValue(i, j, a(i, j) * dum);
	  }
	}
      }
    }

    // copy the lower triangular part of the result matrix into l_a and
    // set the diagonal elements of l_a matrix to (TIntegral)1
    //
    l_a.setDimensions(nrows, nrows, false, Integral::LOWER_TRIANGULAR);
    l_a.setLower(a);
    l_a.setDiagonal((TIntegral)1);

    // get the upper triangle part of result matrix and assign to u_a
    //
    u_a.setDimensions(nrows, nrows, false, Integral::UPPER_TRIANGULAR);
    u_a.setUpper(a);
  }

  // exit gracefully
  //
  return true;

  // for matrices other than float32 and float64, return error
  //
#else
  return Error::handle(name(), L"decompositionLU", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif
}

// explicit instantiations
//
template bool8
MMatrixMethods::decompositionLU(const MMatrix<ISIP_TEMPLATE_TARGET>&,
				MMatrix<ISIP_TEMPLATE_TARGET>&,
			        MMatrix<ISIP_TEMPLATE_TARGET>&,
				MVector<Long, int32>&, int32&,
				float64);

// method: decompositionCholesky
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MMatrix<TScalar, TIntegral>& l: (output) lower triangular matrix
//
// return: a bool8 value indicating status
//
// this method constructs the Cholesky decomposition of an input matrix:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 96-97, 1995.
//
// upon output, l' * l = this
// note that this method only operates on symmetric matrices.
//
template <class TScalar, class TIntegral>
bool8
MMatrixMethods::decompositionCholesky(const
				      MMatrix<TScalar, TIntegral>& this_a,
				      MMatrix<TScalar, TIntegral>& l_a) {

  // this method is defined only for float32 and float64 matrices only
  //
#ifdef ISIP_TEMPLATE_fp
      
  // condition: non-symmetric
  //
  if (!this_a.isSymmetric()) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"decompositionCholesky()", Error::ARG,
			 __FILE__, __LINE__);
  }

  // type: DIAGONAL
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // the diagonal elements should be positive or zero
    //
    if ((float64)this_a.m_d.min() < 0) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"decompositionCholesky()", Error::ARG,
			   __FILE__, __LINE__, Error::WARNING);
    }

    // assign the input matrix to lower triangular matrix
    //
    l_a.assign(this_a);
    l_a.m_d.sqrt();
    l_a.changeType(Integral::LOWER_TRIANGULAR);
  }

  // type: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE
  //
  else {

    // get number of rows of current matrix
    //
    int32 nrows = this_a.getNumRows();

    // make a copy of the current matrix
    //
    MMatrix<TScalar, TIntegral> a;
    a.assign(this_a, Integral::FULL);

    // loop over all rows
    //
    for (int32 i = 0; i < nrows; i++) {

      // constructs a lower triangular matrix directly iterating over columns.
      // remember an upper triangular matrix is the transpose matrix of a
      // lower triangular matrix in our storage format.
      //
      for (int32 j = i; j < nrows; j++) {

	// accumulate the sum
	//
	float64 sum = a(i, j);
	for (int32 k = i - 1; k >= 0; k--) {
	  sum -= a(i, k) * a(j, k);
	}

	// handle diagonal elements separately
	//      
	if (i == j) {

	  // if the sum is not greater than zero, the matrix is
	  // not positive definite
	  //
	  if (sum <= 0.0) {
	    this_a.debug(L"this_a");	    
	    return Error::handle(name(), L"decompositionCholesky()", 
				 MMatrix<TScalar, TIntegral>::ERR_POSDEF,
				 __FILE__, __LINE__, Error::WARNING);
	  }

	  // assign the value
	  //
	  a.setValue(i, i, Integral::sqrt(sum));
	}

	// other elements are handled with the normal calculation
	//      
	else {
	  a.setValue(j, i, sum / a(i, i));
	}
      }
    }
    
    // copy the lower triangular part of the result matrix into l_a and
    // set the diagonal elements of l_a matrix to (TIntegral)1
    //
    l_a.setDimensions(nrows, nrows, false, Integral::LOWER_TRIANGULAR);
    l_a.setLower(a);
  }

  return true;

#else
  return Error::handle(name(), L"decompositionCholesky",
		       Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif
}

// explicit instantiations
//
template bool8
MMatrixMethods::decompositionCholesky(const MMatrix<ISIP_TEMPLATE_TARGET>&,
				      MMatrix<ISIP_TEMPLATE_TARGET>&);


// method: decompositionSVD
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MMatrix<TScalar, TIntegral>& u: (output) row orthonormal
//  MMatrix<TScalar, TIntegral>& w: (output) singular value matrix
//  MMatrix<TScalar, TIntegral>& v: (output) column orthonormal
//  bool8 economy_mode: (input) true for economy and false for int32 format
//
// return: a bool8 value indicating status
//
// this method constructs the singular value decomposition of the input
// matrix such that u * w * transpose(v) = this
//
// this method relies heavily on concepts from the EISPACK math libraries
//   Burton S. Garbow, Mathematics and Computer Science Div, Argonne National
//   Laboratory, August 1983.
//
// Major modifications have been made to incorporate this routine into the
// ISIP IFC libraries
// 
// Householder bidiagonalization and a variant of the qr algorithm are used.
//
// An error is reported if 30 iterations do not produce convergence in the
// singular value decomposition. The number 30 is arbitrary but seems to be
// common to all implementations in math libraries such as LaPack, etc.
//
// At present only the economy (also called short) mode of SVD is implemented
// A volatile variable "temp" is used in some comparisons to lessen the risk
// of convergence issues
//
template <class TScalar, class TIntegral>
bool8
MMatrixMethods::decompositionSVD(const MMatrix<TScalar, TIntegral>& this_a,
				 MMatrix<TScalar, TIntegral>& u_a,
				 MMatrix<TScalar, TIntegral>& w_a,
				 MMatrix<TScalar, TIntegral>& v_a,
				 bool8 economy_mode_a) {

  // this method is defined only for float32 and float64 matrices
  //
#ifdef ISIP_TEMPLATE_fp
  
  // Check the SVD mode and error out if mode is not short (economy mode)
  // The int32 mode is not implemeted yet
  //
  if (!economy_mode_a) {
    return Error::handle(name(), L"decompositionSVD", Error::NOT_IMPLEM,
			 __FILE__, __LINE__);
  }
  // check for matrix shape: SVD is defined for matrices where the number
  // of rows is greater than or equal to the number of columns. In the
  // converse case, we transpose A and solve.
  //
  int32 m = this_a.getNumRows();
  int32 n = this_a.getNumColumns();
  if (m < n) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    tmp.transpose();
    tmp.decompositionSVD(v_a, w_a, u_a);
    w_a.transpose();
  }
  else {
    // declare local variables
    //
    MVector<TScalar, TIntegral> rv1(n);
    rv1.assign(0.0);
    MVector<TScalar, TIntegral> tmp_w(n);
    tmp_w.assign(0.0);
  
    TIntegral anorm = 0.0;
    TIntegral c = 0.0;
    TIntegral f = 0.0;
    TIntegral g = 0.0;
    TIntegral h = 0.0;
    TIntegral s = 0.0;
    TIntegral scale = 0.0;
    TIntegral x = 0.0;
    TIntegral y = 0.0;
    TIntegral z = 0.0;
    TIntegral q = 0.0;
  
    TIntegral absf = 0.0;
    TIntegral absg = 0.0;
    TIntegral absh = 0.0;

    int32 i = 0;
    int32 its = 0;
    int32 j = 0;
    int32 jj = 0;
    int32 k = 0;
    int32 l = 0;
    int32 nm = 0;

    // adding variable temp for handling convergence issues with compiler's
    // equality checking as prescribed in the NRIC website
    // "http://www.nr.com/forum/showthread.php?t=292"
    //
    volatile float32 temp = 0.0;

    // set the dimensions for the output matrices
    //
    v_a.setDimensions(n, n, false, Integral::FULL);
    v_a.assign(0.0);
    
    w_a.setDimensions(n, n, false, Integral::FULL);
    w_a.assign(0.0);
    
    // copy the input for manipulation
    //
    u_a.assign(this_a, Integral::FULL);
    u_a.setDimensions(m, n, true);
     
  
    // Householder reduction to bidiagonal form
    //
    for (i = 0; i < n; i++) {
      l = i + 1;
      rv1(i) = scale * g;
      g = 0.0;
      s = 0.0;
      scale = 0.0;

      if (i < m) {

	for (k = i; k < m; k++) {
	  scale = scale + Integral::abs(u_a(k, i));
	}

	if (scale != 0.0) {
	  for (k = i; k < m; k++) {
	    u_a.setValue(k, i, u_a(k, i) / scale);
	    s = s + u_a(k, i) * u_a(k, i);
	  }  

	  f = u_a(i, i);
	  g = (f > 0.0) ? -Integral::abs(Integral::sqrt(s)) :
	    Integral::abs(Integral::sqrt(s));
	  h = f * g - s;
	  u_a.setValue(i, i, f - g);

	  for (j = l; j < n; j++) {
	    s = 0.0;
	    for (k = i; k < m; k++) {
	      s = s + u_a(k, i) * u_a(k, j);
	    }
	    f = s / h;

	    for (k = i; k < m; k++) {
	      u_a.setValue(k, j, u_a(k, j) + f * u_a(k, i));
	    }
	  }
	  for (k = i; k < m; k++) {
	    u_a.setValue(k, i, scale * u_a(k, i));
	  }
	}
      }
    
      tmp_w(i) = scale * g;
      g = 0.0;
      s = 0.0;
      scale = 0.0;
      if ((i < m) && (i != n - 1)) {
	for (k = l; k < n; k++) {
	  scale = scale + Integral::abs(u_a(i, k));
	}

	if (scale != 0.0) {
	  for (k = l; k < n; k++) {
	    u_a.setValue(i, k, u_a(i, k) / scale);
	    s = s + u_a(i, k) * u_a(i, k);
	  }

	  f = u_a(i, l);
	  g = (f > 0.0) ? -Integral::abs(Integral::sqrt(s)) :
	    Integral::abs(Integral::sqrt(s));
	  h = f * g - s;
	  u_a.setValue(i, l, f - g);

	  for (k = l; k < n; k++) {
	    rv1(k) = u_a(i, k) / h;
	  }

	  for (j = l; j < m; j++) {

	    s = 0.0;

	    for (k = l; k < n; k++) {
	      s = s + u_a(j, k) * u_a(i, k);
	    }

	    for (k = l; k < n; k++) {
	      u_a.setValue(j, k, u_a(j, k) + s * rv1(k));
	    }
	  }

	  for (k = l; k < n; k++) {
	    u_a.setValue(i, k, scale * u_a(i, k));
	  }
	}
      }
      anorm = Integral::max(anorm, (Integral::abs(tmp_w(i)) +
				    Integral::abs(rv1(i))));
    }

    // QR accumulation (compute V)
    //
    for (i = n - 1; i >= 0; i--) {
      if (i < n - 1) {
	if (g != 0.0) {
	  for (j = l; j < n; j++) {

	    // float64 division avoids possible underflow
	    //
	    v_a.setValue(j, i, (u_a(i, j) / u_a(i, l)) / g);
	  }

	  for (j = l; j < n; j++) {
	    s = 0.0;
	    for (k = l; k < n; k++) {
	      s = s + u_a(i, k) * v_a(k, j);
	    }

	    for (k = l; k < n; k++) {
	      v_a.setValue(k, j, v_a(k, j) + s * v_a(k, i));
	    }
	  }
	}
      
	for (j = l; j < n; j++) {
	  v_a.setValue(i, j, 0.0);
	  v_a.setValue(j, i, 0.0);
	}
      }
      v_a.setValue(i, i, 1.0);
      g = rv1(i);
      l = i;
    }

    // LQ accumulation (compute U)
    //
    for (i = n - 1; i >= 0; i--) {
      l = i + 1;
      g = tmp_w(i);

      for (j = l; j < n; j++) {
	u_a.setValue(i, j, 0.0);
      }

      if (g != 0.0) {
      
	for (j = l; j < n; j++) {
	  s = 0.0;

	  for (k = l; k < m; k++) {
	    s = s + u_a(k, i) * u_a(k, j);
	  }

	  // float64 division avoids possible underflow
	  //
	  f = (s / u_a(i, i)) / g;

	  for (k = i; k < m; k++) {
	    u_a.setValue(k, j, u_a(k, j) + f * u_a(k, i));
	  }
	}

	for (j = i; j < m; j++) {
	  u_a.setValue(j, i, u_a(j, i) / g);
	}
      }
      else {
	for (j = i; j < m; j++) {
	  u_a.setValue(j, i, 0.0);
	}
      }
      u_a.setValue(i, i, u_a(i, i) + 1.0);
    }

    // diagonalization of the bidiagonal form (creating the w matrix)
    // and normalizing u and v accordingly
    //
    // loop over singular values
    //
    for (k = n - 1; k >= 0; k--) {

      for (its = 1; its <= 30; its++) {

	bool8 flag = true;

	// test for splitting
	//
	for (l = k; l >= 0; l--) {
	  nm = l - 1;
	  temp = (float32)anorm + (float32)Integral::abs(rv1(l));
	  //if (((float32)anorm + (float32)Integral::abs(rv1(l))) == (float32)anorm) {
	  if (temp == (float32)anorm) {
	    flag = false;
	    break;
	  }

	  // rv1(0) is always zero. thus this section won't be reached so there
	  // is no need to worry with nm < 0
	  //
	  temp = (float32)anorm + (float32)Integral::abs(tmp_w(nm));
	  //	  if (((float32)anorm + (float32)Integral::abs(tmp_w(nm))) == (float32)anorm) {
	  if (temp == (float32)anorm) {
	    break;
	  }
	}
	if (flag) {

	  // cancellation of rv1(l) if l greater than 1
	  //
	  c = 0.0;
	  s = 1.0;

	  for (i = l; i <= k; i++) {
	    f = s * rv1(i);
	    rv1(i) = c * rv1(i);
	    temp = (float32)anorm + (float32)Integral::abs(f);
	    //	    if (((float32)anorm + (float32)Integral::abs(f)) == (float32)anorm) {
	    if (temp == (float32)anorm) {
	      break;
	    }
	    g = tmp_w(i);

	    // compute (a**2 + b**2) ** (1/2) without destructive underflow
	    // or overflow
	    //
	    absf = Integral::abs(f);
	    absg = Integral::abs(g);
	    if (absf > absg) {
	      h = (absf * Integral::sqrt(1.0 + (absg / absf) * (absg / absf)));
	    }
	    else {
	      if (absg == 0.0) {
		h = 0.0;
	      }
	      else {
		h = (absg * Integral::sqrt(1.0 + (absf / absg) *
					   (absf / absg)));
	      }
	    }
	  
	    tmp_w(i) = h;
	    c = g / h;
	    s = -f / h;
	    for (j = 0; j < m; j++) {
	      y = u_a(j, nm);
	      z = u_a(j, i);
	      u_a.setValue(j, nm, y * c + z * s);
	      u_a.setValue(j, i, z * c - y * s);
	    }
	  }
	}

	// test for convergence
	//
	z = tmp_w(k);

	if (l == k) {
	    
	  // convergence is reached
	  //
	  if (z < 0.0) {

	    // singular value is made non-negative and we update the sign of the
	    // right singular vectors
	    //
	    tmp_w(k) = -z;
	    for (j = 0; j < n; j++) {
	      v_a.setValue(j, k, -(v_a(j, k)));
	    }
	  }
	  break;
	}

	// if we've computed the maximum number of iterations and still not
	// converged then give up
	//
	if (its == 30) {
	  u_a.debug(L"u_a");	
	  this_a.debug(L"this_a");	
	  return Error::handle(name(), L"decompositionSVD", u_a.ERR_SINGLR,
			       __FILE__, __LINE__);
	}

	// else we need to iterate again
	//
	// shift from bottom 2 by 2 minor
	x = tmp_w(l);
	nm = k - 1;
	y = tmp_w(nm);
	g = rv1(nm);
	h = rv1(k);
	f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);

	// compute (a**2 + b**2) ** (1/2) without destructive underflow
	// or overflow
	//
	absf = Integral::abs(f);
	if (absf > 1.0) {
	  g = (absf * Integral::sqrt(1.0 + (1.0 / absf) * (1.0 / absf)));
	}
	else {
	  g = Integral::sqrt(1.0 + (absf) * (absf));
	}

	q = (f > 0.0) ? Integral::abs(g) : -Integral::abs(g);
	f = ((x - z) * (x + z) + h * ((y / (f + q)) - h)) / x;

	// next QR transformation
	//
	c = 1.0;
	s = 1.0;

	for (j = l; j <= nm; j++) {
	  i = j + 1;
	  g = rv1(i);
	  y = tmp_w(i);
	  h = s * g;
	  g = c * g;

	  absf = Integral::abs(f);
	  absh = Integral::abs(h);
	  if (absf > absh) {
	    z = (absf * Integral::sqrt(1.0 + (absh / absf) * (absh / absf)));
	  }
	  else {
	    if (absh == 0.0) {
	      z = 0.0;
	    }
	    else {
	      z = (absh * Integral::sqrt(1.0 + (absf / absh) *
					 (absf / absh)));
	    }
	  }

	  rv1(j) = z;
	  c = f / z;
	  s = h / z;
	  f = x * c + g * s;
	  g = g * c - x * s;
	  h = y * s;
	  y = y * c;

	  for (jj = 0; jj < n; jj++) {
	    x = v_a(jj, j);
	    z = v_a(jj, i);
	    v_a.setValue(jj, j, x * c + z * s);
	    v_a.setValue(jj, i, z * c - x * s);
	  }

	  absf = Integral::abs(f);
	  absh = Integral::abs(h);
	  if (absf > absh) {
	    z = (absf * Integral::sqrt(1.0 + (absh / absf) * (absh / absf)));
	  }
	  else {
	    if (absh == 0.0) {
	      z = 0.0;
	    }
	    else {
	      z = (absh * Integral::sqrt(1.0 + (absf / absh) *
					 (absf / absh)));
	    }
	  }
	  tmp_w(j) = z;

	  // rotation can be arbitrary if z is zero
	  //
	  if (z != 0.0) {
	    c = f / z;
	    s = h / z;
	  }

	  f = c * g + s * y;
	  x = c * y - s * g;

	  for (jj = 0; jj < m; jj++) {
	    y = u_a(jj, j);
	    z = u_a(jj, i);
	    u_a.setValue(jj, j, y * c + z * s);
	    u_a.setValue(jj, i, z * c - y * s);
	  }
	}      

	rv1(l) = 0.0;
	rv1(k) = f;
	tmp_w(k) = x;
      }
    }

    // reorder singular values in descending order. adjust the u and v
    // matrices as well
    //
    // sort the w vector
    //
    VectorLong sort_indices;
    tmp_w.index(sort_indices);

    // reverse the order (the index method sorts in ascending order)
    //
    for (int32 i = 0; i < n / 2; i++) {
      int32 tmp = sort_indices(i);
      sort_indices(i) = sort_indices(n - i - 1);
      sort_indices(n - i - 1) = tmp;
    }

    // reorder matrices
    //
    u_a.reorderColumns(sort_indices);
    v_a.reorderColumns(sort_indices);
    tmp_w.reorder(sort_indices);

    // copy data out to the w matrix
    //
    for (i = 0; i < n; i++) {
      w_a.setValue(i, i, tmp_w(i));
    }

  }
    // exit gracefully
  //
  return true;
#else
  return Error::handle(name(), L"decompositionSVD", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif
}

// explicit instantiations
//
template bool8
MMatrixMethods::decompositionSVD(const MMatrix<ISIP_TEMPLATE_TARGET>&,
				 MMatrix<ISIP_TEMPLATE_TARGET>&,
				 MMatrix<ISIP_TEMPLATE_TARGET>&,
				 MMatrix<ISIP_TEMPLATE_TARGET>&,
				 bool8);


// method: decompositionQR
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MMatrix<TScalar, TIntegral>& q: (output) orthonormal matrix
//  MMatrix<TScalar, TIntegral>& r: (output) the upper triangular part contains the upper triangular part of R, while the components j : m-1 of the jth Householder vector are stored in r(j : m-1, j), j < m-1
//
// return: a bool8 value indicating the status
//
// this method constructs the QR decomposition of the input matrix such that 
// q_a * r_a = this
// It is assumed that the input matrix is full rank.
//
// this method is based on Householder transformations
// refer to:
// G. H. Golub and C. F. Van Loan,
// Matrix Computations, Second Edition,
// The Johns Hopkins University Press, Baltimore and London, 1989,
// Sections 5.1 and 5.2.
//

template <class TScalar, class TIntegral>
bool8
MMatrixMethods::decompositionQR(const MMatrix<TScalar, TIntegral>& this_a,
				MMatrix<TScalar, TIntegral>& q_a,
				MMatrix<TScalar, TIntegral>& r_a) {

  // this method is defined only for float32 and float64 matrices
  //
 #ifdef ISIP_TEMPLATE_fp
  
  // check for matrix shape : q_a matrix of qr should be a square matrix
  // of dimensions min_mn*min_mn, where min_mn is the minimum of m, n
  //
  int32 m = this_a.getNumRows();
  int32 n = this_a.getNumColumns();
  int32 min_mn = (m < n) ? m : n;

  // declare local variables
  TIntegral mu = 0.0, b = 0.0;
  int32 j, k, i, n1;
  MVector<TScalar, TIntegral> w;
  TIntegral x1 = 0.0;
  
  // Initialize q_a as identity matrix of dimension m*m
  //
  q_a.setDimensions(m, m, false, Integral::FULL);
  q_a.assign(0.0);
  q_a.setDiagonal(1.0);
  
  // copy the input into r_a for manipulation
  //
  r_a.assign(this_a, Integral::FULL);
  r_a.setDimensions(m, n, true);

  //Householder reduction to upper triangular form
  //
  for (j = 0; j < min_mn; j++) {
    n1 = m - j;
    MVector<TScalar, TIntegral> x(n1), v;

    for (k = j; k < m; k++) {
      x(k - j) = r_a(k, j);
    }
    
    //    house(x, v)
    //
    mu = x.norm();
    v.assign(x);
    if (mu != 0.0) {
      x1 = x(0);
      b = x1 + ((x1 >= 0.0) ? 1 : -1) * mu;
      for (i = 1; i < n1; i++) {
	v(i) /= b;
      }
    }
    v(0) = 1.0;
    MMatrix<TScalar, TIntegral> r_block(m - j, n - j);
    for (k = j; k < m; k++) {
      for (i = j; i < n; i++) {
	r_block.setValue(k - j, i - j, r_a(k, i));
      }
    }

    // row_house(r_block, v)
    //
    MMatrix<TScalar, TIntegral> r_block_t;

    r_block_t.transpose(r_block);
    w.assign(v);
    b = -2.0 / w.dotProduct(w);
    r_block_t.multv(w, v);
    w.mult(b);
    MMatrix<TScalar, TIntegral> tmp;
    tmp.outerProduct(v, w);
    r_block.add(tmp);
  
    for (k = j; k < m; k++) {
      for (i = j; i < n; i++) {
	r_a.setValue(k, i, r_block(k - j, i - j));
      }
    }

    //copy Householder vectors into r
    //
    if (j < m) {
      for (k = j + 1; k < m; k++) {
	r_a.setValue(k, j, v(k - j));
      }
    }
  }

  //Form q_a matrix, using backward accumulation
  for (j = min_mn - 1; j >= 0; j--) {
    n1 = m - j;
    MVector<TScalar, TIntegral> v(n1);

    v(0) = 1.0;
    for (k = j + 1; k < m; k++) {
      v(k - j) = r_a.getValue(k, j);
    }
    MMatrix<TScalar, TIntegral> q_block(m - j, m - j);
    for (k = j; k < m; k++) {
      for (i = j; i < m; i++) {
	q_block.setValue(k - j, i - j, q_a(k, i));
      }
    }

    //   row_house(q_block,v)
    //
    MMatrix<TScalar, TIntegral> q_block_t;
    q_block_t.transpose(q_block);
    w.assign(v);
    b = -2.0 / w.dotProduct(w);
    q_block_t.multv(w, v);
    w.mult(b);
    MMatrix<TScalar, TIntegral> tmp;
    tmp.outerProduct(v, w);
    q_block.add(tmp);

    for (k = j; k < m; k++) {
      for (i = j; i < m; i++) {
	q_a.setValue(k, i, q_block(k - j, i - j));
      }
    }
  }
  return true;
#else
  return Error::handle(name(), L"decompositionQR", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif
}

// explicit instantiations
//
template bool8 
MMatrixMethods::decompositionQR(const MMatrix<ISIP_TEMPLATE_TARGET>&,
				MMatrix<ISIP_TEMPLATE_TARGET>&,
				MMatrix<ISIP_TEMPLATE_TARGET>&);
