#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include <wincrypt.h>
#include <bcrypt.h>
#include "../Exception/Exception.h"
#ifdef _WIN32_WINNT
#include "../Exception/ExceptionWindows.h"
#else
#error This platform is not supported yet.
#endif
#include "Common.h"
#include "CommonSTLHelper.h"

#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "bcrypt.lib")

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountedObject, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ILockableObject, YBWLIB2_API);

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8StringToUtf16String(
		const rawallocator_t* rawallocator,
		char16_t** str_out_ret,
		size_t* size_str_out_ret,
		const char* str_in,
		size_t size_str_in
	) noexcept {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
		if (!str_in && size_str_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out_ret, &size_str_out_ret, &str_in, &size_str_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				if (!size_str_in) {
					*size_str_out_ret = 0;
					*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String); return; }
					*size_str_out_ret = MultiByteToWideChar(CP_UTF8, 0, str_in, size_str_in & ~(unsigned int)0, nullptr, 0);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)MultiByteToWideChar(CP_UTF8, 0, str_in, size_str_in & ~(unsigned int)0, reinterpret_cast<wchar_t*>(*str_out_ret), *size_str_out_ret & ~(unsigned int)0) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					}
				}
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
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf16StringToUtf8String(
		const rawallocator_t* rawallocator,
		char** str_out_ret,
		size_t* size_str_out_ret,
		const char16_t* str_in,
		size_t size_str_in
	) noexcept {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
		if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
		if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
		if (!str_in && size_str_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_out_ret, &size_str_out_ret, &str_in, &size_str_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				if (!size_str_in) {
					*size_str_out_ret = 0;
					*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String); return; }
					*size_str_out_ret = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, *str_out_ret, *size_str_out_ret & ~(unsigned int)0, nullptr, nullptr) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
							if (!rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char))) abort();
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char)));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					}
				}
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
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Decode(
		const rawallocator_t* rawallocator,
		uint8_t** data_out_ret,
		size_t* size_data_out_ret,
		const char* str_base64_in,
		size_t size_str_base64_in
	) noexcept {
		static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!data_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!size_data_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!str_base64_in && size_str_base64_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &data_out_ret, &size_data_out_ret, &str_base64_in, &size_str_base64_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				static_assert(sizeof(uint8_t) == sizeof(BYTE), "The size of uint8_t is different from the size of BYTE.");
				struct holder_u16str_t final {
					const rawallocator_t* rawallocator = nullptr;
					char16_t* str = nullptr;
					size_t size_str = 0;
					inline constexpr holder_u16str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
					holder_u16str_t(const holder_u16str_t&) = delete;
					inline holder_u16str_t(holder_u16str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
						x.rawallocator = nullptr;
						x.str = nullptr;
						x.size_str = 0;
					}
					inline ~holder_u16str_t() {
						if (this->str) {
							if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char16_t))) abort();
							this->str = nullptr;
						}
						this->size_str = 0;
						this->rawallocator = nullptr;
					}
					holder_u16str_t& operator=(const holder_u16str_t&) = delete;
					inline holder_u16str_t& operator=(holder_u16str_t&& x) noexcept {
						this->rawallocator = ::std::move(x.rawallocator);
						this->str = ::std::move(x.str);
						this->size_str = ::std::move(x.size_str);
						x.rawallocator = nullptr;
						x.str = nullptr;
						x.size_str = 0;
						return *this;
					}
				} holder_u16str_out(rawallocator);
				err_inner = Utf8StringToUtf16String(rawallocator, &holder_u16str_out.str, &holder_u16str_out.size_str, str_base64_in, size_str_base64_in);
				if (err_inner) return;
				DWORD dword_size_data_out = 0;
				if (holder_u16str_out.size_str > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptStringToBinaryW(reinterpret_cast<const wchar_t*>(holder_u16str_out.str), holder_u16str_out.size_str & ~(DWORD)0, CRYPT_STRING_BASE64, nullptr, &dword_size_data_out, nullptr, nullptr)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptStringToBinaryW); return; }
				if (dword_size_data_out > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				*size_data_out_ret = dword_size_data_out & ~(size_t)0;
				*data_out_ret = reinterpret_cast<uint8_t*>(rawallocator->Allocate(*size_data_out_ret * sizeof(uint8_t)));
				if (!*data_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (holder_u16str_out.size_str > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (
					!CryptStringToBinaryW(reinterpret_cast<const wchar_t*>(holder_u16str_out.str), holder_u16str_out.size_str & ~(DWORD)0, CRYPT_STRING_BASE64, reinterpret_cast<BYTE*>(*data_out_ret), &dword_size_data_out, nullptr, nullptr)
					|| dword_size_data_out != *size_data_out_ret
					) {
					err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptStringToBinaryW);
					if (!rawallocator->Deallocate(*data_out_ret, *size_data_out_ret * sizeof(uint8_t))) abort();
					*data_out_ret = nullptr;
					*size_data_out_ret = 0;
					return;
				}
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
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Encode(
		const rawallocator_t* rawallocator,
		char** str_base64_out_ret,
		size_t* size_str_base64_out_ret,
		const uint8_t* data_in,
		size_t size_data_in
	) noexcept {
		static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!str_base64_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!size_str_base64_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!data_in && size_data_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_base64_out_ret, &size_str_base64_out_ret, &data_in, &size_data_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				static_assert(sizeof(uint8_t) == sizeof(BYTE), "The size of uint8_t is different from the size of BYTE.");
				struct holder_u16str_t final {
					const rawallocator_t* rawallocator = nullptr;
					char16_t* str = nullptr;
					size_t size_str = 0;
					inline constexpr holder_u16str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
					holder_u16str_t(const holder_u16str_t&) = delete;
					inline holder_u16str_t(holder_u16str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
						x.rawallocator = nullptr;
						x.str = nullptr;
						x.size_str = 0;
					}
					inline ~holder_u16str_t() {
						if (this->str) {
							if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char16_t))) abort();
							this->str = nullptr;
						}
						this->size_str = 0;
						this->rawallocator = nullptr;
					}
					holder_u16str_t& operator=(const holder_u16str_t&) = delete;
					inline holder_u16str_t& operator=(holder_u16str_t&& x) noexcept {
						this->rawallocator = ::std::move(x.rawallocator);
						this->str = ::std::move(x.str);
						this->size_str = ::std::move(x.size_str);
						x.rawallocator = nullptr;
						x.str = nullptr;
						x.size_str = 0;
						return *this;
					}
				} holder_u16str_out(rawallocator);
				if (!data_in) data_in = reinterpret_cast<const uint8_t*>(&dummy);
				DWORD dword_size_u16str_out = 0;
				if (size_data_in > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptBinaryToStringW(reinterpret_cast<const BYTE*>(data_in), size_data_in & ~(DWORD)0, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &dword_size_u16str_out)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptBinaryToStringW); return; }
				if (dword_size_u16str_out > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				holder_u16str_out.size_str = dword_size_u16str_out;
				holder_u16str_out.str = reinterpret_cast<char16_t*>(rawallocator->Allocate(holder_u16str_out.size_str * sizeof(char16_t)));
				if (!holder_u16str_out.str) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (size_data_in > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptBinaryToStringW(reinterpret_cast<const BYTE*>(data_in), size_data_in & ~(DWORD)0, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, reinterpret_cast<wchar_t*>(holder_u16str_out.str), &dword_size_u16str_out)) {
					err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptBinaryToStringW);
					if (!rawallocator->Deallocate(holder_u16str_out.str, holder_u16str_out.size_str * sizeof(char16_t))) abort();
					holder_u16str_out.str = nullptr;
					holder_u16str_out.size_str = 0;
					return;
				}
				err_inner = Utf16StringToUtf8String(rawallocator, str_base64_out_ret, size_str_base64_out_ret, holder_u16str_out.str, holder_u16str_out.size_str);
				if (err_inner) {
					if (!rawallocator->Deallocate(holder_u16str_out.str, holder_u16str_out.size_str * sizeof(char16_t))) abort();
					holder_u16str_out.str = nullptr;
					holder_u16str_out.size_str = 0;
					return;
				}
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
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE HashSha256(
		const rawallocator_t* rawallocator,
		uint8_t** hash_out_ret,
		size_t* size_hash_out_ret,
		const uint8_t* data_in,
		size_t size_data_in
	) noexcept {
		static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!hash_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!size_hash_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!data_in && size_data_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &hash_out_ret, &size_hash_out_ret, &data_in, &size_data_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(uint8_t) == sizeof(UCHAR), "The size of uint8_t is different from the size of UCHAR.");
				struct holder_data_t final {
					const rawallocator_t* rawallocator = nullptr;
					uint8_t* data = nullptr;
					size_t size_data = 0;
					inline constexpr holder_data_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
					holder_data_t(const holder_data_t&) = delete;
					inline holder_data_t(holder_data_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), data(::std::move(x.data)), size_data(::std::move(x.size_data)) {
						x.rawallocator = nullptr;
						x.data = nullptr;
						x.size_data = 0;
					}
					inline ~holder_data_t() {
						if (this->data) {
							if (!this->rawallocator->Deallocate(this->data, size_data * sizeof(uint8_t))) abort();
							this->data = nullptr;
						}
						this->size_data = 0;
						this->rawallocator = nullptr;
					}
					holder_data_t& operator=(const holder_data_t&) = delete;
					inline holder_data_t& operator=(holder_data_t&& x) noexcept {
						this->rawallocator = ::std::move(x.rawallocator);
						this->data = ::std::move(x.data);
						this->size_data = ::std::move(x.size_data);
						x.rawallocator = nullptr;
						x.data = nullptr;
						x.size_data = 0;
						return *this;
					}
				};
				struct holder_halgorithm_t {
					BCRYPT_ALG_HANDLE halgorithm = NULL;
					~holder_halgorithm_t() {
						if (this->halgorithm) {
							if (!NT_SUCCESS(BCryptCloseAlgorithmProvider(this->halgorithm, 0))) abort();
							this->halgorithm = NULL;
						}
					}
				} holder_halgorithm;
				NTSTATUS ntstatus = STATUS_SUCCESS;
				ntstatus = BCryptOpenAlgorithmProvider(&holder_halgorithm.halgorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0);
				if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptOpenAlgorithmProvider, ntstatus); return; }
				unsigned long ulong_size_hashobj = 0;
				{
					unsigned long ulong_size_result_property = 0;
					ntstatus = BCryptGetProperty(holder_halgorithm.halgorithm, BCRYPT_OBJECT_LENGTH, reinterpret_cast<UCHAR*>(&ulong_size_hashobj), sizeof(unsigned long), &ulong_size_result_property, 0);
					if (!NT_SUCCESS(ntstatus) || ulong_size_result_property != sizeof(unsigned long)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptGetProperty, ntstatus); return; }
				}
				holder_data_t holder_data_hashobj(rawallocator);
				if (ulong_size_hashobj > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				holder_data_hashobj.size_data = ulong_size_hashobj;
				holder_data_hashobj.data = reinterpret_cast<uint8_t*>(rawallocator->Allocate(holder_data_hashobj.size_data * sizeof(uint8_t)));
				if (!holder_data_hashobj.data) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				{
					struct holder_hhash_t {
						BCRYPT_HASH_HANDLE hhash = NULL;
						~holder_hhash_t() {
							if (this->hhash) {
								if (!NT_SUCCESS(BCryptDestroyHash(this->hhash))) abort();
								this->hhash = NULL;
							}
						}
					} holder_hhash;
					if (holder_data_hashobj.size_data > ULONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					ntstatus = BCryptCreateHash(holder_halgorithm.halgorithm, &holder_hhash.hhash, reinterpret_cast<UCHAR*>(holder_data_hashobj.data), holder_data_hashobj.size_data & ~(ULONG)0, nullptr, 0, 0);
					if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptCreateHash, ntstatus); return; }
					if constexpr (SIZE_MAX > ULONG_MAX) {
						if (size_data_in > ULONG_MAX) {
							for (; size_data_in > ULONG_MAX; data_in += ULONG_MAX / 2, size_data_in -= ULONG_MAX / 2) {
								ntstatus = BCryptHashData(holder_hhash.hhash, const_cast<UCHAR*>(reinterpret_cast<const UCHAR*>(data_in)), ULONG_MAX / 2, 0);
								if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptHashData, ntstatus); return; }
							}
							ntstatus = BCryptHashData(holder_hhash.hhash, const_cast<UCHAR*>(reinterpret_cast<const UCHAR*>(data_in)), size_data_in & ~(ULONG)0, 0);
							if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptHashData, ntstatus); return; }
						} else {
							ntstatus = BCryptHashData(holder_hhash.hhash, const_cast<UCHAR*>(reinterpret_cast<const UCHAR*>(data_in)), size_data_in & ~(ULONG)0, 0);
							if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptHashData, ntstatus); return; }
						}
					} else {
						ntstatus = BCryptHashData(holder_hhash.hhash, const_cast<UCHAR*>(reinterpret_cast<const UCHAR*>(data_in)), size_data_in & ~(ULONG)0, 0);
						if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptHashData, ntstatus); return; }
					}
					unsigned long ulong_size_hash = 0;
					{
						unsigned long ulong_size_result_property = 0;
						ntstatus = BCryptGetProperty(holder_halgorithm.halgorithm, BCRYPT_HASH_LENGTH, reinterpret_cast<UCHAR*>(&ulong_size_hash), sizeof(unsigned long), &ulong_size_result_property, 0);
						if (!NT_SUCCESS(ntstatus) || ulong_size_result_property != sizeof(unsigned long)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptGetProperty, ntstatus); return; }
					}
					holder_data_t holder_data_hash(rawallocator);
					if (ulong_size_hash > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					holder_data_hash.size_data = ulong_size_hash;
					holder_data_hash.data = reinterpret_cast<uint8_t*>(rawallocator->Allocate(holder_data_hash.size_data * sizeof(uint8_t)));
					if (!holder_data_hash.data) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					if (holder_data_hash.size_data > ULONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					ntstatus = BCryptFinishHash(holder_hhash.hhash, reinterpret_cast<UCHAR*>(holder_data_hash.data), holder_data_hash.size_data & ~(ULONG)0, 0);
					if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptFinishHash, ntstatus); return; }
					*size_hash_out_ret = holder_data_hash.size_data;
					*hash_out_ret = holder_data_hash.data;
					holder_data_hash.data = nullptr;
					holder_data_hash.size_data = 0;
				}
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
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept {
		IReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<IReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<IReferenceCountedObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IReferenceCountedObject), alignof(IReferenceCountedObject));
		ILockableObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ILockableObject>(),
			IsDynamicTypeModuleLocalClass<ILockableObject>(),
			{ DynamicTypeBaseClassDef<ILockableObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ILockableObject), alignof(ILockableObject));
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept {
		delete ILockableObject::DynamicTypeThisClassObject;
		ILockableObject::DynamicTypeThisClassObject = nullptr;
		delete IReferenceCountedObject::DynamicTypeThisClassObject;
		IReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
	}
}
