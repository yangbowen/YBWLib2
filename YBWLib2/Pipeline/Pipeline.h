#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5394D13F_B842_4478_8DF4_88C69F7DBE27
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_9F79D877_16AB_40E8_8BCB_E32845F9892A
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_03DECAAC_C9F7_49B9_922E_B5A3E7EECC4D
#define _INCLUDE_GUARD_03DECAAC_C9F7_49B9_922E_B5A3E7EECC4D

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"

namespace YBWLib2 {
	class Pipeline;
	class PipelineFilter;
	class PipelineInvocationPacket;

	struct always_assign_delegate_pipelineinvocationpacketdataentry_t {};
	static constexpr always_assign_delegate_pipelineinvocationpacketdataentry_t always_assign_delegate_pipelineinvocationpacketdataentry {};

	/// <summary>Unique identifier used to identify a pipeline.</summary>
	struct PipelineID : public VolatileID {
		constexpr PipelineID() noexcept = default;
		explicit PipelineID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit PipelineID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit PipelineID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		PipelineID(const PipelineID& x) noexcept = default;
		PipelineID(PipelineID&& x) noexcept = default;
		~PipelineID() = default;
		PipelineID& operator=(const PipelineID& x) noexcept = default;
		PipelineID& operator=(PipelineID&& x) noexcept = default;
		bool operator==(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const PipelineID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<PipelineID>, "PipelineID is not standard-layout.");

	template<>
	struct hash<PipelineID> {
		inline size_t operator()(const PipelineID& x) const {
			return x.hash();
		}
	};

	/// <summary>Unique identifier used to identify a pipeline filter.</summary>
	struct PipelineFilterID : public VolatileID {
		constexpr PipelineFilterID() noexcept = default;
		explicit PipelineFilterID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit PipelineFilterID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit PipelineFilterID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		PipelineFilterID(const PipelineFilterID& x) noexcept = default;
		PipelineFilterID(PipelineFilterID&& x) noexcept = default;
		~PipelineFilterID() = default;
		PipelineFilterID& operator=(const PipelineFilterID& x) noexcept = default;
		PipelineFilterID& operator=(PipelineFilterID&& x) noexcept = default;
		bool operator==(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const PipelineFilterID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<PipelineFilterID>, "PipelineFilterID is not standard-layout.");

	template<>
	struct hash<PipelineFilterID> {
		inline size_t operator()(const PipelineFilterID& x) const {
			return x.hash();
		}
	};

