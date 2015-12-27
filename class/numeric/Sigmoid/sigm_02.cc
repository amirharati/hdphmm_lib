// file: $isip/class/numeric/Sigmoid/sigm_02.cc
// version: $Id: sigm_02.cc 7473 2001-11-13 15:30:23Z gao $
//

// isip include files
//
#include "Sigmoid.h"
#include <MatrixFloat.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Sigmoid::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // do a quick test of constructors, destructors, and memory management
  // methods
  //
  Sigmoid::setGrowSize(5);
  Sigmoid* sig0 = new Sigmoid;
  Sigmoid* sig1 = new Sigmoid(1.5);
  Sigmoid* sig2 = new Sigmoid(1.5, 2.5);
  Sigmoid* sig3 = new Sigmoid(1.5, 2.5, 3.5);
  Sigmoid* sig3a = new Sigmoid(1.5, 2.5, 3.5, 4.5);
  Sigmoid* sig4 = new Sigmoid[10];

  // clear pointers
  //
  delete sig0;
  delete [] sig4;

  // verify that the constructors worked
  //
  if ((sig1->gain_d != (Float)1.5) || (sig1->slope_d != (Float)DEF_SLOPE) ||
      (sig1->xoffset_d != (Float)DEF_XOFFSET) ||
      (sig1->yoffset_d != (Float)DEF_YOFFSET)) {
    sig1->debug(L"sig1");
    return Error::handle(name(), L"constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  if ((sig2->gain_d != (Float)1.5) || (sig2->slope_d != (Float)2.5) ||
      (sig2->xoffset_d != DEF_XOFFSET) || (sig2->yoffset_d != DEF_YOFFSET)) {
    sig2->debug(L"sig2");
    return Error::handle(name(), L"constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  if ((sig3->gain_d != (Float)1.5) || (sig3->slope_d != (Float)2.5) ||
      (sig3->xoffset_d != (Float)3.5) ||
      (sig3->yoffset_d != (Float)DEF_YOFFSET)) {
    sig3->debug(L"sig3");
    return Error::handle(name(), L"constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  if ((sig3a->gain_d != (Float)1.5) || (sig3a->slope_d != (Float)2.5) ||
      (sig3a->xoffset_d != (Float)3.5) || (sig3a->yoffset_d != (Float)4.5)) {
    sig3a->debug(L"sig3a");
    return Error::handle(name(), L"constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the setDebug method
  //
  setDebug(debug_level_d);
  
  // test the copy constructor, assign, and eq methods
  //
  delete sig1;
  delete sig2;
  sig1 = new Sigmoid(*sig3a);
  sig2 = new Sigmoid;
  sig2->assign(*sig3a);

  if ((sig1->gain_d != (Float)1.5) || (sig1->slope_d != (Float)2.5) ||
      (sig1->xoffset_d != (Float)3.5) || (sig1->yoffset_d != (Float)4.5)) {
    sig1->debug(L"sig1");
    return Error::handle(name(), L"copy constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  if ((sig2->gain_d != (Float)1.5) || (sig2->slope_d != (Float)2.5) ||
      (sig2->xoffset_d != (Float)3.5) || (sig2->yoffset_d != (Float)4.5)) {
    sig2->debug(L"sig2");
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  if (!sig2->eq(*sig3a)) {
    sig2->debug(L"sig2");
    sig3a->debug(L"sig3a");
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test the clear method
  //
  delete sig1;
  sig1 = new Sigmoid;
  sig2->clear();
  if (!sig2->eq(*sig1)) {
    sig1->debug(L"sig1");
    sig2->debug(L"sig2");
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }

  // test the operator= method
  //
  *sig2 = *sig3a;
  if (!sig2->eq(*sig3a)) {
    sig2->debug(L"sig2");
    sig3a->debug(L"sig3a");
    return Error::handle(name(), L"operator=", Error::TEST, __FILE__,__LINE__);
  }

  // clear the pointers
  //
  delete sig1;
  delete sig2;
  delete sig3;
  delete sig3a;  

  // test i/o methods
  //
  Sigmoid sig5(1.7, -1.3, 4.5, 9.0);
  Sigmoid sig6(2.9, -13.3, 95.3, 9.0);  

  // we need binary and text sof files
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  String tmp_filename1;
  Integral::makeTemp(tmp_filename1);

  // open files in write mode
  //
  Sof tmp_file0;
  tmp_file0.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof tmp_file1;
  tmp_file1.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);

  sig5.write(tmp_file0, 0);
  sig6.write(tmp_file0, 1);

  sig5.write(tmp_file1, 0);
  sig6.write(tmp_file1, 1);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the sigmoids from the text file
  //
  Sigmoid sig7;
  Sigmoid sig8;
  sig7.read(tmp_file0, 0);
  sig8.read(tmp_file0, 1);

  if (!sig7.eq(sig5) || !sig8.eq(sig6)) {
    sig5.debug(L"sig5");
    sig6.debug(L"sig6");
    sig7.debug(L"sig7");
    sig8.debug(L"sig8");
    return Error::handle(name(), L"read/write text", Error::TEST,
			 __FILE__, __LINE__);
  }

  // read the sigmoids from the binary file
  //
  sig7.clear();
  sig8.clear();
  sig7.read(tmp_file1, 0);
  sig8.read(tmp_file1, 1);

  if (!sig7.eq(sig5) || !sig8.eq(sig6)) {
    sig5.debug(L"sig5");
    sig6.debug(L"sig6");
    sig7.debug(L"sig7");
    sig8.debug(L"sig8");
    return Error::handle(name(), L"read/write binary", Error::TEST,
			 __FILE__, __LINE__);
  }

  // close and  delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     set/get methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: set/get methods...\n");
    Console::increaseIndention();
  }

  // test the parameter set methods
  //
  sig5.setGain(-4.9);
  sig5.setSlope(3.7);
  sig5.setXOffset(-2.1);
  sig5.setYOffset(14.3);
  sig6.set(-4.9, 3.7, -2.1, 14.3);

  if ((sig5.gain_d != (float32)-4.9) ||
      (sig5.slope_d != (float32)3.7) ||
      (sig5.xoffset_d != (float32)-2.1) ||
      (sig5.yoffset_d != (float32)14.3) ||
      !sig5.eq(sig6)) {
    sig5.debug(L"sig5");
    sig6.debug(L"sig6");
    return Error::handle(name(), L"set methods", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the parameter get methods
  //
  if ((sig5.getGain() != (float32)-4.9) || (sig5.getSlope() != (float32)3.7) ||
      (sig5.getXOffset() != (float32)-2.1) ||
      (sig5.getYOffset() != (float32)14.3)) {
    sig5.debug(L"sig5");
    return Error::handle(name(), L"get methods", Error::TEST,
			 __FILE__, __LINE__);
  }

  float32 tmp_gain = 0;
  float32 tmp_slope = 0;
  float32 tmp_xoffset = 0;
  float32 tmp_yoffset = 0;

  sig5.get(tmp_gain, tmp_slope, tmp_xoffset, tmp_yoffset);
  if ((tmp_gain != (float32)-4.9) || (tmp_slope != (float32)3.7) ||
      (tmp_xoffset != (float32)-2.1) || (tmp_yoffset != (float32)14.3)) {
    sig5.debug(L"sig5");
    return Error::handle(name(), L"get method", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     computation methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: computation methods...\n");
    Console::increaseIndention();
  }

  // create value vectors for testing
  //
  VectorFloat gains(L"1, -5, 10");
  VectorFloat slopes(L"1, -5, 10");
  VectorFloat xoffsets(L"0, -1, 5");
  VectorFloat yoffsets(L"0, -1, 5");
  VectorFloat inputs(L"0, -1.3, 17");
  VectorFloat outputs;
  VectorFloat expected_values;
  
  int32 num_inputs = inputs.length();
  int32 num_configurations = gains.length();

  MatrixFloat expect(num_configurations, num_inputs,
		     L"0.500000, 0.214165, 0.999999, -1.033464, -5.087872, -1.000000, 5.000000, 5.000000, 15.000000", Integral::FULL);
  MatrixFloat expectdydx(num_configurations, num_inputs,
                         L"0.250000, 0.168298, 4.139937e-08, 0.166201, 3.728661, 2.048503e-38, 1.928749e-20, 4.359610e-26, 7.667648e-72", Integral::FULL);
  MatrixFloat expectdydgain(num_configurations, num_inputs,
			     L"0.500000, 0.214165, 0.999999, 0.006693, 0.817574, 8.194013e-40, 1.928749e-22, 4.359610e-28, 1.000000", Integral::FULL);  
  MatrixFloat expectdydslope(num_configurations, num_inputs,
			     L"0.000000, -0.218788, 7.037894e-07, -0.0332403, 0.22371968, -7.374611e-38, 0.000000, -5.667493e-27, 1.303500e-50", Integral::FULL);
  MatrixFloat expectdydxoffset(num_configurations, num_inputs,
			       L"-0.250000, -0.168298, -4.139937e-08, -0.166201, -3.728661, -2.048503e-38, -9.643749e-21, -2.746554e-26, 9.2011777e-51", Integral::FULL);
  MatrixFloat expectdydyoffset(num_configurations, num_inputs,
			       L"1, 1, 1, 1, 1, 1, 1, 1, 1", Integral::FULL);
  
  // loop over sigmoid configurations, the vector compute calls internally
  // call the base methods except for derivativeOffset
  //
  Sigmoid sig_test;
  for (int32 j = 0; j < num_configurations; j++) {

    sig_test.set(gains(j), slopes(j), xoffsets(j), yoffsets(j));

    // compute the sigmoid
    //
    sig_test.compute(outputs, inputs);
    expect.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
    }

    // compute dy/dx
    //
    sig_test.derivative(outputs, inputs);
    expectdydx.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"derivative", Error::TEST, __FILE__, __LINE__);
    }

    // compute dy/dgain
    //
    sig_test.derivativeGain(outputs, inputs);
    expectdydgain.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"derivativeGain", Error::TEST, __FILE__,
		    __LINE__);
    }

    // compute dy/dslope
    //
    sig_test.derivativeSlope(outputs, inputs);
    expectdydslope.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"derivativeSlope", Error::TEST, __FILE__,
		    __LINE__);
    }

    // compute dy/dxoffset
    //
    sig_test.derivativeXOffset(outputs, inputs);
    expectdydxoffset.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"derivativeXOffset", Error::TEST, __FILE__,
		    __LINE__);
    }

    // compute dy/doffset
    //
    sig_test.derivativeYOffset(outputs, inputs);
    expectdydyoffset.getRow(expected_values, j);
    if (!outputs.almostEqual(expected_values)) {
      outputs.debug(L"actual");
      expected_values.debug(L"expected");
      Error::handle(name(), L"derivativeYOffset", Error::TEST, __FILE__,
		    __LINE__);
    }
  }

  // test the single value derivativeOffset method
  //
  float32 actual_tmp = 0;
  sig_test.derivativeYOffset(actual_tmp, (float32)inputs(0));
  if (!Integral::almostEqual(actual_tmp, 1)) {
      Error::handle(name(), L"derivativeOffset", Error::TEST, __FILE__,
		    __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}
