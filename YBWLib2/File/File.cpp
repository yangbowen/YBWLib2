#pragma include_alias("pch.h", "../pch.h")
#include "pch.h"
#include "File.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ISeekableFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IInputFile, YBWLIB2_API);
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(IOutputFile, YBWLIB2_API);

	void YBWLIB2_CALLTYPE File_RealInitGlobal() noexcept {
		ISeekableFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ISeekableFile>(),
			IsDynamicTypeModuleLocalClass<ISeekableFile>(),
			{ DynamicTypeBaseClassDef<ISeekableFile, IReferenceCountedObject, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(ISeekableFile), alignof(ISeekableFile));
		IInputFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IInputFile>(),
			IsDynamicTypeModuleLocalClass<IInputFile>(),
			{ DynamicTypeBaseClassDef<IInputFile, ISeekableFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IInputFile), alignof(IInputFile));
		IOutputFile::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<IOutputFile>(),
			IsDynamicTypeModuleLocalClass<IOutputFile>(),
			{ DynamicTypeBaseClassDef<IOutputFile, ISeekableFile, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(IOutputFile), alignof(IOutputFile));
	}

	void YBWLIB2_CALLTYPE File_RealUnInitGlobal() noexcept {
		delete IOutputFile::DynamicTypeThisClassObject;
		IOutputFile::DynamicTypeThisClassObject = nullptr;
		delete IInputFile::DynamicTypeThisClassObject;
		IInputFile::DynamicTypeThisClassObject = nullptr;
		delete ISeekableFile::DynamicTypeThisClassObject;
		ISeekableFile::DynamicTypeThisClassObject = nullptr;
	}
}
