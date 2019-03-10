#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "Common.h"
#include "CommonSTLHelper.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountedObject, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ILockableObject, YBWLIB2_API);

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept {
		IReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<IReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<IReferenceCountedObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IReferenceCountedObject), alignof(IReferenceCountedObject));
		ILockableObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ILockableObject>(),
			IsDynamicTypeModuleLocalClass<ILockableObject>(),
			{ DynamicTypeBaseClassDef<ILockableObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ILockableObject), alignof(ILockableObject));
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept {
		delete ILockableObject::DynamicTypeThisClassObject;
		ILockableObject::DynamicTypeThisClassObject = nullptr;
		delete IReferenceCountedObject::DynamicTypeThisClassObject;
		IReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
	}
}
