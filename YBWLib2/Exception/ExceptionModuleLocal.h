// Include guard omitted intentionally.

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
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(Exception, IException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(DoubleExceptionException, Exception, IDoubleExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(InvalidParameterException, Exception, IInvalidParameterException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(InsufficientBufferException, Exception, IInsufficientBufferException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(MemoryAllocFailureException, Exception, IMemoryAllocFailureException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(KeyAlreadyExistException, Exception, IKeyAlreadyExistException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(KeyNotExistException, Exception, IKeyNotExistException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(UnhandledUnknownExceptionException, Exception, IUnhandledUnknownExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(STLExceptionException, Exception, ISTLExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALINIT_CLASS(ExternalAPIFailureException, Exception, IExternalAPIFailureException);
	}

	void YBWLIB2_CALLTYPE Exception_RealUnInitModuleLocal() noexcept {
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(ExternalAPIFailureException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(STLExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(UnhandledUnknownExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(KeyNotExistException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(KeyAlreadyExistException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(MemoryAllocFailureException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(InsufficientBufferException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(InvalidParameterException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(DoubleExceptionException);
		YBWLIB2_DYNAMIC_TYPE_REALUNINIT_CLASS(Exception);
	}
}
