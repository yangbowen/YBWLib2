#pragma once
#include <cstdint>
#include "CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
	/// <summary>Reference counted object.</summary>
	class IReferenceCountedObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IReferenceCountedObject, YBWLIB2_API, "{7266C5C6-2238-44A0-B8D7-B8A662591EC7}");
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
	};

	/// <summary>Lockable object.</summary>
	class ILockableObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ILockableObject, YBWLIB2_API, "{E0DEDC23-28AF-48BC-A89F-D254C4389613}");
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
}
