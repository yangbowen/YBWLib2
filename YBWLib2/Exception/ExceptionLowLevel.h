#ifndef _INCLUDE_GUARD_5A563FBB_E8FB_48E1_8AAC_FC3EA9D2674A
#define _INCLUDE_GUARD_5A563FBB_E8FB_48E1_8AAC_FC3EA9D2674A

#include <cstdint>
#include <type_traits>
#include <memory>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"

namespace YBWLib2 {
	class IException;
	class atomic_fnptr_delete_iexception_t;
	class atomic_fnptr_wrap_function_catch_exceptions_raw_t;

	typedef void(YBWLIB2_CALLTYPE* fnptr_delete_iexception_t)(IException* _ptr) noexcept;
	extern YBWLIB2_API const size_t size_atomic_fnptr_delete_iexception;
	YBWLIB2_API atomic_fnptr_delete_iexception_t* YBWLIB2_CALLTYPE ConstructDeleteIExceptionFnptrAtomic(
		void* _ptr_placement,
		fnptr_delete_iexception_t _fnptr_delete_iexception
	) noexcept;
	YBWLIB2_API void YBWLIB2_CALLTYPE DestructDeleteIExceptionFnptrAtomic(
		atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception
	) noexcept;
	YBWLIB2_API fnptr_delete_iexception_t YBWLIB2_CALLTYPE GetDeleteIExceptionFnptr(
		const atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception
	) noexcept;
	YBWLIB2_API fnptr_delete_iexception_t YBWLIB2_CALLTYPE ExchangeDeleteIExceptionFnptr(
		atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception,
		fnptr_delete_iexception_t _fnptr_delete_iexception_new
	) noexcept;
	extern YBWLIB2_API atomic_fnptr_delete_iexception_t* const ptr_atomic_fnptr_delete_iexception_global;

	typedef IException*(YBWLIB2_CALLTYPE* fnptr_wrap_function_catch_exceptions_raw_t)(void(YBWLIB2_CALLTYPE* _fnptr_inner)(uintptr_t _context), uintptr_t _context) noexcept;
	extern const size_t size_atomic_fnptr_wrap_function_catch_exceptions_raw;
	atomic_fnptr_wrap_function_catch_exceptions_raw_t* ConstructRawWrapFunctionCatchExceptionsFnptrAtomic(
		void* _ptr_placement,
		fnptr_wrap_function_catch_exceptions_raw_t _fnptr_wrap_function_catch_exceptions_raw
	) noexcept;
	void DestructRawWrapFunctionCatchExceptionsFnptrAtomic(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw
	) noexcept;
	fnptr_wrap_function_catch_exceptions_raw_t YBWLIB2_CALLTYPE GetRawWrapFunctionCatchExceptionsFnptr(
		const atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw
	) noexcept;
	fnptr_wrap_function_catch_exceptions_raw_t YBWLIB2_CALLTYPE ExchangeRawWrapFunctionCatchExceptionsFnptr(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw,
		fnptr_wrap_function_catch_exceptions_raw_t _fnptr_wrap_function_catch_exceptions_raw_new
	) noexcept;
	extern atomic_fnptr_wrap_function_catch_exceptions_raw_t* const ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_module_local;
	atomic_fnptr_wrap_function_catch_exceptions_raw_t* YBWLIB2_CALLTYPE GetThreadLocalRawWrapFunctionCatchExceptionsFnptrAtomicPtr() noexcept;
	atomic_fnptr_wrap_function_catch_exceptions_raw_t* YBWLIB2_CALLTYPE ExchangeThreadLocalRawWrapFunctionCatchExceptionsFnptrAtomicPtr(
		atomic_fnptr_wrap_function_catch_exceptions_raw_t* _ptr_atomic_fnptr_wrap_function_catch_exceptions_raw_new
	) noexcept;

	inline void DeleteIException(IException* _ptr) noexcept {
		fnptr_delete_iexception_t fnptr_delete_iexception = GetDeleteIExceptionFnptr(ptr_atomic_fnptr_delete_iexception_global);
		if (!fnptr_delete_iexception) abort();
		(*fnptr_delete_iexception)(_ptr);
	}

