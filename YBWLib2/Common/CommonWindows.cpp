#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "../Exception/Exception.h"
#include "../Exception/ExceptionWindows.h"
#include "Common.h"
#include "CommonSTLHelper.h"
#include "CommonWindows.h"
#include "CommonSTLHelperWindows.h"

namespace YBWLib2 {
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE AnsiStringToUtf16String(
		const rawallocator_t* rawallocator,
		char16_t** str_out_ret,
		size_t* size_str_out_ret,
		const char* str_in,
		size_t size_str_in
	) noexcept {
		static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
		if (!str_in && size_str_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out_ret, &size_str_out_ret, &str_in, &size_str_in, &err_inner]() noexcept(false)->void {
				if (!size_str_in) {
					*size_str_out_ret = 0;
					*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String); return; }
					*size_str_out_ret = MultiByteToWideChar(CP_ACP, 0, str_in, size_str_in & ~(unsigned int)0, nullptr, 0);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)MultiByteToWideChar(CP_ACP, 0, str_in, size_str_in & ~(unsigned int)0, reinterpret_cast<wchar_t*>(*str_out_ret), *size_str_out_ret & ~(unsigned int)0) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					}
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf16StringToAnsiString(
		const rawallocator_t* rawallocator,
		char** str_out_ret,
		size_t* size_str_out_ret,
		const char16_t* str_in,
		size_t size_str_in
	) noexcept {
		static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
		if (!str_in && size_str_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out_ret, &size_str_out_ret, &str_in, &size_str_in, &err_inner]() noexcept(false)->void {
				if (!size_str_in) {
					*size_str_out_ret = 0;
					*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString); return; }
					*size_str_out_ret = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, *str_out_ret, *size_str_out_ret & ~(unsigned int)0, nullptr, nullptr) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					}
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE Win32HandleHolder::ClearWin32Handle(HANDLE* _win32handle, bool _is_owned_handle) noexcept {
		if (_win32handle && *_win32handle) {
			if (_is_owned_handle) CloseHandle(*_win32handle);
			*_win32handle = NULL;
		}
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Win32HandleHolder::CopyWin32Handle(HANDLE _win32handle_from, HANDLE* _win32handle_to) noexcept {
		if (!_win32handle_from || !_win32handle_to) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32HandleHolder, CopyWin32Handle);
		if (!DuplicateHandle(GetCurrentProcess(), _win32handle_from, GetCurrentProcess(), _win32handle_to, 0, FALSE, DUPLICATE_SAME_ACCESS))
			return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(DuplicateHandle);
		return nullptr;
	}

	void YBWLIB2_CALLTYPE CommonWindows_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE CommonWindows_RealUnInitGlobal() noexcept {}
}
