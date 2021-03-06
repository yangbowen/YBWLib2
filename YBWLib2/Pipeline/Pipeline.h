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
#include <optional>
#include <array>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#if !defined(YBWLIB2_NO_ALLOCA) && defined(_MSC_VER)
#include <malloc.h>
#endif
#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"

// This is used to temporarily workaround a compiler bug in VC++.
// The class definitions exposed by defining this macro are not supposed to be accessed directly outside the source file.
#define YBWLIB2_PIPELINE_EXPOSE_PRIVATE_CLASSES

namespace YBWLib2 {
	class Pipeline;
	class PipelineFilter;
	class PipelineInvocationPacket;
	class PipelineStore;

	struct always_assign_delegate_pipelineinvocationpacketdataentry_t {};
	static constexpr always_assign_delegate_pipelineinvocationpacketdataentry_t always_assign_delegate_pipelineinvocationpacketdataentry{};

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
}

namespace std {
	template<>
	struct hash<::YBWLib2::PipelineID> {
		inline size_t operator()(const ::YBWLib2::PipelineID& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
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
}

namespace std {
	template<>
	struct hash<::YBWLib2::PipelineFilterID> {
		inline size_t operator()(const ::YBWLib2::PipelineFilterID& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
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
}

namespace std {
	template<>
	struct hash<::YBWLib2::PipelineInvocationPacketDataEntryID> {
		inline size_t operator()(const ::YBWLib2::PipelineInvocationPacketDataEntryID& x) const noexcept {
			return x.hash();
		}
	};
}

namespace YBWLib2 {
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
		constexpr PipelineFilterPosition() noexcept : pipelinefilterpositiontype(PipelineFilterPositionType::PipelineFilterPositionType_Invalid) {}
		explicit constexpr PipelineFilterPosition(PipelineFilterPositionType _pipelinefilterpositiontype) noexcept
			: pipelinefilterpositiontype(_pipelinefilterpositiontype) {}
		PipelineFilterPosition(PipelineFilterPositionType _pipelinefilterpositiontype, PipelineFilterID&& _pipelinefilterid_ref) noexcept
			: pipelinefilterpositiontype(_pipelinefilterpositiontype),
			pipelinefilterid_ref(::std::move(_pipelinefilterid_ref)) {}
	};

