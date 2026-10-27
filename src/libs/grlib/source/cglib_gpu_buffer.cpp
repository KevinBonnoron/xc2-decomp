#include "grlib/cglib_gpu_buffer.h"

#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibGpuBuffer::copyBuffer(CGLibTextureBuffer &dst, CGLibTextureBuffer &src) {
  nvnCommandBufferCopyBufferToBuffer(context::CGLibSystemContext::get()->unknown1070.unknown00, src.unknown20, dst.unknown20, dst.unknown30, 0);
}

void CGLibGpuBuffer::copyBuffer(CGLibOneUniformBlock &dst, CGLibOneUniformBlock &src) {
  nvnCommandBufferCopyBufferToBuffer(context::CGLibSystemContext::get()->unknown1070.unknown00, src.unknown10, dst.unknown10, static_cast<int>(dst.m_size), 0);
}

} // namespace grlib
