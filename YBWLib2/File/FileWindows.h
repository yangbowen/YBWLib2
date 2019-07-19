#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_39802C61_29BE_45D6_B8C0_08400073B687
#define _INCLUDE_GUARD_39802C61_29BE_45D6_B8C0_08400073B687

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <mutex>
#include <minwindef.h>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"
#include "../Common/CommonWindows.h"
#include "../Common/CommonSTLHelperWindows.h"
#include "File.h"

namespace YBWLib2 {
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// An implementation of <c>IFile</c>, <c>IReadableFile</c>, <c>IWriteableFile</c>, <c>ISizedFile</c> and <c>ISeekableFile</c> that operates on a Win32 file.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by the interface classes.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class Win32File
		: public virtual ULongLongSizedFile,
		public virtual ULongLongSeekableFile,
		public virtual ReadableFile,
		public virtual WriteableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Win32File, , "0f872e37-6173-411d-9e4f-7f3df2e34e02");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Win32File);
		struct readonly_t {};
		struct writeonly_t {};
		static constexpr readonly_t readonly {};
		static constexpr writeonly_t writeonly {};
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline Win32File(const Win32HandleHolder& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(_win32handleholder_file), can_read(true), can_write(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(readonly_t, const Win32HandleHolder& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(_win32handleholder_file), can_read(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(writeonly_t, const Win32HandleHolder& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(_win32handleholder_file), can_write(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(Win32HandleHolder&& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(::std::move(_win32handleholder_file)), can_read(true), can_write(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(readonly_t, Win32HandleHolder&& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(::std::move(_win32handleholder_file)), can_read(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(writeonly_t, Win32HandleHolder&& _win32handleholder_file) noexcept(false)
			: win32handleholder_file(::std::move(_win32handleholder_file)), can_write(true) {
			if (!this->win32handleholder_file) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Win32File));
		}
		inline Win32File(const Win32File& x) noexcept(false)
			: ReferenceCountedObject(static_cast<const ReferenceCountedObject&>(x)),
			File(static_cast<const File&>(x)),
			ISizedFile(static_cast<const ISizedFile&>(x)),
			ISeekableFile(static_cast<const ISeekableFile&>(x)),
			IReadableFile(static_cast<const IReadableFile&>(x)),
			IWriteableFile(static_cast<const IWriteableFile&>(x)),
			SizedFile(static_cast<const SizedFile&>(x)),
			SeekableFile(static_cast<const SeekableFile&>(x)),
			ULongLongSizedFile(static_cast<const ULongLongSizedFile&>(x)),
			ULongLongSeekableFile(static_cast<const ULongLongSeekableFile&>(x)),
			ReadableFile(static_cast<const ReadableFile&>(x)),
			WriteableFile(static_cast<const WriteableFile&>(x)) {
				{
					LockableObjectToSTLWrapper wrapper_lock_x(x.lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_x(wrapper_lock_x);
					this->win32handleholder_file = x.win32handleholder_file;
					this->can_read = x.can_read;
					this->can_write = x.can_write;
				}
		}
		inline Win32File(Win32File&& x) noexcept(false)
			: ReferenceCountedObject(static_cast<ReferenceCountedObject&&>(::std::move(x))),
			File(static_cast<File&&>(::std::move(x))),
			ISizedFile(static_cast<ISizedFile&&>(::std::move(x))),
			ISeekableFile(static_cast<ISeekableFile&&>(::std::move(x))),
			IReadableFile(static_cast<IReadableFile&&>(::std::move(x))),
			IWriteableFile(static_cast<IWriteableFile&&>(::std::move(x))),
			SizedFile(static_cast<SizedFile&&>(::std::move(x))),
			SeekableFile(static_cast<SeekableFile&&>(::std::move(x))),
			ULongLongSizedFile(static_cast<ULongLongSizedFile&&>(::std::move(x))),
			ULongLongSeekableFile(static_cast<ULongLongSeekableFile&&>(::std::move(x))),
			ReadableFile(static_cast<ReadableFile&&>(::std::move(x))),
			WriteableFile(static_cast<WriteableFile&&>(::std::move(x))) {
				{
					LockableObjectToSTLWrapper wrapper_lock_x(x.lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_x(wrapper_lock_x);
					this->win32handleholder_file = ::std::move(x.win32handleholder_file);
					this->can_read = ::std::move(x.can_read);
					x.can_read = false;
					this->can_write = ::std::move(x.can_write);
					x.can_write = false;
				}
		}
		inline Win32File& operator=(const Win32File& x) noexcept(false) {
			static_cast<ReferenceCountedObject&>(*this) = static_cast<const ReferenceCountedObject&>(x);
			static_cast<File&>(*this) = static_cast<const File&>(x);
			static_cast<ISizedFile&>(*this) = static_cast<const ISizedFile&>(x);
			static_cast<ISeekableFile&>(*this) = static_cast<const ISeekableFile&>(x);
			static_cast<IReadableFile&>(*this) = static_cast<const IReadableFile&>(x);
			static_cast<IWriteableFile&>(*this) = static_cast<const IWriteableFile&>(x);
			static_cast<SizedFile&>(*this) = static_cast<const SizedFile&>(x);
			static_cast<SeekableFile&>(*this) = static_cast<const SeekableFile&>(x);
			static_cast<ULongLongSizedFile&>(*this) = static_cast<const ULongLongSizedFile&>(x);
			static_cast<ULongLongSeekableFile&>(*this) = static_cast<const ULongLongSeekableFile&>(x);
			static_cast<ReadableFile&>(*this) = static_cast<const ReadableFile&>(x);
			static_cast<WriteableFile&>(*this) = static_cast<const WriteableFile&>(x);
			{
				LockableObjectToSTLWrapper wrapper_lock_x(x.lock_this);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_x(wrapper_lock_x);
				this->win32handleholder_file = x.win32handleholder_file;
				this->can_read = x.can_read;
				this->can_write = x.can_write;
			}
		}
		inline Win32File& operator=(Win32File&& x) noexcept(false) {
			static_cast<ReferenceCountedObject&>(*this) = static_cast<ReferenceCountedObject&&>(::std::move(x));
			static_cast<File&>(*this) = static_cast<File&&>(::std::move(x));
			static_cast<ISizedFile&>(*this) = static_cast<ISizedFile&&>(::std::move(x));
			static_cast<ISeekableFile&>(*this) = static_cast<ISeekableFile&&>(::std::move(x));
			static_cast<IReadableFile&>(*this) = static_cast<IReadableFile&&>(::std::move(x));
			static_cast<IWriteableFile&>(*this) = static_cast<IWriteableFile&&>(::std::move(x));
			static_cast<SizedFile&>(*this) = static_cast<SizedFile&&>(::std::move(x));
			static_cast<SeekableFile&>(*this) = static_cast<SeekableFile&&>(::std::move(x));
			static_cast<ULongLongSizedFile&>(*this) = static_cast<ULongLongSizedFile&&>(::std::move(x));
			static_cast<ULongLongSeekableFile&>(*this) = static_cast<ULongLongSeekableFile&&>(::std::move(x));
			static_cast<ReadableFile&>(*this) = static_cast<ReadableFile&&>(::std::move(x));
			static_cast<WriteableFile&>(*this) = static_cast<WriteableFile&&>(::std::move(x));
			{
				LockableObjectToSTLWrapper wrapper_lock_x(x.lock_this);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_x(wrapper_lock_x);
				this->win32handleholder_file = ::std::move(x.win32handleholder_file);
				this->can_read = ::std::move(x.can_read);
				x.can_read = false;
				this->can_write = ::std::move(x.can_write);
				x.can_write = false;
			}
		}
		/// <summary>Gets a human-readable description for this file.</summary>
		/// <param name="_rawallocator">A pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, including the memory for <c>*description_ret</c>.</param>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this file.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this file.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <paramref name="_rawallocator" />.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this file, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this file, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this file.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this file, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the description string.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) const noexcept;
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetFileSizeULongLong(unsigned long long* size_ret) const noexcept override {
			if (!size_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, GetFileSizeULongLong);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &size_ret, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					LARGE_INTEGER largeint_size_file;
					if (!GetFileSizeEx(this->win32handleholder_file.get(), &largeint_size_file)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(GetFileSizeEx); return; }
					if (largeint_size_file.QuadPart < 0) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					*size_ret = largeint_size_file.QuadPart;
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
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SetFileSizeULongLong(unsigned long long size) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &size, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					struct save_position_file_t final {
						HANDLE win32handle_file = NULL;
						LARGE_INTEGER largeint_position_file;
						inline save_position_file_t(HANDLE _win32handle_file) noexcept(false) : win32handle_file(_win32handle_file) {
							LARGE_INTEGER largeint_zero;
							largeint_zero.QuadPart = 0;
							if (!SetFilePointerEx(this->win32handle_file, largeint_zero, &this->largeint_position_file, FILE_CURRENT)) throw(YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx));
						}
						save_position_file_t(const save_position_file_t&) = delete;
						save_position_file_t(save_position_file_t&&) = delete;
						inline ~save_position_file_t() {
							SetFilePointerEx(this->win32handle_file, this->largeint_position_file, nullptr, FILE_BEGIN);
						}
						save_position_file_t& operator=(const save_position_file_t&) = delete;
						save_position_file_t& operator=(save_position_file_t&&) = delete;
					} save_position_file(this->win32handleholder_file.get());
					{
						LARGE_INTEGER largeint_size_file;
						if (size > LLONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, SetFileSizeULongLong); return; }
						largeint_size_file.QuadPart = size;
						if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_size_file, nullptr, FILE_BEGIN)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
					}
					if (!SetEndOfFile(this->win32handleholder_file.get())) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetEndOfFile); return; }
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
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* IsEof(bool* is_eof_ret) const noexcept override {
			if (!is_eof_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, IsEof);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &is_eof_ret, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					unsigned long long size_file = 0, position_file = 0;
					err_inner = this->GetFileSizeULongLong(&size_file);
					if (err_inner) return;
					err_inner = this->TellULongLong(&position_file);
					if (err_inner) return;
					*is_eof_ret = position_file >= size_file;
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
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="distance">
		/// The distance (in <c>uint8_t</c>s) between the start of the file and the target position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromBeginULongLong(unsigned long long distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					LARGE_INTEGER largeint_distance;
					if (distance > LLONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, SeekFromBeginULongLong); return; }
					largeint_distance.QuadPart = distance;
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
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="distance">
		/// The distance (in <c>uint8_t</c>s) between the target position and the end of file.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromEndULongLong(unsigned long long distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					LARGE_INTEGER largeint_distance;
					if (distance > LLONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, SeekFromEndULongLong); return; }
					largeint_distance.QuadPart = distance;
					if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_distance, nullptr, FILE_END)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
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
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="distance">
		/// The distance (in <c>uint8_t</c>s) between the current position and the target position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekForwardULongLong(unsigned long long distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					LARGE_INTEGER largeint_distance;
					if (distance > LLONG_MAX) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, SeekForwardULongLong); return; }
					largeint_distance.QuadPart = distance;
					if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_distance, nullptr, FILE_CURRENT)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
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
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="distance">
		/// The distance (in <c>uint8_t</c>s) between the target position and the current position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekBackwardULongLong(unsigned long long distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					if (distance > (unsigned long long) - LLONG_MIN) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, SeekBackwardULongLong); return; }
					/// <summary>
					/// The distance to seek backward each time.
					/// It is set to the maximal power of <c>2</c> not greater than <c>LLONG_MAX</c>.
					/// </summary>
					static constexpr long long longlong_step = ((LLONG_MAX >> 1) | ((LLONG_MAX ^ (LLONG_MAX - 1)) >> 2)) + 1;
					for (; distance > (unsigned long long)LLONG_MAX; distance -= (unsigned long long)longlong_step) {
						LARGE_INTEGER largeint_distance;
						largeint_distance.QuadPart = -longlong_step;
						if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_distance, nullptr, FILE_CURRENT)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
					}
					LARGE_INTEGER largeint_distance;
					largeint_distance.QuadPart = -(long long)distance;
					if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_distance, nullptr, FILE_CURRENT)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
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
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* TellULongLong(unsigned long long* distance_ret) const noexcept override {
			if (!distance_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, TellULongLong);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance_ret, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					LARGE_INTEGER largeint_zero, largeint_position_file;
					largeint_zero.QuadPart = 0;
					if (!SetFilePointerEx(this->win32handleholder_file.get(), largeint_zero, &largeint_position_file, FILE_CURRENT)) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(SetFilePointerEx); return; }
					if (largeint_position_file.QuadPart < 0) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
					*distance_ret = largeint_position_file.QuadPart;
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
		/// <summary>
		/// Reads from the current position to the buffer.
		/// If the file object on which this member function is called has a meaningful file position, the position goes forward to just after the written data.
		/// </summary>
		/// <param name="buf">Pointer to the buffer.</param>
		/// <param name="size">The number of bytes to be read.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* Read(void* buf, size_t size_buf) noexcept override {
			if (!size_buf) return nullptr;
			if (!buf) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Read);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &buf, &size_buf, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					if (!this->can_read) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32File, Read); return; }