	inline PipelineFilterPosition PipelineFilterPosition_Front(PipelineFilterPositionType::PipelineFilterPositionType_Front);
	inline PipelineFilterPosition PipelineFilterPosition_Back(PipelineFilterPositionType::PipelineFilterPositionType_Back);
}

#ifdef YBWLIB2_PIPELINE_EXPOSE_PRIVATE_CLASSES
#include "PipelinePrivateClassDef.h"
#endif

namespace YBWLib2 {
	namespace Internal {
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PipelineID* _pipelineid) noexcept;
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PersistentID* _persistentid_pipelineid) noexcept;

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(Pipeline* _pipeline) noexcept;
		YBWLIB2_API const ISharedLockableObject* YBWLIB2_CALLTYPE Pipeline_CastToISharedLockableObject(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API ISharedLockableObject* YBWLIB2_CALLTYPE Pipeline_CastToISharedLockableObject(Pipeline* _pipeline) noexcept;
		YBWLIB2_API PipelineID YBWLIB2_CALLTYPE Pipeline_GetPipelineID(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockExclusive(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockShared(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API IndexedDataStore* YBWLIB2_CALLTYPE Pipeline_GetUserDataIndexedDataStore(Pipeline* _pipeline) noexcept;
		YBWLIB2_API const IndexedDataStore* YBWLIB2_CALLTYPE Pipeline_GetUserDataIndexedDataStore(const Pipeline* _pipeline) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_GetInvocationDataSize(const Pipeline* _pipeline, already_shared_locked_this_t) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_InitializeInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket** _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_CleanupInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket* _pipelineinvocationpacket, already_shared_locked_this_t) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_IsResolved(const Pipeline* _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept;
		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_IsResolved(const Pipeline* _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept;
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
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_AddRefInvocationPacketDataEntry(
			const Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t _already_shared_locked_this
		) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_DecRefInvocationPacketDataEntry(
			const Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t _already_shared_locked_this
		) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_AttachPipelineFilter(Pipeline* _pipeline, PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_DetachPipelineFilter(Pipeline* _pipeline, PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_Resolve(Pipeline* _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept;

		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PipelineFilterID* _pipelinefilterid) noexcept;
		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PersistentID* _persistentid_pipelinefilterid) noexcept;

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(const PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API PipelineFilterID YBWLIB2_CALLTYPE PipelineFilter_GetPipelineFilterID(const PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API IndexedDataStore* YBWLIB2_CALLTYPE PipelineFilter_GetUserDataIndexedDataStore(PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API const IndexedDataStore* YBWLIB2_CALLTYPE PipelineFilter_GetUserDataIndexedDataStore(const PipelineFilter* _pipelinefilter) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_GetRawInvokeDelegate(const PipelineFilter* _pipelinefilter, const PipelineFilterRawInvokeDelegate** _delegate_rawinvoke_ret) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_ReleaseRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke_ret) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke) noexcept;
		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetPipelineFilterPositionArray(PipelineFilter* _pipelinefilter, const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept;

		YBWLIB2_API const Pipeline* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetPipeline(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API const void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;
		YBWLIB2_API size_t YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataSize(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept;

		YBWLIB2_API PipelineStore* YBWLIB2_CALLTYPE CreatePipelineStore() noexcept;

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineStore_CastToIReferenceCountedObject(const PipelineStore* _pipelinestore) noexcept;
		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineStore_CastToIReferenceCountedObject(PipelineStore* _pipelinestore) noexcept;
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE PipelineStore_ReferencePipelineFromPipelineID(PipelineStore* _pipelinestore, const PipelineID* _pipelineid) noexcept;
	};

	inline ReferenceCountedObjectHolder<Pipeline> CreatePipeline(const PipelineID& _pipelineid) noexcept {
		Pipeline* ptr_pipeline = Internal::CreatePipeline(&_pipelineid);
		assert(ptr_pipeline);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::Pipeline_CastToIReferenceCountedObject(ptr_pipeline);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<Pipeline>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipeline
			);
	}

	inline ReferenceCountedObjectHolder<Pipeline> CreatePipeline(const PersistentID& _persistentid_pipelineid) noexcept {
		Pipeline* ptr_pipeline = Internal::CreatePipeline(&_persistentid_pipelineid);
		assert(ptr_pipeline);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::Pipeline_CastToIReferenceCountedObject(ptr_pipeline);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<Pipeline>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipeline
			);
	}

	inline const ISharedLockableObject& Pipeline_CastToISharedLockableObject(const Pipeline& _pipeline) noexcept {
		return *Internal::Pipeline_CastToISharedLockableObject(&_pipeline);
	}

	inline ISharedLockableObject& Pipeline_CastToISharedLockableObject(Pipeline& _pipeline) noexcept {
		return *Internal::Pipeline_CastToISharedLockableObject(&_pipeline);
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

	inline IndexedDataStore& Pipeline_GetUserDataIndexedDataStore(Pipeline& _pipeline) noexcept {
		return *Internal::Pipeline_GetUserDataIndexedDataStore(&_pipeline);
	}

	inline const IndexedDataStore& Pipeline_GetUserDataIndexedDataStore(const Pipeline& _pipeline) noexcept {
		return *Internal::Pipeline_GetUserDataIndexedDataStore(&_pipeline);
	}

	inline size_t Pipeline_GetInvocationDataSize(const Pipeline& _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		return Internal::Pipeline_GetInvocationDataSize(&_pipeline, _already_shared_locked_this);
	}

	inline void Pipeline_InitializeInvocationPacket(const Pipeline& _pipeline, PipelineInvocationPacket*& _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		Internal::Pipeline_InitializeInvocationPacket(&_pipeline, &_pipelineinvocationpacket_ret, _buf_invocationdata, _size_buf_invocationdata, _already_shared_locked_this);
	}

	inline void Pipeline_CleanupInvocationPacket(const Pipeline& _pipeline, PipelineInvocationPacket*& _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		if (_pipelineinvocationpacket) {
			Internal::Pipeline_CleanupInvocationPacket(&_pipeline, _pipelineinvocationpacket, _already_shared_locked_this);
			_pipelineinvocationpacket = nullptr;
		}
	}

	inline bool Pipeline_IsResolved(const Pipeline& _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept {
		return Internal::Pipeline_IsResolved(&_pipeline, _already_shared_locked_this);
	}

	inline bool Pipeline_IsResolved(const Pipeline& _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		return Internal::Pipeline_IsResolved(&_pipeline, _already_exclusive_locked_this);
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

	inline void Pipeline_AddRefInvocationPacketDataEntry(
		const Pipeline& _pipeline,
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		size_t _offset_invocationpacketdataentry,
		already_shared_locked_this_t _already_shared_locked_this
	) noexcept {
		Internal::Pipeline_AddRefInvocationPacketDataEntry(&_pipeline, &_pipelineinvocationpacketdataentryid, _size_invocationpacketdataentry, _offset_invocationpacketdataentry, _already_shared_locked_this);
	}

	inline void Pipeline_DecRefInvocationPacketDataEntry(
		const Pipeline& _pipeline,
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		size_t _offset_invocationpacketdataentry,
		already_shared_locked_this_t _already_shared_locked_this
	) noexcept {
		Internal::Pipeline_DecRefInvocationPacketDataEntry(&_pipeline, &_pipelineinvocationpacketdataentryid, _size_invocationpacketdataentry, _offset_invocationpacketdataentry, _already_shared_locked_this);
	}

	inline void Pipeline_AttachPipelineFilter(Pipeline& _pipeline, PipelineFilter& _pipelinefilter, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		Internal::Pipeline_AttachPipelineFilter(&_pipeline, &_pipelinefilter, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_this);
	}

	inline void Pipeline_DetachPipelineFilter(Pipeline& _pipeline, PipelineFilter& _pipelinefilter, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		Internal::Pipeline_DetachPipelineFilter(&_pipeline, &_pipelinefilter, _should_resolve_immediately, _already_exclusive_locked_this);
	}

	inline void Pipeline_Resolve(Pipeline& _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		Internal::Pipeline_Resolve(&_pipeline, _already_exclusive_locked_this);
	}

	inline ReferenceCountedObjectHolder<PipelineFilter> CreatePipelineFilter(const PipelineFilterID& _pipelinefilterid) noexcept {
		PipelineFilter* ptr_pipelinefilter = Internal::CreatePipelineFilter(&_pipelinefilterid);
		assert(ptr_pipelinefilter);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::PipelineFilter_CastToIReferenceCountedObject(ptr_pipelinefilter);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<PipelineFilter>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipelinefilter
			);
	}

	inline ReferenceCountedObjectHolder<PipelineFilter> CreatePipelineFilter(const PersistentID& _persistentid_pipelinefilterid) noexcept {
		PipelineFilter* ptr_pipelinefilter = Internal::CreatePipelineFilter(&_persistentid_pipelinefilterid);
		assert(ptr_pipelinefilter);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::PipelineFilter_CastToIReferenceCountedObject(ptr_pipelinefilter);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<PipelineFilter>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipelinefilter
			);
	}

	inline PipelineFilterID PipelineFilter_GetPipelineFilterID(const PipelineFilter& _pipelinefilter) noexcept {
		return Internal::PipelineFilter_GetPipelineFilterID(&_pipelinefilter);
	}

	inline IndexedDataStore& PipelineFilter_GetUserDataIndexedDataStore(PipelineFilter& _pipelinefilter) noexcept {
		return *Internal::PipelineFilter_GetUserDataIndexedDataStore(&_pipelinefilter);
	}

	inline const IndexedDataStore& PipelineFilter_GetUserDataIndexedDataStore(const PipelineFilter& _pipelinefilter) noexcept {
		return *Internal::PipelineFilter_GetUserDataIndexedDataStore(&_pipelinefilter);
	}

	inline const PipelineFilterRawInvokeDelegate& PipelineFilter_GetRawInvokeDelegate(const PipelineFilter& _pipelinefilter) noexcept {
		const PipelineFilterRawInvokeDelegate* delegate_rawinvoke = nullptr;
		Internal::PipelineFilter_GetRawInvokeDelegate(&_pipelinefilter, &delegate_rawinvoke);
		return *delegate_rawinvoke;
	}

	inline PipelineFilterRawInvokeDelegate PipelineFilter_ReleaseRawInvokeDelegate(PipelineFilter& _pipelinefilter) noexcept {
		PipelineFilterRawInvokeDelegate delegate_rawinvoke;
		Internal::PipelineFilter_ReleaseRawInvokeDelegate(&_pipelinefilter, &delegate_rawinvoke);
		return delegate_rawinvoke;
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

	inline ReferenceCountedObjectHolder<PipelineStore> CreatePipelineStore() noexcept {
		PipelineStore* ptr_pipelinestore = Internal::CreatePipelineStore();
		assert(ptr_pipelinestore);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::PipelineStore_CastToIReferenceCountedObject(ptr_pipelinestore);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<PipelineStore>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipelinestore
			);
	}

	inline ReferenceCountedObjectHolder<Pipeline> PipelineStore_ReferencePipelineFromPipelineID(PipelineStore& _pipelinestore, const PipelineID& _pipelineid) noexcept {
		Pipeline* ptr_pipeline = Internal::PipelineStore_ReferencePipelineFromPipelineID(&_pipelinestore, &_pipelineid);
		assert(ptr_pipeline);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::Pipeline_CastToIReferenceCountedObject(ptr_pipeline);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<Pipeline>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipeline
			);
	}

	inline ReferenceCountedObjectHolder<Pipeline> PipelineStore_ReferencePipelineFromPersistentID(PipelineStore& _pipelinestore, const PersistentID& _persistentid_pipelineid) noexcept {
		PipelineID pipelineid(_persistentid_pipelineid);
		Pipeline* ptr_pipeline = Internal::PipelineStore_ReferencePipelineFromPipelineID(&_pipelinestore, &pipelineid);
		assert(ptr_pipeline);
		IReferenceCountedObject* ptr_referencecountedobject = Internal::Pipeline_CastToIReferenceCountedObject(ptr_pipeline);
		assert(ptr_referencecountedobject);
		return ReferenceCountedObjectHolder<Pipeline>(
			ReferenceCountedObjectHolder<IReferenceCountedObject>(::std::move(ptr_referencecountedobject)),
			ptr_pipeline
			);
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
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			is_addref_only(false) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
					::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
					this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						_data_initial_invocationpacketdataentry,
						::std::move(_delegate_initialize_invocationpacketdataentry),
						::std::move(_delegate_cleanup_invocationpacketdataentry),
						already_exclusive_locked_pipeline
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
			already_exclusive_locked_this_t _already_exclusive_locked_pipeline
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			is_addref_only(false) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
					*this->objholder_pipeline,
					this->pipelineinvocationpacketdataentryid,
					this->size_pipelineinvocationpacketdataentry,
					_data_initial_invocationpacketdataentry,
					::std::move(_delegate_initialize_invocationpacketdataentry),
					::std::move(_delegate_cleanup_invocationpacketdataentry),
					_already_exclusive_locked_pipeline
				);
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
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			is_addref_only(false) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				{
					SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
					::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
					this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
						*this->objholder_pipeline,
						this->pipelineinvocationpacketdataentryid,
						this->size_pipelineinvocationpacketdataentry,
						_data_initial_invocationpacketdataentry,
						::std::move(_delegate_initialize_invocationpacketdataentry),
						::std::move(_delegate_cleanup_invocationpacketdataentry),
						_always_assign_delegate_pipelineinvocationpacketdataentry,
						already_exclusive_locked_pipeline
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
			always_assign_delegate_pipelineinvocationpacketdataentry_t _always_assign_delegate_pipelineinvocationpacketdataentry,
			already_exclusive_locked_this_t _already_exclusive_locked_pipeline
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			is_addref_only(false) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				this->offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
					*this->objholder_pipeline,
					this->pipelineinvocationpacketdataentryid,
					this->size_pipelineinvocationpacketdataentry,
					_data_initial_invocationpacketdataentry,
					::std::move(_delegate_initialize_invocationpacketdataentry),
					::std::move(_delegate_cleanup_invocationpacketdataentry),
					_always_assign_delegate_pipelineinvocationpacketdataentry,
					_already_exclusive_locked_pipeline
				);
			}
		}
		PipelineInvocationPacketDataEntryHolder(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t _already_shared_locked_pipeline
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			offset_pipelineinvocationpacketdataentry(_offset_invocationpacketdataentry),
			is_addref_only(true) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			assert(this->pipelineinvocationpacketdataentryid);
			assert(this->objholder_pipeline);
			assert(this->size_pipelineinvocationpacketdataentry);
			assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
			Pipeline_AddRefInvocationPacketDataEntry(
				*this->objholder_pipeline,
				this->pipelineinvocationpacketdataentryid,
				this->size_pipelineinvocationpacketdataentry,
				this->offset_pipelineinvocationpacketdataentry,
				_already_shared_locked_pipeline
			);
		}
		PipelineInvocationPacketDataEntryHolder(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			const ReferenceCountedObjectHolder<Pipeline>& _objholder_pipeline,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry
		) noexcept
			: pipelineinvocationpacketdataentryid(_pipelineinvocationpacketdataentryid),
			//objholder_pipeline(_objholder_pipeline),
			size_pipelineinvocationpacketdataentry(_size_invocationpacketdataentry),
			offset_pipelineinvocationpacketdataentry(_offset_invocationpacketdataentry),
			is_addref_only(true) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(_objholder_pipeline);
			assert(this->pipelineinvocationpacketdataentryid);
			assert(this->objholder_pipeline);
			assert(this->size_pipelineinvocationpacketdataentry);
			assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
			{
				SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
				::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
				Pipeline_AddRefInvocationPacketDataEntry(
					*this->objholder_pipeline,
					this->pipelineinvocationpacketdataentryid,
					this->size_pipelineinvocationpacketdataentry,
					this->offset_pipelineinvocationpacketdataentry,
					already_shared_locked_pipeline
				);
			}
		}
		PipelineInvocationPacketDataEntryHolder(const PipelineInvocationPacketDataEntryHolder& x) noexcept
			: pipelineinvocationpacketdataentryid(x.pipelineinvocationpacketdataentryid),
			//objholder_pipeline(x.objholder_pipeline),
			size_pipelineinvocationpacketdataentry(x.size_pipelineinvocationpacketdataentry),
			offset_pipelineinvocationpacketdataentry(x.offset_pipelineinvocationpacketdataentry),
			is_addref_only(x.is_addref_only) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(x.objholder_pipeline);
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_AddRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						size_t _offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							nullptr,
							PipelineInvocationPacketDataEntryInitializeDelegate(),
							PipelineInvocationPacketDataEntryCleanupDelegate(),
							already_exclusive_locked_pipeline
						);
						static_cast<void>(_offset_pipelineinvocationpacketdataentry);
						assert(_offset_pipelineinvocationpacketdataentry == this->offset_pipelineinvocationpacketdataentry);
					}
				}
			}
		}
		PipelineInvocationPacketDataEntryHolder(PipelineInvocationPacketDataEntryHolder&& x) noexcept
			: pipelineinvocationpacketdataentryid(::std::move(x.pipelineinvocationpacketdataentryid)),
			//objholder_pipeline(::std::move(x.objholder_pipeline)),
			size_pipelineinvocationpacketdataentry(::std::move(x.size_pipelineinvocationpacketdataentry)),
			offset_pipelineinvocationpacketdataentry(::std::move(x.offset_pipelineinvocationpacketdataentry)),
			is_addref_only(::std::move(x.is_addref_only)) {
			// TODO: Remove workaround of compiler bug when no longer necessary.
			this->objholder_pipeline.assign(::std::move(x.objholder_pipeline));
			x.pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			x.objholder_pipeline.reset();
			x.size_pipelineinvocationpacketdataentry = 0;
			x.offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			x.is_addref_only = false;
		}
		~PipelineInvocationPacketDataEntryHolder() {
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_DecRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_pipeline);
					}
				}
			}
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
		}
		PipelineInvocationPacketDataEntryHolder& operator=(const PipelineInvocationPacketDataEntryHolder& x) noexcept {
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_DecRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_pipeline);
					}
				}
			}
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			this->pipelineinvocationpacketdataentryid = x.pipelineinvocationpacketdataentryid;
			this->objholder_pipeline = x.objholder_pipeline;
			this->size_pipelineinvocationpacketdataentry = x.size_pipelineinvocationpacketdataentry;
			this->offset_pipelineinvocationpacketdataentry = x.offset_pipelineinvocationpacketdataentry;
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_AddRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						size_t _offset_pipelineinvocationpacketdataentry = Pipeline_RegisterInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							nullptr,
							PipelineInvocationPacketDataEntryInitializeDelegate(),
							PipelineInvocationPacketDataEntryCleanupDelegate(),
							already_exclusive_locked_pipeline
						);
						static_cast<void>(_offset_pipelineinvocationpacketdataentry);
						assert(_offset_pipelineinvocationpacketdataentry == this->offset_pipelineinvocationpacketdataentry);
					}
				}
			}
			return *this;
		}
		PipelineInvocationPacketDataEntryHolder& operator=(PipelineInvocationPacketDataEntryHolder&& x) noexcept {
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_DecRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_pipeline);
					}
				}
			}
			this->is_addref_only = false;
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
			this->is_addref_only = ::std::move(x.is_addref_only);
			x.is_addref_only = false;
			return *this;
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
		void Clear() noexcept {
			if (this->objholder_pipeline) {
				if (this->is_addref_only) {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
						Pipeline_DecRefInvocationPacketDataEntry(
							*this->objholder_pipeline,
							this->pipelineinvocationpacketdataentryid,
							this->size_pipelineinvocationpacketdataentry,
							this->offset_pipelineinvocationpacketdataentry,
							already_shared_locked_pipeline
						);
					}
				} else {
					assert(this->pipelineinvocationpacketdataentryid);
					assert(this->size_pipelineinvocationpacketdataentry);
					{
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->objholder_pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, already_exclusive_locked_pipeline);
					}
				}
			}
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
		}
		void Clear(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
			this->ClearAddRefOnly();
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				Pipeline_UnregisterInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, _already_exclusive_locked_pipeline);
			}
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
		}
		void Clear(already_shared_locked_this_t _already_shared_locked_pipeline) noexcept {
			this->SetAddRefOnly();
			if (this->objholder_pipeline) {
				assert(this->pipelineinvocationpacketdataentryid);
				assert(this->size_pipelineinvocationpacketdataentry);
				assert(this->offset_pipelineinvocationpacketdataentry != SIZE_MAX);
				Pipeline_DecRefInvocationPacketDataEntry(*this->objholder_pipeline, this->pipelineinvocationpacketdataentryid, this->size_pipelineinvocationpacketdataentry, this->offset_pipelineinvocationpacketdataentry, _already_shared_locked_pipeline);
			}
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
		}
		size_t Release() noexcept {
			size_t _offset_pipelineinvocationpacketdataentry = this->offset_pipelineinvocationpacketdataentry;
			this->is_addref_only = false;
			this->offset_pipelineinvocationpacketdataentry = SIZE_MAX;
			this->size_pipelineinvocationpacketdataentry = 0;
			this->objholder_pipeline.reset();
			this->pipelineinvocationpacketdataentryid = PipelineInvocationPacketDataEntryID();
			return _offset_pipelineinvocationpacketdataentry;
		}
		void ClearAddRefOnly() noexcept { this->is_addref_only = false; }
		void SetAddRefOnly() noexcept { this->is_addref_only = true; }
	protected:
		PipelineInvocationPacketDataEntryID pipelineinvocationpacketdataentryid;
		ReferenceCountedObjectHolder<Pipeline> objholder_pipeline;
		size_t size_pipelineinvocationpacketdataentry = 0;
		size_t offset_pipelineinvocationpacketdataentry = SIZE_MAX;
		bool is_addref_only = false;
	};
	static_assert(::std::is_standard_layout_v<PipelineInvocationPacketDataEntryHolder>, "PipelineInvocationPacketDataEntryHolder is not standard-layout.");

	template<typename T_Data>
	class PipelineInvocationPacketDataEntryHolderWrapper final {
	public:
		static_assert(::std::is_object_v<T_Data>, "The specified type is not an object type.");
		static_assert(::std::is_nothrow_destructible_v<T_Data>, "The specified type is not nothrow-destructible.");
		using data_type = T_Data;
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
		void Clear() noexcept { this->pipelineinvocationpacketdataentryholder.Clear(); }
		void Release() noexcept { this->pipelineinvocationpacketdataentryholder.Release(); }
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

	namespace Internal {
		static constexpr PersistentID persistentid_pipelineinvocationpacketdataentryid_arr_ptr_arg(UUIDFromUUIDString_CompileTime("1163516a-3daa-4f60-a2de-2024054eae72"));
		extern YBWLIB2_API PipelineInvocationPacketDataEntryID pipelineinvocationpacketdataentryid_arr_ptr_arg;
		static constexpr PersistentID persistentid_indexeddataentryid_invokedelegatecontext(UUIDFromUUIDString_CompileTime("7085986b-924d-4ae9-b219-dfa035eafdf1"));
		extern YBWLIB2_API IndexedDataEntryID indexeddataentryid_invokedelegatecontext;
		extern YBWLIB2_API ReferenceCountedObjectHolder<PipelineStore>* pipelinestore_global;
		extern ReferenceCountedObjectHolder<PipelineStore>* pipelinestore_modulelocal;
	}

	inline PipelineStore& GetGlobalPipelineStore() noexcept {
		assert(Internal::pipelinestore_global && *Internal::pipelinestore_global);
		return **Internal::pipelinestore_global;
	}

	inline PipelineStore& GetModuleLocalPipelineStore() noexcept {
		assert(Internal::pipelinestore_modulelocal && *Internal::pipelinestore_modulelocal);
		return **Internal::pipelinestore_modulelocal;
	}

	template<typename... T_Args>
	class PipelineTraits final : public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
	public:
		static constexpr size_t count_arg = sizeof...(T_Args);
	private:
		struct pipelinecontext_t final : public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
			friend class PipelineTraits<T_Args...>;
			constexpr pipelinecontext_t() noexcept = default;
			explicit pipelinecontext_t(ReferenceCountedObjectHolder<Pipeline>&& _pipeline) noexcept
				: pipeline(::std::move(_pipeline)) {
				uintptr_t data_initial_pipelineinvocationpacketdataentry_arr_ptr_arg[count_arg] = {};
				this->pipelineinvocationpacketdataentryholder_arr_ptr_arg = PipelineInvocationPacketDataEntryHolder(
					Internal::pipelineinvocationpacketdataentryid_arr_ptr_arg,
					this->pipeline,
					count_arg * sizeof(uintptr_t),
					reinterpret_cast<const void*>(&data_initial_pipelineinvocationpacketdataentry_arr_ptr_arg),
					PipelineInvocationPacketDataEntryInitializeDelegate(),
					PipelineInvocationPacketDataEntryCleanupDelegate()
				);
			}
			pipelinecontext_t(const pipelinecontext_t& x) noexcept = default;
			pipelinecontext_t(pipelinecontext_t&& x) noexcept = default;
			~pipelinecontext_t() = default;
			pipelinecontext_t& operator=(const pipelinecontext_t& x) noexcept = default;
			pipelinecontext_t& operator=(pipelinecontext_t&& x) noexcept = default;
			const ReferenceCountedObjectHolder<Pipeline>& GetPipelineReferenceCountedObjectHolder() const noexcept { return this->pipeline; }
			ReferenceCountedObjectHolder<Pipeline>& GetPipelineReferenceCountedObjectHolder() noexcept { return this->pipeline; }
		protected:
			ReferenceCountedObjectHolder<Pipeline> pipeline;
			PipelineInvocationPacketDataEntryHolder pipelineinvocationpacketdataentryholder_arr_ptr_arg;
			const uintptr_t* GetPipelineInvocationDataEntry_ArgPtrArr(const PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
				const void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
				assert(ptr_invocationpacketdata);
				size_t offset_pipelineinvocationpacketdataentry = this->pipelineinvocationpacketdataentryholder_arr_ptr_arg.GetDataEntryOffset();
				size_t size_pipelineinvocationpacketdataentry = this->pipelineinvocationpacketdataentryholder_arr_ptr_arg.GetDataEntrySize();
				assert(
					offset_pipelineinvocationpacketdataentry != SIZE_MAX
					&& size_pipelineinvocationpacketdataentry == count_arg * sizeof(uintptr_t)
					&& offset_pipelineinvocationpacketdataentry + size_pipelineinvocationpacketdataentry <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket)
				);
				const uintptr_t* ptr_pipelineinvocationpacketdataentry = reinterpret_cast<const uintptr_t*>(reinterpret_cast<const unsigned char*>(ptr_invocationpacketdata) + offset_pipelineinvocationpacketdataentry);
				assert(!mod_alignment(reinterpret_cast<uintptr_t>(ptr_pipelineinvocationpacketdataentry), (uintptr_t)alignof(uintptr_t)));
				return ptr_pipelineinvocationpacketdataentry;
			}
			uintptr_t* GetPipelineInvocationDataEntry_ArgPtrArr(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
				void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
				assert(ptr_invocationpacketdata);
				size_t offset_pipelineinvocationpacketdataentry = this->pipelineinvocationpacketdataentryholder_arr_ptr_arg.GetDataEntryOffset();
				size_t size_pipelineinvocationpacketdataentry = this->pipelineinvocationpacketdataentryholder_arr_ptr_arg.GetDataEntrySize();
				assert(
					offset_pipelineinvocationpacketdataentry != SIZE_MAX
					&& size_pipelineinvocationpacketdataentry == count_arg * sizeof(uintptr_t)
					&& offset_pipelineinvocationpacketdataentry + size_pipelineinvocationpacketdataentry <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket)
				);
				uintptr_t* ptr_pipelineinvocationpacketdataentry = reinterpret_cast<uintptr_t*>(reinterpret_cast<unsigned char*>(ptr_invocationpacketdata) + offset_pipelineinvocationpacketdataentry);
				assert(!mod_alignment(reinterpret_cast<uintptr_t>(ptr_pipelineinvocationpacketdataentry), (uintptr_t)alignof(uintptr_t)));
				return ptr_pipelineinvocationpacketdataentry;
			}
		};
		struct pipelinefiltercontext_t final : public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
			friend class PipelineTraits<T_Args...>;
			constexpr pipelinefiltercontext_t() noexcept = default;
			explicit pipelinefiltercontext_t(const PipelineFilterID& _pipelinefilterid) noexcept
				: pipelinefilter(CreatePipelineFilter(_pipelinefilterid)) {}
			explicit pipelinefiltercontext_t(const PersistentID& _persistentid_pipelinefilterid) noexcept
				: pipelinefilter(CreatePipelineFilter(_persistentid_pipelinefilterid)) {}
			pipelinefiltercontext_t(const pipelinefiltercontext_t& x) noexcept = default;
			pipelinefiltercontext_t(pipelinefiltercontext_t&& x) noexcept = default;
			~pipelinefiltercontext_t() = default;
			pipelinefiltercontext_t& operator=(const pipelinefiltercontext_t& x) noexcept = default;
			pipelinefiltercontext_t& operator=(pipelinefiltercontext_t&& x) noexcept = default;
			const ReferenceCountedObjectHolder<PipelineFilter>& GetPipelineFilterReferenceCountedObjectHolder() const noexcept { return this->pipelinefilter; }
			ReferenceCountedObjectHolder<PipelineFilter>& GetPipelineFilterReferenceCountedObjectHolder() noexcept { return this->pipelinefilter; }
		protected:
			ReferenceCountedObjectHolder<PipelineFilter> pipelinefilter;
			ReferenceCountedObjectHolder<Pipeline> pipeline;
			struct invokedelegatecontext_t final : public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
				uintptr_t fnptr_invoke_delegate_invoke = 0;
				uintptr_t contextvalue1_delegate_invoke = 0;
				uintptr_t contextvalue2_delegate_invoke = 0;
				DelegateCleanupFnptr fnptr_cleanup_delegate_invoke = nullptr;
				size_t offset_pipelineinvocationpacketdataentry_arr_ptr_arg = SIZE_MAX;
				Pipeline* pipeline = nullptr;
				PipelineFilterRawInvokeDelegate::fnptr_invoke_t fnptr_rawinvoke = nullptr;
				invokedelegatecontext_t() noexcept = default;
				invokedelegatecontext_t(const invokedelegatecontext_t&) = delete;
				invokedelegatecontext_t(invokedelegatecontext_t&& x) = delete;
				~invokedelegatecontext_t() {
					this->fnptr_rawinvoke = nullptr;
					if (this->pipeline) {
						SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*this->pipeline));
						::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
						this->UnassociateWithPipeline(already_exclusive_locked_pipeline);
					}
					this->pipeline = nullptr;
					this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg = SIZE_MAX;
					if (this->fnptr_cleanup_delegate_invoke) {
						(*this->fnptr_cleanup_delegate_invoke)(this->contextvalue1_delegate_invoke, this->contextvalue2_delegate_invoke);
					}
					this->fnptr_cleanup_delegate_invoke = nullptr;
					this->contextvalue2_delegate_invoke = 0;
					this->contextvalue1_delegate_invoke = 0;
					this->fnptr_invoke_delegate_invoke = 0;
				}
				invokedelegatecontext_t& operator=(const invokedelegatecontext_t&) = delete;
				invokedelegatecontext_t& operator=(invokedelegatecontext_t&& x) noexcept = delete;
				const uintptr_t* GetPipelineInvocationDataEntry_ArgPtrArr(const PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
					already_shared_locked_this_t already_shared_locked_pipeline;// The pipeline is shared-locked during invocation.
					static_cast<void>(already_shared_locked_pipeline);
					assert(this->pipeline == PipelineInvocationPacket_GetPipeline(_pipelineinvocationpacket));
					const void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
					assert(ptr_invocationpacketdata);
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg != SIZE_MAX);
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg + count_arg * sizeof(uintptr_t) <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket));
					const uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = reinterpret_cast<const uintptr_t*>(reinterpret_cast<const unsigned char*>(ptr_invocationpacketdata) + offset_pipelineinvocationpacketdataentry_arr_ptr_arg);
					assert(!mod_alignment(reinterpret_cast<uintptr_t>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg), (uintptr_t)alignof(uintptr_t)));
					return ptr_pipelineinvocationpacketdataentry_arr_ptr_arg;
				}
				uintptr_t* GetPipelineInvocationDataEntry_ArgPtrArr(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
					already_shared_locked_this_t already_shared_locked_pipeline;// The pipeline is shared-locked during invocation.
					static_cast<void>(already_shared_locked_pipeline);
					assert(this->pipeline == PipelineInvocationPacket_GetPipeline(_pipelineinvocationpacket));
					void* ptr_invocationpacketdata = PipelineInvocationPacket_GetInvocationPacketDataPtr(_pipelineinvocationpacket);
					assert(ptr_invocationpacketdata);
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg != SIZE_MAX);
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg + count_arg * sizeof(uintptr_t) <= PipelineInvocationPacket_GetInvocationPacketDataSize(_pipelineinvocationpacket));
					uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = reinterpret_cast<uintptr_t*>(reinterpret_cast<unsigned char*>(ptr_invocationpacketdata) + offset_pipelineinvocationpacketdataentry_arr_ptr_arg);
					assert(!mod_alignment(reinterpret_cast<uintptr_t>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg), (uintptr_t)alignof(uintptr_t)));
					return ptr_pipelineinvocationpacketdataentry_arr_ptr_arg;
				}
				template<typename T_Delegate_Invoke>
				void SetInvokeDelegate(T_Delegate_Invoke&& _delegate_invoke, PipelineFilterRawInvokeDelegate::fnptr_invoke_t _fnptr_rawinvoke, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
					static_cast<void>(_already_exclusive_locked_pipeline);
					this->fnptr_rawinvoke = nullptr;
					if (this->fnptr_cleanup_delegate_invoke) {
						(*this->fnptr_cleanup_delegate_invoke)(this->contextvalue1_delegate_invoke, this->contextvalue2_delegate_invoke);
					}
					this->fnptr_cleanup_delegate_invoke = nullptr;
					this->contextvalue2_delegate_invoke = 0;
					this->contextvalue1_delegate_invoke = 0;
					this->fnptr_invoke_delegate_invoke = 0;
					this->fnptr_invoke_delegate_invoke = reinterpret_cast<uintptr_t>(_delegate_invoke.fnptr_invoke);
					this->contextvalue1_delegate_invoke = _delegate_invoke.contextvalue1;
					this->contextvalue2_delegate_invoke = _delegate_invoke.contextvalue2;
					this->fnptr_cleanup_delegate_invoke = _delegate_invoke.fnptr_cleanup;
					this->fnptr_rawinvoke = _fnptr_rawinvoke;
					_delegate_invoke.fnptr_cleanup = nullptr;
					_delegate_invoke.contextvalue2 = 0;
					_delegate_invoke.contextvalue1 = 0;
					_delegate_invoke.fnptr_invoke = nullptr;
				}
				void UnassociateWithPipeline(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
					if (this->pipeline) {
						assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg != SIZE_MAX);
						Pipeline_UnregisterInvocationPacketDataEntry(
							*this->pipeline,
							Internal::pipelineinvocationpacketdataentryid_arr_ptr_arg,
							_already_exclusive_locked_pipeline
						);
						this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg = SIZE_MAX;
					}
					this->pipeline = nullptr;
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg == SIZE_MAX);
				}
				void AssociateWithPipeline(Pipeline* _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
					if (this->pipeline) this->UnassociateWithPipeline(_already_exclusive_locked_pipeline);
					assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg == SIZE_MAX);
					if (_pipeline) {
						this->pipeline = _pipeline;
						void* data_initial_pipelineinvocationpacketdataentry_arr_ptr_arg[count_arg] = {};
						this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg = Pipeline_RegisterInvocationPacketDataEntry(
							*this->pipeline,
							Internal::pipelineinvocationpacketdataentryid_arr_ptr_arg,
							count_arg * sizeof(uintptr_t),
							&data_initial_pipelineinvocationpacketdataentry_arr_ptr_arg,
							PipelineInvocationPacketDataEntryInitializeDelegate(),
							PipelineInvocationPacketDataEntryCleanupDelegate(),
							_already_exclusive_locked_pipeline
						);
						assert(this->offset_pipelineinvocationpacketdataentry_arr_ptr_arg != SIZE_MAX);
					}
				}
			};
			void AssociateWithPipeline(const ReferenceCountedObjectHolder<Pipeline>& _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				static_cast<void>(PipelineFilter_ReleaseRawInvokeDelegate(*this->pipelinefilter));
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				IndexedDataRawValue* indexeddatarawvalue_invokedelegatecontext = indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
				invokedelegatecontext_t* invokedelegatecontext = indexeddatarawvalue_invokedelegatecontext ? reinterpret_cast<invokedelegatecontext_t*>(indexeddatarawvalue_invokedelegatecontext->contextvalue) : nullptr;
				if (invokedelegatecontext) invokedelegatecontext->UnassociateWithPipeline(_already_exclusive_locked_pipeline);
				//this->pipeline = _pipeline;
				// TODO: Remove workaround of compiler bug when no longer necessary.
				this->pipeline.assign(_pipeline);
				if (invokedelegatecontext) {
					invokedelegatecontext->AssociateWithPipeline(this->pipeline.get(), _already_exclusive_locked_pipeline);
					PipelineFilter_SetRawInvokeDelegate(*this->pipelinefilter, PipelineFilterRawInvokeDelegate(invokedelegatecontext->fnptr_rawinvoke, reinterpret_cast<uintptr_t>(invokedelegatecontext)));
				}
			}
			void ClearInvokeDelegateContext(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				if (indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext))
					indexeddatastore_userdata_pipelinefilter.RemoveEntryByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
			}
			template<
				typename... T_Args_Delegate_Invoke,
				size_t... index_arg,
				typename ::std::enable_if<sizeof...(T_Args_Delegate_Invoke) == count_arg && sizeof...(index_arg) == count_arg, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::disjunction<::std::is_convertible<T_Args&&, T_Args_Delegate_Invoke>, ::std::is_convertible<T_Args&, T_Args_Delegate_Invoke>>...>, int>::type = 0
			>
				void SetInvokeDelegateContext(Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>&& _delegate_invoke, ::std::index_sequence<index_arg...>, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				IndexedDataRawValue* indexeddatarawvalue_invokedelegatecontext = indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
				if (!indexeddatarawvalue_invokedelegatecontext)
					indexeddatarawvalue_invokedelegatecontext = &indexeddatastore_userdata_pipelinefilter.AddEntry(Internal::indexeddataentryid_invokedelegatecontext, IndexedDataRawValue(&CleanupIndexedDataRawValue_InvokeDelegateContext, reinterpret_cast<uintptr_t>(new invokedelegatecontext_t())));
				invokedelegatecontext_t& invokedelegatecontext = *reinterpret_cast<invokedelegatecontext_t*>(indexeddatarawvalue_invokedelegatecontext->contextvalue);
				PipelineFilterRawInvokeDelegate::fnptr_invoke_t fnptr_rawinvoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept->void {
					invokedelegatecontext_t* invokedelegatecontext = reinterpret_cast<invokedelegatecontext_t*>(_contextvalue1);
					assert(invokedelegatecontext);
					static_cast<void>(_contextvalue2);
					assert(_pipelineinvocationpacket);
					uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = invokedelegatecontext->GetPipelineInvocationDataEntry_ArgPtrArr(*_pipelineinvocationpacket);
					Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>(
						reinterpret_cast<typename Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>::fnptr_invoke_t>(invokedelegatecontext->fnptr_invoke_delegate_invoke),
						invokedelegatecontext->contextvalue1_delegate_invoke,
						invokedelegatecontext->contextvalue2_delegate_invoke,
						nullptr
						)(static_cast<T_Args_Delegate_Invoke>(*reinterpret_cast<::std::remove_reference_t<T_Args>*>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg[index_arg]))...);
				};
				invokedelegatecontext.SetInvokeDelegate(_delegate_invoke, fnptr_rawinvoke, _already_exclusive_locked_pipeline);
				this->AssociateWithPipeline(this->pipeline, _already_exclusive_locked_pipeline);
			}
			template<
				typename... T_Args_Delegate_Invoke,
				size_t... index_arg,
				typename ::std::enable_if<sizeof...(T_Args_Delegate_Invoke) == count_arg && sizeof...(index_arg) == count_arg, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::disjunction<::std::is_convertible<T_Args&&, T_Args_Delegate_Invoke>, ::std::is_convertible<T_Args&, T_Args_Delegate_Invoke>>...>, int>::type = 0
			>
				void SetInvokeDelegateContext(Delegate<DelegateFlag_Noexcept, void, PipelineInvocationPacket&, T_Args_Delegate_Invoke...>&& _delegate_invoke, ::std::index_sequence<index_arg...>, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				IndexedDataRawValue* indexeddatarawvalue_invokedelegatecontext = indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
				if (!indexeddatarawvalue_invokedelegatecontext)
					indexeddatarawvalue_invokedelegatecontext = &indexeddatastore_userdata_pipelinefilter.AddEntry(Internal::indexeddataentryid_invokedelegatecontext, IndexedDataRawValue(&CleanupIndexedDataRawValue_InvokeDelegateContext, reinterpret_cast<uintptr_t>(new invokedelegatecontext_t())));
				invokedelegatecontext_t& invokedelegatecontext = *reinterpret_cast<invokedelegatecontext_t*>(indexeddatarawvalue_invokedelegatecontext->contextvalue);
				PipelineFilterRawInvokeDelegate::fnptr_invoke_t fnptr_rawinvoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept->void {
					invokedelegatecontext_t* invokedelegatecontext = reinterpret_cast<invokedelegatecontext_t*>(_contextvalue1);
					assert(invokedelegatecontext);
					static_cast<void>(_contextvalue2);
					assert(_pipelineinvocationpacket);
					uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = invokedelegatecontext->GetPipelineInvocationDataEntry_ArgPtrArr(*_pipelineinvocationpacket);
					Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>(
						reinterpret_cast<typename Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>::fnptr_invoke_t>(invokedelegatecontext->fnptr_invoke_delegate_invoke),
						invokedelegatecontext->contextvalue1_delegate_invoke,
						invokedelegatecontext->contextvalue2_delegate_invoke,
						nullptr
						)(*_pipelineinvocationpacket, static_cast<T_Args_Delegate_Invoke>(*reinterpret_cast<::std::remove_reference_t<T_Args>*>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg[index_arg]))...);
				};
				invokedelegatecontext.SetInvokeDelegate(_delegate_invoke, fnptr_rawinvoke, _already_exclusive_locked_pipeline);
				this->AssociateWithPipeline(this->pipeline, _already_exclusive_locked_pipeline);
			}
			template<
				typename... T_Args_Delegate_Invoke,
				size_t... index_arg,
				typename ::std::enable_if<sizeof...(T_Args_Delegate_Invoke) == count_arg && sizeof...(index_arg) == count_arg, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::is_pointer<T_Args_Delegate_Invoke>...>, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::is_convertible<::std::remove_reference_t<T_Args>*, T_Args_Delegate_Invoke>...>, int>::type = 0
			>
				void SetInvokeDelegateContext(Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>&& _delegate_invoke, ::std::index_sequence<index_arg...>, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				IndexedDataRawValue* indexeddatarawvalue_invokedelegatecontext = indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
				if (!indexeddatarawvalue_invokedelegatecontext)
					indexeddatarawvalue_invokedelegatecontext = &indexeddatastore_userdata_pipelinefilter.AddEntry(Internal::indexeddataentryid_invokedelegatecontext, IndexedDataRawValue(&CleanupIndexedDataRawValue_InvokeDelegateContext, reinterpret_cast<uintptr_t>(new invokedelegatecontext_t())));
				invokedelegatecontext_t& invokedelegatecontext = *reinterpret_cast<invokedelegatecontext_t*>(indexeddatarawvalue_invokedelegatecontext->contextvalue);
				PipelineFilterRawInvokeDelegate::fnptr_invoke_t fnptr_rawinvoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept->void {
					invokedelegatecontext_t* invokedelegatecontext = reinterpret_cast<invokedelegatecontext_t*>(_contextvalue1);
					assert(invokedelegatecontext);
					static_cast<void>(_contextvalue2);
					assert(_pipelineinvocationpacket);
					uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = invokedelegatecontext->GetPipelineInvocationDataEntry_ArgPtrArr(*_pipelineinvocationpacket);
					Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>(
						reinterpret_cast<typename Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>::fnptr_invoke_t>(invokedelegatecontext->fnptr_invoke_delegate_invoke),
						invokedelegatecontext->contextvalue1_delegate_invoke,
						invokedelegatecontext->contextvalue2_delegate_invoke,
						nullptr
						)(static_cast<T_Args_Delegate_Invoke>(reinterpret_cast<::std::remove_reference_t<T_Args>*>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg[index_arg]))...);
				};
				invokedelegatecontext.SetInvokeDelegate(_delegate_invoke, fnptr_rawinvoke, _already_exclusive_locked_pipeline);
				this->AssociateWithPipeline(this->pipeline, _already_exclusive_locked_pipeline);
			}
			template<
				typename... T_Args_Delegate_Invoke,
				size_t... index_arg,
				typename ::std::enable_if<sizeof...(T_Args_Delegate_Invoke) == count_arg && sizeof...(index_arg) == count_arg, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::is_pointer<T_Args_Delegate_Invoke>...>, int>::type = 0,
				typename ::std::enable_if<::std::conjunction_v<::std::is_convertible<::std::remove_reference_t<T_Args>*, T_Args_Delegate_Invoke>...>, int>::type = 0
			>
				void SetInvokeDelegateContext(Delegate<DelegateFlag_Noexcept, void, PipelineInvocationPacket*, T_Args_Delegate_Invoke...>&& _delegate_invoke, ::std::index_sequence<index_arg...>, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
				IndexedDataStore& indexeddatastore_userdata_pipelinefilter = PipelineFilter_GetUserDataIndexedDataStore(*this->pipelinefilter);
				IndexedDataRawValue* indexeddatarawvalue_invokedelegatecontext = indexeddatastore_userdata_pipelinefilter.GetRawValueByEntryID(Internal::indexeddataentryid_invokedelegatecontext);
				if (!indexeddatarawvalue_invokedelegatecontext)
					indexeddatarawvalue_invokedelegatecontext = &indexeddatastore_userdata_pipelinefilter.AddEntry(Internal::indexeddataentryid_invokedelegatecontext, IndexedDataRawValue(&CleanupIndexedDataRawValue_InvokeDelegateContext, reinterpret_cast<uintptr_t>(new invokedelegatecontext_t())));
				invokedelegatecontext_t& invokedelegatecontext = *reinterpret_cast<invokedelegatecontext_t*>(indexeddatarawvalue_invokedelegatecontext->contextvalue);
				PipelineFilterRawInvokeDelegate::fnptr_invoke_t fnptr_rawinvoke = [](uintptr_t _contextvalue1, uintptr_t _contextvalue2, PipelineInvocationPacket* _pipelineinvocationpacket) noexcept->void {
					invokedelegatecontext_t* invokedelegatecontext = reinterpret_cast<invokedelegatecontext_t*>(_contextvalue1);
					assert(invokedelegatecontext);
					static_cast<void>(_contextvalue2);
					assert(_pipelineinvocationpacket);
					uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = invokedelegatecontext->GetPipelineInvocationDataEntry_ArgPtrArr(*_pipelineinvocationpacket);
					Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>(
						reinterpret_cast<typename Delegate<DelegateFlag_Noexcept, void, T_Args_Delegate_Invoke...>::fnptr_invoke_t>(invokedelegatecontext->fnptr_invoke_delegate_invoke),
						invokedelegatecontext->contextvalue1_delegate_invoke,
						invokedelegatecontext->contextvalue2_delegate_invoke,
						nullptr
						)(_pipelineinvocationpacket, static_cast<T_Args_Delegate_Invoke>(reinterpret_cast<::std::remove_reference_t<T_Args>*>(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg[index_arg]))...);
				};
				invokedelegatecontext.SetInvokeDelegate(_delegate_invoke, fnptr_rawinvoke, _already_exclusive_locked_pipeline);
				this->AssociateWithPipeline(this->pipeline, _already_exclusive_locked_pipeline);
			}
		private:
			static void CleanupIndexedDataRawValue_InvokeDelegateContext(IndexedDataRawValue* _indexeddatarawvalue) noexcept {
				if (_indexeddatarawvalue) {
					invokedelegatecontext_t* invokedelegatecontext = reinterpret_cast<invokedelegatecontext_t*>(_indexeddatarawvalue->contextvalue);
					if (invokedelegatecontext) {
						delete invokedelegatecontext;
						invokedelegatecontext = nullptr;
					}
				}
			}
		};
	public:
		using pipelinecontext_type = pipelinecontext_t;
		using pipelinefiltercontext_type = pipelinefiltercontext_t;
		static PipelineID GetPipelineID(const pipelinecontext_type& _pipelinecontext) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			const Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			return Pipeline_GetPipelineID(pipeline);
		}
		static IndexedDataStore& GetPipelineUserDataIndexedDataStore(pipelinecontext_type& _pipelinecontext) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			return Pipeline_GetUserDataIndexedDataStore(pipeline);
		}
		static const IndexedDataStore& GetPipelineUserDataIndexedDataStore(const pipelinecontext_type& _pipelinecontext) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			const Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			return Pipeline_GetUserDataIndexedDataStore(pipeline);
		}
		static bool IsPipelineResolved(const pipelinecontext_type& _pipelinecontext, already_shared_locked_this_t _already_shared_locked_pipeline) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			const Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			return Pipeline_IsResolved(pipeline, _already_shared_locked_pipeline);
		}
		static bool IsPipelineResolved(const pipelinecontext_type& _pipelinecontext, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			const Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			return Pipeline_IsResolved(pipeline, _already_exclusive_locked_pipeline);
		}
		template<
			typename T_Callable_PreInvoke,
			typename T_Callable_PostInvoke,
			typename ::std::enable_if<::std::is_nothrow_invocable_v<T_Callable_PreInvoke&&, const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t>, int>::type = 0,
			typename ::std::enable_if<::std::is_nothrow_invocable_v<T_Callable_PostInvoke&&, const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t>, int>::type = 0
		>
			static void InvokePipeline(
				const pipelinecontext_type& _pipelinecontext,
				T_Callable_PreInvoke&& _callable_preinvoke,
				T_Callable_PostInvoke&& _callable_postinvoke,
				T_Args... _args
			) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			const Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(pipeline));
			::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
			size_t size_invocationdata = Pipeline_GetInvocationDataSize(pipeline, already_shared_locked_pipeline);
