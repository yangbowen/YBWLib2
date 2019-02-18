// Include guard omitted intentionally.

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include <cstdlib>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include "DynamicType.h"
#include "DynamicTypeInternal.h"

namespace YBWLib2 {
	namespace ModuleLocal {
		static ::std::once_flag onceflag_dtenv;
		static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>* map_dtclassobj = nullptr;
		static void dtenv_init() noexcept {
			try {
				dtenv_init_global();
				::std::call_once(onceflag_dtenv,
					[]() {
						map_dtclassobj = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>();
						if (!map_dtclassobj) abort();
					}
				);
			} catch (...) {
				abort();
			}
		}
	}

	void DynamicTypeBaseClassDefObj::RealInitializeModuleLocal() const {
		try {
			ModuleLocal::dtenv_init();
			{
				::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
				this->dtclassobj = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			}
		} catch (...) {
			abort();
		}
	}

	DynamicTypeClassObj* DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid) {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (_dtclassid && *_dtclassid != DynamicTypeClassID_Null) {
				ModuleLocal::dtenv_init();
				{
					::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = ModuleLocal::map_dtclassobj->find(*_dtclassid);
					ret = it_dtclassobj == ModuleLocal::map_dtclassobj->end() ? nullptr : &it_dtclassobj->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	void DynamicTypeClassObj::RegisterModuleLocal() {
		try {
			ModuleLocal::dtenv_init();
			{
				::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
				if (!ModuleLocal::map_dtclassobj->emplace(this->dtclassid, *this).second) abort();
			}
		} catch (...) {
			abort();
		}
	}

	void DynamicTypeClassObj::UnRegisterModuleLocal() {
		try {
			ModuleLocal::dtenv_init();
			{
				::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
				if (!ModuleLocal::map_dtclassobj->erase(this->dtclassid)) abort();
			}
		} catch (...) {
			abort();
		}
	}
}
