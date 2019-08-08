#ifndef _INCLUDE_GUARD_A2BDBA5D_2D6E_480E_9BB6_7DB0B35F05E2
#define _INCLUDE_GUARD_A2BDBA5D_2D6E_480E_9BB6_7DB0B35F05E2

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <cstdlib>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include "DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	extern YBWLIB2_API ::std::unordered_map<const module_info_t*, DynamicTypeClassObj*(YBWLIB2_CALLTYPE*)(const DynamicTypeClassID* _dtclassid) noexcept>* map_fnptr_FindDynamicTypeClassObject_module;

	static ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash<DynamicTypeClassID>>* map_dtclassobj_module_local = nullptr;

	DynamicTypeClassObj* DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid) noexcept {
		DynamicTypeClassObj* ret = nullptr;
		try {
			if (_dtclassid && *_dtclassid) {
				{
					::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
					::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash<DynamicTypeClassID>>::iterator it_dtclassobj = map_dtclassobj_module_local->find(*_dtclassid);
					if (it_dtclassobj != map_dtclassobj_module_local->end()) ret = &it_dtclassobj->second;
				}
			}
		} catch (...) {
			abort();
		}
		return ret;
	}

	uintptr_t DynamicTypeClassObj::CreateObject(const DynamicTypeClassObj* _dtclassobj_base, IndexedDataStore& _indexeddatastore_parameters) const noexcept {
		if (!_dtclassobj_base || !this->fnptr_create_object) abort();
		bool has_parameter_ptr_obj_from = false;
		uintptr_t ptr_obj_from_base = 0;
		if (_indexeddatastore_parameters.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid)) {
			has_parameter_ptr_obj_from = true;
			static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
			ptr_obj_from_base = objholder_local_t<ObjectPointerFromParameterIndexedDataEntry>(
				[&_indexeddatastore_parameters](void* ptr_placement) noexcept->ObjectPointerFromParameterIndexedDataEntry* {
					ObjectPointerFromParameterIndexedDataEntry* ptr_obj = ObjectPointerFromParameterIndexedDataEntry::MoveFromStore(_indexeddatastore_parameters, ptr_placement);
					if (!ptr_obj) abort();
					return ptr_obj;
				}
			)->uintptr_ptr_obj;
			if (!ptr_obj_from_base) abort();
			IDynamicTypeObject* ptr_obj_from_iobject = reinterpret_cast<IDynamicTypeObject*>(_dtclassobj_base->DynamicUpcastTo(ptr_obj_from_base, GetDynamicTypeClassObject<IDynamicTypeObject>()));
			if (!ptr_obj_from_iobject) abort();
			uintptr_t ptr_obj_from_derived = ptr_obj_from_iobject->DynamicTypeRawCastTo(this);
			if (!ptr_obj_from_derived) abort();
			ObjectPointerFromParameterIndexedDataEntry::AddToStore(_indexeddatastore_parameters, ObjectPointerFromParameterIndexedDataEntry(ptr_obj_from_derived));
		}
		uintptr_t ptr_obj_derived = (*this->fnptr_create_object)(this, &_indexeddatastore_parameters);
		uintptr_t ret = 0;
		if (ptr_obj_derived) {
			uintptr_t ptr_obj_base = this->DynamicUpcastTo(ptr_obj_derived, _dtclassobj_base);
			if (!ptr_obj_base) abort();
			ret = ptr_obj_base;
		}
		if (has_parameter_ptr_obj_from) {
			if (_indexeddatastore_parameters.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid)) {
				ObjectPointerFromParameterIndexedDataEntry::RemoveFromStore(_indexeddatastore_parameters);
				ObjectPointerFromParameterIndexedDataEntry::AddToStore(_indexeddatastore_parameters, ObjectPointerFromParameterIndexedDataEntry(ptr_obj_from_base));
			}
		}
		return ret;
	}

	uintptr_t DynamicTypeClassObj::PlacementCreateObject(const DynamicTypeClassObj* _dtclassobj_base, void* _ptr_placement, IndexedDataStore& _indexeddatastore_parameters) const noexcept {
		if (!_dtclassobj_base || !this->fnptr_placement_create_object) abort();
		bool has_parameter_ptr_obj_from = false;
		uintptr_t ptr_obj_from_base = 0;
		if (_indexeddatastore_parameters.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid)) {
			has_parameter_ptr_obj_from = true;
			static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
			ptr_obj_from_base = objholder_local_t<ObjectPointerFromParameterIndexedDataEntry>(
				[&_indexeddatastore_parameters](void* ptr_placement) noexcept->ObjectPointerFromParameterIndexedDataEntry* {
					ObjectPointerFromParameterIndexedDataEntry* ptr_obj = ObjectPointerFromParameterIndexedDataEntry::MoveFromStore(_indexeddatastore_parameters, ptr_placement);
					if (!ptr_obj) abort();
					return ptr_obj;
				}
			)->uintptr_ptr_obj;
			if (!ptr_obj_from_base) abort();
			IDynamicTypeObject* ptr_obj_from_iobject = reinterpret_cast<IDynamicTypeObject*>(_dtclassobj_base->DynamicUpcastTo(ptr_obj_from_base, GetDynamicTypeClassObject<IDynamicTypeObject>()));
			if (!ptr_obj_from_iobject) abort();
			uintptr_t ptr_obj_from_derived = ptr_obj_from_iobject->DynamicTypeRawCastTo(this);
			if (!ptr_obj_from_derived) abort();
			ObjectPointerFromParameterIndexedDataEntry::AddToStore(_indexeddatastore_parameters, ObjectPointerFromParameterIndexedDataEntry(ptr_obj_from_derived));
		}
		uintptr_t ptr_obj_derived = (*this->fnptr_placement_create_object)(this, _ptr_placement, &_indexeddatastore_parameters);
		uintptr_t ret = 0;
		if (ptr_obj_derived) {
			uintptr_t ptr_obj_base = this->DynamicUpcastTo(ptr_obj_derived, _dtclassobj_base);
			if (!ptr_obj_base) abort();
			ret = ptr_obj_base;
		}
		if (has_parameter_ptr_obj_from) {
			if (_indexeddatastore_parameters.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid)) {
				ObjectPointerFromParameterIndexedDataEntry::RemoveFromStore(_indexeddatastore_parameters);
				ObjectPointerFromParameterIndexedDataEntry::AddToStore(_indexeddatastore_parameters, ObjectPointerFromParameterIndexedDataEntry(ptr_obj_from_base));
			}
		}
		return ret;
	}

	void DynamicTypeClassObj::DeleteObject(const DynamicTypeClassObj* _dtclassobj_base, uintptr_t _ptr_obj) const noexcept {
		if (!_dtclassobj_base || !this->fnptr_delete_object) abort();
		IDynamicTypeObject* ptr_obj_iobject = reinterpret_cast<IDynamicTypeObject*>(_dtclassobj_base->DynamicUpcastTo(_ptr_obj, GetDynamicTypeClassObject<IDynamicTypeObject>()));
		if (!ptr_obj_iobject) abort();
		uintptr_t ptr_obj_derived = ptr_obj_iobject->DynamicTypeRawCastTo(this);
		if (!ptr_obj_derived) abort();
		(*this->fnptr_delete_object)(this, ptr_obj_derived);
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

	ConstructorIDParameterIndexedDataEntry ConstructorIDParameterIndexedDataEntry::CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false) {
		const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			return ConstructorIDParameterIndexedDataEntry(*_indexeddatarawvalue);
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	ConstructorIDParameterIndexedDataEntry ConstructorIDParameterIndexedDataEntry::MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false) {
		IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			ConstructorIDParameterIndexedDataEntry ret(ConstructorIDParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue)));
			_indexeddatastore.RemoveEntryByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
			return ret;
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	ObjectPointerFromParameterIndexedDataEntry ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false) {
		const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			return ObjectPointerFromParameterIndexedDataEntry(*_indexeddatarawvalue);
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	ObjectPointerFromParameterIndexedDataEntry ObjectPointerFromParameterIndexedDataEntry::MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false) {
		IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			ObjectPointerFromParameterIndexedDataEntry ret(ObjectPointerFromParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue)));
			_indexeddatastore.RemoveEntryByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
			return ret;
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	void YBWLIB2_CALLTYPE DynamicType_RealInitModuleLocal() noexcept {
		if (!map_fnptr_FindDynamicTypeClassObject_module) abort();
		if (!map_fnptr_FindDynamicTypeClassObject_module->emplace(
			module_info_current,
			[](const DynamicTypeClassID* _dtclassid) noexcept->DynamicTypeClassObj* {
				return DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(_dtclassid);
			}
		).second) abort();
		map_dtclassobj_module_local = new ::std::unordered_map<DynamicTypeClassID, DynamicTypeClassObj&, hash<DynamicTypeClassID>>();
		if (!map_dtclassobj_module_local) abort();
		GetDynamicTypeClassObject<IDynamicTypeObject>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IDynamicTypeObject)), module_info_current);
	}

	void YBWLIB2_CALLTYPE DynamicType_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<IDynamicTypeObject>()->UnRegisterTypeInfoWrapper(module_info_current);
		if (!map_dtclassobj_module_local->empty()) abort();
		delete map_dtclassobj_module_local;
		map_dtclassobj_module_local = nullptr;
		map_fnptr_FindDynamicTypeClassObject_module->erase(module_info_current);
	}
}

#endif
