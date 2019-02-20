// Include guard omitted intentionally.

#include <cstdlib>
#include <typeinfo>
#include "CommonLowLevel.h"

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
