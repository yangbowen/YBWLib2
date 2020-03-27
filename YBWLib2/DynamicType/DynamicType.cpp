#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <utility>
#include <tuple>
#include "../Common/CommonLowLevel.h"
#include "DynamicType.h"

namespace YBWLib2 {
	YBWLIB2_API wrapper_lockable_t* wrapper_lockable_dtenv = nullptr;
	YBWLIB2_API ::std::unordered_map<const module_info_t*, DynamicTypeClassObj*(YBWLIB2_CALLTYPE*)(const DynamicTypeClassID* _dtclassid) noexcept>* map_fnptr_FindDynamicTypeClassObject_module = nullptr;
	YBWLIB2_API ConstructorID ConstructorID_Default;
	YBWLIB2_API ConstructorID ConstructorID_Copy;
	YBWLIB2_API ConstructorID ConstructorID_Move;
	YBWLIB2_API IndexedDataEntryID ConstructorIDParameterIndexedDataEntry::entryid;
	YBWLIB2_API IndexedDataEntryID ObjectPointerFromParameterIndexedDataEntry::entryid;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDynamicTypeObject, YBWLIB2_API);

	static ::std::recursive_mutex* mtx_dtenv = nullptr;
	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj*>* map_dtclassobj_global = nullptr;

	class DynamicTypeTotalBaseClass {
	public:
		struct upcast_step_t {
			fnptr_dynamic_type_upcast_t fnptr_dynamic_type_upcast = nullptr;
			const DynamicTypeClassObj* dtclassobj_from = nullptr;
			const DynamicTypeBaseClassDefObj* dtbaseclassdef = nullptr;
			inline constexpr upcast_step_t(
				fnptr_dynamic_type_upcast_t _fnptr_dynamic_type_upcast,
				const DynamicTypeClassObj* _dtclassobj_from,
				const DynamicTypeBaseClassDefObj* _dtbaseclassdef
			)
				: fnptr_dynamic_type_upcast(_fnptr_dynamic_type_upcast),
				dtclassobj_from(_dtclassobj_from),
				dtbaseclassdef(_dtbaseclassdef) {}
		};
		const DynamicTypeClassID dtclassid_thisclass;
		const DynamicTypeClassID dtclassid_baseclass;
		DynamicTypeClassObj& dtclassobj_baseclass;
		/// <summary>
		/// A pointer to the <c>DynamicTypeClassObj</c> object that represents the top (most base) virtual base class along the inheritance route form this class to the base class.
		/// If there's none virtual base class along the route, this variable will be set to an empty pointer.
		/// If the base class itself is a virtual base class, this variable will be the same as <c>&this->dtclassobj_baseclass</c>.
		/// This variable is used to check whether 2 different inheritance routes lead to the same location in the object.
		/// </summary>
		DynamicTypeClassObj* const dtclassobj_top_virtual_along_route;
		::std::vector<upcast_step_t> vec_upcast_step;
		inline DynamicTypeTotalBaseClass(
			const DynamicTypeClassID& _dtclassid_thisclass,
			const DynamicTypeClassID& _dtclassid_baseclass,
			DynamicTypeClassObj& _dtclassobj_baseclass,
			DynamicTypeClassObj* _dtclassobj_top_virtual_along_route,
			const ::std::vector<upcast_step_t>& _vec_upcast_step)
			: dtclassid_thisclass(_dtclassid_thisclass),
			dtclassid_baseclass(_dtclassid_baseclass),
			dtclassobj_baseclass(_dtclassobj_baseclass),
			dtclassobj_top_virtual_along_route(_dtclassobj_top_virtual_along_route),
			vec_upcast_step(_vec_upcast_step) {}
		inline DynamicTypeTotalBaseClass(
			const DynamicTypeClassID& _dtclassid_thisclass,
			const DynamicTypeClassID& _dtclassid_baseclass,
			DynamicTypeClassObj& _dtclassobj_baseclass,
			DynamicTypeClassObj* _dtclassobj_top_virtual_along_route,
			::std::vector<upcast_step_t>&& _vec_upcast_step)
			: dtclassid_thisclass(_dtclassid_thisclass),
			dtclassid_baseclass(_dtclassid_baseclass),
			dtclassobj_baseclass(_dtclassobj_baseclass),
			dtclassobj_top_virtual_along_route(_dtclassobj_top_virtual_along_route),
			vec_upcast_step(::std::move(_vec_upcast_step)) {}
	};

	class _impl_DynamicTypeClassObj {
	public:
		const DynamicTypeClassID dtclassid;
		/// <summary>
		/// Pointer to the declaration object.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		DynamicTypeClassObj* pdecl = nullptr;
		/// <summary>The map of <c>wrapper_type_info_t</c> objects that represents the type of this class.</summary>
		::std::unordered_map<const module_info_t*, wrapper_type_info_t> map_wrapper_type_info;
		/// <summary>
		/// The set of direct base classes of this class.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		::std::unordered_set<DynamicTypeBaseClassDefObj> set_baseclass_direct;
		/// <summary>
		/// The map of unique base classes (direct or indirect) of this class.
		/// Base classes that share a common offset in this class are considered the same base class.
		/// This member variable is only modified during the construction and destruction of this object.
		/// </summary>
		::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass> map_baseclass_total;
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
				if (dtclassid_base && *dtclassid_base) {
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass>::iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
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
				if (dtclassid_base && *dtclassid_base) {
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass>::const_iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
						if (it_baseclass_total != this->map_baseclass_total.end()) ret = &it_baseclass_total->second;
					}
				}
			} catch (...) {
				abort();
			}
			return ret;
		}
	};

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(const DynamicTypeClassID* _dtclassid) noexcept {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (_dtclassid && *_dtclassid) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj*>::iterator it_dtclassobj = map_dtclassobj_global->find(*_dtclassid);
					if (it_dtclassobj != map_dtclassobj_global->end()) ret = it_dtclassobj->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindDynamicTypeClassObjectSpecifiedModule(const module_info_t* _module_info, const DynamicTypeClassID* _dtclassid) noexcept {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (!map_fnptr_FindDynamicTypeClassObject_module) abort();
			::std::unordered_map<const module_info_t*, DynamicTypeClassObj*(YBWLIB2_CALLTYPE*)(const DynamicTypeClassID* _dtclassid) noexcept>::const_iterator it_map_fnptr_FindDynamicTypeClassObject_module = map_fnptr_FindDynamicTypeClassObject_module->find(_module_info);
			if (it_map_fnptr_FindDynamicTypeClassObject_module != map_fnptr_FindDynamicTypeClassObject_module->cend()) {
				if (!it_map_fnptr_FindDynamicTypeClassObject_module->second) abort();
				ret = (*it_map_fnptr_FindDynamicTypeClassObject_module->second)(_dtclassid);
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API const wrapper_type_info_t* YBWLIB2_CALLTYPE DynamicTypeClassObj::GetTypeInfoWrapper(const module_info_t* _module_info) const noexcept {
		const wrapper_type_info_t* ret = nullptr;
		try {
			if (_module_info) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<const module_info_t*, wrapper_type_info_t>::const_iterator it_wrapper_type_info = this->pimpl->map_wrapper_type_info.find(_module_info);
					if (it_wrapper_type_info != this->pimpl->map_wrapper_type_info.cend()) ret = &it_wrapper_type_info->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindBaseClassObject(const DynamicTypeClassID* dtclassid_base) const {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (dtclassid_base && *dtclassid_base) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass>::const_iterator it_baseclass_total = this->pimpl->map_baseclass_total.find(*dtclassid_base);
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
						const DynamicTypeTotalBaseClass* dttotalbaseclassobj_target_found = this->pimpl->FindTotalBaseClass(dtclassid_target);
						if (dttotalbaseclassobj_target_found && &dttotalbaseclassobj_target_found->dtclassobj_baseclass == dtclassobj_target) {
							ret = ptr_obj;
							for (const DynamicTypeTotalBaseClass::upcast_step_t& val_upcast_step : dttotalbaseclassobj_target_found->vec_upcast_step) {
								if (!val_upcast_step.fnptr_dynamic_type_upcast) abort();
								if (!ret) break;
								ret = (*val_upcast_step.fnptr_dynamic_type_upcast)(ret, val_upcast_step.dtclassobj_from, val_upcast_step.dtbaseclassdef);
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

	YBWLIB2_API bool YBWLIB2_CALLTYPE DynamicTypeClassObj::CanDynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const {
		bool ret = false;
		try {
			if (ptr_obj && dtclassobj_target && (!dtclassobj_target->IsModuleLocal() || this->IsModuleLocal())) {
				if (dtclassobj_target == this) {
					ret = true;
				} else {
					const DynamicTypeClassID* dtclassid_target = &dtclassobj_target->GetDynamicTypeClassID();
					{
						::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
						const DynamicTypeTotalBaseClass* dttotalbaseclassobj_target_found = this->pimpl->FindTotalBaseClass(dtclassid_target);
						if (dttotalbaseclassobj_target_found && &dttotalbaseclassobj_target_found->dtclassobj_baseclass == dtclassobj_target) {
							ret = true;
						}
					}
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::RegisterTypeInfoWrapper(const wrapper_type_info_t* _wrapper_type_info, const module_info_t* _module_info) noexcept {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!this->pimpl->map_wrapper_type_info.emplace(_module_info, *_wrapper_type_info).second) abort();
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::UnRegisterTypeInfoWrapper(const module_info_t* _module_info) noexcept {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!this->pimpl->map_wrapper_type_info.erase(_module_info)) abort();
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::CreateImplObject(const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef) {
		try {
			if (this->pimpl) {
				delete this->pimpl;
				this->pimpl = nullptr;
			}
			if (!this->is_module_local) {
				for (const DynamicTypeBaseClassDefObj* _it_dtbaseclassdef = _begin_dtbaseclassdef; _it_dtbaseclassdef != _end_dtbaseclassdef; ++_it_dtbaseclassdef)
					if (!_it_dtbaseclassdef || _it_dtbaseclassdef->IsModuleLocal()) abort();
			}
			this->pimpl = new _impl_DynamicTypeClassObj(this, _begin_dtbaseclassdef, _end_dtbaseclassdef);
			::std::unordered_set<DynamicTypeClassID> set_dtclassid_baseclass_conflict;
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				for (const DynamicTypeBaseClassDefObj& val_baseclass_direct : this->pimpl->set_baseclass_direct) {
					const DynamicTypeTotalBaseClass::upcast_step_t upcast_step_direct(
						val_baseclass_direct.GetDynamicTypeStaticCastFnptr(),
						this,
						&val_baseclass_direct
					);
					if (!upcast_step_direct.fnptr_dynamic_type_upcast) abort();
					DynamicTypeClassObj* dtclassobj_baseclass = val_baseclass_direct.GetDynamicTypeClassObject();
					if (!dtclassobj_baseclass) abort();
					if (!set_dtclassid_baseclass_conflict.count(val_baseclass_direct.GetDynamicTypeClassID())) {
						DynamicTypeClassObj* const dtclassobj_top_virtual_along_route =
							val_baseclass_direct.GetDynamicTypeBaseClassFlags() & DynamicTypeBaseClassFlag_VirtualBase ? dtclassobj_baseclass : nullptr;
						::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
							::std::piecewise_construct,
							::std::forward_as_tuple(val_baseclass_direct.GetDynamicTypeClassID()),
							::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeClassObj*, ::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>&&>(
								this->dtclassid,
								val_baseclass_direct.GetDynamicTypeClassID(),
								*dtclassobj_baseclass,
								dtclassobj_top_virtual_along_route,
								::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>(1, upcast_step_direct)
								)
						);
						if (!ret_emplace.second) {
							if (dtclassobj_top_virtual_along_route && dtclassobj_top_virtual_along_route == ret_emplace.first->second.dtclassobj_top_virtual_along_route) {
								// The 2 inheritance routes lead to the same location in the object.
								// There's no actual conflict between these total base classes.
								// To reduce performance overhead of upcasting, the inheritance route with less upcasting steps is preferred.
								// Because the total base class that has just failed to be inserted is direct, it will always be preferred.
								this->pimpl->map_baseclass_total.erase(ret_emplace.first);
								if (!this->pimpl->map_baseclass_total.emplace(
									::std::piecewise_construct,
									::std::forward_as_tuple(val_baseclass_direct.GetDynamicTypeClassID()),
									::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeClassObj*, ::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>&&>(
										this->dtclassid,
										val_baseclass_direct.GetDynamicTypeClassID(),
										*dtclassobj_baseclass,
										dtclassobj_top_virtual_along_route,
										::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>(1, upcast_step_direct)
										)
								).second) abort();
							} else {
								// The 2 inheritance routes lead to different locations in the object.
								// As a result, references to these total base classes are ambiguous.
								set_dtclassid_baseclass_conflict.insert(val_baseclass_direct.GetDynamicTypeClassID());
								this->pimpl->map_baseclass_total.erase(ret_emplace.first);
							}
						}
					}
					for (const ::std::pair<DynamicTypeClassID, DynamicTypeTotalBaseClass>& val_baseclass_indirect : dtclassobj_baseclass->pimpl->map_baseclass_total) {
						if (!set_dtclassid_baseclass_conflict.count(val_baseclass_indirect.first)) {
							::std::vector<DynamicTypeTotalBaseClass::upcast_step_t> vec_upcast_step_total(1, upcast_step_direct);
							vec_upcast_step_total.reserve(1 + val_baseclass_indirect.second.vec_upcast_step.size());
							for (const DynamicTypeTotalBaseClass::upcast_step_t& val_upcast_step_indirect : val_baseclass_indirect.second.vec_upcast_step)
								vec_upcast_step_total.push_back(val_upcast_step_indirect);
							DynamicTypeClassObj* const dtclassobj_top_virtual_along_route =
								val_baseclass_indirect.second.dtclassobj_top_virtual_along_route
								? val_baseclass_indirect.second.dtclassobj_top_virtual_along_route
								: (val_baseclass_direct.GetDynamicTypeBaseClassFlags() & DynamicTypeBaseClassFlag_VirtualBase ? dtclassobj_baseclass : nullptr);
							::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
								::std::piecewise_construct,
								::std::forward_as_tuple(val_baseclass_indirect.first),
								::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeClassObj*, const ::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>&>(
									this->dtclassid,
									val_baseclass_indirect.first,
									val_baseclass_indirect.second.dtclassobj_baseclass,
									dtclassobj_top_virtual_along_route,
									vec_upcast_step_total
									)
							);
							if (!ret_emplace.second) {
								if (dtclassobj_top_virtual_along_route && dtclassobj_top_virtual_along_route == ret_emplace.first->second.dtclassobj_top_virtual_along_route) {
									// The 2 inheritance routes lead to the same location in the object.
									// There's no actual conflict between these total base classes.
									// To reduce performance overhead of upcasting, the inheritance route with less upcasting steps is preferred.
									if (vec_upcast_step_total.size() < ret_emplace.first->second.vec_upcast_step.size()) {
										this->pimpl->map_baseclass_total.erase(ret_emplace.first);
										if (!this->pimpl->map_baseclass_total.emplace(
											::std::piecewise_construct,
											::std::forward_as_tuple(val_baseclass_indirect.first),
											::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeClassObj*, ::std::vector<DynamicTypeTotalBaseClass::upcast_step_t>&&>(
												this->dtclassid,
												val_baseclass_indirect.first,
												val_baseclass_indirect.second.dtclassobj_baseclass,
												dtclassobj_top_virtual_along_route,
												::std::move(vec_upcast_step_total)
												)
										).second) abort();
									}
								} else {
									// The 2 inheritance routes lead to different locations in the object.
									// As a result, references to these total base classes are ambiguous.
									set_dtclassid_baseclass_conflict.insert(val_baseclass_indirect.first);
									this->pimpl->map_baseclass_total.erase(ret_emplace.first);
								}
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
		try {
			if (this->pimpl) {
				delete this->pimpl;
				this->pimpl = nullptr;
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::RegisterGlobal() {
		try {
			{
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				if (!map_dtclassobj_global->emplace(this->dtclassid, this).second) abort();
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
		map_fnptr_FindDynamicTypeClassObject_module = new ::std::unordered_map<const module_info_t*, DynamicTypeClassObj*(YBWLIB2_CALLTYPE*)(const DynamicTypeClassID* _dtclassid) noexcept>();
		if (!map_fnptr_FindDynamicTypeClassObject_module) abort();
		map_dtclassobj_global = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj*>();
		if (!map_dtclassobj_global) abort();
		ConstructorID_Default = ConstructorID(PersistentID_ConstructorID_Default);
		ConstructorID_Copy = ConstructorID(PersistentID_ConstructorID_Copy);
		ConstructorID_Move = ConstructorID(PersistentID_ConstructorID_Move);
		ConstructorIDParameterIndexedDataEntry::entryid = IndexedDataEntryID(ConstructorIDParameterIndexedDataEntry::persistentid_entryid);
		ObjectPointerFromParameterIndexedDataEntry::entryid = IndexedDataEntryID(ObjectPointerFromParameterIndexedDataEntry::persistentid_entryid);
		IDynamicTypeObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IDynamicTypeObject>(),
			IsDynamicTypeModuleLocalClass<IDynamicTypeObject>(),
			{},
			0, sizeof(IDynamicTypeObject), alignof(IDynamicTypeObject));
	}

	void YBWLIB2_CALLTYPE DynamicType_RealUnInitGlobal() noexcept {
		delete IDynamicTypeObject::DynamicTypeThisClassObject;
		IDynamicTypeObject::DynamicTypeThisClassObject = nullptr;
		ObjectPointerFromParameterIndexedDataEntry::entryid = IndexedDataEntryID();
		ConstructorIDParameterIndexedDataEntry::entryid = IndexedDataEntryID();
		ConstructorID_Move = ConstructorID();
		ConstructorID_Copy = ConstructorID();
		ConstructorID_Default = ConstructorID();
		if (!map_dtclassobj_global->empty()) abort();
		delete map_dtclassobj_global;
		map_dtclassobj_global = nullptr;
		if (!map_fnptr_FindDynamicTypeClassObject_module->empty()) abort();
		delete map_fnptr_FindDynamicTypeClassObject_module;
		map_fnptr_FindDynamicTypeClassObject_module = nullptr;
		delete wrapper_lockable_dtenv;
		wrapper_lockable_dtenv = nullptr;
		delete mtx_dtenv;
		mtx_dtenv = nullptr;
	}
}
