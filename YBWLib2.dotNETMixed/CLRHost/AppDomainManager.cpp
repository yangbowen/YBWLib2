#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../YBWLib2dotNETMixedApi.h"
#include "AppDomainManager.h"

#pragma managed(push, off)

namespace YBWLib2 {
	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_InitDLL() noexcept;
	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_UnInitDLL() noexcept;

	struct preinit_t {
		preinit_t() noexcept {
			::YBWLib2::YBWLib2dotNETMixed_InitDLL();
		}
		~preinit_t() {
			::YBWLib2::YBWLib2dotNETMixed_UnInitDLL();
		}
	} preinit;
}

#pragma managed(pop)

#pragma managed(push, on)

namespace YBWLib2::dotNETMixed {
	YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED AppDomainManager::AppDomainManager() {
	}

	YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED AppDomainManager::~AppDomainManager() {
	}
}

#pragma managed(pop)
