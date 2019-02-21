﻿#ifndef _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766
#define _INCLUDE_GUARD_DF823B1A_4110_4426_9366_DF218B32B766

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <utility>
#include <new>
#include <typeinfo>
#include "../YBWLib2Api.h"

namespace YBWLib2 {
	struct UUID;

#define YBWLIB2_STRINGIZE_HELPER(x) #x
#define YBWLIB2_STRINGIZE(x) YBWLIB2_STRINGIZE_HELPER(x)

#define YBWLIB2_CONCATENATE_HELPER(l, r) a ## b
#define YBWLIB2_CONCATENATE(l, r) YBWLIB2_CONCATENATE_HELPER(l, r)

#define YBWLIB2_TO_UTF8_HELPER(s) u8 ## s
#define YBWLIB2_TO_UTF8(s) YBWLIB2_TO_UTF8_HELPER(s)

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
	static_assert(::std::is_pod_v<dummy_t>, "dummy_t is not POD.");
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

#pragma region UUID
	//{ UUID

	/// <summary>Universally unique identifier.</summary>
	struct UUID {
		/// <summary>An equal-to comparing function for <c>UUID</c>.</summary>
		static inline bool IsEqualTo(const UUID* l, const UUID* r) noexcept {
			if constexpr (sizeof(UUID) % sizeof(uintptr_t)) {
				for (size_t i = 0; i < sizeof(UUID) / sizeof(uint8_t); ++i) if (l->data[i] != r->data[i]) return false;
				return true;
			} else {
				for (size_t i = 0; i < sizeof(UUID) / sizeof(uintptr_t); ++i) if (reinterpret_cast<const uintptr_t*>(l)[i] != reinterpret_cast<const uintptr_t*>(r)[i]) return false;
				return true;
			}
		}
		/// <summary>
		/// A less-than comparing function for <c>UUID</c>.
		/// The behaviour is equivalent to comparing the binary representation of the <c>UUID</c> from byte to byte lexicographically.
		/// </summary>
		static inline bool IsLessThan(const UUID* l, const UUID* r) noexcept {
			for (int i = 0; i < sizeof(UUID) / sizeof(uint8_t); ++i) {
				if (reinterpret_cast<const uint8_t*>(l)[i] < reinterpret_cast<const uint8_t*>(r)[i]) return true;
				if (reinterpret_cast<const uint8_t*>(l)[i] != reinterpret_cast<const uint8_t*>(r)[i]) return false;
			}
			return false;
		}
		/// <summary>A secure version of <c>IsEqualTo_UUID</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
		static inline bool SecureIsEqualTo(const UUID* l, const UUID* r) noexcept {
			if constexpr (sizeof(UUID) % sizeof(uintptr_t)) {
				uint8_t x = 0;
				for (size_t i = 0; i < sizeof(UUID) / sizeof(uint8_t); ++i) x |= l->data[i] ^ r->data[i];
				return !x;
			} else {
				uintptr_t x = 0;
				for (size_t i = 0; i < sizeof(UUID) / sizeof(uintptr_t); ++i) x |= reinterpret_cast<const uintptr_t*>(l)[i] ^ reinterpret_cast<const uintptr_t*>(r)[i];
				return !x;
			}
		}
		uint8_t data[0x10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		inline bool operator==(const UUID& r) const { return UUID::IsEqualTo(this, &r); }
		inline bool operator!=(const UUID& r) const { return !UUID::IsEqualTo(this, &r); }
		inline bool operator<(const UUID& r) const { return UUID::IsLessThan(this, &r); }
		inline bool operator<=(const UUID& r) const { return !UUID::IsLessThan(&r, this); }
		inline bool operator>(const UUID& r) const { return UUID::IsLessThan(&r, this); }
		inline bool operator>=(const UUID& r) const { return !UUID::IsLessThan(this, &r); }
		inline size_t hash() const { return hash_trivially_copyable_t<UUID, size_t>()(*this); }
	};
	static_assert(::std::is_standard_layout_v<UUID>, "UUID is not standard-layout.");
	/// <summary>An equal-to comparing function for <c>UUID</c>.</summary>
	inline bool IsEqualTo_UUID(const UUID* l, const UUID* r) noexcept { return UUID::IsEqualTo(l, r); }
	/// <summary>
	/// A less-than comparing function for <c>UUID</c>.
	/// The behaviour is equivalent to comparing the binary representation of the <c>UUID</c> from byte to byte lexicographically.
	/// </summary>
	inline bool IsLessThan_UUID(const UUID* l, const UUID* r) { return UUID::IsLessThan(l, r); }
	/// <summary>A secure version of <c>IsEqualTo_UUID</c> that does not leak information about the length before the first mismatch is found through execution time.</summary>
	inline bool SecureIsEqualTo_UUID(const UUID* l, const UUID* r) { return UUID::SecureIsEqualTo(l, r); }

