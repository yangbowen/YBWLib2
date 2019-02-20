#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"
#include "ExceptionWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureWithLastErrorException, YBWLIB2_API);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureWithWSALastErrorException, YBWLIB2_API);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureWithNTSTATUSException, YBWLIB2_API);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureWithHRESULTException, YBWLIB2_API);
#endif

	void YBWLIB2_CALLTYPE ExceptionWindows_RealInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IExternalAPIFailureWithLastErrorException, IExternalAPIFailureException);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IExternalAPIFailureWithHRESULTException, IExternalAPIFailureException);
#endif
	}

	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IExternalAPIFailureWithHRESULTException);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IExternalAPIFailureWithNTSTATUSException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IExternalAPIFailureWithWSALastErrorException);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IExternalAPIFailureWithLastErrorException);
#endif
	}
}
