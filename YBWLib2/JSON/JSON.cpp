﻿#pragma include_alias("pch.h", "../pch.h");
#include "pch.h"
#include "../Common/CommonLowLevel.h"

#ifndef RAPIDJSON_NOMEMBERITERATORCLASS
#define RAPIDJSON_NOMEMBERITERATORCLASS
#endif
#ifndef RAPIDJSON_ERROR_CHARTYPE
#define RAPIDJSON_ERROR_CHARTYPE char
#endif
#ifndef RAPIDJSON_ERROR_STRING
#define RAPIDJSON_ERROR_STRING(x) YBWLIB2_TO_UTF8(x)
#endif
#if defined(_M_IX86_FP) && _M_IX86_FP >= 2 || defined(_M_X64)
#ifndef RAPIDJSON_SSE2
#define RAPIDJSON_SSE2
#endif
#endif
#include <rapidjson/error/en.h>
#include <rapidjson/document.h>

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
			0, sizeof(IJSONException));
		IParseErrorJSONException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IParseErrorJSONException>(),
			IsDynamicTypeModuleLocalClass<IParseErrorJSONException>(),
			{ DynamicTypeBaseClassDef<IParseErrorJSONException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IParseErrorJSONException));
		IJSONSAXHandler::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IJSONSAXHandler>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXHandler>(),
			{ DynamicTypeBaseClassDef<IJSONSAXHandler, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXHandler));
		IJSONSAXGenerator::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IJSONSAXGenerator>(),
			IsDynamicTypeModuleLocalClass<IJSONSAXGenerator>(),
			{ DynamicTypeBaseClassDef<IJSONSAXGenerator, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IJSONSAXGenerator));
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