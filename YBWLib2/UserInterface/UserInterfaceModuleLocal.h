#ifndef _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5
#define _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameterList, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplate, );

	void YBWLIB2_CALLTYPE UserInterface_RealInitModuleLocal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(StringTemplateParameter, IStringTemplateParameter);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(StringTemplateParameterList, IStringTemplateParameterList);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(StringTemplate, IStringTemplate);
	}

	void YBWLIB2_CALLTYPE UserInterface_RealUnInitModuleLocal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(StringTemplate);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(StringTemplateParameterList);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(StringTemplateParameter);
	}
}

#endif
