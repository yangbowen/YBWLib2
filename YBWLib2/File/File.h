#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD
#define _INCLUDE_GUARD_BE3FAB28_DF80_4A3C_B1F8_C82BB9C20BFD

#include <cstdint>
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
	/// <summary>A file that supports seeking.</summary>
	class ISeekableFile abstract : public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(ISeekableFile, YBWLIB2_API, "cfc42a4e-a1f6-4684-93d1-f27d998aafa4");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ISeekableFile);
		/// <summary>
		/// Returns a pointer to the <c>ILockableObject</c> object that locks the file position.
		/// The <c>ILockableObject</c> object shall be declared <c>mutable</c>.
		/// The duration of the <c>ILockableObject</c> object shall extend at least until the destruction of this object.
		/// </summary>
		virtual ILockableObject* GetFilePositionLock() const = 0;
		/// <summary>Seeks to the position with a specified distance after the start of file.</summary>
		/// <param name="distance">
		/// The distance between the start of the file and the target position.
		/// A distance of <c>0</c> specifies the start of file.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromBegin(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="distance">
		/// The distance between the target position and the end of file.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekFromEnd(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="distance">
		/// The distance between the current position and the target position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekForward(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="distance">
		/// The distance between the target position and the current position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SeekBackward(size_t distance) = 0;
		/// <summary>Checks whether the current position is beyond the last byte of the file.</summary>
		/// <returns>
		/// Returns <c>true</c> if the current position is beyond the last byte of the file.
		/// Returns <c>false</c> otherwise.
		/// </returns>
		virtual bool IsEof() const = 0;
	};

	/// <summary>A file for reading.</summary>
	class IInputFile abstract : public virtual ISeekableFile {
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
		[[nodiscard]] virtual IException* Read(void* buf, size_t size) = 0;
	};

	/// <summary>A file for writing.</summary>
	class IOutputFile abstract : public virtual ISeekableFile {
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
		[[nodiscard]] virtual IException* Write(void* buf, size_t size) = 0;
	};
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_BCC6CEB3_1BA0_4B01_B5A3_91415F2D524B
#endif
