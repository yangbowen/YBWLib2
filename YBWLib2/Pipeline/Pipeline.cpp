#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <map>
#include <shared_mutex>
#include <thread>
#include "../DynamicType/DynamicType.h"
#include "Pipeline.h"

namespace YBWLib2 {
	class Pipeline final : public SharedPtrReferenceCountedObject<Pipeline> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(Pipeline);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(Pipeline);
		static constexpr size_t size_slot_invocationpacketdata = PipelineInvocationPacketDataSlotSize;
		static constexpr size_t align_slot_invocationpacketdata = PipelineInvocationPacketDataSlotAlign;
		const PipelineID pipelineid;
		Pipeline(
			const PersistentID& _persistentid_pipelineid
		) noexcept : pipelineid(_persistentid_pipelineid) {}
		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;
		virtual ~Pipeline() {}
		Pipeline& operator=(const Pipeline&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;
		PipelineID GetPipelineID() const noexcept { return this->pipelineid; }
		void LockExclusive() const noexcept {
			if (!map_lockcount_recursive) map_lockcount_recursive = new ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>();
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.second);
			++it_map_lockcount_recursive->second.first;
			this->mtx_this_prelock.lock();
			this->mtx_this.lock();
			this->mtx_this_prelock.unlock();
		}
		bool TryLockExclusive() const noexcept {
			if (!map_lockcount_recursive) map_lockcount_recursive = new ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>();
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.second);
			if (this->mtx_this.try_lock()) {
				++it_map_lockcount_recursive->second.first;
				return true;
			} else {
				return false;
			}
		}
		void UnlockExclusive() const noexcept {
			this->mtx_this.unlock();
			assert(map_lockcount_recursive);
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->find(this);
			assert(it_map_lockcount_recursive != map_lockcount_recursive->end());
			assert(it_map_lockcount_recursive->second.first && !it_map_lockcount_recursive->second.second);
			--it_map_lockcount_recursive->second.first;
		}
		void LockShared() const noexcept {
			if (!map_lockcount_recursive) map_lockcount_recursive = new ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>();
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.first);
			++it_map_lockcount_recursive->second.second;
			this->mtx_this_prelock.lock_shared();
			this->mtx_this.lock_shared();
			this->mtx_this_prelock.unlock_shared();
		}
		bool TryLockShared() const noexcept {
			if (!map_lockcount_recursive) map_lockcount_recursive = new ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>();
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->try_emplace(this, ::std::make_pair<uintptr_t, uintptr_t>(0, 0)).first;
			assert(!it_map_lockcount_recursive->second.first);
			if (this->mtx_this_prelock.try_lock_shared()) {
				bool is_successful = this->mtx_this.try_lock_shared();
				this->mtx_this_prelock.unlock_shared();
				if (is_successful) {
					++it_map_lockcount_recursive->second.second;
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		}
		void UnlockShared() const noexcept {
			this->mtx_this.unlock_shared();
			assert(map_lockcount_recursive);
			::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>::iterator it_map_lockcount_recursive = map_lockcount_recursive->find(this);
			assert(it_map_lockcount_recursive != map_lockcount_recursive->end());
			assert(!it_map_lockcount_recursive->second.first && it_map_lockcount_recursive->second.second);
			--it_map_lockcount_recursive->second.second;
		}
		size_t GetInvocationDataSize(already_shared_locked_this_t) const noexcept;
		void InitializeInvocationPacket(PipelineInvocationPacket*& _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t) const noexcept;
		void CleanupInvocationPacket(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t) const noexcept;
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
	protected:
		struct PipelineInvocationPacketDataEntry final {
			size_t idx_slot = SIZE_MAX;
			size_t count_slot = 0;
			uintptr_t refcount = 0;
			::std::unique_ptr<unsigned char[]> data_initial_invocationpacketdataentry;
			PipelineInvocationPacketDataEntryInitializeDelegate delegate_initialize;
			PipelineInvocationPacketDataEntryCleanupDelegate delegate_cleanup;
		};
		thread_local static ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>* map_lockcount_recursive;
		/// <summary>A <c>::std::shared_mutex</c> object used to control concurrent accesses to this object.</summary>
		mutable ::std::shared_mutex mtx_this;
		/// <summary>
		/// Another <c>::std::shared_mutex</c> object used to prevent resource starvation of threads waiting to exclusively lock the object.
		/// <c>LockShared</c> and <c>TryLockShared</c> acquires shared ownership of this mutex before locking <c>mtx_this</c> and releases this mutex after locking (NOT unlocking) <c>mtx_this</c>.
		/// </summary>
		mutable ::std::shared_mutex mtx_this_prelock;
		size_t count_slot_invocationpacketdata = 0;
		::std::unordered_map<PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry, hash<PipelineInvocationPacketDataEntryID>> map_invocationpacketdataentry;
		::std::map<size_t, bool> map_slot_invocationpacketdata_rangeboundary_free;
		::std::multimap<size_t, ::std::map<size_t, bool>::iterator> map_slot_invocationpacketdata_size_free;
		size_t AllocateInvocationPacketData(size_t _count_slot_invocationpacketdata_allocate, already_exclusive_locked_this_t) noexcept;
		void DeallocateInvocationPacketData(size_t _idx_slot_invocationpacketdata_deallocate, size_t _count_slot_invocationpacketdata_deallocate, already_exclusive_locked_this_t) noexcept;
	};

	class PipelineFilter final : public SharedPtrReferenceCountedObject<PipelineFilter> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(PipelineFilter);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(PipelineFilter);
		using delegate_rawinvoke_type = PipelineFilterRawInvokeDelegate;
		const PipelineFilterID pipelinefilterid;
		delegate_rawinvoke_type delegate_rawinvoke;
		PipelineFilter(
			const PersistentID& _persistentid_pipelinefilterid
		) noexcept : pipelinefilterid(_persistentid_pipelinefilterid) {}
		PipelineFilter(const PipelineFilter&) = delete;
		PipelineFilter(PipelineFilter&&) = delete;
		virtual ~PipelineFilter() {}
		PipelineFilter& operator=(const PipelineFilter&) = delete;
		PipelineFilter& operator=(PipelineFilter&&) = delete;
		PipelineFilterID GetPipelineFilterID() const noexcept { return this->pipelinefilterid; }
		void GetRawInvokeDelegate(const delegate_rawinvoke_type** _delegate_rawinvoke_ret) const noexcept {
			assert(_delegate_rawinvoke_ret);
			*_delegate_rawinvoke_ret = &this->delegate_rawinvoke;
		}
		void ReleaseRawInvokeDelegate(delegate_rawinvoke_type* _delegate_rawinvoke_ret) noexcept {
			assert(_delegate_rawinvoke_ret);
			*_delegate_rawinvoke_ret = ::std::move(this->delegate_rawinvoke);
		}
		void SetRawInvokeDelegate(delegate_rawinvoke_type* _delegate_rawinvoke) noexcept {
			assert(_delegate_rawinvoke);
			this->delegate_rawinvoke = ::std::move(*_delegate_rawinvoke);
		}
		void RawInvoke(PipelineInvocationPacket& _pipelineinvocationpacket) const noexcept {
			if (this->delegate_rawinvoke) {
				this->delegate_rawinvoke(&_pipelineinvocationpacket);
			}
		}
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

	static constexpr size_t size_PipelineInvocationPacket_padded = ((sizeof(PipelineInvocationPacket) - 1) / Pipeline::align_slot_invocationpacketdata + 1) * Pipeline::align_slot_invocationpacketdata;

	thread_local ::std::unordered_map<const volatile Pipeline*, ::std::pair<uintptr_t, uintptr_t>>* Pipeline::map_lockcount_recursive = nullptr;

	size_t Pipeline::GetInvocationDataSize(already_shared_locked_this_t) const noexcept {
		return size_PipelineInvocationPacket_padded + this->count_slot_invocationpacketdata * Pipeline::size_slot_invocationpacketdata;
	}

	void Pipeline::InitializeInvocationPacket(PipelineInvocationPacket*& _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t _already_shared_locked_this) const noexcept {
		static_cast<void>(_already_shared_locked_this);
		assert(_buf_invocationdata);
		assert(_size_buf_invocationdata >= this->GetInvocationDataSize(_already_shared_locked_this));
		unsigned char* ptr_current_buf_invocationdata = reinterpret_cast<unsigned char*>(_buf_invocationdata);
		size_t size_remaining_buf_invocationdata = _size_buf_invocationdata;
		PipelineInvocationPacket* pipelineinvocationpacket = nullptr;
		void* ptr_invocationpacketdata = nullptr;
		size_t size_invocationpacketdata = 0;
		{
			pipelineinvocationpacket = reinterpret_cast<PipelineInvocationPacket*>(ptr_current_buf_invocationdata);
			ptr_current_buf_invocationdata += size_PipelineInvocationPacket_padded; size_remaining_buf_invocationdata -= size_PipelineInvocationPacket_padded;
		}
		{
			ptr_invocationpacketdata = reinterpret_cast<void*>(ptr_current_buf_invocationdata);
			size_invocationpacketdata = this->count_slot_invocationpacketdata * Pipeline::size_slot_invocationpacketdata;
			ptr_current_buf_invocationdata += this->count_slot_invocationpacketdata * Pipeline::size_slot_invocationpacketdata; size_remaining_buf_invocationdata -= this->count_slot_invocationpacketdata * Pipeline::size_slot_invocationpacketdata;
		}
		pipelineinvocationpacket = new(pipelineinvocationpacket) PipelineInvocationPacket(
			this,
			ptr_invocationpacketdata,
			size_invocationpacketdata
		);
		for (const ::std::pair<const PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry>& val_map_invocationpacketdataentry : this->map_invocationpacketdataentry) {
			void* ptr_invocationpacketdataentry = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(pipelineinvocationpacket->GetInvocationPacketDataPtr()) + val_map_invocationpacketdataentry.second.idx_slot * size_slot_invocationpacketdata);
			size_t size_invocationpacketdataentry = val_map_invocationpacketdataentry.second.count_slot * size_slot_invocationpacketdata;
			if (val_map_invocationpacketdataentry.second.data_initial_invocationpacketdataentry)
				memcpy(
					ptr_invocationpacketdataentry,
					val_map_invocationpacketdataentry.second.data_initial_invocationpacketdataentry.get(),
					size_invocationpacketdataentry
				);
			else
				memset(ptr_invocationpacketdataentry, 0, size_invocationpacketdataentry);
			if (val_map_invocationpacketdataentry.second.delegate_initialize) {
				val_map_invocationpacketdataentry.second.delegate_initialize(
					ptr_invocationpacketdataentry,
					pipelineinvocationpacket
				);
			}
		}
		_pipelineinvocationpacket_ret = pipelineinvocationpacket;
	}

	void Pipeline::CleanupInvocationPacket(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t) const noexcept {
		for (const ::std::pair<const PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry>& val_map_invocationpacketdataentry : this->map_invocationpacketdataentry) {
			void* ptr_invocationpacketdataentry = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(_pipelineinvocationpacket.GetInvocationPacketDataPtr()) + val_map_invocationpacketdataentry.second.idx_slot * size_slot_invocationpacketdata);
			if (val_map_invocationpacketdataentry.second.delegate_cleanup) {
				val_map_invocationpacketdataentry.second.delegate_cleanup(
					ptr_invocationpacketdataentry,
					&_pipelineinvocationpacket
				);
			}
		}
		_pipelineinvocationpacket.~PipelineInvocationPacket();
	}

	void Pipeline::RawInvoke(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t) const noexcept {
		// TODO: Implement Pipeline::RawInvoke.
	}

	size_t Pipeline::RegisterInvocationPacketDataEntry(
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		const void* _data_initial_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
		already_exclusive_locked_this_t _already_exclusive_locked_this
	) noexcept {
		assert(_pipelineinvocationpacketdataentryid);
		assert(_size_invocationpacketdataentry);
		size_t count_slot_invocationpacketdataentry = ((_size_invocationpacketdataentry - 1) / size_slot_invocationpacketdata + 1);
		size_t idx_slot_invocationpacketdataentry = SIZE_MAX;
		::std::unordered_map<PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry, hash<PipelineInvocationPacketDataEntryID>>::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		if (it_map_invocationpacketdataentry == this->map_invocationpacketdataentry.end()) {
			idx_slot_invocationpacketdataentry = this->AllocateInvocationPacketData(count_slot_invocationpacketdataentry, _already_exclusive_locked_this);
			PipelineInvocationPacketDataEntry pipelineinvocationpacketdataentry;
			pipelineinvocationpacketdataentry.idx_slot = idx_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.count_slot = count_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.refcount = 1;
			if (_data_initial_invocationpacketdataentry) {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset(new unsigned char[count_slot_invocationpacketdataentry * size_slot_invocationpacketdata]());
				memcpy(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get(), _data_initial_invocationpacketdataentry, _size_invocationpacketdataentry);
				memset(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get() + _size_invocationpacketdataentry, 0, count_slot_invocationpacketdataentry * size_slot_invocationpacketdata - _size_invocationpacketdataentry);
			}
			pipelineinvocationpacketdataentry.delegate_initialize = ::std::move(_delegate_initialize_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.delegate_cleanup = ::std::move(_delegate_cleanup_invocationpacketdataentry);
			{
				bool is_successful_emplace = false;
				::std::tie(it_map_invocationpacketdataentry, is_successful_emplace) = this->map_invocationpacketdataentry.emplace(_pipelineinvocationpacketdataentryid, ::std::move(pipelineinvocationpacketdataentry));
				assert(is_successful_emplace);
			}
		} else {
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			idx_slot_invocationpacketdataentry = pipelineinvocationpacketdataentry.idx_slot;
			assert(pipelineinvocationpacketdataentry.count_slot == count_slot_invocationpacketdataentry);
			++pipelineinvocationpacketdataentry.refcount;
			if (!pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry && _data_initial_invocationpacketdataentry) {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset(new unsigned char[count_slot_invocationpacketdataentry * size_slot_invocationpacketdata]());
				memcpy(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get(), _data_initial_invocationpacketdataentry, _size_invocationpacketdataentry);
				memset(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get() + _size_invocationpacketdataentry, 0, count_slot_invocationpacketdataentry * size_slot_invocationpacketdata - _size_invocationpacketdataentry);
			}
			if (!pipelineinvocationpacketdataentry.delegate_initialize) pipelineinvocationpacketdataentry.delegate_initialize = ::std::move(_delegate_initialize_invocationpacketdataentry);
			if (!pipelineinvocationpacketdataentry.delegate_cleanup) pipelineinvocationpacketdataentry.delegate_cleanup = ::std::move(_delegate_cleanup_invocationpacketdataentry);
		}
		return idx_slot_invocationpacketdataentry * size_slot_invocationpacketdata;
	}

	size_t Pipeline::RegisterInvocationPacketDataEntry(
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		const void* _data_initial_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryInitializeDelegate&& _delegate_initialize_invocationpacketdataentry,
		PipelineInvocationPacketDataEntryCleanupDelegate&& _delegate_cleanup_invocationpacketdataentry,
		always_assign_delegate_pipelineinvocationpacketdataentry_t,
		already_exclusive_locked_this_t _already_exclusive_locked_this
	) noexcept {
		assert(_pipelineinvocationpacketdataentryid);
		assert(_size_invocationpacketdataentry);
		size_t count_slot_invocationpacketdataentry = ((_size_invocationpacketdataentry - 1) / size_slot_invocationpacketdata + 1);
		size_t idx_slot_invocationpacketdataentry = SIZE_MAX;
		::std::unordered_map<PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry, hash<PipelineInvocationPacketDataEntryID>>::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		if (it_map_invocationpacketdataentry == this->map_invocationpacketdataentry.end()) {
			idx_slot_invocationpacketdataentry = this->AllocateInvocationPacketData(count_slot_invocationpacketdataentry, _already_exclusive_locked_this);
			PipelineInvocationPacketDataEntry pipelineinvocationpacketdataentry;
			pipelineinvocationpacketdataentry.idx_slot = idx_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.count_slot = count_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.refcount = 1;
			if (_data_initial_invocationpacketdataentry) {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset(new unsigned char[count_slot_invocationpacketdataentry * size_slot_invocationpacketdata]());
				memcpy(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get(), _data_initial_invocationpacketdataentry, _size_invocationpacketdataentry);
				memset(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get() + _size_invocationpacketdataentry, 0, count_slot_invocationpacketdataentry * size_slot_invocationpacketdata - _size_invocationpacketdataentry);
			}
			pipelineinvocationpacketdataentry.delegate_initialize = ::std::move(_delegate_initialize_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.delegate_cleanup = ::std::move(_delegate_cleanup_invocationpacketdataentry);
			{
				bool is_successful_emplace = false;
				::std::tie(it_map_invocationpacketdataentry, is_successful_emplace) = this->map_invocationpacketdataentry.emplace(_pipelineinvocationpacketdataentryid, ::std::move(pipelineinvocationpacketdataentry));
				assert(is_successful_emplace);
			}
		} else {
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			idx_slot_invocationpacketdataentry = pipelineinvocationpacketdataentry.idx_slot;
			assert(pipelineinvocationpacketdataentry.count_slot == count_slot_invocationpacketdataentry);
			++pipelineinvocationpacketdataentry.refcount;
			if (_data_initial_invocationpacketdataentry) {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset(new unsigned char[count_slot_invocationpacketdataentry * size_slot_invocationpacketdata]());
				memcpy(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get(), _data_initial_invocationpacketdataentry, _size_invocationpacketdataentry);
				memset(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get() + _size_invocationpacketdataentry, 0, count_slot_invocationpacketdataentry * size_slot_invocationpacketdata - _size_invocationpacketdataentry);
			} else {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset();
			}
			pipelineinvocationpacketdataentry.delegate_initialize = ::std::move(_delegate_initialize_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.delegate_cleanup = ::std::move(_delegate_cleanup_invocationpacketdataentry);
		}
		return idx_slot_invocationpacketdataentry * size_slot_invocationpacketdata;
	}

	void Pipeline::UnregisterInvocationPacketDataEntry(const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		assert(_pipelineinvocationpacketdataentryid);
		::std::unordered_map<PipelineInvocationPacketDataEntryID, PipelineInvocationPacketDataEntry, hash<PipelineInvocationPacketDataEntryID>>::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		assert(it_map_invocationpacketdataentry != this->map_invocationpacketdataentry.end());
		bool should_erase = false;
		{
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			assert(pipelineinvocationpacketdataentry.refcount);
			if (!--pipelineinvocationpacketdataentry.refcount) {
				this->DeallocateInvocationPacketData(pipelineinvocationpacketdataentry.idx_slot, pipelineinvocationpacketdataentry.count_slot, _already_exclusive_locked_this);
				should_erase = true;
			}
		}
		if (should_erase) this->map_invocationpacketdataentry.erase(it_map_invocationpacketdataentry);
	}

	size_t Pipeline::AllocateInvocationPacketData(size_t _count_slot_invocationpacketdata_allocate, already_exclusive_locked_this_t) noexcept {
		assert(_count_slot_invocationpacketdata_allocate);
		::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free;
		{
			::std::pair<
				::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator,
				::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator
			> range_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.equal_range(_count_slot_invocationpacketdata_allocate);
			if (range_map_slot_invocationpacketdata_size_free.first == range_map_slot_invocationpacketdata_size_free.second) {
				it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.lower_bound(_count_slot_invocationpacketdata_allocate);
			} else {
				it_map_slot_invocationpacketdata_size_free = range_map_slot_invocationpacketdata_size_free.first;
				for (::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free_equal = range_map_slot_invocationpacketdata_size_free.first; it_map_slot_invocationpacketdata_size_free_equal != range_map_slot_invocationpacketdata_size_free.second; ++it_map_slot_invocationpacketdata_size_free_equal) {
					if (it_map_slot_invocationpacketdata_size_free_equal->second->first < it_map_slot_invocationpacketdata_size_free->second->first) it_map_slot_invocationpacketdata_size_free = it_map_slot_invocationpacketdata_size_free_equal;
				}
			}
		}
		size_t idx_slot_invocationpacketdata_allocate = SIZE_MAX;
		if (it_map_slot_invocationpacketdata_size_free == this->map_slot_invocationpacketdata_size_free.end()) {
			// No sufficiently large contiguous block of free slots is found.
			// Extend the invocation packet data size.
			idx_slot_invocationpacketdata_allocate = this->count_slot_invocationpacketdata;
			this->count_slot_invocationpacketdata += _count_slot_invocationpacketdata_allocate;
		} else {
			// A sufficiently large contiguous block of free slots is found.
			// Use the contiguous block found.
			::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block = it_map_slot_invocationpacketdata_size_free->second;
			assert(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block != this->map_slot_invocationpacketdata_rangeboundary_free.end());
			::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
			++it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
			assert(it_map_slot_invocationpacketdata_rangeboundary_free_end_block != this->map_slot_invocationpacketdata_rangeboundary_free.end());
			assert(
				it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first < it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
				&& it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first + it_map_slot_invocationpacketdata_size_free->first == it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
				&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first <= this->count_slot_invocationpacketdata
				&& (!it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->second && it_map_slot_invocationpacketdata_rangeboundary_free_end_block->second)
			);
			idx_slot_invocationpacketdata_allocate = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first;
			this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			if (it_map_slot_invocationpacketdata_size_free->first == _count_slot_invocationpacketdata_allocate) {
				// The size of the contiguous block matches the size needed exactly.
				// Remove the contiguous block from the maps keeping track of free slots.
				this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_end_block);
				this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
			} else {
				// The size of the contiguous block is greater than the size needed.
				// Shrink the free contiguous block.
				{
					bool is_successful_emplace_map_slot_invocationpacketdata_rangeboundary_free = false;
					::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block, is_successful_emplace_map_slot_invocationpacketdata_rangeboundary_free) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(idx_slot_invocationpacketdata_allocate + _count_slot_invocationpacketdata_allocate, false);
					assert(is_successful_emplace_map_slot_invocationpacketdata_rangeboundary_free);
				}
				this->map_slot_invocationpacketdata_size_free.emplace(it_map_slot_invocationpacketdata_size_free->first - _count_slot_invocationpacketdata_allocate, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
				this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
			}
		}
		return idx_slot_invocationpacketdata_allocate;
	}

	void Pipeline::DeallocateInvocationPacketData(size_t _idx_slot_invocationpacketdata_deallocate, size_t _count_slot_invocationpacketdata_deallocate, already_exclusive_locked_this_t) noexcept {
		assert(_count_slot_invocationpacketdata_deallocate);
		assert(_idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate <= this->count_slot_invocationpacketdata);
		if (_idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate == this->count_slot_invocationpacketdata) {
			// The deallocation happens at the end.
			// Shrink the invocation packet data size.
			this->count_slot_invocationpacketdata -= _count_slot_invocationpacketdata_deallocate;
			if (!this->map_slot_invocationpacketdata_rangeboundary_free.empty()) {
				::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block = this->map_slot_invocationpacketdata_rangeboundary_free.end();
				--it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_end_block != this->map_slot_invocationpacketdata_rangeboundary_free.begin()
					&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first <= this->count_slot_invocationpacketdata
					&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->second
				);
				::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block = it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
				--it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first < it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
					&& !it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->second
				);
				if (it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first == this->count_slot_invocationpacketdata) {
					// The last free contiguous block is now at the end.
					// Remove the contiguous block and shrink the invocation packet data size even more.
					::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.end();
					{
						::std::pair<
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator,
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator
						> range_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.equal_range(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first);
						assert(range_map_slot_invocationpacketdata_size_free.first != range_map_slot_invocationpacketdata_size_free.second);
						for (::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free_equal = range_map_slot_invocationpacketdata_size_free.first; it_map_slot_invocationpacketdata_size_free_equal != range_map_slot_invocationpacketdata_size_free.second; ++it_map_slot_invocationpacketdata_size_free_equal) {
							if (it_map_slot_invocationpacketdata_size_free_equal->second == it_map_slot_invocationpacketdata_rangeboundary_free_begin_block) {
								it_map_slot_invocationpacketdata_size_free = it_map_slot_invocationpacketdata_size_free_equal;
								break;
							}
						}
						assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					}
					assert(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first + it_map_slot_invocationpacketdata_size_free->first == it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first);
					this->count_slot_invocationpacketdata = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first;
					this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
					this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_end_block);
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
				}
			}
		} else {
			// The deallocation doesn't happen at the end.
			// Mark the deallocated slots as free slots.
			::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.lower_bound(_idx_slot_invocationpacketdata_deallocate);
			if (
				it_map_slot_invocationpacketdata_rangeboundary_free_next == this->map_slot_invocationpacketdata_rangeboundary_free.end()
				|| it_map_slot_invocationpacketdata_rangeboundary_free_next->first > _idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate
				) {
				// No existing free contiguous blocks adjacent to the deallocated slots are found.
				// Create a new free contiguous block.
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_next == this->map_slot_invocationpacketdata_rangeboundary_free.end()
					|| !it_map_slot_invocationpacketdata_rangeboundary_free_next->second
				);// Deallocating slots that are already free is not allowed.
				::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				bool is_successful_emplace = false;
				::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate, false);
				assert(is_successful_emplace);
				::std::tie(::std::ignore, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate, true);
				assert(is_successful_emplace);
				this->map_slot_invocationpacketdata_size_free.emplace(_count_slot_invocationpacketdata_deallocate, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			} else {
				::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				::std::map<size_t, bool>::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_next->first == _idx_slot_invocationpacketdata_deallocate
					|| it_map_slot_invocationpacketdata_rangeboundary_free_next->first == _idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate
				);// Deallocating slots that are already free is not allowed.
				if (it_map_slot_invocationpacketdata_rangeboundary_free_next->first == _idx_slot_invocationpacketdata_deallocate) {
					// An existing free contiguous block adjacent to the left(lower) boundary is found.
					// Merge with the free contiguous block found.
					assert(
						it_map_slot_invocationpacketdata_rangeboundary_free_next != this->map_slot_invocationpacketdata_rangeboundary_free.begin()
						&& it_map_slot_invocationpacketdata_rangeboundary_free_next->second
					);// Deallocating slots that are already free is not allowed.
					it_map_slot_invocationpacketdata_rangeboundary_free_begin_block = it_map_slot_invocationpacketdata_rangeboundary_free_next;
					--it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
					assert(!it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->second);
					::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.end();
					{
						::std::pair<
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator,
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator
						> range_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.equal_range(it_map_slot_invocationpacketdata_rangeboundary_free_next->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first);
						assert(range_map_slot_invocationpacketdata_size_free.first != range_map_slot_invocationpacketdata_size_free.second);
						for (::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free_equal = range_map_slot_invocationpacketdata_size_free.first; it_map_slot_invocationpacketdata_size_free_equal != range_map_slot_invocationpacketdata_size_free.second; ++it_map_slot_invocationpacketdata_size_free_equal) {
							if (it_map_slot_invocationpacketdata_size_free_equal->second == it_map_slot_invocationpacketdata_rangeboundary_free_begin_block) {
								it_map_slot_invocationpacketdata_size_free = it_map_slot_invocationpacketdata_size_free_equal;
								break;
							}
						}
						assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					}
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
					it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_next);
				} else {
					// Create the left(lower) boundary.
					bool is_successful_emplace = false;
					::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate, false);
					assert(is_successful_emplace);
				}
				if (
					it_map_slot_invocationpacketdata_rangeboundary_free_next == this->map_slot_invocationpacketdata_rangeboundary_free.end()
					|| it_map_slot_invocationpacketdata_rangeboundary_free_next->first > _idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate
					) {
					// Create the right(higher) boundary.
					assert(
						it_map_slot_invocationpacketdata_rangeboundary_free_next == this->map_slot_invocationpacketdata_rangeboundary_free.end()
						|| !it_map_slot_invocationpacketdata_rangeboundary_free_next->second
					);
					bool is_successful_emplace = false;
					::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_end_block, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate, true);
					assert(is_successful_emplace);
				} else {
					// An existing free contiguous block adjacent to the right(upper) boundary is found.
					// Merge with the free contiguous block found.
					assert(
						it_map_slot_invocationpacketdata_rangeboundary_free_next->first == _idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate
						&& !it_map_slot_invocationpacketdata_rangeboundary_free_next->second
					);// Deallocating slots that are already free is not allowed.
					it_map_slot_invocationpacketdata_rangeboundary_free_end_block = it_map_slot_invocationpacketdata_rangeboundary_free_next;
					++it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
					assert(
						it_map_slot_invocationpacketdata_rangeboundary_free_end_block != this->map_slot_invocationpacketdata_rangeboundary_free.end()
						&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->second
					);
					::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.end();
					{
						::std::pair<
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator,
							::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator
						> range_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.equal_range(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_next->first);
						assert(range_map_slot_invocationpacketdata_size_free.first != range_map_slot_invocationpacketdata_size_free.second);
						for (::std::multimap<size_t, ::std::map<size_t, bool>::iterator>::iterator it_map_slot_invocationpacketdata_size_free_equal = range_map_slot_invocationpacketdata_size_free.first; it_map_slot_invocationpacketdata_size_free_equal != range_map_slot_invocationpacketdata_size_free.second; ++it_map_slot_invocationpacketdata_size_free_equal) {
							if (it_map_slot_invocationpacketdata_size_free_equal->second == it_map_slot_invocationpacketdata_rangeboundary_free_next) {
								it_map_slot_invocationpacketdata_size_free = it_map_slot_invocationpacketdata_size_free_equal;
								break;
							}
						}
						assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					}
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
					it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_next);
					assert(it_map_slot_invocationpacketdata_rangeboundary_free_next == it_map_slot_invocationpacketdata_rangeboundary_free_end_block);
				}
				this->map_slot_invocationpacketdata_size_free.emplace(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			}
		}
	}

	namespace Internal {
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PersistentID* _persistentid_pipelineid) noexcept {
			assert(_persistentid_pipelineid);
			::std::shared_ptr<Pipeline> pipeline(new Pipeline(*_persistentid_pipelineid));
			pipeline->IncReferenceCount();
			return pipeline.get();
		}

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(const Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<const IReferenceCountedObject*>(_pipeline) : nullptr;
		}

		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<IReferenceCountedObject*>(_pipeline) : nullptr;
		}

		YBWLIB2_API PipelineID YBWLIB2_CALLTYPE Pipeline_GetPipelineID(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			return _pipeline->GetPipelineID();
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockExclusive(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			_pipeline->LockExclusive();
		}

		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockExclusive(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			return _pipeline->TryLockExclusive();
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockExclusive(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			_pipeline->UnlockExclusive();
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_LockShared(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			_pipeline->LockShared();
		}

		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_TryLockShared(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			return _pipeline->TryLockShared();
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnlockShared(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			_pipeline->UnlockShared();
		}

		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_GetInvocationDataSize(const Pipeline* _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept {
			assert(_pipeline);
			return _pipeline->GetInvocationDataSize(_already_shared_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_InitializeInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket** _pipelineinvocationpacket_ret, void* _buf_invocationdata, size_t _size_buf_invocationdata, already_shared_locked_this_t _already_shared_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->InitializeInvocationPacket(*_pipelineinvocationpacket_ret, _buf_invocationdata, _size_buf_invocationdata, _already_shared_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_CleanupInvocationPacket(const Pipeline* _pipeline, PipelineInvocationPacket* _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->CleanupInvocationPacket(*_pipelineinvocationpacket, _already_shared_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_RawInvoke(const Pipeline* _pipeline, PipelineInvocationPacket* _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->RawInvoke(*_pipelineinvocationpacket, _already_shared_locked_this);
		}

		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_RegisterInvocationPacketDataEntry(
			Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate* _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate* _delegate_cleanup_invocationpacketdataentry,
			already_exclusive_locked_this_t _already_exclusive_locked_this
		) noexcept {
			assert(_pipeline);
			return _pipeline->RegisterInvocationPacketDataEntry(
				*_pipelineinvocationpacketdataentryid,
				_size_invocationpacketdataentry,
				_data_initial_invocationpacketdataentry,
				::std::move(*_delegate_initialize_invocationpacketdataentry),
				::std::move(*_delegate_cleanup_invocationpacketdataentry),
				_already_exclusive_locked_this
			);
		}

		YBWLIB2_API size_t YBWLIB2_CALLTYPE Pipeline_RegisterInvocationPacketDataEntry(
			Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			const void* _data_initial_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryInitializeDelegate* _delegate_initialize_invocationpacketdataentry,
			PipelineInvocationPacketDataEntryCleanupDelegate* _delegate_cleanup_invocationpacketdataentry,
			always_assign_delegate_pipelineinvocationpacketdataentry_t _always_assign_delegate_pipelineinvocationpacketdataentry,
			already_exclusive_locked_this_t _already_exclusive_locked_this
		) noexcept {
			assert(_pipeline);
			return _pipeline->RegisterInvocationPacketDataEntry(
				*_pipelineinvocationpacketdataentryid,
				_size_invocationpacketdataentry,
				_data_initial_invocationpacketdataentry,
				::std::move(*_delegate_initialize_invocationpacketdataentry),
				::std::move(*_delegate_cleanup_invocationpacketdataentry),
				_always_assign_delegate_pipelineinvocationpacketdataentry,
				_already_exclusive_locked_this
			);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_UnregisterInvocationPacketDataEntry(Pipeline* _pipeline, const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->UnregisterInvocationPacketDataEntry(*_pipelineinvocationpacketdataentryid, _already_exclusive_locked_this);
		}

		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PersistentID* _persistentid_pipelinefilterid) noexcept {
			assert(_persistentid_pipelinefilterid);
			::std::shared_ptr<PipelineFilter> pipelinefilter(new PipelineFilter(*_persistentid_pipelinefilterid));
			pipelinefilter->IncReferenceCount();
			return pipelinefilter.get();
		}

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(const PipelineFilter* _pipelinefilter) noexcept {
			return _pipelinefilter ? static_cast<const IReferenceCountedObject*>(_pipelinefilter) : nullptr;
		}

		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineFilter_CastToIReferenceCountedObject(PipelineFilter* _pipelinefilter) noexcept {
			return _pipelinefilter ? static_cast<IReferenceCountedObject*>(_pipelinefilter) : nullptr;
		}

		YBWLIB2_API PipelineFilterID YBWLIB2_CALLTYPE PipelineFilter_GetPipelineFilterID(const PipelineFilter* _pipelinefilter) noexcept {
			assert(_pipelinefilter);
			return _pipelinefilter->GetPipelineFilterID();
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_GetRawInvokeDelegate(const PipelineFilter* _pipelinefilter, const PipelineFilterRawInvokeDelegate** _delegate_rawinvoke_ret) noexcept {
			assert(_pipelinefilter);
			_pipelinefilter->GetRawInvokeDelegate(_delegate_rawinvoke_ret);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_ReleaseRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke_ret) noexcept {
			assert(_pipelinefilter);
			_pipelinefilter->ReleaseRawInvokeDelegate(_delegate_rawinvoke_ret);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetRawInvokeDelegate(PipelineFilter* _pipelinefilter, PipelineFilterRawInvokeDelegate* _delegate_rawinvoke) noexcept {
			assert(_pipelinefilter);
			_pipelinefilter->SetRawInvokeDelegate(_delegate_rawinvoke);
		}

		YBWLIB2_API const Pipeline* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetPipeline(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			assert(_pipelineinvocationpacket);
			return _pipelineinvocationpacket->GetPipeline();
		}

		YBWLIB2_API const void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			assert(_pipelineinvocationpacket);
			return _pipelineinvocationpacket->GetInvocationPacketDataPtr();
		}

		YBWLIB2_API void* YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataPtr(PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			assert(_pipelineinvocationpacket);
			return _pipelineinvocationpacket->GetInvocationPacketDataPtr();
		}

		YBWLIB2_API size_t YBWLIB2_CALLTYPE PipelineInvocationPacket_GetInvocationPacketDataSize(const PipelineInvocationPacket* _pipelineinvocationpacket) noexcept {
			assert(_pipelineinvocationpacket);
			return _pipelineinvocationpacket->GetInvocationPacketDataSize();
		}
	}

	void YBWLIB2_CALLTYPE Pipeline_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE Pipeline_RealUnInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE PipelineUserInterface_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE PipelineUserInterface_RealUnInitGlobal() noexcept {}
}
