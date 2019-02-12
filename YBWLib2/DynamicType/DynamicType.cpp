#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <atomic>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <tuple>
#include "DynamicType.h"
#include "DynamicTypeInternal.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS_NOBASE(IDynamicTypeObject, YBWLIB2_API);

	YBWLIB2_API wrapper_mtx_dtenv_t wrapper_mtx_dtenv {};

	static INIT_ONCE initonce_dtenv = INIT_ONCE_STATIC_INIT;
	static ::std::recursive_mutex* impl_mtx_dtenv = nullptr;
	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>* map_dtclassobj = nullptr;
	static void dtenv_init() noexcept {
		if (!InitOnceExecuteOnce(&initonce_dtenv,
			[](PINIT_ONCE InitOnce, PVOID Parameter, PVOID* Context)->BOOL {
				UNREFERENCED_PARAMETER(InitOnce);
				UNREFERENCED_PARAMETER(Parameter);
				UNREFERENCED_PARAMETER(Context);
				try {
					impl_mtx_dtenv = new ::std::recursive_mutex();
					if (!impl_mtx_dtenv) return FALSE;
					map_dtclassobj = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>();
					if (!map_dtclassobj) return FALSE;
				} catch (...) {
					return FALSE;
				}
				return TRUE;
			}
		, nullptr, nullptr)) terminate();
	}

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

	class _impl_DynamicTypeBaseClassDefObj {
	public:
		/// <summary>Pointer to the declaration object.</summary>
		DynamicTypeBaseClassDefObj* pdecl = nullptr;
		INIT_ONCE initonce = INIT_ONCE_STATIC_INIT;
		explicit _impl_DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj* _pdecl)
			: pdecl(_pdecl) {}
		_impl_DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj* _pdecl, const _impl_DynamicTypeBaseClassDefObj&)
			: pdecl(_pdecl) {}
		_impl_DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj* _pdecl, _impl_DynamicTypeBaseClassDefObj&&)
			: pdecl(_pdecl) {}
		_impl_DynamicTypeBaseClassDefObj(const _impl_DynamicTypeBaseClassDefObj&) = delete;
		_impl_DynamicTypeBaseClassDefObj(_impl_DynamicTypeBaseClassDefObj&&) = delete;
		_impl_DynamicTypeBaseClassDefObj& operator=(const _impl_DynamicTypeBaseClassDefObj& x) = delete;
		_impl_DynamicTypeBaseClassDefObj& operator=(_impl_DynamicTypeBaseClassDefObj&& x) = delete;
	};

	class _impl_DynamicTypeClassObj {
	public:
		const DynamicTypeClassID dtclassid;
		/// <summary>
		/// Pointer to the declaration object.
		/// This member variable is only modified during the construction and destruction of this object, which is during executable module initialization and cleanup.
		/// </summary>
		DynamicTypeClassObj* pdecl = nullptr;
		/// <summary>
		/// The set of direct base classes of this class.
		/// This member variable is only modified during the construction and destruction of this object, which is during executable module initialization and cleanup.
		/// </summary>
		::std::unordered_set<DynamicTypeBaseClassDefObj, hash_DynamicTypeBaseClassDefObj_t> set_baseclass_direct;
		INIT_ONCE initonce = INIT_ONCE_STATIC_INIT;
		/// <summary>
		/// The map of unique base classes (direct or indirect) of this class.
		/// Base classes that share a common offset in this class are considered the same base class.
		/// This member variable is filled during initialization of the corresponding <c>DynamicTypeClassObj</c> object.
		/// </summary>
		::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t> map_baseclass_total;
		_impl_DynamicTypeClassObj(DynamicTypeClassObj* _pdecl, const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef)
			: dtclassid(_pdecl->GetDynamicTypeClassID()), pdecl(_pdecl) {
			for (const DynamicTypeBaseClassDefObj* _it_dtbaseclassdef = _begin_dtbaseclassdef; _it_dtbaseclassdef != _end_dtbaseclassdef; ++_it_dtbaseclassdef)
				set_baseclass_direct.emplace(*_it_dtbaseclassdef);
		}
		_impl_DynamicTypeClassObj(const _impl_DynamicTypeClassObj&) = delete;
		_impl_DynamicTypeClassObj(_impl_DynamicTypeClassObj&&) = delete;
		_impl_DynamicTypeClassObj& operator=(const _impl_DynamicTypeClassObj&) = delete;
		_impl_DynamicTypeClassObj& operator=(_impl_DynamicTypeClassObj&&) = delete;
		inline DynamicTypeTotalBaseClass* FindTotalBaseClass(const DynamicTypeClassID* dtclassid_base) {
			if (!dtclassid_base || *dtclassid_base == DynamicTypeClassID_Null) return nullptr;
			dtenv_init();
			{
				::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
				this->pdecl->Initialize();
				::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
				if (it_baseclass_total == this->map_baseclass_total.end())
					return nullptr;
				else
					return &it_baseclass_total->second;
			}
		}
		inline const DynamicTypeTotalBaseClass* FindTotalBaseClass(const DynamicTypeClassID* dtclassid_base) const {
			if (!dtclassid_base || *dtclassid_base == DynamicTypeClassID_Null) return nullptr;
			dtenv_init();
			{
				::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
				this->pdecl->Initialize();
				::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::const_iterator it_baseclass_total = this->map_baseclass_total.find(*dtclassid_base);
				if (it_baseclass_total == this->map_baseclass_total.end())
					return nullptr;
				else
					return &it_baseclass_total->second;
			}
		}
	};

	YBWLIB2_API bool YBWLIB2_CALLTYPE IsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) {
		return InlineIsEqualGUID(l->guid, r->guid);
	}

	YBWLIB2_API bool YBWLIB2_CALLTYPE IsLessThan_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) {
		static_assert(sizeof(uint8_t) == 0x1, "The size of uint8_t is not 0x1.");
		for (int i = 0; i < sizeof(GUID) / sizeof(uint8_t); ++i) {
			if (reinterpret_cast<const uint8_t*>(l)[i] < reinterpret_cast<const uint8_t*>(r)[i]) return true;
			if (reinterpret_cast<const uint8_t*>(l)[i] != reinterpret_cast<const uint8_t*>(r)[i]) return false;
		}
		return false;
	}

	YBWLIB2_API bool YBWLIB2_CALLTYPE SecureIsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) {
		if constexpr (sizeof(GUID) % sizeof(uintptr_t)) {
			uint8_t x = 0;
			for (size_t i = 0; i < sizeof(GUID) / sizeof(uint8_t); ++i) x |= reinterpret_cast<const uint8_t*>(&l->guid)[i] ^ reinterpret_cast<const uint8_t*>(&r->guid)[i];
			return !x;
		} else {
			uintptr_t x = 0;
			for (size_t i = 0; i < sizeof(GUID) / sizeof(uintptr_t); ++i) x |= reinterpret_cast<const uintptr_t*>(&l->guid)[i] ^ reinterpret_cast<const uintptr_t*>(&r->guid)[i];
			return !x;
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::Initialize() const {
		if (!InitOnceExecuteOnce(&this->pimpl->initonce,
			[](PINIT_ONCE InitOnce, PVOID Parameter, PVOID* Context)->BOOL {
				UNREFERENCED_PARAMETER(InitOnce);
				UNREFERENCED_PARAMETER(Context);
				reinterpret_cast<const DynamicTypeBaseClassDefObj*>(reinterpret_cast<uintptr_t>(Parameter))->RealInitialize();
				return TRUE;
			}
		, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this)), nullptr)) terminate();
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::CreateImplObject() {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
		if (this->dtclassid == DynamicTypeClassID_Null) terminate();
		this->pimpl = new _impl_DynamicTypeBaseClassDefObj(this);
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::CopyCreateImplObject(const DynamicTypeBaseClassDefObj* x) {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
		this->pimpl = new _impl_DynamicTypeBaseClassDefObj(this, *x->pimpl);
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::MoveCreateImplObject(DynamicTypeBaseClassDefObj* x) {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
		this->pimpl = new _impl_DynamicTypeBaseClassDefObj(this, ::std::move(*x->pimpl));
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::DestroyImplObject() {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeBaseClassDefObj::RealInitializeGlobal() const {
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			this->dtclassobj = DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
			if (!this->dtclassobj) terminate();
			if (this->dtclassobj->IsModuleLocal() != this->is_module_local) terminate();
		}
	}

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(const DynamicTypeClassID* _dtclassid) {
		if (!_dtclassid || *_dtclassid == DynamicTypeClassID_Null) return nullptr;
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash_DynamicTypeClassID_t>::iterator it_dtclassobj = map_dtclassobj->find(*_dtclassid);
			return it_dtclassobj == map_dtclassobj->end() ? nullptr : &it_dtclassobj->second;
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::CreateImplObject(const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef) {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
		if (!this->is_module_local) {
			for (const DynamicTypeBaseClassDefObj* _it_dtbaseclassdef = _begin_dtbaseclassdef; _it_dtbaseclassdef != _end_dtbaseclassdef; ++_it_dtbaseclassdef)
				if (!_it_dtbaseclassdef || _it_dtbaseclassdef->IsModuleLocal()) terminate();
		}
		this->pimpl = new _impl_DynamicTypeClassObj(this, _begin_dtbaseclassdef, _end_dtbaseclassdef);
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::DestroyImplObject() {
		if (this->pimpl) {
			delete this->pimpl;
			this->pimpl = nullptr;
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::Initialize() const {
		if (!InitOnceExecuteOnce(&this->pimpl->initonce,
			[](PINIT_ONCE InitOnce, PVOID Parameter, PVOID* Context)->BOOL {
				UNREFERENCED_PARAMETER(InitOnce);
				UNREFERENCED_PARAMETER(Context);
				reinterpret_cast<const DynamicTypeClassObj*>(reinterpret_cast<uintptr_t>(Parameter))->RealInitialize();
				return TRUE;
			}
		, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this)), nullptr)) terminate();
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::RealInitialize() const {
		::std::unordered_set<DynamicTypeClassID, hash_DynamicTypeClassID_t> set_dtclassid_baseclass_conflict;
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			for (const DynamicTypeBaseClassDefObj& val_baseclass_direct : this->pimpl->set_baseclass_direct) {
				const size_t offset_upcast_abs_direct = val_baseclass_direct.GetUpcastOffsetAbs();
				const bool is_upcast_negative_offset_direct = val_baseclass_direct.IsUpcastNegativeOffset();
				DynamicTypeClassObj* dtclassobj_baseclass = val_baseclass_direct.GetDynamicTypeClassObject();
				if (!dtclassobj_baseclass) terminate();
				dtclassobj_baseclass->Initialize();
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
	}

	YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE DynamicTypeClassObj::FindBaseClassObject(const DynamicTypeClassID* dtclassid_base) const {
		if (!dtclassid_base || *dtclassid_base == DynamicTypeClassID_Null) return nullptr;
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			this->Initialize();
			::std::unordered_map<DynamicTypeClassID, DynamicTypeTotalBaseClass, hash_DynamicTypeClassID_t>::const_iterator it_baseclass_total = this->pimpl->map_baseclass_total.find(*dtclassid_base);
			if (it_baseclass_total == this->pimpl->map_baseclass_total.cend())
				return nullptr;
			else
				return &it_baseclass_total->second.dtclassobj_baseclass;
		}
	}

	YBWLIB2_API uintptr_t YBWLIB2_CALLTYPE DynamicTypeClassObj::DynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const {
		if (!dtclassobj_target || dtclassobj_target->IsModuleLocal() && !this->IsModuleLocal()) return 0;
		if (dtclassobj_target == this) return ptr_obj;
		const DynamicTypeClassID* dtclassid_target = &dtclassobj_target->GetDynamicTypeClassID();
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			this->Initialize();
			DynamicTypeTotalBaseClass* dttotalbaseclassobj_target_found = this->pimpl->FindTotalBaseClass(dtclassid_target);
			if (!dttotalbaseclassobj_target_found || &dttotalbaseclassobj_target_found->dtclassobj_baseclass != dtclassobj_target) return 0;
			if (dttotalbaseclassobj_target_found->is_upcast_negative_offset) {
				if (ptr_obj < dttotalbaseclassobj_target_found->offset_upcast_abs)
					return 0;
				else
					return ptr_obj - dttotalbaseclassobj_target_found->offset_upcast_abs;
			} else {
				if (ptr_obj > UINTPTR_MAX - dttotalbaseclassobj_target_found->offset_upcast_abs)
					return 0;
				else
					return ptr_obj + dttotalbaseclassobj_target_found->offset_upcast_abs;
			}
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::RegisterGlobal() {
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!map_dtclassobj->emplace(this->dtclassid, *this).second) terminate();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE DynamicTypeClassObj::UnRegisterGlobal() {
		dtenv_init();
		{
			::std::lock_guard<wrapper_mtx_dtenv_t> lock_guard_dtenv(wrapper_mtx_dtenv);
			if (!map_dtclassobj->erase(this->dtclassid)) terminate();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE dtenv_init_global() { dtenv_init(); }

	YBWLIB2_API void YBWLIB2_CALLTYPE mtx_dtenv_lock() {
		dtenv_init();
		impl_mtx_dtenv->lock();
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE mtx_dtenv_unlock() {
		dtenv_init();
		impl_mtx_dtenv->unlock();
	}
}
