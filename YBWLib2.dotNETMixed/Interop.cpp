#include "pch.h"

#pragma managed(push, off)

#include <objbase.h>
#include "YBWLib2dotNETMixedApi.h"

#pragma managed(pop)

#pragma managed(push, on)

#include "Interop.h"

namespace YBWLib2::dotNETMixed {
	inline static System::Runtime::InteropServices::GCHandleType GCHandleType_ToManaged(GCHandleType _gchandletype) noexcept {
		switch (_gchandletype) {
		case GCHandleType::Weak:
			return System::Runtime::InteropServices::GCHandleType::Weak;
		case GCHandleType::WeakTrackResurrection:
			return System::Runtime::InteropServices::GCHandleType::WeakTrackResurrection;
		case GCHandleType::Normal:
			return System::Runtime::InteropServices::GCHandleType::Normal;
		case GCHandleType::Pinned:
			return System::Runtime::InteropServices::GCHandleType::Pinned;
		default:
			assert(false); abort();
		}
	}

	namespace Internal {
		YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE FreeGCHandle_IntPtr(intptr_t _intptr_gchandle) noexcept {
			if (!_intptr_gchandle) return;
			System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(_intptr_gchandle)).Free();
		}

		YBWLIB2DOTNETMIXED_API intptr_t YBWLIB2DOTNETMIXED_CALLTYPE CopyGCHandle_IntPtr(intptr_t _intptr_gchandle, GCHandleType _gchandletype) noexcept {
			if (!_intptr_gchandle) return 0;
			System::Runtime::InteropServices::GCHandle gchandle_from = System::Runtime::InteropServices::GCHandle::FromIntPtr(static_cast<System::IntPtr>(_intptr_gchandle));
			System::Object^ managedobject = gchandle_from.Target;
			return static_cast<intptr_t>(System::Runtime::InteropServices::GCHandle::ToIntPtr(System::Runtime::InteropServices::GCHandle::Alloc(managedobject, GCHandleType_ToManaged(_gchandletype))));
		}

		YBWLIB2DOTNETMIXED_API intptr_t YBWLIB2DOTNETMIXED_CALLTYPE MoveGCHandle_IntPtr(intptr_t _intptr_gchandle, GCHandleType _gchandletype) noexcept {
			if (!_intptr_gchandle) return 0;
			System::Runtime::InteropServices::GCHandle gchandle_from = System::Runtime::InteropServices::GCHandle::FromIntPtr(static_cast<System::IntPtr>(_intptr_gchandle));
			System::Object^ managedobject = gchandle_from.Target;
			gchandle_from.Free();
			return static_cast<intptr_t>(System::Runtime::InteropServices::GCHandle::ToIntPtr(System::Runtime::InteropServices::GCHandle::Alloc(managedobject, GCHandleType_ToManaged(_gchandletype))));
		}
	}
	System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandleRef::get() const {
		if (!this->get_intptr()) return nullptr;
		return System::Runtime::InteropServices::GCHandle::FromIntPtr(static_cast<System::IntPtr>(this->get_intptr())).Target;
	}

	System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandleRef::operator->() const {
		return this->get();
	}

	System::Object% YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandleRef::operator*() const {
		return *this->get();
	}

	YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle::GCHandle(System::Object^ _object, GCHandleType _gchandletype) {
		if (_object) {
			this->intptr_gchandle = static_cast<intptr_t>(System::Runtime::InteropServices::GCHandle::ToIntPtr(System::Runtime::InteropServices::GCHandle::Alloc(_object, GCHandleType_ToManaged(_gchandletype))));
		}
	}

	System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle::get() const {
		if (!this->get_intptr()) return nullptr;
		return System::Runtime::InteropServices::GCHandle::FromIntPtr(static_cast<System::IntPtr>(this->get_intptr())).Target;
	}

	System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle::operator->() const {
		return this->get();
	}

	System::Object% YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle::operator*() const {
		return *this->get();
	}

	void YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle::reset(System::Object^ _object, GCHandleType _gchandletype) {
		GCHandle(_object, _gchandletype).swap(*this);
	}

	System::Runtime::InteropServices::GCHandle^ GCHandle::release() {
		intptr_t intptr_gchandle_original = this->intptr_gchandle;
		this->intptr_gchandle = 0;
		return System::Runtime::InteropServices::GCHandle::FromIntPtr(static_cast<System::IntPtr>(intptr_gchandle_original));
	}

	namespace Internal {
		YBWLIB2DOTNETMIXED_API GCHandle YBWLIB2DOTNETMIXED_CALLTYPE GCHandleFromIUnknown(IUnknown* _iunknown, GCHandleType _gchandletype) {
			return GCHandle(System::Runtime::InteropServices::Marshal::GetObjectForIUnknown(static_cast<System::IntPtr>(reinterpret_cast<void*>(_iunknown))), _gchandletype);
		}

		YBWLIB2DOTNETMIXED_API IUnknown* YBWLIB2DOTNETMIXED_CALLTYPE IUnknownFromGCHandleRef(GCHandleRef _gchandleref) {
			return reinterpret_cast<IUnknown*>(static_cast<void*>(System::Runtime::InteropServices::Marshal::GetIUnknownForObject(_gchandleref.get())));
		}
	}
}

#pragma managed(pop)
