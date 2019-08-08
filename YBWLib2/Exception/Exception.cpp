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
		inline void* AllocateMemory(size_t size, size_t align) noexcept {
			if (!this || !this->hheap) abort();
			align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
			if (!size) size = align;
			void* ptr_allocated = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size + sizeof(void**) + align - 1);
			if (!ptr_allocated) abort();
			void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
			if (!ptr_allocdata) abort();
			*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
			return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
		}
		inline void FreeMemory(void* ptr) noexcept {
			if (!this || !this->hheap) abort();
			if (ptr) {
				void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr) - 1);
				void* ptr_allocated = *reinterpret_cast<void**>(ptr_allocdata);
				if (!ptr_allocated) abort();
				if (!HeapFree(this->hheap, 0, ptr_allocated)) abort();
			}
		}
		inline void* ReAllocateMemory(void* ptr_old, size_t size_old, size_t size_new, size_t align) noexcept {
			if (!this || !this->hheap) abort();
			align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
			if (!size_new) size_new = align;
			if (ptr_old) {
				void* ptr_allocdata_old = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_old) - 1);
				void* ptr_allocated_old = *reinterpret_cast<void**>(ptr_allocdata_old);
				if (!ptr_allocated_old || ptr_allocated_old > ptr_allocdata_old) abort();
				size_t offset_allocdata_old = reinterpret_cast<uintptr_t>(ptr_allocdata_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
				size_t offset_old = reinterpret_cast<uintptr_t>(ptr_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
				void* ptr_allocated_new = HeapReAlloc(this->hheap, HEAP_ZERO_MEMORY, ptr_allocated_old, size_new + sizeof(void**) + align - 1);
				if (!ptr_allocated_new) abort();
				void* ptr_allocdata_new = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated_new) + (sizeof(void*) - 1)), align) - 1);
				void* ptr_new = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata_new) + 1);
				if (ptr_allocdata_new != reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + offset_allocdata_old)) {
					memmove(ptr_new, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + offset_old), size_new < size_old ? size_new : size_old);
					*reinterpret_cast<void**>(ptr_allocdata_new) = ptr_allocated_new;
					return ptr_new;
				} else {
					*reinterpret_cast<void**>(ptr_allocdata_new) = ptr_allocated_new;
					return ptr_new;
				}
			} else {
				void* ptr_allocated = HeapAlloc(this->hheap, HEAP_ZERO_MEMORY, size_new + sizeof(void**) + align - 1);
				if (!ptr_allocated) abort();
				void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
				if (!ptr_allocdata) abort();
				*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
				return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
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
	YBWLIB2_API IStringTemplate* strtmpl_delimiter_cause_description_exception = nullptr;

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

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionAllocateMemory(size_t size, size_t align) noexcept { return exception_handling_environment->AllocateMemory(size, align); }

	YBWLIB2_API void YBWLIB2_CALLTYPE ExceptionFreeMemory(void* ptr) noexcept { exception_handling_environment->FreeMemory(ptr); }

	YBWLIB2_API void* YBWLIB2_CALLTYPE ExceptionReAllocateMemory(void* ptr_old, size_t size_old, size_t size_new, size_t align) noexcept { return exception_handling_environment->ReAllocateMemory(ptr_old, size_old, size_new, align); }

	void YBWLIB2_CALLTYPE Exception_RealInitGlobal() noexcept {
		exception_handling_environment = new ExceptionHandlingEnvironment();
		if (!exception_handling_environment) abort();
		rawallocator_exception = new rawallocator_t(
			nullptr, nullptr, nullptr,
			[](size_t size, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				return ExceptionAllocateMemory(size, align);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->void {
				static_cast<void>(size);
				static_cast<void>(context);
				ExceptionFreeMemory(ptr);
			},
			[](void* ptr_old, size_t size_old, size_t size_new, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				static_cast<void>(size_old);
				return ExceptionReAllocateMemory(ptr_old, size_old, size_new, align);
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return ExceptionGetMaxMemorySize();
			});
		if (!rawallocator_exception) abort();

		IException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IException>(),
			IsDynamicTypeModuleLocalClass<IException>(),
			{ DynamicTypeBaseClassDef<IException, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IException), alignof(IException));
		IDoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IDoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<IDoubleExceptionException>(),
			{ DynamicTypeBaseClassDef<IDoubleExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IDoubleExceptionException), alignof(IDoubleExceptionException));
		IInvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IInvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<IInvalidParameterException>(),
			{ DynamicTypeBaseClassDef<IInvalidParameterException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInvalidParameterException), alignof(IInvalidParameterException));
		IInvalidCallException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IInvalidCallException>(),
			IsDynamicTypeModuleLocalClass<IInvalidCallException>(),
			{ DynamicTypeBaseClassDef<IInvalidCallException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInvalidCallException), alignof(IInvalidCallException));
		IInsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IInsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<IInsufficientBufferException>(),
			{ DynamicTypeBaseClassDef<IInsufficientBufferException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInsufficientBufferException), alignof(IInsufficientBufferException));
		IMemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IMemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<IMemoryAllocFailureException>(),
			{ DynamicTypeBaseClassDef<IMemoryAllocFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IMemoryAllocFailureException), alignof(IMemoryAllocFailureException));
		IKeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IKeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyAlreadyExistException>(),
			{ DynamicTypeBaseClassDef<IKeyAlreadyExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IKeyAlreadyExistException), alignof(IKeyAlreadyExistException));
		IKeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IKeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<IKeyNotExistException>(),
			{ DynamicTypeBaseClassDef<IKeyNotExistException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IKeyNotExistException), alignof(IKeyNotExistException));
		IUnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IUnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<IUnhandledUnknownExceptionException>(),
			{ DynamicTypeBaseClassDef<IUnhandledUnknownExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IUnhandledUnknownExceptionException), alignof(IUnhandledUnknownExceptionException));
		ISTLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<ISTLExceptionException>(),
			IsDynamicTypeModuleLocalClass<ISTLExceptionException>(),
			{ DynamicTypeBaseClassDef<ISTLExceptionException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISTLExceptionException), alignof(ISTLExceptionException));
		IExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<IExternalAPIFailureException>(),
			{ DynamicTypeBaseClassDef<IExternalAPIFailureException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExternalAPIFailureException), alignof(IExternalAPIFailureException));
		IUnexpectedExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IUnexpectedExceptionException>(),
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
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash<DynamicTypeClassID>> map_strtmpl_description_t;
			map_strtmpl_description_t map_strtmpl_description({
				{ GetDynamicTypeClassID<Exception>(), &Exception::strtmpl_description },
				{ GetDynamicTypeClassID<DoubleExceptionException>(), &DoubleExceptionException::strtmpl_description },
				{ GetDynamicTypeClassID<InvalidParameterException>(), &InvalidParameterException::strtmpl_description },
				{ GetDynamicTypeClassID<InvalidCallException>(), &InvalidCallException::strtmpl_description },
				{ GetDynamicTypeClassID<InsufficientBufferException>(), &InsufficientBufferException::strtmpl_description },
				{ GetDynamicTypeClassID<MemoryAllocFailureException>(), &MemoryAllocFailureException::strtmpl_description },
				{ GetDynamicTypeClassID<KeyAlreadyExistException>(), &KeyAlreadyExistException::strtmpl_description },
				{ GetDynamicTypeClassID<KeyNotExistException>(), &KeyNotExistException::strtmpl_description },
				{ GetDynamicTypeClassID<UnhandledUnknownExceptionException>(), &UnhandledUnknownExceptionException::strtmpl_description },
				{ GetDynamicTypeClassID<STLExceptionException>(), &STLExceptionException::strtmpl_description },
				{ GetDynamicTypeClassID<ExternalAPIFailureException>(), &ExternalAPIFailureException::strtmpl_description },
				{ GetDynamicTypeClassID<UnexpectedExceptionException>(), &UnexpectedExceptionException::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval(u8"Exception"));
			if (jsonmemberit_config_internal_Exception == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_Exception->value.IsObject()) abort();
			{
				{
					Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception = jsonmemberit_config_internal_Exception->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"strtmpl_delimiter_cause_description_exception"));
					if (jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception == jsonmemberit_config_internal_Exception->value.MemberEnd() || !jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception->value.IsObject()) abort();
					Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_dtclassid_strtmpl = jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_strtmpl"));
					Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_jsonval_strtmpl = jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"jsonval_strtmpl"));
					if (
						jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_dtclassid_strtmpl == jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception->value.MemberEnd()
						|| !jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_dtclassid_strtmpl->value.IsString()
						|| jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_jsonval_strtmpl == jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception->value.MemberEnd()
						) abort();
					bool is_successful = true;
					DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassID(PersistentID(UUIDFromUUIDString_RunTime(
						jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_dtclassid_strtmpl->value.GetString(),
						jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_dtclassid_strtmpl->value.GetStringLength(),
						is_successful
					)));
					if (!is_successful) abort();
					DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
					if (!dtclassobj_strtmpl) abort();
					IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
					ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
					RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
					ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_Exception_strtmpl_delimiter_cause_description_exception_jsonval_strtmpl->value);
					JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
					strtmpl_delimiter_cause_description_exception = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeClassObject<IStringTemplate>(), indexeddatastore_parameters));
					if (!strtmpl_delimiter_cause_description_exception) abort();
					objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
						[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
							return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
						}
					);
					if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
				}
				{
					Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description = jsonmemberit_config_internal_Exception->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"strtmpl_description"));
					if (jsonmemberit_config_internal_Exception_strtmpl_description == jsonmemberit_config_internal_Exception->value.MemberEnd() || !jsonmemberit_config_internal_Exception_strtmpl_description->value.IsArray()) abort();
					{
						for (const Internal::jsonval_config_internal_t& jsonval_config_internal_Exception_strtmpl_description_element : jsonmemberit_config_internal_Exception_strtmpl_description->value.GetArray()) {
							if (!jsonval_config_internal_Exception_strtmpl_description_element.IsObject()) abort();
							Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_object = jsonval_config_internal_Exception_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_object"));
							Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_strtmpl = jsonval_config_internal_Exception_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_strtmpl"));
							Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_Exception_strtmpl_description_element_jsonval_strtmpl = jsonval_config_internal_Exception_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"jsonval_strtmpl"));
							if (
								jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_object == jsonval_config_internal_Exception_strtmpl_description_element.MemberEnd()
								|| !jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_object->value.IsString()
								|| jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_strtmpl == jsonval_config_internal_Exception_strtmpl_description_element.MemberEnd()
								|| !jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_strtmpl->value.IsString()
								|| jsonmemberit_config_internal_Exception_strtmpl_description_element_jsonval_strtmpl == jsonval_config_internal_Exception_strtmpl_description_element.MemberEnd()
								) abort();
							bool is_successful = true;
							DynamicTypeClassID dtclassid_object = DynamicTypeClassID(PersistentID(UUIDFromUUIDString_RunTime(
								jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_object->value.GetString(),
								jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_object->value.GetStringLength(),
								is_successful
							)));
							if (!is_successful) abort();
							is_successful = true;
							DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassID(PersistentID(UUIDFromUUIDString_RunTime(
								jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_strtmpl->value.GetString(),
								jsonmemberit_config_internal_Exception_strtmpl_description_element_dtclassid_strtmpl->value.GetStringLength(),
								is_successful
							)));
							if (!is_successful) abort();
							map_strtmpl_description_t::iterator it_map_strtmpl_description = map_strtmpl_description.find(dtclassid_object);
							if (it_map_strtmpl_description == map_strtmpl_description.end()) continue;
							DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
							if (!dtclassobj_strtmpl) abort();
							IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
							ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
							RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
							ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_Exception_strtmpl_description_element_jsonval_strtmpl->value);
							JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
							*it_map_strtmpl_description->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeClassObject<IStringTemplate>(), indexeddatastore_parameters));
							if (!*it_map_strtmpl_description->second) abort();
							objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
								[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
									return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
								}
							);
							if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
							map_strtmpl_description.erase(it_map_strtmpl_description);
						}
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
		delete strtmpl_delimiter_cause_description_exception;
		strtmpl_delimiter_cause_description_exception = nullptr;
	}

	static void YBWLIB2_CALLTYPE DeleteIException_Exception(IException* _ptr) noexcept {
		if (_ptr) delete _ptr;
	}
}
