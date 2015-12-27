// file: $isip/class/math/matrix/MMatrix/mmat_16.cc
// version: $Id: mmat_16.cc 10304 2005-12-14 06:25:15Z srinivas $
//

// system include files
//
#include <typeinfo>

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"
#include <VectorLong.h>

#ifndef ISIP_TEMPLATE_unsigned

// method: eigen
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MVector<TScalar, TIntegral>& eigvals: (output) eigenvalues
//  MMatrix<TScalar, TIntegral>& eigvects: (output) eigenvectors
//
// return: a bool8 value indicating status
//
// this method computes the eigenvalues of a real general matrix.
// we use Hessenberg Reduction + QR to compute eigenvalues and Inverse
// Iteration method to compute eigenvectors.
//
// reference:
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 482-495, 1995.
//
// the algorithm used here only supports matrices which have real
// eigenvalues and eigenvectors. if the matrix has complex eigenvalues,
// this method will return the real parts of the eigenvalues and
// eigenvectors.
//
// the eigen vectors are the rows of the output matrix and the eigen values
// are always sorted in decending order.
//
template <class TScalar, class TIntegral>
bool8 MMatrixMethods::eigen(const MMatrix<TScalar, TIntegral>& this_a,
			      MVector<TScalar, TIntegral>& eigvals_a,
			      MMatrix<TScalar, TIntegral>& eigvects_a) {

#ifndef ISIP_TEMPLATE_complex

  // check arguments: non-square or singularity
  //
  if (!this_a.isSquare()) {
    this_a.debug(L"this_a");
    return Error::handle(name(), L"eigen()", Error::ARG, __FILE__, __LINE__);
  }

  // get the number of matrix rows
  //
  int32 nrows = this_a.getNumRows();

  // condition: empty input matrix
  //
  if (nrows <= 0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"eigen()",
			 MMatrix<TScalar, TIntegral>::ERR, 
			 __FILE__, __LINE__, Error::WARNING);
  }

  // initialize the output vector and matrix
  //
  eigvals_a.setLength(nrows);
  eigvects_a.changeType(Integral::FULL);
  eigvects_a.setDimensions(nrows, nrows);

  // if there is only one element in the matrix, the eigenvalue by
  // definition is the element's value.
  //
  if (nrows == 1) {
    eigvals_a(0) = this_a(0, 0);
    eigvects_a.setValue(0, 0, (TIntegral)1);
  }

  // else: do the int32 calculation
  //
  else {

    // for float32 and float64 matrices, use the same current matrix
    //
    if ((typeid(TIntegral) == typeid(float32)) ||
	(typeid(TIntegral) == typeid(float64)) ||
	(typeid(TIntegral) == typeid(complexfloat))) {

      // declare local variables
      //
      MVector<TScalar, TIntegral> eigimage(nrows);
      MVector<TScalar, TIntegral> tmp_vec(nrows);
      
      // make a copy of current matrix as it is const and we can't convert a
      // const matrix to a balance matrix
      // 
      MMatrix<TScalar, TIntegral> tmp;
      tmp.assign(this_a, Integral::FULL);
    
      // perform three key operations:
      //  - balance the matrix
      //  - use Hessenberg elimination
      //  - use QR to get the eigenvalues
      //
      tmp.eigenBalance();
      tmp.eigenEliminateHessenberg();
      tmp.eigenHessenbergQR(eigvals_a, eigimage);
      eigvals_a.sort(Integral::DESCENDING);

      // compute each eigenvector corresponding to an eigenvalue
      //
      for (int32 row = 0; row < nrows; row++) {
	tmp.copy(this_a);
	tmp.eigenComputeVector(tmp_vec, (TIntegral)eigvals_a(row));
	eigvects_a.setRow(row, tmp_vec);
      }
    }
    
    // for other matrices, copy the current matrix to a float64 matrix
    // and call eigen method - this copy is required for numerical
    // precision
    //
    else {

      // declare local variables
      //
      MVector<Double, float64> eigvals;
      MMatrix<Double, float64> eigvects;
      MMatrix<Double, float64> tmp;
      
      // copy the current matrix to a float64 matrix
      //
      tmp.assign(this_a);
      
      // call eigen method for the matrix
      //
      if (!tmp.eigen(eigvals, eigvects)) {
	return false;
      }
      
      // assign the eigen values and eigen vectors to the output arguments
      //
      eigvals_a.assign(eigvals);
      eigvects_a.assign(eigvects);
    } 
  }
  
  // exit gracefully
  //
  return true;

