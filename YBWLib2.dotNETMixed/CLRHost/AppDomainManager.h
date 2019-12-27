#ifndef _INCLUDE_GUARD_CFA6A522_DE78_4487_9823_7A242CFFC5FD
#define _INCLUDE_GUARD_CFA6A522_DE78_4487_9823_7A242CFFC5FD

#include "../YBWLib2dotNETMixedApi.h"

#pragma managed(push, on)

namespace YBWLib2::dotNETMixed {
	ref class AppDomainManager : public System::AppDomainManager {
	public:
		YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED AppDomainManager();
		virtual YBWLIB2DOTNETMIXED_CALLTYPE_MANAGED ~AppDomainManager();
	};
}

#pragma managed(pop)

#endif