	struct hash_UUID_t {
		inline size_t operator()(const UUID& t) const {
			return t.hash();
		}
	};
	constexpr hash_UUID_t hash_UUID {};
	/// <summary>A null <c>UUID</c>.</summary>
	constexpr UUID UUID_Null = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	/// <summary>Converts a UUID string in the format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX to a <c>UUID</c> identifier at compile time.</summary>
	inline constexpr UUID UUIDFromUUIDString_CompileTime(const char(&str)[37]) {
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

	//}
#pragma endregion Universally unique identifier.

	/// <summary>An allocator for allocating raw memory.</summary>
	struct rawallocator_t final {
		/// <summary>Function pointer type for allocating raw memory.</summary>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <param name="context">A context value associated to the <c>rawallocator_t</c> object.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the allocated memory is returned.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		typedef void* (YBWLIB2_CALLTYPE* fnptr_allocate_t)(size_t size, uintptr_t context) noexcept;
		/// <summary>Function pointer type for deallocating raw memory.</summary>
		/// <param name="ptr">
		/// A pointer to some memory previously allocated by the same <c>IRawAllocator</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function succeeds without doing anything.
		/// </param>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <param name="context">A context value associated to the <c>rawallocator_t</c> object.</param>
		/// <returns>Whether the call has succeeded.</returns>
		typedef bool (YBWLIB2_CALLTYPE* fnptr_deallocate_t)(void* ptr, size_t size, uintptr_t context) noexcept;
		/// <summary>Function pointer type for getting the maximum amount of memory that could potentially be allocated by this raw memory allocator.</summary>
		/// <returns>
		/// The maximum amount of memory that could potentially be allocated by this raw memory allocator.
		/// Memory allocations within this limit can still fail.
		/// </returns>
		typedef size_t(YBWLIB2_CALLTYPE* fnptr_get_max_size_t)(uintptr_t context) noexcept;
		fnptr_allocate_t fnptr_allocate = nullptr;
		fnptr_deallocate_t fnptr_deallocate = nullptr;
		fnptr_get_max_size_t fnptr_get_max_size = nullptr;
		uintptr_t context = 0;
		inline constexpr rawallocator_t(fnptr_allocate_t _fnptr_allocate, fnptr_deallocate_t _fnptr_deallocate, fnptr_get_max_size_t _fnptr_get_max_size, uintptr_t _context = 0) noexcept
			: fnptr_allocate(_fnptr_allocate), fnptr_deallocate(_fnptr_deallocate), fnptr_get_max_size(_fnptr_get_max_size), context(_context) {}
		/// <summary>Allocates some memory.</summary>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <returns>
		/// If the call has succeeded, a pointer to the allocated memory is returned.
		/// Otherwise, an empty pointer is returned.
		/// </returns>
		[[nodiscard]] inline void* Allocate(size_t size) const noexcept { return this->fnptr_allocate ? (*this->fnptr_allocate)(size, this->context) : nullptr; }
		/// <summary>Deallocates some memory.</summary>
		/// <param name="ptr">
		/// A pointer to some memory previously allocated by the same <c>IRawAllocator</c> object and not deallocated yet.
		/// If an empty pointer is passed, this function succeeds without doing anything.
		/// </param>
		/// <param name="size">The size, in bytes, of the memory.</param>
		/// <returns>Whether the call has succeeded.</returns>
		inline bool Deallocate(void* ptr, size_t size) const noexcept { return this->fnptr_deallocate ? (*this->fnptr_deallocate)(ptr, size, this->context) : false; }
		/// <summary>Gets the maximum amount of memory that could potentially be allocated by this raw memory allocator.</summary>
		/// <returns>
		/// The maximum amount of memory that could potentially be allocated by this raw memory allocator.
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
		const rawallocator_t* const rawallocator;
		inline constexpr allocator_rawallocator_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {
			if (!_rawallocator) abort();
		}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
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
			pointer ptr = reinterpret_cast<pointer>(this->rawallocator->Allocate(count * sizeof(value_type)));
			if (!ptr) throw(::std::bad_alloc());
			return reinterpret_cast<pointer>(ptr);
		}
		inline void deallocate(pointer ptr, size_type count) const noexcept {
			static_cast<void>(count);
			if (!this->rawallocator->Deallocate(ptr, count * sizeof(value_type))) abort();
		}
		inline size_type max_size() const noexcept { return this->rawallocator->GetMaxSize(); }
		template<typename _Element_Ty, typename... _Args_Ty>
		inline void construct(_Element_Ty* ptr, _Args_Ty&&... args) {
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty>(args)...);
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline constexpr allocator_rawallocator_t select_on_container_copy_construction() const noexcept { return allocator_rawallocator_t(*this); }
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
		const rawallocator_t* const rawallocator;
		inline constexpr allocator_rawallocator_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {
			if (!_rawallocator) abort();
		}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(const allocator_rawallocator_t<_Rebind_From_Ty>& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
		template<typename _Rebind_From_Ty>
		inline constexpr allocator_rawallocator_t(allocator_rawallocator_t<_Rebind_From_Ty>&& x) noexcept : allocator_rawallocator_t(x.rawallocator) {}
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
			new (const_cast<void*>(static_cast<const volatile void*>(ptr))) _Element_Ty(::std::forward<_Args_Ty...>(args...));
		}
		template<typename _Element_Ty>
		inline void destroy(_Element_Ty* ptr) {
			ptr->~_Element_Ty();
		}
		inline constexpr allocator_rawallocator_t select_on_container_copy_construction() const noexcept { return allocator_rawallocator_t(*this); }
	};

