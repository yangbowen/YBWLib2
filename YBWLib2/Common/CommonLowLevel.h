#ifndef _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766
#define _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766

#include <cstdint>
#include <climits>
#include <cinttypes>
#include <cstdlib>
#include <cassert>
#include <type_traits>
#include <utility>
#include <tuple>
#include <new>
#include <memory>
#include <unordered_map>
#include <atomic>
#include <mutex>
#include <typeinfo>
#include "../YBWLib2Api.h"

namespace YBWLib2 {
	struct UUID;

#define YBWLIB2_STRINGIZE_HELPER(x) #x
#define YBWLIB2_STRINGIZE(x) YBWLIB2_STRINGIZE_HELPER(x)

#define YBWLIB2_CONCATENATE_HELPER(l, r) l ## r
#define YBWLIB2_CONCATENATE(l, r) YBWLIB2_CONCATENATE_HELPER(l, r)

#define YBWLIB2_TO_UTF8_HELPER(s) u8 ## s
#define YBWLIB2_TO_UTF8(s) YBWLIB2_TO_UTF8_HELPER(s)

	struct already_exclusive_locked_this_t {
		explicit constexpr already_exclusive_locked_this_t() noexcept = default;
	};
	struct already_shared_locked_this_t {
		explicit constexpr already_shared_locked_this_t() noexcept = default;
	};

	/// <summary>Obtains a type resulting from moving the <c>const</c> and <c>volatile</c> qualification information from another type to one type.</summary>
	template<typename _Ty, typename _Cv_Ty>
	struct move_cv {
		using type = typename ::std::conditional_t<::std::is_volatile_v<_Cv_Ty>, typename ::std::add_volatile_t<
			typename ::std::conditional_t<::std::is_const_v<_Cv_Ty>, typename ::std::add_const_t<_Ty>, typename ::std::remove_const_t<_Ty>>
		>, typename ::std::remove_volatile_t<
			typename ::std::conditional_t<::std::is_const_v<_Cv_Ty>, typename ::std::add_const_t<_Ty>, typename ::std::remove_const_t<_Ty>>
			>>;
	};

	/// <summary>Obtains a type resulting from moving the <c>const</c> and <c>volatile</c> qualification information from another type to one type.</summary>
	template<typename _Ty, typename _Cv_Ty>
	using move_cv_t = typename move_cv<_Ty, _Cv_Ty>::type;

	/// <summary>A helper type that encloses a value known at compile time.</summary>
	template<typename _Ty, _Ty _value>
	struct enclose_constexpr_value_t {
		using value_type = _Ty;
		static constexpr value_type value = _value;
	};

	namespace Internal {
		template<typename _Default_Ty, typename _AlwaysVoid_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
		struct detected_helper_t {
			using value_t = ::std::false_type;
			using type = _Default_Ty;
			static constexpr typename value_t::value_type value = value_t::value;
		};

		template<typename _Default_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
		struct detected_helper_t<_Default_Ty, ::std::void_t<_Template_Ty<_Args_Ty...>>, _Template_Ty, _Args_Ty...> {
			using value_t = ::std::true_type;
			using type = _Template_Ty<_Args_Ty...>;
			static constexpr typename value_t::value_type value = value_t::value;
		};
	}

	struct nonesuch final {
		nonesuch() = delete;
		nonesuch(const nonesuch&) = delete;
		nonesuch(nonesuch&&) = delete;
		~nonesuch() = delete;
		nonesuch& operator=(const nonesuch&) = delete;
		nonesuch& operator=(nonesuch&&) = delete;
	};

	/// <summary>Detects template specialization.</summary>
	template<template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using is_detected = typename Internal::detected_helper_t<nonesuch, void, _Template_Ty, _Args_Ty...>::value_t;
	/// <summary>Detects template specialization.</summary>
	template<template<typename...> typename _Template_Ty, typename... _Args_Ty>
	constexpr bool is_detected_v = is_detected<_Template_Ty, _Args_Ty...>::value;

	/// <summary>Detects template specialization.</summary>
	template<template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using detected_t = typename Internal::detected_helper_t<nonesuch, void, _Template_Ty, _Args_Ty...>::type;
	/// <summary>Detects template specialization.</summary>
	template<typename _Expected_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using is_detected_exact = ::std::is_same<detected_t<_Template_Ty, _Args_Ty...>, _Expected_Ty>;
	/// <summary>Detects template specialization.</summary>
	template<typename _Expected_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	constexpr bool is_detected_exact_v = is_detected_exact<_Expected_Ty, _Template_Ty, _Args_Ty...>::value;
	/// <summary>Detects template specialization.</summary>
	template<typename _To_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using is_detected_convertible = ::std::is_convertible<detected_t<_Template_Ty, _Args_Ty...>, _To_Ty>;
	/// <summary>Detects template specialization.</summary>
	template<typename _To_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	constexpr bool is_detected_convertible_v = is_detected_convertible<_To_Ty, _Template_Ty, _Args_Ty...>::value;

	/// <summary>Detects template specialization.</summary>
	template<typename _Default_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using detected_or = Internal::detected_helper_t<_Default_Ty, void, _Template_Ty, _Args_Ty...>;
	/// <summary>Detects template specialization.</summary>
	template<typename _Default_Ty, template<typename...> typename _Template_Ty, typename... _Args_Ty>
	using detected_or_t = typename detected_or<_Default_Ty, _Template_Ty, _Args_Ty...>::type;

	/// <summary>A helper type whose instances always compares less than the specified original type.</summary>
	template<typename _Ty>
	struct below_min_t {
		using original_type = _Ty;
		using is_always_equal = ::std::true_type;
		constexpr below_min_t() noexcept = default;
		constexpr below_min_t(const below_min_t&) noexcept = default;
		constexpr below_min_t(below_min_t&&) noexcept = default;
		~below_min_t() = default;
		constexpr below_min_t& operator=(const below_min_t&) noexcept = default;
		constexpr below_min_t& operator=(below_min_t&&) noexcept = default;
		constexpr bool operator==(const below_min_t&) const noexcept { return true; }
		constexpr bool operator!=(const below_min_t&) const noexcept { return false; }
		constexpr bool operator<(const below_min_t&) const noexcept { return false; }
		constexpr bool operator<=(const below_min_t&) const noexcept { return true; }
		constexpr bool operator>(const below_min_t&) const noexcept { return false; }
		constexpr bool operator>=(const below_min_t&) const noexcept { return true; }
		constexpr bool operator==(const original_type&) const noexcept { return false; }
		constexpr bool operator!=(const original_type&) const noexcept { return true; }
		constexpr bool operator<(const original_type&) const noexcept { return true; }
		constexpr bool operator<=(const original_type&) const noexcept { return true; }
		constexpr bool operator>(const original_type&) const noexcept { return false; }
		constexpr bool operator>=(const original_type&) const noexcept { return false; }
	};

	/// <summary>A helper type whose instances always compares greater than the specified original type.</summary>
	template<typename _Ty>
	struct above_max_t {
		using original_type = _Ty;
		using is_always_equal = ::std::true_type;
		constexpr above_max_t() noexcept = default;
		constexpr above_max_t(const above_max_t&) noexcept = default;
		constexpr above_max_t(above_max_t&&) noexcept = default;
		~above_max_t() = default;
		constexpr above_max_t& operator=(const above_max_t&) noexcept = default;
		constexpr above_max_t& operator=(above_max_t&&) noexcept = default;
		constexpr bool operator==(const above_max_t&) const noexcept { return true; }
		constexpr bool operator!=(const above_max_t&) const noexcept { return false; }
		constexpr bool operator<(const above_max_t&) const noexcept { return false; }
		constexpr bool operator<=(const above_max_t&) const noexcept { return true; }
		constexpr bool operator>(const above_max_t&) const noexcept { return false; }
		constexpr bool operator>=(const above_max_t&) const noexcept { return true; }
		constexpr bool operator==(const original_type&) const noexcept { return false; }
		constexpr bool operator!=(const original_type&) const noexcept { return true; }
		constexpr bool operator<(const original_type&) const noexcept { return false; }
		constexpr bool operator<=(const original_type&) const noexcept { return false; }
		constexpr bool operator>(const original_type&) const noexcept { return true; }
		constexpr bool operator>=(const original_type&) const noexcept { return true; }
	};

