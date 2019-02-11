#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "Common.h"
#include "CommonSTLHelper.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountedObject, YBWLIB2_API, IDynamicTypeObject);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ILockableObject, YBWLIB2_API, IDynamicTypeObject);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ReferenceCountedObject, YBWLIB2_API, IReferenceCountedObject);
}
