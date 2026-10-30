#include <string.h>

#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool_list.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_instans.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "nn/os.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

CGLibVtxIndex::CGLibVtxIndex() { unknown00 = 0; }

CGLibVtxIndex::~CGLibVtxIndex() { release(); }

void CGLibVtxIndex::release() { CGLibMemHandle::free(unknown10); }

void CGLibVtxIndex::createIndexBuff(u32 count, GrlPrimitiveType type, GrlIndexFormat format) {
  release();
  unknown08 = type;
  unknown04 = format;
  unknown00 = count;
  int size = getSize();
  CGLibMemHandle::allocVertex(unknown10, size + (4 - size % 4) % 4);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown20, unknown10);
}

void CGLibVtxIndex::createMemIndexBuff(CGLibVtlMemPool *memPool, u32 offset, u32 count, GrlPrimitiveType type, GrlIndexFormat format) {
  release();
  unknown08 = type;
  unknown04 = format;
  unknown00 = count;
  CGLibMemHandle::setMemBuff(unknown10, static_cast<u8 *>(memPool->m_buffer) + offset);
  unknown20 = memPool->unknown08 + offset;
}

void CGLibVtxIndex::createCopyIndexBuff(const void *data, u32 count, GrlPrimitiveType type, GrlIndexFormat format) {
  release();
  unknown08 = type;
  unknown04 = format;
  unknown00 = count;
  int size = getSize();
  CGLibMemHandle::allocVertex(unknown10, size + (4 - size % 4) % 4);
  memcpy(unknown10.m_buffer, data, size);
  nn::os::FlushDataCache(unknown10.m_buffer, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown20, unknown10);
}

void CGLibVtxIndex::resetIndexBuff(CGLibVtlMemPool *memPool, u32 offset) {
  CGLibMemHandle::setMemBuff(unknown10, static_cast<u8 *>(memPool->m_buffer) + offset);
  unknown20 = memPool->unknown08 + offset;
}

void CGLibVtxIndex::drawIndex() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElements(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown00, unknown20);
}

void CGLibVtxIndex::drawIndex(u32 count, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElements(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), count, unknown20 + offset);
}

void CGLibVtxIndex::drawInsIndex(int instanceCount) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsInstanced(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown00, unknown20, 0, 0, instanceCount);
}

void CGLibVtxIndex::drawInsIndex(int instanceCount, u32 count, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsInstanced(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), count, unknown20 + offset, 0, 0, instanceCount);
}

void CGLibVtxIndex::drawIndirect(const CGLibOneUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsIndirect(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown20, block.unknown10 + offset);
}

void CGLibVtxIndex::drawIndirect(const CGLibDblUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsIndirect(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown20, block.getGPUAdress() + offset);
}

void CGLibVtxIndex::drawIndirect(const CGLibTriUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsIndirect(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown20, block.getGPUAdress() + offset);
}

void CGLibVtxIndex::drawIndirect(const CGLibEtcUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  nvnCommandBufferDrawElementsIndirect(context->unknown1070.unknown00, static_cast<NVNdrawPrimitive>(unknown08), static_cast<NVNindexType>(unknown04), unknown20, block.unknown10 + offset);
}

void CGLibVtxIndex::drawMultiIndirect(u32 drawCount, u32 stride, const CGLibOneUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  u32 countOffset = context->unknown60.cntOffset(4, 4);
  *reinterpret_cast<u32 *>(static_cast<u8 *>(context->unknown60.unknown18) + countOffset) = drawCount;
  nvnCommandBufferMultiDrawElementsIndirectCount(context->unknown1070.unknown00,
                                                 static_cast<NVNdrawPrimitive>(unknown08),
                                                 static_cast<NVNindexType>(unknown04),
                                                 unknown20,
                                                 block.unknown10 + offset,
                                                 nvnMemoryPoolGetBufferAddress(context->unknown60.m_memoryPool) + countOffset,
                                                 drawCount,
                                                 stride);
}

void CGLibVtxIndex::drawMultiIndirect(u32 drawCount, u32 stride, const CGLibDblUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  u32 countOffset = context->unknown60.cntOffset(4, 4);
  *reinterpret_cast<u32 *>(static_cast<u8 *>(context->unknown60.unknown18) + countOffset) = drawCount;
  nvnCommandBufferMultiDrawElementsIndirectCount(context->unknown1070.unknown00,
                                                 static_cast<NVNdrawPrimitive>(unknown08),
                                                 static_cast<NVNindexType>(unknown04),
                                                 unknown20,
                                                 block.getGPUAdress() + offset,
                                                 nvnMemoryPoolGetBufferAddress(context->unknown60.m_memoryPool) + countOffset,
                                                 drawCount,
                                                 stride);
}

