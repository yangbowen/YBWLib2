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
#include "JSON/JSON.h"
#include "UserInterface/UserInterface.h"
#include "File/File.h"

namespace YBWLib2 {
	static ::std::atomic<uintptr_t> usecount_YBWLib2_ModuleLocal(0);
	static ::std::once_flag onceflag_YBWLib2_RealInitModuleLocal;
	static ::std::once_flag onceflag_YBWLib2_RealUnInitModuleLocal;

	static void YBWLIB2_CALLTYPE YBWLib2_RealInitModuleLocal() noexcept {
		try {
			YBWLib2_InitDLL();
			CommonLowLevel_RealInitModuleLocal();
			DynamicType_RealInitModuleLocal();
			Exception_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealInitModuleLocal();
#endif
			Common_RealInitModuleLocal();
			JSON_RealInitModuleLocal();
			UserInterface_RealInitModuleLocal();
			ExceptionUserInterface_RealInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindowsUserInterface_RealInitModuleLocal();
#endif
			File_RealInitModuleLocal();
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2_CALLTYPE YBWLib2_RealUnInitModuleLocal() noexcept {
		try {
			File_RealUnInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindowsUserInterface_RealUnInitModuleLocal();
#endif
			ExceptionUserInterface_RealUnInitModuleLocal();
			UserInterface_RealUnInitModuleLocal();
			JSON_RealUnInitModuleLocal();
			Common_RealUnInitModuleLocal();
#ifdef _WIN32_WINNT
			ExceptionWindows_RealUnInitModuleLocal();
#endif
			Exception_RealUnInitModuleLocal();
			DynamicType_RealUnInitModuleLocal();
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
