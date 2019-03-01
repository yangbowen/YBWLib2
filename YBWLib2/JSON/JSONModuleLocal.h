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
	}

	void YBWLIB2_CALLTYPE JSON_RealUnInitModuleLocal() noexcept {
		delete ParseErrorJSONException::DynamicTypeThisClassObject;
		ParseErrorJSONException::DynamicTypeThisClassObject = nullptr;
		delete JSONException::DynamicTypeThisClassObject;
		JSONException::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
