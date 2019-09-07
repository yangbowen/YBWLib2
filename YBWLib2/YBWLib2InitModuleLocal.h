#ifndef _INCLUDE_GUARD_9F152DB0_9C4B_4804_BFF3_EF102AC3D6C9
#define _INCLUDE_GUARD_9F152DB0_9C4B_4804_BFF3_EF102AC3D6C9

#include <atomic>
#include <mutex>
#include "YBWLib2Api.h"
#include "YBWLib2Init.h"
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
	static ::std::atomic<uintptr_t> usecount_YBWLib2_ModuleLocal(0);
	static ::std::once_flag onceflag_YBWLib2_RealInitModuleLocal;
	static ::std::once_flag onceflag_YBWLib2_RealUnInitModuleLocal;

	static void YBWLIB2_CALLTYPE YBWLib2_RealInitModuleLocal() noexcept {
		try {
			YBWLib2_InitDLL();
			CommonLowLevel_RealInitModuleLocal();
			ExceptionLowLevel_RealInitModuleLocal();
			DynamicType_RealInitModuleLocal();
			Exception_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealInitModuleLocal();
#endif
			Common_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			CommonWindows_RealInitModuleLocal();
#endif
			Pipeline_RealInitModuleLocal();
			JSON_RealInitModuleLocal();
			UserInterface_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			UserInterfaceWindows_RealInitModuleLocal();
#endif
			File_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			FileWindows_RealInitModuleLocal();
#endif
#ifdef _WIN32_WINNT
			DebuggingWindows_RealInitModuleLocal();
#endif
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2_CALLTYPE YBWLib2_RealUnInitModuleLocal() noexcept {
		try {
#ifdef _WIN32_WINNT
			DebuggingWindows_RealUnInitModuleLocal();
#endif
#ifdef _WIN32_WINNT
			FileWindows_RealUnInitModuleLocal();
#endif
			File_RealUnInitModuleLocal();
#ifdef _WIN32_WINNT
			UserInterfaceWindows_RealUnInitModuleLocal();
#endif
			UserInterface_RealUnInitModuleLocal();
			JSON_RealUnInitModuleLocal();
			Pipeline_RealUnInitModuleLocal();
#ifdef _WIN32_WINNT
			CommonWindows_RealUnInitModuleLocal();
#endif
			Common_RealUnInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealUnInitModuleLocal();
#endif
			Exception_RealUnInitModuleLocal();
			DynamicType_RealUnInitModuleLocal();
			ExceptionLowLevel_RealUnInitModuleLocal();
			CommonLowLevel_RealUnInitModuleLocal();
			YBWLib2_UnInitDLL();
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE YBWLib2_InitModuleLocal() noexcept {
		try {
			::std::call_once(onceflag_YBWLib2_RealInitModuleLocal, YBWLib2_RealInitModuleLocal);
			++usecount_YBWLib2_ModuleLocal;
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE YBWLib2_UnInitModuleLocal() noexcept {
		try {
			if (!--usecount_YBWLib2_ModuleLocal) ::std::call_once(onceflag_YBWLib2_RealUnInitModuleLocal, YBWLib2_RealUnInitModuleLocal);
		} catch (...) {
			abort();
		}
	}
}

#endif
