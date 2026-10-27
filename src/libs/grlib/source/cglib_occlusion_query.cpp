#include "grlib/cglib_occlusion_query.h"

#include "grlib/cglib_buff_occlusion.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

CGLibOcclusionQuery::CGLibOcclusionQuery() : unknown00(nullptr), unknown08(0), unknown10(0), unknown12(0), unknown13(1) {}

void CGLibOcclusionQuery::release() {
  if (unknown00 != nullptr) {
    context::CGLibSystemContext::get()->unknowne38.freeID(unknown08);
    unknown00 = nullptr;
    unknown08 = 0;
  }
}

void CGLibOcclusionQuery::beginQuery() { nvnCommandBufferResetCounter(context::CGLibSystemContext::get()->unknown1070.unknown00, NVN_COUNTER_TYPE_SAMPLES_PASSED); }

} // namespace grlib
