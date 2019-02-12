#pragma once
#include <cstdint>
#include "Exception.h"

#ifndef YBWLIB2_EXPORTS
#error "This header file is only intended to be used by the library internally."
#endif

namespace YBWLib2 {
	/// <summary>Exception.</summary>
	class Exception : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Exception, YBWLIB2_API, "{2C62414A-B7A5-4404-9C0B-504BB02E7644}");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Exception);
		virtual ~Exception() = default;
		/// <summary>Get the exception flags.</summary>
		/// <returns>The exception flags.</returns>
		virtual ExceptionFlags GetExceptionFlags() const noexcept override { return 0; }
		/// <summary>
		/// Get the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <returns>The value of the variable.</returns>
		virtual uintptr_t GetUserData() const noexcept override { return this->userdata; }
		/// <summary>
		/// Set the additional variable reserved for exception handling routines in applications.
		/// Classes that implements this class must provide storage for this variable.
		/// Library functions must not change this variable, except when required by the application by calling <c>SetUserData</c> on the object.
		/// Nor can library functions depend on the value of this variable.
		/// This variable must be initialized to <c>0</c> when constructing the object.
		/// </summary>
		/// <param name="val_new">The new value of the variable.</param>
		virtual void SetUserData(uintptr_t val_new) noexcept override { this->userdata = val_new; }
	private:
		uintptr_t userdata = 0;
	};
}
