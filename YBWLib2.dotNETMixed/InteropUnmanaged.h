#ifndef _INCLUDE_GUARD_9C803758_B4F4_4EBE_BB84_71F24D6B0E6E
#define _INCLUDE_GUARD_9C803758_B4F4_4EBE_BB84_71F24D6B0E6E

#include <cstdint>
#include <type_traits>
#include <utility>
#include <atomic>
#include <objbase.h>

#include "../YBWLib2/Common/CommonLowLevel.h"
#include "../YBWLib2/Common/Common.h"
#include "../YBWLib2/Common/CommonWindows.h"

#include "YBWLib2dotNETMixedApi.h"
#include "InteropCommon.h"

namespace YBWLib2::dotNETMixed {
	class SharedGCHandle final {
	public:
		constexpr SharedGCHandle() noexcept = default;
		inline explicit SharedGCHandle(intptr_t&& _intptr_gchandle) noexcept : controlblock(new ControlBlock(::std::move(_intptr_gchandle))) {
			assert(this->controlblock);
		}
		inline SharedGCHandle(GCHandle&& _gchandle) noexcept : SharedGCHandle(_gchandle.release_intptr()) {}
		inline SharedGCHandle(const SharedGCHandle& x) noexcept {
			if (x.controlblock) {
				x.controlblock->IncReferenceCount();
				this->controlblock = x.controlblock;
			}
		}
		inline SharedGCHandle(SharedGCHandle&& x) noexcept {
			this->controlblock = ::std::move(x.controlblock);
			x.controlblock = nullptr;
		}
		inline ~SharedGCHandle() {
			if (this->controlblock) {
				this->controlblock->DecReferenceCount();
				this->controlblock = nullptr;
			}
		}
		inline SharedGCHandle& operator=(const SharedGCHandle& x) noexcept {
			SharedGCHandle(x).swap(*this);
			return *this;
		}
		inline SharedGCHandle& operator=(SharedGCHandle&& x) noexcept {
			SharedGCHandle(::std::move(x)).swap(*this);
			return *this;
		}
		inline explicit operator bool() noexcept {
			return this->controlblock && *this->controlblock;
		}
		inline operator GCHandleRef() const noexcept { return GCHandleRef(this->get_intptr()); }
		inline intptr_t get_intptr() const noexcept {
			return this->controlblock ? this->controlblock->get_intptr() : 0;
		}
		inline void swap(SharedGCHandle& x) noexcept {
			ControlBlock* controlblock_temp = this->controlblock;
			this->controlblock = x.controlblock;
			x.controlblock = controlblock_temp;
		}
	protected:
		class ControlBlock final : public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
		public:
			ControlBlock() noexcept = default;
			inline explicit ControlBlock(intptr_t&& _intptr_gchandle) noexcept : intptr_gchandle(::std::move(_intptr_gchandle)) {}
			inline ControlBlock(const ControlBlock& x, GCHandleType _gchandletype) noexcept
				: intptr_gchandle(Internal::CopyGCHandle_IntPtr(x.intptr_gchandle, _gchandletype)) {}
			inline ControlBlock(ControlBlock&& x, GCHandleType _gchandletype) noexcept
				: intptr_gchandle(Internal::MoveGCHandle_IntPtr(x.intptr_gchandle, _gchandletype)) {
				x.intptr_gchandle = 0;
			}
			ControlBlock(const ControlBlock&) = delete;
			ControlBlock(ControlBlock&&) = delete;
			inline ~ControlBlock() {
				assert(!this->refcount.load(::std::memory_order_acquire));
				if (this->intptr_gchandle) {
					Internal::FreeGCHandle_IntPtr(this->intptr_gchandle);
					this->intptr_gchandle = 0;
				}
			}
			ControlBlock& operator=(const ControlBlock&) = delete;
			ControlBlock& operator=(ControlBlock&&) = delete;
			inline explicit operator bool() const noexcept { return this->intptr_gchandle.load(::std::memory_order_seq_cst); }
			inline intptr_t get_intptr() const noexcept {
				return this->intptr_gchandle.load(::std::memory_order_seq_cst);
			}
			inline void IncReferenceCount() const noexcept {
				uintptr_t ref_count_old = this->refcount.fetch_add(1, ::std::memory_order_relaxed);
				assert(ref_count_old); static_cast<void>(ref_count_old);
			}
			inline void DecReferenceCount() const noexcept {
				uintptr_t ref_count_old = this->refcount.fetch_sub(1, ::std::memory_order_release);
				assert(ref_count_old);
				if (ref_count_old == 1) delete this;
			}
		protected:
			::std::atomic<intptr_t> intptr_gchandle = 0;
			mutable ::std::atomic<uintptr_t> refcount = 1;
		};
		static_assert(::std::is_standard_layout_v<ControlBlock>, "SharedGCHandle::ControlBlock is not standard layout.");
		ControlBlock* controlblock = nullptr;
	};
	static_assert(::std::is_standard_layout_v<SharedGCHandle>, "SharedGCHandle is not standard layout.");

	namespace Internal {
		YBWLIB2DOTNETMIXED_API GCHandle YBWLIB2DOTNETMIXED_CALLTYPE GCHandleFromIUnknown(IUnknown* _iunknown, GCHandleType _gchandletype);
		YBWLIB2DOTNETMIXED_API IUnknown* YBWLIB2DOTNETMIXED_CALLTYPE IUnknownFromGCHandleRef(GCHandleRef _gchandleref);
	}

	inline GCHandle GCHandleFromIUnknown(const COMObjectHolder<IUnknown>& _iunknown, GCHandleType _gchandletype = GCHandleType::Normal) {
		return Internal::GCHandleFromIUnknown(_iunknown.get(), _gchandletype);
	}

	inline SharedGCHandle SharedGCHandleFromIUnknown(const COMObjectHolder<IUnknown>& _iunknown, GCHandleType _gchandletype = GCHandleType::Normal) {
		return SharedGCHandle(Internal::GCHandleFromIUnknown(_iunknown.get(), _gchandletype));
	}

	inline COMObjectHolder<IUnknown> IUnknownFromGCHandleRef(GCHandleRef _gchandleref) {
		return COMObjectHolder<IUnknown>(Internal::IUnknownFromGCHandleRef(_gchandleref));
	}
}

#endif
