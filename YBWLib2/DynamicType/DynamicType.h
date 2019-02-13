#ifndef _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263
#define _INCLUDE_GUARD_E66D6F4F_4C99_49DE_8A34_907BDE018263

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <initializer_list>
#include <guiddef.h>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"

namespace YBWLib2 {
	struct DynamicTypeClassID;
	class DynamicTypeBaseClassDefObj;
	class DynamicTypeClassObj;
	class IDynamicTypeObject;
	class _impl_DynamicTypeBaseClassDefObj;
	class _impl_DynamicTypeClassObj;

#pragma region DynamicTypeClassID
	//{ DynamicTypeClassID

	/// <summary>An equal-to comparing function for <c>DynamicTypeClassID</c>.</summary>
	YBWLIB2_API bool YBWLIB2_CALLTYPE IsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r);
	/// <summary>
	/// A less-than comparing function for <c>DynamicTypeClassID</c>.
	/// The behaviour is equivalent to comparing the binary representation of the <c>DynamicTypeClassID</c> from byte to byte lexicographically.
	/// </summary>
	YBWLIB2_API bool YBWLIB2_CALLTYPE IsLessThan_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r);
	/// <summary>A secure version of <c>IsEqualTo_DynamicTypeClassID</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
	YBWLIB2_API bool YBWLIB2_CALLTYPE SecureIsEqualTo_DynamicTypeClassID(const DynamicTypeClassID* l, const DynamicTypeClassID* r);
	/// <summary>Unique identifier used to identify a dynamic type class.</summary>
	struct DynamicTypeClassID {
		GUID guid;
		inline bool operator==(const DynamicTypeClassID& r) const { return IsEqualGUID(this->guid, r.guid); }
		inline bool operator!=(const DynamicTypeClassID& r) const { return !IsEqualGUID(this->guid, r.guid); }
		inline bool operator<(const DynamicTypeClassID& r) const { return IsLessThan_DynamicTypeClassID(this, &r); }
		inline bool operator<=(const DynamicTypeClassID& r) const { return !IsLessThan_DynamicTypeClassID(&r, this); }
		inline bool operator>(const DynamicTypeClassID& r) const { return IsLessThan_DynamicTypeClassID(&r, this); }
		inline bool operator>=(const DynamicTypeClassID& r) const { return !IsLessThan_DynamicTypeClassID(this, &r); }
		inline size_t hash() const { return hash_trivially_copyable_t<DynamicTypeClassID, size_t>()(*this); }
	};

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
	constexpr DynamicTypeClassID DynamicTypeClassID_Null = { { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } } };
	/// <summary>Converts a GUID string in the format {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} to a <c>DynamicTypeClassID</c> identifier at compile time.</summary>
	inline constexpr DynamicTypeClassID DynamicTypeClassIDFromGUIDString_CompileTime(const char(&str)[39]) {
		if (str[0] != '{'
			|| str[9] != '-'
			|| str[14] != '-'
			|| str[19] != '-'
			|| str[24] != '-'
			|| str[37] != '}'
			|| str[38]) abort();
		return DynamicTypeClassID { { \
			hex_uint32_from_string({ str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], 0 }), \
			hex_uint16_from_string({ str[10], str[11], str[12], str[13], 0 }), \
			hex_uint16_from_string({ str[15], str[16], str[17], str[18], 0 }), \
		{ hex_uint8_from_string({ str[20], str[21], 0 }), hex_uint8_from_string({ str[22], str[23], 0 }), hex_uint8_from_string({ str[25], str[26], 0 }), hex_uint8_from_string({ str[27], str[28], 0 }), \
			hex_uint8_from_string({ str[29], str[30], 0 }), hex_uint8_from_string({ str[31], str[32], 0 }), hex_uint8_from_string({ str[33], str[34], 0 }), hex_uint8_from_string({ str[35], str[36], 0 })
		}\
			} };
	}

	//}
