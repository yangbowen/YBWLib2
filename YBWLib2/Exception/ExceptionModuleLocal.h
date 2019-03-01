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
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(UnexpectedExceptionException, );

	void YBWLIB2_CALLTYPE Exception_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IException)), module_info_current);
		GetDynamicTypeThisClassObject<IDoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IDoubleExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<IInvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInvalidParameterException)), module_info_current);
		GetDynamicTypeThisClassObject<IInsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IInsufficientBufferException)), module_info_current);
		GetDynamicTypeThisClassObject<IMemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IMemoryAllocFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<IKeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyAlreadyExistException)), module_info_current);
		GetDynamicTypeThisClassObject<IKeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IKeyNotExistException)), module_info_current);
		GetDynamicTypeThisClassObject<IUnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<ISTLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ISTLExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<IExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IExternalAPIFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<IUnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IUnexpectedExceptionException)), module_info_current);
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
		UnexpectedExceptionException::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<UnexpectedExceptionException>(),
			IsDynamicTypeModuleLocalClass<UnexpectedExceptionException>(),
			{
				DynamicTypeBaseClassDef<UnexpectedExceptionException, Exception, DynamicTypeBaseClassFlag_VirtualBase>,
				DynamicTypeBaseClassDef<UnexpectedExceptionException, IUnexpectedExceptionException, DynamicTypeBaseClassFlag_VirtualBase>
			});
		GetDynamicTypeThisClassObject<Exception>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(Exception)), module_info_current);
		GetDynamicTypeThisClassObject<DoubleExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(DoubleExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<InvalidParameterException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InvalidParameterException)), module_info_current);
		GetDynamicTypeThisClassObject<InsufficientBufferException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(InsufficientBufferException)), module_info_current);
		GetDynamicTypeThisClassObject<MemoryAllocFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(MemoryAllocFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<KeyAlreadyExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyAlreadyExistException)), module_info_current);
		GetDynamicTypeThisClassObject<KeyNotExistException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(KeyNotExistException)), module_info_current);
		GetDynamicTypeThisClassObject<UnhandledUnknownExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnhandledUnknownExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<STLExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(STLExceptionException)), module_info_current);
		GetDynamicTypeThisClassObject<ExternalAPIFailureException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(ExternalAPIFailureException)), module_info_current);
		GetDynamicTypeThisClassObject<UnexpectedExceptionException>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(UnexpectedExceptionException)), module_info_current);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<UnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<STLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<UnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<KeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<KeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<MemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<InsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<InvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<DoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<Exception>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete UnexpectedExceptionException::DynamicTypeThisClassObject;
		UnexpectedExceptionException::DynamicTypeThisClassObject = nullptr;
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
		GetDynamicTypeThisClassObject<IUnexpectedExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IExternalAPIFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<ISTLExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IUnhandledUnknownExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IKeyNotExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IKeyAlreadyExistException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IMemoryAllocFailureException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInsufficientBufferException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IInvalidParameterException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IDoubleExceptionException>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IException>()->UnRegisterTypeInfoWrapper(module_info_current);
	}

	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealInitModuleLocal() noexcept {}

	void YBWLIB2_CALLTYPE ExceptionUserInterface_RealUnInitModuleLocal() noexcept {}
}

#endif
