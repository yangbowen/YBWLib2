#pragma include_alias("pch.h", "../pch.h");
#include "pch.h"
#include "../Common/CommonLowLevel.h"
#include "JSON.h"

#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IParseErrorJSONException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONSAXHandler, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONSAXGenerator, YBWLIB2_API);

	YBWLIB2_API IStringTemplate* JSONException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* ParseErrorJSONException::strtmpl_description = nullptr;

	void YBWLIB2_CALLTYPE JSON_RealInitGlobal() noexcept {
		IJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IJSONException>(),
			IsDynamicTypeModuleLocalClass<IJSONException>(),
			{ DynamicTypeBaseClassDef<IJSONException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONException), alignof(IJSONException));
		IParseErrorJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IParseErrorJSONException>(),
			IsDynamicTypeModuleLocalClass<IParseErrorJSONException>(),
			{ DynamicTypeBaseClassDef<IParseErrorJSONException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IParseErrorJSONException), alignof(IParseErrorJSONException));
		IJSONSAXHandler::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IJSONSAXHandler>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXHandler>(),
			{ DynamicTypeBaseClassDef<IJSONSAXHandler, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXHandler), alignof(IJSONSAXHandler));
		IJSONSAXGenerator::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IJSONSAXGenerator>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXGenerator>(),
			{ DynamicTypeBaseClassDef<IJSONSAXGenerator, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXGenerator), alignof(IJSONSAXGenerator));
	}

	void YBWLIB2_CALLTYPE JSON_RealUnInitGlobal() noexcept {
		delete IJSONSAXGenerator::DynamicTypeThisClassObject;
		IJSONSAXGenerator::DynamicTypeThisClassObject = nullptr;
		delete IJSONSAXHandler::DynamicTypeThisClassObject;
		IJSONSAXHandler::DynamicTypeThisClassObject = nullptr;
		delete IParseErrorJSONException::DynamicTypeThisClassObject;
		IParseErrorJSONException::DynamicTypeThisClassObject = nullptr;
		delete IJSONException::DynamicTypeThisClassObject;
		IJSONException::DynamicTypeThisClassObject = nullptr;
	}

	void YBWLIB2_CALLTYPE JSONUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_t;
			map_strtmpl_description_t map_strtmpl_description({
				{ GetDynamicTypeClassID<JSONException>(), &JSONException::strtmpl_description },
				{ GetDynamicTypeClassID<ParseErrorJSONException>(), &ParseErrorJSONException::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval(u8"JSON"));
			if (jsonmemberit_config_internal_JSON == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_JSON->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description = jsonmemberit_config_internal_JSON->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"strtmpl_description"));
				if (jsonmemberit_config_internal_JSON_strtmpl_description == jsonmemberit_config_internal_JSON->value.MemberEnd() || !jsonmemberit_config_internal_JSON_strtmpl_description->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_JSON_strtmpl_description_element : jsonmemberit_config_internal_JSON_strtmpl_description->value.GetArray()) {
						if (!jsonval_config_internal_JSON_strtmpl_description_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_object = jsonval_config_internal_JSON_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_object"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_strtmpl = jsonval_config_internal_JSON_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_element_jsonval_strtmpl = jsonval_config_internal_JSON_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_object == jsonval_config_internal_JSON_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_object->value.IsString()
							|| jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_strtmpl == jsonval_config_internal_JSON_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_JSON_strtmpl_description_element_jsonval_strtmpl == jsonval_config_internal_JSON_strtmpl_description_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_object = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_object->value.GetString(),
							jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_object->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_JSON_strtmpl_description_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_t::iterator it_map_strtmpl_description = map_strtmpl_description.find(dtclassid_object);
						if (it_map_strtmpl_description == map_strtmpl_description.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_JSON_strtmpl_description_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeClassObject<IStringTemplate>(), indexeddatastore_parameters));
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

	void YBWLIB2_CALLTYPE JSONUserInterface_RealUnInitGlobal() noexcept {
		delete ParseErrorJSONException::strtmpl_description;
		ParseErrorJSONException::strtmpl_description = nullptr;
		delete JSONException::strtmpl_description;
		JSONException::strtmpl_description = nullptr;
	}
}