#pragma endregion DynamicTypeClassID is used to uniquely identify a dynamic type class. Keep in mind that module-local dynamic type classes can have the same DynamicTypeClassID in different executable modules.

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
	/// Gets a reference to the <c>DynamicTypeClassObj</c> object that represents the specified class type.
	/// Use this template function instead of directly referencing the <c>DynamicTypeThisClassObject</c> static member variable.
	/// Provide specializations for this template to support classes that do not declare the <c>DynamicTypeClassObj</c> object as the static member variable <c>DynamicTypeThisClassObject</c>.
	/// </summary>
	template<typename _Class_Ty>
	inline constexpr DynamicTypeClassObj& GetDynamicTypeThisClassObject() {
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

#pragma region DynamicTypeBaseClassDefObj
	//{ DynamicTypeBaseClassDefObj

	/// <summary>
	/// Base class definition object for dynamic type classes.
	/// Only construct this object during executable module initialization and destruct this object during executable module cleanup.
	/// </summary>
	class DynamicTypeBaseClassDefObj final {
		friend _impl_DynamicTypeBaseClassDefObj;
	public:
		// Upcast Offset Sign Properties:
		struct upcast_negative_offset_t {};

		// Upcast Offset Sign Properties:
		static constexpr upcast_negative_offset_t upcast_negative_offset {};

		inline DynamicTypeBaseClassDefObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, size_t offset_upcast)
			: dtclassid(_dtclassid), is_module_local(_is_module_local), offset_upcast_abs(offset_upcast), is_upcast_negative_offset(false) {
			this->CreateImplObject();
			// Doesn't call Initialize here because this constructor may be called before corresponding DynamicTypeClassObj objects are constructed and registered.
		}
		inline DynamicTypeBaseClassDefObj(const DynamicTypeClassID& _dtclassid, bool _is_module_local, size_t offset_upcast_neg, upcast_negative_offset_t)
			: dtclassid(_dtclassid), is_module_local(_is_module_local), offset_upcast_abs(offset_upcast_neg), is_upcast_negative_offset(true) {
			this->CreateImplObject();
			// Doesn't call Initialize here because this constructor may be called before corresponding DynamicTypeClassObj objects are constructed and registered.
		}
		inline DynamicTypeBaseClassDefObj(const DynamicTypeBaseClassDefObj& x)
			: dtclassid(x.dtclassid), is_module_local(x.is_module_local), offset_upcast_abs(x.offset_upcast_abs), is_upcast_negative_offset(x.is_upcast_negative_offset) {
			this->CopyCreateImplObject(&x);
			// Doesn't call Initialize here because this constructor may be called before corresponding DynamicTypeClassObj objects are constructed and registered.
		}
		inline DynamicTypeBaseClassDefObj(DynamicTypeBaseClassDefObj&& x)
			: dtclassid(x.dtclassid), is_module_local(x.is_module_local), offset_upcast_abs(x.offset_upcast_abs), is_upcast_negative_offset(x.is_upcast_negative_offset) {
			this->MoveCreateImplObject(&x);
			// Doesn't call Initialize here because this constructor may be called before corresponding DynamicTypeClassObj objects are constructed and registered.
		}
		inline ~DynamicTypeBaseClassDefObj() {
			this->DestroyImplObject();
		}
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
		inline DynamicTypeClassObj* GetDynamicTypeClassObject() const {
			this->Initialize();
			return this->dtclassobj;
		}
		/// <summary>
		/// Does one-time initialization of some members when called on the object for the first time.
		/// Returns directly for subsequent calls.
		/// </summary>
		YBWLIB2_API void YBWLIB2_CALLTYPE Initialize() const;
		/// <summary>
		/// Does one-time initialization.
		/// Declared public to allow calls by internal intermediate non-member functions.
		/// Do NOT call otherwise.
		/// This is the global version which is defind and exported in the library.
		/// </summary>
		YBWLIB2_API void YBWLIB2_CALLTYPE RealInitializeGlobal() const;
		/// <summary>
		/// Does one-time initialization.
		/// Declared public to allow calls by internal intermediate non-member functions.
		/// Do NOT call otherwise.
		/// This is the module local version which is defined in individual executable modules.
		/// </summary>
		void RealInitializeModuleLocal() const;
		inline void RealInitialize() const {
			if (this->is_module_local)
				this->RealInitializeModuleLocal();
			else
				this->RealInitializeGlobal();
		}
	protected:
		const DynamicTypeClassID dtclassid;
		const bool is_module_local;
		const size_t offset_upcast_abs;
		const bool is_upcast_negative_offset;
		mutable DynamicTypeClassObj* dtclassobj = nullptr;
		/// <summary>Pointer to the implementation object.</summary>
		_impl_DynamicTypeBaseClassDefObj* pimpl = nullptr;
	private:
		YBWLIB2_API void YBWLIB2_CALLTYPE CreateImplObject();
		YBWLIB2_API void YBWLIB2_CALLTYPE CopyCreateImplObject(const DynamicTypeBaseClassDefObj* x);
		YBWLIB2_API void YBWLIB2_CALLTYPE MoveCreateImplObject(DynamicTypeBaseClassDefObj* x);
		YBWLIB2_API void YBWLIB2_CALLTYPE DestroyImplObject();
	};

	struct hash_DynamicTypeBaseClassDefObj_t {
		inline size_t operator()(const DynamicTypeBaseClassDefObj& t) const {
			return t.hash();
		}
	};
	constexpr hash_DynamicTypeBaseClassDefObj_t hash_DynamicTypeBaseClassDefObj {};

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

	//}