	template<typename _Ty>
	constexpr bool operator==(const _Ty&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator!=(const _Ty&, const below_min_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<(const _Ty&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator<=(const _Ty&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator>(const _Ty&, const below_min_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator>=(const _Ty&, const below_min_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator==(const _Ty&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator!=(const _Ty&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<(const _Ty&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<=(const _Ty&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator>(const _Ty&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator>=(const _Ty&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator==(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator!=(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<=(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator>(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator>=(const below_min_t<_Ty>&, const above_max_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator==(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator!=(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator<(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator<=(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return false; }
	template<typename _Ty>
	constexpr bool operator>(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return true; }
	template<typename _Ty>
	constexpr bool operator>=(const above_max_t<_Ty>&, const below_min_t<_Ty>&) noexcept { return true; }

	template<typename _Ty>
	struct hash;

	namespace Internal {
		// Helpers for byte_order_t.
		template<unsigned char i>
		struct byte_order_bytearray_test_helper_t {
			const byte_order_bytearray_test_helper_t<i - 1> prev;
			const unsigned char current = i;
		};
		template<>
		struct byte_order_bytearray_test_helper_t<0> {
			const unsigned char current = 0;
		};
		template<unsigned char i>
		constexpr byte_order_bytearray_test_helper_t<i> byte_order_bytearray_test_helper{};
		template<typename _Ty, unsigned char i>
		constexpr _Ty byte_order_number_test_le_helper = byte_order_number_test_le_helper<_Ty, i - 1> | (((_Ty)i) << (i * CHAR_BIT));
		template<typename _Ty>
		constexpr _Ty byte_order_number_test_le_helper<_Ty, 0> = 0;
		template<typename _Ty, unsigned char i>
		constexpr _Ty byte_order_number_test_be_helper = byte_order_number_test_be_helper<_Ty, i - 1> | (((_Ty)(sizeof(_Ty) - i - 1)) << (i * CHAR_BIT));
		template<typename _Ty>
		constexpr _Ty byte_order_number_test_be_helper<_Ty, 0> = sizeof(_Ty) - 1;
	}

	/// <summary>Obtains byte order information about a given unsigned intergral type.</summary>
	template<typename _Ty>
	struct byte_order_t final {
		static_assert(::std::is_integral_v<_Ty> && ::std::is_unsigned_v<_Ty>, "The specified type is not an unsigned integral type.");
		static constexpr _Ty number_test_le = Internal::byte_order_number_test_le_helper<_Ty, sizeof(_Ty) - 1>;
		static constexpr _Ty number_test_be = Internal::byte_order_number_test_be_helper<_Ty, sizeof(_Ty) - 1>;
		const _Ty number_test;
		const bool is_le;
		const bool is_be;
		byte_order_t()
			: number_test(*reinterpret_cast<const _Ty*>(&Internal::byte_order_bytearray_test_helper<sizeof(_Ty) - 1>)),
			is_le(number_test == number_test_le),
			is_be(number_test == number_test_be) {}
	};

	static_assert(::std::is_standard_layout_v<byte_order_t<unsigned char>>, "byte_order_t<unsigned char> is not standard-layout.");
	static_assert(::std::is_standard_layout_v<byte_order_t<unsigned short>>, "byte_order_t<unsigned short> is not standard-layout.");
	static_assert(::std::is_standard_layout_v<byte_order_t<unsigned int>>, "byte_order_t<unsigned int> is not standard-layout.");
	static_assert(::std::is_standard_layout_v<byte_order_t<unsigned long>>, "byte_order_t<unsigned long> is not standard-layout.");
	static_assert(::std::is_standard_layout_v<byte_order_t<unsigned long long>>, "byte_order_t<unsigned long long> is not standard-layout.");

	extern YBWLIB2_API byte_order_t<unsigned char>* byte_order_unsigned_char;
	extern YBWLIB2_API byte_order_t<unsigned short>* byte_order_unsigned_short;
	extern YBWLIB2_API byte_order_t<unsigned int>* byte_order_unsigned_int;
	extern YBWLIB2_API byte_order_t<unsigned long>* byte_order_unsigned_long;
	extern YBWLIB2_API byte_order_t<unsigned long long>* byte_order_unsigned_long_long;
	extern YBWLIB2_API bool* is_byte_order_le;
	extern YBWLIB2_API bool* is_byte_order_be;

	/// <summary>Gets the smallest power of <c>2</c> that's greater than an unsigned integral value.</summary>
	template<typename _Uint_Ty>
	inline constexpr _Uint_Ty ceil_to_power_of_two(_Uint_Ty x) noexcept {
		static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
		if ((x & (x - 1)) && (x << 1) < x) abort();
		bool should_increment_exponent = false;
		if (!x) {
			return 0;
		}
		for (; x & (x - 1); x = x & (x - 1)) should_increment_exponent = true;
		return should_increment_exponent ? x << 1 : x;
	}

	namespace Internal {
		// Helpers for count_leading_zero.
		template<typename _Uint_Ty, size_t bitsize>
		inline constexpr void count_leading_zero_helper(_Uint_Ty& x, size_t& n) {
			static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
			static_assert(!(sizeof(_Uint_Ty) & (sizeof(_Uint_Ty) - 1)), "Integral sizes not a power of 2 is not currently supported.");
			static_assert(bitsize <= sizeof(_Uint_Ty) * CHAR_BIT, "The specified bitsize is greater than the bitsize of the specified unsigned integral type.");
			if constexpr ((bitsize & (bitsize - 1)) != 0) {
				static_assert(
					!(ceil_to_power_of_two(bitsize) & (ceil_to_power_of_two(bitsize) - 1))
					&& ceil_to_power_of_two(bitsize) > bitsize
					&& ceil_to_power_of_two(bitsize) <= sizeof(_Uint_Ty) * CHAR_BIT
					, "Unexpected error."
					);
				// Shifts the bits to the left.
				x <<= ceil_to_power_of_two(bitsize) - bitsize;
				// Sets the trailing bits.
				x |= (((_Uint_Ty)1 << (ceil_to_power_of_two(bitsize) - bitsize)) - 1);
				count_leading_zero_helper<_Uint_Ty, ceil_to_power_of_two(bitsize)>(x, n);
			} else if constexpr (!bitsize) {
				return;
			} else if constexpr (bitsize == 0x1) {
				static constexpr size_t table_1[(size_t)1 << 0x1] = { 0x1, 0x0 };
				n += table_1[(x >> (sizeof(_Uint_Ty) * CHAR_BIT - 0x1))& (((size_t)1 << 0x1) - 1)];
			} else if constexpr (bitsize == 0x2) {
				static constexpr size_t table_2[(size_t)1 << 0x2] = { 0x2, 0x1, 0x0, 0x0 };
				n += table_2[(x >> (sizeof(_Uint_Ty) * CHAR_BIT - 0x2))& (((size_t)1 << 0x2) - 1)];
			} else if constexpr (bitsize == 0x4) {
				static constexpr size_t table_4[(size_t)1 << 0x4] = { 0x4, 0x3, 0x2, 0x2, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
				n += table_4[(x >> (sizeof(_Uint_Ty) * CHAR_BIT - 0x4))& (((size_t)1 << 0x4) - 1)];
			} else {
				static_assert(!(bitsize & 1), "Unexpected error.");
				if (!(x & ((((_Uint_Ty)1 << (bitsize >> 1)) - 1) << (sizeof(_Uint_Ty) * CHAR_BIT - (bitsize >> 1))))) {
					n += (bitsize >> 1);
					x <<= (bitsize >> 1);
				}
				count_leading_zero_helper<_Uint_Ty, (bitsize >> 1)>(x, n);
			}
		}
	}

	/// <summary>Count leading zeros in an unsigned integral value.</summary>
	template<typename _Uint_Ty>
	inline constexpr size_t count_leading_zero(_Uint_Ty x) {
		static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
		size_t n = 0;
		Internal::count_leading_zero_helper<_Uint_Ty, sizeof(_Uint_Ty) * CHAR_BIT>(x, n);
		return n;
	}

	namespace Internal {
		// Helpers for count_trailing_zero.
		template<typename _Uint_Ty, size_t bitsize>
		inline constexpr void count_trailing_zero_helper(_Uint_Ty& x, size_t& n) {
			static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
			static_assert(!(sizeof(_Uint_Ty) & (sizeof(_Uint_Ty) - 1)), "Integral sizes not a power of 2 is not currently supported.");
			static_assert(bitsize <= sizeof(_Uint_Ty) * CHAR_BIT, "The specified bitsize is greater than the bitsize of the specified unsigned integral type.");
			if constexpr ((bitsize & (bitsize - 1)) != 0) {
				static_assert(
					!(ceil_to_power_of_two(bitsize) & (ceil_to_power_of_two(bitsize) - 1))
					&& ceil_to_power_of_two(bitsize) > bitsize
					&& ceil_to_power_of_two(bitsize) <= sizeof(_Uint_Ty) * CHAR_BIT
					, "Unexpected error."
					);
				// Sets the leading bits.
				x |= (((_Uint_Ty)1 << (ceil_to_power_of_two(bitsize) - bitsize)) - 1) << bitsize;
				count_trailing_zero_helper<_Uint_Ty, ceil_to_power_of_two(bitsize)>(x, n);
			} else if constexpr (!bitsize) {
				return;
			} else if constexpr (bitsize == 0x1) {
				static constexpr size_t table_1[(size_t)1 << 0x1] = { 0x1, 0x0 };
				n += table_1[x & (((size_t)1 << 0x1) - 1)];
			} else if constexpr (bitsize == 0x2) {
				static constexpr size_t table_2[(size_t)1 << 0x2] = { 0x2, 0x0, 0x1, 0x0 };
				n += table_2[x & (((size_t)1 << 0x2) - 1)];
			} else if constexpr (bitsize == 0x4) {
				static constexpr size_t table_4[(size_t)1 << 0x4] = { 0x4, 0x0, 0x1, 0x0, 0x2, 0x0, 0x1, 0x0, 0x3, 0x0, 0x1, 0x0, 0x2, 0x0, 0x1, 0x0 };
				n += table_4[x & (((size_t)1 << 0x4) - 1)];
			} else {
				static_assert(!(bitsize & 1), "Unexpected error.");
				if (!(x & (((_Uint_Ty)1 << (bitsize >> 1)) - 1))) {
					n += (bitsize >> 1);
					x >>= (bitsize >> 1);
				}
				count_trailing_zero_helper<_Uint_Ty, (bitsize >> 1)>(x, n);
			}
		}
	}

	/// <summary>Count trailing zeros in an unsigned integral value.</summary>
	template<typename _Uint_Ty>
	inline constexpr size_t count_trailing_zero(_Uint_Ty x) {
		static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
		size_t n = 0;
		Internal::count_trailing_zero_helper<_Uint_Ty, sizeof(_Uint_Ty) * CHAR_BIT>(x, n);
		return n;
	}

	/// <summary>Calculates the greatest common denominator of two values.</summary>
	template<typename _Ty, typename ::std::enable_if<::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline constexpr _Ty greatest_common_denominator(_Ty a, _Ty b) {
		_Ty c(a % b);
		if (!c)
			return b;
		else
			return greatest_common_denominator<_Ty>(b, c);
	}

	/// <summary>Calculates the greatest common denominator of two values.</summary>
	template<typename _Ty, typename ::std::enable_if<!::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline constexpr _Ty greatest_common_denominator(const _Ty& a, const _Ty& b) {
		_Ty c(a % b);
		if (!c)
			return b;
		else
			return greatest_common_denominator<_Ty>(b, c);
	}

	/// <summary>Calculates the least common multiple of two values.</summary>
	template<typename _Ty, typename ::std::enable_if<::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline constexpr _Ty least_common_multiple(_Ty a, _Ty b) {
		return (a / greatest_common_denominator<_Ty>(a, b)) * b;
	}

	/// <summary>Calculates the least common multiple of two values.</summary>
	template<typename _Ty, typename ::std::enable_if<!::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline constexpr _Ty least_common_multiple(const _Ty& a, const _Ty& b) {
		return (a / greatest_common_denominator<_Ty>(a, b)) * b;
	}

	namespace Internal {
		// Helpers for get_lookup_table_least_common_multiple.
		template<typename _Ty>
		using get_lookup_table_least_common_multiple_helper_value_index_t = ::std::conditional_t < sizeof(size_t) < sizeof(_Ty), size_t, _Ty > ;

		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> value_index_base, bool is_odd_count_element>
		struct get_lookup_table_least_common_multiple_helper1_t;

		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> value_index_base>
		struct get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element, value_fixed, value_index_base, false> {
			static_assert(!(count_element % 2));
			get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element / 2, value_fixed, value_index_base, (count_element / 2) % 2> branch_0;
			get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element / 2, value_fixed, value_index_base + count_element / 2, (count_element / 2) % 2> branch_1;
		};

		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> value_index_base>
		struct get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element, value_fixed, value_index_base, true> {
			static_assert(count_element % 2);
			get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element - 1, value_fixed, value_index_base, false> truncated;
			const _Ty remainder = least_common_multiple<_Ty>(value_fixed, value_index_base + count_element);
		};

		template<typename _Ty, _Ty value_fixed, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> value_index_base>
		struct get_lookup_table_least_common_multiple_helper1_t<_Ty, static_cast<get_lookup_table_least_common_multiple_helper_value_index_t<_Ty>>(0), value_fixed, value_index_base, false>;

		template<typename _Ty, _Ty value_fixed, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> value_index_base>
		struct get_lookup_table_least_common_multiple_helper1_t<_Ty, static_cast<get_lookup_table_least_common_multiple_helper_value_index_t<_Ty>>(1), value_fixed, value_index_base, true> {
			const _Ty remainder = least_common_multiple<_Ty>(value_fixed, value_index_base + 1);
		};

		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed>
		using get_lookup_table_least_common_multiple_helper2_t = get_lookup_table_least_common_multiple_helper1_t<_Ty, count_element, value_fixed, static_cast<get_lookup_table_least_common_multiple_helper_value_index_t>(0), count_element % 2>;

		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed>
		constexpr get_lookup_table_least_common_multiple_helper2_t<_Ty, count_element, value_fixed> get_lookup_table_least_common_multiple_helper2{};

		/// <summary>
		/// Gets a reference to a lookup table of least common multiples with one fixed value.
		/// The index in the lookup table is the non-fixed value MINUS ONE.
		/// Used in alignment calculations.
		/// </summary>
		template<typename _Ty, get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element, _Ty value_fixed>
		inline const _Ty* get_lookup_table_least_common_multiple() noexcept {
			return reinterpret_cast<const _Ty*>(&get_lookup_table_least_common_multiple_helper2<_Ty, count_element, value_fixed>);
		}
	}

	/// <summary>Calculates the least common multiple of a run-time value and a compile-time-fixed value, using a lookup table to optimize for small values.</summary>
	template<typename _Ty, Internal::get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element_lookup_table, _Ty value_fixed, typename ::std::enable_if<::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline _Ty least_common_multiple_optimized1(_Ty value_runtime) {
		return value_runtime > count_element_lookup_table ? least_common_multiple<_Ty>(value_runtime, value_fixed) : Internal::get_lookup_table_least_common_multiple<_Ty, count_element_lookup_table, value_fixed>()[value_runtime - 1];
	}

	/// <summary>Calculates the least common multiple of a run-time value and a compile-time-fixed value, using a lookup table to optimize for small values.</summary>
	template<typename _Ty, Internal::get_lookup_table_least_common_multiple_helper_value_index_t<_Ty> count_element_lookup_table, _Ty value_fixed, typename ::std::enable_if<!::std::is_fundamental_v<_Ty>, int>::type = 0>
	inline _Ty least_common_multiple_optimized1(const _Ty& value_runtime) {
		return value_runtime > count_element_lookup_table ? least_common_multiple<_Ty>(value_runtime, value_fixed) : Internal::get_lookup_table_least_common_multiple<_Ty, count_element_lookup_table, value_fixed>()[value_runtime - 1];
	}

	/// <summary>Integer modulus operation optimized for alignment calculations.</summary>
	template<typename _Ty>
	inline constexpr _Ty mod_alignment(_Ty dividend, _Ty divisor) {
		static_assert(::std::is_integral_v<_Ty> && ::std::is_unsigned_v<_Ty>, "The specified type is not an unsigned integral type.");
		if (!divisor) abort();
		if (divisor & (divisor - 1))
			return dividend % divisor;
		else
			return dividend & (divisor - 1);
	}

	namespace Internal {
		// Helpers for hash_trivially_copyable_t.
		template<typename _Ty, typename _Hash_Ty, size_t size_hash>
		struct hash_trivially_copyable_helper_t {};
		template<typename _Ty, typename _Hash_Ty>
		struct hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(uint32_t)> {
			static_assert(::std::is_trivially_copyable_v<_Ty>, "The specified type is not a trivially copyable type.");
			static_assert(::std::is_integral_v<_Hash_Ty>&& ::std::is_unsigned_v<_Hash_Ty>, "The specified hash type is not an unsigned integral type.");
			static_assert(sizeof(_Hash_Ty) == sizeof(uint32_t), "The specified hash size does not equal to the size of the specified hash type.");
			inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) {
				_Hash_Ty _hash = fnv1a_offset_basis;
				for (size_t i = 0; i < sizeof(data); ++i) _hash = (_hash ^ reinterpret_cast<const unsigned char*>(&data)[i])* fnv1a_prime;
				return _hash;
			}
		private:
			static constexpr size_t fnv1a_offset_basis = 0x811C9DC5;
			static constexpr size_t fnv1a_prime = 0x1000193;
		};
		template<typename _Ty, typename _Hash_Ty>
		struct hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(uint64_t)> {
			static_assert(::std::is_trivially_copyable_v<_Ty>, "The specified type is not a trivially copyable type.");
			static_assert(::std::is_integral_v<_Hash_Ty>&& ::std::is_unsigned_v<_Hash_Ty>, "The specified hash type is not an unsigned integral type.");
			static_assert(sizeof(_Hash_Ty) == sizeof(uint64_t), "The specified hash size does not equal to the size of the specified hash type.");
			inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) {
				_Hash_Ty _hash = fnv1a_offset_basis;
				for (size_t i = 0; i < sizeof(data); ++i) _hash = (_hash ^ reinterpret_cast<const unsigned char*>(&data)[i])* fnv1a_prime;
				return _hash;
			}
		private:
			static constexpr size_t fnv1a_offset_basis = 0xCBF29CE484222325;
			static constexpr size_t fnv1a_prime = 0x100000001B3;
		};
	}

	/// <summary>Hashes a trivially copyable object.</summary>
	template<typename _Ty, typename _Hash_Ty>
	struct hash_trivially_copyable_t {
		inline _Hash_Ty operator()(typename ::std::conditional_t<::std::is_fundamental_v<_Ty>, _Ty, const _Ty&> data) { return Internal::hash_trivially_copyable_helper_t<_Ty, _Hash_Ty, sizeof(_Hash_Ty)>()(data); }
	};

	struct dummy_t {};
	static_assert(::std::is_pod_v<dummy_t>, "dummy_t is not POD.");
	extern YBWLIB2_API dummy_t dummy;

	inline constexpr bool is_hex_uint8_string(const char(&str)[3]) noexcept {
		return (str[0] >= '0' && str[0] <= '9' || str[0] >= 'A' && str[0] <= 'F' || str[0] >= 'a' && str[0] <= 'f')
			&& (str[1] >= '0' && str[1] <= '9' || str[1] >= 'A' && str[1] <= 'F' || str[1] >= 'a' && str[1] <= 'f');
	}
	inline constexpr bool is_hex_uint16_string(const char(&str)[5]) noexcept {
		return is_hex_uint8_string({ str[0], str[1], 0 }) || is_hex_uint8_string({ str[2], str[3], 0 });
	}
	inline constexpr bool is_hex_uint32_string(const char(&str)[9]) noexcept {
		return is_hex_uint16_string({ str[0], str[1], str[2], str[3], 0 }) || is_hex_uint16_string({ str[4], str[5], str[6], str[7], 0 });
	}
	inline constexpr bool is_hex_uint64_string(const char(&str)[17]) noexcept {
		return is_hex_uint32_string({ str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], 0 }) || is_hex_uint32_string({ str[8], str[9], str[10], str[11], str[12], str[13], str[14], str[15], 0 });
	}
	inline constexpr uint8_t hex_uint8_from_string(const char(&str)[3]) noexcept {
		if (!is_hex_uint8_string(str)) abort();
		return (str[0] >= '0' && str[0] <= '9' ? str[0] - '0'
			: str[0] >= 'A' && str[0] <= 'F' ? str[0] - 'A' + 0xA
			: str[0] - 'a' + 0xA) << 0x4
			| (str[1] >= '0' && str[1] <= '9' ? str[1] - '0'
				: str[1] >= 'A' && str[1] <= 'F' ? str[1] - 'A' + 0xA
				: str[1] - 'a' + 0xA);
	}
	inline constexpr uint16_t hex_uint16_from_string(const char(&str)[5]) noexcept {
		return ((uint16_t)hex_uint8_from_string({ str[0], str[1], 0 }) << 0x8) | hex_uint8_from_string({ str[2], str[3], 0 });
	}
	inline constexpr uint32_t hex_uint32_from_string(const char(&str)[9]) noexcept {
		return ((uint32_t)hex_uint16_from_string({ str[0], str[1], str[2], str[3], 0 }) << 0x10) | hex_uint16_from_string({ str[4], str[5], str[6], str[7], 0 });
	}
	inline constexpr uint64_t hex_uint64_from_string(const char(&str)[17]) noexcept {
		return ((uint64_t)hex_uint32_from_string({ str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], 0 }) << 0x20) | hex_uint32_from_string({ str[8], str[9], str[10], str[11], str[12], str[13], str[14], str[15], 0 });
	}

	template<typename _Ty>
	struct inttype_traits_t {};

#define _DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(type, prefix_fmtspec)\
	template<>\
	struct inttype_traits_t<unsigned type> {\
		static constexpr char fmtspec_printf_o[] = prefix_fmtspec "o";\
		static constexpr char fmtspec_printf_o_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "o");\
		static constexpr char fmtspec_printf_u[] = prefix_fmtspec "u";\
		static constexpr char fmtspec_printf_u_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "u");\
		static constexpr char fmtspec_printf_x[] = prefix_fmtspec "x";\
		static constexpr char fmtspec_printf_x_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "x");\
		static constexpr char fmtspec_printf_X[] = prefix_fmtspec "X";\
		static constexpr char fmtspec_printf_X_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "X");\
		static constexpr char fmtspec_printf_decimal[] = prefix_fmtspec "u";\
		static constexpr char fmtspec_printf_decimal_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "u");\
		static constexpr char fmtspec_scanf_o[] = prefix_fmtspec "o";\
		static constexpr char fmtspec_scanf_o_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "o");\
		static constexpr char fmtspec_scanf_u[] = prefix_fmtspec "u";\
		static constexpr char fmtspec_scanf_u_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "u");\
		static constexpr char fmtspec_scanf_x[] = prefix_fmtspec "x";\
		static constexpr char fmtspec_scanf_x_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "x");\
		static constexpr char fmtspec_scanf_decimal[] = prefix_fmtspec "u";\
		static constexpr char fmtspec_scanf_decimal_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "u");\
	};\
\
	template<>\
	struct inttype_traits_t<signed type> {\
		static constexpr char fmtspec_printf_d[] = prefix_fmtspec "d";\
		static constexpr char fmtspec_printf_d_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "d");\
		static constexpr char fmtspec_printf_i[] = prefix_fmtspec "i";\
		static constexpr char fmtspec_printf_i_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "i");\
		static constexpr char fmtspec_printf_decimal[] = prefix_fmtspec "d";\
		static constexpr char fmtspec_printf_decimal_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "d");\
		static constexpr char fmtspec_scanf_d[] = prefix_fmtspec "d";\
		static constexpr char fmtspec_scanf_d_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "d");\
		static constexpr char fmtspec_scanf_i[] = prefix_fmtspec "i";\
		static constexpr char fmtspec_scanf_i_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "i");\
		static constexpr char fmtspec_scanf_decimal[] = prefix_fmtspec "d";\
		static constexpr char fmtspec_scanf_decimal_utf8[] = YBWLIB2_TO_UTF8(prefix_fmtspec "d");\
	};

	_DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(char, "hh");
	_DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(short, "h");
	_DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(int, "");
	_DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(long, "l");
	_DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9(long long, "ll");

#undef _DECLARE_8F6D94DA_B6C1_4743_9EB6_134A3348BDC9

#pragma region UUID
	//{ UUID

	/// <summary>Universally unique identifier.</summary>
	struct UUID {
		/// <summary>An equal-to comparing function for <c>UUID</c>.</summary>
		static inline bool IsEqualTo(const UUID& l, const UUID& r) noexcept {
			return !memcmp(l.data, r.data, sizeof(UUID::data));
		}
		/// <summary>
		/// A less-than comparing function for <c>UUID</c>.
		/// The behaviour is equivalent to comparing the binary representation of the <c>UUID</c> from byte to byte lexicographically.
		/// </summary>
		static inline bool IsLessThan(const UUID& l, const UUID& r) noexcept {
			for (int i = 0; i < sizeof(UUID::data); ++i) {
				if (reinterpret_cast<const unsigned char*>(l.data)[i] < reinterpret_cast<const unsigned char*>(r.data)[i]) return true;
				if (reinterpret_cast<const unsigned char*>(l.data)[i] != reinterpret_cast<const unsigned char*>(r.data)[i]) return false;
			}
			return false;
		}
		/// <summary>A secure version of <c>IsEqualTo</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
		static inline bool SecureIsEqualTo(const UUID& l, const UUID& r) noexcept {
			if constexpr (sizeof(UUID::data) % sizeof(uintptr_t)) {
				uint8_t x = 0;
				for (size_t i = 0; i < sizeof(UUID::data) / sizeof(uint8_t); ++i) x |= l.data[i] ^ r.data[i];
				return !x;
			} else {
				uintptr_t x = 0;
				for (size_t i = 0; i < sizeof(UUID::data) / sizeof(uintptr_t); ++i) x |= reinterpret_cast<const uintptr_t*>(l.data)[i] ^ reinterpret_cast<const uintptr_t*>(r.data)[i];
				return !x;
			}
		}
		uint8_t data[0x10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		constexpr UUID() noexcept = default;
		constexpr UUID(const UUID& x) noexcept = default;
		constexpr UUID(UUID&& x) noexcept = default;
		~UUID() = default;
		UUID& operator=(const UUID& x) noexcept = default;
		UUID& operator=(UUID&& x) noexcept = default;
		inline bool operator==(const UUID& r) const { return UUID::IsEqualTo(*this, r); }
		inline bool operator!=(const UUID& r) const { return !UUID::IsEqualTo(*this, r); }
		inline bool operator<(const UUID& r) const { return UUID::IsLessThan(*this, r); }
		inline bool operator<=(const UUID& r) const { return !UUID::IsLessThan(r, *this); }
		inline bool operator>(const UUID& r) const { return UUID::IsLessThan(r, *this); }
		inline bool operator>=(const UUID& r) const { return !UUID::IsLessThan(*this, r); }
		inline size_t hash() const { return hash_trivially_copyable_t<UUID, size_t>()(*this); }
	};
	static_assert(::std::is_standard_layout_v<UUID>, "UUID is not standard-layout.");

	template<>
	struct hash<UUID> {
		inline size_t operator()(const UUID& x) const {
			return x.hash();
		}
	};
	/// <summary>Converts a UUID string in the format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX to a <c>UUID</c> identifier at compile time.</summary>
	inline constexpr UUID UUIDFromUUIDString_CompileTime(const char(&str)[37]) noexcept {
		if (str[8] != '-'
			|| str[13] != '-'
			|| str[18] != '-'
			|| str[23] != '-'
			|| str[36]) abort();
		return UUID {
			hex_uint8_from_string({ str[0], str[1], 0 }), hex_uint8_from_string({ str[2], str[3], 0 }), hex_uint8_from_string({ str[4], str[5], 0 }), hex_uint8_from_string({ str[6], str[7], 0 }),
			hex_uint8_from_string({ str[9], str[10], 0 }), hex_uint8_from_string({ str[11], str[12], 0 }), hex_uint8_from_string({ str[14], str[15], 0 }), hex_uint8_from_string({ str[16], str[17], 0 }),
			hex_uint8_from_string({ str[19], str[20], 0 }), hex_uint8_from_string({ str[21], str[22], 0 }), hex_uint8_from_string({ str[24], str[25], 0 }), hex_uint8_from_string({ str[26], str[27], 0 }),
			hex_uint8_from_string({ str[28], str[29], 0 }), hex_uint8_from_string({ str[30], str[31], 0 }), hex_uint8_from_string({ str[32], str[33], 0 }), hex_uint8_from_string({ str[34], str[35], 0 })
		};
	}
	/// <summary>Converts a UUID string in the format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX to a <c>UUID</c> identifier at run time.</summary>
	inline UUID UUIDFromUUIDString_RunTime(const char* str, size_t size_str, bool& is_successful) noexcept {
		is_successful = false;
		if (
			!str
			|| size_str != 36
			|| str[8] != '-'
			|| str[13] != '-'
			|| str[18] != '-'
			|| str[23] != '-'
			|| !is_hex_uint8_string({ str[0], str[1], 0 }) || !is_hex_uint8_string({ str[2], str[3], 0 }) || !is_hex_uint8_string({ str[4], str[5], 0 }) || !is_hex_uint8_string({ str[6], str[7], 0 })
			|| !is_hex_uint8_string({ str[9], str[10], 0 }) || !is_hex_uint8_string({ str[11], str[12], 0 }) || !is_hex_uint8_string({ str[14], str[15], 0 }) || !is_hex_uint8_string({ str[16], str[17], 0 })
			|| !is_hex_uint8_string({ str[19], str[20], 0 }) || !is_hex_uint8_string({ str[21], str[22], 0 }) || !is_hex_uint8_string({ str[24], str[25], 0 }) || !is_hex_uint8_string({ str[26], str[27], 0 })
			|| !is_hex_uint8_string({ str[28], str[29], 0 }) || !is_hex_uint8_string({ str[30], str[31], 0 }) || !is_hex_uint8_string({ str[32], str[33], 0 }) || !is_hex_uint8_string({ str[34], str[35], 0 })
			) return UUID();
		is_successful = true;
		return UUID {
			hex_uint8_from_string({ str[0], str[1], 0 }), hex_uint8_from_string({ str[2], str[3], 0 }), hex_uint8_from_string({ str[4], str[5], 0 }), hex_uint8_from_string({ str[6], str[7], 0 }),
			hex_uint8_from_string({ str[9], str[10], 0 }), hex_uint8_from_string({ str[11], str[12], 0 }), hex_uint8_from_string({ str[14], str[15], 0 }), hex_uint8_from_string({ str[16], str[17], 0 }),
			hex_uint8_from_string({ str[19], str[20], 0 }), hex_uint8_from_string({ str[21], str[22], 0 }), hex_uint8_from_string({ str[24], str[25], 0 }), hex_uint8_from_string({ str[26], str[27], 0 }),
			hex_uint8_from_string({ str[28], str[29], 0 }), hex_uint8_from_string({ str[30], str[31], 0 }), hex_uint8_from_string({ str[32], str[33], 0 }), hex_uint8_from_string({ str[34], str[35], 0 })
		};
	}

	//}
#pragma endregion Universally unique identifier.

	struct PersistentID;
	class VolatileIDAnchor;
	struct VolatileID;

	struct PersistentID {
		UUID uuid;
		constexpr PersistentID() noexcept = default;
		explicit constexpr PersistentID(const UUID& _uuid) noexcept : uuid(_uuid) {}
		explicit constexpr PersistentID(UUID&& _uuid) noexcept : uuid(_uuid) {}
		constexpr PersistentID(const PersistentID& x) noexcept = default;
		constexpr PersistentID(PersistentID&& x) noexcept = default;
		~PersistentID() = default;
		PersistentID& operator=(const PersistentID& x) noexcept = default;
		PersistentID& operator=(PersistentID&& x) noexcept = default;
		bool operator==(const PersistentID& r) const { return this->uuid == r.uuid; }
		bool operator!=(const PersistentID& r) const { return this->uuid != r.uuid; }
		bool operator<(const PersistentID& r) const { return this->uuid < r.uuid; }
		bool operator<=(const PersistentID& r) const { return this->uuid <= r.uuid; }
		bool operator>(const PersistentID& r) const { return this->uuid > r.uuid; }
		bool operator>=(const PersistentID& r) const { return this->uuid >= r.uuid; }
		size_t hash() const { return this->uuid.hash(); }
	};
	static_assert(::std::is_standard_layout_v<PersistentID>, "PersistentID is not standard-layout.");

	template<>
	struct hash<PersistentID> {
		inline size_t operator()(const PersistentID& x) const {
			return x.hash();
		}
	};

	class VolatileIDAnchor final {
		friend struct VolatileID;
		friend void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept;
		friend void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept;
	public:
		VolatileIDAnchor(const VolatileIDAnchor&) = delete;
		VolatileIDAnchor(VolatileIDAnchor&&) = delete;
		~VolatileIDAnchor() {
			assert(!this->refcount.load(::std::memory_order_acquire));
		}
		VolatileIDAnchor& operator=(const VolatileIDAnchor&) = delete;
		VolatileIDAnchor& operator=(VolatileIDAnchor&&) = delete;
		YBWLIB2_API const PersistentID& GetPersistentID() const noexcept;
	protected:
		static YBWLIB2_API ::std::mutex* mtx_map_volatileidanchor;
		static YBWLIB2_API ::std::unordered_map<PersistentID, ::std::unique_ptr<VolatileIDAnchor>, hash<PersistentID>>* map_volatileidanchor;
		static YBWLIB2_API VolatileIDAnchor* ReferenceVolatileIDAnchorFromPersistentID(const PersistentID* _persistentid) noexcept;
		YBWLIB2_API void IncrementReferenceCount() const noexcept;
		YBWLIB2_API void DecrementReferenceCount() const noexcept;
	private:
		mutable ::std::atomic<uintptr_t> refcount = 1;
		const PersistentID persistentid;
		explicit VolatileIDAnchor(const PersistentID& _persistentid) noexcept : persistentid(_persistentid) {}
	};

	struct VolatileID {
	public:
		constexpr VolatileID() noexcept = default;
		explicit VolatileID(const PersistentID& _persistentid) noexcept : VolatileID() {
			this->ptr_volatileidanchor = VolatileIDAnchor::ReferenceVolatileIDAnchorFromPersistentID(&_persistentid);
		}
		VolatileID(const VolatileID& x) noexcept {
			this->ptr_volatileidanchor = x.ptr_volatileidanchor;
			if (this->ptr_volatileidanchor)
				this->ptr_volatileidanchor->IncrementReferenceCount();
		}
		VolatileID(VolatileID&& x) noexcept {
			this->ptr_volatileidanchor = ::std::move(x.ptr_volatileidanchor);
			x.ptr_volatileidanchor = nullptr;
		}
		~VolatileID() {
			if (this->ptr_volatileidanchor)
				this->ptr_volatileidanchor->DecrementReferenceCount();
			this->ptr_volatileidanchor = nullptr;
		}
		VolatileID& operator=(const VolatileID& x) noexcept {
			if (this->ptr_volatileidanchor)
				this->ptr_volatileidanchor->DecrementReferenceCount();
			this->ptr_volatileidanchor = x.ptr_volatileidanchor;
			if (this->ptr_volatileidanchor)
				this->ptr_volatileidanchor->IncrementReferenceCount();
			return *this;
		}
		VolatileID& operator=(VolatileID&& x) noexcept {
			if (this->ptr_volatileidanchor)
				this->ptr_volatileidanchor->DecrementReferenceCount();
			this->ptr_volatileidanchor = ::std::move(x.ptr_volatileidanchor);
			x.ptr_volatileidanchor = nullptr;
			return *this;
		}
		bool operator==(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor == r.ptr_volatileidanchor; }
		bool operator!=(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor != r.ptr_volatileidanchor; }
		bool operator<(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor < r.ptr_volatileidanchor; }
		bool operator<=(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor <= r.ptr_volatileidanchor; }
		bool operator>(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor > r.ptr_volatileidanchor; }
		bool operator>=(const VolatileID& r) const noexcept { return this->ptr_volatileidanchor >= r.ptr_volatileidanchor; }
		explicit operator bool() const noexcept { return this->ptr_volatileidanchor; }
		explicit operator PersistentID() const noexcept { return this->GetPersistentID(); }
		size_t hash() const noexcept { return hash_trivially_copyable_t<const VolatileIDAnchor*, size_t>()(this->ptr_volatileidanchor); }
		const VolatileIDAnchor& GetVolatileIDAnchor() const noexcept {
			assert(this->ptr_volatileidanchor);
			return *this->ptr_volatileidanchor;
		}
		const PersistentID& GetPersistentID() const noexcept {
			return this->ptr_volatileidanchor ? this->ptr_volatileidanchor->GetPersistentID() : PersistentID();
		}
	protected:
		const VolatileIDAnchor* ptr_volatileidanchor = nullptr;
	};
	static_assert(::std::is_standard_layout_v<VolatileID>, "VolatileID is not standard-layout.");
	static_assert(sizeof(VolatileID) == sizeof(void*), "The size of VolatileID doesn't match the pointer size.");

	inline bool operator==(const VolatileID& l, const PersistentID& r) noexcept { return static_cast<PersistentID>(l) == r; }
	inline bool operator==(const PersistentID& l, const VolatileID& r) noexcept { return l == static_cast<PersistentID>(r); }

	inline bool operator!=(const VolatileID& l, const PersistentID& r) noexcept { return static_cast<PersistentID>(l) != r; }
	inline bool operator!=(const PersistentID& l, const VolatileID& r) noexcept { return l != static_cast<PersistentID>(r); }

	template<>
	struct hash<VolatileID> {
		inline size_t operator()(const VolatileID& x) const {
			return x.hash();
		}
	};

	/// <summary>An allocator for allocating raw memory.</summary>
	struct rawallocator_t final {
		/// <summary>Function pointer type for cleaning up the allocator.</summary>
		/// <param name="rawallocator_from">Pointer to the <c>rawallocator_t</c> object.</param>
		typedef void (YBWLIB2_CALLTYPE* fnptr_cleanup_rawallocator_t)(rawallocator_t* rawallocator) noexcept;
		/// <summary>Function pointer type for copying the allocator.</summary>
		/// <param name="rawallocator_to">Pointer to the <c>rawallocator_t</c> object to be copied to.</param>
		/// <param name="rawallocator_from">Pointer to the <c>rawallocator_t</c> object to be copied from.</param>
		typedef void (YBWLIB2_CALLTYPE* fnptr_copy_rawallocator_t)(rawallocator_t* rawallocator_to, const rawallocator_t* rawallocator_from) noexcept;
		/// <summary>
		/// Function pointer type for comparing equality of allocators.
		/// <c>rawallocator_t</c> objects with different <c>fnptr_is_equal_rawallocator</c> function pointers never compare equal.
		/// </summary>
		/// <param name="rawallocator_l">Pointer to the <c>rawallocator_t</c> object on the left side of the comparison operator.</param>
		/// <param name="rawallocator_r">Pointer to the <c>rawallocator_t</c> object on the right side of the comparison operator.</param>
		/// <returns>Whether the two allocators compare equal (which means that memory allocated using one can be deallocated using the other).</returns>
		typedef bool (YBWLIB2_CALLTYPE* fnptr_is_equal_rawallocator_t)(const rawallocator_t* rawallocator_l, const rawallocator_t* rawallocator_r) noexcept;
		/// <summary>Function pointer type for allocating raw memory.</summary>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <param name="align">The alignment, in bytes, of the memory.</param>
		/// <param name="context">A context value associated to the <c>rawallocator_t</c> object.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the allocated memory is returned.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		typedef void* (YBWLIB2_CALLTYPE* fnptr_allocate_t)(size_t size, size_t align, uintptr_t context) noexcept;
		/// <summary>Function pointer type for deallocating raw memory.</summary>
		/// <param name="ptr">
		/// A pointer to some memory previously allocated with the same <c>rawallocator_t</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function succeeds without doing anything.
		/// </param>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <param name="context">A context value associated to the <c>rawallocator_t</c> object.</param>
		typedef void (YBWLIB2_CALLTYPE* fnptr_deallocate_t)(void* ptr, size_t size, uintptr_t context) noexcept;
		/// <summary>Function pointer type for reallocating some memory to change its size.</summary>
		/// <param name="ptr_old">
		/// An optional pointer to some memory previously allocated with the same <c>rawallocator_t</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function allocates some memory, just like when <c>Allocate</c> is called on the same object.
		/// If this pointer is not empty, the data in the memory up to the lesser of <c>size_old</c> and <c>size_new</c> is preserved.
		/// If the call fails, this pointer is still valid and so is the data in the memory pointed to by it.
		/// </param>
		/// <param name="size_old">The size, in bytes, of the memory previously allocated.</param>
		/// <param name="size_new">The new size, in bytes, of the memory to be reallocated.</param>
		/// <param name="align">The alignment, in bytes, of the memory.</param>
		/// <param name="context">A context value associated to the <c>rawallocator_t</c> object.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the reallocated memory is returned, which may or may not be the same as the original pointer passed as <c>ptr_old</c>.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		typedef void* (YBWLIB2_CALLTYPE* fnptr_reallocate_t)(void* ptr_old, size_t size_old, size_t size_new, size_t align, uintptr_t context) noexcept;
		/// <summary>Function pointer type for getting the maximum amount of memory that could potentially be allocated with this raw memory allocator.</summary>
		/// <returns>
		/// The maximum amount of memory that could potentially be allocated with this raw memory allocator.
		/// Memory allocations within this limit can still fail.
		/// </returns>
		typedef size_t(YBWLIB2_CALLTYPE* fnptr_get_max_size_t)(uintptr_t context) noexcept;
		fnptr_cleanup_rawallocator_t fnptr_cleanup_rawallocator = nullptr;
		fnptr_copy_rawallocator_t fnptr_copy_rawallocator = nullptr;
		fnptr_is_equal_rawallocator_t fnptr_is_equal_rawallocator = nullptr;
		fnptr_allocate_t fnptr_allocate = nullptr;
		fnptr_deallocate_t fnptr_deallocate = nullptr;
		fnptr_reallocate_t fnptr_reallocate = nullptr;
		fnptr_get_max_size_t fnptr_get_max_size = nullptr;
		uintptr_t context = 0;
		inline constexpr rawallocator_t(
			fnptr_cleanup_rawallocator_t _fnptr_cleanup_rawallocator,
			fnptr_copy_rawallocator_t _fnptr_copy_rawallocator,
			fnptr_is_equal_rawallocator_t _fnptr_is_equal_rawallocator,
			fnptr_allocate_t _fnptr_allocate,
			fnptr_deallocate_t _fnptr_deallocate,
			fnptr_reallocate_t _fnptr_reallocate,
			fnptr_get_max_size_t _fnptr_get_max_size,
			uintptr_t _context = 0
		) noexcept
			: fnptr_cleanup_rawallocator(_fnptr_cleanup_rawallocator),
			fnptr_copy_rawallocator(_fnptr_copy_rawallocator),
			fnptr_is_equal_rawallocator(_fnptr_is_equal_rawallocator),
			fnptr_allocate(_fnptr_allocate),
			fnptr_deallocate(_fnptr_deallocate),
			fnptr_reallocate(_fnptr_reallocate),
			fnptr_get_max_size(_fnptr_get_max_size),
			context(_context) {}
		inline rawallocator_t(const rawallocator_t& x) noexcept {
			if (x.fnptr_copy_rawallocator) {
				(*x.fnptr_copy_rawallocator)(this, &x);
			} else {
				this->fnptr_cleanup_rawallocator = x.fnptr_cleanup_rawallocator;
				this->fnptr_copy_rawallocator = x.fnptr_copy_rawallocator;
				this->fnptr_is_equal_rawallocator = x.fnptr_is_equal_rawallocator;
				this->fnptr_allocate = x.fnptr_allocate;
				this->fnptr_deallocate = x.fnptr_deallocate;
				this->fnptr_reallocate = x.fnptr_reallocate;
				this->fnptr_get_max_size = x.fnptr_get_max_size;
				this->context = x.context;
			}
		}
		inline rawallocator_t(rawallocator_t&& x) noexcept {
			this->fnptr_cleanup_rawallocator = ::std::move(x.fnptr_cleanup_rawallocator);
			x.fnptr_cleanup_rawallocator = nullptr;
			this->fnptr_copy_rawallocator = ::std::move(x.fnptr_copy_rawallocator);
			x.fnptr_copy_rawallocator = nullptr;
			this->fnptr_is_equal_rawallocator = ::std::move(x.fnptr_is_equal_rawallocator);
			x.fnptr_is_equal_rawallocator = nullptr;
			this->fnptr_allocate = ::std::move(x.fnptr_allocate);
			x.fnptr_allocate = nullptr;
			this->fnptr_deallocate = ::std::move(x.fnptr_deallocate);
			x.fnptr_deallocate = nullptr;
			this->fnptr_reallocate = ::std::move(x.fnptr_reallocate);
			x.fnptr_reallocate = nullptr;
			this->fnptr_get_max_size = ::std::move(x.fnptr_get_max_size);
			x.fnptr_get_max_size = nullptr;
			this->context = ::std::move(x.context);
			x.context = 0;
		}
		inline ~rawallocator_t() noexcept {
			if (this->fnptr_cleanup_rawallocator) (*this->fnptr_cleanup_rawallocator)(this);
			this->fnptr_cleanup_rawallocator = nullptr;
			this->fnptr_copy_rawallocator = nullptr;
			this->fnptr_is_equal_rawallocator = nullptr;
			this->fnptr_allocate = nullptr;
			this->fnptr_deallocate = nullptr;
			this->fnptr_reallocate = nullptr;
			this->fnptr_get_max_size = nullptr;
			this->context = 0;
		}
		inline rawallocator_t& operator=(const rawallocator_t& x) noexcept {
			if (this->fnptr_cleanup_rawallocator) (*this->fnptr_cleanup_rawallocator)(this);
			this->fnptr_cleanup_rawallocator = nullptr;
			this->fnptr_copy_rawallocator = nullptr;
			this->fnptr_is_equal_rawallocator = nullptr;
			this->fnptr_allocate = nullptr;
			this->fnptr_deallocate = nullptr;
			this->fnptr_reallocate = nullptr;
			this->fnptr_get_max_size = nullptr;
			this->context = 0;
			if (x.fnptr_copy_rawallocator) {
				(*x.fnptr_copy_rawallocator)(this, &x);
			} else {
				this->fnptr_cleanup_rawallocator = x.fnptr_cleanup_rawallocator;
				this->fnptr_copy_rawallocator = x.fnptr_copy_rawallocator;
				this->fnptr_is_equal_rawallocator = x.fnptr_is_equal_rawallocator;
				this->fnptr_allocate = x.fnptr_allocate;
				this->fnptr_deallocate = x.fnptr_deallocate;
				this->fnptr_reallocate = x.fnptr_reallocate;
				this->fnptr_get_max_size = x.fnptr_get_max_size;
				this->context = x.context;
			}
			return *this;
		}
		inline rawallocator_t& operator=(rawallocator_t&& x) noexcept {
			if (this->fnptr_cleanup_rawallocator) (*this->fnptr_cleanup_rawallocator)(this);
			this->fnptr_cleanup_rawallocator = nullptr;
			this->fnptr_copy_rawallocator = nullptr;
			this->fnptr_is_equal_rawallocator = nullptr;
			this->fnptr_allocate = nullptr;
			this->fnptr_deallocate = nullptr;
			this->fnptr_reallocate = nullptr;
			this->fnptr_get_max_size = nullptr;
			this->context = 0;
			this->fnptr_cleanup_rawallocator = ::std::move(x.fnptr_cleanup_rawallocator);
			x.fnptr_cleanup_rawallocator = nullptr;
			this->fnptr_copy_rawallocator = ::std::move(x.fnptr_copy_rawallocator);
			x.fnptr_copy_rawallocator = nullptr;
			this->fnptr_is_equal_rawallocator = ::std::move(x.fnptr_is_equal_rawallocator);
			x.fnptr_is_equal_rawallocator = nullptr;
			this->fnptr_allocate = ::std::move(x.fnptr_allocate);
			x.fnptr_allocate = nullptr;
			this->fnptr_deallocate = ::std::move(x.fnptr_deallocate);
			x.fnptr_deallocate = nullptr;
			this->fnptr_reallocate = ::std::move(x.fnptr_reallocate);
			x.fnptr_reallocate = nullptr;
			this->fnptr_get_max_size = ::std::move(x.fnptr_get_max_size);
			x.fnptr_get_max_size = nullptr;
			this->context = ::std::move(x.context);
			x.context = 0;
			return *this;
		}
		inline bool operator==(const rawallocator_t& x) const noexcept {
			if (this->fnptr_is_equal_rawallocator != x.fnptr_is_equal_rawallocator) return false;
			if (this->fnptr_is_equal_rawallocator) {
				return (*this->fnptr_is_equal_rawallocator)(this, &x);
			} else {
				return
					this->fnptr_cleanup_rawallocator == x.fnptr_cleanup_rawallocator
					&& this->fnptr_copy_rawallocator == x.fnptr_copy_rawallocator
					&& this->fnptr_is_equal_rawallocator == x.fnptr_is_equal_rawallocator
					&& this->fnptr_allocate == x.fnptr_allocate
					&& this->fnptr_deallocate == x.fnptr_deallocate
					&& this->fnptr_reallocate == x.fnptr_reallocate
					&& this->fnptr_get_max_size == x.fnptr_get_max_size
					&& this->context == x.context;
			}
		}
		inline bool operator!=(const rawallocator_t& x) const noexcept {
			if (this->fnptr_is_equal_rawallocator != x.fnptr_is_equal_rawallocator) return true;
			if (this->fnptr_is_equal_rawallocator) {
				return !(*this->fnptr_is_equal_rawallocator)(this, &x);
			} else {
				return
					this->fnptr_cleanup_rawallocator != x.fnptr_cleanup_rawallocator
					|| this->fnptr_copy_rawallocator != x.fnptr_copy_rawallocator
					|| this->fnptr_is_equal_rawallocator != x.fnptr_is_equal_rawallocator
					|| this->fnptr_allocate != x.fnptr_allocate
					|| this->fnptr_deallocate != x.fnptr_deallocate
					|| this->fnptr_reallocate != x.fnptr_reallocate
					|| this->fnptr_get_max_size != x.fnptr_get_max_size
					|| this->context != x.context;
			}
		}
		/// <summary>Allocates some memory.</summary>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <param name="align">The alignment, in bytes, of the memory.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the allocated memory is returned.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		[[nodiscard]] inline void* Allocate(size_t size, size_t align) const noexcept { return this->fnptr_allocate ? (*this->fnptr_allocate)(size, align, this->context) : nullptr; }
		/// <summary>Deallocates some memory.</summary>
		/// <param name="ptr">
		/// A pointer to some memory previously allocated with the same <c>rawallocator_t</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function succeeds without doing anything.
		/// </param>
		/// <param name="size">The size, in bytes, of the memory.</param>
		inline void Deallocate(void* ptr, size_t size) const noexcept {
			if (!this->fnptr_deallocate) abort();
			(*this->fnptr_deallocate)(ptr, size, this->context);
		}
		/// <summary>Reallocates some memory to change its size.</summary>
		/// <param name="ptr_old">
		/// An optional pointer to some memory previously allocated with the same <c>rawallocator_t</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function allocates some memory, just like when <c>Allocate</c> is called on the same object.
		/// If this pointer is not empty, the data in the memory up to the lesser of <c>size_old</c> and <c>size_new</c> is preserved.
		/// If the call fails, this pointer is still valid and so is the data in the memory pointed to with it.
		/// </param>
		/// <param name="size_old">The size, in bytes, of the memory previously allocated.</param>
		/// <param name="size_new">The new size, in bytes, of the memory to be reallocated.</param>
		/// <param name="align">The alignment, in bytes, of the memory.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the reallocated memory is returned, which may or may not be the same as the original pointer passed as <c>ptr_old</c>.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		[[nodiscard]] inline void* Reallocate(void* ptr_old, size_t size_old, size_t size_new, size_t align) const noexcept {
			if (this->fnptr_reallocate) {
				return (*this->fnptr_reallocate)(ptr_old, size_old, size_new, align, this->context);
			} else {
				void* ptr_new = this->Allocate(size_new, align);
				if (!ptr_new) {
					this->Deallocate(ptr_old, size_old);
					return nullptr;
				} else {
					if (ptr_old) memcpy(ptr_new, ptr_old, size_new < size_old ? size_new : size_old);
					this->Deallocate(ptr_old, size_old);
					return ptr_new;
				}
			}
		}
		/// <summary>Gets the maximum amount of memory that could potentially be allocated with this raw memory allocator.</summary>
		/// <returns>
		/// The maximum amount of memory that could potentially be allocated with this raw memory allocator.
		/// Memory allocations within this limit can still fail.
		/// </returns>
		inline size_t GetMaxSize() const noexcept { return this->fnptr_get_max_size ? (*this->fnptr_get_max_size)(this->context) : 0; }
	};
	static_assert(::std::is_standard_layout_v<rawallocator_t>, "rawallocator_t is not standard-layout.");

	/// <summary>Allocator template structure for allocating memory using a <c>rawallocator_t</c> object.</summary>
	template<typename _Ty>
	struct allocator_rawallocator_t {
		typedef _Ty value_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty& reference;
		typedef const _Ty& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_rawallocator_t<_Rebind_Ty>;
		};
		using propagate_on_container_copy_assignment = ::std::true_type;
		using propagate_on_container_move_assignment = ::std::true_type;
		using propagate_on_container_swap = ::std::true_type;
		using is_always_equal = ::std::false_type;
		rawallocator_t rawallocator;
		inline allocator_rawallocator_t(const rawallocator_t& _rawallocator) noexcept : rawallocator(_rawallocator) {}
		inline allocator_rawallocator_t(rawallocator_t&& _rawallocator) noexcept : rawallocator(::std::move(_rawallocator)) {}
		inline allocator_rawallocator_t(const allocator_rawallocator_t& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		inline allocator_rawallocator_t(allocator_rawallocator_t&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t& operator=(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept {
			this->rawallocator = x.rawallocator;
			return *this;
		}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t& operator=(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept {
			this->rawallocator = x.rawallocator;
			return *this;
		}
		template<typename _Rebind_Ty>
		inline constexpr operator allocator_rawallocator_t<_Rebind_Ty>() const noexcept { return allocator_rawallocator_t<_Rebind_Ty>(this->rawallocator); }
		template<typename _Allocator_Ty>
		inline constexpr bool operator==(const _Allocator_Ty&) const noexcept { return false; }
		template<typename _Element_Ty>
		inline bool operator==(const allocator_rawallocator_t<_Element_Ty>& r) const noexcept { return this->rawallocator == r.rawallocator; }
		template<typename _Allocator_Ty>
		inline constexpr bool operator!=(const _Allocator_Ty&) const noexcept { return true; }
		template<typename _Element_Ty>
		inline bool operator!=(const allocator_rawallocator_t<_Element_Ty>& r) const noexcept { return this->rawallocator != r.rawallocator; }
		inline pointer address(reference ref) const noexcept { return ::std::addressof(ref); }
		inline const_pointer address(const_reference ref) const noexcept { return ::std::addressof(ref); }
		inline pointer allocate(size_type count, const void* hint = nullptr) const noexcept(false) {
			static_cast<void>(hint);
			pointer ptr = reinterpret_cast<pointer>(this->rawallocator.Allocate(count * sizeof(value_type), alignof(value_type)));
			if (!ptr) throw(::std::bad_alloc());
			return reinterpret_cast<pointer>(ptr);
		}
		inline void deallocate(pointer ptr, size_type count) const noexcept {
			static_cast<void>(count);
			this->rawallocator.Deallocate(ptr, count * sizeof(value_type));
		}
		inline size_type max_size() const noexcept { return this->rawallocator.GetMaxSize(); }
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline allocator_rawallocator_t select_on_container_copy_construction() const noexcept { return allocator_rawallocator_t(*this); }
	};
	/// <summary>Allocator template structure for allocating memory using a <c>rawallocator_t</c> object.</summary>
	template<>
	struct allocator_rawallocator_t<void> {
		typedef void value_type;
		typedef void* pointer;
		typedef const void* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename _Rebind_Ty>
		struct rebind {
			using other = allocator_rawallocator_t<_Rebind_Ty>;
		};
		using propagate_on_container_copy_assignment = ::std::true_type;
		using propagate_on_container_move_assignment = ::std::true_type;
		using propagate_on_container_swap = ::std::true_type;
		using is_always_equal = ::std::false_type;
		rawallocator_t rawallocator;
		inline allocator_rawallocator_t(const rawallocator_t& _rawallocator) noexcept : rawallocator(_rawallocator) {}
		inline allocator_rawallocator_t(rawallocator_t&& _rawallocator) noexcept : rawallocator(::std::move(_rawallocator)) {}
		inline allocator_rawallocator_t(const allocator_rawallocator_t& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		inline allocator_rawallocator_t(allocator_rawallocator_t&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t& operator=(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept {
			this->rawallocator = x.rawallocator;
			return *this;
		}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t& operator=(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept {
			this->rawallocator = x.rawallocator;
			return *this;
		}
		template<typename _Rebind_Ty>
		inline constexpr operator allocator_rawallocator_t<_Rebind_Ty>() const noexcept { return allocator_rawallocator_t<_Rebind_Ty>(this->rawallocator); }
		template<typename _Allocator_Ty>
		inline constexpr bool operator==(const _Allocator_Ty&) const noexcept { return false; }
		template<typename _Element_Ty>
		inline bool operator==(const allocator_rawallocator_t<_Element_Ty>& r) const noexcept { return this->rawallocator == r.rawallocator; }
		template<typename _Allocator_Ty>
		inline constexpr bool operator!=(const _Allocator_Ty&) const noexcept { return true; }
		template<typename _Element_Ty>
		inline bool operator!=(const allocator_rawallocator_t<_Element_Ty>& r) const noexcept { return this->rawallocator != r.rawallocator; }
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline allocator_rawallocator_t select_on_container_copy_construction() const noexcept { return allocator_rawallocator_t(*this); }
	};

	/// <summary>A raw memory allocator that uses the CRT <c>malloc</c> and <c>free</c> functions provided by the CRT of the executable module that contains this reference to this variable.</summary>
	extern rawallocator_t* rawallocator_crt_module_local;
	/// <summary>A raw memory allocator that uses the CRT <c>malloc</c> and <c>free</c> functions provided by the CRT of YBWLib2.</summary>
	extern YBWLIB2_API rawallocator_t* rawallocator_crt_YBWLib2;

	template<const rawallocator_t* const * _Ptr_Ptr_RawAllocator>
	class RawAllocatorAllocatedClass {
	public:
		static_assert(_Ptr_Ptr_RawAllocator);
		[[nodiscard]] static inline void* operator new(size_t _size) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			return rawallocator->Allocate(_size, __STDCPP_DEFAULT_NEW_ALIGNMENT__);
		}
		[[nodiscard]] static inline void* operator new[](size_t _size) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			return rawallocator->Allocate(_size, __STDCPP_DEFAULT_NEW_ALIGNMENT__);
		}
		[[nodiscard]] static inline void* operator new(size_t _size, ::std::align_val_t _align_val) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			return rawallocator->Allocate(_size, _align_val);
		}
		[[nodiscard]] static inline void* operator new[](size_t _size, ::std::align_val_t _align_val) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			return rawallocator->Allocate(_size, _align_val);
		}
		static inline void operator delete(void* _ptr, size_t _size) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			rawallocator->Deallocate(_ptr, _size);
		}
		static inline void operator delete[](void* _ptr, size_t _size) noexcept {
			const rawallocator_t* rawallocator = *_Ptr_Ptr_RawAllocator;
			assert(rawallocator);
			rawallocator->Deallocate(_ptr, _size);
		}
	};

#pragma region Delegate
	//{ Delegate

	enum DelegateFlags : unsigned int {
		DelegateFlags_None = 0x0,
		DelegateFlag_Noexcept = 0x1
	};

	using DelegateCleanupFnptr = void (YBWLIB2_CALLTYPE*)(uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept;

	template<unsigned int _delegateflags, typename _Return_Ty, typename... _Args_Ty>
	struct Delegate final {
	public:
		using return_type = _Return_Ty;
		using argument_tuple_type = ::std::tuple<_Args_Ty&&...>;
		static constexpr unsigned int delegateflags = _delegateflags;
		static constexpr bool is_noexcept = delegateflags & DelegateFlags::DelegateFlag_Noexcept;
		struct invoke_constexpr_callable_t {};
		struct invoke_function_t {};
		struct invoke_observe_callable_t {};
		struct invoke_adopt_callable_t {};
		struct invoke_construct_callable_t {};
		struct address_insensitive_callable_t {};
		struct invoke_member_function_t {};
		struct use_argument_tuple_t {};
		static constexpr invoke_constexpr_callable_t invoke_constexpr_callable {};
		static constexpr invoke_function_t invoke_function {};
		static constexpr invoke_observe_callable_t invoke_observe_callable {};
		static constexpr invoke_adopt_callable_t invoke_adopt_callable {};
		static constexpr invoke_construct_callable_t invoke_construct_callable {};
		static constexpr address_insensitive_callable_t address_insensitive_callable {};
		static constexpr invoke_member_function_t invoke_member_function {};
		static constexpr use_argument_tuple_t use_argument_tuple {};
		using fnptr_invoke_t =
			::std::conditional_t<
			is_noexcept,
			return_type(YBWLIB2_CALLTYPE*)(uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept,
			return_type(YBWLIB2_CALLTYPE*)(uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args)
			>;
		using fnptr_cleanup_t = DelegateCleanupFnptr;
		fnptr_invoke_t fnptr_invoke = nullptr;
		uintptr_t contextvalue1 = 0;
		uintptr_t contextvalue2 = 0;
		fnptr_cleanup_t fnptr_cleanup = nullptr;
		constexpr Delegate(
			fnptr_invoke_t _fnptr_invoke = nullptr,
			uintptr_t _contextvalue1 = 0,
			uintptr_t _contextvalue2 = 0,
			fnptr_cleanup_t _fnptr_cleanup = nullptr
		) noexcept
			: fnptr_invoke(_fnptr_invoke),
			contextvalue1(_contextvalue1),
			contextvalue2(_contextvalue2),
			fnptr_cleanup(_fnptr_cleanup) {}
		constexpr Delegate(
			invoke_function_t,
			return_type(YBWLIB2_CALLTYPE* _fnptr_invoke)(uintptr_t _contextvalue1, _Args_Ty... args) noexcept(is_noexcept),
			uintptr_t _contextvalue1 = 0
		) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				(*reinterpret_cast<decltype(_fnptr_invoke)>(_contextvalue2))(_contextvalue1, ::std::forward<_Args_Ty>(args)...);
			};
			this->contextvalue1 = _contextvalue1;
			this->contextvalue2 = reinterpret_cast<uintptr_t>(_fnptr_invoke);
		}
		constexpr Delegate(
			invoke_function_t,
			return_type(YBWLIB2_CALLTYPE* _fnptr_invoke)(_Args_Ty... args) noexcept(is_noexcept)
		) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				static_cast<void>(_contextvalue2);
				(*reinterpret_cast<decltype(_fnptr_invoke)>(_contextvalue1))(::std::forward<_Args_Ty>(args)...);
			};
			this->contextvalue1 = reinterpret_cast<uintptr_t>(_fnptr_invoke);
		}
		template<
			typename _Callable_Invoke_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, uintptr_t, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_observe_callable_t, _Callable_Invoke_Ty& _callable_invoke, uintptr_t _contextvalue1 = 0) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue2))(_contextvalue1, ::std::forward<_Args_Ty>(args)...);
			};
			this->contextvalue1 = _contextvalue1;
			this->contextvalue2 = reinterpret_cast<uintptr_t>(&_callable_invoke);
		}
		template<
			typename _Callable_Invoke_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_observe_callable_t, _Callable_Invoke_Ty& _callable_invoke) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				static_cast<void>(_contextvalue2);
				return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1))(::std::forward<_Args_Ty>(args)...);
			};
			this->contextvalue1 = reinterpret_cast<uintptr_t>(&_callable_invoke);
		}
		template<
			typename _Callable_Invoke_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, uintptr_t, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_adopt_callable_t, _Callable_Invoke_Ty*&& _ptr_callable_invoke, uintptr_t _contextvalue1 = 0) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue2))(_contextvalue1, ::std::forward<_Args_Ty>(args)...);
			};
			_ptr_callable_invoke = nullptr;
			this->contextvalue1 = _contextvalue1;
			this->contextvalue2 = reinterpret_cast<uintptr_t>(::std::move(_ptr_callable_invoke));
			this->fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
				static_cast<void>(_contextvalue1);
				delete reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue2);
			};
		}
		template<
			typename _Callable_Invoke_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_adopt_callable_t, _Callable_Invoke_Ty*&& _ptr_callable_invoke) noexcept {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				static_cast<void>(_contextvalue2);
				return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1))(::std::forward<_Args_Ty>(args)...);
			};
			_ptr_callable_invoke = nullptr;
			this->contextvalue1 = reinterpret_cast<uintptr_t>(::std::move(_ptr_callable_invoke));
			this->fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
				static_cast<void>(_contextvalue2);
				delete reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1);
			};
		}
		template<
			typename _Callable_Invoke_Ty,
			typename _Tuple_Args_Ctor_Callable_Invoke_Ty,
			typename _Allocator_Callable_Invoke_Ty = ::std::allocator<_Callable_Invoke_Ty>,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_construct_callable_t, _Tuple_Args_Ctor_Callable_Invoke_Ty&& _tuple_args_ctor_callable_invoke, const _Allocator_Callable_Invoke_Ty& _allocator_callable_invoke = _Allocator_Callable_Invoke_Ty())
			noexcept(noexcept(PlacementCreateTupleIndexSequenceImpl(_allocator_callable_invoke.allocate(1), ::std::move(_tuple_args_ctor_callable_invoke), ::std::make_index_sequence<::std::tuple_size_v<_Tuple_Args_Ctor_Callable_Invoke_Ty>>()))) {
			this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
				static_cast<void>(_contextvalue2);
				return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1))(::std::forward<_Args_Ty>(args)...);
			};
			this->contextvalue1 = reinterpret_cast<uintptr_t>(PlacementCreateTupleIndexSequenceImpl(_allocator_callable_invoke.allocate(1), ::std::move(_tuple_args_ctor_callable_invoke), ::std::make_index_sequence<::std::tuple_size_v<_Tuple_Args_Ctor_Callable_Invoke_Ty>>()));
			this->contextvalue2 = reinterpret_cast<uintptr_t>(&_allocator_callable_invoke);
			this->fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
				_Callable_Invoke_Ty* ptr_callable_invoke = reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1);
				ptr_callable_invoke->~_Callable_Invoke_Ty();
				reinterpret_cast<const _Allocator_Callable_Invoke_Ty*>(_contextvalue2)->deallocate(ptr_callable_invoke, 1);
			};
		}
		template<
			typename _Callable_Invoke_Ty,
			typename _Tuple_Args_Ctor_Callable_Invoke_Ty,
			typename _Allocator_Callable_Invoke_Ty = ::std::allocator<_Callable_Invoke_Ty>,
			typename ::std::enable_if<::std::is_convertible_v<typename ::std::invoke_result<_Callable_Invoke_Ty, _Args_Ty...>::type, return_type>, int>::type = 0
		>
			Delegate(invoke_construct_callable_t, address_insensitive_callable_t, _Tuple_Args_Ctor_Callable_Invoke_Ty&& _tuple_args_ctor_callable_invoke, const _Allocator_Callable_Invoke_Ty& _allocator_callable_invoke = _Allocator_Callable_Invoke_Ty())
			noexcept(noexcept(PlacementCreateTupleIndexSequenceImpl(_allocator_callable_invoke.allocate(1), ::std::move(_tuple_args_ctor_callable_invoke), ::std::make_index_sequence<::std::tuple_size_v<_Tuple_Args_Ctor_Callable_Invoke_Ty>>()))) {
			if constexpr (::std::is_object_v<_Callable_Invoke_Ty> && sizeof(_Callable_Invoke_Ty) <= sizeof(uintptr_t)) {
				static_cast<void>(_allocator_callable_invoke);
				this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
					static_cast<void>(_contextvalue2);
					return (*reinterpret_cast<_Callable_Invoke_Ty*>(&_contextvalue1))(::std::forward<_Args_Ty>(args)...);
				};
				PlacementCreateTupleIndexSequenceImpl(reinterpret_cast<_Callable_Invoke_Ty*>(&this->contextvalue1), ::std::move(_tuple_args_ctor_callable_invoke), ::std::make_index_sequence<::std::tuple_size_v<_Tuple_Args_Ctor_Callable_Invoke_Ty>>());
				this->fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
					static_cast<void>(_contextvalue2);
					reinterpret_cast<_Callable_Invoke_Ty*>(&_contextvalue1)->~_Callable_Invoke_Ty();
				};
			} else {
				this->fnptr_invoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, _Args_Ty... args) noexcept(is_noexcept)->return_type {
					static_cast<void>(_contextvalue2);
					return (*reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1))(::std::forward<_Args_Ty>(args)...);
				};
				this->contextvalue1 = reinterpret_cast<uintptr_t>(PlacementCreateTupleIndexSequenceImpl(_allocator_callable_invoke.allocate(1), ::std::move(_tuple_args_ctor_callable_invoke), ::std::make_index_sequence<::std::tuple_size_v<_Tuple_Args_Ctor_Callable_Invoke_Ty>>()));
				this->contextvalue2 = reinterpret_cast<uintptr_t>(&_allocator_callable_invoke);
				this->fnptr_cleanup = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2) noexcept->void {
					_Callable_Invoke_Ty* ptr_callable_invoke = reinterpret_cast<_Callable_Invoke_Ty*>(_contextvalue1);
					ptr_callable_invoke->~_Callable_Invoke_Ty();
					reinterpret_cast<const _Allocator_Callable_Invoke_Ty*>(_contextvalue2)->deallocate(ptr_callable_invoke, 1);
				};
			}
		}
		Delegate(const Delegate&) = delete;
		template<
			unsigned int _delegateflags_from,
			typename _Return_From_Ty,
			typename... _Args_From_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename Delegate<_delegateflags_from, _Return_From_Ty, _Args_From_Ty...>::fnptr_invoke_t, fnptr_invoke_t>, int>::type = 0
		>
			constexpr Delegate(Delegate<_delegateflags_from, _Return_From_Ty, _Args_From_Ty...>&& x) noexcept
			: fnptr_invoke(::std::move(x.fnptr_invoke)),
			contextvalue1(::std::move(x.contextvalue1)),
			contextvalue2(::std::move(x.contextvalue2)),
			fnptr_cleanup(::std::move(x.fnptr_cleanup)) {
			x.fnptr_cleanup = nullptr;
			x.contextvalue2 = 0;
			x.contextvalue1 = 0;
			x.fnptr_invoke = nullptr;
		}
		~Delegate() {
			assert(this);
			if (this->fnptr_cleanup)
				(*this->fnptr_cleanup)(this->contextvalue1, this->contextvalue2);
			this->fnptr_cleanup = nullptr;
			this->contextvalue2 = 0;
			this->contextvalue1 = 0;
			this->fnptr_invoke = nullptr;
		}
		Delegate& operator=(const Delegate&) = delete;
		template<
			unsigned int _delegateflags_from,
			typename _Return_From_Ty,
			typename... _Args_From_Ty,
			typename ::std::enable_if<::std::is_convertible_v<typename Delegate<_delegateflags_from, _Return_From_Ty, _Args_From_Ty...>::fnptr_invoke_t, fnptr_invoke_t>, int>::type = 0
		>
			constexpr Delegate& operator=(Delegate<_delegateflags_from, _Return_From_Ty, _Args_From_Ty...>&& x) noexcept {
			assert(this);
			if (this->fnptr_cleanup)
				(*this->fnptr_cleanup)(this->contextvalue1, this->contextvalue2);
			this->fnptr_invoke = ::std::move(x.fnptr_invoke);
			x.fnptr_invoke = nullptr;
			this->contextvalue1 = ::std::move(x.contextvalue1);
			x.contextvalue1 = 0;
			this->contextvalue2 = ::std::move(x.contextvalue2);
			x.contextvalue2 = 0;
			this->fnptr_cleanup = ::std::move(x.fnptr_cleanup);
			x.fnptr_cleanup = nullptr;
			return *this;
		}
		explicit operator bool() const noexcept { return this->fnptr_invoke; }
		return_type YBWLIB2_CALLTYPE operator()(_Args_Ty... args) const noexcept(is_noexcept) {
			assert(this && this->fnptr_invoke);
			return (*this->fnptr_invoke)(this->contextvalue1, this->contextvalue2, ::std::forward<_Args_Ty>(args)...);
		}
		return_type YBWLIB2_CALLTYPE operator()(use_argument_tuple_t, argument_tuple_type&& _tuple_args) noexcept(is_noexcept) {
			return (*this)(use_argument_tuple, ::std::move(_tuple_args), ::std::make_index_sequence<::std::tuple_size_v<argument_tuple_type>>());
		}
	private:
		template<
			typename _Ty,
			typename _Tuple_Args_Ctor_Ty,
			size_t... _index_tuple_args_ctor
		>
			static _Ty* PlacementCreateTupleIndexSequenceImpl(_Ty* _ptr, _Tuple_Args_Ctor_Ty&& _tuple_args_ctor, ::std::index_sequence<_index_tuple_args_ctor...>)
			noexcept(noexcept(_Ty(::std::get<_index_tuple_args_ctor>(::std::forward<_Tuple_Args_Ctor_Ty>(_tuple_args_ctor))...))) {
			return new (_ptr) _Ty(::std::get<_index_tuple_args_ctor>(::std::forward<_Tuple_Args_Ctor_Ty>(_tuple_args_ctor))...);
		};
		template<size_t... _index_tuple_args>
		return_type YBWLIB2_CALLTYPE operator()(use_argument_tuple_t, argument_tuple_type&& _tuple_args, ::std::index_sequence<_index_tuple_args...>)
			noexcept(noexcept((*this)(::std::get<_index_tuple_args>(::std::move(_tuple_args))...))) {
			return (*this)(::std::get<_index_tuple_args>(::std::move(_tuple_args))...);
		}
	};

	//}
