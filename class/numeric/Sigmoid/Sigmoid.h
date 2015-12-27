// file: $isip/class/numeric/Sigmoid/Sigmoid.h
// version: $Id: Sigmoid.h 8338 2002-07-11 03:35:34Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_SIGMOID
#define ISIP_SIGMOID

// isip include files
//
#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_VECTOR_DOUBLE
#include <VectorDouble.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Sigmoid: a class used to analyze and evaluate sigmoid functions of the form:
//
//                      gain
//      y(x)  =   -------------------------------  + y_offset
//                1 + e^(-slope * (x - x_offset))
//
// Nominally, the gain is 1, the offset is 0 and the slope is 1 which
// produces a function that varies smoothly between 0 and 1. The gain,
// x_offset and y_offset, can be adjusted to control the effective domain
// and range of the output. The slope is not truly the slope of the
// transition region but can be varied to control that slope.
//
class Sigmoid {

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
  // other important constants
  //
  //----------------------------------------

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  static const String PARAM_GAIN;
  static const String PARAM_SLOPE;  
  static const String PARAM_XOFFSET; 
  static const String PARAM_YOFFSET;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  static const float32 DEF_GAIN = 1.0;
  static const float32 DEF_SLOPE = 1.0;
  static const float32 DEF_XOFFSET = 0.0;
  static const float32 DEF_YOFFSET = 0.0;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 35000;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // parameters of the functional sigmoid form
  //
  Float gain_d;
  Float slope_d;
  Float xoffset_d;
  Float yoffset_d;  

  // a static debug level
  //
  static Integral::DEBUG debug_level_d;
  
