#ifndef _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8
#define _INCLUDE_GUARD_9C46E5D6_24DA_4BE8_AA14_7AC6C92F67F8

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "Exception.h"

namespace YBWLib2 {
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(Exception, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(DoubleExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(InvalidParameterException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(InsufficientBufferException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(MemoryAllocFailureException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(KeyAlreadyExistException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(KeyNotExistException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(UnhandledUnknownExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(STLExceptionException, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(ExternalAPIFailureException, );

	void YBWLIB2_CALLTYPE Exception_RealInitModuleLocal() noexcept {
		Exception::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<Exception>(),
			IsDynamicTypeModuleLocalClass<Exception>(),
			{ DynamicTypeBaseClassDef<Exception, IException, DynamicTypeBaseClassFlag_VirtualBase> });
		DoubleExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<DoubleExceptionException>(),
			IsDynamicTypeModuleLocalClass<DoubleExceptionException>(),
			{
				DynamicTypeBaseClassDef<DoubleExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<DoubleExceptionException, IDoubleExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		InvalidParameterException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<InvalidParameterException>(),
			IsDynamicTypeModuleLocalClass<InvalidParameterException>(),
			{
				DynamicTypeBaseClassDef<InvalidParameterException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InvalidParameterException, IInvalidParameterException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		InsufficientBufferException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<InsufficientBufferException>(),
			IsDynamicTypeModuleLocalClass<InsufficientBufferException>(),
			{
				DynamicTypeBaseClassDef<InsufficientBufferException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<InsufficientBufferException, IInsufficientBufferException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		MemoryAllocFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<MemoryAllocFailureException>(),
			IsDynamicTypeModuleLocalClass<MemoryAllocFailureException>(),
			{
				DynamicTypeBaseClassDef<MemoryAllocFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<MemoryAllocFailureException, IMemoryAllocFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		KeyAlreadyExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<KeyAlreadyExistException>(),
			IsDynamicTypeModuleLocalClass<KeyAlreadyExistException>(),
			{
				DynamicTypeBaseClassDef<KeyAlreadyExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyAlreadyExistException, IKeyAlreadyExistException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		KeyNotExistException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<KeyNotExistException>(),
			IsDynamicTypeModuleLocalClass<KeyNotExistException>(),
			{
				DynamicTypeBaseClassDef<KeyNotExistException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<KeyNotExistException, IKeyNotExistException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		UnhandledUnknownExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<UnhandledUnknownExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnhandledUnknownExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnhandledUnknownExceptionException, IUnhandledUnknownExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		STLExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<STLExceptionException>(),
			IsDynamicTypeModuleLocalClass<STLExceptionException>(),
			{
				DynamicTypeBaseClassDef<STLExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<STLExceptionException, ISTLExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		ExternalAPIFailureException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<ExternalAPIFailureException>(),
			IsDynamicTypeModuleLocalClass<ExternalAPIFailureException>(),
			{
				DynamicTypeBaseClassDef<ExternalAPIFailureException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<ExternalAPIFailureException, IExternalAPIFailureException, DynamicTypeBaseClassFlag_VirtualBase>
			});
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept {
		delete ExternalAPIFailureException::DynamicTypeThisClassObject;
		ExternalAPIFailureException::DynamicTypeThisClassObject = nullptr;
		delete STLExceptionException::DynamicTypeThisClassObject;
		STLExceptionException::DynamicTypeThisClassObject = nullptr;
		delete UnhandledUnknownExceptionException::DynamicTypeThisClassObject;
		UnhandledUnknownExceptionException::DynamicTypeThisClassObject = nullptr;
		delete KeyNotExistException::DynamicTypeThisClassObject;
		KeyNotExistException::DynamicTypeThisClassObject = nullptr;
		delete KeyAlreadyExistException::DynamicTypeThisClassObject;
		KeyAlreadyExistException::DynamicTypeThisClassObject = nullptr;
		delete MemoryAllocFailureException::DynamicTypeThisClassObject;
		MemoryAllocFailureException::DynamicTypeThisClassObject = nullptr;
		delete InsufficientBufferException::DynamicTypeThisClassObject;
		InsufficientBufferException::DynamicTypeThisClassObject = nullptr;
		delete InvalidParameterException::DynamicTypeThisClassObject;
		InvalidParameterException::DynamicTypeThisClassObject = nullptr;
		delete DoubleExceptionException::DynamicTypeThisClassObject;
		DoubleExceptionException::DynamicTypeThisClassObject = nullptr;
		delete Exception::DynamicTypeThisClassObject;
		Exception::DynamicTypeThisClassObject = nullptr;
	}
}

#endif
