#ifndef _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263
#define _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <new>
#include <initializer_list>
#include <mutex>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"

namespace YBWLib2 {
	struct DynamicTypeClassID;
	class DynamicTypeClassObj;
	class DynamicTypeBaseClassDefObj;
	class IDynamicTypeObject;
	class _impl_DynamicTypeClassObj;

#pragma region DynamicTypeClassID
	//{ DynamicTypeClassID

	/// <summary>Unique identifier used to identify a dynamic type class.</summary>
	struct DynamicTypeClassID : public VolatileID {
		constexpr DynamicTypeClassID() noexcept = default;
		explicit DynamicTypeClassID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit DynamicTypeClassID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit DynamicTypeClassID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		DynamicTypeClassID(const DynamicTypeClassID& x) noexcept = default;
		DynamicTypeClassID(DynamicTypeClassID&& x) noexcept = default;
		~DynamicTypeClassID() = default;
		DynamicTypeClassID& operator=(const DynamicTypeClassID& x) noexcept = default;
		DynamicTypeClassID& operator=(DynamicTypeClassID&& x) noexcept = default;
		bool operator==(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const DynamicTypeClassID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<DynamicTypeClassID>, "DynamicTypeClassID is not standard-layout.");
}

namespace std {
	template<>
	struct hash<::YBWLib2::DynamicTypeClassID> {
		inline size_t operator()(const ::YBWLib2::DynamicTypeClassID& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
	//}
#pragma endregion DynamicTypeClassID is used to uniquely identify a dynamic type class. Keep in mind that module-local dynamic type classes can have the same DynamicTypeClassID in different executable modules.

	/// <summary><c>wrapper_lockable_t</c> object that controls the dynamic type environment.</summary>
	extern YBWLIB2_API wrapper_lockable_t* wrapper_lockable_dtenv;

	/// <summary>Function pointer type for upcasting a pointer from one dynamic type class to another.</summary>
	typedef uintptr_t(YBWLIB2_CALLTYPE* fnptr_dynamic_type_upcast_t)(uintptr_t ptr_from, const DynamicTypeClassObj* dtclassobj_from, const DynamicTypeBaseClassDefObj* dtbaseclassdef) noexcept;

#pragma region Dynamic type class declaration getting templates
	//{ Dynamic Type declaration getting templates.

	/// <summary>
	/// Checks whether the specified class type has been (explicitly) declared not a dynamic type class.
	/// Use this template function instead of directly referencing the <c>DynamicTypeNoClass</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the no-class boolean as the static member variable <c>DynamicTypeNoClass</c>.
	/// </summary>
	template<typename T_Class>
	inline constexpr bool IsDynamicTypeNoClass() {
		static_assert(::std::is_class_v<T_Class>, "The specified type is not a class.");
		return T_Class::DynamicTypeNoClass;
	}
	/// <summary>
	/// Checks whether the specified class type has been declared module-local.
	/// Module-local classes have per-module dynamic type class objects, so these classes can share definitions between modules while being binary-incompatible.
	/// Module-local classes can inherit from non-module-local classes, but non-module-local classes CANNOT inherit from module-local classes.
	/// Use this template function instead of directly referencing the <c>DynamicTypeModuleLocalClass</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the module-local boolean as the static member variable <c>DynamicTypeModuleLocalClass</c>.
	/// </summary>
	template<typename T_Class>
	inline constexpr bool IsDynamicTypeModuleLocalClass() {
		static_assert(::std::is_class_v<T_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class>(), "The specified type is not a dynamic type class.");
		return T_Class::DynamicTypeModuleLocalClass;
	}
	/// <summary>
	/// Gets a pointer to the <c>DynamicTypeClassObj</c> object that represents the specified class type.
	/// Use this template function instead of directly referencing the <c>DynamicTypeThisClassObject</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the pointer to the <c>DynamicTypeClassObj</c> object as the static member variable <c>DynamicTypeThisClassObject</c>.
	/// </summary>
	template<typename T_Class>
	inline constexpr DynamicTypeClassObj* GetDynamicTypeClassObject() {
		static_assert(::std::is_class_v<T_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class>(), "The specified type is not a dynamic type class.");
		return T_Class::DynamicTypeThisClassObject;
	}
	/// <summary>
	/// Gets a reference to the <c>PersistentID</c> identifier that persistently identifies the specified class type.
	/// Use this template function instead of directly referencing the <c>DynamicTypeThisClassPersistentID</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the <c>PersistentID</c> identifier as the static member variable <c>DynamicTypeThisClassPersistentID</c>.
	/// Notice that this identifier must be either <c>constexpr</c> or statically initialized, so that it's available before global constructors get executed.
	/// </summary>
	template<typename T_Class>
	inline constexpr const PersistentID& GetDynamicTypeClassPersistentID() {
		static_assert(::std::is_class_v<T_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class>(), "The specified type is not a dynamic type class.");
		return T_Class::DynamicTypeThisClassPersistentID;
	}
	/// <summary>Gets a reference to the <c>DynamicTypeClassID</c> identifier that identifies the specified class type.</summary>
	template<typename T_Class>
	inline constexpr const DynamicTypeClassID& GetDynamicTypeClassID() {
		static_assert(::std::is_class_v<T_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class>(), "The specified type is not a dynamic type class.");
		DynamicTypeClassObj* dtclassobj = GetDynamicTypeClassObject<T_Class>();
		assert(dtclassobj);
		return dtclassobj->GetDynamicTypeClassID();
	}
	/// <summary>
	/// Gets a function pointer to a function that statically casts a pointer from one dynamic type class to another.
	/// Provide specializations for this template to support classes that implement custom static type cast mechanism.
	/// </summary>
	template<typename T_Class_To, typename T_Class_From>
	inline fnptr_dynamic_type_upcast_t DynamicTypeGetStaticCastFnptr() {
		static_assert(::std::is_class_v<T_Class_To>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_To>(), "The specified type is not a dynamic type class.");
		static_assert(::std::is_class_v<T_Class_From>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_From>(), "The specified type is not a dynamic type class.");
		return [](uintptr_t ptr_from, const DynamicTypeClassObj* dtclassobj_from, const DynamicTypeBaseClassDefObj* dtbaseclassdef) noexcept->uintptr_t {
			static_cast<void>(dtclassobj_from);
			static_cast<void>(dtbaseclassdef);
			return reinterpret_cast<uintptr_t>(static_cast<T_Class_To*>(reinterpret_cast<T_Class_From*>(ptr_from)));
		};
	}

	//}
#pragma endregion These templates are used for getting various declarations in dynamic type classes.

#pragma region DynamicTypeClassObj
	//{ DynamicTypeClassObj

	/// <summary>
	/// Dynamic type class.
	/// Only construct this object during executable module initialization and destruct this object during executable module cleanup.
	/// </summary>
	class DynamicTypeClassObj final {
		friend _impl_DynamicTypeClassObj;
	public:
		/// <summary>
		/// Delegate type for dynamically creating object.
		/// A pointer to the created object, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>, should be returned.
		/// The type of the pointer is a pointer to the class represented by the dynamic type class object pointed to by the <c>const DynamicTypeClassObj*</c> parameter.
		/// If the object creation has failed, <c>0</c> should be returned, and the delegate may pass additional error information in <c>_indexeddatastore_parameters</c>.
		/// </summary>
		using delegate_create_object_t = Delegate<DelegateFlag_Noexcept, uintptr_t, const DynamicTypeClassObj*, IndexedDataStore*>;
		/// <summary>Delegate type for dynamically placement-creating object.
		/// A pointer to the created object, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>, should be returned.
		/// The type of the pointer is a pointer to the class represented by the dynamic type class object pointed to by the <c>const DynamicTypeClassObj*</c> parameter.
		/// If the object creation has failed, <c>0</c> should be returned, and the function may pass additional error information in <c>_indexeddatastore_parameters</c>.
		/// </summary>
		using delegate_placement_create_object_t = Delegate<DelegateFlag_Noexcept, uintptr_t, const DynamicTypeClassObj*, void*, IndexedDataStore*>;
		/// <summary>
		/// Delegate type for dynamically deleting object.
		/// A pointer to object, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>, is passed.
		/// The type of the pointer is a pointer to the class represented by the dynamic type class object pointed to by the <c>const DynamicTypeClassObj*</c> parameter.
		/// </summary>
		using delegate_delete_object_t = Delegate<DelegateFlag_Noexcept, void, const DynamicTypeClassObj*, uintptr_t>;
		/// <summary>Finds a registered non-module-local dynamic type class object with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if there isn't a non-module-local dynamic type class object with the specified identifier registered), it returns an empty pointer.
		/// </returns>
		static YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE FindDynamicTypeClassObjectGlobal(const DynamicTypeClassID* _dtclassid) noexcept;
		/// <summary>Finds a registered module-local dynamic type class object with the specified <c>DynamicTypeClassID</c> identifier in the specified module.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if there isn't a non-module-local dynamic type class object with the specified identifier registered), it returns an empty pointer.
		/// </returns>
		static YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE FindDynamicTypeClassObjectSpecifiedModule(const module_info_t* _module_info, const DynamicTypeClassID* _dtclassid) noexcept;
		/// <summary>Finds a registered module-local dynamic type class object with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if there isn't a module-local dynamic type class object with the specified identifier registered), it returns an empty pointer.
		/// </returns>
		static DynamicTypeClassObj* FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid) noexcept;
		inline DynamicTypeClassObj(
			const PersistentID& _persistentid_dtclassid,
			bool _is_module_local,
			::std::initializer_list<DynamicTypeBaseClassDefObj> _dtbaseclassdef,
			size_t _extent_before,
			size_t _extent_after,
			size_t _alignment,
			delegate_create_object_t&& _delegate_create_object = delegate_create_object_t(),
			delegate_placement_create_object_t&& _delegate_placement_create_object = delegate_placement_create_object_t(),
			delegate_delete_object_t&& _delegate_delete_object = delegate_delete_object_t()
		)
			: dtclassid(_persistentid_dtclassid),
			is_module_local(_is_module_local),
			extent_before(_extent_before),
			extent_after(_extent_after),
			alignment(_alignment),
			delegate_create_object(::std::move(_delegate_create_object)),
			delegate_placement_create_object(::std::move(_delegate_placement_create_object)),
			delegate_delete_object(::std::move(_delegate_delete_object)) {
			this->CreateImplObject(_dtbaseclassdef.begin(), _dtbaseclassdef.end());
			if (_persistentid_dtclassid != PersistentID()) this->Register();
		}
		DynamicTypeClassObj(const DynamicTypeClassObj&) = delete;
		DynamicTypeClassObj(DynamicTypeClassObj&&) = delete;
		inline ~DynamicTypeClassObj() {
			if (this->dtclassid != PersistentID()) this->UnRegister();
			this->DestroyImplObject();
		}
		DynamicTypeClassObj& operator=(const DynamicTypeClassObj&) = delete;
		DynamicTypeClassObj& operator=(DynamicTypeClassObj&&) = delete;
		inline const DynamicTypeClassID& GetDynamicTypeClassID() const noexcept { return this->dtclassid; }
		inline bool IsModuleLocal() const noexcept { return this->is_module_local; }
		/// <summary>Gets a pointer to the <c>wrapper_type_info_t</c> object that represents the type of this dynamic type class in the specified module.</summary>
		/// <param name="_module_info">Pointer to the <c>module_info</c> object that represents the specified module.</param>
		/// <returns>
		/// This function returns a pointer to the <c>wrapper_type_info_t</c> object if successful.
		/// Otherwise (if this class doesn't have a <c>wrapper_type_info_t</c> object registered in the specified module), it returns an empty pointer.
		/// </returns>
		YBWLIB2_API const wrapper_type_info_t* YBWLIB2_CALLTYPE GetTypeInfoWrapper(const module_info_t* _module_info) const noexcept;
		/// <summary>Finds a dynamic type base class of this class with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if this class doesn't have a dynamic type base class with the specified identifier), it returns an empty pointer.
		/// </returns>
		YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE FindBaseClassObject(const DynamicTypeClassID* dtclassid_base) const;
		/// <summary>Dynamically upcasts a pointer.</summary>
		YBWLIB2_API uintptr_t YBWLIB2_CALLTYPE DynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const;
		/// <summary>Checks whether a pointer can be dynamically upcasted.</summary>
		YBWLIB2_API bool YBWLIB2_CALLTYPE CanDynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const;
		/// <summary>
		/// Returns the alignment (in bytes) of the object.
		/// The position pointed to by the pointer to the object, instead of the beginning of the memory that the object occupies, is aligned.
		/// </summary>
		inline size_t GetAlignment() const noexcept { return this->alignment; }
		/// <summary>
		/// Returns the size (in bytes) of the part of the memory that the object occupies before the position pointed to by the pointer to the object.
		/// This is usually <c>0</c>. But don't assume it's <c>0</c> unless guranteed by other means.
		/// If <c>ptr</c> points to the object, the object occupies [ <c>ptr - this->GetExtentBefore()</c>, <c>ptr + this->GetExtentAfter()</c> ).
		/// </summary>
		inline size_t GetExtentBefore() const noexcept { return this->extent_before; }
		/// <summary>
		/// Returns the size (in bytes) of the part of the memory that the object occupies after the position pointed to by the pointer to the object.
		/// This is usually the value returned by the <c>sizeof</c> operator used on the type.
		/// If <c>ptr</c> points to the object, the object occupies [ <c>ptr - this->GetExtentBefore()</c>, <c>ptr + this->GetExtentAfter()</c> ).
		/// </summary>
		inline size_t GetExtentAfter() const noexcept { return this->extent_after; }
		/// <summary>Dynamically creates object of this class.</summary>
		/// <param name="_dtclassobj_base">A pointer to the <c>DynamicTypeClassObj</c> object that represents the base class the pointer to which is passed.</param>
		/// <param name="_indexeddatastore_parameters">
		/// A pointer to an indexed data store that contains creation parameters.
		/// Dynamic type classes may define parameters to be used.
		/// The constructor is identified by a <c>ConstructorID</c> passed as an entry using <c>ConstructorIDParameterIndexedDataEntry</c>.
		/// If an exception has occurred during object creation, it's returned as an entry using <c>ExceptionReturnParameterIndexedDataEntry</c>.
		/// If the entry represented by <c>ObjectPointerFromParameterIndexedDataEntry</c> exists, its value (the pointer) will be temporarily casted to a pointer to the derived object.
		/// </param>
		/// <returns>
		/// A pointer to the created object, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>.
		/// The type of the pointer is a pointer to the class represented by <paramref name="_dtclassobj_base" />.
		/// If the object creation has failed, <c>0</c> is returned, and the function may pass additional error information in <c>_indexeddatastore_parameters</c>.
		/// </returns>
		uintptr_t CreateObject(const DynamicTypeClassObj* _dtclassobj_base, IndexedDataStore& _indexeddatastore_parameters) const noexcept;
		/// <summary>Dynamically placement-creates object of this class.</summary>
		/// <param name="_dtclassobj_base">A pointer to the <c>DynamicTypeClassObj</c> object that represents the base class the pointer to which is passed.</param>
		/// <param name="_ptr_placement">A pointer to the memory position at which the object is requested to be placement-created.</param>
		/// <param name="_indexeddatastore_parameters">
		/// A pointer to an indexed data store that contains creation parameters.
		/// Dynamic type classes may define parameters to be used.
		/// The constructor is identified by a <c>ConstructorID</c> passed as an entry using <c>ConstructorIDParameterIndexedDataEntry</c>.
		/// If an exception has occurred during object creation, it's returned as an entry using <c>ExceptionReturnParameterIndexedDataEntry</c>.
		/// If the entry represented by <c>ObjectPointerFromParameterIndexedDataEntry</c> exists, its value (the pointer) will be temporarily casted to a pointer to the derived object.
		/// </param>
		/// <returns>
		/// A pointer to the created object, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>.
		/// The type of the pointer is a pointer to the class represented by <paramref name="_dtclassobj_base" />.
		/// If the object creation has failed, <c>0</c> is returned, and the function may pass additional error information in <c>_indexeddatastore_parameters</c>.
		/// </returns>
		uintptr_t PlacementCreateObject(const DynamicTypeClassObj* _dtclassobj_base, void* _ptr_placement, IndexedDataStore& _indexeddatastore_parameters) const noexcept;
		/// <summary>Dynamically deletes object of this class.</summary>
		/// <param name="_dtclassobj_base">A pointer to the <c>DynamicTypeClassObj</c> object that represents the base class the pointer to which is passed.</param>
		/// <param name="_ptr_obj">
		/// A pointer to the object that is requested to be deleted, <c>reinterpret_cast</c>ed to <c>uintptr_t</c>.
		/// The type of the pointer is a pointer to the class represented by <paramref name="_dtclassobj_base" />.
		/// </param>
		void DeleteObject(const DynamicTypeClassObj* _dtclassobj_base, uintptr_t _ptr_obj) const noexcept;
		/// <summary>Registers a <c>wrapper_type_info_t</c> object that represents the type of this dynamic type class in the specified module.</summary>
		/// <param name="_wrapper_type_info">Pointer to a <c>wrapper_type_info_t</c> object that represents the type.</param>
		/// <param name="_module_info">Pointer to the <c>module_info</c> object that represents the specified module.</param>
		YBWLIB2_API void YBWLIB2_CALLTYPE RegisterTypeInfoWrapper(const wrapper_type_info_t* _wrapper_type_info, const module_info_t* _module_info) noexcept;
		/// <summary>Registers a <c>wrapper_type_info_t</c> object that represents the type of this dynamic type class in the specified module.</summary>
		/// <param name="_wrapper_type_info">Reference to a <c>wrapper_type_info_t</c> object that represents the type.</param>
		/// <param name="_module_info">Pointer to the <c>module_info</c> object that represents the specified module.</param>
		inline void RegisterTypeInfoWrapper(const wrapper_type_info_t& _wrapper_type_info, const module_info_t* _module_info) noexcept { this->RegisterTypeInfoWrapper(&_wrapper_type_info, _module_info); }
		/// <summary>Unregisters the <c>wrapper_type_info_t</c> object that represents the type of this dynamic type class in the specified module.</summary>
		/// <param name="_module_info">Pointer to the <c>module_info</c> object that represents the specified module.</param>
		YBWLIB2_API void YBWLIB2_CALLTYPE UnRegisterTypeInfoWrapper(const module_info_t* _module_info) noexcept;
	protected:
		const DynamicTypeClassID dtclassid;
		const bool is_module_local;
		/// <summary>Pointer to the implementation object.</summary>
		_impl_DynamicTypeClassObj* pimpl = nullptr;
		/// <summary>
		/// The alignment (in bytes) of the object.
		/// The position pointed to by the pointer to the object, instead of the beginning of the memory that the object occupies, is aligned.
		/// </summary>
		size_t alignment;
		/// <summary>
		/// The size (in bytes) of the part of the memory that the object occupies before the position pointed to by the pointer to the object.
		/// This is usually <c>0</c>. But don't assume it's <c>0</c> unless guranteed by other means.
		/// If <c>ptr</c> points to the object, the object occupies [ <c>ptr - this->extent_before</c>, <c>ptr + this->extent_after</c> ).
		/// </summary>
		size_t extent_before;
		/// <summary>
		/// The size (in bytes) of the part of the memory that the object occupies after the position pointed to by the pointer to the object.
		/// This is usually the value returned by the <c>sizeof</c> operator used on the type.
		/// If <c>ptr</c> points to the object, the object occupies [ <c>ptr - this->extent_before</c>, <c>ptr + this->extent_after</c> ).
		/// </summary>
		size_t extent_after;
		delegate_create_object_t delegate_create_object;
		delegate_placement_create_object_t delegate_placement_create_object;
		delegate_delete_object_t delegate_delete_object;
	private:
		YBWLIB2_API void YBWLIB2_CALLTYPE CreateImplObject(const DynamicTypeBaseClassDefObj* _begin_dtbaseclassdef, const DynamicTypeBaseClassDefObj* _end_dtbaseclassdef);
		YBWLIB2_API void YBWLIB2_CALLTYPE DestroyImplObject();
		YBWLIB2_API void YBWLIB2_CALLTYPE RegisterGlobal();
		YBWLIB2_API void YBWLIB2_CALLTYPE UnRegisterGlobal();
		void RegisterModuleLocal();
		void UnRegisterModuleLocal();
		inline void Register() {
			if (this->is_module_local)
				this->RegisterModuleLocal();
			else
				this->RegisterGlobal();
		}
		inline void UnRegister() {
			if (this->is_module_local)
				this->UnRegisterModuleLocal();
			else
				this->UnRegisterGlobal();
		}
	};
	static_assert(::std::is_standard_layout_v<DynamicTypeClassObj>, "DynamicTypeClassObj is not standard-layout.");

