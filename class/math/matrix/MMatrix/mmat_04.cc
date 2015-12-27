// file: $isip/class/math/matrix/MMatrix/mmat_04.cc
// version: $Id: mmat_04.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"
#include <Console.h>

// method: write
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method writes the matrix object to an Sof file
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::write(const MMatrix<TScalar, TIntegral>& this_a, 
			      Sof& sof_a, int32 tag_a, const String& name_a) {

  // declare local variable
  //
  int32 obj_size = 0;
  
  // write the instance of the object into the Sof file
  //
  if (sof_a.isText()) {

    // set the size to be dynamic
    //
    obj_size = Sof::ANY_SIZE;
  }
  else {

    // set the size to be the size of the object written to the Sof file
    //
    obj_size = this_a.sofSize();
  }

  // write the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }
  
  // exit gracefully
  //
  return this_a.writeData(sof_a, MMatrix<ISIP_TEMPLATE_TARGET>::DEF_PARAM);
}

// explicit instantiations
//
template bool8
MMatrixMethods::write<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, Sof&, int32, const String&);

// method: writeData
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: a bool8 value indicating status
//
// this method writes the object to an Sof file. it assumes that the
// Sof file is already positioned correctly.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::writeData(const MMatrix<TScalar, TIntegral>& this_a, 
				  Sof& sof_a, const String& pname_a) {

  // write a start string if necessary
  //
  sof_a.writeLabelPrefix(pname_a);

  // write the type - for text file, type will be written as string
  //
  if (!this_a.TYPE_MAP.writeElementData(sof_a,
			     MMatrix<TScalar, TIntegral>::PARAM_TYPE,
					(int32)this_a.type_d)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"writeData", Error::IO, 
			 __FILE__, __LINE__);
  }
  
  // write the number of rows
  //
  if (!this_a.nrows_d.writeData(sof_a, 
				MMatrix<TScalar, TIntegral>::PARAM_NROWS)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"writeData", Error::IO, 
			 __FILE__, __LINE__);
  }
  
  // write the number of columns
  //        
  if (!this_a.ncols_d.writeData(sof_a, 
				MMatrix<TScalar, TIntegral>::PARAM_NCOLS)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"writeData", Error::IO, 
			 __FILE__, __LINE__);
  }
          
  // write out the elements of the matrix - in case of diagonal matrix, just
  // write the diagonal elements, in case of symmetric and lower triangle
  // matrix, write the elements in the lower triangle only, in case of upper
  // triangle, write the elements in the upper triangle and in case of sparse,
  // only write the non-zero elements
  //
  if (!this_a.m_d.writeData(sof_a, 
				MMatrix<TScalar, TIntegral>::PARAM_DATA)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"writeData", Error::IO, 
			 __FILE__, __LINE__);
  }

  // in case of sparse matrix, write the row and column indices of
  // non-zero elements also
  //  
  else if (this_a.type_d == Integral::SPARSE) {

    // write the row indices of the non-zero elements of the matrix
    //
    if (!this_a.row_index_d.writeData(sof_a,
				      MMatrix<TScalar, TIntegral>::
				      PARAM_ROW_IND)) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"writeData", Error::IO, 
                           __FILE__, __LINE__);
    }

    // write the column indices of the non-zero elements of the matrix
    //    
    if (!this_a.col_index_d.writeData(sof_a, 
				      MMatrix<TScalar, TIntegral>::
				      PARAM_COL_IND)) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"writeData", Error::IO, 
                           __FILE__, __LINE__);
    }
  }

  // write an end string if necessary
  //
  sof_a.writeLabelSuffix(pname_a);
  
  // exit gracefully
  //
   return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::writeData<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, Sof&, const String&);

// method: sofSize
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: size of object
//
// this method returns the size of the object in the Sof file and is
// used for binary write
//
template<class TScalar, class TIntegral>
int32 MMatrixMethods::sofSize(const MMatrix<TScalar, TIntegral>& this_a) {

  // start with enough space for the type
  //
  int32 bytes = this_a.TYPE_MAP.elementSofSize();

  // add space for value vector, number of rows and columns
  //
  bytes += this_a.nrows_d.sofSize();
  bytes += this_a.ncols_d.sofSize();
  bytes += this_a.m_d.sofSize();
  
  // if the current is sparse, then add the space for vectors containing
  // row and column indices
  //
  if (this_a.type_d == Integral::SPARSE) {
    bytes += this_a.row_index_d.sofSize();
    bytes += this_a.col_index_d.sofSize();
  }

  // return the size
  //
  return bytes;   
}

// explicit instantiations
//
template int32
MMatrixMethods::sofSize<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);
