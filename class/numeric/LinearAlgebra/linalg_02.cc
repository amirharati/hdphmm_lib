// file: $isip/class/numeric/LinearAlgebra/linalg_02.cc
// version: $Id: linalg_02.cc 7333 2001-08-27 20:22:06Z hamaker $
//

// isip include files
//
#include "LinearAlgebra.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 LinearAlgebra::diagnose(Integral::DEBUG level_a) {

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
  LinearAlgebra::setGrowSize(5);
  LinearAlgebra* linalg0 = new LinearAlgebra;
  LinearAlgebra* linalg1 = new LinearAlgebra(*linalg0);
  LinearAlgebra* linalg2 = new LinearAlgebra[10];

  // clear pointers
  //
  delete [] linalg2;

  // test the setDebug method
  //
  setDebug(debug_level_d);
  
  // test the eq method
  //
  delete linalg1;
  linalg1 = new LinearAlgebra;
  linalg2 = new LinearAlgebra(*linalg1);

  if (!linalg2->eq(*linalg1)) {
    linalg2->debug(L"linalg2");
    linalg1->debug(L"linalg1");
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test the clear method
  //
  delete linalg1;
  linalg1 = new LinearAlgebra;
  linalg2->clear();
  if (!linalg2->eq(*linalg1)) {
    linalg2->debug(L"linalg2");
    linalg1->debug(L"linalg1");
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }

  // test the operator= method
  //
  *linalg1 = *linalg0;
  if (!linalg2->eq(*linalg0)) {
    linalg2->debug(L"linalg2");
    linalg1->debug(L"linalg1");
    return Error::handle(name(), L"operator=", Error::TEST, __FILE__,__LINE__);
  }

  // clear the pointers
  //
  delete linalg0;
  delete linalg1;
  delete linalg2;

  // test i/o methods
  //
  LinearAlgebra linalg5;
  LinearAlgebra linalg6;

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

  linalg5.write(tmp_file0, 0);
  linalg6.write(tmp_file0, 1);

  linalg5.write(tmp_file1, 0);
  linalg6.write(tmp_file1, 1);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the LinearAlgebras from the text file
  //
  LinearAlgebra linalg7;
  LinearAlgebra linalg8;
  linalg7.read(tmp_file0, 0);
  linalg8.read(tmp_file0, 1);

  if (!linalg7.eq(linalg5) || !linalg8.eq(linalg6)) {
    linalg5.debug(L"linalg5");
    linalg6.debug(L"linalg6");
    linalg7.debug(L"linalg7");
    linalg8.debug(L"linalg8");
    return Error::handle(name(), L"read/write text", Error::TEST,
			 __FILE__, __LINE__);
  }

  // read the LinearAlgebras from the binary file
  //
  linalg7.clear();
  linalg8.clear();
  linalg7.read(tmp_file1, 0);
  linalg8.read(tmp_file1, 1);

  if (!linalg7.eq(linalg5) || !linalg8.eq(linalg6)) {
    linalg5.debug(L"linalg5");
    linalg6.debug(L"linalg6");
    linalg7.debug(L"linalg7");
    linalg8.debug(L"linalg8");
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
  //     linear solver methods (square matrix)
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: linear solver methods for square matrices...\n");
    Console::increaseIndention();
  }

  // declare a multiplier matrix (10x10)
  //
  MatrixFloat A_fl(10, 10, L"0.58279168156123,0.20906940443842,0.41537486044322,0.21396333159617,0.68333232433848,0.45142482676248,0.60854036122399,0.08407906075044,0.12104711303641,0.23189431811233,0.42349625685105,0.37981837035079,0.30499867700349,0.64349228788535,0.21255986433874,0.04389532534714,0.01575981791975,0.45435514975555,0.45075394097939,0.2393125644689,0.51551175214076,0.78332864986771,0.87436717158763,0.32003557746650,0.83923824033620,0.02718512299667,0.01635493355000,0.44182829690634,0.71588294817297,0.04975448407125,0.33395147997176,0.68084575139723,0.01500949867662,0.96009860036901,0.62878460002407,0.31268504808015,0.19007458907973,0.35325045500069,0.89284160814575,0.07838407477005,0.43290659610673,0.46109512665670,0.76795039001114,0.72663176664190,0.13377274847343,0.01286257467300,0.58691847188467,0.15360636252349,0.27310247022514,0.64081540987002,0.22594986814445,0.56782871242883,0.97084493925562,0.41195320816864,0.20713272964136,0.38396728849430,0.05758108987829,0.67564464963341,0.25476929556228,0.19088657039756,0.57980687324960,0.79421065137261,0.99008259261306,0.74456578310616,0.60719894453953,0.68311596780460,0.36756803882634,0.69921332774126,0.86560347774475,0.84386949887436,0.76036500980434,0.05918259347107,0.78886169223375,0.26794725070937,0.62988784884231,0.09284246174092,0.63145116474444,0.72750912921793,0.23235037062753,0.17390024846178,0.52982311671607,0.60286908566699,0.43865853377091,0.43992430956534,0.37047682605190,0.03533832396916,0.71763442146570,0.47838438095666,0.80487174411571,0.17079281374168,0.64052649898984,0.05026880374687,0.49831130344848,0.93338010818959,0.57514777904747,0.61239548137302,0.69266939471779,0.55484198634168,0.90839754344852,0.99429549051392", Integral::FULL);

  MatrixDouble A_doub(10, 10, L"0.58279168156123,0.20906940443842,0.41537486044322,0.21396333159617,0.68333232433848,0.45142482676248,0.60854036122399,0.08407906075044,0.12104711303641,0.23189431811233,0.42349625685105,0.37981837035079,0.30499867700349,0.64349228788535,0.21255986433874,0.04389532534714,0.01575981791975,0.45435514975555,0.45075394097939,0.2393125644689,0.51551175214076,0.78332864986771,0.87436717158763,0.32003557746650,0.83923824033620,0.02718512299667,0.01635493355000,0.44182829690634,0.71588294817297,0.04975448407125,0.33395147997176,0.68084575139723,0.01500949867662,0.96009860036901,0.62878460002407,0.31268504808015,0.19007458907973,0.35325045500069,0.89284160814575,0.07838407477005,0.43290659610673,0.46109512665670,0.76795039001114,0.72663176664190,0.13377274847343,0.01286257467300,0.58691847188467,0.15360636252349,0.27310247022514,0.64081540987002,0.22594986814445,0.56782871242883,0.97084493925562,0.41195320816864,0.20713272964136,0.38396728849430,0.05758108987829,0.67564464963341,0.25476929556228,0.19088657039756,0.57980687324960,0.79421065137261,0.99008259261306,0.74456578310616,0.60719894453953,0.68311596780460,0.36756803882634,0.69921332774126,0.86560347774475,0.84386949887436,0.76036500980434,0.05918259347107,0.78886169223375,0.26794725070937,0.62988784884231,0.09284246174092,0.63145116474444,0.72750912921793,0.23235037062753,0.17390024846178,0.52982311671607,0.60286908566699,0.43865853377091,0.43992430956534,0.37047682605190,0.03533832396916,0.71763442146570,0.47838438095666,0.80487174411571,0.17079281374168,0.64052649898984,0.05026880374687,0.49831130344848,0.93338010818959,0.57514777904747,0.61239548137302,0.69266939471779,0.55484198634168,0.90839754344852,0.99429549051392", Integral::FULL);

  // declare the vector of knowns (10x1)
  VectorFloat b_fl(L"0.93423651891762, 0.26444916614927, 0.16030033919718, 0.87285525701963,0.23788030773557, 0.64583124997499, 0.96688742090893, 0.66493121192534,0.87038102590598, 0.00992730476335 ");
  VectorDouble b_doub(L"0.93423651891762, 0.26444916614927, 0.16030033919718, 0.87285525701963,0.23788030773557, 0.64583124997499, 0.96688742090893, 0.66493121192534,0.87038102590598, 0.00992730476335 ");

  // declare the expected output (10x1)
  VectorFloat expected_x_fl(L"-0.50191278570136,2.46510443988885,-1.85833970101978,-0.47147969983892,0.91032488719446,0.27305443123786,1.20684838083948,2.02022380340132,-2.03776258794210,0.78151547389827 ");
  VectorDouble expected_x_doub(L"-0.50191278570136,2.46510443988885,-1.85833970101978,-0.47147969983892,0.91032488719446,0.27305443123786,1.20684838083948,2.02022380340132,-2.03776258794210,0.78151547389827 ");

  // test vectors
  //
  VectorFloat x_fl;
  VectorDouble x_doub;

  // test linearSolve
  //
  LinearAlgebra::linearSolve(x_fl, A_fl, b_fl);
  LinearAlgebra::linearSolve(x_doub, A_doub, b_doub);

  // verify that results match
  //
  if (!expected_x_fl.almostEqual(x_fl)) {
    x_fl.debug(L"actual x");
    expected_x_fl.debug(L"expected x");    
    return Error::handle(name(), L"linearSolve (float32)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!expected_x_doub.almostEqual(x_doub)) {
    x_doub.debug(L"actual x");
    expected_x_doub.debug(L"expected x");    
    return Error::handle(name(), L"linearSolve (float64)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     linear solver methods (non-square matrix)
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: linear solver methods for non-square matrices...\n");
    Console::increaseIndention();
  }

  // declare a multiplier matrix (10x6 - underdetermined set)
  //
  A_fl.assign(6, 10, L"0.58279168156123,0.20906940443842,0.41537486044322,0.21396333159617,0.68333232433848,0.45142482676248,0.42349625685105,0.37981837035079,0.30499867700349,0.64349228788535,0.21255986433874,0.04389532534714,0.78332864986771,0.87436717158763,0.32003557746650,0.83923824033620,0.02718512299667,0.01635493355000,0.68084575139723,0.01500949867662,0.96009860036901,0.62878460002407,0.31268504808015,0.19007458907973,0.46109512665670,0.76795039001114,0.72663176664190,0.13377274847343,0.01286257467300,0.58691847188467,0.56782871242883,0.97084493925562,0.41195320816864,0.20713272964136,0.38396728849430,0.05758108987829,0.79421065137261,0.99008259261306,0.74456578310616,0.60719894453953,0.68311596780460,0.36756803882634,0.05918259347107,0.78886169223375,0.26794725070937,0.62988784884231,0.09284246174092,0.63145116474444,0.60286908566699,0.43865853377091,0.43992430956534,0.37047682605190,0.03533832396916,0.71763442146570,0.05026880374687,0.49831130344848,0.93338010818959,0.57514777904747,0.61239548137302,0.69266939471779", Integral::FULL);
  A_doub.assign(6, 10, L"0.58279168156123,0.20906940443842,0.41537486044322,0.21396333159617,0.68333232433848,0.45142482676248,0.42349625685105,0.37981837035079,0.30499867700349,0.64349228788535,0.21255986433874,0.04389532534714,0.78332864986771,0.87436717158763,0.32003557746650,0.83923824033620,0.02718512299667,0.01635493355000,0.68084575139723,0.01500949867662,0.96009860036901,0.62878460002407,0.31268504808015,0.19007458907973,0.46109512665670,0.76795039001114,0.72663176664190,0.13377274847343,0.01286257467300,0.58691847188467,0.56782871242883,0.97084493925562,0.41195320816864,0.20713272964136,0.38396728849430,0.05758108987829,0.79421065137261,0.99008259261306,0.74456578310616,0.60719894453953,0.68311596780460,0.36756803882634,0.05918259347107,0.78886169223375,0.26794725070937,0.62988784884231,0.09284246174092,0.63145116474444,0.60286908566699,0.43865853377091,0.43992430956534,0.37047682605190,0.03533832396916,0.71763442146570,0.05026880374687,0.49831130344848,0.93338010818959,0.57514777904747,0.61239548137302,0.69266939471779", Integral::FULL);


  // declare the vector of knowns (6x1)
  //
  b_fl.assign(L"0.23788030773557, 0.64583124997499, 0.96688742090893, 0.66493121192534,0.87038102590598, 0.00992730476335 ");
  b_doub.assign(L"0.23788030773557, 0.64583124997499, 0.96688742090893, 0.66493121192534,0.87038102590598, 0.00992730476335 ");

  // declare the expected output (10x1)
  //
  expected_x_fl.assign(L"0.76331300975900,1.03272003477806,0.16384200945957,0.06865617224243,-0.10085777766474,0.42004129123027,-0.58166886291840,0.02108491768940,-0.06804155995489,-0.57070978446245");
  expected_x_doub.assign(L"0.76331300975900,1.03272003477806,0.16384200945957,0.06865617224243,-0.10085777766474,0.42004129123027,-0.58166886291840,0.02108491768940,-0.06804155995489,-0.57070978446245");

  // test linearSolve
  //
  LinearAlgebra::linearSolve(x_doub, A_doub, b_doub);
  LinearAlgebra::linearSolve(x_fl, A_fl, b_fl);

  // verify that results match
  //
  if (!expected_x_fl.almostEqual(x_fl)) {
    b_fl.debug(L"b");
    x_fl.debug(L"actual x");
    expected_x_fl.debug(L"expected x");    
    return Error::handle(name(), L"linearSolve (float32)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!expected_x_doub.almostEqual(x_doub)) {
    b_doub.debug(L"b");
    x_doub.debug(L"actual x");
    expected_x_doub.debug(L"expected x");    
    return Error::handle(name(), L"linearSolve (float64)", Error::TEST,
			 __FILE__, __LINE__);
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
