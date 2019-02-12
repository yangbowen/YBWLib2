#pragma once
#include "../YBWLib2Api.h"
#include "DynamicType.h"

namespace YBWLib2 {
	YBWLIB2_API void YBWLIB2_CALLTYPE dtenv_init_global();
	YBWLIB2_API void YBWLIB2_CALLTYPE mtx_dtenv_lock();
	YBWLIB2_API void YBWLIB2_CALLTYPE mtx_dtenv_unlock();

	struct wrapper_mtx_dtenv_t {
		inline void lock() { return mtx_dtenv_lock(); }
		inline void unlock() { return mtx_dtenv_unlock(); }
	};
	extern YBWLIB2_API wrapper_mtx_dtenv_t wrapper_mtx_dtenv;
}
