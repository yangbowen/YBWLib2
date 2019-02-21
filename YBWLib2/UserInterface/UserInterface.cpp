#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <climits>
#include <cstdarg>
#include "../Windows.h"
#include <strsafe.h>
#include "../Common/CommonLowLevel.h"

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

#include "../Exception/Exception.h"
#include "../Exception/ExceptionWindows.h"
#include "UserInterface.h"

#define YBWLIB2_EXCEPTION_MACROS_ENABLED

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplateParameter, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplateParameterList, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplate, YBWLIB2_API);

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE utf8_vsnprintf(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		va_list arglist
	) {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!str_out) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!size_max_str_out) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!str_format) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!size_str_format) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
#ifdef _WIN32_WINNT
		struct wchar_array_holder_t {
			wchar_t* ptr = nullptr;
			size_t size = 0;
			const rawallocator_t* rawallocator = nullptr;
			inline wchar_array_holder_t(wchar_t* _ptr, size_t _size, const rawallocator_t* _rawallocator) noexcept : ptr(_ptr), size(_size), rawallocator(_rawallocator) {}
			wchar_array_holder_t(const wchar_array_holder_t&) = delete;
			wchar_array_holder_t(wchar_array_holder_t&&) = delete;
			inline ~wchar_array_holder_t() {
				if (this->ptr) {
					if (!this->rawallocator->Deallocate(this->ptr, this->size * sizeof(wchar_t))) abort();
					this->ptr = nullptr;
					this->size = 0;
				}
				this->rawallocator = nullptr;
			}
			wchar_array_holder_t& operator=(const wchar_array_holder_t&) = delete;
			wchar_array_holder_t& operator=(wchar_array_holder_t&&) = delete;
		};
		if (size_str_format > INT_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		unsigned int cch_u16str_format = MultiByteToWideChar(CP_UTF8, 0, str_format, size_str_format & ~(unsigned int)0, nullptr, 0);
		if (!cch_u16str_format) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
		wchar_array_holder_t u16str_format(reinterpret_cast<wchar_t*>(rawallocator->Allocate(cch_u16str_format * sizeof(wchar_t))), cch_u16str_format, rawallocator);
		if (!u16str_format.ptr) return YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION();
		if (size_str_format > INT_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!MultiByteToWideChar(CP_UTF8, 0, str_format, size_str_format & ~(unsigned int)0, u16str_format.ptr, cch_u16str_format)) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
		size_t cch_max_u16str_out = size_max_str_out;
		wchar_array_holder_t u16str_out(reinterpret_cast<wchar_t*>(rawallocator->Allocate(cch_max_u16str_out * sizeof(wchar_t))), cch_max_u16str_out, rawallocator);
		if (!u16str_out.ptr) return YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION();
		size_t cch_u16str_out = 0;
		{
			wchar_t* endptr_u16str_out = nullptr;
			HRESULT hr = StringCchVPrintfExW(u16str_out.ptr, cch_max_u16str_out, &endptr_u16str_out, nullptr, 0, u16str_format.ptr, arglist);
			if (FAILED(hr)) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(StringCchVPrintfExW, hr);
			cch_u16str_out = endptr_u16str_out + 1 - u16str_out.ptr;
		}
		if (cch_u16str_out > INT_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		unsigned int cb_u8str_out = WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
		if (!cb_u8str_out) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
		if (cb_u8str_out > size_max_str_out) return YBWLIB2_EXCEPTION_CREATE_INSUFFICIENT_BUFFER_EXCEPTION(str_out);
		if (size_max_str_out > INT_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (cch_u16str_out > INT_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::utf8_vsnprintf);
		if (!WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, str_out, size_max_str_out & ~(unsigned int)0, nullptr, nullptr)) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
		return nullptr;
#else
#error This platform is not supported yet.
#endif
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE utf8_snprintf(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		...
	) {
		va_list arglist;
		va_start(arglist, str_format);
		IException* exception = utf8_vsnprintf(rawallocator, str_out, size_max_str_out, str_format, size_str_format, arglist);
		va_end(arglist);
		return exception;
	}

	void YBWLIB2_CALLTYPE UserInterface_RealInitGlobal() noexcept {
		IStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<IStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<IStringTemplateParameter, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> });
		IStringTemplateParameterList::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplateParameterList>(),
			IsDynamicTypeModuleLocalClass<IStringTemplateParameterList>(),
			{ DynamicTypeBaseClassDef<IStringTemplateParameterList, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> });
		IStringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplate>(),
			IsDynamicTypeModuleLocalClass<IStringTemplate>(),
			{ DynamicTypeBaseClassDef<IStringTemplate, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> });
	}

	void YBWLIB2_CALLTYPE UserInterface_RealUnInitGlobal() noexcept {
		delete IStringTemplate::DynamicTypeThisClassObject;
		IStringTemplate::DynamicTypeThisClassObject = nullptr;
		delete IStringTemplateParameterList::DynamicTypeThisClassObject;
		IStringTemplateParameterList::DynamicTypeThisClassObject = nullptr;
		delete IStringTemplateParameter::DynamicTypeThisClassObject;
		IStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
	}
}
