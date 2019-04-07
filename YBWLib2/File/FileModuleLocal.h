#ifndef _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E
#define _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "../UserInterface/UserInterface.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(FileException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(BofFileException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(EofFileException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(File, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizedFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SeekableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ReadableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(WriteableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizetSizedFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizetSeekableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ULongLongSizedFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ULongLongSeekableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(MemoryFile, );

	[[nodiscard]] IException* FileException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				const IFile* file = this->GetFile();
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_file;
				objholder_strtmplparameter_address_file.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_file", reinterpret_cast<uintptr_t>(file));
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_description_file;
				{
					objholder_rawallocator_t<char[]> holder_str_description_file(rawallocator_exception);
					if (file) {
						IException* err_cause_inner = file->GetDescription(rawallocator_exception, &holder_str_description_file.get_ref_ptr_array_element_element_as_mem(), &holder_str_description_file.get_ref_count_element_element_as_mem(), false);
						err_inner = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_inner->AttachCause(err_cause_inner);
						return;
					}
					if (holder_str_description_file.get() && holder_str_description_file.get_count()) {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", holder_str_description_file.get(), holder_str_description_file.get_count());
					} else {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
					}
				}
				err_inner = FileException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_address_file.get(),
						objholder_strtmplparameter_description_file.get()
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}

	[[nodiscard]] IException* BofFileException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				const IFile* file = this->GetFile();
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_file;
				objholder_strtmplparameter_address_file.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_file", reinterpret_cast<uintptr_t>(file));
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_description_file;
				{
					objholder_rawallocator_t<char[]> holder_str_description_file(rawallocator_exception);
					if (file) {
						IException* err_cause_inner = file->GetDescription(rawallocator_exception, &holder_str_description_file.get_ref_ptr_array_element_element_as_mem(), &holder_str_description_file.get_ref_count_element_element_as_mem(), false);
						err_inner = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_inner->AttachCause(err_cause_inner);
						return;
					}
					if (holder_str_description_file.get() && holder_str_description_file.get_count()) {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", holder_str_description_file.get(), holder_str_description_file.get_count());
					} else {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
					}
				}
				err_inner = BofFileException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_address_file.get(),
						objholder_strtmplparameter_description_file.get()
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}

	[[nodiscard]] IException* EofFileException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				const IFile* file = this->GetFile();
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_file;
				objholder_strtmplparameter_address_file.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_file", reinterpret_cast<uintptr_t>(file));
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_description_file;
				{
					objholder_rawallocator_t<char[]> holder_str_description_file(rawallocator_exception);
					if (file) {
						IException* err_cause_inner = file->GetDescription(rawallocator_exception, &holder_str_description_file.get_ref_ptr_array_element_element_as_mem(), &holder_str_description_file.get_ref_count_element_element_as_mem(), false);
						err_inner = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_inner->AttachCause(err_cause_inner);
						return;
					}
					if (holder_str_description_file.get() && holder_str_description_file.get_count()) {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", holder_str_description_file.get(), holder_str_description_file.get_count());
					} else {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
					}
				}
				err_inner = EofFileException::strtmpl_description->GenerateString(StringTemplateParameterList(rawallocator_exception,
					{
						objholder_strtmplparameter_address_file.get(),
						objholder_strtmplparameter_description_file.get()
					}
				), description_ret, size_description_ret, false, rawallocator_exception);
				if (err_inner && description_ret && *description_ret) { ExceptionFreeMemory(*description_ret); *description_ret = nullptr; *size_description_ret = 0; }
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err;
		}
		if (err_inner) {
			if (is_successful_ret) *is_successful_ret = false;
			delete this;
			return err_inner;
		}
		if (is_successful_ret) *is_successful_ret = true;
		return this;
	}

	[[nodiscard]] IException* MemoryFile::GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) const noexcept {
		if (!_rawallocator || !description_ret || !size_description_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, GetDescription);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_rawallocator, &description_ret, &size_description_ret, &should_null_terminate, &err_inner]() noexcept(false)->void {
				LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
				LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block(this->lock_objholder_holder_memory_block);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block(wrapper_lock_objholder_holder_memory_block);
				{
					MemoryBlockHolder* holder_memory_block = this->objholder_holder_memory_block.get();
					if (!holder_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					LockableObjectToSTLWrapper wrapper_lock_memory_block_holder(holder_memory_block->lock_memory_block_holder);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder(wrapper_lock_memory_block_holder);
					{
						static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
						objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_memory_block;
						objholder_strtmplparameter_address_memory_block.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, _rawallocator, u8"address_memory_block", reinterpret_cast<uintptr_t>(holder_memory_block->is_readonly ? holder_memory_block->address_memory_block_readonly : holder_memory_block->address_memory_block));
						objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_size_memory_block;
						{
							char str_size_memory_block[sizeof(size_t) / sizeof(uint8_t) * 2 + 16];
							static constexpr char str_prefix_fmt[] = u8"0x%0*";
							char str_fmt[(sizeof(str_prefix_fmt) / sizeof(char) - 1) + (sizeof(inttype_traits_t<size_t>::fmtspec_printf_X_utf8) / sizeof(char))];
							memcpy(str_fmt, str_prefix_fmt, sizeof(str_prefix_fmt) - sizeof(char));
							memcpy(str_fmt + sizeof(str_prefix_fmt) / sizeof(char) - 1, inttype_traits_t<size_t>::fmtspec_printf_X_utf8, sizeof(inttype_traits_t<size_t>::fmtspec_printf_X_utf8) / sizeof(char));
							err_inner = SnPrintfUtf8(_rawallocator, str_size_memory_block, sizeof(str_size_memory_block) / sizeof(char), str_fmt, sizeof(str_fmt) / sizeof(char), (int)(sizeof(size_t) / sizeof(uint8_t) * 2), holder_memory_block->size_memory_block);
							if (err_inner) return;
							objholder_strtmplparameter_size_memory_block.construct(
								objholder_local_t<StringStringTemplateParameter>::construct_obj,
								_rawallocator,
								u8"size_memory_block",
								str_size_memory_block,
								strnlen(str_size_memory_block, sizeof(str_size_memory_block) / sizeof(char))
							);
						}
						err_inner = MemoryFile::strtmpl_description->GenerateString(StringTemplateParameterList(_rawallocator,
							{
								objholder_strtmplparameter_address_memory_block.get(),
								objholder_strtmplparameter_size_memory_block.get()
							}
						), description_ret, size_description_ret, should_null_terminate, _rawallocator);
						if (err_inner) {
							if (description_ret && *description_ret) {
								_rawallocator->Deallocate(*description_ret, *size_description_ret);
								*description_ret = nullptr;
							}
							if (size_description_ret && *size_description_ret) {
								*size_description_ret = 0;
							}
						}
					}
				}
			}
		);
		if (err) {
			if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
			}
			return err;
		}
		if (err_inner) {
			return err_inner;
		}
		return nullptr;
	}

	void YBWLIB2_CALLTYPE File_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IFileException)), module_info_current);
		GetDynamicTypeThisClassObject<IBofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IBofFileException)), module_info_current);
		GetDynamicTypeThisClassObject<IEofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IEofFileException)), module_info_current);
		GetDynamicTypeThisClassObject<IFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IFile)), module_info_current);
		GetDynamicTypeThisClassObject<ISizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<ISeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<IReadableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IReadableFile)), module_info_current);
		GetDynamicTypeThisClassObject<IWriteableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IWriteableFile)), module_info_current);
		FileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<FileException>(),
			IsDynamicTypeModuleLocalClass<FileException>(),
			{
				DynamicTypeBaseClassDef<FileException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<FileException, IFileException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(FileException), alignof(FileException));
		BofFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<BofFileException>(),
			IsDynamicTypeModuleLocalClass<BofFileException>(),
			{
				DynamicTypeBaseClassDef<BofFileException, FileException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<BofFileException, IBofFileException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(BofFileException), alignof(BofFileException));
		EofFileException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<EofFileException>(),
			IsDynamicTypeModuleLocalClass<EofFileException>(),
			{
				DynamicTypeBaseClassDef<EofFileException, FileException, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<EofFileException, IEofFileException, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(EofFileException), alignof(EofFileException));
		File::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<File>(),
			IsDynamicTypeModuleLocalClass<File>(),
			{
				DynamicTypeBaseClassDef<File, ReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<File, IFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(File), alignof(File));
		SizedFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<SizedFile>(),
			IsDynamicTypeModuleLocalClass<SizedFile>(),
			{
				DynamicTypeBaseClassDef<SizedFile, File, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<SizedFile, ISizedFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(SizedFile), alignof(SizedFile));
		SeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<SeekableFile>(),
			IsDynamicTypeModuleLocalClass<SeekableFile>(),
			{
				DynamicTypeBaseClassDef<SeekableFile, File, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<SeekableFile, ISeekableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(SeekableFile), alignof(SeekableFile));
		ReadableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ReadableFile>(),
			IsDynamicTypeModuleLocalClass<ReadableFile>(),
			{
				DynamicTypeBaseClassDef<ReadableFile, File, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ReadableFile, IReadableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ReadableFile), alignof(ReadableFile));
		WriteableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<WriteableFile>(),
			IsDynamicTypeModuleLocalClass<WriteableFile>(),
			{
				DynamicTypeBaseClassDef<WriteableFile, File, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<WriteableFile, IWriteableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(WriteableFile), alignof(WriteableFile));
		SizetSizedFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<SizetSizedFile>(),
			IsDynamicTypeModuleLocalClass<SizetSizedFile>(),
			{
				DynamicTypeBaseClassDef<SizetSizedFile, SizedFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(SizetSizedFile), alignof(SizetSizedFile));
		SizetSeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<SizetSeekableFile>(),
			IsDynamicTypeModuleLocalClass<SizetSeekableFile>(),
			{
				DynamicTypeBaseClassDef<SizetSeekableFile, SeekableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(SizetSeekableFile), alignof(SizetSeekableFile));
		ULongLongSizedFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ULongLongSizedFile>(),
			IsDynamicTypeModuleLocalClass<ULongLongSizedFile>(),
			{
				DynamicTypeBaseClassDef<ULongLongSizedFile, SizedFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ULongLongSizedFile), alignof(ULongLongSizedFile));
		ULongLongSeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ULongLongSeekableFile>(),
			IsDynamicTypeModuleLocalClass<ULongLongSeekableFile>(),
			{
				DynamicTypeBaseClassDef<ULongLongSeekableFile, SeekableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(ULongLongSeekableFile), alignof(ULongLongSeekableFile));
		MemoryFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<MemoryFile>(),
			IsDynamicTypeModuleLocalClass<MemoryFile>(),
			{
				DynamicTypeBaseClassDef<MemoryFile, SizetSizedFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryFile, SizetSeekableFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryFile, ReadableFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryFile, WriteableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(MemoryFile), alignof(MemoryFile));
		GetDynamicTypeThisClassObject<FileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(FileException)), module_info_current);
		GetDynamicTypeThisClassObject<BofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(BofFileException)), module_info_current);
		GetDynamicTypeThisClassObject<EofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(EofFileException)), module_info_current);
		GetDynamicTypeThisClassObject<File>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(File)), module_info_current);
		GetDynamicTypeThisClassObject<SizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<SeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<ReadableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ReadableFile)), module_info_current);
		GetDynamicTypeThisClassObject<WriteableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(WriteableFile)), module_info_current);
		GetDynamicTypeThisClassObject<SizetSizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizetSizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<SizetSeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizetSeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<ULongLongSizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ULongLongSizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<ULongLongSeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ULongLongSeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<MemoryFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(MemoryFile)), module_info_current);
	}

	void YBWLIB2_CALLTYPE File_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<MemoryFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ULongLongSeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ULongLongSizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SizetSeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SizetSizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<WriteableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ReadableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<File>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<EofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<BofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<FileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete MemoryFile::DynamicTypeThisClassObject;
		MemoryFile::DynamicTypeThisClassObject = nullptr;
		delete ULongLongSeekableFile::DynamicTypeThisClassObject;
		ULongLongSeekableFile::DynamicTypeThisClassObject = nullptr;
		delete ULongLongSizedFile::DynamicTypeThisClassObject;
		ULongLongSizedFile::DynamicTypeThisClassObject = nullptr;
		delete SizetSeekableFile::DynamicTypeThisClassObject;
		SizetSeekableFile::DynamicTypeThisClassObject = nullptr;
		delete SizetSizedFile::DynamicTypeThisClassObject;
		SizetSizedFile::DynamicTypeThisClassObject = nullptr;
		delete WriteableFile::DynamicTypeThisClassObject;
		WriteableFile::DynamicTypeThisClassObject = nullptr;
		delete ReadableFile::DynamicTypeThisClassObject;
		ReadableFile::DynamicTypeThisClassObject = nullptr;
		delete SeekableFile::DynamicTypeThisClassObject;
		SeekableFile::DynamicTypeThisClassObject = nullptr;
		delete SizedFile::DynamicTypeThisClassObject;
		SizedFile::DynamicTypeThisClassObject = nullptr;
		delete File::DynamicTypeThisClassObject;
		File::DynamicTypeThisClassObject = nullptr;
		delete EofFileException::DynamicTypeThisClassObject;
		EofFileException::DynamicTypeThisClassObject = nullptr;
		delete BofFileException::DynamicTypeThisClassObject;
		BofFileException::DynamicTypeThisClassObject = nullptr;
		delete FileException::DynamicTypeThisClassObject;
		FileException::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IWriteableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IReadableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IEofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IBofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
