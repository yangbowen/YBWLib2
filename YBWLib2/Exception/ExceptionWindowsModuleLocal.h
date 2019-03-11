#ifndef _INCLUDE_GUARD_93ABD222_7D79_4F3D_BB9E_E853F4015CD8
#define _INCLUDE_GUARD_93ABD222_7D79_4F3D_BB9E_E853F4015CD8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"
#include "ExceptionWindows.h"

#include "../UserInterface/UserInterfaceWindows.h"

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

	[[nodiscard]] IException* ExternalAPIFailureWithLastErrorException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_api;
				if (this->name_api && this->size_name_api) {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				} else {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_api;
				objholder_strtmplparameter_address_api.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->address_api));
				LastErrorStringTemplateParameter strtmplparameter_lasterr(rawallocator_exception, u8"lasterr", this->lasterr);
				err_inner = ExternalAPIFailureWithLastErrorException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_api.get(),
						objholder_strtmplparameter_address_api.get(),
						&strtmplparameter_lasterr
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	[[nodiscard]] IException* ExternalAPIFailureWithWSALastErrorException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_api;
				if (this->name_api && this->size_name_api) {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				} else {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_api;
				objholder_strtmplparameter_address_api.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->address_api));
				WSALastErrorStringTemplateParameter strtmplparameter_wsalasterr(rawallocator_exception, u8"wsalasterr", wsalasterr);
				err_inner = ExternalAPIFailureWithWSALastErrorException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_api.get(),
						objholder_strtmplparameter_address_api.get(),
						&strtmplparameter_wsalasterr
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	[[nodiscard]] IException* ExternalAPIFailureWithNTSTATUSException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_api;
				if (this->name_api && this->size_name_api) {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				} else {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_api;
				objholder_strtmplparameter_address_api.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->address_api));
				NTSTATUSStringTemplateParameter strtmplparameter_ntstatus(rawallocator_exception, u8"ntstatus", ntstatus);
				err_inner = ExternalAPIFailureWithNTSTATUSException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_api.get(),
						objholder_strtmplparameter_address_api.get(),
						&strtmplparameter_ntstatus
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	[[nodiscard]] IException* ExternalAPIFailureWithHRESULTException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_api;
				if (this->name_api && this->size_name_api) {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				} else {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_api;
				objholder_strtmplparameter_address_api.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->address_api));
				HRESULTStringTemplateParameter strtmplparameter_hresult(rawallocator_exception, u8"hresult", hresult);
				err_inner = ExternalAPIFailureWithHRESULTException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_api.get(),
						objholder_strtmplparameter_address_api.get(),
						&strtmplparameter_hresult
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}
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
			0, sizeof(ExternalAPIFailureWithLastErrorException), alignof(ExternalAPIFailureWithLastErrorException));
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		ExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithWSALastErrorException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithWSALastErrorException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureWithWSALastErrorException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithWSALastErrorException), alignof(ExternalAPIFailureWithWSALastErrorException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		ExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithNTSTATUSException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithNTSTATUSException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureWithNTSTATUSException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithNTSTATUSException), alignof(ExternalAPIFailureWithNTSTATUSException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		ExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureWithHRESULTException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureWithHRESULTException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, ExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureWithHRESULTException, IExternalAPIFailureWithHRESULTException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureWithHRESULTException), alignof(ExternalAPIFailureWithHRESULTException));
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
}

#endif