#pragma endregion DynamicTypeBaseClassDefObj is used to represent a base class definition in a dynamic type class.

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
		DynamicTypeClassObj& operator=(const DynamicTypeClassObj&) = delete;
		DynamicTypeClassObj& operator=(DynamicTypeClassObj&&) = delete;
		inline ~DynamicTypeClassObj() {
			if (this->dtclassid != DynamicTypeClassID_Null) this->UnRegister();
			this->DestroyImplObject();
		}
		inline const DynamicTypeClassID& GetDynamicTypeClassID() const noexcept { return this->dtclassid; }
		inline bool IsModuleLocal() const noexcept { return this->is_module_local; }
		/// <summary>
		/// Does one-time initialization of some members when called on the object for the first time.
		/// Returns directly for subsequent calls.
		/// </summary>
		YBWLIB2_API void YBWLIB2_CALLTYPE Initialize() const;
		/// <summary>
		/// Does one-time initialization.
		/// Declared public to allow calls by internal intermediate non-member functions.
		/// Do NOT call otherwise.
		/// </summary>
		YBWLIB2_API void YBWLIB2_CALLTYPE RealInitialize() const;
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

	/// <summary>Class definition structure template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename ... _Base_Class_Ty>
	struct DynamicTypeClass_t {
		static_assert(::std::is_class_v<_This_Class_Ty>, "The specified derived class type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_This_Class_Ty>(), "The specified derived class type is not a dynamic type class.");
		//static_assert(... && ::std::is_class_v<_Base_Class_Ty>, "At least one of the specified base class types is not a class.");
		inline operator DynamicTypeClassObj() const {
			return DynamicTypeClassObj(
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
#pragma endregion DynamicTypeClassObj is used to represent a dynamic type class.

#pragma region Dynamic type class declaration and implementation macros
	//{ Dynamic type class declaration and implementation macros.

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(classname) \
static constexpr bool DynamicTypeNoClass = true

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(classname, specifiers_dtclassobj, string_dtclassid) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = false;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassIDFromGUIDString_CompileTime(string_dtclassid);\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_GLOBAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = false;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassID_Null;\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(classname, specifiers_dtclassobj, string_dtclassid) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassIDFromGUIDString_CompileTime(string_dtclassid);\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_MODULE_LOCAL(classname, specifiers_dtclassobj) \
static constexpr bool DynamicTypeNoClass = false;\
static constexpr bool DynamicTypeModuleLocalClass = true;\
static constexpr ::YBWLib2::DynamicTypeClassID DynamicTypeThisClassID = ::YBWLib2::DynamicTypeClassID_Null;\
static specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj DynamicTypeThisClassObject

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(classname, specifiers_dtclassobj, ...) \
specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname, __VA_ARGS__>

#ifdef YBWLIB2_EXPORTS

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS_NOBASE(classname, specifiers_dtclassobj) \
specifiers_dtclassobj ::YBWLib2::DynamicTypeClassObj classname::DynamicTypeThisClassObject = ::YBWLib2::DynamicTypeClass<classname>

#endif

#endif

	//}
#pragma endregion These macros are used in declarations and implementations of dynamic type classes.

#pragma region Dynamic type casting intermediates
	//{ Dynamic type casting

	template<typename _Most_Derived_DT_Class_Ty>
	inline uintptr_t DynamicTypeDynamicUpcastTo(uintptr_t ptr, const DynamicTypeClassObj* dtclassobj_target) {
		static_assert(::std::is_class_v<_Most_Derived_DT_Class_Ty>, "The specified type is not a class.");
		static_assert(!IsDynamicTypeNoClass<_Most_Derived_DT_Class_Ty>(), "The specified type is not a dynamic type class.");
		return GetDynamicTypeThisClassObject<_Most_Derived_DT_Class_Ty>().DynamicUpcastTo(ptr, dtclassobj_target);
	}

	//}
#pragma endregion These declarations do some intermediate work of dynamically casting pointers.

#pragma region IDynamicTypeObject
	//{ IDynamicTypeObject

	/// <summary>Objects that support getting pointers to various classes in the inheritance hierarchy.</summary>
	class IDynamicTypeObject abstract {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IDynamicTypeObject, YBWLIB2_API, "{C3AB7BB2-05D8-4B8A-8856-3FE8423063E7}");
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
			reinterpret_cast<_Class_To_Ty*>(ptr->DynamicTypeRawCastTo(&GetDynamicTypeThisClassObject<_Class_To_Ty>()));
		}
	};
	/// <summary>Variable template for type casting using dynamic type functionality.</summary>
	template<typename _Class_To_Ty, typename _Class_From_Ty>
	constexpr DynamicTypeCast_t<_Class_To_Ty, _Class_From_Ty> DynamicTypeCast {};

	//}
#pragma endregion IDynamicTypeObject is used as a virtual base class of other dynamic type classes. This enables casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).

#pragma region IDynamicTypeObject derived classes declaration and implementation macros
	//{ IDynamicTypeObject derived classes declaration and implementation macros

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_UNSUPPORTED(classname) \
inline virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return nullptr; }\
inline virtual DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return nullptr; }\
inline virtual void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) override { return nullptr; }\
inline virtual const void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const override { return nullptr; }\
inline virtual volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) volatile override { return nullptr; }\
inline virtual const volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile override { return nullptr; }

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(classname)

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_DECLARE(classname, specifiers_vfunc) \
specifiers_vfunc virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override;\
specifiers_vfunc virtual DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override;\
specifiers_vfunc virtual void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) override;\
specifiers_vfunc virtual const void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const override;\
specifiers_vfunc virtual volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) volatile override;\
specifiers_vfunc virtual const volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile override

