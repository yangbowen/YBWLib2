#include "pch.h"
#include "YBWLib2Api.h"
#include "YBWLib2RawData.h"
#include "Common/CommonLowLevel.h"

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

#include "JSON/JSON.h"
#include "YBWLib2InternalConfig.h"

namespace YBWLib2::Internal {
	const jsondoc_config_internal_t* jsondoc_config_internal = nullptr;

	static jsondoc_config_internal_t* _jsondoc_config_internal = nullptr;

	void YBWLIB2_CALLTYPE YBWLib2InternalConfig_RealInitGlobal() noexcept {
		_jsondoc_config_internal = new jsondoc_config_internal_t();
		_jsondoc_config_internal->Parse<parseflags_rapidjson_config_internal>(GetRawData_YBWLib2InternalConfig(), GetRawDataSize_YBWLib2InternalConfig());
		if (_jsondoc_config_internal->HasParseError()) abort();
		jsondoc_config_internal = _jsondoc_config_internal;
		if (!jsondoc_config_internal->IsObject()) abort();
	}

	void YBWLIB2_CALLTYPE YBWLib2InternalConfig_RealUnInitGlobal() noexcept {
		jsondoc_config_internal = nullptr;
		delete _jsondoc_config_internal;
		_jsondoc_config_internal = nullptr;
	}
}
