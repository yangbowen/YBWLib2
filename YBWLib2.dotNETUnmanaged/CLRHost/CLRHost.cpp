#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"

#include <objbase.h>
#include <mscoree.h>
#include <metahost.h>
#include <cor.h>
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "mscoree.lib")

#include "../../YBWLib2/Common/CommonLowLevel.h"
#include "../../YBWLib2/Exception/ExceptionLowLevel.h"
#include "../../YBWLib2/Exception/Exception.h"
#include "../../YBWLib2/Common/Common.h"
#include "../../YBWLib2/Common/CommonSTLHelper.h"
#include "../../YBWLib2/Common/CommonWindows.h"
#include "../../YBWLib2/Common/CommonSTLHelperWindows.h"
#include "../../YBWLib2/Pipeline/Pipeline.h"
#include "../YBWLib2dotNETUnmanagedApi.h"
#include "CLRHost.h"
#include "../ReferenceInfo.h"
#include "../../YBWLib2.dotNETMixed/InteropUnmanaged.h"

namespace YBWLib2 {
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	class CLRHostContext final
		: public virtual ReferenceCountedObject,
		public RecursiveSharedLockableObject,
		public ICLRHostContext,
		public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(CLRHostContext, , "5a36444a-7218-453b-bea1-6d4a56fd6d47");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(CLRHostContext);
		CLRHostContext() noexcept : indexeddatastore(rawallocator_crt_YBWLib2) {}
		virtual ~CLRHostContext() {
			SharedLockableObjectToSTLWrapper lockablewrapper_clrhostcontext(*static_cast<ICLRHostContext*>(this));
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_clrhostcontext(lockablewrapper_clrhostcontext); already_exclusive_locked_this_t already_exclusive_locked_clrhostcontext;
			pipelinewrapper_CLRHostStop(*this, already_exclusive_locked_clrhostcontext);
		}
	protected:
		using map_sharedgchandle_appdomainmanager_t = ::std::unordered_map<DWORD, dotNETMixed::SharedGCHandle>;
		IndexedDataStore indexeddatastore;
		CLRRuntimePolicy clrruntimepolicy;
		COMObjectHolder<ICLRMetaHost> comobjholder_ICLRMetaHost;
		COMObjectHolder<ICLRMetaHostPolicy> comobjholder_ICLRMetaHostPolicy;
		COMObjectHolder<ICLRRuntimeInfo> comobjholder_ICLRRuntimeInfo;
		COMObjectHolder<IMetaDataDispenserEx> comobjholder_IMetaDataDispenserEx;
		COMObjectHolder<ICLRRuntimeHost> comobjholder_ICLRRuntimeHost;
		COMObjectHolder<ICLRStrongName> comobjholder_ICLRStrongName;
		COMObjectHolder<ICLRControl> comobjholder_ICLRControl;
		COMObjectHolder<IHostControl> comobjholder_IHostControl;
		map_sharedgchandle_appdomainmanager_t map_sharedgchandle_appdomainmanager;
		inline virtual void LockExclusive() const noexcept override { this->RecursiveSharedLockableObject::LockExclusive(); }
		inline virtual bool TryLockExclusive() const noexcept override { return this->RecursiveSharedLockableObject::TryLockExclusive(); }
		inline virtual void UnlockExclusive() const noexcept override { this->RecursiveSharedLockableObject::UnlockExclusive(); }
		inline virtual void LockShared() const noexcept override { this->RecursiveSharedLockableObject::LockShared(); }
		inline virtual bool TryLockShared() const noexcept override { return this->RecursiveSharedLockableObject::TryLockShared(); }
		inline virtual void UnlockShared() const noexcept override { this->RecursiveSharedLockableObject::UnlockShared(); }
		inline virtual void GetIndexedDataStore(const IndexedDataStore** _indexeddatastore_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_indexeddatastore_ret);
			*_indexeddatastore_ret = &this->indexeddatastore;
		}
		inline virtual void GetIndexedDataStore(const IndexedDataStore** _indexeddatastore_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_indexeddatastore_ret);
			*_indexeddatastore_ret = &this->indexeddatastore;
		}
		inline virtual void GetIndexedDataStore(IndexedDataStore** _indexeddatastore_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_indexeddatastore_ret);
			*_indexeddatastore_ret = &this->indexeddatastore;
		}
		inline virtual void GetCLRRuntimePolicy(const CLRRuntimePolicy** _clrruntimepolicy_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_clrruntimepolicy_ret);
			*_clrruntimepolicy_ret = &this->clrruntimepolicy;
		}
		inline virtual void GetCLRRuntimePolicy(const CLRRuntimePolicy** _clrruntimepolicy_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_clrruntimepolicy_ret);
			*_clrruntimepolicy_ret = &this->clrruntimepolicy;
		}
		inline virtual void GetCLRRuntimePolicy(CLRRuntimePolicy** _clrruntimepolicy_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_clrruntimepolicy_ret);
			*_clrruntimepolicy_ret = &this->clrruntimepolicy;
		}
		inline virtual void GetCLRMetaHostCOMObjectHolder(const COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRMetaHost_ret);
			*_comobjholder_ICLRMetaHost_ret = &this->comobjholder_ICLRMetaHost;
		}
		inline virtual void GetCLRMetaHostCOMObjectHolder(const COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRMetaHost_ret);
			*_comobjholder_ICLRMetaHost_ret = &this->comobjholder_ICLRMetaHost;
		}
		inline virtual void GetCLRMetaHostCOMObjectHolder(COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRMetaHost_ret);
			*_comobjholder_ICLRMetaHost_ret = &this->comobjholder_ICLRMetaHost;
		}
		inline virtual void GetCLRMetaHostPolicyCOMObjectHolder(const COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRMetaHostPolicy_ret);
			*_comobjholder_ICLRMetaHostPolicy_ret = &this->comobjholder_ICLRMetaHostPolicy;
		}
		inline virtual void GetCLRMetaHostPolicyCOMObjectHolder(const COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRMetaHostPolicy_ret);
			*_comobjholder_ICLRMetaHostPolicy_ret = &this->comobjholder_ICLRMetaHostPolicy;
		}
		inline virtual void GetCLRMetaHostPolicyCOMObjectHolder(COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRMetaHostPolicy_ret);
			*_comobjholder_ICLRMetaHostPolicy_ret = &this->comobjholder_ICLRMetaHostPolicy;
		}
		inline virtual void GetCLRRuntimeInfoCOMObjectHolder(const COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRRuntimeInfo_ret);
			*_comobjholder_ICLRRuntimeInfo_ret = &this->comobjholder_ICLRRuntimeInfo;
		}
		inline virtual void GetCLRRuntimeInfoCOMObjectHolder(const COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRRuntimeInfo_ret);
			*_comobjholder_ICLRRuntimeInfo_ret = &this->comobjholder_ICLRRuntimeInfo;
		}
		inline virtual void GetCLRRuntimeInfoCOMObjectHolder(COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRRuntimeInfo_ret);
			*_comobjholder_ICLRRuntimeInfo_ret = &this->comobjholder_ICLRRuntimeInfo;
		}
		inline virtual void GetMetaDataDispenserExCOMObjectHolder(const COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_IMetaDataDispenserEx_ret);
			*_comobjholder_IMetaDataDispenserEx_ret = &this->comobjholder_IMetaDataDispenserEx;
		}
		inline virtual void GetMetaDataDispenserExCOMObjectHolder(const COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_IMetaDataDispenserEx_ret);
			*_comobjholder_IMetaDataDispenserEx_ret = &this->comobjholder_IMetaDataDispenserEx;
		}
		inline virtual void GetMetaDataDispenserExCOMObjectHolder(COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_IMetaDataDispenserEx_ret);
			*_comobjholder_IMetaDataDispenserEx_ret = &this->comobjholder_IMetaDataDispenserEx;
		}
		inline virtual void GetCLRRuntimeHostCOMObjectHolder(const COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRRuntimeHost_ret);
			*_comobjholder_ICLRRuntimeHost_ret = &this->comobjholder_ICLRRuntimeHost;
		}
		inline virtual void GetCLRRuntimeHostCOMObjectHolder(const COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRRuntimeHost_ret);
			*_comobjholder_ICLRRuntimeHost_ret = &this->comobjholder_ICLRRuntimeHost;
		}
		inline virtual void GetCLRRuntimeHostCOMObjectHolder(COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRRuntimeHost_ret);
			*_comobjholder_ICLRRuntimeHost_ret = &this->comobjholder_ICLRRuntimeHost;
		}
		inline virtual void GetCLRStrongNameCOMObjectHolder(const COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRStrongName_ret);
			*_comobjholder_ICLRStrongName_ret = &this->comobjholder_ICLRStrongName;
		}
		inline virtual void GetCLRStrongNameCOMObjectHolder(const COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRStrongName_ret);
			*_comobjholder_ICLRStrongName_ret = &this->comobjholder_ICLRStrongName;
		}
		inline virtual void GetCLRStrongNameCOMObjectHolder(COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRStrongName_ret);
			*_comobjholder_ICLRStrongName_ret = &this->comobjholder_ICLRStrongName;
		}
		inline virtual void GetCLRControlCOMObjectHolder(const COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_ICLRControl_ret);
			*_comobjholder_ICLRControl_ret = &this->comobjholder_ICLRControl;
		}
		inline virtual void GetCLRControlCOMObjectHolder(const COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRControl_ret);
			*_comobjholder_ICLRControl_ret = &this->comobjholder_ICLRControl;
		}
		inline virtual void GetCLRControlCOMObjectHolder(COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_ICLRControl_ret);
			*_comobjholder_ICLRControl_ret = &this->comobjholder_ICLRControl;
		}
		inline virtual void GetHostControlCOMObjectHolder(const COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_comobjholder_IHostControl_ret);
			*_comobjholder_IHostControl_ret = &this->comobjholder_IHostControl;
		}
		inline virtual void GetHostControlCOMObjectHolder(const COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_IHostControl_ret);
			*_comobjholder_IHostControl_ret = &this->comobjholder_IHostControl;
		}
		inline virtual void GetHostControlCOMObjectHolder(COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_comobjholder_IHostControl_ret);
			*_comobjholder_IHostControl_ret = &this->comobjholder_IHostControl;
		}
		virtual void GetAppDomainManagerSharedGCHandle(const dotNETMixed::SharedGCHandle** _sharedgchandle_AppDomainManager_ret, DWORD _appdomainid, already_shared_locked_this_t _already_shared_locked_this) const noexcept override {
			static_cast<void>(_already_shared_locked_this);
			assert(_sharedgchandle_AppDomainManager_ret);

			map_sharedgchandle_appdomainmanager_t::const_iterator it_map_sharedgchandle_appdomainmanager;
			it_map_sharedgchandle_appdomainmanager = this->map_sharedgchandle_appdomainmanager.find(_appdomainid);
			if (it_map_sharedgchandle_appdomainmanager == this->map_sharedgchandle_appdomainmanager.cend()) {
				*_sharedgchandle_AppDomainManager_ret = &it_map_sharedgchandle_appdomainmanager->second;
			} else {
				*_sharedgchandle_AppDomainManager_ret = nullptr;
			}
		}
		virtual void GetAppDomainManagerSharedGCHandle(const dotNETMixed::SharedGCHandle** _sharedgchandle_AppDomainManager_ret, DWORD _appdomainid, already_exclusive_locked_this_t _already_exclusive_locked_this) const noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_sharedgchandle_AppDomainManager_ret);
			map_sharedgchandle_appdomainmanager_t::const_iterator it_map_sharedgchandle_appdomainmanager;
			it_map_sharedgchandle_appdomainmanager = this->map_sharedgchandle_appdomainmanager.find(_appdomainid);
			if (it_map_sharedgchandle_appdomainmanager == this->map_sharedgchandle_appdomainmanager.cend()) {
				*_sharedgchandle_AppDomainManager_ret = &it_map_sharedgchandle_appdomainmanager->second;
			} else {
				*_sharedgchandle_AppDomainManager_ret = nullptr;
			}
		}
		virtual void GetAppDomainManagerSharedGCHandle(dotNETMixed::SharedGCHandle** _sharedgchandle_AppDomainManager_ret, DWORD _appdomainid, bool _may_insert, already_exclusive_locked_this_t _already_exclusive_locked_this) noexcept override {
			static_cast<void>(_already_exclusive_locked_this);
			assert(_sharedgchandle_AppDomainManager_ret);
			map_sharedgchandle_appdomainmanager_t::iterator it_map_sharedgchandle_appdomainmanager;
			if (_may_insert) {
				::std::tie(it_map_sharedgchandle_appdomainmanager, ::std::ignore) = this->map_sharedgchandle_appdomainmanager.insert(::std::pair(_appdomainid, dotNETMixed::SharedGCHandle()));
			} else {
				it_map_sharedgchandle_appdomainmanager = this->map_sharedgchandle_appdomainmanager.find(_appdomainid);
			}
			if (it_map_sharedgchandle_appdomainmanager == this->map_sharedgchandle_appdomainmanager.end()) {
				*_sharedgchandle_AppDomainManager_ret = &it_map_sharedgchandle_appdomainmanager->second;
			} else {
				*_sharedgchandle_AppDomainManager_ret = nullptr;
			}
		}
	};

	class CLRHostControl final
		: public virtual ReferenceCountedObject,
		public IHostControl,
		public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(CLRHostControl, , "bc5f544b-0a02-452a-ba73-98f088f5c2a9");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(CLRHostControl);
		CLRHostControl(const ReferenceCountedObjectHolder<ICLRHostContext>& _clrhostcontext) noexcept {
			assert(_clrhostcontext);
			this->refcountedobjectweakholder_clrhostcontext = _clrhostcontext;
		};
		virtual ~CLRHostControl() {}
		inline virtual ULONG STDMETHODCALLTYPE AddRef() override {
			return YBWLib2::COMHelper_ReferenceCountedObject_AddRef(this);
		}
		inline virtual ULONG STDMETHODCALLTYPE Release() override {
			return YBWLib2::COMHelper_ReferenceCountedObject_Release(this);
		}
		inline virtual HRESULT STDMETHODCALLTYPE QueryInterface(
			/* [in] */ REFIID _iid,
			/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* _obj_ret
		) override {
			return YBWLib2::COMHelper_QueryInterface<CLRHostControl, IUnknown, IHostControl>(this, _iid, _obj_ret);
		}
		inline virtual HRESULT STDMETHODCALLTYPE GetHostManager(
			/* [in] */ REFIID _iid,
			/* [out] */ void** _hostmanager_ret
		) noexcept override {
			if (!_hostmanager_ret) return E_POINTER;
			ReferenceCountedObjectHolder<ICLRHostContext> clrhostcontext = this->refcountedobjectweakholder_clrhostcontext.lock();
			if (!clrhostcontext) return HOST_E_CLRNOTAVAILABLE;
			HRESULT hr = E_NOINTERFACE;
			*_hostmanager_ret = nullptr;
			SharedLockableObjectToSTLWrapper lockablewrapper_clrhostcontext(*clrhostcontext);
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_clrhostcontext(lockablewrapper_clrhostcontext); already_exclusive_locked_this_t already_exclusive_locked_clrhostcontext;
			pipelinewrapper_CLRHostGetHostManager(hr, *clrhostcontext, already_exclusive_locked_clrhostcontext, IID(_iid), *_hostmanager_ret);
			return hr;
		}
		inline virtual HRESULT STDMETHODCALLTYPE SetAppDomainManager(
			/* [in] */ DWORD _appdomainid,
			/* [in] */ IUnknown* _iunknown_appdomainmanager
		) noexcept override {
			ReferenceCountedObjectHolder<ICLRHostContext> clrhostcontext = this->refcountedobjectweakholder_clrhostcontext.lock();
			if (!clrhostcontext) return HOST_E_CLRNOTAVAILABLE;
			if (!_iunknown_appdomainmanager) return E_POINTER;
			COMObjectHolder<IUnknown> comobjholder_IUnknown_appdomainmanager;
			dotNETMixed::SharedGCHandle sharedgchandle_appdomainmanager;
			sharedgchandle_appdomainmanager = dotNETMixed::SharedGCHandleFromIUnknown(comobjholder_IUnknown_appdomainmanager, dotNETMixed::GCHandleType::Normal);
			HRESULT hr = S_OK;
			SharedLockableObjectToSTLWrapper lockablewrapper_clrhostcontext(*clrhostcontext);
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_clrhostcontext(lockablewrapper_clrhostcontext); already_exclusive_locked_this_t already_exclusive_locked_clrhostcontext;
			pipelinewrapper_CLRHostSetAppDomainManager(hr, *clrhostcontext, already_exclusive_locked_clrhostcontext, _appdomainid, comobjholder_IUnknown_appdomainmanager, sharedgchandle_appdomainmanager);
			return hr;
		}
	protected:
		ReferenceCountedObjectWeakHolder<ICLRHostContext> refcountedobjectweakholder_clrhostcontext;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	class CLRHostManager_CLRHost final
		: public virtual ReferenceCountedObject,
		public IUnknown,
		public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(CLRHostManager_CLRHost, , "e3c83eb7-2bc7-4d48-aba1-2721300a599a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(CLRHostManager_CLRHost);
		CLRHostManager_CLRHost(const ReferenceCountedObjectHolder<ICLRHostContext>& _clrhostcontext) noexcept {
			assert(_clrhostcontext);
			this->refcountedobjectweakholder_clrhostcontext = _clrhostcontext;
		};
		virtual ~CLRHostManager_CLRHost() {}
		inline virtual ULONG STDMETHODCALLTYPE AddRef() override {
			return YBWLib2::COMHelper_ReferenceCountedObject_AddRef(this);
		}
		inline virtual ULONG STDMETHODCALLTYPE Release() override {
			return YBWLib2::COMHelper_ReferenceCountedObject_Release(this);
		}
		inline virtual HRESULT STDMETHODCALLTYPE QueryInterface(
			/* [in] */ REFIID _iid,
			/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* _obj_ret
		) override {
			return YBWLib2::COMHelper_QueryInterface<
				CLRHostManager_CLRHost,
				IUnknown
			>(this, _iid, _obj_ret);
		}
	protected:
		ReferenceCountedObjectWeakHolder<ICLRHostContext> refcountedobjectweakholder_clrhostcontext;
	};

	static constexpr PersistentID persistentid_entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost = PersistentID(UUIDFromUUIDString_CompileTime("c5d3292c-9b09-49ae-9414-2c1d745d0d73"));
	IndexedDataEntryID entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost;

	YBWLIB2DOTNETUNMANAGED_API DynamicTypeClassObj* ICLRHostContext::DynamicTypeThisClassObject = nullptr;
	DynamicTypeClassObj* CLRHostContext::DynamicTypeThisClassObject = nullptr;
	DynamicTypeClassObj* CLRHostControl::DynamicTypeThisClassObject = nullptr;
	DynamicTypeClassObj* CLRHostManager_CLRHost::DynamicTypeThisClassObject = nullptr;

	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStart pipelinewrapper_CLRHostStart;
	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStop pipelinewrapper_CLRHostStop;
	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostGetHostManager pipelinewrapper_CLRHostGetHostManager;
	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostSetAppDomainManager pipelinewrapper_CLRHostSetAppDomainManager;

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_COMInit(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateMetaHost(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_MakeRuntimePolicy(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInfo(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInterfaces(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetCLRControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetAppDomainManagerType(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateHostControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetHostControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_StartRuntimeHost(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_StopRuntimeHost(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseHostControl(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseCLRControl(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseRuntimeInterfaces(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseRuntimeInfo(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseMetaHost(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_COMUnInit(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostGetHostManager_CLRHost(HRESULT& _hr, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext, const IID& _iid, void*& _hostmanager_ret) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle(HRESULT& _hr, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext, DWORD _appdomainid, const COMObjectHolder<IUnknown>& _comobjholder_IUnknown_appdomainmanager, const dotNETMixed::SharedGCHandle& _sharedgchandle_appdomainmanager) noexcept;

	namespace Internal {
		[[nodiscard]] YBWLIB2DOTNETUNMANAGED_API IException* YBWLIB2DOTNETUNMANAGED_CALLTYPE StartCLRHost(ReferenceCountedObjectHolder<ICLRHostContext>* _clrhostcontext_ret, CLRRuntimePolicy* _clrruntimepolicy) noexcept {
			IException* err = nullptr;
			ReferenceCountedObjectHolder<CLRHostContext> clrhostcontext(new CLRHostContext());
			assert(clrhostcontext);
			SharedLockableObjectToSTLWrapper lockablewrapper_clrhostcontext(*static_cast<ICLRHostContext*>(clrhostcontext.get()));
			::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_clrhostcontext(lockablewrapper_clrhostcontext); already_exclusive_locked_this_t already_exclusive_locked_clrhostcontext;
			if (_clrruntimepolicy) clrhostcontext->ICLRHostContext::GetCLRRuntimePolicy(already_exclusive_locked_clrhostcontext) = *_clrruntimepolicy;
			pipelinewrapper_CLRHostStart(err, *clrhostcontext, already_exclusive_locked_clrhostcontext);
			if (_clrhostcontext_ret) *_clrhostcontext_ret = clrhostcontext;
			return err;
		}
	}

	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealInitGlobal() noexcept {
		{
			entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost = IndexedDataEntryID(persistentid_entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost);
		}
		{
			ICLRHostContext::DynamicTypeThisClassObject = new DynamicTypeClassObj(
				GetDynamicTypeClassPersistentID<ICLRHostContext>(),
				IsDynamicTypeModuleLocalClass<ICLRHostContext>(),
				{ DynamicTypeBaseClassDef<ICLRHostContext, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
				0, sizeof(ICLRHostContext), alignof(ICLRHostContext)
			);
			CLRHostContext::DynamicTypeThisClassObject = new DynamicTypeClassObj(
				GetDynamicTypeClassPersistentID<CLRHostContext>(),
				IsDynamicTypeModuleLocalClass<CLRHostContext>(),
				{
					DynamicTypeBaseClassDef<CLRHostContext, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase>,
					DynamicTypeBaseClassDef<CLRHostContext, ICLRHostContext, 0>
				},
				0, sizeof(CLRHostContext), alignof(CLRHostContext)
			);
			CLRHostControl::DynamicTypeThisClassObject = new DynamicTypeClassObj(
				GetDynamicTypeClassPersistentID<CLRHostControl>(),
				IsDynamicTypeModuleLocalClass<CLRHostControl>(),
				{ DynamicTypeBaseClassDef<CLRHostControl, ReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
				0, sizeof(CLRHostControl), alignof(CLRHostControl)
			);
			CLRHostManager_CLRHost::DynamicTypeThisClassObject = new DynamicTypeClassObj(
				GetDynamicTypeClassPersistentID<CLRHostManager_CLRHost>(),
				IsDynamicTypeModuleLocalClass<CLRHostManager_CLRHost>(),
				{ DynamicTypeBaseClassDef<CLRHostManager_CLRHost, ReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
				0, sizeof(CLRHostManager_CLRHost), alignof(CLRHostManager_CLRHost)
			);
			GetDynamicTypeClassObject<ICLRHostContext>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ICLRHostContext)), module_info_current);
			GetDynamicTypeClassObject<CLRHostContext>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(CLRHostContext)), module_info_current);
			GetDynamicTypeClassObject<CLRHostControl>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(CLRHostControl)), module_info_current);
			GetDynamicTypeClassObject<CLRHostManager_CLRHost>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(CLRHostManager_CLRHost)), module_info_current);
		}
		{
			pipelinewrapper_CLRHostStart = PipelineWrapper_CLRHostStart(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostStart);
			pipelinewrapper_CLRHostStop = PipelineWrapper_CLRHostStop(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostStop);
			pipelinewrapper_CLRHostGetHostManager = PipelineWrapper_CLRHostGetHostManager(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostGetHostManager);
			pipelinewrapper_CLRHostSetAppDomainManager = PipelineWrapper_CLRHostSetAppDomainManager(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostSetAppDomainManager);
		}
		{
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_COMInit);
			pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_COMInit));
			pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.SetPipelineFilterPositionArray(PipelineFilterPosition_Back);
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateMetaHost);
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_CreateMetaHost));
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_MakeRuntimePolicy);
			pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_MakeRuntimePolicy));
			pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInfo);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_GetRuntimeInfo));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInterfaces);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_GetRuntimeInterfaces));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetCLRControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_GetCLRControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetAppDomainManagerType);
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_SetAppDomainManagerType));
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateHostControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_CreateHostControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetHostControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_SetHostControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_StartRuntimeHost);
			pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStart_CLRHost_StartRuntimeHost));
			pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.GetPipelineFilterID()));
			{
				SharedLockableObjectToSTLWrapper pipelinesharedlockablewrapper(pipelinewrapper_CLRHostStart.GetPipelineSharedLockableWrapper());
				::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(pipelinesharedlockablewrapper); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStart.Resolve(already_exclusive_locked_pipeline);
			}
		}
		{
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_StopRuntimeHost(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_StopRuntimeHost);
			pipelinefilterwrapper_CLRHostStop_CLRHost_StopRuntimeHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_StopRuntimeHost));
			pipelinefilterwrapper_CLRHostStop_CLRHost_StopRuntimeHost.SetPipelineFilterPositionArray(PipelineFilterPosition_Back);
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseHostControl(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_ReleaseHostControl);
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseHostControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_ReleaseHostControl));
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseHostControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_StopRuntimeHost.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseCLRControl(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_ReleaseCLRControl);
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseCLRControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_ReleaseCLRControl));
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseCLRControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseHostControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces);
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_ReleaseRuntimeInterfaces));
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseCLRControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInfo(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_ReleaseRuntimeInfo);
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInfo.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_ReleaseRuntimeInfo));
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInfo.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseMetaHost(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_ReleaseMetaHost);
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseMetaHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_ReleaseMetaHost));
			pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseMetaHost.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInfo.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStop pipelinefilterwrapper_CLRHostStop_CLRHost_COMUnInit(PersistentID_PipelineFilterID_CLRHostStop_CLRHost_COMUnInit);
			pipelinefilterwrapper_CLRHostStop_CLRHost_COMUnInit.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, ICLRHostContext&, already_exclusive_locked_this_t>(&CLRHostStop_CLRHost_COMUnInit));
			pipelinefilterwrapper_CLRHostStop_CLRHost_COMUnInit.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseMetaHost.GetPipelineFilterID()));
			{
				SharedLockableObjectToSTLWrapper pipelinesharedlockablewrapper(pipelinewrapper_CLRHostStop.GetPipelineSharedLockableWrapper());
				::std::unique_lock<SharedLockableObjectToSTLWrapper> unique_lock_pipeline(pipelinesharedlockablewrapper); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_StopRuntimeHost, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseHostControl, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseCLRControl, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInterfaces, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseRuntimeInfo, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_ReleaseMetaHost, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.AttachPipelineFilter(pipelinefilterwrapper_CLRHostStop_CLRHost_COMUnInit, false, nullptr, already_exclusive_locked_pipeline);
				pipelinewrapper_CLRHostStop.Resolve(already_exclusive_locked_pipeline);
			}
		}
		{
			PipelineFilterWrapper_CLRHostGetHostManager pipelinefilterwrapper_CLRHostGetHostManager_CLRHost(PersistentID_PipelineFilterID_CLRHostGetHostManager_CLRHost);
			pipelinefilterwrapper_CLRHostGetHostManager_CLRHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, HRESULT&, ICLRHostContext&, already_exclusive_locked_this_t, const IID&, void*&>(&CLRHostGetHostManager_CLRHost));
			pipelinefilterwrapper_CLRHostGetHostManager_CLRHost.SetPipelineFilterPositionArray(PipelineFilterPosition_Back);
			pipelinefilterwrapper_CLRHostGetHostManager_CLRHost.AttachToPipeline(pipelinewrapper_CLRHostGetHostManager, true, nullptr);
		}
		{
			PipelineFilterWrapper_CLRHostSetAppDomainManager pipelinefilterwrapper_CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle(PersistentID_PipelineFilterID_CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle);
			pipelinefilterwrapper_CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, HRESULT&, ICLRHostContext&, already_exclusive_locked_this_t, DWORD, const COMObjectHolder<IUnknown>&, const dotNETMixed::SharedGCHandle&>(&CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle));
			pipelinefilterwrapper_CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle.SetPipelineFilterPositionArray(PipelineFilterPosition_Back);
			pipelinefilterwrapper_CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle.AttachToPipeline(pipelinewrapper_CLRHostSetAppDomainManager, true, nullptr);
		}
	}

	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealUnInitGlobal() noexcept {
		{
			pipelinewrapper_CLRHostSetAppDomainManager = PipelineWrapper_CLRHostSetAppDomainManager();
			pipelinewrapper_CLRHostGetHostManager = PipelineWrapper_CLRHostGetHostManager();
			pipelinewrapper_CLRHostStop = PipelineWrapper_CLRHostStop();
			pipelinewrapper_CLRHostStart = PipelineWrapper_CLRHostStart();
		}
		{
			GetDynamicTypeClassObject<CLRHostManager_CLRHost>()->UnRegisterTypeInfoWrapper(module_info_current);
			GetDynamicTypeClassObject<CLRHostControl>()->UnRegisterTypeInfoWrapper(module_info_current);
			GetDynamicTypeClassObject<CLRHostContext>()->UnRegisterTypeInfoWrapper(module_info_current);
			GetDynamicTypeClassObject<ICLRHostContext>()->UnRegisterTypeInfoWrapper(module_info_current);
			delete CLRHostManager_CLRHost::DynamicTypeThisClassObject;
			CLRHostManager_CLRHost::DynamicTypeThisClassObject;
			delete CLRHostControl::DynamicTypeThisClassObject;
			CLRHostControl::DynamicTypeThisClassObject;
			delete CLRHostContext::DynamicTypeThisClassObject;
			CLRHostContext::DynamicTypeThisClassObject;
			delete ICLRHostContext::DynamicTypeThisClassObject;
			ICLRHostContext::DynamicTypeThisClassObject;
		}
		{
			entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost = IndexedDataEntryID();
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_COMInit(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		static_cast<void>(_clrhostcontext);
		static_cast<void>(_already_exclusive_locked_clrhostcontext);
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CoInitializeEx, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateMetaHost(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&_clrhostcontext.GetCLRMetaHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CLRCreateInstance, hr);
			return;
		}
		hr = CLRCreateInstance(CLSID_CLRMetaHostPolicy, IID_PPV_ARGS(&_clrhostcontext.GetCLRMetaHostPolicyCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CLRCreateInstance, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_MakeRuntimePolicy(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		CLRRuntimePolicy& clrruntimepolicy = _clrhostcontext.GetCLRRuntimePolicy(_already_exclusive_locked_clrhostcontext);
		clrruntimepolicy.metahostpolicyflags = static_cast<METAHOST_POLICY_FLAGS>(
			clrruntimepolicy.metahostconfigflags
			| METAHOST_POLICY_HIGHCOMPAT
			| METAHOST_POLICY_APPLY_UPGRADE_POLICY
			| METAHOST_POLICY_SHOW_ERROR_DIALOG
			);
		if (!clrruntimepolicy.holder_u16str_version.get_count()) {
			clrruntimepolicy.holder_u16str_version.construct(MAX_PATH + 1, objholder_rawallocator_t<char16_t[]>::construct_obj);
			assert(clrruntimepolicy.holder_u16str_version.get_count() <= MAXDWORD);
			DWORD dword_cch_u16str_version = clrruntimepolicy.holder_u16str_version.get_count() & ~(DWORD)0;
			static_assert(sizeof(wchar_t) == sizeof(char16_t));
			HRESULT hr = _clrhostcontext.GetCLRMetaHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->GetVersionFromFile(
				L"YBWLib2.dotNETMixed.dll",
				reinterpret_cast<wchar_t*>(clrruntimepolicy.holder_u16str_version.get()),
				&dword_cch_u16str_version
			);
			if (!SUCCEEDED(hr)) {
				_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CLRCreateInstance, hr);
				return;
			}
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInfo(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		CLRRuntimePolicy& clrruntimepolicy = _clrhostcontext.GetCLRRuntimePolicy(_already_exclusive_locked_clrhostcontext);
		static_assert(sizeof(DWORD) == sizeof(METAHOST_CONFIG_FLAGS));
		static_assert(sizeof(wchar_t) == sizeof(char16_t));
		assert(clrruntimepolicy.holder_u16str_version.get_count() <= MAXDWORD);
		DWORD dword_cch_u16str_version = clrruntimepolicy.holder_u16str_version.get_count() & ~(DWORD)0;
		assert(clrruntimepolicy.holder_u16str_version_image.get_count() <= MAXDWORD);
		DWORD dword_cch_u16str_version_image = clrruntimepolicy.holder_u16str_version_image.get_count() & ~(DWORD)0;
		HRESULT hr = _clrhostcontext.GetCLRMetaHostPolicyCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->GetRequestedRuntime(
			clrruntimepolicy.metahostpolicyflags,
			reinterpret_cast<const wchar_t*>(clrruntimepolicy.holder_u16str_path_assembly.get()),
			clrruntimepolicy.comobjholder_IStream_config.get(),
			reinterpret_cast<wchar_t*>(clrruntimepolicy.holder_u16str_version.get()),
			&dword_cch_u16str_version,
			reinterpret_cast<wchar_t*>(clrruntimepolicy.holder_u16str_version_image.get()),
			&dword_cch_u16str_version_image,
			reinterpret_cast<DWORD*>(&clrruntimepolicy.metahostconfigflags),
			IID_PPV_ARGS(&_clrhostcontext.GetCLRRuntimeInfoCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element())
		);
		_err = WrapFunctionCatchExceptions(
			[&clrruntimepolicy, &dword_cch_u16str_version, &dword_cch_u16str_version_image]() noexcept(false)->void {
				assert(dword_cch_u16str_version <= clrruntimepolicy.holder_u16str_version.get_count());
				clrruntimepolicy.holder_u16str_version.set_count(dword_cch_u16str_version & ~(size_t)0);
				assert(dword_cch_u16str_version_image <= clrruntimepolicy.holder_u16str_version_image.get_count());
				clrruntimepolicy.holder_u16str_version_image.set_count(dword_cch_u16str_version_image & ~(size_t)0);
			}
		);
		if (_err) return;
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRMetaHostPolicy::GetRequestedRuntime", sizeof(u8"ICLRMetaHostPolicy::GetRequestedRuntime") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInterfaces(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		COMObjectHolder<ICLRRuntimeInfo>& comobjholder_ICLRRuntimeInfo = _clrhostcontext.GetCLRRuntimeInfoCOMObjectHolder(_already_exclusive_locked_clrhostcontext);
		HRESULT hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CorMetaDataDispenser, IID_IMetaDataDispenserEx, reinterpret_cast<void**>(&_clrhostcontext.GetMetaDataDispenserExCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
		hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&_clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
		hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CLRStrongName, IID_PPV_ARGS(&_clrhostcontext.GetCLRStrongNameCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetCLRControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->GetCLRControl(&_clrhostcontext.GetCLRControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get_ref_ptr_element());
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::GetCLRControl", sizeof(u8"ICLRRuntimeHost::GetCLRControl") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetAppDomainManagerType(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		static_assert(sizeof(char16_t) == sizeof(wchar_t));
		HRESULT hr = _clrhostcontext.GetCLRControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->SetAppDomainManagerType(reinterpret_cast<const wchar_t*>(&u16str_strongname_dotNETMixed), reinterpret_cast<const wchar_t*>(u16str_dotnettypename_dotNETMixed_AppDomainManager));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRControl::SetAppDomainManagerType", sizeof(u8"ICLRControl::SetAppDomainManagerType") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateHostControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		_clrhostcontext.GetHostControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset(new CLRHostControl(ReferenceCountedObjectHolder<ICLRHostContext>(&_clrhostcontext, ReferenceCountedObjectHolder<ICLRHostContext>::inc_ref_count)));
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetHostControl(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->SetHostControl(_clrhostcontext.GetHostControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext).get());
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::SetHostControl", sizeof(u8"ICLRRuntimeHost::SetHostControl") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_StartRuntimeHost(IException*& _err, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->Start();
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::Start", sizeof(u8"ICLRRuntimeHost::Start") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_StopRuntimeHost(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext)->Stop();
		if (!SUCCEEDED(hr)) abort();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseHostControl(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		_clrhostcontext.GetHostControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseCLRControl(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		_clrhostcontext.GetCLRControlCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseRuntimeInterfaces(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		_clrhostcontext.GetCLRStrongNameCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
		_clrhostcontext.GetCLRRuntimeHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
		_clrhostcontext.GetMetaDataDispenserExCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseRuntimeInfo(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		_clrhostcontext.GetCLRRuntimeInfoCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_ReleaseMetaHost(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		_clrhostcontext.GetCLRMetaHostPolicyCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
		_clrhostcontext.GetCLRMetaHostCOMObjectHolder(_already_exclusive_locked_clrhostcontext).reset();
	}

	static void YBWLIB2_CALLTYPE CLRHostStop_CLRHost_COMUnInit(ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext) noexcept {
		static_cast<void>(_clrhostcontext);
		static_cast<void>(_already_exclusive_locked_clrhostcontext);
		CoUninitialize();
	}

	static void YBWLIB2_CALLTYPE CLRHostGetHostManager_CLRHost(HRESULT& _hr, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext, const IID& _iid, void*& _hostmanager_ret) noexcept {
		if (FAILED(_hr) && _hr != E_NOINTERFACE) return;
		IndexedDataStore& indexeddatastore_clrhostcontext = _clrhostcontext.GetIndexedDataStore(_already_exclusive_locked_clrhostcontext);
		IndexedDataRawValue* indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost = indexeddatastore_clrhostcontext.GetRawValueByEntryID(entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost);
		if (!indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost) {
			indexeddatastore_clrhostcontext.AddEntry(
				entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost,
				IndexedDataRawValue(
					[](IndexedDataRawValue* _indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost) noexcept->void {
						if (_indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost) {
							CLRHostManager_CLRHost* ptr_clrhostmanager_clrhost = reinterpret_cast<CLRHostManager_CLRHost*>(_indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost->contextvalue);
							if (ptr_clrhostmanager_clrhost) {
								ReferenceCountedObjectHolder<CLRHostManager_CLRHost>(::std::move(ptr_clrhostmanager_clrhost)).reset();
								ptr_clrhostmanager_clrhost = nullptr;
							}
						}
					},
					reinterpret_cast<uintptr_t>(ReferenceCountedObjectHolder<CLRHostManager_CLRHost>(new CLRHostManager_CLRHost(ReferenceCountedObjectHolder<ICLRHostContext>(&_clrhostcontext, ReferenceCountedObjectHolder<ICLRHostContext>::inc_ref_count))).release())
				)
			);
			indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost = indexeddatastore_clrhostcontext.GetRawValueByEntryID(entryid_indexeddatastore_clrhostcontext_CLRHostManager_CLRHost);
		}
		assert(indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost);
		assert(reinterpret_cast<CLRHostManager_CLRHost*>(indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost->contextvalue));
		ReferenceCountedObjectHolder<CLRHostManager_CLRHost> clrhostmanager_clrhost(reinterpret_cast<CLRHostManager_CLRHost*>(indexeddatarawvalue_clrhostcontext_CLRHostManager_CLRHost->contextvalue), ReferenceCountedObjectHolder<CLRHostManager_CLRHost>::inc_ref_count);
		assert(clrhostmanager_clrhost);
		if (_hr == E_NOINTERFACE) {
			_hr = clrhostmanager_clrhost->QueryInterface(_iid, &_hostmanager_ret);
		} else {
			assert(SUCCEEDED(_hr));
			// TODO: Implement CLRHostGetHostManager_CLRHost.
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostSetAppDomainManager_CLRHost_SaveAppDomainManagerGCHandle(HRESULT& _hr, ICLRHostContext& _clrhostcontext, already_exclusive_locked_this_t _already_exclusive_locked_clrhostcontext, DWORD _appdomainid, const COMObjectHolder<IUnknown>& _comobjholder_IUnknown_appdomainmanager, const dotNETMixed::SharedGCHandle& _sharedgchandle_appdomainmanager) noexcept {
		if (FAILED(_hr)) return;
		static_cast<void>(_comobjholder_IUnknown_appdomainmanager);
		_clrhostcontext.GetAppDomainManagerSharedGCHandle(_appdomainid, true, _already_exclusive_locked_clrhostcontext) = dotNETMixed::SharedGCHandle(dotNETMixed::GCHandle(_sharedgchandle_appdomainmanager, dotNETMixed::GCHandleType::Weak));
	}
}