#pragma endregion

	/// <summary>An object for holding a pointer to another object that's placement-created in the storage of the former object.</summary>
	template<typename _Element_Ty>
	struct objholder_local_t final {
		static_assert(::std::is_object_v<_Element_Ty>, "The element type is not an object type.");
		static_assert(!::std::is_const_v<_Element_Ty>, "The element type is const-qualified.");
		struct construct_obj_t {};
		static constexpr construct_obj_t construct_obj {};
		inline constexpr objholder_local_t() noexcept = default;
		template<typename... _Args_Ty>
		inline objholder_local_t(construct_obj_t, _Args_Ty&&... args) noexcept(::std::is_nothrow_constructible_v<_Element_Ty, _Args_Ty...>) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			this->ptr_element = new(this->buf_element) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Callable_Ty>
		inline objholder_local_t(_Callable_Ty _callable) noexcept(::std::is_nothrow_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			this->ptr_element = _callable(static_cast<void*>(this->buf_element));
		}
		inline objholder_local_t(const objholder_local_t& x) noexcept(::std::is_nothrow_copy_constructible_v<_Element_Ty>) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (x.ptr_element)
				this->ptr_element = new(this->buf_element) _Element_Ty(*x.ptr_element);
		}
		inline objholder_local_t(objholder_local_t&& x) noexcept(::std::is_nothrow_move_constructible_v<_Element_Ty>) {
			static_assert(::std::is_move_constructible_v<_Element_Ty>, "The element type is not move-constructible.");
			if (x.ptr_element) {
				this->ptr_element = new(this->buf_element) _Element_Ty(::std::move(*x.ptr_element));
				x.ptr_element->~_Element_Ty();
				x.ptr_element = nullptr;
			}
		}
		inline ~objholder_local_t() {
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
		}
		inline objholder_local_t& operator=(const objholder_local_t& x) noexcept(::std::is_nothrow_copy_constructible_v<_Element_Ty>) {
			static_assert(::std::is_copy_constructible_v<_Element_Ty>, "The element type is not copy-constructible.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			if (x.ptr_element) {
				this->ptr_element = new(this->buf_element) _Element_Ty(*x.ptr_element);
			}
			return *this;
		}
		inline objholder_local_t& operator=(objholder_local_t&& x) noexcept(::std::is_nothrow_move_constructible_v<_Element_Ty>) {
			static_assert(::std::is_move_constructible_v<_Element_Ty>, "The element type is not move-constructible.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			if (x.ptr_element) {
				this->ptr_element = new(this->buf_element) _Element_Ty(::std::move(*x.ptr_element));
				x.ptr_element->~_Element_Ty();
				x.ptr_element = nullptr;
			}
			return *this;
		}
		inline explicit operator bool() const noexcept { return this->ptr_element; }
		inline _Element_Ty& operator*() const noexcept { return *this->ptr_element; }
		inline _Element_Ty* operator->() const noexcept { return this->ptr_element; }
		inline _Element_Ty* get() const noexcept { return this->ptr_element; }
		template<typename... _Args_Ty>
		inline void construct(construct_obj_t, _Args_Ty&&... args) noexcept(::std::is_nothrow_constructible_v<_Element_Ty, _Args_Ty...>) {
			static_assert(::std::is_constructible_v<_Element_Ty, _Args_Ty...>, "The element type is not constructible with the specified arguments.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			this->ptr_element = new(this->buf_element) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Callable_Ty>
		inline void construct(_Callable_Ty _callable) noexcept(::std::is_nothrow_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>) {
			static_assert(::std::is_invocable_r_v<_Element_Ty*, _Callable_Ty, void*>, "The callable value is invalid.");
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
			this->ptr_element = _callable(static_cast<void*>(this->buf_element));
		}
		inline void destruct() noexcept {
			if (this->ptr_element) {
				this->ptr_element->~_Element_Ty();
				this->ptr_element = nullptr;
			}
		}
	private:
		_Element_Ty* ptr_element = nullptr;
		alignas(_Element_Ty) uint8_t buf_element[sizeof(_Element_Ty)];
	};

	/// <summary>A wrapper for objects that satisfy the requirement <c>BasicLockable</c>.</summary>
	struct wrapper_basic_lockable_t final {
		/// <summary>Function pointer type for blocking if necessary and locking the object.</summary>
		typedef void(YBWLIB2_CALLTYPE* fnptr_lock_t)(uintptr_t context);
		/// <summary>Function pointer type for unlocking the object.</summary>
		typedef void(YBWLIB2_CALLTYPE* fnptr_unlock_t)(uintptr_t context) noexcept;
		fnptr_lock_t fnptr_lock = nullptr;
		fnptr_unlock_t fnptr_unlock = nullptr;
		uintptr_t context = 0;
		inline constexpr wrapper_basic_lockable_t(fnptr_lock_t _fnptr_lock, fnptr_unlock_t _fnptr_unlock, uintptr_t _context = 0) noexcept
			: fnptr_lock(_fnptr_lock), fnptr_unlock(_fnptr_unlock), context(_context) {}
		/// <summary>Blocks if necessary and locks the object.</summary>
		inline void lock() const {
			if (!this->fnptr_lock) abort();
			(*this->fnptr_lock)(this->context);
		}
		/// <summary>Unlocks the object.</summary>
		inline void unlock() const noexcept {
			if (!this->fnptr_unlock) abort();
			(*this->fnptr_unlock)(this->context);
		}
	};
	static_assert(::std::is_standard_layout_v<wrapper_basic_lockable_t>, "wrapper_basic_lockable_t is not standard-layout.");

	template<typename _Class_BasicLockable_Ty>
	inline wrapper_basic_lockable_t WrapBasicLockable(_Class_BasicLockable_Ty& _obj) {
		return wrapper_basic_lockable_t(
			[](uintptr_t context)->void {
				_Class_BasicLockable_Ty* obj = reinterpret_cast<_Class_BasicLockable_Ty*>(context);
				obj->lock();
			},
			[](uintptr_t context) noexcept->void {
				_Class_BasicLockable_Ty* obj = reinterpret_cast<_Class_BasicLockable_Ty*>(context);
				obj->unlock();
			},
				reinterpret_cast<uintptr_t>(&_obj)
				);
	}

	/// <summary>A wrapper for objects that satisfy the requirement <c>Lockable</c>.</summary>
	struct wrapper_lockable_t final {
		/// <summary>Function pointer type for blocking if necessary and locking the object.</summary>
		typedef void(YBWLIB2_CALLTYPE* fnptr_lock_t)(uintptr_t context);
		/// <summary>Function pointer type for unlocking the object.</summary>
		typedef void(YBWLIB2_CALLTYPE* fnptr_unlock_t)(uintptr_t context) noexcept;
		/// <summary>Function pointer type for attempting to lock the object without blocking.</summary>
		typedef bool(YBWLIB2_CALLTYPE* fnptr_try_lock_t)(uintptr_t context);
		fnptr_lock_t fnptr_lock = nullptr;
		fnptr_unlock_t fnptr_unlock = nullptr;
		fnptr_try_lock_t fnptr_try_lock = nullptr;
		uintptr_t context = 0;
		inline constexpr wrapper_lockable_t(fnptr_lock_t _fnptr_lock, fnptr_unlock_t _fnptr_unlock, fnptr_try_lock_t _fnptr_try_lock, uintptr_t _context = 0) noexcept
			: fnptr_lock(_fnptr_lock), fnptr_unlock(_fnptr_unlock), fnptr_try_lock(_fnptr_try_lock), context(_context) {}
		inline operator wrapper_basic_lockable_t() const noexcept { return wrapper_basic_lockable_t(this->fnptr_lock, this->fnptr_unlock, this->context); }
		/// <summary>Blocks if necessary and locks the object.</summary>
		inline void lock() const {
			if (!this->fnptr_lock) abort();
			(*this->fnptr_lock)(this->context);
		}
		/// <summary>Unlocks the object.</summary>
		inline void unlock() const noexcept {
			if (!this->fnptr_unlock) abort();
			(*this->fnptr_unlock)(this->context);
		}
		/// <summary>Attempts to lock the object without blocking.</summary>
		inline bool try_lock() const {
			if (!this->fnptr_try_lock) abort();
			(*this->fnptr_try_lock)(this->context);
		}
	};
	static_assert(::std::is_standard_layout_v<wrapper_lockable_t>, "wrapper_lockable_t is not standard-layout.");

	template<typename _Class_Lockable_Ty>
	inline wrapper_lockable_t WrapLockable(_Class_Lockable_Ty& _obj) {
		return wrapper_lockable_t(
			[](uintptr_t context)->void {
				_Class_Lockable_Ty* obj = reinterpret_cast<_Class_Lockable_Ty*>(context);
				obj->lock();
			},
			[](uintptr_t context) noexcept->void {
				_Class_Lockable_Ty* obj = reinterpret_cast<_Class_Lockable_Ty*>(context);
				obj->unlock();
			},
				[](uintptr_t context)->bool {
				_Class_Lockable_Ty* obj = reinterpret_cast<_Class_Lockable_Ty*>(context);
				return obj->try_lock();
			},
			reinterpret_cast<uintptr_t>(&_obj)
		);
	}

	/// <summary>
	/// A structure for storing executable module information.
	/// One executable module that uses functionalities provided by this library corresponds to exactly one instance of this structure.
	/// As a result, this structure is not copy-constructible, move-constructible, copy-assignable or move-assignable.
	/// Comparisons of objects of this type is done by comparing pointers to them.
	/// As a result, the order of the objects may change between different runs of the same program.
	/// </summary>
	struct module_info_t final {
		const void* addr_module_base = nullptr;
		inline constexpr module_info_t(const void* _addr_module_base) noexcept : addr_module_base(_addr_module_base) {}
		module_info_t(const module_info_t&) = delete;
		module_info_t(module_info_t&&) = delete;
		inline ~module_info_t() noexcept = default;
		module_info_t& operator=(const module_info_t&) = delete;
		module_info_t& operator=(module_info_t&&) = delete;
		inline bool operator==(const module_info_t& r) const noexcept { return this == &r; }
		inline bool operator!=(const module_info_t& r) const noexcept { return this != &r; }
		inline bool operator<(const module_info_t& r) const noexcept { return this < &r; }
		inline bool operator<=(const module_info_t& r) const noexcept { return this <= &r; }
		inline bool operator>(const module_info_t& r) const noexcept { return this > &r; }
		inline bool operator>=(const module_info_t& r) const noexcept { return this >= &r; }
	};
	static_assert(::std::is_standard_layout_v<module_info_t>, "module_info_t is not standard-layout.");

	/// <summary>A pointer to the <c>module_info_t</c> object that represents the executable module that contains this reference to this variable.</summary>
	extern module_info_t* module_info_current;

	/// <summary>A wrapper for <c>::std::type_info</c> that may be used across executable module boundaries.</summary>
	struct wrapper_type_info_t final {
		/// <summary>
		/// Checks type equivalence.
		/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
		/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
		/// </summary>
		/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
		/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
		/// <returns>Whether the type represented by <c>*l</c> is considered equivalent to the type represented by <c>*r</c>.</returns>
		static inline bool IsEqualTo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept {
			if (!l || !r) return !l && !r;
			if (l->module_info != r->module_info) return false;
			if (l->fnptr_is_equal_to)
				return (*l->fnptr_is_equal_to)(l, r);
			else if (r->fnptr_is_equal_to)
				return (*r->fnptr_is_equal_to)(l, r);
			else if (l->fnptr_is_less_than)
				return !(*l->fnptr_is_less_than)(l, r) && !(*l->fnptr_is_less_than)(r, l);
			else if (r->fnptr_is_less_than)
				return !(*r->fnptr_is_less_than)(l, r) && !(*r->fnptr_is_less_than)(r, l);
			else
				return l->context == r->context;
		}
		/// <summary>
		/// Checks type precedence.
		/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
		/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
		/// If 2 <c>wrapper_type_info_t</c> objects are associated with different executable modules,
		/// one precedes another IF AND ONLY IF the <c>module_info_t</c> POINTER associated with the former one precedes the <c>module_info_t</c> POINTER associated with the later one.
		/// <c>wrapper_type_info_t</c> objects associated with the same executable module are grouped together,
		/// i.e., if <c>a</c> precedes <c>c</c> and <c>a</c> is associated with the same executable module as <c>c</c>,
		/// there will not be an object <c>b</c> associated with a different executable module such that <c>a</c> precedes <c>b</c> and <c>b</c> precedes <c>c</c>.
		/// </summary>
		/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
		/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
		/// <returns>Whether the type represented by <c>*l</c> is considered to precede the type represented by <c>*r</c>.</returns>
		static inline bool IsLessThan(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept {
			if (!l || !r) return r;
			if (l->module_info != r->module_info) return l->module_info < r->module_info;
			if (l->fnptr_is_less_than)
				return (*l->fnptr_is_less_than)(l, r);
			else if (r->fnptr_is_less_than)
				return (*r->fnptr_is_less_than)(l, r);
			else
				return l->context < r->context;
		}
		/// <summary>
		/// Function pointer type for checking type equivalence.
		/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
		/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
		/// </summary>
		/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
		/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
		/// <returns>Whether the type represented by <c>*l</c> is considered equivalent to the type represented by <c>*r</c>.</returns>
		typedef bool(YBWLIB2_CALLTYPE* fnptr_is_equal_to_t)(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
		/// <summary>
		/// Function pointer type for checking type precedence.
		/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
		/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
		/// If 2 <c>wrapper_type_info_t</c> objects are associated with different executable modules,
		/// one precedes another IF AND ONLY IF the <c>module_info_t</c> POINTER associated with the former one precedes the <c>module_info_t</c> POINTER associated with the later one.
		/// <c>wrapper_type_info_t</c> objects associated with the same executable module are grouped together,
		/// i.e., if <c>a</c> precedes <c>c</c> and <c>a</c> is associated with the same executable module as <c>c</c>,
		/// there will not be an object <c>b</c> associated with a different executable module such that <c>a</c> precedes <c>b</c> and <c>b</c> precedes <c>c</c>.
		/// </summary>
		/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
		/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
		/// <returns>Whether the type represented by <c>*l</c> is considered to precede the type represented by <c>*r</c>.</returns>
		typedef bool(YBWLIB2_CALLTYPE* fnptr_is_less_than_t)(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
		/// <summary>Function pointer type for getting the implementation-defined hash code of the type.</summary>
		/// <returns>Returns the implementation-defined hash code of the type.</returns>
		typedef size_t(YBWLIB2_CALLTYPE* fnptr_get_hash_code_t)(const wrapper_type_info_t* x) noexcept;
		/// <summary>Function pointer type for getting the implementation-defined null-terminated name of the type, if available.</summary>
		/// <returns>
		/// Returns the implementation-defined null-terminated name, in UTF-8, of the type, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		typedef const char*(YBWLIB2_CALLTYPE* fnptr_get_name_t)(const wrapper_type_info_t* x) noexcept;
		fnptr_is_equal_to_t fnptr_is_equal_to = nullptr;
		fnptr_is_less_than_t fnptr_is_less_than = nullptr;
		fnptr_get_hash_code_t fnptr_get_hash_code = nullptr;
		fnptr_get_name_t fnptr_get_name = nullptr;
		const module_info_t* module_info = nullptr;
		uintptr_t context = 0;
		inline constexpr wrapper_type_info_t(
			fnptr_is_equal_to_t _fnptr_is_equal_to,
			fnptr_is_less_than_t _fnptr_is_less_than,
			fnptr_get_hash_code_t _fnptr_get_hash_code,
			fnptr_get_name_t _fnptr_get_name,
			const module_info_t* _module_info,
			uintptr_t _context
		) noexcept
			: fnptr_is_equal_to(_fnptr_is_equal_to),
			fnptr_is_less_than(_fnptr_is_less_than),
			fnptr_get_hash_code(_fnptr_get_hash_code),
			fnptr_get_name(_fnptr_get_name),
			module_info(_module_info),
			context(_context) {}
		inline wrapper_type_info_t(const ::std::type_info& val_type_info) noexcept
			: fnptr_is_equal_to(&wrapper_type_info_t::IsEqualTo_TypeInfo),
			fnptr_is_less_than(&wrapper_type_info_t::IsLessThan_TypeInfo),
			fnptr_get_hash_code(&wrapper_type_info_t::GetHashCode_TypeInfo),
			fnptr_get_name(&wrapper_type_info_t::GetName_TypeInfo),
			module_info(module_info_current),
			context(reinterpret_cast<uintptr_t>(&val_type_info)) {}
		/// <summary>Gets the implementation-defined hash code of the type.</summary>
		/// <returns>Returns the implementation-defined hash code of the type.</returns>
		inline size_t GetHashCode() const noexcept {
			if (!this || !this->fnptr_get_hash_code)
				return 0;
			else
				return (*this->fnptr_get_hash_code)(this);
		}
		/// <summary>Gets the implementation-defined null-terminated name of the type, if available.</summary>
		/// <returns>
		/// Returns the implementation-defined null-terminated name, in UTF-8, of the type, if available.
		/// If no meaningful name can be provided, an empty pointer is returned.
		/// </returns>
		inline const char* GetName() const noexcept {
			if (!this || !this->fnptr_get_name)
				return nullptr;
			else
				return (*this->fnptr_get_name)(this);
		}
	protected:
		/// <summary>Checks type equivalence for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static bool YBWLIB2_CALLTYPE IsEqualTo_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
		/// <summary>Checks type precedence for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static bool YBWLIB2_CALLTYPE IsLessThan_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
		/// <summary>Gets the implementation-defined hash code of the type for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static size_t YBWLIB2_CALLTYPE GetHashCode_TypeInfo(const wrapper_type_info_t* x) noexcept;
		/// <summary>Gets the implementation-defined null-terminated name of the type for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static const char* YBWLIB2_CALLTYPE GetName_TypeInfo(const wrapper_type_info_t* x) noexcept;
	};
	static_assert(::std::is_standard_layout_v<wrapper_type_info_t>, "wrapper_type_info_t is not standard-layout.");
	/// <summary>
	/// Checks type equivalence.
	/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
	/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
	/// </summary>
	/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
	/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
	/// <returns>Whether the type represented by <c>*l</c> is considered equivalent to the type represented by <c>*r</c>.</returns>
	inline bool IsEqualTo_WrapperTypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept { return wrapper_type_info_t::IsEqualTo(l, r); }
	/// <summary>
	/// Checks type precedence.
	/// <c>wrapper_type_info_t</c> objects associated with different executable modules are never equivalent,
	/// even if the types represented have the same name and are binary-compatible (for example, if the types are interface classes with the same declaration).
	/// If 2 <c>wrapper_type_info_t</c> objects are associated with different executable modules,
	/// one precedes another IF AND ONLY IF the <c>module_info_t</c> POINTER associated with the former one precedes the <c>module_info_t</c> POINTER associated with the later one.
	/// <c>wrapper_type_info_t</c> objects associated with the same executable module are grouped together,
	/// i.e., if <c>a</c> precedes <c>c</c> and <c>a</c> is associated with the same executable module as <c>c</c>,
	/// there will not be an object <c>b</c> associated with a different executable module such that <c>a</c> precedes <c>b</c> and <c>b</c> precedes <c>c</c>.
	/// </summary>
	/// <param name="l">Pointer to the <c>wrapper_type_info_t</c> object on the left side of the comparison operator.</param>
	/// <param name="r">Pointer to the <c>wrapper_type_info_t</c> object on the right side of the comparison operator.</param>
	/// <returns>Whether the type represented by <c>*l</c> is considered to precede the type represented by <c>*r</c>.</returns>
	inline bool IsLessThan_WrapperTypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept { return wrapper_type_info_t::IsLessThan(l, r); }

#pragma region IndexedDataStore
	//{ IndexedDataStore

	/// <summary>Unique identifier used to identify an indexed data entry.</summary>
	struct IndexedDataEntryID : public VolatileID {
		constexpr IndexedDataEntryID() noexcept = default;
		explicit IndexedDataEntryID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit IndexedDataEntryID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit IndexedDataEntryID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		IndexedDataEntryID(const IndexedDataEntryID& x) noexcept = default;
		IndexedDataEntryID(IndexedDataEntryID&& x) noexcept = default;
		~IndexedDataEntryID() = default;
		IndexedDataEntryID& operator=(const IndexedDataEntryID& x) noexcept = default;
		IndexedDataEntryID& operator=(IndexedDataEntryID&& x) noexcept = default;
		bool operator==(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const IndexedDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<IndexedDataEntryID>, "IndexedDataEntryID is not standard-layout.");

	template<>
	struct hash<IndexedDataEntryID> {
		inline size_t operator()(const IndexedDataEntryID& x) const {
			return x.hash();
		}
	};

	/// <summary>A raw value in an indexed data entry.</summary>
	struct IndexedDataRawValue final {
		/// <summary>Function pointer type for cleaning up the raw value before it's destructed.</summary>
		typedef void(YBWLIB2_CALLTYPE* fnptr_cleanup_t)(IndexedDataRawValue* x) noexcept;
		fnptr_cleanup_t fnptr_cleanup = nullptr;
		uintptr_t contextvalue = 0;
		inline IndexedDataRawValue(
			fnptr_cleanup_t _fnptr_cleanup,
			uintptr_t _contextvalue
		) noexcept
			: fnptr_cleanup(_fnptr_cleanup),
			contextvalue(_contextvalue) {}
		IndexedDataRawValue(const IndexedDataRawValue&) = delete;
		inline IndexedDataRawValue(IndexedDataRawValue&& x) noexcept : fnptr_cleanup(::std::move(x.fnptr_cleanup)), contextvalue(::std::move(x.contextvalue)) {
			x.contextvalue = 0;
			x.fnptr_cleanup = nullptr;
		}
		inline ~IndexedDataRawValue() {
			if (this->fnptr_cleanup)
				(*this->fnptr_cleanup)(this);
			this->contextvalue = 0;
			this->fnptr_cleanup = nullptr;
		}
		IndexedDataRawValue& operator=(const IndexedDataRawValue&) = delete;
		inline IndexedDataRawValue& operator=(IndexedDataRawValue&& x) noexcept {
			if (this->fnptr_cleanup)
				(*this->fnptr_cleanup)(this);
			this->fnptr_cleanup = ::std::move(x.fnptr_cleanup);
			this->contextvalue = ::std::move(x.contextvalue);
			x.contextvalue = 0;
			x.fnptr_cleanup = nullptr;
			return *this;
		}
	};
	static_assert(::std::is_standard_layout_v<IndexedDataRawValue>, "IndexedDataRawValue is not standard-layout.");

	class IndexedDataStore final {
	public:
		/// <summary>Constructs an <c>IndexedDataStore</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		inline IndexedDataStore(const rawallocator_t* _rawallocator) noexcept { this->ConstructWithRawAllocator(_rawallocator); }
		/// <summary>Move-constructs the indexed data store.</summary>
		inline IndexedDataStore(IndexedDataStore&& x) noexcept { this->MoveConstruct(&x); }
		inline ~IndexedDataStore() { this->Destruct(); }
		/// <summary>Move-assigns the indexed data store.</summary>
		inline IndexedDataStore& operator=(IndexedDataStore&& x) noexcept {
			this->MoveAssign(&x);
			return *this;
		}
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		inline const rawallocator_t* GetRawAllocator() const noexcept { return this->rawallocator; }
		/// <summary>Gets a pointer to the raw value of the entry with the specified identifier in this store.</summary>
		/// <param name="_entryid">Reference to the indexed data entry ID.</param>
		/// <returns>
		/// Returns a pointer to the raw value of the entry with the specified identifier.
		/// If there wasn't an entry with the specified identifier in this store, an empty pointer will be returned.
		/// The caller should NOT destruct or free the object pointed to by the returned pointer.
		/// </returns>
		inline const IndexedDataRawValue* GetRawValueByEntryID(const IndexedDataEntryID& _entryid) const noexcept { return this->GetRawValueByEntryID(&_entryid); }
		/// <summary>Gets a pointer to the raw value of the entry with the specified identifier in this store.</summary>
		/// <param name="_entryid">Reference to the indexed data entry ID.</param>
		/// <returns>
		/// Returns a pointer to the raw value of the entry with the specified identifier.
		/// If there wasn't an entry with the specified identifier in this store, an empty pointer will be returned.
		/// The caller should NOT destruct or free the object pointed to by the returned pointer.
		/// </returns>
		inline IndexedDataRawValue* GetRawValueByEntryID(const IndexedDataEntryID& _entryid) noexcept { return this->GetRawValueByEntryID(&_entryid); }
		/// <summary>Gets a pointer to the raw value of the entry with the specified identifier in this store.</summary>
		/// <param name="_entryid">Pointer to the indexed data entry ID.</param>
		/// <returns>
		/// Returns a pointer to the raw value of the entry with the specified identifier.
		/// If there wasn't an entry with the specified identifier in this store, an empty pointer will be returned.
		/// The caller should NOT destruct or free the object pointed to by the returned pointer.
		/// </returns>
		YBWLIB2_API const IndexedDataRawValue* YBWLIB2_CALLTYPE GetRawValueByEntryID(const IndexedDataEntryID* _entryid) const noexcept;
		/// <summary>Gets a pointer to the raw value of the entry with the specified identifier in this store.</summary>
		/// <param name="_entryid">Pointer to the indexed data entry ID.</param>
		/// <returns>
		/// Returns a pointer to the raw value of the entry with the specified identifier.
		/// If there wasn't an entry with the specified identifier in this store, an empty pointer will be returned.
		/// The caller should NOT destruct or free the object pointed to by the returned pointer.
		/// </returns>
		YBWLIB2_API IndexedDataRawValue* YBWLIB2_CALLTYPE GetRawValueByEntryID(const IndexedDataEntryID* _entryid) noexcept;
		/// <summary>Adds an entry into this store.</summary>
		/// <param name="_entryid">Reference to the indexed data entry ID.</param>
		/// <param name="_rawval">Reference to the raw value of the entry to be added.</param>
		inline void AddEntry(const IndexedDataEntryID& _entryid, IndexedDataRawValue&& _rawval) noexcept { this->AddEntry(&_entryid, &_rawval); }
		/// <summary>Adds an entry into this store.</summary>
		/// <param name="_entryid">Pointer to the indexed data entry ID.</param>
		/// <param name="_rawval">
		/// Pointer to the raw value of the entry to be added.
		/// This function does NOT own the object pointed to by this pointer.
		/// However, this function move-constructs an object from the object pointed to by this pointer.
		/// </param>
		YBWLIB2_API void YBWLIB2_CALLTYPE AddEntry(const IndexedDataEntryID* _entryid, IndexedDataRawValue* _rawval) noexcept;
		/// <summary>Destructs and removes the entry with the specified identifier from this store.</summary>
		/// <param name="_entryid">Reference to the indexed data entry ID.</param>
		inline void RemoveEntryByEntryID(const IndexedDataEntryID& _entryid) noexcept { this->RemoveEntryByEntryID(&_entryid); }
		/// <summary>Destructs and removes the entry with the specified identifier from this store.</summary>
		/// <param name="_entryid">Pointer to the indexed data entry ID.</param>
		YBWLIB2_API void YBWLIB2_CALLTYPE RemoveEntryByEntryID(const IndexedDataEntryID* _entryid) noexcept;
	private:
		using value_map_entry_t = ::std::pair<const IndexedDataEntryID, IndexedDataRawValue>;
		using map_entry_t = ::std::unordered_map<IndexedDataEntryID, IndexedDataRawValue, hash<IndexedDataEntryID>, ::std::equal_to<IndexedDataEntryID>, allocator_rawallocator_t<value_map_entry_t>>;
		const rawallocator_t* rawallocator = nullptr;
		map_entry_t* map_entry = nullptr;
		YBWLIB2_API void YBWLIB2_CALLTYPE ConstructWithRawAllocator(const rawallocator_t* _rawallocator) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE MoveConstruct(IndexedDataStore* x) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Destruct() noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE MoveAssign(IndexedDataStore* x) noexcept;
	};
	static_assert(::std::is_standard_layout_v<IndexedDataStore>, "IndexedDataStore is not standard-layout.");

	//}
#pragma endregion Entries in IndexedDataStore have unique identifiers, so that custom entries may be added without changing the declaration or definition of the data store.

	class RawAllocatorParameterIndexedDataEntry final {
	public:
		static constexpr PersistentID persistentid_entryid = PersistentID(UUIDFromUUIDString_CompileTime("88817185-e459-4527-a44b-33621380b9a4"));
		static YBWLIB2_API IndexedDataEntryID entryid;
		inline static RawAllocatorParameterIndexedDataEntry* CopyFromStore(const IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				return new(_ptr_placement) RawAllocatorParameterIndexedDataEntry(*_indexeddatarawvalue);
			} else {
				return nullptr;
			}
		}
		static RawAllocatorParameterIndexedDataEntry CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static RawAllocatorParameterIndexedDataEntry* MoveFromStore(IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				RawAllocatorParameterIndexedDataEntry* ret = new(_ptr_placement) RawAllocatorParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue));
				_indexeddatastore.RemoveEntryByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
				return ret;
			} else {
				return nullptr;
			}
		}
		static RawAllocatorParameterIndexedDataEntry MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static void AddToStore(IndexedDataStore& _indexeddatastore, RawAllocatorParameterIndexedDataEntry&& _entry) noexcept {
			_indexeddatastore.AddEntry(RawAllocatorParameterIndexedDataEntry::entryid, static_cast<IndexedDataRawValue>(_entry));
		}
		inline static void RemoveFromStore(IndexedDataStore& _indexeddatastore) noexcept {
			_indexeddatastore.RemoveEntryByEntryID(RawAllocatorParameterIndexedDataEntry::entryid);
		}
		const rawallocator_t* rawalloctor = nullptr;
		inline explicit constexpr RawAllocatorParameterIndexedDataEntry(const rawallocator_t* _rawalloctor) noexcept : rawalloctor(_rawalloctor) {}
		inline constexpr RawAllocatorParameterIndexedDataEntry(const RawAllocatorParameterIndexedDataEntry& x) noexcept : rawalloctor(x.rawalloctor) {}
		inline constexpr RawAllocatorParameterIndexedDataEntry(RawAllocatorParameterIndexedDataEntry&& x) noexcept : rawalloctor(x.rawalloctor) {
			x.rawalloctor = nullptr;
		}
		inline ~RawAllocatorParameterIndexedDataEntry() {
			this->rawalloctor = nullptr;
		}
		inline RawAllocatorParameterIndexedDataEntry& operator=(const RawAllocatorParameterIndexedDataEntry& x) noexcept {
			this->rawalloctor = x.rawalloctor;
			return *this;
		}
		inline RawAllocatorParameterIndexedDataEntry& operator=(RawAllocatorParameterIndexedDataEntry&& x) noexcept {
			this->rawalloctor = x.rawalloctor;
			x.rawalloctor = nullptr;
			return *this;
		}
	private:
		inline explicit RawAllocatorParameterIndexedDataEntry(const IndexedDataRawValue& _indexeddatarawvalue) : rawalloctor(reinterpret_cast<const rawallocator_t*>(_indexeddatarawvalue.contextvalue)) {}
		inline explicit RawAllocatorParameterIndexedDataEntry(IndexedDataRawValue&& _indexeddatarawvalue) : rawalloctor(::std::move(reinterpret_cast<const rawallocator_t*>(_indexeddatarawvalue.contextvalue))) {
			_indexeddatarawvalue.contextvalue = 0;
		}
		inline operator IndexedDataRawValue() const noexcept { return IndexedDataRawValue(nullptr, reinterpret_cast<uintptr_t>(this->rawalloctor)); }
	};
	static_assert(::std::is_standard_layout_v<RawAllocatorParameterIndexedDataEntry>, "RawAllocatorParameterIndexedDataEntry is not standard-layout.");

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitModuleLocal() noexcept;
}

#endif