	//}
#pragma endregion DynamicTypeClassObj is used to represent a dynamic type class.

#pragma region DynamicTypeBaseClassDefObj
	//{ DynamicTypeBaseClassDefObj

	/// <summary>Dynamic type base class flags.</summary>
	typedef uint64_t DynamicTypeBaseClassFlags;

	// Dynamic type base class flag definitions:
	/// <summary>
	/// Dynamic type base class flag:
	/// The base class is a virtual base class.
	/// </summary>
	constexpr DynamicTypeBaseClassFlags DynamicTypeBaseClassFlag_VirtualBase = 0x1;

	/// <summary>
	/// Base class definition object for dynamic type classes.
	/// Only construct this object during executable module initialization and destruct this object during executable module cleanup.
	/// </summary>
	class DynamicTypeBaseClassDefObj final {
	public:
		inline DynamicTypeBaseClassDefObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, DynamicTypeBaseClassFlags _dtbaseclassflags, fnptr_dynamic_type_upcast_t _fnptr_dynamic_type_static_upcast) noexcept
			: dtclassid(_dtclassid),
			is_module_local(_is_module_local),
			module_info(_is_module_local ? module_info_current : nullptr),
			dtbaseclassflags(_dtbaseclassflags),
			fnptr_dynamic_type_static_upcast(_fnptr_dynamic_type_static_upcast) {
			if (this->dtclassid == PersistentID()) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectSpecifiedModule(this->module_info, &this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline DynamicTypeBaseClassDefObj(const DynamicTypeBaseClassDefObj& x) noexcept
			: dtclassid(x.dtclassid),
			is_module_local(x.is_module_local),
			module_info(x.module_info),
			dtbaseclassflags(x.dtbaseclassflags),
			fnptr_dynamic_type_static_upcast(x.fnptr_dynamic_type_static_upcast) {
			if (this->dtclassid == PersistentID()) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectSpecifiedModule(this->module_info, &this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj&& x) noexcept
			: dtclassid(x.dtclassid),
			is_module_local(x.is_module_local),
			module_info(x.module_info),
			dtbaseclassflags(x.dtbaseclassflags),
			fnptr_dynamic_type_static_upcast(x.fnptr_dynamic_type_static_upcast) {
			if (this->dtclassid == PersistentID()) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectSpecifiedModule(this->module_info, &this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline ~DynamicTypeBaseClassDefObj() = default;
		inline DynamicTypeBaseClassDefObj& operator=(const DynamicTypeBaseClassDefObj&) = delete;
		inline DynamicTypeBaseClassDefObj& operator=(DynamicTypeBaseClassDefObj&&) = delete;
		inline bool operator==(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid == r.dtclassid; }
		inline bool operator!=(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid != r.dtclassid; }
		inline bool operator<(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid < r.dtclassid; }
		inline bool operator<=(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid <= r.dtclassid; }
		inline bool operator>(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid > r.dtclassid; }
		inline bool operator>=(const DynamicTypeBaseClassDefObj& r) const { return this->dtclassid >= r.dtclassid; }
		inline size_t hash() const noexcept { return this->dtclassid.hash(); }
		inline const DynamicTypeClassID& GetDynamicTypeClassID() const noexcept { return this->dtclassid; }
		inline bool IsModuleLocal() const noexcept { return this->is_module_local; }
		inline DynamicTypeBaseClassFlags GetDynamicTypeBaseClassFlags() const noexcept { return this->dtbaseclassflags; }
		inline DynamicTypeClassObj* GetDynamicTypeClassObject() const { return this->dtclassobj; }
		inline fnptr_dynamic_type_upcast_t GetDynamicTypeStaticCastFnptr() const noexcept { return this->fnptr_dynamic_type_static_upcast; }
	protected:
		const DynamicTypeClassID dtclassid;
		const bool is_module_local;
		const module_info_t* const module_info;
		const DynamicTypeBaseClassFlags dtbaseclassflags;
		DynamicTypeClassObj* dtclassobj = nullptr;
		fnptr_dynamic_type_upcast_t fnptr_dynamic_type_static_upcast = nullptr;
	};
	static_assert(::std::is_standard_layout_v<DynamicTypeBaseClassDefObj>, "DynamicTypeBaseClassDefObj is not standard-layout.");
}

namespace std {
	template<>
	struct hash<::YBWLib2::DynamicTypeBaseClassDefObj> {
		inline size_t operator()(const ::YBWLib2::DynamicTypeBaseClassDefObj& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
	//}
#pragma endregion DynamicTypeBaseClassDefObj is used to represent a base class definition in a dynamic type class.

#pragma region Dynamic object creation
	//{ Dynamic object creation

	/// <summary>
	/// Unique identifier used to identify a constructor.
	/// Constructors in different classes may have the same constructor ID.
	/// </summary>
	struct ConstructorID : public VolatileID {
		constexpr ConstructorID() noexcept = default;
		explicit ConstructorID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit ConstructorID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit ConstructorID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		ConstructorID(const ConstructorID& x) noexcept = default;
		ConstructorID(ConstructorID&& x) noexcept = default;
		~ConstructorID() = default;
		ConstructorID& operator=(const ConstructorID& x) noexcept = default;
		ConstructorID& operator=(ConstructorID&& x) noexcept = default;
		bool operator==(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const ConstructorID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<ConstructorID>, "ConstructorID is not standard-layout.");
}

namespace std {
	template<>
	struct hash<::YBWLib2::ConstructorID> {
		inline size_t operator()(const ::YBWLib2::ConstructorID& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
	/// <summary>
	/// Default constructor.
	/// No additional parameters are defined.
	/// </summary>
	constexpr PersistentID PersistentID_ConstructorID_Default = PersistentID(UUIDFromUUIDString_CompileTime("47b6f6f3-0981-4475-85b6-72c9ea1ed269"));
	/// <summary>
	/// Copy constructor.
	/// The pointer to the object to be copied from is passed as a parameter using <c>ObjectPointerFromParameterIndexedDataEntry</c>.
	/// </summary>
	constexpr PersistentID PersistentID_ConstructorID_Copy = PersistentID(UUIDFromUUIDString_CompileTime("c3cee6f1-891a-4a77-85bf-47e3eaf06ee2"));
	/// <summary>
	/// Move constructor.
	/// The pointer to the object to be moved from is passed as a parameter using <c>ObjectPointerFromParameterIndexedDataEntry</c>.
	/// </summary>
	constexpr PersistentID PersistentID_ConstructorID_Move = PersistentID(UUIDFromUUIDString_CompileTime("d554cab4-ecc4-43f6-9171-bb4ba483de05"));
	/// <summary>
	/// Default constructor.
	/// No additional parameters are defined.
	/// </summary>
	extern YBWLIB2_API ConstructorID ConstructorID_Default;
	/// <summary>
	/// Copy constructor.
	/// The pointer to the object to be copied from is passed as a parameter using <c>ObjectPointerFromParameterIndexedDataEntry</c>.
	/// </summary>
	extern YBWLIB2_API ConstructorID ConstructorID_Copy;
	/// <summary>
	/// Move constructor.
	/// The pointer to the object to be moved from is passed as a parameter using <c>ObjectPointerFromParameterIndexedDataEntry</c>.
	/// </summary>
	extern YBWLIB2_API ConstructorID ConstructorID_Move;

	class ConstructorIDParameterIndexedDataEntry final {
	public:
		static constexpr PersistentID persistentid_entryid = PersistentID(UUIDFromUUIDString_CompileTime("1ad0e374-8406-40c9-86f5-1f686ca45a03"));
		static YBWLIB2_API IndexedDataEntryID entryid;
		inline static ConstructorIDParameterIndexedDataEntry* CopyFromStore(const IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				return new(_ptr_placement) ConstructorIDParameterIndexedDataEntry(*_indexeddatarawvalue);
			} else {
				return nullptr;
			}
		}
		static ConstructorIDParameterIndexedDataEntry CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static ConstructorIDParameterIndexedDataEntry* MoveFromStore(IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				ConstructorIDParameterIndexedDataEntry* ret = new(_ptr_placement) ConstructorIDParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue));
				_indexeddatastore.RemoveEntryByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
				return ret;
			} else {
				return nullptr;
			}
		}
		static ConstructorIDParameterIndexedDataEntry MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static void AddToStore(IndexedDataStore& _indexeddatastore, ConstructorIDParameterIndexedDataEntry&& _entry) noexcept {
			_indexeddatastore.AddEntry(ConstructorIDParameterIndexedDataEntry::entryid, static_cast<IndexedDataRawValue>(_entry));
		}
		inline static void RemoveFromStore(IndexedDataStore& _indexeddatastore) noexcept {
			_indexeddatastore.RemoveEntryByEntryID(ConstructorIDParameterIndexedDataEntry::entryid);
		}
		ConstructorID ctorid;
		inline explicit ConstructorIDParameterIndexedDataEntry(const ConstructorID& _ctorid) noexcept : ctorid(_ctorid) {}
		inline ConstructorIDParameterIndexedDataEntry(const ConstructorIDParameterIndexedDataEntry& x) noexcept : ctorid(x.ctorid) {}
		inline ConstructorIDParameterIndexedDataEntry(ConstructorIDParameterIndexedDataEntry&& x) noexcept : ctorid(::std::move(x.ctorid)) {
			x.ctorid = ConstructorID();
		}
		inline ~ConstructorIDParameterIndexedDataEntry() {
			this->ctorid = ConstructorID();
		}
		inline ConstructorIDParameterIndexedDataEntry& operator=(const ConstructorIDParameterIndexedDataEntry& x) noexcept {
			this->ctorid = x.ctorid;
			return *this;
		}
		inline ConstructorIDParameterIndexedDataEntry& operator=(ConstructorIDParameterIndexedDataEntry&& x) noexcept {
			this->ctorid = ::std::move(x.ctorid);
			x.ctorid = ConstructorID();
			return *this;
		}
	private:
		inline explicit ConstructorIDParameterIndexedDataEntry(const IndexedDataRawValue& _indexeddatarawvalue) : ctorid(*reinterpret_cast<const ConstructorID*>(&_indexeddatarawvalue.contextvalue)) {}
		inline explicit ConstructorIDParameterIndexedDataEntry(IndexedDataRawValue&& _indexeddatarawvalue) : ctorid(::std::move(*reinterpret_cast<ConstructorID*>(&_indexeddatarawvalue.contextvalue))) {}
		inline operator IndexedDataRawValue() const noexcept {
			uintptr_t _contextvalue = 0;
			new (&_contextvalue) ConstructorID(this->ctorid);
			return IndexedDataRawValue(
				[](IndexedDataRawValue* x) noexcept->void {
					if (x) {
						reinterpret_cast<ConstructorID*>(&x->contextvalue)->~ConstructorID();
						x->contextvalue = 0;
					}
				},
				_contextvalue
				);
		}
	};
	static_assert(::std::is_standard_layout_v<ConstructorIDParameterIndexedDataEntry>, "ConstructorIDParameterIndexedDataEntry is not standard-layout.");

	class ObjectPointerFromParameterIndexedDataEntry final {
	public:
		static constexpr PersistentID persistentid_entryid = PersistentID(UUIDFromUUIDString_CompileTime("95ca9ad6-1718-4e19-8491-8915aeadf6d1"));
		static YBWLIB2_API IndexedDataEntryID entryid;
		inline static ObjectPointerFromParameterIndexedDataEntry* CopyFromStore(const IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				return new(_ptr_placement) ObjectPointerFromParameterIndexedDataEntry(*_indexeddatarawvalue);
			} else {
				return nullptr;
			}
		}
		static ObjectPointerFromParameterIndexedDataEntry CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static ObjectPointerFromParameterIndexedDataEntry* MoveFromStore(IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				ObjectPointerFromParameterIndexedDataEntry* ret = new(_ptr_placement) ObjectPointerFromParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue));
				_indexeddatastore.RemoveEntryByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
				return ret;
			} else {
				return nullptr;
			}
		}
		static ObjectPointerFromParameterIndexedDataEntry MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static void AddToStore(IndexedDataStore& _indexeddatastore, ObjectPointerFromParameterIndexedDataEntry&& _entry) noexcept {
			_indexeddatastore.AddEntry(ObjectPointerFromParameterIndexedDataEntry::entryid, static_cast<IndexedDataRawValue>(_entry));
		}
		inline static void RemoveFromStore(IndexedDataStore& _indexeddatastore) noexcept {
			_indexeddatastore.RemoveEntryByEntryID(ObjectPointerFromParameterIndexedDataEntry::entryid);
		}
		uintptr_t uintptr_ptr_obj = 0;
		inline explicit constexpr ObjectPointerFromParameterIndexedDataEntry(uintptr_t _uintptr_ptr_obj) noexcept : uintptr_ptr_obj(_uintptr_ptr_obj) {}
		inline constexpr ObjectPointerFromParameterIndexedDataEntry(const ObjectPointerFromParameterIndexedDataEntry& x) noexcept : uintptr_ptr_obj(x.uintptr_ptr_obj) {}
		inline constexpr ObjectPointerFromParameterIndexedDataEntry(ObjectPointerFromParameterIndexedDataEntry&& x) noexcept : uintptr_ptr_obj(::std::move(x.uintptr_ptr_obj)) {
			x.uintptr_ptr_obj = 0;
		}
		inline ~ObjectPointerFromParameterIndexedDataEntry() {
			this->uintptr_ptr_obj = 0;
		}
		inline ObjectPointerFromParameterIndexedDataEntry& operator=(const ObjectPointerFromParameterIndexedDataEntry& x) noexcept {
			this->uintptr_ptr_obj = x.uintptr_ptr_obj;
			return *this;
		}
		inline ObjectPointerFromParameterIndexedDataEntry& operator=(ObjectPointerFromParameterIndexedDataEntry&& x) noexcept {
			this->uintptr_ptr_obj = ::std::move(x.uintptr_ptr_obj);
			x.uintptr_ptr_obj = 0;
			return *this;
		}
	private:
		inline explicit ObjectPointerFromParameterIndexedDataEntry(const IndexedDataRawValue& _indexeddatarawvalue) : uintptr_ptr_obj(_indexeddatarawvalue.contextvalue) {}
		inline explicit ObjectPointerFromParameterIndexedDataEntry(IndexedDataRawValue&& _indexeddatarawvalue) : uintptr_ptr_obj(::std::move(_indexeddatarawvalue.contextvalue)) {
			_indexeddatarawvalue.contextvalue = 0;
		}
		inline operator IndexedDataRawValue() const noexcept { return IndexedDataRawValue(nullptr, this->uintptr_ptr_obj); }
	};
	static_assert(::std::is_standard_layout_v<ObjectPointerFromParameterIndexedDataEntry>, "ObjectPointerFromParameterIndexedDataEntry is not standard-layout.");

	//}
#pragma endregion Stuff used in dynamic object creation

#pragma region Dynamic type class declarations, implementations and initializations helper templates
	//{ Dynamic type class declarations, implementations and initializations helper templates

	/// <summary>Base class definition structure template for dynamic type classes.</summary>
	template<typename T_This_Class, typename T_Base_Class, DynamicTypeBaseClassFlags dtbaseclassflags>
	struct DynamicTypeBaseClassDef_t {
		static_assert(::std::is_class_v<T_This_Class>, "The specified derived class type is not a class.");
		static_assert(::std::is_class_v<T_Base_Class>, "The specified base class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_This_Class>(), "The specified derived class type is not a dynamic type class.");
		static_assert(!IsDynamicTypeNoClass<T_Base_Class>(), "The specified base class type is not a dynamic type class.");
		static_assert(
			IsDynamicTypeModuleLocalClass<T_This_Class>() || !IsDynamicTypeModuleLocalClass<T_Base_Class>(),
			"The specified derived class type is non-module-local, but the specified base class type is module-local."
			);
		inline operator DynamicTypeBaseClassDefObj() const {
			return DynamicTypeBaseClassDefObj(
				GetDynamicTypeClassID<T_Base_Class>(),
				IsDynamicTypeModuleLocalClass<T_Base_Class>(),
				dtbaseclassflags,
				DynamicTypeGetStaticCastFnptr<T_Base_Class, T_This_Class>()
			);
		}
	};
	/// <summary>Base class definition variable template for dynamic type classes.</summary>
	template<typename T_This_Class, typename T_Base_Class, DynamicTypeBaseClassFlags dtbaseclassflags>
	constexpr DynamicTypeBaseClassDef_t<T_This_Class, T_Base_Class, dtbaseclassflags> DynamicTypeBaseClassDef {};

	//}
#pragma endregion These templates aid in the declarations, implementations and initializations of dynamic type classes.

	void YBWLIB2_CALLTYPE DynamicType_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE DynamicType_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE DynamicType_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE DynamicType_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED

#pragma region Dynamic type class declaration and implementation macros
//{ Dynamic type class declaration and implementation macros.

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(classname) \
static constexpr bool DynamicTypeNoClass = true

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(classname, specifiers_dtclassobj, string_dtclassid) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = false;\
static constexpr ::YBWLib2::PersistentID DynamicTypeThisClassPersistentID = ::YBWLib2::PersistentID(::YBWLib2::UUIDFromUUIDString_CompileTime(string_dtclassid));\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_GLOBAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = false;\
static constexpr ::YBWLib2::PersistentID DynamicTypeThisClassPersistentID = ::YBWLib2::PersistentID();\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(classname, specifiers_dtclassobj, string_dtclassid) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::PersistentID DynamicTypeThisClassPersistentID = ::YBWLib2::PersistentID(::YBWLib2::UUIDFromUUIDString_CompileTime(string_dtclassid));\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_MODULE_LOCAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::PersistentID DynamicTypeThisClassPersistentID = ::YBWLib2::PersistentID();\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(classname, specifiers_dtclassobj) \
specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* classname::DynamicTypeThisClassObject = nullptr

//}
#pragma endregion These macros are used in declarations and implementations of dynamic type classes.

#define YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED
#endif

#endif

#ifndef _INCLUDE_GUARD_F44A8AB9_6FB1_45E6_B529_4338B21078FA
#define _INCLUDE_GUARD_F44A8AB9_6FB1_45E6_B529_4338B21078FA

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A384CA1D_8E06_4C4F_9960_E71D9B723F09
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "DynamicType.h"

namespace YBWLib2 {
#pragma region Dynamic type casting intermediates
	//{ Dynamic type casting

	template<typename T_Most_Derived_DT_Class>
	inline uintptr_t DynamicTypeDynamicUpcastTo(uintptr_t ptr, const DynamicTypeClassObj* dtclassobj_target) {
		static_assert(::std::is_class_v<T_Most_Derived_DT_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Most_Derived_DT_Class>(), "The specified type is not a dynamic type class.");
		const DynamicTypeClassObj* dtclassobj = GetDynamicTypeClassObject<T_Most_Derived_DT_Class>();
		if (!dtclassobj) abort();
		return dtclassobj->DynamicUpcastTo(ptr, dtclassobj_target);
	}

	template<typename T_Most_Derived_DT_Class>
	inline uintptr_t DynamicTypeCanDynamicUpcastTo(uintptr_t ptr, const DynamicTypeClassObj* dtclassobj_target) {
		static_assert(::std::is_class_v<T_Most_Derived_DT_Class>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Most_Derived_DT_Class>(), "The specified type is not a dynamic type class.");
		const DynamicTypeClassObj* dtclassobj = GetDynamicTypeClassObject<T_Most_Derived_DT_Class>();
		if (!dtclassobj) abort();
		return dtclassobj->CanDynamicUpcastTo(ptr, dtclassobj_target);
	}

	//}
#pragma endregion These declarations do some intermediate work of dynamically casting pointers.

#pragma region IDynamicTypeObject
	//{ IDynamicTypeObject

	/// <summary>Objects that support getting pointers to various classes in the inheritance hierarchy.</summary>
	class IDynamicTypeObject abstract {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IDynamicTypeObject, YBWLIB2_API, "96b737a3-583d-44ca-a366-fb98b7987e0f");
		inline virtual ~IDynamicTypeObject() = default;
		/// <summary>Gets a pointer to the <c>DynamicTypeClassID</c> identifier that identifies the most derived dynamic type class of the object.</summary>
		/// <returns>
		/// This function returns the required pointer if successful.
		/// Otherwise (if the concrete class of the object does not support this operation), it returns an empty pointer.
		/// </returns>
		virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept = 0;
		/// <summary>Gets a pointer to the <c>DynamicTypeClassObj</c> object that represents the most derived dynamic type class of the object.</summary>
		/// <returns>
		/// This function returns the required pointer if successful.
		/// Otherwise (if the concrete class of the object does not support this operation), it returns an empty pointer.
		/// </returns>
		virtual DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept = 0;
		/// <summary>Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.</summary>
		/// <param name="dtclassobj_target">Pointer to a <c>DynamicTypeClassObj</c> that represents the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>const volatile void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassObj</c> does not represent a registered dynamic type class of the object), it returns an empty pointer.
		/// </returns>
		virtual uintptr_t DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile = 0;
		/// <summary>Gets whether a pointer to this object can be casted to to the most derived dynamic type class or one of its dynamic type base classes.</summary>
		/// <param name="dtclassobj_target">Pointer to a <c>DynamicTypeClassObj</c> that represents the target class.</param>
		/// <returns>Whether a pointer to this object can be casted to to the specified target class.</returns>
		virtual bool DynamicTypeRawCanCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile = 0;
	};

	/// <summary>Structure template for type casting using dynamic type functionality.</summary>
	template<typename T_Class_To, typename T_Class_From>
	struct DynamicTypeCast_t {
		static_assert(::std::is_class_v<T_Class_To>, "The specified target class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_To>(), "The specified target class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, T_Class_To>, "The specified target class type is not derived from IDynamicTypeObject.");
		static_assert(::std::is_class_v<T_Class_From>, "The specified source class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_From>(), "The specified source class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, T_Class_From>, "The specified target class type is not derived from IDynamicTypeObject.");
		static_assert(::std::is_convertible_v<move_cv_t<void, T_Class_From>, move_cv_t<void, T_Class_To>>, "The specified source class type has extra cv-qualifiers that the specified target class type doesn't.");
		inline T_Class_To* operator()(T_Class_From* ptr) const {
			if constexpr (
				::std::is_convertible_v<::std::remove_cv_t<T_Class_From>*, ::std::remove_cv_t<T_Class_To>*>
				&& !IsDynamicTypeModuleLocalClass<T_Class_To>()
				&& !IsDynamicTypeModuleLocalClass<T_Class_From>()
				) {
				return ptr ? static_cast<T_Class_To*>(ptr) : nullptr;
			} else {
				return ptr ? reinterpret_cast<T_Class_To*>(ptr->DynamicTypeRawCastTo(GetDynamicTypeClassObject<T_Class_To>())) : nullptr;
			}
		}
	};
	/// <summary>Variable template for type casting using dynamic type functionality.</summary>
	template<typename T_Class_To, typename T_Class_From>
	constexpr DynamicTypeCast_t<T_Class_To, T_Class_From> DynamicTypeCast {};

	/// <summary>Structure template for checking type casting validity using dynamic type functionality.</summary>
	template<typename T_Class_To, typename T_Class_From>
	struct DynamicTypeCanCast_t {
		static_assert(::std::is_class_v<T_Class_To>, "The specified target class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_To>(), "The specified target class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, T_Class_To>, "The specified target class type is not derived from IDynamicTypeObject.");
		static_assert(::std::is_class_v<T_Class_From>, "The specified source class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<T_Class_From>(), "The specified source class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, T_Class_From>, "The specified target class type is not derived from IDynamicTypeObject.");
		inline bool operator()(T_Class_From* ptr) const {
			if constexpr (::std::is_convertible_v<move_cv_t<void, T_Class_From>, move_cv_t<void, T_Class_To>>) {
				if constexpr (
					::std::is_convertible_v<::std::remove_cv_t<T_Class_From>*, ::std::remove_cv_t<T_Class_To>*>
					&& !IsDynamicTypeModuleLocalClass<T_Class_To>()
					&& !IsDynamicTypeModuleLocalClass<T_Class_From>()
					) {
					return ptr;
				} else {
					return ptr && ptr->DynamicTypeRawCanCastTo(GetDynamicTypeClassObject<T_Class_To>());
				}
			} else {
				return false;
			}
		}
	};
	/// <summary>Variable template for checking type casting validity using dynamic type functionality.</summary>
	template<typename T_Class_To, typename T_Class_From>
	constexpr DynamicTypeCanCast_t<T_Class_To, T_Class_From> DynamicTypeCanCast {};

	//}
#pragma endregion IDynamicTypeObject is used as a virtual base class of other dynamic type classes. This enables casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).
}

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A384CA1D_8E06_4C4F_9960_E71D9B723F09
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A384CA1D_8E06_4C4F_9960_E71D9B723F09
#endif

#endif

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED_IOBJECT

#pragma region IDynamicTypeObject derived classes declaration and implementation macros
//{ IDynamicTypeObject derived classes declaration and implementation macros

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_UNSUPPORTED(classname) \
inline virtual const ::YBWLib2::DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return nullptr; }\
inline virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return nullptr; }\
inline virtual uintptr_t DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return 0; }\
inline virtual bool DynamicTypeRawCanCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return false; }

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(classname)

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_DECLARE(classname, specifiers_vfunc) \
specifiers_vfunc virtual const ::YBWLib2::DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override;\
specifiers_vfunc virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override;\
specifiers_vfunc virtual uintptr_t DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override;\
specifiers_vfunc virtual bool DynamicTypeRawCanCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(classname) \
inline virtual const ::YBWLib2::DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &::YBWLib2::GetDynamicTypeClassID<classname>(); }\
inline virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return ::YBWLib2::GetDynamicTypeClassObject<classname>(); }\
inline virtual uintptr_t DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return ::YBWLib2::DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(static_cast<const volatile classname*>(this)), dtclassobj_target); }\
inline virtual bool DynamicTypeRawCanCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return ::YBWLib2::DynamicTypeCanDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(static_cast<const volatile classname*>(this)), dtclassobj_target); }

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_IOBJECT(classname, specifiers_vfunc) \
specifiers_vfunc const ::YBWLib2::DynamicTypeClassID* classname::DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &::YBWLib2::GetDynamicTypeClassID<classname>(); }\
specifiers_vfunc ::YBWLib2::DynamicTypeClassObj* classname::DynamicTypeGetMostDerivedClassObj() const noexcept override { return ::YBWLib2::GetDynamicTypeClassObject<classname>(); }\
specifiers_vfunc uintptr_t classname::DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return ::YBWLib2::DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(static_cast<const volatile classname*>(this)), dtclassobj_target); }\
specifiers_vfunc bool classname::DynamicTypeRawCanCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return ::YBWLib2::DynamicTypeCanDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(static_cast<const volatile classname*>(this)), dtclassobj_target); }

//}
#pragma endregion These macros are used in dynamic type classes derived from IDynamicTypeObject to support casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).

#define YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED_IOBJECT
#endif

#endif
