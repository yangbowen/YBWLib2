#pragma once

#ifdef YBWLIB2_EXPORTS
#define YBWLIB2_API __declspec(dllexport)
#else
#define YBWLIB2_API __declspec(dllimport)
#endif

#define YBWLIB2_CALLTYPE __stdcall
