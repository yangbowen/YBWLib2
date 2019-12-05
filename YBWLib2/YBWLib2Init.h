#ifndef _INCLUDE_GUARD_0B4C1AD9_92C9_43D0_9FFA_2A865B921EC6
#define _INCLUDE_GUARD_0B4C1AD9_92C9_43D0_9FFA_2A865B921EC6

#include "YBWLib2Api.h"
#include <new>
#include <atomic>
#include <mutex>

namespace YBWLib2 {
	class SharedResourceInitializer final {
	public:
		using fnptr_RealInitialize_t = void (YBWLIB2_CALLTYPE*)() noexcept;
		using fnptr_RealUnInitialize_t = void (YBWLIB2_CALLTYPE*)() noexcept;
		SharedResourceInitializer(fnptr_RealInitialize_t _fnptr_RealInitialize, fnptr_RealUnInitialize_t _fnptr_RealUnInitialize) noexcept : usecount(0), fnptr_RealInitialize(_fnptr_RealInitialize), fnptr_RealUnInitialize(_fnptr_RealUnInitialize) {}
		SharedResourceInitializer(const SharedResourceInitializer&) = delete;
		SharedResourceInitializer(SharedResourceInitializer&&) = delete;
		~SharedResourceInitializer() = default;
		SharedResourceInitializer& operator=(const SharedResourceInitializer&) = delete;
		SharedResourceInitializer& operator=(SharedResourceInitializer&&) = delete;
		void YBWLIB2_CALLTYPE Initialize() noexcept {
			try {
				uintptr_t value_usecount = this->usecount.load(::std::memory_order_relaxed);
				while (true) {
					if (value_usecount) {
						if (this->usecount.compare_exchange_weak(value_usecount, value_usecount + 1, ::std::memory_order_acquire, ::std::memory_order_relaxed)) break;
					} else {
						::std::unique_lock<::std::mutex> unique_lock(this->mtx);
						if (this->usecount.compare_exchange_weak(value_usecount, 1, ::std::memory_order_acq_rel, ::std::memory_order_relaxed)) {
							(*this->fnptr_RealInitialize)();
							break;
						}
					}
				}
			} catch (...) {
				abort();
			}
		}
		void YBWLIB2_CALLTYPE UnInitialize() noexcept {
			try {
				uintptr_t value_usecount = this->usecount.load(::std::memory_order_relaxed);
				while (true) {
					if (!value_usecount) abort();
					if (value_usecount > 1) {
						if (this->usecount.compare_exchange_weak(value_usecount, value_usecount - 1, ::std::memory_order_release, ::std::memory_order_relaxed)) break;
					} else {
						::std::unique_lock<::std::mutex> unique_lock(this->mtx);
						if (this->usecount.compare_exchange_weak(value_usecount, 0, ::std::memory_order_acq_rel, ::std::memory_order_relaxed)) {
							(*this->fnptr_RealUnInitialize)();
							break;
						}
					}
				}
			} catch (...) {
				abort();
			}
		}
	private:
		::std::atomic<uintptr_t> usecount;
		::std::mutex mtx;
		fnptr_RealInitialize_t fnptr_RealInitialize = nullptr;
		fnptr_RealUnInitialize_t fnptr_RealUnInitialize = nullptr;
	};

	class SharedResourceInitializer_StaticInit final {
	public:
		using fnptr_RealInitialize_t = void (YBWLIB2_CALLTYPE*)() noexcept;
		using fnptr_RealUnInitialize_t = void (YBWLIB2_CALLTYPE*)() noexcept;
		constexpr SharedResourceInitializer_StaticInit() noexcept = default;
		SharedResourceInitializer_StaticInit(const SharedResourceInitializer_StaticInit&) = delete;
		SharedResourceInitializer_StaticInit(SharedResourceInitializer_StaticInit&&) = delete;
		~SharedResourceInitializer_StaticInit() = default;
		SharedResourceInitializer_StaticInit& operator=(const SharedResourceInitializer_StaticInit&) = delete;
		SharedResourceInitializer_StaticInit& operator=(SharedResourceInitializer_StaticInit&&) = delete;
		void YBWLIB2_CALLTYPE Initialize(fnptr_RealInitialize_t _fnptr_RealInitialize, fnptr_RealUnInitialize_t _fnptr_RealUnInitialize) noexcept {
			::std::call_once(
				this->onceflag_sharedresourceinitializer,
				[this, _fnptr_RealInitialize, _fnptr_RealUnInitialize]() noexcept->void {
					new(&this->buf_sharedresourceinitializer) SharedResourceInitializer(_fnptr_RealInitialize, _fnptr_RealUnInitialize);
				}
			);
			SharedResourceInitializer* sharedresourceinitializer = ::std::launder(reinterpret_cast<SharedResourceInitializer*>(&this->buf_sharedresourceinitializer));
			sharedresourceinitializer->Initialize();
		}
		void YBWLIB2_CALLTYPE UnInitialize(fnptr_RealInitialize_t _fnptr_RealInitialize, fnptr_RealUnInitialize_t _fnptr_RealUnInitialize) noexcept {
			::std::call_once(
				this->onceflag_sharedresourceinitializer,
				[this, _fnptr_RealInitialize, _fnptr_RealUnInitialize]() noexcept->void {
					new(&this->buf_sharedresourceinitializer) SharedResourceInitializer(_fnptr_RealInitialize, _fnptr_RealUnInitialize);
				}
			);
			SharedResourceInitializer* sharedresourceinitializer = ::std::launder(reinterpret_cast<SharedResourceInitializer*>(&this->buf_sharedresourceinitializer));
			sharedresourceinitializer->UnInitialize();
		}
	private:
		::std::once_flag onceflag_sharedresourceinitializer;
		alignas(alignof(SharedResourceInitializer)) unsigned char buf_sharedresourceinitializer[sizeof(SharedResourceInitializer)] = {};
	};

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
	/// This function includes a call to <c>YBWLib2_UnInitDLL</c>.
	/// The CRT must be available when this function is being called.
	/// <c>addr_module_base</c> must have been initialized to the correct value when this function is being called.
	/// </summary>
	void YBWLIB2_CALLTYPE YBWLib2_UnInitModuleLocal() noexcept;
}

#endif
