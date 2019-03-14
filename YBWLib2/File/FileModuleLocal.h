#ifndef _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E
#define _INCLUDE_GUARD_CEA824C3_26E8_47B5_A9C6_76D1D96DF93E

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(FileException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(BofFileException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(File, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizedFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SeekableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ReadableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(WriteableFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizetSizedFile, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SizetSeekableFile, );

	[[nodiscard]] IException* FileException::GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret) noexcept {
		if (!description_ret || !size_description_ret) abort();
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &description_ret, &size_description_ret, &err_inner]() noexcept(false)->void {
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				IFile* file = this->GetFile();
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_file;
				objholder_strtmplparameter_address_file.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_file", reinterpret_cast<uintptr_t>(file));
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_description_file;
				{
					struct holder_str_t final {
						const rawallocator_t* rawallocator = nullptr;
						char* str = nullptr;
						size_t size_str = 0;
						inline constexpr holder_str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
						/*holder_str_t(const holder_str_t&) = delete;
						inline holder_str_t(holder_str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
						}*/
						inline ~holder_str_t() {
							if (this->str) {
								if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char))) abort();
								this->str = nullptr;
							}
							this->size_str = 0;
							this->rawallocator = nullptr;
						}
						/*holder_str_t& operator=(const holder_str_t&) = delete;
						inline holder_str_t& operator=(holder_str_t&& x) noexcept {
							this->rawallocator = ::std::move(x.rawallocator);
							this->str = ::std::move(x.str);
							this->size_str = ::std::move(x.size_str);
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
							return *this;
						}*/
					} holder_str_description_file(rawallocator_exception);
					if (file) {
						IException* err_cause_inner = file->GetDescription(rawallocator_exception, &holder_str_description_file.str, &holder_str_description_file.size_str, false);
						err_inner = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_inner->AttachCause(err_cause_inner);
						return;
					}
					if (holder_str_description_file.str && holder_str_description_file.size_str) {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", holder_str_description_file.str, holder_str_description_file.size_str);
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
				IFile* file = this->GetFile();
				objholder_local_t<AddressStringTemplateParameter> objholder_strtmplparameter_address_file;
				objholder_strtmplparameter_address_file.construct(objholder_local_t<AddressStringTemplateParameter>::construct_obj, rawallocator_exception, u8"address_file", reinterpret_cast<uintptr_t>(file));
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_description_file;
				{
					struct holder_str_t final {
						const rawallocator_t* rawallocator = nullptr;
						char* str = nullptr;
						size_t size_str = 0;
						inline constexpr holder_str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
						/*holder_str_t(const holder_str_t&) = delete;
						inline holder_str_t(holder_str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
						}*/
						inline ~holder_str_t() {
							if (this->str) {
								if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char))) abort();
								this->str = nullptr;
							}
							this->size_str = 0;
							this->rawallocator = nullptr;
						}
						/*holder_str_t& operator=(const holder_str_t&) = delete;
						inline holder_str_t& operator=(holder_str_t&& x) noexcept {
							this->rawallocator = ::std::move(x.rawallocator);
							this->str = ::std::move(x.str);
							this->size_str = ::std::move(x.size_str);
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
							return *this;
						}*/
					} holder_str_description_file(rawallocator_exception);
					if (file) {
						IException* err_cause_inner = file->GetDescription(rawallocator_exception, &holder_str_description_file.str, &holder_str_description_file.size_str, false);
						err_inner = YBWLIB2_EXCEPTION_CREATE_DOUBLE_EXCEPTION_EXCEPTION();
						err_inner->AttachCause(err_cause_inner);
						return;
					}
					if (holder_str_description_file.str && holder_str_description_file.size_str) {
						objholder_strtmplparameter_description_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, rawallocator_exception, u8"description_file", holder_str_description_file.str, holder_str_description_file.size_str);
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

	void YBWLIB2_CALLTYPE File_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IFileException)), module_info_current);
		GetDynamicTypeThisClassObject<IBofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IBofFileException)), module_info_current);
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
		GetDynamicTypeThisClassObject<FileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(FileException)), module_info_current);
		GetDynamicTypeThisClassObject<BofFileException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(BofFileException)), module_info_current);
		GetDynamicTypeThisClassObject<File>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(File)), module_info_current);
		GetDynamicTypeThisClassObject<SizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<SeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SeekableFile)), module_info_current);
		GetDynamicTypeThisClassObject<ReadableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ReadableFile)), module_info_current);
		GetDynamicTypeThisClassObject<WriteableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(WriteableFile)), module_info_current);
		GetDynamicTypeThisClassObject<SizetSizedFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizetSizedFile)), module_info_current);
		GetDynamicTypeThisClassObject<SizetSeekableFile>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SizetSeekableFile)), module_info_current);
	}

	void YBWLIB2_CALLTYPE File_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<SizetSeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SizetSizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<WriteableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ReadableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<SizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<File>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<BofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<FileException>()->UnRegisterTypeInfoWrapper(module_info_current);
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
		delete BofFileException::DynamicTypeThisClassObject;
		BofFileException::DynamicTypeThisClassObject = nullptr;
		delete FileException::DynamicTypeThisClassObject;
		FileException::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IWriteableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IReadableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISeekableFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISizedFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IFile>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IBofFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IFileException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
