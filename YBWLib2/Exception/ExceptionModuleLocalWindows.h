﻿#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#include "../DynamicType/DynamicType.h"
#include "Exception.h"
#include "ExceptionWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithLastErrorException, , IExternalAPIFailureWithLastErrorException);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithWSALastErrorException, , IExternalAPIFailureWithWSALastErrorException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithNTSTATUSException, , IExternalAPIFailureWithNTSTATUSException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithHRESULTException, , IExternalAPIFailureWithHRESULTException);
#endif
}
