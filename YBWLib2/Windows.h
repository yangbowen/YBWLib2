#ifndef _INCLUDE_GUARD_D370BC7D_DF74_42E2_9449_83D15A4BE9E6
#define _INCLUDE_GUARD_D370BC7D_DF74_42E2_9449_83D15A4BE9E6

#include <winsdkver.h>
#define _WIN32_WINNT 0x601
#include <sdkddkver.h>

#include <ntstatus.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_NO_STATUS
#define NOMINMAX
#include <Windows.h>

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
typedef NTSTATUS *PNTSTATUS;

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#ifndef NT_INFORMATION
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#endif

#ifndef NT_WARNING
#define NT_WARNING(Status) ((((ULONG)(Status)) >> 30) == 2)
#endif

#ifndef NT_ERROR
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)
#endif

#endif
