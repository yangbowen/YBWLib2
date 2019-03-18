#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_6D5B340E_F74B_4EDD_83D5_6BAB5945B5D8
#define _INCLUDE_GUARD_6D5B340E_F74B_4EDD_83D5_6BAB5945B5D8

#include <cstdint>
#include <cstring>
#include <type_traits>
#include <utility>
#include <memory>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
	class IStringTemplateParameter;
	class IStringTemplateParameterList;
	class IStringTemplate;

#pragma region ExceptionFlags
	//{ ExceptionFlags

	/// <summary>Exception flags.</summary>
	typedef uint64_t ExceptionFlags;

	// Exception flag definitions:
	/// <summary>Exception flag mask: Exception flags that should be inherited from the underlying cause.</summary>
	constexpr ExceptionFlags ExceptionFlag_Mask_Inheritable = 0xFFFFFFFF;
	/// <summary>Exception flag mask: Exception flags that should not be inherited from the underlying cause.</summary>
	constexpr ExceptionFlags ExceptionFlag_Mask_UnInheritable = 0xFFFFFFFF00000000;
	/// <summary>
	/// Exception flag:
	/// The exception has occured when handling another exception.
	/// </summary>
	constexpr ExceptionFlags ExceptionFlag_DoubleException = 0x1;
	/// <summary>
	/// Exception flag:
	/// A previous memory allocation from the default heap has failed, probably because of insufficient system memory.
	/// The exception handler should avoid allocating memory from the default heap.
	/// <c>ExceptionAllocateMemory</c> and <c>ExceptionFreeMemory</c> may still be used.
	/// </summary>
	constexpr ExceptionFlags ExceptionFlag_MemoryAllocFailure = 0x2;

	//}
#pragma endregion Exception flags are flags that indicate some characteristics of the exception.

