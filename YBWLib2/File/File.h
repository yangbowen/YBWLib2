#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_16A4E3E0_92C7_4B6F_994C_A8CA0D9314BE
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD
#define _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <mutex>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"

namespace YBWLib2 {
	class IFileException;
	class IBofFileException;
	class IEofFileException;
	class FileException;
	class BofFileException;
	class EofFileException;
	class IFile;
	class ISizedFile;
	class ISeekableFile;
	class IReadableFile;
	class IWriteableFile;
	class File;
	class SizedFile;
	class SeekableFile;
	class ReadableFile;
	class WriteableFile;
	class SizetSizedFile;
	class SizetSeekableFile;
	class ULongLongSizedFile;
	class ULongLongSeekableFile;
	class MemoryFile;

	/// <summary>An exception that relates to a file.</summary>
	class IFileException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IFileException, YBWLIB2_API, "86efb724-caf5-4d57-ae4e-631c780c7ed5");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IFileException);
		inline virtual ~IFileException() = default;
		/// <summary>Gets the <c>IFile</c> object related to the exception.</summary>
		/// <returns>
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The object on which this member function is called keeps one reference count of the <c>IFile</c> object.
		/// </returns>
		virtual const IFile* GetFile() const noexcept = 0;
	};

	/// <summary>An exception that occurs because the file position is attempted to be set beyond the start of the file.</summary>
	class IBofFileException abstract : public virtual IFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IBofFileException, YBWLIB2_API, "71f26d51-6f27-49de-99ab-8142c5c54f39");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IBofFileException);
		inline virtual ~IBofFileException() = default;
	};

	/// <summary>An exception that occurs because the file is attempted to be accessed in some ways unsupported when the position is beyond the last byte of the file.</summary>
	class IEofFileException abstract : public virtual IFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IEofFileException, YBWLIB2_API, "e255d047-bd87-4ef8-8b96-091ef18618c8");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IEofFileException);
		inline virtual ~IEofFileException() = default;
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IFileException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IFileException</c>.
	/// </summary>
	class FileException
		: public virtual Exception,
		public virtual IFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(FileException, , "a3232404-3264-47c1-aaab-e20132d99fd9");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(FileException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>FileException</c> object.</summary>
		/// <param name="_file">
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The constructed object increments and keeps one reference count of the <c>IFile</c> object.
		/// </param>
		inline FileException(const IFile* _file) noexcept : holder_file(_file, ReferenceCountedObjectHolder<const IFile>::inc_ref_count) {}
		inline virtual ~FileException() {}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the <c>IFile</c> object related to the exception.</summary>
		/// <returns>
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The object on which this member function is called keeps one reference count of the <c>IFile</c> object.
		/// </returns>
		inline virtual const IFile* GetFile() const noexcept override { return this->holder_file.get(); }
	protected:
		ReferenceCountedObjectHolder<const IFile> holder_file;
	};

	/// <summary>
	/// A default implementation of <c>IBofFileException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IBofFileException</c>.
	/// </summary>
	class BofFileException
		: public virtual FileException,
		public virtual IBofFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(BofFileException, , "be41ef8d-18f5-4287-a2b2-fbadc7e0db81");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(BofFileException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>BofFileException</c> object.</summary>
		/// <param name="_file">
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The constructed object increments and keeps one reference count of the <c>IFile</c> object.
		/// </param>
		inline BofFileException(const IFile* _file) noexcept : FileException(_file) {}
		inline virtual ~BofFileException() {}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};

	/// <summary>
	/// A default implementation of <c>IEofFileException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IEofFileException</c>.
	/// </summary>
	class EofFileException
		: public virtual FileException,
		public virtual IEofFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(EofFileException, , "ab687fb2-4c3f-45c2-b1e0-9b9c2aa2a479");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(EofFileException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>EofFileException</c> object.</summary>
		/// <param name="_file">
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The constructed object increments and keeps one reference count of the <c>IFile</c> object.
		/// </param>
		inline EofFileException(const IFile* _file) noexcept : FileException(_file) {}
		inline virtual ~EofFileException() {}
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	/// <summary>A file.</summary>
	class IFile abstract : public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IFile, YBWLIB2_API, "e4f0b590-127c-4481-8700-084dac47d30b");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IFile);
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
		[[nodiscard]] virtual IException* GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IFile() = default;
	};

	/// <summary>A file that has a size.</summary>
	class ISizedFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ISizedFile, YBWLIB2_API, "d75b8ae6-87ec-4821-a40f-de450160a6bd");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ISizedFile);
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSize(size_t* size_ret) const noexcept = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSize(size_t size) noexcept = 0;
		/// <summary>Gets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that receives the current file size (in <c>uint8_t</c>s).
		/// The file size will be stored in machine byte order.
		/// </param>
		/// <param name="size_buf_size">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSizeLarge(void* buf_size, size_t size_buf_size) const noexcept = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that specifies the new file size (in <c>uint8_t</c>s).
		/// The file size must be stored in machine byte order.
		/// If the new file size is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_size">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSizeLarge(const void* buf_size, size_t size_buf_size) noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~ISizedFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>A file that supports seeking and/or telling.</summary>
	class ISeekableFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ISeekableFile, YBWLIB2_API, "cfc42a4e-a1f6-4684-93d1-f27d998aafa4");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ISeekableFile);
		/// <summary>
		/// Returns a pointer to the <c>ILockableObject</c> object that locks the file position.
		/// The object on which this member function is called, instead of the caller, owns the object pointed to by the returned pointer.
		/// The <c>ILockableObject</c> object shall be declared <c>mutable</c>.
		/// The duration of the <c>ILockableObject</c> object shall extend at least until the destruction of this object.
		/// </summary>
		virtual ILockableObject* GetFilePositionLock() const noexcept = 0;
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* IsEof(bool* is_eof_ret) const noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekFromBegin(size_t distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekFromEnd(size_t distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekForward(size_t distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekBackward(size_t distance) noexcept = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* Tell(size_t* distance_ret) const noexcept = 0;
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the start of the file and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromBeginLarge(const void* buf_distance, size_t size_buf_distance) noexcept = 0;
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the end of file.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromEndLarge(const void* buf_distance, size_t size_buf_distance) noexcept = 0;
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the current position and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekForwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept = 0;
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the current position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekBackwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// The distance will be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <param name="size_buf_distance">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* TellLarge(void* buf_distance, size_t size_buf_distance) const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~ISeekableFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>A file for reading.</summary>
	class IReadableFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IReadableFile, YBWLIB2_API, "1bff7b77-8bcb-42a4-8ccf-bd5e297a351e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IReadableFile);
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
		[[nodiscard]] virtual IException* Read(void* buf, size_t size_buf) noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IReadableFile() = default;
	};

	/// <summary>A file for writing.</summary>
	class IWriteableFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IWriteableFile, YBWLIB2_API, "4d104398-ff0f-4a4c-934a-0cf1bbcfc4ce");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IWriteableFile);
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
		[[nodiscard]] virtual IException* Write(const void* buf, size_t size_buf) noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IWriteableFile() = default;
	};

	/// <summary>Converts an unsigned integer buffer to an unsigned integral value.</summary>
	/// <param name="buf_uint">
	/// An unsigned integer buffer that specifies the value to be converted.
	/// The value must be stored in machine byte order.
	/// If the value is too large, the function call will fail.
	/// </param>
	/// <param name="size_buf_uint">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Uint_Ty>
	[[nodiscard]] inline IException* GenericUintFromLarge(_Uint_Ty* uint_ret, const void* buf_uint, size_t size_buf_uint) noexcept {
		static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
		if (!uint_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
		if (!size_buf_uint) {
			*uint_ret = 0;
			return nullptr;
		}
		if (!buf_uint) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
		*uint_ret = 0;
		if (sizeof(_Uint_Ty) >= size_buf_uint) {
			if (*is_byte_order_le) {
				memcpy(reinterpret_cast<void*>(uint_ret), buf_uint, size_buf_uint);
				return nullptr;
			} else if (*is_byte_order_be) {
				memcpy(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(uint_ret) + (sizeof(_Uint_Ty) - size_buf_uint)), buf_uint, size_buf_uint);
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
			}
		} else {
			if (*is_byte_order_le) {
				{
					const uint8_t* limit_p = reinterpret_cast<const uint8_t*>(buf_uint) + size_buf_uint;
					for (const uint8_t* p = reinterpret_cast<const uint8_t*>(buf_uint) + sizeof(_Uint_Ty); p < limit_p; ++p)
						if (*p)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
				}
				memcpy(reinterpret_cast<void*>(uint_ret), buf_uint, sizeof(_Uint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				{
					const uint8_t* limit_p = reinterpret_cast<const uint8_t*>(buf_uint) + (size_buf_uint - sizeof(_Uint_Ty));
					for (const uint8_t* p = reinterpret_cast<const uint8_t*>(buf_uint); p < limit_p; ++p)
						if (*p)
							return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
				}
				memcpy(reinterpret_cast<void*>(uint_ret), reinterpret_cast<const void*>(reinterpret_cast<const uint8_t*>(buf_uint) + (size_buf_uint - sizeof(_Uint_Ty))), sizeof(_Uint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintFromLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>Converts an unsigned integral value to an unsigned integer buffer.</summary>
	/// <param name="buf_uint">
	/// An unsigned integer buffer that receives the converted value.
	/// The value will be stored in machine byte order.
	/// </param>
	/// <param name="size_buf_uint">
	/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint</c>.
	/// If the buffer is insufficient to contain the value, the function call will fail.
	/// </param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	template<typename _Uint_Ty>
	[[nodiscard]] inline IException* GenericUintToLarge(_Uint_Ty uint, void* buf_uint, size_t size_buf_uint) noexcept {
		static_assert(::std::is_integral_v<_Uint_Ty> && ::std::is_unsigned_v<_Uint_Ty>, "The specified unsigned integral type is not an unsigned integral type.");
		if (!size_buf_uint) {
			if (uint)
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			else
				return nullptr;
		}
		if (!buf_uint) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
		if (size_buf_uint >= sizeof(_Uint_Ty)) {
			if (*is_byte_order_le) {
				memcpy(buf_uint, reinterpret_cast<const void*>(&uint), sizeof(_Uint_Ty));
				memset(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(buf_uint) + sizeof(_Uint_Ty)), 0, size_buf_uint - sizeof(_Uint_Ty));
				return nullptr;
			} else if (*is_byte_order_be) {
				memset(buf_uint, 0, size_buf_uint - sizeof(_Uint_Ty));
				memcpy(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(buf_uint) + (size_buf_uint - sizeof(_Uint_Ty))), reinterpret_cast<const void*>(&uint), sizeof(_Uint_Ty));
				return nullptr;
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			}
		} else {
			size_t size_needed_uint = (sizeof(_Uint_Ty) - count_leading_zero<_Uint_Ty>(uint) - 1) / 0x8 + 1;
			if (size_buf_uint >= size_needed_uint) {
				if (*is_byte_order_le) {
					memcpy(buf_uint, reinterpret_cast<const void*>(&uint), size_needed_uint);
					memset(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(buf_uint) + size_needed_uint), 0, size_buf_uint - size_needed_uint);
					return nullptr;
				} else if (*is_byte_order_be) {
					memset(buf_uint, 0, size_buf_uint - size_needed_uint);
					memcpy(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(buf_uint) + (size_buf_uint - size_needed_uint)), reinterpret_cast<const void*>(&uint), size_needed_uint);
					return nullptr;
				} else {
					return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
				}
			} else {
				return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_NOCLASS(::YBWLib2::GenericUintToLarge);
			}
		}
	}
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IFile</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class File abstract
		: public virtual ReferenceCountedObject,
		public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(File, , "43f3461f-7fca-4849-9424-475122dd18c4");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(File);
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
		[[nodiscard]] virtual IException* GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) const noexcept override = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~File() = default;
	};

	/// <summary>
	/// A default implementation of <c>ISizedFile</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISizedFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class SizedFile abstract
		: public virtual File,
		public virtual ISizedFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(SizedFile, , "f81fe56f-74e1-4aac-b57c-9635a030f898");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(SizedFile);
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSize(size_t* size_ret) const noexcept override = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSize(size_t size) noexcept override = 0;
		/// <summary>Gets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that receives the current file size (in <c>uint8_t</c>s).
		/// The file size will be stored in machine byte order.
		/// </param>
		/// <param name="size_buf_size">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSizeLarge(void* buf_size, size_t size_buf_size) const noexcept override = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that specifies the new file size (in <c>uint8_t</c>s).
		/// The file size must be stored in machine byte order.
		/// If the new file size is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_size">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSizeLarge(const void* buf_size, size_t size_buf_size) noexcept override = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~SizedFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// A default implementation of <c>ISeekableFile</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISeekableFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class SeekableFile abstract
		: public virtual File,
		public virtual ISeekableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(SeekableFile, , "7848b484-524e-4efd-9ce1-e5424ec71a93");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(SeekableFile);
		inline SeekableFile() noexcept : lock_position_file() {}
		inline SeekableFile(const SeekableFile& x) noexcept : lock_position_file() {
			static_cast<void>(x);
		}
		inline SeekableFile(SeekableFile&& x) noexcept : lock_position_file() {
			static_cast<void>(x);
		}
		inline SeekableFile& operator=(const SeekableFile& x) noexcept {
			static_cast<void>(x);
		}
		inline SeekableFile& operator=(SeekableFile&& x) noexcept {
			static_cast<void>(x);
		}
		/// <summary>
		/// Returns a pointer to the <c>ILockableObject</c> object that locks the file position.
		/// The object on which this member function is called, instead of the caller, owns the object pointed to by the returned pointer.
		/// The <c>ILockableObject</c> object shall be declared <c>mutable</c>.
		/// The duration of the <c>ILockableObject</c> object shall extend at least until the destruction of this object.
		/// </summary>
		inline virtual ILockableObject* GetFilePositionLock() const noexcept override { return &this->lock_position_file; }
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* IsEof(bool* is_eof_ret) const noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekFromBegin(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekFromEnd(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekForward(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekBackward(size_t distance) noexcept override = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* Tell(size_t* distance_ret) const noexcept override = 0;
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the start of the file and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromBeginLarge(const void* buf_distance, size_t size_buf_distance) noexcept override = 0;
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the end of file.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromEndLarge(const void* buf_distance, size_t size_buf_distance) noexcept override = 0;
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the current position and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekForwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override = 0;
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the current position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekBackwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// The distance will be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <param name="size_buf_distance">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* TellLarge(void* buf_distance, size_t size_buf_distance) const noexcept override = 0;
	protected:
		mutable LockableObjectFromSTLWrapper<::std::recursive_mutex> lock_position_file;
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~SeekableFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// A default implementation of <c>IReadableFile</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IReadableFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class ReadableFile abstract
		: public virtual File,
		public virtual IReadableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ReadableFile, , "e3a04ee9-ecc0-440c-b106-2e23d52ec27f");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ReadableFile);
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
		[[nodiscard]] virtual IException* Read(void* buf, size_t size_buf) noexcept override = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~ReadableFile() = default;
	};

	/// <summary>
	/// A default implementation of <c>IWriteableFile</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IWriteableFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class WriteableFile abstract
		: public virtual File,
		public virtual IWriteableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(WriteableFile, , "fed17616-b3d8-4dce-bf77-2c088e661cda");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(WriteableFile);
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
		[[nodiscard]] virtual IException* Write(const void* buf, size_t size_buf) noexcept override = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~WriteableFile() = default;
	};

	/// <summary>
	/// An implementation of <c>ISizedFile</c> that has the file size always representable in <c>size_t</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISizedFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class SizetSizedFile abstract : public virtual SizedFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(SizetSizedFile, , "6b6ea58d-56b5-47de-be5a-608e64fdf34e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(SizetSizedFile);
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSize(size_t* size_ret) const noexcept override = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSize(size_t size) noexcept override = 0;
		/// <summary>Gets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that receives the current file size (in <c>uint8_t</c>s).
		/// The file size will be stored in machine byte order.
		/// </param>
		/// <param name="size_buf_size">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetFileSizeLarge(void* buf_size, size_t size_buf_size) const noexcept override {
			size_t size = 0;
			IException* err_inner = this->GetFileSize(&size);
			if (err_inner) return err_inner;
			err_inner = GenericUintToLarge<size_t>(size, buf_size, size_buf_size);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSizedFile, GetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSizedFile, GetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return nullptr;
		}
		/// <summary>Sets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that specifies the new file size (in <c>uint8_t</c>s).
		/// The file size must be stored in machine byte order.
		/// If the new file size is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_size">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SetFileSizeLarge(const void* buf_size, size_t size_buf_size) noexcept override {
			size_t size = 0;
			IException* err_inner = GenericUintFromLarge<size_t>(&size, buf_size, size_buf_size);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSizedFile, SetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSizedFile, SetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SetFileSize(size);
		}
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~SizetSizedFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// An implementation of <c>ISeekableFile</c> that has the file position always representable in <c>size_t</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISeekableFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class SizetSeekableFile abstract : public virtual SeekableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(SizetSeekableFile, , "2fed556f-96f6-4c58-a069-357c866c0676");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(SizetSeekableFile);
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* IsEof(bool* is_eof_ret) const noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekFromBegin(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekFromEnd(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekForward(size_t distance) noexcept override = 0;
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
		[[nodiscard]] virtual IException* SeekBackward(size_t distance) noexcept override = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* Tell(size_t* distance_ret) const noexcept override = 0;
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the start of the file and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromBeginLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			size_t distance = 0;
			IException* err_inner = GenericUintFromLarge<size_t>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekFromBeginLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekFromBeginLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekFromBegin(distance);
		}
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the end of file.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromEndLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			size_t distance = 0;
			IException* err_inner = GenericUintFromLarge<size_t>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekFromEndLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekFromEndLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekFromEnd(distance);
		}
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the current position and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekForwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			size_t distance = 0;
			IException* err_inner = GenericUintFromLarge<size_t>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekForwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekForwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekForward(distance);
		}
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the current position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekBackwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			size_t distance = 0;
			IException* err_inner = GenericUintFromLarge<size_t>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekBackwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, SeekBackwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekBackward(distance);
		}
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// The distance will be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <param name="size_buf_distance">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* TellLarge(void* buf_distance, size_t size_buf_distance) const noexcept override {
			size_t distance = 0;
			IException* err_inner = this->Tell(&distance);
			if (err_inner) return err_inner;
			err_inner = GenericUintToLarge<size_t>(distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, TellLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SizetSeekableFile, TellLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return nullptr;
		}
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~SizetSeekableFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// An implementation of <c>ISizedFile</c> that has the file size always representable in <c>unsigned long long</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISizedFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class ULongLongSizedFile abstract : public virtual SizedFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ULongLongSizedFile, , "34869489-e20a-4e02-b0b0-15d3c69cad8c");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ULongLongSizedFile);
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetFileSize(size_t* size_ret) const noexcept override {
			if (!size_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSize);
			if constexpr (::std::is_same_v<size_t, unsigned long long>) {
				return this->GetFileSizeULongLong(reinterpret_cast<unsigned long long*>(size_ret));
			} else if constexpr (sizeof(size_t) == sizeof(unsigned long long)) if (*is_byte_order_le || *is_byte_order_be) {
				return this->GetFileSizeULongLong(reinterpret_cast<unsigned long long*>(size_ret));
			}
			unsigned long long ulonglong_size = 0;
			IException* err_inner = this->GetFileSizeULongLong(&ulonglong_size);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSize);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSize);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			if constexpr (sizeof(size_t) < sizeof(unsigned long long))
				if (ulonglong_size > SIZE_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSize);
			*size_ret = ulonglong_size & ~(size_t)0;
			return nullptr;
		}
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SetFileSize(size_t size) noexcept override {
			if constexpr (sizeof(size_t) <= sizeof(unsigned long long)) {
				return this->SetFileSizeULongLong(size);
			} else {
				if (size > ULLONG_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, SetFileSize);
				unsigned long long ulonglong_size = size & ~(unsigned long long)0;
				return this->SetFileSizeULongLong(ulonglong_size);
			}
		}
		/// <summary>Gets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that receives the current file size (in <c>uint8_t</c>s).
		/// The file size will be stored in machine byte order.
		/// </param>
		/// <param name="size_buf_size">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetFileSizeLarge(void* buf_size, size_t size_buf_size) const noexcept override {
			unsigned long long size = 0;
			IException* err_inner = this->GetFileSizeULongLong(&size);
			if (err_inner) return err_inner;
			err_inner = GenericUintToLarge<unsigned long long>(size, buf_size, size_buf_size);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, GetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return nullptr;
		}
		/// <summary>Sets the size of the file.</summary>
		/// <param name="buf_size">
		/// An unsigned integer buffer that specifies the new file size (in <c>uint8_t</c>s).
		/// The file size must be stored in machine byte order.
		/// If the new file size is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_size">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_size</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SetFileSizeLarge(const void* buf_size, size_t size_buf_size) noexcept override {
			unsigned long long size = 0;
			IException* err_inner = GenericUintFromLarge<unsigned long long>(&size, buf_size, size_buf_size);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, SetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSizedFile, SetFileSizeLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SetFileSizeULongLong(size);
		}
		/// <summary>Gets the size of the file.</summary>
		/// <param name="size_ret">A pointer to a variable that receives the current file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetFileSizeULongLong(unsigned long long* size_ret) const noexcept = 0;
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetFileSizeULongLong(unsigned long long size) noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~ULongLongSizedFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// An implementation of <c>ISeekableFile</c> that has the file position always representable in <c>unsigned long long</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>ISeekableFile</c>.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class ULongLongSeekableFile abstract : public virtual SeekableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ULongLongSeekableFile, , "6ea5ca33-fbc5-4369-9626-e1c94d8b51ff");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ULongLongSeekableFile);
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* IsEof(bool* is_eof_ret) const noexcept override = 0;
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
		[[nodiscard]] inline virtual IException* SeekFromBegin(size_t distance) noexcept override {
			if constexpr (sizeof(size_t) <= sizeof(unsigned long long)) {
				return this->SeekFromBeginULongLong(distance);
			} else {
				if (distance > ULLONG_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromBegin);
				unsigned long long ulonglong_distance = distance & ~(unsigned long long)0;
				return this->SeekFromBeginULongLong(ulonglong_distance);
			}
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
		[[nodiscard]] inline virtual IException* SeekFromEnd(size_t distance) noexcept override {
			if constexpr (sizeof(size_t) <= sizeof(unsigned long long)) {
				return this->SeekFromEndULongLong(distance);
			} else {
				if (distance > ULLONG_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromEnd);
				unsigned long long ulonglong_distance = distance & ~(unsigned long long)0;
				return this->SeekFromEndULongLong(ulonglong_distance);
			}
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
		[[nodiscard]] inline virtual IException* SeekForward(size_t distance) noexcept override {
			if constexpr (sizeof(size_t) <= sizeof(unsigned long long)) {
				return this->SeekForwardULongLong(distance);
			} else {
				if (distance > ULLONG_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekForward);
				unsigned long long ulonglong_distance = distance & ~(unsigned long long)0;
				return this->SeekForwardULongLong(ulonglong_distance);
			}
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
		[[nodiscard]] inline virtual IException* SeekBackward(size_t distance) noexcept override {
			if constexpr (sizeof(size_t) <= sizeof(unsigned long long)) {
				return this->SeekBackwardULongLong(distance);
			} else {
				if (distance > ULLONG_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekBackward);
				unsigned long long ulonglong_distance = distance & ~(unsigned long long)0;
				return this->SeekBackwardULongLong(ulonglong_distance);
			}
		}
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* Tell(size_t* distance_ret) const noexcept override {
			if (!distance_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, Tell);
			if constexpr (::std::is_same_v<size_t, unsigned long long>) {
				return this->TellULongLong(reinterpret_cast<unsigned long long*>(distance_ret));
			} else if constexpr (sizeof(size_t) == sizeof(unsigned long long)) if (*is_byte_order_le || *is_byte_order_be) {
				return this->TellULongLong(reinterpret_cast<unsigned long long*>(distance_ret));
			}
			unsigned long long ulonglong_distance = 0;
			IException* err_inner = this->TellULongLong(&ulonglong_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, Tell);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, Tell);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			if constexpr (sizeof(size_t) < sizeof(unsigned long long))
				if (ulonglong_distance > SIZE_MAX) return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, Tell);
			*distance_ret = ulonglong_distance & ~(size_t)0;
			return nullptr;
		}
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the start of the file and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromBeginLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			unsigned long long distance = 0;
			IException* err_inner = GenericUintFromLarge<unsigned long long>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromBeginLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromBeginLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekFromBeginULongLong(distance);
		}
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the end of file.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekFromEndLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			unsigned long long distance = 0;
			IException* err_inner = GenericUintFromLarge<unsigned long long>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromEndLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekFromEndLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekFromEndULongLong(distance);
		}
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the current position and the target position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekForwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			unsigned long long distance = 0;
			IException* err_inner = GenericUintFromLarge<unsigned long long>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekForwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekForwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekForwardULongLong(distance);
		}
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that specifies the distance (in <c>uint8_t</c>s) between the target position and the current position.
		/// The distance must be stored in machine byte order.
		/// A distance of <c>0</c> specifies the current position.
		/// If the distance is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_distance">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SeekBackwardLarge(const void* buf_distance, size_t size_buf_distance) noexcept override {
			unsigned long long distance = 0;
			IException* err_inner = GenericUintFromLarge<unsigned long long>(&distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekBackwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, SeekBackwardLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
			}
			return this->SeekBackwardULongLong(distance);
		}
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="buf_distance">
		/// An unsigned integer buffer that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// The distance will be stored in machine byte order.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <param name="size_buf_distance">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_distance</c>.
		/// If the buffer is insufficient to contain the current file size, the function call will fail.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* TellLarge(void* buf_distance, size_t size_buf_distance) const noexcept override {
			unsigned long long distance = 0;
			IException* err_inner = this->TellULongLong(&distance);
			if (err_inner) return err_inner;
			err_inner = GenericUintToLarge<unsigned long long>(distance, buf_distance, size_buf_distance);
			if (err_inner) {
				if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, TellLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
					IException* err = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ULongLongSeekableFile, TellLarge);
					err->AttachCause(err_inner);
					err_inner = nullptr;
					return err;
				} else {
					return err_inner;
				}
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
		[[nodiscard]] virtual IException* SeekFromBeginULongLong(unsigned long long distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekFromEndULongLong(unsigned long long distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekForwardULongLong(unsigned long long distance) noexcept = 0;
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
		[[nodiscard]] virtual IException* SeekBackwardULongLong(unsigned long long distance) noexcept = 0;
		/// <summary>Gets the distance between the start of the file and the current position.</summary>
		/// <param name="distance_ret">
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* TellULongLong(unsigned long long* distance_ret) const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~ULongLongSeekableFile() = default;
	};
	static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");

	/// <summary>
	/// An implementation of <c>IFile</c>, <c>IReadableFile</c>, <c>IWriteableFile</c>, <c>ISizedFile</c> and <c>ISeekableFile</c> that operates on a memory area.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by the interface classes.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class MemoryFile
		: public virtual SizetSizedFile,
		public virtual SizetSeekableFile,
		public virtual ReadableFile,
		public virtual WriteableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(MemoryFile, , "ce0268fb-69ab-4838-be0e-7b4f7f453f9a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(MemoryFile);
		typedef void(YBWLIB2_CALLTYPE* fnptr_release_view_t)(uintptr_t context, void* address_memory_block, size_t size_memory_block) noexcept;
		typedef void(YBWLIB2_CALLTYPE* fnptr_release_view_readonly_t)(uintptr_t context, const void* address_memory_block, size_t size_memory_block) noexcept;
		struct view_memory_t {};
		struct view_memory_readonly_t {};
		struct allocate_memory_t {};
		struct adopt_allocated_memory_t {};
		static constexpr view_memory_t view_memory {};
		static constexpr view_memory_readonly_t view_memory_readonly {};
		static constexpr allocate_memory_t allocate_memory {};
		static constexpr adopt_allocated_memory_t adopt_allocated_memory {};
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline MemoryFile(
			view_memory_t,
			void* _address_memory_block,
			size_t _size_memory_block,
			fnptr_release_view_t _fnptr_release_view = nullptr,
			uintptr_t _context = 0
		) noexcept(false)
			: objholder_holder_memory_block(new MemoryBlockHolder(view_memory, _address_memory_block, _size_memory_block, _fnptr_release_view, _context), ReferenceCountedObjectHolder<MemoryBlockHolder>::adopt_ref_count) {}
		inline MemoryFile(
			view_memory_readonly_t,
			const void* _address_memory_block,
			size_t _size_memory_block,
			fnptr_release_view_readonly_t _fnptr_release_view = nullptr,
			uintptr_t _context = 0
		) noexcept(false)
			: objholder_holder_memory_block(new MemoryBlockHolder(view_memory_readonly, _address_memory_block, _size_memory_block, _fnptr_release_view, _context), ReferenceCountedObjectHolder<MemoryBlockHolder>::adopt_ref_count) {}
		inline MemoryFile(allocate_memory_t, const rawallocator_t* _rawallocator, size_t _size_memory_block_initial) noexcept(false)
			: objholder_holder_memory_block(new MemoryBlockHolder(allocate_memory, _rawallocator, _size_memory_block_initial), ReferenceCountedObjectHolder<MemoryBlockHolder>::adopt_ref_count) {}
		inline MemoryFile(adopt_allocated_memory_t, const rawallocator_t* _rawallocator, void* _address_memory_block, size_t _size_memory_block_initial) noexcept(false)
			: objholder_holder_memory_block(new MemoryBlockHolder(adopt_allocated_memory, _rawallocator, _address_memory_block, _size_memory_block_initial), ReferenceCountedObjectHolder<MemoryBlockHolder>::adopt_ref_count) {}
		inline MemoryFile(const MemoryFile& x) noexcept(false)
			: IReferenceCountedObject(static_cast<const IReferenceCountedObject&>(x)),
			ReferenceCountedObject(static_cast<const ReferenceCountedObject&>(x)),
			File(static_cast<const File&>(x)),
			ISizedFile(static_cast<const ISizedFile&>(x)),
			ISeekableFile(static_cast<const ISeekableFile&>(x)),
			IReadableFile(static_cast<const IReadableFile&>(x)),
			IWriteableFile(static_cast<const IWriteableFile&>(x)),
			SizedFile(static_cast<const SizedFile&>(x)),
			SeekableFile(static_cast<const SeekableFile&>(x)),
			SizetSizedFile(static_cast<const SizetSizedFile&>(x)),
			SizetSeekableFile(static_cast<const SizetSeekableFile&>(x)),
			ReadableFile(static_cast<const ReadableFile&>(x)),
			WriteableFile(static_cast<const WriteableFile&>(x)) {
				{
					LockableObjectToSTLWrapper wrapper_lock_position_file_x(*x.GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file_x(wrapper_lock_position_file_x);
					LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block_x(x.lock_objholder_holder_memory_block);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block_x(wrapper_lock_objholder_holder_memory_block_x);
					this->objholder_holder_memory_block = x.objholder_holder_memory_block;
					this->position_file = x.position_file;
				}
		}
		inline MemoryFile(MemoryFile&& x) noexcept(false)
			: IReferenceCountedObject(static_cast<IReferenceCountedObject&&>(::std::move(x))),
			ReferenceCountedObject(static_cast<ReferenceCountedObject&&>(::std::move(x))),
			File(static_cast<File&&>(::std::move(x))),
			ISizedFile(static_cast<ISizedFile&&>(::std::move(x))),
			ISeekableFile(static_cast<ISeekableFile&&>(::std::move(x))),
			IReadableFile(static_cast<IReadableFile&&>(::std::move(x))),
			IWriteableFile(static_cast<IWriteableFile&&>(::std::move(x))),
			SizedFile(static_cast<SizedFile&&>(::std::move(x))),
			SeekableFile(static_cast<SeekableFile&&>(::std::move(x))),
			SizetSizedFile(static_cast<SizetSizedFile&&>(::std::move(x))),
			SizetSeekableFile(static_cast<SizetSeekableFile&&>(::std::move(x))),
			ReadableFile(static_cast<ReadableFile&&>(::std::move(x))),
			WriteableFile(static_cast<WriteableFile&&>(::std::move(x))) {
				{
					LockableObjectToSTLWrapper wrapper_lock_position_file_x(*x.GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file_x(wrapper_lock_position_file_x);
					LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block_x(x.lock_objholder_holder_memory_block);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block_x(wrapper_lock_objholder_holder_memory_block_x);
					this->objholder_holder_memory_block = ::std::move(x.objholder_holder_memory_block);
					this->position_file = ::std::move(x.position_file);
					x.position_file = 0;
				}
		}
		inline MemoryFile& operator=(const MemoryFile& x) noexcept(false) {
			static_cast<IReferenceCountedObject&>(*this) = static_cast<const IReferenceCountedObject&>(x);
			static_cast<ReferenceCountedObject&>(*this) = static_cast<const ReferenceCountedObject&>(x);
			static_cast<File&>(*this) = static_cast<const File&>(x);
			static_cast<ISizedFile&>(*this) = static_cast<const ISizedFile&>(x);
			static_cast<ISeekableFile&>(*this) = static_cast<const ISeekableFile&>(x);
			static_cast<IReadableFile&>(*this) = static_cast<const IReadableFile&>(x);
			static_cast<IWriteableFile&>(*this) = static_cast<const IWriteableFile&>(x);
			static_cast<SizedFile&>(*this) = static_cast<const SizedFile&>(x);
			static_cast<SeekableFile&>(*this) = static_cast<const SeekableFile&>(x);
			static_cast<SizetSizedFile&>(*this) = static_cast<const SizetSizedFile&>(x);
			static_cast<SizetSeekableFile&>(*this) = static_cast<const SizetSeekableFile&>(x);
			static_cast<ReadableFile&>(*this) = static_cast<const ReadableFile&>(x);
			static_cast<WriteableFile&>(*this) = static_cast<const WriteableFile&>(x);
			{
				LockableObjectToSTLWrapper wrapper_lock_position_file_x(*x.GetFilePositionLock());
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file_x(wrapper_lock_position_file_x);
				LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block_x(x.lock_objholder_holder_memory_block);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block_x(wrapper_lock_objholder_holder_memory_block_x);
				this->objholder_holder_memory_block = x.objholder_holder_memory_block;
				this->position_file = x.position_file;
			}
		}
		inline MemoryFile& operator=(MemoryFile&& x) noexcept(false) {
			static_cast<IReferenceCountedObject&>(*this) = static_cast<IReferenceCountedObject&&>(::std::move(x));
			static_cast<ReferenceCountedObject&>(*this) = static_cast<ReferenceCountedObject&&>(::std::move(x));
			static_cast<File&>(*this) = static_cast<File&&>(::std::move(x));
			static_cast<ISizedFile&>(*this) = static_cast<ISizedFile&&>(::std::move(x));
			static_cast<ISeekableFile&>(*this) = static_cast<ISeekableFile&&>(::std::move(x));
			static_cast<IReadableFile&>(*this) = static_cast<IReadableFile&&>(::std::move(x));
			static_cast<IWriteableFile&>(*this) = static_cast<IWriteableFile&&>(::std::move(x));
			static_cast<SizedFile&>(*this) = static_cast<SizedFile&&>(::std::move(x));
			static_cast<SeekableFile&>(*this) = static_cast<SeekableFile&&>(::std::move(x));
			static_cast<SizetSizedFile&>(*this) = static_cast<SizetSizedFile&&>(::std::move(x));
			static_cast<SizetSeekableFile&>(*this) = static_cast<SizetSeekableFile&&>(::std::move(x));
			static_cast<ReadableFile&>(*this) = static_cast<ReadableFile&&>(::std::move(x));
			static_cast<WriteableFile&>(*this) = static_cast<WriteableFile&&>(::std::move(x));
			{
				LockableObjectToSTLWrapper wrapper_lock_position_file_x(*x.GetFilePositionLock());
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file_x(wrapper_lock_position_file_x);
				LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block_x(x.lock_objholder_holder_memory_block);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block_x(wrapper_lock_objholder_holder_memory_block_x);
				this->objholder_holder_memory_block = ::std::move(x.objholder_holder_memory_block);
				this->position_file = ::std::move(x.position_file);
				x.position_file = 0;
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
		[[nodiscard]] inline virtual IException* GetFileSize(size_t* size_ret) const noexcept override {
			if (!size_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, GetFileSize);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &size_ret, &err_inner]() noexcept(false)->void {
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
							*size_ret = holder_memory_block->size_memory_block;
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
		/// <summary>Sets the size of the file.</summary>
		/// <param name="size">The new file size (in <c>uint8_t</c>s).</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* SetFileSize(size_t size) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &size, &err_inner]() noexcept(false)->void {
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
							if (size != holder_memory_block->size_memory_block) {
								if (holder_memory_block->is_readonly || !holder_memory_block->rawallocator) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::MemoryFile, SetFileSize); return; }
								holder_memory_block->address_memory_block = holder_memory_block->rawallocator->Reallocate(holder_memory_block->address_memory_block, holder_memory_block->size_memory_block, size);
								if (!holder_memory_block->address_memory_block) {
									holder_memory_block->size_memory_block = 0;
									{ err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
								}
								holder_memory_block->size_memory_block = size;
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
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <param name="is_eof_ret">Pointer to a variable that receives whether the current position is beyond the last byte of the file.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* IsEof(bool* is_eof_ret) const noexcept override {
			if (!is_eof_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, IsEof);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &is_eof_ret, &err_inner]() noexcept(false)->void {
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
							*is_eof_ret = this->position_file >= holder_memory_block->size_memory_block;
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
		[[nodiscard]] inline virtual IException* SeekFromBegin(size_t distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					this->position_file = distance;
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
		[[nodiscard]] inline virtual IException* SeekFromEnd(size_t distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
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
							if (distance > holder_memory_block->size_memory_block) { err_inner = new BofFileException(this); return; }
							this->position_file = holder_memory_block->size_memory_block - distance;
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
		[[nodiscard]] inline virtual IException* SeekForward(size_t distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					if (distance > SIZE_MAX - this->position_file) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, SeekForward); return; }
					this->position_file = this->position_file + distance;
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
		[[nodiscard]] inline virtual IException* SeekBackward(size_t distance) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					if (distance > this->position_file) { err_inner = new BofFileException(this); return; }
					this->position_file = this->position_file - distance;
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
		/// A pointer to a variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] inline virtual IException* Tell(size_t* distance_ret) const noexcept override {
			if (!distance_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Tell);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &distance_ret, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					*distance_ret = this->position_file;
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
			if (!buf) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Read);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &buf, &size_buf, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					if (size_buf > SIZE_MAX - this->position_file) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Read); return; }
					LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block(this->lock_objholder_holder_memory_block);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block(wrapper_lock_objholder_holder_memory_block);
					{
						MemoryBlockHolder* holder_memory_block = this->objholder_holder_memory_block.get();
						if (!holder_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						LockableObjectToSTLWrapper wrapper_lock_memory_block_holder(holder_memory_block->lock_memory_block_holder);
						::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder(wrapper_lock_memory_block_holder);
						{
							if (this->position_file + size_buf > holder_memory_block->size_memory_block) { err_inner = new EofFileException(this); return; }
							if (holder_memory_block->is_readonly) {
								if (!holder_memory_block->address_memory_block_readonly) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Read); return; }
								memcpy(buf, reinterpret_cast<const void*>(reinterpret_cast<const uint8_t*>(holder_memory_block->address_memory_block_readonly) + this->position_file), size_buf);
							} else {
								if (!holder_memory_block->address_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Read); return; }
								memcpy(buf, reinterpret_cast<const void*>(reinterpret_cast<const uint8_t*>(holder_memory_block->address_memory_block) + this->position_file), size_buf);
							}
							this->position_file += size_buf;
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
			if (!buf) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Write);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &buf, &size_buf, &err_inner]() noexcept(false)->void {
					LockableObjectToSTLWrapper wrapper_lock_position_file(*this->GetFilePositionLock());
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_position_file(wrapper_lock_position_file);
					if (size_buf > SIZE_MAX - this->position_file) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Write); return; }
					LockableObjectToSTLWrapper wrapper_lock_objholder_holder_memory_block(this->lock_objholder_holder_memory_block);
					::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_objholder_holder_memory_block(wrapper_lock_objholder_holder_memory_block);
					{
						MemoryBlockHolder* holder_memory_block = this->objholder_holder_memory_block.get();
						if (!holder_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						LockableObjectToSTLWrapper wrapper_lock_memory_block_holder(holder_memory_block->lock_memory_block_holder);
						::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder(wrapper_lock_memory_block_holder);
						{
							if (holder_memory_block->is_readonly || !holder_memory_block->address_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Write); return; }
							if (this->position_file + size_buf > holder_memory_block->size_memory_block) {
								err_inner = this->SetFileSize(this->position_file + size_buf);
								if (err_inner) {
									if (DynamicTypeCanCast<IInvalidParameterException, IException>(err_inner)) {
										IException* err_consequence = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile, Write);
										err_consequence->AttachCause(err_inner);
										err_inner = err_consequence;
										return;
									} else if (DynamicTypeCanCast<IInvalidCallException, IException>(err_inner)) {
										IException* err_consequence = new EofFileException(this);
										err_consequence->AttachCause(err_inner);
										err_inner = err_consequence;
										return;
									} else {
										return;
									}
								}
							}
							if (!holder_memory_block->address_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
							if (this->position_file + size_buf > holder_memory_block->size_memory_block) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
							memcpy(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(holder_memory_block->address_memory_block) + this->position_file), buf, size_buf);
							this->position_file += size_buf;
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
	protected:
		/// <summary>
		/// Reference counted memory block holder.
		/// Has a reference count of <c>1</c> when constructed.
		/// </summary>
		class MemoryBlockHolder final : public virtual ReferenceCountedObject {
		public:
			mutable LockableObjectFromSTLWrapper<::std::recursive_mutex> lock_memory_block_holder;
			union {
				void* address_memory_block = nullptr;
				const void* address_memory_block_readonly;
			};
			size_t size_memory_block = 0;
			bool is_readonly = false;
			const rawallocator_t* rawallocator = nullptr;
			union {
				fnptr_release_view_t fnptr_release_view = nullptr;
				fnptr_release_view_readonly_t fnptr_release_view_readonly;
			};
			uintptr_t context = 0;
			inline MemoryBlockHolder(
				view_memory_t,
				void* _address_memory_block,
				size_t _size_memory_block,
				fnptr_release_view_t _fnptr_release_view = nullptr,
				uintptr_t _context = 0
			) noexcept(false)
				: address_memory_block(_address_memory_block),
				size_memory_block(_size_memory_block),
				rawallocator(nullptr),
				fnptr_release_view(_fnptr_release_view),
				context(_context) {
				if (!this->address_memory_block && this->size_memory_block)
					throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile::MemoryBlockHolder, MemoryBlockHolder));
			}
			inline MemoryBlockHolder(
				view_memory_readonly_t,
				const void* _address_memory_block,
				size_t _size_memory_block,
				fnptr_release_view_readonly_t _fnptr_release_view = nullptr,
				uintptr_t _context = 0
			) noexcept(false)
				: address_memory_block_readonly(_address_memory_block),
				size_memory_block(_size_memory_block),
				is_readonly(true),
				rawallocator(nullptr),
				fnptr_release_view_readonly(_fnptr_release_view),
				context(_context) {
				if (!this->address_memory_block_readonly && this->size_memory_block)
					throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile::MemoryBlockHolder, MemoryBlockHolder));
			}
			inline MemoryBlockHolder(allocate_memory_t, const rawallocator_t* _rawallocator, size_t _size_memory_block_initial) noexcept(false)
				: rawallocator(_rawallocator) {
				this->size_memory_block = _size_memory_block_initial;
				this->address_memory_block = this->rawallocator->Allocate(this->size_memory_block);
				if (!this->address_memory_block) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			}
			inline MemoryBlockHolder(adopt_allocated_memory_t, const rawallocator_t* _rawallocator, void* _address_memory_block, size_t _size_memory_block_initial) noexcept(false)
				: address_memory_block(_address_memory_block), size_memory_block(_size_memory_block_initial), rawallocator(_rawallocator) {
				if (!this->address_memory_block && this->size_memory_block)
					throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::MemoryFile::MemoryBlockHolder, MemoryBlockHolder));
			}
			MemoryBlockHolder(const MemoryBlockHolder&) = delete;
			inline MemoryBlockHolder(MemoryBlockHolder&& x) noexcept(false)
				: ReferenceCountedObject(),
				lock_memory_block_holder() {
				LockableObjectToSTLWrapper wrapper_lock_memory_block_holder_this(this->lock_memory_block_holder);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder_this(wrapper_lock_memory_block_holder_this);
				LockableObjectToSTLWrapper wrapper_lock_memory_block_holder_x(x.lock_memory_block_holder);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder_x(wrapper_lock_memory_block_holder_x);
				this->is_readonly = ::std::move(x.is_readonly);
				if (this->is_readonly) {
					this->address_memory_block_readonly = ::std::move(x.address_memory_block_readonly);
					x.address_memory_block_readonly = nullptr;
				} else {
					this->address_memory_block = ::std::move(x.address_memory_block);
					x.address_memory_block = nullptr;
				}
				this->size_memory_block = ::std::move(x.size_memory_block);
				x.size_memory_block = 0;
				this->rawallocator = ::std::move(x.rawallocator);
				x.rawallocator = nullptr;
				this->fnptr_release_view = ::std::move(x.fnptr_release_view);
				x.fnptr_release_view = nullptr;
				this->context = ::std::move(x.context);
				x.context = 0;
			}
			MemoryBlockHolder& operator=(const MemoryBlockHolder&) = delete;
			inline MemoryBlockHolder& operator=(MemoryBlockHolder&& x) noexcept(false) {
				LockableObjectToSTLWrapper wrapper_lock_memory_block_holder_this(this->lock_memory_block_holder);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder_this(wrapper_lock_memory_block_holder_this);
				LockableObjectToSTLWrapper wrapper_lock_memory_block_holder_x(x.lock_memory_block_holder);
				::std::unique_lock<LockableObjectToSTLWrapper> unique_lock_memory_block_holder_x(wrapper_lock_memory_block_holder_x);
				this->is_readonly = ::std::move(x.is_readonly);
				if (this->is_readonly) {
					this->address_memory_block_readonly = ::std::move(x.address_memory_block_readonly);
					x.address_memory_block_readonly = nullptr;
				} else {
					this->address_memory_block = ::std::move(x.address_memory_block);
					x.address_memory_block = nullptr;
				}
				this->size_memory_block = ::std::move(x.size_memory_block);
				x.size_memory_block = 0;
				this->rawallocator = ::std::move(x.rawallocator);
				x.rawallocator = nullptr;
				this->fnptr_release_view = ::std::move(x.fnptr_release_view);
				x.fnptr_release_view = nullptr;
				this->context = ::std::move(x.context);
				x.context = 0;
			}
		protected:
			/// <summary>
			/// Destructor intentionally declared protected.
			/// Object users should use the reference counting mechanism instead.
			/// </summary>
			virtual ~MemoryBlockHolder() {
				if (this->is_readonly) {
					if (this->address_memory_block_readonly) {
						if (this->fnptr_release_view_readonly)
							(*this->fnptr_release_view_readonly)(this->context, this->address_memory_block_readonly, this->size_memory_block);
						this->address_memory_block_readonly = nullptr;
					}
				} else {
					if (this->address_memory_block) {
						if (this->fnptr_release_view)
							(*this->fnptr_release_view)(this->context, this->address_memory_block, this->size_memory_block);
						if (this->rawallocator)
							this->rawallocator->Deallocate(this->address_memory_block, this->size_memory_block);
						this->address_memory_block = nullptr;
					}
				}
				this->size_memory_block = 0;
				this->rawallocator = nullptr;
				this->fnptr_release_view = nullptr;
				this->context = 0;
			}
			/// <summary>
			/// Destructs the object and frees any resources allocated for the object.
			/// This function is intended to be called only by <c>DecReferenceCount</c>.
			/// </summary>
			inline virtual void DeleteMe() override {
				delete this;
			}
		};
		ReferenceCountedObjectHolder<MemoryBlockHolder> objholder_holder_memory_block;
		size_t position_file = 0;
		mutable LockableObjectFromSTLWrapper<::std::recursive_mutex> lock_objholder_holder_memory_block;
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~MemoryFile() = default;
		/// <summary>
		/// Destructs the object and frees any resources allocated for the object.
		/// This function is intended to be called only by <c>DecReferenceCount</c>.
		/// </summary>
		inline virtual void DeleteMe() override {
			delete this;
		}
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	void YBWLIB2_CALLTYPE File_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE File_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE File_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE File_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE FileUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_16A4E3E0_92C7_4B6F_994C_A8CA0D9314BE
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_16A4E3E0_92C7_4B6F_994C_A8CA0D9314BE
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#endif