#else

  // this algorithm is not supported for complex matrix
  //
  return Error::handle(name(), L"eigen: eigenvalues computation is not supported for complex matrix", Error::ARG, __FILE__, __LINE__);
  
#endif
}

// explicit instantiations
//
template bool8
MMatrixMethods::eigen<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&,
 MMatrix<ISIP_TEMPLATE_TARGET>&);
#endif

// these methods are for MMatrix<Float, float32> and MMatrix<Double, float64>
// only because they use values related to float-point precision. so they
// can be compiled and linked only once
//
#ifdef ISIP_TEMPLATE_fp

// method: eigenBalance
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (input/output) input matrix
//
// return: a bool8 value indicating status
//
// this method replaces a matrix by a balanced matrix with
// identical eigenvalues. see:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 482-484, 1995.
//
// for more details.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::eigenBalance(MMatrix<TScalar, TIntegral>& this_a) {

  // get the dimension of matrix
  //
  int32 nrows = this_a.getNumRows();

  // choose the radix base employed for floating-point arithmetic
  // i.e. 2 for most machines, but 16 for IBM mainframe architectures
  //
  float64 radix = 2.0;
  float64 sqrdx = radix * radix;

  // begin the balance operations
  //
  bool8 last = false;

  while (!last) {

    // iterate over all rows
    //
    last = true;
    for (int32 i = 0; i < nrows ; i++) {

      // initialize accumulators
      //
      float64 row_norm = 0;
      float64 col_norm = 0;
      float64 sum = 0;

      // calculate norms of row and column
      //
      for (int32 j = 0; j < nrows; j++) {
	if (j != i) {
	  col_norm += Integral::abs((float64)this_a(j, i));
	  row_norm += Integral::abs((float64)this_a(i, j));
	}
      }

      // when both norms are nonzero
      //
      if ((col_norm != 0) && (row_norm != 0)) {

	// compute a measure of the need to balance the matrix
	//
	sum = col_norm + row_norm;

	// find the integer power of the machine radix that comes
	// closest to balancing the matrix
	//
	float64 factor = 1;
	float64 g = row_norm / radix;
	while (col_norm < g) {
	  factor *= radix;
	  col_norm *= sqrdx;
	}
	
	g = row_norm * radix;
	while (col_norm > g) {
	  factor /= radix;
	  col_norm /= sqrdx;
	}

	// determine if a similarity transformation is needed
	//
	if ((MMatrix<TScalar, TIntegral>::THRESH_BALANCE * sum) >
	    (col_norm + row_norm) / factor) {

	  // perform a similarity transformation
	  //
	  last = false;
	  for (int32 j = 0; j < nrows; j++) {
	    this_a.setValue(i, j, this_a(i, j) / factor);
	  }
	  for (int32 j = 0; j < nrows; j++) {
	    this_a.setValue(j, i, this_a(j, i) * factor);
	  }
	}
      }
    }
  }

  // exit gracefully
  //
  return true;
}  

