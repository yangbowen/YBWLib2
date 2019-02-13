#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED

#include "../DynamicType/DynamicType.h"
#include "Common.h"
#include "CommonSTLHelper.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ReferenceCountedObject, , IReferenceCountedObject);
}
