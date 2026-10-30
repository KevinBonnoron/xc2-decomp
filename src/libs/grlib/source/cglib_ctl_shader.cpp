#include "grlib/cglib_ctl_shader.h"

#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_dec_shd_ext_tbl.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_sampler_descriptor.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_util_obj.h"
#include "grlib/cglib_vtx_fetch.h"
#include "nvn/nvn.h"

namespace grlib {
class CGLibTextureBuffer;

void CGLibCtlTexture::setTexture(const CGLibTextureBuffer &texture, const CGLibSampler &sampler, u32 location) {
  if (location != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    int textureId = context->unknown538.setTexture(texture);
    int samplerId = context->unknown5a0.setSampler(sampler);
    NVNtextureHandle handle = nvnDeviceGetTextureHandle(&CGLibManager::get()->unknown00, textureId, samplerId);
    context->unknown1070._98->setTextureHandle(location, context->unknown1070.unknown00, handle);
  }
}

void CGLibCtlTexture::setUAVTexture(const CGLibTextureBuffer &texture, u32 location, u32 level, u32 layer) {
  if (location != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    int imageId = context->unknown538.setImage(texture);
    NVNimageHandle handle = nvnDeviceGetImageHandle(&CGLibManager::get()->unknown00, imageId);
    context->unknown1070._98->setImageHandle(location, context->unknown1070.unknown00, handle);
  }
}

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

CGLibDecShader *CGLibCtlShader::getDecShader() { return &context::CGLibSystemContext::get()->unknown2320.unknown00; }

CGLibVtxFetch *CGLibCtlShader::getVtxFetch(GrlUtilVertFetch type) { return &context::CGLibSystemContext::get()->unknown2320.unknown68[type]; }

CGLibSampler *CGLibCtlShader::getSampler(GrlUtilSampler type) { return &context::CGLibSystemContext::get()->unknown2320.unknown98[type]; }

} // namespace grlib
