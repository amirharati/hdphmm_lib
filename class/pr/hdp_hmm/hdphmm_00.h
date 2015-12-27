// file: hdphmm_00.cc
// version: $Id: hdphmm_00.cc 2013-1-25 Amir Harati $
//

// there is no source code in this file
//


// there is no source code in this file
//

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
template <class emission_type> 
const String HDPHMM<emission_type>::CLASS_NAME(L"HDPHMM");

// constants: i/o related constants
//
template <class emission_type>
const String HDPHMM<emission_type>::DEF_PARAM(L"");
template <class emission_type>
const String HDPHMM<emission_type>::PARAM_MODEL(L"HDPHMM");
template <class emission_type>
const String HDPHMM<emission_type>::PARAM_FILE(L"HDPHMM_PARAMS");

// static instantiations: memory manager and a permanent scratch space
//
template <class emission_type>
MemoryManager HDPHMM<emission_type>::mgr_d(sizeof(HDPHMM),
				   HDPHMM::CLASS_NAME);


// debug level and verbosity
//
template <class emission_type>
Integral::DEBUG HDPHMM<emission_type>::debug_level_d = Integral::NONE;
template <class emission_type>
Integral::DEBUG HDPHMM<emission_type>::verbosity_d = Integral::NONE;



