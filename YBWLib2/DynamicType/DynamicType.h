#ifndef _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263
#define _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <initializer_list>
#include <mutex>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"

namespace YBWLib2 {
	struct DynamicTypeClassID;
	class DynamicTypeClassObj;
	class DynamicTypeBaseClassDefObj;
	class IDynamicTypeObject;
	class _impl_DynamicTypeClassObj;

#pragma region DynamicTypeClassID
	//{ DynamicTypeClassID

	/// <summary>Unique identifier used to identify a dynamic type class.</summary>
	struct DynamicTypeClassID {
		UUID uuid = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
		/// <summary>An equal-to comparing function for <c>DynamicTypeClassID</c>.</summary>
		static inline bool IsEqualTo(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return IsEqualTo_UUID(&l->uuid, &r->uuid); }
		/// <summary>
		/// A less-than comparing function for <c>DynamicTypeClassID</c>.
		/// The behaviour is equivalent to comparing the binary representation of the <c>DynamicTypeClassID</c> from byte to byte lexicographically.
		/// </summary>
		static inline bool IsLessThan(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return IsLessThan_UUID(&l->uuid, &r->uuid); }
		/// <summary>A secure version of <c>IsEqualTo_DynamicTypeClassID</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
		static inline bool SecureIsEqualTo(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return SecureIsEqualTo_UUID(&l->uuid, &r->uuid); }
		inline bool operator==(const DynamicTypeClassID& r) const { return DynamicTypeClassID::IsEqualTo(this, &r); }
		inline bool operator!=(const DynamicTypeClassID& r) const { return !DynamicTypeClassID::IsEqualTo(this, &r); }
		inline bool operator<(const DynamicTypeClassID& r) const { return DynamicTypeClassID::IsLessThan(this, &r); }
		inline bool operator<=(const DynamicTypeClassID& r) const { return !DynamicTypeClassID::IsLessThan(&r, this); }
		inline bool operator>(const DynamicTypeClassID& r) const { return DynamicTypeClassID::IsLessThan(&r, this); }
		inline bool operator>=(const DynamicTypeClassID& r) const { return !DynamicTypeClassID::IsLessThan(this, &r); }
		inline size_t hash() const { return this->uuid.hash(); }
	};
	/// <summary>An equal-to comparing function for <c>DynamicTypeClassID</c>.</summary>
	inline bool IsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return DynamicTypeClassID::IsEqualTo(l, r); }
	/// <summary>
	/// A less-than comparing function for <c>DynamicTypeClassID</c>.
	/// The behaviour is equivalent to comparing the binary representation of the <c>DynamicTypeClassID</c> from byte to byte lexicographically.
	/// </summary>
	inline bool IsLessThan_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return DynamicTypeClassID::IsLessThan(l, r); }
	/// <summary>A secure version of <c>IsEqualTo_DynamicTypeClassID</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
	inline bool SecureIsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r) noexcept { return DynamicTypeClassID::SecureIsEqualTo(l, r); }

	struct hash_DynamicTypeClassID_t {
		inline size_t operator()(const DynamicTypeClassID& t) const {
			return t.hash();
		}
	};
	constexpr hash_DynamicTypeClassID_t hash_DynamicTypeClassID {};
	/// <summary>
	/// A null <c>DynamicTypeClassID</c>.
	/// Classes with a null <c>DynamicTypeClassID</c> are not registered and therefore cannot be further inherited from.
	/// </summary>
	constexpr DynamicTypeClassID DynamicTypeClassID_Null = { UUID_Null };
	/// <summary>Converts a UUID string in the format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX to a <c>DynamicTypeClassID</c> identifier at compile time.</summary>
	inline constexpr DynamicTypeClassID DynamicTypeClassIDFromUUIDString_CompileTime(const char(&str)[37]) { return { UUIDFromUUIDString_CompileTime(str) }; }

	//}