	/// <summary>A raw memory allocator that uses the CRT <c>malloc</c> and <c>free</c> functions provided by the CRT of the executable module that contains this reference to this variable.</summary>
	extern rawallocator_t* rawallocator_crt_module_local;
	/// <summary>A raw memory allocator that uses the CRT <c>malloc</c> and <c>free</c> functions provided by the CRT of YBWLib2.</summary>
	extern YBWLIB2_API rawallocator_t* rawallocator_crt_YBWLib2;

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
		fnptr_is_equal_to_t fnptr_is_equal_to = nullptr;
		fnptr_is_less_than_t fnptr_is_less_than = nullptr;
		const module_info_t* module_info = nullptr;
		uintptr_t context = 0;
		inline constexpr wrapper_type_info_t(
			fnptr_is_equal_to_t _fnptr_is_equal_to,
			fnptr_is_less_than_t _fnptr_is_less_than,
			const module_info_t* _module_info,
			uintptr_t _context
		) noexcept
			: fnptr_is_equal_to(_fnptr_is_equal_to),
			fnptr_is_less_than(_fnptr_is_less_than),
			module_info(_module_info),
			context(_context) {}
		inline wrapper_type_info_t(const ::std::type_info& val_type_info) noexcept
			: fnptr_is_equal_to(wrapper_type_info_t::IsEqualTo_TypeInfo),
			fnptr_is_less_than(wrapper_type_info_t::IsLessThan_TypeInfo),
			module_info(module_info_current),
			context(reinterpret_cast<uintptr_t>(&val_type_info)) {}
	protected:
		/// <summary>Checks type equivalence for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static bool YBWLIB2_CALLTYPE IsEqualTo_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
		/// <summary>Checks type precedence for <c>wrapper_type_info_t</c> objects constructed using <c>const ::std::type_info&</c>.</summary>
		static bool YBWLIB2_CALLTYPE IsLessThan_TypeInfo(const wrapper_type_info_t* l, const wrapper_type_info_t* r) noexcept;
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

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitModuleLocal() noexcept;
}

#endif