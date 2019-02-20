// This header file provides definitions for per-module data structures.
// For each executable module that uses functionalities provided by this library,
// include this header file in one and only one source file.

// Include guard omitted intentionally.

#include "YBWLib2InitModuleLocal.h"
#include "Common/CommonLowLevelModuleLocal.h"
#include "DynamicType/DynamicTypeModuleLocal.h"
#include "Exception/ExceptionModuleLocal.h"
#ifdef _WIN32_WINNT
#include "Exception/ExceptionModuleLocalWindows.h"
#endif
#include "Common/CommonModuleLocal.h"
#include "UserInterface/UserInterfaceModuleLocal.h"
