#include "pch.h"
#include "../YBWLib2/YBWLib2Init.h"
#include "YBWLib2dotNETMixedApi.h"
#include "YBWLib2dotNETMixedInit.h"

namespace YBWLib2 {
	static void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealInitDLL() noexcept;
	static void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealUnInitDLL() noexcept;
	extern void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealInitDLL_Managed() noexcept(false);
	extern void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealUnInitDLL_Managed() noexcept(false);

	static void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealInitDLL() noexcept {
		try {
			YBWLib2_InitModuleLocal();
			YBWLib2dotNETMixed_RealInitDLL_Managed();
		} catch (...) {
			abort();
		}
	}

	static void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_RealUnInitDLL() noexcept {
		try {
			YBWLib2dotNETMixed_RealUnInitDLL_Managed();
			YBWLib2_UnInitModuleLocal();
		} catch (...) {
			abort();
		}
	}

	static SharedResourceInitializer& GetSharedResourceInitializer_YBWLib2dotNETMixed_DLL() noexcept {
		static SharedResourceInitializer sharedresourceinitializer(&YBWLib2dotNETMixed_RealInitDLL, &YBWLib2dotNETMixed_RealUnInitDLL);
		return sharedresourceinitializer;
	}

	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_InitDLL() noexcept {
		GetSharedResourceInitializer_YBWLib2dotNETMixed_DLL().Initialize();
	}

	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_UnInitDLL() noexcept {
		GetSharedResourceInitializer_YBWLib2dotNETMixed_DLL().UnInitialize();
	}
}
