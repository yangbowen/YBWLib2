﻿#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "Exception.h"

namespace YBWLib2 {
	/// <summary>The global environment for exception handling.</summary>
	class ExceptionHandlingEnvironment final {
	public:
		inline ExceptionHandlingEnvironment() noexcept {
			try {
				if (!this->hheap) {
					this->hheap = HeapCreate(0, this->size_heap_initial, this->size_heap_max);
					if (!this->hheap) abort();
				}
			} catch (...) {
				abort();
			}
		}
		ExceptionHandlingEnvironment(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment(ExceptionHandlingEnvironment&&) = delete;
		~ExceptionHandlingEnvironment() {
			if (this->hheap) {
				if (!HeapDestroy(this->hheap)) abort();
				this->hheap = NULL;
			}
		}
		ExceptionHandlingEnvironment& operator=(const ExceptionHandlingEnvironment&) = delete;
		ExceptionHandlingEnvironment& operator=(ExceptionHandlingEnvironment&&) = delete;
		inline size_t GetMaxMemorySize() const noexcept {
			if (!this) abort();
			return this->size_heap_max;
		}
		inline void* AllocateMemory(size_t size) noexcept {
			if (!this || !this->hheap) abort();
			if (!size) size = 1;
			void* ptr = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size);
			if (!ptr) abort();
			return ptr;
		}
		inline void FreeMemory(void* ptr) noexcept {
			if (!this || !this->hheap) abort();
			if (ptr) if (HeapFree(this->hheap, 0, ptr)) abort();
		}
	private:
		static constexpr size_t size_heap_initial = 0x1000000;
		static constexpr size_t size_heap_max = 0x4000000;
		HANDLE hheap = NULL;
	};

	YBWLIB2_API rawallocator_t* rawallocator_exception = nullptr;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDoubleExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInvalidParameterException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInsufficientBufferException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IMemoryAllocFailureException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IKeyAlreadyExistException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IKeyNotExistException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IUnhandledUnknownExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISTLExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureException, YBWLIB2_API);

	static ExceptionHandlingEnvironment* exception_handling_environment = nullptr;

	YBWLIB2_API size_t YBWLIB2_CALLTYPE ExceptionGetMaxMemorySize() noexcept { return exception_handling_environment->GetMaxMemorySize(); }

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept { return exception_handling_environment->AllocateMemory(size); }

	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept { exception_handling_environment->FreeMemory(ptr); }

	void YBWLIB2_CALLTYPE Exception_RealInitGlobal() noexcept {
		exception_handling_environment = new ExceptionHandlingEnvironment();
		if (!exception_handling_environment) abort();
		rawallocator_exception = new rawallocator_t(
			[](size_t size, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				return ExceptionAllocateMemory(size);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->bool {
				static_cast<void>(size);
				static_cast<void>(context);
				ExceptionFreeMemory(ptr);
				return true;
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return ExceptionGetMaxMemorySize();
			});
		if (!rawallocator_exception) abort();
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IException, IDynamicTypeObject);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IDoubleExceptionException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IInvalidParameterException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IInsufficientBufferException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IMemoryAllocFailureException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IKeyAlreadyExistException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IKeyNotExistException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IUnhandledUnknownExceptionException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(ISTLExceptionException, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(IExternalAPIFailureException, IException);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IExternalAPIFailureException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(ISTLExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IUnhandledUnknownExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IKeyNotExistException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IKeyAlreadyExistException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IMemoryAllocFailureException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IInsufficientBufferException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IInvalidParameterException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IDoubleExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IException);
		delete rawallocator_exception;
		rawallocator_exception = nullptr;
		delete exception_handling_environment;
		exception_handling_environment = nullptr;
	}
}