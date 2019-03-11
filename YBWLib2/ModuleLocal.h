// This header file provides definitions for per-module data structures.
// For each executable module that uses functionalities provided by this library,
// include this header file in one and only one source file.

#ifndef _INCLUDE_GUARD_653EEAC0_F784_4FBA_9955_725282D5A5AD
#define _INCLUDE_GUARD_653EEAC0_F784_4FBA_9955_725282D5A5AD

#include "YBWLib2InitModuleLocal.h"
#include "Common/CommonLowLevelModuleLocal.h"
#include "Exception/ExceptionLowLevelModuleLocal.h"
#include "DynamicType/DynamicTypeModuleLocal.h"
#include "Exception/ExceptionModuleLocal.h"
#ifdef _WIN32_WINNT
#include "Exception/ExceptionWindowsModuleLocal.h"
#endif
#include "Common/CommonModuleLocal.h"
#ifdef _WIN32_WINNT
#include "Common/CommonWindowsModuleLocal.h"
#endif
#include "JSON/JSONModuleLocal.h"
#include "UserInterface/UserInterfaceModuleLocal.h"
#ifdef _WIN32_WINNT
#include "UserInterface/UserInterfaceWindowsModuleLocal.h"
#endif
#include "File/FileModuleLocal.h"

#endif
