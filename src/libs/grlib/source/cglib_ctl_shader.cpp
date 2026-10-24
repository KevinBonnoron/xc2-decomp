#include "grlib/cglib_ctl_shader.h"

#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_vtx_fetch.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibCtlShader::setDispatchCompute(u32 groupsX, u32 groupsY, u32 groupsZ) {
  nvnCommandBufferDispatchCompute(context::CGLibSystemContext::get()->unknown1070.unknown00, groupsX, groupsY, groupsZ);
}

void CGLibCtlShader::setMemoryBarrier() { nvnCommandBufferBarrier(context::CGLibSystemContext::get()->unknown1070.unknown00, 9); }

void CGLibCtlShader::setMemoryBarrierBit(u32 bits) { nvnCommandBufferBarrier(context::CGLibSystemContext::get()->unknown1070.unknown00, bits); }

CGLibDecShader *CGLibCtlShader::getDecShader() { return &context::CGLibSystemContext::get()->unknown2320; }

CGLibVtxFetch *CGLibCtlShader::getVtxFetch(GrlUtilVertFetch type) { return &context::CGLibSystemContext::get()->unknown2388[type]; }

} // namespace grlib
