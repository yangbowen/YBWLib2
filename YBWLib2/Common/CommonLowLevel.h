#ifndef _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766
#define _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include "../YBWLib2Api.h"

namespace YBWLib2 {
	/// <summary>Obtains a type resulting from moving the <c>const</c> and <c>volatile</c> qualification information from another type to one type.</summary>
	template<typename _Ty, typename _Cv_Ty>
	struct move_cv_t {
		using type = typename ::std::conditional_t<::std::is_volatile_v<_Cv_Ty>, typename ::std::add_volatile_t<
			typename ::std::conditional_t<::std::is_const_v<_Cv_Ty>, typename ::std::add_const_t<_Ty>, typename ::std::remove_const_t<_Ty>>
		>, typename ::std::remove_volatile_t<
			typename ::std::conditional_t<::std::is_volatile_v<_Cv_Ty>, typename ::std::add_const_t<_Ty>, typename ::std::remove_const_t<_Ty>>
		>>;
	};

	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	// Helpers for byte_order_t.
	template<uint8_t i>
	struct byte_order_bytearray_test_helper_t {
		const byte_order_bytearray_test_helper_t<i - 1> prev;
		const uint8_t current = i;
	};
	template<>
	struct byte_order_bytearray_test_helper_t<0> {
		const uint8_t current = 0;
	};
	template<uint8_t i>
	constexpr byte_order_bytearray_test_helper_t<i> byte_order_bytearray_test_helper {};
	template<typename _Ty, uint8_t i>
	constexpr _Ty byte_order_number_test_le_helper = byte_order_number_test_le_helper<_Ty, i - 1> | (((_Ty)i) << (i * 8));
	template<typename _Ty>
	constexpr _Ty byte_order_number_test_le_helper<_Ty, 0> = 0;
	template<typename _Ty, uint8_t i>
	constexpr _Ty byte_order_number_test_be_helper = byte_order_number_test_be_helper<_Ty, i - 1> | (((_Ty)(sizeof(_Ty) - i - 1)) << (i * 8));
	template<typename _Ty>
	constexpr _Ty byte_order_number_test_be_helper<_Ty, 0> = sizeof(_Ty) - 1;

	/// <summary>Obtains byte order information about a given unsigned intergral type.</summary>
	template<typename _Ty>
	struct byte_order_t {
		static_assert(::std::is_integral_v<_Ty> && ::std::is_unsigned_v<_Ty>, "The specified type is not an unsigned integral type.");
		static constexpr _Ty number_test_le = byte_order_number_test_le_helper<_Ty, sizeof(_Ty) - 1>;
		static constexpr _Ty number_test_be = byte_order_number_test_be_helper<_Ty, sizeof(_Ty) - 1>;
		const _Ty number_test;
		const bool is_le;
		const bool is_be;
		byte_order_t()
			: number_test(*reinterpret_cast<const _Ty*>(&byte_order_bytearray_test_helper<sizeof(_Ty) - 1>)),
			is_le(number_test == number_test_le),
			is_be(number_test == number_test_be) {}
	};

	// Helpers for hash_trivially_copyable_t.
	template<typename _Ty, typename _Hash_Ty, size_t size_hash>
	struct hash_trivially_copyable_helper_t {};
	template<typename _Ty, typename _Hash_Ty>
	struct hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(uint32_t)> {
		static_assert(::std::is_trivially_copyable_v<_Ty>, "The specified type is not a trivially copyable type.");
		static_assert(::std::is_integral_v<_Hash_Ty> && ::std::is_unsigned_v<_Hash_Ty>, "The specified hash type is not an unsigned integral type.");
		static_assert(sizeof(_Hash_Ty) == sizeof(uint32_t), "The specified hash size does not equal to the size of the specified hash type.");
		inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) {
			_Hash_Ty _hash = fnv1a_offset_basis;
			for (size_t i = 0; i < sizeof(data); ++i) _hash = (_hash ^ reinterpret_cast<const uint8_t*>(&data)[i]) * fnv1a_prime;
			return _hash;
		}
	private:
		static constexpr size_t fnv1a_offset_basis = 0x811C9DC5;
		static constexpr size_t fnv1a_prime = 0x1000193;
	};
	template<typename _Ty, typename _Hash_Ty>
	struct hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(uint64_t)> {
		static_assert(::std::is_trivially_copyable_v<_Ty>, "The specified type is not a trivially copyable type.");
		static_assert(::std::is_integral_v<_Hash_Ty> && ::std::is_unsigned_v<_Hash_Ty>, "The specified hash type is not an unsigned integral type.");
		static_assert(sizeof(_Hash_Ty) == sizeof(uint64_t), "The specified hash size does not equal to the size of the specified hash type.");
		inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) {
			_Hash_Ty _hash = fnv1a_offset_basis;
			for (size_t i = 0; i < sizeof(data); ++i) _hash = (_hash ^ reinterpret_cast<const uint8_t*>(&data)[i]) * fnv1a_prime;
			return _hash;
		}
	private:
		static constexpr size_t fnv1a_offset_basis = 0xCBF29CE484222325;
		static constexpr size_t fnv1a_prime = 0x100000001B3;
	};

	/// <summary>Hashes a trivially copyable object.</summarY>
	template<typename _Ty, typename _Hash_Ty>
	struct hash_trivially_copyable_t {
		inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) { return hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(_Hash_Ty)>()(data); }
	};

	struct dummy_t {};
	extern YBWLIB2_API dummy_t dummy;

	inline constexpr bool is_hex_uint8_string(const char(&str)[3]) {
		return (str[0] >= '0' && str[0] <= '9' || str[0] >= 'A' && str[0] <= 'F' || str[0] >= 'a' && str[0] <= 'f')
			&& (str[1] >= '0' && str[1] <= '9' || str[1] >= 'A' && str[1] <= 'F' || str[1] >= 'a' && str[1] <= 'f');
	}
	inline constexpr uint8_t hex_uint8_from_string(const char(&str)[3]) {
		if (!is_hex_uint8_string(str)) abort();
		return (str[0] >= '0' && str[0] <= '9' ? str[0] - '0'
			: str[0] >= 'A' && str[0] <= 'F' ? str[0] - 'A' + 0xA
			: str[0] - 'a' + 0xA) << 0x4
			| (str[1] >= '0' && str[1] <= '9' ? str[1] - '0'
				: str[1] >= 'A' && str[1] <= 'F' ? str[1] - 'A' + 0xA
				: str[1] - 'a' + 0xA);
	}
	inline constexpr uint16_t hex_uint16_from_string(const char(&str)[5]) {
		return ((uint16_t)hex_uint8_from_string({ str[0], str[1], 0 }) << 0x8) | hex_uint8_from_string({ str[2], str[3], 0 });
	}
	inline constexpr uint32_t hex_uint32_from_string(const char(&str)[9]) {
		return ((uint32_t)hex_uint16_from_string({ str[0], str[1], str[2], str[3], 0 }) << 0x10) | hex_uint16_from_string({ str[4], str[5], str[6], str[7], 0 });
	}
	inline constexpr uint64_t hex_uint64_from_string(const char(&str)[17]) {
		return ((uint64_t)hex_uint32_from_string({ str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], 0 }) << 0x20) | hex_uint32_from_string({ str[8], str[9], str[10], str[11], str[12], str[13], str[14], str[15], 0 });
	}
}

#endif
