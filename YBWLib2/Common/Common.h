#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_30119E3B_9939_4A65_A63A_B13F0B7928DC
#define _INCLUDE_GUARD_30119E3B_9939_4A65_A63A_B13F0B7928DC

#include <cstdint>
#include <cassert>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include "CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	/// <summary>Reads an unsigned integer from a buffer and writes it to an unsigned integral value.</summary>
	/// <param name="buf_uint_from">
	/// An unsigned integer buffer that specifies the value.
	/// The value must be stored in machine byte order.
	/// If the value is too large, the function call will fail.
	/// </param>
	/// <param name="size_buf_uint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_from</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Uint_Ty>
	[[nodiscard]] inline IException* GenericUintFromLarge(_Uint_Ty& uint_ret, const void* buf_uint_from, size_t size_buf_uint_from) noexcept {
		static_assert(::std::is_object_v<_Uint_Ty>, "The specified unsigned integral type is not an object type.");
		static_assert(::std::is_integral_v<_Uint_Ty>, "The specified unsigned integral type is not integral.");
		static_assert(::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not unsigned.");
		if (!size_buf_uint_from) {
			uint_ret = 0;
			return nullptr;
		}
		if (!buf_uint_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
		uint_ret = 0;
		if (sizeof(_Uint_Ty) >= size_buf_uint_from) {
			if (*is_byte_order_le) {
				memcpy(&uint_ret, buf_uint_from, size_buf_uint_from);
				return nullptr;
			} else if (*is_byte_order_be) {
				memcpy(reinterpret_cast<uint8_t*>(&uint_ret) + (sizeof(_Uint_Ty) - size_buf_uint_from), buf_uint_from, size_buf_uint_from);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
			}
		} else {
			if (*is_byte_order_le) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_uint_from) + size_buf_uint_from;
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_uint_from) + sizeof(_Uint_Ty); p_from < limit_p_from; ++p_from)
						if (*p_from)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
				}
				memcpy(&uint_ret, buf_uint_from, sizeof(_Uint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_uint_from) + (size_buf_uint_from - sizeof(_Uint_Ty));
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_uint_from); p_from < limit_p_from; ++p_from)
						if (*p_from)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
				}
				memcpy(&uint_ret, reinterpret_cast<const uint8_t*>(buf_uint_from) + (size_buf_uint_from - sizeof(_Uint_Ty)), sizeof(_Uint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reads an unsigned integer from an unsigned integral value and writes it to a buffer.</summary>
	/// <param name="buf_uint_to">
	/// An unsigned integer buffer that receives the value.
	/// The value will be stored in machine byte order.
	/// </param>
	/// <param name="size_buf_uint_to">
	/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_to</c>.
	/// If the buffer is insufficient to contain the value, the function call will fail.
	/// </param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Uint_Ty>
	[[nodiscard]] inline IException* GenericUintToLarge(_Uint_Ty uint, void* buf_uint_to, size_t size_buf_uint_to) noexcept {
		static_assert(::std::is_object_v<_Uint_Ty>, "The specified unsigned integral type is not an object type.");
		static_assert(::std::is_integral_v<_Uint_Ty>, "The specified unsigned integral type is not integral.");
		static_assert(::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not unsigned.");
		if (!size_buf_uint_to) {
			if (uint)
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			else
				return nullptr;
		}
		if (!buf_uint_to) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
		if (size_buf_uint_to >= sizeof(_Uint_Ty)) {
			if (*is_byte_order_le) {
				memcpy(buf_uint_to, &uint, sizeof(_Uint_Ty));
				memset(reinterpret_cast<uint8_t*>(buf_uint_to) + sizeof(_Uint_Ty), 0, size_buf_uint_to - sizeof(_Uint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(buf_uint_to, 0, size_buf_uint_to - sizeof(_Uint_Ty));
				memcpy(reinterpret_cast<uint8_t*>(buf_uint_to) + (size_buf_uint_to - sizeof(_Uint_Ty)), &uint, sizeof(_Uint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			}
		} else {
			size_t size_needed_uint = sizeof(_Uint_Ty) - count_leading_zero<_Uint_Ty>(uint) / 0x8;
			if (size_buf_uint_to >= size_needed_uint) {
				if (*is_byte_order_le) {
					memcpy(buf_uint_to, &uint, size_needed_uint);
					memset(reinterpret_cast<uint8_t*>(buf_uint_to) + size_needed_uint, 0, size_buf_uint_to - size_needed_uint);
					return nullptr;
				} else if (*is_byte_order_be) {
					memset(buf_uint_to, 0, size_buf_uint_to - size_needed_uint);
					memcpy(reinterpret_cast<uint8_t*>(buf_uint_to) + (size_buf_uint_to - size_needed_uint), reinterpret_cast<const uint8_t*>(&uint) + (sizeof(_Uint_Ty) - size_needed_uint), size_needed_uint);
					return nullptr;
				} else {
					return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
				}
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reads an unsigned integer from a buffer and writes it to another buffer.</summary>
	/// <param name="buf_uint_to">
	/// An unsigned integer buffer that receives the value.
	/// The value will be stored in machine byte order.
	/// </param>
	/// <param name="size_buf_uint_to">
	/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_to</c>.
	/// If the buffer is insufficient to contain the value, the function call will fail.
	/// </param>
	/// <param name="buf_uint_from">
	/// An unsigned integer buffer that specifies the value.
	/// The value must be stored in machine byte order.
	/// If the value is too large, the function call will fail.
	/// </param>
	/// <param name="size_buf_uint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_from</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] inline IException* GenericUintBetweenLarge(void* buf_uint_to, size_t size_buf_uint_to, const void* buf_uint_from, size_t size_buf_uint_from) noexcept {
		if (!size_buf_uint_to) {
			const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_uint_from) + size_buf_uint_from;
			for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_uint_from); p_from < limit_p_from; ++p_from)
				if (*p_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
			return nullptr;
		}
		if (!buf_uint_to) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
		if (!size_buf_uint_from) {
			memset(buf_uint_to, 0, size_buf_uint_to);
			return nullptr;
		}
		if (!buf_uint_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
		if (size_buf_uint_to >= size_buf_uint_from) {
			if (*is_byte_order_le) {
				memcpy(buf_uint_to, buf_uint_from, size_buf_uint_from);
				memset(reinterpret_cast<uint8_t*>(buf_uint_to) + size_buf_uint_from, 0, size_buf_uint_to - size_buf_uint_from);
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(buf_uint_to, 0, size_buf_uint_to - size_buf_uint_from);
				memcpy(reinterpret_cast<uint8_t*>(buf_uint_to) + (size_buf_uint_to - size_buf_uint_from), buf_uint_from, size_buf_uint_from);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
			}
		} else {
			if (*is_byte_order_le) {
				{
					const uint8_t* limit_p = reinterpret_cast<const uint8_t*>(buf_uint_from) + size_buf_uint_from;
					for (const uint8_t* p = reinterpret_cast<const uint8_t*>(buf_uint_from) + size_buf_uint_to; p < limit_p; ++p)
						if (*p)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
				}
				memcpy(buf_uint_to, buf_uint_from, size_buf_uint_to);
				return nullptr;
			} else if (*is_byte_order_be) {
				{
					const uint8_t* limit_p = reinterpret_cast<const uint8_t*>(buf_uint_from) + (size_buf_uint_from - size_buf_uint_to);
					for (const uint8_t* p = reinterpret_cast<const uint8_t*>(buf_uint_from); p < limit_p; ++p)
						if (*p)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
				}
				memcpy(buf_uint_to, reinterpret_cast<const uint8_t*>(buf_uint_from) + (size_buf_uint_from - size_buf_uint_to), size_buf_uint_to);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintBetweenLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reads a signed integer from a buffer and writes it to a signed integral value.</summary>
	/// <param name="buf_sint_from">
	/// A signed integer buffer that specifies the value.
	/// The value must be stored in machine byte order.
	/// If the value has a magnitude that's too large, the function call will fail.
	/// </param>
	/// <param name="size_buf_sint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_from</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Sint_Ty>
	[[nodiscard]] inline IException* GenericSintFromLarge(_Sint_Ty& sint_ret, const void* buf_sint_from, size_t size_buf_sint_from) noexcept {
		static_assert(::std::is_object_v<_Sint_Ty>, "The specified signed integral type is not an object type.");
		static_assert(::std::is_integral_v<_Sint_Ty>, "The specified signed integral type is not integral.");
		static_assert(::std::is_signed_v<_Sint_Ty>, "The specified signed integral type is not signed.");
		if (!size_buf_sint_from) {
			sint_ret = 0;
			return nullptr;
		}
		if (!buf_sint_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
		uint8_t byte_sign_extend = 0;
		if (*is_byte_order_le) {
			byte_sign_extend = ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - 1))) >> (0x8 - 1)) * ~(uint8_t)0;
		} else if (*is_byte_order_be) {
			byte_sign_extend = ((*reinterpret_cast<const uint8_t*>(buf_sint_from)) >> (0x8 - 1)) * ~(uint8_t)0;
		} else {
			return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
		}
		if (sizeof(_Sint_Ty) >= size_buf_sint_from) {
			if (*is_byte_order_le) {
				memcpy(&sint_ret, buf_sint_from, size_buf_sint_from);
				memset(reinterpret_cast<uint8_t*>(&sint_ret) + size_buf_sint_from, byte_sign_extend, sizeof(_Sint_Ty) - size_buf_sint_from);
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(&sint_ret, byte_sign_extend, sizeof(_Sint_Ty) - size_buf_sint_from);
				memcpy(reinterpret_cast<uint8_t*>(&sint_ret) + (sizeof(_Sint_Ty) - size_buf_sint_from), buf_sint_from, size_buf_sint_from);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
			}
		} else {
			if (*is_byte_order_le) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + size_buf_sint_from;
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + sizeof(_Sint_Ty); p_from < limit_p_from; ++p_from)
						if (*p_from != byte_sign_extend)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
				}
				if ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (sizeof(_Sint_Ty) - 1)) & (1 << (0x8 - 1))) != (byte_sign_extend & (1 << (0x8 - 1))))
					return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
				memcpy(&sint_ret, buf_sint_from, sizeof(_Sint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - sizeof(_Sint_Ty));
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_sint_from); p_from < limit_p_from; ++p_from)
						if (*p_from != byte_sign_extend)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
				}
				if ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - sizeof(_Sint_Ty))) & (1 << (0x8 - 1))) != (byte_sign_extend & (1 << (0x8 - 1))))
					return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
				memcpy(&sint_ret, reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - sizeof(_Sint_Ty)), sizeof(_Sint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintFromLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reads a signed integer from a signed integral value and writes it to a buffer.</summary>
	/// <param name="buf_sint_to">
	/// A signed integer buffer that receives the value.
	/// The value will be stored in machine byte order.
	/// </param>
	/// <param name="size_buf_sint_to">
	/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_to</c>.
	/// If the buffer is insufficient to contain the value, the function call will fail.
	/// </param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Sint_Ty>
	[[nodiscard]] inline IException* GenericSintToLarge(_Sint_Ty sint, void* buf_sint_to, size_t size_buf_sint_to) noexcept {
		static_assert(::std::is_object_v<_Sint_Ty>, "The specified signed integral type is not an object type.");
		static_assert(::std::is_integral_v<_Sint_Ty>, "The specified signed integral type is not integral.");
		static_assert(::std::is_signed_v<_Sint_Ty>, "The specified signed integral type is not signed.");
		if (!size_buf_sint_to) {
			if (sint)
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintToLarge);
			else
				return nullptr;
		}
		if (!buf_sint_to) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintToLarge);
		uint8_t byte_sign_extend = sint < 0 ? ~(uint8_t)0 : 0;
		if (size_buf_sint_to >= sizeof(_Sint_Ty)) {
			if (*is_byte_order_le) {
				memcpy(buf_sint_to, &sint, sizeof(_Sint_Ty));
				memset(reinterpret_cast<uint8_t*>(buf_sint_to) + sizeof(_Sint_Ty), byte_sign_extend, size_buf_sint_to - sizeof(_Sint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(buf_sint_to, byte_sign_extend, size_buf_sint_to - sizeof(_Sint_Ty));
				memcpy(reinterpret_cast<uint8_t*>(buf_sint_to) + (size_buf_sint_to - sizeof(_Sint_Ty)), &sint, sizeof(_Sint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintToLarge);
			}
		} else {
			size_t size_needed_sint = sizeof(_Sint_Ty) - (count_leading_zero<::std::make_unsigned_t<_Sint_Ty>>(sint < 0 ? ~(::std::make_unsigned_t<_Sint_Ty>)sint : (::std::make_unsigned_t<_Sint_Ty>)sint) - 1) / 0x8;
			if (size_buf_sint_to >= size_needed_sint) {
				if (*is_byte_order_le) {
					memcpy(buf_sint_to, &sint, size_needed_sint);
					memset(reinterpret_cast<uint8_t*>(buf_sint_to) + size_needed_sint, byte_sign_extend, size_buf_sint_to - size_needed_sint);
					return nullptr;
				} else if (*is_byte_order_be) {
					memset(buf_sint_to, byte_sign_extend, size_buf_sint_to - size_needed_sint);
					memcpy(reinterpret_cast<uint8_t*>(buf_sint_to) + (size_buf_sint_to - size_needed_sint), reinterpret_cast<const uint8_t*>(&sint) + (sizeof(_Sint_Ty) - size_needed_sint), size_needed_sint);
					return nullptr;
				} else {
					return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintToLarge);
				}
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintToLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Reads a signed integer from a buffer and writes it to another buffer.</summary>
	/// <param name="buf_sint_to">
	/// A signed integer buffer that receives the value.
	/// The value will be stored in machine byte order.
	/// </param>
	/// <param name="size_buf_sint_to">
	/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_to</c>.
	/// If the buffer is insufficient to contain the value, the function call will fail.
	/// </param>
	/// <param name="buf_sint_from">
	/// A signed integer buffer that specifies the value.
	/// The value must be stored in machine byte order.
	/// If the value has a magnitude that's too large, the function call will fail.
	/// </param>
	/// <param name="size_buf_sint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_from</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] inline IException* GenericSintBetweenLarge(void* buf_sint_to, size_t size_buf_sint_to, const void* buf_sint_from, size_t size_buf_sint_from) noexcept {
		if (!size_buf_sint_to) {
			const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + size_buf_sint_from;
			for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_sint_from); p_from < limit_p_from; ++p_from)
				if (*p_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
			return nullptr;
		}
		if (!buf_sint_to) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
		if (!size_buf_sint_from) {
			memset(buf_sint_to, 0, size_buf_sint_to);
			return nullptr;
		}
		if (!buf_sint_from) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
		uint8_t byte_sign_extend = 0;
		if (*is_byte_order_le) {
			byte_sign_extend = ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - 1))) >> (0x8 - 1)) * ~(uint8_t)0;
		} else if (*is_byte_order_be) {
			byte_sign_extend = ((*reinterpret_cast<const uint8_t*>(buf_sint_from)) >> (0x8 - 1)) * ~(uint8_t)0;
		} else {
			return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
		}
		if (size_buf_sint_to >= size_buf_sint_from) {
			if (*is_byte_order_le) {
				memcpy(buf_sint_to, buf_sint_from, size_buf_sint_from);
				memset(reinterpret_cast<uint8_t*>(buf_sint_to) + size_buf_sint_from, byte_sign_extend, size_buf_sint_to - size_buf_sint_from);
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(buf_sint_to, byte_sign_extend, size_buf_sint_to - size_buf_sint_from);
				memcpy(reinterpret_cast<uint8_t*>(buf_sint_to) + (size_buf_sint_to - size_buf_sint_from), buf_sint_from, size_buf_sint_from);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
			}
		} else {
			if (*is_byte_order_le) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + size_buf_sint_from;
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + size_buf_sint_to; p_from < limit_p_from; ++p_from)
						if (*p_from != byte_sign_extend)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
				}
				if ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_to - 1)) & (1 << (0x8 - 1))) != (byte_sign_extend & (1 << (0x8 - 1))))
					return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
				memcpy(buf_sint_to, buf_sint_from, size_buf_sint_to);
				return nullptr;
			} else if (*is_byte_order_be) {
				{
					const uint8_t* limit_p_from = reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - size_buf_sint_to);
					for (const uint8_t* p_from = reinterpret_cast<const uint8_t*>(buf_sint_from); p_from < limit_p_from; ++p_from)
						if (*p_from != byte_sign_extend)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
				}
				if ((*(reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - size_buf_sint_to)) & (1 << (0x8 - 1))) != (byte_sign_extend & (1 << (0x8 - 1))))
					return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
				memcpy(buf_sint_to, reinterpret_cast<const uint8_t*>(buf_sint_from) + (size_buf_sint_from - size_buf_sint_to), size_buf_sint_to);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericSintBetweenLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>An object for holding a pointer to another object that's placement-created in memory allocated by a <c>rawallocator_t</c> object.</summary>
	template<typename _Element_Ty>
	struct objholder_rawallocator_t final {
		static_assert(::std::is_object_v<_Element_Ty>, "The element type is not an object type.");
		static_assert(!::std::is_const_v<_Element_Ty>, "The element type is const-qualified.");
		struct construct_obj_t {};
		static constexpr construct_obj_t construct_obj {};
		inline static constexpr void* align(void* _ptr) noexcept {
			return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - 1) % alignof(_Element_Ty)) - 1);
		}
		inline static constexpr const void* align(const void* _ptr) noexcept {
			return reinterpret_cast<const void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty) - 1) % alignof(_Element_Ty)) - 1);
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator) noexcept(false)
			: rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator, _Element_Ty*&& _ptr_element, void*&& _ptr_mem, size_t _size_mem) noexcept(false)
			: rawallocator(_rawallocator), ptr_element(::std::move(_ptr_element)), ptr_mem(::std::move(_ptr_mem)), size_mem(_size_mem) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			_ptr_element = nullptr;
			_ptr_mem = nullptr;
		}
		template<typename... _Args_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, construct_obj_t, _Args_Ty&&... args) noexcept(false)
			: rawallocator(_rawallocator) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty);
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			this->ptr_element = new(this->ptr_mem) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Callable_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, _Callable_Ty _callable) noexcept(false)
			: rawallocator(_rawallocator) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty);
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			this->ptr_element = _callable(static_cast<void*>(this->ptr_mem));
		}
		inline objholder_rawallocator_t(const objholder_rawallocator_t& x) noexcept(false) : rawallocator(x.rawallocator) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (x.is_element_as_mem) {
				if (x.ptr_mem || x.size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (x.ptr_element) {
					this->size_mem = sizeof(_Element_Ty);
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			} else {
				this->size_mem = x.size_mem;
				if (x.ptr_mem) {
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			}
			if (x.ptr_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
				this->ptr_element = new(this->ptr_mem) _Element_Ty(*x.ptr_element);
			}
		}
		inline objholder_rawallocator_t(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->rawallocator = x.rawallocator;
			this->ptr_element = x.ptr_element;
			x.ptr_element = nullptr;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			this->is_element_as_mem = x.is_element_as_mem;
			x.is_element_as_mem = false;
			x.rawallocator = nullptr;
		}
		inline ~objholder_rawallocator_t() {
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				if (this->is_element_as_mem) {
					if (this->ptr_mem || this->size_mem) abort();
					this->ptr_mem = this->ptr_element;
					this->size_mem = sizeof(_Element_Ty);
					this->is_element_as_mem = false;
				}
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				if (!this->rawallocator) abort();
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->is_element_as_mem = false;
			this->rawallocator = nullptr;
		}
		inline objholder_rawallocator_t& operator=(const objholder_rawallocator_t& x) noexcept(false) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				if (this->is_element_as_mem) {
					if (this->ptr_mem || this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->ptr_mem = this->ptr_element;
					this->size_mem = sizeof(_Element_Ty);
					this->is_element_as_mem = false;
				}
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->is_element_as_mem = false;
			this->rawallocator = x.rawallocator;
			if (x.is_element_as_mem) {
				if (x.ptr_mem || x.size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (x.ptr_element) {
					this->size_mem = sizeof(_Element_Ty);
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			} else {
				this->size_mem = x.size_mem;
				if (x.ptr_mem) {
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			}
			if (x.ptr_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, operator=));
				this->ptr_element = new(this->ptr_mem) _Element_Ty(*x.ptr_element);
			}
			return *this;
		}
		inline objholder_rawallocator_t& operator=(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				if (this->is_element_as_mem) {
					if (this->ptr_mem || this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->ptr_mem = this->ptr_element;
					this->size_mem = sizeof(_Element_Ty);
					this->is_element_as_mem = false;
				}
				this->ptr_element = nullptr;
			}
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->is_element_as_mem = false;
			this->rawallocator = x.rawallocator;
			this->ptr_element = x.ptr_element;
			x.ptr_element = nullptr;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			this->is_element_as_mem = x.is_element_as_mem;
			x.is_element_as_mem = false;
			x.rawallocator = nullptr;
			return *this;
		}
		inline explicit operator bool() const noexcept { return this->ptr_element; }
		inline _Element_Ty& operator*() const noexcept {
			assert(this->ptr_element);
			return *this->ptr_element;
		}
		inline _Element_Ty* operator->() const noexcept {
			assert(this->ptr_element);
			return this->ptr_element;
		}
		inline _Element_Ty* const& get() const noexcept { return this->ptr_element; }
		inline void reset(_Element_Ty*&& _ptr_element, void*&& _ptr_mem, size_t _size_mem) noexcept {
			this->free();
			this->ptr_element = _ptr_element;
			_ptr_element = nullptr;
			this->ptr_mem = _ptr_mem;
			_ptr_mem = nullptr;
			this->size_mem = _size_mem;
		}
		inline void release(_Element_Ty*& _ptr_element, void*& _ptr_mem, size_t& _size_mem) noexcept {
			_ptr_element = this->ptr_element;
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_element;
				this->size_mem = sizeof(_Element_Ty);
				this->is_element_as_mem = false;
			}
			this->ptr_element = nullptr;
			_ptr_mem = this->ptr_mem;
			this->ptr_mem = nullptr;
			_size_mem = this->size_mem;
			this->size_mem = nullptr;
		}
		template<typename... _Args_Ty>
		inline void construct(construct_obj_t, _Args_Ty&&... args) noexcept(false) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			if (this->is_element_as_mem && this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				void* ptr_mem_aligned = this->ptr_element;
				this->ptr_element = nullptr;
				this->ptr_element = new(ptr_mem_aligned) _Element_Ty(::std::forward<_Args_Ty>(args)...);
			} else {
				this->destruct();
				this->allocate();
				void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
				if (reinterpret_cast<uintptr_t>(ptr_mem_aligned) + sizeof(_Element_Ty) > reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				this->ptr_element = new(ptr_mem_aligned) _Element_Ty(::std::forward<_Args_Ty>(args)...);
			}
		}
		template<typename _Callable_Ty>
		inline void construct(_Callable_Ty _callable) noexcept(false) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			if (this->is_element_as_mem && this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				void* ptr_mem_aligned = this->ptr_element;
				this->ptr_element = nullptr;
				this->ptr_element = _callable(static_cast<void*>(ptr_mem_aligned));
			} else {
				this->destruct();
				this->allocate();
				void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
				if (reinterpret_cast<uintptr_t>(ptr_mem_aligned) + sizeof(_Element_Ty) > reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				this->ptr_element = _callable(static_cast<void*>(ptr_mem_aligned));
			}
		}
		inline void destruct() noexcept {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_element;
				this->size_mem = sizeof(_Element_Ty);
				this->is_element_as_mem = false;
			}
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
		}
		inline void allocate() noexcept(false) {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_element;
				this->size_mem = sizeof(_Element_Ty);
				this->is_element_as_mem = false;
			}
			if (!this->ptr_mem) {
				this->size_mem = sizeof(_Element_Ty);
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			} else if (reinterpret_cast<uintptr_t>(objholder_rawallocator_t::align(this->ptr_mem)) + sizeof(_Element_Ty) != reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) {
				this->free();
				this->size_mem = sizeof(_Element_Ty);
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty));
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			}
		}
		inline void free() noexcept {
			this->destruct();
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
		}
		inline void set_element_as_mem() noexcept {
			if (!this->is_element_as_mem) free();
			this->is_element_as_mem = true;
		}
		inline _Element_Ty*& get_ref_ptr_element_element_as_mem() noexcept {
			this->set_element_as_mem();
			return this->ptr_element;
		}
	private:
		_Element_Ty* ptr_element = nullptr;
		const rawallocator_t* rawallocator = nullptr;
		void* ptr_mem = nullptr;
		size_t size_mem = 0;
		bool is_element_as_mem = false;
	};

	/// <summary>An object for holding a pointer to an array of objects that's placement-created in memory allocated by a <c>rawallocator_t</c> object.</summary>
	template<typename _Element_Ty>
	struct objholder_rawallocator_t<_Element_Ty[]> final {
		static_assert(::std::is_object_v<_Element_Ty>, "The element type is not an object type.");
		static_assert(!::std::is_const_v<_Element_Ty>, "The element type is const-qualified.");
		struct construct_obj_t {};
		static constexpr construct_obj_t construct_obj {};
		inline static constexpr void* align(void* _ptr) noexcept {
			return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty[]) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty[]) - 1) % alignof(_Element_Ty[])) - 1);
		}
		inline static constexpr const void* align(const void* _ptr) noexcept {
			return reinterpret_cast<const void*>(reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty[]) - ((reinterpret_cast<uintptr_t>(_ptr) + alignof(_Element_Ty[]) - 1) % alignof(_Element_Ty[])) - 1);
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator) noexcept(false)
			: rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
		}
		inline constexpr objholder_rawallocator_t(const rawallocator_t* _rawallocator, _Element_Ty*&& _ptr_array_element, size_t _count_element, void*&& _ptr_mem, size_t _size_mem) noexcept(false)
			: rawallocator(_rawallocator), ptr_array_element(::std::move(_ptr_array_element)), count_element(_count_element), ptr_mem(::std::move(_ptr_mem)), size_mem(_size_mem) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			_ptr_array_element = nullptr;
			_ptr_mem = nullptr;
		}
		template<typename... _Args_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, size_t _count_element, construct_obj_t, _Args_Ty&&... args) noexcept(false)
			: rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty) * _count_element;
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			try {
				this->ptr_array_element = reinterpret_cast<_Element_Ty*>(this->ptr_mem);
				for (this->count_element = 0; this->count_element < _count_element; ++this->count_element)
					new(this->ptr_array_element + this->count_element) _Element_Ty(::std::forward<decltype(::std::declval<_Args_Ty>()[this->count_element])>(args[this->count_element])...);
			} catch (...) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
				throw;
			}
		}
		template<typename _Callable_Ty>
		inline objholder_rawallocator_t(const rawallocator_t* _rawallocator, size_t _count_element, _Callable_Ty _callable) noexcept(false)
			: rawallocator(_rawallocator) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*, size_t>, "The callable value is invalid.");
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->size_mem = sizeof(_Element_Ty) * _count_element;
			this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
			if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			this->count_element = _count_element;
			try {
				this->ptr_array_element = _callable(static_cast<void*>(this->ptr_mem), _count_element);
			} catch (...) {
				this->count_element = 0;
				throw;
			}
		}
		inline objholder_rawallocator_t(const objholder_rawallocator_t& x) noexcept(false) : rawallocator(x.rawallocator) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (x.is_element_as_mem) {
				if (x.ptr_mem || x.size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (x.ptr_array_element) {
					this->size_mem = sizeof(_Element_Ty) * x.count_element;
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			} else {
				this->size_mem = x.size_mem;
				if (x.ptr_mem) {
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			}
			if (x.ptr_array_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
				try {
					this->ptr_array_element = reinterpret_cast<_Element_Ty*>(this->ptr_mem);
					for (this->count_element = 0; this->count_element < x.count_element; ++this->count_element)
						new(this->ptr_array_element + this->count_element) _Element_Ty(static_cast<const _Element_Ty&>(x.ptr_array_element[this->count_element]));
				} catch (...) {
					for (; this->count_element; --this->count_element)
						this->ptr_array_element[this->count_element - 1].~_Element_Ty();
					this->ptr_array_element = nullptr;
					throw;
				}
			}
		}
		inline objholder_rawallocator_t(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			this->rawallocator = x.rawallocator;
			this->ptr_array_element = x.ptr_array_element;
			x.ptr_array_element = nullptr;
			this->count_element = x.count_element;
			x.count_element = 0;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			this->is_element_as_mem = x.is_element_as_mem;
			x.is_element_as_mem = false;
			x.rawallocator = nullptr;
		}
		inline ~objholder_rawallocator_t() {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (this->ptr_array_element) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
			}
			if (this->ptr_mem) {
				if (!this->rawallocator) abort();
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = nullptr;
		}
		inline objholder_rawallocator_t& operator=(const objholder_rawallocator_t& x) noexcept(false) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (this->ptr_array_element) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
			}
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = x.rawallocator;
			if (x.is_element_as_mem) {
				if (x.ptr_mem || x.size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				if (x.ptr_array_element) {
					this->size_mem = sizeof(_Element_Ty) * x.count_element;
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			} else {
				this->size_mem = x.size_mem;
				if (x.ptr_mem) {
					this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
					if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
			}
			if (x.ptr_array_element) {
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
				try {
					this->ptr_array_element = reinterpret_cast<_Element_Ty*>(this->ptr_mem);
					for (this->count_element = 0; this->count_element < x.count_element; ++this->count_element)
						new(this->ptr_array_element + this->count_element) _Element_Ty(static_cast<const _Element_Ty&>(x.ptr_array_element[this->count_element]));
				} catch (...) {
					for (; this->count_element; --this->count_element)
						this->ptr_array_element[this->count_element - 1].~_Element_Ty();
					this->ptr_array_element = nullptr;
					throw;
				}
			}
			return *this;
		}
		inline objholder_rawallocator_t& operator=(objholder_rawallocator_t&& x) noexcept(false) {
			if (!x.rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::objholder_rawallocator_t, objholder_rawallocator_t));
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (this->ptr_array_element) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
			}
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
			this->rawallocator = x.rawallocator;
			this->ptr_array_element = x.ptr_array_element;
			x.ptr_array_element = nullptr;
			this->count_element = x.count_element;
			x.count_element = 0;
			this->ptr_mem = x.ptr_mem;
			x.ptr_mem = nullptr;
			this->size_mem = x.size_mem;
			x.size_mem = 0;
			this->is_element_as_mem = x.is_element_as_mem;
			x.is_element_as_mem = false;
			x.rawallocator = nullptr;
			return *this;
		}
		inline explicit operator bool() const noexcept { return this->ptr_array_element; }
		inline _Element_Ty& operator[](size_t idx_element) const noexcept {
			assert(this->ptr_array_element);
			return this->ptr_array_element[idx_element];
		}
		inline _Element_Ty* const& get() const noexcept { return this->ptr_array_element; }
		inline size_t get_count() const noexcept { return this->count_element; }
		inline void reset(_Element_Ty*&& _ptr_array_element, size_t _count_element, void*&& _ptr_mem, size_t _size_mem) noexcept {
			this->free();
			this->ptr_array_element = _ptr_array_element;
			_ptr_array_element = nullptr;
			this->ptr_mem = _ptr_mem;
			_ptr_mem = nullptr;
			this->count_element = _count_element;
			this->size_mem = _size_mem;
		}
		inline void release(_Element_Ty*& _ptr_array_element, size_t& _count_element, void*& _ptr_mem, size_t& _size_mem) noexcept {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			_ptr_array_element = this->ptr_array_element;
			this->ptr_array_element = nullptr;
			_count_element = this->count_element;
			this->count_element = 0;
			_ptr_mem = this->ptr_mem;
			this->ptr_mem = nullptr;
			_size_mem = this->size_mem;
			this->size_mem = 0;
		}
		template<typename... _Args_Ty>
		inline void construct(size_t _count_element, construct_obj_t, _Args_Ty&&... args) noexcept(false) {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			this->destruct();
			this->allocate(_count_element);
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			if (reinterpret_cast<uintptr_t>(ptr_mem_aligned) + sizeof(_Element_Ty) * _count_element > reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			try {
				this->ptr_array_element = reinterpret_cast<_Element_Ty*>(ptr_mem_aligned);
				for (this->count_element = 0; this->count_element < _count_element; ++this->count_element)
					new(this->ptr_array_element + this->count_element) _Element_Ty(::std::forward<decltype(::std::declval<_Args_Ty>()[this->count_element])>(args[this->count_element])...);
			} catch (...) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
				throw;
			}
		}
		template<typename _Callable_Ty>
		inline void construct(size_t _count_element, _Callable_Ty _callable) noexcept(false) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*, size_t>, "The callable value is invalid.");
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			this->destruct();
			this->allocate(_count_element);
			void* ptr_mem_aligned = objholder_rawallocator_t::align(this->ptr_mem);
			if (reinterpret_cast<uintptr_t>(ptr_mem_aligned) + sizeof(_Element_Ty) * _count_element > reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->count_element = _count_element;
			try {
				this->ptr_array_element = _callable(static_cast<void*>(ptr_mem_aligned), _count_element);
			} catch (...) {
				this->count_element = 0;
				throw;
			}
		}
		inline void destruct() noexcept {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (this->ptr_array_element) {
				for (; this->count_element; --this->count_element)
					this->ptr_array_element[this->count_element - 1].~_Element_Ty();
				this->ptr_array_element = nullptr;
			}
		}
		inline void allocate(size_t _count_element) noexcept(false) {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (!this->ptr_mem) {
				this->size_mem = sizeof(_Element_Ty) * _count_element;
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			} else if (reinterpret_cast<uintptr_t>(objholder_rawallocator_t::align(this->ptr_mem)) + sizeof(_Element_Ty) * _count_element != reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) {
				this->free();
				this->size_mem = sizeof(_Element_Ty) * _count_element;
				this->ptr_mem = this->rawallocator->Allocate(this->size_mem, alignof(_Element_Ty[]));
				if (!this->ptr_mem) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			} else {
				this->destruct();
			}
		}
		template<typename ::std::enable_if<::std::is_trivially_copyable_v<_Element_Ty>, int>::type = 0>
		inline void reallocate(size_t _count_element) noexcept(false) {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			if (!this->ptr_mem) {
				this->allocate(_count_element);
			} else if (reinterpret_cast<uintptr_t>(objholder_rawallocator_t::align(this->ptr_mem)) + sizeof(_Element_Ty) * _count_element < reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) {
				if (this->ptr_array_element) {
					for (
						;
						this->count_element && reinterpret_cast<uintptr_t>(this->ptr_array_element) + sizeof(_Element_Ty) * this->count_element > reinterpret_cast<uintptr_t>(objholder_rawallocator_t::align(this->ptr_mem)) + sizeof(_Element_Ty) * _count_element;
						--this->count_element
						)
						this->ptr_array_element[this->count_element - 1].~_Element_Ty();
					if (!this->count_element) this->ptr_array_element = nullptr;
				}
				void* ptr_mem_old = this->ptr_mem;
				this->ptr_mem = this->rawallocator->Reallocate(ptr_mem_old, this->size_mem, sizeof(_Element_Ty) * _count_element, alignof(_Element_Ty[]));
				if (!this->ptr_mem) {
					this->rawallocator->Deallocate(ptr_mem_old, this->size_mem);
					throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
				this->size_mem = sizeof(_Element_Ty) * _count_element;
			} else if (reinterpret_cast<uintptr_t>(objholder_rawallocator_t::align(this->ptr_mem)) + sizeof(_Element_Ty) * _count_element > reinterpret_cast<uintptr_t>(this->ptr_mem) + this->size_mem) {
				void* ptr_mem_old = this->ptr_mem;
				this->ptr_mem = this->rawallocator->Reallocate(ptr_mem_old, this->size_mem, sizeof(_Element_Ty) * _count_element, alignof(_Element_Ty[]));
				if (!this->ptr_mem) {
					this->rawallocator->Deallocate(ptr_mem_old, this->size_mem);
					throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				}
				this->size_mem = sizeof(_Element_Ty) * _count_element;
			}
		}
		inline void free() noexcept {
			this->destruct();
			if (this->ptr_mem) {
				this->rawallocator->Deallocate(this->ptr_mem, this->size_mem);
				this->ptr_mem = nullptr;
			}
			this->size_mem = 0;
		}
		template<typename ::std::enable_if<::std::is_trivial_v<_Element_Ty>, int>::type = 0>
		inline void set_count(size_t _count_element) noexcept(false) {
			if (this->is_element_as_mem) {
				if (this->ptr_mem || this->size_mem) abort();
				this->ptr_mem = this->ptr_array_element;
				this->size_mem = sizeof(_Element_Ty) * this->count_element;
				this->is_element_as_mem = false;
			}
			this->reallocate(_count_element);
			assert(this->count_element <= _count_element);
			for (; this->count_element < _count_element; ++this->count_element)
				new(this->ptr_array_element + this->count_element) _Element_Ty();
		}
		inline void set_element_as_mem() noexcept {
			if (!this->is_element_as_mem) free();
			this->is_element_as_mem = true;
		}
		inline _Element_Ty*& get_ref_ptr_array_element_element_as_mem() noexcept {
			this->set_element_as_mem();
			return this->ptr_array_element;
		}
		inline size_t& get_ref_count_element_element_as_mem() noexcept {
			this->set_element_as_mem();
			return this->count_element;
		}
	private:
		_Element_Ty* ptr_array_element = nullptr;
		size_t count_element = 0;
		const rawallocator_t* rawallocator = nullptr;
		void* ptr_mem = nullptr;
		size_t size_mem = 0;
		bool is_element_as_mem = false;
	};

	/// <summary>Converts a UTF-8 string into a UTF-16 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output string, in UTF-16.
	/// After successfully returning from this function, <c>*str_out_ret</c> will be set to the output string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_out_ret">
	/// Pointer to a variable that receives the size (in <c>char16_t</c>s) of the output string, in UTF-16.
	/// After successfully returning from this function, <c>*size_str_out_ret</c> will be set to the size (in <c>char16_t</c>s) of the output string.
	/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_in">Pointer to the input string, in UTF-8.</param>
	/// <param name="size_str_in">The size, in <c>char</c>s, of the input string, in UTF-8, pointed to by <c>str_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8StringToUtf16String(
		const rawallocator_t* rawallocator,
		char16_t** str_out_ret,
		size_t* size_str_out_ret,
		const char* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Converts a UTF-16 string into a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output string, in UTF-8.
	/// After successfully returning from this function, <c>*str_out_ret</c> will be set to the output string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_out_ret">
	/// Pointer to a variable that receives the size (in <c>char</c>s) of the output string, in UTF-8.
	/// After successfully returning from this function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the output string.
	/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_in">Pointer to the input string, in UTF-16.</param>
	/// <param name="size_str_in">The size, in <c>char16_t</c>s, of the input string, in UTF-16, pointed to by <c>str_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf16StringToUtf8String(
		const rawallocator_t* rawallocator,
		char** str_out_ret,
		size_t* size_str_out_ret,
		const char16_t* str_in,
		size_t size_str_in
	) noexcept;

	/// <summary>Base64-decodes some data from a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="data_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output data.
	/// After successfully returning from this function, <c>*data_out_ret</c> will be set to a pointer to the output data.
	/// The caller is responsible for freeing the memory pointed to by <c>*data_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*data_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_data_out_ret">
	/// Pointer to a variable that receives the size (in <c>unsigned char</c>s) of the output data.
	/// After successfully returning from this function, <c>*size_data_out_ret</c> will be set to the size (in <c>unsigned char</c>s) of the output data.
	/// Any value originally in <c>*size_data_out_ret</c> will be discarded.
	/// </param>
	/// <param name="str_base64_in">Pointer to the input Base64 string, in UTF-8.</param>
	/// <param name="size_str_base64_in">The size, in <c>char</c>s, of the input Base64 string, in UTF-8, pointed to by <c>str_base64_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Decode(
		const rawallocator_t* rawallocator,
		unsigned char** data_out_ret,
		size_t* size_data_out_ret,
		const char* str_base64_in,
		size_t size_str_base64_in
	) noexcept;

	/// <summary>Base64-encodes some data into a UTF-8 string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_base64_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the output Base64 string, in UTF-8.
	/// After successfully returning from this function, <c>*str_base64_out_ret</c> will be set to the output Base64 string.
	/// The caller is responsible for freeing the memory pointed to by <c>*str_base64_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*str_base64_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_str_base64_out_ret">
	/// Pointer to a variable that receives the size (in <c>char</c>s) of the output Base64 string, in UTF-8.
	/// After successfully returning from this function, <c>*size_str_base64_out_ret</c> will be set to the size (in <c>char</c>s) of the output Base64 string.
	/// Any value originally in <c>*size_str_base64_out_ret</c> will be discarded.
	/// </param>
	/// <param name="data_in">Pointer to the input data.</param>
	/// <param name="size_data_in">The size, in <c>unsigned char</c>s, of the input data, pointed to by <c>data_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Utf8Base64Encode(
		const rawallocator_t* rawallocator,
		char** str_base64_out_ret,
		size_t* size_str_base64_out_ret,
		const unsigned char* data_in,
		size_t size_data_in
	) noexcept;

	/// <summary>Computes the SHA256 cryptographic hash of some data.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="hash_out_ret">
	/// Pointer to a pointer variable that receives a pointer to the hash.
	/// After successfully returning from this function, <c>*hash_out_ret</c> will be set to a pointer to the hash.
	/// The caller is responsible for freeing the memory pointed to by <c>*hash_out_ret</c>.
	/// The memory will be allocated using <paramref name="rawallocator" />.
	/// Any value originally in <c>*hash_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
	/// </param>
	/// <param name="size_hash_out_ret">
	/// Pointer to a variable that receives the size (in <c>unsigned char</c>s) of the hash.
	/// After successfully returning from this function, <c>*size_hash_out_ret</c> will be set to the size (in <c>unsigned char</c>s) of the hash.
	/// Any value originally in <c>*size_hash_out_ret</c> will be discarded.
	/// </param>
	/// <param name="data_in">Pointer to the input data.</param>
	/// <param name="size_data_in">The size, in <c>unsigned char</c>s, of the input data, pointed to by <c>data_in</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE HashSha256(
		const rawallocator_t* rawallocator,
		unsigned char** hash_out_ret,
		size_t* size_hash_out_ret,
		const unsigned char* data_in,
		size_t size_data_in
	) noexcept;

	class IReferenceCountControlBlock;
	class IReferenceCountedObject;

	class IReferenceCountControlBlock abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IReferenceCountControlBlock, YBWLIB2_API, "d42f4bb5-ac59-41a8-90f7-5ae9b6db6f7a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IReferenceCountControlBlock);
		/// <summary>
		/// Gets the strong reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The current strong reference count.</returns>
		virtual uintptr_t GetStrongReferenceCount() const noexcept = 0;
		/// <summary>
		/// Gets the weak reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The current weak reference count.</returns>
		virtual uintptr_t GetWeakReferenceCount() const noexcept = 0;
		/// <summary>
		/// Increments the strong reference count if and only if the object managed by this control block hasn't expired yet.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>
		/// The new strong reference count.
		/// <c>0</c> will be returned if and only if the object managed by this control block has already expired.
		/// </returns>
		virtual uintptr_t IncStrongReferenceCount() noexcept = 0;
		/// <summary>
		/// Decrements the strong reference count.
		/// Permits the object to be freed if the strong reference count reaches <c>0</c>.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new strong reference count.</returns>
		virtual uintptr_t DecStrongReferenceCount() noexcept = 0;
		/// <summary>
		/// Increments the weak reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new weak reference count.</returns>
		virtual uintptr_t IncWeakReferenceCount() noexcept = 0;
		/// <summary>
		/// Decrements the weak reference count.
		/// Permits the control block to be freed if BOTH the strong reference count AND the weak reference count reaches <c>0</c>.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new weak reference count.</returns>
		virtual uintptr_t DecWeakReferenceCount() noexcept = 0;
		/// <summary>
		/// Gets whether the object managed by this control block has expired.
		/// This function must be thread-safe.
		/// However, a <c>false</c> return is inherently unreliable, as the object may become expired after the function returns, but before the caller takes subsequent actions.
		/// </summary>
		/// <returns>Whether the object managed by this control block has expired.</returns>
		virtual bool HasObjectExpired() const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IReferenceCountControlBlock() = default;
	};

	/// <summary>Reference counted object.</summary>
	class IReferenceCountedObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IReferenceCountedObject, YBWLIB2_API, "6abec0cb-c444-492c-af61-04f502ade136");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IReferenceCountedObject);
		/// <summary>
		/// Returns an <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.
		/// If the control block hasn't been set up yet, it will be created and set up.
		/// </summary>
		/// <returns>A <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.</returns>
		virtual IReferenceCountControlBlock* GetReferenceCountControlBlock() const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IReferenceCountedObject() = default;
	};

	/// <summary>Lockable object that only supports locking in exclusive mode.</summary>
	class IExclusiveLockableObject abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExclusiveLockableObject, YBWLIB2_API, "6fdf58be-4668-4967-8f62-9ab35b5cc271");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExclusiveLockableObject);
		/// <summary>Locks the object in exclusive mode. Blocks if necessary.</summary>
		virtual void LockExclusive() const noexcept = 0;
		/// <summary>Tries to lock the object in exclusive mode. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		virtual bool TryLockExclusive() const noexcept = 0;
		/// <summary>Unlocks the object in exclusive mode.</summary>
		virtual void UnlockExclusive() const noexcept = 0;
	};

	/// <summary>Lockable object that supports locking in both exclusive mode and shared mode.</summary>
	class ISharedLockableObject abstract : public IExclusiveLockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ISharedLockableObject, YBWLIB2_API, "be035d02-3a8b-431c-bae5-c02a7897c9f6");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ISharedLockableObject);
		/// <summary>
		/// Locks the object in shared mode. Blocks if necessary.
		/// Multiple threads may simultaneously lock an object in shared mode.
		/// However, when an object is locked in exclusive mode, no other thread may lock that object in either mode.
		/// </summary>
		virtual void LockShared() const noexcept = 0;
		/// <summary>Tries to lock the object in shared mode. Fail immediately if it's already locked in exclusive mode by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		virtual bool TryLockShared() const noexcept = 0;
		/// <summary>Unlocks the object in shared mode.</summary>
		virtual void UnlockShared() const noexcept = 0;
	};

	/// <summary>Lockable object that supports recursive locking in both exclusive mode and shared mode.</summary>
	class RecursiveSharedLockableObject abstract : public ISharedLockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(RecursiveSharedLockableObject, , "74b4f459-39c8-4c41-b367-37907dec7e39");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(RecursiveSharedLockableObject);
		/// <summary>Locks the object in exclusive mode. Blocks if necessary.</summary>
		inline virtual void LockExclusive() const noexcept override {
			if (!objholder_map_lockcount_recursive) objholder_map_lockcount_recursive.construct(objholder_local_t<map_lockcount_recursive_t>::construct_obj);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.second);
			if (!it_map_lockcount_recursive->second.first) {
				this->mtx_this_prelock.lock();
				this->mtx_this.lock();
				this->mtx_this_prelock.unlock();
			}
			++it_map_lockcount_recursive->second.first;
		}
		/// <summary>Tries to lock the object in exclusive mode. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLockExclusive() const noexcept override {
			if (!objholder_map_lockcount_recursive) objholder_map_lockcount_recursive.construct(objholder_local_t<map_lockcount_recursive_t>::construct_obj);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.second);
			if (!it_map_lockcount_recursive->second.first) {
				if (this->mtx_this.try_lock()) {
					++it_map_lockcount_recursive->second.first;
					return true;
				} else {
					return false;
				}
			} else {
				++it_map_lockcount_recursive->second.first;
				return true;
			}
		}
		/// <summary>Unlocks the object in exclusive mode.</summary>
		inline virtual void UnlockExclusive() const noexcept override {
			assert(objholder_map_lockcount_recursive);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->find(this);
			assert(it_map_lockcount_recursive != objholder_map_lockcount_recursive->end());
			assert(it_map_lockcount_recursive->second.first && !it_map_lockcount_recursive->second.second);
			if (!--it_map_lockcount_recursive->second.first) {
				this->mtx_this.unlock();
			}
		}
		/// <summary>
		/// Locks the object in shared mode. Blocks if necessary.
		/// Multiple threads may simultaneously lock an object in shared mode.
		/// However, when an object is locked in exclusive mode, no other thread may lock that object in either mode.
		/// </summary>
		inline virtual void LockShared() const noexcept override {
			if (!objholder_map_lockcount_recursive) objholder_map_lockcount_recursive.construct(objholder_local_t<map_lockcount_recursive_t>::construct_obj);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.first);
			if (!it_map_lockcount_recursive->second.second) {
				this->mtx_this_prelock.lock_shared();
				this->mtx_this.lock_shared();
				this->mtx_this_prelock.unlock_shared();
			}
			++it_map_lockcount_recursive->second.second;
		}
		/// <summary>Tries to lock the object in shared mode. Fail immediately if it's already locked in exclusive mode by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLockShared() const noexcept override {
			if (!objholder_map_lockcount_recursive) objholder_map_lockcount_recursive.construct(objholder_local_t<map_lockcount_recursive_t>::construct_obj);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.first);
			if (!it_map_lockcount_recursive->second.second) {
				if (this->mtx_this_prelock.try_lock_shared()) {
					bool is_successful = this->mtx_this.try_lock_shared();
					this->mtx_this_prelock.unlock_shared();
					if (is_successful) {
						++it_map_lockcount_recursive->second.second;
						return true;
					} else {
						return false;
					}
				} else {
					return false;
				}
			} else {
				++it_map_lockcount_recursive->second.second;
				return true;
			}
		}
		/// <summary>Unlocks the object in shared mode.</summary>
		inline virtual void UnlockShared() const noexcept override {
			assert(objholder_map_lockcount_recursive);
			map_lockcount_recursive_t::iterator it_map_lockcount_recursive = objholder_map_lockcount_recursive->find(this);
			assert(it_map_lockcount_recursive != objholder_map_lockcount_recursive->end());
			assert(!it_map_lockcount_recursive->second.first && it_map_lockcount_recursive->second.second);
			if (!--it_map_lockcount_recursive->second.second) {
				this->mtx_this.unlock_shared();
			}
		}
	protected:
		using map_lockcount_recursive_t = ::std::unordered_map<const RecursiveSharedLockableObject*, ::std::pair<uintptr_t, uintptr_t>>;
		thread_local static objholder_local_t<map_lockcount_recursive_t> objholder_map_lockcount_recursive;
		/// <summary>A <c>::std::shared_mutex</c> object used to control concurrent accesses to this object.</summary>
		mutable ::std::shared_mutex mtx_this;
		/// <summary>
		/// Another <c>::std::shared_mutex</c> object used to prevent resource starvation of threads waiting to exclusively lock the object.
		/// <c>LockShared</c> and <c>TryLockShared</c> acquires shared ownership of this mutex before locking <c>mtx_this</c> and releases this mutex after locking (NOT unlocking) <c>mtx_this</c>.
		/// </summary>
		mutable ::std::shared_mutex mtx_this_prelock;
	};

	class ReferenceCountControlBlock;
	class ReferenceCountedObject;
	template<typename _Element_Ty>
	class ReferenceCountedObjectHolder;
	template<typename _Element_Ty>
	class ReferenceCountedObjectWeakHolder;

	/// <summary>
	/// Reference count control block for <c>ReferenceCountedObject</c>.
	/// Has a strong reference count of <c>1</c> when constructed.
	/// Has a weak reference count of <c>1</c> reserved for itself, so that the control block will remain available when there are still strong references.
	/// </summary>
	class ReferenceCountControlBlock abstract : public virtual IReferenceCountControlBlock {
		friend class ReferenceCountedObject;
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ReferenceCountControlBlock, , "d0698257-3fa5-47fa-931e-3af23c4322e9");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ReferenceCountControlBlock);
		ReferenceCountControlBlock() noexcept = default;
		ReferenceCountControlBlock(const ReferenceCountControlBlock&) = delete;
		ReferenceCountControlBlock(ReferenceCountControlBlock&&) = delete;
		ReferenceCountControlBlock& operator=(const ReferenceCountControlBlock&) = delete;
		ReferenceCountControlBlock& operator=(ReferenceCountControlBlock&&) = delete;
		/// <summary>
		/// Gets the strong reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The current strong reference count.</returns>
		inline virtual uintptr_t GetStrongReferenceCount() const noexcept override {
			return this->ref_count_strong.load(::std::memory_order_relaxed);
		}
		/// <summary>
		/// Gets the weak reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The current weak reference count.</returns>
		inline virtual uintptr_t GetWeakReferenceCount() const noexcept override {
			return this->ref_count_weak.load(::std::memory_order_relaxed);
		}
		/// <summary>
		/// Increments the strong reference count, if and only if the object managed by this control block hasn't expired yet.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>
		/// The new strong reference count.
		/// <c>0</c> will be returned if and only if the object managed by this control block has already expired.
		/// </returns>
		inline virtual uintptr_t IncStrongReferenceCount() noexcept override {
			uintptr_t ref_count_strong_old = this->ref_count_strong.load(::std::memory_order_relaxed);
			while (ref_count_strong_old && !this->ref_count_strong.compare_exchange_weak(ref_count_strong_old, ref_count_strong_old + 1, ::std::memory_order_acq_rel, ::std::memory_order_relaxed));
			return ref_count_strong_old ? ref_count_strong_old + 1 : 0;
		}
		/// <summary>
		/// Decrements the strong reference count.
		/// Permits the object to be freed if the strong reference count reaches <c>0</c>.
		/// Permits the control block to be freed if the weak reference count reaches <c>0</c>.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new strong reference count.</returns>
		inline virtual uintptr_t DecStrongReferenceCount() noexcept override {
			uintptr_t ref_count_strong_old = this->ref_count_strong.fetch_sub(1, ::std::memory_order_acq_rel);
			assert(ref_count_strong_old);
			if (ref_count_strong_old == 1) this->DestroyManagedObject();
			return ref_count_strong_old - 1;
		}
		/// <summary>
		/// Increments the weak reference count.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new weak reference count.</returns>
		inline virtual uintptr_t IncWeakReferenceCount() noexcept override {
			uintptr_t ref_count_weak_old = this->ref_count_weak.fetch_add(1, ::std::memory_order_relaxed);
			assert(ref_count_weak_old);
			return ref_count_weak_old + 1;
		}
		/// <summary>
		/// Decrements the weak reference count.
		/// Permits the control block to be freed if the weak reference count reaches <c>0</c>.
		/// This function must be thread-safe.
		/// </summary>
		/// <returns>The new weak reference count.</returns>
		inline virtual uintptr_t DecWeakReferenceCount() noexcept override {
			uintptr_t ref_count_weak_old = this->ref_count_weak.fetch_sub(1, ::std::memory_order_acq_rel);
			assert(ref_count_weak_old);
			if (ref_count_weak_old == 1) this->DestroyControlBlock();
			return ref_count_weak_old - 1;
		}
		/// <summary>
		/// Gets whether the object managed by this control block has expired.
		/// This function must be thread-safe.
		/// However, a <c>false</c> return is inherently unreliable, as the object may become expired after the function returns, but before the caller takes subsequent actions.
		/// </summary>
		/// <returns>Whether the object managed by this control block has expired.</returns>
		inline virtual bool HasObjectExpired() const noexcept override {
			return !this->GetWeakReferenceCount();
		}
	protected:
		inline virtual ~ReferenceCountControlBlock() {
			assert(!this->ref_count_strong.load(::std::memory_order_acquire));
			assert(!this->ref_count_weak.load(::std::memory_order_acquire));
		}
		/// <summary>Destroys the object managed by this control block.</summary>
		virtual void DestroyManagedObject() noexcept = 0;
		/// <summary>Destroys this control block itself.</summary>
		virtual void DestroyControlBlock() noexcept = 0;
	private:
		mutable ::std::atomic<uintptr_t> ref_count_strong = 1;
		mutable ::std::atomic<uintptr_t> ref_count_weak = 1;
	};

	/// <summary>
	/// Potentially reference counted object.
	/// Does NOT has a reference count control block when constructed.
	/// </summary>
	class ReferenceCountedObject abstract : public virtual IReferenceCountedObject {
	private:
		template<typename _Element_Ty, typename... _Args_Ty>
		friend ReferenceCountedObjectHolder<_Element_Ty> MakeReferenceCountedObject(_Args_Ty&&... _args) noexcept(::std::is_nothrow_constructible_v<_Element_Ty, _Args_Ty &&...>);
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ReferenceCountedObject, , "8c28401a-e53e-4f56-ab55-7a21fb37be19");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ReferenceCountedObject);
		inline ReferenceCountedObject() noexcept = default;
		inline ReferenceCountedObject(const ReferenceCountedObject& x) noexcept {
			static_cast<void>(x);
			this->controlblock = nullptr;
		}
		inline ReferenceCountedObject(ReferenceCountedObject&& x) noexcept {
			static_cast<void>(x);
			this->controlblock = nullptr;
		}
		virtual ~ReferenceCountedObject() {
			if (this->controlblock) {
				this->controlblock->DecWeakReferenceCount();
				this->controlblock = nullptr;
			}
		}
		inline ReferenceCountedObject& operator=(const ReferenceCountedObject& x) noexcept {
			static_cast<void>(x);
			return *this;
		}
		inline ReferenceCountedObject& operator=(ReferenceCountedObject&& x) noexcept {
			static_cast<void>(x);
			return *this;
		}
		/// <summary>
		/// Returns an <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.
		/// If the control block hasn't been set up yet, it will be created and set up.
		/// </summary>
		/// <returns>A <c>IReferenceCountControlBlock*</c> pointer to the control block that manages the object.</returns>
		inline virtual IReferenceCountControlBlock* GetReferenceCountControlBlock() const noexcept override {
			if (!this->controlblock) {
				::std::call_once(
					this->onceflag_controlblock,
					[this]() noexcept->void {
						class ControlBlock final : public ReferenceCountControlBlock {
						public:
							explicit ControlBlock(ReferenceCountedObject* _refcountedobject_managed) : refcountedobject_managed(_refcountedobject_managed) {}
							ControlBlock(const ControlBlock&) = delete;
							ControlBlock(ControlBlock&&) = delete;
							ControlBlock& operator=(const ControlBlock&) = delete;
							ControlBlock& operator=(ControlBlock&&) = delete;
							/// <summary>Destroys the object managed by this control block.</summary>
							inline virtual void DestroyManagedObject() noexcept override {
								delete this->refcountedobject_managed;
								this->refcountedobject_managed = nullptr;
							}
							/// <summary>Destroys this control block itself.</summary>
							inline virtual void DestroyControlBlock() noexcept override {
								delete this;
							}
						private:
							ReferenceCountedObject* refcountedobject_managed = nullptr;
						};
						this->controlblock = new ControlBlock(const_cast<ReferenceCountedObject*>(this));
					}
				);
				assert(this->controlblock);
			}
			return this->controlblock;
		}
	protected:
		mutable ReferenceCountControlBlock* controlblock = nullptr;
		mutable ::std::once_flag onceflag_controlblock;
	};

	/// <summary>
	/// Reference counted object holder.
	/// Counts as one strong reference of the owned object until destructed.
	/// </summary>
	/// <typeparam name="_Element_Ty">The type of the object objects of this class dereferences to.</typeparam>
	template<typename _Element_Ty>
	class ReferenceCountedObjectHolder final {
		template<typename _Element_Ty_Other>
		friend class ReferenceCountedObjectHolder;
		template<typename _Element_Ty_Other>
		friend class ReferenceCountedObjectWeakHolder;
	public:
		struct inc_ref_count_t {};
		static constexpr inc_ref_count_t inc_ref_count {};
		using element_type = _Element_Ty;
		constexpr ReferenceCountedObjectHolder() noexcept {}
		constexpr ReferenceCountedObjectHolder(nullptr_t) noexcept : ReferenceCountedObjectHolder() {}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that owns the object the specified pointer points to, incrementing the object's strong reference count.
		/// Use this function on a pointer to an already reference-counted object that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectHolder(_Element_From_Ty* _ptr, inc_ref_count_t) noexcept {
			static_assert(::std::is_base_of_v<IReferenceCountedObject, _Element_From_Ty>, "The element type isn't derived from IReferenceCountedObject.");
			if (_ptr) {
				const IReferenceCountedObject* refcountedobject_owned = _ptr;
				this->controlblock_owned = refcountedobject_owned->GetReferenceCountControlBlock();
				assert(this->controlblock_owned);
				uintptr_t ref_count_strong_new = this->controlblock_owned->IncStrongReferenceCount();
				assert(ref_count_strong_new);
				this->ptr_stored = _ptr;
			}
		}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that manages the object the specified pointer points to, without changing the object's reference count.
		/// Use this function on a pointer to a freshly-created object whose reference count control block hasn't been set up yet,
		/// or an already reference-counted object that has <c>1</c> strong reference count reserved for the caller..
		/// </summary>
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline explicit ReferenceCountedObjectHolder(_Element_From_Ty*&& _ptr) noexcept {
			static_assert(::std::is_base_of_v<IReferenceCountedObject, _Element_From_Ty>, "The element type isn't derived from IReferenceCountedObject.");
			if (_ptr) {
				const IReferenceCountedObject* refcountedobject_owned = _ptr;
				this->controlblock_owned = refcountedobject_owned->GetReferenceCountControlBlock();
				assert(this->controlblock_owned);
				this->ptr_stored = _ptr;
				_ptr = nullptr;
			}
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectHolder(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			this->assign(::std::move(x));
		}
		template<typename _Element_From_Ty>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x, element_type* _ptr) noexcept {
			if (x.controlblock_owned) {
				uintptr_t ref_count_strong_new = x.controlblock_owned->IncStrongReferenceCount();
				assert(ref_count_strong_new);
				this->controlblock_owned = x.controlblock_owned;
			}
			if (_ptr) this->ptr_stored = _ptr;
		}
		inline ~ReferenceCountedObjectHolder() {
			this->reset();
		}
		inline element_type* const& get() const noexcept { return this->ptr_stored; }
		inline explicit operator bool() const noexcept { return this->ptr_stored; }
		inline element_type& operator*() const noexcept { return *this->ptr_stored; }
		inline element_type* operator->() const noexcept { return this->ptr_stored; }
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectHolder& operator=(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
			return *this;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectHolder& operator=(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			this->assign(::std::move(x));
			return *this;
		}
		template<typename _Element_From_Ty>
		inline bool owner_before(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) const noexcept { return this->controlblock_owned < x.controlblock_owned; }
		template<typename _Element_From_Ty>
		inline bool owner_before(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) const noexcept;
		inline void reset() noexcept {
			if (this->controlblock_owned) {
				this->controlblock_owned->DecStrongReferenceCount();
				this->controlblock_owned = nullptr;
			}
			this->ptr_stored = nullptr;
		}
		inline void reset(nullptr_t) noexcept {
			this->reset();
		}
		/// <summary>
		/// Makes this object manages the object the specified pointer points to, incrementing the later object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void reset(_Element_From_Ty* _ptr, inc_ref_count_t) noexcept {
			ReferenceCountedObjectHolder<element_type>(_ptr, inc_ref_count).swap(*this);
		}
		/// <summary>
		/// Makes this object manage the object the specified pointer points to, without changing the later object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void reset(_Element_From_Ty*&& _ptr) noexcept {
			ReferenceCountedObjectHolder<element_type>(::std::move(_ptr)).swap(*this);
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void assign(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->reset();
			if (x.controlblock_owned) {
				uintptr_t ref_count_strong_new = x.controlblock_owned->IncStrongReferenceCount();
				assert(ref_count_strong_new);
				this->controlblock_owned = x.controlblock_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void assign(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			this->reset();
			this->ptr_stored = x.ptr_stored;
			this->controlblock_owned = x.controlblock_owned;
			x.ptr_stored = nullptr;
			x.controlblock_owned = nullptr;
		}
		/// <summary>Releases the stored pointer and the owned control block without changing the reference count.</summary>
		[[nodiscard]] inline IReferenceCountControlBlock*&& release(element_type*& _ptr_ret) noexcept {
			element_type* ptr_stored_old = this->ptr_stored;
			IReferenceCountControlBlock* controlblock_owned_old = this->controlblock_owned;
			this->ptr_stored = nullptr;
			this->controlblock_owned = nullptr;
			_ptr_ret = ptr_stored_old;
			return ::std::move(controlblock_owned_old);
		}
		/// <summary>
		/// Releases the stored pointer without changing the reference count.
		/// The owned control block must be the one that manages the stored pointer.
		/// </summary>
		[[nodiscard]] inline element_type*&& release() noexcept {
			static_assert(::std::is_base_of_v<IReferenceCountedObject, element_type>, "The element type isn't derived from IReferenceCountedObject.");
			element_type* ptr_stored_old = this->ptr_stored;
			if (ptr_stored_old) {
				const IReferenceCountedObject* refcountedobject_stored_old = ptr_stored_old;
				assert(this->controlblock_owned == refcountedobject_stored_old->GetReferenceCountControlBlock());
			} else {
				assert(!this->controlblock_owned);
			}
			this->ptr_stored = nullptr;
			this->controlblock_owned = nullptr;
			return ::std::move(ptr_stored_old);
		}
		inline void swap(ReferenceCountedObjectHolder& x) noexcept {
			element_type* ptr_stored_temp = this->ptr_stored;
			IReferenceCountControlBlock* controlblock_owned_temp = this->controlblock_owned;
			this->ptr_stored = x.ptr_stored;
			this->controlblock_owned = x.controlblock_owned;
			x.ptr_stored = ptr_stored_temp;
			x.controlblock_owned = controlblock_owned_temp;
		}
		inline bool unique() const noexcept { return this->controlblock_owned && this->controlblock_owned->GetStrongReferenceCount() == 1; }
		inline uintptr_t use_count() const noexcept { return this->controlblock_owned ? this->controlblock_owned->GetStrongReferenceCount() : 0; }
		inline uintptr_t weak_count() const noexcept { return this->controlblock_owned ? this->controlblock_owned->GetWeakReferenceCount() : 0; }
	protected:
		element_type* ptr_stored = nullptr;
		IReferenceCountControlBlock* controlblock_owned = nullptr;
	};
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() == nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() != nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() < nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() <= nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() > nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() >= nullptr; }

	/// <summary>
	/// Reference counted object weak holder.
	/// Counts as one weak reference of the owned object until destructed.
	/// </summary>
	/// <typeparam name="_Element_Ty">The type of the object objects of this class dereferences to.</typeparam>
	template<typename _Element_Ty>
	class ReferenceCountedObjectWeakHolder final {
		template<typename _Element_Ty_Other>
		friend class ReferenceCountedObjectHolder;
		template<typename _Element_Ty_Other>
		friend class ReferenceCountedObjectWeakHolder;
	public:
		struct inc_ref_count_t {};
		static constexpr inc_ref_count_t inc_ref_count {};
		using element_type = _Element_Ty;
		constexpr ReferenceCountedObjectWeakHolder() noexcept {}
		constexpr ReferenceCountedObjectWeakHolder(nullptr_t) noexcept : ReferenceCountedObjectWeakHolder() {}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder(ReferenceCountedObjectWeakHolder<_Element_From_Ty>&& x) noexcept {
			this->assign(::std::move(x));
		}
		inline ~ReferenceCountedObjectWeakHolder() {
			this->reset();
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder& operator=(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
			return *this;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder& operator=(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) noexcept {
			this->assign(x);
			return *this;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline ReferenceCountedObjectWeakHolder& operator=(ReferenceCountedObjectWeakHolder<_Element_From_Ty>&& x) noexcept {
			this->assign(::std::move(x));
			return *this;
		}
		template<typename _Element_To_Ty, typename ::std::enable_if<::std::is_convertible_v<element_type*, _Element_To_Ty*>, int>::type = 0>
		inline operator ReferenceCountedObjectHolder<_Element_To_Ty>() const noexcept {
			ReferenceCountedObjectHolder<_Element_To_Ty> refcountedobjectholder;
			if (!this->controlblock_owned || !this->controlblock_owned->IncStrongReferenceCount()) {
				assert(false);
				abort();
			}
			refcountedobjectholder.controlblock_owned = this->controlblock_owned;
			refcountedobjectholder.ptr_stored = this->ptr_stored;
			return refcountedobjectholder;
		}
		inline bool expired() const noexcept {
			return this->controlblock_owned ? this->controlblock_owned->HasObjectExpired() : true;
		}
		template<typename _Element_From_Ty>
		inline bool owner_before(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) const noexcept { return this->controlblock_owned < x.controlblock_owned; }
		template<typename _Element_From_Ty>
		inline bool owner_before(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) const noexcept;
		inline ReferenceCountedObjectHolder<element_type> lock() const noexcept {
			ReferenceCountedObjectHolder<element_type> refcountedobjectholder;
			if (this->controlblock_owned && this->controlblock_owned->IncStrongReferenceCount()) {
				refcountedobjectholder.controlblock_owned = this->controlblock_owned;
				refcountedobjectholder.ptr_stored = this->ptr_stored;
			}
			return refcountedobjectholder;
		}
		inline void reset() noexcept {
			if (this->controlblock_owned) {
				this->controlblock_owned->DecWeakReferenceCount();
				this->controlblock_owned = nullptr;
			}
			this->ptr_stored = nullptr;
		}
		inline void reset(nullptr_t) noexcept {
			this->reset();
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void assign(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			this->reset();
			if (x.controlblock_owned) {
				uintptr_t ref_count_weak_new = x.controlblock_owned->IncWeakReferenceCount();
				assert(ref_count_weak_new);
				this->controlblock_owned = x.controlblock_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void assign(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) noexcept {
			this->reset();
			if (x.controlblock_owned) {
				uintptr_t ref_count_weak_new = x.controlblock_owned->IncWeakReferenceCount();
				assert(ref_count_weak_new);
				this->controlblock_owned = x.controlblock_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, typename ::std::enable_if<::std::is_convertible_v<_Element_From_Ty*, element_type*>, int>::type = 0>
		inline void assign(ReferenceCountedObjectWeakHolder<_Element_From_Ty>&& x) noexcept {
			this->reset();
			this->ptr_stored = x.ptr_stored;
			this->controlblock_owned = x.controlblock_owned;
			x.ptr_stored = nullptr;
			x.controlblock_owned = nullptr;
		}
		/// <summary>Releases the stored pointer and the owned control block without changing the reference count.</summary>
		[[nodiscard]] inline IReferenceCountControlBlock*&& release(element_type*& _ptr_ret) noexcept {
			element_type* ptr_stored_old = this->ptr_stored;
			IReferenceCountControlBlock* controlblock_owned_old = this->controlblock_owned;
			this->ptr_stored = nullptr;
			this->controlblock_owned = nullptr;
			_ptr_ret = ptr_stored_old;
			return ::std::move(controlblock_owned_old);
		}
		inline void swap(ReferenceCountedObjectWeakHolder& x) noexcept {
			element_type* ptr_stored_temp = this->ptr_stored;
			IReferenceCountControlBlock* controlblock_owned_temp = this->controlblock_owned;
			this->ptr_stored = x.ptr_stored;
			this->controlblock_owned = x.controlblock_owned;
			x.ptr_stored = ptr_stored_temp;
			x.controlblock_owned = controlblock_owned_temp;
		}
		inline uintptr_t use_count() const noexcept { return this->controlblock_owned ? this->controlblock_owned->GetStrongReferenceCount() : 0; }
		inline uintptr_t weak_count() const noexcept { return this->controlblock_owned ? this->controlblock_owned->GetWeakReferenceCount() : 0; }
	protected:
		element_type* ptr_stored = nullptr;
		IReferenceCountControlBlock* controlblock_owned = nullptr;
	};
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator==(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() == nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator!=(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() != nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() < nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<=(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() <= nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() > nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>=(const ReferenceCountedObjectWeakHolder<_Element_L_Ty>& l, const ReferenceCountedObjectWeakHolder<_Element_R_Ty>& r) { return l.get() >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(nullptr_t, const ReferenceCountedObjectWeakHolder<_Element_Ty>& r) { return nullptr >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(const ReferenceCountedObjectWeakHolder<_Element_Ty>& l, nullptr_t) { return l.get() >= nullptr; }

	template<typename _Element_Ty>
	template<typename _Element_From_Ty>
	inline bool ReferenceCountedObjectHolder<_Element_Ty>::owner_before(const ReferenceCountedObjectWeakHolder<_Element_From_Ty>& x) const noexcept { return this->controlblock_owned < x.controlblock_owned; }
	template<typename _Element_Ty>
	template<typename _Element_From_Ty>
	inline bool ReferenceCountedObjectWeakHolder<_Element_Ty>::owner_before(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) const noexcept { return this->controlblock_owned < x.controlblock_owned; }

	template<
		typename _Element_Ty,
		typename... _Args_Ty,
		typename ::std::enable_if<::std::is_base_of_v<ReferenceCountedObject, _Element_Ty>, int>::type = 0
	>
		inline ReferenceCountedObjectHolder<_Element_Ty> MakeReferenceCountedObject(_Args_Ty&&... _args) noexcept(::std::is_nothrow_constructible_v<_Element_Ty, _Args_Ty&&...>) {
		using element_type = _Element_Ty;
		class ControlBlock final : public ReferenceCountControlBlock {
		public:
			explicit ControlBlock(_Args_Ty&&... _args) noexcept(::std::is_nothrow_constructible_v<element_type, _Args_Ty&&...>) {
				new(&this->GetElement()) element_type(::std::forward<_Args_Ty>(_args)...);
			}
			//ControlBlock(const ControlBlock&) = delete;
			//ControlBlock(ControlBlock&&) = delete;
			//ControlBlock& operator=(const ControlBlock&) = delete;
			//ControlBlock& operator=(ControlBlock&&) = delete;
			inline const element_type* GetElement() const noexcept { return reinterpret_cast<const element_type*>(&this->buf_element); }
			inline element_type* GetElement() noexcept { return reinterpret_cast<element_type*>(&this->buf_element); }
			inline const ReferenceCountedObject* GetManagedObject() const noexcept { return static_cast<ReferenceCountedObject*>(this->GetElement()); }
			inline ReferenceCountedObject* GetManagedObject() noexcept { return static_cast<ReferenceCountedObject*>(this->GetElement()); }
			/// <summary>Destroys the object managed by this control block.</summary>
			inline virtual void DestroyManagedObject() noexcept override {
				this->GetManagedObject()->~element_type();
			}
			/// <summary>Destroys this control block itself.</summary>
			inline virtual void DestroyControlBlock() noexcept override {
				delete this;
			}
		private:
			alignas(alignof(element_type)) unsigned char buf_element[sizeof(element_type)] = {};
		};
		ControlBlock* controlblock = new ControlBlock(::std::forward<_Args_Ty>(_args)...);
		assert(controlblock);
		ReferenceCountedObject* refcountedobject_managed = controlblock->GetManagedObject();
		assert(!refcountedobject_managed->controlblock);
		::std::call_once(
			controlblock->GetManagedObject()->onceflag_controlblock,
			[controlblock, refcountedobject_managed]() noexcept->void {
				refcountedobject_managed->controlblock = static_cast<ReferenceCountControlBlock*>(controlblock);
			}
		);
		assert(refcountedobject_managed->controlblock == static_cast<ReferenceCountControlBlock*>(controlblock));
		return ReferenceCountedObjectHolder<element_type>(controlblock->GetElement());
	}

	void YBWLIB2_CALLTYPE Common_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE Common_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_6E727F38_3A2F_43F0_88A5_4DD2F630A819
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5FFBCAEB_0B64_4B64_924A_0A630F01A923
#endif