#define YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(classname) \
inline virtual const DynamicTypeClassID* DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &GetDynamicTypeThisClassID<classname>(); }\
inline virtual DynamicTypeClassObj* DynamicTypeGetMostDerivedClassObj() const noexcept override { return &GetDynamicTypeThisClassObject<classname>(); }\
inline virtual void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) override { return reinterpret_cast<void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual const void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const override { return reinterpret_cast<const void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) volatile override { return reinterpret_cast<volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
inline virtual const volatile void* DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile override { return reinterpret_cast<const volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }

#define YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_IOBJECT(classname, specifiers_vfunc) \
specifiers_vfunc const DynamicTypeClassID* classname::DynamicTypeGetMostDerivedClassID() const noexcept override { static_assert(::std::is_same_v<::std::remove_cv_t<::std::remove_pointer_t<decltype(this)>>, classname>, "The specified class name is not correct."); return &GetDynamicTypeThisClassID<classname>(); }\
specifiers_vfunc DynamicTypeClassObj* classname::DynamicTypeGetMostDerivedClassObj() const noexcept override { return &GetDynamicTypeThisClassObject<classname>(); }\
specifiers_vfunc void* classname::DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) override { return reinterpret_cast<void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc const void* classname::DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const override { return reinterpret_cast<const void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc volatile void* classname::DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) volatile override { return reinterpret_cast<volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }\
specifiers_vfunc const volatile void* classname::DynamicTypeRawCastTo(const DynamicTypeClassObj* dtclassobj_target) const volatile override { return reinterpret_cast<const volatile void*>(DynamicTypeDynamicUpcastTo<classname>(reinterpret_cast<uintptr_t>(this), dtclassobj_target)); }

#endif

	//}
#pragma endregion These macros are used in dynamic type classes derived from IDynamicTypeObject to support casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).
}

#endif
