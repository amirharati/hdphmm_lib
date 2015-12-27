// file: $isip/class/math/matrix/MatrixComplexLong/MatrixComplexLong.h
// version: $Id: MatrixComplexLong.h 7291 2001-08-09 02:21:35Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_MATRIX_COMPLEX_FLOAT
#define ISIP_MATRIX_COMPLEX_FLOAT

// isip include files
//
#ifndef ISIP_MMATRIX
#include <MMatrix.h>
#endif

// MatrixComplexLong: this is a matrix of ComplexLong objects, which inherits
// the matrix template class.
//
class MatrixComplexLong : public MMatrix<ComplexLong, complexlong> {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default arguments to methods
  //
  
  // define the default value(s) of the class data
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 25200;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // static memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
 
  // method: name
  //
  static const String& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);

  // setDebug methods:
  //  these methods are inherited from the MMatrix template class
  //
  
  // method: debug
  //
  bool8 debug(const unichar* msg) const {
    return MMatrix<ComplexLong, complexlong>::debug(name(), &msg[0]);
  }

  // method: destructor
  //  the destructor does not do anything here since it inherits the
  //  destructor from the MMatrix template class
  //
  ~MatrixComplexLong() {}

  // method: default constructor
  //  
  MatrixComplexLong(int32 nrows = DEF_SIZE, int32 ncols = DEF_SIZE, 
		     Integral::MTYPE type = Integral::DEF_MTYPE):
    MMatrix<ComplexLong, complexlong>(nrows, ncols, type) {
  }

  // method: copy constructor
  //  
  MatrixComplexLong(const MatrixComplexLong& arg):
    MMatrix<ComplexLong, complexlong>(arg) {
  }

  // assign methods:
  //  these methods are inherited from the MMatrix template class  
  //

  // method: operator=
  //
  MatrixComplexLong& operator=(const MatrixComplexLong& matrix) {
    assign(matrix);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData and writeData methods are inherited from
  //  the MMatrix template class
  //

  // method: read
  //  
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MMatrix<ComplexLong, complexlong>::read(sof, tag, name);
  }

  // method: write
  //    
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MMatrix<ComplexLong, complexlong>::write(sof, tag, name);
  }

  // equality methods:
  //  these methods are inherited from the MMatrix template class
  //

  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }

  // method: setGrowSize
  //
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  // other memory management methods:
  //  the clear method is inherited from the MMatrix template class
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //  this method constructs a matrix with a unichar* object
  //  
  MatrixComplexLong(int32 nrows, int32 ncols, const unichar* str, 
		     Integral::MTYPE type = Integral::DEF_MTYPE,
		     const Char delim = DEF_DELIM) {
    assign(nrows, ncols, str, type, delim);
  }    
  
  // method: operator=
  //  this method assigns a complexlong value to the matrix  
  //
  MatrixComplexLong& operator=(complexlong value) {
    assign(value);
    return *this;
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
};

// end of include file
//
#endif
