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
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(ReferenceCountedObject, IReferenceCountedObject);
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(ReferenceCountedObject);
	}
}

#endif
