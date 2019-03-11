#ifndef _INCLUDE_GUARD_0F846D3C_4297_4755_912A_2376A1CABD75
#define _INCLUDE_GUARD_0F846D3C_4297_4755_912A_2376A1CABD75

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include <cstdint>
#include <cstdlib>
#include <new>
#include <atomic>
#include "../YBWLib2Api.h"
#include "ExceptionLowLevel.h"
#include "Exception.h"

namespace YBWLib2 {
	class atomic_fnptr_wrap_function_catch_exceptions_raw_t final : public ::std::atomic<fnptr_wrap_function_catch_exceptions_raw_t> {
	public:
		inline atomic_fnptr_wrap_function_catch_exceptions_raw_t() noexcept = default;
		inline constexpr atomic_fnptr_wrap_function_catch_exceptions_raw_t(fnptr_wrap_function_catch_exceptions_raw_t _value) noexcept : atomic(_value) {}
	};

	static IException* YBWLIB2_CALLTYPE WrapFunctionCatchExceptionsRaw_Initial(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept;

	const size_t size_atomic_fnptr_wrap_function_catch_exceptions_raw = sizeof(atomic_fnptr_wrap_function_catch_exceptions_raw_t);
	static atomic_fnptr_wrap_function_catch_exceptions_raw_t atomic_fnptr_wrap_function_catch_exceptions_raw_module_local(&WrapFunctionCatchExceptionsRaw_Initial);
	atomic_fnptr_wrap_function_catch_exceptions_raw_t* const ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local = &atomic_fnptr_wrap_function_catch_exceptions_raw_module_local;
	thread_local atomic_fnptr_wrap_function_catch_exceptions_raw_t* ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_thread_local = ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local;

	atomic_fnptr_wrap_function_catch_exceptions_raw_t* ConstructRawWrapFunctionCatchExceptionsFnptrAtomic(
		void* _ptr_placement,
		fnptr_wrap_function_catch_exceptions_raw_t _fnptr_wrap_function_catch_exceptions_raw
	) noexcept {
		if (!_ptr_placement) abort();
		return new(_ptr_placement) atomic_fnptr_wrap_function_catch_exceptions_raw_t(_fnptr_wrap_function_catch_exceptions_raw);
	}

	void DestructRawWrapFunctionCatchExceptionsFnptrAtomic(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw
	) noexcept {
		if (!_ptr_atomic_fnptr_wrap_function_catch_exceptions_raw) abort();
		_ptr_atomic_fnptr_wrap_function_catch_exceptions_raw->~atomic_fnptr_wrap_function_catch_exceptions_raw_t();
	}

	fnptr_wrap_function_catch_exceptions_raw_t YBWLIB2_CALLTYPE GetRawWrapFunctionCatchExceptionsFnptr(
		const atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw
	) noexcept {
		if (!_ptr_atomic_fnptr_wrap_function_catch_exceptions_raw) abort();
		return static_cast<fnptr_wrap_function_catch_exceptions_raw_t>(*_ptr_atomic_fnptr_wrap_function_catch_exceptions_raw);
	}

	fnptr_wrap_function_catch_exceptions_raw_t YBWLIB2_CALLTYPE ExchangeRawWrapFunctionCatchExceptionsFnptr(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw,
		fnptr_wrap_function_catch_exceptions_raw_t _fnptr_wrap_function_catch_exceptions_raw_new
	) noexcept {
		if (!_ptr_atomic_fnptr_wrap_function_catch_exceptions_raw) abort();
		return _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw->exchange(_fnptr_wrap_function_catch_exceptions_raw_new);
	}

	atomic_fnptr_wrap_function_catch_exceptions_raw_t* YBWLIB2_CALLTYPE GetThreadLocalRawWrapFunctionCatchExceptionsFnptrAtomicPtr() noexcept {
		return ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_thread_local;
	}
	atomic_fnptr_wrap_function_catch_exceptions_raw_t* YBWLIB2_CALLTYPE ExchangeThreadLocalRawWrapFunctionCatchExceptionsFnptrAtomicPtr(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_new
	) noexcept {
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_old = ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_thread_local;
		ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_thread_local = _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_new;
		return _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_old;
	}

	ExceptionReturnParameterIndexedDataEntry ExceptionReturnParameterIndexedDataEntry::MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false) {
		IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid);
		if (_indexeddatarawvalue) {
			ExceptionReturnParameterIndexedDataEntry ret(ExceptionReturnParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue)));
			_indexeddatastore.RemoveEntryByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid);
			return ret;
		} else {
			throw(YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION());
		}
	}

	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealInitModuleLocal() noexcept {}

	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealUnInitModuleLocal() noexcept {}

	static IException* YBWLIB2_CALLTYPE WrapFunctionCatchExceptionsRaw_Initial(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept {
		if (!_fnptr_inner) abort();
		try {
			(*_fnptr_inner)(_context);
		} catch (...) {
			abort();
		}
		return nullptr;
	}
}

#endif
