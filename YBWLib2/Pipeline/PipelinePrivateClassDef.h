#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_87D870BC_1E98_49D6_A6AC_DA2C3254F458
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_2BE238AE_E961_4FF3_9D2D_E924DC57B445
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_AFCFE979_884B_4181_8162_AD8D8905AD78
#define _INCLUDE_GUARD_AFCFE979_884B_4181_8162_AD8D8905AD78

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <optional>
#include <array>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>
#include <mutex>
#include <shared_mutex>
#if !defined(YBWLIB2_NO_ALLOCA) && defined(_MSC_VER)
#include <malloc.h>
#endif
#include <thread>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"

namespace YBWLib2 {
	class Pipeline final
		: public ReferenceCountedObject,
		public RecursiveSharedLockableObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Pipeline, , "9c669745-6208-4ed7-ad40-8e085c74cc73");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Pipeline);
		static constexpr size_t size_slot_invocationpacketdata = PipelineInvocationPacketDataSlotSize;
		static constexpr size_t align_slot_invocationpacketdata = PipelineInvocationPacketDataSlotAlign;
		const PipelineID pipelineid;
		explicit Pipeline(
			const PipelineID& _pipelineid
			) noexcept : pipelineid(_pipelineid), indexeddatastore_userdata(rawallocator_crt_YBWLib2) {}
		explicit Pipeline(
			const PersistentID& _persistentid_pipelineid
			) noexcept : pipelineid(_persistentid_pipelineid), indexeddatastore_userdata(rawallocator_crt_YBWLib2) {}
		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;
		virtual ~Pipeline() {
			already_exclusive_locked_this_t already_exclusive_locked_this;
			::std::vector<ReferenceCountedObjectHolder<PipelineFilter>> vec_pipelinefilter_pending_detach;
			for (const ::std::pair<const PipelineFilterID, PipelineFilterAttachment>& val_map_pipelinefilterattachment : this->map_pipelinefilterattachment) {
				if (!val_map_pipelinefilterattachment.second.IsZombie()) {
					assert(val_map_pipelinefilterattachment.second.pipelinefilter);
					// TODO: Remove workaround of compiler bug when no longer necessary.
					//vec_pipelinefilter_pending_detach.push_back(val_map_pipelinefilterattachment.second.pipelinefilter);
					vec_pipelinefilter_pending_detach.push_back(ReferenceCountedObjectHolder<PipelineFilter>());
					vec_pipelinefilter_pending_detach.back().assign(val_map_pipelinefilterattachment.second.pipelinefilter);
				}
			}
			for (const ReferenceCountedObjectHolder<PipelineFilter>& pipelinefilter_pending_detach : vec_pipelinefilter_pending_detach)
				this->DetachPipelineFilter(pipelinefilter_pending_detach.get(), false, already_exclusive_locked_this);
		}
		Pipeline& operator=(const Pipeline&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;
		PipelineID GetPipelineID() const noexcept { return this->pipelineid; }
		IndexedDataStore& GetUserDataIndexedDataStore() noexcept {
			return this->indexeddatastore_userdata;
		}
		const IndexedDataStore& GetUserDataIndexedDataStore() const noexcept {
			return this->indexeddatastore_userdata;
		}
		size_t GetInvocationDataSize(already_shared_locked_this_t) const noexcept;
		void InitializeInvocationPacket(PipelineInvocationPacket*& _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t) const noexcept;
		void CleanupInvocationPacket(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t) const noexcept;
		bool IsResolved(already_shared_locked_this_t) const noexcept;
		bool IsResolved(already_exclusive_locked_this_t) const noexcept;
		void RawInvoke(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t) const noexcept;
		size_t RegisterInvocationPacketDataEntry(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
			already_exclusive_locked_this_t
			) noexcept;
		size_t RegisterInvocationPacketDataEntry(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
			always_assign_delegate_pipelineinvocationpacketdataentry_t,
			already_exclusive_locked_this_t
			) noexcept;
		void UnregisterInvocationPacketDataEntry(const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t) noexcept;
		void AddRefInvocationPacketDataEntry(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t
			) const noexcept;
		void DecRefInvocationPacketDataEntry(
			const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t
			) const noexcept;
		void AttachPipelineFilter(PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t) noexcept;
		void DetachPipelineFilter(PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, already_exclusive_locked_this_t) noexcept;
		void Resolve(already_exclusive_locked_this_t) noexcept;
	protected:
		struct PipelineInvocationPacketDataEntry final {
			size_t idx_slot = SIZE_MAX;
			size_t count_slot = 0;
			mutable ::std::atomic<uintptr_t> refcount = 0;
			::std::unique_ptr<unsigned char[]> data_initial_invocationpacketdataentry;
			PipelineInvocationPacketDataEntryInitializeDelegate delegate_initialize;
			PipelineInvocationPacketDataEntryCleanupDelegate delegate_cleanup;
			PipelineInvocationPacketDataEntry() noexcept = default;
			PipelineInvocationPacketDataEntry(const PipelineInvocationPacketDataEntry&) = delete;
			PipelineInvocationPacketDataEntry(PipelineInvocationPacketDataEntry&& x) noexcept {
				this->idx_slot = ::std::move(x.idx_slot);
				x.idx_slot = SIZE_MAX;
				this->count_slot = ::std::move(x.count_slot);
				x.count_slot = 0;
				this->refcount.store(x.refcount.load(::std::memory_order_relaxed), ::std::memory_order_relaxed);
				x.refcount.store(0, ::std::memory_order_relaxed);
				this->data_initial_invocationpacketdataentry = ::std::move(x.data_initial_invocationpacketdataentry);
				x.data_initial_invocationpacketdataentry.reset();
				this->delegate_initialize = ::std::move(x.delegate_initialize);
				this->delegate_cleanup = ::std::move(x.delegate_cleanup);
			}
			~PipelineInvocationPacketDataEntry() = default;
			PipelineInvocationPacketDataEntry& operator=(const PipelineInvocationPacketDataEntry&) = delete;
			PipelineInvocationPacketDataEntry& operator=(PipelineInvocationPacketDataEntry&& x) noexcept {
				this->delegate_cleanup = PipelineInvocationPacketDataEntryCleanupDelegate();
				this->delegate_initialize = PipelineInvocationPacketDataEntryInitializeDelegate();
				this->data_initial_invocationpacketdataentry.reset();
				this->refcount.store(0, ::std::memory_order_relaxed);
				this->count_slot = 0;
				this->idx_slot = SIZE_MAX;
				this->idx_slot = ::std::move(x.idx_slot);
				x.idx_slot = SIZE_MAX;
				this->count_slot = ::std::move(x.count_slot);
				x.count_slot = 0;
				this->refcount.store(x.refcount.load(::std::memory_order_relaxed), ::std::memory_order_relaxed);
				x.refcount.store(0, ::std::memory_order_relaxed);
				this->data_initial_invocationpacketdataentry = ::std::move(x.data_initial_invocationpacketdataentry);
				x.data_initial_invocationpacketdataentry.reset();
				this->delegate_initialize = ::std::move(x.delegate_initialize);
				this->delegate_cleanup = ::std::move(x.delegate_cleanup);
				return *this;
			}
		};
		struct PipelineFilterAttachment final {
			PipelineFilterID pipelinefilterid;
			ReferenceCountedObjectHolder<PipelineFilter> pipelinefilter;
			size_t idx_pipelinefilterposition_resolve = SIZE_MAX;
			::std::list<PipelineFilterAttachment*>::iterator it_list_pipelinefilterattachment_invocation;
			::std::vector<PipelineFilterPosition> vec_pipelinefilterposition_zombie;
			PipelineFilterAttachment() noexcept {}
			PipelineFilterAttachment(const PipelineFilterAttachment&) = delete;
			PipelineFilterAttachment(PipelineFilterAttachment&&) = delete;
			~PipelineFilterAttachment() = default;
			PipelineFilterAttachment& operator=(const PipelineFilterAttachment&) = delete;
			PipelineFilterAttachment& operator=(PipelineFilterAttachment&&) = delete;
			/// <summary>
			/// Whether this pipeline filter attachment is in zombie state.
			/// When a pipeline filter is being detached, the corresponding attachment becomes zombie until the dependencies are resolved, allowing the pipeline filter to be released.
			/// Such a zombie attachment is merely a placeholder for dependency resolution, and doesn't represent an actual attached pipeline filter.
			/// </summary>
			bool IsZombie() const noexcept { return !this->pipelinefilter; }
		};
		using map_invocationpacketdataentry_t = ::std::unordered_map<PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry>;
		using map_slot_invocationpacketdata_rangeboundary_t = ::std::map<size_t, bool>;
		using map_slot_invocationpacketdata_size_t = ::std::map<::std::tuple<size_t, size_t>, map_slot_invocationpacketdata_rangeboundary_t::iterator, ::std::less<>>;
		using map_pipelinefilterattachment_t = ::std::unordered_map<PipelineFilterID, PipelineFilterAttachment>;
		using map_ptr_pipelinefilterattachment_t = ::std::unordered_map<PipelineFilterID, PipelineFilterAttachment*>;
		using map_ptr_pipelinefilterattachment_dependency_t = ::std::map<::std::tuple<PipelineFilterID, PipelineFilterID>, PipelineFilterAttachment*, ::std::less<>>;
		/// <summary>A <c>::std::shared_mutex</c> object used to control concurrent accesses to this object.</summary>
		mutable ::std::shared_mutex mtx_this;
		/// <summary>
		/// Another <c>::std::shared_mutex</c> object used to prevent resource starvation of threads waiting to exclusively lock the object.
		/// <c>LockShared</c> and <c>TryLockShared</c> acquires shared ownership of this mutex before locking <c>mtx_this</c> and releases this mutex after locking (NOT unlocking) <c>mtx_this</c>.
		/// </summary>
		mutable ::std::shared_mutex mtx_this_prelock;
		IndexedDataStore indexeddatastore_userdata;
		mutable ::std::atomic<bool> should_scan_map_invocationpacketdataentry = false;
		size_t count_slot_invocationpacketdata = 0;
		map_invocationpacketdataentry_t map_invocationpacketdataentry;
		map_slot_invocationpacketdata_rangeboundary_t map_slot_invocationpacketdata_rangeboundary_free;
		map_slot_invocationpacketdata_size_t map_slot_invocationpacketdata_size_free;
		/// <summary>An unordered map from pipeline filter IDs to <c>PipelineFilterAttachment</c> objects.</summary>
		map_pipelinefilterattachment_t map_pipelinefilterattachment;
		/// <summary>
		/// A doubly-linked list of references to <c>PipelineFilterAttachment</c> objects.
		/// This list represents the chain of invocation of this pipeline.
		/// </summary>
		::std::list<PipelineFilterAttachment*> list_pipelinefilterattachment_invocation;
		/// <summary>
		/// An unordered map that contains references to <c>PipelineFilterAttachment</c> objects that represent floating pipeline filter attachments.
		/// Floating pipeline filter attachments correspond to pipeline filters that have just been attached or detached, but whose dependency relationships have not been resolved yet.
		/// After resolving the dependencies, this map becomes empty, and invocations can take place.
		/// </summary>
		map_ptr_pipelinefilterattachment_t map_pipelinefilterattachment_floating;
		/// <summary>
		/// An unordered map that contains references to <c>PipelineFilterAttachment</c> objects that represent unchained pipeline filter attachments.
		/// Unchained pipeline filter attachments correspond to pipeline filters that have been attached and are not floating, but would not be invoked because of unsatisfied dependencies.
		/// </summary>
		map_ptr_pipelinefilterattachment_t map_pipelinefilterattachment_unchained;
		/// <summary>
		/// An unordered map that represents currently active dependencies between pipeline filter attachments.
		/// The first <c>PipelineFilterID</c> in the key represents the depended pipeline filter attachment.
		/// The second <c>PipelineFilterID</c> in the key represents the dependent pipeline filter attachment.
		/// The mapped value is a pointer to the dependent pipeline filter attachment.
		/// </summary>
		map_ptr_pipelinefilterattachment_dependency_t map_pipelinefilterattachment_dependency_current;
		/// <summary>
		/// An unordered map that represents dependencies between pipeline filter attachments that are being expected.
		/// When an expected depended pipeline filter attachment becomes chained, the dependent pipeline filter attachment re-chains to the depended one.
		/// The first <c>PipelineFilterID</c> in the key represents the depended pipeline filter attachment.
		/// The second <c>PipelineFilterID</c> in the key represents the dependent pipeline filter attachment.
		/// The mapped value is a pointer to the dependent pipeline filter attachment.
		/// </summary>
		map_ptr_pipelinefilterattachment_dependency_t map_pipelinefilterattachment_dependency_expecting;
		size_t AllocateInvocationPacketData(size_t _count_slot_invocationpacketdata_allocate, already_exclusive_locked_this_t) noexcept;
		void DeallocateInvocationPacketData(size_t _idx_slot_invocationpacketdata_deallocate, size_t _count_slot_invocationpacketdata_deallocate, already_exclusive_locked_this_t) noexcept;
		void AdjustPipelineFilterAttachmentDependencyMapsInitialize(PipelineFilterAttachment& _pipelinefilterattachment, already_exclusive_locked_this_t) noexcept;
		void AdjustPipelineFilterAttachmentDependencyMapsClear(PipelineFilterAttachment& _pipelinefilterattachment, already_exclusive_locked_this_t) noexcept;
		void AdjustPipelineFilterAttachmentDependencyMaps(PipelineFilterAttachment& _pipelinefilterattachment, size_t _idx_pipelinefilterposition_resolve_new, already_exclusive_locked_this_t) noexcept;
	};

	class PipelineFilter final : public ReferenceCountedObject {
		friend class Pipeline;
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(PipelineFilter);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(PipelineFilter);
		using delegate_rawinvoke_type = PipelineFilterRawInvokeDelegate;
		const PipelineFilterID pipelinefilterid;
		explicit PipelineFilter(
			const PipelineFilterID& _pipelinefilterid
			) noexcept : pipelinefilterid(_pipelinefilterid), indexeddatastore_userdata(rawallocator_crt_YBWLib2) {}
		explicit PipelineFilter(
			const PersistentID& _persistentid_pipelinefilterid
			) noexcept : pipelinefilterid(_persistentid_pipelinefilterid), indexeddatastore_userdata(rawallocator_crt_YBWLib2) {}
		PipelineFilter(const PipelineFilter&) = delete;
		PipelineFilter(PipelineFilter&&) = delete;
		virtual ~PipelineFilter() {}
		PipelineFilter& operator=(const PipelineFilter&) = delete;
		PipelineFilter& operator=(PipelineFilter&&) = delete;
		PipelineFilterID GetPipelineFilterID() const noexcept { return this->pipelinefilterid; }
		IndexedDataStore& GetUserDataIndexedDataStore() noexcept {
			return this->indexeddatastore_userdata;
		}
		const IndexedDataStore& GetUserDataIndexedDataStore() const noexcept {
			return this->indexeddatastore_userdata;
		}
		void GetRawInvokeDelegate(const delegate_rawinvoke_type** _delegate_rawinvoke_ret) const noexcept {
			assert(_delegate_rawinvoke_ret);
			*_delegate_rawinvoke_ret = &this->delegate_rawinvoke;
		}
		void RawInvoke(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
			if (this->delegate_rawinvoke) {
				this->delegate_rawinvoke(&_pipelineinvocationpacket);
			}
		}
		void ReleaseRawInvokeDelegate(delegate_rawinvoke_type* _delegate_rawinvoke_ret) noexcept {
			assert(!this->pipeline);
			assert(_delegate_rawinvoke_ret);
			*_delegate_rawinvoke_ret = ::std::move(this->delegate_rawinvoke);
		}
		void SetRawInvokeDelegate(delegate_rawinvoke_type* _delegate_rawinvoke) noexcept {
			assert(!this->pipeline);
			assert(_delegate_rawinvoke);
			this->delegate_rawinvoke = ::std::move(*_delegate_rawinvoke);
		}
		void SetPipelineFilterPositionArray(const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept {
			assert(!this->pipeline);
			assert(_arr_pipelinefilterposition || !_size_pipelinefilterposition);
			this->vec_pipelinefilterposition.assign(_arr_pipelinefilterposition, _arr_pipelinefilterposition + _size_pipelinefilterposition);
		}
	protected:
		IndexedDataStore indexeddatastore_userdata;
		delegate_rawinvoke_type delegate_rawinvoke;
		::std::vector<PipelineFilterPosition> vec_pipelinefilterposition;
		Pipeline* pipeline = nullptr;
	};

	class PipelineInvocationPacket final {
	public:
		constexpr PipelineInvocationPacket() noexcept = default;
		PipelineInvocationPacket(
			const Pipeline* _pipeline,
			void* _ptr_invocationpacketdata,
			size_t _size_invocationpacketdata
			) noexcept
			: ptr_invocationpacketdata(_ptr_invocationpacketdata),
			size_invocationpacketdata(_size_invocationpacketdata),
			pipeline(_pipeline) {}
		PipelineInvocationPacket(const PipelineInvocationPacket&) = delete;
		PipelineInvocationPacket(PipelineInvocationPacket&&) = delete;
		~PipelineInvocationPacket() = default;
		PipelineInvocationPacket& operator=(const PipelineInvocationPacket&) = delete;
		PipelineInvocationPacket& operator=(PipelineInvocationPacket&&) = delete;
		const Pipeline* GetPipeline() const noexcept { return this->pipeline; }
		const void* GetInvocationPacketDataPtr() const noexcept { return this->ptr_invocationpacketdata; }
		void* GetInvocationPacketDataPtr() noexcept { return this->ptr_invocationpacketdata; }
		size_t GetInvocationPacketDataSize() const noexcept { return this->size_invocationpacketdata; }
	protected:
		void* ptr_invocationpacketdata = nullptr;
		size_t size_invocationpacketdata = 0;
		const Pipeline* pipeline = nullptr;
	};

	class PipelineStore final : public ReferenceCountedObject {
	public:
		PipelineStore() noexcept(false) {}
		PipelineStore(const PipelineStore&) = delete;
		PipelineStore(PipelineStore&&) = delete;
		virtual ~PipelineStore() = default;
		PipelineStore& operator=(const PipelineStore&) = delete;
		PipelineStore& operator=(PipelineStore&&) = delete;
		Pipeline* ReferencePipelineFromPipelineID(const PipelineID& _pipelineid) noexcept;
	protected:
		using map_pipeline_t = ::std::unordered_map<PipelineID, ReferenceCountedObjectHolder<Pipeline>>;
		::std::shared_mutex mtx_this;
		map_pipeline_t map_pipeline;
	};
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_2BE238AE_E961_4FF3_9D2D_E924DC57B445
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_2BE238AE_E961_4FF3_9D2D_E924DC57B445
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_87D870BC_1E98_49D6_A6AC_DA2C3254F458
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_87D870BC_1E98_49D6_A6AC_DA2C3254F458
#endif
