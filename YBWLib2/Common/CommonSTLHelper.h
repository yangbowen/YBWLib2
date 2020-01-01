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
	/// Objects of this class must be managed by an STL shared pointer before <c>GetReferenceCountControlBlock</c> is called.
	/// </summary>
	/// <typeparam name="_Concrete_Class_Ty">The concrete class that inherits from this class.</typeparam>
	template<typename _Concrete_Class_Ty>
	class SharedPtrReferenceCountedObject abstract
		: public ::std::enable_shared_from_this<_Concrete_Class_Ty>,
		public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(SharedPtrReferenceCountedObject);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(SharedPtrReferenceCountedObject);
		inline SharedPtrReferenceCountedObject() noexcept = default;
		inline SharedPtrReferenceCountedObject(const SharedPtrReferenceCountedObject& x) noexcept {
			this->controlblock = nullptr;
		}
		inline SharedPtrReferenceCountedObject(SharedPtrReferenceCountedObject&& x) noexcept {
			this->controlblock = nullptr;
		}
		inline virtual ~SharedPtrReferenceCountedObject() {
			if (this->controlblock) this->controlblock->DecWeakReferenceCount();
		}
		inline SharedPtrReferenceCountedObject& operator=(const SharedPtrReferenceCountedObject& x) noexcept {
			return *this;
		}
		inline SharedPtrReferenceCountedObject& operator=(SharedPtrReferenceCountedObject&& x) noexcept {
			return *this;
		}
		/// <summary>
		/// Returns an <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.
		/// If the control block hasn't been set up yet, it will be created and set up.
		/// </summary>
		/// <returns>A <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.</returns>
		inline virtual IReferenceCountControlBlock* GetReferenceCountControlBlock() const noexcept override {
			if (!this->controlblock) {
				::std::call_once(
					this->onceflag_controlblock,
					[this]() noexcept->void {
						class ControlBlock final : public ReferenceCountControlBlock {
						public:
							explicit ControlBlock(::std::shared_ptr<_Concrete_Class_Ty>&& _sharedptr_managed) : sharedptr_managed(::std::move(_sharedptr_managed)) {}
							//ControlBlock(const ControlBlock&) = delete;
							//ControlBlock(ControlBlock&&) = delete;
							//ControlBlock& operator=(const ControlBlock&) = delete;
							//ControlBlock& operator=(ControlBlock&&) = delete;
							/// <summary>Destroys the object managed by this control block.</summary>
							inline virtual void DestroyManagedObject() noexcept override {
								this->sharedptr_managed.reset();
							}
							/// <summary>Destroys this control block itself.</summary>
							inline virtual void DestroyControlBlock() noexcept override {
								delete this;
							}
						private:
							::std::shared_ptr<_Concrete_Class_Ty> sharedptr_managed;
						};
						::std::shared_ptr<_Concrete_Class_Ty> sharedptr_managed(const_cast<SharedPtrReferenceCountedObject<_Concrete_Class_Ty>*>(this)->shared_from_this());
						assert(sharedptr_managed);
						this->controlblock = new ControlBlock(::std::move(sharedptr_managed));
					}
				);
				assert(this->controlblock);
			}
			return this->controlblock;
		}
	protected:
		mutable ReferenceCountControlBlock* controlblock = nullptr;
		mutable ::std::once_flag onceflag_controlblock;
	};

	/// <summary>An object that implements <c>IExclusiveLockableObject</c> and wraps an STL <c>Lockable</c> object.</summary>
	/// <typeparam name="_Ty">The type of the wrapped object.</typeparam>
	template<typename _Ty>
	class ExclusiveLockableObjectFromSTLWrapper : public IExclusiveLockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(ExclusiveLockableObjectFromSTLWrapper);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(ExclusiveLockableObjectFromSTLWrapper);
		using wrapped_type = _Ty;
		template<typename... _Args_Ty>
		inline explicit ExclusiveLockableObjectFromSTLWrapper(_Args_Ty&&... args) : obj(::std::forward<_Args_Ty>(args)...) {}
		inline ExclusiveLockableObjectFromSTLWrapper(const ExclusiveLockableObjectFromSTLWrapper& x) noexcept : obj(x.obj) {}
		inline ExclusiveLockableObjectFromSTLWrapper(ExclusiveLockableObjectFromSTLWrapper&& x) noexcept : obj(::std::move(x.obj)) {}
		inline virtual ~ExclusiveLockableObjectFromSTLWrapper() = default;
		inline ExclusiveLockableObjectFromSTLWrapper& operator=(const ExclusiveLockableObjectFromSTLWrapper& x) noexcept {
			this->obj = x.obj;
			return *this;
		}
		inline ExclusiveLockableObjectFromSTLWrapper& operator=(ExclusiveLockableObjectFromSTLWrapper&& x) noexcept {
			this->obj = ::std::move(x.obj);
			return *this;
		}
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ::std::remove_reference_t<wrapped_type>& GetWrappedLockableObject() noexcept { return this->obj; }
		/// <summary>Get a reference to the wrapped object.</summary>
		inline const ::std::remove_reference_t<wrapped_type>& GetWrappedLockableObject() const noexcept { return this->obj; }
		/// <summary>Locks the object in exclusive mode. Blocks if necessary.</summary>
		inline virtual void LockExclusive() const noexcept override {
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
		/// <summary>Tries to lock the object in exclusive mode. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLockExclusive() const noexcept override {
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
		/// <summary>Unlocks the object in exclusive mode.</summary>
		inline virtual void UnlockExclusive() const noexcept override {
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
		mutable _Ty obj;
	};

	/// <summary>An object that implements <c>ISharedLockableObject</c> and wraps an STL <c>SharedMutex</c> object.</summary>
	/// <typeparam name="_Ty">The type of the wrapped object.</typeparam>
	template<typename _Ty>
	class SharedLockableObjectFromSTLWrapper : public ISharedLockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(SharedLockableObjectFromSTLWrapper);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(SharedLockableObjectFromSTLWrapper);
		using wrapped_type = _Ty;
		template<typename... _Args_Ty>
		inline explicit SharedLockableObjectFromSTLWrapper(_Args_Ty&&... args) : obj(::std::forward<_Args_Ty>(args)...) {}
		inline SharedLockableObjectFromSTLWrapper(const SharedLockableObjectFromSTLWrapper& x) noexcept : obj(x.obj) {}
		inline SharedLockableObjectFromSTLWrapper(SharedLockableObjectFromSTLWrapper&& x) noexcept : obj(::std::move(x.obj)) {}
		inline virtual ~SharedLockableObjectFromSTLWrapper() = default;
		inline SharedLockableObjectFromSTLWrapper& operator=(const SharedLockableObjectFromSTLWrapper& x) noexcept {
			this->obj = x.obj;
			return *this;
		}
		inline SharedLockableObjectFromSTLWrapper& operator=(SharedLockableObjectFromSTLWrapper&& x) noexcept {
			this->obj = ::std::move(x.obj);
			return *this;
		}
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ::std::remove_reference_t<wrapped_type>& GetWrappedLockableObject() noexcept { return this->obj; }
		/// <summary>Get a reference to the wrapped object.</summary>
		inline const ::std::remove_reference_t<wrapped_type>& GetWrappedLockableObject() const noexcept { return this->obj; }
		/// <summary>Locks the object in exclusive mode. Blocks if necessary.</summary>
		inline virtual void LockExclusive() const noexcept override {
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
		/// <summary>Tries to lock the object in exclusive mode. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLockExclusive() const noexcept override {
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
			return ret;
		}
		/// <summary>Unlocks the object in exclusive mode.</summary>
		inline virtual void UnlockExclusive() const noexcept override {
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
		/// <summary>
		/// Locks the object in shared mode. Blocks if necessary.
		/// Multiple threads may simultaneously lock an object in shared mode.
		/// However, when an object is locked in exclusive mode, no other thread may lock that object in either mode.
		/// </summary>
		inline virtual void LockShared() const noexcept override {
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::lock_shared), _Ty>) {
				this->obj.lock_shared();
			} else {
				try {
					this->obj.lock_shared();
				} catch (...) {
					abort();
				}
			}
		}
		/// <summary>Tries to lock the object in shared mode. Fail immediately if it's already locked in exclusive mode by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLockShared() const noexcept override {
			bool ret = false;
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::try_lock_shared), _Ty>) {
				ret = this->obj.try_lock_shared();
			} else {
				try {
					ret = this->obj.try_lock_shared();
				} catch (...) {
					abort();
				}
			}
			return ret;
		}
		/// <summary>Unlocks the object in shared mode.</summary>
		inline virtual void UnlockShared() const noexcept override {
			if constexpr (::std::is_nothrow_invocable_r_v<void, decltype(&_Ty::unlock_shared), _Ty>) {
				this->obj.unlock_shared();
			} else {
				try {
					this->obj.unlock_shared();
				} catch (...) {
					abort();
				}
			}
		}
	private:
		mutable _Ty obj;
	};

	/// <summary>An object that wraps a reference to an <c>IExclusiveLockableObject</c> object and behaves like an STL <c>Lockable</c> object.</summary>
	class ExclusiveLockableObjectToSTLWrapper final {
	public:
		inline explicit ExclusiveLockableObjectToSTLWrapper(IExclusiveLockableObject& x) : obj(x) {}
		inline ~ExclusiveLockableObjectToSTLWrapper() = default;
		/// <summary>Get a reference to the wrapped object.</summary>
		inline IExclusiveLockableObject& GetWrappedLockableObject() const { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline void lock() noexcept { this->obj.LockExclusive(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline bool try_lock() noexcept { return this->obj.TryLockExclusive(); }
		/// <summary>Unlocks the object.</summary>
		inline void unlock() noexcept { this->obj.UnlockExclusive(); }
	private:
		IExclusiveLockableObject& obj;
	};

	/// <summary>An object that wraps a reference to an <c>IExclusiveLockableObject</c> object and behaves like an STL <c>Lockable</c> object.</summary>
	class SharedLockableObjectToSTLWrapper final {
	public:
		inline explicit SharedLockableObjectToSTLWrapper(ISharedLockableObject& x) : obj(x) {}
		inline ~SharedLockableObjectToSTLWrapper() = default;
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ISharedLockableObject& GetWrappedLockableObject() const { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline void lock() noexcept { this->obj.LockExclusive(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline bool try_lock() noexcept { return this->obj.TryLockExclusive(); }
		/// <summary>Unlocks the object.</summary>
		inline void unlock() noexcept { this->obj.UnlockExclusive(); }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline void lock_shared() noexcept { this->obj.LockShared(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline bool try_lock_shared() noexcept { return this->obj.TryLockShared(); }
		/// <summary>Unlocks the object.</summary>
		inline void unlock_shared() noexcept { this->obj.UnlockShared(); }
	private:
		ISharedLockableObject& obj;
	};
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_FBE53E15_FF1A_465B_8B84_419A5A81274B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_FBE53E15_FF1A_465B_8B84_419A5A81274B
#endif
