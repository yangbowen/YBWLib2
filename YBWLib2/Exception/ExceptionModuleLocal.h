﻿#ifndef _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8
#define _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include <vector>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"

#include "../UserInterface/UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Exception, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(DoubleExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(InvalidParameterException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(InvalidCallException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(InsufficientBufferException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(MemoryAllocFailureException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(KeyAlreadyExistException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(KeyNotExistException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(UnhandledUnknownExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(STLExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(UnexpectedExceptionException, );

	static IException* YBWLIB2_CALLTYPE WrapFunctionCatchExceptionsRaw_Exception(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept;

	static fnptr_wrap_function_catch_exceptions_raw_t fnptr_wrap_function_catch_exceptions_raw_old_Exception = nullptr;

	[[nodiscard]] IException* Exception::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = Exception::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* DoubleExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = DoubleExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* InvalidParameterException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				StringStringTemplateParameter strtmplparameter_name_function(rawallocator_exception, u8"name_function", this->name_function, this->size_name_function);
				StringStringTemplateParameter strtmplparameter_name_class_member_function(rawallocator_exception, u8"name_class_member_function", this->name_class_member_function, this->size_name_class_member_function);
				err_inner = InvalidParameterException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_name_function,
						&strtmplparameter_name_class_member_function
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* InvalidCallException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				StringStringTemplateParameter strtmplparameter_name_function(rawallocator_exception, u8"name_function", this->name_function, this->size_name_function);
				StringStringTemplateParameter strtmplparameter_name_class_member_function(rawallocator_exception, u8"name_class_member_function", this->name_class_member_function, this->size_name_class_member_function);
				err_inner = InvalidCallException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_name_function,
						&strtmplparameter_name_class_member_function
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* InsufficientBufferException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				AddressStringTemplateParameter strtmplparameter_address_buffer_insufficient(rawallocator_exception, u8"address_buffer_insufficient", reinterpret_cast<uintptr_t>(this->GetInsufficientBufferAddress()));
				err_inner = InsufficientBufferException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_address_buffer_insufficient
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* MemoryAllocFailureException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = MemoryAllocFailureException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* KeyAlreadyExistException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = KeyAlreadyExistException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* KeyNotExistException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = KeyNotExistException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* UnhandledUnknownExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				err_inner = UnhandledUnknownExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* STLExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				StringStringTemplateParameter strtmplparameter_str_what_stlexception(rawallocator_exception, u8"str_what_stlexception", this->str_what_stlexception, this->size_str_what_stlexception);
				err_inner = STLExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_str_what_stlexception
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* ExternalAPIFailureException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				StringStringTemplateParameter strtmplparameter_name_api(rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				AddressStringTemplateParameter strtmplparameter_address_api(rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->GetExternalAPIAddress()));
				err_inner = ExternalAPIFailureException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_name_api,
						&strtmplparameter_address_api
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	[[nodiscard]] IException* UnexpectedExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_descrption_ret, bool* is_successful_ret) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_descrption_ret, &err_inner]() noexcept(false)->void {
				StringStringTemplateParameter strtmplparameter_filename_source_code(rawallocator_exception, u8"filename_source_code", this->filename_source_code, this->size_filename_source_code);
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_linenumber_source_code;
				{
					char str_linenumber_source_code[sizeof(int) / sizeof(uint8_t) * 3 + 4];
					IException* err_utf8_snprintf = utf8_snprintf(rawallocator_exception, str_linenumber_source_code, sizeof(str_linenumber_source_code) / sizeof(char), u8"%d", sizeof(u8"%d") / sizeof(char), this->linenumber_source_code);
					if (err_utf8_snprintf) { err_inner = err_utf8_snprintf; return; }
					objholder_strtmplparameter_linenumber_source_code.construct(
						objholder_local_t<StringStringTemplateParameter>::construct_obj,
						rawallocator_exception,
						u8"linenumber_source_code",
						str_linenumber_source_code,
						strnlen(str_linenumber_source_code, sizeof(str_linenumber_source_code) / sizeof(char))
					);
				}
				err_inner = UnexpectedExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						&strtmplparameter_filename_source_code,
						objholder_strtmplparameter_linenumber_source_code.get()
					}
				), description_ret, size_descrption_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_descrption_ret = 0; }
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

	void YBWLIB2_CALLTYPE Exception_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IException)), module_info_current);
		GetDynamicTypeThisClassObject<IDoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IDoubleExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<IInvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInvalidParameterException)), module_info_current);
		GetDynamicTypeThisClassObject<IInvalidCallException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInvalidCallException)), module_info_current);
		GetDynamicTypeThisClassObject<IInsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInsufficientBufferException)), module_info_current);
		GetDynamicTypeThisClassObject<IMemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IMemoryAllocFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<IKeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyAlreadyExistException)), module_info_current);
		GetDynamicTypeThisClassObject<IKeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyNotExistException)), module_info_current);
		GetDynamicTypeThisClassObject<IUnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<ISTLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISTLExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<IExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<IUnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnexpectedExceptionException)), module_info_current);
		Exception::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<Exception>(),
			IsDynamicTypeModuleLocalClass<Exception>(),
			{ DynamicTypeBaseClassDef<Exception, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(Exception), alignof(Exception));
		DoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<DoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<DoubleExceptionException>(),
			{
				DynamicTypeBaseClassDef<DoubleExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<DoubleExceptionException, IDoubleExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(DoubleExceptionException), alignof(DoubleExceptionException));
		InvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<InvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<InvalidParameterException>(),
			{
				DynamicTypeBaseClassDef<InvalidParameterException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InvalidParameterException, IInvalidParameterException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InvalidParameterException), alignof(InvalidParameterException));
		InvalidCallException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<InvalidCallException>(),
			IsDynamicTypeModuleLocalClass<InvalidCallException>(),
			{
				DynamicTypeBaseClassDef<InvalidCallException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InvalidCallException, IInvalidCallException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InvalidCallException), alignof(InvalidCallException));
		InsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<InsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<InsufficientBufferException>(),
			{
				DynamicTypeBaseClassDef<InsufficientBufferException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InsufficientBufferException, IInsufficientBufferException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InsufficientBufferException), alignof(InsufficientBufferException));
		MemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<MemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<MemoryAllocFailureException>(),
			{
				DynamicTypeBaseClassDef<MemoryAllocFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryAllocFailureException, IMemoryAllocFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(MemoryAllocFailureException), alignof(MemoryAllocFailureException));
		KeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<KeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<KeyAlreadyExistException>(),
			{
				DynamicTypeBaseClassDef<KeyAlreadyExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyAlreadyExistException, IKeyAlreadyExistException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(KeyAlreadyExistException), alignof(KeyAlreadyExistException));
		KeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<KeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<KeyNotExistException>(),
			{
				DynamicTypeBaseClassDef<KeyNotExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyNotExistException, IKeyNotExistException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(KeyNotExistException), alignof(KeyNotExistException));
		UnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<UnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnhandledUnknownExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, IUnhandledUnknownExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(UnhandledUnknownExceptionException), alignof(UnhandledUnknownExceptionException));
		STLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<STLExceptionException>(),
			IsDynamicTypeModuleLocalClass<STLExceptionException>(),
			{
				DynamicTypeBaseClassDef<STLExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<STLExceptionException, ISTLExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(STLExceptionException), alignof(STLExceptionException));
		ExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureException), alignof(ExternalAPIFailureException));
		UnexpectedExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<UnexpectedExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnexpectedExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnexpectedExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnexpectedExceptionException, IUnexpectedExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(UnexpectedExceptionException), alignof(UnexpectedExceptionException));
		GetDynamicTypeThisClassObject<Exception>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Exception)), module_info_current);
		GetDynamicTypeThisClassObject<DoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(DoubleExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<InvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InvalidParameterException)), module_info_current);
		GetDynamicTypeThisClassObject<InvalidCallException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InvalidCallException)), module_info_current);
		GetDynamicTypeThisClassObject<InsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InsufficientBufferException)), module_info_current);
		GetDynamicTypeThisClassObject<MemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(MemoryAllocFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<KeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyAlreadyExistException)), module_info_current);
		GetDynamicTypeThisClassObject<KeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyNotExistException)), module_info_current);
		GetDynamicTypeThisClassObject<UnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<STLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(STLExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<ExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<UnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnexpectedExceptionException)), module_info_current);
		fnptr_wrap_function_catch_exceptions_raw_old_Exception = ExchangeRawWrapFunctionCatchExceptionsFnptr(ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local, &WrapFunctionCatchExceptionsRaw_Exception);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept {
		ExchangeRawWrapFunctionCatchExceptionsFnptr(ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local, fnptr_wrap_function_catch_exceptions_raw_old_Exception);
		fnptr_wrap_function_catch_exceptions_raw_old_Exception = nullptr;
		GetDynamicTypeThisClassObject<UnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<STLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<UnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<KeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<KeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<MemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<InsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<InvalidCallException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<InvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<DoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<Exception>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete UnexpectedExceptionException::DynamicTypeThisClassObject;
		UnexpectedExceptionException::DynamicTypeThisClassObject = nullptr;
		delete ExternalAPIFailureException::DynamicTypeThisClassObject;
		ExternalAPIFailureException::DynamicTypeThisClassObject = nullptr;
		delete STLExceptionException::DynamicTypeThisClassObject;
		STLExceptionException::DynamicTypeThisClassObject = nullptr;
		delete UnhandledUnknownExceptionException::DynamicTypeThisClassObject;
		UnhandledUnknownExceptionException::DynamicTypeThisClassObject = nullptr;
		delete KeyNotExistException::DynamicTypeThisClassObject;
		KeyNotExistException::DynamicTypeThisClassObject = nullptr;
		delete KeyAlreadyExistException::DynamicTypeThisClassObject;
		KeyAlreadyExistException::DynamicTypeThisClassObject = nullptr;
		delete MemoryAllocFailureException::DynamicTypeThisClassObject;
		MemoryAllocFailureException::DynamicTypeThisClassObject = nullptr;
		delete InsufficientBufferException::DynamicTypeThisClassObject;
		InsufficientBufferException::DynamicTypeThisClassObject = nullptr;
		delete InvalidCallException::DynamicTypeThisClassObject;
		InvalidCallException::DynamicTypeThisClassObject = nullptr;
		delete InvalidParameterException::DynamicTypeThisClassObject;
		InvalidParameterException::DynamicTypeThisClassObject = nullptr;
		delete DoubleExceptionException::DynamicTypeThisClassObject;
		DoubleExceptionException::DynamicTypeThisClassObject = nullptr;
		delete Exception::DynamicTypeThisClassObject;
		Exception::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IUnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISTLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IUnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IKeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IKeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IMemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInvalidCallException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IDoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}

	static IException* YBWLIB2_CALLTYPE WrapFunctionCatchExceptionsRaw_Exception(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept {
		if (!_fnptr_inner)
			return YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION()->AttachCause(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::WrapFunctionCatchExceptionsRaw_Exception));
		if (!fnptr_wrap_function_catch_exceptions_raw_old_Exception)
			return YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION()->AttachCause(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		struct ctx_t final {
			void(YBWLIB2_CALLTYPE* const fnptr_inner)(uintptr_t _context) = nullptr;
			const uintptr_t context;
			IException* err = nullptr;
			inline constexpr ctx_t(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) : fnptr_inner(_fnptr_inner), context(_context) {}
		} ctx(_fnptr_inner, _context);
		IException* err_original = (*fnptr_wrap_function_catch_exceptions_raw_old_Exception)(
			[](uintptr_t _context) {
				ctx_t* ctx = reinterpret_cast<ctx_t*>(_context);
				if (!ctx) abort();
				ctx->err = nullptr;
				try {
					(*ctx->fnptr_inner)(ctx->context);
				} catch (::std::bad_alloc&) {
					ctx->err = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION();
				} catch (::std::exception& err) {
					ctx->err = YBWLIB2_EXCEPTION_CREATE_STL_EXCEPTION_EXCEPTION(err);
				} catch (IException* err) {
					ctx->err = err;
				} catch (...) {
					ctx->err = YBWLIB2_EXCEPTION_CREATE_UNHANDLED_UNKNOWN_EXCEPTION_EXCEPTION();
				}
			}, reinterpret_cast<uintptr_t>(&ctx));
		if (err_original) {
			if (ctx.err) {
				delete ctx.err;
				ctx.err = nullptr;
			}
			return err_original;
		} else return ctx.err;
	}
}

#endif
