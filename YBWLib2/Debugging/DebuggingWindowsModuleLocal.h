#ifndef _INCLUDE_GUARD_C7850743_263D_4E54_AF07_F66878010435
#define _INCLUDE_GUARD_C7850743_263D_4E54_AF07_F66878010435

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <map>
#ifdef _MSC_VER
#include <intrin.h>
#if defined(_M_X64)
#pragma intrinsic(_mulx_u64)
#endif
#if defined(_M_IX86) || defined(_M_X64)
#pragma intrinsic(_mulx_u32)
#endif
#endif
#include <TlHelp32.h>
#include <Psapi.h>
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"
#include "../DynamicType/DynamicType.h"
#include "../UserInterface/UserInterface.h"
#include "../UserInterface/UserInterfaceWindows.h"
#include "DebuggingWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(UnsupportedTargetWin32ArchitectureException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32DebuggingTargetMemoryRegionInfo, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32DebuggingTargetExecutableModuleInfo, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32DebuggingTargetExportSymbolInfo, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32DebuggingProcess, );

	[[nodiscard]] IException* UnsupportedTargetWin32ArchitectureException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		static constexpr char conststr_unknown[] = u8"<UNKNOWN>";
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_machine_native;
				if (this->GetNativeArchitectureImageFileMachineWord() != IMAGE_FILE_MACHINE_UNKNOWN) {
					char str_machine_native[sizeof(USHORT) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<USHORT>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(rawallocator_exception, str_machine_native, sizeof(str_machine_native) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(USHORT) / sizeof(uint8_t) * 2), this->GetNativeArchitectureImageFileMachineWord());
					if (err_inner) return;
					objholder_strtmplparameter_machine_native.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_native", str_machine_native, strnlen(str_machine_native, sizeof(USHORT) / sizeof(uint8_t) * 2 + 16));
				} else {
					objholder_strtmplparameter_machine_native.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_native", conststr_unknown, sizeof(conststr_unknown) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_machine_process_current;
				if (this->GetCurrentProcessArchitectureImageFileMachineWord() != IMAGE_FILE_MACHINE_UNKNOWN) {
					char str_machine_process_current[sizeof(USHORT) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<USHORT>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(rawallocator_exception, str_machine_process_current, sizeof(str_machine_process_current) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(USHORT) / sizeof(uint8_t) * 2), this->GetCurrentProcessArchitectureImageFileMachineWord());
					if (err_inner) return;
					objholder_strtmplparameter_machine_process_current.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_process_current", str_machine_process_current, strnlen(str_machine_process_current, sizeof(USHORT) / sizeof(uint8_t) * 2 + 16));
				} else {
					objholder_strtmplparameter_machine_process_current.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_process_current", conststr_unknown, sizeof(conststr_unknown) / sizeof(char) - 1);
				}
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_machine_process_target;
				if (this->GetTargetProcessArchitectureImageFileMachineWord() != IMAGE_FILE_MACHINE_UNKNOWN) {
					char str_machine_process_target[sizeof(USHORT) / sizeof(uint8_t) * 2 + 16];
					static constexpr char str_prefix_fmt[] = u8"0x%0*";
					char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char))];
					memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
					memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<USHORT>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<USHORT>::fmtspec_printf_X_utf8) / sizeof(char));
					err_inner = SnPrintfUtf8(rawallocator_exception, str_machine_process_target, sizeof(str_machine_process_target) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(USHORT) / sizeof(uint8_t) * 2), this->GetTargetProcessArchitectureImageFileMachineWord());
					if (err_inner) return;
					objholder_strtmplparameter_machine_process_target.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_process_target", str_machine_process_target, strnlen(str_machine_process_target, sizeof(USHORT) / sizeof(uint8_t) * 2 + 16));
				} else {
					objholder_strtmplparameter_machine_process_target.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"machine_process_target", conststr_unknown, sizeof(conststr_unknown) / sizeof(char) - 1);
				}
				err_inner = UnsupportedTargetWin32ArchitectureException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_machine_native.get(),
						objholder_strtmplparameter_machine_process_current.get(),
						objholder_strtmplparameter_machine_process_target.get()
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}

	Win32DebuggingTargetAddressDiff::Win32DebuggingTargetAddressDiff(Win32Architecture _architecture) noexcept(false) : architecture(_architecture), is_negative(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff::Win32DebuggingTargetAddressDiff(const Win32DebuggingTargetAddressDiff& x) noexcept(false) : architecture(x.architecture), is_negative(x.is_negative) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff::Win32DebuggingTargetAddressDiff(Win32DebuggingTargetAddressDiff&& x) noexcept(false) : architecture(x.architecture), is_negative(x.is_negative) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			x.uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			x.uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		x.is_negative = false;
	}

	Win32DebuggingTargetAddressDiff::~Win32DebuggingTargetAddressDiff() {
		this->is_negative = false;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			abort();
		}
	}

	Win32DebuggingTargetAddressDiff& Win32DebuggingTargetAddressDiff::operator=(const Win32DebuggingTargetAddressDiff& x) noexcept(false) {
		this->is_negative = false;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		this->architecture = x.architecture;
		this->is_negative = x.is_negative;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		return *this;
	}

	Win32DebuggingTargetAddressDiff& Win32DebuggingTargetAddressDiff::operator=(Win32DebuggingTargetAddressDiff&& x) noexcept(false) {
		this->is_negative = false;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		this->architecture = x.architecture;
		this->is_negative = x.is_negative;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			x.uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			x.uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		x.is_negative = false;
		return *this;
	}

	bool Win32DebuggingTargetAddressDiff::operator==(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) return false;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return this->uint64 == r.uint64 && (this->is_negative == r.is_negative || !this->uint64);
		case Win32Architecture::Win32Architecture_x86:
			return this->uint32 == r.uint32 && (this->is_negative == r.is_negative || !this->uint32);
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddressDiff::operator<(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) return this->architecture < r.architecture;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return false;
		case Win32Architecture::Win32Architecture_x64:
			return
				!this->is_negative && !r.is_negative && this->uint64 < r.uint64
				|| this->is_negative && !r.is_negative && (this->uint64 || r.uint64)
				|| this->is_negative && r.is_negative && this->uint64 > r.uint64;
		case Win32Architecture::Win32Architecture_x86:
			return
				!this->is_negative && !r.is_negative && this->uint32 < r.uint32
				|| this->is_negative && !r.is_negative && (this->uint32 || r.uint32)
				|| this->is_negative && r.is_negative && this->uint32 > r.uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator+() const noexcept(false) {
		Win32DebuggingTargetAddressDiff ret(*this);
		return ret;
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator-() const noexcept(false) {
		Win32DebuggingTargetAddressDiff ret(*this);
		ret.is_negative = !ret.is_negative;
		return ret;
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator+(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator+));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64:
			if (this->is_negative != r.is_negative) {
				if (this->uint64 < r.uint64) {
					Win32DebuggingTargetAddressDiff ret(r);
					ret.uint64 -= this->uint64;
					return ret;
				} else {
					Win32DebuggingTargetAddressDiff ret(*this);
					ret.uint64 -= r.uint64;
					return ret;
				}
			} else {
				if (r.uint64 > UINT64_MAX - this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator+));
				Win32DebuggingTargetAddressDiff ret(*this);
				ret.uint64 += r.uint64;
				return ret;
			}
		case Win32Architecture::Win32Architecture_x86:
			if (this->is_negative != r.is_negative) {
				if (this->uint32 < r.uint32) {
					Win32DebuggingTargetAddressDiff ret(r);
					ret.uint32 -= this->uint32;
					return ret;
				} else {
					Win32DebuggingTargetAddressDiff ret(*this);
					ret.uint32 -= r.uint32;
					return ret;
				}
			} else {
				if (r.uint32 > UINT32_MAX - this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator+));
				Win32DebuggingTargetAddressDiff ret(*this);
				ret.uint32 += r.uint32;
				return ret;
			}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator-(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator-));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64:
			if (this->is_negative != r.is_negative) {
				if (r.uint64 > UINT64_MAX - this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator-));
				Win32DebuggingTargetAddressDiff ret(*this);
				ret.uint64 += r.uint64;
				return ret;
			} else {
				if (this->uint64 < r.uint64) {
					Win32DebuggingTargetAddressDiff ret(r);
					ret.uint64 -= this->uint64;
					return ret;
				} else {
					Win32DebuggingTargetAddressDiff ret(*this);
					ret.uint64 -= r.uint64;
					return ret;
				}
			}
		case Win32Architecture::Win32Architecture_x86:
			if (this->is_negative != r.is_negative) {
				if (r.uint32 > UINT32_MAX - this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator-));
				Win32DebuggingTargetAddressDiff ret(*this);
				ret.uint32 += r.uint32;
				return ret;
			} else {
				if (this->uint32 < r.uint32) {
					Win32DebuggingTargetAddressDiff ret(r);
					ret.uint32 -= this->uint32;
					return ret;
				} else {
					Win32DebuggingTargetAddressDiff ret(*this);
					ret.uint32 -= r.uint32;
					return ret;
				}
			}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator*(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator*));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.is_negative ^= r.is_negative;
#if defined(_MSC_VER) && defined(_M_X64)
			uint64_t result_high = 0;
			ret.uint64 = _mulx_u64(ret.uint64, r.uint64, &result_high);
			if (result_high) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator*));
#else
			if (r.uint64 > UINT64_MAX / ret.uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator*));
			ret.uint64 *= r.uint64;
#endif
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.is_negative ^= r.is_negative;
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
			uint32_t result_high = 0;
			ret.uint32 = _mulx_u32(ret.uint32, r.uint32, &result_high);
			if (result_high) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator*));
#else
			if (r.uint32 > UINT32_MAX / ret.uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator*));
			ret.uint32 *= r.uint32;
