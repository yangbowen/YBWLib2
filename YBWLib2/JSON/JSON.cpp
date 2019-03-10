#pragma include_alias("pch.h", "../pch.h");
#include "pch.h"
#include "../Common/CommonLowLevel.h"
#include "JSON.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IParseErrorJSONException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONSAXHandler, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IJSONSAXGenerator, YBWLIB2_API);

	void YBWLIB2_CALLTYPE JSON_RealInitGlobal() noexcept {
		IJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IJSONException>(),
			IsDynamicTypeModuleLocalClass<IJSONException>(),
			{ DynamicTypeBaseClassDef<IJSONException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONException), alignof(IJSONException));
		IParseErrorJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IParseErrorJSONException>(),
			IsDynamicTypeModuleLocalClass<IParseErrorJSONException>(),
			{ DynamicTypeBaseClassDef<IParseErrorJSONException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IParseErrorJSONException), alignof(IParseErrorJSONException));
		IJSONSAXHandler::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IJSONSAXHandler>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXHandler>(),
			{ DynamicTypeBaseClassDef<IJSONSAXHandler, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXHandler), alignof(IJSONSAXHandler));
		IJSONSAXGenerator::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IJSONSAXGenerator>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXGenerator>(),
			{ DynamicTypeBaseClassDef<IJSONSAXGenerator, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXGenerator), alignof(IJSONSAXGenerator));
	}

	void YBWLIB2_CALLTYPE JSON_RealUnInitGlobal() noexcept {
		delete IJSONSAXGenerator::DynamicTypeThisClassObject;
		IJSONSAXGenerator::DynamicTypeThisClassObject = nullptr;
		delete IJSONSAXHandler::DynamicTypeThisClassObject;
		IJSONSAXHandler::DynamicTypeThisClassObject = nullptr;
		delete IParseErrorJSONException::DynamicTypeThisClassObject;
		IParseErrorJSONException::DynamicTypeThisClassObject = nullptr;
		delete IJSONException::DynamicTypeThisClassObject;
		IJSONException::DynamicTypeThisClassObject = nullptr;
	}
}
