#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <climits>
#include <cstdarg>
#include "../Windows.h"
#include <strsafe.h>

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../Exception/Exception.h"
#include "../Exception/ExceptionWindows.h"
#include "UserInterface.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplateParameter, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplateParameterList, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IStringTemplate, YBWLIB2_API);

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE VsnPrintfUtf8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		va_list arglist
	) noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out, &size_max_str_out, &str_format, &size_str_format, &arglist, &err_inner]() noexcept(false)->void {
				if (!rawallocator) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!size_max_str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!str_format) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!size_str_format) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
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
				if (size_str_format > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				unsigned int cch_u16str_format = MultiByteToWideChar(CP_UTF8, 0, str_format, size_str_format & ~(unsigned int)0, nullptr, 0);
				if (!cch_u16str_format) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
				wchar_array_holder_t u16str_format(reinterpret_cast<wchar_t*>(rawallocator->Allocate(cch_u16str_format * sizeof(wchar_t))), cch_u16str_format, rawallocator);
				if (!u16str_format.ptr) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (size_str_format > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!MultiByteToWideChar(CP_UTF8, 0, str_format, size_str_format & ~(unsigned int)0, u16str_format.ptr, cch_u16str_format)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
				size_t cch_max_u16str_out = size_max_str_out;
				wchar_array_holder_t u16str_out(reinterpret_cast<wchar_t*>(rawallocator->Allocate(cch_max_u16str_out * sizeof(wchar_t))), cch_max_u16str_out, rawallocator);
				if (!u16str_out.ptr) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				size_t cch_u16str_out = 0;
				{
					wchar_t* endptr_u16str_out = nullptr;
					HRESULT hr = StringCchVPrintfExW(u16str_out.ptr, cch_max_u16str_out, &endptr_u16str_out, nullptr, 0, u16str_format.ptr, arglist);
					if (FAILED(hr)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(StringCchVPrintfExW, hr); return; }
					cch_u16str_out = endptr_u16str_out + 1 - u16str_out.ptr;
				}
				if (cch_u16str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				unsigned int cb_u8str_out = WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
				if (!cb_u8str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
				if (cb_u8str_out > size_max_str_out) { err_inner = YBWLIB2_EXCEPTION_CREATE_INSUFFICIENT_BUFFER_EXCEPTION(str_out); return; }
				if (size_max_str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (cch_u16str_out > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::VsnPrintfUtf8); return; }
				if (!WideCharToMultiByte(CP_UTF8, 0, u16str_out.ptr, cch_u16str_out & ~(unsigned int)0, str_out, size_max_str_out & ~(unsigned int)0, nullptr, nullptr)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
#else
#error This platform is not supported yet.
#endif
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		} else {
			return err_inner;
		}
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE SnPrintfUtf8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		...
	) noexcept {
		va_list arglist;
		va_start(arglist, str_format);
		IException* exception = VsnPrintfUtf8(rawallocator, str_out, size_max_str_out, str_format, size_str_format, arglist);
		va_end(arglist);
		return exception;
	}

	void YBWLIB2_CALLTYPE UserInterface_RealInitGlobal() noexcept {
		IStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<IStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<IStringTemplateParameter, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IStringTemplateParameter), alignof(IStringTemplateParameter));
		IStringTemplateParameterList::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplateParameterList>(),
			IsDynamicTypeModuleLocalClass<IStringTemplateParameterList>(),
			{ DynamicTypeBaseClassDef<IStringTemplateParameterList, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IStringTemplateParameterList), alignof(IStringTemplateParameterList));
		IStringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IStringTemplate>(),
			IsDynamicTypeModuleLocalClass<IStringTemplate>(),
			{ DynamicTypeBaseClassDef<IStringTemplate, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IStringTemplate), alignof(IStringTemplate));
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
