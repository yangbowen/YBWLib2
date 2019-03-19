#ifndef _INCLUDE_GUARD_3D594305_7F68_434A_B42B_D64ED83791FD
#define _INCLUDE_GUARD_3D594305_7F68_434A_B42B_D64ED83791FD

#include <type_traits>
#include "YBWLib2Api.h"
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

namespace YBWLib2::Internal {
	constexpr unsigned int parseflags_rapidjson =
		::rapidjson::kParseValidateEncodingFlag
		| ::rapidjson::kParseFullPrecisionFlag
		| ::rapidjson::kParseCommentsFlag
		| ::rapidjson::kParseNanAndInfFlag;

	typedef ::rapidjson::UTF8<char> jsonencoding_config_internal_t;
	typedef ::rapidjson::CrtAllocator jsonallocator_config_internal_t;
	typedef ::rapidjson::CrtAllocator jsonallocator_stack_config_internal_t;
	typedef ::rapidjson::GenericStringRef<char> jsonstrref_config_internal_t;
	typedef ::rapidjson::GenericValue<jsonencoding_config_internal_t, jsonallocator_config_internal_t> jsonval_config_internal_t;
	typedef ::rapidjson::GenericDocument<jsonencoding_config_internal_t, jsonallocator_config_internal_t, jsonallocator_stack_config_internal_t> jsondoc_config_internal_t;
	static_assert(::std::is_same_v<typename jsondoc_config_internal_t::ValueType, jsonval_config_internal_t>, "jsondoc_config_internal_t::ValueType is not the same as jsonval_config_internal_t.");

	extern const jsondoc_config_internal_t* jsondoc_config_internal;

	template<size_t count_char>
	inline jsonval_config_internal_t ConstStringToInternalConfigJsonval(const char(&str)[count_char]) noexcept {
		return Internal::jsonval_config_internal_t(Internal::jsonstrref_config_internal_t(str));
	}

	void YBWLIB2_CALLTYPE YBWLib2InternalConfig_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE YBWLib2InternalConfig_RealUnInitGlobal() noexcept;
}

#endif
