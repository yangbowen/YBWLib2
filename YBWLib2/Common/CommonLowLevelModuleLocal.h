#ifndef _INCLUDE_GUARD_AF5FE342_E198_4EEE_972C_9077EE5E9919
#define _INCLUDE_GUARD_AF5FE342_E198_4EEE_972C_9077EE5E9919

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <cstdlib>
#include <typeinfo>
#include "CommonLowLevel.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	rawallocator_t* rawallocator_crt_module_local = nullptr;
	module_info_t* module_info_current = nullptr;

	bool YBWLIB2_CALLTYPE wrapper_type_info_t::IsEqualTo_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept {
		if (!l || !r || l->module_info != module_info_current || r->module_info != module_info_current) return wrapper_type_info_t::IsEqualTo(l, r);
		const ::std::type_info* val_type_info_l = reinterpret_cast<const ::std::type_info*>(l->context);
		const ::std::type_info* val_type_info_r = reinterpret_cast<const ::std::type_info*>(r->context);
		if (!val_type_info_l || !val_type_info_r) return !val_type_info_l && !val_type_info_r;
		return *val_type_info_l == *val_type_info_r;
	}

	bool YBWLIB2_CALLTYPE wrapper_type_info_t::IsLessThan_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept {
		if (!l || !r || l->module_info != module_info_current || r->module_info != module_info_current) return wrapper_type_info_t::IsLessThan(l, r);
		const ::std::type_info* val_type_info_l = reinterpret_cast<const ::std::type_info*>(l->context);
		const ::std::type_info* val_type_info_r = reinterpret_cast<const ::std::type_info*>(r->context);
		if (!val_type_info_l || !val_type_info_r) return val_type_info_r;
		return val_type_info_l->before(*val_type_info_r);
	}

	size_t YBWLIB2_CALLTYPE wrapper_type_info_t::GetHashCode_TypeInfo(const wrapper_type_info_t* x) noexcept {
		if (!x || x->module_info != module_info_current) return x->GetHashCode();
		const ::std::type_info* val_type_info_x = reinterpret_cast<const ::std::type_info*>(x->context);
		return val_type_info_x->hash_code();
	}

	const char* YBWLIB2_CALLTYPE wrapper_type_info_t::GetName_TypeInfo(const wrapper_type_info_t* x) noexcept {
		if (!x || x->module_info != module_info_current) return x->GetName();
		const ::std::type_info* val_type_info_x = reinterpret_cast<const ::std::type_info*>(x->context);
		return val_type_info_x->name();
	}

	RawAllocatorParameterIndexedDataEntry RawAllocatorParameterIndexedDataEntry::CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false) {
		const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			return RawAllocatorParameterIndexedDataEntry(*_indexeddatarawvalue);
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	RawAllocatorParameterIndexedDataEntry RawAllocatorParameterIndexedDataEntry::MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false) {
		IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			RawAllocatorParameterIndexedDataEntry ret(RawAllocatorParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue)));
			_indexeddatastore.RemoveEntryByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
			return ret;
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitModuleLocal() noexcept {
		rawallocator_crt_module_local = new rawallocator_t(
			nullptr, nullptr, nullptr,
			[](size_t size, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
				if (!size) size = align;
				void* ptr_allocated = malloc(size + align - 1);
				if (!ptr_allocated) abort();
				void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
				if (!ptr_allocdata) abort();
				*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
				return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->void {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) {
					void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr) - 1);
					void* ptr_allocated = *reinterpret_cast<void**>(ptr_allocdata);
					if (!ptr_allocated) abort();
					free(ptr_allocated);
				}
			},
			[](void* ptr_old, size_t size_old, size_t size_new, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(size_old);
				static_cast<void>(context);
				align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
				if (!size_new) size_new = align;
				if (ptr_old) {
					void* ptr_allocdata_old = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_old) - 1);
					void* ptr_allocated_old = *reinterpret_cast<void**>(ptr_allocdata_old);
					if (!ptr_allocated_old || ptr_allocated_old > ptr_allocdata_old) abort();
					size_t offset_allocdata_old = reinterpret_cast<uintptr_t>(ptr_allocdata_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
					size_t offset_old = reinterpret_cast<uintptr_t>(ptr_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
					void* ptr_allocated_new = realloc(ptr_allocated_old, size_new + align - 1);
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
					void* ptr_allocated = malloc(size_new + align - 1);
					if (!ptr_allocated) abort();
					void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
					if (!ptr_allocdata) abort();
					*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
					return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
				}
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return SIZE_MAX;
			});
		module_info_current = new module_info_t(addr_module_base);
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitModuleLocal() noexcept {
		delete module_info_current;
		module_info_current = nullptr;
		delete rawallocator_crt_module_local;
		rawallocator_crt_module_local = nullptr;
	}
}

#endif
