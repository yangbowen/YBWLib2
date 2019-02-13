#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

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
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			this->dtclassobj = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid);
			if (!this->dtclassobj) abort();
			if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
		}
	}

	DynamicTypeClassObj* DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid) {
		if (!_dtclassid || *_dtclassid == DynamicTypeClassID_Null) return nullptr;
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = ModuleLocal::map_dtclassobj->find(*_dtclassid);
			return it_dtclassobj == ModuleLocal::map_dtclassobj->end() ? nullptr : &it_dtclassobj->second;
		}
	}

	void DynamicTypeClassObj::RegisterModuleLocal() {
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!ModuleLocal::map_dtclassobj->emplace(this->dtclassid, *this).second) abort();
		}
	}

	void DynamicTypeClassObj::UnRegisterModuleLocal() {
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!ModuleLocal::map_dtclassobj->erase(this->dtclassid)) abort();
		}
	}
}
