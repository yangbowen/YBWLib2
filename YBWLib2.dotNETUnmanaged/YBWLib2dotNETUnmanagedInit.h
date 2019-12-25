#ifndef _INCLUDE_GUARD_B747B247_C83C_4DFC_8505_F166C5D24233
#define _INCLUDE_GUARD_B747B247_C83C_4DFC_8505_F166C5D24233

#include "../YBWLib2/YBWLib2Init.h"

#include "YBWLib2dotNETUnmanagedApi.h"

namespace YBWLib2 {
	/// <summary>
	/// Increments the YBWLib2.dotNETUnmanaged global use count (not to be confused with the library use count keeped by the system).
	/// Performs initialization for the YBWLib2.dotNETUnmanaged DLL if the use count is incremented from <c>0</c>.
	/// </summary>
	YBWLIB2DOTNETUNMANAGED_API void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_InitDLL() noexcept;
	/// <summary>
	/// Decrements the YBWLib2.dotNETUnmanaged global use count (not to be confused with the library use count keeped by the system).
	/// Performs uninitialization for the YBWLib2.dotNETUnmanaged DLL if the use count is decremented to <c>0</c>.
	/// </summary>
	YBWLIB2DOTNETUNMANAGED_API void YBWLIB2DOTNETUNMANAGED_CALLTYPE YBWLib2dotNETUnmanaged_UnInitDLL() noexcept;
}

#endif
