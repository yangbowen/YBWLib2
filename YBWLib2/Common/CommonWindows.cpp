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
					*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String); return; }
					*size_str_out_ret = MultiByteToWideChar(CP_ACP, 0, str_in, size_str_in & ~(unsigned int)0, nullptr, 0);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::AnsiStringToUtf16String);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)MultiByteToWideChar(CP_ACP, 0, str_in, size_str_in & ~(unsigned int)0, reinterpret_cast<wchar_t*>(*str_out_ret), *size_str_out_ret & ~(unsigned int)0) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
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
					*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString); return; }
					*size_str_out_ret = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToAnsiString);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, *str_out_ret, *size_str_out_ret & ~(unsigned int)0, nullptr, nullptr) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
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

	void YBWLIB2_CALLTYPE CommonWindows_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE CommonWindows_RealUnInitGlobal() noexcept {}
}