void CGLibVtxIndex::drawMultiIndirect(u32 drawCount, u32 stride, const CGLibTriUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  u32 countOffset = context->unknown60.cntOffset(4, 4);
  *reinterpret_cast<u32 *>(static_cast<u8 *>(context->unknown60.unknown18) + countOffset) = drawCount;
  nvnCommandBufferMultiDrawElementsIndirectCount(context->unknown1070.unknown00,
                                                 static_cast<NVNdrawPrimitive>(unknown08),
                                                 static_cast<NVNindexType>(unknown04),
                                                 unknown20,
                                                 block.getGPUAdress() + offset,
                                                 nvnMemoryPoolGetBufferAddress(context->unknown60.m_memoryPool) + countOffset,
                                                 drawCount,
                                                 stride);
}

void CGLibVtxIndex::drawMultiIndirect(u32 drawCount, u32 stride, const CGLibEtcUniformBlock &block, u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070.updateVertex();
  u32 countOffset = context->unknown60.cntOffset(4, 4);
  *reinterpret_cast<u32 *>(static_cast<u8 *>(context->unknown60.unknown18) + countOffset) = drawCount;
  nvnCommandBufferMultiDrawElementsIndirectCount(context->unknown1070.unknown00,
                                                 static_cast<NVNdrawPrimitive>(unknown08),
                                                 static_cast<NVNindexType>(unknown04),
                                                 unknown20,
                                                 block.unknown10 + offset,
                                                 nvnMemoryPoolGetBufferAddress(context->unknown60.m_memoryPool) + countOffset,
                                                 drawCount,
                                                 stride);
}

void CGLibVtxIndex::lock(void **buffer, u32 *size) {
  *buffer = unknown10.m_buffer;
  *size = getSize();
}

void CGLibVtxIndex::unlock() {
  int size = getSize();
  nn::os::FlushDataCache(unknown10.m_buffer, size);
}

void CGLibVtxIndex::copyIndexBuff(const void *data) {
  int size = getSize();
  memcpy(unknown10.m_buffer, data, size);
  nn::os::FlushDataCache(unknown10.m_buffer, size);
}

CGLibVtxInstans::CGLibVtxInstans() { unknown10 = 0; }

CGLibVtxInstans::~CGLibVtxInstans() { release(); }

void CGLibVtxInstans::release() { CGLibMemHandle::free(unknown18); }

void CGLibVtxInstans::createInstansBuffer(int size) {
  release();
  m_size = size;
  unknown04 = static_cast<u32>(size) / 2;
  CGLibMemHandle::allocVertex(unknown18, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown28, unknown18);
}

void CGLibVtxInstans::beginInstansBuff() {
  unknown10 = CGLibManager::s_nDblNowIdx * unknown04;
  unknown08 = 0;
  unknown0c = 0;
}

void CGLibVtxInstans::updateInstansBuff() {
  u32 size = unknown08 - unknown0c;
  if (size != 0) {
    nn::os::FlushDataCache(static_cast<u8 *>(unknown18.m_buffer) + (unknown10 + unknown0c), size);
    unknown0c = unknown08;
  }
}

void *CGLibVtxInstans::getNextInstansBuff() { return static_cast<u8 *>(unknown18.m_buffer) + (unknown08 + unknown10); }

u64 CGLibVtxInstans_plf::getGPUAdress() { return unknown28 + CGLibManager::s_nDblNowIdx * unknown04; }

CGLibVtxOneInstans::CGLibVtxOneInstans() {}

CGLibVtxOneInstans::~CGLibVtxOneInstans() { release(); }

void CGLibVtxOneInstans::release() { CGLibMemHandle::free(unknown18); }

void CGLibVtxOneInstans::createInstansBuffer(int size) {
  release();
  m_size = size;
  CGLibMemHandle::allocVertex(unknown18, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown10, unknown18);
}

void CGLibVtxOneInstans::beginInstansBuff() {
  unknown04 = 0;
  unknown08 = 0;
}

void CGLibVtxOneInstans::updateInstansBuff() {
  if (unknown04 != unknown08) {
    nn::os::FlushDataCache(static_cast<u8 *>(unknown18.m_buffer) + unknown08, unknown04 - unknown08);
    unknown08 = unknown04;
  }
}

void *CGLibVtxOneInstans::getNextInstansBuff() { return static_cast<u8 *>(unknown18.m_buffer) + unknown04; }

void *CGLibVtxOneInstans::getBuff() { return unknown18.m_buffer; }

