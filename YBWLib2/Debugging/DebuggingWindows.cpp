#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../Windows.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"
#include "DebuggingWindows.h"

namespace YBWLib2 {
	static size_t size_page = 0;

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IUnsupportedTargetWin32ArchitectureException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IWin32DebuggingTargetMemoryRegionInfo, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IWin32DebuggingTargetExecutableModuleInfo, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IWin32DebuggingTargetExportSymbolInfo, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IWin32DebuggingProcess, YBWLIB2_API);

	YBWLIB2_API HMODULE hmod_kernel32 = NULL;
	YBWLIB2_API BOOL(WINAPI* fnptr_IsWow64Process)(_In_ HANDLE hProcess, _Out_ PBOOL Wow64Process) = nullptr;
	YBWLIB2_API BOOL(WINAPI* fnptr_IsWow64Process2)(_In_ HANDLE hProcess, _Out_ USHORT* pProcessMachine, _Out_opt_ USHORT* pNativeMachine) = nullptr;
	YBWLIB2_API rawallocator_t* rawallocator_virtual_Win32 = nullptr;

	YBWLIB2_API IStringTemplate* UnsupportedTargetWin32ArchitectureException::strtmpl_description = nullptr;

	void YBWLIB2_CALLTYPE DebuggingWindows_RealInitGlobal() noexcept {
		{
			SYSTEM_INFO systeminfo;
			memset(&systeminfo, 0, sizeof(SYSTEM_INFO));
			GetSystemInfo(&systeminfo);
			size_page = systeminfo.dwPageSize;
		}
		hmod_kernel32 = LoadLibraryW(L"kernel32");
		if (!hmod_kernel32) abort();
		fnptr_IsWow64Process = reinterpret_cast<
			BOOL(WINAPI*)(_In_ HANDLE hProcess, _Out_ PBOOL Wow64Process)
		>(GetProcAddress(hmod_kernel32, "fnptr_IsWow64Process"));
		fnptr_IsWow64Process2 = reinterpret_cast<
			BOOL(WINAPI*)(_In_ HANDLE hProcess, _Out_ USHORT* pProcessMachine, _Out_opt_ USHORT* pNativeMachine)
		>(GetProcAddress(hmod_kernel32, "fnptr_IsWow64Process2"));
		rawallocator_virtual_Win32 = new rawallocator_t(
			nullptr, nullptr, nullptr,
			[](size_t size, size_t align, uintptr_t context) noexcept->void* {
				static_cast<void>(context);
				if (mod_alignment(size_page, align)) abort();
				if (!size) size = align;
				void* ptr = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				if (!ptr) return nullptr;
				if (mod_alignment(reinterpret_cast<uintptr_t>(ptr), align)) abort();
				return ptr;
			},
			[](void* ptr, size_t size, uintptr_t context) noexcept->void {
				static_cast<void>(size);
				static_cast<void>(context);
				if (ptr) {
					if (!VirtualFree(ptr, 0, MEM_RELEASE)) abort();
				}
			},
			nullptr,
			[](uintptr_t context) noexcept->size_t {
				static_cast<void>(context);
				return SIZE_MAX;
			});
		IUnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IUnsupportedTargetWin32ArchitectureException>(),
			IsDynamicTypeModuleLocalClass<IUnsupportedTargetWin32ArchitectureException>(),
			{
				DynamicTypeBaseClassDef<IUnsupportedTargetWin32ArchitectureException, IException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(IUnsupportedTargetWin32ArchitectureException), alignof(IUnsupportedTargetWin32ArchitectureException)
		);
		IWin32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IWin32DebuggingTargetMemoryRegionInfo>(),
			IsDynamicTypeModuleLocalClass<IWin32DebuggingTargetMemoryRegionInfo>(),
			{
				DynamicTypeBaseClassDef<IWin32DebuggingTargetMemoryRegionInfo, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(IWin32DebuggingTargetMemoryRegionInfo), alignof(IWin32DebuggingTargetMemoryRegionInfo)
		);
		IWin32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IWin32DebuggingTargetExecutableModuleInfo>(),
			IsDynamicTypeModuleLocalClass<IWin32DebuggingTargetExecutableModuleInfo>(),
			{
				DynamicTypeBaseClassDef<IWin32DebuggingTargetExecutableModuleInfo, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(IWin32DebuggingTargetExecutableModuleInfo), alignof(IWin32DebuggingTargetExecutableModuleInfo)
		);
		IWin32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IWin32DebuggingTargetExportSymbolInfo>(),
			IsDynamicTypeModuleLocalClass<IWin32DebuggingTargetExportSymbolInfo>(),
			{
				DynamicTypeBaseClassDef<IWin32DebuggingTargetExportSymbolInfo, IDynamicTypeObject, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(IWin32DebuggingTargetExportSymbolInfo), alignof(IWin32DebuggingTargetExportSymbolInfo)
		);
		IWin32DebuggingProcess::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassID<IWin32DebuggingProcess>(),
			IsDynamicTypeModuleLocalClass<IWin32DebuggingProcess>(),
			{
				DynamicTypeBaseClassDef<IWin32DebuggingProcess, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(IWin32DebuggingProcess), alignof(IWin32DebuggingProcess)
		);
	}

	void YBWLIB2_CALLTYPE DebuggingWindows_RealUnInitGlobal() noexcept {
		delete IWin32DebuggingProcess::DynamicTypeThisClassObject;
		IWin32DebuggingProcess::DynamicTypeThisClassObject = nullptr;
		delete IWin32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject;
		IWin32DebuggingTargetExportSymbolInfo::DynamicTypeThisClassObject = nullptr;
		delete IWin32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject;
		IWin32DebuggingTargetExecutableModuleInfo::DynamicTypeThisClassObject = nullptr;
		delete IWin32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject;
		IWin32DebuggingTargetMemoryRegionInfo::DynamicTypeThisClassObject = nullptr;
		delete IUnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject;
		IUnsupportedTargetWin32ArchitectureException::DynamicTypeThisClassObject = nullptr;
		delete rawallocator_virtual_Win32;
		rawallocator_virtual_Win32 = nullptr;
		fnptr_IsWow64Process2 = nullptr;
		fnptr_IsWow64Process = nullptr;
		hmod_kernel32 = NULL;
	}

	void YBWLIB2_CALLTYPE DebuggingWindowsUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_t;
			map_strtmpl_description_t map_strtmpl_description({
				{ GetDynamicTypeClassID<UnsupportedTargetWin32ArchitectureException>(), &UnsupportedTargetWin32ArchitectureException::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_DebuggingWindows = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval(u8"DebuggingWindows"));
			if (jsonmemberit_config_internal_DebuggingWindows == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_DebuggingWindows->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_DebuggingWindows_strtmpl_description = jsonmemberit_config_internal_DebuggingWindows->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"strtmpl_description"));
				if (jsonmemberit_config_internal_DebuggingWindows_strtmpl_description == jsonmemberit_config_internal_DebuggingWindows->value.MemberEnd() || !jsonmemberit_config_internal_DebuggingWindows_strtmpl_description->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_DebuggingWindows_strtmpl_description_element : jsonmemberit_config_internal_DebuggingWindows_strtmpl_description->value.GetArray()) {
						if (!jsonval_config_internal_DebuggingWindows_strtmpl_description_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_object = jsonval_config_internal_DebuggingWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_object"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_strtmpl = jsonval_config_internal_DebuggingWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_jsonval_strtmpl = jsonval_config_internal_DebuggingWindows_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_object == jsonval_config_internal_DebuggingWindows_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_object->value.IsString()
							|| jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_strtmpl == jsonval_config_internal_DebuggingWindows_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_jsonval_strtmpl == jsonval_config_internal_DebuggingWindows_strtmpl_description_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_object = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_object->value.GetString(),
							jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_object->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_t::iterator it_map_strtmpl_description = map_strtmpl_description.find(dtclassid_object);
						if (it_map_strtmpl_description == map_strtmpl_description.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_DebuggingWindows_strtmpl_description_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeClassObject<IStringTemplate>(), indexeddatastore_parameters));
						if (!*it_map_strtmpl_description->second) abort();
						objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
							[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
								return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
							}
						);
						if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
						map_strtmpl_description.erase(it_map_strtmpl_description);
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE DebuggingWindowsUserInterface_RealUnInitGlobal() noexcept {
		delete UnsupportedTargetWin32ArchitectureException::strtmpl_description;
		UnsupportedTargetWin32ArchitectureException::strtmpl_description = nullptr;
	}
}
