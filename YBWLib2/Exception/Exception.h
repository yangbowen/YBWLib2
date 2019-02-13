#ifndef _INCLUDE_GUARD_6D5B340E_F74B_4EDD_83D5_6BAB5945B5D8
#define _INCLUDE_GUARD_6D5B340E_F74B_4EDD_83D5_6BAB5945B5D8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_UNDEF_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include <cstdint>
#include <type_traits>
#include <memory>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
#pragma region ExceptionFlags
	//{ ExceptionFlags

	/// <summary>Exception flags.</summary>
	typedef uint64_t ExceptionFlags;

	// Exception flag definitions:
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
	/// Get the maximum amount of memory that could potentially be allocated by <c>ExceptionAllocateMemory</c>.
	/// Memory allocations within this limit can still fail.
	/// </summary>
	YBWLIB2_API size_t YBWLIB2_CALLTYPE ExceptionGetMaxMemorySize() noexcept;
	/// <summary>
	/// Allocate memory from a separate store dedicated to exception handling.
	/// The allocated memory is zero-initialized.
	/// Because memory is committed in advance for this separate store, this function usually succeeds even if the system memory is insufficient.
	/// The size of this separate store is limited, so don't waste memory allocated with this function on purposes unrelated to exception handling.
	/// Failure to allocating memory in this function is considered fatal, and results in the process being terminated.
	/// </summary>
	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept;
	/// <summary>
	/// Free memory previously allocated with <c>ExceptionAllocateMemory</c>.
	/// Failure to free memory in this function is considered fatal, and results in the process being terminated.
	/// </summary>
	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept;

	/// <summary>Allocator template structure for allocating memory for exception handling.</summary>
	template<typename _Ty>
	struct allocator_exception {
		typedef _Ty value_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty& reference;
		typedef const _Ty& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_exception<_Rebind_Ty>;
		};
		using propagate_on_container_move_assignment = ::std::true_type;
		constexpr allocator_exception() noexcept = default;
		constexpr allocator_exception(const allocator_exception&) noexcept = default;
		inline pointer address(reference ref) const noexcept { return ::std::addressof(ref); }
		inline const_pointer address(const_reference ref) const noexcept { return ::std::addressof(ref); }
		inline pointer allocate(size_type count, const void* hint = nullptr) const noexcept {
			static_cast<void>(hint);
			return ExceptionAllocateMemory(count * sizeof(value_type));
		}
		inline void deallocate(pointer ptr, size_type count) const noexcept {
			static_cast<void>(count);
			return ExceptionFreeMemory(ptr);
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
	};
	/// <summary>Allocator template structure for allocating memory for exception handling.</summary>
	template<>
	struct allocator_exception<void> {
		typedef void value_type;
		typedef void* pointer;
		typedef const void* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_exception<_Rebind_Ty>;
		};
		using propagate_on_container_move_assignment = ::std::true_type;
		constexpr allocator_exception() noexcept = default;
		constexpr allocator_exception(const allocator_exception&) noexcept = default;
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty...>(args...));
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
	};

	//}
#pragma endregion These functions and templates can be used to allocate memory from a separate store dedicated to exception handling, which may be used even when the system memory is insufficient.

#pragma region Exception interface classes
	//{ Exception interface classes

	/// <summary>Exception.</summary>
	class IException abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IException, YBWLIB2_API, "{0A010AD2-24CD-48A4-90C4-EBB66618E7CE}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IException);
		IException() noexcept = default;
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
		/// <summary>Gets the exception flags.</summary>
		/// <returns>The exception flags.</returns>
		virtual ExceptionFlags GetExceptionFlags() const noexcept = 0;
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
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* AttachCause(IException* exception_cause_new) noexcept = 0;
		/// <summary>Gets a pointer to the <c>IException</c> object that represents the underlying cause of this exception.</summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called continues to own the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetCause(IException** exception_cause_ret) noexcept = 0;
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
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer
		/// (and the object pointed to by <c>*exception_cause</c>).
		/// </returns>
		[[nodiscard]] virtual IException* DetachCause(IException** exception_cause_ret) noexcept = 0;
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
	};

	/// <summary>An exception that occurs when handling another exception.</summary>
	class IDoubleExceptionException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IDoubleExceptionException, YBWLIB2_API, "{AE163E22-B2EF-4381-A092-025309287D53}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IDoubleExceptionException);
		inline virtual ~IDoubleExceptionException() = default;
	};

	/// <summary>An exception that occurs because of failing to call an external API.</summary>
	class IExternalAPIFailureException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureException, YBWLIB2_API, "{E921F6A5-62A6-45B7-A517-45C001154FA4}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureException);
		inline virtual ~IExternalAPIFailureException() = default;
		/// <summary>Gets the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetExternalAPIName() const noexcept = 0;
		/// <summary>Gets the size of the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the size of the name, in UTF-8, of the external API, if available.
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

	//}
#pragma endregion Exception classes that may be transferred across executable module boundaries.

