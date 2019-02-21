#pragma include_alias("pch.h", "../pch.h")
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
		IException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IException>(),
			IsDynamicTypeModuleLocalClass<IException>(),
			{ DynamicTypeBaseClassDef<IException, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> });
		IDoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IDoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<IDoubleExceptionException>(),
			{ DynamicTypeBaseClassDef<IDoubleExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IInvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<IInvalidParameterException>(),
			{ DynamicTypeBaseClassDef<IInvalidParameterException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IInsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<IInsufficientBufferException>(),
			{ DynamicTypeBaseClassDef<IInsufficientBufferException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IMemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IMemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<IMemoryAllocFailureException>(),
			{ DynamicTypeBaseClassDef<IMemoryAllocFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IKeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IKeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyAlreadyExistException>(),
			{ DynamicTypeBaseClassDef<IKeyAlreadyExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IKeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IKeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyNotExistException>(),
			{ DynamicTypeBaseClassDef<IKeyNotExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IUnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IUnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<IUnhandledUnknownExceptionException>(),
			{ DynamicTypeBaseClassDef<IUnhandledUnknownExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		ISTLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ISTLExceptionException>(),
			IsDynamicTypeModuleLocalClass<ISTLExceptionException>(),
			{ DynamicTypeBaseClassDef<ISTLExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		IExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> });
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitGlobal() noexcept {
		delete IExternalAPIFailureException::DynamicTypeThisClassObject;
		IExternalAPIFailureException::DynamicTypeThisClassObject = nullptr;
		delete ISTLExceptionException::DynamicTypeThisClassObject;
		ISTLExceptionException::DynamicTypeThisClassObject = nullptr;
		delete IUnhandledUnknownExceptionException::DynamicTypeThisClassObject;
		IUnhandledUnknownExceptionException::DynamicTypeThisClassObject = nullptr;
		delete IKeyNotExistException::DynamicTypeThisClassObject;
		IKeyNotExistException::DynamicTypeThisClassObject = nullptr;
		delete IKeyAlreadyExistException::DynamicTypeThisClassObject;
		IKeyAlreadyExistException::DynamicTypeThisClassObject = nullptr;
		delete IMemoryAllocFailureException::DynamicTypeThisClassObject;
		IMemoryAllocFailureException::DynamicTypeThisClassObject = nullptr;
		delete IInsufficientBufferException::DynamicTypeThisClassObject;
		IInsufficientBufferException::DynamicTypeThisClassObject = nullptr;
		delete IInvalidParameterException::DynamicTypeThisClassObject;
		IInvalidParameterException::DynamicTypeThisClassObject = nullptr;
		delete IDoubleExceptionException::DynamicTypeThisClassObject;
		IDoubleExceptionException::DynamicTypeThisClassObject = nullptr;
		delete IException::DynamicTypeThisClassObject;
		IException::DynamicTypeThisClassObject = nullptr;
		delete rawallocator_exception;
		rawallocator_exception = nullptr;
		delete exception_handling_environment;
		exception_handling_environment = nullptr;
	}
}
