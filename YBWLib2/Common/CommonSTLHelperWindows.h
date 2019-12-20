#ifndef _WIN32_WINNT
#error This header file is only to be used when you're targeting Microsoft Windows. If you are, set the targetted windows version before including this header file.
#endif

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
#include <unordered_map>
#include <mutex>
#include <ostream>
#include <minwindef.h>
#include <objbase.h>
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
	inline ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>> AnsiStringToUtf16String(const ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>& ansistr) noexcept(false) {
		rawallocator_t rawallocator(ansistr.get_allocator().rawallocator);
		return AnsiStringToUtf16String<
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>,
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>
		>(&rawallocator, ansistr, ansistr.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	inline ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>> Utf16StringToAnsiString(const ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>& u16str) noexcept(false) {
		rawallocator_t rawallocator(u16str.get_allocator().rawallocator);
		return Utf16StringToAnsiString<
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>,
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>
		>(&rawallocator, u16str, u16str.get_allocator());
	}

	/// <summary>Converts a ANSI string into a UTF-16 string.</summary>
	inline ::std::u16string AnsiStringToUtf16String(const ::std::string& ansistr) noexcept(false) {
		return AnsiStringToUtf16String<::std::u16string, ::std::string>(rawallocator_crt_module_local, ansistr, ansistr.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a ANSI string.</summary>
	inline ::std::string Utf16StringToAnsiString(const ::std::u16string& u16str) noexcept(false) {
		return Utf16StringToAnsiString<::std::string, ::std::u16string>(rawallocator_crt_module_local, u16str, u16str.get_allocator());
	}

	class ReferenceCountedCOMObject abstract : public IReferenceCountedObject, public IUnknown {
	public:
		inline virtual ULONG STDMETHODCALLTYPE AddRef() override {
			return this->IReferenceCountedObject::IncReferenceCount() & ~(ULONG)0;
		}
		inline virtual ULONG STDMETHODCALLTYPE Release() override {
			return this->IReferenceCountedObject::DecReferenceCount() & ~(ULONG)0;
		}
	};

	template<typename... _Interface_Ty>
	class COMObjectWithQueryInterface abstract : public _Interface_Ty... {
	public:
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject
		) override {
			using map_cast_t = ::std::unordered_map<IID, void* (__stdcall*)(COMObjectWithQueryInterface<_Interface_Ty...> * _ptr) noexcept>;
			static const map_cast_t map_cast(
				{
					{
						__uuidof(_Interface_Ty),
						[](COMObjectWithQueryInterface<_Interface_Ty...>* _ptr) noexcept->void* { return reinterpret_cast<void*>(static_cast<_Interface_Ty*>(_ptr)); }
					}...
				}
			);
			typename map_cast_t::const_iterator it_map_cast = map_cast.find(riid);
			if (it_map_cast == map_cast.cend()) {
				*ppvObject = nullptr;
				return E_NOINTERFACE;
			} else {
				*ppvObject = (*it_map_cast->second)(this);
				return S_OK;
			}
		}
	};
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_8452DD82_9EB3_4C99_8F90_884D03CAF60A
#endif
