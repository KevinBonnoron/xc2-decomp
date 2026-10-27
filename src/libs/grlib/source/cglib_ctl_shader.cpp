#include "grlib/cglib_ctl_shader.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_dec_shd_ext_tbl.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_vtx_fetch.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibCtlShader::setShader(CGLibDecShader &shader, CGLibVtxFetch &fetch) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibShader *shaders = shader.unknown38;
  CGLibShader *program = &shaders[shader.unknown58];
  context->unknown1070._98 = program;
  nvnCommandBufferBindProgram(context->unknown1070.unknown00, &program->unknown18, program->unknown14);
  nvnCommandBufferBindVertexAttribState(context->unknown1070.unknown00, fetch.unknown08, fetch.unknown00);
}

void CGLibCtlShader::setShader(CGLibDecShdExtTbl &shader, CGLibVtxFetch &fetch) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibDecShader *decShader = shader.unknown00;
  CGLibShader *program = &decShader->unknown38[shader.unknown08];
  context->unknown1070._98 = program;
  nvnCommandBufferBindProgram(context->unknown1070.unknown00, &program->unknown18, program->unknown14);
  nvnCommandBufferBindVertexAttribState(context->unknown1070.unknown00, fetch.unknown08, fetch.unknown00);
}

void CGLibCtlShader::setComputeShader(CGLibDecShader &shader) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibShader *shaders = shader.unknown38;
  CGLibShader *program = &shaders[shader.unknown58];
  context->unknown1070._98 = program;
  nvnCommandBufferBindProgram(context->unknown1070.unknown00, &program->unknown18, program->unknown14);
}

void CGLibCtlShader::setComputeShader(CGLibDecShdExtTbl &shader) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibDecShader *decShader = shader.unknown00;
  CGLibShader *program = &decShader->unknown38[shader.unknown08];
  context->unknown1070._98 = program;
  nvnCommandBufferBindProgram(context->unknown1070.unknown00, &program->unknown18, program->unknown14);
}

void CGLibCtlShader::setDispatchCompute(u32 groupsX, u32 groupsY, u32 groupsZ) {
  nvnCommandBufferDispatchCompute(context::CGLibSystemContext::get()->unknown1070.unknown00, groupsX, groupsY, groupsZ);
}

void CGLibCtlShader::setDispatchComputeIndirect(const CGLibEtcUniformBlock &block, u32 offset) {
  nvnCommandBufferDispatchComputeIndirect(context::CGLibSystemContext::get()->unknown1070.unknown00, block.unknown10 + offset);
}

void CGLibCtlShader::setDispatchComputeIndirect(const CGLibOneUniformBlock &block, u32 offset) {
  nvnCommandBufferDispatchComputeIndirect(context::CGLibSystemContext::get()->unknown1070.unknown00, block.unknown10 + offset);
}

void CGLibCtlShader::setDispatchComputeIndirect(const CGLibDblUniformBlock &block, u32 offset) {
  nvnCommandBufferDispatchComputeIndirect(context::CGLibSystemContext::get()->unknown1070.unknown00, block.getGPUAdress() + offset);
}

void CGLibCtlShader::setDispatchComputeIndirect(const CGLibTriUniformBlock &block, u32 offset) {
  nvnCommandBufferDispatchComputeIndirect(context::CGLibSystemContext::get()->unknown1070.unknown00, block.getGPUAdress() + offset);
}

void CGLibCtlShader::setMemoryBarrier() { nvnCommandBufferBarrier(context::CGLibSystemContext::get()->unknown1070.unknown00, 9); }

void CGLibCtlShader::setMemoryBarrierBit(u32 bits) { nvnCommandBufferBarrier(context::CGLibSystemContext::get()->unknown1070.unknown00, bits); }

CGLibDecShader *CGLibCtlShader::getDecShader() { return &context::CGLibSystemContext::get()->unknown2320; }

CGLibVtxFetch *CGLibCtlShader::getVtxFetch(GrlUtilVertFetch type) { return &context::CGLibSystemContext::get()->unknown2388[type]; }

CGLibSampler *CGLibCtlShader::getSampler(GrlUtilSampler type) { return &context::CGLibSystemContext::get()->unknown23b8[type]; }

} // namespace grlib
