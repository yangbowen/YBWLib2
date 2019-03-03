#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "ExceptionLowLevel.h"

namespace YBWLib2 {
	class atomic_fnptr_delete_iexception_t final : public ::std::atomic<fnptr_delete_iexception_t> {
	public:
		inline atomic_fnptr_delete_iexception_t() noexcept = default;
		inline constexpr atomic_fnptr_delete_iexception_t(fnptr_delete_iexception_t _value) noexcept : atomic(_value) {}
	};

	static void YBWLIB2_CALLTYPE DeleteIException_Initial(IException* _ptr) noexcept;

	YBWLIB2_API const size_t size_atomic_fnptr_delete_iexception = sizeof(atomic_fnptr_delete_iexception_t);
	atomic_fnptr_delete_iexception_t atomic_fnptr_delete_iexception_global(&DeleteIException_Initial);
	YBWLIB2_API atomic_fnptr_delete_iexception_t* const ptr_atomic_fnptr_delete_iexception_global = &atomic_fnptr_delete_iexception_global;

	atomic_fnptr_delete_iexception_t* ConstructDeleteIExceptionFnptrAtomic(
		void* _ptr_placement,
		fnptr_delete_iexception_t _fnptr_delete_iexception
	) noexcept {
		if (!_ptr_placement) abort();
		return new(_ptr_placement) atomic_fnptr_delete_iexception_t(_fnptr_delete_iexception);
	}

	void DestructDeleteIExceptionFnptrAtomic(
		atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception
	) noexcept {
		if (!_ptr_atomic_fnptr_delete_iexception) abort();
		_ptr_atomic_fnptr_delete_iexception->~atomic_fnptr_delete_iexception_t();
	}

	fnptr_delete_iexception_t YBWLIB2_CALLTYPE GetDeleteIExceptionFnptr(
		const atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception
	) noexcept {
		if (!_ptr_atomic_fnptr_delete_iexception) abort();
		return static_cast<fnptr_delete_iexception_t>(*_ptr_atomic_fnptr_delete_iexception);
	}

	fnptr_delete_iexception_t YBWLIB2_CALLTYPE ExchangeDeleteIExceptionFnptr(
		atomic_fnptr_delete_iexception_t* _ptr_atomic_fnptr_delete_iexception,
		fnptr_delete_iexception_t _fnptr_delete_iexception_new
	) noexcept {
		if (!_ptr_atomic_fnptr_delete_iexception) abort();
		return _ptr_atomic_fnptr_delete_iexception->exchange(_fnptr_delete_iexception_new);
	}

	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE ExceptionLowLevel_RealUnInitGlobal() noexcept {}

	static void YBWLIB2_CALLTYPE DeleteIException_Initial(IException* _ptr) noexcept {
		static_cast<void>(_ptr);
		abort();
	}
}
