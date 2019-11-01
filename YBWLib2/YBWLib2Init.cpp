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
#ifdef _WIN32_WINNT
#include "Common/CommonWindows.h"
#endif
#include "Pipeline/Pipeline.h"
#include "JSON/JSON.h"
#include "UserInterface/UserInterface.h"
#ifdef _WIN32_WINNT
#include "UserInterface/UserInterfaceWindows.h"
#endif
#include "File/File.h"
#ifdef _WIN32_WINNT
#include "File/FileWindows.h"
#endif
#ifdef _WIN32_WINNT
#include "Debugging/DebuggingWindows.h"
#endif

namespace YBWLib2 {
	static void YBWLIB2_CALLTYPE YBWLib2_RealInitDLL() noexcept;
	static void YBWLIB2_CALLTYPE YBWLib2_RealUnInitDLL() noexcept;

	static SharedResourceInitializer sharedresourceinitializer_YBWLib2_DLL(&YBWLib2_RealInitDLL, &YBWLib2_RealUnInitDLL);

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
#ifdef _WIN32_WINNT
			CommonWindows_RealInitGlobal();
			CommonWindows_RealInitModuleLocal();
#endif
			Pipeline_RealInitGlobal();
			Pipeline_RealInitModuleLocal();
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
			PipelineUserInterface_RealInitGlobal();
			JSONUserInterface_RealInitGlobal();
			File_RealInitGlobal();
			File_RealInitModuleLocal();
			FileUserInterface_RealInitGlobal();
#ifdef _WIN32_WINNT
			FileWindows_RealInitGlobal();
			FileWindows_RealInitModuleLocal();
			FileWindowsUserInterface_RealInitGlobal();
#endif
#ifdef _WIN32_WINNT
			DebuggingWindows_RealInitGlobal();
			DebuggingWindows_RealInitModuleLocal();
			DebuggingWindowsUserInterface_RealInitGlobal();
#endif
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2_CALLTYPE YBWLib2_RealUnInitDLL() noexcept {
		try {
#ifdef _WIN32_WINNT
			DebuggingWindowsUserInterface_RealUnInitGlobal();
			DebuggingWindows_RealUnInitModuleLocal();
			DebuggingWindows_RealUnInitGlobal();
#endif
#ifdef _WIN32_WINNT
			FileWindowsUserInterface_RealUnInitGlobal();
			FileWindows_RealUnInitModuleLocal();
			FileWindows_RealUnInitGlobal();
#endif
			FileUserInterface_RealUnInitGlobal();
			File_RealUnInitModuleLocal();
			File_RealUnInitGlobal();
			JSONUserInterface_RealUnInitGlobal();
			PipelineUserInterface_RealUnInitGlobal();
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
			Pipeline_RealUnInitModuleLocal();
			Pipeline_RealUnInitGlobal();
#ifdef _WIN32_WINNT
			CommonWindows_RealUnInitModuleLocal();
			CommonWindows_RealUnInitGlobal();
#endif
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
		sharedresourceinitializer_YBWLib2_DLL.Initialize();
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE YBWLib2_UnInitDLL() noexcept {
		sharedresourceinitializer_YBWLib2_DLL.UnInitialize();
	}
}
