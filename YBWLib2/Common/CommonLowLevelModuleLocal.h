// Include guard omitted intentionally.

#include <typeinfo>
#include "CommonLowLevel.h"

namespace YBWLib2 {
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
		module_info_current = new module_info_t();
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitModuleLocal() noexcept {
		delete module_info_current;
		module_info_current = nullptr;
	}
}
