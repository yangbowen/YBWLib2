#ifndef _INCLUDE_GUARD_93ABD222_7D79_4F3D_BB9E_E853F4015CD8
#define _INCLUDE_GUARD_93ABD222_7D79_4F3D_BB9E_E853F4015CD8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "Exception.h"
#include "ExceptionWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithLastErrorException, );
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithWSALastErrorException, );
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithNTSTATUSException, );
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureWithHRESULTException, );
#endif

	void YBWLIB2_CALLTYPE ExceptionWindows_RealInitModuleLocal() noexcept {
		ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithLastErrorException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithLastErrorException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithLastErrorException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithLastErrorException, IExternalAPIFailureWithLastErrorException, DynamicTypeBaseClassFlag_VirtualBase>
			});
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithWSALastErrorException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithWSALastErrorException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureWithWSALastErrorException, DynamicTypeBaseClassFlag_VirtualBase>
			});
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithNTSTATUSException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithNTSTATUSException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureWithNTSTATUSException, DynamicTypeBaseClassFlag_VirtualBase>
			});
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithHRESULTException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithHRESULTException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, IExternalAPIFailureWithHRESULTException, DynamicTypeBaseClassFlag_VirtualBase>
			});
#endif
	}

	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitModuleLocal() noexcept {
		delete ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = nullptr;
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		delete ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		delete ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		delete ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = nullptr;
#endif
	}
}

#endif
