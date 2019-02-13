#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "Exception.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IException, YBWLIB2_API, IDynamicTypeObject);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDoubleExceptionException, YBWLIB2_API, IException);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureException, YBWLIB2_API, IException);

	/// <summary>The global environment for exception handling.</summary>
	class ExceptionHandlingEnvironment final {
	public:
		constexpr ExceptionHandlingEnvironment() noexcept {}
		ExceptionHandlingEnvironment(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment(ExceptionHandlingEnvironment&&) = delete;
		~ExceptionHandlingEnvironment() {
			if (this->hheap) if (!HeapDestroy(this->hheap)) abort();
		}
		ExceptionHandlingEnvironment& operator=(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment& operator=(ExceptionHandlingEnvironment&&) = delete;
		inline void Initialize() const noexcept {
			try {
				::std::call_once(this->onceflag, [this]() { const_cast<ExceptionHandlingEnvironment*>(this)->RealInitialize(); });
			} catch (...) {
				abort();
			}
		}
		inline void RealInitialize() noexcept {
			try {
				if (!this->hheap) {
					this->hheap = HeapCreate(0, size_heap_initial, size_heap_max);
					if (!this->hheap) abort();
				}
			} catch (...) {
				abort();
			}
		}
		inline size_t GetMaxMemorySize() const noexcept {
			return size_heap_max;
		}
		inline void* AllocateMemory(size_t size) noexcept {
			this->Initialize();
			if (!this->hheap) abort();
			if (!size) size = 1;
			void* ptr = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size);
			if (!ptr) abort();
			return ptr;
		}
		inline void FreeMemory(void* ptr) noexcept {
			this->Initialize();
			if (!this->hheap) abort();
			if (ptr) if (HeapFree(this->hheap, 0, ptr)) abort();
		}
	private:
		static constexpr size_t size_heap_initial = 0x400000;
		static constexpr size_t size_heap_max = 0x4000000;
		mutable ::std::once_flag onceflag;
		HANDLE hheap = nullptr;
	} static exception_handling_environment;

	struct exception_handling_environment_init_t {
		exception_handling_environment_init_t() {
			exception_handling_environment.Initialize();
		}
	} static exception_handling_environment_init;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(DoubleExceptionException, , Exception, IDoubleExceptionException);

	YBWLIB2_API size_t YBWLIB2_CALLTYPE ExceptionGetMaxMemorySize() noexcept { return exception_handling_environment.GetMaxMemorySize(); }

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept { return exception_handling_environment.AllocateMemory(size); }

	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept { exception_handling_environment.FreeMemory(ptr); }
}
