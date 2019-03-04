#include "pch.h"
#include "YBWLib2Api.h"
#include "YBWLib2RawData.h"

extern "C" {
#include "YBWLib2RawData_Generated.h"
}

namespace YBWLib2 {
	YBWLIB2_API const char* YBWLIB2_CALLTYPE GetRawData_InternalConfig() {
		return reinterpret_cast<const char*>(YBWLib2_internal_config_json);
	}

	YBWLIB2_API size_t YBWLIB2_CALLTYPE GetRawData_Size_InternalConfig() {
		return YBWLib2_internal_config_json_len;
	}
}
