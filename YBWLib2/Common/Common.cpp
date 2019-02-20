#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "Common.h"
#include "CommonSTLHelper.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountedObject, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ILockableObject, YBWLIB2_API);

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IReferenceCountedObject, IDynamicTypeObject);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(ILockableObject, IDynamicTypeObject);
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(ILockableObject);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IReferenceCountedObject);
	}
}
