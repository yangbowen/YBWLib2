#ifndef _INCLUDE_GUARD_F68609C9_0483_40A1_9648_995B4B7953C3
#define _INCLUDE_GUARD_F68609C9_0483_40A1_9648_995B4B7953C3

#include <mutex>
#include "Concurrency/Concurrency.h"

namespace YBWLib2 {
	class Awaitable_STLLockable final : public Awaitable {
	public:
	private:
	};

	YBWLIB2_API AwaitableImplementation AwaitableImplementation_STLLockable;

	static AwaitableWaitResult YBWLIB2_CALLTYPE WaitForAwaitables_STLLockable(const Awaitable* const* _arrptr_awaitables, size_t _count_awaitables, bool _is_waitforall, const AwaitableImplementation* _awaitableimplementation) noexcept;

	static AwaitableWaitResult YBWLIB2_CALLTYPE WaitForAwaitables_STLLockable(const Awaitable* const* _arrptr_awaitables, size_t _count_awaitables, bool _is_waitforall, const AwaitableImplementation* _awaitableimplementation) noexcept {
		assert(_awaitableimplementation == &AwaitableImplementation_STLLockable);
		// TODO
	}

	void YBWLIB2_CALLTYPE Concurrency_RealInitModuleLocal() noexcept {
		AwaitableImplementation_STLLockable = AwaitableImplementation(
			WaitForAwaitablesDelegate(&WaitForAwaitables_STLLockable),
			true
			);
	}

	void YBWLIB2_CALLTYPE Concurrency_RealUnInitModuleLocal() noexcept {
		AwaitableImplementation_STLLockable = AwaitableImplementation();
	}
}

#endif
