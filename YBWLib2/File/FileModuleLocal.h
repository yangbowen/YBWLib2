#ifndef _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E
#define _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "File.h"

namespace YBWLib2 {
	void YBWLIB2_CALLTYPE File_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<ISeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<IInputFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInputFile)), module_info_current);
		GetDynamicTypeThisClassObject<IOutputFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IOutputFile)), module_info_current);
	}

	void YBWLIB2_CALLTYPE File_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IOutputFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInputFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
