#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <climits>
#include <atomic>
#include "../Windows.h"

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../Exception/Exception.h"
#include "../Exception/ExceptionWindows.h"
#include "UserInterface.h"
#include "UserInterfaceWindows.h"

namespace YBWLib2 {
	YBWLIB2_API HMODULE YBWLIB2_CALLTYPE GetNtdllHmodule() noexcept;

	static ::std::atomic<HMODULE> atomic_hmod_ntdll(NULL);

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE GetWindowsMessageStringUTF8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		bool is_system_message_table_searched,
		bool is_module_message_table_searched,
		HMODULE hmod,
		DWORD messageid
	) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out, &size_max_str_out, &is_system_message_table_searched, &is_module_message_table_searched, &hmod, &messageid, &err_inner]() noexcept(false)->void {
				if (!rawallocator) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				if (!str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				if (!size_max_str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				if (!is_system_message_table_searched && !is_module_message_table_searched) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
#ifdef _WIN32_WINNT
				struct wchar_array_holder_t {
					wchar_t* ptr = nullptr;
					size_t size = 0;
					const rawallocator_t* rawallocator = nullptr;
					inline wchar_array_holder_t(wchar_t* _ptr, size_t _size, const rawallocator_t* _rawallocator) noexcept : ptr(_ptr), size(_size), rawallocator(_rawallocator) {}
					wchar_array_holder_t(const wchar_array_holder_t&) = delete;
					wchar_array_holder_t(wchar_array_holder_t&&) = delete;
					inline ~wchar_array_holder_t() {
						if (this->ptr) {
							if (!this->rawallocator->Deallocate(this->ptr, this->size * sizeof(wchar_t))) abort();
							this->ptr = nullptr;
							this->size = 0;
						}
						this->rawallocator = nullptr;
					}
					wchar_array_holder_t& operator=(const wchar_array_holder_t&) = delete;
					wchar_array_holder_t& operator=(wchar_array_holder_t&&) = delete;
				};
				size_t cch_max_u16str_out = size_max_str_out;
				if (cch_max_u16str_out > 0x10000 / sizeof(wchar_t)) cch_max_u16str_out = 0x10000 / sizeof(wchar_t);
				if (cch_max_u16str_out > MAXDWORD) cch_max_u16str_out = MAXDWORD;
				wchar_array_holder_t u16str_out(reinterpret_cast<wchar_t*>(rawallocator->Allocate(cch_max_u16str_out * sizeof(wchar_t))), cch_max_u16str_out, rawallocator);
				if (!u16str_out.ptr) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				size_t cch_u16str_out = 0;
				{
					cch_u16str_out = FormatMessageW(
						(is_module_message_table_searched ? FORMAT_MESSAGE_FROM_HMODULE : 0) | (is_system_message_table_searched ? FORMAT_MESSAGE_FROM_SYSTEM : 0) | FORMAT_MESSAGE_IGNORE_INSERTS,
						is_module_message_table_searched ? static_cast<const void*>(hmod) : nullptr,
						messageid,
						0,
						u16str_out.ptr,
						cch_max_u16str_out & ~(DWORD)0,
						nullptr
					);
					if (!cch_u16str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(FormatMessageW); return; }
					++cch_u16str_out;
					if (cch_u16str_out > cch_max_u16str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				}
				if (cch_u16str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				unsigned int cb_u8str_out = WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
				if (!cb_u8str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
				if (cb_u8str_out > size_max_str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INSUFFICIENT_BUFFER_EXCEPTION(str_out); return; }
				if (size_max_str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				if (cch_u16str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GetWindowsMessageStringUTF8); return; }
				if (!WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, str_out, size_max_str_out & ~(unsigned int)0, nullptr, nullptr)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
#else
#error This platform is not supported yet.
#endif
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		} else {
			return err_inner;
		}
	}

	YBWLIB2_API HMODULE YBWLIB2_CALLTYPE GetNtdllHmodule() noexcept {
		return atomic_hmod_ntdll.load();
	}

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealInitGlobal() noexcept {
		{
			HMODULE _hmod_ntdll = LoadLibraryExW(L"ntdll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
			if (!_hmod_ntdll) abort();
			_hmod_ntdll = atomic_hmod_ntdll.exchange(_hmod_ntdll);
			if (_hmod_ntdll) {
				if (!FreeLibrary(_hmod_ntdll)) abort();
				_hmod_ntdll = nullptr;
			}
		}
	}

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealUnInitGlobal() noexcept {
		{
			HMODULE _hmod_ntdll = NULL;
			_hmod_ntdll = atomic_hmod_ntdll.exchange(_hmod_ntdll);
			if (_hmod_ntdll) {
				if (!FreeLibrary(_hmod_ntdll)) abort();
				_hmod_ntdll = nullptr;
			}
		}
	}
}
