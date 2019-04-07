﻿#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "CommonLowLevel.h"

namespace YBWLib2 {
	YBWLIB2_API byte_order_t<unsigned char>* byte_order_unsigned_char = nullptr;
	YBWLIB2_API byte_order_t<unsigned short>* byte_order_unsigned_short = nullptr;
	YBWLIB2_API byte_order_t<unsigned int>* byte_order_unsigned_int = nullptr;
	YBWLIB2_API byte_order_t<unsigned long>* byte_order_unsigned_long = nullptr;
	YBWLIB2_API byte_order_t<unsigned long long>* byte_order_unsigned_long_long = nullptr;
	YBWLIB2_API bool* is_byte_order_le = nullptr;
	YBWLIB2_API bool* is_byte_order_be = nullptr;
	YBWLIB2_API dummy_t dummy;
	YBWLIB2_API rawallocator_t* rawallocator_crt_YBWLib2 = nullptr;

	YBWLIB2_API const IndexedDataRawValue* YBWLIB2_CALLTYPE IndexedDataStore::GetRawValueByEntryID(const IndexedDataEntryID* _entryid) const noexcept {
		if (!_entryid) abort();
		const IndexedDataRawValue* rawval = nullptr;
		try {
			map_entry_t::const_iterator it_map_entry = this->map_entry->find(*_entryid);
			if (it_map_entry != this->map_entry->cend()) rawval = &it_map_entry->second;
		} catch (...) {
			abort();
		}
		return rawval;
	}