	template<typename T_Callable>
	inline IException* WrapFunctionCatchExceptions(T_Callable _callable) noexcept {
		static_assert(::std::is_invocable_r_v<void, T_Callable>, "The callable value is invalid.");
		if constexpr (::std::is_nothrow_invocable_r_v<void, T_Callable>) {
			_callable();
			return nullptr;
		} else {
			::std::add_pointer_t<T_Callable> ptr_callable = ::std::addressof(_callable);
			const atomic_fnptr_wrap_function_catch_exceptions_raw_t* ptr_atomic_fnptr_wrap_function_catch_exceptions_raw = GetThreadLocalRawWrapFunctionCatchExceptionsFnptrAtomicPtr();
			if (!ptr_atomic_fnptr_wrap_function_catch_exceptions_raw) abort();
			fnptr_wrap_function_catch_exceptions_raw_t fnptr_wrap_function_catch_exceptions_raw = GetRawWrapFunctionCatchExceptionsFnptr(ptr_atomic_fnptr_wrap_function_catch_exceptions_raw);
			if (!fnptr_wrap_function_catch_exceptions_raw) abort();
			return (*fnptr_wrap_function_catch_exceptions_raw)(
				[](uintptr_t _context) {
					::std::add_pointer_t<T_Callable> ptr_callable = reinterpret_cast<::std::add_pointer_t<T_Callable>>(_context);
					(*ptr_callable)();
				}, reinterpret_cast<uintptr_t>(ptr_callable));
		}
	}

	class ExceptionReturnParameterIndexedDataEntry final {
	public:
		static constexpr PersistentID persistentid_entryid = PersistentID(UUIDFromUUIDString_CompileTime("6a63caff-efc1-4a3f-adf0-43b506e2f787"));
		static YBWLIB2_API IndexedDataEntryID entryid;
		inline static ExceptionReturnParameterIndexedDataEntry* MoveFromStore(IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				ExceptionReturnParameterIndexedDataEntry* ret = new(_ptr_placement) ExceptionReturnParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue));
				_indexeddatastore.RemoveEntryByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid);
				return ret;
			} else {
				return nullptr;
			}
		}
		static ExceptionReturnParameterIndexedDataEntry MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static void AddToStore(IndexedDataStore& _indexeddatastore, ExceptionReturnParameterIndexedDataEntry&& _entry) noexcept {
			_indexeddatastore.AddEntry(ExceptionReturnParameterIndexedDataEntry::entryid, static_cast<IndexedDataRawValue>(_entry));
		}
		inline static void RemoveFromStore(IndexedDataStore& _indexeddatastore) noexcept {
			_indexeddatastore.RemoveEntryByEntryID(ExceptionReturnParameterIndexedDataEntry::entryid);
		}
		IException* exception = nullptr;
		inline explicit constexpr ExceptionReturnParameterIndexedDataEntry(IException*&& _exception) noexcept : exception(_exception) {
			_exception = nullptr;
		}
		ExceptionReturnParameterIndexedDataEntry(const ExceptionReturnParameterIndexedDataEntry&) = delete;
		inline constexpr ExceptionReturnParameterIndexedDataEntry(ExceptionReturnParameterIndexedDataEntry&& x) noexcept : exception(x.exception) {
			x.exception = nullptr;
		}
		inline ~ExceptionReturnParameterIndexedDataEntry() {
			if (this->exception) {
				DeleteIException(this->exception);
				this->exception = nullptr;
			}
		}
		ExceptionReturnParameterIndexedDataEntry& operator=(const ExceptionReturnParameterIndexedDataEntry&) = delete;
		inline ExceptionReturnParameterIndexedDataEntry& operator=(ExceptionReturnParameterIndexedDataEntry&& x) noexcept {
			if (this->exception) {
				DeleteIException(this->exception);
				this->exception = nullptr;
			}
			this->exception = ::std::move(x.exception);
			x.exception = nullptr;
			return *this;
		}
	private:
		inline explicit ExceptionReturnParameterIndexedDataEntry(IndexedDataRawValue&& _indexeddatarawvalue) : exception(::std::move(reinterpret_cast<IException*>(_indexeddatarawvalue.contextvalue))) {
			_indexeddatarawvalue.contextvalue = 0;
			_indexeddatarawvalue.fnptr_cleanup = nullptr;
		}
		inline operator IndexedDataRawValue() noexcept {
			IException* _exception = this->exception;
			this->exception = nullptr;
			return IndexedDataRawValue(
				[](IndexedDataRawValue* _indexeddatarawvalue) noexcept->void {
					if (_indexeddatarawvalue && _indexeddatarawvalue->contextvalue) {
						DeleteIException(reinterpret_cast<IException*>(_indexeddatarawvalue->contextvalue));
						_indexeddatarawvalue->contextvalue = 0;
					}
				}, reinterpret_cast<uintptr_t>(_exception));
		}
	};
	static_assert(::std::is_standard_layout_v<ExceptionReturnParameterIndexedDataEntry>, "ExceptionReturnParameterIndexedDataEntry is not standard-layout.");

	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealUnInitModuleLocal() noexcept;
}

#endif