#pragma region Exception handling dedicated memory
	//{ Exception handling dedicated memory

	/// <summary>
	/// Gets the maximum amount of memory that could potentially be allocated by <c>ExceptionAllocateMemory</c>.
	/// Memory allocations within this limit can still fail.
	/// </summary>
	YBWLIB2_API size_t YBWLIB2_CALLTYPE ExceptionGetMaxMemorySize() noexcept;
	/// <summary>
	/// Allocates memory from a separate store dedicated to exception handling.
	/// The allocated memory is zero-initialized.
	/// Because memory is committed in advance for this separate store, this function usually succeeds even if the system memory is insufficient.
	/// The size of this separate store is limited, so don't waste memory allocated with this function on purposes unrelated to exception handling.
	/// Failure to allocate memory in this function is considered fatal, and results in the process being terminated.
	/// </summary>
	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept;
	/// <summary>
	/// Frees memory previously allocated with <c>ExceptionAllocateMemory</c> or <c>ExceptionReAllocateMemory</c>.
	/// Failure to free memory in this function is considered fatal, and results in the process being terminated.
	/// </summary>
	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept;
	/// <summary>
	/// Reallocates memory from a separate store dedicated to exception handling.
	/// If the new size is greater than the original size, the additional memory is zero-initialized.
	/// Because memory is committed in advance for this separate store, this function usually succeeds even if the system memory is insufficient.
	/// The size of this separate store is limited, so don't waste memory allocated with this function on purposes unrelated to exception handling.
	/// Failure to allocate memory in this function is considered fatal, and results in the process being terminated.
	/// </summary>
	/// <param name="ptr_old">
	/// An optional pointer to some memory previously allocated with <c>ExceptionAllocateMemory</c> or <c>ExceptionReAllocateMemory</c>.
	/// If an empty pointer is passed, this function allocates some memory, just like when <c>ExceptionAllocateMemory</c> is called.
	/// If this pointer is not empty, the data in the memory up to the lesser of <c>size_old</c> and <c>size_new</c> is preserved.
	/// </param>
	/// <param name="size_new">The new size, in bytes, of the memory to be reallocated.</param>
	/// <returns>Returns a pointer to the reallocated memory, which may or may not be the same as the original pointer passed as <c>ptr_old</c>.</returns>
	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionReAllocateMemory(void* ptr_old, size_t size_new) noexcept;

	/// <summary>An allocator for allocating exception handling dedicated raw memory.</summary>
	extern YBWLIB2_API rawallocator_t* rawallocator_exception;

	/// <summary>Allocator template structure for allocating memory for exception handling.</summary>
	template<typename _Ty>
	struct allocator_exception_t {
		typedef _Ty value_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty& reference;
		typedef const _Ty& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_exception_t<_Rebind_Ty>;
		};
		using propagate_on_container_copy_assignment = ::std::true_type;
		using propagate_on_container_move_assignment = ::std::true_type;
		using propagate_on_container_swap = ::std::true_type;
		using is_always_equal = ::std::true_type;
		inline constexpr allocator_exception_t() noexcept = default;
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_exception_t(const allocator_exception_t<_Rebind_From_Ty>&) noexcept : allocator_exception_t() {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_exception_t(allocator_exception_t<_Rebind_From_Ty>&&) noexcept : allocator_exception_t() {}
		template<typename _Rebind_Ty>
		inline constexpr operator allocator_exception_t<_Rebind_Ty>() const noexcept { return allocator_exception_t<_Rebind_Ty>(); }
		template<typename _Allocator_Ty>
		inline constexpr bool operator==(const _Allocator_Ty&) const noexcept { return false; }
		template<typename _Element_Ty>
		inline constexpr bool operator==(const allocator_exception_t<_Element_Ty>&) const noexcept { return true; }
		template<typename _Allocator_Ty>
		inline constexpr bool operator!=(const _Allocator_Ty&) const noexcept { return true; }
		template<typename _Element_Ty>
		inline constexpr bool operator!=(const allocator_exception_t<_Element_Ty>&) const noexcept { return false; }
		inline pointer address(reference ref) const noexcept { return ::std::addressof(ref); }
		inline const_pointer address(const_reference ref) const noexcept { return ::std::addressof(ref); }
		inline pointer allocate(size_type count, const void* hint = nullptr) const noexcept {
			static_cast<void>(hint);
			return reinterpret_cast<pointer>(ExceptionAllocateMemory(count * sizeof(value_type)));
		}
		inline void deallocate(pointer ptr, size_type count) const noexcept {
			static_cast<void>(count);
			ExceptionFreeMemory(ptr);
		}
		inline size_type max_size() const noexcept { return ExceptionGetMaxMemorySize() / sizeof(value_type); }
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty...>(args...));
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline constexpr allocator_exception_t select_on_container_copy_construction() const noexcept { return allocator_exception_t(*this); }
	};
	/// <summary>Allocator template structure for allocating memory for exception handling.</summary>
	template<>
	struct allocator_exception_t<void> {
		typedef void value_type;
		typedef void* pointer;
		typedef const void* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_exception_t<_Rebind_Ty>;
		};
		using propagate_on_container_copy_assignment = ::std::true_type;
		using propagate_on_container_move_assignment = ::std::true_type;
		using propagate_on_container_swap = ::std::true_type;
		using is_always_equal = ::std::true_type;
		inline constexpr allocator_exception_t() noexcept = default;
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_exception_t(const allocator_exception_t<_Rebind_From_Ty>&) noexcept : allocator_exception_t() {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_exception_t(allocator_exception_t<_Rebind_From_Ty>&&) noexcept : allocator_exception_t() {}
		template<typename _Rebind_Ty>
		inline constexpr operator allocator_exception_t<_Rebind_Ty>() const noexcept { return allocator_exception_t<_Rebind_Ty>(); }
		template<typename _Allocator_Ty>
		inline constexpr bool operator==(const _Allocator_Ty&) const noexcept { return false; }
		template<typename _Element_Ty>
		inline constexpr bool operator==(const allocator_exception_t<_Element_Ty>&) const noexcept { return true; }
		template<typename _Allocator_Ty>
		inline constexpr bool operator!=(const _Allocator_Ty&) const noexcept { return true; }
		template<typename _Element_Ty>
		inline constexpr bool operator!=(const allocator_exception_t<_Element_Ty>&) const noexcept { return false; }
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty...>(args...));
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline constexpr allocator_exception_t select_on_container_copy_construction() const noexcept { return allocator_exception_t(*this); }
	};

	//}
#pragma endregion These functions and templates can be used to allocate memory from a separate store dedicated to exception handling, which may be used even when the system memory is insufficient.

