#include "grlib/cglib_ctl_vertex.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "nvn/nvn.h"

namespace grlib {

// Inferred role: sets the stride and divisor of a vertex stream; original name unknown.
inline void CGLibCtlVertex::unknown001(context::CGLibSystemContext *context, size_t stride, u32 divisor, int stream) {
  nvnVertexStreamStateSetStride(&context->unknown1070.unknown50[stream], stride);
  nvnVertexStreamStateSetDivisor(&context->unknown1070.unknown50[stream], divisor);
  context->unknown1070.unknown90 = stream;
  context->unknown1070.unknown94 = true;
}

void CGLibCtlVertex::setVertex(CGLibVtxVertex &vertex) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, vertex.unknown04, 0, 0);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, 0, vertex.unknown20, vertex.m_size);
}

void CGLibCtlVertex::setVertex(CGLibVtxVertex &vertex, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, vertex.unknown04, 0, 0);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, 0, vertex.unknown20 + offset, vertex.m_size);
}

void CGLibCtlVertex::setAddVertex(CGLibVtxVertex &vertex, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, vertex.unknown04, divisor, stream);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, vertex.unknown20 + offset, vertex.m_size);
}

void CGLibCtlVertex::setUniformVertex(CGLibOneUniformBlock &block, int stride, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, stride, divisor, stream);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, block.unknown10 + offset, static_cast<int>(block.m_size));
}

void CGLibCtlVertex::setUniformVertex(CGLibDblUniformBlock &block, int stride, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, stride, divisor, stream);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, block.getGPUAdress() + offset, static_cast<int>(block.m_size));
}

void CGLibCtlVertex::setUniformVertex(CGLibTriUniformBlock &block, int stride, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, stride, divisor, stream);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, block.getGPUAdress() + offset, static_cast<int>(block.m_size));
}

void CGLibCtlVertex::setInstanceVertex(CGLibVtxOneInstans &instance, int stride, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, stride, divisor, stream);
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, instance.unknown10 + offset, instance.unknown04);
}

void CGLibCtlVertex::setStreamOutVertex(CGLibVtxStmOut &streamOut, int stride, int offset, int stream, u32 divisor) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  unknown001(context, stride, divisor, stream);
  u64 address = streamOut.unknown20;
  nvnCommandBufferBindVertexBuffer(context->unknown1070.unknown00, stream, address + offset, static_cast<u32>(streamOut.getSize()));
}

} // namespace grlib
