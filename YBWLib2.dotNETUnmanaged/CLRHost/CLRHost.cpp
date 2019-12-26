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

namespace YBWLib2 {
	class CLRHostContext final
		: public virtual ReferenceCountedObject,
		public ICLRHostContext,
		public RawAllocatorAllocatedClass<&rawallocator_crt_YBWLib2> {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(CLRHostContext, , "5a36444a-7218-453b-bea1-6d4a56fd6d47");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(CLRHostContext);
		CLRHostContext() noexcept = default;
		virtual ~CLRHostContext() {
			pipelinewrapper_CLRHostStop(*this);
		}
	protected:
		CLRRuntimePolicy clrruntimepolicy;
		COMObjectHolder<ICLRMetaHost> comobjholder_ICLRMetaHost;
		COMObjectHolder<ICLRMetaHostPolicy> comobjholder_ICLRMetaHostPolicy;
		COMObjectHolder<ICLRRuntimeInfo> comobjholder_ICLRRuntimeInfo;
		COMObjectHolder<IMetaDataDispenserEx> comobjholder_IMetaDataDispenserEx;
		COMObjectHolder<ICLRRuntimeHost> comobjholder_ICLRRuntimeHost;
		COMObjectHolder<ICLRStrongName> comobjholder_ICLRStrongName;
		COMObjectHolder<ICLRControl> comobjholder_ICLRControl;
		COMObjectHolder<IHostControl> comobjholder_IHostControl;
		inline virtual void DeleteMe() noexcept override {
			delete this;
		}
		inline virtual void GetCLRRuntimePolicy(const CLRRuntimePolicy** _clrruntimepolicy_ret) const noexcept override {
			assert(_clrruntimepolicy_ret);
			*_clrruntimepolicy_ret = &this->clrruntimepolicy;
		}
		inline virtual void GetCLRRuntimePolicy(CLRRuntimePolicy** _clrruntimepolicy_ret) noexcept override {
			assert(_clrruntimepolicy_ret);
			*_clrruntimepolicy_ret = &this->clrruntimepolicy;
		}
		inline virtual void GetCLRMetaHostCOMObjectHolder(const COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret) const noexcept override {
			assert(_comobjholder_ICLRMetaHost_ret);
			*_comobjholder_ICLRMetaHost_ret = &this->comobjholder_ICLRMetaHost;
		}
		inline virtual void GetCLRMetaHostCOMObjectHolder(COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret) noexcept override {
			assert(_comobjholder_ICLRMetaHost_ret);
			*_comobjholder_ICLRMetaHost_ret = &this->comobjholder_ICLRMetaHost;
		}
		inline virtual void GetCLRMetaHostPolicyCOMObjectHolder(const COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret) const noexcept override {
			assert(_comobjholder_ICLRMetaHostPolicy_ret);
			*_comobjholder_ICLRMetaHostPolicy_ret = &this->comobjholder_ICLRMetaHostPolicy;
		}
		inline virtual void GetCLRMetaHostPolicyCOMObjectHolder(COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret) noexcept override {
			assert(_comobjholder_ICLRMetaHostPolicy_ret);
			*_comobjholder_ICLRMetaHostPolicy_ret = &this->comobjholder_ICLRMetaHostPolicy;
		}
		inline virtual void GetCLRRuntimeInfoCOMObjectHolder(const COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret) const noexcept override {
			assert(_comobjholder_ICLRRuntimeInfo_ret);
			*_comobjholder_ICLRRuntimeInfo_ret = &this->comobjholder_ICLRRuntimeInfo;
		}
		inline virtual void GetCLRRuntimeInfoCOMObjectHolder(COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret) noexcept override {
			assert(_comobjholder_ICLRRuntimeInfo_ret);
			*_comobjholder_ICLRRuntimeInfo_ret = &this->comobjholder_ICLRRuntimeInfo;
		}
		inline virtual void GetMetaDataDispenserExCOMObjectHolder(const COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret) const noexcept override {
			assert(_comobjholder_IMetaDataDispenserEx_ret);
			*_comobjholder_IMetaDataDispenserEx_ret = &this->comobjholder_IMetaDataDispenserEx;
		}
		inline virtual void GetMetaDataDispenserExCOMObjectHolder(COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret) noexcept override {
			assert(_comobjholder_IMetaDataDispenserEx_ret);
			*_comobjholder_IMetaDataDispenserEx_ret = &this->comobjholder_IMetaDataDispenserEx;
		}
		inline virtual void GetCLRRuntimeHostCOMObjectHolder(const COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret) const noexcept override {
			assert(_comobjholder_ICLRRuntimeHost_ret);
			*_comobjholder_ICLRRuntimeHost_ret = &this->comobjholder_ICLRRuntimeHost;
		}
		inline virtual void GetCLRRuntimeHostCOMObjectHolder(COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret) noexcept override {
			assert(_comobjholder_ICLRRuntimeHost_ret);
			*_comobjholder_ICLRRuntimeHost_ret = &this->comobjholder_ICLRRuntimeHost;
		}
		inline virtual void GetCLRStrongNameCOMObjectHolder(const COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret) const noexcept override {
			assert(_comobjholder_ICLRStrongName_ret);
			*_comobjholder_ICLRStrongName_ret = &this->comobjholder_ICLRStrongName;
		}
		inline virtual void GetCLRStrongNameCOMObjectHolder(COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret) noexcept override {
			assert(_comobjholder_ICLRStrongName_ret);
			*_comobjholder_ICLRStrongName_ret = &this->comobjholder_ICLRStrongName;
		}
		inline virtual void GetCLRControlCOMObjectHolder(const COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret) const noexcept override {
			assert(_comobjholder_ICLRControl_ret);
			*_comobjholder_ICLRControl_ret = &this->comobjholder_ICLRControl;
		}
		inline virtual void GetCLRControlCOMObjectHolder(COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret) noexcept override {
			assert(_comobjholder_ICLRControl_ret);
			*_comobjholder_ICLRControl_ret = &this->comobjholder_ICLRControl;
		}
		inline virtual void GetHostControlCOMObjectHolder(const COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret) const noexcept override {
			assert(_comobjholder_IHostControl_ret);
			*_comobjholder_IHostControl_ret = &this->comobjholder_IHostControl;
		}
		inline virtual void GetHostControlCOMObjectHolder(COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret) noexcept override {
			assert(_comobjholder_IHostControl_ret);
			*_comobjholder_IHostControl_ret = &this->comobjholder_IHostControl;
		}
	};

