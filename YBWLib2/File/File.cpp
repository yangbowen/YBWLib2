#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "../YBWLib2InternalConfig.h"
#include "../UserInterface/UserInterface.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IFileException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IBofFileException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IEofFileException, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISizedFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISeekableFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IReadableFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IWriteableFile, YBWLIB2_API);

	YBWLIB2_API IStringTemplate* FileException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* BofFileException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* EofFileException::strtmpl_description = nullptr;
	YBWLIB2_API IStringTemplate* MemoryFile::strtmpl_description = nullptr;

	void YBWLIB2_CALLTYPE File_RealInitGlobal() noexcept {
		IFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IFileException>(),
			IsDynamicTypeModuleLocalClass<IFileException>(),
			{ DynamicTypeBaseClassDef<IFileException, IException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IFileException), alignof(IFileException));
		IBofFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IBofFileException>(),
			IsDynamicTypeModuleLocalClass<IBofFileException>(),
			{ DynamicTypeBaseClassDef<IBofFileException, IFileException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IBofFileException), alignof(IBofFileException));
		IEofFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IEofFileException>(),
			IsDynamicTypeModuleLocalClass<IEofFileException>(),
			{ DynamicTypeBaseClassDef<IEofFileException, IFileException, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IEofFileException), alignof(IEofFileException));
		IFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IFile>(),
			IsDynamicTypeModuleLocalClass<IFile>(),
			{ DynamicTypeBaseClassDef<IFile, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IFile), alignof(IFile));
		ISizedFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<ISizedFile>(),
			IsDynamicTypeModuleLocalClass<ISizedFile>(),
			{ DynamicTypeBaseClassDef<ISizedFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISizedFile), alignof(ISizedFile));
		ISeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<ISeekableFile>(),
			IsDynamicTypeModuleLocalClass<ISeekableFile>(),
			{ DynamicTypeBaseClassDef<ISeekableFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISeekableFile), alignof(ISeekableFile));
		IReadableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IReadableFile>(),
			IsDynamicTypeModuleLocalClass<IReadableFile>(),
			{ DynamicTypeBaseClassDef<IReadableFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IReadableFile), alignof(IReadableFile));
		IWriteableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeClassPersistentID<IWriteableFile>(),
			IsDynamicTypeModuleLocalClass<IWriteableFile>(),
			{ DynamicTypeBaseClassDef<IWriteableFile, IFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IWriteableFile), alignof(IWriteableFile));
	}

	void YBWLIB2_CALLTYPE File_RealUnInitGlobal() noexcept {
		delete IWriteableFile::DynamicTypeThisClassObject;
		IWriteableFile::DynamicTypeThisClassObject = nullptr;
		delete IReadableFile::DynamicTypeThisClassObject;
		IReadableFile::DynamicTypeThisClassObject = nullptr;
		delete ISeekableFile::DynamicTypeThisClassObject;
		ISeekableFile::DynamicTypeThisClassObject = nullptr;
		delete ISizedFile::DynamicTypeThisClassObject;
		ISizedFile::DynamicTypeThisClassObject = nullptr;
		delete IFile::DynamicTypeThisClassObject;
		IFile::DynamicTypeThisClassObject = nullptr;
		delete IEofFileException::DynamicTypeThisClassObject;
		IEofFileException::DynamicTypeThisClassObject = nullptr;
		delete IBofFileException::DynamicTypeThisClassObject;
		IBofFileException::DynamicTypeThisClassObject = nullptr;
		delete IFileException::DynamicTypeThisClassObject;
		IFileException::DynamicTypeThisClassObject = nullptr;
	}

	void YBWLIB2_CALLTYPE FileUserInterface_RealInitGlobal() noexcept {
		try {
			typedef ::std::unordered_map<DynamicTypeClassID, IStringTemplate**, hash<DynamicTypeClassID>> map_strtmpl_description_t;
			map_strtmpl_description_t map_strtmpl_description({
				{ GetDynamicTypeClassID<FileException>(), &FileException::strtmpl_description },
				{ GetDynamicTypeClassID<BofFileException>(), &BofFileException::strtmpl_description },
				{ GetDynamicTypeClassID<EofFileException>(), &EofFileException::strtmpl_description },
				{ GetDynamicTypeClassID<MemoryFile>(), &MemoryFile::strtmpl_description }
				});
			Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_File = Internal::jsondoc_config_internal->FindMember(Internal::ConstStringToInternalConfigJsonval(u8"File"));
			if (jsonmemberit_config_internal_File == Internal::jsondoc_config_internal->MemberEnd() || !jsonmemberit_config_internal_File->value.IsObject()) abort();
			{
				Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_File_strtmpl_description = jsonmemberit_config_internal_File->value.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"strtmpl_description"));
				if (jsonmemberit_config_internal_File_strtmpl_description == jsonmemberit_config_internal_File->value.MemberEnd() || !jsonmemberit_config_internal_File_strtmpl_description->value.IsArray()) abort();
				{
					for (const Internal::jsonval_config_internal_t& jsonval_config_internal_File_strtmpl_description_element : jsonmemberit_config_internal_File_strtmpl_description->value.GetArray()) {
						if (!jsonval_config_internal_File_strtmpl_description_element.IsObject()) abort();
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_object = jsonval_config_internal_File_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_object"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_strtmpl = jsonval_config_internal_File_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"dtclassid_strtmpl"));
						Internal::jsonval_config_internal_t::ConstMemberIterator jsonmemberit_config_internal_File_strtmpl_description_element_jsonval_strtmpl = jsonval_config_internal_File_strtmpl_description_element.FindMember(Internal::ConstStringToInternalConfigJsonval(u8"jsonval_strtmpl"));
						if (
							jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_object == jsonval_config_internal_File_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_object->value.IsString()
							|| jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_strtmpl == jsonval_config_internal_File_strtmpl_description_element.MemberEnd()
							|| !jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_strtmpl->value.IsString()
							|| jsonmemberit_config_internal_File_strtmpl_description_element_jsonval_strtmpl == jsonval_config_internal_File_strtmpl_description_element.MemberEnd()
							) abort();
						bool is_successful = true;
						DynamicTypeClassID dtclassid_object = DynamicTypeClassID(PersistentID(UUIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_object->value.GetString(),
							jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_object->value.GetStringLength(),
							is_successful
						)));
						if (!is_successful) abort();
						is_successful = true;
						DynamicTypeClassID dtclassid_strtmpl = DynamicTypeClassID(PersistentID(UUIDFromUUIDString_RunTime(
							jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_strtmpl->value.GetString(),
							jsonmemberit_config_internal_File_strtmpl_description_element_dtclassid_strtmpl->value.GetStringLength(),
							is_successful
						)));
						if (!is_successful) abort();
						map_strtmpl_description_t::iterator it_map_strtmpl_description = map_strtmpl_description.find(dtclassid_object);
						if (it_map_strtmpl_description == map_strtmpl_description.end()) continue;
						DynamicTypeClassObj* dtclassobj_strtmpl = DynamicTypeClassObj::FindDynamicTypeClassObjectModuleLocal(&dtclassid_strtmpl);
						if (!dtclassobj_strtmpl) abort();
						IndexedDataStore indexeddatastore_parameters(rawallocator_crt_YBWLib2);
						ConstructorIDParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, ConstructorIDParameterIndexedDataEntry(ConstructorID_StringTemplateFromJSONSAXGenerator));
						RawAllocatorParameterIndexedDataEntry::AddToStore(indexeddatastore_parameters, RawAllocatorParameterIndexedDataEntry(rawallocator_crt_YBWLib2));
						ValueJSONSAXGeneratorWrapper<const Internal::jsonval_config_internal_t> jsonsaxgeneratorwrapper(jsonmemberit_config_internal_File_strtmpl_description_element_jsonval_strtmpl->value);
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

	void YBWLIB2_CALLTYPE FileUserInterface_RealUnInitGlobal() noexcept {
		delete MemoryFile::strtmpl_description;
		MemoryFile::strtmpl_description = nullptr;
		delete EofFileException::strtmpl_description;
		EofFileException::strtmpl_description = nullptr;
		delete BofFileException::strtmpl_description;
		BofFileException::strtmpl_description = nullptr;
		delete FileException::strtmpl_description;
		FileException::strtmpl_description = nullptr;
	}
}
