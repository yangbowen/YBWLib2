#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_31329106_84C8_4044_AC33_04EE19FB4C66
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4A4E59E1_D53B_45BF_89A9_4EF26463FAFC
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_A99FAA24_D275_4E60_9376_ECFC0DF1766C
#define _INCLUDE_GUARD_A99FAA24_D275_4E60_9376_ECFC0DF1766C

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <atomic>
#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"

namespace YBWLib2 {
	enum class AwaitableCategory : uint32_t {
		AwaitableCategory_Invalid = 0,
		AwaitableCategory_Lock = 1,
		AwaitableCategory_Notify = 2
	};

	struct AwaitableWaitResult final {};

	class AwaitableImplementation;
	class Awaitable;

	using WaitForAwaitablesDelegate = Delegate<DelegateFlag_Noexcept, AwaitableWaitResult, const Awaitable* const*, size_t, bool, const AwaitableImplementation*>;

	class AwaitableImplementation final {
	public:
		inline constexpr AwaitableImplementation() noexcept = default;
		inline AwaitableImplementation(
			WaitForAwaitablesDelegate&& _delegate_waitforawaitables,
			bool _is_supported_waitforall
		) {
			this->delegate_waitforawaitables = ::std::move(_delegate_waitforawaitables);
			this->is_supported_waitforall = _is_supported_waitforall;
		}
		AwaitableImplementation(const AwaitableImplementation&) = delete;
		AwaitableImplementation(AwaitableImplementation&& x) noexcept {
			this->delegate_waitforawaitables = ::std::move(x.delegate_waitforawaitables);
			this->is_supported_waitforall = ::std::move(x.is_supported_waitforall);
		}
		~AwaitableImplementation() = default;
		AwaitableImplementation& operator=(const AwaitableImplementation&) = delete;
		AwaitableImplementation& operator=(AwaitableImplementation&& x) noexcept {
			this->delegate_waitforawaitables = ::std::move(x.delegate_waitforawaitables);
			this->is_supported_waitforall = ::std::move(x.is_supported_waitforall);
		}
		inline bool IsWaitForAllSupported() const noexcept { return this->is_supported_waitforall; }
		inline AwaitableWaitResult operator()(const Awaitable* const* _arrptr_awaitables, size_t _count_awaitables, bool _is_waitforall) const noexcept {
			if (!_count_awaitables) {
				// TODO: Return.
			}
			if (_is_waitforall) {
				if (_count_awaitables == 1) {
					_is_waitforall = false;
				} else {
					assert(this->IsWaitForAllSupported());
				}
			}
			return this->delegate_waitforawaitables(_arrptr_awaitables, _count_awaitables, _is_waitforall, this);
		}
	private:
		WaitForAwaitablesDelegate delegate_waitforawaitables;
		bool is_supported_waitforall = false;
	};

	class Awaitable {
	public:
		inline const AwaitableImplementation& GetAwaitableImplementation() const noexcept {
			assert(this->awaitableimplementation);
			return *this->awaitableimplementation;
		}
		inline Awaitable(const AwaitableImplementation& _awaitableimplementation, AwaitableCategory _awaitablecategory) noexcept {
			this->awaitableimplementation = &_awaitableimplementation;
			this->awaitablecategory = _awaitablecategory;
		}
		inline virtual ~Awaitable() {
			this->awaitablecategory = AwaitableCategory::AwaitableCategory_Invalid;
			this->awaitableimplementation = nullptr;
		}
	protected:
		inline Awaitable(const Awaitable& x) noexcept {
			this->awaitableimplementation = x.awaitableimplementation;
			this->awaitablecategory = x.awaitablecategory;
		}
		inline Awaitable(Awaitable&& x) noexcept {
			this->awaitableimplementation = x.awaitableimplementation;
			this->awaitablecategory = x.awaitablecategory;
		}
		inline Awaitable& operator=(const Awaitable& x) noexcept {
			this->awaitableimplementation = x.awaitableimplementation;
			this->awaitablecategory = x.awaitablecategory;
		}
		inline Awaitable& operator=(Awaitable&& x) noexcept {
			this->awaitableimplementation = x.awaitableimplementation;
			this->awaitablecategory = x.awaitablecategory;
		}
	private:
		const AwaitableImplementation* awaitableimplementation = nullptr;
		AwaitableCategory awaitablecategory = AwaitableCategory::AwaitableCategory_Invalid;
	};

	extern YBWLIB2_API AwaitableImplementation AwaitableImplementation_STLLockable;

	void YBWLIB2_CALLTYPE Concurrency_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Concurrency_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Concurrency_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE Concurrency_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4A4E59E1_D53B_45BF_89A9_4EF26463FAFC
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4A4E59E1_D53B_45BF_89A9_4EF26463FAFC
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_31329106_84C8_4044_AC33_04EE19FB4C66
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_31329106_84C8_4044_AC33_04EE19FB4C66
#endif