#pragma region Exception implementation classes
	//{ Exception implementation classes

	/// <summary>
	/// A default implementation of <c>IException</c>.
	/// One executable module should NOT be allowed to access objects using this type created by other executable modules.
	/// Instead, access by <c>IException</c>.
	/// </summary>
	class Exception : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Exception, , "{2C62414A-B7A5-4404-9C0B-504BB02E7644}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Exception);
		inline Exception() noexcept {}
		inline virtual ~Exception() {
			if (this->exception_cause) {
				delete this->exception_cause;
				this->exception_cause = nullptr;
			}
		}
		/// <summary>Get the exception flags.</summary>
		/// <returns>The exception flags.</returns>
		inline virtual ExceptionFlags GetExceptionFlags() const noexcept override { return 0; }
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
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] inline virtual IException* AttachCause(IException* exception_cause_new) noexcept override {
			if (this->exception_cause) {
				delete this->exception_cause;
				this->exception_cause = nullptr;
			}
			this->exception_cause = exception_cause_new;
			return this;
		}
		/// <summary>Gets a pointer to the <c>IException</c> object that represents the underlying cause of this exception.</summary>
		/// <param name="exception_cause_ret">
		/// Pointer to a pointer variable that receives a pointer to the underlying cause of this exception.
		/// After successfully returning from this member function, <c>*exception_cause</c> will be set to the underlying cause of this exception.
		/// Any value originally in <c>*exception_cause</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The object on which this function is called continues to own the object pointed to by the new <c>*exception_cause</c> after a successful call.
		/// If there wasn't an underlying cause of this exception, <c>*exception_cause</c> will be set to an empty pointer.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetCause(IException** exception_cause_ret) noexcept override {
			*exception_cause_ret = this->exception_cause;
			return this;
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
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer
		/// (and the object pointed to by <c>*exception_cause</c>).
		/// </returns>
		[[nodiscard]] inline virtual IException* DetachCause(IException** exception_cause_ret) noexcept override {
			*exception_cause_ret = this->exception_cause;
			if (this->exception_cause) {
				delete this->exception_cause;
				this->exception_cause = nullptr;
			}
			return this;
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
	private:
		IException* exception_cause = nullptr;
		uintptr_t userdata = 0;
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IDoubleExceptionException</c>.
	/// One executable module should NOT be allowed to access objects using this type created by other executable modules.
	/// Instead, access by <c>IDoubleExceptionException</c>.
	/// </summary>
	class DoubleExceptionException
		: public virtual Exception,
		public virtual IDoubleExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(DoubleExceptionException, , "{12F7B9FB-928E-4197-8DF7-B33DD0FDABDC}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(DoubleExceptionException);
		inline DoubleExceptionException() noexcept = default;
		inline virtual ~DoubleExceptionException() = default;
		inline virtual ExceptionFlags GetExceptionFlags() const noexcept override { return this->Exception::GetExceptionFlags() | ExceptionFlag_DoubleException; }
	};

	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureException</c>.
	/// One executable module should NOT be allowed to access objects using this type created by other executable modules.
	/// Instead, access by <c>IExternalAPIFailureException</c>.
	/// </summary>
	class ExternalAPIFailureException
		: public virtual Exception,
		public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureException, , "{960E5785-6CE2-4EBE-BAB4-BB43B540AF22}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureException);
		/// <summary>Constructs an <c>ExternalAPIFailureException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		inline ExternalAPIFailureException(const char* _name_api, size_t _size_name_api, const void* _address_api) noexcept {
			if (_name_api && _size_name_api) {
				this->size_name_api = _size_name_api;
				this->name_api = new char[this->size_name_api]();
			}
			if (_address_api) this->address_api = _address_api;
		}
		inline virtual ~ExternalAPIFailureException() {
			if (this->name_api) {
				delete[] this->name_api;
				this->name_api = nullptr;
			}
		}
		/// <summary>Gets the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetExternalAPIName() const noexcept override {
			return this->name_api && this->size_name_api ? this->name_api : nullptr;
		}
		/// <summary>Gets the size of the name of the external API, if available.</summary>
		/// <returns>
		/// Returns the size of the name, in UTF-8, of the external API, if available.
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
	private:
		char* name_api = nullptr;
		size_t size_name_api = 0;
		const void* address_api = nullptr;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	//}
#pragma endregion Exception classes that provide a default implementation but may not be transferred across executable modules without using an exception interface class pointer.

#pragma region Default exception implementation objects creating macros
	//{ Default exception implementation objects creating macros

#ifdef YBWLIB2_EXCEPTION_MACROS_ENABLED

#ifndef YBWLIB2_EXCEPTION_CREATE_EXCEPTION
#define YBWLIB2_EXCEPTION_CREATE_EXCEPTION() (new Exception())
#endif

#ifndef YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION
#define YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION() (new DoubleExceptionException())
#endif

#ifndef YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_EXCEPTION
#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_EXCEPTION(apiname) (new ExternalAPIFailureException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname)))
#endif

#endif

	//}
#pragma endregion These macros are used to create exception objects with the above default implementation.
}

#ifdef _MACRO_UNDEF_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#undef _MACRO_UNDEF_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_32EC34B6_5BCE_48CC_B1F7_BEDFC08A5774
#endif

#endif
