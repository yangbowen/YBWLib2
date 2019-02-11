#pragma once
#include <cstdint>
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../DynamicType/DynamicType.h"

namespace YBWLib2 {
	/// <summary>A file that supports seeking.</summary>
	class ISeekableFile abstract : public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(ISeekableFile, YBWLIB2_API, "{FA943A6B-90B0-47DE-B84F-3E9750B53B01}");
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
		virtual void SeekFromBegin(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance before the end of file.</summary>
		/// <param name="distance">
		/// The distance between the target position and the end of file.
		/// A distance of <c>0</c> specifies the end of file (just after the last byte).
		/// </param>
		virtual void SeekFromEnd(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance after the current position.</summary>
		/// <param name="distance">
		/// The distance between the current position and the target position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		virtual void SeekForward(size_t distance) = 0;
		/// <summary>Seeks to the position with a specified distance before the current position.</summary>
		/// <param name="distance">
		/// The distance between the target position and the current position.
		/// A distance of <c>0</c> specifies the current position.
		/// </param>
		virtual void SeekBackward(size_t distance) = 0;
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
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(IInputFile, YBWLIB2_API, "{41977894-4378-4B81-8857-4157DCE52CAC}");
		/// <summary>Reads from the current position to the buffer.</summary>
		/// <param name="buf">Pointer to the buffer.</param>
		/// <param name="size">The number of bytes to be read.</param>
		virtual void Read(void* buf, size_t size) = 0;
	};

	/// <summary>A file for writing.</summary>
	class IOutputFile abstract : public virtual ISeekableFile {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS(IOutputFile, YBWLIB2_API, "{63E3E8AF-A2F1-4CDA-9B44-922E6B1C59BF}");
		/// <summary>Writes from the buffer to the current position.</summary>
		/// <param name="buf">Pointer to the buffer.</param>
		/// <param name="size">The number of bytes to be written.</param>
		virtual void Write(void* buf, size_t size) = 0;
	};
}
