#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_39802C61_29BE_45D6_B8C0_08400073B687
#define _INCLUDE_GUARD_39802C61_29BE_45D6_B8C0_08400073B687

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <mutex>
#include <minwindef.h>
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"
#include "File.h"

namespace YBWLib2 {
	void YBWLIB2_CALLTYPE FileWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#endif
