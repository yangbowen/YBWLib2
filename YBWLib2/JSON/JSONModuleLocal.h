#ifndef _INCLUDE_GUARD_B1D13803_939D_4D57_BEB2_F29AC2CFE595
#define _INCLUDE_GUARD_B1D13803_939D_4D57_BEB2_F29AC2CFE595

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "JSON.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(JSONException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ParseErrorJSONException, );

	[[nodiscard]] IException* JSONException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = JSONException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
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

	[[nodiscard]] IException* ParseErrorJSONException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_str_parse_error;
				if (this->str_parse_error && this->str_parse_error[0]) {
					objholder_strtmplparameter_str_parse_error.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"str_parse_error", this->str_parse_error, strlen(this->str_parse_error));
				} else {
					objholder_strtmplparameter_str_parse_error.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"str_parse_error", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_offset_parse_error;
				{
					char str_offset_parse_error[sizeof(size_t) / sizeof(uint8_t) * 3 + 4];
					static constexpr char str_prefix_fmt[] = u8"%";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<::std::make_unsigned_t<size_t>>::fmtspec_printf_u_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<::std::make_unsigned_t<size_t>>::fmtspec_printf_u_utf8, sizeof(inttype_traits_t<::std::make_unsigned_t<size_t>>::fmtspec_printf_u_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(rawallocator_exception, str_offset_parse_error, sizeof(str_offset_parse_error) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), this->offset_parse_error);
					if (err_inner) return;
					objholder_strtmplparameter_offset_parse_error.construct(
						objholder_local_t<StringStringTemplateParameter>::construct_obj,
						rawallocator_exception,
						u8"offset_parse_error",
						str_offset_parse_error,
						strnlen(str_offset_parse_error, sizeof(str_offset_parse_error) / sizeof(char))
					);
				}
				err_inner = ParseErrorJSONException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_str_parse_error.get(),
						objholder_strtmplparameter_offset_parse_error.get()
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

	JSONSAXGeneratorParameterIndexedDataEntry JSONSAXGeneratorParameterIndexedDataEntry::CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false) {
		const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			return JSONSAXGeneratorParameterIndexedDataEntry(*_indexeddatarawvalue);
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	JSONSAXGeneratorParameterIndexedDataEntry JSONSAXGeneratorParameterIndexedDataEntry::MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false) {
		IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			JSONSAXGeneratorParameterIndexedDataEntry ret(JSONSAXGeneratorParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue)));
			_indexeddatastore.RemoveEntryByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
			return ret;
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	void YBWLIB2_CALLTYPE JSON_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONException)), module_info_current);
		GetDynamicTypeThisClassObject<IParseErrorJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IParseErrorJSONException)), module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXHandler>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONSAXHandler)), module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXGenerator>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONSAXGenerator)), module_info_current);
		JSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<JSONException>(),
			IsDynamicTypeModuleLocalClass<JSONException>(),
			{
				DynamicTypeBaseClassDef<JSONException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<JSONException, IJSONException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(JSONException), alignof(JSONException));
		ParseErrorJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ParseErrorJSONException>(),
			IsDynamicTypeModuleLocalClass<ParseErrorJSONException>(),
			{
				DynamicTypeBaseClassDef<ParseErrorJSONException, JSONException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ParseErrorJSONException, IParseErrorJSONException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ParseErrorJSONException), alignof(ParseErrorJSONException));
		GetDynamicTypeThisClassObject<JSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(JSONException)), module_info_current);
		GetDynamicTypeThisClassObject<ParseErrorJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ParseErrorJSONException)), module_info_current);
	}

	void YBWLIB2_CALLTYPE JSON_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<JSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ParseErrorJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete ParseErrorJSONException::DynamicTypeThisClassObject;
		ParseErrorJSONException::DynamicTypeThisClassObject = nullptr;
		delete JSONException::DynamicTypeThisClassObject;
		JSONException::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IJSONSAXGenerator>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXHandler>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IParseErrorJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
