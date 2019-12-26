#include "pch.h"
#include "../YBWLib2/YBWLib2Init.h"
#include "YBWLib2dotNETUnmanagedApi.h"
#include "YBWLib2dotNETUnmanagedInit.h"
#include "CLRHost/CLRHost.h"

namespace YBWLib2 {
	static void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_RealInitDLL() noexcept;
	static void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_RealUnInitDLL() noexcept;

	static void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_RealInitDLL() noexcept {
		try {
			YBWLib2_InitModuleLocal();
			CLRHost_RealInitGlobal();
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_RealUnInitDLL() noexcept {
		try {
			CLRHost_RealUnInitGlobal();
			YBWLib2_UnInitModuleLocal();
		} catch (...) {
			abort();
		}
	}

	static SharedResourceInitializer& GetSharedResourceInitializer_YBWLib2dotNETUnmanaged_DLL() noexcept {
		static SharedResourceInitializer sharedresourceinitializer(&YBWLib2dotNETUnmanaged_RealInitDLL, &YBWLib2dotNETUnmanaged_RealUnInitDLL);
		return sharedresourceinitializer;
	}

	YBWLIB2DOTNETUNMANAGED_API void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_InitDLL() noexcept {
		GetSharedResourceInitializer_YBWLib2dotNETUnmanaged_DLL().Initialize();
	}

	YBWLIB2DOTNETUNMANAGED_API void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_UnInitDLL() noexcept {
		GetSharedResourceInitializer_YBWLib2dotNETUnmanaged_DLL().UnInitialize();
	}
}
