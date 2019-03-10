#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "Exception.h"

#include "../JSON/JSON.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"

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
		inline void* ReAllocateMemory(void* ptr_old, size_t size_new) noexcept {
			if (!this || !this->hheap) abort();
			if (!size_new) size_new = 1;
			if (ptr_old) {
				void* ptr_new = HeapReAlloc(this->hheap, HEAP_ZERO_MEMORY, ptr_old, size_new);
				if (!ptr_new) abort();
				return ptr_new;
			} else {
				void* ptr_new = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size_new);
				if (!ptr_new) abort();
				return ptr_new;
			}
		}
	private:
		static constexpr size_t size_heap_initial = 0x1000000;
		static constexpr size_t size_heap_max = 0x4000000;
		HANDLE hheap = NULL;
	};

	static void YBWLIB2_CALLTYPE DeleteIException_Exception(IException* _ptr) noexcept;

	static fnptr_delete_iexception_t fnptr_delete_iexception_old_Exception = nullptr;

	YBWLIB2_API rawallocator_t* rawallocator_exception = nullptr;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDoubleExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInvalidParameterException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInvalidCallException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInsufficientBufferException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IMemoryAllocFailureException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IKeyAlreadyExistException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IKeyNotExistException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IUnhandledUnknownExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISTLExceptionException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExternalAPIFailureException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IUnexpectedExceptionException, YBWLIB2_API);

	YBWLIB2_API IStringTemplate* Exception::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* DoubleExceptionException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* InvalidParameterException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* InvalidCallException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* InsufficientBufferException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* MemoryAllocFailureException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* KeyAlreadyExistException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* KeyNotExistException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* UnhandledUnknownExceptionException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* STLExceptionException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* ExternalAPIFailureException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* UnexpectedExceptionException::strtmpl_description = nullptr;

	static ExceptionHandlingEnvironment* exception_handling_environment = nullptr;

	YBWLIB2_API size_t YBWLIB2_CALLTYPE ExceptionGetMaxMemorySize() noexcept { return exception_handling_environment->GetMaxMemorySize(); }

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size) noexcept { return exception_handling_environment->AllocateMemory(size); }

	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept { exception_handling_environment->FreeMemory(ptr); }

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionReAllocateMemory(void* ptr_old, size_t size_new) noexcept { return exception_handling_environment->ReAllocateMemory(ptr_old, size_new); }

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
			[](void* ptr_old, size_t size_old, size_t size_new, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				static_cast<void>(size_old);
				return ExceptionReAllocateMemory(ptr_old, size_new);
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return ExceptionGetMaxMemorySize();
			});
		if (!rawallocator_exception) abort();

		IException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IException>(),
			IsDynamicTypeModuleLocalClass<IException>(),
			{ DynamicTypeBaseClassDef<IException, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IException), alignof(IException));
		IDoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IDoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<IDoubleExceptionException>(),
			{ DynamicTypeBaseClassDef<IDoubleExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IDoubleExceptionException), alignof(IDoubleExceptionException));
		IInvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<IInvalidParameterException>(),
			{ DynamicTypeBaseClassDef<IInvalidParameterException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInvalidParameterException), alignof(IInvalidParameterException));
		IInvalidCallException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInvalidCallException>(),
			IsDynamicTypeModuleLocalClass<IInvalidCallException>(),
			{ DynamicTypeBaseClassDef<IInvalidCallException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInvalidCallException), alignof(IInvalidCallException));
		IInsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<IInsufficientBufferException>(),
			{ DynamicTypeBaseClassDef<IInsufficientBufferException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInsufficientBufferException), alignof(IInsufficientBufferException));
		IMemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IMemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<IMemoryAllocFailureException>(),
			{ DynamicTypeBaseClassDef<IMemoryAllocFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IMemoryAllocFailureException), alignof(IMemoryAllocFailureException));
		IKeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IKeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyAlreadyExistException>(),
			{ DynamicTypeBaseClassDef<IKeyAlreadyExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IKeyAlreadyExistException), alignof(IKeyAlreadyExistException));
		IKeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IKeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyNotExistException>(),
			{ DynamicTypeBaseClassDef<IKeyNotExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IKeyNotExistException), alignof(IKeyNotExistException));
		IUnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IUnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<IUnhandledUnknownExceptionException>(),
			{ DynamicTypeBaseClassDef<IUnhandledUnknownExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IUnhandledUnknownExceptionException), alignof(IUnhandledUnknownExceptionException));
		ISTLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ISTLExceptionException>(),
			IsDynamicTypeModuleLocalClass<ISTLExceptionException>(),
			{ DynamicTypeBaseClassDef<ISTLExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISTLExceptionException), alignof(ISTLExceptionException));
		IExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureException), alignof(IExternalAPIFailureException));
		IUnexpectedExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IUnexpectedExceptionException>(),
			IsDynamicTypeModuleLocalClass<IUnexpectedExceptionException>(),
			{ DynamicTypeBaseClassDef<IUnexpectedExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IUnexpectedExceptionException), alignof(IUnexpectedExceptionException));
		fnptr_delete_iexception_old_Exception = ExchangeDeleteIExceptionFnptr(ptr_atomic_fnptr_delete_iexception_global, &DeleteIException_Exception);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitGlobal() noexcept {
		ExchangeDeleteIExceptionFnptr(ptr_atomic_fnptr_delete_iexception_global, fnptr_delete_iexception_old_Exception);
		fnptr_delete_iexception_old_Exception = nullptr;
		delete IUnexpectedExceptionException::DynamicTypeThisClassObject;
		IUnexpectedExceptionException::DynamicTypeThisClassObject = nullptr;
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
		delete IInvalidCallException::DynamicTypeThisClassObject;
		IInvalidCallException::DynamicTypeThisClassObject = nullptr;
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

	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_exception_t;
			map_strtmpl_description_exception_t map_strtmpl_description_exception({
				{ GetDynamicTypeThisClassID<Exception>(), &Exception::strtmpl_description },
				{ GetDynamicTypeThisClassID<DoubleExceptionException>(), &DoubleExceptionException::strtmpl_description },
				{ GetDynamicTypeThisClassID<InvalidParameterException>(), &InvalidParameterException::strtmpl_description },
				{ GetDynamicTypeThisClassID<InvalidCallException>(), &InvalidCallException::strtmpl_description },
				{ GetDynamicTypeThisClassID<InsufficientBufferException>(), &InsufficientBufferException::strtmpl_description },
				{ GetDynamicTypeThisClassID<MemoryAllocFailureException>(), &MemoryAllocFailureException::strtmpl_description },
				{ GetDynamicTypeThisClassID<KeyAlreadyExistException>(), &KeyAlreadyExistException::strtmpl_description },
				{ GetDynamicTypeThisClassID<KeyNotExistException>(), &KeyNotExistException::strtmpl_description },
				{ GetDynamicTypeThisClassID<UnhandledUnknownExceptionException>(), &UnhandledUnknownExceptionException::strtmpl_description },
				{ GetDynamicTypeThisClassID<STLExceptionException>(), &STLExceptionException::strtmpl_description },
				{ GetDynamicTypeThisClassID<ExternalAPIFailureException>(), &ExternalAPIFailureException::strtmpl_description },
				{ GetDynamicTypeThisClassID<UnexpectedExceptionException>(), &UnexpectedExceptionException::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval("Exception"));
			if (jsonmemberit_config_internal_Exception == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_Exception->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_exception = jsonmemberit_config_internal_Exception->value.FindMember(Internal::ConstStringToInternalConfigJsonval("strtmpl_description_exception"));
				if (jsonmemberit_config_internal_Exception_strtmpl_description_exception == jsonmemberit_config_internal_Exception->value.MemberEnd() || !jsonmemberit_config_internal_Exception_strtmpl_description_exception->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_Exception_strtmpl_description_exception_element : jsonmemberit_config_internal_Exception_strtmpl_description_exception->value.GetArray()) {
						if (!jsonval_config_internal_Exception_strtmpl_description_exception_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_exception = jsonval_config_internal_Exception_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_exception"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_strtmpl = jsonval_config_internal_Exception_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_jsonval_strtmpl = jsonval_config_internal_Exception_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_exception == jsonval_config_internal_Exception_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_exception->value.IsString()
							|| jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_strtmpl == jsonval_config_internal_Exception_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_jsonval_strtmpl == jsonval_config_internal_Exception_strtmpl_description_exception_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_exception = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_exception->value.GetString(),
							jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_exception->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_exception_t::iterator it_map_strtmpl_description_exception = map_strtmpl_description_exception.find(dtclassid_exception);
						if (it_map_strtmpl_description_exception == map_strtmpl_description_exception.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_Exception_strtmpl_description_exception_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description_exception->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeThisClassObject<IStringTemplate>(), indexeddatastore_parameters));
						if (!*it_map_strtmpl_description_exception->second) abort();
						objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
							[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
								return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
							}
						);
						if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
						map_strtmpl_description_exception.erase(it_map_strtmpl_description_exception);
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealUnInitGlobal() noexcept {
		delete UnexpectedExceptionException::strtmpl_description;
		UnexpectedExceptionException::strtmpl_description = nullptr;
		delete ExternalAPIFailureException::strtmpl_description;
		ExternalAPIFailureException::strtmpl_description = nullptr;
		delete STLExceptionException::strtmpl_description;
		STLExceptionException::strtmpl_description = nullptr;
		delete UnhandledUnknownExceptionException::strtmpl_description;
		UnhandledUnknownExceptionException::strtmpl_description = nullptr;
		delete KeyNotExistException::strtmpl_description;
		KeyNotExistException::strtmpl_description = nullptr;
		delete KeyAlreadyExistException::strtmpl_description;
		KeyAlreadyExistException::strtmpl_description = nullptr;
		delete MemoryAllocFailureException::strtmpl_description;
		MemoryAllocFailureException::strtmpl_description = nullptr;
		delete InsufficientBufferException::strtmpl_description;
		InsufficientBufferException::strtmpl_description = nullptr;
		delete InvalidCallException::strtmpl_description;
		InvalidCallException::strtmpl_description = nullptr;
		delete InvalidParameterException::strtmpl_description;
		InvalidParameterException::strtmpl_description = nullptr;
		delete DoubleExceptionException::strtmpl_description;
		DoubleExceptionException::strtmpl_description = nullptr;
		delete Exception::strtmpl_description;
		Exception::strtmpl_description = nullptr;
	}

	static void YBWLIB2_CALLTYPE DeleteIException_Exception(IException* _ptr) noexcept {
		if (_ptr) delete _ptr;
	}
}
