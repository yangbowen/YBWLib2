#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IFileException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IBofFileException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IFileWithSize, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISeekableFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInputFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IOutputFile, YBWLIB2_API);

	YBWLIB2_API IStringTemplate* FileException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* BofFileException::strtmpl_description = nullptr;

	void YBWLIB2_CALLTYPE File_RealInitGlobal() noexcept {
		IFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IFileException>(),
			IsDynamicTypeModuleLocalClass<IFileException>(),
			{ DynamicTypeBaseClassDef<IFileException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IFileException), alignof(IFileException));
		IBofFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IBofFileException>(),
			IsDynamicTypeModuleLocalClass<IBofFileException>(),
			{ DynamicTypeBaseClassDef<IBofFileException, IFileException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IBofFileException), alignof(IBofFileException));
		IFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IFile>(),
			IsDynamicTypeModuleLocalClass<IFile>(),
			{ DynamicTypeBaseClassDef<IFile, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IFile), alignof(IFile));
		IFileWithSize::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IFileWithSize>(),
			IsDynamicTypeModuleLocalClass<IFileWithSize>(),
			{ DynamicTypeBaseClassDef<IFileWithSize, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IFileWithSize), alignof(IFileWithSize));
		ISeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ISeekableFile>(),
			IsDynamicTypeModuleLocalClass<ISeekableFile>(),
			{ DynamicTypeBaseClassDef<ISeekableFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISeekableFile), alignof(ISeekableFile));
		IInputFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInputFile>(),
			IsDynamicTypeModuleLocalClass<IInputFile>(),
			{ DynamicTypeBaseClassDef<IInputFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInputFile), alignof(IInputFile));
		IOutputFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IOutputFile>(),
			IsDynamicTypeModuleLocalClass<IOutputFile>(),
			{ DynamicTypeBaseClassDef<IOutputFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IOutputFile), alignof(IOutputFile));
	}

	void YBWLIB2_CALLTYPE File_RealUnInitGlobal() noexcept {
		delete IOutputFile::DynamicTypeThisClassObject;
		IOutputFile::DynamicTypeThisClassObject = nullptr;
		delete IInputFile::DynamicTypeThisClassObject;
		IInputFile::DynamicTypeThisClassObject = nullptr;
		delete ISeekableFile::DynamicTypeThisClassObject;
		ISeekableFile::DynamicTypeThisClassObject = nullptr;
		delete IFileWithSize::DynamicTypeThisClassObject;
		IFileWithSize::DynamicTypeThisClassObject = nullptr;
		delete IFile::DynamicTypeThisClassObject;
		IFile::DynamicTypeThisClassObject = nullptr;
		delete IBofFileException::DynamicTypeThisClassObject;
		IBofFileException::DynamicTypeThisClassObject = nullptr;
		delete IFileException::DynamicTypeThisClassObject;
		IFileException::DynamicTypeThisClassObject = nullptr;
	}

	void YBWLIB2_CALLTYPE FileUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash_DynamicTypeClassID_t> map_strtmpl_description_exception_t;
			map_strtmpl_description_exception_t map_strtmpl_description_exception({
				{ GetDynamicTypeThisClassID<FileException>(), &FileException::strtmpl_description },
				{ GetDynamicTypeThisClassID<BofFileException>(), &BofFileException::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval("JSON"));
			if (jsonmemberit_config_internal_JSON == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_JSON->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_exception = jsonmemberit_config_internal_JSON->value.FindMember(Internal::ConstStringToInternalConfigJsonval("strtmpl_description_exception"));
				if (jsonmemberit_config_internal_JSON_strtmpl_description_exception == jsonmemberit_config_internal_JSON->value.MemberEnd() || !jsonmemberit_config_internal_JSON_strtmpl_description_exception->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_JSON_strtmpl_description_exception_element : jsonmemberit_config_internal_JSON_strtmpl_description_exception->value.GetArray()) {
						if (!jsonval_config_internal_JSON_strtmpl_description_exception_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_exception = jsonval_config_internal_JSON_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_exception"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_strtmpl = jsonval_config_internal_JSON_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_jsonval_strtmpl = jsonval_config_internal_JSON_strtmpl_description_exception_element.FindMember(Internal::ConstStringToInternalConfigJsonval("jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_exception == jsonval_config_internal_JSON_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_exception->value.IsString()
							|| jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_strtmpl == jsonval_config_internal_JSON_strtmpl_description_exception_element.MemberEnd()
							|| !jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_jsonval_strtmpl == jsonval_config_internal_JSON_strtmpl_description_exception_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_exception = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_exception->value.GetString(),
							jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_exception->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						);
						if (!is_successful) abort();
						map_strtmpl_description_exception_t::iterator it_map_strtmpl_description_exception = map_strtmpl_description_exception.find(dtclassid_exception);
						if (it_map_strtmpl_description_exception == map_strtmpl_description_exception.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_JSON_strtmpl_description_exception_element_jsonval_strtmpl->value);
						JSONSAXGeneratorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, JSONSAXGeneratorParameterIndexedDataEntry(&jsonsaxgeneratorwrapper));
						*it_map_strtmpl_description_exception->second = reinterpret_cast<IStringTemplate*>(dtclassobj_strtmpl->CreateObject(GetDynamicTypeThisClassObject<IStringTemplate>(), indexeddatastore_parameters));
						if (!*it_map_strtmpl_description_exception->second) abort();
						objholder_local_t<ExceptionReturnParameterIndexedDataEntry> objholder_indexeddataentry_parameter_exception_return(
							[&indexeddatastore_parameters](void* ptr_placement) noexcept->ExceptionReturnParameterIndexedDataEntry* {
								return ExceptionReturnParameterIndexedDataEntry::MoveFromStore(indexeddatastore_parameters, ptr_placement);
							}
						);
						if (objholder_indexeddataentry_parameter_exception_return && objholder_indexeddataentry_parameter_exception_return->exception) abort();
						map_strtmpl_description_exception.erase(it_map_strtmpl_description_exception);
					}
				}
			}
		} catch (...) {
			abort();
		}
	}

	void YBWLIB2_CALLTYPE FileUserInterface_RealUnInitGlobal() noexcept {
		delete BofFileException::strtmpl_description;
		BofFileException::strtmpl_description = nullptr;
		delete FileException::strtmpl_description;
		FileException::strtmpl_description = nullptr;
	}
}