#if SIZE_MAX > MAXDWORD
					/// <summary>
					/// The size to read each time.
					/// It is set to the maximal power of <c>2</c> not greater than <c>MAXDWORD</c>.
					/// </summary>
					static constexpr DWORD dword_step = ((MAXDWORD >> 1) | ((MAXDWORD ^ (MAXDWORD - 1)) >> 2)) + 1;
					for (; size_buf > MAXDWORD; reinterpret_cast<uint8_t*&>(buf) += dword_step, size_buf -= dword_step) {
						DWORD dword_cb_read = 0;
						if (!ReadFile(this->win32handleholder_file.get(), buf, dword_step, &dword_cb_read, nullptr) || dword_cb_read != dword_step) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ReadFile); return; }
					}
					DWORD dword_cb_read = 0;
					if (!ReadFile(this->win32handleholder_file.get(), buf, size_buf & ~(DWORD)0, &dword_cb_read, nullptr) || dword_cb_read != size_buf) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ReadFile); return; }
#else
					DWORD dword_cb_read = 0;
					if (!ReadFile(this->win32handleholder_file.get(), buf, size_buf, &dword_cb_read, nullptr) || dword_cb_read != size_buf) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(ReadFile); return; }
#endif
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
		/// <summary>
		/// Writes from the buffer to the current position.
		/// If the file object on which this member function is called has a meaningful file position, the position goes forward to just after the written data.
		/// </summary>
		/// <param name="buf">Pointer to the buffer.</param>
		/// <param name="size">The number of bytes to be written.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* Write(const void* buf, size_t size_buf) noexcept override {
			if (!size_buf) return nullptr;
			if (!buf) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::Win32File, Write);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &buf, &size_buf, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					LockableObjectToSTLWrapper wrapper_lock_this(this->lock_this);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_this(wrapper_lock_this);
					if (!this->can_write) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::Win32File, Write); return; }