  // a static memory manager
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
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }
  
  // other debug methods
  //
  bool8 debug(const unichar* msg) const;

  // method: destructor
  //
  ~Sigmoid() {}
  
  // method: default constructor
  //
  Sigmoid(float32 gain = DEF_GAIN, float32 slope = DEF_SLOPE,
	  float32 xoffset = DEF_XOFFSET, float32 yoffset = DEF_YOFFSET) {
    gain_d = gain;
    slope_d = slope;
    xoffset_d = xoffset;
    yoffset_d = yoffset;
  }

  // method: copy constructor
  //
  Sigmoid(const Sigmoid& arg) {
    assign(arg);
  }
  
  // method: assign
  //
  bool8 assign(const Sigmoid& arg) {
    gain_d = arg.gain_d;
    slope_d = arg.slope_d;
    xoffset_d = arg.xoffset_d;
    yoffset_d = arg.yoffset_d;
    return true;
  }

  // method: operator=
  //
  Sigmoid& operator= (const Sigmoid& arg) {
    assign(arg);
    return *this;
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return (gain_d.sofSize() + slope_d.sofSize() + xoffset_d.sofSize() +
	    yoffset_d.sofSize());
  }
  
  // other i/o methods
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME);
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
                   int32 size = SofParser::FULL_OBJECT,
                   bool8 param = true,
                   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& name = DEF_PARAM) const;

  // method: eq
  //
  bool8 eq(const Sigmoid& arg) const {
    return(gain_d.eq(arg.gain_d) && slope_d.eq(arg.slope_d) &&
	   xoffset_d.eq(arg.xoffset_d) && yoffset_d.eq(arg.yoffset_d));
  }

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

  // method: clear
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE) {
    if (cmode != Integral::RETAIN) {
      gain_d = DEF_GAIN;
      slope_d = DEF_SLOPE;
      xoffset_d = DEF_XOFFSET;
      yoffset_d = DEF_YOFFSET;
    }
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set methods
  //
  //---------------------------------------------------------------------------
 
  // method: setGain
  //
  bool8 setGain(float32 gain) {
    gain_d = gain;
    return true;  
  }
  
  // method: setSlope
  //
  bool8 setSlope(float32 slope) {
    slope_d = slope;
    return true;  
  }
  
  // method: setXOffset
  //
  bool8 setXOffset(float32 xoffset) {
    xoffset_d = xoffset;
    return true;  
  }
  
  // method: setYOffset
  //
  bool8 setYOffset(float32 yoffset) {
    yoffset_d = yoffset;
    return true;  
  }
  
  // method: set
  //
  bool8 set(float32 gain, float32 slope, float32 xoffset, float32 yoffset) {
    gain_d = gain;
    slope_d = slope;
    xoffset_d = xoffset;
    yoffset_d = yoffset;
    return true;  
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods
  //
  //---------------------------------------------------------------------------
 
  // method: getGain
  //
  float32 getGain() {
    return gain_d;
  }
  
  // method: getSlope
  //
  float32 getSlope() {
    return slope_d;
  }
  
  // method: getXOffset
  //
  float32 getXOffset() {
    return xoffset_d;
  }
  
  // method: getYOffset
  //
  float32 getYOffset() {
    return yoffset_d;
  }
  
  // method: get
  //
  bool8 get(float32& gain, float32& slope, float32& xoffset, float32& yoffset) {
    gain = gain_d;
    slope = slope_d;
    xoffset = xoffset_d;
    yoffset = yoffset_d;
    return true;  
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  computational methods
  //  all of these methods are defined for float64 and float32 types
  //
  //---------------------------------------------------------------------------

  // method: compute
  //  the vector method gives y[i] = sigmoid(x[i])
  //
  bool8 compute(float32& y, float32 x) const {
    return computeScalar<float32>(y, x);
  }

  // method: compute
  //
  bool8 compute(float64& y, const float64 x) const {
    return computeScalar<float64>(y, x);
  }

  // method: compute
  //
  bool8 compute(VectorFloat& y, const VectorFloat& x) const {
    return computeVector<VectorFloat, float32>(y, x);
  }

  // method: compute
  //
  bool8 compute(VectorDouble& y, const VectorDouble& x) const {
    return computeVector<VectorDouble, float64>(y, x);
  }

  // method: derivative
  //  derivative = the derivative with respect to (w.r.t.) x, evaluated at x
  //
  bool8 derivative(float32& dydx, float32 x) const {
    return derivativeScalar<float32>(dydx, x);
  }

  // method: derivative
  //  derivative = the derivative with respect to (w.r.t.) x, evaluated at x
  //
  bool8 derivative(float64& dydx, const float64 x) const {
    return derivativeScalar<float64>(dydx, x);
  }

  // method: derivative
  //  derivative = the derivative with respect to (w.r.t.) x, evaluated at x
  //
  bool8 derivative(VectorFloat& dydx, const VectorFloat& x) const {
    return derivativeVector<VectorFloat, float32>(dydx, x);
  }

  // method: derivative
  //  derivative = the derivative with respect to (w.r.t.) x, evaluated at x
  //
  bool8 derivative(VectorDouble& dydx, const VectorDouble& x) const {
    return derivativeVector<VectorDouble, float64>(dydx, x);
  }

  // method: derivativeGain
  //  derivativeGain = the derivative w.r.t. the gain, evaluated at x
  //
  bool8 derivativeGain(float32& dydgain, float32 x) const {
    return derivativeGainScalar<float32>(dydgain, x);
  }

  // method: derivativeGain
  //  derivativeGain = the derivative w.r.t. the gain, evaluated at x
  //
  bool8 derivativeGain(float64& dydgain, const float64 x) const {
    return derivativeGainScalar<float64>(dydgain, x);
  }

  // method: derivativeGain
  //  derivativeGain = the derivative w.r.t. the gain, evaluated at x
  //
  bool8 derivativeGain(VectorFloat& dydgain,
			 const VectorFloat& x) const {
    return derivativeGainVector<VectorFloat, float32>(dydgain, x);
  }

  // method: derivativeGain
  //  derivativeGain = the derivative w.r.t. the gain, evaluated at x
  //
  bool8 derivativeGain(VectorDouble& dydgain,
			 const VectorDouble& x) const {
    return derivativeGainVector<VectorDouble, float64>(dydgain, x);
  }

  // method: derivativeSlope
  //  derivativeSlope = the derivative w.r.t. the slope, evaluated at x
  //
  bool8 derivativeSlope(float32& dydslope, float32 x) const {
    return derivativeSlopeScalar<float32>(dydslope, x);
  }

  // method: derivativeSlope
  //  derivativeSlope = the derivative w.r.t. the slope, evaluated at x
  //
  bool8 derivativeSlope(float64& dydslope, const float64 x) const {
    return derivativeSlopeScalar<float64>(dydslope, x);
  }

  // method: derivativeSlope
  //  derivativeSlope = the derivative w.r.t. the slope, evaluated at x
  //
  bool8 derivativeSlope(VectorFloat& dydslope,
			  const VectorFloat& x) const {
    return derivativeSlopeVector<VectorFloat, float32>(dydslope, x);
  }

  // method: derivativeSlope
  //  derivativeSlope = the derivative w.r.t. the slope, evaluated at x
  //
  bool8 derivativeSlope(VectorDouble& dydslope,
			  const VectorDouble& x) const {
    return derivativeSlopeVector<VectorDouble, float64>(dydslope, x);
  }

  // method: derivativeXOffset
  //  derivativeXOffset = the derivative w.r.t. the xoffset, evaluated at x
  //
  bool8 derivativeXOffset(float32& dydxoffset, float32 x) const {
    return derivativeXOffsetScalar<float32>(dydxoffset, x);
  }

  // method: derivativeXOffset
  //  derivativeXOffset = the derivative w.r.t. the xoffset, evaluated at x
  //
  bool8 derivativeXOffset(float64& dydxoffset, const float64 x) const {
    return derivativeXOffsetScalar<float64>(dydxoffset, x);
  }

  // method: derivativeXOffset
  //  derivativeXOffset = the derivative w.r.t. the xoffset, evaluated at x
  //
  bool8 derivativeXOffset(VectorFloat& dydxoffset,
			    const VectorFloat& x) const {
    return derivativeXOffsetVector<VectorFloat, float32>(dydxoffset, x);
  }
  
  // method: derivativeXOffset
  //  derivativeXOffset = the derivative w.r.t. the xoffset, evaluated at x
  //
  bool8 derivativeXOffset(VectorDouble& dydxoffset,
			    const VectorDouble& x) const {
    return derivativeXOffsetVector<VectorDouble, float64>(dydxoffset, x);
  }
  
  // method: derivativeYOffset
  //  derivativeYOffset = the derivative w.r.t. the yoffset, evaluated at x
  //
  bool8 derivativeYOffset(float32& dydyoffset, float32 x) const {
    return derivativeYOffsetScalar<float32>(dydyoffset, x);
  }

  // method: derivativeYOffset
  //  derivativeYOffset = the derivative w.r.t. the yoffset, evaluated at x
  //
  bool8 derivativeYOffset(float64& dydyoffset, const float64 x) const {
    return derivativeYOffsetScalar<float64>(dydyoffset, x);
  }

  // method: derivativeYOffset
  //  derivativeYOffset = the derivative w.r.t. the yoffset, evaluated at x
  //
  bool8 derivativeYOffset(VectorFloat& dydyoffset,
			    const VectorFloat& x) const {
    return derivativeYOffsetVector<VectorFloat, float32>(dydyoffset, x);
  }
  
  // method: derivativeYOffset
  //  derivativeYOffset = the derivative w.r.t. the yoffset, evaluated at x
  //
  bool8 derivativeYOffset(VectorDouble& dydyoffset,
			    const VectorDouble& x) const {
    return derivativeYOffsetVector<VectorDouble, float64>(dydyoffset, x);
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // templatized computation methods
  //
  template <class TIntegral>
  bool8 computeScalar(TIntegral& y, const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 computeVector(TVector& y, const TVector& x) const;  

  template <class TIntegral>
  bool8 derivativeScalar(TIntegral& dydx, const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 derivativeVector(TVector& dydx, const TVector& x) const;

  template <class TIntegral>
  bool8 derivativeGainScalar(TIntegral& dydgain, const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 derivativeGainVector(TVector& dydgain, const TVector& x) const;

  template <class TIntegral>
  bool8 derivativeSlopeScalar(TIntegral& dydslope, const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 derivativeSlopeVector(TVector& dydslope, const TVector& x) const;

  template <class TIntegral>
  bool8 derivativeXOffsetScalar(TIntegral& dydxoffset,
				  const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 derivativeXOffsetVector(TVector& dydxoffset, const TVector& x) const;
  
  template <class TIntegral>
  bool8 derivativeYOffsetScalar(TIntegral& dydyoffset,
				  const TIntegral x) const;

  template <class TVector, class TIntegral>
  bool8 derivativeYOffsetVector(TVector& dydyoffset, const TVector& x) const;
  
};

// end of include file
// 
#endif



