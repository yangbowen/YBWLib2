#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"
#include "File.h"
#include "FileWindows.h"

namespace YBWLib2 {
	YBWLIB2_API IStringTemplate* Win32File::strtmpl_description = nullptr;

	void YBWLIB2_CALLTYPE FileWindows_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE FileWindows_RealUnInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_t;
			map_strtmpl_description_t map_strtmpl_description({
				{ GetDynamicTypeThisClassID<Win32File>(), &Win32File::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_FileWindows = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval("FileWindows"));
			if (jsonmemberit_config_internal_FileWindows == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_FileWindows->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_FileWindows_strtmpl_description = jsonmemberit_config_internal_FileWindows->value.FindMember(Internal::ConstStringToInternalConfigJsonval("strtmpl_description"));
				if (jsonmemberit_config_internal_FileWindows_strtmpl_description == jsonmemberit_config_internal_FileWindows->value.MemberEnd() || !jsonmemberit_config_internal_FileWindows_strtmpl_description->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_FileWindows_strtmpl_description_element : jsonmemberit_config_internal_FileWindows_strtmpl_description->value.GetArray()) {
						if (!jsonval_config_internal_FileWindows_strtmpl_description_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_exception = jsonval_config_internal_FileWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_exception"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_strtmpl = jsonval_config_internal_FileWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_FileWindows_strtmpl_description_element_jsonval_strtmpl = jsonval_config_internal_FileWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval("jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_exception == jsonval_config_internal_FileWindows_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_exception->value.IsString()
							|| jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_strtmpl == jsonval_config_internal_FileWindows_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_FileWindows_strtmpl_description_element_jsonval_strtmpl == jsonval_config_internal_FileWindows_strtmpl_description_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_exception = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_exception->value.GetString(),
							jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_exception->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_FileWindows_strtmpl_description_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_t::iterator it_map_strtmpl_description = map_strtmpl_description.find(dtclassid_exception);
						if (it_map_strtmpl_description == map_strtmpl_description.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_FileWindows_strtmpl_description_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeThisClassObject<IStringTemplate>(), indexeddatastore_parameters));
						if (!*it_map_strtmpl_description->second) abort();
						objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
							[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
								return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
							}
						);
						if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
						map_strtmpl_description.erase(it_map_strtmpl_description);
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealUnInitGlobal() noexcept {
		delete Win32File::strtmpl_description;
		Win32File::strtmpl_description = nullptr;
	}
}
