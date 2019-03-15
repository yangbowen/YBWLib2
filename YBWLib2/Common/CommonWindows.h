﻿#ifndef _WIN32_WINNT
#error This header file is only to be used when you're targeting Microsoft Windows. If you are, set the targetted windows version before including this header file.
#endif

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_83D6146A_4FDA_461C_84C5_8247F88A40CA
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B2352359_1626_4CF1_AEBF_4F58A5F48AD7
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_B9D2E995_F86E_4578_B986_64C314F7A9EE
#define _INCLUDE_GUARD_B9D2E995_F86E_4578_B986_64C314F7A9EE

#include <cstdint>
#include <type_traits>
#include "CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Exception/ExceptionWindows.h"
#include "Common.h"

namespace YBWLib2 {
	/// <summary>Converts an ANSI string into a UTF-16 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output string, in UTF-16.
	/// After successfully returning from this function, <c>*str_out_ret</c> will be set to the output string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_out_ret">
	/// Pointer to a variable that receives the size (in <c>char16_t</c>s) of the output string, in UTF-16.
	/// After successfully returning from this function, <c>*size_str_out_ret</c> will be set to the size (in <c>char16_t</c>s) of the output string.
	/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_in">Pointer to the input string, in ANSI.</param>
	/// <param name="size_str_in">The size, in <c>char</c>s, of the input string, in ANSI, pointed to by <c>str_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE AnsiStringToUtf16String(
		const rawallocator_t* rawallocator,
		char16_t** str_out_ret,
		size_t* size_str_out_ret,
		const char* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output string, in ANSI.
	/// After successfully returning from this function, <c>*str_out_ret</c> will be set to the output string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_out_ret">
	/// Pointer to a variable that receives the size (in <c>char</c>s) of the output string, in ANSI.
	/// After successfully returning from this function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the output string.
	/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_in">Pointer to the input string, in UTF-16.</param>
	/// <param name="size_str_in">The size, in <c>char16_t</c>s, of the input string, in UTF-16, pointed to by <c>str_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf16StringToAnsiString(
		const rawallocator_t* rawallocator,
		char** str_out_ret,
		size_t* size_str_out_ret,
		const char16_t* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Win32 handle holder.</summary>
	class Win32HandleHolder {
	public:
		struct view_handle_t {};
		struct own_handle_t {};
		struct no_eliminate_invalid_handle_value_t {};

		static constexpr view_handle_t view_handle {};
		static constexpr own_handle_t own_handle {};
		static constexpr no_eliminate_invalid_handle_value_t no_eliminate_invalid_handle_value {};

		inline constexpr Win32HandleHolder() noexcept {}
		inline constexpr Win32HandleHolder(view_handle_t, const HANDLE& _handle) noexcept : handle(_handle == INVALID_HANDLE_VALUE ? NULL : _handle), is_owned_handle(false) {}
		inline constexpr Win32HandleHolder(view_handle_t, no_eliminate_invalid_handle_value_t, const HANDLE& _handle) noexcept : handle(_handle), is_owned_handle(false) {}
		inline constexpr Win32HandleHolder(own_handle_t, HANDLE&& _handle) noexcept : handle(_handle == INVALID_HANDLE_VALUE ? NULL : _handle), is_owned_handle(true) {
			_handle = NULL;
		}
		inline constexpr Win32HandleHolder(own_handle_t, no_eliminate_invalid_handle_value_t, HANDLE&& _handle) noexcept : handle(_handle), is_owned_handle(true) {
			_handle = NULL;
		}
		inline Win32HandleHolder(const Win32HandleHolder& x) noexcept(false) {
			if (x.handle) {
				IException* err = Win32HandleHolder::CopyHandle(x.handle, &this->handle);
				if (err) throw(err);
				this->is_owned_handle = true;
			} else {
				this->handle = NULL;
				this->is_owned_handle = false;
			}
		}
		inline Win32HandleHolder(Win32HandleHolder&& x) noexcept {
			this->handle = ::std::move(x.handle);
			x.handle = NULL;
			this->is_owned_handle = ::std::move(x.is_owned_handle);
			x.is_owned_handle = false;
		}
		inline virtual ~Win32HandleHolder() {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
		}
		inline Win32HandleHolder& operator=(const Win32HandleHolder& x) noexcept(false) {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			if (x.handle) {
				IException* err = Win32HandleHolder::CopyHandle(x.handle, &this->handle);
				if (err) throw(err);
				this->is_owned_handle = true;
			} else {
				this->handle = NULL;
				this->is_owned_handle = false;
			}
		}
		inline Win32HandleHolder& operator=(Win32HandleHolder&& x) noexcept {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			this->handle = ::std::move(x.handle);
			x.handle = NULL;
			this->is_owned_handle = ::std::move(x.is_owned_handle);
			x.is_owned_handle = false;
		}
		inline void swap(Win32HandleHolder& x) noexcept {
			HANDLE handle_temp = this->handle;
			bool is_owned_handle_temp = this->is_owned_handle;
			this->handle = x.handle;
			this->is_owned_handle = x.is_owned_handle;
			x.handle = handle_temp;
			x.is_owned_handle = is_owned_handle_temp;
		}
		inline void reset(view_handle_t, const HANDLE& _handle) noexcept {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			this->handle = _handle == INVALID_HANDLE_VALUE ? NULL : _handle;
			this->is_owned_handle = false;
		}
		inline void reset(view_handle_t, no_eliminate_invalid_handle_value_t, const HANDLE& _handle) noexcept {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			this->handle = _handle;
			this->is_owned_handle = false;
		}
		inline void reset(own_handle_t, HANDLE&& _handle) noexcept {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			this->handle = _handle == INVALID_HANDLE_VALUE ? NULL : _handle;
			_handle = NULL;
			this->is_owned_handle = true;
		}
		inline void reset(own_handle_t, no_eliminate_invalid_handle_value_t, HANDLE&& _handle) noexcept {
			Win32HandleHolder::ClearHandle(&this->handle);
			this->is_owned_handle = false;
			this->handle = _handle;
			_handle = NULL;
			this->is_owned_handle = true;
		}
		inline HANDLE get() const noexcept { return this->handle; }
		inline operator bool() const noexcept { return this->handle; }
	protected:
		HANDLE handle = NULL;
		bool is_owned_handle = false;
		static YBWLIB2_API void YBWLIB2_CALLTYPE ClearHandle(HANDLE* _handle) noexcept;
		[[nodiscard]] static YBWLIB2_API IException* YBWLIB2_CALLTYPE CopyHandle(HANDLE _handle_from, HANDLE* _handle_to) noexcept;
	};
	template<typename _Char_Ty, typename _Traits_Ty>
	inline ::std::basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(::std::basic_ostream<_Char_Ty, _Traits_Ty>& os, const Win32HandleHolder& x) {
		return os << x.get();
	}
	inline bool operator==(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() == r.get(); }
	inline bool operator!=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() != r.get(); }
	inline bool operator<(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() < r.get(); }
	inline bool operator<=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() <= r.get(); }
	inline bool operator>(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() > r.get(); }
	inline bool operator>=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() >= r.get(); }
	inline void swap(Win32HandleHolder& l, Win32HandleHolder& r) { l.swap(r); }

	void YBWLIB2_CALLTYPE CommonWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE CommonWindows_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B2352359_1626_4CF1_AEBF_4F58A5F48AD7
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B2352359_1626_4CF1_AEBF_4F58A5F48AD7
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_83D6146A_4FDA_461C_84C5_8247F88A40CA
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_83D6146A_4FDA_461C_84C5_8247F88A40CA
#endif
