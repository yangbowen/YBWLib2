#ifndef _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8
#define _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <type_traits>
#include <string>
#include <vector>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"

#include "../UserInterface/UserInterface.h"

namespace YBWLib2 {
	extern YBWLIB2_API IStringTemplate* strtmpl_delimiter_cause_description_exception;

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

	[[nodiscard]] IException* Exception::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = Exception::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* Exception::GetDescriptionTotal(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		bool has_deleted_this = false;
		IException* exception_cause_current = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner, &has_deleted_this, &exception_cause_current]() noexcept(false)->void {
				allocator_exception_t<char> allocator_exception_char;
				using str_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_exception_t<char>>;
				str_t str_description_total(allocator_exception_char);
				str_t str_prefix_line_description(allocator_exception_char);
				auto append_string_with_prefix_line = [](str_t& str_destination, const char* str_source, size_t size_str_source, const str_t& str_prefix_line) noexcept(false)->void {
					if (!str_source && size_str_source || size_str_source > UINTPTR_MAX - reinterpret_cast<uintptr_t>(str_source)) {
						IException* err_double_exception = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_double_exception->AttachCause(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Exception, GetDescriptionTotal::append_string_with_prefix_line));
						throw(err_double_exception);
					}
					while (size_str_source) {
						if (*str_source == '\n') {
							str_destination.push_back('\n');
							++str_source;
							--size_str_source;
							str_destination += str_prefix_line;
						} else {
							str_destination.push_back(*str_source);
							++str_source;
							--size_str_source;
						}
					}
				};
				str_description_total += str_prefix_line_description;
				{
					objholder_rawallocator_t<char[]> holder_description_this(rawallocator_exception);
					bool is_successful_this = false;
					IException* exception_new_this = this->GetDescriptionSingleLevel(&holder_description_this.get_ref_ptr_array_element_element_as_mem(), &holder_description_this.get_ref_count_element_element_as_mem(), &is_successful_this);
					if (is_successful_this) {
						if (exception_new_this != this) abort();
					} else {
						has_deleted_this = true;
						err_inner = exception_new_this;
						return;
					}
					append_string_with_prefix_line(str_description_total, holder_description_this.get(), holder_description_this.get_count(), str_prefix_line_description);
				}
				IException* exception_consequence_current = this;
				while (true) {
					if (exception_cause_current) abort();
					exception_consequence_current->DetachCause(&exception_cause_current);
					if (!exception_cause_current) break;
					str_prefix_line_description.push_back('\t');
					{
						objholder_rawallocator_t<char[]> holder_delimiter_cause_description_exception(rawallocator_exception);
						if (!strtmpl_delimiter_cause_description_exception) abort();
						err_inner = strtmpl_delimiter_cause_description_exception->GenerateString(StringTemplateParameterList(rawallocator_exception,
							{
							}
						), &holder_delimiter_cause_description_exception.get_ref_ptr_array_element_element_as_mem(), &holder_delimiter_cause_description_exception.get_ref_count_element_element_as_mem(), false, rawallocator_exception);
						if (err_inner) return;
						append_string_with_prefix_line(str_description_total, holder_delimiter_cause_description_exception.get(), holder_delimiter_cause_description_exception.get_count(), str_prefix_line_description);
					}
					{
						objholder_rawallocator_t<char[]> holder_description_exception_cause_current(rawallocator_exception);
						bool is_successful_exception_cause_current = false;
						IException* exception_new_cause_current = exception_cause_current->GetDescriptionSingleLevel(&holder_description_exception_cause_current.get_ref_ptr_array_element_element_as_mem(), &holder_description_exception_cause_current.get_ref_count_element_element_as_mem(), &is_successful_exception_cause_current);
						if (is_successful_exception_cause_current) {
							if (exception_new_cause_current != exception_cause_current) abort();
						} else {
							err_inner = exception_new_cause_current;
							exception_cause_current = nullptr;
							return;
						}
						append_string_with_prefix_line(str_description_total, holder_description_exception_cause_current.get(), holder_description_exception_cause_current.get_count(), str_prefix_line_description);
					}
					exception_consequence_current->AttachCause(exception_cause_current);
					exception_consequence_current = exception_cause_current;
					exception_cause_current = nullptr;
				}
				if (exception_cause_current) abort();
				exception_consequence_current = nullptr;
				*size_description_ret = str_description_total.size();
				*description_ret = reinterpret_cast<char*>(ExceptionAllocateMemory(*size_description_ret * sizeof(char), alignof(char[])));
				if (!*description_ret) abort();
				if (*size_description_ret) {
					memcpy(*description_ret, str_description_total.data(), *size_description_ret * sizeof(char));
				}
			}
		);
		if (exception_cause_current) {
			delete exception_cause_current;
			exception_cause_current = nullptr;
		}
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			if (!has_deleted_this) {
				delete this;
				has_deleted_this = true;
			}
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			if (!has_deleted_this) {
				delete this;
				has_deleted_this = true;
			}
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		if (has_deleted_this) abort();
		return this;
	}

	[[nodiscard]] IException* DoubleExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = DoubleExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* InvalidParameterException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_function;
				if (this->name_function && this->size_name_function) {
					objholder_strtmplparameter_name_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_function", this->name_function, this->size_name_function);
				} else {
					objholder_strtmplparameter_name_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_function", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_class_member_function;
				if (this->name_class_member_function && this->size_name_class_member_function) {
					objholder_strtmplparameter_name_class_member_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_class_member_function", this->name_class_member_function, this->size_name_class_member_function);
				} else {
					objholder_strtmplparameter_name_class_member_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_class_member_function", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				err_inner = InvalidParameterException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_function.get(),
						objholder_strtmplparameter_name_class_member_function.get()
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

	[[nodiscard]] IException* InvalidCallException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_function;
				if (this->name_function && this->size_name_function) {
					objholder_strtmplparameter_name_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_function", this->name_function, this->size_name_function);
				} else {
					objholder_strtmplparameter_name_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_function", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_class_member_function;
				if (this->name_class_member_function && this->size_name_class_member_function) {
					objholder_strtmplparameter_name_class_member_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_class_member_function", this->name_class_member_function, this->size_name_class_member_function);
				} else {
					objholder_strtmplparameter_name_class_member_function.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_class_member_function", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				err_inner = InvalidCallException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_function.get(),
						objholder_strtmplparameter_name_class_member_function.get()
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

	[[nodiscard]] IException* InsufficientBufferException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_buffer_insufficient;
				objholder_strtmplparameter_address_buffer_insufficient.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_buffer_insufficient", reinterpret_cast<uintptr_t>(this->address_buffer_insufficient));
				err_inner = InsufficientBufferException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_address_buffer_insufficient.get()
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

	[[nodiscard]] IException* MemoryAllocFailureException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = MemoryAllocFailureException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* KeyAlreadyExistException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = KeyAlreadyExistException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* KeyNotExistException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = KeyNotExistException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* UnhandledUnknownExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				err_inner = UnhandledUnknownExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
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

	[[nodiscard]] IException* STLExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_str_what_stlexception;
				if (this->str_what_stlexception && this->size_str_what_stlexception) {
					objholder_strtmplparameter_str_what_stlexception.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"str_what_stlexception", this->str_what_stlexception, this->size_str_what_stlexception);
				} else {
					objholder_strtmplparameter_str_what_stlexception.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"str_what_stlexception", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				err_inner = STLExceptionException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_str_what_stlexception.get()
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

	[[nodiscard]] IException* ExternalAPIFailureException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_name_api;
				if (this->name_api && this->size_name_api) {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", this->name_api, this->size_name_api);
				} else {
					objholder_strtmplparameter_name_api.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"name_api", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_api;
				objholder_strtmplparameter_address_api.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_api", reinterpret_cast<uintptr_t>(this->address_api));
				err_inner = ExternalAPIFailureException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_name_api.get(),
						objholder_strtmplparameter_address_api.get()
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

	[[nodiscard]] IException* UnexpectedExceptionException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_filename_source_code;
				if (this->filename_source_code && this->size_filename_source_code) {
					objholder_strtmplparameter_filename_source_code.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"filename_source_code", this->filename_source_code, this->size_filename_source_code);
				} else {
					objholder_strtmplparameter_filename_source_code.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"filename_source_code", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_linenumber_source_code;
				{
					char str_linenumber_source_code[sizeof(int) / sizeof(uint8_t) * 3 + 4];
					err_inner = SnPrintfUtf8(rawallocator_exception, str_linenumber_source_code, sizeof(str_linenumber_source_code) / sizeof(char), u8"%d", sizeof(u8"%d") / sizeof(char), this->linenumber_source_code);
					if (err_inner) return;
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
						objholder_strtmplparameter_filename_source_code.get(),
						objholder_strtmplparameter_linenumber_source_code.get()
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

	void YBWLIB2_CALLTYPE Exception_RealInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<IException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IException)), module_info_current);
		GetDynamicTypeClassObject<IDoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IDoubleExceptionException)), module_info_current);
		GetDynamicTypeClassObject<IInvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInvalidParameterException)), module_info_current);
		GetDynamicTypeClassObject<IInvalidCallException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInvalidCallException)), module_info_current);
		GetDynamicTypeClassObject<IInsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInsufficientBufferException)), module_info_current);
		GetDynamicTypeClassObject<IMemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IMemoryAllocFailureException)), module_info_current);
		GetDynamicTypeClassObject<IKeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyAlreadyExistException)), module_info_current);
		GetDynamicTypeClassObject<IKeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyNotExistException)), module_info_current);
		GetDynamicTypeClassObject<IUnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeClassObject<ISTLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISTLExceptionException)), module_info_current);
		GetDynamicTypeClassObject<IExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureException)), module_info_current);
		GetDynamicTypeClassObject<IUnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnexpectedExceptionException)), module_info_current);
		Exception::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<Exception>(),
			IsDynamicTypeModuleLocalClass<Exception>(),
			{ DynamicTypeBaseClassDef<Exception, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(Exception), alignof(Exception));
		DoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<DoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<DoubleExceptionException>(),
			{
				DynamicTypeBaseClassDef<DoubleExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<DoubleExceptionException, IDoubleExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(DoubleExceptionException), alignof(DoubleExceptionException));
		InvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<InvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<InvalidParameterException>(),
			{
				DynamicTypeBaseClassDef<InvalidParameterException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InvalidParameterException, IInvalidParameterException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InvalidParameterException), alignof(InvalidParameterException));
		InvalidCallException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<InvalidCallException>(),
			IsDynamicTypeModuleLocalClass<InvalidCallException>(),
			{
				DynamicTypeBaseClassDef<InvalidCallException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InvalidCallException, IInvalidCallException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InvalidCallException), alignof(InvalidCallException));
		InsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<InsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<InsufficientBufferException>(),
			{
				DynamicTypeBaseClassDef<InsufficientBufferException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InsufficientBufferException, IInsufficientBufferException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(InsufficientBufferException), alignof(InsufficientBufferException));
		MemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<MemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<MemoryAllocFailureException>(),
			{
				DynamicTypeBaseClassDef<MemoryAllocFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryAllocFailureException, IMemoryAllocFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(MemoryAllocFailureException), alignof(MemoryAllocFailureException));
		KeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<KeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<KeyAlreadyExistException>(),
			{
				DynamicTypeBaseClassDef<KeyAlreadyExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyAlreadyExistException, IKeyAlreadyExistException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(KeyAlreadyExistException), alignof(KeyAlreadyExistException));
		KeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<KeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<KeyNotExistException>(),
			{
				DynamicTypeBaseClassDef<KeyNotExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyNotExistException, IKeyNotExistException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(KeyNotExistException), alignof(KeyNotExistException));
		UnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<UnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnhandledUnknownExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, IUnhandledUnknownExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(UnhandledUnknownExceptionException), alignof(UnhandledUnknownExceptionException));
		STLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<STLExceptionException>(),
			IsDynamicTypeModuleLocalClass<STLExceptionException>(),
			{
				DynamicTypeBaseClassDef<STLExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<STLExceptionException, ISTLExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(STLExceptionException), alignof(STLExceptionException));
		ExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<ExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ExternalAPIFailureException), alignof(ExternalAPIFailureException));
		UnexpectedExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<UnexpectedExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnexpectedExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnexpectedExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnexpectedExceptionException, IUnexpectedExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(UnexpectedExceptionException), alignof(UnexpectedExceptionException));
		GetDynamicTypeClassObject<Exception>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Exception)), module_info_current);
		GetDynamicTypeClassObject<DoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(DoubleExceptionException)), module_info_current);
		GetDynamicTypeClassObject<InvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InvalidParameterException)), module_info_current);
		GetDynamicTypeClassObject<InvalidCallException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InvalidCallException)), module_info_current);
		GetDynamicTypeClassObject<InsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InsufficientBufferException)), module_info_current);
		GetDynamicTypeClassObject<MemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(MemoryAllocFailureException)), module_info_current);
		GetDynamicTypeClassObject<KeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyAlreadyExistException)), module_info_current);
		GetDynamicTypeClassObject<KeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyNotExistException)), module_info_current);
		GetDynamicTypeClassObject<UnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeClassObject<STLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(STLExceptionException)), module_info_current);
		GetDynamicTypeClassObject<ExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureException)), module_info_current);
		GetDynamicTypeClassObject<UnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnexpectedExceptionException)), module_info_current);
		fnptr_wrap_function_catch_exceptions_raw_old_Exception = ExchangeRawWrapFunctionCatchExceptionsFnptr(ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local, &WrapFunctionCatchExceptionsRaw_Exception);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept {
		ExchangeRawWrapFunctionCatchExceptionsFnptr(ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local, fnptr_wrap_function_catch_exceptions_raw_old_Exception);
		fnptr_wrap_function_catch_exceptions_raw_old_Exception = nullptr;
		GetDynamicTypeClassObject<UnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<ExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<STLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<UnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<KeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<KeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<MemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<InsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<InvalidCallException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<InvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<DoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<Exception>()->UnRegisterTypeInfoWrapper(module_info_current);
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
		GetDynamicTypeClassObject<IUnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<ISTLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IUnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IKeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IKeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IMemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IInsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IInvalidCallException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IInvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IDoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}

	static IException* YBWLIB2_CALLTYPE WrapFunctionCatchExceptionsRaw_Exception(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept {
		if (!_fnptr_inner) {
			IException* err_double_exception = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
			err_double_exception->AttachCause(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::WrapFunctionCatchExceptionsRaw_Exception));
			return err_double_exception;
		}
		if (!fnptr_wrap_function_catch_exceptions_raw_old_Exception) {
			IException* err_double_exception = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
			err_double_exception->AttachCause(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			return err_double_exception;
		}
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
