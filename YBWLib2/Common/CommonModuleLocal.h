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
		GetDynamicTypeThisClassObject<IReferenceCountedObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IReferenceCountedObject)), module_info_current);
		GetDynamicTypeThisClassObject<ILockableObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ILockableObject)), module_info_current);
		ReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<ReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<ReferenceCountedObject, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> }
		);
		GetDynamicTypeThisClassObject<ReferenceCountedObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ReferenceCountedObject)), module_info_current);
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<ReferenceCountedObject>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete ReferenceCountedObject::DynamicTypeThisClassObject;
		ReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<ILockableObject>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IReferenceCountedObject>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
