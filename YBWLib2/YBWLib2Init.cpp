#include "pch.h"
#include "Windows.h"
#include "YBWLib2Api.h"
#include "YBWLib2Init.h"
#include "YBWLib2InternalConfig.h"
#include "Common/CommonLowLevel.h"
#include "DynamicType/DynamicType.h"
#include "Exception/Exception.h"
#ifdef _WIN32_WINNT
#include "Exception/ExceptionWindows.h"
#endif
#include "Common/Common.h"
#include "JSON/JSON.h"
#include "UserInterface/UserInterface.h"
#ifdef _WIN32_WINNT
#include "UserInterface/UserInterfaceWindows.h"
#endif
#include "File/File.h"

namespace YBWLib2 {
	static ::std::atomic<uintptr_t> usecount_YBWLib2_DLL(0);
	static ::std::once_flag onceflag_YBWLib2_RealInitDLL;
	static ::std::once_flag onceflag_YBWLib2_RealUnInitDLL;

	static void YBWLIB2_CALLTYPE YBWLib2_RealInitDLL() noexcept {
		try {
			CommonLowLevel_RealInitGlobal();
			CommonLowLevel_RealInitModuleLocal();
			ExceptionLowLevel_RealInitGlobal();
			ExceptionLowLevel_RealInitModuleLocal();
			DynamicType_RealInitGlobal();
			DynamicType_RealInitModuleLocal();
			Exception_RealInitGlobal();
			Exception_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealInitGlobal();
			ExceptionWindows_RealInitModuleLocal();
#endif
			Common_RealInitGlobal();
			Common_RealInitModuleLocal();
			JSON_RealInitGlobal();
			JSON_RealInitModuleLocal();
			Internal::YBWLib2InternalConfig_RealInitGlobal();
			UserInterface_RealInitGlobal();
			UserInterface_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			UserInterfaceWindows_RealInitGlobal();
			UserInterfaceWindows_RealInitModuleLocal();
#endif
			ExceptionUserInterface_RealInitGlobal();
#ifdef _WIN32_WINNT
			ExceptionWindowsUserInterface_RealInitGlobal();
#endif
			File_RealInitGlobal();
			File_RealInitModuleLocal();
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2_CALLTYPE YBWLib2_RealUnInitDLL() noexcept {
		try {
			File_RealUnInitModuleLocal();
			File_RealUnInitGlobal();
#ifdef _WIN32_WINNT
			ExceptionWindowsUserInterface_RealUnInitGlobal();
#endif
			ExceptionUserInterface_RealUnInitGlobal();
#ifdef _WIN32_WINNT
			UserInterfaceWindows_RealUnInitModuleLocal();
			UserInterfaceWindows_RealUnInitGlobal();
#endif
			UserInterface_RealUnInitModuleLocal();
			UserInterface_RealUnInitGlobal();
			Internal::YBWLib2InternalConfig_RealUnInitGlobal();
			JSON_RealUnInitModuleLocal();
			JSON_RealUnInitGlobal();
			Common_RealUnInitModuleLocal();
			Common_RealUnInitGlobal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealUnInitModuleLocal();
			ExceptionWindows_RealUnInitGlobal();
#endif
			Exception_RealUnInitModuleLocal();
			Exception_RealUnInitGlobal();
			DynamicType_RealUnInitModuleLocal();
			DynamicType_RealUnInitGlobal();
			ExceptionLowLevel_RealUnInitModuleLocal();
			ExceptionLowLevel_RealUnInitGlobal();
			CommonLowLevel_RealUnInitModuleLocal();
			CommonLowLevel_RealUnInitGlobal();
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE YBWLib2_InitDLL() noexcept {
		try {
			::std::call_once(onceflag_YBWLib2_RealInitDLL, YBWLib2_RealInitDLL);
			++usecount_YBWLib2_DLL;
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE YBWLib2_UnInitDLL() noexcept {
		try {
			if (!--usecount_YBWLib2_DLL) ::std::call_once(onceflag_YBWLib2_RealUnInitDLL, YBWLib2_RealUnInitDLL);
		} catch (...) {
			abort();
		}
	}
}
