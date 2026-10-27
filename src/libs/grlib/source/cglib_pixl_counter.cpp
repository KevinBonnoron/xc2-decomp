#include "grlib/cglib_pixl_counter.h"

#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

CGLibPixlCounter::CGLibPixlCounter() : unknown00(0) {}

void CGLibPixlCounter::release() {
  CGLibMemHandle::free(unknown08);
  unknown00 = 0;
}

void CGLibPixlCounter::beginCounter() { nvnCommandBufferResetCounter(context::CGLibSystemContext::get()->unknown1070.unknown00, NVN_COUNTER_TYPE_SAMPLES_PASSED); }

void CGLibPixlCounter::endCounter() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  if (unknown00 == 0) {
    CGLibMemHandle::allocUniform(unknown08, 0x100);
    context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown00, unknown08);
  }
  nvnCommandBufferReportCounter(context->unknown1070.unknown00, NVN_COUNTER_TYPE_SAMPLES_PASSED, unknown00);
}

void CGLibPixlCounter::setUniformBlock(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown00, 0x100);
}

} // namespace grlib
