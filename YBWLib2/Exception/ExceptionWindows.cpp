﻿#pragma include_alias("pch.h", "../pch.h")
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
		IExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithLastErrorException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithLastErrorException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithLastErrorException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> });
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		IExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithWSALastErrorException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithWSALastErrorException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> });
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		IExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithNTSTATUSException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithNTSTATUSException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> });
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		IExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithHRESULTException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithHRESULTException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithHRESULTException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> });
#endif
	}

	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitGlobal() noexcept {
		delete IExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject;
		IExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = nullptr;
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		delete IExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject;
		IExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		delete IExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject;
		IExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		delete IExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject;
		IExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = nullptr;
#endif
	}
}
