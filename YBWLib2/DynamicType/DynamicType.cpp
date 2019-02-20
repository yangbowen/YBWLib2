#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <utility>
#include <tuple>
#include "../Common/CommonLowLevel.h"
#include "DynamicType.h"
#include "DynamicTypeInternal.h"

namespace YBWLib2 {
	YBWLIB2_API wrapper_lockable_t* wrapper_lockable_dtenv = nullptr;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDynamicTypeObject, YBWLIB2_API);

	static ::std::recursive_mutex* mtx_dtenv = nullptr;
	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>* map_dtclassobj_global = nullptr;

	class DynamicTypeTotalBaseClass {
	public:
		const DynamicTypeClassID dtclassid_thisclass;
		const DynamicTypeClassID dtclassid_baseclass;
		const size_t offset_upcast_abs;
		const bool is_upcast_negative_offset;
		DynamicTypeClassObj& dtclassobj_baseclass;
		inline DynamicTypeTotalBaseClass(
			const DynamicTypeClassID& _dtclassid_thisclass,
			const DynamicTypeClassID& _dtclassid_baseclass,
			size_t _offset_upcast_abs,
			bool _is_upcast_negative_offset,
			DynamicTypeClassObj& _dtclassobj_baseclass)
			: dtclassid_thisclass(_dtclassid_thisclass),
			dtclassid_baseclass(_dtclassid_baseclass),
			offset_upcast_abs(_offset_upcast_abs),
			is_upcast_negative_offset(_is_upcast_negative_offset),
			dtclassobj_baseclass(_dtclassobj_baseclass) {}
		inline bool operator==(const DynamicTypeTotalBaseClass& r) {
			return
				this->dtclassid_thisclass == r.dtclassid_thisclass
				&& this->dtclassid_baseclass == r.dtclassid_baseclass
				&& this->offset_upcast_abs == r.offset_upcast_abs
				&& this->is_upcast_negative_offset == r.is_upcast_negative_offset
				&& &this->dtclassobj_baseclass == &r.dtclassobj_baseclass;
		}
		inline bool operator!=(const DynamicTypeTotalBaseClass& r) { return !(*this == r); }
	};

	class _impl_DynamicTypeClassObj {
	public:
		const DynamicTypeClassID dtclassid;
		/// <summary>
		/// Pointer to the declaration object.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		DynamicTypeClassObj* pdecl = nullptr;
		/// <summary>
		/// The set of direct base classes of this class.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		::std::unordered_set<DynamicTypeBaseClassDefObj, hash_DynamicTypeBaseClassDefObj_t> set_baseclass_direct;
		/// <summary>
		/// The map of unique base classes (direct or indirect) of this class.
		/// Base classes that share a common offset in this class are considered the same base class.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t> map_baseclass_total;
		_impl_DynamicTypeClassObj(DynamicTypeClassObj* _pdecl, const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef)
			: dtclassid(_pdecl->GetDynamicTypeClassID()), pdecl(_pdecl) {
			try {
				for (const DynamicTypeBaseClassDefObj* _it_dtbaseclassdef = _begin_dtbaseclassdef; _it_dtbaseclassdef != _end_dtbaseclassdef; ++_it_dtbaseclassdef)
					if (!set_baseclass_direct.emplace(*_it_dtbaseclassdef).second) abort();
			} catch (...) {
				abort();
			}
		}
		_impl_DynamicTypeClassObj(const _impl_DynamicTypeClassObj&) = delete;
		_impl_DynamicTypeClassObj(_impl_DynamicTypeClassObj&&) = delete;
		_impl_DynamicTypeClassObj& operator=(const _impl_DynamicTypeClassObj&) = delete;
		_impl_DynamicTypeClassObj& operator=(_impl_DynamicTypeClassObj&&) = delete;
		inline DynamicTypeTotalBaseClass* FindTotalBaseClass(const DynamicTypeClassID* dtclassid_base) {
			DynamicTypeTotalBaseClass* ret = nullptr;
			try {
				if (dtclassid_base && *dtclassid_base != DynamicTypeClassID_Null) {
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
						if (it_baseclass_total != this->map_baseclass_total.end()) ret = &it_baseclass_total->second;
					}
				}
			} catch (...) {
				abort();
			}
			return ret;
		}
		inline const DynamicTypeTotalBaseClass* FindTotalBaseClass(const DynamicTypeClassID* dtclassid_base) const {
			const DynamicTypeTotalBaseClass* ret = nullptr;
			try {
				if (dtclassid_base && *dtclassid_base != DynamicTypeClassID_Null) {
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::const_iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
						if (it_baseclass_total != this->map_baseclass_total.end()) ret = &it_baseclass_total->second;
					}
				}
			} catch (...) {
				abort();
			}
			return ret;
		}
	};

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(const DynamicTypeClassID* _dtclassid) {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (_dtclassid && *_dtclassid != DynamicTypeClassID_Null) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = map_dtclassobj_global->find(*_dtclassid);
					ret = it_dtclassobj == map_dtclassobj_global->end() ? nullptr : &it_dtclassobj->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::CreateImplObject(const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef) {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
		if (!this->is_module_local) {
			for (const DynamicTypeBaseClassDefObj* _it_dtbaseclassdef = _begin_dtbaseclassdef; _it_dtbaseclassdef != _end_dtbaseclassdef; ++_it_dtbaseclassdef)
				if (!_it_dtbaseclassdef || _it_dtbaseclassdef->IsModuleLocal()) abort();
		}
		this->pimpl = new _impl_DynamicTypeClassObj(this, _begin_dtbaseclassdef, _end_dtbaseclassdef);
		try {
			::std::unordered_set<DynamicTypeClassID, hash_DynamicTypeClassID_t> set_dtclassid_baseclass_conflict;
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				for (const DynamicTypeBaseClassDefObj& val_baseclass_direct : this->pimpl->set_baseclass_direct) {
					const size_t offset_upcast_abs_direct = val_baseclass_direct.GetUpcastOffsetAbs();
					const bool is_upcast_negative_offset_direct = val_baseclass_direct.IsUpcastNegativeOffset();
					DynamicTypeClassObj* dtclassobj_baseclass = val_baseclass_direct.GetDynamicTypeClassObject();
					if (!dtclassobj_baseclass) abort();
					if (!set_dtclassid_baseclass_conflict.count(val_baseclass_direct.GetDynamicTypeClassID())) {
						::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
							::std::piecewise_construct,
							::std::forward_as_tuple(val_baseclass_direct.GetDynamicTypeClassID()),
							::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, size_t, bool, DynamicTypeClassObj&>(
								this->dtclassid,
								val_baseclass_direct.GetDynamicTypeClassID(),
								offset_upcast_abs_direct,
								is_upcast_negative_offset_direct,
								*dtclassobj_baseclass
								)
						);
						if (!ret_emplace.second && ret_emplace.first->second != DynamicTypeTotalBaseClass(
							this->dtclassid,
							val_baseclass_direct.GetDynamicTypeClassID(),
							offset_upcast_abs_direct,
							is_upcast_negative_offset_direct,
							*dtclassobj_baseclass
						)) {
							set_dtclassid_baseclass_conflict.insert(val_baseclass_direct.GetDynamicTypeClassID());
							this->pimpl->map_baseclass_total.erase(ret_emplace.first);
						}
					}
					for (const ::std::pair<DynamicTypeClassID, DynamicTypeTotalBaseClass>& val_baseclass_indirect : dtclassobj_baseclass->pimpl->map_baseclass_total) {
						const size_t offset_upcast_abs_indirect = val_baseclass_indirect.second.offset_upcast_abs;
						const bool is_upcast_negative_offset_indirect = val_baseclass_indirect.second.is_upcast_negative_offset;
						size_t offset_upcast_abs_total;
						bool is_upcast_negative_offset_total;
						if (is_upcast_negative_offset_direct) {
							if (is_upcast_negative_offset_indirect) {
								offset_upcast_abs_total = offset_upcast_abs_direct + offset_upcast_abs_indirect;
								is_upcast_negative_offset_total = true;
							} else {
								if (offset_upcast_abs_indirect < offset_upcast_abs_direct) {
									offset_upcast_abs_total = offset_upcast_abs_direct - offset_upcast_abs_indirect;
									is_upcast_negative_offset_total = true;
								} else {
									offset_upcast_abs_total = offset_upcast_abs_indirect - offset_upcast_abs_direct;
									is_upcast_negative_offset_total = false;
								}
							}
						} else {
							if (is_upcast_negative_offset_indirect) {
								if (offset_upcast_abs_direct < offset_upcast_abs_indirect) {
									offset_upcast_abs_total = offset_upcast_abs_indirect - offset_upcast_abs_direct;
									is_upcast_negative_offset_total = true;
								} else {
									offset_upcast_abs_total = offset_upcast_abs_direct - offset_upcast_abs_indirect;
									is_upcast_negative_offset_total = false;
								}
							} else {
								offset_upcast_abs_total = offset_upcast_abs_direct + offset_upcast_abs_indirect;
								is_upcast_negative_offset_total = false;
							}
						}
						if (!set_dtclassid_baseclass_conflict.count(val_baseclass_indirect.first)) {
							::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
								::std::piecewise_construct,
								::std::forward_as_tuple(val_baseclass_indirect.first),
								::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, size_t, bool, DynamicTypeClassObj&>(
									this->dtclassid,
									val_baseclass_indirect.first,
									offset_upcast_abs_total,
									is_upcast_negative_offset_total,
									val_baseclass_indirect.second.dtclassobj_baseclass
									)
							);
							if (!ret_emplace.second && ret_emplace.first->second != DynamicTypeTotalBaseClass(
								this->dtclassid,
								val_baseclass_indirect.first,
								offset_upcast_abs_total,
								is_upcast_negative_offset_total,
								val_baseclass_indirect.second.dtclassobj_baseclass
							)) {
								set_dtclassid_baseclass_conflict.insert(val_baseclass_indirect.first);
								this->pimpl->map_baseclass_total.erase(ret_emplace.first);
							}
						}
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::DestroyImplObject() {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
	}

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindBaseClassObject(const DynamicTypeClassID* dtclassid_base) const {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (dtclassid_base && *dtclassid_base != DynamicTypeClassID_Null) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::const_iterator it_baseclass_total = this->pimpl->map_baseclass_total.find(*dtclassid_base);
					if (it_baseclass_total != this->pimpl->map_baseclass_total.cend()) ret = &it_baseclass_total->second.dtclassobj_baseclass;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API uintptr_t YBWLIB2_CALLTYPE DynamicTypeClassObj::DynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const {
		uintptr_t ret = 0;
		try {
			if (dtclassobj_target && (!dtclassobj_target->IsModuleLocal() || this->IsModuleLocal())) {
				if (dtclassobj_target == this) {
					ret = ptr_obj;
				} else {
					const DynamicTypeClassID* dtclassid_target = &dtclassobj_target->GetDynamicTypeClassID();
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						DynamicTypeTotalBaseClass* dttotalbaseclassobj_target_found = this->pimpl->FindTotalBaseClass(dtclassid_target);
						if (dttotalbaseclassobj_target_found && &dttotalbaseclassobj_target_found->dtclassobj_baseclass == dtclassobj_target) {
							if (dttotalbaseclassobj_target_found->is_upcast_negative_offset) {
								if (ptr_obj >= dttotalbaseclassobj_target_found->offset_upcast_abs) ret = ptr_obj - dttotalbaseclassobj_target_found->offset_upcast_abs;
							} else {
								if (ptr_obj <= UINTPTR_MAX - dttotalbaseclassobj_target_found->offset_upcast_abs) ret = ptr_obj + dttotalbaseclassobj_target_found->offset_upcast_abs;
							}
						}
					}
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::RegisterGlobal() {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!map_dtclassobj_global->emplace(this->dtclassid, *this).second) abort();
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::UnRegisterGlobal() {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!map_dtclassobj_global->erase(this->dtclassid)) abort();
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE DynamicType_RealInitGlobal() noexcept {
		mtx_dtenv = new ::std::recursive_mutex();
		if (!mtx_dtenv) abort();
		wrapper_lockable_dtenv = new wrapper_lockable_t(WrapLockable(*mtx_dtenv));
		if (!wrapper_lockable_dtenv) abort();
		map_dtclassobj_global = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>();
		if (!map_dtclassobj_global) abort();
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE(IDynamicTypeObject);
	}

	void YBWLIB2_CALLTYPE DynamicType_RealUnInitGlobal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(IDynamicTypeObject);
		if (!map_dtclassobj_global->empty()) abort();
		delete map_dtclassobj_global;
		map_dtclassobj_global = nullptr;
		delete wrapper_lockable_dtenv;
		wrapper_lockable_dtenv = nullptr;
		delete mtx_dtenv;
		mtx_dtenv = nullptr;
	}
}