#pragma endregion DynamicTypeClassID is used to uniquely identify a dynamic type class. Keep in mind that module-local dynamic type classes can have the same DynamicTypeClassID in different executable modules.

	/// <summary><c>wrapper_lockable_t</c> object that controls the dynamic type environment.</summary>
	extern YBWLIB2_API wrapper_lockable_t* wrapper_lockable_dtenv;

#pragma region Dynamic type class declaration getting templates
	//{ Dynamic Type declaration getting templates.

	/// <summary>
	/// Checks whether the specified class type has been (explicitly) declared not a dynamic type class.
	/// Use this template function instead of directly referencing the <c>DynamicTypeNoClass</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the no-class boolean as the static member variable <c>DynamicTypeNoClass</c>.
	/// </summary>
	template<typename _Class_Ty>
	inline constexpr bool IsDynamicTypeNoClass() {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified type is not a class.");
		return _Class_Ty::DynamicTypeNoClass;
	}
	/// <summary>
	/// Checks whether the specified class type has been declared module-local.
	/// Module-local classes have per-module dynamic type class objects, so these classes can share definitions between modules while being binary-incompatible.
	/// Module-local classes can inherit from non-module-local classes, but non-module-local classes CANNOT inherit from module-local classes.
	/// Use this template function instead of directly referencing the <c>DynamicTypeModuleLocalClass</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the module-local boolean as the static member variable <c>DynamicTypeModuleLocalClass</c>.
	/// </summary>
	template<typename _Class_Ty>
	inline constexpr bool IsDynamicTypeModuleLocalClass() {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified type is not a dynamic type class.");
		return _Class_Ty::DynamicTypeModuleLocalClass;
	}
	/// <summary>
	/// Gets a pointer to the <c>DynamicTypeClassObj</c> object that represents the specified class type.
	/// Use this template function instead of directly referencing the <c>DynamicTypeThisClassObject</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the pointer to the <c>DynamicTypeClassObj</c> object as the static member variable <c>DynamicTypeThisClassObject</c>.
	/// </summary>
	template<typename _Class_Ty>
	inline constexpr DynamicTypeClassObj* GetDynamicTypeThisClassObject() {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified type is not a dynamic type class.");
		return _Class_Ty::DynamicTypeThisClassObject;
	}
	/// <summary>
	/// Gets a reference to the <c>DynamicTypeClassID</c> identifier that identifies the specified class type.
	/// Use this template function instead of directly referencing the <c>DynamicTypeThisClassID</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the <c>DynamicTypeClassID</c> identifier as the static member variable <c>DynamicTypeThisClassID</c>.
	/// Notice that this identifier must be either <c>constexpr</c> or statically initialized, so that it's available before global constructors get executed.
	/// </summary>
	template<typename _Class_Ty>
	inline constexpr const DynamicTypeClassID& GetDynamicTypeThisClassID() {
		static_assert(::std::is_class_v<_Class_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_Ty>(), "The specified type is not a dynamic type class.");
		return _Class_Ty::DynamicTypeThisClassID;
	}
	/// <summary>
	/// Statically casts a pointer from one dynamic type class to another.
	/// Provide specializations for this template to support classes that implement custom static type cast mechanism.
	/// The returned value MUST be statically relative to the passed value, and the function MAY NOT access or depend on memory pointed to by the passed value.
	/// The library does not necessarily pass a valid pointer that points to a <c>_Class_From_Ty</c> object.
	/// </summary>
	template<typename _Class_To_Ty, typename _Class_From_Ty>
	inline constexpr uintptr_t DynamicTypeStaticCast(uintptr_t ptr) {
		static_assert(::std::is_class_v<_Class_To_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_To_Ty>(), "The specified type is not a dynamic type class.");
		static_assert(::std::is_class_v<_Class_From_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_From_Ty>(), "The specified type is not a dynamic type class.");
		return reinterpret_cast<uintptr_t>(static_cast<_Class_To_Ty*>(reinterpret_cast<_Class_From_Ty*>(ptr)));
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
		/// <summary>Finds a registered non-module-local dynamic type class object with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if there isn't a non-module-local dynamic type class object with the specified identifier registered), it returns an empty pointer.
		/// </returns>
		static YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE FindDynamicTypeClassObjectGlobal(const DynamicTypeClassID* _dtclassid);
		/// <summary>Finds a registered module-local dynamic type class object with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if there isn't a module-local dynamic type class object with the specified identifier registered), it returns an empty pointer.
		/// </returns>
		static DynamicTypeClassObj* FindDynamicTypeClassObjectModuleLocal(const DynamicTypeClassID* _dtclassid);
		inline DynamicTypeClassObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, ::std::initializer_list<DynamicTypeBaseClassDefObj> _dtbaseclassdef)
			: dtclassid(_dtclassid), is_module_local(_is_module_local) {
			this->CreateImplObject(_dtbaseclassdef.begin(), _dtbaseclassdef.end());
			if (this->dtclassid != DynamicTypeClassID_Null) this->Register();
		}
		DynamicTypeClassObj(const DynamicTypeClassObj&) = delete;
		DynamicTypeClassObj(DynamicTypeClassObj&&) = delete;
		inline ~DynamicTypeClassObj() {
			if (this->dtclassid != DynamicTypeClassID_Null) this->UnRegister();
			this->DestroyImplObject();
		}
		DynamicTypeClassObj& operator=(const DynamicTypeClassObj&) = delete;
		DynamicTypeClassObj& operator=(DynamicTypeClassObj&&) = delete;
		inline const DynamicTypeClassID& GetDynamicTypeClassID() const noexcept { return this->dtclassid; }
		inline bool IsModuleLocal() const noexcept { return this->is_module_local; }
		/// <summary>Finds a dynamic type base class of this class with the specified <c>DynamicTypeClassID</c> identifier.</summary>
		/// <returns>
		/// This function returns a pointer to the found dynamic type class object if successful.
		/// Otherwise (if this class doesn't have a dynamic type base class with the specified identifier), it returns an empty pointer.
		/// </returns>
		YBWLIB2_API DynamicTypeClassObj* YBWLIB2_CALLTYPE FindBaseClassObject(const DynamicTypeClassID* dtclassid_base) const;
		/// <summary>Dynamically upcasts a pointer.</summary>
		YBWLIB2_API uintptr_t YBWLIB2_CALLTYPE DynamicUpcastTo(uintptr_t ptr_obj, const DynamicTypeClassObj* dtclassobj_target) const;
	protected:
		const DynamicTypeClassID dtclassid;
		const bool is_module_local;
		/// <summary>Pointer to the implementation object.</summary>
		_impl_DynamicTypeClassObj* pimpl = nullptr;
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

	/// <summary>
	/// Base class definition object for dynamic type classes.
	/// Only construct this object during executable module initialization and destruct this object during executable module cleanup.
	/// </summary>
	class DynamicTypeBaseClassDefObj final {
	public:
		// Upcast Offset Sign Properties:
		struct upcast_negative_offset_t {};

		// Upcast Offset Sign Properties:
		static constexpr upcast_negative_offset_t upcast_negative_offset {};

		inline DynamicTypeBaseClassDefObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, size_t offset_upcast)
			: dtclassid(_dtclassid), is_module_local(_is_module_local), offset_upcast_abs(offset_upcast), is_upcast_negative_offset(false) {
			if (this->dtclassid == DynamicTypeClassID_Null) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline DynamicTypeBaseClassDefObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, size_t offset_upcast_neg, upcast_negative_offset_t)
			: dtclassid(_dtclassid), is_module_local(_is_module_local), offset_upcast_abs(offset_upcast_neg), is_upcast_negative_offset(true) {
			if (this->dtclassid == DynamicTypeClassID_Null) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline DynamicTypeBaseClassDefObj(const DynamicTypeBaseClassDefObj& x)
			: dtclassid(x.dtclassid), is_module_local(x.is_module_local), offset_upcast_abs(x.offset_upcast_abs), is_upcast_negative_offset(x.is_upcast_negative_offset) {
			if (this->dtclassid == DynamicTypeClassID_Null) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid)
					: DynamicTypeClassObj::FindDynamicTypeClassObjectGlobal(&this->dtclassid);
				if (!this->dtclassobj) abort();
				if (this->dtclassobj->IsModuleLocal() != this->is_module_local) abort();
			} catch (...) {
				abort();
			}
		}
		inline DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj&& x)
			: dtclassid(x.dtclassid), is_module_local(x.is_module_local), offset_upcast_abs(x.offset_upcast_abs), is_upcast_negative_offset(x.is_upcast_negative_offset) {
			if (this->dtclassid == DynamicTypeClassID_Null) abort();
			try {
				::std::lock_guard<wrapper_lockable_t> lock_guard_dtenv(*wrapper_lockable_dtenv);
				this->dtclassobj =
					this->IsModuleLocal()
					? DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&this->dtclassid)
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
		inline size_t hash() const { return this->dtclassid.hash(); }
		inline const DynamicTypeClassID& GetDynamicTypeClassID() const noexcept { return this->dtclassid; }
		inline bool IsModuleLocal() const noexcept { return this->is_module_local; }
		inline size_t GetUpcastOffsetAbs() const noexcept { return this->offset_upcast_abs; }
		inline bool IsUpcastNegativeOffset() const noexcept { return this->is_upcast_negative_offset; }
		inline DynamicTypeClassObj* GetDynamicTypeClassObject() const { return this->dtclassobj; }
	protected:
		const DynamicTypeClassID dtclassid;
		const bool is_module_local;
		const size_t offset_upcast_abs;
		const bool is_upcast_negative_offset;
		DynamicTypeClassObj* dtclassobj = nullptr;
	};
	static_assert(::std::is_standard_layout_v<DynamicTypeBaseClassDefObj>, "DynamicTypeBaseClassDefObj is not standard-layout.");

	struct hash_DynamicTypeBaseClassDefObj_t {
		inline size_t operator()(const DynamicTypeBaseClassDefObj& t) const {
			return t.hash();
		}
	};
	constexpr hash_DynamicTypeBaseClassDefObj_t hash_DynamicTypeBaseClassDefObj {};

	//}
