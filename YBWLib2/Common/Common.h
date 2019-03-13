#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_30119E3B_9939_4A65_A63A_B13F0B7928DC
#define _INCLUDE_GUARD_30119E3B_9939_4A65_A63A_B13F0B7928DC

#include <cstdint>
#include "CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	/// <summary>An object for holding a pointer to another object that's placement-created in memory allocated by a <c>rawallocator_t</c> object.</summary>
	template<typename _Element_Ty>
	struct objholder_rawallocator_t final {
		static_assert(::std::is_class_v<_Element_Ty>, "The element type is not a class.");
		static_assert(!::std::is_const_v<_Element_Ty>, "The element type is const-qualified.");
		struct construct_obj_t {};
		static constexpr construct_obj_t construct_obj {};
		inline static constexpr void* align(void* _ptr) noexcept {
			return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - 1) % alignof(_Element_Ty)) - 1);
		}
		inline static constexpr const void* align(const void* _ptr) noexcept {
			return reinterpret_cast<const void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - 1) % alignof(_Element_Ty)) - 1);
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator) noexcept(false)
			: rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator, _Element_Ty*&& _ptr_element, void*&& _ptr_mem, size_t _size_mem) noexcept(false)
			: rawallocator(_rawallocator), ptr_element(::std::move(_ptr_element)), ptr_mem(::std::move(_ptr_mem)), size_mem(_size_mem) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			_ptr_element = nullptr;
			_ptr_mem = nullptr;
		}
		template<typename... _Args_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, construct_obj_t, _Args_Ty&&... args) noexcept(false)
			: rawallocator(_rawallocator) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty) + alignof(_Element_Ty) - 1;
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			this->ptr_element = new(ptr_mem_aligned) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Callable_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, _Callable_Ty _callable) noexcept(false)
			: rawallocator(_rawallocator) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty) + alignof(_Element_Ty) - 1;
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			this->ptr_element = _callable(static_cast<void*>(ptr_mem_aligned));
		}
		inline objholder_rawallocator_t(const objholder_rawallocator_t& x) noexcept(false) : rawallocator(x.rawallocator) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = x.size_mem;
			if (x.ptr_mem) {
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			}
			if (x.ptr_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
				void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
				this->ptr_element = new(ptr_mem_aligned) _Element_Ty(*x.ptr_element);
			}
		}
		inline objholder_rawallocator_t(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->rawallocator = x.rawallocator;
			this->ptr_element = x.ptr_element;
			x.ptr_element = nullptr;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			x.rawallocator = nullptr;
		}
		inline ~objholder_rawallocator_t() {
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				if (!this->rawallocator || !this->rawallocator->Deallocate(this->ptr_mem, this->size_mem)) abort();
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = nullptr;
		}
		inline objholder_rawallocator_t& operator=(const objholder_rawallocator_t& x) noexcept(false) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				if (!this->rawallocator->Deallocate(this->ptr_mem, this->size_mem)) abort();
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = x.rawallocator;
			this->size_mem = x.size_mem;
			if (x.ptr_mem) {
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			}
			if (x.ptr_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, operator=));
				void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
				this->ptr_element = new(ptr_mem_aligned) _Element_Ty(*x.ptr_element);
			}
			return *this;
		}
		inline objholder_rawallocator_t& operator=(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				if (!this->rawallocator->Deallocate(this->ptr_mem, this->size_mem)) abort();
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = x.rawallocator;
			this->ptr_element = x.ptr_element;
			x.ptr_element = nullptr;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			x.rawallocator = nullptr;
			return *this;
		}
		inline operator bool() const noexcept { return this->ptr_element; }
		inline _Element_Ty& operator*() const noexcept { return *this->ptr_element; }
		inline _Element_Ty* operator->() const noexcept { return this->ptr_element; }
		inline _Element_Ty* get() const noexcept { return this->ptr_element; }
		inline void reset(_Element_Ty*&& _ptr_element, void*&& _ptr_mem, size_t _size_mem) noexcept {
			this->free();
			this->ptr_element = _ptr_element;
			_ptr_element = nullptr;
			this->ptr_mem = _ptr_mem;
			_ptr_mem = nullptr;
			this->size_mem = _size_mem;
		}
		inline void release(_Element_Ty*& _ptr_element, void*& _ptr_mem, size_t& _size_mem) noexcept {
			_ptr_element = this->ptr_element;
			this->ptr_element = nullptr;
			_ptr_mem = this->ptr_mem;
			this->ptr_mem = nullptr;
			_size_mem = this->size_mem;
			this->size_mem = nullptr;
		}
		template<typename... _Args_Ty>
		inline void construct(construct_obj_t, _Args_Ty&&... args) noexcept(false) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			this->allocate();
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			this->ptr_element = new(ptr_mem_aligned) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Callable_Ty>
		inline void construct(_Callable_Ty _callable) noexcept(false) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			this->allocate();
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			this->ptr_element = _callable(static_cast<void*>(ptr_mem_aligned));
		}
		inline void destruct() noexcept {
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
		}
		inline void allocate() noexcept(false) {
			if (!this->ptr_mem) {
				this->size_mem = sizeof(_Element_Ty) + alignof(_Element_Ty) - 1;
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			} else if (this->size_mem != sizeof(_Element_Ty) + alignof(_Element_Ty) - 1) {
				this->free();
				this->size_mem = sizeof(_Element_Ty) + alignof(_Element_Ty) - 1;
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem);
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			}
		}
		inline void free() noexcept {
			this->destruct();
			if (this->ptr_mem) {
				if (!this->rawallocator->Deallocate(this->ptr_mem, this->size_mem)) abort();
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
		}
	private:
		_Element_Ty* ptr_element = nullptr;
		const rawallocator_t* rawallocator = nullptr;
		void* ptr_mem = nullptr;
		size_t size_mem = 0;
	};

	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
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
	/// <param name="str_in">Pointer to the input string, in UTF-8.</param>
	/// <param name="size_str_in">The size, in <c>char</c>s, of the input string, in UTF-8, pointed to by <c>str_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8StringToUtf16String(
		const rawallocator_t* rawallocator,
		char16_t** str_out_ret,
		size_t* size_str_out_ret,
		const char* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output string, in UTF-8.
	/// After successfully returning from this function, <c>*str_out_ret</c> will be set to the output string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_out_ret">
	/// Pointer to a variable that receives the size (in <c>char</c>s) of the output string, in UTF-8.
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
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf16StringToUtf8String(
		const rawallocator_t* rawallocator,
		char** str_out_ret,
		size_t* size_str_out_ret,
		const char16_t* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="data_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output data.
	/// After successfully returning from this function, <c>*data_out_ret</c> will be set to a pointer to the output data.
	/// The caller is responsible for freeing the memory pointed to by <c>*data_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*data_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_data_out_ret">
	/// Pointer to a variable that receives the size (in <c>uint8_t</c>s) of the output data.
	/// After successfully returning from this function, <c>*size_data_out_ret</c> will be set to the size (in <c>uint8_t</c>s) of the output data.
	/// Any value originally in <c>*size_data_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_base64_in">Pointer to the input Base64 string, in UTF-8.</param>
	/// <param name="size_str_base64_in">The size, in <c>char</c>s, of the input Base64 string, in UTF-8, pointed to by <c>str_base64_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Decode(
		const rawallocator_t* rawallocator,
		uint8_t** data_out_ret,
		size_t* size_data_out_ret,
		const char* str_base64_in,
		size_t size_str_base64_in
	) noexcept;
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_base64_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output Base64 string, in UTF-8.
	/// After successfully returning from this function, <c>*str_base64_out_ret</c> will be set to the output Base64 string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_base64_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_base64_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_base64_out_ret">
	/// Pointer to a variable that receives the size (in <c>char</c>s) of the output Base64 string, in UTF-8.
	/// After successfully returning from this function, <c>*size_str_base64_out_ret</c> will be set to the size (in <c>char</c>s) of the output Base64 string.
	/// Any value originally in <c>*size_str_base64_out_ret</c> will be discarded.
	/// </param>
	/// <param name="data_in">Pointer to the input data.</param>
	/// <param name="size_data_in">The size, in <c>uint8_t</c>s, of the input data, pointed to by <c>data_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Encode(
		const rawallocator_t* rawallocator,
		char** str_base64_out_ret,
		size_t* size_str_base64_out_ret,
		const uint8_t* data_in,
		size_t size_data_in
	) noexcept;
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="hash_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the hash.
	/// After successfully returning from this function, <c>*hash_out_ret</c> will be set to a pointer to the hash.
	/// The caller is responsible for freeing the memory pointed to by <c>*hash_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*hash_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_hash_out_ret">
	/// Pointer to a variable that receives the size (in <c>uint8_t</c>s) of the hash.
	/// After successfully returning from this function, <c>*size_hash_out_ret</c> will be set to the size (in <c>uint8_t</c>s) of the hash.
	/// Any value originally in <c>*size_hash_out_ret</c> will be discarded.
	/// </param>
	/// <param name="data_in">Pointer to the input data.</param>
	/// <param name="size_data_in">The size, in <c>uint8_t</c>s, of the input data, pointed to by <c>data_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE HashSha256(
		const rawallocator_t* rawallocator,
		uint8_t** hash_out_ret,
		size_t* size_hash_out_ret,
		const uint8_t* data_in,
		size_t size_data_in
	) noexcept;
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reference counted object.</summary>
	class IReferenceCountedObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IReferenceCountedObject, YBWLIB2_API, "6abec0cb-c444-492c-af61-04f502ade136");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IReferenceCountedObject);
		/// <summary>
		/// Gets the reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The current reference count.</returns>
		virtual uintptr_t GetReferenceCount() const = 0;
		/// <summary>
		/// Increments the reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		virtual uintptr_t IncReferenceCount() const = 0;
		/// <summary>
		/// Decrements the reference count.
		/// Permits the object to be freed if the reference count reaches <c>0</c>.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		virtual uintptr_t DecReferenceCount() const = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IReferenceCountedObject() = default;
	};

	/// <summary>Lockable object.</summary>
	class ILockableObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ILockableObject, YBWLIB2_API, "6fdf58be-4668-4967-8f62-9ab35b5cc271");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ILockableObject);
		/// <summary>Locks the object. Blocks if necessary.</summary>
		virtual void Lock() = 0;
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		virtual bool TryLock() = 0;
		/// <summary>Unlocks the object.</summary>
		virtual void Unlock() noexcept = 0;
	};

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#endif
