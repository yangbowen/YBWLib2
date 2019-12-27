#ifndef _WIN32_WINNT
#error This header file is only to be used when you're targeting Microsoft Windows. If you are, set the targetted windows version before including this header file.
#endif

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_0939BABA_5E02_4A75_B81A_A1E3E566F25C
#define _INCLUDE_GUARD_0939BABA_5E02_4A75_B81A_A1E3E566F25C

#include <cassert>
#include <type_traits>
#include <utility>
#include <atomic>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <ostream>
#include <minwindef.h>
#include <objbase.h>
#include "../DynamicType/DynamicType.h"
#include "Common.h"
#include "CommonWindows.h"

namespace std {
	template<typename _Char_Ty, typename _Traits_Ty>
	inline basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(basic_ostream<_Char_Ty, _Traits_Ty>& os, const ::YBWLib2::Win32HandleHolder& x) {
		return os << x.get();
	}
	inline void swap(::YBWLib2::Win32HandleHolder& l, ::YBWLib2::Win32HandleHolder& r) noexcept { l.swap(r); }

	template<typename _Char_Ty, typename _Traits_Ty, typename _Element_Ty>
	inline basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(basic_ostream<_Char_Ty, _Traits_Ty>& os, const ::YBWLib2::COMObjectHolder<_Element_Ty>& x) {
		return os << x.get();
	}
	template<typename _Element_Ty>
	inline void swap(::YBWLib2::COMObjectHolder<_Element_Ty>& l, ::YBWLib2::COMObjectHolder<_Element_Ty>& r) noexcept { l.swap(r); }
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ::YBWLib2::COMObjectHolder<_Element_To_Ty> dynamic_pointer_cast(const ::YBWLib2::COMObjectHolder<_Element_From_Ty>& x) noexcept(false) {
		::YBWLib2::COMObjectHolder<_Element_To_Ty> comobjholder;
		if (x) {
			HRESULT hr = x->QueryInterface(__uuidof(_Element_To_Ty), &comobjholder.get_ref_ptr_element());
			if (FAILED(hr)) {
				if (hr != E_NOINTERFACE) {
					throw(new ::YBWLib2::ExternalAPIFailureWithHRESULTException(u8"IUnknown::QueryInterface", sizeof(u8"IUnknown::QueryInterface") / sizeof(char) - 1, nullptr, hr));
				} else {
					comobjholder.reset();
				}
			}
		}
		return comobjholder;
	}
}

namespace YBWLib2 {
	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	template<typename _U16String_Ty, typename _AnsiString_Ty>
	inline _U16String_Ty AnsiStringToUtf16String(
		const rawallocator_t* _rawallocator,
		const _AnsiString_Ty& ansistr,
		const typename _U16String_Ty::allocator_type& _allocator_u16str_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_U16String_Ty>, "The UTF-16 string type is not a class.");
		static_assert(::std::is_class_v<_AnsiString_Ty>, "The ANSI string type is not a class.");
		objholder_rawallocator_t<char16_t[]> holder_u16str_out(_rawallocator);
		IException* err = AnsiStringToUtf16String(_rawallocator, &holder_u16str_out.get_ref_ptr_array_element_element_as_mem(), &holder_u16str_out.get_ref_count_element_element_as_mem(), ansistr.data(), ansistr.size());
		if (err) throw(err);
		return _U16String_Ty(holder_u16str_out.get(), holder_u16str_out.get_count(), _allocator_u16str_out);
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	template<typename _AnsiString_Ty, typename _U16String_Ty>
	inline _AnsiString_Ty Utf16StringToAnsiString(
		const rawallocator_t* _rawallocator,
		const _U16String_Ty& u16str,
		const typename _AnsiString_Ty::allocator_type& _allocator_ansistr_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_AnsiString_Ty>, "The ANSI string type is not a class.");
		static_assert(::std::is_class_v<_U16String_Ty>, "The UTF-16 string type is not a class.");
		objholder_rawallocator_t<char[]> holder_ansistr_out(_rawallocator);
		IException* err = Utf16StringToAnsiString(_rawallocator, &holder_ansistr_out.get_ref_ptr_array_element_element_as_mem(), &holder_ansistr_out.get_ref_count_element_element_as_mem(), u16str.data(), u16str.size());
		if (err) throw(err);
		return _AnsiString_Ty(holder_ansistr_out.get(), holder_ansistr_out.get_count(), _allocator_ansistr_out);
	}

	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	template<typename _Allocator_Ty>
	inline ::std::basic_string<char16_t, ::std::char_traits<char16_t>, _Allocator_Ty> AnsiStringToUtf16String(const ::std::string_view& ansistr, const _Allocator_Ty& _allocator = ::std::allocator<char16_t>()) noexcept(false) {
		return AnsiStringToUtf16String<
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, _Allocator_Ty>,
			::std::string_view
		>(rawallocator_crt_module_local, ansistr, _allocator);
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	template<typename _Allocator_Ty>
	inline ::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty> Utf16StringToAnsiString(const ::std::u16string_view& u16str, const _Allocator_Ty& _allocator = ::std::allocator<char>()) noexcept(false) {
		return Utf16StringToAnsiString<
			::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty>,
			::std::u16string_view
		>(rawallocator_crt_module_local, u16str, _allocator);
	}

	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	inline ::std::u16string AnsiStringToUtf16String(const ::std::string_view& ansistr) noexcept(false) {
		return AnsiStringToUtf16String<::std::u16string, ::std::string_view>(rawallocator_crt_module_local, ansistr, ::std::allocator<char16_t>());
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	inline ::std::string Utf16StringToAnsiString(const ::std::u16string_view& u16str) noexcept(false) {
		return Utf16StringToAnsiString<::std::string, ::std::u16string_view>(rawallocator_crt_module_local, u16str, ::std::allocator<char>());
	}
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#endif
