// file: $isip/class/
// version: $Id: database_00.cc 7/10/2013
//

// isip include files
//
#include "Database.h"

//------------------------------------------------------------------------
//
// required public methods
//
//-----------------------------------------------------------------------

long Database::MAX_BUFF_SIZE = 100000;

const String Database::CLASS_NAME(L"Database");

// constants: i/o related constants
//
const String Database::DEF_PARAM(L"");
const String Database::PARAM_DATA(L"data");
const String Database::PARAM_LABELS(L"labels");
const String Database::PARAM_RECORD(L"record");
