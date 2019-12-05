#ifndef _INCLUDE_GUARD_65CC313E_2130_410F_8AA7_E702E3627AAF
#define _INCLUDE_GUARD_65CC313E_2130_410F_8AA7_E702E3627AAF

#include "../DynamicType/DynamicType.h"
#include "Pipeline.h"

namespace YBWLib2 {
	namespace Internal {
		ReferenceCountedObjectHolder<PipelineStore>* pipelinestore_modulelocal = nullptr;
	}

	void YBWLIB2_CALLTYPE Pipeline_RealInitModuleLocal() noexcept {
		Internal::pipelinestore_modulelocal = new ReferenceCountedObjectHolder<PipelineStore>(CreatePipelineStore());
	}

	void YBWLIB2_CALLTYPE Pipeline_RealUnInitModuleLocal() noexcept {
		delete Internal::pipelinestore_modulelocal;
		Internal::pipelinestore_modulelocal = nullptr;
	}
}

#endif