#endif
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator/(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator/));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			if (!r.uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator/));
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.is_negative ^= r.is_negative;
			ret.uint64 /= r.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (!r.uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator/));
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.is_negative ^= r.is_negative;
			ret.uint32 /= r.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator%(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator%));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			if (!r.uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator%));
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.uint64 %= r.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (!r.uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator%));
			Win32DebuggingTargetAddressDiff ret(*this);
			ret.uint32 %= r.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator~() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint64 = ret.uint64 ? ~(ret.uint64 - 1) : 0;
			}
			ret.uint64 = ~ret.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint32 = ret.uint32 ? ~(ret.uint32 - 1) : 0;
			}
			ret.uint32 = ~ret.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator&(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator&));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint64 = ret.uint64 ? ~(ret.uint64 - 1) : 0;
			}
			ret.uint64 &= r.is_negative ? (r.uint64 ? ~(r.uint64 - 1) : 0) : r.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint32 = ret.uint32 ? ~(ret.uint32 - 1) : 0;
			}
			ret.uint32 &= r.is_negative ? (r.uint32 ? ~(r.uint32 - 1) : 0) : r.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator|(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator|));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint64 = ret.uint64 ? ~(ret.uint64 - 1) : 0;
			}
			ret.uint64 |= r.is_negative ? (r.uint64 ? ~(r.uint64 - 1) : 0) : r.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint32 = ret.uint32 ? ~(ret.uint32 - 1) : 0;
			}
			ret.uint32 |= r.is_negative ? (r.uint32 ? ~(r.uint32 - 1) : 0) : r.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator^(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, operator^));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint64 = ret.uint64 ? ~(ret.uint64 - 1) : 0;
			}
			ret.uint64 ^= r.is_negative ? (r.uint64 ? ~(r.uint64 - 1) : 0) : r.uint64;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (ret.is_negative) {
				ret.is_negative = false;
				ret.uint32 = ret.uint32 ? ~(ret.uint32 - 1) : 0;
			}
			ret.uint32 ^= r.is_negative ? (r.uint32 ? ~(r.uint32 - 1) : 0) : r.uint32;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator<<(uint8_t r) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (r >= 0x40)
				ret.uint64 = 0;
			else
				ret.uint64 <<= r;
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (r >= 0x20)
				ret.uint32 = 0;
			else
				ret.uint32 <<= r;
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddressDiff::operator>>(uint8_t r) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (r >= 0x40)
				ret.uint64 = ret.is_negative && ret.uint64 ? 1 : 0;
			else {
				bool should_increment = ret.is_negative && (ret.uint64 & ((1 << r) - 1));
				ret.uint64 >>= r;
				if (should_increment) ++ret.uint64;
			}
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			Win32DebuggingTargetAddressDiff ret(*this);
			if (r >= 0x20)
				ret.uint32 = ret.is_negative && ret.uint32 ? 1 : 0;
			else {
				bool should_increment = ret.is_negative && (ret.uint32 & ((1 << r) - 1));
				ret.uint32 >>= r;
				if (should_increment) ++ret.uint32;
			}
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddressDiff::IsEmpty() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return !this->uint64;
		case Win32Architecture::Win32Architecture_x86:
			return !this->uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddressDiff::IsMin() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return this->is_negative && this->uint64 == UINT64_MAX;
		case Win32Architecture::Win32Architecture_x86:
			return this->is_negative && this->uint32 == UINT32_MAX;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddressDiff::IsMax() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return !this->is_negative && this->uint64 == UINT64_MAX;
		case Win32Architecture::Win32Architecture_x86:
			return !this->is_negative && this->uint32 == UINT32_MAX;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	size_t Win32DebuggingTargetAddressDiff::Hash() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
			} data_source_hash { this->architecture };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		case Win32Architecture::Win32Architecture_x64: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_x64;
				bool is_negative = false;
				uint64_t uint64 = 0;
			} data_source_hash { this->architecture, this->is_negative && this->uint64, this->uint64 };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		case Win32Architecture::Win32Architecture_x86: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_x86;
				bool is_negative = false;
				uint32_t uint32 = 0;
			} data_source_hash { this->architecture, this->is_negative && this->uint32, this->uint32 };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::GetUint(void* buf_uint_to, size_t size_buf_uint_to) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			IException* err_inner = GenericUintToLarge((unsigned char)0, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			if (this->is_negative && this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, GetUint));
			IException* err_inner = GenericUintToLarge(this->uint64, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (this->is_negative && this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, GetUint));
			IException* err_inner = GenericUintToLarge(this->uint32, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::GetSint(void* buf_sint_to, size_t size_buf_sint_to) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			IException* err_inner = GenericSintToLarge((char)0, buf_sint_to, size_buf_sint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			unsigned char buf_sint_large[sizeof(uint64_t) + 1];
			unsigned char* p_low_buf_sint_large = nullptr;
			unsigned char* p_high_buf_sint_large = nullptr;
			if (*is_byte_order_le) {
				p_low_buf_sint_large = buf_sint_large;
				p_high_buf_sint_large = buf_sint_large + sizeof(uint64_t);
			} else if (*is_byte_order_be) {
				p_low_buf_sint_large = buf_sint_large + 1;
				p_high_buf_sint_large = buf_sint_large;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, GetSint));
			}
			if (this->is_negative && this->uint64) {
				uint64_t value_complement = ~(this->uint64 - 1);
				memcpy(p_low_buf_sint_large, &value_complement, sizeof(uint64_t));
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4245)
#endif
				*p_high_buf_sint_large = ~(unsigned char)0u;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
			} else {
				memcpy(p_low_buf_sint_large, &this->uint64, sizeof(uint64_t));
				*p_high_buf_sint_large = 0;
			}
			IException* err_inner = GenericSintBetweenLarge(buf_sint_to, size_buf_sint_to, buf_sint_large, sizeof(buf_sint_large));
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			unsigned char buf_sint_large[sizeof(uint32_t) + 1];
			unsigned char* p_low_buf_sint_large = nullptr;
			unsigned char* p_high_buf_sint_large = nullptr;
			if (*is_byte_order_le) {
				p_low_buf_sint_large = buf_sint_large;
				p_high_buf_sint_large = buf_sint_large + sizeof(uint32_t);
			} else if (*is_byte_order_be) {
				p_low_buf_sint_large = buf_sint_large + 1;
				p_high_buf_sint_large = buf_sint_large;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, GetSint));
			}
			if (this->is_negative && this->uint32) {
				uint32_t value_complement = ~(this->uint32 - 1);
				memcpy(p_low_buf_sint_large, &value_complement, sizeof(uint32_t));
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4245)
#endif
				*p_high_buf_sint_large = ~(unsigned char)0u;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
			} else {
				memcpy(p_low_buf_sint_large, &this->uint32, sizeof(uint32_t));
				*p_high_buf_sint_large = 0;
			}
			IException* err_inner = GenericSintBetweenLarge(buf_sint_to, size_buf_sint_to, buf_sint_large, sizeof(buf_sint_large));
			if (err_inner) throw(err_inner);
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::SetEmpty() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->is_negative = false;
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->is_negative = false;
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::SetMin() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->is_negative = true;
			this->uint64 = UINT64_MAX;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->is_negative = true;
			this->uint32 = UINT32_MAX;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::SetMax() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->is_negative = false;
			this->uint64 = UINT64_MAX;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->is_negative = false;
			this->uint32 = UINT32_MAX;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::SetUint(const void* buf_uint_from, size_t size_buf_uint_from) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			this->is_negative = false;
			IException* err_inner = GenericUintBetweenLarge(nullptr, 0, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			this->is_negative = false;
			IException* err_inner = GenericUintFromLarge(this->uint64, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			this->is_negative = false;
			IException* err_inner = GenericUintFromLarge(this->uint32, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddressDiff::SetSint(const void* buf_sint_from, size_t size_buf_sint_from) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			this->is_negative = false;
			IException* err_inner = GenericSintBetweenLarge(nullptr, 0, buf_sint_from, size_buf_sint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			unsigned char buf_sint_large[sizeof(uint64_t) + 1];
			unsigned char* p_low_buf_sint_large = nullptr;
			unsigned char* p_high_buf_sint_large = nullptr;
			if (*is_byte_order_le) {
				p_low_buf_sint_large = buf_sint_large;
				p_high_buf_sint_large = buf_sint_large + sizeof(uint64_t);
			} else if (*is_byte_order_be) {
				p_low_buf_sint_large = buf_sint_large + 1;
				p_high_buf_sint_large = buf_sint_large;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
			}
			IException* err_inner = GenericSintBetweenLarge(buf_sint_large, sizeof(buf_sint_large), buf_sint_from, size_buf_sint_from);
			if (err_inner) throw(err_inner);
			if (!*p_high_buf_sint_large) {
				this->is_negative = false;
				memcpy(&this->uint64, p_low_buf_sint_large, sizeof(uint64_t));
			} else if (*p_high_buf_sint_large == ~(unsigned char)0) {
				this->is_negative = true;
				uint64_t value_complement = 0;
				memcpy(&value_complement, p_low_buf_sint_large, sizeof(uint64_t));
				if (~value_complement == UINT64_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
				this->uint64 = (~value_complement) + 1;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
			}
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			unsigned char buf_sint_large[sizeof(uint32_t) + 1];
			unsigned char* p_low_buf_sint_large = nullptr;
			unsigned char* p_high_buf_sint_large = nullptr;
			if (*is_byte_order_le) {
				p_low_buf_sint_large = buf_sint_large;
				p_high_buf_sint_large = buf_sint_large + sizeof(uint32_t);
			} else if (*is_byte_order_be) {
				p_low_buf_sint_large = buf_sint_large + 1;
				p_high_buf_sint_large = buf_sint_large;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
			}
			IException* err_inner = GenericSintBetweenLarge(buf_sint_large, sizeof(buf_sint_large), buf_sint_from, size_buf_sint_from);
			if (err_inner) throw(err_inner);
			if (!*p_high_buf_sint_large) {
				this->is_negative = false;
				memcpy(&this->uint32, p_low_buf_sint_large, sizeof(uint32_t));
			} else if (*p_high_buf_sint_large == ~(unsigned char)0) {
				this->is_negative = true;
				uint32_t value_complement = 0;
				memcpy(&value_complement, p_low_buf_sint_large, sizeof(uint32_t));
				if (~value_complement == UINT32_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
				this->uint32 = (~value_complement) + 1;
			} else {
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddressDiff, SetSint));
			}
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	size_t Win32DebuggingTargetAddress::GetRawTargetAddressSize(Win32Architecture architecture) noexcept(false) {
		switch (architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return 0;
		case Win32Architecture::Win32Architecture_x64:
			return sizeof(uint64_t);
		case Win32Architecture::Win32Architecture_x86:
			return sizeof(uint32_t);
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress::Win32DebuggingTargetAddress(Win32Architecture _architecture) noexcept(false) : architecture(_architecture) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress::Win32DebuggingTargetAddress(const Win32DebuggingTargetAddress& x) noexcept(false) : architecture(x.architecture) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress::Win32DebuggingTargetAddress(Win32DebuggingTargetAddress&& x) noexcept(false) : architecture(x.architecture) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			x.uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			x.uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress::~Win32DebuggingTargetAddress() {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			abort();
		}
	}

	Win32DebuggingTargetAddress& Win32DebuggingTargetAddress::operator=(const Win32DebuggingTargetAddress& x) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		this->architecture = x.architecture;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		return *this;
	}

	Win32DebuggingTargetAddress& Win32DebuggingTargetAddress::operator=(Win32DebuggingTargetAddress&& x) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		this->architecture = x.architecture;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = x.uint64;
			x.uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = x.uint32;
			x.uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
		return *this;
	}

	bool Win32DebuggingTargetAddress::operator==(const Win32DebuggingTargetAddress& r) const noexcept(false) {
		if (this->architecture != r.architecture) return false;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return this->uint64 == r.uint64;
		case Win32Architecture::Win32Architecture_x86:
			return this->uint32 == r.uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddress::operator<(const Win32DebuggingTargetAddress& r) const noexcept(false) {
		if (this->architecture != r.architecture) return this->architecture < r.architecture;
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return false;
		case Win32Architecture::Win32Architecture_x64:
			return this->uint64 < r.uint64;
		case Win32Architecture::Win32Architecture_x86:
			return this->uint32 < r.uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddress::operator-(const Win32DebuggingTargetAddress& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64:
			if (this->uint64 < r.uint64) {
				Win32DebuggingTargetAddressDiff ret(this->architecture);
				ret.is_negative = true;
				ret.uint64 = r.uint64 - this->uint64;
				return ret;
			} else {
				Win32DebuggingTargetAddressDiff ret(this->architecture);
				ret.is_negative = false;
				ret.uint64 = this->uint64 - r.uint64;
				return ret;
			}
		case Win32Architecture::Win32Architecture_x86:
			if (this->uint32 < r.uint32) {
				Win32DebuggingTargetAddressDiff ret(this->architecture);
				ret.is_negative = true;
				ret.uint32 = r.uint32 - this->uint32;
				return ret;
			} else {
				Win32DebuggingTargetAddressDiff ret(this->architecture);
				ret.is_negative = false;
				ret.uint32 = this->uint32 - r.uint32;
				return ret;
			}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress Win32DebuggingTargetAddress::operator+(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator+));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddress(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64:
			if (r.is_negative) {
				if (r.uint64 > this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator+));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint64 -= r.uint64;
				return ret;
			} else {
				if (r.uint64 > UINT64_MAX - this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator+));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint64 += r.uint64;
				return ret;
			}
		case Win32Architecture::Win32Architecture_x86:
			if (r.is_negative) {
				if (r.uint32 > this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator+));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint32 -= r.uint32;
				return ret;
			} else {
				if (r.uint32 > UINT32_MAX - this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator+));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint32 += r.uint32;
				return ret;
			}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddress Win32DebuggingTargetAddress::operator-(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddress(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64:
			if (r.is_negative) {
				if (r.uint64 > UINT64_MAX - this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint64 += r.uint64;
				return ret;
			} else {
				if (r.uint64 > this->uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint64 -= r.uint64;
				return ret;
			}
		case Win32Architecture::Win32Architecture_x86:
			if (r.is_negative) {
				if (r.uint32 > UINT32_MAX - this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint32 += r.uint32;
				return ret;
			} else {
				if (r.uint32 > this->uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator-));
				Win32DebuggingTargetAddress ret(*this);
				ret.uint32 -= r.uint32;
				return ret;
			}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	Win32DebuggingTargetAddressDiff Win32DebuggingTargetAddress::operator%(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) {
		if (this->architecture != r.architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator%));
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return Win32DebuggingTargetAddressDiff(Win32Architecture::Win32Architecture_Invalid);
		case Win32Architecture::Win32Architecture_x64: {
			if (!r.uint64) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator%));
			Win32DebuggingTargetAddressDiff ret(this->architecture);
			ret.is_negative = false;
			ret.uint64 = mod_alignment(this->uint64, r.uint64);
			return ret;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (!r.uint32) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, operator%));
			Win32DebuggingTargetAddressDiff ret(this->architecture);
			ret.is_negative = false;
			ret.uint32 = mod_alignment(this->uint32, r.uint32);
			return ret;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddress::IsEmpty() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return !this->uint64;
		case Win32Architecture::Win32Architecture_x86:
			return !this->uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}
	bool Win32DebuggingTargetAddress::IsMin() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return !this->uint64;
		case Win32Architecture::Win32Architecture_x86:
			return !this->uint32;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	bool Win32DebuggingTargetAddress::IsMax() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			return true;
		case Win32Architecture::Win32Architecture_x64:
			return this->uint64 == UINT64_MAX;
		case Win32Architecture::Win32Architecture_x86:
			return this->uint32 == UINT32_MAX;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	size_t Win32DebuggingTargetAddress::Hash() const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
			} data_source_hash { this->architecture };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		case Win32Architecture::Win32Architecture_x64: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_x64;
				uint64_t uint64 = 0;
			} data_source_hash { this->architecture, this->uint64 };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		case Win32Architecture::Win32Architecture_x86: {
			struct data_source_hash_t {
				Win32Architecture architecture = Win32Architecture::Win32Architecture_x86;
				uint32_t uint32 = 0;
			} data_source_hash { this->architecture, this->uint32 };
			return hash_trivially_copyable_t<data_source_hash_t, size_t>()(data_source_hash);
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::GetUint(void* buf_uint_to, size_t size_buf_uint_to) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			IException* err_inner = GenericUintToLarge((unsigned char)0, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			IException* err_inner = GenericUintToLarge(this->uint64, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			IException* err_inner = GenericUintToLarge(this->uint32, buf_uint_to, size_buf_uint_to);
			if (err_inner) throw(err_inner);
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::GetRawTargetAddress(void* buf_rawtargetaddress_to, size_t size_buf_rawtargetaddress_to) const noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			if (size_buf_rawtargetaddress_to != 0) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, GetRawTargetAddress));
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			if (size_buf_rawtargetaddress_to != sizeof(uint64_t)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, GetRawTargetAddress));
			if (*is_byte_order_le) {
				memcpy(buf_rawtargetaddress_to, &this->uint64, sizeof(uint64_t));
			} else {
				for (size_t i = 0; i < sizeof(uint64_t); ++i) {
					*(reinterpret_cast<unsigned char*>(buf_rawtargetaddress_to) + i) = (this->uint64 >> (i * CHAR_BIT)) & ~(unsigned char)0;
				}
			}
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (size_buf_rawtargetaddress_to != sizeof(uint32_t)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, GetRawTargetAddress));
			if (*is_byte_order_le) {
				memcpy(buf_rawtargetaddress_to, &this->uint32, sizeof(uint32_t));
			} else {
				for (size_t i = 0; i < sizeof(uint32_t); ++i) {
					*(reinterpret_cast<unsigned char*>(buf_rawtargetaddress_to) + i) = (this->uint32 >> (i * CHAR_BIT)) & ~(unsigned char)0;
				}
			}
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void* Win32DebuggingTargetAddress::GetRawCurrentProcessAddress() const noexcept(false) {
		switch (this->architecture) {
#if defined(_M_AMD64) || defined(__amd64__)
		case Win32Architecture::Win32Architecture_x64: {
			return reinterpret_cast<void*>(this->uint64);
		}
#endif
#if defined (_M_IX86) || defined (__i386__)
		case Win32Architecture::Win32Architecture_x86: {
			return reinterpret_cast<void*>(this->uint32);
		}
#elif defined(_M_AMD64) || defined(__amd64__)
		case Win32Architecture::Win32Architecture_x86: {
			return reinterpret_cast<void*>(static_cast<uint64_t>(this->uint32));
		}
#endif
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, GetRawCurrentProcessAddress));
		}
	}

	void Win32DebuggingTargetAddress::SetEmpty() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::SetMin() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = 0;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = 0;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::SetMax() noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid:
			break;
		case Win32Architecture::Win32Architecture_x64:
			this->uint64 = UINT64_MAX;
			break;
		case Win32Architecture::Win32Architecture_x86:
			this->uint32 = UINT32_MAX;
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::SetUint(const void* buf_uint_from, size_t size_buf_uint_from) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			IException* err_inner = GenericUintBetweenLarge(nullptr, 0, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			IException* err_inner = GenericUintFromLarge(this->uint64, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			IException* err_inner = GenericUintFromLarge(this->uint32, buf_uint_from, size_buf_uint_from);
			if (err_inner) throw(err_inner);
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::SetRawTargetAddress(const void* buf_rawtargetaddress_from, size_t size_buf_rawtargetaddress_from) noexcept(false) {
		switch (this->architecture) {
		case Win32Architecture::Win32Architecture_Invalid: {
			if (size_buf_rawtargetaddress_from != 0) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, SetRawTargetAddress));
			break;
		}
		case Win32Architecture::Win32Architecture_x64: {
			if (size_buf_rawtargetaddress_from != sizeof(uint64_t)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, SetRawTargetAddress));
			if (*is_byte_order_le) {
				memcpy(&this->uint64, buf_rawtargetaddress_from, sizeof(uint64_t));
			} else {
				this->uint64 = 0;
				for (size_t i = 0; i < sizeof(uint64_t); ++i) {
					this->uint64 |= ((uint64_t)*(reinterpret_cast<const unsigned char*>(buf_rawtargetaddress_from) + i)) << (i * CHAR_BIT);
				}
			}
			break;
		}
		case Win32Architecture::Win32Architecture_x86: {
			if (size_buf_rawtargetaddress_from != sizeof(uint32_t)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, SetRawTargetAddress));
			if (*is_byte_order_le) {
				memcpy(&this->uint32, buf_rawtargetaddress_from, sizeof(uint32_t));
			} else {
				this->uint32 = 0;
				for (size_t i = 0; i < sizeof(uint32_t); ++i) {
					this->uint32 |= ((uint32_t)*(reinterpret_cast<const unsigned char*>(buf_rawtargetaddress_from) + i)) << (i * CHAR_BIT);
				}
			}
			break;
		}
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
	}

	void Win32DebuggingTargetAddress::SetRawCurrentProcessAddress(const volatile void* rawcurrentprocessaddress) noexcept(false) {
		switch (this->architecture) {
#if defined(_M_AMD64) || defined(__amd64__)
		case Win32Architecture::Win32Architecture_x64: {
			static_assert(sizeof(uintptr_t) == sizeof(uint64_t));
			this->uint64 = reinterpret_cast<uintptr_t>(rawcurrentprocessaddress);
			break;
		}
#endif
#if defined (_M_IX86) || defined (__i386__)
		case Win32Architecture::Win32Architecture_x86: {
			static_assert(sizeof(uintptr_t) == sizeof(uint32_t));
			this->uint32 = reinterpret_cast<uintptr_t>(rawcurrentprocessaddress);
			break;
		}
#elif defined(_M_AMD64) || defined(__amd64__)
		case Win32Architecture::Win32Architecture_x86: {
			static_assert(sizeof(uintptr_t) == sizeof(uint64_t));
			uint64_t uint64_rawcurrentprocessaddress = reinterpret_cast<uintptr_t>(rawcurrentprocessaddress);
			if (uint64_rawcurrentprocessaddress > UINT32_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, SetRawCurrentProcessAddress));
			this->uint32 = uint64_rawcurrentprocessaddress & ~(uint32_t)0;
			break;
		}
#endif
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetAddress, SetRawCurrentProcessAddress));
		}
	}

	Win32DebuggingSuspendThreadsInProcess::Win32DebuggingSuspendThreadsInProcess(
		const Win32HandleHolder& _win32handleholder_process,
		const ::std::unordered_set<DWORD>& _vec_threadid_exempted,
		const ::std::vector<::std::pair<Win32DebuggingTargetAddress, Win32DebuggingTargetAddress>> _vec_range_targetaddress_code_lock
	) noexcept(false) : win32handleholder_process(_win32handleholder_process),
		set_threadid_exempted(_vec_threadid_exempted.cbegin(), _vec_threadid_exempted.cend()) {
		this->architecture = Win32DebuggingProcess::GetProcessWin32Architecture(this->win32handleholder_process);
		for (const ::std::pair<Win32DebuggingTargetAddress, Win32DebuggingTargetAddress>& val_vec_range_targetaddress_code_lock : _vec_range_targetaddress_code_lock) {
			if (
				val_vec_range_targetaddress_code_lock.first > val_vec_range_targetaddress_code_lock.second
				|| val_vec_range_targetaddress_code_lock.first.GetWin32Architecture() != this->architecture
				|| val_vec_range_targetaddress_code_lock.second.GetWin32Architecture() != this->architecture
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(Win32DebuggingSuspendThreadsInProcess, Win32DebuggingSuspendThreadsInProcess));
			Win32DebuggingTargetAddress targetaddress_begin_range(val_vec_range_targetaddress_code_lock.first);
			Win32DebuggingTargetAddress targetaddress_end_range(val_vec_range_targetaddress_code_lock.second);
			map_targetaddress_code_lock_t::const_iterator it_map_targetaddress_code_lock_begin_merge, it_map_targetaddress_code_lock_end_merge;
			// Find the beginning of existing range boundaries whose ranges overlap with the range currently being processed.
			it_map_targetaddress_code_lock_begin_merge = this->map_targetaddress_code_lock.lower_bound(targetaddress_begin_range);
			if (
				it_map_targetaddress_code_lock_begin_merge != this->map_targetaddress_code_lock.cend()
				&& it_map_targetaddress_code_lock_begin_merge->second
				) {
				// If the boundary found is an upper boundary, go to the corresponding lower boundary instead.
				if (it_map_targetaddress_code_lock_begin_merge == this->map_targetaddress_code_lock.cbegin()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				--it_map_targetaddress_code_lock_begin_merge;
				if (it_map_targetaddress_code_lock_begin_merge->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				targetaddress_begin_range = it_map_targetaddress_code_lock_begin_merge->first;
			}
			// Find the end of existing range boundaries whose ranges overlap with the range currently being processed.
			it_map_targetaddress_code_lock_end_merge = this->map_targetaddress_code_lock.upper_bound(targetaddress_end_range);
			if (
				it_map_targetaddress_code_lock_end_merge != this->map_targetaddress_code_lock.cend()
				&& it_map_targetaddress_code_lock_end_merge->second
				) {
				// If the boundary found is an upper boundary, go to the corresponding lower boundary instead.
				if (it_map_targetaddress_code_lock_end_merge == this->map_targetaddress_code_lock.cbegin()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				targetaddress_end_range = it_map_targetaddress_code_lock_end_merge->first;
				++it_map_targetaddress_code_lock_end_merge;
				if (it_map_targetaddress_code_lock_end_merge != this->map_targetaddress_code_lock.cend() && it_map_targetaddress_code_lock_end_merge->second) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			}
			// Erase overlapping range boundaries.
			this->map_targetaddress_code_lock.erase(it_map_targetaddress_code_lock_begin_merge, it_map_targetaddress_code_lock_end_merge);
			// Insert new range boundaries.
			this->map_targetaddress_code_lock.insert(::std::make_pair(targetaddress_begin_range, false));
			this->map_targetaddress_code_lock.insert(::std::make_pair(targetaddress_end_range, true));
		}
	}

	Win32DebuggingSuspendThreadsInProcess::Win32DebuggingSuspendThreadsInProcess(Win32DebuggingSuspendThreadsInProcess&& x) noexcept(false)
		: has_suspended(::std::move(x.has_suspended)),
		win32handleholder_process(::std::move(x.win32handleholder_process)),
		architecture(::std::move(x.architecture)),
		set_threadid_exempted(::std::move(x.set_threadid_exempted)),
		map_targetaddress_code_lock(::std::move(x.map_targetaddress_code_lock)),
		list_thread_suspended(::std::move(x.list_thread_suspended)) {
		x.list_thread_suspended.clear();
		x.map_targetaddress_code_lock.clear();
		x.set_threadid_exempted.clear();
		x.architecture = Win32Architecture::Win32Architecture_Invalid;
		x.win32handleholder_process.reset();
		x.has_suspended = false;
	}

	Win32DebuggingSuspendThreadsInProcess& Win32DebuggingSuspendThreadsInProcess::operator=(Win32DebuggingSuspendThreadsInProcess&& x) noexcept(false) {
		this->list_thread_suspended.clear();
		this->map_targetaddress_code_lock.clear();
		this->set_threadid_exempted.clear();
		this->architecture = Win32Architecture::Win32Architecture_Invalid;
		this->win32handleholder_process.reset();
		this->has_suspended = false;
		this->has_suspended = ::std::move(x.has_suspended);
		x.has_suspended = false;
		this->win32handleholder_process = ::std::move(x.win32handleholder_process);
		x.win32handleholder_process.reset();
		this->architecture = ::std::move(x.architecture);
		x.architecture = Win32Architecture::Win32Architecture_Invalid;
		this->set_threadid_exempted = ::std::move(x.set_threadid_exempted);
		x.set_threadid_exempted.clear();
		this->map_targetaddress_code_lock = ::std::move(x.map_targetaddress_code_lock);
		x.map_targetaddress_code_lock.clear();
		this->list_thread_suspended = ::std::move(x.list_thread_suspended);
		x.list_thread_suspended.clear();
		return *this;
	}

	void Win32DebuggingSuspendThreadsInProcess::AddExemptedThread(DWORD threadid) noexcept(false) {
		this->set_threadid_exempted.insert(threadid);
	}

	void Win32DebuggingSuspendThreadsInProcess::RemoveExemptedThread(DWORD threadid) noexcept(false) {
		this->set_threadid_exempted.erase(threadid);
	}

	void Win32DebuggingSuspendThreadsInProcess::SuspendThreads() noexcept(false) {
		this->has_suspended = true;
		this->UpdateThreadSuspendResume();
	}

	void Win32DebuggingSuspendThreadsInProcess::ResumeThreads() noexcept {
		if (this->win32handleholder_process) {
			this->has_suspended = false;
			try {
				this->UpdateThreadSuspendResume();
			} catch (...) {
				abort();
			}
		}
	}

	void Win32DebuggingSuspendThreadsInProcess::UpdateThreadSuspendResume() noexcept(false) {
		if (!this->win32handleholder_process) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(Win32DebuggingSuspendThreadsInProcess, UpdateThreadSuspendResume));
		DWORD processid_process_current = GetCurrentProcessId();
		DWORD processid_process_target = GetProcessId(this->win32handleholder_process.get());
		if (!processid_process_target) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetProcessId));
		DWORD threadid_thread_current = GetCurrentThreadId();
		if (this->has_suspended) {
			bool is_stable = false;
			do {
				is_stable = true;
				std::vector<Win32HandleHolder> vec_win32handleholder_thread;
				{
					Win32HandleHolder win32handleholder_snapshot(Win32HandleHolder::own_handle, CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processid_process_target));
					if (!win32handleholder_snapshot) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CreateToolhelp32Snapshot));
					bool has_finished = false;
					if (!has_finished) {
						THREADENTRY32 threadentry32;
						memset(&threadentry32, 0, sizeof(THREADENTRY32));
						threadentry32.dwSize = sizeof(THREADENTRY32);
						if (Thread32First(win32handleholder_snapshot.get(), &threadentry32)) {
							if (
								threadentry32.th32OwnerProcessID == processid_process_target
								&& !(threadentry32.th32OwnerProcessID == processid_process_current && threadentry32.th32ThreadID == threadid_thread_current)
								&& !this->set_threadid_exempted.count(threadentry32.th32ThreadID)
								) {
								Win32HandleHolder win32handleholder_thread(
									Win32HandleHolder::own_handle,
									OpenThread(THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | READ_CONTROL, FALSE, threadentry32.th32ThreadID)
								);
								if (win32handleholder_thread) {
									DWORD processid_process_thread = GetProcessIdOfThread(win32handleholder_thread.get());
									if (!processid_process_thread) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetProcessIdOfThread));
									DWORD threadid_thread = GetThreadId(win32handleholder_thread.get());
									if (!threadid_thread) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadId));
									if (processid_process_thread != threadentry32.th32OwnerProcessID || threadid_thread != threadentry32.th32ThreadID) {
										is_stable = false;
									} else {
										vec_win32handleholder_thread.push_back(win32handleholder_thread);
									}
								}
							}
						} else {
							if (GetLastError() == ERROR_NO_MORE_FILES)
								has_finished = true;
							else
								throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(Thread32First));
						}
					}
					while (!has_finished) {
						THREADENTRY32 threadentry32;
						memset(&threadentry32, 0, sizeof(THREADENTRY32));
						threadentry32.dwSize = sizeof(THREADENTRY32);
						if (Thread32Next(win32handleholder_snapshot.get(), &threadentry32)) {
							if (
								threadentry32.th32OwnerProcessID == processid_process_target
								&& !(threadentry32.th32OwnerProcessID == processid_process_current && threadentry32.th32ThreadID == threadid_thread_current)
								&& !this->set_threadid_exempted.count(threadentry32.th32ThreadID)
								) {
								Win32HandleHolder win32handleholder_thread(
									Win32HandleHolder::own_handle,
									OpenThread(THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | READ_CONTROL, FALSE, threadentry32.th32ThreadID)
								);
								if (win32handleholder_thread) {
									DWORD processid_process_thread = GetProcessIdOfThread(win32handleholder_thread.get());
									if (!processid_process_thread) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetProcessIdOfThread));
									DWORD threadid_thread = GetThreadId(win32handleholder_thread.get());
									if (!threadid_thread) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadId));
									if (processid_process_thread != threadentry32.th32OwnerProcessID || threadid_thread != threadentry32.th32ThreadID) {
										is_stable = false;
									} else {
										vec_win32handleholder_thread.push_back(win32handleholder_thread);
									}
								}
							}
						} else {
							if (GetLastError() == ERROR_NO_MORE_FILES)
								has_finished = true;
							else
								throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(Thread32Next));
						}
					}
				}
				::std::unordered_map<DWORD, list_thread_suspended_t::iterator> map_thread_suspended_remaining;
				for (list_thread_suspended_t::iterator it_list_thread_suspended = this->list_thread_suspended.begin(); it_list_thread_suspended != this->list_thread_suspended.end(); ++it_list_thread_suspended) {
					DWORD threadid_thread_suspended = GetThreadId(it_list_thread_suspended->first.get());
					if (!threadid_thread_suspended) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadId));
					map_thread_suspended_remaining.insert(::std::make_pair(threadid_thread_suspended, it_list_thread_suspended));
				}
				for (const Win32HandleHolder& val_vec_win32handleholder_thread : vec_win32handleholder_thread) {
					DWORD threadid_thread = GetThreadId(val_vec_win32handleholder_thread.get());
					if (!threadid_thread) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadId));
					bool should_suspend = false;
					if (!map_thread_suspended_remaining.count(threadid_thread)) {
						should_suspend = true;
					} else {
						list_thread_suspended_t::iterator it_list_thread_suspended = map_thread_suspended_remaining.at(threadid_thread);
						{
							map_targetaddress_code_lock_t::const_iterator it_map_targetaddress_code_lock = this->map_targetaddress_code_lock.upper_bound(it_list_thread_suspended->second);
							if (
								it_map_targetaddress_code_lock != this->map_targetaddress_code_lock.cend()
								&& it_map_targetaddress_code_lock->second
								) {
								if (ResumeThread(val_vec_win32handleholder_thread.get()) == static_cast<DWORD>(-1)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ResumeThread));
								this->list_thread_suspended.erase(it_list_thread_suspended);
								if (SleepEx(Win32DebuggingSuspendThreadsInProcess::timeduration_sleep_retry_suspend, FALSE)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SleepEx));
								should_suspend = true;
							}
						}
						map_thread_suspended_remaining.erase(threadid_thread);
					}
					if (should_suspend) {
						bool should_retry_suspend = false;
						do {
							if (SuspendThread(val_vec_win32handleholder_thread.get()) == static_cast<DWORD>(-1)) {
								DWORD waitresult = WaitForSingleObject(val_vec_win32handleholder_thread.get(), 0);
								if (waitresult == WAIT_OBJECT_0)
									throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SuspendThread));
								else if (waitresult != WAIT_TIMEOUT)
									throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WaitForSingleObject));
							} else {
								try {
									is_stable = false;
									Win32DebuggingTargetAddress targetaddress_programcounter(architecture);
									switch (architecture) {
#if defined(_M_AMD64) || defined(__amd64__)
									case Win32Architecture::Win32Architecture_x64: {
										CONTEXT context;
										memset(&context, 0, sizeof(CONTEXT));
										context.ContextFlags = CONTEXT_CONTROL;
										if (!GetThreadContext(val_vec_win32handleholder_thread.get(), &context)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadContext));
										targetaddress_programcounter.SetInt(context.Rip);
										break;
									}
									case Win32Architecture::Win32Architecture_x86: {
										WOW64_CONTEXT context;
										memset(&context, 0, sizeof(WOW64_CONTEXT));
										context.ContextFlags = WOW64_CONTEXT_CONTROL;
										if (!Wow64GetThreadContext(val_vec_win32handleholder_thread.get(), &context)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(Wow64GetThreadContext));
										targetaddress_programcounter.SetInt(context.Eip);
										break;
									}
#elif defined (_M_IX86) || defined (__i386__)
									case Win32Architecture::Win32Architecture_x86: {
										CONTEXT context;
										memset(&context, 0, sizeof(CONTEXT));
										context.ContextFlags = CONTEXT_CONTROL;
										if (!GetThreadContext(val_vec_win32handleholder_thread.get(), &context)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadContext));
										targetaddress_programcounter.SetInt(context.Eip);
										break;
									}
#else
#error Unrecognized architecture.
#endif
									default:
										throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
									}
									{
										map_targetaddress_code_lock_t::const_iterator it_map_targetaddress_code_lock = this->map_targetaddress_code_lock.upper_bound(targetaddress_programcounter);
										if (
											it_map_targetaddress_code_lock != this->map_targetaddress_code_lock.cend()
											&& it_map_targetaddress_code_lock->second
											) {
											should_retry_suspend = true;
										}
									}
									if (!should_retry_suspend) this->list_thread_suspended.push_back(::std::make_pair(val_vec_win32handleholder_thread, targetaddress_programcounter));
								} catch (...) {
									if (ResumeThread(val_vec_win32handleholder_thread.get()) == static_cast<DWORD>(-1)) abort();
									throw;
								}
								if (should_retry_suspend) {
									if (ResumeThread(val_vec_win32handleholder_thread.get()) == static_cast<DWORD>(-1)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ResumeThread));
									if (SleepEx(Win32DebuggingSuspendThreadsInProcess::timeduration_sleep_retry_suspend, FALSE)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SleepEx));
								}
							}
						} while (should_retry_suspend);
					}
				}
				if (map_thread_suspended_remaining.size()) {
					is_stable = false;
					list_thread_suspended_t::iterator it_list_thread_suspended = this->list_thread_suspended.begin();
					while (it_list_thread_suspended != this->list_thread_suspended.end()) {
						list_thread_suspended_t::iterator it_list_thread_suspended_current = it_list_thread_suspended++;
						DWORD threadid_thread_suspended = GetThreadId(it_list_thread_suspended_current->first.get());
						if (!threadid_thread_suspended) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetThreadId));
						if (map_thread_suspended_remaining.count(threadid_thread_suspended)) {
							if (ResumeThread(it_list_thread_suspended_current->first.get()) == static_cast<DWORD>(-1)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ResumeThread));
							this->list_thread_suspended.erase(it_list_thread_suspended_current);
						}
					}
				}
			} while (!is_stable);
		} else {
			list_thread_suspended_t::iterator it_list_thread_suspended = this->list_thread_suspended.begin();
			while (it_list_thread_suspended != this->list_thread_suspended.end()) {
				list_thread_suspended_t::iterator it_list_thread_suspended_current = it_list_thread_suspended++;
				if (ResumeThread(it_list_thread_suspended_current->first.get()) == static_cast<DWORD>(-1)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ResumeThread));
				this->list_thread_suspended.erase(it_list_thread_suspended_current);
			}
		}
	}

	Win32DebuggingTargetMemoryRegionInfo::Win32DebuggingTargetMemoryRegionInfo(Win32Architecture _architecture) noexcept(false)
		: architecture(_architecture),
		addr_base(_architecture),
		addr_base_alloc(_architecture),
		size(_architecture) {}

	Win32DebuggingTargetMemoryRegionInfo::Win32DebuggingTargetMemoryRegionInfo(
		Win32Architecture _architecture,
		const Win32DebuggingTargetAddress& _addr_base,
		const Win32DebuggingTargetAddress& _addr_base_alloc,
		const Win32DebuggingTargetAddressDiff& _size,
		DWORD _protect,
		DWORD _protect_alloc,
		DWORD _state,
		DWORD _type
	) noexcept(false)
		: architecture(_architecture),
		addr_base(_addr_base),
		addr_base_alloc(_addr_base_alloc),
		size(_size),
		protect(_protect),
		protect_alloc(_protect_alloc),
		state(_state),
		type(_type) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, Win32DebuggingTargetMemoryRegionInfo));
		if (this->addr_base_alloc.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, Win32DebuggingTargetMemoryRegionInfo));
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, Win32DebuggingTargetMemoryRegionInfo));
	}

	Win32DebuggingTargetMemoryRegionInfo::Win32DebuggingTargetMemoryRegionInfo(const Win32DebuggingTargetMemoryRegionInfo& x) noexcept(false)
		: architecture(x.architecture),
		addr_base(x.addr_base),
		addr_base_alloc(x.addr_base_alloc),
		size(x.size),
		protect(x.protect),
		protect_alloc(x.protect_alloc),
		state(x.state),
		type(x.type) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_base_alloc.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
	}

	Win32DebuggingTargetMemoryRegionInfo::Win32DebuggingTargetMemoryRegionInfo(Win32DebuggingTargetMemoryRegionInfo&& x) noexcept(false)
		: architecture(x.architecture),
		addr_base(::std::move(x.addr_base)),
		addr_base_alloc(::std::move(x.addr_base_alloc)),
		size(::std::move(x.size)),
		protect(::std::move(x.protect)),
		protect_alloc(::std::move(x.protect_alloc)),
		state(::std::move(x.state)),
		type(::std::move(x.type)) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_base_alloc.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		x.type = 0;
		x.state = 0;
		x.protect_alloc = 0;
		x.protect = 0;
		x.size.SetEmpty();
		x.addr_base_alloc.SetEmpty();
		x.addr_base.SetEmpty();
	}

	Win32DebuggingTargetMemoryRegionInfo::~Win32DebuggingTargetMemoryRegionInfo() {
		this->type = 0;
		this->state = 0;
		this->protect_alloc = 0;
		this->protect = 0;
		this->size.SetEmpty();
		this->addr_base_alloc.SetEmpty();
		this->addr_base.SetEmpty();
	}

	Win32DebuggingTargetMemoryRegionInfo& Win32DebuggingTargetMemoryRegionInfo::operator=(const Win32DebuggingTargetMemoryRegionInfo& x) noexcept(false) {
		this->type = 0;
		this->state = 0;
		this->protect_alloc = 0;
		this->protect = 0;
		this->size.SetEmpty();
		this->addr_base_alloc.SetEmpty();
		this->addr_base.SetEmpty();
		this->architecture = x.architecture;
		this->addr_base = x.addr_base;
		this->addr_base_alloc = x.addr_base_alloc;
		this->size = x.size;
		this->protect = x.protect;
		this->protect_alloc = x.protect_alloc;
		this->state = x.state;
		this->type = x.type;
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_base_alloc.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	Win32DebuggingTargetMemoryRegionInfo& Win32DebuggingTargetMemoryRegionInfo::operator=(Win32DebuggingTargetMemoryRegionInfo&& x) noexcept(false) {
		this->type = 0;
		this->state = 0;
		this->protect_alloc = 0;
		this->protect = 0;
		this->size.SetEmpty();
		this->addr_base_alloc.SetEmpty();
		this->addr_base.SetEmpty();
		this->architecture = x.architecture;
		this->addr_base = ::std::move(x.addr_base);
		x.addr_base.SetEmpty();
		this->addr_base_alloc = ::std::move(x.addr_base_alloc);
		x.addr_base_alloc.SetEmpty();
		this->size = ::std::move(x.size);
		x.size.SetEmpty();
		this->protect = ::std::move(x.protect);
		x.protect = 0;
		this->protect_alloc = ::std::move(x.protect_alloc);
		x.protect_alloc = 0;
		this->state = ::std::move(x.state);
		x.state = 0;
		this->type = ::std::move(x.type);
		x.type = 0;
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_base_alloc.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept {
		if (!targetaddress_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetBaseAddress);
		*targetaddress_ret = &this->addr_base;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetAllocationBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept {
		if (!targetaddress_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetAllocationBaseAddress);
		*targetaddress_ret = &this->addr_base_alloc;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept {
		if (!size_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetSize);
		*size_ret = &this->size;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetProtect(DWORD* protect_ret) const noexcept {
		if (!protect_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetProtect);
		*protect_ret = this->protect;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetAllocationProtect(DWORD* protect_ret) const noexcept {
		if (!protect_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetAllocationProtect);
		*protect_ret = this->protect_alloc;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetState(DWORD* state_ret) const noexcept {
		if (!state_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetState);
		*state_ret = this->state;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::GetType(DWORD* type_ret) const noexcept {
		if (!type_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, GetType);
		*type_ret = this->type;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept {
		if (!_targetaddress || _targetaddress->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, SetBaseAddress);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_targetaddress, &err_inner]() noexcept(false)->void {
				this->addr_base = *_targetaddress;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetAllocationBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept {
		if (!_targetaddress || _targetaddress->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, SetAllocationBaseAddress);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_targetaddress, &err_inner]() noexcept(false)->void {
				this->addr_base_alloc = *_targetaddress;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept {
		if (!_size || _size->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetMemoryRegionInfo, SetSize);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_size, &err_inner]() noexcept(false)->void {
				this->size = *_size;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetProtect(DWORD _protect) noexcept {
		this->protect = _protect;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetAllocationProtect(DWORD _protect) noexcept {
		this->protect_alloc = _protect;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetState(DWORD _state) noexcept {
		this->state = _state;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetMemoryRegionInfo::SetType(DWORD _type) noexcept {
		this->type = _type;
		return nullptr;
	}

	Win32DebuggingTargetExecutableModuleInfo::Win32DebuggingTargetExecutableModuleInfo(Win32Architecture _architecture) noexcept(false)
		: architecture(_architecture),
		addr_base(_architecture),
		size(_architecture),
		name_module(rawallocator_crt_module_local),
		path_module(rawallocator_crt_module_local) {}

	Win32DebuggingTargetExecutableModuleInfo::Win32DebuggingTargetExecutableModuleInfo(
		Win32Architecture _architecture,
		const Win32DebuggingTargetAddress& _addr_base,
		const Win32DebuggingTargetAddressDiff& _size,
		const char* _name_module,
		size_t _size_name_module,
		const char* _path_module,
		size_t _size_path_module
	) noexcept(false)
		: architecture(_architecture),
		addr_base(_addr_base),
		size(_size),
		name_module(rawallocator_crt_module_local),
		path_module(rawallocator_crt_module_local) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo));
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo));
		if (_size_name_module && !_name_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo));
		if (_size_path_module && !_path_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo));
		name_module.construct(_size_name_module, objholder_rawallocator_t<char[]>::construct_obj, _name_module);
		path_module.construct(_size_path_module, objholder_rawallocator_t<char[]>::construct_obj, _path_module);
	}

	Win32DebuggingTargetExecutableModuleInfo::Win32DebuggingTargetExecutableModuleInfo(const Win32DebuggingTargetExecutableModuleInfo& x) noexcept(false)
		: architecture(x.architecture),
		addr_base(x.addr_base),
		size(x.size),
		name_module(rawallocator_crt_module_local, x.name_module.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.name_module),
		path_module(rawallocator_crt_module_local, x.path_module.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.path_module) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
	}

	Win32DebuggingTargetExecutableModuleInfo::Win32DebuggingTargetExecutableModuleInfo(Win32DebuggingTargetExecutableModuleInfo&& x) noexcept(false)
		: architecture(x.architecture),
		addr_base(::std::move(x.addr_base)),
		size(::std::move(x.size)),
		name_module(::std::move(x.name_module)),
		path_module(::std::move(x.path_module)) {
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		x.path_module.free();
		x.name_module.free();
		x.size.SetEmpty();
		x.addr_base.SetEmpty();
	}

	Win32DebuggingTargetExecutableModuleInfo::~Win32DebuggingTargetExecutableModuleInfo() {
		this->path_module.free();
		this->name_module.free();
		this->size.SetEmpty();
		this->addr_base.SetEmpty();
	}

	Win32DebuggingTargetExecutableModuleInfo& Win32DebuggingTargetExecutableModuleInfo::operator=(const Win32DebuggingTargetExecutableModuleInfo& x) noexcept(false) {
		this->path_module.free();
		this->name_module.free();
		this->size.SetEmpty();
		this->addr_base.SetEmpty();
		this->architecture = x.architecture;
		this->addr_base = x.addr_base;
		this->size = x.size;
		this->name_module.construct(x.name_module.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.name_module);
		this->path_module.construct(x.path_module.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.path_module);
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	Win32DebuggingTargetExecutableModuleInfo& Win32DebuggingTargetExecutableModuleInfo::operator=(Win32DebuggingTargetExecutableModuleInfo&& x) noexcept(false) {
		this->path_module.free();
		this->name_module.free();
		this->size.SetEmpty();
		this->addr_base.SetEmpty();
		this->architecture = x.architecture;
		this->addr_base = ::std::move(x.addr_base);
		x.addr_base.SetEmpty();
		this->size = ::std::move(x.size);
		x.size.SetEmpty();
		this->name_module = ::std::move(x.name_module);
		x.name_module.free();
		this->path_module = ::std::move(x.path_module);
		x.path_module.free();
		if (this->addr_base.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->size.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept {
		if (!targetaddress_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, GetBaseAddress);
		*targetaddress_ret = &this->addr_base;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept {
		if (!size_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, GetSize);
		*size_ret = &this->size;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::GetModuleName(const char** name_module_ret, size_t* size_name_module_ret) const noexcept {
		if (!name_module_ret || !size_name_module_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, GetModuleName);
		*name_module_ret = this->name_module.get();
		*size_name_module_ret = this->name_module.get_count();
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::GetModulePath(const char** path_module_ret, size_t* size_path_module_ret) const noexcept {
		if (!path_module_ret || !size_path_module_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, GetModulePath);
		*path_module_ret = this->path_module.get();
		*size_path_module_ret = this->path_module.get_count();
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept {
		if (!_targetaddress || _targetaddress->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, SetBaseAddress);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_targetaddress, &err_inner]() noexcept(false)->void {
				this->addr_base = *_targetaddress;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept {
		if (!_size || _size->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, SetSize);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_size, &err_inner]() noexcept(false)->void {
				this->size = *_size;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::SetModuleName(const char* _name_module, size_t _size_name_module) noexcept {
		if (_size_name_module && !_name_module) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, SetModuleName);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_name_module, _size_name_module, &err_inner]() noexcept(false)->void {
				this->name_module.construct(_size_name_module, objholder_rawallocator_t<char[]>::construct_obj, _name_module);
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExecutableModuleInfo::SetModulePath(const char* _path_module, size_t _size_path_module) noexcept {
		if (_size_path_module && !_path_module) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, SetModulePath);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_path_module, _size_path_module, &err_inner]() noexcept(false)->void {
				this->path_module.construct(_size_path_module, objholder_rawallocator_t<char[]>::construct_obj, _path_module);
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(Win32Architecture _architecture) noexcept(false)
		: architecture(_architecture),
		name_export(rawallocator_crt_module_local),
		rva_export(_architecture),
		str_forward_export(rawallocator_crt_module_local),
		addr_resolved(_architecture) {}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(
		Win32Architecture _architecture,
		const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
		DWORD _ordinal_export,
		const Win32DebuggingTargetAddressDiff& _rva_export
	) noexcept(false)
		: architecture(_architecture),
		info_module_export(_info_module_export),
		ordinal_export(_ordinal_export),
		has_name_export(false),
		name_export(rawallocator_crt_module_local),
		rva_export(_rva_export),
		is_forwarder_export(false),
		str_forward_export(rawallocator_crt_module_local),
		addr_resolved(_architecture) {
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(
		Win32Architecture _architecture,
		const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
		DWORD _ordinal_export,
		const char* _name_export,
		size_t _size_name_export,
		const Win32DebuggingTargetAddressDiff& _rva_export
	) noexcept(false)
		: architecture(_architecture),
		info_module_export(_info_module_export),
		ordinal_export(_ordinal_export),
		has_name_export(true),
		name_export(rawallocator_crt_module_local),
		rva_export(_rva_export),
		is_forwarder_export(false),
		str_forward_export(rawallocator_crt_module_local),
		addr_resolved(_architecture) {
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		if (_size_name_export && !_name_export) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		name_export.construct(_size_name_export, objholder_rawallocator_t<char[]>::construct_obj, _name_export);
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(
		Win32Architecture _architecture,
		const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
		DWORD _ordinal_export,
		const Win32DebuggingTargetAddressDiff& _rva_export,
		const char* _str_forward_export,
		size_t _size_str_forward_export
	) noexcept(false)
		: architecture(_architecture),
		info_module_export(_info_module_export),
		ordinal_export(_ordinal_export),
		has_name_export(false),
		name_export(rawallocator_crt_module_local),
		rva_export(_rva_export),
		is_forwarder_export(true),
		str_forward_export(rawallocator_crt_module_local),
		addr_resolved(_architecture) {
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		if (_size_str_forward_export && !_str_forward_export) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		str_forward_export.construct(_size_str_forward_export, objholder_rawallocator_t<char[]>::construct_obj, _str_forward_export);
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(
		Win32Architecture _architecture,
		const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
		DWORD _ordinal_export,
		const char* _name_export,
		size_t _size_name_export,
		const Win32DebuggingTargetAddressDiff& _rva_export,
		const char* _str_forward_export,
		size_t _size_str_forward_export
	) noexcept(false)
		: architecture(_architecture),
		info_module_export(_info_module_export),
		ordinal_export(_ordinal_export),
		has_name_export(true),
		name_export(rawallocator_crt_module_local),
		rva_export(_rva_export),
		is_forwarder_export(true),
		str_forward_export(rawallocator_crt_module_local),
		addr_resolved(_architecture) {
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		if (_size_name_export && !_name_export) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		if (_size_str_forward_export && !_str_forward_export) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, Win32DebuggingTargetExportSymbolInfo));
		name_export.construct(_size_name_export, objholder_rawallocator_t<char[]>::construct_obj, _name_export);
		str_forward_export.construct(_size_str_forward_export, objholder_rawallocator_t<char[]>::construct_obj, _str_forward_export);
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(const Win32DebuggingTargetExportSymbolInfo& x) noexcept(false)
		: architecture(x.architecture),
		info_module_export(x.info_module_export),
		ordinal_export(x.ordinal_export),
		has_name_export(x.has_name_export),
		name_export(rawallocator_crt_module_local, x.name_export.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.name_export),
		rva_export(x.rva_export),
		is_forwarder_export(x.is_forwarder_export),
		str_forward_export(rawallocator_crt_module_local, x.str_forward_export.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.str_forward_export),
		is_set_addr_resolved(x.is_set_addr_resolved),
		addr_resolved(x.addr_resolved) {
		if (this->info_module_export && this->info_module_export->GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->has_name_export && this->name_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->is_forwarder_export && this->str_forward_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_resolved.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
	}

	Win32DebuggingTargetExportSymbolInfo::Win32DebuggingTargetExportSymbolInfo(Win32DebuggingTargetExportSymbolInfo&& x) noexcept(false)
		: architecture(x.architecture),
		info_module_export(::std::move(x.info_module_export)),
		ordinal_export(::std::move(x.ordinal_export)),
		has_name_export(::std::move(x.has_name_export)),
		name_export(::std::move(x.name_export)),
		rva_export(::std::move(x.rva_export)),
		is_forwarder_export(::std::move(x.is_forwarder_export)),
		str_forward_export(::std::move(x.str_forward_export)),
		is_set_addr_resolved(::std::move(x.is_set_addr_resolved)),
		addr_resolved(::std::move(x.addr_resolved)) {
		if (this->info_module_export && this->info_module_export->GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->has_name_export && this->name_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->is_forwarder_export && this->str_forward_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_resolved.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		x.addr_resolved.SetEmpty();
		x.is_set_addr_resolved = false;
		x.str_forward_export.free();
		x.is_forwarder_export = false;
		x.rva_export.SetEmpty();
		x.name_export.free();
		x.has_name_export = false;
		x.ordinal_export = 0;
		x.info_module_export.reset();
	}

	Win32DebuggingTargetExportSymbolInfo::~Win32DebuggingTargetExportSymbolInfo() {
		this->addr_resolved.SetEmpty();
		this->is_set_addr_resolved = false;
		this->str_forward_export.free();
		this->is_forwarder_export = false;
		this->rva_export.SetEmpty();
		this->name_export.free();
		this->has_name_export = false;
		this->ordinal_export = 0;
		this->info_module_export.reset();
	}

	Win32DebuggingTargetExportSymbolInfo& Win32DebuggingTargetExportSymbolInfo::operator=(const Win32DebuggingTargetExportSymbolInfo& x) noexcept(false) {
		this->addr_resolved.SetEmpty();
		this->is_set_addr_resolved = false;
		this->str_forward_export.free();
		this->is_forwarder_export = false;
		this->rva_export.SetEmpty();
		this->name_export.free();
		this->has_name_export = false;
		this->ordinal_export = 0;
		this->info_module_export.reset();
		this->architecture = x.architecture;
		this->info_module_export = x.info_module_export;
		this->ordinal_export = x.ordinal_export;
		this->has_name_export = x.has_name_export;
		this->name_export.construct(x.name_export.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.name_export);
		this->rva_export = x.rva_export;
		this->is_forwarder_export = x.is_forwarder_export;
		this->str_forward_export.construct(x.str_forward_export.get_count(), objholder_rawallocator_t<char[]>::construct_obj, x.str_forward_export);
		this->is_set_addr_resolved = x.is_set_addr_resolved;
		this->addr_resolved = x.addr_resolved;
		if (this->info_module_export && this->info_module_export->GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->has_name_export && this->name_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->is_forwarder_export && this->str_forward_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_resolved.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	Win32DebuggingTargetExportSymbolInfo& Win32DebuggingTargetExportSymbolInfo::operator=(Win32DebuggingTargetExportSymbolInfo&& x) noexcept(false) {
		this->addr_resolved.SetEmpty();
		this->is_set_addr_resolved = false;
		this->str_forward_export.free();
		this->is_forwarder_export = false;
		this->rva_export.SetEmpty();
		this->name_export.free();
		this->has_name_export = false;
		this->ordinal_export = 0;
		this->info_module_export.reset();
		this->architecture = x.architecture;
		this->info_module_export = ::std::move(x.info_module_export);
		x.info_module_export.reset();
		this->ordinal_export = ::std::move(x.ordinal_export);
		x.ordinal_export = 0;
		this->has_name_export = ::std::move(x.has_name_export);
		x.has_name_export = false;
		this->name_export = ::std::move(x.name_export);
		x.name_export.free();
		this->rva_export = ::std::move(x.rva_export);
		x.rva_export.SetEmpty();
		this->is_forwarder_export = ::std::move(x.is_forwarder_export);
		x.is_forwarder_export = false;
		this->str_forward_export = ::std::move(x.str_forward_export);
		x.str_forward_export.free();
		this->is_set_addr_resolved = ::std::move(x.is_set_addr_resolved);
		x.is_set_addr_resolved = false;
		this->addr_resolved = ::std::move(x.addr_resolved);
		x.addr_resolved.SetEmpty();
		if (this->info_module_export && this->info_module_export->GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->has_name_export && this->name_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->rva_export.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (!this->is_forwarder_export && this->str_forward_export.get_count()) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		if (this->addr_resolved.GetWin32Architecture() != this->architecture) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		return *this;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetExportModuleInfo(const IWin32DebuggingTargetExecutableModuleInfo** info_module_ret) const noexcept {
		if (!info_module_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportModuleInfo);
		*info_module_ret = this->info_module_export.get();
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetExportOrdinal(DWORD* ordinal_ret) const noexcept {
		if (!ordinal_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportOrdinal);
		*ordinal_ret = this->ordinal_export;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetHasExportName(bool* has_name_ret) const noexcept {
		if (!has_name_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetHasExportName);
		*has_name_ret = this->has_name_export;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetExportName(const char** name_export_ret, size_t* size_name_export_ret) const noexcept {
		if (!name_export_ret || !size_name_export_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportName);
		*name_export_ret = this->name_export.get();
		*size_name_export_ret = this->name_export.get_count();
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetExportRva(const Win32DebuggingTargetAddressDiff** rva_ret) const noexcept {
		if (!rva_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportRva);
		*rva_ret = &this->rva_export;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetIsExportForwarder(bool* is_forwarder_ret) const noexcept {
		if (!is_forwarder_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetIsExportForwarder);
		*is_forwarder_ret = this->is_forwarder_export;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetExportForwardString(const char** str_forward_export_ret, size_t* size_str_forward_export_ret) const noexcept {
		if (!this->is_forwarder_export) return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportForwardString);
		if (!str_forward_export_ret || !size_str_forward_export_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetExportForwardString);
		*str_forward_export_ret = this->str_forward_export.get();
		*size_str_forward_export_ret = this->str_forward_export.get_count();
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetIsExportResolvedAddressSet(bool* is_set_addr_resolved_ret) const noexcept {
		if (!is_set_addr_resolved_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetIsExportResolvedAddressSet);
		*is_set_addr_resolved_ret = this->is_set_addr_resolved;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::GetResolvedAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept {
		if (!this->is_set_addr_resolved) return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetResolvedAddress);
		if (!targetaddress_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExportSymbolInfo, GetResolvedAddress);
		*targetaddress_ret = &this->addr_resolved;
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::ClearResolvedAddress() noexcept {
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &err_inner]() noexcept(false)->void {
				this->addr_resolved.SetEmpty();
				this->is_set_addr_resolved = false;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] IException* Win32DebuggingTargetExportSymbolInfo::SetResolvedAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept {
		if (!_targetaddress || _targetaddress->GetWin32Architecture() != this->architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingTargetExecutableModuleInfo, SetBaseAddress);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_targetaddress, &err_inner]() noexcept(false)->void {
				this->addr_resolved = *_targetaddress;
				this->is_set_addr_resolved = true;
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	Win32Architecture Win32DebuggingProcess::GetProcessWin32Architecture(const Win32HandleHolder& _win32handleholder_process) noexcept(false) {
		if (!_win32handleholder_process) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingProcess, GetProcessWin32Architecture));
#if defined(_M_AMD64) || defined(__amd64__)
		if (fnptr_IsWow64Process2) {
			USHORT machine_native = IMAGE_FILE_MACHINE_UNKNOWN;
			USHORT machine_process_current = IMAGE_FILE_MACHINE_UNKNOWN;
			USHORT machine_process_target = IMAGE_FILE_MACHINE_UNKNOWN;
			if (!(*fnptr_IsWow64Process2)(GetCurrentProcess(), &machine_process_current, &machine_native)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2))) / sizeof(char)) - 1, fnptr_IsWow64Process2, GetLastError()));
			if (machine_process_current == IMAGE_FILE_MACHINE_UNKNOWN) machine_process_current = machine_native;
			if (!(*fnptr_IsWow64Process2)(_win32handleholder_process.get(), &machine_process_target, &machine_native)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2))) / sizeof(char)) - 1, fnptr_IsWow64Process2, GetLastError()));
			if (machine_process_target == IMAGE_FILE_MACHINE_UNKNOWN) machine_process_target = machine_native;
			if (machine_process_current != IMAGE_FILE_MACHINE_AMD64) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			switch (machine_process_target) {
			case IMAGE_FILE_MACHINE_AMD64:
				return Win32Architecture::Win32Architecture_x64;
			case IMAGE_FILE_MACHINE_I386:
				return Win32Architecture::Win32Architecture_x86;
			}
			throw(UnsupportedTargetWin32ArchitectureException(machine_native, machine_process_current, machine_process_target));
		} else if (fnptr_IsWow64Process) {
			SYSTEM_INFO system_info;
			GetNativeSystemInfo(&system_info);
			if (system_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
				BOOL is_wow64_process_current = FALSE;
				BOOL is_wow64_process_target = FALSE;
				if (!(*fnptr_IsWow64Process)(GetCurrentProcess(), &is_wow64_process_current)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process))) / sizeof(char)) - 1, fnptr_IsWow64Process, GetLastError()));
				if (!(*fnptr_IsWow64Process)(_win32handleholder_process.get(), &is_wow64_process_target)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process))) / sizeof(char)) - 1, fnptr_IsWow64Process, GetLastError()));
				if (is_wow64_process_current) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (is_wow64_process_target) {
					return Win32Architecture::Win32Architecture_x86;
				} else {
					return Win32Architecture::Win32Architecture_x64;
				}
			} else if (system_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
				return Win32Architecture::Win32Architecture_x86;
			} else {
				throw(UnsupportedTargetWin32ArchitectureException(IMAGE_FILE_MACHINE_UNKNOWN, IMAGE_FILE_MACHINE_AMD64, IMAGE_FILE_MACHINE_UNKNOWN));
			}
		} else {
			return Win32Architecture::Win32Architecture_x86;
		}
#elif defined (_M_IX86) || defined (__i386__)
		if (fnptr_IsWow64Process2) {
			USHORT machine_native = IMAGE_FILE_MACHINE_UNKNOWN;
			USHORT machine_process_current = IMAGE_FILE_MACHINE_UNKNOWN;
			USHORT machine_process_target = IMAGE_FILE_MACHINE_UNKNOWN;
			if (!(*fnptr_IsWow64Process2)(GetCurrentProcess(), &machine_process_current, &machine_native)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2))) / sizeof(char)) - 1, fnptr_IsWow64Process2, GetLastError()));
			if (machine_process_current == IMAGE_FILE_MACHINE_UNKNOWN) machine_process_current = machine_native;
			if (!(*fnptr_IsWow64Process2)(_win32handleholder_process.get(), &machine_process_target, &machine_native)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process2))) / sizeof(char)) - 1, fnptr_IsWow64Process2, GetLastError()));
			if (machine_process_target == IMAGE_FILE_MACHINE_UNKNOWN) machine_process_target = machine_native;
			if (machine_process_current != IMAGE_FILE_MACHINE_I386) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			switch (machine_process_target) {
			case IMAGE_FILE_MACHINE_AMD64:
				// 32 to 64.
				break;
			case IMAGE_FILE_MACHINE_I386:
				return Win32Architecture::Win32Architecture_x86;
			}
			throw(UnsupportedTargetWin32ArchitectureException(machine_native, machine_process_current, machine_process_target));
		} else if (fnptr_IsWow64Process) {
			SYSTEM_INFO system_info;
			GetNativeSystemInfo(&system_info);
			if (system_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
				BOOL is_wow64_process_current = FALSE;
				BOOL is_wow64_process_target = FALSE;
				if (!(*fnptr_IsWow64Process)(GetCurrentProcess(), &is_wow64_process_current)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process))) / sizeof(char)) - 1, fnptr_IsWow64Process, GetLastError()));
				if (!(*fnptr_IsWow64Process)(_win32handleholder_process.get(), &is_wow64_process_target)) throw(new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(IsWow64Process))) / sizeof(char)) - 1, fnptr_IsWow64Process, GetLastError()));
				if (!is_wow64_process_current) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (is_wow64_process_target) {
					return Win32Architecture::Win32Architecture_x86;
				} else {
					// 32 to 64.
					throw(UnsupportedTargetWin32ArchitectureException(IMAGE_FILE_MACHINE_AMD64, IMAGE_FILE_MACHINE_I386, IMAGE_FILE_MACHINE_AMD64));
				}
			} else if (system_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
				return Win32Architecture::Win32Architecture_x86;
			} else {
				throw(UnsupportedTargetWin32ArchitectureException(IMAGE_FILE_MACHINE_UNKNOWN, IMAGE_FILE_MACHINE_I386, IMAGE_FILE_MACHINE_UNKNOWN));
			}
		} else {
			return Win32Architecture::Win32Architecture_x86;
		}
