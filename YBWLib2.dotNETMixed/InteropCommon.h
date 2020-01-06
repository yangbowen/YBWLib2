#ifndef _INCLUDE_GUARD_762CAD29_702E_48CA_B56B_50D5ABBDB64B
#define _INCLUDE_GUARD_762CAD29_702E_48CA_B56B_50D5ABBDB64B

#include <cstdint>

#include "YBWLib2dotNETMixedApi.h"

namespace YBWLib2::dotNETMixed {
	enum class GCHandleType : unsigned int {
		Weak = 0,
		WeakTrackResurrection = 1,
		Normal = 2,
		Pinned = 3
	};

	namespace Internal {
		YBWLIB2DOTNETMIXED_API void YBWLIB2DOTNETMIXED_CALLTYPE FreeGCHandle_IntPtr(intptr_t _intptr_gchandle) noexcept;
		YBWLIB2DOTNETMIXED_API intptr_t YBWLIB2DOTNETMIXED_CALLTYPE CopyGCHandle_IntPtr(intptr_t _intptr_gchandle, GCHandleType _gchandletype) noexcept;
		YBWLIB2DOTNETMIXED_API intptr_t YBWLIB2DOTNETMIXED_CALLTYPE MoveGCHandle_IntPtr(intptr_t _intptr_gchandle, GCHandleType _gchandletype) noexcept;
	}

	class GCHandleRef final {
	public:
		constexpr GCHandleRef() noexcept = default;
		inline explicit GCHandleRef(intptr_t _intptr_gchandle) noexcept : intptr_gchandle(_intptr_gchandle) {}
		inline GCHandleRef(const GCHandleRef& x) noexcept = default;
		inline GCHandleRef(GCHandleRef&& x) noexcept = default;
		inline ~GCHandleRef() = default;
		inline GCHandleRef& operator=(const GCHandleRef& x) noexcept = default;
		inline GCHandleRef& operator=(GCHandleRef&& x) noexcept = default;
		inline explicit operator bool() const noexcept { return this->intptr_gchandle; }
		inline intptr_t get_intptr() const noexcept { return this->intptr_gchandle; }
		inline void swap(GCHandleRef& x) noexcept {
			intptr_t intptr_gchandle_temp = this->intptr_gchandle;
			this->intptr_gchandle = x.intptr_gchandle;
			x.intptr_gchandle = intptr_gchandle_temp;
		}
	protected:
		intptr_t intptr_gchandle = 0;
#ifdef __CLR_VER
	public:
		System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED get() const;
		System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED operator->() const;
		System::Object% YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED operator*() const;
#endif
	};

	class GCHandle final {
	public:
		constexpr GCHandle() noexcept = default;
		inline explicit GCHandle(intptr_t&& _intptr_gchandle) noexcept : intptr_gchandle(::std::move(_intptr_gchandle)) {}
		inline GCHandle(const GCHandle& x, GCHandleType _gchandletype) noexcept {
			if (x.intptr_gchandle) {
				this->intptr_gchandle = Internal::CopyGCHandle_IntPtr(x.intptr_gchandle, _gchandletype);
			}
		}
		inline GCHandle(GCHandle&& x, GCHandleType _gchandletype) noexcept {
			if (x.intptr_gchandle) {
				this->intptr_gchandle = Internal::MoveGCHandle_IntPtr(x.intptr_gchandle, _gchandletype);
				x.intptr_gchandle = 0;
			}
		}
		inline GCHandle(const GCHandleRef& x, GCHandleType _gchandletype) noexcept {
			if (x.get_intptr()) {
				this->intptr_gchandle = Internal::CopyGCHandle_IntPtr(x.get_intptr(), _gchandletype);
			}
		}
		GCHandle(const GCHandle&) = delete;
		inline GCHandle(GCHandle&& x) noexcept {
			this->intptr_gchandle = ::std::move(x.intptr_gchandle);
			x.intptr_gchandle = 0;
		}
		inline ~GCHandle() {
			if (this->intptr_gchandle) {
				Internal::FreeGCHandle_IntPtr(this->intptr_gchandle);
				this->intptr_gchandle = 0;
			}
		}
		GCHandle& operator=(const GCHandle&) = delete;
		inline GCHandle& operator=(GCHandle&& x) noexcept {
			GCHandle(::std::move(x)).swap(*this);
			return *this;
		}
		inline explicit operator bool() const noexcept { return this->get_intptr(); }
		inline operator GCHandleRef() const noexcept { return GCHandleRef(this->intptr_gchandle); }
		inline intptr_t get_intptr() const noexcept { return this->intptr_gchandle; }
		inline void reset() noexcept {
			GCHandle().swap(*this);
		}
		inline void reset(intptr_t&& _intptr_gchandle) noexcept {
			GCHandle(::std::move(_intptr_gchandle)).swap(*this);
		}
		inline intptr_t release_intptr() noexcept {
			intptr_t intptr_gchandle_original = this->intptr_gchandle;
			this->intptr_gchandle = 0;
			return intptr_gchandle_original;
		}
		inline void swap(GCHandle& x) noexcept {
			intptr_t intptr_gchandle_temp = this->intptr_gchandle;
			this->intptr_gchandle = x.intptr_gchandle;
			x.intptr_gchandle = intptr_gchandle_temp;
		}
	protected:
		intptr_t intptr_gchandle = 0;
#ifdef __CLR_VER
	public:
		YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED GCHandle(System::Object^ _object, GCHandleType _gchandletype);
		System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED get() const;
		System::Object^ YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED operator->() const;
		System::Object% YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED operator*() const;
		void YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED reset(System::Object^ _object, GCHandleType _gchandletype);
		System::Runtime::InteropServices::GCHandle^ release();
#endif
	};
}

#endif