#pragma endregion DynamicTypeBaseClassDefObj is used to represent a base class definition in a dynamic type class.

#pragma region Dynamic type class declarations, implementations and initializations helper templates
	//{ Dynamic type class declarations, implementations and initializations helper templates

	/// <summary>Base class definition structure template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename _Base_Class_Ty>
	struct DynamicTypeBaseClassDef_t {
		static_assert(::std::is_class_v<_This_Class_Ty>, "The specified derived class type is not a class.");
		static_assert(::std::is_class_v<_Base_Class_Ty>, "The specified base class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_This_Class_Ty>(), "The specified derived class type is not a dynamic type class.");
		static_assert(!IsDynamicTypeNoClass<_Base_Class_Ty>(), "The specified base class type is not a dynamic type class.");
		static_assert(
			IsDynamicTypeModuleLocalClass<_This_Class_Ty>() || !IsDynamicTypeModuleLocalClass<_Base_Class_Ty>(),
			"The specified derived class type is non-module-local, but the specified base class type is module-local."
			);
		inline operator DynamicTypeBaseClassDefObj() const {
			if (DynamicTypeStaticCast<_Base_Class_Ty, _This_Class_Ty>(reinterpret_cast<uintptr_t>(&dummy)) < reinterpret_cast<uintptr_t>(&dummy)) {
				return DynamicTypeBaseClassDefObj(
					GetDynamicTypeThisClassID<_Base_Class_Ty>(),
					IsDynamicTypeModuleLocalClass<_Base_Class_Ty>(),
					reinterpret_cast<uintptr_t>(&dummy) - DynamicTypeStaticCast<_Base_Class_Ty, _This_Class_Ty>(reinterpret_cast<uintptr_t>(&dummy)),
					DynamicTypeBaseClassDefObj::upcast_negative_offset
				);
			} else {
				return DynamicTypeBaseClassDefObj(
					GetDynamicTypeThisClassID<_Base_Class_Ty>(),
					IsDynamicTypeModuleLocalClass<_Base_Class_Ty>(),
					DynamicTypeStaticCast<_Base_Class_Ty, _This_Class_Ty>(reinterpret_cast<uintptr_t>(&dummy)) - reinterpret_cast<uintptr_t>(&dummy)
				);
			}
		}
	};
	/// <summary>Base class definition variable template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename _Base_Class_Ty>
	constexpr DynamicTypeBaseClassDef_t<_This_Class_Ty, _Base_Class_Ty> DynamicTypeBaseClassDef {};

	/// <summary>Class definition structure template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename... _Base_Class_Ty>
	struct DynamicTypeClass_t {
		static_assert(::std::is_class_v<_This_Class_Ty>, "The specified derived class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_This_Class_Ty>(), "The specified derived class type is not a dynamic type class.");
		//static_assert(... && ::std::is_class_v<_Base_Class_Ty>, "At least one of the specified base class types is not a class.");
		inline DynamicTypeClassObj* CreateDynamicTypeClassObject() const {
			return new DynamicTypeClassObj(
				GetDynamicTypeThisClassID<_This_Class_Ty>(),
				IsDynamicTypeModuleLocalClass<_This_Class_Ty>(),
				{ DynamicTypeBaseClassDef<_This_Class_Ty, _Base_Class_Ty>... }
			);
		}
		template<typename _Arg1_New_Ty>
		inline DynamicTypeClassObj* Placement1CreateDynamicTypeClassObject(_Arg1_New_Ty arg1_new) const {
			return new(::std::forward(arg1_new)) DynamicTypeClassObj(
				GetDynamicTypeThisClassID<_This_Class_Ty>(),
				IsDynamicTypeModuleLocalClass<_This_Class_Ty>(),
				{ DynamicTypeBaseClassDef<_This_Class_Ty, _Base_Class_Ty>... }
			);
		}
		template<typename _Arg1_New_Ty, typename _Arg2_New_Ty>
		inline DynamicTypeClassObj* Placement2CreateDynamicTypeClassObject(_Arg1_New_Ty arg1_new, _Arg2_New_Ty arg2_new) const {
			return new(::std::forward(arg1_new), ::std::forward(arg2_new)) DynamicTypeClassObj(
				GetDynamicTypeThisClassID<_This_Class_Ty>(),
				IsDynamicTypeModuleLocalClass<_This_Class_Ty>(),
				{ DynamicTypeBaseClassDef<_This_Class_Ty, _Base_Class_Ty>... }
			);
		}
		template<typename _Arg1_New_Ty, typename _Arg2_New_Ty, typename _Arg3_New_Ty>
		inline DynamicTypeClassObj* Placement3CreateDynamicTypeClassObject(_Arg1_New_Ty arg1_new, _Arg2_New_Ty arg2_new, _Arg3_New_Ty arg3_new) const {
			return new(::std::forward(arg1_new), ::std::forward(arg2_new), ::std::forward(arg3_new)) DynamicTypeClassObj(
				GetDynamicTypeThisClassID<_This_Class_Ty>(),
				IsDynamicTypeModuleLocalClass<_This_Class_Ty>(),
				{ DynamicTypeBaseClassDef<_This_Class_Ty, _Base_Class_Ty>... }
			);
		}
		template<typename _Arg1_New_Ty, typename _Arg2_New_Ty, typename _Arg3_New_Ty, typename _Arg4_New_Ty>
		inline DynamicTypeClassObj* Placement4CreateDynamicTypeClassObject(_Arg1_New_Ty arg1_new, _Arg2_New_Ty arg2_new, _Arg3_New_Ty arg3_new, _Arg4_New_Ty arg4_new) const {
			return new(::std::forward(arg1_new), ::std::forward(arg2_new), ::std::forward(arg3_new), ::std::forward(arg4_new)) DynamicTypeClassObj(
				GetDynamicTypeThisClassID<_This_Class_Ty>(),
				IsDynamicTypeModuleLocalClass<_This_Class_Ty>(),
				{ DynamicTypeBaseClassDef<_This_Class_Ty, _Base_Class_Ty>... }
			);
		}
	};
	/// <summary>Class definition variable template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename... _Base_Class_Ty>
	constexpr DynamicTypeClass_t<_This_Class_Ty, _Base_Class_Ty...> DynamicTypeClass {};

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
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassIDFromUUIDString_CompileTime(string_dtclassid);\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_GLOBAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = false;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassID_Null;\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(classname, specifiers_dtclassobj, string_dtclassid) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassIDFromUUIDString_CompileTime(string_dtclassid);\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_MODULE_LOCAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassID_Null;\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(classname, specifiers_dtclassobj) \
specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj* classname::DynamicTypeThisClassObject = nullptr

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(classname, ...) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>.CreateDynamicTypeClassObject()

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE(classname) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>.CreateDynamicTypeClassObject()

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_PLACEMENT1(classname, arg1_new, ...) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>.Placement1CreateDynamicTypeClassObject(arg1_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE_PLACEMENT1(classname, arg1_new) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>.Placement1CreateDynamicTypeClassObject(arg1_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_PLACEMENT2(classname, arg1_new, arg2_new, ...) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>.Placement2CreateDynamicTypeClassObject(arg1_new, arg2_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE_PLACEMENT2(classname, arg1_new, arg2_new) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>.Placement2CreateDynamicTypeClassObject(arg1_new, arg2_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_PLACEMENT3(classname, arg1_new, arg2_new, arg3_new, ...) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>.Placement3CreateDynamicTypeClassObject(arg1_new, arg2_new, arg3_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE_PLACEMENT3(classname, arg1_new, arg2_new, arg3_new) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>.Placement3CreateDynamicTypeClassObject(arg1_new, arg2_new, arg3_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_PLACEMENT4(classname, arg1_new, arg2_new, arg3_new, arg4_new, ...) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>.Placement3CreateDynamicTypeClassObject(arg1_new, arg2_new, arg3_new, arg4_new)

#define YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS_NOBASE_PLACEMENT4(classname, arg1_new, arg2_new, arg3_new, arg4_new) \
classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>.Placement3CreateDynamicTypeClassObject(arg1_new, arg2_new, arg3_new, arg4_new)

#define YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(classname) \
delete classname::DynamicTypeThisClassObject;\
classname::DynamicTypeThisClassObject = nullptr

#define YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS_NOFREE(classname, lvrefname_ptr) \
(lvrefname_ptr) = classname::DynamicTypeThisClassObject;\
classname::DynamicTypeThisObject->~::YBWLib2::DynamicTypeClassObj();\
classname::DynamicTypeThisClassObject = nullptr

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

	template<typename _Most_Derived_DT_Class_Ty>
	inline uintptr_t DynamicTypeDynamicUpcastTo(uintptr_t ptr, const DynamicTypeClassObj* dtclassobj_target) {
		static_assert(::std::is_class_v<_Most_Derived_DT_Class_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Most_Derived_DT_Class_Ty>(), "The specified type is not a dynamic type class.");
		const DynamicTypeClassObj* dtclassobj = GetDynamicTypeThisClassObject<_Most_Derived_DT_Class_Ty>();
		if (!dtclassobj) abort();
		return dtclassobj->DynamicUpcastTo(ptr, dtclassobj_target);
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
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassObj</c> does not represent a registered dynamic type class of the object), it returns an empty pointer.
		/// </returns>
		virtual void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) = 0;
		/// <summary>Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.</summary>
		/// <param name="dtclassobj_target">Pointer to a <c>DynamicTypeClassObj</c> that represents the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>const void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassObj</c> does not represent a registered dynamic type class of the object), it returns an empty pointer.
		/// </returns>
		virtual const void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const = 0;
		/// <summary>Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.</summary>
		/// <param name="dtclassobj_target">Pointer to a <c>DynamicTypeClassObj</c> that represents the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>volatile void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassObj</c> does not represent a registered dynamic type class of the object), it returns an empty pointer.
		/// </returns>
		virtual volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) volatile = 0;
		/// <summary>Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.</summary>
		/// <param name="dtclassobj_target">Pointer to a <c>DynamicTypeClassObj</c> that represents the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>const volatile void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassObj</c> does not represent a registered dynamic type class of the object), it returns an empty pointer.
		/// </returns>
		virtual const volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile = 0;
	};

	/// <summary>Structure template for type casting using dynamic type functionality.</summary>
	template<typename _Class_To_Ty, typename _Class_From_Ty>
	struct DynamicTypeCast_t {
		static_assert(::std::is_class_v<_Class_To_Ty>, "The specified target class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_To_Ty>(), "The specified target class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, _Class_To_Ty>, "The specified target class type is not derived from IDynamicTypeObject.");
		static_assert(::std::is_class_v<_Class_From_Ty>, "The specified source class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Class_From_Ty>(), "The specified source class type is not a dynamic type class.");
		static_assert(::std::is_base_of_v<IDynamicTypeObject, _Class_From_Ty>, "The specified target class type is not derived from IDynamicTypeObject.");
		static_assert(::std::is_convertible_v<typename move_cv_t<void, _Class_From_Ty>::type, typename move_cv_t<void, _Class_To_Ty>::type>, "The specified source class type has extra cv-qualifiers that the specified target class type doesn't.");
		inline _Class_To_Ty* operator()(_Class_From_Ty* ptr) const {
			reinterpret_cast<_Class_To_Ty*>(ptr->DynamicTypeRawCastTo(GetDynamicTypeThisClassObject<_Class_To_Ty>()));
		}
	};
	/// <summary>Variable template for type casting using dynamic type functionality.</summary>
	template<typename _Class_To_Ty, typename _Class_From_Ty>
	constexpr DynamicTypeCast_t<_Class_To_Ty, _Class_From_Ty> DynamicTypeCast {};

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
inline virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return nullptr; }\
inline virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return nullptr; }\
inline virtual void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) override { return nullptr; }\
inline virtual const void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const override { return nullptr; }\
inline virtual volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) volatile override { return nullptr; }\
inline virtual const volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return nullptr; }

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(classname)

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_DECLARE(classname, specifiers_vfunc) \
specifiers_vfunc virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override;\
specifiers_vfunc virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override;\
specifiers_vfunc virtual void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) override;\
specifiers_vfunc virtual const void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const override;\
specifiers_vfunc virtual volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) volatile override;\
specifiers_vfunc virtual const volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(classname) \
inline virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &GetDynamicTypeThisClassID<classname>(); }\
inline virtual ::YBWLib2::DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return GetDynamicTypeThisClassObject<classname>(); }\
inline virtual void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) override { return reinterpret_cast<void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual const void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const override { return reinterpret_cast<const void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) volatile override { return reinterpret_cast<volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual const volatile void* DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return reinterpret_cast<const volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_IOBJECT(classname, specifiers_vfunc) \
specifiers_vfunc const DynamicTypeClassID* classname::DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &GetDynamicTypeThisClassID<classname>(); }\
specifiers_vfunc ::YBWLib2::DynamicTypeClassObj* classname::DynamicTypeGetMostDerivedClassObj() const noexcept override { return GetDynamicTypeThisClassObject<classname>(); }\
specifiers_vfunc void* classname::DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) override { return reinterpret_cast<void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc const void* classname::DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const override { return reinterpret_cast<const void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc volatile void* classname::DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) volatile override { return reinterpret_cast<volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc const volatile void* classname::DynamicTypeRawCastTo(const ::YBWLib2::DynamicTypeClassObj* dtclassobj_target) const volatile override { return reinterpret_cast<const volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }

//}
#pragma endregion These macros are used in dynamic type classes derived from IDynamicTypeObject to support casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).

#define YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED_IOBJECT
#endif

#endif
