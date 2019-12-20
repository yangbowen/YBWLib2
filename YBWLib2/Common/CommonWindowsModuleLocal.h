#ifndef _INCLUDE_GUARD_CAE73D50_B22F_4835_AF06_D540604B0D16
#define _INCLUDE_GUARD_CAE73D50_B22F_4835_AF06_D540604B0D16

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "Common.h"
#include "CommonSTLHelper.h"
#include "CommonWindows.h"

namespace YBWLib2 {
	void YBWLIB2_CALLTYPE CommonWindows_RealInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<ReferenceCountedCOMObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ReferenceCountedCOMObject)), module_info_current);
	}

	void YBWLIB2_CALLTYPE CommonWindows_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<ReferenceCountedCOMObject>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
