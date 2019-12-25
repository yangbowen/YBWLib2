#ifndef _INCLUDE_GUARD_7DD6EE9B_1104_4104_A1E3_03E7973992CB
#define _INCLUDE_GUARD_7DD6EE9B_1104_4104_A1E3_03E7973992CB

#include "../YBWLib2/YBWLib2Init.h"

#include "YBWLib2dotNETMixedApi.h"

namespace YBWLib2 {
	/// <summary>
	/// Increments the YBWLib2.dotNETMixed global use count (not to be confused with the library use count keeped by the system).
	/// Performs initialization for the YBWLib2.dotNETMixed DLL if the use count is incremented from <c>0</c>.
	/// </summary>
	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_InitDLL() noexcept;
	/// <summary>
	/// Decrements the YBWLib2.dotNETMixed global use count (not to be confused with the library use count keeped by the system).
	/// Performs uninitialization for the YBWLib2.dotNETMixed DLL if the use count is decremented to <c>0</c>.
	/// </summary>
	YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE YBWLib2dotNETMixed_UnInitDLL() noexcept;
}

#endif
