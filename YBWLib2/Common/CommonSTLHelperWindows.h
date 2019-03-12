#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_0939BABA_5E02_4A75_B81A_A1E3E566F25C
#define _INCLUDE_GUARD_0939BABA_5E02_4A75_B81A_A1E3E566F25C

#include <type_traits>
#include <utility>
#include <atomic>
#include <memory>
#include <mutex>
#include <ostream>
#include "../DynamicType/DynamicType.h"
#include "Common.h"

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
		struct holder_u16str_t final {
			const rawallocator_t* rawallocator = nullptr;
			char16_t* str = nullptr;
			size_t size_str = 0;
			inline constexpr holder_u16str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
			/*holder_u16str_t(const holder_u16str_t&) = delete;
			inline holder_u16str_t(holder_u16str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
				x.rawallocator = nullptr;
				x.str = nullptr;
				x.size_str = 0;
			}*/
			inline ~holder_u16str_t() {
				if (this->str) {
					if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char16_t))) abort();
					this->str = nullptr;
				}
				this->size_str = 0;
				this->rawallocator = nullptr;
			}
			/*holder_u16str_t& operator=(const holder_u16str_t&) = delete;
			inline holder_u16str_t& operator=(holder_u16str_t&& x) noexcept {
				this->rawallocator = ::std::move(x.rawallocator);
				this->str = ::std::move(x.str);
				this->size_str = ::std::move(x.size_str);
				x.rawallocator = nullptr;
				x.str = nullptr;
				x.size_str = 0;
				return *this;
			}*/
		} holder_u16str_out(_rawallocator);
		IException* err = AnsiStringToUtf16String(_rawallocator, &holder_u16str_out.str, &holder_u16str_out.size_str, ansistr.data(), ansistr.size());
		if (err) throw(err);
		return _U16String_Ty(holder_u16str_out.str, holder_u16str_out.size_str, _allocator_u16str_out);
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
		struct holder_ansistr_t final {
			const rawallocator_t* rawallocator = nullptr;
			char* str = nullptr;
			size_t size_str = 0;
			inline constexpr holder_ansistr_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
			/*holder_ansistr_t(const holder_ansistr_t&) = delete;
			inline holder_ansistr_t(holder_ansistr_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
				x.rawallocator = nullptr;
				x.str = nullptr;
				x.size_str = 0;
			}*/
			inline ~holder_ansistr_t() {
				if (this->str) {
					if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char))) abort();
					this->str = nullptr;
				}
				this->size_str = 0;
				this->rawallocator = nullptr;
			}
			/*holder_ansistr_t& operator=(const holder_ansistr_t&) = delete;
			inline holder_ansistr_t& operator=(holder_ansistr_t&& x) noexcept {
				this->rawallocator = ::std::move(x.rawallocator);
				this->str = ::std::move(x.str);
				this->size_str = ::std::move(x.size_str);
				x.rawallocator = nullptr;
				x.str = nullptr;
				x.size_str = 0;
				return *this;
			}*/
		} holder_ansistr_out(_rawallocator);
		IException* err = Utf16StringToAnsiString(_rawallocator, &holder_ansistr_out.str, &holder_ansistr_out.size_str, u16str.data(), u16str.size());
		if (err) throw(err);
		return _AnsiString_Ty(holder_ansistr_out.str, holder_ansistr_out.size_str, _allocator_ansistr_out);
	}

	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	inline ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>> AnsiStringToUtf16String(const ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>& ansistr) noexcept(false) {
		return AnsiStringToUtf16String<
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>,
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>
		>(ansistr.get_allocator().rawallocator, ansistr, ansistr.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	inline ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>> Utf16StringToAnsiString(const ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>& u16str) noexcept(false) {
		return Utf16StringToAnsiString<
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>,
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>
		>(u16str.get_allocator().rawallocator, u16str, u16str.get_allocator());
	}

	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	inline ::std::u16string AnsiStringToUtf16String(const ::std::string& ansistr) noexcept(false) {
		return AnsiStringToUtf16String<::std::u16string, ::std::string>(rawallocator_crt_module_local, ansistr, ansistr.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	inline ::std::string Utf16StringToAnsiString(const ::std::u16string& u16str) noexcept(false) {
		return Utf16StringToAnsiString<::std::string, ::std::u16string>(rawallocator_crt_module_local, u16str, u16str.get_allocator());
	}
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#endif
