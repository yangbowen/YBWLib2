#include "pch.h"
#include "Windows.h"

#ifdef _MSC_VER
extern "C" const IMAGE_DOS_HEADER __ImageBase;

namespace YBWLib2 {
	const void* addr_module_base = &__ImageBase;
}
#else
#error This platform is not supported yet.
#endif

#include "ModuleLocal.h"
