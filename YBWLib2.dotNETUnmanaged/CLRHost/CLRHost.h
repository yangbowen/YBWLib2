#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_525993F0_A611_44C7_8FE2_CFB648FFA501
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4269737B_7A7C_44E8_90F2_968004942B3F
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_636CD7BA_45ED_48CE_8203_322A60A360F2
#define _INCLUDE_GUARD_636CD7BA_45ED_48CE_8203_322A60A360F2

#include <cassert>
#include <minwindef.h>
#include <objbase.h>
#include <mscoree.h>
#include <metahost.h>
#include <cor.h>
#include "../../YBWLib2/Common/CommonLowLevel.h"
#include "../../YBWLib2/DynamicType/DynamicType.h"
#include "../../YBWLib2/Exception/Exception.h"
#include "../../YBWLib2/Common/Common.h"
#include "../../YBWLib2/Common/CommonSTLHelper.h"
#include "../../YBWLib2/Common/CommonWindows.h"
#include "../../YBWLib2/Common/CommonSTLHelperWindows.h"
#include "../../YBWLib2/Pipeline/Pipeline.h"
#include "../YBWLib2dotNETUnmanagedApi.h"

namespace YBWLib2 {
	struct CLRRuntimePolicy final {
		METAHOST_POLICY_FLAGS metahostpolicyflags = METAHOST_POLICY_HIGHCOMPAT;
		objholder_rawallocator_t<char16_t[]> holder_u16str_path_assembly;
		COMObjectHolder<IStream> comobjholder_IStream_config;
		objholder_rawallocator_t<char16_t[]> holder_u16str_version;
		objholder_rawallocator_t<char16_t[]> holder_u16str_version_image;
		METAHOST_CONFIG_FLAGS metahostconfigflags = static_cast<METAHOST_CONFIG_FLAGS>(0);
		constexpr CLRRuntimePolicy() noexcept
			: holder_u16str_path_assembly(rawallocator_crt_YBWLib2),
			holder_u16str_version(rawallocator_crt_YBWLib2),
			holder_u16str_version_image(rawallocator_crt_YBWLib2) {}
	};

