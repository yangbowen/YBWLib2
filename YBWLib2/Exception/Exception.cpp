#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "Exception.h"
#include "ExceptionInternal.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IException, YBWLIB2_API, IDynamicTypeObject);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDoubleExceptionException, YBWLIB2_API, IException);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISystemAPIFailureException, YBWLIB2_API, IException);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Exception, YBWLIB2_API, IException);

#pragma warning(push)
#pragma warning(disable:4250)
	/// <summary>An exception that occurs when handling another exception.</summary>
	class DoubleExceptionException abstract
		: public virtual Exception,
		public virtual IDoubleExceptionException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(DoubleExceptionException, , "{12F7B9FB-928E-4197-8DF7-B33DD0FDABDC}");
		virtual ~DoubleExceptionException() = default;
		virtual ExceptionFlags GetExceptionFlags() const noexcept override { return this->Exception::GetExceptionFlags() | ExceptionFlag_DoubleException; }
	};
#pragma warning(pop)

	/// <summary>The global environment for exception handling.</summary>
	class ExceptionHandlingEnvironment final {
	public:
		ExceptionHandlingEnvironment() {
			if (!this->hheap) {
				this->hheap = HeapCreate(0, size_heap_initial, size_heap_max);
				if (!this->hheap) terminate();
			}
		}
		ExceptionHandlingEnvironment(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment(ExceptionHandlingEnvironment&&) = delete;
		~ExceptionHandlingEnvironment() {
			if (this->hheap) HeapDestroy(this->hheap);
		}
		ExceptionHandlingEnvironment& operator=(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment& operator=(ExceptionHandlingEnvironment&&) = delete;
		inline void* AllocateMemory(size_t size) {
			if (!this->hheap) terminate();
			if (!size) size = 1;
			void* ptr = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size);
			if (!ptr) terminate();
			return ptr;
		}
		inline void FreeMemory(void* ptr) {
			if (!this->hheap) terminate();
			if (ptr) if (HeapFree(this->hheap, 0, ptr)) terminate();
		}
	private:
		static constexpr size_t size_heap_initial = 0x400000;
		static constexpr size_t size_heap_max = 0x4000000;
		HANDLE hheap = nullptr;
	} static exception_handling_environment;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(DoubleExceptionException, , Exception, IDoubleExceptionException);

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept { return exception_handling_environment.AllocateMemory(size); }

	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept { exception_handling_environment.FreeMemory(ptr); }
}