	YBWLIB2DOTNETUNMANAGED_API DynamicTypeClassObj* ICLRHostContext::DynamicTypeThisClassObject = nullptr;
	DynamicTypeClassObj* CLRHostContext::DynamicTypeThisClassObject = nullptr;

	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStart pipelinewrapper_CLRHostStart;
	YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStop pipelinewrapper_CLRHostStop;

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_COMInit(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateMetaHost(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_MakeRuntimePolicy(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInfo(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInterfaces(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetCLRControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetAppDomainManagerType(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateHostControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetHostControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;
	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_StartRuntimeHost(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept;

	namespace Internal {
		[[nodiscard]] YBWLIB2DOTNETUNMANAGED_API IException* YBWLIB2DOTNETUNMANAGED_CALLTYPE StartCLRHost(ReferenceCountedObjectHolder<ICLRHostContext>* _clrhostcontext_ret, CLRRuntimePolicy* _clrruntimepolicy) noexcept {
			IException* err = nullptr;
			ReferenceCountedObjectHolder<CLRHostContext> clrhostcontext(new CLRHostContext());
			if (_clrruntimepolicy) clrhostcontext->ICLRHostContext::GetCLRRuntimePolicy() = *_clrruntimepolicy;
			pipelinewrapper_CLRHostStart(err, *clrhostcontext);
			if (_clrhostcontext_ret) *_clrhostcontext_ret = clrhostcontext;
			return err;
		}
	}

	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealInitGlobal() noexcept {
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
					DynamicTypeBaseClassDef<CLRHostContext, ReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase>,
					DynamicTypeBaseClassDef<CLRHostContext, ICLRHostContext, 0>
				},
				0, sizeof(CLRHostContext), alignof(CLRHostContext)
			);
		}
		{
			pipelinewrapper_CLRHostStart = PipelineWrapper_CLRHostStart(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostStart);
			pipelinewrapper_CLRHostStop = PipelineWrapper_CLRHostStop(GetGlobalPipelineStore(), PersistentID_PipelineID_CLRHostStop);
		}
		{
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_COMInit);
			pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_COMInit));
			pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.SetPipelineFilterPositionArray(PipelineFilterPosition_Back);
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateMetaHost);
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_CreateMetaHost));
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_COMInit.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_MakeRuntimePolicy);
			pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_MakeRuntimePolicy));
			pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_CreateMetaHost.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInfo);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_GetRuntimeInfo));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_MakeRuntimePolicy.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInterfaces);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_GetRuntimeInterfaces));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInfo.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetCLRControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_GetCLRControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetRuntimeInterfaces.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetAppDomainManagerType);
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_SetAppDomainManagerType));
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_GetCLRControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateHostControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_CreateHostControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_SetAppDomainManagerType.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetHostControl);
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_SetHostControl));
			pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_CreateHostControl.GetPipelineFilterID()));
			PipelineFilterWrapper_CLRHostStart pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost(PersistentID_PipelineFilterID_CLRHostStart_CLRHost_StartRuntimeHost);
			pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost.SetInvokeDelegate(Delegate<DelegateFlag_Noexcept, void, IException*&, ICLRHostContext&>(&CLRHostStart_CLRHost_StartRuntimeHost));
			pipelinefilterwrapper_CLRHostStart_CLRHost_StartRuntimeHost.SetPipelineFilterPositionArray(PipelineFilterPosition(PipelineFilterPositionType::PipelineFilterPositionType_AfterRef, pipelinefilterwrapper_CLRHostStart_CLRHost_SetHostControl.GetPipelineFilterID()));
			{
				PipelineSharedMutexWrapper pipelinesharedmutexwrapper(pipelinewrapper_CLRHostStart.GetPipelineSharedMutexWrapper());
				::std::unique_lock<PipelineSharedMutexWrapper> unique_lock_pipeline(pipelinesharedmutexwrapper); already_exclusive_locked_this_t already_exclusive_locked_pipeline;
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
	}

	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealUnInitGlobal() noexcept {
		{
			pipelinewrapper_CLRHostStop = PipelineWrapper_CLRHostStop();
			pipelinewrapper_CLRHostStart = PipelineWrapper_CLRHostStart();
		}
		{
			delete CLRHostContext::DynamicTypeThisClassObject;
			CLRHostContext::DynamicTypeThisClassObject;
			delete ICLRHostContext::DynamicTypeThisClassObject;
			ICLRHostContext::DynamicTypeThisClassObject;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_COMInit(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		static_cast<void>(_clrhostcontext);
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CoInitializeEx, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateMetaHost(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&_clrhostcontext.GetCLRMetaHostCOMObjectHolder().get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CLRCreateInstance, hr);
			return;
		}
		hr = CLRCreateInstance(CLSID_CLRMetaHostPolicy, IID_PPV_ARGS(&_clrhostcontext.GetCLRMetaHostPolicyCOMObjectHolder().get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(CLRCreateInstance, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_MakeRuntimePolicy(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		CLRRuntimePolicy& clrruntimepolicy = _clrhostcontext.GetCLRRuntimePolicy();
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
			HRESULT hr = _clrhostcontext.GetCLRMetaHostCOMObjectHolder()->GetVersionFromFile(
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

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInfo(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		CLRRuntimePolicy& clrruntimepolicy = _clrhostcontext.GetCLRRuntimePolicy();
		static_assert(sizeof(DWORD) == sizeof(METAHOST_CONFIG_FLAGS));
		static_assert(sizeof(wchar_t) == sizeof(char16_t));
		assert(clrruntimepolicy.holder_u16str_version.get_count() <= MAXDWORD);
		DWORD dword_cch_u16str_version = clrruntimepolicy.holder_u16str_version.get_count() & ~(DWORD)0;
		assert(clrruntimepolicy.holder_u16str_version_image.get_count() <= MAXDWORD);
		DWORD dword_cch_u16str_version_image = clrruntimepolicy.holder_u16str_version_image.get_count() & ~(DWORD)0;
		HRESULT hr = _clrhostcontext.GetCLRMetaHostPolicyCOMObjectHolder()->GetRequestedRuntime(
			clrruntimepolicy.metahostpolicyflags,
			reinterpret_cast<const wchar_t*>(clrruntimepolicy.holder_u16str_path_assembly.get()),
			clrruntimepolicy.comobjholder_IStream_config.get(),// TODO: Should the reference count be incremented for the argument?
			reinterpret_cast<wchar_t*>(clrruntimepolicy.holder_u16str_version.get()),
			&dword_cch_u16str_version,
			reinterpret_cast<wchar_t*>(clrruntimepolicy.holder_u16str_version_image.get()),
			&dword_cch_u16str_version_image,
			reinterpret_cast<DWORD*>(&clrruntimepolicy.metahostconfigflags),
			IID_PPV_ARGS(&_clrhostcontext.GetCLRRuntimeInfoCOMObjectHolder().get_ref_ptr_element())
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

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetRuntimeInterfaces(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		COMObjectHolder<ICLRRuntimeInfo>& comobjholder_ICLRRuntimeInfo = _clrhostcontext.GetCLRRuntimeInfoCOMObjectHolder();
		HRESULT hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CorMetaDataDispenser, IID_IMetaDataDispenserEx, reinterpret_cast<void**>(&_clrhostcontext.GetMetaDataDispenserExCOMObjectHolder().get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
		hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&_clrhostcontext.GetCLRRuntimeHostCOMObjectHolder().get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
		hr = comobjholder_ICLRRuntimeInfo->GetInterface(CLSID_CLRStrongName, IID_PPV_ARGS(&_clrhostcontext.GetCLRStrongNameCOMObjectHolder().get_ref_ptr_element()));
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeInfo::GetInterface", sizeof(u8"ICLRRuntimeInfo::GetInterface") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_GetCLRControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder()->GetCLRControl(&_clrhostcontext.GetCLRControlCOMObjectHolder().get_ref_ptr_element());
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::GetCLRControl", sizeof(u8"ICLRRuntimeHost::GetCLRControl") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetAppDomainManagerType(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRControlCOMObjectHolder()->SetAppDomainManagerType(, );// TODO: Set AppDomainManager Type.
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRControl::SetAppDomainManagerType", sizeof(u8"ICLRControl::SetAppDomainManagerType") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_CreateHostControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		// TODO: Create host control.
		_clrhostcontext.GetHostControlCOMObjectHolder().reset(new HostControl());
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_SetHostControl(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		// TODO: Should the reference count be incremented for the argument?
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder()->SetHostControl(_clrhostcontext.GetHostControlCOMObjectHolder().get());
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::SetHostControl", sizeof(u8"ICLRRuntimeHost::SetHostControl") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}

	static void YBWLIB2_CALLTYPE CLRHostStart_CLRHost_StartRuntimeHost(IException*& _err, ICLRHostContext& _clrhostcontext) noexcept {
		if (_err) return;
		HRESULT hr = _clrhostcontext.GetCLRRuntimeHostCOMObjectHolder()->Start();
		if (!SUCCEEDED(hr)) {
			_err = new ExternalAPIFailureWithHRESULTException(u8"ICLRRuntimeHost::Start", sizeof(u8"ICLRRuntimeHost::Start") / sizeof(char) - 1, nullptr, hr);
			return;
		}
	}
}
