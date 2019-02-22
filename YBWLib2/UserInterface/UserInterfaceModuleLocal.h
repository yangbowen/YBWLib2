#ifndef _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5
#define _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringStringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameterList, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplate, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(FixedStringTemplate, );

	void YBWLIB2_CALLTYPE UserInterface_RealInitModuleLocal() noexcept {
		StringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<StringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<StringTemplateParameter, IStringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> });
		StringStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<StringStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<StringStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> });
		StringTemplateParameterList::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplateParameterList>(),
			IsDynamicTypeModuleLocalClass<StringTemplateParameterList>(),
			{ DynamicTypeBaseClassDef<StringTemplateParameterList, IStringTemplateParameterList, DynamicTypeBaseClassFlag_VirtualBase> });
		StringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplate>(),
			IsDynamicTypeModuleLocalClass<StringTemplate>(),
			{ DynamicTypeBaseClassDef<StringTemplate, IStringTemplate, DynamicTypeBaseClassFlag_VirtualBase> });
		FixedStringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<FixedStringTemplate>(),
			IsDynamicTypeModuleLocalClass<FixedStringTemplate>(),
			{ DynamicTypeBaseClassDef<FixedStringTemplate, StringTemplate, DynamicTypeBaseClassFlag_VirtualBase> });
	}

	void YBWLIB2_CALLTYPE UserInterface_RealUnInitModuleLocal() noexcept {
		delete FixedStringTemplate::DynamicTypeThisClassObject;
		FixedStringTemplate::DynamicTypeThisClassObject = nullptr;
		delete StringTemplate::DynamicTypeThisClassObject;
		StringTemplate::DynamicTypeThisClassObject = nullptr;
		delete StringTemplateParameterList::DynamicTypeThisClassObject;
		StringTemplateParameterList::DynamicTypeThisClassObject = nullptr;
		delete StringStringTemplateParameter::DynamicTypeThisClassObject;
		StringStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
		delete StringTemplateParameter::DynamicTypeThisClassObject;
		StringTemplateParameter::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