// method: eigenEliminateHessenberg
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (input) input matrix
//
// return: a bool8 value indicating status
//
// this method reduces a matrix to hessenberg's form by the elimination
// method. see:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 484-486, 1995.
//
// for more details.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::eigenEliminateHessenberg(MMatrix<TScalar,
						 TIntegral>& this_a) {

  // get the dimension of input matrix
  //
  int32 nrows = this_a.getNumRows();

  // process eliminating operation to the input matrix
  //
  for (int32 m = 1; m < (nrows - 1); m++) {

    // declare local variables
    //
    float64 x = 0;
    int32 i = m;

    // find the pivot
    //
    for (int32 j = m; j < nrows; j++) {
      if (Integral::abs(this_a(j, m - 1)) > Integral::abs(x)) {
	x = this_a(j, m - 1);
	i = j;
      }
    }

    // if the pivot is found, interchange rows and columns
    //
    if (i != m) {
      for (int32 j = m - 1; j < nrows; j++) {
	float64 tmp = this_a(i, j); 
	this_a.setValue(i, j, this_a(m, j)); 
	this_a.setValue(m, j, tmp);
      }
      for (int32 j = 0; j < nrows; j++) {
	float64 tmp = this_a(j, i); 
	this_a.setValue(j, i, this_a(j, m)); 
	this_a.setValue(j, m, tmp);
      }
    }

    // carry out the elimination
    //
    if (x != 0) {

      // loop over rows
      //
      for (i = m + 1; i < nrows; i++) {

	float64 y = this_a(i, m - 1);
	if (y != 0) {
	  y /= x;
	  this_a.setValue(i, m - 1, y);
	  
	  for (int32 j = m; j < nrows; j++) {
	    this_a.setValue(i, j, this_a(i, j) - y * this_a(m, j));
	  }
	  
	  for (int32 j = 0; j < nrows; j++) {
	    this_a.setValue(j, m, this_a(j, m) + y * this_a(j, i));
	  }
	}
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// method: eigenHessenbergQR
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MVector<TScalar, TIntegral>& eigval_r: (output) real part of eigenvalues
//  MVector<TScalar, TIntegral>& eigval_i: (output) imag part of eigenvalues
//
// return: a bool8 value indicating status
//
// this method finds all eigenvalues of an upper hessenberg matrix. see:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 491-493, 1995.
//
// for more details. this is a rather specialized method that has some
// internal constants associated with it. we chose not to make these
// part of the class header file because they are very algorithm specific.
//
// note that this method destroys the input.
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::eigenHessenbergQR(MMatrix<TScalar, TIntegral>& this_a,
				  MVector<TScalar, TIntegral>& eigval_r_a,
				  MVector<TScalar, TIntegral>& eigval_i_a) {

  // get the dimension of input matrix
  //
  int32 nrows = this_a.getNumRows();

  // compute matrix norm for possible use in locating single small
  // subdiagonal element
  //
  float64 anorm = 0;
  for (int32 i = 0; i < nrows; i++) {
    for (int32 j = ((i - 1) < 0 ? 0: i - 1); j < nrows; j++) {
      anorm += Integral::abs(this_a(i, j));
    }
  }
  
  // declare local variables
  //
  float64 z = 0.0;
  float64 y = 0.0;
  float64 x = 0.0;
  float64 w = 0.0;
  float64 v = 0.0;
  float64 u = 0.0;
  float64 r = 0.0;
  float64 q = 0.0;
  float64 p = 0.0; 

  int32 hqr_max_iterations = 30;

  MVector<Double, float64> wr(nrows);
  MVector<Double, float64> wi(nrows);
  
  int32 nn = nrows;
  int32 l;
  float64 t = 0.0;
  float64 s = 0.0;

  // loop over the number of rows
  //
  while (nn >= 1) {

    int32 its = 0;

    do {

      // look for single small subdiagonal element
      //
      for (l = nn; l >= 2; l--) {
	s = Integral::abs(this_a(l - 2, l - 2)) +
	  Integral::abs(this_a(l - 1, l - 1));
	if (s == 0.0) {
	  s = anorm;
	}
	if ((float64)(Integral::abs(this_a(l - 1, l - 2)) + s) == s) {
	  break;
	}
      }

      x = this_a(nn - 1, nn - 1);
      if (l == nn) {

	// one root is found
	//
	wr(nn - 1) = x + t;
	wi(nn - 1) = 0.0;
	nn--;
      }
      else {

	y = this_a(nn - 2, nn - 2);
	w = this_a(nn - 1, nn - 2) * this_a(nn - 2, nn - 1);
	if (l == (nn - 1)) {
	  p = 0.5 * (y - x);
	  q = p * p + w;
	  z = Integral::sqrt((float64)Integral::abs(q));
	  x += t;
	  if (q >= 0.0) {
	    if (p > 0) {
	      z = Integral::abs(z);
	    }
	    else {
	      z = -Integral::abs(z);
	    }       
	    z += p;
	    wr(nn - 2) = wr(nn - 1) = x + z;
	    if (z != 0) {
	      wr(nn - 1) = x - w / z;
	    }
	    wi(nn - 2) = wi(nn - 1) = 0.0;
	  }
	  else {
	    wr(nn - 2) = wr(nn - 1) = x + p;
	    wi(nn - 2) = -(wi(nn - 1) = z);
	  }
	  nn -= 2;
	}
	else {
	  if (its >= hqr_max_iterations) {
	    this_a.debug(L"this_a");	    
	    return Error::handle(name(), L"eigenHessenbergQR()",
				 MMatrix<Double, float64>::ERR,
	      			 __FILE__, __LINE__, Error::WARNING);
      	  }
	  if (its == 10 || its == 20) {
	    t += x;
	    for (int32 i = 1; i <= nn; i++) {
	      this_a.setValue(i - 1, i - 1, this_a(i - 1, i - 1) - x);
	    }
	    s = Integral::abs(this_a(nn - 1, nn - 2)) +
	      Integral::abs(this_a(nn - 2, nn - 3));
	    y = x = 0.75 * s;
	    w = -0.4375 * s * s;
	  }
	  its++;

	  int32 m;
	  for (m = (nn - 2); m >= l; m--) {
	    z = this_a(m - 1, m - 1);
	    r = x - z;
	    s = y - z;
	    p = (r * s - w) / this_a(m, m - 1) + this_a(m - 1, m);
	    q = this_a(m, m) - z - r - s;
	    r = this_a(m + 1, m);
	    s = Integral::abs(p) + Integral::abs(q) + Integral::abs(r);
	    p /= s;
	    q /= s;
	    r /= s;
	    if (m == l) {
	      break;
	    }
	    u = Integral::abs(this_a(m - 1, m - 2)) *
	      (Integral::abs(q) + Integral::abs(r));
	    v = Integral::abs(p) * (Integral::abs(this_a(m - 2, m - 2)) +
				    Integral::abs(z) +
				    Integral::abs(this_a(m, m)));
	    if ((float64)(u + v) == v) {
	      break;
	    }
	  }
	  for (int32 i = m + 2; i <= nn; i++) {
	    this_a.setValue(i - 1, i - 3, 0.0);
	    if  (i != (m + 2)) {
	      this_a.setValue(i - 1, i - 4, 0.0);
	    }
	  }
	  for (int32 k = m; k <= nn - 1; k++) {
	    if (k != m) {
	      p = this_a(k - 1, k - 2);
	      q = this_a(k, k - 2);
	      r = 0.0;
	      if (k != (nn - 1)) {
		r = this_a(k + 1, k - 2);
	      }
	      x = Integral::abs(p) + Integral::abs(q) + Integral::abs(r);
	      if (x != 0) {
		p /= x;
		q /= x;
		r /= x;
	      }
	    }
	    if (p > 0) {
	      s = Integral::sqrt(p * p + q * q + r * r);
	    }
	    else {
	      s = -Integral::sqrt(p * p + q * q + r * r);
	    }     

	    if (s != 0) {
	      if (k == m) {
		if (l != m) {
		  this_a.setValue(k - 1, k - 2, -this_a(k - 1, k - 2));
		}
	      }
	      else {
		this_a.setValue(k - 1, k - 2, -s * x);
	      }
	      p += s;
	      x = p / s;
	      y = q / s;
	      z = r / s;
	      q /= p;
	      r /= p;
	      
	      for (int32 j = k; j <= nn; j++) {
		p = this_a(k - 1, j - 1) + q * this_a(k, j - 1);
		if (k != (nn - 1)) {
		  p += r * this_a(k + 1, j - 1);
		  this_a.setValue(k + 1, j - 1, this_a(k + 1, j - 1) - p * z);
		}
		this_a.setValue(k, j - 1, this_a(k, j - 1) - p * y);
		this_a.setValue(k - 1, j - 1, this_a(k - 1, j - 1) - p * x);
	      }

	      int32 mmin = nn < k + 3 ? nn : k + 3;
	      for (int32 i = l; i <= mmin; i++) {
		p = x * this_a(i - 1, k - 1) + y * this_a(i - 1, k);
		if (k != (nn - 1)) {
		  p += z * this_a(i - 1, k + 1);
		  this_a.setValue(i - 1, k + 1, this_a(i - 1, k + 1) - p * r);
		}
		this_a.setValue(i - 1, k, this_a(i - 1, k) - p * q);
		this_a.setValue(i - 1, k - 1, this_a(i - 1, k - 1) - p);
	      }
	    }
	  }
	}
      }
    } while (l < nn - 1);
  }

  // copy results to output vector
  //
  eigval_r_a.assign(wr);
  eigval_i_a.assign(wi);

  // exit gracefully
  //
  return true;
}

// method: eigenComputeVector
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (input) input matrix
//  MVector<TScalar, TIntegral>& eigvect: (output) eigenvector
//  TIntegral eigval: (input) eigenvalue
//
// return: a bool8 value indicating status
//
// this method computes the eigenvalues of a matrix. see:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 493-495, 1995.
//
// for more details. there are a lot of local constants to this code,
// and the algorithm is fairly dependent on these.
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::eigenComputeVector(MMatrix<TScalar, TIntegral>& this_a,
				   MVector<TScalar, TIntegral>& eigvect_a,
				   TIntegral eigval_a) {

  // get the dimension of input matrix
  //
  int32 n = this_a.getNumRows();

  // initialize constants and variables
  //
  const float64 MIN_INITIAL_GROWTH = (float64)1000.0;
  const int32 MAX_INITIAL_ITER = (int32)10;
  const int32 MAX_ITER = (int32)8;
  const int32 MAX_L_UPDATE = (int32)5;
  const float64 EPSILON = (float64)0.0000001;
  const float64 MIN_DECREASE = (float64)0.01;

  // initialize the output vector
  //
  eigvect_a.setLength(n);
  
  // treat diagonal matrix in a different way
  //
  if (this_a.isDiagonal()) {

    // fill output eigenvector with zero
    //
    eigvect_a.clear(Integral::RETAIN);

    // find the exact eigenvalue in diagonal elements of the matrix
    //
    for (int32 i = 0; i < n; i++) {
      Double temp_val = this_a(i, i);

      // if eigenvalue found, the corresponding eigenvector value
      // should be set to 1, otherwise the value should keep 0
      //
      if (temp_val.almostEqual(eigval_a)) {
	eigvect_a(i) = 1;
      }
    }
  }

  // for FULL, SYMMETRIC, TRIANGULAR or SPARSE matrix
  //
  else {

    // subtract eigenvalue from the diagonal elements
    //
    float64 eig_val = (float64) eigval_a;
    for (int32 i = 0; i < n; i++) {
      this_a.setValue(i, i, this_a(i, i) - eig_val);
    }

    // declare local variables
    //
    MVector<TScalar, TIntegral> xi(n);
    MVector<TScalar, TIntegral> xi_init;
    MVector<TScalar, TIntegral> y;
    MVector<TScalar, TIntegral> y_init_max;
    VectorLong index(n);
    int32 sign;
    float64 tiny_num = 0;
    if (typeid(TIntegral) == typeid(float32)) {
      tiny_num = 1.e-10;
    }
    else if (typeid(TIntegral) == typeid(float64)) {
      tiny_num = 1.e-20;
    }
    else {
      tiny_num = 1.e-10;
    }

    // get the LU decomposition of temporary matrix
    //
    MMatrix<TScalar, TIntegral> lower_trig, upper_trig;
    this_a.decompositionLU(lower_trig, upper_trig, index, sign, tiny_num);

    // choose a random normalized vector xi as the initial guess for the
    // eigenvector and solve A * y = xi, new vector y should be bigger than
    // xi by a "growth factor", which is now MIN_INITIAL_GROWTH
    //
    int32 iter_num = 0;
    float64 len_y;
    float64 maxGF = -1;
    do {
      iter_num++;

      // random and normalize a vector xi
      // make xi(0)*xi(0) + xi(1)*xi(1) + .... == 1
      //
      xi.rand(-50, 50);
      xi.div((float64)((Double)(xi.sumSquare())).sqrt());

      // use LU matrix to solve equation L * U * y = xi
      //
      lower_trig.luSolve(y, lower_trig, upper_trig, index, xi);

      // get the norm of vector y
      //
      len_y = (float64)((Double)y.sumSquare()).sqrt();

      // record max len_y and the corresponding vector y
      //
      if (len_y > maxGF) {
	maxGF = len_y;
	xi_init.assign(xi);
	y_init_max.assign(y);
      }
    }
    while((len_y < MIN_INITIAL_GROWTH) && (iter_num < MAX_INITIAL_ITER));

    // copy and normalize vector y
    //
    y.div(y_init_max, maxGF);

    iter_num = 0;
    int32 update_num = 0;
    float64 di = 0;
    float64 di1;
    do {

      // get the value of |y - xi| and if it is too small, no further
      // improvement is needed
      //
      di1 = (TScalar)xi.distance(y);
      if (di1 < EPSILON) {
	break;
      }

      // if |y - xi| is not decreasing rapidly enough, we will try to
      // updating the eigenvalue. if the eigenvalue can not be updated
      // to a new one because of machine accuracy, no further
      // improvement for the eigenvector is needed, we just quit
      //
      iter_num++;
      float64 decrease = (float64) Integral::abs(di1 - di);
      float64 delta_val = 0;
	
      if (decrease < MIN_DECREASE) {

	// calculate the improvement for eigenvalue as 1/|xi * y * len_y|
	//
	delta_val = 1 / (xi.dotProduct(y) * len_y);
	eig_val += delta_val;
	update_num++;
	
	if (delta_val == 0) {

	  // no further iteration is need since the delta value is zero
	  //
	  break;
	}
	else {
	  iter_num = 0;

	  // update new diagonal elements with updated eigenvalue
	  //
	  for (int32 i = 0; i < n; i++) {
	    this_a.setValue(i, i, this_a(i, i) - delta_val);
	  }

	  // get LU decomposition result of updated temporary matrix
	  //
	  this_a.decompositionLU(lower_trig, upper_trig, index, sign,tiny_num);
	}
      }

      // this is iteration algorithm, we update xi with y and by solving
      // equation A * y = xi we get new vector y
      //
      xi.assign(y);
      di = di1;

      // solve y with the LU decomposition results
      //
      lower_trig.luSolve(y, lower_trig, upper_trig, index, xi);

      // normalize vector y
      //
      len_y = (float64)((Double)y.sumSquare()).sqrt();
      y.div((float64)len_y);
    }
    while ((iter_num < MAX_ITER) && (update_num < MAX_L_UPDATE));

    // copy the result vector to output vector
    //
    eigvect_a.assign(y);
  }

  // exit gracefully
  //
  return true;
}

#endif

// method: luSolve
//
// arguments:
//  MVector<TScalar, TIntegral>& out_vec: (output) output vector
//  const MMatrix<TScalar, TIntegral>& l: (input) lower triangular
//  const MMatrix<TScalar, TIntegral>& u: (input) upper triangular
//  const VectorLong& index: (input) input pivot index
//  const MVector<TScalar, TIntegral>& in_vec: (output) input vector
//
// return: a bool8 value indicating status
//
// this method solves the linear equation L * U * x = b, where L, U are
// lower and upper triangular matrices respectively and b is an input vector.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::luSolve(MVector<TScalar, TIntegral>& out_vec_a,
				const MMatrix<TScalar, TIntegral>& l_a,
				const MMatrix<TScalar, TIntegral>& u_a,
				const VectorLong& index_a,
				const MVector<TScalar, TIntegral>& in_vec_a) {

  // get the dimensions of input matrix
  //
  int32 nrows = u_a.getNumRows();

  // reorder the input vector elements' sequence caused by pivoting
  // and copy it to temporary vector
  //
  out_vec_a.setLength(in_vec_a.length());
  for (int32 i = 0; i < nrows; i++) {
    out_vec_a(i) = in_vec_a(index_a(i));
  }

  // solve lower triangular matrix first, we start loop from the second
  // element of vector because out_vec_a(0) == in_vec_a(0)
  //
  for (int32 i = 1; i < nrows; i++) {

    // declare an accumulator
    //
    TIntegral sum = out_vec_a(i);

    // subtract every previous element
    //
    for (int32 j = 0; j < i; j++) {
      sum -= (TIntegral)(l_a(i, j)) * out_vec_a(j);
    }

    // output the result
    //
    out_vec_a(i) = (TIntegral) sum;
  }

  // solve for the upper triangular matrix
  //
  for (int32 i = nrows - 1; i >= 0; i--) {

    // declare an accumulator
    //
    TIntegral sum = (TIntegral) out_vec_a(i);

    // subtract every previous element
    //
    for (int32 j = i + 1; j < nrows; j++) {
      sum -= ((TIntegral)(u_a(i, j))) * (TIntegral)out_vec_a(j);
    }

    // output the result
    //
    out_vec_a(i) = (TIntegral) sum / u_a(i, i);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::luSolve(MVector<ISIP_TEMPLATE_TARGET>&,
			const MMatrix<ISIP_TEMPLATE_TARGET>&,
			const MMatrix<ISIP_TEMPLATE_TARGET>&,
			const VectorLong&,
			const MVector<ISIP_TEMPLATE_TARGET>&);


// method: choleskySolve
//
// arguments:
//  MVector<TScalar, TIntegral>& out_vec: (output) output vector
//  const MMatrix<TScalar, TIntegral>& l: (input) lower triangular cholesky
//                                        decomposition matrix
//  const MVector<TScalar, TIntegral>& in_vec: (output) input vector
//
// return: a bool8 value indicating status
//
// this method solves the linear equation l * l' * x = b, where L is the
// cholesky decomposition matrix and b is an input vector.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::choleskySolve(MVector<TScalar, TIntegral>& out_vec_a,
				const MMatrix<TScalar, TIntegral>& l_a,
				const MVector<TScalar, TIntegral>& in_vec_a) {

  // get the dimensions of input matrix
  //
  int32 nrows = l_a.getNumRows();
  out_vec_a.setLength(nrows);
  
  // solve L * y = in_vec, result is stored in out_vec
  //
  for (int32 i = 0; i < nrows; i++) {

    // declare an accumulator
    //
    TIntegral sum = in_vec_a(i);

    // subtract every previous element
    //
    for (int32 j = i - 1; j >= 0; j--) {
      sum -= (TIntegral)(l_a(i, j)) * out_vec_a(j);
    }

    // output the result
    //
    out_vec_a(i) = (TIntegral) sum / l_a(i,i);
  }

  // solve for the L' * x = y
  //
  for (int32 i = nrows - 1; i >= 0; i--) {

    // declare an accumulator
    //
    TIntegral sum = (TIntegral) out_vec_a(i);

    // subtract every previous element
    //
    for (int32 j = i + 1; j < nrows; j++) {
      sum -= ((TIntegral)(l_a(j, i))) * (TIntegral)out_vec_a(j);
    }

    // output the result
    //
    out_vec_a(i) = (TIntegral) sum / l_a(i, i);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::choleskySolve(MVector<ISIP_TEMPLATE_TARGET>&,
			      const MMatrix<ISIP_TEMPLATE_TARGET>&,
			      const MVector<ISIP_TEMPLATE_TARGET>&);


// method: svdSolve
//
// arguments:
//  MVector<TScalar, TIntegral>& out_vec: (output) output vector
//  const MMatrix<TScalar, TIntegral>& u: (input) row orthonormal
//  const MMatrix<TScalar, TIntegral>& w: (input) singular value matrix
//  const MMatrix<TScalar, TIntegral>& v: (input) column orthonormal
//  const MVector<TScalar, TIntegral>& in_vec: (input) input vector
//  bool8 zero_singulars : (input) if true then near-zero singular values
//                           are ignored
//
// return: a bool8 value indicating status
//
// this method solves the linear equation u * w * transpose(v) * x = b,
// where u and v are orthonormal column matrices and w is the
// singular value matrix. this routine follows the techniques from:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, pp. 61-64, 1995.
//
// Particularly important is equation (2.6.7)
// If zero_singulars is set to false then this routine assumes that the
// near-singular values in the w matrix have already been zeroed.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::svdSolve(MVector<TScalar, TIntegral>& out_vec_a,
				 const MMatrix<TScalar, TIntegral>& u_a,
				 const MMatrix<TScalar, TIntegral>& w_a,
				 const MMatrix<TScalar, TIntegral>& v_a,
				 const MVector<TScalar, TIntegral>& in_vec_a,
				 bool8 zero_singulars_a) {
#ifdef ISIP_TEMPLATE_fp

  // declare local variables.
  //
  int32 rows = u_a.getNumRows();  // the original matrix number of rows
  int32 cols = v_a.getNumRows();  // the original matrix number of columns
  MVector<TScalar, TIntegral> tmp_vec;
  MVector<TScalar, TIntegral> tmp_w; // vector of singular values

  // check dimensions (this is only for economy mode SVD)
  //   u should be rows*cols or rows*rows
  //   w should be cols*cols or rows*rows
  //   v should be cols*cols or cols*rows
  //   in_vec should be a rows-length vector
  //
  if (rows >= cols) {
    if (!w_a.isSquare() || (w_a.getNumRows() != cols) ||
	(u_a.getNumColumns() != cols) || (v_a.getNumColumns() != cols) ||
	(in_vec_a.length() != rows)) {
      u_a.debug(L"u_a");
      v_a.debug(L"v_a");
      in_vec_a.debug(L"in_vec_a");    
      return Error::handle(name(), L"svdSolve", u_a.ERR_DIM, __FILE__,__LINE__);
    }
  }
  else {
    if (!w_a.isSquare() || (w_a.getNumRows() != rows) ||
	(u_a.getNumColumns() != rows) || (v_a.getNumColumns() != rows) ||
	(in_vec_a.length() != rows)) {
      u_a.debug(L"u_a");
      v_a.debug(L"v_a");
      in_vec_a.debug(L"in_vec_a");    
      return Error::handle(name(), L"svdSolve", u_a.ERR_DIM, __FILE__,__LINE__);
    }
  }
  
  
  // zero out near-singular values if requested
  //
  TIntegral wmin = 0.0;
  if (zero_singulars_a) {
    TIntegral wmax = w_a.max();
    wmin = wmax * Integral::max(rows, cols) * w_a.THRESH_SINGULAR;
  }

  // compute the inverse of the singular values for all that are non-zero
  //
  int32 min_dimension = (rows < cols) ? rows : cols;
  tmp_w.assign((int32)min_dimension, (TIntegral)0.0);
  for (int32 i = 0; i < min_dimension; i++) {
    if (w_a(i, i) > wmin) {
      tmp_w(i) = 1.0 / w_a(i, i);
    }
  }

  // compute transpose(U) * b from equation (2.6.7)
  //  note that only those columns of U which correspond to non-zero
  //  entries in the w matrix are used. also note that the outer loop
  //  is over the columns of U not the rows.
  //
  tmp_vec.assign(min_dimension, (TIntegral)0.0);
  for (int32 j = 0; j < min_dimension; j++) {
    if (tmp_w(j) != (TIntegral)0.0) {
      for (int32 i = 0; i < rows; i++) {
	tmp_vec(j) += u_a(i, j) * in_vec_a(i);
      }
      tmp_vec(j) *= tmp_w(j);
    }
  }

  // multiply v by the temporary vector to get the final result
  //
  v_a.multv(out_vec_a, tmp_vec);

  // exit gracefully
  //
  return true;

  // for matrices other than float32 and float64, return error
  //
#else
  return Error::handle(name(), L"svdSolve", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif

}

// explicit instantiations
//
template bool8
MMatrixMethods::svdSolve(MVector<ISIP_TEMPLATE_TARGET>&,
			 const MMatrix<ISIP_TEMPLATE_TARGET>&,
			 const MMatrix<ISIP_TEMPLATE_TARGET>&,
			 const MMatrix<ISIP_TEMPLATE_TARGET>&,
			 const MVector<ISIP_TEMPLATE_TARGET>&,
			 bool8);
