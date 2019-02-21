#ifndef _INCLUDE_GUARD_A2BDBA5D_2D6E_480E_9BB6_7DB0B35F05E2
#define _INCLUDE_GUARD_A2BDBA5D_2D6E_480E_9BB6_7DB0B35F05E2

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include <cstdlib>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include "DynamicType.h"

namespace YBWLib2 {
	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>* map_dtclassobj_module_local = nullptr;

	DynamicTypeClassObj* DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid) {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (_dtclassid && *_dtclassid != DynamicTypeClassID_Null) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = map_dtclassobj_module_local->find(*_dtclassid);
					ret = it_dtclassobj == map_dtclassobj_module_local->end() ? nullptr : &it_dtclassobj->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	void DynamicTypeClassObj::RegisterModuleLocal() {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!map_dtclassobj_module_local->emplace(this->dtclassid, *this).second) abort();
			}
		} catch (...) {
			abort();
		}
	}

	void DynamicTypeClassObj::UnRegisterModuleLocal() {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!map_dtclassobj_module_local->erase(this->dtclassid)) abort();
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE DynamicType_RealInitModuleLocal() noexcept {
		map_dtclassobj_module_local = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>();
		if (!map_dtclassobj_module_local) abort();
	}

	void YBWLIB2_CALLTYPE DynamicType_RealUnInitModuleLocal() noexcept {
		if (!map_dtclassobj_module_local->empty()) abort();
		delete map_dtclassobj_module_local;
		map_dtclassobj_module_local = nullptr;
	}
}

#endif