#else
#error Unrecognized architecture.
#endif
	}

	Win32DebuggingProcess::Win32DebuggingProcess(const Win32HandleHolder& _win32handleholder_process) noexcept(false) {
		if (!_win32handleholder_process) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingProcess, Win32DebuggingProcess));
		this->win32handleholder_process = Win32HandleHolder(_win32handleholder_process, Win32HandleHolder::change_desired_access, PROCESS_ALL_ACCESS);
		this->architecture = Win32DebuggingProcess::GetProcessWin32Architecture(this->win32handleholder_process);
		this->processid = GetProcessId(this->win32handleholder_process.get());
		if (!this->processid) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetProcessId));
	}

	Win32DebuggingProcess::~Win32DebuggingProcess() {
		this->processid = 0;
		this->win32handleholder_process = Win32HandleHolder();
		this->architecture = Win32Architecture::Win32Architecture_Invalid;
	}

	[[nodiscard]] IException* Win32DebuggingProcess::GetProcessWin32HandleHolder(const Win32HandleHolder** win32handleholder_ret) const noexcept {
		if (!win32handleholder_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32DebuggingProcess, GetProcessWin32HandleHolder);
		*win32handleholder_ret = &this->win32handleholder_process;
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Win32DebuggingReadTargetMemory(Win32Architecture architecture, const Win32HandleHolder* win32handleholder_process, void* buf, size_t size, const Win32DebuggingTargetAddress* targetaddress) noexcept {
		if (!win32handleholder_process || !buf && size || !targetaddress || targetaddress->GetWin32Architecture() != architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingReadTargetMemory);
		if (!ReadProcessMemory(win32handleholder_process->get(), targetaddress->GetRawCurrentProcessAddress(), buf, size, nullptr)) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ReadProcessMemory);
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Win32DebuggingWriteTargetMemory(Win32Architecture architecture, const Win32HandleHolder* win32handleholder_process, const void* buf, size_t size, const Win32DebuggingTargetAddress* targetaddress) noexcept {
		if (!win32handleholder_process || !buf && size || !targetaddress || targetaddress->GetWin32Architecture() != architecture) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingWriteTargetMemory);
		if (!WriteProcessMemory(win32handleholder_process->get(), targetaddress->GetRawCurrentProcessAddress(), buf, size, nullptr)) return YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WriteProcessMemory);
		return nullptr;
	}

	Win32DebuggingTargetMemoryRegionInfo Win32DebuggingQueryTargetMemoryRegion(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process, const Win32DebuggingTargetAddress& targetaddress) noexcept(false) {
		if (targetaddress.GetWin32Architecture() != architecture) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(QueryWin32DebuggingTargetMemoryRegion));
		MEMORY_BASIC_INFORMATION memorybasicinformation;
		memset(&memorybasicinformation, 0, sizeof(MEMORY_BASIC_INFORMATION));
		{
			void* rawcurrentprocessaddress = targetaddress.GetRawCurrentProcessAddress();
			if (VirtualQueryEx(
				win32handleholder_process.get(),
				rawcurrentprocessaddress,
				&memorybasicinformation,
				sizeof(MEMORY_BASIC_INFORMATION)
			) != sizeof(memorybasicinformation)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(VirtualQueryEx));
		}
		return Win32DebuggingTargetMemoryRegionInfo(
			architecture,
			Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, memorybasicinformation.BaseAddress),
			Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, memorybasicinformation.AllocationBase),
			Win32DebuggingTargetAddressDiff(architecture, memorybasicinformation.RegionSize),
			memorybasicinformation.Protect,
			memorybasicinformation.AllocationProtect,
			memorybasicinformation.State,
			memorybasicinformation.Type
		);
	}

	::std::vector<Win32DebuggingTargetMemoryRegionInfo> Win32DebuggingListTargetMemoryRegions(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process) noexcept(false) {
		::std::vector<Win32DebuggingTargetMemoryRegionInfo> vec_targetmemoryregioninfo;
		Win32DebuggingTargetAddress _targetaddress = Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_min);
		while (true) {
			Win32DebuggingTargetMemoryRegionInfo targetmemoryregioninfo(architecture);
			{
				IException* err_QueryWin32DebuggingTargetMemoryRegion = WrapFunctionCatchExceptions(
					[&architecture, &win32handleholder_process, &_targetaddress, &targetmemoryregioninfo]() noexcept(false)->void {
						targetmemoryregioninfo = Win32DebuggingQueryTargetMemoryRegion(architecture, win32handleholder_process, _targetaddress);
					}
				);
				if (err_QueryWin32DebuggingTargetMemoryRegion) {
					if (err_QueryWin32DebuggingTargetMemoryRegion->DynamicTypeRawCanCastTo(::YBWLib2::GetDynamicTypeClassObject<::YBWLib2::IExternalAPIFailureException>())) {
						delete err_QueryWin32DebuggingTargetMemoryRegion;
						err_QueryWin32DebuggingTargetMemoryRegion = nullptr;
						break;
					} else {
						throw(err_QueryWin32DebuggingTargetMemoryRegion);
					}
				}
			}
			vec_targetmemoryregioninfo.push_back(::std::move(targetmemoryregioninfo));
			{
				const Win32DebuggingTargetAddress& targetaddress_base = *targetmemoryregioninfo.IWin32DebuggingTargetMemoryRegionInfo::GetBaseAddress();
				const Win32DebuggingTargetAddressDiff& targetaddressdiff_size = *targetmemoryregioninfo.IWin32DebuggingTargetMemoryRegionInfo::GetSize();
				if (targetaddress_base > Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_max) - targetaddressdiff_size) break;
				_targetaddress = targetaddress_base + targetaddressdiff_size;
			}
		}
		return vec_targetmemoryregioninfo;
	}

	::std::vector<Win32DebuggingTargetExecutableModuleInfo> Win32DebuggingListTargetExecutableModules(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process) noexcept(false) {
		::std::map<Win32DebuggingTargetAddress, Win32DebuggingTargetExecutableModuleInfo> map_targetexecutablemoduleinfo;
		DWORD processid = GetProcessId(win32handleholder_process.get());
		if (!processid) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetProcessId));
		Win32HandleHolder win32handleholder_snapshot;
