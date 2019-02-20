#ifndef _INCLUDE_GUARD_0B4C1AD9_92C9_43D0_9FFA_2A865B921EC6
#define _INCLUDE_GUARD_0B4C1AD9_92C9_43D0_9FFA_2A865B921EC6

#include "YBWLib2Api.h"

namespace YBWLib2 {
	/// <summary>
	/// The base address of the memory that contains the executable module that contains this reference to this variable.
	/// Although declared here, YBWLib2 doesn't contain a definition for this variable for executable modules other than YBWLib2 itself.
	/// Each executable module that uses functionalities provided by this library must define this variable in its own source code.
	/// </summary>
	extern const void* addr_module_base;

	/// <summary>
	/// Increments the YBWLib2 global use count (not to be confused with the library use count keeped by the system).
	/// Performs initialization for the YBWLib2 DLL if the use count is incremented from <c>0</c>.
	/// Includes both YBWLib2 global initialization and YBWLib2 module-local initialization for the YBWLib2 DLL.
	/// YBWLib2 module-local initialization for the caller is not performed, unless the caller is in the YBWLib2 DLL.
	/// The CRT must be available when this function is being called.
	/// </summary>
	YBWLIB2_API void YBWLIB2_CALLTYPE YBWLib2_InitDLL() noexcept;
	/// <summary>
	/// Decrements the YBWLib2 global use count (not to be confused with the library use count keeped by the system).
	/// Performs uninitialization for the YBWLib2 DLL if the use count is decremented to <c>0</c>.
	/// After the real uninitialization has been performed, do NOT call <c>YBWLib2_InitDLL</c> to initialize again.
	/// Includes both YBWLib2 global uninitialization and YBWLib2 module-local uninitialization for the YBWLib2 DLL.
	/// YBWLib2 module-local uninitialization for the caller is not performed, unless the caller is in the YBWLib2 DLL.
	/// The CRT must be available when this function is being called.
	/// </summary>
	YBWLIB2_API void YBWLIB2_CALLTYPE YBWLib2_UnInitDLL() noexcept;

	/// <summary>
	/// Increments the YBWLib2 module-local use count (not to be confused with the library use count keeped by the system).
	/// Performs YBWLib2 module-local initialization for the caller if the use count is incremented from <c>0</c>.
	/// Includes both YBWLib2 global initialization and YBWLib2 module-local initialization for the YBWLib2 DLL.
	/// This function includes a call to <c>YBWLib2_InitDLL</c>.
	/// The CRT must be available when this function is being called.
	/// <c>addr_module_base</c> must have been initialized to the correct value when this function is being called.
	/// </summary>
	void YBWLIB2_CALLTYPE YBWLib2_InitModuleLocal() noexcept;
	/// <summary>
	/// Decrements the YBWLib2 module-local use count (not to be confused with the library use count keeped by the system).
	/// Performs YBWLib2 module-local uninitialization for the caller if the use count is decremented to <c>0</c>.
	/// After the real uninitialization has been performed, do NOT call <c>YBWLib2_InitModuleLocal</c> to initialize again.
	/// This function includes a call to <c>YBWLib2_UnInitDLL</c>.
	/// The CRT must be available when this function is being called.
	/// <c>addr_module_base</c> must have been initialized to the correct value when this function is being called.
	/// </summary>
	void YBWLIB2_CALLTYPE YBWLib2_UnInitModuleLocal() noexcept;
}

#endif
