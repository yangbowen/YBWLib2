#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_FBE53E15_FF1A_465B_8B84_419A5A81274B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_068CE365_7FF5_4D62_A0BD_1F427E075355
#define _INCLUDE_GUARD_068CE365_7FF5_4D62_A0BD_1F427E075355

#include <cstdlib>
#include <type_traits>
#include <utility>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <ostream>
#include "../DynamicType/DynamicType.h"
#include "Common.h"

namespace std {
	template<typename _Char_Ty, typename _Traits_Ty, typename _Element_Ty>
	inline basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(basic_ostream<_Char_Ty, _Traits_Ty>& os, const ::YBWLib2::ReferenceCountedObjectHolder<_Element_Ty>& x) {
		return os << x.get();
	}
	template<typename _Element_Ty>
	inline void swap(::YBWLib2::ReferenceCountedObjectHolder<_Element_Ty>& l, ::YBWLib2::ReferenceCountedObjectHolder<_Element_Ty>& r) noexcept { l.swap(r); }
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty> static_pointer_cast(const ::YBWLib2::ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
		return x ? ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>(x, static_cast<_Element_To_Ty*>(x.get())) : ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty> const_pointer_cast(const ::YBWLib2::ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
		return x ? ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>(x, const_cast<_Element_To_Ty*>(x.get())) : ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty> reinterpret_pointer_cast(const ::YBWLib2::ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
		return x ? ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>(x, reinterpret_cast<_Element_To_Ty*>(x.get())) : ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty> dynamic_pointer_cast(const ::YBWLib2::ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept(false) {
		if (x) {
			_Element_To_Ty* p = dynamic_cast<_Element_To_Ty*>(x.get());
			if (p) {
				return ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>(x, p);
			}
		}
		return ::YBWLib2::ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
}

namespace YBWLib2 {
	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
	template<typename _U16String_Ty, typename _U8String_Ty>
	inline _U16String_Ty Utf8StringToUtf16String(
		const rawallocator_t* _rawallocator,
		const _U8String_Ty& u8str,
		const typename _U16String_Ty::allocator_type& _allocator_u16str_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_U16String_Ty>, "The UTF-16 string type is not a class.");
		static_assert(::std::is_class_v<_U8String_Ty>, "The UTF-8 string type is not a class.");
		objholder_rawallocator_t<char16_t[]> holder_u16str_out(_rawallocator);
		IException* err = Utf8StringToUtf16String(_rawallocator, &holder_u16str_out.get_ref_ptr_array_element_element_as_mem(), &holder_u16str_out.get_ref_count_element_element_as_mem(), u8str.data(), u8str.size());
		if (err) throw(err);
		return _U16String_Ty(holder_u16str_out.get(), holder_u16str_out.get_count(), _allocator_u16str_out);
	}

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	template<typename _U8String_Ty, typename _U16String_Ty>
	inline _U8String_Ty Utf16StringToUtf8String(
		const rawallocator_t* _rawallocator,
		const _U16String_Ty& u16str,
		const typename _U8String_Ty::allocator_type& _allocator_u8str_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_U8String_Ty>, "The UTF-8 string type is not a class.");
		static_assert(::std::is_class_v<_U16String_Ty>, "The UTF-16 string type is not a class.");
		objholder_rawallocator_t<char[]> holder_u8str_out(_rawallocator);
		IException* err = Utf16StringToUtf8String(_rawallocator, &holder_u8str_out.get_ref_ptr_array_element_element_as_mem(), &holder_u8str_out.get_ref_count_element_element_as_mem(), u16str.data(), u16str.size());
		if (err) throw(err);
		return _U8String_Ty(holder_u8str_out.get(), holder_u8str_out.get_count(), _allocator_u8str_out);
	}

	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
	template<typename _Allocator_Ty>
	inline ::std::basic_string<char16_t, ::std::char_traits<char16_t>, _Allocator_Ty> Utf8StringToUtf16String(const ::std::string_view& u8str, const _Allocator_Ty& _allocator = ::std::allocator<char16_t>()) noexcept(false) {
		return Utf8StringToUtf16String<
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, _Allocator_Ty>,
			::std::string_view
		>(rawallocator_crt_module_local, u8str, _allocator);
	}

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	template<typename _Allocator_Ty>
	inline ::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty> Utf16StringToUtf8String(const ::std::u16string_view& u16str, const _Allocator_Ty& _allocator = ::std::allocator<char>()) noexcept(false) {
		return Utf16StringToUtf8String<
			::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty>,
			::std::u16string_view
		>(rawallocator_crt_module_local, u16str, _allocator);
	}

	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
	inline ::std::u16string Utf8StringToUtf16String(const ::std::string_view& u8str) noexcept(false) {
		return Utf8StringToUtf16String<::std::u16string, ::std::string_view>(rawallocator_crt_module_local, u8str, ::std::allocator<char16_t>());
	}

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	inline ::std::string Utf16StringToUtf8String(const ::std::u16string_view& u16str) noexcept(false) {
		return Utf16StringToUtf8String<::std::string, ::std::u16string_view>(rawallocator_crt_module_local, u16str, ::std::allocator<char>());
	}

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	template<typename _Vector_Data_Ty, typename _U8String_Ty>
	inline _Vector_Data_Ty Utf8Base64Decode(
		const rawallocator_t* _rawallocator,
		const _U8String_Ty& u8str,
		const typename _Vector_Data_Ty::allocator_type& _allocator_vec_data_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_Vector_Data_Ty>, "The data vector type is not a class.");
		static_assert(::std::is_class_v<_U8String_Ty>, "The UTF-8 string type is not a class.");
		objholder_rawallocator_t<unsigned char[]> holder_data_out(_rawallocator);
		IException* err = Utf8Base64Decode(_rawallocator, &holder_data_out.get_ref_ptr_array_element_element_as_mem(), &holder_data_out.get_ref_count_element_element_as_mem(), u8str.data(), u8str.size());
		if (err) throw(err);
		return _Vector_Data_Ty(holder_data_out.get(), holder_data_out.get() + holder_data_out.get_count(), _allocator_vec_data_out);
	}

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	template<typename _U8String_Ty, typename _Vector_Data_Ty>
	inline _U8String_Ty Utf8Base64Encode(
		const rawallocator_t* _rawallocator,
		const _Vector_Data_Ty& vec_data,
		const typename _U8String_Ty::allocator_type& _allocator_u8str_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_U8String_Ty>, "The UTF-8 string type is not a class.");
		static_assert(::std::is_class_v<_Vector_Data_Ty>, "The data vector type is not a class.");
		objholder_rawallocator_t<char[]> holder_u8str_out(_rawallocator);
		IException* err = Utf8Base64Encode(_rawallocator, &holder_u8str_out.get_ref_ptr_array_element_element_as_mem(), &holder_u8str_out.get_ref_count_element_element_as_mem(), vec_data.data(), vec_data.size());
		if (err) throw(err);
		return _U8String_Ty(holder_u8str_out.get(), holder_u8str_out.get_count(), _allocator_u8str_out);
	}

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	template<typename _Allocator_Ty>
	inline ::std::vector<unsigned char, _Allocator_Ty> Utf8Base64Decode(const ::std::string_view& u8str, const _Allocator_Ty& _allocator = ::std::allocator<unsigned char>()) noexcept(false) {
		return Utf8Base64Decode<
			::std::vector<unsigned char, _Allocator_Ty>,
			::std::string_view
		>(rawallocator_crt_module_local, u8str, _allocator);
	}

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	template<typename _Allocator_Ty, typename _Allocator_From_Ty>
	inline ::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty> Utf8Base64Encode(const ::std::vector<unsigned char, _Allocator_From_Ty>& vec_data, const _Allocator_Ty& _allocator = ::std::allocator<char>()) noexcept(false) {
		return Utf8Base64Encode<
			::std::basic_string<char, ::std::char_traits<char>, _Allocator_Ty>,
			::std::vector<unsigned char, _Allocator_From_Ty>
		>(rawallocator_crt_module_local, vec_data, _allocator);
	}

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	inline ::std::vector<unsigned char> Utf8Base64Decode(const ::std::string_view& u8str) noexcept(false) {
		return Utf8Base64Decode<::std::vector<unsigned char>, ::std::string_view>(rawallocator_crt_module_local, u8str, ::std::allocator<unsigned char>());
	}

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	inline ::std::string Utf8Base64Encode(const ::std::vector<unsigned char>& u16str) noexcept(false) {
		return Utf8Base64Encode<::std::string, ::std::vector<unsigned char>>(rawallocator_crt_module_local, u16str, ::std::allocator<char>());
	}

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	template<typename _Vector_Hash_Ty, typename _Vector_Data_Ty>
	inline _Vector_Hash_Ty HashSha256(
		const rawallocator_t* _rawallocator,
		const _Vector_Data_Ty& vec_data,
		const typename _Vector_Hash_Ty::allocator_type& _allocator_vec_hash_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_Vector_Hash_Ty>, "The hash vector type is not a class.");
		static_assert(::std::is_class_v<_Vector_Data_Ty>, "The data vector type is not a class.");
		objholder_rawallocator_t<unsigned char[]> holder_data_hash(_rawallocator);
		IException* err = HashSha256(_rawallocator, &holder_data_hash.get_ref_ptr_array_element_element_as_mem(), &holder_data_hash.get_ref_count_element_element_as_mem(), vec_data.data(), vec_data.size());
		if (err) throw(err);
		return _Vector_Hash_Ty(holder_data_hash.get(), holder_data_hash.get() + holder_data_hash.get_count(), _allocator_vec_hash_out);
	}

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	inline ::std::vector<unsigned char, allocator_rawallocator_t<unsigned char>> HashSha256(const ::std::vector<unsigned char, allocator_rawallocator_t<unsigned char>>& vec_data) noexcept(false) {
		rawallocator_t rawallocator(vec_data.get_allocator().rawallocator);
		return HashSha256<
			::std::vector<unsigned char, allocator_rawallocator_t<unsigned char>>,
			::std::vector<unsigned char, allocator_rawallocator_t<unsigned char>>
		>(&rawallocator, vec_data, vec_data.get_allocator());
	}

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	inline ::std::vector<unsigned char> HashSha256(const ::std::vector<unsigned char>& vec_data) noexcept(false) {
		return HashSha256<::std::vector<unsigned char>, ::std::vector<unsigned char>>(rawallocator_crt_module_local, vec_data, vec_data.get_allocator());
	}

