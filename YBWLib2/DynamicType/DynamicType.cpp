#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <utility>
#include <tuple>
#include "../Common/CommonLowLevel.h"
#include "DynamicType.h"

namespace YBWLib2 {
	YBWLIB2_API wrapper_lockable_t* wrapper_lockable_dtenv = nullptr;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IDynamicTypeObject, YBWLIB2_API);

	static ::std::recursive_mutex* mtx_dtenv = nullptr;
	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>* map_dtclassobj_global = nullptr;

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
		upcast_step_t* arr_upcast_step = nullptr;
		size_t size_arr_upcast_step = 0;
		inline DynamicTypeTotalBaseClass(
			const DynamicTypeClassID& _dtclassid_thisclass,
			const DynamicTypeClassID& _dtclassid_baseclass,
			DynamicTypeClassObj& _dtclassobj_baseclass,
			upcast_step_t* _arr_upcast_step,
			size_t _size_arr_upcast_step) noexcept
			: dtclassid_thisclass(_dtclassid_thisclass),
			dtclassid_baseclass(_dtclassid_baseclass),
			dtclassobj_baseclass(_dtclassobj_baseclass),
			arr_upcast_step(_arr_upcast_step),
			size_arr_upcast_step(_size_arr_upcast_step) {
			if (this->size_arr_upcast_step && !this->arr_upcast_step) abort();
		}
		inline DynamicTypeTotalBaseClass(const DynamicTypeTotalBaseClass& x)
			: dtclassid_thisclass(x.dtclassid_thisclass),
			dtclassid_baseclass(x.dtclassid_baseclass),
			dtclassobj_baseclass(x.dtclassobj_baseclass),
			size_arr_upcast_step(x.size_arr_upcast_step) {
			if (x.arr_upcast_step) {
				this->arr_upcast_step = reinterpret_cast<upcast_step_t*>(rawallocator_crt_YBWLib2->Allocate(this->size_arr_upcast_step * sizeof(upcast_step_t)));
				for (size_t i = 0; i < this->size_arr_upcast_step; ++i)
					new(this->arr_upcast_step + i) upcast_step_t(x.arr_upcast_step[i]);
				this->arr_upcast_step = ::std::launder(this->arr_upcast_step);
			}
		}
		inline DynamicTypeTotalBaseClass(DynamicTypeTotalBaseClass&& x) noexcept
			: dtclassid_thisclass(x.dtclassid_thisclass),
			dtclassid_baseclass(x.dtclassid_baseclass),
			dtclassobj_baseclass(x.dtclassobj_baseclass),
			size_arr_upcast_step(x.size_arr_upcast_step) {
			if (x.arr_upcast_step) {
				this->arr_upcast_step = x.arr_upcast_step;
				x.arr_upcast_step = nullptr;
			}
			x.size_arr_upcast_step = 0;
		}
		inline ~DynamicTypeTotalBaseClass() {
			if (this->arr_upcast_step) {
				for (size_t i = 0; i < this->size_arr_upcast_step; ++i)
					this->arr_upcast_step[i].~upcast_step_t();
				this->arr_upcast_step = ::std::launder(this->arr_upcast_step);
				if (!rawallocator_crt_YBWLib2->Deallocate(this->arr_upcast_step, this->size_arr_upcast_step * sizeof(upcast_step_t))) abort();
				this->arr_upcast_step = nullptr;
			}
			this->size_arr_upcast_step = 0;
		}
		DynamicTypeTotalBaseClass& operator=(const DynamicTypeTotalBaseClass& x) = delete;
		DynamicTypeTotalBaseClass& operator=(DynamicTypeTotalBaseClass&& x) = delete;
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
					const DynamicTypeTotalBaseClass::upcast_step_t upcast_step_direct(
						val_baseclass_direct.GetDynamicTypeStaticCastFnptr(),
						this,
						&val_baseclass_direct
					);
					if (!upcast_step_direct.fnptr_dynamic_type_upcast) abort();
					DynamicTypeClassObj* dtclassobj_baseclass = val_baseclass_direct.GetDynamicTypeClassObject();
					if (!dtclassobj_baseclass) abort();
					if (!set_dtclassid_baseclass_conflict.count(val_baseclass_direct.GetDynamicTypeClassID())) {
						DynamicTypeTotalBaseClass::upcast_step_t* arr_upcast_step =
							reinterpret_cast<DynamicTypeTotalBaseClass::upcast_step_t*>(rawallocator_crt_YBWLib2->Allocate(1 * sizeof(DynamicTypeTotalBaseClass::upcast_step_t)));
						if (!arr_upcast_step) abort();
						new(arr_upcast_step) DynamicTypeTotalBaseClass::upcast_step_t(upcast_step_direct);
						arr_upcast_step = ::std::launder(arr_upcast_step);
						try {
							::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
								::std::piecewise_construct,
								::std::forward_as_tuple(val_baseclass_direct.GetDynamicTypeClassID()),
								::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeTotalBaseClass::upcast_step_t*, size_t>(
									this->dtclassid,
									val_baseclass_direct.GetDynamicTypeClassID(),
									*dtclassobj_baseclass,
									arr_upcast_step,
									1
									)
							);
							if (ret_emplace.second) {
								arr_upcast_step = nullptr;
							} else {
								arr_upcast_step->~upcast_step_t();
								arr_upcast_step = ::std::launder(arr_upcast_step);
								if (!rawallocator_crt_YBWLib2->Deallocate(arr_upcast_step, 1 * sizeof(DynamicTypeTotalBaseClass::upcast_step_t))) abort();
								arr_upcast_step = nullptr;
								set_dtclassid_baseclass_conflict.insert(val_baseclass_direct.GetDynamicTypeClassID());
								this->pimpl->map_baseclass_total.erase(ret_emplace.first);
							}
						} catch (...) {
							if (arr_upcast_step) {
								arr_upcast_step->~upcast_step_t();
								arr_upcast_step = ::std::launder(arr_upcast_step);
								if (!rawallocator_crt_YBWLib2->Deallocate(arr_upcast_step, 1 * sizeof(DynamicTypeTotalBaseClass::upcast_step_t))) abort();
								arr_upcast_step = nullptr;
							}
							throw;
						}
					}
					for (const ::std::pair<DynamicTypeClassID, DynamicTypeTotalBaseClass>& val_baseclass_indirect : dtclassobj_baseclass->pimpl->map_baseclass_total) {
						const DynamicTypeTotalBaseClass::upcast_step_t* arr_upcast_step_indirect = val_baseclass_indirect.second.arr_upcast_step;
						size_t size_arr_upcast_step_indirect = val_baseclass_indirect.second.size_arr_upcast_step;
						if (size_arr_upcast_step_indirect && !arr_upcast_step_indirect) abort();
						if (!set_dtclassid_baseclass_conflict.count(val_baseclass_indirect.first)) {
							size_t size_arr_upcast_step_total = size_arr_upcast_step_indirect + 1;
							DynamicTypeTotalBaseClass::upcast_step_t* arr_upcast_step_total =
								reinterpret_cast<DynamicTypeTotalBaseClass::upcast_step_t*>(rawallocator_crt_YBWLib2->Allocate(size_arr_upcast_step_total * sizeof(DynamicTypeTotalBaseClass::upcast_step_t)));
							if (!arr_upcast_step_total) abort();
							new(arr_upcast_step_total + 0) DynamicTypeTotalBaseClass::upcast_step_t(upcast_step_direct);
							for (size_t i = 0; i < size_arr_upcast_step_indirect; ++i)
								new(arr_upcast_step_total + 1 + i) DynamicTypeTotalBaseClass::upcast_step_t(arr_upcast_step_indirect[i]);
							arr_upcast_step_total = ::std::launder(arr_upcast_step_total);
							try {
								::std::pair<::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator, bool> ret_emplace = this->pimpl->map_baseclass_total.emplace(
									::std::piecewise_construct,
									::std::forward_as_tuple(val_baseclass_indirect.first),
									::std::tuple<const DynamicTypeClassID&, const DynamicTypeClassID&, DynamicTypeClassObj&, DynamicTypeTotalBaseClass::upcast_step_t*, size_t>(
										this->dtclassid,
										val_baseclass_indirect.first,
										val_baseclass_indirect.second.dtclassobj_baseclass,
										arr_upcast_step_total,
										size_arr_upcast_step_total
										)
								);
								if (ret_emplace.second) {
									arr_upcast_step_total = nullptr;
								} else {
									for (size_t i = 0; i < size_arr_upcast_step_total; ++i)
										arr_upcast_step_total[i].~upcast_step_t();
									arr_upcast_step_total = ::std::launder(arr_upcast_step_total);
									if (!rawallocator_crt_YBWLib2->Deallocate(arr_upcast_step_total, size_arr_upcast_step_total * sizeof(DynamicTypeTotalBaseClass::upcast_step_t))) abort();
									arr_upcast_step_total = nullptr;
									set_dtclassid_baseclass_conflict.insert(val_baseclass_indirect.first);
									this->pimpl->map_baseclass_total.erase(ret_emplace.first);
									// TODO: Handle virtual base class case.
								}
							} catch (...) {
								if (arr_upcast_step_total) {
									for (size_t i = 0; i < size_arr_upcast_step_total; ++i)
										arr_upcast_step_total[i].~upcast_step_t();
									arr_upcast_step_total = ::std::launder(arr_upcast_step_total);
									if (!rawallocator_crt_YBWLib2->Deallocate(arr_upcast_step_total, size_arr_upcast_step_total * sizeof(DynamicTypeTotalBaseClass::upcast_step_t))) abort();
									arr_upcast_step_total = nullptr;
								}
								throw;
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
						const DynamicTypeTotalBaseClass* dttotalbaseclassobj_target_found = this->pimpl->FindTotalBaseClass(dtclassid_target);
						if (dttotalbaseclassobj_target_found && &dttotalbaseclassobj_target_found->dtclassobj_baseclass == dtclassobj_target) {
							if (dttotalbaseclassobj_target_found->size_arr_upcast_step && !dttotalbaseclassobj_target_found->arr_upcast_step) abort();
							ret = ptr_obj;
							for (
								const DynamicTypeTotalBaseClass::upcast_step_t* upcast_step = dttotalbaseclassobj_target_found->arr_upcast_step;
								upcast_step != dttotalbaseclassobj_target_found->arr_upcast_step + dttotalbaseclassobj_target_found->size_arr_upcast_step;
								++upcast_step
								) {
								if (!upcast_step->fnptr_dynamic_type_upcast) abort();
								if (!ret) break;
								ret = (*upcast_step->fnptr_dynamic_type_upcast)(ret, upcast_step->dtclassobj_from, upcast_step->dtbaseclassdef);
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
		IDynamicTypeObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IDynamicTypeObject>(),
			IsDynamicTypeModuleLocalClass<IDynamicTypeObject>(),
			{});
	}

	void YBWLIB2_CALLTYPE DynamicType_RealUnInitGlobal() noexcept {
		delete IDynamicTypeObject::DynamicTypeThisClassObject;
		IDynamicTypeObject::DynamicTypeThisClassObject = nullptr;
		if (!map_dtclassobj_global->empty()) abort();
		delete map_dtclassobj_global;
		map_dtclassobj_global = nullptr;
		delete wrapper_lockable_dtenv;
		wrapper_lockable_dtenv = nullptr;
		delete mtx_dtenv;
		mtx_dtenv = nullptr;
	}
}