#pragma region Exception interface classes
	//{ Exception interface classes

	/// <summary>Exception.</summary>
	class IException abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IException, YBWLIB2_API, "50bca171-aceb-4298-ad6f-a17baace7594");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IException);
		inline IException() noexcept = default;
		IException(const IException&) = delete;
		IException(IException&&) = delete;
		inline virtual ~IException() = default;
		IException& operator=(const IException&) = delete;
		IException& operator=(IException&&) = delete;
		static inline void* operator new(size_t size) noexcept {
			return ExceptionAllocateMemory(size);
		}
		static inline void* operator new[](size_t size) noexcept {
			return ExceptionAllocateMemory(size);
		}
		static inline void operator delete(void* ptr) noexcept {
			return ExceptionFreeMemory(ptr);
		}
		static inline void operator delete[](void* ptr) noexcept {
			return ExceptionFreeMemory(ptr);
		}
		/// <summary>
		/// Gets the exception flags.
		/// The underlying cause is not included.
		/// <c>GetExceptionFlagsTotal</c> normally calls this member function.
		/// </summary>
		/// <returns>The exception flags.</returns>
		virtual ExceptionFlags GetExceptionFlagsSingleLevel() const noexcept = 0;
		/// <summary>
		/// Gets the exception flags.
		/// The full chain of underlying causes is included.
		/// </summary>
		/// <returns>The exception flags.</returns>
		virtual ExceptionFlags GetExceptionFlagsTotal() const noexcept = 0;
		/// <summary>
		/// Attaches another <c>IException</c> object as the underlying cause of this exception.
		/// If there's already an exception object attached as the cause, it will be destructed and freed.
		/// </summary>
		/// <param name="exception_cause_new">
		/// The underlying cause of this exception to be attached.
		/// After returning from this member function (either successfully or unsuccessfully), the object on which this function is called acquires ownership of the object pointed to by this parameter and is responsible for destructing and freeing the object.
		/// Do NOT pass a pointer to a local object variable or an object already managed by other mechanisms.
		/// Passing an empty pointer clears the cause stored in this object.
		/// </param>
		virtual void AttachCause(IException* exception_cause_new) noexcept = 0;
		/// <summary>Gets a pointer to the <c>IException</c> object that represents the underlying cause of this exception.</summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called continues to own the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		virtual void GetCause(IException** exception_cause_ret) noexcept = 0;
		/// <summary>
		/// Detaches the pointer to the <c>IException</c> object that represents the underlying cause of this exception and gives it to the caller.
		/// After successfully returning from this function, the object on which this function is called no longer has a exception cause object.
		/// </summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called stops owning the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		virtual void DetachCause(IException** exception_cause_ret) noexcept = 0;
		/// <summary>
		/// Gets the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <returns>The value of the variable.</returns>
		virtual uintptr_t GetUserData() const noexcept = 0;
		/// <summary>
		/// Sets the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <param name="val_new">The new value of the variable.</param>
		virtual void SetUserData(uintptr_t val_new) noexcept = 0;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept = 0;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The full chain of underlying causes is included.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionTotal(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept = 0;
	};

	/// <summary>An exception that occurs when handling another exception.</summary>
	class IDoubleExceptionException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IDoubleExceptionException, YBWLIB2_API, "335aeafa-ff9b-42fc-ae65-24c00b1a4f1d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IDoubleExceptionException);
		inline virtual ~IDoubleExceptionException() = default;
	};

	/// <summary>An exception that occurs because of an invalid parameter passed to a function.</summary>
	class IInvalidParameterException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IInvalidParameterException, YBWLIB2_API, "8585713d-0d9e-4b14-87ea-85ddab280fff");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IInvalidParameterException);
		inline virtual ~IInvalidParameterException() = default;
		/// <summary>Gets the name of the function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetFunctionName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the name of the function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetFunctionNameSize() const noexcept = 0;
		/// <summary>Gets the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetMemberFunctionClassName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetMemberFunctionClassNameSize() const noexcept = 0;
	};

	/// <summary>An exception that occurs because of a call to a function that should not be called currently.</summary>
	class IInvalidCallException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IInvalidCallException, YBWLIB2_API, "249846e4-03be-4a4b-8770-13bab9dd0257");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IInvalidCallException);
		inline virtual ~IInvalidCallException() = default;
		/// <summary>Gets the name of the function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetFunctionName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the name of the function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetFunctionNameSize() const noexcept = 0;
		/// <summary>Gets the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetMemberFunctionClassName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetMemberFunctionClassNameSize() const noexcept = 0;
	};

	/// <summary>An exception that occurs because a buffer is insufficient.</summary>
	class IInsufficientBufferException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IInsufficientBufferException, YBWLIB2_API, "0a8cb47f-6b04-4b1a-8bde-6fbce4643009");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IInsufficientBufferException);
		inline virtual ~IInsufficientBufferException() = default;
		/// <summary>Gets the address to the insufficient buffer.</summary>
		/// <returns>
		/// Returns the address to the insufficient buffer, if available.
		/// If no meaningful pointer can be provided, an empty pointer is returned.
		/// </returns>
		virtual void* GetInsufficientBufferAddress() const noexcept = 0;
	};

	/// <summary>An exception that occurs because of failing to allocate memory.</summary>
	class IMemoryAllocFailureException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IMemoryAllocFailureException, YBWLIB2_API, "734b6864-6bb9-4159-abbc-ee099e4beeca");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IMemoryAllocFailureException);
		inline virtual ~IMemoryAllocFailureException() = default;
	};

	/// <summary>An exception that occurs because of attempting to insert an entry into a data structure that doesn't allow multiple equivalent keys and already has an entry with an equivalent key.</summary>
	class IKeyAlreadyExistException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IKeyAlreadyExistException, YBWLIB2_API, "c2f221a3-3955-4611-bdc2-2064b486381d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IKeyAlreadyExistException);
		inline virtual ~IKeyAlreadyExistException() = default;
	};

	/// <summary>An exception that occurs because of referencing to a non-existent key in a data structure.</summary>
	class IKeyNotExistException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IKeyNotExistException, YBWLIB2_API, "932a411b-94b7-4492-a47e-89c8fbf59683");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IKeyNotExistException);
		inline virtual ~IKeyNotExistException() = default;
	};

	/// <summary>An exception that occurs because of an unhandled exception thrown with other mechanisms not supported by this exception handling facility.</summary>
	class IUnhandledUnknownExceptionException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IUnhandledUnknownExceptionException, YBWLIB2_API, "627ed568-7a33-4025-a9e3-41f6996d9214");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IUnhandledUnknownExceptionException);
		inline virtual ~IUnhandledUnknownExceptionException() = default;
	};

	/// <summary>An exception that occurs because of an STL exception.</summary>
	class ISTLExceptionException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ISTLExceptionException, YBWLIB2_API, "3ba5f35b-c52c-447b-b2d1-d2733affdc3a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ISTLExceptionException);
		inline virtual ~ISTLExceptionException() = default;
		/// <summary>Gets the null-terminated <c>what</c> string of the STL exception, if available.</summary>
		/// <returns>
		/// Returns the null-terminated <c>what</c> string of the STL exception, if available.
		/// If no meaningful <c>what</c> string can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetSTLExceptionWhatString() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s, INCLUDING the terminating null character) of the null-terminated <c>what</c> string of the STL exception, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s, INCLUDING the terminating null character) of the null-terminated <c>what</c> string of the STL exception, if available.
		/// If no meaningful <c>what</c> string can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetSTLExceptionWhatStringSize() const noexcept = 0;
	};

	/// <summary>An exception that occurs because of failing to call an external API.</summary>
	class IExternalAPIFailureException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureException, YBWLIB2_API, "d64eb2f6-813e-483d-89fc-b6a07bd02aa9");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureException);
		inline virtual ~IExternalAPIFailureException() = default;
		/// <summary>Gets the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetExternalAPIName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetExternalAPINameSize() const noexcept = 0;
		/// <summary>Gets the address to the external API, if available.</summary>
		/// <returns>
		/// Returns the address to the external API, if available.
		/// If no meaningful address can be provided, an empty pointer is returned.
		/// </returns>
		virtual const void* GetExternalAPIAddress() const noexcept = 0;
	};

	/// <summary>An unexpected exception.</summary>
	class IUnexpectedExceptionException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IUnexpectedExceptionException, YBWLIB2_API, "99ce058f-4074-4ef9-8e34-661121b7754c");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IUnexpectedExceptionException);
		inline virtual ~IUnexpectedExceptionException() = default;
		/// <summary>Gets the filename of the source code file in which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetSourceCodeFileName() const noexcept = 0;
		/// <summary>Gets the size (in <c>char</c>s) of the filename of the source code file in which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, <c>0</c> is returned.
		/// </returns>
		virtual size_t GetSourceCodeFileNameSize() const noexcept = 0;
		/// <summary>Gets the line number of the source code at which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the line number of the source code at which the exception has occured, if available.
		/// If no meaningful line number can be provided, <c>-1</c> is returned.
		/// </returns>
		virtual int GetSourceCodeLineNumber() const noexcept = 0;
	};

	//}
