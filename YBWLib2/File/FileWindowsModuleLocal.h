#ifndef _INCLUDE_GUARD_49CC5EC3_F66A_46A0_BE03_0856F77E7E84
#define _INCLUDE_GUARD_49CC5EC3_F66A_46A0_BE03_0856F77E7E84

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"
#include "../DynamicType/DynamicType.h"
#include "../UserInterface/UserInterface.h"
#include "../UserInterface/UserInterfaceWindows.h"
#include "File.h"
#include "FileWindows.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Win32File, );

	[[nodiscard]] IException* Win32File::GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) const noexcept {
		if (!_rawallocator || !description_ret || !size_description_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, GetDescription);
		IException* err_inner = nullptr;
		IException* err = WrapFunctionCatchExceptions(
			[this, &_rawallocator, &description_ret, &size_description_ret, &should_null_terminate, &err_inner]() noexcept(false)->void {
				LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
				LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
				static constexpr char conststr_unavailable[] = u8"<UNAVAILABLE>";
				objholder_local_t<Win32HandleStringTemplateParameter> objholder_strtmplparameter_win32handle_file;
				objholder_strtmplparameter_win32handle_file.construct(objholder_local_t<Win32HandleStringTemplateParameter>::construct_obj, _rawallocator, u8"win32handle_file", this->win32handleholder_file.get());
				objholder_local_t<StringStringTemplateParameter> objholder_strtmplparameter_filename_file;
				{
					static_assert(sizeof(char16_t) == sizeof(wchar_t), "The size of char16_t is different from the size of wchar_t.");
					struct holder_u16str_t final {
						const rawallocator_t* rawallocator = nullptr;
						char16_t* str = nullptr;
						size_t size_str = 0;
						inline constexpr holder_u16str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
						/*holder_u16str_t(const holder_u16str_t&) = delete;
						inline holder_u16str_t(holder_u16str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
						}*/
						inline ~holder_u16str_t() {
							if (this->str) {
								if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char16_t))) abort();
								this->str = nullptr;
							}
							this->size_str = 0;
							this->rawallocator = nullptr;
						}
						/*holder_u16str_t& operator=(const holder_u16str_t&) = delete;
						inline holder_u16str_t& operator=(holder_u16str_t&& x) noexcept {
							this->rawallocator = ::std::move(x.rawallocator);
							this->str = ::std::move(x.str);
							this->size_str = ::std::move(x.size_str);
							x.rawallocator = nullptr;
							x.str = nullptr;
							x.size_str = 0;
							return *this;
						}*/
					} holder_u16str_filename_file(_rawallocator);
					holder_u16str_filename_file.size_str = 1;
					holder_u16str_filename_file.str = reinterpret_cast<char16_t*>(_rawallocator->Allocate(holder_u16str_filename_file.size_str * sizeof(char16_t)));
					if (!holder_u16str_filename_file.str) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					DWORD dword_size_filename_file = 0;
					dword_size_filename_file = GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
					if (!dword_size_filename_file) {
						dword_size_filename_file = GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_GUID);
						if (!dword_size_filename_file) {
							err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetFinalPathNameByHandleW);
							return;
						} else {
							holder_u16str_filename_file.size_str = dword_size_filename_file;
							holder_u16str_filename_file.str = reinterpret_cast<char16_t*>(_rawallocator->Reallocate(holder_u16str_filename_file.str, 1 * sizeof(char16_t), holder_u16str_filename_file.size_str * sizeof(char16_t)));
							if (!holder_u16str_filename_file.str) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
							--dword_size_filename_file;
							if (GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_GUID) != dword_size_filename_file) {
								err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetFinalPathNameByHandleW);
								return;
							}
						}
					} else {
						holder_u16str_filename_file.size_str = dword_size_filename_file;
						holder_u16str_filename_file.str = reinterpret_cast<char16_t*>(_rawallocator->Reallocate(holder_u16str_filename_file.str, 1 * sizeof(char16_t), holder_u16str_filename_file.size_str * sizeof(char16_t)));
						if (!holder_u16str_filename_file.str) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						--dword_size_filename_file;
						if (GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS) != dword_size_filename_file) {
							dword_size_filename_file = GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_GUID);
							if (!dword_size_filename_file) {
								err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetFinalPathNameByHandleW);
								return;
							} else {
								holder_u16str_filename_file.size_str = dword_size_filename_file;
								holder_u16str_filename_file.str = reinterpret_cast<char16_t*>(_rawallocator->Reallocate(holder_u16str_filename_file.str, 1 * sizeof(char16_t), holder_u16str_filename_file.size_str * sizeof(char16_t)));
								if (!holder_u16str_filename_file.str) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
								--dword_size_filename_file;
								if (GetFinalPathNameByHandleW(this->win32handleholder_file.get(), reinterpret_cast<wchar_t*>(holder_u16str_filename_file.str), dword_size_filename_file, FILE_NAME_NORMALIZED | VOLUME_NAME_GUID) != dword_size_filename_file) {
									err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetFinalPathNameByHandleW);
									return;
								}
							}
						}
					}
					if (holder_u16str_filename_file.str && holder_u16str_filename_file.size_str) {
						struct holder_u8str_t final {
							const rawallocator_t* rawallocator = nullptr;
							char* str = nullptr;
							size_t size_str = 0;
							inline constexpr holder_u8str_t(const rawallocator_t* _rawallocator) noexcept : rawallocator(_rawallocator) {}
							/*holder_u8str_t(const holder_u8str_t&) = delete;
							inline holder_u8str_t(holder_u8str_t&& x) noexcept : rawallocator(::std::move(x.rawallocator)), str(::std::move(x.str)), size_str(::std::move(x.size_str)) {
								x.rawallocator = nullptr;
								x.str = nullptr;
								x.size_str = 0;
							}*/
							inline ~holder_u8str_t() {
								if (this->str) {
									if (!this->rawallocator->Deallocate(this->str, size_str * sizeof(char))) abort();
									this->str = nullptr;
								}
								this->size_str = 0;
								this->rawallocator = nullptr;
							}
							/*holder_u8str_t& operator=(const holder_u8str_t&) = delete;
							inline holder_u8str_t& operator=(holder_u8str_t&& x) noexcept {
								this->rawallocator = ::std::move(x.rawallocator);
								this->str = ::std::move(x.str);
								this->size_str = ::std::move(x.size_str);
								x.rawallocator = nullptr;
								x.str = nullptr;
								x.size_str = 0;
								return *this;
							}*/
						} holder_u8str_filename_file(_rawallocator);
						err_inner = Utf16StringToUtf8String(_rawallocator, &holder_u8str_filename_file.str, &holder_u8str_filename_file.size_str, holder_u16str_filename_file.str, holder_u16str_filename_file.size_str - 1);
						if (err_inner) return;
						objholder_strtmplparameter_filename_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, _rawallocator, u8"filename_file", holder_u8str_filename_file.str, holder_u8str_filename_file.size_str);
					} else {
						objholder_strtmplparameter_filename_file.construct(objholder_local_t<StringStringTemplateParameter>::construct_obj, _rawallocator, u8"filename_file", conststr_unavailable, sizeof(conststr_unavailable) / sizeof(char) - 1);
					}
				}
				err_inner = Win32File::strtmpl_description->GenerateString(StringTemplateParameterList(_rawallocator,
					{
						objholder_strtmplparameter_win32handle_file.get(),
						objholder_strtmplparameter_filename_file.get()
					}
				), description_ret, size_description_ret, should_null_terminate, _rawallocator);
				if (err_inner) {
					if (description_ret && *description_ret) {
						if (!_rawallocator->Deallocate(*description_ret, *size_description_ret)) abort();
						*description_ret = nullptr;
					}
					if (size_description_ret && *size_description_ret) {
						*size_description_ret = 0;
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

	void YBWLIB2_CALLTYPE FileWindows_RealInitModuleLocal() noexcept {
		Win32File::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<Win32File>(),
			IsDynamicTypeModuleLocalClass<Win32File>(),
			{
				DynamicTypeBaseClassDef<Win32File, ULongLongSizedFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<Win32File, ULongLongSeekableFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<Win32File, ReadableFile, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<Win32File, WriteableFile, DynamicTypeBaseClassFlag_VirtualBase>
			},
			0, sizeof(Win32File), alignof(Win32File));
		GetDynamicTypeThisClassObject<Win32File>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Win32File)), module_info_current);
	}

	void YBWLIB2_CALLTYPE FileWindows_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<Win32File>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete Win32File::DynamicTypeThisClassObject;
		Win32File::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
