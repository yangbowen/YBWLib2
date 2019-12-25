#include "pch.h"

#ifdef _MSC_VER
extern "C" const IMAGE_DOS_HEADER __ImageBase;

namespace YBWLib2 {
	const void* addr_module_base = &__ImageBase;
}
#else
#error This platform is not supported yet.
#endif

#include "../YBWLib2/ModuleLocal.h"
