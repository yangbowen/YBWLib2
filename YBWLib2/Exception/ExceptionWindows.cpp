﻿#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"
#include "ExceptionWindows.h"

#include "../JSON/JSON.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"

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

	YBWLIB2_API IStringTemplate* ExternalAPIFailureWithLastErrorException::strtmpl_description = nullptr;
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	YBWLIB2_API IStringTemplate* ExternalAPIFailureWithWSALastErrorException::strtmpl_description = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	YBWLIB2_API IStringTemplate* ExternalAPIFailureWithNTSTATUSException::strtmpl_description = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	YBWLIB2_API IStringTemplate* ExternalAPIFailureWithHRESULTException::strtmpl_description = nullptr;
#endif

	void YBWLIB2_CALLTYPE ExceptionWindows_RealInitGlobal() noexcept {
		IExternalAPIFailureWithLastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithLastErrorException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithLastErrorException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithLastErrorException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureWithLastErrorException), alignof(IExternalAPIFailureWithLastErrorException));
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		IExternalAPIFailureWithWSALastErrorException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithWSALastErrorException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithWSALastErrorException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithWSALastErrorException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureWithWSALastErrorException), alignof(IExternalAPIFailureWithWSALastErrorException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		IExternalAPIFailureWithNTSTATUSException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithNTSTATUSException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithNTSTATUSException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithNTSTATUSException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureWithNTSTATUSException), alignof(IExternalAPIFailureWithNTSTATUSException));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		IExternalAPIFailureWithHRESULTException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureWithHRESULTException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureWithHRESULTException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureWithHRESULTException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureWithHRESULTException), alignof(IExternalAPIFailureWithHRESULTException));
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

	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_exception_t;
			map_strtmpl_description_exception_t map_strtmpl_description_exception({
				{ GetDynamicTypeThisClassID<ExternalAPIFailureWithLastErrorException>(), &ExternalAPIFailureWithLastErrorException::strtmpl_description }
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
				, { GetDynamicTypeThisClassID<ExternalAPIFailureWithWSALastErrorException>(), &ExternalAPIFailureWithWSALastErrorException::strtmpl_description }
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
				, { GetDynamicTypeThisClassID<ExternalAPIFailureWithNTSTATUSException>(), &ExternalAPIFailureWithNTSTATUSException::strtmpl_description }
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
				, { GetDynamicTypeThisClassID<ExternalAPIFailureWithHRESULTException>(), &ExternalAPIFailureWithHRESULTException::strtmpl_description }
#endif
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_ExceptionWindows = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval("ExceptionWindows"));
			if (jsonmemberit_config_internal_ExceptionWindows == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_ExceptionWindows->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception = jsonmemberit_config_internal_ExceptionWindows->value.FindMember(Internal::ConstStringToInternalConfigJsonval("strtmpl_description_exception"));
				if (jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception == jsonmemberit_config_internal_ExceptionWindows->value.MemberEnd() || !jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element : jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception->value.GetArray()) {
						if (!jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_exception = jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_exception"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_strtmpl = jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_jsonval_strtmpl = jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_exception == jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_exception->value.IsString()
							|| jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_strtmpl == jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_jsonval_strtmpl == jsonval_config_internal_ExceptionWindows_strtmpl_description_exception_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_exception = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_exception->value.GetString(),
							jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_exception->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_exception_t::iterator it_map_strtmpl_description_exception = map_strtmpl_description_exception.find(dtclassid_exception);
						if (it_map_strtmpl_description_exception == map_strtmpl_description_exception.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_ExceptionWindows_strtmpl_description_exception_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description_exception->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeThisClassObject<IStringTemplate>(), indexeddatastore_parameters));
						if (!*it_map_strtmpl_description_exception->second) abort();
						objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
							[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
								return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
							}
						);
						if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
						map_strtmpl_description_exception.erase(it_map_strtmpl_description_exception);
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealUnInitGlobal() noexcept {
		delete ExternalAPIFailureWithHRESULTException::strtmpl_description;
		ExternalAPIFailureWithHRESULTException::strtmpl_description = nullptr;
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		delete ExternalAPIFailureWithNTSTATUSException::strtmpl_description;
		ExternalAPIFailureWithNTSTATUSException::strtmpl_description = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		delete ExternalAPIFailureWithWSALastErrorException::strtmpl_description;
		ExternalAPIFailureWithWSALastErrorException::strtmpl_description = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		delete ExternalAPIFailureWithLastErrorException::strtmpl_description;
		ExternalAPIFailureWithLastErrorException::strtmpl_description = nullptr;
#endif
	}
}
