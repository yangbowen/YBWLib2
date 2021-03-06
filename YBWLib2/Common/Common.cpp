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
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountControlBlock, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReferenceCountedObject, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IExclusiveLockableObject, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISharedLockableObject, YBWLIB2_API);

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
					*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String); return; }
					*size_str_out_ret = MultiByteToWideChar(CP_UTF8, 0, str_in, size_str_in & ~(unsigned int)0, nullptr, 0);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8StringToUtf16String);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)MultiByteToWideChar(CP_UTF8, 0, str_in, size_str_in & ~(unsigned int)0, reinterpret_cast<wchar_t*>(*str_out_ret), *size_str_out_ret & ~(unsigned int)0) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(MultiByteToWideChar);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char16_t));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char16_t*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char16_t), alignof(char16_t[])));
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
					*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				} else {
					if (size_str_in > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String); return; }
					*size_str_out_ret = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, nullptr, 0, nullptr, nullptr);
					if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte); return; }
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (size_str_in > INT_MAX) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf16StringToUtf8String);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
						if (*size_str_out_ret > INT_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						if ((size_t)WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(str_in), size_str_in & ~(unsigned int)0, *str_out_ret, *size_str_out_ret & ~(unsigned int)0, nullptr, nullptr) != *size_str_out_ret) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WideCharToMultiByte);
							rawallocator->Deallocate(*str_out_ret, *size_str_out_ret * sizeof(char));
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
							return;
						}
					} else {
						*str_out_ret = reinterpret_cast<char*>(rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
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
		unsigned char** data_out_ret,
		size_t* size_data_out_ret,
		const char* str_base64_in,
		size_t size_str_base64_in
	) noexcept {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!data_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!size_data_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		if (!str_base64_in && size_str_base64_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Decode);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &data_out_ret, &size_data_out_ret, &str_base64_in, &size_str_base64_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				static_assert(sizeof(unsigned char) == sizeof(BYTE), "The size of unsigned char is different from the size of BYTE.");
				objholder_rawallocator_t<char16_t[]> holder_u16str_base64_in(rawallocator);
				err_inner = Utf8StringToUtf16String(rawallocator, &holder_u16str_base64_in.get_ref_ptr_array_element_element_as_mem(), &holder_u16str_base64_in.get_ref_count_element_element_as_mem(), str_base64_in, size_str_base64_in);
				if (err_inner) return;
				DWORD dword_size_data_out = 0;
				if (holder_u16str_base64_in.get_count() > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptStringToBinaryW(reinterpret_cast<const wchar_t*>(holder_u16str_base64_in.get()), holder_u16str_base64_in.get_count() & ~(DWORD)0, CRYPT_STRING_BASE64, nullptr, &dword_size_data_out, nullptr, nullptr)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptStringToBinaryW); return; }
				if (dword_size_data_out > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				*size_data_out_ret = dword_size_data_out & ~(size_t)0;
				*data_out_ret = reinterpret_cast<unsigned char*>(rawallocator->Allocate(*size_data_out_ret * sizeof(unsigned char), alignof(unsigned char[])));
				if (!*data_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (holder_u16str_base64_in.get_count() > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (
					!CryptStringToBinaryW(reinterpret_cast<const wchar_t*>(holder_u16str_base64_in.get()), holder_u16str_base64_in.get_count() & ~(DWORD)0, CRYPT_STRING_BASE64, reinterpret_cast<BYTE*>(*data_out_ret), &dword_size_data_out, nullptr, nullptr)
					|| dword_size_data_out != *size_data_out_ret
					) {
					err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptStringToBinaryW);
					rawallocator->Deallocate(*data_out_ret, *size_data_out_ret * sizeof(unsigned char));
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
		const unsigned char* data_in,
		size_t size_data_in
	) noexcept {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!str_base64_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!size_str_base64_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		if (!data_in && size_data_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::Utf8Base64Encode);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &str_base64_out_ret, &size_str_base64_out_ret, &data_in, &size_data_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
				static_assert(sizeof(unsigned char) == sizeof(BYTE), "The size of unsigned char is different from the size of BYTE.");
				objholder_rawallocator_t<char16_t[]> holder_u16str_base64_out(rawallocator);
				if (!data_in) data_in = reinterpret_cast<const unsigned char*>(&dummy);
				DWORD dword_size_u16str_out = 0;
				if (size_data_in > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptBinaryToStringW(reinterpret_cast<const BYTE*>(data_in), size_data_in & ~(DWORD)0, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &dword_size_u16str_out)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptBinaryToStringW); return; }
				if (dword_size_u16str_out > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				holder_u16str_base64_out.get_ref_count_element_element_as_mem() = dword_size_u16str_out;
				holder_u16str_base64_out.get_ref_ptr_array_element_element_as_mem() = reinterpret_cast<char16_t*>(rawallocator->Allocate(holder_u16str_base64_out.get_count() * sizeof(char16_t), alignof(char16_t[])));
				if (!holder_u16str_base64_out.get()) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
				if (size_data_in > MAXDWORD) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				if (!CryptBinaryToStringW(reinterpret_cast<const BYTE*>(data_in), size_data_in & ~(DWORD)0, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, reinterpret_cast<wchar_t*>(holder_u16str_base64_out.get()), &dword_size_u16str_out)) {
					err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(CryptBinaryToStringW);
					return;
				}
				err_inner = Utf16StringToUtf8String(rawallocator, str_base64_out_ret, size_str_base64_out_ret, holder_u16str_base64_out.get(), holder_u16str_base64_out.get_count());
				if (err_inner) {
					rawallocator->Deallocate(*str_base64_out_ret, *size_str_base64_out_ret * sizeof(char16_t));
					*str_base64_out_ret = nullptr;
					*size_str_base64_out_ret = 0;
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
		unsigned char** hash_out_ret,
		size_t* size_hash_out_ret,
		const unsigned char* data_in,
		size_t size_data_in
	) noexcept {
		if (!rawallocator) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!hash_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!size_hash_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		if (!data_in && size_data_in) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::HashSha256);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[&rawallocator, &hash_out_ret, &size_hash_out_ret, &data_in, &size_data_in, &err_inner]() noexcept(false)->void {
#ifdef _WIN32_WINNT
				static_assert(sizeof(unsigned char) == sizeof(UCHAR), "The size of unsigned char is different from the size of UCHAR.");
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
				objholder_rawallocator_t<unsigned char[]> holder_data_hashobj(rawallocator);
				if (ulong_size_hashobj > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
				holder_data_hashobj.get_ref_count_element_element_as_mem() = ulong_size_hashobj;
				holder_data_hashobj.get_ref_ptr_array_element_element_as_mem() = reinterpret_cast<unsigned char*>(rawallocator->Allocate(holder_data_hashobj.get_count() * sizeof(unsigned char), alignof(unsigned char[])));
				if (!holder_data_hashobj.get()) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
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
					if (holder_data_hashobj.get_count() > ULONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					ntstatus = BCryptCreateHash(holder_halgorithm.halgorithm, &holder_hhash.hhash, reinterpret_cast<UCHAR*>(holder_data_hashobj.get()), holder_data_hashobj.get_count() & ~(ULONG)0, nullptr, 0, 0);
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
					objholder_rawallocator_t<unsigned char[]> holder_data_hash(rawallocator);
					if (ulong_size_hash > SIZE_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					holder_data_hash.get_ref_count_element_element_as_mem() = ulong_size_hash;
					holder_data_hash.get_ref_ptr_array_element_element_as_mem() = reinterpret_cast<unsigned char*>(rawallocator->Allocate(holder_data_hash.get_count() * sizeof(unsigned char), alignof(unsigned char[])));
					if (!holder_data_hash.get()) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					if (holder_data_hash.get_count() > ULONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					ntstatus = BCryptFinishHash(holder_hhash.hhash, reinterpret_cast<UCHAR*>(holder_data_hash.get()), holder_data_hash.get_count() & ~(ULONG)0, 0);
					if (!NT_SUCCESS(ntstatus)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(BCryptFinishHash, ntstatus); return; }
					{
						void* ptr_mem_hash_out = nullptr;
						size_t size_mem_hash_out = 0;
						holder_data_hash.release(*hash_out_ret, *size_hash_out_ret, ptr_mem_hash_out, size_mem_hash_out);
						if (ptr_mem_hash_out != *hash_out_ret || size_mem_hash_out != *size_hash_out_ret * sizeof(unsigned char)) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
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

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept {
		IReferenceCountControlBlock::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IReferenceCountControlBlock>(),
			IsDynamicTypeModuleLocalClass<IReferenceCountControlBlock>(),
			{ DynamicTypeBaseClassDef<IReferenceCountControlBlock, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IReferenceCountControlBlock), alignof(IReferenceCountControlBlock));
		IReferenceCountedObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IReferenceCountedObject>(),
			IsDynamicTypeModuleLocalClass<IReferenceCountedObject>(),
			{ DynamicTypeBaseClassDef<IReferenceCountedObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IReferenceCountedObject), alignof(IReferenceCountedObject));
		IExclusiveLockableObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IExclusiveLockableObject>(),
			IsDynamicTypeModuleLocalClass<IExclusiveLockableObject>(),
			{ DynamicTypeBaseClassDef<IExclusiveLockableObject, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IExclusiveLockableObject), alignof(IExclusiveLockableObject));
		ISharedLockableObject::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<ISharedLockableObject>(),
			IsDynamicTypeModuleLocalClass<ISharedLockableObject>(),
			{ DynamicTypeBaseClassDef<ISharedLockableObject, IExclusiveLockableObject, 0> },
			0, sizeof(ISharedLockableObject), alignof(ISharedLockableObject));
	}

	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept {
		delete ISharedLockableObject::DynamicTypeThisClassObject;
		ISharedLockableObject::DynamicTypeThisClassObject = nullptr;
		delete IExclusiveLockableObject::DynamicTypeThisClassObject;
		IExclusiveLockableObject::DynamicTypeThisClassObject = nullptr;
		delete IReferenceCountedObject::DynamicTypeThisClassObject;
		IReferenceCountedObject::DynamicTypeThisClassObject = nullptr;
		delete IReferenceCountControlBlock::DynamicTypeThisClassObject;
		IReferenceCountControlBlock::DynamicTypeThisClassObject = nullptr;
	}
}