CGLibVtxStmOut::CGLibVtxStmOut() {}

CGLibVtxStmOut::~CGLibVtxStmOut() { release(); }

void CGLibVtxStmOut::release() { CGLibMemHandle::free(unknown10); }

int CGLibVtxStmOut::getStreamOutWorkSize() { return 0; }

void CGLibVtxStmOut::createWorkBuff(int size) {
  release();
  int alignedSize = size + (4 - size % 4) % 4;
  CGLibMemHandle::allocVertex(unknown10, alignedSize);
  unknown08 = 0;
  unknown00 = 0;
  m_size = alignedSize;
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown20, unknown10);
}

void CGLibVtxStmOut::begin(int stride) {
  unknown08 = stride;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, true);
  nvnCommandBufferBindTransformFeedbackBuffer(context->unknown1070.unknown00, 0, unknown20, m_size);
  nvnCommandBufferBeginTransformFeedback(context->unknown1070.unknown00, unknown20 + m_size);
}

void CGLibVtxStmOut::end(u32 count) {
  unknown00 = unknown08 * count;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferEndTransformFeedback(context->unknown1070.unknown00, unknown20 + unknown00);
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, false);
  nvnCommandBufferBarrier(context->unknown1070.unknown00, 0x21);
}

void CGLibVtxStmOut::setUniformBlock(u32 index) {
  if (index != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown20, m_size);
  }
}

void CGLibVtxStmOut::setUniformBlock(u32 index, u32 offset, u32 size) {
  if (index != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown20 + offset, size);
  }
}

void CGLibVtxStmOut::setStorageBuffer(u32 index) {
  if (index != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, unknown20, m_size);
  }
}

void CGLibVtxStmOut::setStorageBuffer(u32 index, u32 offset, u32 size) {
  if (index != 0xffffffff) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, unknown20 + offset, size);
  }
}

int CGLibVtxStmOut::getSize() { return m_size; }

void *CGLibVtxStmOut::getBuff() { return unknown10.m_buffer; }

void *CGLibVtxStmOut::getMapping() { return unknown10.m_buffer; }

CGLibVtxVertex::CGLibVtxVertex() : m_size(0), unknown04(0), unknown08(0) {}

CGLibVtxVertex::~CGLibVtxVertex() { release(); }

void CGLibVtxVertex::release() { CGLibMemHandle::free(unknown10); }

void CGLibVtxVertex::delayRelease() { context::CGLibSystemContext::get()->releaseDelayVertex(unknown10); }

void CGLibVtxVertex::createVertexBuff(u32 size, u32 stride) {
  release();
  unknown08 = size / stride;
  m_size = size;
  unknown04 = stride;
  CGLibMemHandle::allocVertex(unknown10, size + (4 - size % 4) % 4);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown20, unknown10);
}

void CGLibVtxVertex::createMemVertexBuff(CGLibVtlMemPool *memPool, u32 offset, u32 size, u32 stride) {
  release();
  m_size = size;
  unknown04 = stride;
  unknown08 = size / stride;
  CGLibMemHandle::setMemBuff(unknown10, static_cast<u8 *>(memPool->m_buffer) + offset);
  unknown20 = memPool->unknown08 + offset;
}

void CGLibVtxVertex::createCopyVertexBuff(const void *data, u32 size, u32 stride) {
  release();
  unknown08 = size / unknown04;
  m_size = size;
  unknown04 = stride;
  CGLibMemHandle::allocVertex(unknown10, size + (4 - size % 4) % 4);
  memcpy(unknown10.m_buffer, data, size);
  nn::os::FlushDataCache(unknown10.m_buffer, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(unknown20, unknown10);
}

void CGLibVtxVertex::resetVertexBuff(CGLibVtlMemPool *memPool, u32 offset) {
  CGLibMemHandle::setMemBuff(unknown10, static_cast<u8 *>(memPool->m_buffer) + offset);
  unknown20 = memPool->unknown08 + offset;
}

void CGLibVtxVertex::lock(void **buffer, u32 *size) {
  *buffer = unknown10.m_buffer;
  *size = m_size;
}

void CGLibVtxVertex::unlock() { nn::os::FlushDataCache(unknown10.m_buffer, m_size); }

void CGLibVtxVertex::unlock(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(unknown10.m_buffer) + offset, size); }

void CGLibVtxVertex::copyVertexBuff(const void *data) {
  void *buffer = unknown10.m_buffer;
  memcpy(buffer, data, m_size);
  nn::os::FlushDataCache(buffer, m_size);
}

} // namespace grlib
