#ifndef _INCLUDE_GUARD_B1D13803_939D_4D57_BEB2_F29AC2CFE595
#define _INCLUDE_GUARD_B1D13803_939D_4D57_BEB2_F29AC2CFE595

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "JSON.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(JSONException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ParseErrorJSONException, );

	void YBWLIB2_CALLTYPE JSON_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONException)), module_info_current);
		GetDynamicTypeThisClassObject<IParseErrorJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IParseErrorJSONException)), module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXHandler>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONSAXHandler)), module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXGenerator>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IJSONSAXGenerator)), module_info_current);
		JSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<JSONException>(),
			IsDynamicTypeModuleLocalClass<JSONException>(),
			{
				DynamicTypeBaseClassDef<JSONException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<JSONException, IJSONException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		ParseErrorJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ParseErrorJSONException>(),
			IsDynamicTypeModuleLocalClass<ParseErrorJSONException>(),
			{
				DynamicTypeBaseClassDef<ParseErrorJSONException, JSONException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ParseErrorJSONException, IParseErrorJSONException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		GetDynamicTypeThisClassObject<JSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(JSONException)), module_info_current);
		GetDynamicTypeThisClassObject<ParseErrorJSONException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ParseErrorJSONException)), module_info_current);
	}

	void YBWLIB2_CALLTYPE JSON_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<JSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ParseErrorJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete ParseErrorJSONException::DynamicTypeThisClassObject;
		ParseErrorJSONException::DynamicTypeThisClassObject = nullptr;
		delete JSONException::DynamicTypeThisClassObject;
		JSONException::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IJSONSAXGenerator>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IJSONSAXHandler>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IParseErrorJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IJSONException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
