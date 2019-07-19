#ifndef _INCLUDE_GUARD_5C9C6DAF_E965_4CC9_887B_88AE85D8524A
#define _INCLUDE_GUARD_5C9C6DAF_E965_4CC9_887B_88AE85D8524A

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "Common.h"
#include "CommonSTLHelper.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ReferenceCountedObject, );

	void YBWLIB2_CALLTYPE Common_RealInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<IReferenceCountedObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IReferenceCountedObject)), module_info_current);
		GetDynamicTypeClassObject<ILockableObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ILockableObject)), module_info_current);
		ReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<ReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<ReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<ReferenceCountedObject, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ReferenceCountedObject), alignof(ReferenceCountedObject)
		);
		GetDynamicTypeClassObject<ReferenceCountedObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ReferenceCountedObject)), module_info_current);
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<ReferenceCountedObject>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete ReferenceCountedObject::DynamicTypeThisClassObject;
		ReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeClassObject<ILockableObject>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IReferenceCountedObject>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
