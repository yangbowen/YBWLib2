#pragma once
#include <cstdint>
#include <type_traits>
#include <initializer_list>
#include <guiddef.h>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"

namespace YBWLib2 {
	struct DynamicTypeClassID;
	class DynamicTypeBaseClassDef;
	class DynamicTypeClassObj;
	class IDynamicTypeObject;
	class _impl_DynamicTypeBaseClassDefObj;
	class _impl_DynamicTypeClassObj;

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
	/// Classes with a null <c>DynamicTypeClassID</c> are not registered and therefore cannot be further inherited from or be dynamically casted to.
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
			|| str[38]) terminate();
		return DynamicTypeClassID { { \
			hex_uint32_from_string({ str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], 0 }), \
			hex_uint16_from_string({ str[10], str[11], str[12], str[13], 0 }), \
			hex_uint16_from_string({ str[15], str[16], str[17], str[18], 0 }), \
		{ hex_uint8_from_string({ str[20], str[21], 0 }), hex_uint8_from_string({ str[22], str[23], 0 }), hex_uint8_from_string({ str[25], str[26], 0 }), hex_uint8_from_string({ str[27], str[28], 0 }), \
			hex_uint8_from_string({ str[29], str[30], 0 }), hex_uint8_from_string({ str[31], str[32], 0 }), hex_uint8_from_string({ str[33], str[34], 0 }), hex_uint8_from_string({ str[35], str[36], 0 })
		}\
			} };
	}

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
			if (reinterpret_cast<uintptr_t>(static_cast<_Base_Class_Ty*>(reinterpret_cast<_This_Class_Ty*>(&dummy))) < reinterpret_cast<uintptr_t>(&dummy)) {
				return DynamicTypeBaseClassDefObj(
					GetDynamicTypeThisClassID<_Base_Class_Ty>(),
					IsDynamicTypeModuleLocalClass<_Base_Class_Ty>(),
					reinterpret_cast<uintptr_t>(&dummy) - reinterpret_cast<uintptr_t>(static_cast<_Base_Class_Ty*>(reinterpret_cast<_This_Class_Ty*>(&dummy))),
					DynamicTypeBaseClassDefObj::upcast_negative_offset
				);
			} else {
				return DynamicTypeBaseClassDefObj(
					GetDynamicTypeThisClassID<_Base_Class_Ty>(),
					IsDynamicTypeModuleLocalClass<_Base_Class_Ty>(),
					reinterpret_cast<uintptr_t>(static_cast<_Base_Class_Ty*>(reinterpret_cast<_This_Class_Ty*>(&dummy))) - reinterpret_cast<uintptr_t>(&dummy)
				);
			}
		}
	};
	/// <summary>Base class definition variable template for dynamic type classes.</summary>
	template<typename _This_Class_Ty, typename _Base_Class_Ty>
	constexpr DynamicTypeBaseClassDef_t<_This_Class_Ty, _Base_Class_Ty> DynamicTypeBaseClassDef {};

	/// <summary>
	/// Dynamic type class.
	/// Only construct this object during executable module initialization and destruct this object during executable module cleanup.
	/// </summary>
	class DynamicTypeClassObj final {
		friend _impl_DynamicTypeClassObj;
	public:
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

	/// <summary>Objects that support getting pointers to various classes in the inheritance hierarchy.</summary>
	class IDynamicTypeObject abstract {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IDynamicTypeObject, YBWLIB2_API, "{C3AB7BB2-05D8-4B8A-8856-3FE8423063E7}");
		inline virtual ~IDynamicTypeObject() = default;
		/// <summary>
		/// Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.
		/// </summary>
		/// <param name="dtclassid">Pointer to a <c>DynamicTypeClassID</c> that identifies the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassID</c> does not identify a registered dynamic type class of the object), it returns a null pointer.
		/// </returns>
		virtual void* DynamicCastTo(const DynamicTypeClassID* dtclassid) = 0;
		/// <summary>
		/// Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.
		/// </summary>
		/// <param name="dtclassid">Pointer to a <c>DynamicTypeClassID</c> that identifies the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>const void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassID</c> does not identify a registered dynamic type class of the object), it returns a null pointer.
		/// </returns>
		virtual const void* DynamicCastTo(const DynamicTypeClassID* dtclassid) const = 0;
		/// <summary>
		/// Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.
		/// </summary>
		/// <param name="dtclassid">Pointer to a <c>DynamicTypeClassID</c> that identifies the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>volatile void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassID</c> does not identify a registered dynamic type class of the object), it returns a null pointer.
		/// </returns>
		virtual volatile void* DynamicCastTo(const DynamicTypeClassID* dtclassid) volatile = 0;
		/// <summary>
		/// Cast to a pointer to the most derived dynamic type class or one of its dynamic type base classes.
		/// </summary>
		/// <param name="dtclassid">Pointer to a <c>DynamicTypeClassID</c> that identifies the target class.</param>
		/// <returns>
		/// This function returns the casted pointer, <c>reinterpret_cast</c>ed to a <c>const volatile void*</c> pointer, if successful.
		/// Otherwise (if the specified <c>DynamicTypeClassID</c> does not identify a registered dynamic type class of the object), it returns a null pointer.
		/// </returns>
		virtual const volatile void* DynamicCastTo(const DynamicTypeClassID* dtclassid) const volatile = 0;
	};
}
