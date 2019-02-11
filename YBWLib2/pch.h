#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include <winsdkver.h>
#define _WIN32_WINNT 0x601
#include <sdkddkver.h>

#include <ntstatus.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_NO_STATUS
#include <Windows.h>

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
typedef NTSTATUS *PNTSTATUS;

#undef min
#undef max

#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
