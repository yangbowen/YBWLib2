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
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32HandleStringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(LastErrorStringTemplateParameter, );
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(WSALastErrorStringTemplateParameter, );
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(NTSTATUSStringTemplateParameter, );
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(HRESULTStringTemplateParameter, );
#endif

	YBWLIB2_API HMODULE YBWLIB2_CALLTYPE GetNtdllHmodule() noexcept;

	[[nodiscard]] IException* Win32HandleStringTemplateParameter::GenerateString(
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
				allocator_rawallocator_t<char> allocator_rawallocator_char(*_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[Win32Handle "s;
				{
					using integral_HANDLE_t = ::std::conditional_t<::std::is_integral_v<HANDLE>, HANDLE, ::std::conditional_t<::std::is_pointer_v<HANDLE>, uintptr_t, void>>;
					static_assert(!::std::is_void_v<integral_HANDLE_t>, "Cannot obtain the corresponding integral type of HANDLE.");
					char str_win32handle[sizeof(integral_HANDLE_t) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<integral_HANDLE_t>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<integral_HANDLE_t>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<integral_HANDLE_t>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(_rawallocator, str_win32handle, sizeof(str_win32handle) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(::std::make_unsigned_t<integral_HANDLE_t>) / sizeof(uint8_t) * 2), this->GetWin32Handle());
					if (err_inner) return;
					str_out += str_out_t(str_win32handle, strnlen(str_win32handle, sizeof(integral_HANDLE_t) / sizeof(uint8_t) * 3 + 4), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		}
		if (err_inner) {
			if (*str_out_ret) {
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
		return nullptr;
	}

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
				allocator_rawallocator_t<char> allocator_rawallocator_char(*_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[GetLastError "s;
				{
					char str_lasterr[sizeof(DWORD) / sizeof(uint8_t) * 3 + 4];
					static constexpr char str_prefix_fmt[] = u8"%";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<DWORD>::fmtspec_printf_u_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<DWORD>::fmtspec_printf_u_utf8, sizeof(inttype_traits_t<DWORD>::fmtspec_printf_u_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(_rawallocator, str_lasterr, sizeof(str_lasterr) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), this->GetLastErrorCode());
					if (err_inner) return;
					str_out += str_out_t(str_lasterr, strnlen(str_lasterr, sizeof(DWORD) / sizeof(uint8_t) * 3 + 4), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_lasterr_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_lasterr_t vec_char_message_lasterr(allocator_rawallocator_char);
					vec_char_message_lasterr.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_lasterr.data(), vec_char_message_lasterr.size(), true, false, NULL, this->GetLastErrorCode(), true);
					if (err_inner) return;
					vec_char_message_lasterr.resize(strnlen(vec_char_message_lasterr.data(), vec_char_message_lasterr.size()));
					for (; !vec_char_message_lasterr.empty() && (vec_char_message_lasterr.back() == '\r' || vec_char_message_lasterr.back() == '\n'); vec_char_message_lasterr.pop_back());
					str_out += str_out_t(vec_char_message_lasterr.data(), vec_char_message_lasterr.size(), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		}
		if (err_inner) {
			if (*str_out_ret) {
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
		return nullptr;
	}

#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
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
				allocator_rawallocator_t<char> allocator_rawallocator_char(*_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[WSAGetLastError "s;
				{
					char str_wsalasterr[sizeof(int) / sizeof(uint8_t) * 3 + 4];
					static constexpr char str_prefix_fmt[] = u8"%";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<int>::fmtspec_printf_d_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<int>::fmtspec_printf_d_utf8, sizeof(inttype_traits_t<int>::fmtspec_printf_d_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(_rawallocator, str_wsalasterr, sizeof(str_wsalasterr) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), this->GetWSALastErrorCode());
					if (err_inner) return;
					str_out += str_out_t(str_wsalasterr, strnlen(str_wsalasterr, sizeof(int) / sizeof(uint8_t) * 3 + 4), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_wsalasterr_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_wsalasterr_t vec_char_message_wsalasterr(allocator_rawallocator_char);
					vec_char_message_wsalasterr.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_wsalasterr.data(), vec_char_message_wsalasterr.size(), true, false, NULL, (DWORD)this->GetWSALastErrorCode(), true);
					if (err_inner) return;
					vec_char_message_wsalasterr.resize(strnlen(vec_char_message_wsalasterr.data(), vec_char_message_wsalasterr.size()));
					for (; !vec_char_message_wsalasterr.empty() && (vec_char_message_wsalasterr.back() == '\r' || vec_char_message_wsalasterr.back() == '\n'); vec_char_message_wsalasterr.pop_back());
					str_out += str_out_t(vec_char_message_wsalasterr.data(), vec_char_message_wsalasterr.size(), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		}
		if (err_inner) {
			if (*str_out_ret) {
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
		return nullptr;
	}
#endif

#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
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
				allocator_rawallocator_t<char> allocator_rawallocator_char(*_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[NTSTATUS "s;
				{
					char str_ntstatus[sizeof(::std::make_unsigned_t<NTSTATUS>) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<::std::make_unsigned_t<NTSTATUS>>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(_rawallocator, str_ntstatus, sizeof(str_ntstatus) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(::std::make_unsigned_t<NTSTATUS>) / sizeof(uint8_t) * 2), (::std::make_unsigned_t<NTSTATUS>)this->GetNTSTATUSCode());
					if (err_inner) return;
					str_out += str_out_t(str_ntstatus, strnlen(str_ntstatus, sizeof(::std::make_unsigned_t<NTSTATUS>) / sizeof(uint8_t) * 2 + 16), allocator_rawallocator_char);
				}
				str_out += u8" "s;
				{
					using vec_char_message_ntstatus_t = ::std::vector<char, allocator_rawallocator_t<char>>;
					vec_char_message_ntstatus_t vec_char_message_ntstatus(allocator_rawallocator_char);
					vec_char_message_ntstatus.resize(4096);
					err_inner = GetWindowsMessageStringUTF8(_rawallocator, vec_char_message_ntstatus.data(), vec_char_message_ntstatus.size(), true, false, GetNtdllHmodule(), (DWORD)this->GetNTSTATUSCode(), true);
					if (err_inner) return;
					vec_char_message_ntstatus.resize(strnlen(vec_char_message_ntstatus.data(), vec_char_message_ntstatus.size()));
					for (; !vec_char_message_ntstatus.empty() && (vec_char_message_ntstatus.back() == '\r' || vec_char_message_ntstatus.back() == '\n'); vec_char_message_ntstatus.pop_back());
					str_out += str_out_t(vec_char_message_ntstatus.data(), vec_char_message_ntstatus.size(), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		}
		if (err_inner) {
			if (*str_out_ret) {
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
		return nullptr;
	}
#endif

#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
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
				allocator_rawallocator_t<char> allocator_rawallocator_char(*_rawallocator);
				using str_out_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
				str_out_t str_out(allocator_rawallocator_char);
				str_out += u8"[HRESULT "s;
				{
					char str_hresult[sizeof(HRESULT) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<::std::make_unsigned_t<HRESULT>>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(_rawallocator, str_hresult, sizeof(str_hresult) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(::std::make_unsigned_t<HRESULT>) / sizeof(uint8_t) * 2), (::std::make_unsigned_t<HRESULT>)this->GetHRESULTCode());
					if (err_inner) return;
					str_out += str_out_t(str_hresult, strnlen(str_hresult, sizeof(HRESULT) / sizeof(uint8_t) * 2 + 16), allocator_rawallocator_char);
				}
				str_out += u8"]"s;
				*size_str_out_ret = should_null_terminate ? str_out.size() + 1 : str_out.size();
				*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err;
		}
		if (err_inner) {
			if (*str_out_ret) {
				_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
			}
			return err_inner;
		}
		return nullptr;
	}
#endif

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealInitModuleLocal() noexcept {
		Win32HandleStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<Win32HandleStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<Win32HandleStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<Win32HandleStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(Win32HandleStringTemplateParameter), alignof(Win32HandleStringTemplateParameter));
		LastErrorStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<LastErrorStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<LastErrorStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<LastErrorStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(LastErrorStringTemplateParameter), alignof(LastErrorStringTemplateParameter));
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
		WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<WSALastErrorStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<WSALastErrorStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<WSALastErrorStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(WSALastErrorStringTemplateParameter), alignof(WSALastErrorStringTemplateParameter));
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
		NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<NTSTATUSStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<NTSTATUSStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<NTSTATUSStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(NTSTATUSStringTemplateParameter), alignof(NTSTATUSStringTemplateParameter));
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
		HRESULTStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<HRESULTStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<HRESULTStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<HRESULTStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(HRESULTStringTemplateParameter), alignof(HRESULTStringTemplateParameter));
#endif
		GetDynamicTypeClassObject<Win32HandleStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32HandleStringTemplateParameter)), module_info_current);
		GetDynamicTypeClassObject<LastErrorStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(LastErrorStringTemplateParameter)), module_info_current);
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
		GetDynamicTypeClassObject<WSALastErrorStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(WSALastErrorStringTemplateParameter)), module_info_current);
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
		GetDynamicTypeClassObject<NTSTATUSStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(NTSTATUSStringTemplateParameter)), module_info_current);
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
		GetDynamicTypeClassObject<HRESULTStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(HRESULTStringTemplateParameter)), module_info_current);
#endif
	}

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealUnInitModuleLocal() noexcept {
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
		GetDynamicTypeClassObject<HRESULTStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
		GetDynamicTypeClassObject<NTSTATUSStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
		GetDynamicTypeClassObject<WSALastErrorStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#endif
		GetDynamicTypeClassObject<LastErrorStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<Win32HandleStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_HRESULT
		delete HRESULTStringTemplateParameter::DynamicTypeThisClassObject;
		HRESULTStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_NTSTATUS
		delete NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject;
		NTSTATUSStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
#ifndef YBWLIB2_USERINTERFACE_WINDOWS_NO_WSA
		delete WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject;
		WSALastErrorStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
#endif
		delete LastErrorStringTemplateParameter::DynamicTypeThisClassObject;
		LastErrorStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
		delete Win32HandleStringTemplateParameter::DynamicTypeThisClassObject;
		Win32HandleStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
