// Include guard omitted intentionally.

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameter, , IStringTemplateParameter);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameterList, , IStringTemplateParameterList);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplate, , IStringTemplate);

	void YBWLIB2_CALLTYPE UserInterface_RealInitModuleLocal() noexcept {}

	void YBWLIB2_CALLTYPE UserInterface_RealUnInitModuleLocal() noexcept {}
}
