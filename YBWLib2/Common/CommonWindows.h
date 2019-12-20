#ifndef _WIN32_WINNT
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
#include <minwindef.h>
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
	class Win32HandleHolder final {
	public:
		struct view_handle_t {};
		struct own_handle_t {};
		struct no_eliminate_invalid_handle_value_t {};
		struct change_desired_access_t {};

		static constexpr view_handle_t view_handle {};
		static constexpr own_handle_t own_handle {};
		static constexpr no_eliminate_invalid_handle_value_t no_eliminate_invalid_handle_value {};
		static constexpr change_desired_access_t change_desired_access {};

		inline constexpr Win32HandleHolder() noexcept {}
		inline constexpr Win32HandleHolder(view_handle_t, const HANDLE& _win32handle) noexcept : win32handle(_win32handle == INVALID_HANDLE_VALUE ? NULL : _win32handle), is_owned_handle(false) {}
		inline constexpr Win32HandleHolder(view_handle_t, no_eliminate_invalid_handle_value_t, const HANDLE& _win32handle) noexcept : win32handle(_win32handle), is_owned_handle(false) {}
		inline constexpr Win32HandleHolder(own_handle_t, HANDLE&& _win32handle) noexcept : win32handle(_win32handle == INVALID_HANDLE_VALUE ? NULL : _win32handle), is_owned_handle(true) {
			_win32handle = NULL;
		}
		inline constexpr Win32HandleHolder(own_handle_t, no_eliminate_invalid_handle_value_t, HANDLE&& _win32handle) noexcept : win32handle(_win32handle), is_owned_handle(true) {
			_win32handle = NULL;
		}
		inline Win32HandleHolder(const Win32HandleHolder& x) noexcept(false) {
			if (x.win32handle) {
				IException* err = Win32HandleHolder::CopyWin32Handle(x.win32handle, &this->win32handle);
				if (err) throw(err);
				this->is_owned_handle = true;
			} else {
				this->win32handle = NULL;
				this->is_owned_handle = false;
			}
		}
		inline Win32HandleHolder(const Win32HandleHolder& x, change_desired_access_t, DWORD _desiredaccess) noexcept(false) {
			if (x.win32handle) {
				IException* err = Win32HandleHolder::CopyWin32HandleChangeDesiredAccess(x.win32handle, &this->win32handle, _desiredaccess);
				if (err) throw(err);
				this->is_owned_handle = true;
			} else {
				this->win32handle = NULL;
				this->is_owned_handle = false;
			}
		}
		inline Win32HandleHolder(Win32HandleHolder&& x) noexcept {
			this->win32handle = ::std::move(x.win32handle);
			x.win32handle = NULL;
			this->is_owned_handle = ::std::move(x.is_owned_handle);
			x.is_owned_handle = false;
		}
		inline ~Win32HandleHolder() {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
		}
		inline Win32HandleHolder& operator=(const Win32HandleHolder& x) noexcept(false) {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			if (x.win32handle) {
				IException* err = Win32HandleHolder::CopyWin32Handle(x.win32handle, &this->win32handle);
				if (err) throw(err);
				this->is_owned_handle = true;
			} else {
				this->win32handle = NULL;
				this->is_owned_handle = false;
			}
			return *this;
		}
		inline Win32HandleHolder& operator=(Win32HandleHolder&& x) noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			this->win32handle = ::std::move(x.win32handle);
			x.win32handle = NULL;
			this->is_owned_handle = ::std::move(x.is_owned_handle);
			x.is_owned_handle = false;
			return *this;
		}
		inline void swap(Win32HandleHolder& x) noexcept {
			HANDLE win32handle_temp = this->win32handle;
			bool is_owned_handle_temp = this->is_owned_handle;
			this->win32handle = x.win32handle;
			this->is_owned_handle = x.is_owned_handle;
			x.win32handle = win32handle_temp;
			x.is_owned_handle = is_owned_handle_temp;
		}
		inline void reset() noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
		}
		inline void reset(view_handle_t, const HANDLE& _win32handle) noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			this->win32handle = _win32handle == INVALID_HANDLE_VALUE ? NULL : _win32handle;
			this->is_owned_handle = false;
		}
		inline void reset(view_handle_t, no_eliminate_invalid_handle_value_t, const HANDLE& _win32handle) noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			this->win32handle = _win32handle;
			this->is_owned_handle = false;
		}
		inline void reset(own_handle_t, HANDLE&& _win32handle) noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			this->win32handle = _win32handle == INVALID_HANDLE_VALUE ? NULL : _win32handle;
			_win32handle = NULL;
			this->is_owned_handle = true;
		}
		inline void reset(own_handle_t, no_eliminate_invalid_handle_value_t, HANDLE&& _win32handle) noexcept {
			Win32HandleHolder::ClearWin32Handle(&this->win32handle, this->is_owned_handle);
			this->is_owned_handle = false;
			this->win32handle = _win32handle;
			_win32handle = NULL;
			this->is_owned_handle = true;
		}
		inline HANDLE get() const noexcept { return this->win32handle; }
		inline explicit operator bool() const noexcept { return this->win32handle; }
	protected:
		HANDLE win32handle = NULL;
		bool is_owned_handle = false;
		static YBWLIB2_API void YBWLIB2_CALLTYPE ClearWin32Handle(HANDLE* _win32handle, bool _is_owned_handle) noexcept;
		[[nodiscard]] static YBWLIB2_API IException* YBWLIB2_CALLTYPE CopyWin32Handle(HANDLE _win32handle_from, HANDLE* _win32handle_to) noexcept;
		[[nodiscard]] static YBWLIB2_API IException* YBWLIB2_CALLTYPE CopyWin32HandleChangeDesiredAccess(HANDLE _win32handle_from, HANDLE* _win32handle_to, DWORD _desiredaccess) noexcept;
	};
	static_assert(::std::is_standard_layout_v<Win32HandleHolder>, "Win32HandleHolder is not standard-layout.");
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
