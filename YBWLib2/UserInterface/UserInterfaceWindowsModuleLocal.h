#ifndef _INCLUDE_GUARD_8AD873EC_547C_47BD_8700_5815A9E35AE9
#define _INCLUDE_GUARD_8AD873EC_547C_47BD_8700_5815A9E35AE9

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <cstdint>
#include <climits>
#include <string>
#include <vector>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "UserInterface.h"
#include "UserInterfaceWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(LastErrorStringTemplateParameter, );
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(WSALastErrorStringTemplateParameter, );
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(NTSTATUSStringTemplateParameter, );
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(HRESULTStringTemplateParameter, );
#endif

	YBWLIB2_API HMODULE YBWLIB2_CALLTYPE GetNtdllHmodule() noexcept;

	[[nodiscard]] IException* LastErrorStringTemplateParameter::GenerateString(
		const char* str_options,
		size_t size_str_options,
		char** str_out_ret,
		size_t* size_str_out_ret,
		bool should_null_terminate,
		const rawallocator_t* _rawallocator
	) const noexcept {
		using namespace ::std::string_literals;
		static_cast<void>(str_options);
		if (size_str_options) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		*str_out_ret = nullptr;
		*size_str_out_ret = 0;
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
				if (!_rawallocator) _rawallocator = this->GetRawAllocator();
				allocator_rawallocator_t<char> allocator_rawallocator_char(_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[GetLastError "s;
				{
					char str_lasterr[sizeof(DWORD) / sizeof(uint8_t) * 3 + 4];
					static constexpr char str_prefix_fmt[] = u8"%";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<DWORD>::fmtspec_printf_u_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<DWORD>::fmtspec_printf_u_utf8, sizeof(inttype_traits_t<DWORD>::fmtspec_printf_u_utf8) / sizeof(char));
					IException* err_utf8_snprintf = utf8_snprintf(_rawallocator, str_lasterr, sizeof(str_lasterr) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), this->GetLastErrorCode());
					if (err_utf8_snprintf) { err_inner = err_utf8_snprintf; return; }
					str_out += str_out_t(str_lasterr, strnlen(str_lasterr, sizeof(DWORD) / sizeof(uint8_t) * 3 + 4), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_lasterr_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_lasterr_t vec_char_message_lasterr(allocator_rawallocator_char);
					vec_char_message_lasterr.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_lasterr.data(), vec_char_message_lasterr.size(), true, false, NULL, this->GetLastErrorCode());
					if (err_inner) return;
					str_out += str_out_t(vec_char_message_lasterr.data(), strnlen(vec_char_message_lasterr.data(), vec_char_message_lasterr.size()), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(this->rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
				if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (*size_str_out_ret) {
					memcpy(*str_out_ret, str_out.c_str(), *size_str_out_ret * sizeof(char));
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		} else {
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
	}

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	[[nodiscard]] IException* WSALastErrorStringTemplateParameter::GenerateString(
		const char* str_options,
		size_t size_str_options,
		char** str_out_ret,
		size_t* size_str_out_ret,
		bool should_null_terminate,
		const rawallocator_t* _rawallocator
	) const noexcept {
		using namespace ::std::string_literals;
		static_cast<void>(str_options);
		if (size_str_options) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		*str_out_ret = nullptr;
		*size_str_out_ret = 0;
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
				if (!_rawallocator) _rawallocator = this->GetRawAllocator();
				allocator_rawallocator_t<char> allocator_rawallocator_char(_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[WSAGetLastError "s;
				{
					char str_wsalasterr[sizeof(int) / sizeof(uint8_t) * 3 + 4];
					static constexpr char str_prefix_fmt[] = u8"%";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<int>::fmtspec_printf_d_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<int>::fmtspec_printf_d_utf8, sizeof(inttype_traits_t<int>::fmtspec_printf_d_utf8) / sizeof(char));
					IException* err_utf8_snprintf = utf8_snprintf(_rawallocator, str_wsalasterr, sizeof(str_wsalasterr) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), this->GetWSALastErrorCode());
					if (err_utf8_snprintf) { err_inner = err_utf8_snprintf; return; }
					str_out += str_out_t(str_wsalasterr, strnlen(str_wsalasterr, sizeof(int) / sizeof(uint8_t) * 3 + 4), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_wsalasterr_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_wsalasterr_t vec_char_message_wsalasterr(allocator_rawallocator_char);
					vec_char_message_wsalasterr.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_wsalasterr.data(), vec_char_message_wsalasterr.size(), true, false, NULL, (DWORD)this->GetWSALastErrorCode());
					if (err_inner) return;
					str_out += str_out_t(vec_char_message_wsalasterr.data(), strnlen(vec_char_message_wsalasterr.data(), vec_char_message_wsalasterr.size()), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(this->rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
				if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (*size_str_out_ret) {
					memcpy(*str_out_ret, str_out.c_str(), *size_str_out_ret * sizeof(char));
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		} else {
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
	}
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	[[nodiscard]] IException* NTSTATUSStringTemplateParameter::GenerateString(
		const char* str_options,
		size_t size_str_options,
		char** str_out_ret,
		size_t* size_str_out_ret,
		bool should_null_terminate,
		const rawallocator_t* _rawallocator
	) const noexcept {
		using namespace ::std::string_literals;
		static_cast<void>(str_options);
		if (size_str_options) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		*str_out_ret = nullptr;
		*size_str_out_ret = 0;
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
				if (!_rawallocator) _rawallocator = this->GetRawAllocator();
				allocator_rawallocator_t<char> allocator_rawallocator_char(_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[NTSTATUS "s;
				{
					char str_ntstatus[sizeof(int) / sizeof(uint8_t) * 2 + 4];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8) / sizeof(char));
					IException* err_utf8_snprintf = utf8_snprintf(_rawallocator, str_ntstatus, sizeof(str_ntstatus) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), sizeof(::std::make_unsigned_t<NTSTATUS>) / sizeof(uint8_t) * 8, (::std::make_unsigned_t<NTSTATUS>)this->GetNTSTATUSCode());
					if (err_utf8_snprintf) { err_inner = err_utf8_snprintf; return; }
					str_out += str_out_t(str_ntstatus, strnlen(str_ntstatus, sizeof(int) / sizeof(uint8_t) * 2 + 4), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_ntstatus_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_ntstatus_t vec_char_message_ntstatus(allocator_rawallocator_char);
					vec_char_message_ntstatus.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_ntstatus.data(), vec_char_message_ntstatus.size(), true, false, GetNtdllHmodule(), (DWORD)this->GetNTSTATUSCode());
					if (err_inner) return;
					str_out += str_out_t(vec_char_message_ntstatus.data(), strnlen(vec_char_message_ntstatus.data(), vec_char_message_ntstatus.size()), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(this->rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
				if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (*size_str_out_ret) {
					memcpy(*str_out_ret, str_out.c_str(), *size_str_out_ret * sizeof(char));
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		} else {
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
	}
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	[[nodiscard]] IException* HRESULTStringTemplateParameter::GenerateString(
		const char* str_options,
		size_t size_str_options,
		char** str_out_ret,
		size_t* size_str_out_ret,
		bool should_null_terminate,
		const rawallocator_t* _rawallocator
	) const noexcept {
		using namespace ::std::string_literals;
		static_cast<void>(str_options);
		if (size_str_options) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
		*str_out_ret = nullptr;
		*size_str_out_ret = 0;
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
				if (!_rawallocator) _rawallocator = this->GetRawAllocator();
				allocator_rawallocator_t<char> allocator_rawallocator_char(_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[HRESULT "s;
				{
					char str_hresult[sizeof(HRESULT) / sizeof(uint8_t) * 2 + 4];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8) / sizeof(char));
					IException* err_utf8_snprintf = utf8_snprintf(_rawallocator, str_hresult, sizeof(str_hresult) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), sizeof(::std::make_unsigned_t<HRESULT>) / sizeof(uint8_t) * 8, (::std::make_unsigned_t<HRESULT>)this->GetHRESULTCode());
					if (err_utf8_snprintf) { err_inner = err_utf8_snprintf; return; }
					str_out += str_out_t(str_hresult, strnlen(str_hresult, sizeof(HRESULT) / sizeof(uint8_t) * 2 + 4), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(this->rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
				if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (*size_str_out_ret) {
					memcpy(*str_out_ret, str_out.c_str(), *size_str_out_ret * sizeof(char));
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		} else {
			if (*str_out_ret) {
				if (!_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret)) abort();
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
	}
#endif

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealInitModuleLocal() noexcept {
		LastErrorStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<LastErrorStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<LastErrorStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<LastErrorStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(LastErrorStringTemplateParameter), alignof(LastErrorStringTemplateParameter));
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<WSALastErrorStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<WSALastErrorStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<WSALastErrorStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(WSALastErrorStringTemplateParameter), alignof(WSALastErrorStringTemplateParameter));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<NTSTATUSStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<NTSTATUSStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<NTSTATUSStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(NTSTATUSStringTemplateParameter), alignof(NTSTATUSStringTemplateParameter));
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		HRESULTStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<HRESULTStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<HRESULTStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<HRESULTStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(HRESULTStringTemplateParameter), alignof(HRESULTStringTemplateParameter));
#endif
		GetDynamicTypeThisClassObject<LastErrorStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(LastErrorStringTemplateParameter)), module_info_current);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<WSALastErrorStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(WSALastErrorStringTemplateParameter)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<NTSTATUSStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(NTSTATUSStringTemplateParameter)), module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<HRESULTStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(HRESULTStringTemplateParameter)), module_info_current);
#endif
	}

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealUnInitModuleLocal() noexcept {
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		GetDynamicTypeThisClassObject<HRESULTStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		GetDynamicTypeThisClassObject<NTSTATUSStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		GetDynamicTypeThisClassObject<WSALastErrorStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
		GetDynamicTypeThisClassObject<LastErrorStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
		delete HRESULTStringTemplateParameter::DynamicTypeThisClassObject;
		HRESULTStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
		delete NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject;
		NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
		delete WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject;
		WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
		delete LastErrorStringTemplateParameter::DynamicTypeThisClassObject;
		LastErrorStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
