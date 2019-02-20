#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "CommonLowLevel.h"

namespace YBWLib2 {
	YBWLIB2_API dummy_t dummy;
	YBWLIB2_API rawallocator_t* rawallocator_crt = nullptr;

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept {
		rawallocator_crt = new rawallocator_t(
			[](size_t size, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				if (!size) size = 1;
				return malloc(size);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->bool {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) free(ptr);
				return true;
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return SIZE_MAX;
			});
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept {
		delete rawallocator_crt;
		rawallocator_crt = nullptr;
	}
}
