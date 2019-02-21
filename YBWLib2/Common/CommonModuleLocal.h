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
		ReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<ReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<ReferenceCountedObject, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> }
		);
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept {
		delete ReferenceCountedObject::DynamicTypeThisClassObject;
		ReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
