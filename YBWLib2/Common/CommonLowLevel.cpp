#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "CommonLowLevel.h"

namespace YBWLib2 {
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
			this->map_entry = reinterpret_cast<map_entry_t*>(this->rawallocator->Allocate(sizeof(map_entry_t)));
			if (!this->map_entry) abort();
			this->map_entry = ::std::launder(new (this->map_entry) map_entry_t(allocator_rawallocator_t<value_map_entry_t>(this->rawallocator)));
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
				if (!this->rawallocator->Deallocate(this->map_entry, sizeof(map_entry_t))) abort();
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
				if (!this->rawallocator->Deallocate(this->map_entry, sizeof(map_entry_t))) abort();
				this->map_entry = nullptr;
			}
			this->rawallocator = x->rawallocator;
			x->rawallocator = nullptr;
			if (!this->map_entry && x->map_entry) {
				this->map_entry = reinterpret_cast<map_entry_t*>(this->rawallocator->Allocate(sizeof(map_entry_t)));
				if (!this->map_entry) abort();
			}
			if (x->map_entry) {
				this->map_entry = ::std::launder(new (this->map_entry) map_entry_t(::std::move(*x->map_entry), allocator_rawallocator_t<value_map_entry_t>(this->rawallocator)));
				x->map_entry->~map_entry_t();
				if (!x->rawallocator->Deallocate(x->map_entry, sizeof(map_entry_t))) abort();
				x->map_entry = nullptr;
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealInitGlobal() noexcept {
		rawallocator_crt_YBWLib2 = new rawallocator_t(
			[](size_t size, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				if (!size) size = 1;
				return malloc(size);
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->bool {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) free(ptr);
				return true;
			},
				[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return SIZE_MAX;
			});
	}

	void YBWLIB2_CALLTYPE CommonLowLevel_RealUnInitGlobal() noexcept {
		delete rawallocator_crt_YBWLib2;
		rawallocator_crt_YBWLib2 = nullptr;
	}
}
