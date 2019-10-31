#ifndef _INCLUDE_GUARD_65CC313E_2130_410F_8AA7_E702E3627AAF
#define _INCLUDE_GUARD_65CC313E_2130_410F_8AA7_E702E3627AAF

#include "../DynamicType/DynamicType.h"
#include "Pipeline.h"

namespace YBWLib2 {
	ReferenceCountedObjectHolder<PipelineStore> pipelinestore_modulelocal;

	void YBWLIB2_CALLTYPE Pipeline_RealInitModuleLocal() noexcept {
		pipelinestore_modulelocal = CreatePipelineStore();
	}

	void YBWLIB2_CALLTYPE Pipeline_RealUnInitModuleLocal() noexcept {
		pipelinestore_modulelocal.reset();
	}
}

#endif