	YBWLIB2_API IndexedDataRawValue* YBWLIB2_CALLTYPE IndexedDataStore::GetRawValueByEntryID(const IndexedDataEntryID* _entryid) noexcept {
		if (!_entryid) abort();
		IndexedDataRawValue* rawval = nullptr;
		try {
			map_entry_t::iterator it_map_entry = this->map_entry->find(*_entryid);
			if (it_map_entry != this->map_entry->end()) rawval = &it_map_entry->second;
		} catch (...) {
			abort();
		}
		return rawval;
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::AddEntry(const IndexedDataEntryID* _entryid, IndexedDataRawValue* _rawval) noexcept {
		try {
			if (!_entryid || !_rawval) abort();
			if (!this->map_entry->emplace(*_entryid, ::std::move(*_rawval)).second)
				abort();
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::RemoveEntryByEntryID(const IndexedDataEntryID* _entryid) noexcept {
		try {
			if (!_entryid) abort();
			if (!this->map_entry->erase(*_entryid))
				abort();
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::ConstructWithRawAllocator(const rawallocator_t* _rawallocator) noexcept {
		try {
			if (!_rawallocator) abort();
			this->rawallocator = _rawallocator;
			this->map_entry = reinterpret_cast<map_entry_t*>(this->rawallocator->Allocate(sizeof(map_entry_t), alignof(map_entry_t)));
			if (!this->map_entry) abort();
			this->map_entry = ::std::launder(new (this->map_entry) map_entry_t(allocator_rawallocator_t<value_map_entry_t>(*this->rawallocator)));
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::MoveConstruct(IndexedDataStore* x) noexcept {
		if (!x) abort();
		if (x->rawallocator) {
			this->rawallocator = x->rawallocator;
			x->rawallocator = nullptr;
		}
		if (x->map_entry) {
			this->map_entry = x->map_entry;
			x->map_entry = nullptr;
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::Destruct() noexcept {
		try {
			if (this->map_entry) {
				this->map_entry->~map_entry_t();
				this->rawallocator->Deallocate(this->map_entry, sizeof(map_entry_t));
				this->map_entry = nullptr;
			}
		} catch (...) {
			abort();
		}
	}

	YBWLIB2_API void YBWLIB2_CALLTYPE IndexedDataStore::MoveAssign(IndexedDataStore* x) noexcept {
		try {
			if (this->map_entry) {
				this->map_entry->~map_entry_t();
			}
			if (this->map_entry && (!x->map_entry || this->rawallocator != x->rawallocator)) {
				this->rawallocator->Deallocate(this->map_entry, sizeof(map_entry_t));
				this->map_entry = nullptr;
			}
			this->rawallocator = x->rawallocator;
			x->rawallocator = nullptr;
			if (!this->map_entry && x->map_entry) {
				this->map_entry = reinterpret_cast<map_entry_t*>(this->rawallocator->Allocate(sizeof(map_entry_t), alignof(map_entry_t)));
				if (!this->map_entry) abort();
			}
			if (x->map_entry) {
				this->map_entry = ::std::launder(new (this->map_entry) map_entry_t(::std::move(*x->map_entry), allocator_rawallocator_t<value_map_entry_t>(*this->rawallocator)));
				x->map_entry->~map_entry_t();
				x->rawallocator->Deallocate(x->map_entry, sizeof(map_entry_t));
				x->map_entry = nullptr;
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept {
		byte_order_unsigned_char = new byte_order_t<unsigned char>();
		byte_order_unsigned_short = new byte_order_t<unsigned short>();
		byte_order_unsigned_int = new byte_order_t<unsigned int>();
		byte_order_unsigned_long = new byte_order_t<unsigned long>();
		byte_order_unsigned_long_long = new byte_order_t<unsigned long long>();
		is_byte_order_le = new bool(true);
		is_byte_order_be = new bool(true);
		if (!byte_order_unsigned_char->is_le) *is_byte_order_le = false;
		if (!byte_order_unsigned_char->is_be) *is_byte_order_be = false;
		if (!byte_order_unsigned_short->is_le) *is_byte_order_le = false;
		if (!byte_order_unsigned_short->is_be) *is_byte_order_be = false;
		if (!byte_order_unsigned_int->is_le) *is_byte_order_le = false;
		if (!byte_order_unsigned_int->is_be) *is_byte_order_be = false;
		if (!byte_order_unsigned_long->is_le) *is_byte_order_le = false;
		if (!byte_order_unsigned_long->is_be) *is_byte_order_be = false;
		if (!byte_order_unsigned_long_long->is_le) *is_byte_order_le = false;
		if (!byte_order_unsigned_long_long->is_be) *is_byte_order_be = false;
		rawallocator_crt_YBWLib2 = new rawallocator_t(
			nullptr, nullptr, nullptr,
			[](size_t size, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
				if (!size) size = align;
				void* ptr_allocated = malloc(size + sizeof(void**) + align - 1);
				if (!ptr_allocated) abort();
				void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
				if (!ptr_allocdata) abort();
				*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
				return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->void {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) {
					void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr) - 1);
					void* ptr_allocated = *reinterpret_cast<void**>(ptr_allocdata);
					if (!ptr_allocated) abort();
					free(ptr_allocated);
				}
			},
			[](void* ptr_old, size_t size_old, size_t size_new, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(size_old);
				static_cast<void>(context);
				align = least_common_multiple_optimized1<size_t, 0x10, alignof(void*)>(align);
				if (!size_new) size_new = align;
				if (ptr_old) {
					void* ptr_allocdata_old = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_old) - 1);
					void* ptr_allocated_old = *reinterpret_cast<void**>(ptr_allocdata_old);
					if (!ptr_allocated_old || ptr_allocated_old > ptr_allocdata_old) abort();
					size_t offset_allocdata_old = reinterpret_cast<uintptr_t>(ptr_allocdata_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
					size_t offset_old = reinterpret_cast<uintptr_t>(ptr_old) - reinterpret_cast<uintptr_t>(ptr_allocated_old);
					void* ptr_allocated_new = realloc(ptr_allocated_old, size_new + sizeof(void**) + align - 1);
					if (!ptr_allocated_new) abort();
					void* ptr_allocdata_new = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated_new) + (sizeof(void*) - 1)), align) - 1);
					void* ptr_new = reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata_new) + 1);
					if (ptr_allocdata_new != reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + offset_allocdata_old)) {
						memmove(ptr_new, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated_new) + offset_old), size_new < size_old ? size_new : size_old);
						*reinterpret_cast<void**>(ptr_allocdata_new) = ptr_allocated_new;
						return ptr_new;
					} else {
						*reinterpret_cast<void**>(ptr_allocdata_new) = ptr_allocated_new;
						return ptr_new;
					}
				} else {
					void* ptr_allocated = malloc(size_new + sizeof(void**) + align - 1);
					if (!ptr_allocated) abort();
					void* ptr_allocdata = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr_allocated) + align - mod_alignment((reinterpret_cast<uintptr_t>(ptr_allocated) + (sizeof(void*) - 1)), align) - 1);
					if (!ptr_allocdata) abort();
					*reinterpret_cast<void**>(ptr_allocdata) = ptr_allocated;
					return reinterpret_cast<void*>(reinterpret_cast<void**>(ptr_allocdata) + 1);
				}
			},
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return SIZE_MAX;
			});
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept {
		delete rawallocator_crt_YBWLib2;
		rawallocator_crt_YBWLib2 = nullptr;
		delete is_byte_order_be;
		is_byte_order_be = nullptr;
		delete is_byte_order_le;
		is_byte_order_le = nullptr;
		delete byte_order_unsigned_long_long;
		byte_order_unsigned_long_long = nullptr;
		delete byte_order_unsigned_long;
		byte_order_unsigned_long = nullptr;
		delete byte_order_unsigned_int;
		byte_order_unsigned_int = nullptr;
		delete byte_order_unsigned_short;
		byte_order_unsigned_short = nullptr;
		delete byte_order_unsigned_char;
		byte_order_unsigned_char = nullptr;
	}
}
