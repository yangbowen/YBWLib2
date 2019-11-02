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
#include "../Common/CommonLowLevel.h"
#include "DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	template<typename _Class_Ty>
	using DynamicTypeClassSpecificCreateObjectDelegate = Delegate<DelegateFlags_None, _Class_Ty*, IndexedDataStore*>;
	template<typename _Class_Ty>
	using DynamicTypeClassSpecificPlacementCreateObjectDelegate = Delegate<DelegateFlags_None, _Class_Ty*, void*, IndexedDataStore*>;

	/// <summary>Gets the dynamic object creation delegate.</summary>
	template<typename _Class_Ty, typename _Iterator_Delegate_Create_Ty>
	inline DynamicTypeClassObj::delegate_create_object_t DynamicTypeGetCreateObjectDelegate(
		_Iterator_Delegate_Create_Ty _it_begin_delegate_create,
		_Iterator_Delegate_Create_Ty _it_end_delegate_create
	) noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		using map_delegate_create_t = ::std::unordered_map<ConstructorID, DynamicTypeClassSpecificCreateObjectDelegate<_Class_Ty>, hash<ConstructorID>>;
		DynamicTypeClassObj::delegate_create_object_t delegate_create_object;
		delegate_create_object.fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, const DynamicTypeClassObj* _dtclassobj, IndexedDataStore* _indexeddatastore_parameters) noexcept->uintptr_t {
			map_delegate_create_t* map_delegate_create = reinterpret_cast<map_delegate_create_t*>(_contextvalue1);
			static_cast<void>(_contextvalue2);
			assert(map_delegate_create);
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_indexeddatastore_parameters) abort();
			if (_indexeddatastore_parameters->GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid)) abort();
			uintptr_t ret = 0;
			IException* err = WrapFunctionCatchExceptions([&_dtclassobj, &_indexeddatastore_parameters, &map_delegate_create, &ret]() noexcept(false)->void {
				typename map_delegate_create_t::const_iterator it_map_delegate_create = map_delegate_create->find(ConstructorIDParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).ctorid);
				if (it_map_delegate_create == map_delegate_create->cend()) throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
				if (!it_map_delegate_create->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				ret = reinterpret_cast<uintptr_t>(it_map_delegate_create->second(_indexeddatastore_parameters));
				});
			ExceptionReturnParameterIndexedDataEntry::AddToStore(*_indexeddatastore_parameters, ExceptionReturnParameterIndexedDataEntry(::std::move(err)));
			err = nullptr;
			return ret;
		};
		{
			void* buf_map_delegate_create = rawallocator_crt_YBWLib2->Allocate(sizeof(map_delegate_create_t), alignof(map_delegate_create_t));
			assert(buf_map_delegate_create);
			map_delegate_create_t* map_delegate_create = new(buf_map_delegate_create) map_delegate_create_t();
			assert(map_delegate_create);
			for (_Iterator_Delegate_Create_Ty it_delegate_create = _it_begin_delegate_create; it_delegate_create != _it_end_delegate_create; ++it_delegate_create) {
				map_delegate_create->emplace(::std::move(*it_delegate_create));
			}
			delegate_create_object.contextvalue1 = reinterpret_cast<uintptr_t>(map_delegate_create);
		}
		delegate_create_object.fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
			map_delegate_create_t* map_delegate_create = reinterpret_cast<map_delegate_create_t*>(_contextvalue1);
			static_cast<void>(_contextvalue2);
			assert(map_delegate_create);
			map_delegate_create->~map_delegate_create_t();
			rawallocator_crt_YBWLib2->Deallocate(map_delegate_create, sizeof(map_delegate_create_t));
		};
		return delegate_create_object;
	}

	/// <summary>Gets the default dynamic object creation delegate.</summary>
	template<typename _Class_Ty>
	inline DynamicTypeClassObj::delegate_create_object_t DynamicTypeGetDefaultCreateObjectDelegate() noexcept {
		static const ::std::initializer_list<::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<_Class_Ty>>> il_delegate_create(
			{
				{ PersistentID_ConstructorID_Default, DynamicTypeClassSpecificCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					static_cast<void>(_indexeddatastore_parameters);
					return new _Class_Ty();
				}) },
				{ PersistentID_ConstructorID_Copy, DynamicTypeClassSpecificCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new _Class_Ty(*ptr_obj_from);
				}) },
				{ PersistentID_ConstructorID_Move, DynamicTypeClassSpecificCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new _Class_Ty(::std::move(*ptr_obj_from));
				}) }
			}
		);
		return DynamicTypeGetCreateObjectDelegate<_Class_Ty>(il_delegate_create.begin(), il_delegate_create.end());
	}

	/// <summary>Gets the dynamic object placement-creation delegate.</summary>
	template<typename _Class_Ty, typename _Iterator_Delegate_Placement_Create_Ty>
	inline DynamicTypeClassObj::delegate_placement_create_object_t DynamicTypeGetPlacementCreateObjectDelegate(
		_Iterator_Delegate_Placement_Create_Ty _it_begin_delegate_placement_create,
		_Iterator_Delegate_Placement_Create_Ty _it_end_delegate_placement_create
	) noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		using map_delegate_placement_create_t = ::std::unordered_map<ConstructorID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<_Class_Ty>, hash<ConstructorID>>;
		DynamicTypeClassObj::delegate_placement_create_object_t delegate_placement_create_object;
		delegate_placement_create_object.fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, const DynamicTypeClassObj* _dtclassobj, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept->uintptr_t {
			map_delegate_placement_create_t* map_delegate_placement_create = reinterpret_cast<map_delegate_placement_create_t*>(_contextvalue1);
			static_cast<void>(_contextvalue2);
			assert(map_delegate_placement_create);
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_ptr_placement || !_indexeddatastore_parameters) abort();
			if (_indexeddatastore_parameters->GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid)) abort();
			uintptr_t ret = 0;
			IException* err = WrapFunctionCatchExceptions([&_dtclassobj, &_ptr_placement, &_indexeddatastore_parameters, &map_delegate_placement_create, &ret]() noexcept(false)->void {
				typename map_delegate_placement_create_t::const_iterator it_map_delegate_placement_create = map_delegate_placement_create->find(ConstructorIDParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).ctorid);
				if (it_map_delegate_placement_create == map_delegate_placement_create->cend()) throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
				if (!it_map_delegate_placement_create->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				ret = reinterpret_cast<uintptr_t>(it_map_delegate_placement_create->second(_ptr_placement, _indexeddatastore_parameters));
				});
			ExceptionReturnParameterIndexedDataEntry::AddToStore(*_indexeddatastore_parameters, ExceptionReturnParameterIndexedDataEntry(::std::move(err)));
			err = nullptr;
			return ret;
		};
		{
			void* buf_map_delegate_placement_create = rawallocator_crt_YBWLib2->Allocate(sizeof(map_delegate_placement_create_t), alignof(map_delegate_placement_create_t));
			assert(buf_map_delegate_placement_create);
			map_delegate_placement_create_t* map_delegate_placement_create = new(buf_map_delegate_placement_create) map_delegate_placement_create_t();
			assert(map_delegate_placement_create);
			for (_Iterator_Delegate_Placement_Create_Ty it_delegate_placement_create = _it_begin_delegate_placement_create; it_delegate_placement_create != _it_end_delegate_placement_create; ++it_delegate_placement_create) {
				map_delegate_placement_create->emplace(::std::move(*it_delegate_placement_create));
			}
			delegate_placement_create_object.contextvalue1 = reinterpret_cast<uintptr_t>(map_delegate_placement_create);
		}
		delegate_placement_create_object.fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
			map_delegate_placement_create_t* map_delegate_placement_create = reinterpret_cast<map_delegate_placement_create_t*>(_contextvalue1);
			static_cast<void>(_contextvalue2);
			assert(map_delegate_placement_create);
			map_delegate_placement_create->~map_delegate_placement_create_t();
			rawallocator_crt_YBWLib2->Deallocate(map_delegate_placement_create, sizeof(map_delegate_placement_create_t));
		};
		return delegate_placement_create_object;
	}

	/// <summary>Gets the default dynamic object placement-creation delegate.</summary>
	template<typename _Class_Ty>
	inline DynamicTypeClassObj::delegate_placement_create_object_t DynamicTypeGetDefaultPlacementCreateObjectDelegate() noexcept {
		static const ::std::initializer_list<::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<_Class_Ty>>> il_delegate_placement_create(
			{
				{ PersistentID_ConstructorID_Default, DynamicTypeClassSpecificPlacementCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					static_cast<void>(_indexeddatastore_parameters);
					return new(_ptr_placement) _Class_Ty();
				}) },
				{ PersistentID_ConstructorID_Copy, DynamicTypeClassSpecificPlacementCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new(_ptr_placement) _Class_Ty(*ptr_obj_from);
				}) },
				{ PersistentID_ConstructorID_Move, DynamicTypeClassSpecificPlacementCreateObjectDelegate<_Class_Ty>([](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->_Class_Ty* {
					if (!_indexeddatastore_parameters) abort();
					_Class_Ty* ptr_obj_from = ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters);
					if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
					return new(_ptr_placement) _Class_Ty(::std::move(*ptr_obj_from));
				}) }
			}
		);
		return DynamicTypeGetPlacementCreateObjectDelegate<_Class_Ty>(il_delegate_placement_create.begin(), il_delegate_placement_create.end());
	}

	/// <summary>Gets the default dynamic object deletion delegate.</summary>
	template<typename _Class_Ty>
	inline constexpr DynamicTypeClassObj::delegate_delete_object_t DynamicTypeGetDefaultDeleteObjectDelegate() noexcept {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified class type is not a dynamic type class.");
		return DynamicTypeClassObj::delegate_delete_object_t([](uintptr_t, uintptr_t, const DynamicTypeClassObj* _dtclassobj, uintptr_t _ptr_obj) noexcept->void {
			if (_dtclassobj != GetDynamicTypeClassObject<_Class_Ty>()) abort();
			if (!_ptr_obj) abort();
			try {
				delete reinterpret_cast<_Class_Ty*>(_ptr_obj);
			} catch (...) {
				abort();
			}
		});
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
