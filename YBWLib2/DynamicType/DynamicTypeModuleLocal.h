#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

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
				::std::call_once(onceflag_dtenv,
					[]() {
						try {
							map_dtclassobj = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>();
							if (!map_dtclassobj) terminate();
						} catch (...) {
							terminate();
						}
					}
				);
			} catch (...) {
				terminate();
			}
		}
	}

	void DynamicTypeBaseClassDefObj::RealInitializeModuleLocal() const {
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = ModuleLocal::map_dtclassobj->find(this->dtclassid);
			if (it_dtclassobj == ModuleLocal::map_dtclassobj->end()) terminate();
			if (it_dtclassobj->second.IsModuleLocal() != this->is_module_local) terminate();
			this->dtclassobj = &it_dtclassobj->second;
		}
	}

	void DynamicTypeClassObj::RegisterModuleLocal() {
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!ModuleLocal::map_dtclassobj->emplace(this->dtclassid, *this).second) terminate();
		}
	}

	void DynamicTypeClassObj::UnRegisterModuleLocal() {
		ModuleLocal::dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!ModuleLocal::map_dtclassobj->erase(this->dtclassid)) terminate();
		}
	}
}
