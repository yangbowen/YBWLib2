// This header file undefines previously-defined macros controlled by YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED,
// if and only if YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED is not defined.
// Include this header file after undefining YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED to undo YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED.

// Include guard omitted intentionally.

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED

#pragma region Dynamic type class declaration and implementation macros
//{ Dynamic type class declaration and implementation macros.

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_GLOBAL

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_NULL_ID_MODULE_LOCAL

#undef YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS

#undef YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS_NOBASE

//}
#pragma endregion These macros are used in declarations and implementations of dynamic type classes.

#undef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED
#endif

#ifdef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED_IOBJECT

#pragma region IDynamicTypeObject derived classes declaration and implementation macros
//{ IDynamicTypeObject derived classes declaration and implementation macros

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_UNSUPPORTED

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_DECLARE

#undef YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE

#undef YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_IOBJECT

//}
#pragma endregion These macros are used in dynamic type classes derived from IDynamicTypeObject to support casting the object dynamically using information provided by the most derived dynamic type class (often the concrete class).

#undef YBWLIB2_DYNAMIC_TYPE_MACROS_DEFINED_IOBJECT
#endif

#endif