	class ICLRHostContext : public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ICLRHostContext, YBWLIB2DOTNETUNMANAGED_API, "4775ea09-ca49-4de9-ba4c-5932c3ba8716");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ICLRHostContext);
		inline const CLRRuntimePolicy& GetCLRRuntimePolicy() const noexcept {
			const CLRRuntimePolicy* clrruntimepolicy = nullptr;
			this->GetCLRRuntimePolicy(&clrruntimepolicy);
			assert(clrruntimepolicy);
			return *clrruntimepolicy;
		}
		inline CLRRuntimePolicy& GetCLRRuntimePolicy() noexcept {
			CLRRuntimePolicy* clrruntimepolicy = nullptr;
			this->GetCLRRuntimePolicy(&clrruntimepolicy);
			assert(clrruntimepolicy);
			return *clrruntimepolicy;
		}
		inline const COMObjectHolder<ICLRMetaHost>& GetCLRMetaHostCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRMetaHost>* comobjholder_ICLRMetaHost = nullptr;
			this->GetCLRMetaHostCOMObjectHolder(&comobjholder_ICLRMetaHost);
			assert(comobjholder_ICLRMetaHost);
			return *comobjholder_ICLRMetaHost;
		}
		inline COMObjectHolder<ICLRMetaHost>& GetCLRMetaHostCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRMetaHost>* comobjholder_ICLRMetaHost = nullptr;
			this->GetCLRMetaHostCOMObjectHolder(&comobjholder_ICLRMetaHost);
			assert(comobjholder_ICLRMetaHost);
			return *comobjholder_ICLRMetaHost;
		}
		inline const COMObjectHolder<ICLRMetaHostPolicy>& GetCLRMetaHostPolicyCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRMetaHostPolicy>* comobjholder_ICLRMetaHostPolicy = nullptr;
			this->GetCLRMetaHostPolicyCOMObjectHolder(&comobjholder_ICLRMetaHostPolicy);
			assert(comobjholder_ICLRMetaHostPolicy);
			return *comobjholder_ICLRMetaHostPolicy;
		}
		inline COMObjectHolder<ICLRMetaHostPolicy>& GetCLRMetaHostPolicyCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRMetaHostPolicy>* comobjholder_ICLRMetaHostPolicy = nullptr;
			this->GetCLRMetaHostPolicyCOMObjectHolder(&comobjholder_ICLRMetaHostPolicy);
			assert(comobjholder_ICLRMetaHostPolicy);
			return *comobjholder_ICLRMetaHostPolicy;
		}
		inline const COMObjectHolder<ICLRRuntimeInfo>& GetCLRRuntimeInfoCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRRuntimeInfo>* comobjholder_ICLRRuntimeInfo = nullptr;
			this->GetCLRRuntimeInfoCOMObjectHolder(&comobjholder_ICLRRuntimeInfo);
			assert(comobjholder_ICLRRuntimeInfo);
			return *comobjholder_ICLRRuntimeInfo;
		}
		inline COMObjectHolder<ICLRRuntimeInfo>& GetCLRRuntimeInfoCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRRuntimeInfo>* comobjholder_ICLRRuntimeInfo = nullptr;
			this->GetCLRRuntimeInfoCOMObjectHolder(&comobjholder_ICLRRuntimeInfo);
			assert(comobjholder_ICLRRuntimeInfo);
			return *comobjholder_ICLRRuntimeInfo;
		}
		inline const COMObjectHolder<IMetaDataDispenserEx>& GetMetaDataDispenserExCOMObjectHolder() const noexcept {
			const COMObjectHolder<IMetaDataDispenserEx>* comobjholder_IMetaDataDispenserEx = nullptr;
			this->GetMetaDataDispenserExCOMObjectHolder(&comobjholder_IMetaDataDispenserEx);
			assert(comobjholder_IMetaDataDispenserEx);
			return *comobjholder_IMetaDataDispenserEx;
		}
		inline COMObjectHolder<IMetaDataDispenserEx>& GetMetaDataDispenserExCOMObjectHolder() noexcept {
			COMObjectHolder<IMetaDataDispenserEx>* comobjholder_IMetaDataDispenserEx = nullptr;
			this->GetMetaDataDispenserExCOMObjectHolder(&comobjholder_IMetaDataDispenserEx);
			assert(comobjholder_IMetaDataDispenserEx);
			return *comobjholder_IMetaDataDispenserEx;
		}
		inline const COMObjectHolder<ICLRRuntimeHost>& GetCLRRuntimeHostCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRRuntimeHost>* comobjholder_ICLRRuntimeHost = nullptr;
			this->GetCLRRuntimeHostCOMObjectHolder(&comobjholder_ICLRRuntimeHost);
			assert(comobjholder_ICLRRuntimeHost);
			return *comobjholder_ICLRRuntimeHost;
		}
		inline COMObjectHolder<ICLRRuntimeHost>& GetCLRRuntimeHostCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRRuntimeHost>* comobjholder_ICLRRuntimeHost = nullptr;
			this->GetCLRRuntimeHostCOMObjectHolder(&comobjholder_ICLRRuntimeHost);
			assert(comobjholder_ICLRRuntimeHost);
			return *comobjholder_ICLRRuntimeHost;
		}
		inline const COMObjectHolder<ICLRStrongName>& GetCLRStrongNameCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRStrongName>* comobjholder_ICLRStrongName = nullptr;
			this->GetCLRStrongNameCOMObjectHolder(&comobjholder_ICLRStrongName);
			assert(comobjholder_ICLRStrongName);
			return *comobjholder_ICLRStrongName;
		}
		inline COMObjectHolder<ICLRStrongName>& GetCLRStrongNameCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRStrongName>* comobjholder_ICLRStrongName = nullptr;
			this->GetCLRStrongNameCOMObjectHolder(&comobjholder_ICLRStrongName);
			assert(comobjholder_ICLRStrongName);
			return *comobjholder_ICLRStrongName;
		}
		inline const COMObjectHolder<ICLRControl>& GetCLRControlCOMObjectHolder() const noexcept {
			const COMObjectHolder<ICLRControl>* comobjholder_ICLRControl = nullptr;
			this->GetCLRControlCOMObjectHolder(&comobjholder_ICLRControl);
			assert(comobjholder_ICLRControl);
			return *comobjholder_ICLRControl;
		}
		inline COMObjectHolder<ICLRControl>& GetCLRControlCOMObjectHolder() noexcept {
			COMObjectHolder<ICLRControl>* comobjholder_ICLRControl = nullptr;
			this->GetCLRControlCOMObjectHolder(&comobjholder_ICLRControl);
			assert(comobjholder_ICLRControl);
			return *comobjholder_ICLRControl;
		}
		inline const COMObjectHolder<IHostControl>& GetHostControlCOMObjectHolder() const noexcept {
			const COMObjectHolder<IHostControl>* comobjholder_IHostControl = nullptr;
			this->GetHostControlCOMObjectHolder(&comobjholder_IHostControl);
			assert(comobjholder_IHostControl);
			return *comobjholder_IHostControl;
		}
		inline COMObjectHolder<IHostControl>& GetHostControlCOMObjectHolder() noexcept {
			COMObjectHolder<IHostControl>* comobjholder_IHostControl = nullptr;
			this->GetHostControlCOMObjectHolder(&comobjholder_IHostControl);
			assert(comobjholder_IHostControl);
			return *comobjholder_IHostControl;
		}
	protected:
		virtual void GetCLRRuntimePolicy(const CLRRuntimePolicy** _clrruntimepolicy_ret) const noexcept = 0;
		virtual void GetCLRRuntimePolicy(CLRRuntimePolicy** _clrruntimepolicy_ret) noexcept = 0;
		virtual void GetCLRMetaHostCOMObjectHolder(const COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret) const noexcept = 0;
		virtual void GetCLRMetaHostCOMObjectHolder(COMObjectHolder<ICLRMetaHost>** _comobjholder_ICLRMetaHost_ret) noexcept = 0;
		virtual void GetCLRMetaHostPolicyCOMObjectHolder(const COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret) const noexcept = 0;
		virtual void GetCLRMetaHostPolicyCOMObjectHolder(COMObjectHolder<ICLRMetaHostPolicy>** _comobjholder_ICLRMetaHostPolicy_ret) noexcept = 0;
		virtual void GetCLRRuntimeInfoCOMObjectHolder(const COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret) const noexcept = 0;
		virtual void GetCLRRuntimeInfoCOMObjectHolder(COMObjectHolder<ICLRRuntimeInfo>** _comobjholder_ICLRRuntimeInfo_ret) noexcept = 0;
		virtual void GetMetaDataDispenserExCOMObjectHolder(const COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret) const noexcept = 0;
		virtual void GetMetaDataDispenserExCOMObjectHolder(COMObjectHolder<IMetaDataDispenserEx>** _comobjholder_IMetaDataDispenserEx_ret) noexcept = 0;
		virtual void GetCLRRuntimeHostCOMObjectHolder(const COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret) const noexcept = 0;
		virtual void GetCLRRuntimeHostCOMObjectHolder(COMObjectHolder<ICLRRuntimeHost>** _comobjholder_ICLRRuntimeHost_ret) noexcept = 0;
		virtual void GetCLRStrongNameCOMObjectHolder(const COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret) const noexcept = 0;
		virtual void GetCLRStrongNameCOMObjectHolder(COMObjectHolder<ICLRStrongName>** _comobjholder_ICLRStrongName_ret) noexcept = 0;
		virtual void GetCLRControlCOMObjectHolder(const COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret) const noexcept = 0;
		virtual void GetCLRControlCOMObjectHolder(COMObjectHolder<ICLRControl>** _comobjholder_ICLRControl_ret) noexcept = 0;
		virtual void GetHostControlCOMObjectHolder(const COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret) const noexcept = 0;
		virtual void GetHostControlCOMObjectHolder(COMObjectHolder<IHostControl>** _comobjholder_IHostControl_ret) noexcept = 0;
	};

	using PipelineTraits_CLRHostStart = YBWLib2::PipelineTraits<IException*&, ICLRHostContext&>;
	using PipelineWrapper_CLRHostStart = YBWLib2::PipelineWrapper<PipelineTraits_CLRHostStart>;
	using PipelineFilterWrapper_CLRHostStart = YBWLib2::PipelineFilterWrapper<PipelineTraits_CLRHostStart>;
	static constexpr YBWLib2::PersistentID PersistentID_PipelineID_CLRHostStart = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("74a81fdd-694f-4def-a416-3a91cf7cf8b3"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_COMInit = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("ffd0e56f-ba24-44ac-ae50-7f1df9d2d80a"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateMetaHost = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("a09581f2-0866-4605-9ee0-c3275b7f9148"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_MakeRuntimePolicy = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("07fb97cd-01e3-4906-9cb3-d7134a05477b"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInfo = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("4fb252b1-5cbf-4852-bba4-6c8121bd3dda"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetRuntimeInterfaces = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("fb2ce72e-6195-4b6f-84cf-97e8f5b82663"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_GetCLRControl = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("bda1f4d2-024d-4266-a65b-eff42fe772a4"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetAppDomainManagerType = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("6da5030b-c84f-4238-b529-4ea912e87549"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_CreateHostControl = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("0bb93ea3-84ba-4378-aecc-c577f62f70f5"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_SetHostControl = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("9d21aff8-7103-4ea8-9378-a18317b06ce6"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostStart_CLRHost_StartRuntimeHost = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("c75ff1bb-740f-47d1-b7a2-afc7bfe308cc"));

	using PipelineTraits_CLRHostStop = YBWLib2::PipelineTraits<ICLRHostContext&>;
	using PipelineWrapper_CLRHostStop = YBWLib2::PipelineWrapper<PipelineTraits_CLRHostStop>;
	using PipelineFilterWrapper_CLRHostStop = YBWLib2::PipelineFilterWrapper<PipelineTraits_CLRHostStop>;
	static constexpr YBWLib2::PersistentID PersistentID_PipelineID_CLRHostStop = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("04f5f136-f14f-445e-bcea-f41251e2fd8d"));

	using PipelineTraits_CLRHostGetHostManager = YBWLib2::PipelineTraits<HRESULT&, ICLRHostContext&, IID, void*&>;
	using PipelineWrapper_CLRHostGetHostManager = YBWLib2::PipelineWrapper<PipelineTraits_CLRHostGetHostManager>;
	using PipelineFilterWrapper_CLRHostGetHostManager = YBWLib2::PipelineFilterWrapper<PipelineTraits_CLRHostGetHostManager>;
	static constexpr YBWLib2::PersistentID PersistentID_PipelineID_CLRHostGetHostManager = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("bf1f158d-68e3-4752-902f-1f5cfbd063d7"));
	static constexpr YBWLib2::PersistentID PersistentID_PipelineFilterID_CLRHostGetHostManager_CLRHost = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("fe311422-200a-4615-8707-b02852ce4079"));

	using PipelineTraits_CLRHostSetAppDomainManager = YBWLib2::PipelineTraits<HRESULT&, ICLRHostContext&, DWORD, IUnknown*>;
	using PipelineWrapper_CLRHostSetAppDomainManager = YBWLib2::PipelineWrapper<PipelineTraits_CLRHostSetAppDomainManager>;
	using PipelineFilterWrapper_CLRHostSetAppDomainManager = YBWLib2::PipelineFilterWrapper<PipelineTraits_CLRHostSetAppDomainManager>;
	static constexpr YBWLib2::PersistentID PersistentID_PipelineID_CLRHostSetAppDomainManager = YBWLib2::PersistentID(YBWLib2::UUIDFromUUIDString_CompileTime("3a121a77-5d5c-4ed2-890d-61075fc0fda1"));

	extern YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStart pipelinewrapper_CLRHostStart;
	extern YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostStop pipelinewrapper_CLRHostStop;
	extern YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostGetHostManager pipelinewrapper_CLRHostGetHostManager;
	extern YBWLIB2DOTNETUNMANAGED_API PipelineWrapper_CLRHostSetAppDomainManager pipelinewrapper_CLRHostSetAppDomainManager;

	namespace Internal {
		[[nodiscard]] YBWLIB2DOTNETUNMANAGED_API IException* YBWLIB2DOTNETUNMANAGED_CALLTYPE StartCLRHost(ReferenceCountedObjectHolder<ICLRHostContext>* _clrhostcontext_ret, CLRRuntimePolicy* _clrruntimepolicy) noexcept;
	}

	inline ReferenceCountedObjectHolder<ICLRHostContext> StartCLRHost(CLRRuntimePolicy&& _clrruntimepolicy = CLRRuntimePolicy()) noexcept(false) {
		ReferenceCountedObjectHolder<ICLRHostContext> clrhostcontext;
		IException* err = Internal::StartCLRHost(&clrhostcontext, &_clrruntimepolicy);
		if (err) throw(err);
		return clrhostcontext;
	}

	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealInitGlobal() noexcept;
	void YBWLIB2DOTNETUNMANAGED_CALLTYPE CLRHost_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4269737B_7A7C_44E8_90F2_968004942B3F
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_4269737B_7A7C_44E8_90F2_968004942B3F
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_525993F0_A611_44C7_8FE2_CFB648FFA501
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_525993F0_A611_44C7_8FE2_CFB648FFA501
#endif