#if SIZE_MAX > MAXDWORD
					/// <summary>
					/// The size to write each time.
					/// It is set to the maximal power of <c>2</c> not greater than <c>MAXDWORD</c>.
					/// </summary>
					static constexpr DWORD dword_step = ((MAXDWORD >> 1) | ((MAXDWORD ^ (MAXDWORD - 1)) >> 2)) + 1;
					for (; size_buf > MAXDWORD; reinterpret_cast<const uint8_t*&>(buf) += dword_step, size_buf -= dword_step) {
						DWORD dword_cb_written = 0;
						if (!WriteFile(this->win32handleholder_file.get(), buf, dword_step, &dword_cb_written, nullptr) || dword_cb_written != dword_step) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WriteFile); return; }
					}
					DWORD dword_cb_written = 0;
					if (!WriteFile(this->win32handleholder_file.get(), buf, size_buf & ~(DWORD)0, &dword_cb_written, nullptr) || dword_cb_written != size_buf) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WriteFile); return; }
#else
					DWORD dword_cb_written = 0;
					if (!WriteFile(this->win32handleholder_file.get(), buf, size_buf, &dword_cb_written, nullptr) || dword_cb_written != size_buf) { err_inner = YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(WriteFile); return; }
#endif
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
	protected:
		mutable LockableObjectFromSTLWrapper<::std::recursive_mutex> lock_this;
		Win32HandleHolder win32handleholder_file;
		bool can_read = false;
		bool can_write = false;
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~Win32File() = default;
		/// <summary>
		/// Destructs the object and frees any resources allocated for the object.
		/// This function is intended to be called only by <c>DecReferenceCount</c>.
		/// </summary>
		inline virtual void DeleteMe() noexcept override {
			delete this;
		}
	};
	static_assert(sizeof(LARGE_INTEGER) == sizeof(LARGE_INTEGER::QuadPart), "The size of LARGE_INTEGER does not equal to the size of its QuadPart.");
	static_assert(::std::is_same_v<decltype(LARGE_INTEGER::QuadPart), long long>, "The type of LARGE_INTEGER::QuadPart is different from long long.");
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	void YBWLIB2_CALLTYPE FileWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE FileWindows_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileWindowsUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_C4BBB069_4E45_4779_A7BB_BD83B521C5EF
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_4CEEB035_7EBA_44EB_AB61_4739CC130675
#endif
