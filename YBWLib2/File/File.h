#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD
#define _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD

#include <cstdint>
#include <type_traits>
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"

namespace YBWLib2 {
	class IFileException;
	class IBofFileException;
	class FileException;
	class BofFileException;
	class IFile;
	class IFileWithSize;
	class ISeekableFile;
	class IInputFile;
	class IOutputFile;

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
		virtual IFile* GetFile() const noexcept = 0;
	};

	/// <summary>An exception that occurs because the file position is attempted to be set beyond the start of the file.</summary>
	class IBofFileException abstract : public virtual IFileException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IBofFileException, YBWLIB2_API, "71f26d51-6f27-49de-99ab-8142c5c54f39");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IBofFileException);
		inline virtual ~IBofFileException() = default;
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
		inline FileException(IFile* _file) noexcept : holder_file(_file, ReferenceCountedObjectHolder<IFile>::inc_ref_count) {}
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
		inline virtual IFile* GetFile() const noexcept override { return this->holder_file.get(); }
	protected:
		ReferenceCountedObjectHolder<IFile> holder_file;
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
		inline BofFileException(IFile* _file) noexcept : FileException(_file) {}
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
		[[nodiscard]] virtual IException* GetDescription(const rawallocator_t* _rawallocator, char** description_ret, size_t* size_description_ret, bool should_null_terminate) noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IFile() = default;
	};

	/// <summary>A file that has a size.</summary>
	class IFileWithSize abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IFileWithSize, YBWLIB2_API, "d75b8ae6-87ec-4821-a40f-de450160a6bd");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IFileWithSize);
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
		virtual ~IFileWithSize() = default;
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
		/// A pointer variable that receives the distance (in <c>uint8_t</c>s) between the start of the file and the current position.
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

	/// <summary>A file for reading.</summary>
	class IInputFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IInputFile, YBWLIB2_API, "1bff7b77-8bcb-42a4-8ccf-bd5e297a351e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IInputFile);
		/// <summary>Reads from the current position to the buffer.</summary>
		/// <param name="buf">Pointer to the buffer.</param>
		/// <param name="size">The number of bytes to be read.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* Read(void* buf, size_t size_buf) const noexcept = 0;
	protected:
		/// <summary>
		/// Destructor intentionally declared protected.
		/// Object users should use the reference counting mechanism instead.
		/// </summary>
		virtual ~IInputFile() = default;
	};

	/// <summary>A file for writing.</summary>
	class IOutputFile abstract : public virtual IFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IOutputFile, YBWLIB2_API, "4d104398-ff0f-4a4c-934a-0cf1bbcfc4ce");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IOutputFile);
		/// <summary>Writes from the buffer to the current position.</summary>
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
		virtual ~IOutputFile() = default;
	};

	void YBWLIB2_CALLTYPE File_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE File_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE File_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE File_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE FileUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE FileUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#endif
