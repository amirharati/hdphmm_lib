// file: $isip/class/math/matrix/MatrixComplexDouble/MatrixComplexDouble.h
// version: $Id: MatrixComplexDouble.h 7256 2001-07-29 21:45:30Z jelinek $
//

// make sure definitions are only made once
//
#ifndef ISIP_MATRIX_COMPLEX_DOUBLE
#define ISIP_MATRIX_COMPLEX_DOUBLE

// isip include files
//
#ifndef ISIP_MMATRIX
#include <MMatrix.h>
#endif

// MatrixComplexDouble: this is a matrix of ComplexDouble objects,
// which inherits the matrix template class.
//
class MatrixComplexDouble : public MMatrix<ComplexDouble, complexdouble> {

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

  static const int32 ERR = 25000;

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
    return MMatrix<ComplexDouble, complexdouble>::debug(name(), &msg[0]);
  }

  // method: destructor
  //  the destructor does not do anything here since it inherits the
  //  destructor from the MMatrix template class
  //
  ~MatrixComplexDouble() {}

  // method: default constructor
  //  
  MatrixComplexDouble(int32 nrows = DEF_SIZE, int32 ncols = DEF_SIZE, 
		     Integral::MTYPE type = Integral::DEF_MTYPE):
    MMatrix<ComplexDouble, complexdouble>(nrows, ncols, type) {
  }

  // method: copy constructor
  //  
  MatrixComplexDouble(const MatrixComplexDouble& arg):
    MMatrix<ComplexDouble, complexdouble>(arg) {
  }

  // assign methods:
  //  these methods are inherited from the MMatrix template class  
  //

  // method: operator=
  //
  MatrixComplexDouble& operator=(const MatrixComplexDouble& matrix) {
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
    return MMatrix<ComplexDouble, complexdouble>::read(sof, tag, name);
  }

  // method: write
  //    
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MMatrix<ComplexDouble, complexdouble>::write(sof, tag, name);
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
  MatrixComplexDouble(int32 nrows, int32 ncols, const unichar* str, 
		     Integral::MTYPE type = Integral::DEF_MTYPE,
		     const Char delim = DEF_DELIM) {
    assign(nrows, ncols, str, type, delim);
  }    
  
  // method: operator=
  //  this method assigns a complexdouble value to the matrix  
  //
  MatrixComplexDouble& operator=(complexdouble value) {
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
