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
	inline ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>> Utf8StringToUtf16String(const ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>& u8str) noexcept(false) {
		rawallocator_t rawallocator(u8str.get_allocator().rawallocator);
		return Utf8StringToUtf16String<
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>,
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>
		>(&rawallocator, u8str, u8str.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	inline ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>> Utf16StringToUtf8String(const ::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>& u16str) noexcept(false) {
		rawallocator_t rawallocator(u16str.get_allocator().rawallocator);
		return Utf16StringToUtf8String<
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>,
			::std::basic_string<char16_t, ::std::char_traits<char16_t>, allocator_rawallocator_t<char16_t>>
		>(&rawallocator, u16str, u16str.get_allocator());
	}

	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
	inline ::std::u16string Utf8StringToUtf16String(const ::std::string& u8str) noexcept(false) {
		return Utf8StringToUtf16String<::std::u16string, ::std::string>(rawallocator_crt_module_local, u8str, u8str.get_allocator());
	}

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	inline ::std::string Utf16StringToUtf8String(const ::std::u16string& u16str) noexcept(false) {
		return Utf16StringToUtf8String<::std::string, ::std::u16string>(rawallocator_crt_module_local, u16str, u16str.get_allocator());
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
		objholder_rawallocator_t<uint8_t[]> holder_data_out(_rawallocator);
		IException* err = Utf8Base64Decode(_rawallocator, &holder_data_out.get_ref_ptr_array_element_element_as_mem(), &holder_data_out.get_ref_count_element_element_as_mem(), u8str.data(), u8str.size());
		if (err) throw(err);
		return _Vector_Data_Ty(holder_data_out.get(), holder_data_out.get() + holder_data_out.get_count(), _allocator_vec_data_out);
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

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
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	inline ::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>> Utf8Base64Decode(const ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>& u8str) noexcept(false) {
		rawallocator_t rawallocator(u8str.get_allocator().rawallocator);
		return Utf8Base64Decode<
			::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>,
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>
		>(&rawallocator, u8str, u8str.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	inline ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>> Utf8Base64Encode(const ::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>& vec_data) noexcept(false) {
		rawallocator_t rawallocator(vec_data.get_allocator().rawallocator);
		return Utf8Base64Encode<
			::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>,
			::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>
		>(&rawallocator, vec_data, vec_data.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	inline ::std::vector<uint8_t> Utf8Base64Decode(const ::std::string& u8str) noexcept(false) {
		return Utf8Base64Decode<::std::vector<uint8_t>, ::std::string>(rawallocator_crt_module_local, u8str, u8str.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	inline ::std::string Utf8Base64Encode(const ::std::vector<uint8_t>& u16str) noexcept(false) {
		return Utf8Base64Encode<::std::string, ::std::vector<uint8_t>>(rawallocator_crt_module_local, u16str, u16str.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	template<typename _Vector_Hash_Ty, typename _Vector_Data_Ty>
	inline _Vector_Hash_Ty HashSha256(
		const rawallocator_t* _rawallocator,
		const _Vector_Data_Ty& vec_data,
		const typename _Vector_Hash_Ty::allocator_type& _allocator_vec_hash_out
	) noexcept(false) {
		static_assert(::std::is_class_v<_Vector_Hash_Ty>, "The hash vector type is not a class.");
		static_assert(::std::is_class_v<_Vector_Data_Ty>, "The data vector type is not a class.");
		objholder_rawallocator_t<uint8_t[]> holder_data_hash(_rawallocator);
		IException* err = HashSha256(_rawallocator, &holder_data_hash.get_ref_ptr_array_element_element_as_mem(), &holder_data_hash.get_ref_count_element_element_as_mem(), vec_data.data(), vec_data.size());
		if (err) throw(err);
		return _Vector_Hash_Ty(holder_data_hash.get(), holder_data_hash.get() + holder_data_hash.get_count(), _allocator_vec_hash_out);
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	inline ::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>> HashSha256(const ::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>& vec_data) noexcept(false) {
		rawallocator_t rawallocator(vec_data.get_allocator().rawallocator);
		return HashSha256<
			::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>,
			::std::vector<uint8_t, allocator_rawallocator_t<uint8_t>>
		>(&rawallocator, vec_data, vec_data.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	inline ::std::vector<uint8_t> HashSha256(const ::std::vector<uint8_t>& vec_data) noexcept(false) {
		return HashSha256<::std::vector<uint8_t>, ::std::vector<uint8_t>>(rawallocator_crt_module_local, vec_data, vec_data.get_allocator());
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

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

	/// <summary>
	/// Reference counted object holder.
	/// Counts as one reference of the owned object until destructed.
	/// </summary>
	/// <typeparam name="_Element_Ty">The type of the object objects of this class dereferences to.</typeparam>
	template<typename _Element_Ty>
	class ReferenceCountedObjectHolder final {
		template<typename _Element_Ty_Other>
		friend class ReferenceCountedObjectHolder;
	public:
		struct inc_ref_count_t {};
		struct adopt_ref_count_t {};

		static constexpr inc_ref_count_t inc_ref_count {};
		static constexpr adopt_ref_count_t adopt_ref_count {};

		using element_type = _Element_Ty;
		constexpr ReferenceCountedObjectHolder() noexcept {}
		constexpr ReferenceCountedObjectHolder(nullptr_t) noexcept : ReferenceCountedObjectHolder() {}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that manages the object the specified pointer points to, incrementing the object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline explicit ReferenceCountedObjectHolder(_Element_From_Ty* p, inc_ref_count_t) noexcept {
			if (p) {
				const IReferenceCountedObject* _ptr_owned = p;
				_ptr_owned->IncReferenceCount();
				this->ptr_stored = p;
				this->ptr_owned = _ptr_owned;
			}
		}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that manages the object the specified pointer points to, without changing the object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline explicit ReferenceCountedObjectHolder(_Element_From_Ty*&& p, adopt_ref_count_t) noexcept {
			if (p) {
				this->ptr_stored = p;
				this->ptr_owned = p;
				p = nullptr;
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		template<typename _Element_From_Ty>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x, _Element_Ty* p) noexcept {
			const IReferenceCountedObject* _ptr_owned = x.ptr_owned;
			if (_ptr_owned) {
				_ptr_owned->IncReferenceCount();
				this->ptr_owned = _ptr_owned;
			}
			if (p) this->ptr_stored = p;
		}
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder& x) noexcept {
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			this->ptr_stored = x.ptr_stored;
		}
		inline ReferenceCountedObjectHolder(ReferenceCountedObjectHolder&& x) noexcept {
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		inline ~ReferenceCountedObjectHolder() {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
		}
		inline _Element_Ty* get() const noexcept { return this->ptr_stored; }
		inline explicit operator bool() const noexcept { return this->ptr_stored; }
		inline _Element_Ty& operator*() const noexcept { return *this->ptr_stored; }
		inline _Element_Ty* operator->() const noexcept { return this->ptr_stored; }
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder& operator=(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
			return *this;
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder& operator=(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
			return *this;
		}
		inline ReferenceCountedObjectHolder& operator=(const ReferenceCountedObjectHolder& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			this->ptr_stored = x.ptr_stored;
			return *this;
		}
		inline ReferenceCountedObjectHolder& operator=(ReferenceCountedObjectHolder&& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
			return *this;
		}
		template<typename _Element_From_Ty>
		inline bool owner_before(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) const noexcept { return this->ptr_owned < x.ptr_owned; }
		inline void reset() noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
		}
		/// <summary>
		/// Makes this object manages the object the specified pointer points to, incrementing the later object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline void reset(_Element_From_Ty* p, inc_ref_count_t) noexcept {
			const IReferenceCountedObject* _ptr_owned_old = this->ptr_owned;
			if (_ptr_owned_old) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned_old->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (p) {
				const IReferenceCountedObject* _ptr_owned = p;
				_ptr_owned->IncReferenceCount();
				this->ptr_stored = p;
				this->ptr_owned = _ptr_owned;
			}
		}
		/// <summary>
		/// Makes this object manage the object the specified pointer points to, without changing the later object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline void reset(_Element_From_Ty*&& p, adopt_ref_count_t) noexcept {
			const IReferenceCountedObject* _ptr_owned_old = this->ptr_owned;
			if (_ptr_owned_old) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned_old->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (p) {
				this->ptr_stored = p;
				this->ptr_owned = p;
				p = nullptr;
			}
		}
		inline void swap(ReferenceCountedObjectHolder& x) noexcept {
			_Element_Ty* _ptr_stored = this->ptr_stored;
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = _ptr_stored;
			x.ptr_owned = _ptr_owned;
		}
		inline bool unique() const noexcept { return this && this->ptr_owned && this->ptr_owned->GetReferenceCount() == 1; }
		inline uintptr_t use_count() const noexcept { return this && this->ptr_owned ? this->ptr_owned->GetReferenceCount() : 0; }
	private:
		_Element_Ty* ptr_stored = nullptr;
		const IReferenceCountedObject* ptr_owned = nullptr;
	};
	template<typename _Char_Ty, typename _Traits_Ty, typename _Element_Ty>
	inline ::std::basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(::std::basic_ostream<_Char_Ty, _Traits_Ty>& os, const ReferenceCountedObjectHolder<_Element_Ty>& x) {
		return os << x.get();
	}
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() == nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() != nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() < nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() <= nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() > nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() >= nullptr; }
	template<typename _Element_Ty>
	inline void swap(ReferenceCountedObjectHolder<_Element_Ty>& l, ReferenceCountedObjectHolder<_Element_Ty>& r) { l.swap(r); }
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> static_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, static_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> const_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, const_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> reinterpret_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, reinterpret_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> dynamic_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		if (x) {
			_Element_To_Ty* p = dynamic_cast<_Element_To_Ty*>(x.get());
			if (p) {
				return ReferenceCountedObjectHolder<_Element_To_Ty>(x, p);
			}
		}
		return ReferenceCountedObjectHolder<_Element_To_Ty>();
	}

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
