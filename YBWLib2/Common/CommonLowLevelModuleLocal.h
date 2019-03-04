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
			[](size_t size, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				if (!size) size = 1;
				return malloc(size);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->bool {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) free(ptr);
				return true;
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
