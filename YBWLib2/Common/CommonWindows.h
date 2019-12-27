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
#include <objbase.h>
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
	inline bool operator==(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() == r.get(); }
	inline bool operator!=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() != r.get(); }
	inline bool operator<(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() < r.get(); }
	inline bool operator<=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() <= r.get(); }
	inline bool operator>(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() > r.get(); }
	inline bool operator>=(const Win32HandleHolder& l, const Win32HandleHolder& r) { return l.get() >= r.get(); }

	inline ULONG STDMETHODCALLTYPE COMHelper_ReferenceCountedObject_AddRef(const IReferenceCountedObject* _obj) noexcept {
		assert(_obj);
		return _obj->IncReferenceCount() & ~(ULONG)0;
	}

	inline ULONG STDMETHODCALLTYPE COMHelper_ReferenceCountedObject_Release(const IReferenceCountedObject* _obj) noexcept {
		assert(_obj);
		return _obj->DecReferenceCount() & ~(ULONG)0;
	}

	template<typename _Class_Ty, typename... _Interface_Ty>
	inline HRESULT STDMETHODCALLTYPE COMHelper_QueryInterface(
		_Class_Ty* _obj,
		const IID& _iid,
		_COM_Outptr_ void** _obj_ret
	) {
		static_assert(::std::conjunction_v<::std::is_base_of<IUnknown, _Interface_Ty>...>, "At least one of the interface classes is not derived from IUnknown.");
		assert(_obj);
		if (!_obj_ret) return E_POINTER;
		using fnptr_cast_t = void* (__stdcall*)(_Class_Ty* _ptr) noexcept;
		using map_cast_t = ::std::unordered_map<IID, fnptr_cast_t, hash_trivially_copyable_t<IID, size_t>>;
		static const map_cast_t map_cast(
			{
				{
					__uuidof(_Interface_Ty),
					[](_Class_Ty* _ptr) noexcept->void* { static_cast<_Interface_Ty*>(_ptr)->AddRef(); return reinterpret_cast<void*>(static_cast<_Interface_Ty*>(_ptr)); }
				}...
			}
		);
		typename map_cast_t::const_iterator it_map_cast = map_cast.find(_iid);
		if (it_map_cast == map_cast.cend()) {
			*_obj_ret = nullptr;
			return E_NOINTERFACE;
		} else {
			*_obj_ret = (*it_map_cast->second)(_obj);
			return S_OK;
		}
	}

	template<class _Element_Ty>
	class COMObjectHolder {
	public:
		struct inc_ref_count_t {};
		static constexpr inc_ref_count_t inc_ref_count {};
		using element_type = _Element_Ty;
		static_assert(::std::is_base_of_v<IUnknown, element_type>, "The element class is not derived from IUnknown.");
		inline constexpr COMObjectHolder() noexcept = default;
		inline constexpr COMObjectHolder(nullptr_t) noexcept : COMObjectHolder() {}
		/// <summary>
		/// Constructs a <c>COMObjectHolder</c> that manages the COM object the specified pointer points to, without changing the object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline explicit COMObjectHolder(_Element_From_Ty*&& _ptr_element) noexcept : ptr_element(static_cast<element_type*&&>(_ptr_element)) {}
		/// <summary>
		/// Constructs a <c>COMObjectHolder</c> that manages the COM object the specified pointer points to, incrementing the object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder(_Element_From_Ty* _ptr_element, inc_ref_count_t) noexcept {
			if (_ptr_element) {
				static_cast<element_type*>(_ptr_element)->AddRef();
				this->ptr_element = static_cast<element_type*>(_ptr_element);
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder(const COMObjectHolder<_Element_From_Ty>& x) noexcept {
			if (x.ptr_element) {
				x.ptr_element->AddRef();
				this->ptr_element = static_cast<element_type*>(x.ptr_element);
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder(COMObjectHolder<_Element_From_Ty>&& x) noexcept {
			this->ptr_element = static_cast<element_type*&&>(::std::move(x.ptr_element));
			x.ptr_element = nullptr;
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<!::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder(const COMObjectHolder<_Element_From_Ty>& x) noexcept(false) {
			if (x.ptr_element) {
				HRESULT hr = x->QueryInterface(__uuidof(element_type), &this->get_ref_ptr_element());
				if (FAILED(hr)) {
					if (hr != E_NOINTERFACE) {
						throw(new ExternalAPIFailureWithHRESULTException(u8"IUnknown::QueryInterface", sizeof(u8"IUnknown::QueryInterface") / sizeof(char) - 1, nullptr, hr));
					} else {
						this->reset();
					}
				}
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<!::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder(COMObjectHolder<_Element_From_Ty>&& x) noexcept(false) {
			if (x.ptr_element) {
				HRESULT hr = x->QueryInterface(__uuidof(element_type), &this->get_ref_ptr_element());
				if (FAILED(hr)) {
					if (hr != E_NOINTERFACE) {
						throw(new ExternalAPIFailureWithHRESULTException(u8"IUnknown::QueryInterface", sizeof(u8"IUnknown::QueryInterface") / sizeof(char) - 1, nullptr, hr));
					} else {
						this->reset();
					}
				}
			}
			::std::move(x).reset();
		}
		inline ~COMObjectHolder() {
			this->reset();
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder& operator=(const COMObjectHolder<_Element_From_Ty>& x) noexcept {
			this->reset();
			if (x.ptr_element) {
				x.ptr_element->AddRef();
				this->ptr_element = static_cast<element_type*>(x.ptr_element);
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline COMObjectHolder& operator=(COMObjectHolder<_Element_From_Ty>&& x) noexcept {
			this->reset();
			this->ptr_element = static_cast<element_type*&&>(::std::move(x.ptr_element));
			x.ptr_element = nullptr;
		}
		inline explicit operator bool() const noexcept { return this->ptr_element; }
		inline element_type& operator*() const noexcept {
			assert(this->ptr_element);
			return *this->ptr_element;
		}
		inline element_type* operator->() const noexcept {
			assert(this->ptr_element);
			return this->ptr_element;
		}
		inline element_type* const& get() const noexcept { return this->ptr_element; }
		inline void reset() noexcept {
			if (this->ptr_element) {
				this->ptr_element->Release();
				this->ptr_element = nullptr;
			}
		}
		inline void reset(nullptr_t) noexcept {
			this->reset();
		}
		/// <summary>
		/// Makes this object manage the object the specified pointer points to, without changing the object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline void reset(_Element_From_Ty*&& _ptr_element) noexcept {
			this->reset();
			this->ptr_element = static_cast<element_type*&&>(_ptr_element);
		}
		/// <summary>
		/// Makes this object manage the object the specified pointer points to, incrementing the object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int> = 0>
		inline void reset(_Element_From_Ty* _ptr_element, inc_ref_count_t) noexcept {
			this->reset();
			if (_ptr_element) {
				static_cast<element_type*>(_ptr_element)->AddRef();
				this->ptr_element = static_cast<element_type*>(_ptr_element);
			}
		}
		/// <summary>
		/// Releases the stored pointer without changing the reference count.
		/// </summary>
		[[nodiscard]] inline element_type*&& release() noexcept {
			element_type* ptr_element_old = this->ptr_element;
			this->ptr_element = nullptr;
			return ::std::move(ptr_element_old);
		}
		inline element_type*& get_ref_ptr_element() noexcept {
			this->reset();
			return this->ptr_element;
		}
		inline void swap(COMObjectHolder& x) noexcept {
			element_type* ptr_element_temp = this->ptr_element;
			this->ptr_element = x.ptr_element;
			x.ptr_element = ptr_element_temp;
		}
	protected:
		element_type* ptr_element = nullptr;
	};
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator==(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() == r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() == COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator==(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() == nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator!=(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() != r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() != COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator!=(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() != nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() < r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() < COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator<(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() < nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<=(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() <= r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() <= COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator<=(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() <= nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() > r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() > COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator>(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() > nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>=(const COMObjectHolder<_Element_L_Ty>& l, const COMObjectHolder<_Element_R_Ty>& r) noexcept {
		if constexpr (::std::is_same_v<_Element_L_Ty, _Element_R_Ty>) {
			return l.get() >= r.get();
		} else {
			try {
				return COMObjectHolder<IUnknown>(l).get() >= COMObjectHolder<IUnknown>(r).get();
			} catch (...) {
				abort();
			}
		}
	}
	template<typename _Element_Ty>
	inline bool operator>=(nullptr_t, const COMObjectHolder<_Element_Ty>& r) noexcept { return nullptr >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(const COMObjectHolder<_Element_Ty>& l, nullptr_t) noexcept { return l.get() >= nullptr; }

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
