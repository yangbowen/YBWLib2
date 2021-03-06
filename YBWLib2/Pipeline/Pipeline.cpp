#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include <list>
#include <unordered_map>
#include <map>
#include <stack>
#include <shared_mutex>
#include <thread>
#include "../DynamicType/DynamicType.h"
#include "Pipeline.h"

#ifndef YBWLIB2_PIPELINE_EXPOSE_PRIVATE_CLASSES
#include "PipelinePrivateClassDef.h"
#endif

namespace YBWLib2 {
	static constexpr size_t size_PipelineInvocationPacket_padded = ((sizeof(PipelineInvocationPacket) - 1) / Pipeline::align_slot_invocationpacketdata + 1) * Pipeline::align_slot_invocationpacketdata;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Pipeline, );

	namespace Internal {
		YBWLIB2_API PipelineInvocationPacketDataEntryID pipelineinvocationpacketdataentryid_arr_ptr_arg;
		YBWLIB2_API IndexedDataEntryID indexeddataentryid_invokedelegatecontext;
		YBWLIB2_API ReferenceCountedObjectHolder<PipelineStore>* pipelinestore_global = nullptr;
	}

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

	bool Pipeline::IsResolved(already_shared_locked_this_t) const noexcept {
		return this->map_pipelinefilterattachment_floating.empty();
	}

	bool Pipeline::IsResolved(already_exclusive_locked_this_t) const noexcept {
		return this->map_pipelinefilterattachment_floating.empty();
	}

	void Pipeline::RawInvoke(PipelineInvocationPacket& _pipelineinvocationpacket, already_shared_locked_this_t _already_shared_locked_this) const noexcept {
		assert(this->IsResolved(_already_shared_locked_this)); static_cast<void>(_already_shared_locked_this);
		for (const PipelineFilterAttachment* pipelinefilterattachment : this->list_pipelinefilterattachment_invocation) {
			assert(pipelinefilterattachment && pipelinefilterattachment->pipelinefilter);
			pipelinefilterattachment->pipelinefilter->RawInvoke(_pipelineinvocationpacket);
		}
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
		map_invocationpacketdataentry_t::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		if (it_map_invocationpacketdataentry == this->map_invocationpacketdataentry.end()) {
			idx_slot_invocationpacketdataentry = this->AllocateInvocationPacketData(count_slot_invocationpacketdataentry, _already_exclusive_locked_this);
			PipelineInvocationPacketDataEntry pipelineinvocationpacketdataentry;
			pipelineinvocationpacketdataentry.idx_slot = idx_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.count_slot = count_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.refcount.fetch_add(1, ::std::memory_order_relaxed);
			if (_data_initial_invocationpacketdataentry) {
				pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.reset(new unsigned char[count_slot_invocationpacketdataentry * size_slot_invocationpacketdata]());
				memcpy(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get(), _data_initial_invocationpacketdataentry, _size_invocationpacketdataentry);
				memset(pipelineinvocationpacketdataentry.data_initial_invocationpacketdataentry.get() + _size_invocationpacketdataentry, 0, count_slot_invocationpacketdataentry * size_slot_invocationpacketdata - _size_invocationpacketdataentry);
			}
			pipelineinvocationpacketdataentry.delegate_initialize = ::std::move(_delegate_initialize_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.delegate_cleanup = ::std::move(_delegate_cleanup_invocationpacketdataentry);
			{
				bool is_successful_emplace = false;
				::std::tie(it_map_invocationpacketdataentry, is_successful_emplace) = this->map_invocationpacketdataentry.emplace(PipelineInvocationPacketDataEntryID(_pipelineinvocationpacketdataentryid), ::std::move(pipelineinvocationpacketdataentry));
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
			}
		} else {
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			idx_slot_invocationpacketdataentry = pipelineinvocationpacketdataentry.idx_slot;
			assert(pipelineinvocationpacketdataentry.count_slot == count_slot_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.refcount.fetch_add(1, ::std::memory_order_relaxed);
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
		if (this->should_scan_map_invocationpacketdataentry.load(::std::memory_order_relaxed)) {
			::std::vector<map_invocationpacketdataentry_t::iterator> vec_it_map_invocationpacketdataentry_should_erase;
			for (
				map_invocationpacketdataentry_t::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.begin(), it_map_invocationpacketdataentry_end = this->map_invocationpacketdataentry.end();
				it_map_invocationpacketdataentry != it_map_invocationpacketdataentry_end;
				++it_map_invocationpacketdataentry
				) {
				if (!it_map_invocationpacketdataentry->second.refcount.load(::std::memory_order_relaxed)) {
					this->DeallocateInvocationPacketData(it_map_invocationpacketdataentry->second.idx_slot, it_map_invocationpacketdataentry->second.count_slot, _already_exclusive_locked_this);
					vec_it_map_invocationpacketdataentry_should_erase.push_back(it_map_invocationpacketdataentry);
				}
			}
			while (!vec_it_map_invocationpacketdataentry_should_erase.empty()) {
				this->map_invocationpacketdataentry.erase(vec_it_map_invocationpacketdataentry_should_erase.back());
				vec_it_map_invocationpacketdataentry_should_erase.pop_back();
			}
			this->should_scan_map_invocationpacketdataentry.store(false, ::std::memory_order_relaxed);
		}
		size_t count_slot_invocationpacketdataentry = ((_size_invocationpacketdataentry - 1) / size_slot_invocationpacketdata + 1);
		size_t idx_slot_invocationpacketdataentry = SIZE_MAX;
		map_invocationpacketdataentry_t::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		if (it_map_invocationpacketdataentry == this->map_invocationpacketdataentry.end()) {
			idx_slot_invocationpacketdataentry = this->AllocateInvocationPacketData(count_slot_invocationpacketdataentry, _already_exclusive_locked_this);
			PipelineInvocationPacketDataEntry pipelineinvocationpacketdataentry;
			pipelineinvocationpacketdataentry.idx_slot = idx_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.count_slot = count_slot_invocationpacketdataentry;
			pipelineinvocationpacketdataentry.refcount.fetch_add(1, ::std::memory_order_relaxed);
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
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
			}
		} else {
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			idx_slot_invocationpacketdataentry = pipelineinvocationpacketdataentry.idx_slot;
			assert(pipelineinvocationpacketdataentry.count_slot == count_slot_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.refcount.fetch_add(1, ::std::memory_order_relaxed);
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
		if (this->should_scan_map_invocationpacketdataentry.load(::std::memory_order_relaxed)) {
			::std::vector<map_invocationpacketdataentry_t::iterator> vec_it_map_invocationpacketdataentry_should_erase;
			for (
				map_invocationpacketdataentry_t::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.begin(), it_map_invocationpacketdataentry_end = this->map_invocationpacketdataentry.end();
				it_map_invocationpacketdataentry != it_map_invocationpacketdataentry_end;
				++it_map_invocationpacketdataentry
				) {
				if (!it_map_invocationpacketdataentry->second.refcount.load(::std::memory_order_relaxed)) {
					this->DeallocateInvocationPacketData(it_map_invocationpacketdataentry->second.idx_slot, it_map_invocationpacketdataentry->second.count_slot, _already_exclusive_locked_this);
					vec_it_map_invocationpacketdataentry_should_erase.push_back(it_map_invocationpacketdataentry);
				}
			}
			while (!vec_it_map_invocationpacketdataentry_should_erase.empty()) {
				this->map_invocationpacketdataentry.erase(vec_it_map_invocationpacketdataentry_should_erase.back());
				vec_it_map_invocationpacketdataentry_should_erase.pop_back();
			}
			this->should_scan_map_invocationpacketdataentry.store(false, ::std::memory_order_relaxed);
		}
		map_invocationpacketdataentry_t::iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		assert(it_map_invocationpacketdataentry != this->map_invocationpacketdataentry.end());
		bool should_erase = false;
		{
			PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			uintptr_t refcount_before = pipelineinvocationpacketdataentry.refcount.fetch_sub(1, ::std::memory_order_relaxed);
			assert(refcount_before);
			if (refcount_before == 1) {
				this->DeallocateInvocationPacketData(pipelineinvocationpacketdataentry.idx_slot, pipelineinvocationpacketdataentry.count_slot, _already_exclusive_locked_this);
				should_erase = true;
			}
		}
		if (should_erase) this->map_invocationpacketdataentry.erase(it_map_invocationpacketdataentry);
	}

	void Pipeline::AddRefInvocationPacketDataEntry(
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		size_t _offset_invocationpacketdataentry,
		already_shared_locked_this_t
	) const noexcept {
		assert(_pipelineinvocationpacketdataentryid);
		map_invocationpacketdataentry_t::const_iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		assert(it_map_invocationpacketdataentry != this->map_invocationpacketdataentry.end());
		{
			const PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			assert(_size_invocationpacketdataentry <= pipelineinvocationpacketdataentry.count_slot * size_slot_invocationpacketdata); static_cast<void>(_size_invocationpacketdataentry);
			assert(_offset_invocationpacketdataentry == pipelineinvocationpacketdataentry.idx_slot * size_slot_invocationpacketdata); static_cast<void>(_offset_invocationpacketdataentry);
			pipelineinvocationpacketdataentry.refcount.fetch_add(1, ::std::memory_order_acq_rel);
		}
	}

	void Pipeline::DecRefInvocationPacketDataEntry(
		const PipelineInvocationPacketDataEntryID& _pipelineinvocationpacketdataentryid,
		size_t _size_invocationpacketdataentry,
		size_t _offset_invocationpacketdataentry,
		already_shared_locked_this_t
	) const noexcept {
		assert(_pipelineinvocationpacketdataentryid);
		map_invocationpacketdataentry_t::const_iterator it_map_invocationpacketdataentry = this->map_invocationpacketdataentry.find(_pipelineinvocationpacketdataentryid);
		assert(it_map_invocationpacketdataentry != this->map_invocationpacketdataentry.end());
		{
			const PipelineInvocationPacketDataEntry& pipelineinvocationpacketdataentry = it_map_invocationpacketdataentry->second;
			assert(_size_invocationpacketdataentry <= pipelineinvocationpacketdataentry.count_slot * size_slot_invocationpacketdata); static_cast<void>(_size_invocationpacketdataentry);
			assert(_offset_invocationpacketdataentry == pipelineinvocationpacketdataentry.idx_slot * size_slot_invocationpacketdata); static_cast<void>(_offset_invocationpacketdataentry);
			uintptr_t refcount_before = pipelineinvocationpacketdataentry.refcount.fetch_sub(1, ::std::memory_order_acq_rel);
			assert(refcount_before);
			if (refcount_before == 1) this->should_scan_map_invocationpacketdataentry.store(true, ::std::memory_order_relaxed);
		}
	}

	void Pipeline::AttachPipelineFilter(PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		assert(_pipelinefilter && !_pipelinefilter->pipeline);
		PipelineFilterAttachment* pipelinefilterattachment = nullptr;
		{
			map_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment = this->map_pipelinefilterattachment.find(_pipelinefilter->GetPipelineFilterID());
			if (it_map_pipelinefilterattachment != this->map_pipelinefilterattachment.end()) {
				if (it_map_pipelinefilterattachment->second.IsZombie()) {
					this->Resolve(_already_exclusive_locked_this);
				} else {
					// A pipeline filter with an identical pipeline filter ID has already been attached.
					abort();
				}
			}
			{
				bool is_successful_emplace = false;
				::std::tie(it_map_pipelinefilterattachment, is_successful_emplace) = this->map_pipelinefilterattachment.emplace(::std::piecewise_construct, ::std::tuple(_pipelinefilter->GetPipelineFilterID()), ::std::tuple());
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
			}
			it_map_pipelinefilterattachment->second.pipelinefilterid = _pipelinefilter->pipelinefilterid;
			it_map_pipelinefilterattachment->second.pipelinefilter.reset(_pipelinefilter, ReferenceCountedObjectHolder<PipelineFilter>::inc_ref_count);
			pipelinefilterattachment = &it_map_pipelinefilterattachment->second;
			_pipelinefilter->pipeline = this;
		}
		{
			bool is_successful_emplace = false;
			::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_floating.emplace(_pipelinefilter->GetPipelineFilterID(), pipelinefilterattachment);
			assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
		}
		this->AdjustPipelineFilterAttachmentDependencyMapsInitialize(*pipelinefilterattachment, _already_exclusive_locked_this);
		{
			bool is_successful_emplace = false;
			::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_unchained.emplace(_pipelinefilter->GetPipelineFilterID(), pipelinefilterattachment);
			assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
		}
		if (_should_resolve_immediately) this->Resolve(_already_exclusive_locked_this);
		if (_idx_pipelinefilterposition_resolve_ret)
			*_idx_pipelinefilterposition_resolve_ret = pipelinefilterattachment->idx_pipelinefilterposition_resolve;
	}

	void Pipeline::DetachPipelineFilter(PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		assert(_pipelinefilter);
		if (_pipelinefilter->pipeline != this) {
			// The specified pipeline filter hasn't been attached to this pipeline yet.
			abort();
		}
		PipelineFilterID pipelinefilterid = _pipelinefilter->GetPipelineFilterID();
		PipelineFilterAttachment* pipelinefilterattachment = nullptr;
		map_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment = this->map_pipelinefilterattachment.find(pipelinefilterid);
		assert(it_map_pipelinefilterattachment != this->map_pipelinefilterattachment.end());
		pipelinefilterattachment = &it_map_pipelinefilterattachment->second;
		assert(pipelinefilterattachment->pipelinefilter.get() == _pipelinefilter);
		_pipelinefilter->pipeline = nullptr;
		::std::pair<
			map_ptr_pipelinefilterattachment_dependency_t::iterator,
			map_ptr_pipelinefilterattachment_dependency_t::iterator
		> range_map_pipelinefilterattachment_dependency_current = ::std::pair(
			this->map_pipelinefilterattachment_dependency_current.upper_bound(::std::tuple(pipelinefilterid, below_min_t<PipelineFilterID>())),
			this->map_pipelinefilterattachment_dependency_current.lower_bound(::std::tuple(pipelinefilterid, above_max_t<PipelineFilterID>()))
		);
		if (range_map_pipelinefilterattachment_dependency_current.first == range_map_pipelinefilterattachment_dependency_current.second) {
			// Pipeline filter attachments that are not currently depended on can be safely removed.
			map_ptr_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment_unchained = this->map_pipelinefilterattachment_unchained.find(pipelinefilterid);
			if (pipelinefilterattachment->idx_pipelinefilterposition_resolve != SIZE_MAX) {
				// The pipeline filter attachment is currently chained.
				assert(pipelinefilterattachment->idx_pipelinefilterposition_resolve < _pipelinefilter->vec_pipelinefilterposition.size());
				assert(it_map_pipelinefilterattachment_unchained == this->map_pipelinefilterattachment_unchained.end());
				this->list_pipelinefilterattachment_invocation.erase(pipelinefilterattachment->it_list_pipelinefilterattachment_invocation);
			} else {
				// The pipeline filter attachment is currently unchained.
				assert(it_map_pipelinefilterattachment_unchained != this->map_pipelinefilterattachment_unchained.end());
				this->map_pipelinefilterattachment_unchained.erase(it_map_pipelinefilterattachment_unchained);
			}
			this->AdjustPipelineFilterAttachmentDependencyMapsClear(*pipelinefilterattachment, _already_exclusive_locked_this);
			this->map_pipelinefilterattachment.erase(it_map_pipelinefilterattachment);
		} else {
			// Pipeline filter attachments that are currently depended on must be made zombie.
			// They will be removed later by Resolve.
			pipelinefilterattachment->vec_pipelinefilterposition_zombie = _pipelinefilter->vec_pipelinefilterposition;
			pipelinefilterattachment->pipelinefilter.reset();
			this->map_pipelinefilterattachment_floating.emplace(pipelinefilterid, pipelinefilterattachment);
		}
		if (_should_resolve_immediately) this->Resolve(_already_exclusive_locked_this);
	}

	void Pipeline::Resolve(already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
		/// <summary>An unordered map that contains references to <c>PipelineFilterAttachment</c> objects that represent pipeline filter attachments that needs to be updated later.</summary>
		map_ptr_pipelinefilterattachment_t map_pipelinefilterattachment_pending_update;
		// Fill map_pipelinefilterattachment_pending_update.
		{
			for (const ::std::pair<const PipelineFilterID, PipelineFilterAttachment*>& val_map_pipelinefilterattachment_floating : this->map_pipelinefilterattachment_floating) {
				assert(val_map_pipelinefilterattachment_floating.second);
				struct state_recurse_dependency_t final {
					enum class Checkpoint : size_t {
						Checkpoint_Initial = 0,
						Checkpoint_AfterRecurse
					} checkpoint = Checkpoint::Checkpoint_Initial;
					const PipelineFilterID pipelinefilterid;
					PipelineFilterAttachment& pipelinefilterattachment;
					::std::pair<
						map_ptr_pipelinefilterattachment_dependency_t::iterator,
						map_ptr_pipelinefilterattachment_dependency_t::iterator
					> range_map_pipelinefilterattachment_dependency;
					map_ptr_pipelinefilterattachment_dependency_t::iterator it_range_map_pipelinefilterattachment_dependency;
					explicit state_recurse_dependency_t(PipelineFilterAttachment& _pipelinefilterattachment)
						: pipelinefilterid(_pipelinefilterattachment.pipelinefilterid),
						pipelinefilterattachment(_pipelinefilterattachment) {}
					state_recurse_dependency_t(const state_recurse_dependency_t&) = delete;
					state_recurse_dependency_t(state_recurse_dependency_t&&) = default;
					~state_recurse_dependency_t() = default;
					state_recurse_dependency_t& operator=(const state_recurse_dependency_t&) = delete;
					state_recurse_dependency_t& operator=(state_recurse_dependency_t&&) = default;
				};
				::std::stack<state_recurse_dependency_t> stack_state_recurse_dependency;
				::std::unordered_set<PipelineFilterID> set_pipelinefilterid_depended;
				stack_state_recurse_dependency.emplace(*val_map_pipelinefilterattachment_floating.second);
				{
					bool is_successful_emplace = false;
					::std::tie(::std::ignore, is_successful_emplace) = set_pipelinefilterid_depended.emplace(val_map_pipelinefilterattachment_floating.first);
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				}
				// Recursively fill map_pipelinefilterattachment_pending_update.
				// The recursion is simulated using a stack and a loop.
				while (!stack_state_recurse_dependency.empty()) {
					state_recurse_dependency_t& state_recurse_dependency = stack_state_recurse_dependency.top();
					switch (state_recurse_dependency.checkpoint) {
					case state_recurse_dependency_t::Checkpoint::Checkpoint_Initial:
					{
						bool is_successful_emplace_map_pipelinefilterattachment_pending_update = false;
						::std::tie(::std::ignore, is_successful_emplace_map_pipelinefilterattachment_pending_update) = map_pipelinefilterattachment_pending_update.emplace(state_recurse_dependency.pipelinefilterattachment.pipelinefilterid, &state_recurse_dependency.pipelinefilterattachment);
						if (is_successful_emplace_map_pipelinefilterattachment_pending_update) {
							// state_recurse_dependency.pipelinefilterattachment has not been processed yet.
							// Recursively search for dependencies.
							state_recurse_dependency.range_map_pipelinefilterattachment_dependency = ::std::pair(
								this->map_pipelinefilterattachment_dependency_current.upper_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, below_min_t<PipelineFilterID>())),
								this->map_pipelinefilterattachment_dependency_current.lower_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, above_max_t<PipelineFilterID>()))
							);
							if (state_recurse_dependency.range_map_pipelinefilterattachment_dependency.first != state_recurse_dependency.range_map_pipelinefilterattachment_dependency.second) {
								assert(
									this->map_pipelinefilterattachment_dependency_expecting.upper_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, below_min_t<PipelineFilterID>()))
									== this->map_pipelinefilterattachment_dependency_expecting.lower_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, above_max_t<PipelineFilterID>()))
								);
							} else {
								state_recurse_dependency.range_map_pipelinefilterattachment_dependency = ::std::pair(
									this->map_pipelinefilterattachment_dependency_expecting.upper_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, below_min_t<PipelineFilterID>())),
									this->map_pipelinefilterattachment_dependency_expecting.lower_bound(::std::tuple(state_recurse_dependency.pipelinefilterid, above_max_t<PipelineFilterID>()))
								);
							}
							if (state_recurse_dependency.range_map_pipelinefilterattachment_dependency.first != state_recurse_dependency.range_map_pipelinefilterattachment_dependency.second) {
								state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency = state_recurse_dependency.range_map_pipelinefilterattachment_dependency.first;
								assert(state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second);
								stack_state_recurse_dependency.emplace(*state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second);
								{
									bool is_successful_emplace = false;
									::std::tie(::std::ignore, is_successful_emplace) = set_pipelinefilterid_depended.emplace(state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second->pipelinefilterid);
									if (!is_successful_emplace) {
										// Failure to emplace into set_pipelinefilterid_depended indicates that a cyclic dependency has been encountered.
										abort();
									}
								}
								++state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency;
								state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse;
							} else {
								{
									bool is_successful_erase = false;
									is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
									assert(is_successful_erase); static_cast<void>(is_successful_erase);
								}
								stack_state_recurse_dependency.pop();
								assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse);
							}
						} else {
							// state_recurse_dependency.pipelinefilterattachment has already been processed.
							// No need to recursively search for dependencies.
							{
								bool is_successful_erase = false;
								is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
								assert(is_successful_erase); static_cast<void>(is_successful_erase);
							}
							stack_state_recurse_dependency.pop();
							assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse);
						}
						break;
					}
					case state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse:
					{
						assert(state_recurse_dependency.range_map_pipelinefilterattachment_dependency.first != state_recurse_dependency.range_map_pipelinefilterattachment_dependency.second);
						if (state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency != state_recurse_dependency.range_map_pipelinefilterattachment_dependency.second) {
							assert(state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second);
							stack_state_recurse_dependency.emplace(*state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second);
							{
								bool is_successful_emplace = false;
								::std::tie(::std::ignore, is_successful_emplace) = set_pipelinefilterid_depended.emplace(state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency->second->pipelinefilterid);
								if (!is_successful_emplace) {
									// Failure to emplace into set_pipelinefilterid_depended indicates that a cyclic dependency has been encountered.
									abort();
								}
							}
							++state_recurse_dependency.it_range_map_pipelinefilterattachment_dependency;
							assert(state_recurse_dependency.checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse);
						} else {
							{
								bool is_successful_erase = false;
								is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
								assert(is_successful_erase); static_cast<void>(is_successful_erase);
							}
							stack_state_recurse_dependency.pop();
							assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterRecurse);
						}
						break;
					}
					default:
						assert(false); abort();
					}
				}
				assert(set_pipelinefilterid_depended.empty());
			}
		}
		{
			struct state_recurse_dependency_t final {
				enum class Checkpoint : size_t {
					Checkpoint_Initial = 0,
					Checkpoint_Loop,
					Checkpoint_AfterResolveDepended
				} checkpoint = Checkpoint::Checkpoint_Initial;
				const PipelineFilterID pipelinefilterid;
				PipelineFilterAttachment* pipelinefilterattachment = nullptr;
				map_ptr_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment_pending_update;
				size_t idx_pipelinefilterposition_resolving = SIZE_MAX;
				const ::std::vector<PipelineFilterPosition>* vec_pipelinefilterposition = nullptr;
				explicit state_recurse_dependency_t(const PipelineFilterID& _pipelinefilterid)
					: pipelinefilterid(_pipelinefilterid) {}
				state_recurse_dependency_t(const state_recurse_dependency_t&) = delete;
				state_recurse_dependency_t(state_recurse_dependency_t&&) = default;
				~state_recurse_dependency_t() = default;
				state_recurse_dependency_t& operator=(const state_recurse_dependency_t&) = delete;
				state_recurse_dependency_t& operator=(state_recurse_dependency_t&&) = default;
			};
			::std::stack<state_recurse_dependency_t> stack_state_recurse_dependency;
			::std::unordered_set<PipelineFilterID> set_pipelinefilterid_depended;
			::std::list<PipelineFilterAttachment*>::const_iterator it_list_pipelinefilterattachment_invocation_return_recurse_dependency;
			bool is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = false;
			// Recursively resolve dependencies.
			// The recursion is simulated using a stack and a loop.
			while (true) {
				if (!stack_state_recurse_dependency.empty()) {
					// We're in a recursion.
					state_recurse_dependency_t& state_recurse_dependency = stack_state_recurse_dependency.top();
					switch (state_recurse_dependency.checkpoint) {
					case state_recurse_dependency_t::Checkpoint::Checkpoint_Initial:
					{
						state_recurse_dependency.it_map_pipelinefilterattachment_pending_update = map_pipelinefilterattachment_pending_update.find(state_recurse_dependency.pipelinefilterid);
						map_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment = this->map_pipelinefilterattachment.find(state_recurse_dependency.pipelinefilterid);
						if (state_recurse_dependency.it_map_pipelinefilterattachment_pending_update == map_pipelinefilterattachment_pending_update.end()) {
							// The pipeline filter attachment has already been updated.
							// Return the result directly.
							if (it_map_pipelinefilterattachment == this->map_pipelinefilterattachment.cend()) {
								it_list_pipelinefilterattachment_invocation_return_recurse_dependency = ::std::list<PipelineFilterAttachment*>::const_iterator();
								is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = false;
							} else {
								state_recurse_dependency.pipelinefilterattachment = &it_map_pipelinefilterattachment->second;
								if (state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve == SIZE_MAX) {
									it_list_pipelinefilterattachment_invocation_return_recurse_dependency = ::std::list<PipelineFilterAttachment*>::const_iterator();
									is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = false;
								} else {
									it_list_pipelinefilterattachment_invocation_return_recurse_dependency = state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation;
									is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = true;
								}
							}
						} else {
							// The pipeline filter attachment hasn't been updated yet.
							// Update and return the result.
							assert(it_map_pipelinefilterattachment != this->map_pipelinefilterattachment.end());
							state_recurse_dependency.pipelinefilterattachment = &it_map_pipelinefilterattachment->second;
							if (state_recurse_dependency.pipelinefilterattachment->IsZombie()) {
								// The pipeline filter attachment is zombie.
								// Remove the pipeline filter attachment.
								// Pipeline filter attachments dependent on this one will get updated later.
								map_ptr_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment_unchained = this->map_pipelinefilterattachment_unchained.find(state_recurse_dependency.pipelinefilterid);
								if (state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve != SIZE_MAX) {
									// The pipeline filter attachment is currently chained.
									assert(state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve < state_recurse_dependency.pipelinefilterattachment->vec_pipelinefilterposition_zombie.size());
									assert(it_map_pipelinefilterattachment_unchained == this->map_pipelinefilterattachment_unchained.end());
									this->list_pipelinefilterattachment_invocation.erase(state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation);
								} else {
									// The pipeline filter attachment is currently unchained.
									assert(it_map_pipelinefilterattachment_unchained != this->map_pipelinefilterattachment_unchained.end());
									this->map_pipelinefilterattachment_unchained.erase(it_map_pipelinefilterattachment_unchained);
								}
								this->AdjustPipelineFilterAttachmentDependencyMapsClear(*state_recurse_dependency.pipelinefilterattachment, _already_exclusive_locked_this);
								state_recurse_dependency.pipelinefilterattachment = nullptr;
								this->map_pipelinefilterattachment.erase(it_map_pipelinefilterattachment);
								it_list_pipelinefilterattachment_invocation_return_recurse_dependency = ::std::list<PipelineFilterAttachment*>::const_iterator();
								is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = false;
							} else {
								// The pipeline filter attachment is not a zombie.
								// Start resolve dependencies of this pipeline filter attachment.
								state_recurse_dependency.idx_pipelinefilterposition_resolving = 0;
								state_recurse_dependency.vec_pipelinefilterposition = &state_recurse_dependency.pipelinefilterattachment->pipelinefilter->vec_pipelinefilterposition;
								state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_Loop;
								break;
							}
							static_cast<void>(this->map_pipelinefilterattachment_floating.erase(state_recurse_dependency.pipelinefilterid));
							// Remove the pipeline filter attachment from the pending update map.
							map_pipelinefilterattachment_pending_update.erase(state_recurse_dependency.it_map_pipelinefilterattachment_pending_update);
						}
						{
							bool is_successful_erase = false;
							is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
							assert(is_successful_erase); static_cast<void>(is_successful_erase);
						}
						stack_state_recurse_dependency.pop();
						assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended);
						break;
					}
					case state_recurse_dependency_t::Checkpoint::Checkpoint_Loop:
					{
						assert(state_recurse_dependency.vec_pipelinefilterposition);
						if (state_recurse_dependency.idx_pipelinefilterposition_resolving == state_recurse_dependency.vec_pipelinefilterposition->size()) {
							// Nowhere in the invocation list can the pipeline filter attachment be inserted.
							// The pipeline filter attachment should be made unchained.
							state_recurse_dependency.idx_pipelinefilterposition_resolving = SIZE_MAX;
							map_ptr_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment_unchained = this->map_pipelinefilterattachment_unchained.find(state_recurse_dependency.pipelinefilterid);
							if (state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve != SIZE_MAX) {
								// The pipeline filter attachment is currently chained.
								assert(state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve < state_recurse_dependency.vec_pipelinefilterposition->size());
								assert(it_map_pipelinefilterattachment_unchained == this->map_pipelinefilterattachment_unchained.end());
								this->list_pipelinefilterattachment_invocation.erase(state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation);
								it_map_pipelinefilterattachment_unchained = this->map_pipelinefilterattachment_unchained.emplace(state_recurse_dependency.pipelinefilterid, state_recurse_dependency.pipelinefilterattachment).first;
							} else {
								// The pipeline filter attachment is currently unchained.
								assert(it_map_pipelinefilterattachment_unchained != this->map_pipelinefilterattachment_unchained.end());
							}
							this->AdjustPipelineFilterAttachmentDependencyMaps(*state_recurse_dependency.pipelinefilterattachment, state_recurse_dependency.idx_pipelinefilterposition_resolving, _already_exclusive_locked_this);
							it_list_pipelinefilterattachment_invocation_return_recurse_dependency = ::std::list<PipelineFilterAttachment*>::const_iterator();
							is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = false;
							static_cast<void>(this->map_pipelinefilterattachment_floating.erase(state_recurse_dependency.pipelinefilterid));
							// Remove the pipeline filter attachment from the pending update map.
							map_pipelinefilterattachment_pending_update.erase(state_recurse_dependency.it_map_pipelinefilterattachment_pending_update);
							{
								bool is_successful_erase = false;
								is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
								assert(is_successful_erase); static_cast<void>(is_successful_erase);
							}
							stack_state_recurse_dependency.pop();
							assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended);
							break;
						}
						assert(state_recurse_dependency.idx_pipelinefilterposition_resolving < state_recurse_dependency.vec_pipelinefilterposition->size());
						const PipelineFilterPosition& pipelinefilterposition = (*state_recurse_dependency.vec_pipelinefilterposition)[state_recurse_dependency.idx_pipelinefilterposition_resolving];
						switch (pipelinefilterposition.pipelinefilterpositiontype) {
						case PipelineFilterPositionType::PipelineFilterPositionType_Front:
						{
							// The pipeline filter attachment should be inserted at the front of the invocation list.
							state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended;
							it_list_pipelinefilterattachment_invocation_return_recurse_dependency = this->list_pipelinefilterattachment_invocation.cbegin();
							is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = true;
							break;
						}
						case PipelineFilterPositionType::PipelineFilterPositionType_Back:
						{
							// The pipeline filter attachment should be inserted at the back of the invocation list.
							state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended;
							it_list_pipelinefilterattachment_invocation_return_recurse_dependency = this->list_pipelinefilterattachment_invocation.cend();
							is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = true;
							break;
						}
						case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
							[[fallthrough]];
						case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
						{
							// Whether or not the pipeline filter attachment can be inserted here can be known only after resolving the depended pipeline filter attachment.
							state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended;
							stack_state_recurse_dependency.emplace(pipelinefilterposition.pipelinefilterid_ref);
							{
								bool is_successful_emplace = false;
								::std::tie(::std::ignore, is_successful_emplace) = set_pipelinefilterid_depended.emplace(pipelinefilterposition.pipelinefilterid_ref);
								if (!is_successful_emplace) {
									// Failure to emplace into set_pipelinefilterid_depended indicates that a cyclic dependency has been encountered.
									abort();
								}
							}
							break;
						}
						default:
							assert(false); abort();
						}
						break;
					}
					case state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended:
					{
						assert(state_recurse_dependency.vec_pipelinefilterposition);
						assert(state_recurse_dependency.idx_pipelinefilterposition_resolving < state_recurse_dependency.vec_pipelinefilterposition->size());
						if (!is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency) {
							// The pipeline filter attachment cannot be inserted here.
							// Continue to check the next candidate position.
							++state_recurse_dependency.idx_pipelinefilterposition_resolving;
							state_recurse_dependency.checkpoint = state_recurse_dependency_t::Checkpoint::Checkpoint_Loop;
							break;
						}
						// A place has been found for the pipeline filter attachment to be inserted.
						// The pipeline filter attachment should be made chained.
						map_ptr_pipelinefilterattachment_t::iterator it_map_pipelinefilterattachment_unchained = this->map_pipelinefilterattachment_unchained.find(state_recurse_dependency.pipelinefilterid);
						if (state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve != SIZE_MAX) {
							// The pipeline filter attachment is currently chained.
							assert(state_recurse_dependency.pipelinefilterattachment->idx_pipelinefilterposition_resolve < state_recurse_dependency.vec_pipelinefilterposition->size());
							assert(it_map_pipelinefilterattachment_unchained == this->map_pipelinefilterattachment_unchained.end());
							this->list_pipelinefilterattachment_invocation.erase(state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation);
						} else {
							// The pipeline filter attachment is currently unchained.
							assert(it_map_pipelinefilterattachment_unchained != this->map_pipelinefilterattachment_unchained.end());
							this->map_pipelinefilterattachment_unchained.erase(it_map_pipelinefilterattachment_unchained);
						}
						const PipelineFilterPosition& pipelinefilterposition = (*state_recurse_dependency.vec_pipelinefilterposition)[state_recurse_dependency.idx_pipelinefilterposition_resolving];
						switch (pipelinefilterposition.pipelinefilterpositiontype) {
						case PipelineFilterPositionType::PipelineFilterPositionType_Front:
							[[fallthrough]];
						case PipelineFilterPositionType::PipelineFilterPositionType_Back:
							[[fallthrough]];
						case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
						{
							state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation =
								this->list_pipelinefilterattachment_invocation.insert(
									it_list_pipelinefilterattachment_invocation_return_recurse_dependency,
									state_recurse_dependency.pipelinefilterattachment
								);
							break;
						}
						case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
						{
							// We cannot make the following assertion check, because past-the-end iterators of valid container objects cannot be compared with value-initialized iterators of the same type.
							//assert(it_list_pipelinefilterattachment_invocation_return_recurse_dependency != ::std::list<PipelineFilterAttachment*>::const_iterator());
							assert(it_list_pipelinefilterattachment_invocation_return_recurse_dependency != this->list_pipelinefilterattachment_invocation.cend());
							++it_list_pipelinefilterattachment_invocation_return_recurse_dependency;
							state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation =
								this->list_pipelinefilterattachment_invocation.insert(
									it_list_pipelinefilterattachment_invocation_return_recurse_dependency,
									state_recurse_dependency.pipelinefilterattachment
								);
							--it_list_pipelinefilterattachment_invocation_return_recurse_dependency;
							break;
						}
						default:
							assert(false); abort();
						}
						this->AdjustPipelineFilterAttachmentDependencyMaps(*state_recurse_dependency.pipelinefilterattachment, state_recurse_dependency.idx_pipelinefilterposition_resolving, _already_exclusive_locked_this);
						it_list_pipelinefilterattachment_invocation_return_recurse_dependency = state_recurse_dependency.pipelinefilterattachment->it_list_pipelinefilterattachment_invocation;
						is_available_it_list_pipelinefilterattachment_invocation_return_recurse_dependency = true;
						static_cast<void>(this->map_pipelinefilterattachment_floating.erase(state_recurse_dependency.pipelinefilterid));
						// Remove the pipeline filter attachment from the pending update map.
						map_pipelinefilterattachment_pending_update.erase(state_recurse_dependency.it_map_pipelinefilterattachment_pending_update);
						{
							bool is_successful_erase = false;
							is_successful_erase = set_pipelinefilterid_depended.erase(state_recurse_dependency.pipelinefilterid);
							assert(is_successful_erase); static_cast<void>(is_successful_erase);
						}
						stack_state_recurse_dependency.pop();
						assert(stack_state_recurse_dependency.empty() || stack_state_recurse_dependency.top().checkpoint == state_recurse_dependency_t::Checkpoint::Checkpoint_AfterResolveDepended);
						break;
					}
					default:
						assert(false); abort();
					}
				} else if (!map_pipelinefilterattachment_pending_update.empty()) {
					// We're not in a recursion.
					// However, some pipeline filter attachments are still pending update.
					assert(set_pipelinefilterid_depended.empty());
					// Start a new recursion.
					assert(map_pipelinefilterattachment_pending_update.begin()->second);
					stack_state_recurse_dependency.emplace(map_pipelinefilterattachment_pending_update.begin()->first);
					{
						bool is_successful_emplace = false;
						::std::tie(::std::ignore, is_successful_emplace) = set_pipelinefilterid_depended.emplace(map_pipelinefilterattachment_pending_update.begin()->first);
						assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
					}
				} else {
					assert(set_pipelinefilterid_depended.empty());
					break;
				}
			}
		}
		assert(map_pipelinefilterattachment_pending_update.empty());
		assert(this->IsResolved(_already_exclusive_locked_this));
	}

	size_t Pipeline::AllocateInvocationPacketData(size_t _count_slot_invocationpacketdata_allocate, already_exclusive_locked_this_t) noexcept {
		assert(_count_slot_invocationpacketdata_allocate);
		map_slot_invocationpacketdata_size_t::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.upper_bound(::std::tuple(_count_slot_invocationpacketdata_allocate, below_min_t<size_t>()));
		size_t idx_slot_invocationpacketdata_allocate = SIZE_MAX;
		if (it_map_slot_invocationpacketdata_size_free == this->map_slot_invocationpacketdata_size_free.end()) {
			// No sufficiently large contiguous block of free slots is found.
			// Extend the invocation packet data size.
			idx_slot_invocationpacketdata_allocate = this->count_slot_invocationpacketdata;
			this->count_slot_invocationpacketdata += _count_slot_invocationpacketdata_allocate;
		} else {
			// A sufficiently large contiguous block of free slots is found.
			// Use the contiguous block found.
			map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block = it_map_slot_invocationpacketdata_size_free->second;
			assert(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block != this->map_slot_invocationpacketdata_rangeboundary_free.end());
			map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
			++it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
			assert(it_map_slot_invocationpacketdata_rangeboundary_free_end_block != this->map_slot_invocationpacketdata_rangeboundary_free.end());
			assert(
				it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first < it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
				&& it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first + ::std::get<0>(it_map_slot_invocationpacketdata_size_free->first) == it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
				&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first <= this->count_slot_invocationpacketdata
				&& (!it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->second && it_map_slot_invocationpacketdata_rangeboundary_free_end_block->second)
			);
			idx_slot_invocationpacketdata_allocate = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first;
			this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			if (::std::get<0>(it_map_slot_invocationpacketdata_size_free->first) == _count_slot_invocationpacketdata_allocate) {
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
					assert(is_successful_emplace_map_slot_invocationpacketdata_rangeboundary_free); static_cast<void>(is_successful_emplace_map_slot_invocationpacketdata_rangeboundary_free);
				}
				this->map_slot_invocationpacketdata_size_free.emplace(::std::tuple(::std::get<0>(it_map_slot_invocationpacketdata_size_free->first) - _count_slot_invocationpacketdata_allocate, idx_slot_invocationpacketdata_allocate + _count_slot_invocationpacketdata_allocate), it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
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
				map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block = this->map_slot_invocationpacketdata_rangeboundary_free.end();
				--it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_end_block != this->map_slot_invocationpacketdata_rangeboundary_free.begin()
					&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first <= this->count_slot_invocationpacketdata
					&& it_map_slot_invocationpacketdata_rangeboundary_free_end_block->second
				);
				map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block = it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
				--it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				assert(
					it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first < it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first
					&& !it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->second
				);
				if (it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first == this->count_slot_invocationpacketdata) {
					// The last free contiguous block is now at the end.
					// Remove the contiguous block and shrink the invocation packet data size even more.
					map_slot_invocationpacketdata_size_t::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.find(::std::tuple(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first));
					assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					assert(it_map_slot_invocationpacketdata_size_free->second == it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
					this->count_slot_invocationpacketdata = it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first;
					this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
					this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_end_block);
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
				}
			}
		} else {
			// The deallocation doesn't happen at the end.
			// Mark the deallocated slots as free slots.
			map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.lower_bound(_idx_slot_invocationpacketdata_deallocate);
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
				map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				bool is_successful_emplace = false;
				::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate, false);
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				::std::tie(::std::ignore, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate + _count_slot_invocationpacketdata_deallocate, true);
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				this->map_slot_invocationpacketdata_size_free.emplace(::std::tuple(_count_slot_invocationpacketdata_deallocate, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first), it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			} else {
				map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_begin_block;
				map_slot_invocationpacketdata_rangeboundary_t::iterator it_map_slot_invocationpacketdata_rangeboundary_free_end_block;
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
					map_slot_invocationpacketdata_size_t::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.find(::std::tuple(it_map_slot_invocationpacketdata_rangeboundary_free_next->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first));
					assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					assert(it_map_slot_invocationpacketdata_size_free->second == it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
					it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_next);
				} else {
					// Create the left(lower) boundary.
					bool is_successful_emplace = false;
					::std::tie(it_map_slot_invocationpacketdata_rangeboundary_free_begin_block, is_successful_emplace) = this->map_slot_invocationpacketdata_rangeboundary_free.emplace(_idx_slot_invocationpacketdata_deallocate, false);
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
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
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
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
					map_slot_invocationpacketdata_size_t::iterator it_map_slot_invocationpacketdata_size_free = this->map_slot_invocationpacketdata_size_free.find(::std::tuple(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_next->first, it_map_slot_invocationpacketdata_rangeboundary_free_next->first));
					assert(it_map_slot_invocationpacketdata_size_free != this->map_slot_invocationpacketdata_size_free.end());
					assert(it_map_slot_invocationpacketdata_size_free->second == it_map_slot_invocationpacketdata_rangeboundary_free_next);
					this->map_slot_invocationpacketdata_size_free.erase(it_map_slot_invocationpacketdata_size_free);
					it_map_slot_invocationpacketdata_rangeboundary_free_next = this->map_slot_invocationpacketdata_rangeboundary_free.erase(it_map_slot_invocationpacketdata_rangeboundary_free_next);
					assert(it_map_slot_invocationpacketdata_rangeboundary_free_next == it_map_slot_invocationpacketdata_rangeboundary_free_end_block);
				}
				this->map_slot_invocationpacketdata_size_free.emplace(::std::tuple(it_map_slot_invocationpacketdata_rangeboundary_free_end_block->first - it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first, it_map_slot_invocationpacketdata_rangeboundary_free_begin_block->first), it_map_slot_invocationpacketdata_rangeboundary_free_begin_block);
			}
		}
	}

	void Pipeline::AdjustPipelineFilterAttachmentDependencyMapsInitialize(PipelineFilterAttachment& _pipelinefilterattachment, already_exclusive_locked_this_t) noexcept {
		::std::vector<PipelineFilterPosition>* vec_pipelinefilterposition = _pipelinefilterattachment.IsZombie() ? &_pipelinefilterattachment.vec_pipelinefilterposition_zombie : &_pipelinefilterattachment.pipelinefilter->vec_pipelinefilterposition;
		::std::pair<
			::std::vector<PipelineFilterPosition>::const_iterator,
			::std::vector<PipelineFilterPosition>::const_iterator
		> range_vec_pipelinefilterposition_add_expecting;
		range_vec_pipelinefilterposition_add_expecting.first = vec_pipelinefilterposition->cbegin();
		if (_pipelinefilterattachment.idx_pipelinefilterposition_resolve != SIZE_MAX) {
			assert(_pipelinefilterattachment.idx_pipelinefilterposition_resolve < vec_pipelinefilterposition->size());
			range_vec_pipelinefilterposition_add_expecting.second = vec_pipelinefilterposition->cbegin() + _pipelinefilterattachment.idx_pipelinefilterposition_resolve;
			const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_pipelinefilterattachment.idx_pipelinefilterposition_resolve];
			switch (pipelinefilterposition.pipelinefilterpositiontype) {
			case PipelineFilterPositionType::PipelineFilterPositionType_Front:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_Back:
				break;
			case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
			{
				bool is_successful_emplace = false;
				::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_dependency_current.emplace(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid), &_pipelinefilterattachment);
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				break;
			}
			default:
				assert(false); abort();
			}
		} else {
			range_vec_pipelinefilterposition_add_expecting.second = vec_pipelinefilterposition->cend();
		}
		for (
			::std::vector<PipelineFilterPosition>::const_iterator it_vec_pipelinefilterposition = range_vec_pipelinefilterposition_add_expecting.first;
			it_vec_pipelinefilterposition != range_vec_pipelinefilterposition_add_expecting.second;
			++it_vec_pipelinefilterposition
			) {
			const PipelineFilterPosition& pipelinefilterposition = *it_vec_pipelinefilterposition;
			switch (pipelinefilterposition.pipelinefilterpositiontype) {
			case PipelineFilterPositionType::PipelineFilterPositionType_Front:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_Back:
				break;
			case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
			{
				bool is_successful_emplace = false;
				::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_dependency_expecting.emplace(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid), &_pipelinefilterattachment);
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				break;
			}
			default:
				assert(false); abort();
			}
		}
		_pipelinefilterattachment.idx_pipelinefilterposition_resolve = SIZE_MAX;
	}

	void Pipeline::AdjustPipelineFilterAttachmentDependencyMapsClear(PipelineFilterAttachment& _pipelinefilterattachment, already_exclusive_locked_this_t) noexcept {
		::std::vector<PipelineFilterPosition>* vec_pipelinefilterposition = _pipelinefilterattachment.IsZombie() ? &_pipelinefilterattachment.vec_pipelinefilterposition_zombie : &_pipelinefilterattachment.pipelinefilter->vec_pipelinefilterposition;
		::std::pair<
			::std::vector<PipelineFilterPosition>::const_iterator,
			::std::vector<PipelineFilterPosition>::const_iterator
		> range_vec_pipelinefilterposition_remove_expecting;
		range_vec_pipelinefilterposition_remove_expecting.first = vec_pipelinefilterposition->cbegin();
		if (_pipelinefilterattachment.idx_pipelinefilterposition_resolve != SIZE_MAX) {
			assert(_pipelinefilterattachment.idx_pipelinefilterposition_resolve < vec_pipelinefilterposition->size());
			range_vec_pipelinefilterposition_remove_expecting.second = vec_pipelinefilterposition->cbegin() + _pipelinefilterattachment.idx_pipelinefilterposition_resolve;
			const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_pipelinefilterattachment.idx_pipelinefilterposition_resolve];
			switch (pipelinefilterposition.pipelinefilterpositiontype) {
			case PipelineFilterPositionType::PipelineFilterPositionType_Front:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_Back:
				break;
			case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
			{
				bool is_successful_erase = this->map_pipelinefilterattachment_dependency_current.erase(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid));
				assert(is_successful_erase); static_cast<void>(is_successful_erase);
				break;
			}
			default:
				assert(false); abort();
			}
		} else {
			range_vec_pipelinefilterposition_remove_expecting.second = vec_pipelinefilterposition->cend();
		}
		for (
			::std::vector<PipelineFilterPosition>::const_iterator it_vec_pipelinefilterposition = range_vec_pipelinefilterposition_remove_expecting.first;
			it_vec_pipelinefilterposition != range_vec_pipelinefilterposition_remove_expecting.second;
			++it_vec_pipelinefilterposition
			) {
			const PipelineFilterPosition& pipelinefilterposition = *it_vec_pipelinefilterposition;
			switch (pipelinefilterposition.pipelinefilterpositiontype) {
			case PipelineFilterPositionType::PipelineFilterPositionType_Front:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_Back:
				break;
			case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
				[[fallthrough]];
			case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
			{
				bool is_successful_erase = this->map_pipelinefilterattachment_dependency_expecting.erase(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid));
				assert(is_successful_erase); static_cast<void>(is_successful_erase);
				break;
			}
			default:
				assert(false); abort();
			}
		}
		_pipelinefilterattachment.idx_pipelinefilterposition_resolve = SIZE_MAX;
	}

	void Pipeline::AdjustPipelineFilterAttachmentDependencyMaps(PipelineFilterAttachment& _pipelinefilterattachment, size_t _idx_pipelinefilterposition_resolve_new, already_exclusive_locked_this_t) noexcept {
		if (_idx_pipelinefilterposition_resolve_new == _pipelinefilterattachment.idx_pipelinefilterposition_resolve) return;
		::std::vector<PipelineFilterPosition>* vec_pipelinefilterposition = _pipelinefilterattachment.IsZombie() ? &_pipelinefilterattachment.vec_pipelinefilterposition_zombie : &_pipelinefilterattachment.pipelinefilter->vec_pipelinefilterposition;
		if (_idx_pipelinefilterposition_resolve_new < _pipelinefilterattachment.idx_pipelinefilterposition_resolve) {
			::std::pair<
				::std::vector<PipelineFilterPosition>::const_iterator,
				::std::vector<PipelineFilterPosition>::const_iterator
			> range_vec_pipelinefilterposition_remove_expecting;
			assert(_idx_pipelinefilterposition_resolve_new < vec_pipelinefilterposition->size());
			{
				range_vec_pipelinefilterposition_remove_expecting.first = vec_pipelinefilterposition->cbegin() + _idx_pipelinefilterposition_resolve_new;
				const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_idx_pipelinefilterposition_resolve_new];
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_emplace = false;
					::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_dependency_current.emplace(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid), &_pipelinefilterattachment);
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
					break;
				}
				default:
					assert(false); abort();
				}
			}
			if (_pipelinefilterattachment.idx_pipelinefilterposition_resolve != SIZE_MAX) {
				assert(_pipelinefilterattachment.idx_pipelinefilterposition_resolve < vec_pipelinefilterposition->size());
				range_vec_pipelinefilterposition_remove_expecting.second = vec_pipelinefilterposition->cbegin() + _pipelinefilterattachment.idx_pipelinefilterposition_resolve;
				const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_pipelinefilterattachment.idx_pipelinefilterposition_resolve];
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_erase = this->map_pipelinefilterattachment_dependency_current.erase(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid));
					assert(is_successful_erase); static_cast<void>(is_successful_erase);
					break;
				}
				default:
					assert(false); abort();
				}
			} else {
				range_vec_pipelinefilterposition_remove_expecting.second = vec_pipelinefilterposition->cend();
			}
			for (
				::std::vector<PipelineFilterPosition>::const_iterator it_vec_pipelinefilterposition = range_vec_pipelinefilterposition_remove_expecting.first;
				it_vec_pipelinefilterposition != range_vec_pipelinefilterposition_remove_expecting.second;
				++it_vec_pipelinefilterposition
				) {
				const PipelineFilterPosition& pipelinefilterposition = *it_vec_pipelinefilterposition;
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_erase = this->map_pipelinefilterattachment_dependency_expecting.erase(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid));
					assert(is_successful_erase); static_cast<void>(is_successful_erase);
					break;
				}
				default:
					assert(false); abort();
				}
			}
		} else {
			::std::pair<
				::std::vector<PipelineFilterPosition>::const_iterator,
				::std::vector<PipelineFilterPosition>::const_iterator
			> range_vec_pipelinefilterposition_add_expecting;
			assert(_pipelinefilterattachment.idx_pipelinefilterposition_resolve < vec_pipelinefilterposition->size());
			{
				range_vec_pipelinefilterposition_add_expecting.first = vec_pipelinefilterposition->cbegin() + _pipelinefilterattachment.idx_pipelinefilterposition_resolve;
				const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_pipelinefilterattachment.idx_pipelinefilterposition_resolve];
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_erase = this->map_pipelinefilterattachment_dependency_current.erase(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid));
					assert(is_successful_erase); static_cast<void>(is_successful_erase);
					break;
				}
				default:
					assert(false); abort();
				}
			}
			if (_idx_pipelinefilterposition_resolve_new != SIZE_MAX) {
				assert(_idx_pipelinefilterposition_resolve_new < vec_pipelinefilterposition->size());
				range_vec_pipelinefilterposition_add_expecting.second = vec_pipelinefilterposition->cbegin() + _idx_pipelinefilterposition_resolve_new;
				const PipelineFilterPosition& pipelinefilterposition = (*vec_pipelinefilterposition)[_idx_pipelinefilterposition_resolve_new];
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_emplace = false;
					::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_dependency_current.emplace(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid), &_pipelinefilterattachment);
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
					break;
				}
				default:
					assert(false); abort();
				}
			} else {
				range_vec_pipelinefilterposition_add_expecting.second = vec_pipelinefilterposition->cend();
			}
			for (
				::std::vector<PipelineFilterPosition>::const_iterator it_vec_pipelinefilterposition = range_vec_pipelinefilterposition_add_expecting.first;
				it_vec_pipelinefilterposition != range_vec_pipelinefilterposition_add_expecting.second;
				++it_vec_pipelinefilterposition
				) {
				const PipelineFilterPosition& pipelinefilterposition = *it_vec_pipelinefilterposition;
				switch (pipelinefilterposition.pipelinefilterpositiontype) {
				case PipelineFilterPositionType::PipelineFilterPositionType_Front:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_Back:
					break;
				case PipelineFilterPositionType::PipelineFilterPositionType_BeforeRef:
					[[fallthrough]];
				case PipelineFilterPositionType::PipelineFilterPositionType_AfterRef:
				{
					bool is_successful_emplace = false;
					::std::tie(::std::ignore, is_successful_emplace) = this->map_pipelinefilterattachment_dependency_expecting.emplace(::std::tuple(pipelinefilterposition.pipelinefilterid_ref, _pipelinefilterattachment.pipelinefilterid), &_pipelinefilterattachment);
					assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
					break;
				}
				default:
					assert(false); abort();
				}
			}
		}
		_pipelinefilterattachment.idx_pipelinefilterposition_resolve = _idx_pipelinefilterposition_resolve_new;
	}

	Pipeline* PipelineStore::ReferencePipelineFromPipelineID(const PipelineID& _pipelineid) noexcept {
		{
			::std::shared_lock<::std::shared_mutex> shared_lock_this(this->mtx_this);
			map_pipeline_t::const_iterator it_map_pipeline = this->map_pipeline.find(_pipelineid);
			if (it_map_pipeline != this->map_pipeline.cend()) {
				assert(it_map_pipeline->second);
				Pipeline* pipeline = it_map_pipeline->second.get();
				pipeline->GetReferenceCountControlBlock()->IncStrongReferenceCount();
				return pipeline;
			}
		}
		{
			::std::unique_lock<::std::shared_mutex> unique_lock_this(this->mtx_this);
			map_pipeline_t::const_iterator it_map_pipeline = this->map_pipeline.find(_pipelineid);
			if (it_map_pipeline != this->map_pipeline.cend()) {
				assert(it_map_pipeline->second);
				Pipeline* pipeline = it_map_pipeline->second.get();
				pipeline->GetReferenceCountControlBlock()->IncStrongReferenceCount();
				return pipeline;
			} else {
				bool is_successful_emplace = false;
				::std::tie(it_map_pipeline, is_successful_emplace) = this->map_pipeline.emplace(_pipelineid, CreatePipeline(_pipelineid));
				assert(is_successful_emplace); static_cast<void>(is_successful_emplace);
				assert(it_map_pipeline != this->map_pipeline.cend());
				assert(it_map_pipeline->second);
				Pipeline* pipeline = it_map_pipeline->second.get();
				pipeline->GetReferenceCountControlBlock()->IncStrongReferenceCount();
				return pipeline;
			}
		}
	}

	namespace Internal {
		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PipelineID* _pipelineid) noexcept {
			assert(_pipelineid);
			return new Pipeline(*_pipelineid);
		}

		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE CreatePipeline(const PersistentID* _persistentid_pipelineid) noexcept {
			assert(_persistentid_pipelineid);
			return new Pipeline(*_persistentid_pipelineid);
		}

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(const Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<const IReferenceCountedObject*>(_pipeline) : nullptr;
		}

		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE Pipeline_CastToIReferenceCountedObject(Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<IReferenceCountedObject*>(_pipeline) : nullptr;
		}

		YBWLIB2_API const ISharedLockableObject* YBWLIB2_CALLTYPE Pipeline_CastToISharedLockableObject(const Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<const ISharedLockableObject*>(_pipeline) : nullptr;
		}

		YBWLIB2_API ISharedLockableObject* YBWLIB2_CALLTYPE Pipeline_CastToISharedLockableObject(Pipeline* _pipeline) noexcept {
			return _pipeline ? static_cast<ISharedLockableObject*>(_pipeline) : nullptr;
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

		YBWLIB2_API IndexedDataStore* YBWLIB2_CALLTYPE Pipeline_GetUserDataIndexedDataStore(Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			return &_pipeline->GetUserDataIndexedDataStore();
		}

		YBWLIB2_API const IndexedDataStore* YBWLIB2_CALLTYPE Pipeline_GetUserDataIndexedDataStore(const Pipeline* _pipeline) noexcept {
			assert(_pipeline);
			return &_pipeline->GetUserDataIndexedDataStore();
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

		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_IsResolved(const Pipeline* _pipeline, already_shared_locked_this_t _already_shared_locked_this) noexcept {
			assert(_pipeline);
			return _pipeline->IsResolved(_already_shared_locked_this);
		}

		YBWLIB2_API bool YBWLIB2_CALLTYPE Pipeline_IsResolved(const Pipeline* _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
			assert(_pipeline);
			return _pipeline->IsResolved(_already_exclusive_locked_this);
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

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_AddRefInvocationPacketDataEntry(
			const Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t _already_shared_locked_this
		) noexcept {
			assert(_pipeline);
			_pipeline->AddRefInvocationPacketDataEntry(*_pipelineinvocationpacketdataentryid, _size_invocationpacketdataentry, _offset_invocationpacketdataentry, _already_shared_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_DecRefInvocationPacketDataEntry(
			const Pipeline* _pipeline,
			const PipelineInvocationPacketDataEntryID* _pipelineinvocationpacketdataentryid,
			size_t _size_invocationpacketdataentry,
			size_t _offset_invocationpacketdataentry,
			already_shared_locked_this_t _already_shared_locked_this
		) noexcept {
			assert(_pipeline);
			_pipeline->DecRefInvocationPacketDataEntry(*_pipelineinvocationpacketdataentryid, _size_invocationpacketdataentry, _offset_invocationpacketdataentry, _already_shared_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_AttachPipelineFilter(Pipeline* _pipeline, PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, size_t* _idx_pipelinefilterposition_resolve_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->AttachPipelineFilter(_pipelinefilter, _should_resolve_immediately, _idx_pipelinefilterposition_resolve_ret, _already_exclusive_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_DetachPipelineFilter(Pipeline* _pipeline, PipelineFilter* _pipelinefilter, bool _should_resolve_immediately, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->DetachPipelineFilter(_pipelinefilter, _should_resolve_immediately, _already_exclusive_locked_this);
		}

		YBWLIB2_API void YBWLIB2_CALLTYPE Pipeline_Resolve(Pipeline* _pipeline, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept {
			assert(_pipeline);
			_pipeline->Resolve(_already_exclusive_locked_this);
		}

		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PipelineFilterID* _pipelinefilterid) noexcept {
			assert(_pipelinefilterid);
			return new PipelineFilter(*_pipelinefilterid);
		}

		YBWLIB2_API PipelineFilter* YBWLIB2_CALLTYPE CreatePipelineFilter(const PersistentID* _persistentid_pipelinefilterid) noexcept {
			assert(_persistentid_pipelinefilterid);
			return new PipelineFilter(*_persistentid_pipelinefilterid);
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

		YBWLIB2_API IndexedDataStore* YBWLIB2_CALLTYPE PipelineFilter_GetUserDataIndexedDataStore(PipelineFilter* _pipelinefilter) noexcept {
			assert(_pipelinefilter);
			return &_pipelinefilter->GetUserDataIndexedDataStore();
		}

		YBWLIB2_API const IndexedDataStore* YBWLIB2_CALLTYPE PipelineFilter_GetUserDataIndexedDataStore(const PipelineFilter* _pipelinefilter) noexcept {
			assert(_pipelinefilter);
			return &_pipelinefilter->GetUserDataIndexedDataStore();
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

		YBWLIB2_API void YBWLIB2_CALLTYPE PipelineFilter_SetPipelineFilterPositionArray(PipelineFilter* _pipelinefilter, const PipelineFilterPosition* _arr_pipelinefilterposition, size_t _size_pipelinefilterposition) noexcept {
			assert(_pipelinefilter);
			_pipelinefilter->SetPipelineFilterPositionArray(_arr_pipelinefilterposition, _size_pipelinefilterposition);
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

		YBWLIB2_API PipelineStore* YBWLIB2_CALLTYPE CreatePipelineStore() noexcept {
			return new PipelineStore();
		}

		YBWLIB2_API const IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineStore_CastToIReferenceCountedObject(const PipelineStore* _pipelinestore) noexcept {
			return _pipelinestore ? static_cast<const IReferenceCountedObject*>(_pipelinestore) : nullptr;
		}

		YBWLIB2_API IReferenceCountedObject* YBWLIB2_CALLTYPE PipelineStore_CastToIReferenceCountedObject(PipelineStore* _pipelinestore) noexcept {
			return _pipelinestore ? static_cast<IReferenceCountedObject*>(_pipelinestore) : nullptr;
		}

		YBWLIB2_API Pipeline* YBWLIB2_CALLTYPE PipelineStore_ReferencePipelineFromPipelineID(PipelineStore* _pipelinestore, const PipelineID* _pipelineid) noexcept {
			static_assert(::std::is_standard_layout_v<ReferenceCountedObjectHolder<Pipeline>>, "ReferenceCountedObjectHolder<Pipeline> is not standard layout.");
			assert(_pipelinestore);
			return _pipelinestore->ReferencePipelineFromPipelineID(*_pipelineid);
		}
	}

	void YBWLIB2_CALLTYPE Pipeline_RealInitGlobal() noexcept {
		{
			Pipeline::DynamicTypeThisClassObject = new DynamicTypeClassObj(
				GetDynamicTypeClassPersistentID<Pipeline>(),
				IsDynamicTypeModuleLocalClass<Pipeline>(),
				{
					DynamicTypeBaseClassDef<Pipeline, ReferenceCountedObject, 0>,
					DynamicTypeBaseClassDef<Pipeline, RecursiveSharedLockableObject, 0>
				},
				0, sizeof(Pipeline), alignof(Pipeline)
			);
		}
		Internal::pipelineinvocationpacketdataentryid_arr_ptr_arg = PipelineInvocationPacketDataEntryID(Internal::persistentid_pipelineinvocationpacketdataentryid_arr_ptr_arg);
		Internal::indexeddataentryid_invokedelegatecontext = IndexedDataEntryID(Internal::persistentid_indexeddataentryid_invokedelegatecontext);
		Internal::pipelinestore_global = new ReferenceCountedObjectHolder<PipelineStore>(CreatePipelineStore());
	}

	void YBWLIB2_CALLTYPE Pipeline_RealUnInitGlobal() noexcept {
		delete Internal::pipelinestore_global;
		Internal::pipelinestore_global = nullptr;
		Internal::indexeddataentryid_invokedelegatecontext = IndexedDataEntryID();
		Internal::pipelineinvocationpacketdataentryid_arr_ptr_arg = PipelineInvocationPacketDataEntryID();
		{
			delete Pipeline::DynamicTypeThisClassObject;
			Pipeline::DynamicTypeThisClassObject = nullptr;
		}
	}

	void YBWLIB2_CALLTYPE PipelineUserInterface_RealInitGlobal() noexcept {}

	void YBWLIB2_CALLTYPE PipelineUserInterface_RealUnInitGlobal() noexcept {}
}