	/// <summary>
	/// Reference counted object that keeps an STL shared pointer of itself.
	/// Objects of this class must be managed by an STL shared pointer before <c>IncReferenceCount</c> is called.
	/// Has a reference count of <c>0</c> when constructed.
	/// </summary>
	/// <typeparam name="_Concrete_Class_Ty">The concrete class that inherits from this class.</typeparam>
	template<typename _Concrete_Class_Ty>
	class SharedPtrReferenceCountedObject abstract
		: public ::std::enable_shared_from_this<_Concrete_Class_Ty>,
		public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(SharedPtrReferenceCountedObject);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(SharedPtrReferenceCountedObject);
		inline SharedPtrReferenceCountedObject() noexcept
			: ::std::enable_shared_from_this<_Concrete_Class_Ty>(),
			ref_count(0),
			ptr() {}
		inline SharedPtrReferenceCountedObject(const SharedPtrReferenceCountedObject& x) noexcept
			: ::std::enable_shared_from_this<_Concrete_Class_Ty>(static_cast<const ::std::enable_shared_from_this<_Concrete_Class_Ty>&>(x)),
			ref_count(0),
			ptr() {}
		inline SharedPtrReferenceCountedObject(SharedPtrReferenceCountedObject&& x) noexcept
			: ::std::enable_shared_from_this<_Concrete_Class_Ty>(static_cast<::std::enable_shared_from_this<_Concrete_Class_Ty>&&>(::std::move(x))),
			ref_count(0),
			ptr() {}
		inline SharedPtrReferenceCountedObject& operator=(const SharedPtrReferenceCountedObject& x) noexcept {
			static_cast<IReferenceCountedObject&>(*this) = static_cast<const IReferenceCountedObject&>(x);
			return *this;
		}
		inline SharedPtrReferenceCountedObject& operator=(SharedPtrReferenceCountedObject&& x) noexcept {
			static_cast<IReferenceCountedObject&>(*this) = static_cast<IReferenceCountedObject&&>(::std::move(x));
			return *this;
		}
		/// <summary>
		/// Gets the reference count.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The current reference count.</returns>
		inline virtual uintptr_t GetReferenceCount() const noexcept override {
			if (!this) return 0;
			return this->ref_count.load(::std::memory_order_relaxed);
		}
		/// <summary>
		/// Increments the reference count.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t IncReferenceCount() const noexcept override {
			if (!this) return 0;
			uintptr_t ref_count_old = this->ref_count.fetch_add(1, ::std::memory_order_acq_rel);
			if (!ref_count_old) {
				// The reference count is incremented from 0.
				// Keep a shared pointer of *this to prevent destruction.
				::std::shared_ptr<const volatile _Concrete_Class_Ty> ptr_desired = this->shared_from_this();
				// TODO: Implement better mechanism to wait.
#if false// TODO: Add support for C++20 ::std::atomic<::std::shared_ptr>.
				while (true) {
					static constexpr size_t count_spin = 0x10;
					static constexpr ::std::chrono::duration<unsigned int, ::std::milli> duration_sleep(100);
					size_t i_spin = 0;
					for (; i_spin < count_spin && this->ptr.atomic_exchange(ptr_desired, ::std::memory_order_acq_rel); ++i_spin);
					if (i_spin < count_spin)
						break;
					else
						::std::this_thread::sleep_for(duration_sleep);
				}
#else
				while (true) {
					static constexpr size_t count_spin = 0x10;
					static constexpr ::std::chrono::duration<unsigned int, ::std::milli> duration_sleep(100);
					size_t i_spin = 0;
					for (; i_spin < count_spin && ::std::atomic_exchange_explicit(&this->ptr, ptr_desired, ::std::memory_order_acq_rel); ++i_spin);
					if (i_spin < count_spin)
						break;
					else
						::std::this_thread::sleep_for(duration_sleep);
				}
#endif
			}
			return ref_count_old + 1;
		}
		/// <summary>
		/// Decrements the reference count.
		/// Permits the object to be freed if the reference count reaches <c>0</c>.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t DecReferenceCount() const noexcept override {
			if (!this) return 0;
			uintptr_t ref_count_old = this->ref_count.fetch_sub(1, ::std::memory_order::memory_order_acq_rel);
			assert(ref_count_old);
			if (ref_count_old == 1) {
				// The reference count is decremented to 0.
				// Clear the shared pointer.
				::std::shared_ptr<const volatile _Concrete_Class_Ty> ptr_desired;
				// TODO: Implement better mechanism to wait.
#if false// TODO: Add support for C++20 ::std::atomic<::std::shared_ptr>.
				while (true) {
					static constexpr size_t count_spin = 0x10;
					static constexpr ::std::chrono::duration<unsigned int, ::std::milli> duration_sleep(100);
					size_t i_spin = 0;
					for (; i_spin < count_spin && !this->ptr.atomic_exchange(ptr_desired, ::std::memory_order_acq_rel); ++i_spin);
					if (i_spin < count_spin)
						break;
					else
						::std::this_thread::sleep_for(duration_sleep);
				}
#else
				while (true) {
					static constexpr size_t count_spin = 0x10;
					static constexpr ::std::chrono::duration<unsigned int, ::std::milli> duration_sleep(100);
					size_t i_spin = 0;
					for (; i_spin < count_spin && !::std::atomic_exchange_explicit(&this->ptr, ptr_desired, ::std::memory_order_acq_rel); ++i_spin);
					if (i_spin < count_spin)
						break;
					else
						::std::this_thread::sleep_for(duration_sleep);
				}
#endif
			}
			return ref_count_old - 1;
		}
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~SharedPtrReferenceCountedObject() = default;
	private:
		mutable ::std::atomic<uintptr_t> ref_count = 0;
