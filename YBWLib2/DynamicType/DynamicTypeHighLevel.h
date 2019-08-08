#ifndef _INCLUDE_GUARD_7C74AE76_4A99_4CC0_AF82_AD934257D492
#define _INCLUDE_GUARD_7C74AE76_4A99_4CC0_AF82_AD934257D492

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_71C27721_8AF0_49E9_92FA_36788780562F
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_3151B7B3_2887_45BB_98F7_170A5761711D
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <new>
#include <initializer_list>
#include <unordered_map>
#include "../YBWLib2Api.h"
#include "DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	/// <summary>Gets the dynamic object creation function pointer.</summary>
	template<typename _Class_Ty, typename _Iterator_Fnptr_Create_Ty>
	inline DynamicTypeClassObj::fnptr_create_object_t DynamicTypeGetCreateObjectFnptr(
		_Iterator_Fnptr_Create_Ty _it_begin_fnptr_create,
		_Iterator_Fnptr_Create_Ty _it_end_fnptr_create
	) noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		using map_fnptr_create_t = ::std::unordered_map<ConstructorID, _Class_Ty*(YBWLIB2_CALLTYPE*)(IndexedDataStore* _indexeddatastore_parameters) noexcept(false), hash<ConstructorID>>;
		static const map_fnptr_create_t map_fnptr_create(_it_begin_fnptr_create, _it_end_fnptr_create);
		return [](const DynamicTypeClassObj* _dtclassobj, IndexedDataStore* _indexeddatastore_parameters) noexcept->uintptr_t {
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_indexeddatastore_parameters) abort();
			if (_indexeddatastore_parameters->GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid)) abort();
			uintptr_t ret = 0;
			IException* err = WrapFunctionCatchExceptions([&_dtclassobj, &_indexeddatastore_parameters, &ret]() noexcept(false)->void {
				typename map_fnptr_create_t::const_iterator it_map_fnptr_create = map_fnptr_create.find(ConstructorIDParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).ctorid);
				if (it_map_fnptr_create == map_fnptr_create.cend()) throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
				if (!it_map_fnptr_create->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				ret = reinterpret_cast<uintptr_t>((*it_map_fnptr_create->second)(_indexeddatastore_parameters));
				});
			ExceptionReturnParameterIndexedDataEntry::AddToStore(*_indexeddatastore_parameters, ExceptionReturnParameterIndexedDataEntry(::std::move(err)));
			err = nullptr;
			return ret;
		};
	}

	/// <summary>Gets the default dynamic object creation function pointer.</summary>
	template<typename _Class_Ty>
	inline DynamicTypeClassObj::fnptr_create_object_t DynamicTypeGetDefaultCreateObjectFnptr() noexcept {
		static const ::std::initializer_list<::std::pair<PersistentID, _Class_Ty*(YBWLIB2_CALLTYPE*)(IndexedDataStore* _indexeddatastore_parameters) noexcept(false)>> il_fnptr_create(
			{
				{ PersistentID_ConstructorID_Default, [](IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					static_cast<void>(_indexeddatastore_parameters);
					return new _Class_Ty();
				} },
				{ PersistentID_ConstructorID_Copy, [](IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new _Class_Ty(*ptr_obj_from);
				} },
				{ PersistentID_ConstructorID_Move, [](IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new _Class_Ty(::std::move(*ptr_obj_from));
				} }
			}
		);
		return DynamicTypeGetCreateObjectFnptr<_Class_Ty>(il_fnptr_create.begin(), il_fnptr_create.end());
	}

	/// <summary>Gets the dynamic object placement-creation function pointer.</summary>
	template<typename _Class_Ty, typename _Iterator_Fnptr_Placement_Create_Ty>
	inline DynamicTypeClassObj::fnptr_placement_create_object_t DynamicTypeGetPlacementCreateObjectFnptr(
		_Iterator_Fnptr_Placement_Create_Ty _it_begin_fnptr_placement_create,
		_Iterator_Fnptr_Placement_Create_Ty _it_end_fnptr_placement_create
	) noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		using map_fnptr_placement_create_t = ::std::unordered_map<ConstructorID, _Class_Ty*(YBWLIB2_CALLTYPE*)(void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false), hash<ConstructorID>>;
		static const map_fnptr_placement_create_t map_fnptr_placement_create(_it_begin_fnptr_placement_create, _it_end_fnptr_placement_create);
		return [](const DynamicTypeClassObj* _dtclassobj, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept->uintptr_t {
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_ptr_placement || !_indexeddatastore_parameters) abort();
			if (_indexeddatastore_parameters->GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid)) abort();
			uintptr_t ret = 0;
			IException* err = WrapFunctionCatchExceptions([&_dtclassobj, &_ptr_placement, &_indexeddatastore_parameters, &ret]() noexcept(false)->void {
				typename map_fnptr_placement_create_t::const_iterator it_map_fnptr_placement_create = map_fnptr_placement_create.find(ConstructorIDParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).ctorid);
				if (it_map_fnptr_placement_create == map_fnptr_placement_create.cend()) throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
				if (!it_map_fnptr_placement_create->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				ret = reinterpret_cast<uintptr_t>((*it_map_fnptr_placement_create->second)(_ptr_placement, _indexeddatastore_parameters));
				});
			ExceptionReturnParameterIndexedDataEntry::AddToStore(*_indexeddatastore_parameters, ExceptionReturnParameterIndexedDataEntry(::std::move(err)));
			err = nullptr;
			return ret;
		};
	}

	/// <summary>Gets the default dynamic object placement-creation function pointer.</summary>
	template<typename _Class_Ty>
	inline DynamicTypeClassObj::fnptr_placement_create_object_t DynamicTypeGetDefaultPlacementCreateObjectFnptr() noexcept {
		static const ::std::initializer_list<::std::pair<PersistentID, _Class_Ty*(YBWLIB2_CALLTYPE*)(void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)>> il_fnptr_placement_create(
			{
				{ PersistentID_ConstructorID_Default, [](void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					static_cast<void>(_indexeddatastore_parameters);
					return new(_ptr_placement) _Class_Ty();
				} },
				{ PersistentID_ConstructorID_Copy, [](void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new(_ptr_placement) _Class_Ty(*ptr_obj_from);
				} },
				{ PersistentID_ConstructorID_Move, [](void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new(_ptr_placement) _Class_Ty(::std::move(*ptr_obj_from));
				} }
			}
		);
		return DynamicTypeGetPlacementCreateObjectFnptr<_Class_Ty>(il_fnptr_placement_create.begin(), il_fnptr_placement_create.end());
	}

	/// <summary>Gets the default dynamic object deletion function pointer.</summary>
	template<typename _Class_Ty>
	inline constexpr DynamicTypeClassObj::fnptr_delete_object_t DynamicTypeGetDefaultDeleteObjectFnptr() noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		return [](const DynamicTypeClassObj* _dtclassobj, uintptr_t _ptr_obj) noexcept->void {
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_ptr_obj) abort();
			try {
				delete reinterpret_cast<_Class_Ty*>(_ptr_obj);
			} catch (...) {
				abort();
			}
		};
	}
}

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_3151B7B3_2887_45BB_98F7_170A5761711D
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_3151B7B3_2887_45BB_98F7_170A5761711D
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_71C27721_8AF0_49E9_92FA_36788780562F
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_71C27721_8AF0_49E9_92FA_36788780562F
#endif

#endif