	/// <summary>Unique identifier used to identify a pipeline invocation packet data entry.</summary>
	struct PipelineInvocationPacketDataEntryID : public VolatileID {
		constexpr PipelineInvocationPacketDataEntryID() noexcept = default;
		explicit PipelineInvocationPacketDataEntryID(const VolatileID& _volatileid) noexcept : VolatileID(_volatileid) {}
		explicit PipelineInvocationPacketDataEntryID(VolatileID&& _volatileid) noexcept : VolatileID(::std::move(_volatileid)) {}
		explicit PipelineInvocationPacketDataEntryID(const PersistentID& _persistentid) noexcept : VolatileID(_persistentid) {}
		PipelineInvocationPacketDataEntryID(const PipelineInvocationPacketDataEntryID& x) noexcept = default;
		PipelineInvocationPacketDataEntryID(PipelineInvocationPacketDataEntryID&& x) noexcept = default;
		~PipelineInvocationPacketDataEntryID() = default;
		PipelineInvocationPacketDataEntryID& operator=(const PipelineInvocationPacketDataEntryID& x) noexcept = default;
		PipelineInvocationPacketDataEntryID& operator=(PipelineInvocationPacketDataEntryID&& x) noexcept = default;
		bool operator==(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) == static_cast<const VolatileID&>(r); }
		bool operator!=(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) != static_cast<const VolatileID&>(r); }
		bool operator<(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) < static_cast<const VolatileID&>(r); }
		bool operator<=(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) <= static_cast<const VolatileID&>(r); }
		bool operator>(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) > static_cast<const VolatileID&>(r); }
		bool operator>=(const PipelineInvocationPacketDataEntryID& r) const noexcept { return static_cast<const VolatileID&>(*this) >= static_cast<const VolatileID&>(r); }
		explicit operator bool() const noexcept { return static_cast<bool>(static_cast<const VolatileID&>(*this)); }
		explicit operator PersistentID() const noexcept { return static_cast<PersistentID>(static_cast<const VolatileID&>(*this)); }
		size_t hash() const noexcept { return static_cast<const VolatileID&>(*this).hash(); }
	};
	static_assert(::std::is_standard_layout_v<PipelineInvocationPacketDataEntryID>, "PipelineInvocationPacketDataEntryID is not standard-layout.");

	template<>
	struct hash<PipelineInvocationPacketDataEntryID> {
		inline size_t operator()(const PipelineInvocationPacketDataEntryID& x) const {
			return x.hash();
		}
	};

	using PipelineInvocationPacketDataEntryInitializeDelegate = Delegate<DelegateFlag_Noexcept, void, void*, PipelineInvocationPacket*>;
	using PipelineInvocationPacketDataEntryCleanupDelegate = Delegate<DelegateFlag_Noexcept, void, void*, PipelineInvocationPacket*>;
	using PipelineFilterRawInvokeDelegate = Delegate<DelegateFlags::DelegateFlag_Noexcept, void, PipelineInvocationPacket*>;

	constexpr size_t PipelineInvocationPacketDataSlotSize = alignof(::std::max_align_t);
	constexpr size_t PipelineInvocationPacketDataSlotAlign = alignof(::std::max_align_t);

	enum class PipelineFilterPositionType : unsigned int {
		PipelineFilterPositionType_Invalid = 0x0,
		PipelineFilterPositionType_Front = 0x1,
		PipelineFilterPositionType_Back = 0x2,
		PipelineFilterPositionType_BeforeRef = 0x3,
		PipelineFilterPositionType_AfterRef = 0x4
	};

	struct PipelineFilterPosition final {
		PipelineFilterPositionType pipelinefilterpositiontype;
		PipelineFilterID pipelinefilterid_ref;
		constexpr PipelineFilterPosition() : pipelinefilterpositiontype(PipelineFilterPositionType::PipelineFilterPositionType_Invalid) {}
		PipelineFilterPosition(PipelineFilterPositionType _pipelinefilterpositiontype, PipelineFilterID&& _pipelinefilterid_ref = PipelineFilterID())
			: pipelinefilterpositiontype(_pipelinefilterpositiontype),
			pipelinefilterid_ref(::std::move(_pipelinefilterid_ref)) {}
	};

	namespace Internal {
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PersistentID* _persistentid_pipelineid) noexcept;

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(Pipeline* _pipeline) noexcept;
		YBWLIB2_API PipelineID YBWLIB2_CALLTYPE Pipeline_GetPipelineID(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_GetInvocationDataSize(const Pipeline* _pipeline, already_shared_locked_this_t) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_InitializeInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket** _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_CleanupInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket* _pipelineinvocationpacket, already_shared_locked_this_t) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_RawInvoke(const Pipeline* _pipeline, PipelineInvocationPacket* _pipelineinvocationpacket, already_shared_locked_this_t) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_RegisterInvocationPacketDataEntry(
			Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate* _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate* _delegate_cleanup_invocationpacketdataentry,
			already_exclusive_locked_this_t
		) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_RegisterInvocationPacketDataEntry(
			Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate* _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate* _delegate_cleanup_invocationpacketdataentry,
			always_assign_delegate_pipelineinvocationpacketdataentry_t,
			already_exclusive_locked_this_t
		) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnregisterInvocationPacketDataEntry(Pipeline* _pipeline, const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t) noexcept;

		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PersistentID* _persistentid_pipelinefilterid) noexcept;

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(const PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API PipelineFilterID YBWLIB2_CALLTYPE PipelineFilter_GetPipelineFilterID(const PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_GetRawInvokeDelegate(const PipelineFilter* _pipelinefilter, const PipelineFilterRawInvokeDelegate** _delegate_rawinvoke_ret) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_ReleaseRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke_ret) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetPipelineFilterPositionArray(PipelineFilter* _pipelinefilter, const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept;

		YBWLIB2_API const Pipeline* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetPipeline(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API const void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataSize(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
	};

	inline ReferenceCountedObjectHolder<Pipeline> CreatePipeline(const PersistentID& _persistentid_pipelineid) noexcept {
		Pipeline* ptr_pipeline = Internal::CreatePipeline(&_persistentid_pipelineid);
		assert(ptr_pipeline);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::Pipeline_CastToIReferenceCountedObject(ptr_pipeline);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<Pipeline>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject), ReferenceCountedObjectHolder<IReferenceCountedObject>::adopt_ref_count),
			ptr_pipeline
			);
	}

	inline PipelineID Pipeline_GetPipelineID(const Pipeline& _pipeline) noexcept {
		return Internal::Pipeline_GetPipelineID(&_pipeline);
	}

	inline void Pipeline_LockExclusive(const Pipeline& _pipeline) noexcept {
		Internal::Pipeline_LockExclusive(&_pipeline);
	}

	inline bool Pipeline_TryLockExclusive(const Pipeline& _pipeline) noexcept {
		return Internal::Pipeline_TryLockExclusive(&_pipeline);
	}

	inline void Pipeline_UnlockExclusive(const Pipeline& _pipeline) noexcept {
		Internal::Pipeline_UnlockExclusive(&_pipeline);
	}

	inline void Pipeline_LockShared(const Pipeline& _pipeline) noexcept {
		Internal::Pipeline_LockShared(&_pipeline);
	}

	inline bool Pipeline_TryLockShared(const Pipeline& _pipeline) noexcept {
		return Internal::Pipeline_TryLockShared(&_pipeline);
	}

	inline void Pipeline_UnlockShared(const Pipeline& _pipeline) noexcept {
		Internal::Pipeline_UnlockShared(&_pipeline);
	}

	struct PipelineSharedMutexWrapper final {
		PipelineSharedMutexWrapper(const Pipeline& _pipeline) noexcept : pipeline(&_pipeline) {}
		PipelineSharedMutexWrapper(const PipelineSharedMutexWrapper&) = delete;
		PipelineSharedMutexWrapper(PipelineSharedMutexWrapper&&) = delete;
		~PipelineSharedMutexWrapper() {
			this->pipeline = nullptr;
		}
		PipelineSharedMutexWrapper& operator=(const PipelineSharedMutexWrapper&) = delete;
		PipelineSharedMutexWrapper& operator=(PipelineSharedMutexWrapper&&) = delete;
		const Pipeline& GetPipeline() const noexcept {
			assert(this->pipeline);
			return *this->pipeline;
		}
		void lock() const noexcept {
			assert(this->pipeline);
			Pipeline_LockExclusive(*this->pipeline);
		}
		bool try_lock() const noexcept {
			assert(this->pipeline);
			return Pipeline_TryLockExclusive(*this->pipeline);
		}
		void unlock() const noexcept {
			assert(this->pipeline);
			Pipeline_UnlockExclusive(*this->pipeline);
		}
		void lock_shared() const noexcept {
			assert(this->pipeline);
			Pipeline_LockShared(*this->pipeline);
		}
		bool try_lock_shared() const noexcept {
			assert(this->pipeline);
			return Pipeline_TryLockShared(*this->pipeline);
		}
		void unlock_shared() const noexcept {
			assert(this->pipeline);
			Pipeline_UnlockShared(*this->pipeline);
		}
	private:
		const Pipeline* pipeline = nullptr;
	};
	static_assert(::std::is_standard_layout_v<PipelineSharedMutexWrapper>, "PipelineSharedMutexWrapper is not standard-layout.");

	inline size_t Pipeline_GetInvocationDataSize(const Pipeline& _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		return Internal::Pipeline_GetInvocationDataSize(&_pipeline, _already_shared_locked_this);
	}

	inline void Pipeline_InitializeInvocationPacket(const Pipeline& _pipeline, PipelineInvocationPacket*& _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		Internal::Pipeline_InitializeInvocationPacket(&_pipeline, &_pipelineinvocationpacket_ret, _buf_invocationdata, _size_buf_invocationdata, _already_shared_locked_this);
	}

	inline void Pipeline_CleanupInvocationPacket(const Pipeline& _pipeline, PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		Internal::Pipeline_CleanupInvocationPacket(&_pipeline, &_pipelineinvocationpacket, _already_shared_locked_this);
	}

	inline void Pipeline_RawInvoke(const Pipeline& _pipeline, PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		Internal::Pipeline_RawInvoke(&_pipeline, &_pipelineinvocationpacket, _already_shared_locked_this);
	}

	inline size_t Pipeline_RegisterInvocationPacketDataEntry(
		Pipeline& _pipeline,
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		const void* _data_initial_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
		already_exclusive_locked_this_t _already_exclusive_locked_this
	) noexcept {
		return Internal::Pipeline_RegisterInvocationPacketDataEntry(
			&_pipeline,
			&_pipelineinvocationpacketdataentryid,
			_size_invocationpacketdataentry,
			_data_initial_invocationpacketdataentry,
			&_delegate_initialize_invocationpacketdataentry,
			&_delegate_cleanup_invocationpacketdataentry,
			_already_exclusive_locked_this
		);
	}

	inline size_t Pipeline_RegisterInvocationPacketDataEntry(
		Pipeline& _pipeline,
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		const void* _data_initial_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
		always_assign_delegate_pipelineinvocationpacketdataentry_t _always_assign_delegate_pipelineinvocationpacketdataentry,
		already_exclusive_locked_this_t _already_exclusive_locked_this
	) noexcept {
		return Internal::Pipeline_RegisterInvocationPacketDataEntry(
			&_pipeline,
			&_pipelineinvocationpacketdataentryid,
			_size_invocationpacketdataentry,
			_data_initial_invocationpacketdataentry,
			&_delegate_initialize_invocationpacketdataentry,
			&_delegate_cleanup_invocationpacketdataentry,
			_always_assign_delegate_pipelineinvocationpacketdataentry,
			_already_exclusive_locked_this
		);
	}

	inline void Pipeline_UnregisterInvocationPacketDataEntry(Pipeline& _pipeline, const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		Internal::Pipeline_UnregisterInvocationPacketDataEntry(&_pipeline, &_pipelineinvocationpacketdataentryid, _already_exclusive_locked_this);
	}

	inline ReferenceCountedObjectHolder<PipelineFilter> CreatePipelineFilter(const PersistentID& _persistentid_pipelinefilterid) noexcept {
		PipelineFilter* ptr_pipelinefilter = Internal::CreatePipelineFilter(&_persistentid_pipelinefilterid);
		assert(ptr_pipelinefilter);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::PipelineFilter_CastToIReferenceCountedObject(ptr_pipelinefilter);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<PipelineFilter>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject), ReferenceCountedObjectHolder<IReferenceCountedObject>::adopt_ref_count),
			ptr_pipelinefilter
			);
	}

	inline PipelineFilterID PipelineFilter_GetPipelineFilterID(const PipelineFilter& _pipelinefilter) noexcept {
		return Internal::PipelineFilter_GetPipelineFilterID(&_pipelinefilter);
	}

	inline const PipelineFilterRawInvokeDelegate& PipelineFilter_GetRawInvokeDelegate(const PipelineFilter& _pipelinefilter) noexcept {
		const PipelineFilterRawInvokeDelegate* delegate_rawinvoke = nullptr;
		Internal::PipelineFilter_GetRawInvokeDelegate(&_pipelinefilter, &delegate_rawinvoke);
		return *delegate_rawinvoke;
	}

	inline PipelineFilterRawInvokeDelegate&& PipelineFilter_ReleaseRawInvokeDelegate(PipelineFilter& _pipelinefilter) noexcept {
		PipelineFilterRawInvokeDelegate delegate_rawinvoke;
		Internal::PipelineFilter_ReleaseRawInvokeDelegate(&_pipelinefilter, &delegate_rawinvoke);
		return ::std::move(delegate_rawinvoke);
	}

	inline void PipelineFilter_SetRawInvokeDelegate(PipelineFilter& _pipelinefilter, PipelineFilterRawInvokeDelegate&& _delegate_rawinvoke) noexcept {
		Internal::PipelineFilter_SetRawInvokeDelegate(&_pipelinefilter, &_delegate_rawinvoke);
	}

	inline void PipelineFilter_SetPipelineFilterPositionArray(PipelineFilter& _pipelinefilter, const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept {
		Internal::PipelineFilter_SetPipelineFilterPositionArray(&_pipelinefilter, _arr_pipelinefilterposition, _size_pipelinefilterposition);
	}

	inline const Pipeline* PipelineInvocationPacket_GetPipeline(const PipelineInvocationPacket& _pipelineinvocationpacket) noexcept {
		return Internal::PipelineInvocationPacket_GetPipeline(&_pipelineinvocationpacket);
	}

	inline const void* PipelineInvocationPacket_GetInvocationPacketDataPtr(const PipelineInvocationPacket& _pipelineinvocationpacket) noexcept {
		return Internal::PipelineInvocationPacket_GetInvocationPacketDataPtr(&_pipelineinvocationpacket);
	}

	inline void* PipelineInvocationPacket_GetInvocationPacketDataPtr(PipelineInvocationPacket& _pipelineinvocationpacket) noexcept {
		return Internal::PipelineInvocationPacket_GetInvocationPacketDataPtr(&_pipelineinvocationpacket);
	}

	inline size_t PipelineInvocationPacket_GetInvocationPacketDataSize(const PipelineInvocationPacket& _pipelineinvocationpacket) noexcept {
		return Internal::PipelineInvocationPacket_GetInvocationPacketDataSize(&_pipelineinvocationpacket);
	}

	class PipelineInvocationPacketDataEntryHolder final {
	public:
		constexpr PipelineInvocationPacketDataEntryHolder() noexcept = default;
		PipelineInvocationPacketDataEntryHolder(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry) {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						_data_initial_invocationpacketdataentry,
						::std::move(_delegate_initialize_invocationpacketdataentry),
						::std::move(_delegate_cleanup_invocationpacketdataentry),
						already_exclusive_locked_this_t()
					);
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
			always_assign_delegate_pipelineinvocationpacketdataentry_t _always_assign_delegate_pipelineinvocationpacketdataentry
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry) {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						_data_initial_invocationpacketdataentry,
						::std::move(_delegate_initialize_invocationpacketdataentry),
						::std::move(_delegate_cleanup_invocationpacketdataentry),
						_always_assign_delegate_pipelineinvocationpacketdataentry,
						already_exclusive_locked_this_t()
					);
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder(const PipelineInvocationPacketDataEntryHolder& x) noexcept
			: pipelineinvocationpacketdataentryid(x.pipelineinvocationpacketdataentryid),
			objholder_pipeline(x.objholder_pipeline),
			size_pipelineinvocationpacketdataentry(x.size_pipelineinvocationpacketdataentry),
			offset_pipelineinvocationpacketdataentry(x.offset_pipelineinvocationpacketdataentry) {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					size_t _offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						nullptr,
						PipelineInvocationPacketDataEntryInitializeDelegate(),
						PipelineInvocationPacketDataEntryCleanupDelegate(),
						already_exclusive_locked_this_t()
					);
					static_cast<void>(_offset_pipelineinvocationpacketdataentry);
					assert(_offset_pipelineinvocationpacketdataentry == this->offset_pipelineinvocationpacketdataentry);
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder(PipelineInvocationPacketDataEntryHolder&& x) noexcept
			: pipelineinvocationpacketdataentryid(::std::move(x.pipelineinvocationpacketdataentryid)),
			objholder_pipeline(::std::move(x.objholder_pipeline)),
			size_pipelineinvocationpacketdataentry(::std::move(x.size_pipelineinvocationpacketdataentry)),
			offset_pipelineinvocationpacketdataentry(::std::move(x.offset_pipelineinvocationpacketdataentry)) {
			x.pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			x.objholder_pipeline.reset();
			x.size_pipelineinvocationpacketdataentry = 0;
			x.offset_pipelineinvocationpacketdataentry = SIZE_MAX;
		}
		~PipelineInvocationPacketDataEntryHolder() {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t());
				}
			}
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
		}
		PipelineInvocationPacketDataEntryHolder& operator=(const PipelineInvocationPacketDataEntryHolder& x) noexcept {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t());
				}
			}
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			this->pipelineinvocationpacketdataentryid = x.pipelineinvocationpacketdataentryid;
			this->objholder_pipeline = x.objholder_pipeline;
			this->size_pipelineinvocationpacketdataentry = x.size_pipelineinvocationpacketdataentry;
			this->offset_pipelineinvocationpacketdataentry = x.offset_pipelineinvocationpacketdataentry;
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					size_t _offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						nullptr,
						PipelineInvocationPacketDataEntryInitializeDelegate(),
						PipelineInvocationPacketDataEntryCleanupDelegate(),
						already_exclusive_locked_this_t()
					);
					static_cast<void>(_offset_pipelineinvocationpacketdataentry);
					assert(_offset_pipelineinvocationpacketdataentry == this->offset_pipelineinvocationpacketdataentry);
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder& operator=(PipelineInvocationPacketDataEntryHolder&& x) noexcept {
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					PipelineSharedMutexWrapper sharedmutexwrapper_pipeline(*this->objholder_pipeline);
					::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(sharedmutexwrapper_pipeline);
					Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t());
				}
			}
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			this->pipelineinvocationpacketdataentryid = ::std::move(x.pipelineinvocationpacketdataentryid);
			x.pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			this->objholder_pipeline = ::std::move(x.objholder_pipeline);
			x.objholder_pipeline.reset();
			this->size_pipelineinvocationpacketdataentry = ::std::move(x.size_pipelineinvocationpacketdataentry);
			x.size_pipelineinvocationpacketdataentry = 0;
			this->offset_pipelineinvocationpacketdataentry = ::std::move(x.offset_pipelineinvocationpacketdataentry);
			x.offset_pipelineinvocationpacketdataentry = SIZE_MAX;
		}
		const PipelineInvocationPacketDataEntryID& GetPipelineInvocationPacketDataEntryID() const noexcept { return this->pipelineinvocationpacketdataentryid; }
		const ReferenceCountedObjectHolder<Pipeline>& GetPipeline() const noexcept { return this->objholder_pipeline; }
		size_t GetDataEntrySize() const noexcept { return this->size_pipelineinvocationpacketdataentry; }
		size_t GetDataEntryOffset() const noexcept { return this->offset_pipelineinvocationpacketdataentry; }
		const void* GetDataEntry(const PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
			const void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
			assert(ptr_invocationpacketdata);
			assert(this->offset_pipelineinvocationpacketdataentry + this->size_pipelineinvocationpacketdataentry <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket));
			return reinterpret_cast<const void*>(reinterpret_cast<const unsigned char*>(ptr_invocationpacketdata) + this->offset_pipelineinvocationpacketdataentry);
		}
		void* GetDataEntry(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
			void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
			assert(ptr_invocationpacketdata);
			assert(this->offset_pipelineinvocationpacketdataentry + this->size_pipelineinvocationpacketdataentry <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket));
			return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(ptr_invocationpacketdata) + this->offset_pipelineinvocationpacketdataentry);
		}
	protected:
		PipelineInvocationPacketDataEntryID pipelineinvocationpacketdataentryid;
		ReferenceCountedObjectHolder<Pipeline> objholder_pipeline;
		size_t size_pipelineinvocationpacketdataentry = 0;
		size_t offset_pipelineinvocationpacketdataentry = SIZE_MAX;
	};
	static_assert(::std::is_standard_layout_v<PipelineInvocationPacketDataEntryHolder>, "PipelineInvocationPacketDataEntryHolder is not standard-layout.");

	template<typename _Data_Ty>
	class PipelineInvocationPacketDataEntryHolderWrapper final {
	public:
		static_assert(::std::is_object_v<_Data_Ty>, "The specified type is not an object type.");
		static_assert(::std::is_nothrow_destructible_v<_Data_Ty>, "The specified type is not nothrow-destructible.");
		using data_type = _Data_Ty;
		constexpr PipelineInvocationPacketDataEntryHolderWrapper() noexcept = default;
		template<typename ::std::enable_if<::std::is_nothrow_copy_constructible_v<data_type>, int>::type = 0>
		PipelineInvocationPacketDataEntryHolderWrapper(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			const data_type& _data_initial
		) noexcept {
			PipelineInvocationPacketDataEntryCleanupDelegate delegate_cleanup_invocationpacketdataentry;
			if constexpr (!::std::is_trivially_destructible_v<data_type>)
				delegate_cleanup_invocationpacketdataentry = PipelineInvocationPacketDataEntryCleanupDelegate<CleanupPipelineInvocationPacketData>(PipelineInvocationPacketDataEntryCleanupDelegate::invoke_function);
			if constexpr (::std::is_trivially_copy_constructible_v<data_type>) {
				this->pipelineinvocationpacketdataentryholder = PipelineInvocationPacketDataEntryHolder(
					_pipelineinvocationpacketdataentryid,
					_objholder_pipeline,
					sizeof(data_type),
					reinterpret_cast<const void*>(::std::addressof(_data_initial)),
					PipelineInvocationPacketDataEntryInitializeDelegate(),
					::std::move(delegate_cleanup_invocationpacketdataentry)
				);
			} else {
				auto fn_InitializePipelineInvocationPacketData = [_data_initial](void* _ptr_pipelineinvocationpacketdataentry, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept->void {
					if (_ptr_pipelineinvocationpacketdataentry) {
						new(_ptr_pipelineinvocationpacketdataentry) data_type(_data_initial);
					}
				};
				this->pipelineinvocationpacketdataentryholder = PipelineInvocationPacketDataEntryHolder(
					_pipelineinvocationpacketdataentryid,
					_objholder_pipeline,
					sizeof(data_type),
					nullptr,
					PipelineInvocationPacketDataEntryInitializeDelegate(fn_InitializePipelineInvocationPacketData),
					::std::move(delegate_cleanup_invocationpacketdataentry)
				);
			}
		}
		template<typename ::std::enable_if<::std::is_nothrow_default_constructible_v<data_type>, int>::type = 0>
		PipelineInvocationPacketDataEntryHolderWrapper(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline
		) noexcept {
			PipelineInvocationPacketDataEntryInitializeDelegate delegate_initialize_invocationpacketdataentry;
			PipelineInvocationPacketDataEntryCleanupDelegate delegate_cleanup_invocationpacketdataentry;
			if constexpr (!::std::is_trivially_default_constructible_v<data_type>)
				delegate_initialize_invocationpacketdataentry = PipelineInvocationPacketDataEntryInitializeDelegate<DefaultInitializePipelineInvocationPacketData>(PipelineInvocationPacketDataEntryInitializeDelegate::invoke_function);
			if constexpr (!::std::is_trivially_destructible_v<data_type>)
				delegate_cleanup_invocationpacketdataentry = PipelineInvocationPacketDataEntryCleanupDelegate<CleanupPipelineInvocationPacketData>(PipelineInvocationPacketDataEntryCleanupDelegate::invoke_function);
			this->pipelineinvocationpacketdataentryholder = PipelineInvocationPacketDataEntryHolder(
				_pipelineinvocationpacketdataentryid,
				_objholder_pipeline,
				sizeof(data_type),
				nullptr,
				::std::move(delegate_initialize_invocationpacketdataentry),
				::std::move(delegate_cleanup_invocationpacketdataentry)
			);
		}
		PipelineInvocationPacketDataEntryHolderWrapper(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry
		) noexcept {
			this->pipelineinvocationpacketdataentryholder = PipelineInvocationPacketDataEntryHolder(
				_pipelineinvocationpacketdataentryid,
				_objholder_pipeline,
				sizeof(data_type),
				_data_initial_invocationpacketdataentry,
				::std::move(_delegate_initialize_invocationpacketdataentry),
				::std::move(_delegate_cleanup_invocationpacketdataentry)
			);
		}
		PipelineInvocationPacketDataEntryHolderWrapper(const PipelineInvocationPacketDataEntryHolderWrapper& x) noexcept = default;
		PipelineInvocationPacketDataEntryHolderWrapper(PipelineInvocationPacketDataEntryHolderWrapper&& x) noexcept = default;
		~PipelineInvocationPacketDataEntryHolderWrapper() = default;
		PipelineInvocationPacketDataEntryHolderWrapper& operator=(const PipelineInvocationPacketDataEntryHolderWrapper& x) noexcept = default;
		PipelineInvocationPacketDataEntryHolderWrapper& operator=(PipelineInvocationPacketDataEntryHolderWrapper&& x) noexcept = default;
		const PipelineInvocationPacketDataEntryID& GetPipelineInvocationPacketDataEntryID() const noexcept { return this->pipelineinvocationpacketdataentryholder.GetPipelineInvocationPacketDataEntryID(); }
		const ReferenceCountedObjectHolder<Pipeline>& GetPipeline() const noexcept { return this->pipelineinvocationpacketdataentryholder.GetPipeline(); }
		size_t GetDataEntrySize() const noexcept { return this->pipelineinvocationpacketdataentryholder.GetDataEntrySize(); }
		size_t GetDataEntryOffset() const noexcept { return this->pipelineinvocationpacketdataentryholder.GetDataEntryOffset(); }
		const data_type& GetDataEntry(const PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept { return *::std::launder(reinterpret_cast<const data_type*>(this->pipelineinvocationpacketdataentryholder.GetDataEntry(_pipelineinvocationpacket))); }
		data_type& GetDataEntry(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept { return *::std::launder(reinterpret_cast<data_type*>(this->pipelineinvocationpacketdataentryholder.GetDataEntry(_pipelineinvocationpacket))); }
	protected:
		template<typename ::std::enable_if<::std::is_nothrow_default_constructible_v<data_type>, int>::type = 0>
		static void DefaultInitializePipelineInvocationPacketData(void* _ptr_pipelineinvocationpacketdataentry, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			if (_ptr_pipelineinvocationpacketdataentry) {
				new(_ptr_pipelineinvocationpacketdataentry) data_type();
			}
		}
		static void CleanupPipelineInvocationPacketData(void* _ptr_pipelineinvocationpacketdataentry, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			if constexpr (!::std::is_trivially_destructible_v<data_type>) {
				if (_ptr_pipelineinvocationpacketdataentry) {
					reinterpret_cast<data_type*>(_ptr_pipelineinvocationpacketdataentry)->~data_type();
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder pipelineinvocationpacketdataentryholder;
	};

	void YBWLIB2_CALLTYPE Pipeline_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Pipeline_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE Pipeline_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE Pipeline_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE PipelineUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE PipelineUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_9F79D877_16AB_40E8_8BCB_E32845F9892A
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_9F79D877_16AB_40E8_8BCB_E32845F9892A
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5394D13F_B842_4478_8DF4_88C69F7DBE27
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_5394D13F_B842_4478_8DF4_88C69F7DBE27
#endif