#if false// TODO: Add support for C++20 ::std::atomic<::std::shared_ptr>.
		mutable ::std::atomic<::std::shared_ptr<const volatile _Concrete_Class_Ty>> ptr;
#else
		mutable ::std::shared_ptr<const volatile _Concrete_Class_Ty> ptr;
#endif
	};

	/// <summary>An object that implements <c>ILockableObject</c> and wraps an STL <c>Lockable</c> object.</summary>
	/// <typeparam name="_Ty">The type of the wrapped object.</typeparam>
	template<typename _Ty>
	class LockableObjectFromSTLWrapper : public virtual ILockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(SharedPtrReferenceCountedObject);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(LockableObjectFromSTLWrapper);
		using wrapped_type = _Ty;
		template<typename... _Args_Ty>
		inline explicit LockableObjectFromSTLWrapper(_Args_Ty&&... args) : obj(::std::forward<_Args_Ty>(args)...) {}
		inline LockableObjectFromSTLWrapper(const LockableObjectFromSTLWrapper& x) noexcept : obj(x.obj) {}
		inline LockableObjectFromSTLWrapper(LockableObjectFromSTLWrapper&& x) noexcept : obj(::std::move(x.obj)) {}
		inline virtual ~LockableObjectFromSTLWrapper() = default;
		inline LockableObjectFromSTLWrapper& operator=(const LockableObjectFromSTLWrapper& x) noexcept {
			static_cast<ILockableObject&>(*this) = static_cast<const ILockableObject&>(x);
			return *this;
		}
		inline LockableObjectFromSTLWrapper& operator=(LockableObjectFromSTLWrapper&& x) noexcept {
			static_cast<ILockableObject&>(*this) = static_cast<ILockableObject&&>(::std::move(x));
			return *this;
		}
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ::std::remove_reference_t<_Ty>& GetWrappedLockableObject() noexcept { return this->obj; }
		/// <summary>Get a reference to the wrapped object.</summary>
		inline const ::std::remove_reference_t<_Ty>& GetWrappedLockableObject() const noexcept { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline virtual void Lock() noexcept override {
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::lock), _Ty>) {
				this->obj.lock();
			} else {
				try {
					this->obj.lock();
				} catch (...) {
					abort();
				}
			}
		}
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLock() noexcept override {
			bool ret = false;
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::try_lock), _Ty>) {
				ret = this->obj.try_lock();
			} else {
				try {
					ret = this->obj.try_lock();
				} catch (...) {
					abort();
				}
			}
		}
		/// <summary>Unlocks the object.</summary>
		inline virtual void Unlock() noexcept override {
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::unlock), _Ty>) {
				this->obj.unlock();
			} else {
				try {
					this->obj.unlock();
				} catch (...) {
					abort();
				}
			}
		}
	private:
		_Ty obj;
	};

	/// <summary>An object that wraps a reference to an <c>ILockableObject</c> object and behaves like an STL <c>Lockable</c> object.</summary>
	class LockableObjectToSTLWrapper {
	public:
		inline explicit LockableObjectToSTLWrapper(ILockableObject& x) : obj(x) {}
		inline virtual ~LockableObjectToSTLWrapper() = default;
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ILockableObject& GetWrappedLockableObject() const { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline virtual void lock() noexcept { this->obj.Lock(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool try_lock() noexcept { return this->obj.TryLock(); }
		/// <summary>Unlocks the object.</summary>
		inline virtual void unlock() noexcept { this->obj.Unlock(); }
	private:
		ILockableObject& obj;
	};
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_FBE53E15_FF1A_465B_8B84_419A5A81274B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_FBE53E15_FF1A_465B_8B84_419A5A81274B
#endif
