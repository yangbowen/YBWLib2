#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISeekableFile, YBWLIB2_API, IReferenceCountedObject);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInputFile, YBWLIB2_API, ISeekableFile);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IOutputFile, YBWLIB2_API, ISeekableFile);
}