#pragma endregion Exception classes that may be transferred across executable module boundaries.

#pragma region Exception implementation classes
	//{ Exception implementation classes

	/// <summary>
	/// A default implementation of <c>IException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IException</c>.
	/// </summary>
	class Exception : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Exception, , "ae07f679-f0a1-4f24-9e1b-2e7ad8f59f6d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Exception);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline Exception() noexcept {}
		inline virtual ~Exception() {
			if (this->exception_cause) {
				delete this->exception_cause;
				this->exception_cause = nullptr;
			}
		}
		/// <summary>
		/// Gets the exception flags.
		/// The underlying cause is not included.
		/// <c>GetExceptionFlagsTotal</c> normally calls this member function.
		/// </summary>
		/// <returns>The exception flags.</returns>
		inline virtual ExceptionFlags GetExceptionFlagsSingleLevel() const noexcept override { return 0; }
		/// <summary>
		/// Gets the exception flags.
		/// The full chain of underlying causes is included.
		/// </summary>
		/// <returns>The exception flags.</returns>
		inline virtual ExceptionFlags GetExceptionFlagsTotal() const noexcept override {
			return (this->exception_cause ? this->exception_cause->GetExceptionFlagsTotal() & ExceptionFlag_Mask_Inheritable : 0) | this->GetExceptionFlagsSingleLevel();
		}
		/// <summary>
		/// Attaches another <c>IException</c> object as the underlying cause of this exception.
		/// If there's already an exception object attached as the cause, it will be destructed and freed.
		/// </summary>
		/// <param name="exception_cause_new">
		/// The underlying cause of this exception to be attached.
		/// After returning from this member function (either successfully or unsuccessfully), the object on which this function is called acquires ownership of the object pointed to by this parameter and is responsible for destructing and freeing the object.
		/// Do NOT pass a pointer to a local object variable or an object already managed by other mechanisms.
		/// Passing an empty pointer clears the cause stored in this object.
		/// </param>
		inline virtual void AttachCause(IException* exception_cause_new) noexcept override {
			if (this->exception_cause) {
				delete this->exception_cause;
				this->exception_cause = nullptr;
			}
			this->exception_cause = exception_cause_new;
		}
		/// <summary>Gets a pointer to the <c>IException</c> object that represents the underlying cause of this exception.</summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called continues to own the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		inline virtual void GetCause(IException** exception_cause_ret) noexcept override {
			*exception_cause_ret = this->exception_cause;
		}
		/// <summary>
		/// Detaches the pointer to the <c>IException</c> object that represents the underlying cause of this exception and gives it to the caller.
		/// After successfully returning from this function, the object on which this function is called no longer has a exception cause object.
		/// </summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called stops owning the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		inline virtual void DetachCause(IException** exception_cause_ret) noexcept override {
			*exception_cause_ret = this->exception_cause;
			this->exception_cause = nullptr;
		}
		/// <summary>
		/// Get the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <returns>The value of the variable.</returns>
		inline virtual uintptr_t GetUserData() const noexcept override { return this->userdata; }
		/// <summary>
		/// Set the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <param name="val_new">The new value of the variable.</param>
		inline virtual void SetUserData(uintptr_t val_new) noexcept override { this->userdata = val_new; }
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The full chain of underlying causes is included.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionTotal(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	protected:
		IException* exception_cause = nullptr;
		uintptr_t userdata = 0;
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IDoubleExceptionException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IDoubleExceptionException</c>.
	/// </summary>
	class DoubleExceptionException
		: public virtual Exception,
		public virtual IDoubleExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(DoubleExceptionException, , "3e8fb777-36a8-4484-8dfc-c0c1d0769921");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(DoubleExceptionException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline DoubleExceptionException() noexcept = default;
		inline virtual ~DoubleExceptionException() = default;
		/// <summary>
		/// Gets the exception flags.
		/// The underlying cause is not included.
		/// <c>GetExceptionFlagsTotal</c> normally calls this member function.
		/// </summary>
		/// <returns>The exception flags.</returns>
		inline virtual ExceptionFlags GetExceptionFlagsSingleLevel() const noexcept override {
			return this->Exception::GetExceptionFlagsSingleLevel() | ExceptionFlag_DoubleException;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>IInvalidParameterException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IInvalidParameterException</c>.
	/// </summary>
	class InvalidParameterException
		: public virtual Exception,
		public virtual IInvalidParameterException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(InvalidParameterException, , "64bcf888-15dc-4a20-95ec-d11ea4511e08");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(InvalidParameterException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>InvalidParameterException</c> object.</summary>
		/// <param name="_name_function">
		/// The name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_function">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_name_class_member_function">
		/// The name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_class_member_function">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		inline InvalidParameterException(const char* _name_function, size_t _size_name_function, const char* _name_class_member_function = nullptr, size_t _size_name_class_member_function = 0) noexcept {
			if (_name_function && _size_name_function) {
				this->size_name_function = _size_name_function;
				this->name_function = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_name_function * sizeof(char)));
				memcpy(this->name_function, _name_function, this->size_name_function * sizeof(char));
			}
			if (_name_class_member_function && _size_name_class_member_function) {
				this->size_name_class_member_function = _size_name_class_member_function;
				this->name_class_member_function = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_name_class_member_function * sizeof(char)));
				memcpy(this->name_class_member_function, _name_class_member_function, this->size_name_class_member_function * sizeof(char));
			}
		}
		inline virtual ~InvalidParameterException() {
			if (this->name_function) {
				ExceptionFreeMemory(this->name_function);
				this->name_function = nullptr;
			}
			this->size_name_function = 0;
			if (this->name_class_member_function) {
				ExceptionFreeMemory(this->name_class_member_function);
				this->name_class_member_function = nullptr;
			}
			this->size_name_class_member_function = 0;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the name of the function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetFunctionName() const noexcept override {
			return this->name_function && this->size_name_function ? this->name_function : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the name of the function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetFunctionNameSize() const noexcept override {
			return this->name_function && this->size_name_function ? this->size_name_function : 0;
		}
		/// <summary>Gets the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetMemberFunctionClassName() const noexcept override {
			return this->name_class_member_function && this->size_name_class_member_function ? this->name_class_member_function : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetMemberFunctionClassNameSize() const noexcept override {
			return this->name_class_member_function && this->size_name_class_member_function ? this->size_name_class_member_function : 0;
		}
	protected:
		char* name_function = nullptr;
		size_t size_name_function = 0;
		char* name_class_member_function = nullptr;
		size_t size_name_class_member_function = 0;
	};

	/// <summary>
	/// A default implementation of <c>IInvalidCallException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IInvalidCallException</c>.
	/// </summary>
	class InvalidCallException
		: public virtual Exception,
		public virtual IInvalidCallException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(InvalidCallException, , "24f2c099-be5d-4401-8338-18817687589c");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(InvalidCallException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>InvalidCallException</c> object.</summary>
		/// <param name="_name_function">
		/// The name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_function">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_name_class_member_function">
		/// The name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_class_member_function">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		inline InvalidCallException(const char* _name_function, size_t _size_name_function, const char* _name_class_member_function = nullptr, size_t _size_name_class_member_function = 0) noexcept {
			if (_name_function && _size_name_function) {
				this->size_name_function = _size_name_function;
				this->name_function = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_name_function * sizeof(char)));
				memcpy(this->name_function, _name_function, this->size_name_function * sizeof(char));
			}
			if (_name_class_member_function && _size_name_class_member_function) {
				this->size_name_class_member_function = _size_name_class_member_function;
				this->name_class_member_function = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_name_class_member_function * sizeof(char)));
				memcpy(this->name_class_member_function, _name_class_member_function, this->size_name_class_member_function * sizeof(char));
			}
		}
		inline virtual ~InvalidCallException() {
			if (this->name_function) {
				ExceptionFreeMemory(this->name_function);
				this->name_function = nullptr;
			}
			this->size_name_function = 0;
			if (this->name_class_member_function) {
				ExceptionFreeMemory(this->name_class_member_function);
				this->name_class_member_function = nullptr;
			}
			this->size_name_class_member_function = 0;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the name of the function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetFunctionName() const noexcept override {
			return this->name_function && this->size_name_function ? this->name_function : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the name of the function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetFunctionNameSize() const noexcept override {
			return this->name_function && this->size_name_function ? this->size_name_function : 0;
		}
		/// <summary>Gets the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetMemberFunctionClassName() const noexcept override {
			return this->name_class_member_function && this->size_name_class_member_function ? this->name_class_member_function : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the name of the class of which the function is a member function, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the class of which the function is a member function, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetMemberFunctionClassNameSize() const noexcept override {
			return this->name_class_member_function && this->size_name_class_member_function ? this->size_name_class_member_function : 0;
		}
	protected:
		char* name_function = nullptr;
		size_t size_name_function = 0;
		char* name_class_member_function = nullptr;
		size_t size_name_class_member_function = 0;
	};

	/// <summary>
	/// A default implementation of <c>IInsufficientBufferException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IInsufficientBufferException</c>.
	/// </summary>
	class InsufficientBufferException
		: public virtual Exception,
		public virtual IInsufficientBufferException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(InsufficientBufferException, , "58050bd3-cd5e-4501-b717-ee9603a31e77");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(InsufficientBufferException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>InsufficientBufferException</c> object.</summary>
		/// <param name="_address_buffer_insufficient">
		/// The address to the insufficient buffer, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		inline InsufficientBufferException(void* _address_buffer_insufficient) noexcept {
			if (_address_buffer_insufficient) this->address_buffer_insufficient = _address_buffer_insufficient;
		}
		inline virtual ~InsufficientBufferException() = default;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the address to the insufficient buffer.</summary>
		/// <returns>
		/// Returns the address to the insufficient buffer, if available.
		/// If no meaningful pointer can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual void* GetInsufficientBufferAddress() const noexcept override {
			return this->address_buffer_insufficient ? this->address_buffer_insufficient : nullptr;
		}
	protected:
		void* address_buffer_insufficient = nullptr;
	};

	/// <summary>
	/// A default implementation of <c>IMemoryAllocFailureException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IMemoryAllocFailureException</c>.
	/// </summary>
	class MemoryAllocFailureException
		: public virtual Exception,
		public virtual IMemoryAllocFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(MemoryAllocFailureException, , "5b87c2db-b7e8-4f02-928e-76fdc457d1a3");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(MemoryAllocFailureException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline MemoryAllocFailureException() noexcept = default;
		inline virtual ~MemoryAllocFailureException() = default;
		inline virtual ExceptionFlags GetExceptionFlagsSingleLevel() const noexcept override {
			return this->Exception::GetExceptionFlagsSingleLevel() | ExceptionFlag_MemoryAllocFailure;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>IKeyAlreadyExistException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IKeyAlreadyExistException</c>.
	/// </summary>
	class KeyAlreadyExistException
		: public virtual Exception,
		public virtual IKeyAlreadyExistException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(KeyAlreadyExistException, , "7f492596-20cd-430c-8ebb-8a63b03f648a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(KeyAlreadyExistException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline KeyAlreadyExistException() noexcept = default;
		inline virtual ~KeyAlreadyExistException() = default;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>IKeyNotExistException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IKeyNotExistException</c>.
	/// </summary>
	class KeyNotExistException
		: public virtual Exception,
		public virtual IKeyNotExistException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(KeyNotExistException, , "41af914c-4067-4088-8c87-0da29e4f3b28");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(KeyNotExistException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline KeyNotExistException() noexcept = default;
		inline virtual ~KeyNotExistException() = default;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>IUnhandledUnknownExceptionException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IUnhandledUnknownExceptionException</c>.
	/// </summary>
	class UnhandledUnknownExceptionException
		: public virtual Exception,
		public virtual IUnhandledUnknownExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(UnhandledUnknownExceptionException, , "394df091-137c-4214-9a74-1e3f8ef7601a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(UnhandledUnknownExceptionException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline UnhandledUnknownExceptionException() noexcept = default;
		inline virtual ~UnhandledUnknownExceptionException() = default;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>ISTLExceptionException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISTLExceptionException</c>.
	/// </summary>
	class STLExceptionException
		: public virtual Exception,
		public virtual ISTLExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(STLExceptionException, , "6bfb4f69-92fb-4b8f-b9b0-439243fdc80d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(STLExceptionException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>STLExceptionException</c> object.</summary>
		/// <param name="_str_what_stlexception">
		/// The null-terminated <c>what</c> string of the STL exception, if available.
		/// If no meaningful <c>what</c> string can be provided, pass an empty pointer.
		/// </param>
		inline STLExceptionException(const char* _str_what_stlexception) noexcept {
			if (_str_what_stlexception) {
				this->size_str_what_stlexception = strlen(_str_what_stlexception) + 1;
				this->str_what_stlexception = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_str_what_stlexception * sizeof(char)));
				memcpy(this->str_what_stlexception, _str_what_stlexception, this->size_str_what_stlexception * sizeof(char));
			}
		}
		inline virtual ~STLExceptionException() {
			if (this->str_what_stlexception) {
				ExceptionFreeMemory(this->str_what_stlexception);
				this->str_what_stlexception = nullptr;
			}
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the null-terminated <c>what</c> string of the STL exception, if available.</summary>
		/// <returns>
		/// Returns the null-terminated <c>what</c> string, in UTF-8, of the STL exception, if available.
		/// If no meaningful <c>what</c> string can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetSTLExceptionWhatString() const noexcept override {
			return this->str_what_stlexception ? this->str_what_stlexception : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s, INCLUDING the terminating null character) of the null-terminated <c>what</c> string of the STL exception, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s, INCLUDING the terminating null character) of the null-terminated <c>what</c> string of the STL exception, if available.
		/// If no meaningful <c>what</c> string can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetSTLExceptionWhatStringSize() const noexcept override {
			return this->size_str_what_stlexception && this->size_str_what_stlexception ? this->size_str_what_stlexception : 0;
		}
	protected:
		char* str_what_stlexception = nullptr;
		size_t size_str_what_stlexception = 0;
	};

	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IExternalAPIFailureException</c>.
	/// </summary>
	class ExternalAPIFailureException
		: public virtual Exception,
		public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureException, , "e1c1550b-2b64-48c8-8904-0013c4469f24");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ExternalAPIFailureException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		inline ExternalAPIFailureException(const char* _name_api, size_t _size_name_api, const void* _address_api) noexcept {
			if (_name_api && _size_name_api) {
				this->size_name_api = _size_name_api;
				this->name_api = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_name_api * sizeof(char)));
				memcpy(this->name_api, _name_api, this->size_name_api * sizeof(char));
			}
			if (_address_api) this->address_api = _address_api;
		}
		inline virtual ~ExternalAPIFailureException() {
			if (this->name_api) {
				ExceptionFreeMemory(this->name_api);
				this->name_api = nullptr;
			}
			this->size_name_api = 0;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetExternalAPIName() const noexcept override {
			return this->name_api && this->size_name_api ? this->name_api : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetExternalAPINameSize() const noexcept override {
			return this->name_api && this->size_name_api ? this->size_name_api : 0;
		}
		/// <summary>Gets the address to the external API, if available.</summary>
		/// <returns>
		/// Returns the address to the external API, if available.
		/// If no meaningful address can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const void* GetExternalAPIAddress() const noexcept override {
			return this->address_api ? this->address_api : nullptr;
		}
	protected:
		char* name_api = nullptr;
		size_t size_name_api = 0;
		const void* address_api = nullptr;
	};

	/// <summary>
	/// A default implementation of <c>IUnexpectedExceptionException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IUnexpectedExceptionException</c>.
	/// </summary>
	class UnexpectedExceptionException
		: public virtual Exception,
		public virtual IUnexpectedExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(UnexpectedExceptionException, , "a7f160c0-3ccc-45ab-aa5a-3172469faf64");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(UnexpectedExceptionException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>UnexpectedExceptionException</c> object.</summary>
		/// <param name="_filename_source_code">
		/// The filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_filename_source_code">
		/// The size (in <c>char</c>s) of the filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_linenumber_source_code">
		/// The line number of the source code at which the exception has occured, if available.
		/// If no meaningful line number can be provided, pass <c>-1</c>.
		/// </param>
		inline UnexpectedExceptionException(const char* _filename_source_code, size_t _size_filename_source_code, int _linenumber_source_code) noexcept {
			if (_filename_source_code && _size_filename_source_code) {
				this->size_filename_source_code = _size_filename_source_code;
				this->filename_source_code = reinterpret_cast<char*>(ExceptionAllocateMemory(this->size_filename_source_code * sizeof(char)));
				memcpy(this->filename_source_code, _filename_source_code, this->size_filename_source_code * sizeof(char));
			}
			if (_linenumber_source_code != -1) this->linenumber_source_code = _linenumber_source_code;
		}
		inline virtual ~UnexpectedExceptionException() {
			if (this->filename_source_code) {
				ExceptionFreeMemory(this->filename_source_code);
				this->filename_source_code = nullptr;
			}
			this->size_filename_source_code = 0;
			this->linenumber_source_code = -1;
		}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the filename of the source code file in which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetSourceCodeFileName() const noexcept override {
			return this->filename_source_code && this->size_filename_source_code ? this->filename_source_code : nullptr;
		}
		/// <summary>Gets the size (in <c>char</c>s) of the filename of the source code file in which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the size (in <c>char</c>s) of the filename, in UTF-8, of the source code file in which the exception has occured, if available.
		/// If no meaningful filename can be provided, <c>0</c> is returned.
		/// </returns>
		inline virtual size_t GetSourceCodeFileNameSize() const noexcept override {
			return this->filename_source_code && this->size_filename_source_code ? this->size_filename_source_code : 0;
		}
		/// <summary>Gets the line number of the source code at which the exception has occured, if available.</summary>
		/// <returns>
		/// Returns the line number of the source code at which the exception has occured, if available.
		/// If no meaningful line number can be provided, <c>-1</c> is returned.
		/// </returns>
		inline virtual int GetSourceCodeLineNumber() const noexcept override {
			return this->linenumber_source_code != -1 ? this->linenumber_source_code : -1;
		}
	protected:
		char* filename_source_code = nullptr;
		size_t size_filename_source_code = 0;
		int linenumber_source_code = -1;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	//}
#pragma endregion Exception classes that provide a default implementation but may not be transferred across executable modules without using an exception interface class pointer.

	void YBWLIB2_CALLTYPE Exception_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Exception_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Exception_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef YBWLIB2_EXCEPTION_MACROS_ENABLED

#ifndef YBWLIB2_EXCEPTION_MACROS_DEFINED

#pragma region Default exception implementation objects creating macros
//{ Default exception implementation objects creating macros

#define YBWLIB2_EXCEPTION_CREATE_EXCEPTION() (new ::YBWLib2::Exception())

#define YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION() (new ::YBWLib2::DoubleExceptionException())

#define YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(funcname) (new ::YBWLib2::InvalidParameterException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname))) / sizeof(char)) - 1))

#define YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(classname, funcname) (new ::YBWLib2::InvalidParameterException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname))) / sizeof(char)) - 1,YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(classname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(classname))) / sizeof(char)) - 1))

#define YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(funcname) (new ::YBWLib2::InvalidCallException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname))) / sizeof(char)) - 1))

#define YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(classname, funcname) (new ::YBWLib2::InvalidCallException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(funcname))) / sizeof(char)) - 1,YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(classname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(classname))) / sizeof(char)) - 1))

#define YBWLIB2_EXCEPTION_CREATE_INSUFFICIENT_BUFFER_EXCEPTION(bufferaddr) (new ::YBWLib2::InsufficientBufferException(bufferaddr))

#define YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION() (new ::YBWLib2::MemoryAllocFailureException())

#define YBWLIB2_EXCEPTION_CREATE_KEY_ALREADY_EXIST_EXCEPTION() (new ::YBWLib2::KeyAlreadyExistException())

#define YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION() (new ::YBWLib2::KeyNotExistException())

#define YBWLIB2_EXCEPTION_CREATE_UNHANDLED_UNKNOWN_EXCEPTION_EXCEPTION() (new ::YBWLib2::UnhandledUnknownExceptionException())

#define YBWLIB2_EXCEPTION_CREATE_STL_EXCEPTION_EXCEPTION(stlexceptionname) (new ::YBWLib2::STLExceptionException((stlexceptionname).what()))

#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_EXCEPTION(apiname) (new ::YBWLib2::ExternalAPIFailureException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname)))

#define YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION() (new ::YBWLib2::UnexpectedExceptionException(YBWLIB2_TO_UTF8(__FILE__), (sizeof(YBWLIB2_TO_UTF8(__FILE__)) / sizeof(char)) - 1, __LINE__))

//}
#pragma endregion These macros are used to create exception objects with the above default implementation.

#define YBWLIB2_EXCEPTION_MACROS_DEFINED
#endif

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#endif