#if defined(_M_AMD64) || defined(__amd64__)
		switch (architecture) {
		case Win32Architecture::Win32Architecture_x64:
			do {
				win32handleholder_snapshot.reset(Win32HandleHolder::own_handle, CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processid));
			} while (!win32handleholder_snapshot && GetLastError() == ERROR_BAD_LENGTH);
			break;
		case Win32Architecture::Win32Architecture_x86:
			do {
				win32handleholder_snapshot.reset(Win32HandleHolder::own_handle, CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processid));
			} while (!win32handleholder_snapshot && GetLastError() == ERROR_BAD_LENGTH);
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
#elif defined (_M_IX86) || defined (__i386__)
		switch (architecture) {
		case Win32Architecture::Win32Architecture_x86:
			do {
				win32handleholder_snapshot.reset(Win32HandleHolder::own_handle, CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processid));
			} while (!win32handleholder_snapshot && GetLastError() == ERROR_BAD_LENGTH);
			break;
		default:
			throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
		}
#else
#error Unrecognized architecture.
#endif
		if (!win32handleholder_snapshot) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CreateToolhelp32Snapshot));
		MODULEENTRY32W moduleentry32;
		::std::vector<char16_t> vecbuf_u16str_temp;
		memset(&moduleentry32, 0, sizeof(MODULEENTRY32W));
		moduleentry32.dwSize = sizeof(MODULEENTRY32W);
		if (Module32FirstW(win32handleholder_snapshot.get(), &moduleentry32)) {
			{
				bool is_mismatch_architecture = false;
				{
					IException* err_test_mismatch_architecture = WrapFunctionCatchExceptions(
						[&architecture, &moduleentry32]() noexcept(false)->void {
							Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, moduleentry32.modBaseAddr);
						}
					);
					if (err_test_mismatch_architecture) {
						if (err_test_mismatch_architecture->DynamicTypeRawCanCastTo(::YBWLib2::GetDynamicTypeClassObject<::YBWLib2::IInvalidParameterException>())) {
							delete err_test_mismatch_architecture;
							err_test_mismatch_architecture = nullptr;
							is_mismatch_architecture = true;
						} else {
							throw(err_test_mismatch_architecture);
						}
					}
				}
				if (!is_mismatch_architecture) {
					::std::string name_module;
					::std::string path_module;
					{
						static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
						char16_t(&u16strarr_name_module)[sizeof(moduleentry32.szModule) / sizeof(wchar_t)] = reinterpret_cast<char16_t(&)[sizeof(moduleentry32.szModule) / sizeof(wchar_t)]>(moduleentry32.szModule);
						const char16_t* endptr_u16strarr_name_module = ::std::char_traits<char16_t>::find(u16strarr_name_module, sizeof(u16strarr_name_module) / sizeof(char16_t), char16_t());
						name_module = Utf16StringToUtf8String<::std::string, ::std::u16string_view>(
							rawallocator_crt_module_local,
							::std::u16string_view(u16strarr_name_module, endptr_u16strarr_name_module ? endptr_u16strarr_name_module - u16strarr_name_module : sizeof(u16strarr_name_module) / sizeof(char16_t)),
							::std::allocator<char>()
							);
					}
					{
						static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
						if (vecbuf_u16str_temp.size() < 0x10000) vecbuf_u16str_temp.resize(0x10000);
						DWORD dword_size_u16str_path_module = GetModuleFileNameExW(win32handleholder_process.get(), moduleentry32.hModule, reinterpret_cast<wchar_t*>(vecbuf_u16str_temp.data()), 0x10000);
						if (!dword_size_u16str_path_module || dword_size_u16str_path_module > 0x10000) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetModuleFileNameExW));
						path_module = Utf16StringToUtf8String<::std::string, ::std::vector<char16_t>>(rawallocator_crt_module_local, vecbuf_u16str_temp, ::std::allocator<char>());
					}
					Win32DebuggingTargetExecutableModuleInfo targetexecutablemoduleinfo(
						architecture,
						Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, moduleentry32.modBaseAddr),
						Win32DebuggingTargetAddressDiff(architecture, moduleentry32.modBaseSize),
						name_module.data(), name_module.size(),
						path_module.data(), path_module.size()
					);
					const Win32DebuggingTargetAddress& targetaddress = *targetexecutablemoduleinfo.IWin32DebuggingTargetExecutableModuleInfo::GetBaseAddress();
					if (!map_targetexecutablemoduleinfo.count(targetaddress))
						map_targetexecutablemoduleinfo.insert(::std::make_pair(targetaddress, ::std::move(targetexecutablemoduleinfo)));
				}
			}
			memset(&moduleentry32, 0, sizeof(MODULEENTRY32W));
			moduleentry32.dwSize = sizeof(MODULEENTRY32W);
			while (Module32NextW(win32handleholder_snapshot.get(), &moduleentry32)) {
				{
					bool is_mismatch_architecture = false;
					{
						IException* err_test_mismatch_architecture = WrapFunctionCatchExceptions(
							[&architecture, &moduleentry32]() noexcept(false)->void {
								Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, moduleentry32.modBaseAddr);
							}
						);
						if (err_test_mismatch_architecture) {
							if (err_test_mismatch_architecture->DynamicTypeRawCanCastTo(::YBWLib2::GetDynamicTypeClassObject<::YBWLib2::IInvalidParameterException>())) {
								delete err_test_mismatch_architecture;
								err_test_mismatch_architecture = nullptr;
								is_mismatch_architecture = true;
							} else {
								throw(err_test_mismatch_architecture);
							}
						}
					}
					if (!is_mismatch_architecture) {
						::std::string name_module;
						::std::string path_module;
						{
							static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
							char16_t(&u16strarr_name_module)[sizeof(moduleentry32.szModule) / sizeof(wchar_t)] = reinterpret_cast<char16_t(&)[sizeof(moduleentry32.szModule) / sizeof(wchar_t)]>(moduleentry32.szModule);
							const char16_t* endptr_u16strarr_name_module = ::std::char_traits<char16_t>::find(u16strarr_name_module, sizeof(u16strarr_name_module) / sizeof(char16_t), char16_t());
							name_module = Utf16StringToUtf8String<::std::string, ::std::u16string_view>(
								rawallocator_crt_module_local,
								::std::u16string_view(u16strarr_name_module, endptr_u16strarr_name_module ? endptr_u16strarr_name_module - u16strarr_name_module : sizeof(u16strarr_name_module) / sizeof(char16_t)),
								::std::allocator<char>()
								);
						}
						Win32DebuggingTargetExecutableModuleInfo targetexecutablemoduleinfo(
							architecture,
							Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_raw_current_process_address, moduleentry32.modBaseAddr),
							Win32DebuggingTargetAddressDiff(architecture, moduleentry32.modBaseSize),
							name_module.data(), name_module.size(),
							path_module.data(), path_module.size()
						);
						const Win32DebuggingTargetAddress& targetaddress = *targetexecutablemoduleinfo.IWin32DebuggingTargetExecutableModuleInfo::GetBaseAddress();
						if (!map_targetexecutablemoduleinfo.count(targetaddress))
							map_targetexecutablemoduleinfo.insert(::std::make_pair(targetaddress, ::std::move(targetexecutablemoduleinfo)));
					}
				}
				memset(&moduleentry32, 0, sizeof(MODULEENTRY32W));
				moduleentry32.dwSize = sizeof(MODULEENTRY32W);
			}
			if (GetLastError() != ERROR_NO_MORE_FILES) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(Module32NextW));
		} else if (GetLastError() != ERROR_NO_MORE_FILES) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(Module32FirstW));
		{
			::std::vector<Win32DebuggingTargetExecutableModuleInfo> vec_targetexecutablemoduleinfo;
			vec_targetexecutablemoduleinfo.reserve(map_targetexecutablemoduleinfo.size());
			for (::std::pair<const Win32DebuggingTargetAddress, Win32DebuggingTargetExecutableModuleInfo>& val_map_targetexecutablemoduleinfo : map_targetexecutablemoduleinfo) {
				vec_targetexecutablemoduleinfo.push_back(::std::move(val_map_targetexecutablemoduleinfo.second));
			}
			map_targetexecutablemoduleinfo.clear();
			return vec_targetexecutablemoduleinfo;
		}
	}

	::std::vector<Win32DebuggingTargetExportSymbolInfo> Win32DebuggingListTargetExportSymbolsInTargetExecutableModule(const ::std::shared_ptr<Win32DebuggingTargetExecutableModuleInfo>& targetexecutablemoduleinfo, const void* buf_module, size_t size_buf_module) noexcept(false) {
		if (!targetexecutablemoduleinfo) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
		if (!buf_module && size_buf_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
		const void* ptr_end_module = reinterpret_cast<const unsigned char*>(buf_module) + size_buf_module;
		std::vector<Win32DebuggingTargetExportSymbolInfo> vec_targetexportsymbolinfo;
		const IMAGE_DOS_HEADER* imagedosheader = nullptr;
		{
			if (size_buf_module < sizeof(IMAGE_DOS_HEADER)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			imagedosheader = reinterpret_cast<const IMAGE_DOS_HEADER*>(buf_module);
		}
		const IMAGE_FILE_HEADER* imagefileheader = nullptr;
		WORD machine = IMAGE_FILE_MACHINE_UNKNOWN;
		WORD count_section = 0;
		const unsigned char* ptr_imageoptionalheader = nullptr;
		const IMAGE_DATA_DIRECTORY* arrptr_imagedatadirectory = nullptr;
		size_t count_imagedatadirectory = 0;
		{
			if (imagedosheader->e_lfanew < 0 || imagedosheader->e_lfanew > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			size_t offs_pesignature = static_cast<::std::make_unsigned_t<LONG>>(imagedosheader->e_lfanew) & ~(size_t)0;
			if (
				offs_pesignature > SIZE_MAX - (4 + sizeof(IMAGE_FILE_HEADER))
				|| offs_pesignature + (4 + sizeof(IMAGE_FILE_HEADER)) > size_buf_module
				|| memcmp(reinterpret_cast<const unsigned char*>(buf_module) + offs_pesignature, "PE\0\0", 4)
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			imagefileheader = reinterpret_cast<const IMAGE_FILE_HEADER*>(reinterpret_cast<const unsigned char*>(buf_module) + offs_pesignature + 4);
			machine = imagefileheader->Machine;
			count_section = imagefileheader->NumberOfSections;
			if (imagefileheader->SizeOfOptionalHeader > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			size_t size_imageoptionalheader = imagefileheader->SizeOfOptionalHeader & ~(size_t)0;
			if (
				size_imageoptionalheader > SIZE_MAX - (4 + sizeof(IMAGE_FILE_HEADER))
				|| offs_pesignature > SIZE_MAX - (4 + sizeof(IMAGE_FILE_HEADER) + size_imageoptionalheader)
				|| offs_pesignature + (4 + sizeof(IMAGE_FILE_HEADER) + size_imageoptionalheader) > size_buf_module
				|| size_imageoptionalheader < sizeof(WORD)
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			ptr_imageoptionalheader = reinterpret_cast<const unsigned char*>(buf_module) + offs_pesignature + 4 + sizeof(IMAGE_FILE_HEADER);
			switch (*reinterpret_cast<const WORD*>(ptr_imageoptionalheader)) {
			case 0x20B: {
				if (size_imageoptionalheader < sizeof(IMAGE_OPTIONAL_HEADER64)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				const IMAGE_OPTIONAL_HEADER64* imageoptionalheader = reinterpret_cast<const IMAGE_OPTIONAL_HEADER64*>(ptr_imageoptionalheader);
				if (imageoptionalheader->NumberOfRvaAndSizes > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				count_imagedatadirectory = imageoptionalheader->NumberOfRvaAndSizes & ~(size_t)0;
				if (
					count_imagedatadirectory > SIZE_MAX / sizeof(IMAGE_DATA_DIRECTORY)
					|| count_imagedatadirectory * sizeof(IMAGE_DATA_DIRECTORY) < size_imageoptionalheader - sizeof(IMAGE_OPTIONAL_HEADER64)
					) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				arrptr_imagedatadirectory = reinterpret_cast<const IMAGE_DATA_DIRECTORY*>(imageoptionalheader + 1);
				break;
			}
			case 0x10B: {
				if (size_imageoptionalheader < sizeof(IMAGE_OPTIONAL_HEADER32)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				const IMAGE_OPTIONAL_HEADER32* imageoptionalheader = reinterpret_cast<const IMAGE_OPTIONAL_HEADER32*>(ptr_imageoptionalheader);
				if (imageoptionalheader->NumberOfRvaAndSizes > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				count_imagedatadirectory = imageoptionalheader->NumberOfRvaAndSizes & ~(size_t)0;
				if (
					count_imagedatadirectory > SIZE_MAX / sizeof(IMAGE_DATA_DIRECTORY)
					|| count_imagedatadirectory * sizeof(IMAGE_DATA_DIRECTORY) < size_imageoptionalheader - sizeof(IMAGE_OPTIONAL_HEADER32)
					) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				arrptr_imagedatadirectory = reinterpret_cast<const IMAGE_DATA_DIRECTORY*>(imageoptionalheader + 1);
				break;
			}
			default:
				throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			}
		}
		// Find export table in module.
		DWORD rva_exporttable = 0;
		DWORD size_exporttable = 0;
		DWORD rva_end_exporttable = 0;
		{
			if (count_imagedatadirectory < 1) return ::std::vector<Win32DebuggingTargetExportSymbolInfo>();
			const IMAGE_DATA_DIRECTORY& imagedatadirectory_exporttable = arrptr_imagedatadirectory[0];
			if (!imagedatadirectory_exporttable.Size) return ::std::vector<Win32DebuggingTargetExportSymbolInfo>();
			rva_exporttable = imagedatadirectory_exporttable.VirtualAddress;
			size_exporttable = imagedatadirectory_exporttable.Size;
			if (rva_exporttable > MAXDWORD - size_exporttable) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			rva_end_exporttable = rva_exporttable + size_exporttable;
			if (rva_end_exporttable > size_buf_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
		}
		// Find export directory table in module.
		const IMAGE_EXPORT_DIRECTORY* image_directory_export = nullptr;
		{
			if (size_exporttable < sizeof(IMAGE_EXPORT_DIRECTORY)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			image_directory_export = reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(reinterpret_cast<const unsigned char*>(buf_module) + rva_exporttable);
		}
		// Read export address table.
		::std::vector<DWORD> vec_rva_export;
		{
			DWORD rva_exportaddresstable = image_directory_export->AddressOfFunctions;
			if (
				rva_exportaddresstable > SIZE_MAX
				|| (rva_exportaddresstable & ~(size_t)0) > size_buf_module
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			const DWORD* arrptr_rva_export = reinterpret_cast<const DWORD*>(reinterpret_cast<const unsigned char*>(buf_module) + (rva_exportaddresstable & ~(size_t)0));
			if (image_directory_export->NumberOfFunctions > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			size_t count_rva_export = image_directory_export->NumberOfFunctions & ~(size_t)0;
			if (
				count_rva_export > SIZE_MAX / sizeof(DWORD)
				|| count_rva_export * sizeof(DWORD) > size_buf_module - (rva_exportaddresstable & ~(size_t)0)
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			vec_rva_export = ::std::vector<DWORD>(arrptr_rva_export, arrptr_rva_export + count_rva_export);
		}
		// Read export name pointer table, export name table and export ordinal table.
		::std::vector<std::string> vec_exportname;
		::std::vector<WORD> vec_exportordinal;
		{
			DWORD rva_exportnamepointertable = image_directory_export->AddressOfNames;
			if (
				rva_exportnamepointertable > SIZE_MAX
				|| (rva_exportnamepointertable & ~(size_t)0) > size_buf_module
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			const DWORD* arrptr_rva_exportname = reinterpret_cast<const DWORD*>(reinterpret_cast<const unsigned char*>(buf_module) + (rva_exportnamepointertable & ~(size_t)0));
			if (image_directory_export->NumberOfNames > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			size_t count_rva_exportname = image_directory_export->NumberOfNames & ~(size_t)0;
			if (
				count_rva_exportname > SIZE_MAX / sizeof(DWORD)
				|| count_rva_exportname * sizeof(DWORD) > size_buf_module - (rva_exportnamepointertable & ~(size_t)0)
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			{
				vec_exportname.reserve(count_rva_exportname);
				for (size_t idx_rva_exportname = 0; idx_rva_exportname < count_rva_exportname; ++idx_rva_exportname) {
					DWORD rva_exportname = arrptr_rva_exportname[idx_rva_exportname];
					if (
						rva_exportname > SIZE_MAX
						|| (rva_exportname & ~(size_t)0) > size_buf_module
						) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					const char* strptr_exportname = reinterpret_cast<const char*>(reinterpret_cast<const unsigned char*>(buf_module) + (rva_exportname & ~(size_t)0));
					const char* ptr_end_exportname = nullptr;
					for (ptr_end_exportname = strptr_exportname; ptr_end_exportname < ptr_end_module && *ptr_end_exportname; ++ptr_end_exportname);
					if (ptr_end_exportname >= ptr_end_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					std::string& exportname = vec_exportname.emplace_back(strptr_exportname, ptr_end_exportname);
					if (exportname.empty()) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					for (char ch_exportname : exportname)
						if (ch_exportname < 0) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				}
			}
			DWORD rva_exportordinaltable = image_directory_export->AddressOfNameOrdinals;
			if (
				rva_exportordinaltable > SIZE_MAX
				|| (rva_exportordinaltable & ~(size_t)0) > size_buf_module
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			const WORD* arrptr_exportordinal = reinterpret_cast<const WORD*>(reinterpret_cast<const unsigned char*>(buf_module) + (rva_exportordinaltable & ~(size_t)0));
			if (image_directory_export->NumberOfNames > SIZE_MAX) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			size_t count_exportordinal = image_directory_export->NumberOfNames & ~(size_t)0;
			if (
				count_exportordinal > SIZE_MAX / sizeof(WORD)
				|| count_exportordinal * sizeof(WORD) > size_buf_module - (rva_exportordinaltable & ~(size_t)0)
				) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			vec_exportordinal = ::std::vector<WORD>(arrptr_exportordinal, arrptr_exportordinal + count_exportordinal);
		}
		// Process vectors and generate export symbol vector.
		{
			::std::map<DWORD, DWORD> map_rva_export_from_ordinal;
			if (vec_rva_export.size() > MAXDWORD) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			if ((vec_rva_export.size() & ~(DWORD)0) >= 1 && (vec_rva_export.size() & ~(DWORD)0) - 1 > MAXDWORD - image_directory_export->Base) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
			for (DWORD idx_export = 0; idx_export < (vec_rva_export.size() & ~(DWORD)0); ++idx_export)
				map_rva_export_from_ordinal.insert(::std::make_pair(image_directory_export->Base + idx_export, vec_rva_export.at(idx_export)));
			::std::map<DWORD, DWORD> map_rva_export_from_ordinal_remaining(map_rva_export_from_ordinal);
			vec_targetexportsymbolinfo.reserve(vec_exportname.size() > map_rva_export_from_ordinal.size() ? vec_exportname.size() : map_rva_export_from_ordinal.size());
			for (size_t idx_exportname = 0; idx_exportname < vec_exportname.size(); ++idx_exportname) {
				DWORD exportordinal = image_directory_export->Base + vec_exportordinal.at(idx_exportname);
				const ::std::string& exportname = vec_exportname.at(idx_exportname);
				if (!map_rva_export_from_ordinal.count(exportordinal)) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				DWORD rva_export = map_rva_export_from_ordinal.at(exportordinal);
				if (
					rva_export > SIZE_MAX
					|| (rva_export & ~(size_t)0) >= size_buf_module
					) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				const void* ptr_export = reinterpret_cast<const unsigned char*>(buf_module) + (rva_export & ~(size_t)0);
				Win32DebuggingTargetAddressDiff targetaddressdiff_rva_export(targetexecutablemoduleinfo->GetWin32Architecture(), rva_export);
				Win32DebuggingTargetAddress targetaddress_export = *targetexecutablemoduleinfo->IWin32DebuggingTargetExecutableModuleInfo::GetBaseAddress() + targetaddressdiff_rva_export;
				if (rva_export >= rva_exporttable && rva_export < rva_end_exporttable) {
					// Forwarder RVA.
					const char* strptr_str_forward = reinterpret_cast<const char*>(ptr_export);
					const char* ptr_end_str_forward = nullptr;
					for (ptr_end_str_forward = strptr_str_forward; ptr_end_str_forward < ptr_end_module && *ptr_end_str_forward; ++ptr_end_str_forward);
					if (ptr_end_str_forward >= ptr_end_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					::std::string str_forward(strptr_str_forward, ptr_end_str_forward);
					if (str_forward.empty()) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					for (char c : str_forward)
						if (c < 0) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					vec_targetexportsymbolinfo.emplace_back(
						targetexecutablemoduleinfo->GetWin32Architecture(),
						::std::static_pointer_cast<IWin32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo>(targetexecutablemoduleinfo),
						exportordinal,
						exportname.data(),
						exportname.size(),
						targetaddressdiff_rva_export,
						str_forward.data(),
						str_forward.size()
					);
				} else {
					// Export RVA.
					IException* err_SetResolvedAddress = vec_targetexportsymbolinfo.emplace_back(
						targetexecutablemoduleinfo->GetWin32Architecture(),
						::std::static_pointer_cast<IWin32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo>(targetexecutablemoduleinfo),
						exportordinal,
						exportname.data(),
						exportname.size(),
						targetaddressdiff_rva_export
					).SetResolvedAddress(&targetaddress_export);
					if (err_SetResolvedAddress) throw(err_SetResolvedAddress);
				}
				if (map_rva_export_from_ordinal_remaining.count(exportordinal)) map_rva_export_from_ordinal_remaining.erase(exportordinal);
			}
			for (const std::pair<DWORD, DWORD>& val_map_rva_export_from_ordinal_remaining : map_rva_export_from_ordinal_remaining) {
				DWORD exportordinal = val_map_rva_export_from_ordinal_remaining.first;
				DWORD rva_export = val_map_rva_export_from_ordinal_remaining.second;
				if (
					rva_export > SIZE_MAX
					|| (rva_export & ~(size_t)0) >= size_buf_module
					) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
				const void* ptr_export = reinterpret_cast<const unsigned char*>(buf_module) + (rva_export & ~(size_t)0);
				Win32DebuggingTargetAddressDiff targetaddressdiff_rva_export(targetexecutablemoduleinfo->GetWin32Architecture(), rva_export);
				Win32DebuggingTargetAddress targetaddress_export = *targetexecutablemoduleinfo->IWin32DebuggingTargetExecutableModuleInfo::GetBaseAddress() + targetaddressdiff_rva_export;
				if (rva_export >= rva_exporttable && rva_export < rva_end_exporttable) {
					// Forwarder RVA.
					const char* strptr_str_forward = reinterpret_cast<const char*>(ptr_export);
					const char* ptr_end_str_forward = nullptr;
					for (ptr_end_str_forward = strptr_str_forward; ptr_end_str_forward < ptr_end_module && *ptr_end_str_forward; ++ptr_end_str_forward);
					if (ptr_end_str_forward >= ptr_end_module) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					::std::string str_forward(strptr_str_forward, ptr_end_str_forward);
					if (str_forward.empty()) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					for (char c : str_forward)
						if (c < 0) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(Win32DebuggingListTargetExportSymbolsInTargetExecutableModule));
					vec_targetexportsymbolinfo.emplace_back(
						targetexecutablemoduleinfo->GetWin32Architecture(),
						::std::static_pointer_cast<IWin32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo>(targetexecutablemoduleinfo),
						exportordinal,
						targetaddressdiff_rva_export,
						str_forward.data(),
						str_forward.size()
					);
				} else {
					// Export RVA.
					IException* err_SetResolvedAddress = vec_targetexportsymbolinfo.emplace_back(
						targetexecutablemoduleinfo->GetWin32Architecture(),
						::std::static_pointer_cast<IWin32DebuggingTargetExecutableModuleInfo, Win32DebuggingTargetExecutableModuleInfo>(targetexecutablemoduleinfo),
						exportordinal,
						targetaddressdiff_rva_export
					).SetResolvedAddress(&targetaddress_export);
					if (err_SetResolvedAddress) throw(err_SetResolvedAddress);
				}
			}
		}
		return vec_targetexportsymbolinfo;
	}

	void YBWLIB2_CALLTYPE DebuggingWindows_RealInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<IUnsupportedTargetWin32ArchitectureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnsupportedTargetWin32ArchitectureException)), module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetMemoryRegionInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IWin32DebuggingTargetMemoryRegionInfo)), module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetExecutableModuleInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IWin32DebuggingTargetExecutableModuleInfo)), module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetExportSymbolInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IWin32DebuggingTargetExportSymbolInfo)), module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingProcess>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IWin32DebuggingProcess)), module_info_current);
		UnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<UnsupportedTargetWin32ArchitectureException>(),
			IsDynamicTypeModuleLocalClass<UnsupportedTargetWin32ArchitectureException>(),
			{
				DynamicTypeBaseClassDef<UnsupportedTargetWin32ArchitectureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnsupportedTargetWin32ArchitectureException, IUnsupportedTargetWin32ArchitectureException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(UnsupportedTargetWin32ArchitectureException), alignof(UnsupportedTargetWin32ArchitectureException)
		);
		Win32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<Win32DebuggingTargetMemoryRegionInfo>(),
			IsDynamicTypeModuleLocalClass<Win32DebuggingTargetMemoryRegionInfo>(),
			{
				DynamicTypeBaseClassDef<Win32DebuggingTargetMemoryRegionInfo, IWin32DebuggingTargetMemoryRegionInfo, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(Win32DebuggingTargetMemoryRegionInfo), alignof(Win32DebuggingTargetMemoryRegionInfo)
		);
		Win32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<Win32DebuggingTargetExecutableModuleInfo>(),
			IsDynamicTypeModuleLocalClass<Win32DebuggingTargetExecutableModuleInfo>(),
			{
				DynamicTypeBaseClassDef<Win32DebuggingTargetExecutableModuleInfo, IWin32DebuggingTargetExecutableModuleInfo, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(Win32DebuggingTargetExecutableModuleInfo), alignof(Win32DebuggingTargetExecutableModuleInfo)
		);
		Win32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<Win32DebuggingTargetExportSymbolInfo>(),
			IsDynamicTypeModuleLocalClass<Win32DebuggingTargetExportSymbolInfo>(),
			{
				DynamicTypeBaseClassDef<Win32DebuggingTargetExportSymbolInfo, IWin32DebuggingTargetExportSymbolInfo, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(Win32DebuggingTargetExportSymbolInfo), alignof(Win32DebuggingTargetExportSymbolInfo)
		);
		Win32DebuggingProcess::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<Win32DebuggingProcess>(),
			IsDynamicTypeModuleLocalClass<Win32DebuggingProcess>(),
			{
				DynamicTypeBaseClassDef<Win32DebuggingProcess, ReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<Win32DebuggingProcess, IWin32DebuggingProcess, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(Win32DebuggingProcess), alignof(Win32DebuggingProcess)
		);
		GetDynamicTypeClassObject<UnsupportedTargetWin32ArchitectureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnsupportedTargetWin32ArchitectureException)), module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetMemoryRegionInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32DebuggingTargetMemoryRegionInfo)), module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetExecutableModuleInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32DebuggingTargetExecutableModuleInfo)), module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetExportSymbolInfo>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32DebuggingTargetExportSymbolInfo)), module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingProcess>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32DebuggingProcess)), module_info_current);
	}

	void YBWLIB2_CALLTYPE DebuggingWindows_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeClassObject<Win32DebuggingProcess>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetExportSymbolInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetExecutableModuleInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<Win32DebuggingTargetMemoryRegionInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<UnsupportedTargetWin32ArchitectureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete Win32DebuggingProcess::DynamicTypeThisClassObject;
		Win32DebuggingProcess::DynamicTypeThisClassObject = nullptr;
		delete Win32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject;
		Win32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject = nullptr;
		delete Win32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject;
		Win32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject = nullptr;
		delete Win32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject;
		Win32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject = nullptr;
		delete UnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject;
		UnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeClassObject<IWin32DebuggingProcess>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetExportSymbolInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetExecutableModuleInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IWin32DebuggingTargetMemoryRegionInfo>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeClassObject<IUnsupportedTargetWin32ArchitectureException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
