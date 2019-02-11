#pragma once
#include <cstdint>
#include "../YBWLib2Api.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
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

	/// <summary>Exception.</summary>
	class IException abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(IException, YBWLIB2_API, "{0A010AD2-24CD-48A4-90C4-EBB66618E7CE}");
		inline virtual ~IException() = default;
		/// <summary>Gets the exception flags.</summary>
		/// <returns>The exception flags.</returns>
		virtual ExceptionFlags GetExceptionFlags() const noexcept = 0;
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
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(IDoubleExceptionException, YBWLIB2_API, "{AE163E22-B2EF-4381-A092-025309287D53}");
		inline virtual ~IDoubleExceptionException() = default;
	};

	/// <summary>An exception that occurs because of failing to call a system API.</summary>
	class ISystemAPIFailureException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(ISystemAPIFailureException, YBWLIB2_API, "{E921F6A5-62A6-45B7-A517-45C001154FA4}");
		inline virtual ~ISystemAPIFailureException() = default;
		/// <summary>Gets the address to the system API, if available.</summary>
		/// <returns>
		/// Returns the address to the system API if available.
		/// If no meaningful address can be provided, <c>nullptr</c> is returned.
		/// </returns>
		virtual const void* GetSystemAPIAddress() const noexcept = 0;
	};

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
}
