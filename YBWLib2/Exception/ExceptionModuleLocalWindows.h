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
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithLastErrorException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureWithLastErrorException)), module_info_current);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithWSALastErrorException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureWithWSALastErrorException)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithNTSTATUSException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureWithNTSTATUSException)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithHRESULTException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureWithHRESULTException)), module_info_current);
#endif
		ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithLastErrorException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithLastErrorException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithLastErrorException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithLastErrorException, IExternalAPIFailureWithLastErrorException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithLastErrorException));
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithWSALastErrorException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithWSALastErrorException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureWithWSALastErrorException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithWSALastErrorException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithNTSTATUSException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithNTSTATUSException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureWithNTSTATUSException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithNTSTATUSException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithHRESULTException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithHRESULTException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, IExternalAPIFailureWithHRESULTException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithHRESULTException));
#endif
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithLastErrorException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureWithLastErrorException)), module_info_current);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithWSALastErrorException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureWithWSALastErrorException)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithNTSTATUSException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureWithNTSTATUSException)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithHRESULTException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureWithHRESULTException)), module_info_current);
#endif
	}

	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitModuleLocal() noexcept {
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithHRESULTException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithNTSTATUSException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithWSALastErrorException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
		GetDynamicTypeThisClassObject<ExternalAPIFailureWithLastErrorException>()->UnRegisterTypeInfoWrapper(module_info_current);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		delete ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		delete ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		delete ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = nullptr;
#endif
		delete ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject;
		ExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = nullptr;
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithHRESULTException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithNTSTATUSException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithWSALastErrorException>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
		GetDynamicTypeThisClassObject<IExternalAPIFailureWithLastErrorException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}

	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealInitModuleLocal() noexcept {}

	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealUnInitModuleLocal() noexcept {}
}

#endif