#if defined(YBWLIB2_NO_ALLOCA)
			::std::unique_ptr<::std::max_align_t[]> uniqueptr_buf_invocationdata(new ::std::max_align_t[(size_invocationdata - 1) / sizeof(::std::max_align_t) + 1]);
			void* buf_invocationdata = static_cast<void*>(uniqueptr_buf_invocationdata.get());
#elif defined(_MSC_VER)
			void* buf_invocationdata = _malloca(size_invocationdata);
#else
			void* buf_invocationdata = alloca(size_invocationdata);
#endif
			assert(buf_invocationdata);
			PipelineInvocationPacket* pipelineinvocationpacket = nullptr;
			Pipeline_InitializeInvocationPacket(pipeline, pipelineinvocationpacket, buf_invocationdata, size_invocationdata, already_shared_locked_pipeline);
			assert(pipelineinvocationpacket);
			{
				uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = _pipelinecontext.GetPipelineInvocationDataEntry_ArgPtrArr(*pipelineinvocationpacket);
				((*(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg++) = reinterpret_cast<uintptr_t>(::std::addressof(_args))), ...);
			}
			::std::invoke(::std::forward<T_Callable_PreInvoke>(_callable_preinvoke), pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			Pipeline_RawInvoke(pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			::std::invoke(::std::forward<T_Callable_PostInvoke>(_callable_postinvoke), pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			Pipeline_CleanupInvocationPacket(pipeline, pipelineinvocationpacket, already_shared_locked_pipeline);
#if !defined(YBWLIB2_NO_ALLOCA) && defined(_MSC_VER)
			_freea(buf_invocationdata); buf_invocationdata = nullptr;
#else
			buf_invocationdata = nullptr;
#endif
		}
		template<
			typename T_Callable_PreInvoke,
			typename T_Callable_PostInvoke,
			typename ::std::enable_if<::std::is_nothrow_invocable_v<T_Callable_PreInvoke&&, const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t>, int>::type = 0,
			typename ::std::enable_if<::std::is_nothrow_invocable_v<T_Callable_PostInvoke&&, const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t>, int>::type = 0
		>
			static void InvokePipeline(
				pipelinecontext_type& _pipelinecontext,
				T_Callable_PreInvoke&& _callable_preinvoke,
				T_Callable_PostInvoke&& _callable_postinvoke,
				T_Args... _args
			) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(pipeline));
			::std::shared_lock<SharedLockableObjectToSTLWrapper> shared_lock_pipeline(sharedlockablewrapper_pipeline); already_shared_locked_this_t already_shared_locked_pipeline;
			while (!Pipeline_IsResolved(pipeline, already_shared_locked_pipeline)) {
				shared_lock_pipeline.unlock();
				{
					::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
					Pipeline_Resolve(pipeline, already_exclusive_locked_pipeline);
				}
				shared_lock_pipeline.lock();
			}
			size_t size_invocationdata = Pipeline_GetInvocationDataSize(pipeline, already_shared_locked_pipeline);
#if defined(YBWLIB2_NO_ALLOCA)
			::std::unique_ptr<::std::max_align_t[]> uniqueptr_buf_invocationdata(new ::std::max_align_t[(size_invocationdata - 1) / sizeof(::std::max_align_t) + 1]);
			void* buf_invocationdata = static_cast<void*>(uniqueptr_buf_invocationdata.get());
#elif defined(_MSC_VER)
			void* buf_invocationdata = _malloca(size_invocationdata);
#else
			void* buf_invocationdata = alloca(size_invocationdata);
#endif
			assert(buf_invocationdata);
			PipelineInvocationPacket* pipelineinvocationpacket = nullptr;
			Pipeline_InitializeInvocationPacket(pipeline, pipelineinvocationpacket, buf_invocationdata, size_invocationdata, already_shared_locked_pipeline);
			assert(pipelineinvocationpacket);
			{
				uintptr_t* ptr_pipelineinvocationpacketdataentry_arr_ptr_arg = _pipelinecontext.GetPipelineInvocationDataEntry_ArgPtrArr(*pipelineinvocationpacket);
				((*(ptr_pipelineinvocationpacketdataentry_arr_ptr_arg++) = reinterpret_cast<uintptr_t>(::std::addressof(_args))), ...);
			}
			::std::invoke(::std::forward<T_Callable_PreInvoke>(_callable_preinvoke), pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			Pipeline_RawInvoke(pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			::std::invoke(::std::forward<T_Callable_PostInvoke>(_callable_postinvoke), pipeline, *pipelineinvocationpacket, already_shared_locked_pipeline);
			Pipeline_CleanupInvocationPacket(pipeline, pipelineinvocationpacket, already_shared_locked_pipeline);
#if !defined(YBWLIB2_NO_ALLOCA) && defined(_MSC_VER)
			_freea(buf_invocationdata); buf_invocationdata = nullptr;
#else
			buf_invocationdata = nullptr;
#endif
		}
		static void ResolvePipeline(pipelinecontext_type& _pipelinecontext, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			Pipeline_Resolve(pipeline, _already_exclusive_locked_pipeline);
		}
		static void ResolvePipeline(pipelinecontext_type& _pipelinecontext) noexcept {
			assert(_pipelinecontext.GetPipelineReferenceCountedObjectHolder());
			Pipeline& pipeline = *_pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(pipeline));
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			Pipeline_Resolve(pipeline, already_exclusive_locked_pipeline);
		}
		static PipelineFilterID GetPipelineFilterID(const pipelinefiltercontext_type& _pipelinefiltercontext) noexcept {
			assert(_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder());
			const PipelineFilter& pipelinefilter = *_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
			return PipelineFilter_GetPipelineFilterID(pipelinefilter);
		}
		static IndexedDataStore& GetPipelineFilterUserDataIndexedDataStore(pipelinefiltercontext_type& _pipelinefiltercontext) noexcept {
			assert(_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder());
			PipelineFilter& pipelinefilter = *_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
			return PipelineFilter_GetUserDataIndexedDataStore(pipelinefilter);
		}
		static const IndexedDataStore& GetPipelineFilterUserDataIndexedDataStore(const pipelinefiltercontext_type& _pipelinefiltercontext) noexcept {
			assert(_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder());
			const PipelineFilter& pipelinefilter = *_pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
			return PipelineFilter_GetUserDataIndexedDataStore(pipelinefilter);
		}
		static void ClearPipelineFilterInvokeDelegate(pipelinefiltercontext_t& _pipelinefiltercontext) noexcept {
			::std::optional<SharedLockableObjectToSTLWrapper> optional_sharedlockablewrapper_pipeline;
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline; already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			if (_pipelinefiltercontext.pipeline) {
				optional_sharedlockablewrapper_pipeline.emplace(Pipeline_CastToISharedLockableObject(*_pipelinefiltercontext.pipeline));
				unique_lock_pipeline = ::std::unique_lock<SharedLockableObjectToSTLWrapper>(*optional_sharedlockablewrapper_pipeline);
			}
			assert(_pipelinefiltercontext.pipelinefilter);
			_pipelinefiltercontext.ClearInvokeDelegateContext(already_exclusive_locked_pipeline);
		}
	private:
		template<typename... T_Args>
		struct sfinae_SetInvokeDelegateContext final {
			using type = decltype(::std::declval<pipelinefiltercontext_t>().SetInvokeDelegateContext(::std::declval<T_Args>()..., ::std::declval<already_exclusive_locked_this_t>()));
			using is_nothrow = ::std::bool_constant<noexcept(::std::declval<pipelinefiltercontext_t>().SetInvokeDelegateContext(::std::declval<T_Args>()..., ::std::declval<already_exclusive_locked_this_t>()))>;
			static constexpr bool is_nothrow_v = is_nothrow::value;
		};
		template<typename... T_Args>
		using sfinae_SetInvokeDelegateContext_t = typename sfinae_SetInvokeDelegateContext<T_Args...>::type;
	public:
		template<
			typename T_Delegate_Invoke,
			typename ::std::enable_if<is_detected_v<sfinae_SetInvokeDelegateContext_t, T_Delegate_Invoke&&, ::std::make_index_sequence<count_arg>>, int>::type = 0
		>
			static void SetPipelineFilterInvokeDelegate(pipelinefiltercontext_t& _pipelinefiltercontext, T_Delegate_Invoke&& _delegate_invoke) noexcept {
			::std::optional<SharedLockableObjectToSTLWrapper> optional_sharedlockablewrapper_pipeline;
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline; already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			if (_pipelinefiltercontext.pipeline) {
				optional_sharedlockablewrapper_pipeline.emplace(Pipeline_CastToISharedLockableObject(*_pipelinefiltercontext.pipeline));
				unique_lock_pipeline = ::std::unique_lock<SharedLockableObjectToSTLWrapper>(*optional_sharedlockablewrapper_pipeline);
			}
			assert(_pipelinefiltercontext.pipelinefilter);
			_pipelinefiltercontext.SetInvokeDelegateContext(::std::forward<T_Delegate_Invoke>(_delegate_invoke), ::std::make_index_sequence<count_arg>(), already_exclusive_locked_pipeline);
		}
		static void SetPipelineFilterPositionArray(pipelinefiltercontext_t& _pipelinefiltercontext, const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept {
			::std::optional<SharedLockableObjectToSTLWrapper> optional_sharedlockablewrapper_pipeline;
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline; already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			if (_pipelinefiltercontext.pipeline) {
				optional_sharedlockablewrapper_pipeline.emplace(Pipeline_CastToISharedLockableObject(*_pipelinefiltercontext.pipeline));
				unique_lock_pipeline = ::std::unique_lock<SharedLockableObjectToSTLWrapper>(*optional_sharedlockablewrapper_pipeline);
			}
			static_cast<void>(already_exclusive_locked_pipeline);
			assert(_pipelinefiltercontext.pipelinefilter);
			PipelineFilter_SetPipelineFilterPositionArray(*_pipelinefiltercontext.pipelinefilter, _arr_pipelinefilterposition, _size_pipelinefilterposition);
		}
		static void AttachPipelineFilter(pipelinefiltercontext_t& _pipelinefiltercontext, pipelinecontext_t& _pipelinecontext, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
			assert(_pipelinefiltercontext.pipelinefilter);
			PipelineFilter& pipelinefilter = *_pipelinefiltercontext.pipelinefilter;
			assert(_pipelinecontext.pipeline);
			Pipeline& pipeline = *_pipelinecontext.pipeline;
			assert(!_pipelinefiltercontext.pipeline);
			_pipelinefiltercontext.AssociateWithPipeline(_pipelinecontext.pipeline, _already_exclusive_locked_pipeline);
			Pipeline_AttachPipelineFilter(pipeline, pipelinefilter, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		}
		static void AttachPipelineFilter(pipelinefiltercontext_t& _pipelinefiltercontext, pipelinecontext_t& _pipelinecontext, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) noexcept {
			assert(_pipelinecontext.pipeline);
			SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*_pipelinecontext.pipeline));
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			AttachPipelineFilter(_pipelinefiltercontext, _pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_pipeline);
		}
		static void DetachPipelineFilter(pipelinefiltercontext_t& _pipelinefiltercontext, pipelinecontext_t& _pipelinecontext, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) noexcept {
			assert(_pipelinefiltercontext.pipelinefilter);
			PipelineFilter& pipelinefilter = *_pipelinefiltercontext.pipelinefilter;
			assert(_pipelinecontext.pipeline);
			Pipeline& pipeline = *_pipelinecontext.pipeline;
			assert(_pipelinefiltercontext.pipeline == _pipelinecontext.pipeline);
			Pipeline_DetachPipelineFilter(pipeline, pipelinefilter, _should_resolve_immediately, _already_exclusive_locked_pipeline);
			_pipelinefiltercontext.AssociateWithPipeline(ReferenceCountedObjectHolder<Pipeline>(), _already_exclusive_locked_pipeline);
		}
		static void DetachPipelineFilter(pipelinefiltercontext_t& _pipelinefiltercontext, pipelinecontext_t& _pipelinecontext, bool _should_resolve_immediately) noexcept {
			assert(_pipelinecontext.pipeline);
			SharedLockableObjectToSTLWrapper sharedlockablewrapper_pipeline(Pipeline_CastToISharedLockableObject(*_pipelinefiltercontext.pipeline));
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(sharedlockablewrapper_pipeline); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
			DetachPipelineFilter(_pipelinefiltercontext, _pipelinecontext, _should_resolve_immediately, already_exclusive_locked_pipeline);
		}
	};

	template<typename T_PipelineTraits>
	class PipelineFilterWrapper;
	template<typename T_PipelineTraits>
	class PipelineWrapper;

	template<typename T_PipelineTraits>
	class PipelineFilterWrapper final {
		friend class PipelineWrapper<T_PipelineTraits>;
	public:
		using pipelinetraits_type = T_PipelineTraits;
		constexpr PipelineFilterWrapper() noexcept = default;
		PipelineFilterWrapper(const PipelineFilterID& _pipelinefilterid) noexcept : pipelinefiltercontext(_pipelinefilterid) {}
		PipelineFilterWrapper(const PersistentID& _persistentid_pipelinefilterid) noexcept : pipelinefiltercontext(_persistentid_pipelinefilterid) {}
		PipelineFilterWrapper(const PipelineFilterWrapper& x) noexcept = default;
		PipelineFilterWrapper(PipelineFilterWrapper&& x) noexcept = default;
		~PipelineFilterWrapper() = default;
		PipelineFilterWrapper& operator=(const PipelineFilterWrapper& x) noexcept = default;
		PipelineFilterWrapper& operator=(PipelineFilterWrapper&& x) noexcept = default;
		explicit operator bool() const noexcept {
			return static_cast<bool>(this->pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder());
		}
		explicit operator ReferenceCountedObjectHolder<PipelineFilter>() const noexcept {
			return this->pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
		}
		const PipelineFilter& GetPipelineFilter() const noexcept {
			const ReferenceCountedObjectHolder<PipelineFilter>& pipelinefilter = this->pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
			assert(pipelinefilter);
			return *pipelinefilter;
		}
		PipelineFilter& GetPipelineFilter() noexcept {
			ReferenceCountedObjectHolder<PipelineFilter>& pipelinefilter = this->pipelinefiltercontext.GetPipelineFilterReferenceCountedObjectHolder();
			assert(pipelinefilter);
			return *pipelinefilter;
		}
		PipelineFilterID GetPipelineFilterID() const noexcept {
			return pipelinetraits_type::GetPipelineFilterID(this->pipelinefiltercontext);
		}
		const PipelineFilter& operator*() const noexcept { return this->GetPipelineFilter(); }
		PipelineFilter& operator*() noexcept { return this->GetPipelineFilter(); }
		const PipelineFilter* operator->() const noexcept { return &this->GetPipelineFilter(); }
		PipelineFilter* operator->() noexcept { return &this->GetPipelineFilter(); }
		IndexedDataStore& GetUserDataIndexedDataStore() noexcept {
			return pipelinetraits_type::GetPipelineFilterUserDataIndexedDataStore(this->pipelinefiltercontext);
		}
		const IndexedDataStore& GetUserDataIndexedDataStore() const noexcept {
			return pipelinetraits_type::GetPipelineFilterUserDataIndexedDataStore(this->pipelinefiltercontext);
		}
		PipelineFilterWrapper& ClearInvokeDelegate() & noexcept {
			pipelinetraits_type::ClearPipelineFilterInvokeDelegate(this->pipelinefiltercontext);
			return *this;
		}
		PipelineFilterWrapper&& ClearInvokeDelegate() && noexcept {
			pipelinetraits_type::ClearPipelineFilterInvokeDelegate(this->pipelinefiltercontext);
			return ::std::move(*this);
		}
		template<typename T_Delegate_Invoke>
		PipelineFilterWrapper& SetInvokeDelegate(T_Delegate_Invoke&& _delegate_invoke) & noexcept {
			pipelinetraits_type::SetPipelineFilterInvokeDelegate(this->pipelinefiltercontext, ::std::move(_delegate_invoke));
			return *this;
		}
		template<typename T_Delegate_Invoke>
		PipelineFilterWrapper&& SetInvokeDelegate(T_Delegate_Invoke&& _delegate_invoke) && noexcept {
			pipelinetraits_type::SetPipelineFilterInvokeDelegate(this->pipelinefiltercontext, ::std::move(_delegate_invoke));
			return ::std::move(*this);
		}
		PipelineFilterWrapper& SetPipelineFilterPositionArray(const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) & noexcept {
			pipelinetraits_type::SetPipelineFilterPositionArray(this->pipelinefiltercontext, _arr_pipelinefilterposition, _size_pipelinefilterposition);
			return *this;
		}
		PipelineFilterWrapper&& SetPipelineFilterPositionArray(const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) && noexcept {
			pipelinetraits_type::SetPipelineFilterPositionArray(this->pipelinefiltercontext, _arr_pipelinefilterposition, _size_pipelinefilterposition);
			return ::std::move(*this);
		}
		template<size_t _size_pipelinefilterposition>
		PipelineFilterWrapper& SetPipelineFilterPositionArray(const PipelineFilterPosition(&_arr_pipelinefilterposition)[_size_pipelinefilterposition]) & noexcept {
			return this->SetPipelineFilterPositionArray(_arr_pipelinefilterposition, _size_pipelinefilterposition);
		}
		template<size_t _size_pipelinefilterposition>
		PipelineFilterWrapper&& SetPipelineFilterPositionArray(const PipelineFilterPosition(&_arr_pipelinefilterposition)[_size_pipelinefilterposition]) && noexcept {
			return this->SetPipelineFilterPositionArray(_arr_pipelinefilterposition, _size_pipelinefilterposition);
		}
		template<size_t _size_pipelinefilterposition>
		PipelineFilterWrapper& SetPipelineFilterPositionArray(const ::std::array<PipelineFilterPosition, _size_pipelinefilterposition>& _arr_pipelinefilterposition) & noexcept {
			return this->SetPipelineFilterPositionArray(_arr_pipelinefilterposition.data(), _arr_pipelinefilterposition.size());
		}
		template<size_t _size_pipelinefilterposition>
		PipelineFilterWrapper&& SetPipelineFilterPositionArray(const ::std::array<PipelineFilterPosition, _size_pipelinefilterposition>& _arr_pipelinefilterposition) && noexcept {
			return this->SetPipelineFilterPositionArray(_arr_pipelinefilterposition.data(), _arr_pipelinefilterposition.size());
		}
		PipelineFilterWrapper& SetPipelineFilterPositionArray(const ::std::vector<PipelineFilterPosition>& _vec_pipelinefilterposition) & noexcept {
			return this->SetPipelineFilterPositionArray(_vec_pipelinefilterposition.data(), _vec_pipelinefilterposition.size());
		}
		PipelineFilterWrapper&& SetPipelineFilterPositionArray(const ::std::vector<PipelineFilterPosition>& _vec_pipelinefilterposition) && noexcept {
			return this->SetPipelineFilterPositionArray(_vec_pipelinefilterposition.data(), _vec_pipelinefilterposition.size());
		}
		PipelineFilterWrapper& SetPipelineFilterPositionArray(const PipelineFilterPosition& _pipelinefilterposition) & noexcept {
			return this->SetPipelineFilterPositionArray(&_pipelinefilterposition, 1);
		}
		PipelineFilterWrapper&& SetPipelineFilterPositionArray(const PipelineFilterPosition& _pipelinefilterposition) && noexcept {
			return this->SetPipelineFilterPositionArray(&_pipelinefilterposition, 1);
		}
		PipelineFilterWrapper& AttachToPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept;
		PipelineFilterWrapper& AttachToPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			return this->AttachToPipeline(_pipelinewrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		}
		PipelineFilterWrapper&& AttachToPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept;
		PipelineFilterWrapper&& AttachToPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			return ::std::move(*this).AttachToPipeline(_pipelinewrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		}
		PipelineFilterWrapper& AttachToPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) & noexcept;
		PipelineFilterWrapper& AttachToPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) & noexcept {
			return this->AttachToPipeline(_pipelinewrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		}
		PipelineFilterWrapper&& AttachToPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) && noexcept;
		PipelineFilterWrapper&& AttachToPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) && noexcept {
			return ::std::move(*this).AttachToPipeline(_pipelinewrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		}
		PipelineFilterWrapper& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept;
		PipelineFilterWrapper& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			return this->DetachFromPipeline(_pipelinewrapper, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		}
		PipelineFilterWrapper&& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept;
		PipelineFilterWrapper&& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			return ::std::move(*this).DetachFromPipeline(_pipelinewrapper, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		}
		PipelineFilterWrapper& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately) & noexcept;
		PipelineFilterWrapper& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately) & noexcept {
			return this->DetachFromPipeline(_pipelinewrapper, _should_resolve_immediately);
		}
		PipelineFilterWrapper&& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately) && noexcept;
		PipelineFilterWrapper&& DetachFromPipeline(PipelineWrapper<pipelinetraits_type>&& _pipelinewrapper, bool _should_resolve_immediately) && noexcept {
			return ::std::move(*this).DetachFromPipeline(_pipelinewrapper, _should_resolve_immediately);
		}
	protected:
		typename pipelinetraits_type::pipelinefiltercontext_type pipelinefiltercontext;
	};

	template<typename T_PipelineTraits>
	class PipelineWrapper final {
		friend class PipelineFilterWrapper<T_PipelineTraits>;
	public:
		using pipelinetraits_type = T_PipelineTraits;
		constexpr PipelineWrapper() noexcept = default;
		PipelineWrapper(const ReferenceCountedObjectHolder<Pipeline>& _pipeline) noexcept : pipelinecontext(ReferenceCountedObjectHolder<Pipeline>(_pipeline)) {}
		PipelineWrapper(ReferenceCountedObjectHolder<Pipeline>&& _pipeline) noexcept : pipelinecontext(::std::move(_pipeline)) {}
		PipelineWrapper(PipelineStore& _pipelinestore, const PipelineID& _pipelineid) noexcept : pipelinecontext(PipelineStore_ReferencePipelineFromPipelineID(_pipelinestore, _pipelineid)) {}
		PipelineWrapper(PipelineStore& _pipelinestore, const PersistentID& _persistentid_pipelineid) noexcept : pipelinecontext(PipelineStore_ReferencePipelineFromPersistentID(_pipelinestore, _persistentid_pipelineid)) {}
		PipelineWrapper(const PipelineWrapper& x) noexcept = default;
		PipelineWrapper(PipelineWrapper&& x) noexcept = default;
		~PipelineWrapper() = default;
		PipelineWrapper& operator=(const PipelineWrapper& x) noexcept = default;
		PipelineWrapper& operator=(PipelineWrapper&& x) noexcept = default;
		explicit operator bool() const noexcept {
			return static_cast<bool>(this->pipelinecontext.GetPipelineReferenceCountedObjectHolder());
		}
		explicit operator ReferenceCountedObjectHolder<Pipeline>() const noexcept {
			return this->pipelinecontext.GetPipelineReferenceCountedObjectHolder();
		}
		const Pipeline& GetPipeline() const noexcept {
			const ReferenceCountedObjectHolder<Pipeline>& pipeline = this->pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			assert(pipeline);
			return *pipeline;
		}
		Pipeline& GetPipeline() noexcept {
			ReferenceCountedObjectHolder<Pipeline>& pipeline = this->pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			assert(pipeline);
			return *pipeline;
		}
		PipelineID GetPipelineID() const noexcept {
			return pipelinetraits_type::GetPipelineID(this->pipelinecontext);
		}
		SharedLockableObjectToSTLWrapper&& GetPipelineSharedLockableWrapper() const noexcept {
			const ReferenceCountedObjectHolder<Pipeline>& pipeline = this->pipelinecontext.GetPipelineReferenceCountedObjectHolder();
			assert(pipeline);
			return SharedLockableObjectToSTLWrapper(Pipeline_CastToISharedLockableObject(*pipeline));
		}
		const Pipeline& operator*() const noexcept { return this->GetPipeline(); }
		Pipeline& operator*() noexcept { return this->GetPipeline(); }
		const Pipeline* operator->() const noexcept { return &this->GetPipeline(); }
		Pipeline* operator->() noexcept { return &this->GetPipeline(); }
	private:
		template<typename... T_Args>
		struct sfinae_InvokePipeline final {
			using type = decltype(pipelinetraits_type::InvokePipeline(::std::declval<T_Args>()...));
			using is_nothrow = ::std::bool_constant<noexcept(pipelinetraits_type::InvokePipeline(::std::declval<T_Args>()...))>;
			static constexpr bool is_nothrow_v = is_nothrow::value;
		};
		template<typename... T_Args>
		using sfinae_InvokePipeline_t = typename sfinae_InvokePipeline<T_Args...>::type;
	public:
		template<
			typename... T_Args,
			typename T_Callable_PreInvoke,
			typename T_Callable_PostInvoke,
			typename ::std::enable_if<sizeof...(T_Args) == pipelinetraits_type::count_arg, int>::type = 0,
			typename ::std::enable_if<is_detected_v<sfinae_InvokePipeline_t, const typename pipelinetraits_type::pipelinecontext_type&, T_Callable_PreInvoke&&, T_Callable_PostInvoke&&, T_Args&&...>, int>::type = 0,
			typename ::std::enable_if<sfinae_InvokePipeline<const typename pipelinetraits_type::pipelinecontext_type&, T_Callable_PreInvoke&&, T_Callable_PostInvoke&&, T_Args&&...>::is_nothrow_v, int>::type = 0
		>
			void operator()(
				T_Callable_PreInvoke&& _callable_preinvoke,
				T_Callable_PostInvoke&& _callable_postinvoke,
				T_Args&&... _args
				) const noexcept {
			pipelinetraits_type::InvokePipeline(
				this->pipelinecontext,
				::std::forward<T_Callable_PreInvoke>(_callable_preinvoke),
				::std::forward<T_Callable_PostInvoke>(_callable_postinvoke),
				::std::forward<T_Args>(_args)...
			);
		}
		template<
			typename... T_Args,
			typename ::std::enable_if<sizeof...(T_Args) == pipelinetraits_type::count_arg, int>::type = 0,
			typename ::std::enable_if<is_detected_v<sfinae_InvokePipeline_t, const typename pipelinetraits_type::pipelinecontext_type&, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, T_Args&&...>, int>::type = 0,
			typename ::std::enable_if<sfinae_InvokePipeline<const typename pipelinetraits_type::pipelinecontext_type&, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, T_Args&&...>::is_nothrow_v, int>::type = 0
		>
			void operator()(T_Args&&... _args) const noexcept {
			pipelinetraits_type::InvokePipeline(
				this->pipelinecontext,
				[](const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept->void {},
				[](const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept->void {},
				::std::forward<T_Args>(_args)...
			);
		}
		template<
			typename... T_Args,
			typename T_Callable_PreInvoke,
			typename T_Callable_PostInvoke,
			typename ::std::enable_if<sizeof...(T_Args) == pipelinetraits_type::count_arg, int>::type = 0,
			typename ::std::enable_if<is_detected_v<sfinae_InvokePipeline_t, typename pipelinetraits_type::pipelinecontext_type&, T_Callable_PreInvoke&&, T_Callable_PostInvoke&&, T_Args&&...>, int>::type = 0,
			typename ::std::enable_if<sfinae_InvokePipeline<typename pipelinetraits_type::pipelinecontext_type&, T_Callable_PreInvoke&&, T_Callable_PostInvoke&&, T_Args&&...>::is_nothrow_v, int>::type = 0
		>
			void operator()(
				T_Callable_PreInvoke&& _callable_preinvoke,
				T_Callable_PostInvoke&& _callable_postinvoke,
				T_Args&&... _args
				) noexcept {
			pipelinetraits_type::InvokePipeline(
				this->pipelinecontext,
				::std::forward<T_Callable_PreInvoke>(_callable_preinvoke),
				::std::forward<T_Callable_PostInvoke>(_callable_postinvoke),
				::std::forward<T_Args>(_args)...
			);
		}
		template<
			typename... T_Args,
			typename ::std::enable_if<sizeof...(T_Args) == pipelinetraits_type::count_arg, int>::type = 0,
			typename ::std::enable_if<is_detected_v<sfinae_InvokePipeline_t, typename pipelinetraits_type::pipelinecontext_type&, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, T_Args&&...>, int>::type = 0,
			typename ::std::enable_if<sfinae_InvokePipeline<typename pipelinetraits_type::pipelinecontext_type&, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, void (*)(const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept, T_Args&&...>::is_nothrow_v, int>::type = 0
		>
			void operator()(T_Args&&... _args) noexcept {
			pipelinetraits_type::InvokePipeline(
				this->pipelinecontext,
				[](const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept->void {},
				[](const Pipeline&, PipelineInvocationPacket&, already_shared_locked_this_t) noexcept->void {},
				::std::forward<T_Args>(_args)...
			);
		}
		IndexedDataStore& GetUserDataIndexedDataStore() noexcept {
			return pipelinetraits_type::GetPipelineUserDataIndexedDataStore(this->pipelinecontext);
		}
		const IndexedDataStore& GetPipelineUserDataIndexedDataStore() const noexcept {
			return pipelinetraits_type::GetUserDataIndexedDataStore(this->pipelinecontext);
		}
		bool IsResolved(already_shared_locked_this_t _already_shared_locked_pipeline) const noexcept {
			return pipelinetraits_type::IsPipelineResolved(this->pipelinecontext, _already_shared_locked_pipeline);
		}
		bool IsResolved(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) const noexcept {
			return pipelinetraits_type::IsPipelineResolved(this->pipelinecontext, _already_exclusive_locked_pipeline);
		}
		PipelineWrapper& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			pipelinetraits_type::AttachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
			return *this;
		}
		PipelineWrapper& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			return this->AttachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		}
		PipelineWrapper&& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			pipelinetraits_type::AttachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
			return ::std::move(*this);
		}
		PipelineWrapper&& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			return ::std::move(*this).AttachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		}
		PipelineWrapper& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) & noexcept {
			pipelinetraits_type::AttachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
			return *this;
		}
		PipelineWrapper& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) & noexcept {
			return this->AttachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		}
		PipelineWrapper&& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) && noexcept {
			pipelinetraits_type::AttachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
			return ::std::move(*this);
		}
		PipelineWrapper&& AttachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) && noexcept {
			return ::std::move(*this).AttachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		}
		PipelineWrapper& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			pipelinetraits_type::DetachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _already_exclusive_locked_pipeline);
			return *this;
		}
		PipelineWrapper& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			return this->DetachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		}
		PipelineWrapper&& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			pipelinetraits_type::DetachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately, _already_exclusive_locked_pipeline);
			return ::std::move(*this);
		}
		PipelineWrapper&& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			return ::std::move(*this).DetachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		}
		PipelineWrapper& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately) & noexcept {
			pipelinetraits_type::DetachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately);
			return *this;
		}
		PipelineWrapper& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately) & noexcept {
			return this->DetachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately);
		}
		PipelineWrapper&& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>& _pipelinefilterwrapper, bool _should_resolve_immediately) && noexcept {
			pipelinetraits_type::DetachPipelineFilter(_pipelinefilterwrapper.pipelinefiltercontext, this->pipelinecontext, _should_resolve_immediately);
			return ::std::move(*this);
		}
		PipelineWrapper&& DetachPipelineFilter(PipelineFilterWrapper<pipelinetraits_type>&& _pipelinefilterwrapper, bool _should_resolve_immediately) && noexcept {
			return ::std::move(*this).DetachPipelineFilter(_pipelinefilterwrapper, _should_resolve_immediately);
		}
		PipelineWrapper& Resolve(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
			pipelinetraits_type::ResolvePipeline(this->pipelinecontext, _already_exclusive_locked_pipeline);
			return *this;
		}
		PipelineWrapper&& Resolve(already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
			pipelinetraits_type::ResolvePipeline(this->pipelinecontext, _already_exclusive_locked_pipeline);
			return ::std::move(*this);
		}
		PipelineWrapper& Resolve() & noexcept {
			pipelinetraits_type::ResolvePipeline(this->pipelinecontext);
			return *this;
		}
		PipelineWrapper&& Resolve() && noexcept {
			pipelinetraits_type::ResolvePipeline(this->pipelinecontext);
			return ::std::move(*this);
		}
	protected:
		typename pipelinetraits_type::pipelinecontext_type pipelinecontext;
	};

	template<typename T_PipelineTraits>
	inline PipelineFilterWrapper<T_PipelineTraits>& PipelineFilterWrapper<T_PipelineTraits>::AttachToPipeline(PipelineWrapper<T_PipelineTraits>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
		T_PipelineTraits::AttachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		return *this;
	}

	template<typename T_PipelineTraits>
	inline PipelineFilterWrapper<T_PipelineTraits>&& PipelineFilterWrapper<T_PipelineTraits>::AttachToPipeline(PipelineWrapper<T_PipelineTraits>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
		T_PipelineTraits::AttachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_pipeline);
		return ::std::move(*this);
	}

	template<typename T_PipelineTraits>
	inline PipelineFilterWrapper<T_PipelineTraits>& PipelineFilterWrapper<T_PipelineTraits>::AttachToPipeline(PipelineWrapper<T_PipelineTraits>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) & noexcept {
		T_PipelineTraits::AttachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		return *this;
	}

	template<typename T_PipelineTraits>
	inline PipelineFilterWrapper<T_PipelineTraits>&& PipelineFilterWrapper<T_PipelineTraits>::AttachToPipeline(PipelineWrapper<T_PipelineTraits>& _pipelinewrapper, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret) && noexcept {
		T_PipelineTraits::AttachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret);
		return ::std::move(*this);
	}

	template<typename T_PipelineTraits>
	PipelineFilterWrapper<T_PipelineTraits>& PipelineFilterWrapper<T_PipelineTraits>::DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) & noexcept {
		pipelinetraits_type::DetachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		return *this;
	}

	template<typename T_PipelineTraits>
	PipelineFilterWrapper<T_PipelineTraits>&& PipelineFilterWrapper<T_PipelineTraits>::DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_pipeline) && noexcept {
		pipelinetraits_type::DetachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately, _already_exclusive_locked_pipeline);
		return ::std::move(*this);
	}

	template<typename T_PipelineTraits>
	PipelineFilterWrapper<T_PipelineTraits>& PipelineFilterWrapper<T_PipelineTraits>::DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately) & noexcept {
		pipelinetraits_type::DetachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately);
		return *this;
	}

	template<typename T_PipelineTraits>
	PipelineFilterWrapper<T_PipelineTraits>&& PipelineFilterWrapper<T_PipelineTraits>::DetachFromPipeline(PipelineWrapper<pipelinetraits_type>& _pipelinewrapper, bool _should_resolve_immediately) && noexcept {
		pipelinetraits_type::DetachPipelineFilter(this->pipelinefiltercontext, _pipelinewrapper.pipelinecontext, _should_resolve_immediately);
		return ::std::move(*this);
	}

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
