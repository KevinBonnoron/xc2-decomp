#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "nn/os.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

u64 CGLibDblUniformBlock_plf::getGPUAdress() const { return unknown18[CGLibManager::s_nDblNowIdx]; }

void CGLibDblUniformBlock_plf::setupUniformBuffer(u32 size, CGLibMemType &memType, u32 offset) {
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown18[0], memType);
  u64 address = unknown18[0];
  unknown18[0] = address + offset;
  unknown18[1] = address + offset + size;
}

CGLibDblUniformBlock::CGLibDblUniformBlock() {}

CGLibDblUniformBlock::~CGLibDblUniformBlock() { release(); }

void CGLibDblUniformBlock::release() {
  CGLibMemHandle::free(unknown28);
  unknown00[0] = nullptr;
  unknown00[1] = nullptr;
}

void CGLibDblUniformBlock::setup(int size) {
  release();
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  CGLibMemHandle::allocUniform(unknown28, alignedSize * 2);
  unknown00[0] = unknown28.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown28.m_buffer) + alignedSize;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown18[0], unknown28);
  unknown18[1] = unknown18[0] + alignedSize;
}

void CGLibDblUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(unknown28, static_cast<u8 *>(memPool->m_buffer) + offset);
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  unknown00[0] = unknown28.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown28.m_buffer) + alignedSize;
  unknown18[0] = memPool->unknown08 + offset;
  unknown18[1] = memPool->unknown08 + (alignedSize + offset);
}

int CGLibDblUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  CGLibMemHandle::setMemBuff(unknown28, static_cast<u8 *>(memType.m_buffer) + offset);
  unknown00[0] = unknown28.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown28.m_buffer) + alignedSize;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown18[0], memType);
  unknown18[0] += offset;
  unknown18[1] = unknown18[0] + alignedSize;
  return alignedSize * 2;
}

void CGLibDblUniformBlock::updateData() { nn::os::FlushDataCache(unknown00[CGLibManager::s_nDblNowIdx], m_size); }

void CGLibDblUniformBlock::updateData(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(unknown00[CGLibManager::s_nDblNowIdx]) + offset, size); }

void *CGLibDblUniformBlock::getBuff() { return unknown00[CGLibManager::s_nDblNowIdx]; }

void *CGLibDblUniformBlock::getOldBuff() { return unknown00[CGLibManager::s_nDblNowIdx == 0]; }

void CGLibDblUniformBlock::setUniformBlock(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, getGPUAdress(), m_size);
}

void CGLibDblUniformBlock::setStorageBuffer(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, getGPUAdress(), m_size);
}

void CGLibDblUniformBlock::setUniformBlock(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, getGPUAdress() + offset, size);
}

void CGLibDblUniformBlock::setStorageBuffer(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, getGPUAdress() + offset, size);
}

void *CGLibDblUniformBlock::getMapping() { return unknown00[CGLibManager::s_nDblNowIdx]; }

void CGLibDblUniformBlock::beginStreamOut(u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, true);
  nvnCommandBufferBindTransformFeedbackBuffer(context->unknown1070.unknown00, 0, unknown18[CGLibManager::s_nDblNowIdx], offset);
  nvnCommandBufferBeginTransformFeedback(context->unknown1070.unknown00, unknown18[CGLibManager::s_nDblNowIdx]);
}

void CGLibDblUniformBlock::endStreamOut(u32 count, u32 stride) {
  u32 size = count * stride;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferEndTransformFeedback(context->unknown1070.unknown00, unknown18[CGLibManager::s_nDblNowIdx] + size);
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, false);
  nvnCommandBufferBarrier(context->unknown1070.unknown00, 0x21);
}

CGLibOneUniformBlock::CGLibOneUniformBlock() : m_mapping(nullptr), unknown10(0) {}

CGLibOneUniformBlock::~CGLibOneUniformBlock() { release(); }

void CGLibOneUniformBlock::release() {
  CGLibMemHandle::free(unknown18);
  m_mapping = nullptr;
}

void CGLibOneUniformBlock::setup(int size) {
  release();
  CGLibMemHandle::allocUniform(unknown18, size + (0x100 - size % 0x100) % 0x100);
  m_mapping = unknown18.m_buffer;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown10, unknown18);
}

void CGLibOneUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(unknown18, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_mapping = unknown18.m_buffer;
  m_size = size;
  unknown10 = memPool->unknown08 + offset;
}

int CGLibOneUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  CGLibMemHandle::setMemBuff(unknown18, static_cast<u8 *>(memType.m_buffer) + offset);
  m_mapping = unknown18.m_buffer;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown10, memType);
  unknown10 += offset;
  return size + (0x100 - size % 0x100) % 0x100;
}

void CGLibOneUniformBlock::setupArray(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  CGLibMemHandle::setMemBuff(unknown18, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_mapping = unknown18.m_buffer;
  m_size = size;
  unknown10 = memPool->unknown08 + offset;
}

void CGLibOneUniformBlock::updateData() { nn::os::FlushDataCache(m_mapping, m_size); }

void CGLibOneUniformBlock::updateData(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(m_mapping) + offset, size); }

void CGLibOneUniformBlock::setUniformBlock(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown10, m_size);
}

void CGLibOneUniformBlock::setStorageBuffer(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, unknown10, m_size);
}

void CGLibOneUniformBlock::setUniformBlock(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown10 + offset, size);
}

void CGLibOneUniformBlock::setStorageBuffer(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, unknown10 + offset, size);
}

void *CGLibOneUniformBlock::getMapping() { return m_mapping; }

void CGLibOneUniformBlock::beginStreamOut(u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, true);
  nvnCommandBufferBindTransformFeedbackBuffer(context->unknown1070.unknown00, 0, unknown10, offset);
  nvnCommandBufferBeginTransformFeedback(context->unknown1070.unknown00, unknown10);
}

void CGLibOneUniformBlock::endStreamOut(u32 count, u32 stride) {
  u32 size = count * stride;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferEndTransformFeedback(context->unknown1070.unknown00, unknown10 + size);
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, false);
  nvnCommandBufferBarrier(context->unknown1070.unknown00, 0x21);
}

u64 CGLibTriUniformBlock_plf::getGPUAdress() const { return unknown20[CGLibManager::s_nTriNowIdx]; }

void CGLibTriUniformBlock_plf::setupUniformBuffer(u32 size, CGLibMemType &memType, u32 offset) {
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown20[0], memType);
  u64 address = unknown20[0] + offset;
  unknown20[0] = address;
  unknown20[1] = address + size;
  unknown20[2] = address + size * 2;
}

CGLibTriUniformBlock::CGLibTriUniformBlock() {}

CGLibTriUniformBlock::~CGLibTriUniformBlock() { release(); }

void CGLibTriUniformBlock::release() {
  unknown20[0] = 0;
  unknown20[1] = 0;
  unknown20[2] = 0;
  CGLibMemHandle::free(unknown38);
  unknown00[0] = nullptr;
  unknown00[1] = nullptr;
  unknown00[2] = nullptr;
}

void CGLibTriUniformBlock::setup(int size) {
  release();
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  CGLibMemHandle::allocUniform(unknown38, alignedSize * 3);
  unknown00[0] = unknown38.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize;
  unknown00[2] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize * 2;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown20[0], unknown38);
  unknown20[1] = unknown20[0] + alignedSize;
  unknown20[2] = unknown20[0] + alignedSize * 2;
}

void CGLibTriUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(unknown38, static_cast<u8 *>(memPool->m_buffer) + offset);
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  unknown00[0] = unknown38.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize;
  unknown00[2] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize * 2;
  unknown20[0] = memPool->unknown08 + offset;
  unknown20[1] = memPool->unknown08 + (alignedSize + offset);
  unknown20[2] = memPool->unknown08 + (alignedSize * 2 + offset);
}

int CGLibTriUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  CGLibMemHandle::setMemBuff(unknown38, static_cast<u8 *>(memType.m_buffer) + offset);
  unknown00[0] = unknown38.m_buffer;
  unknown00[1] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize;
  unknown00[2] = static_cast<u8 *>(unknown38.m_buffer) + alignedSize * 2;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(unknown20[0], memType);
  unknown20[0] += offset;
  unknown20[1] = unknown20[0] + alignedSize;
  unknown20[2] = unknown20[0] + alignedSize * 2;
  return alignedSize * 3;
}

void CGLibTriUniformBlock::updateData() { nn::os::FlushDataCache(unknown00[CGLibManager::s_nTriNowIdx], m_size); }

void CGLibTriUniformBlock::updateData(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(unknown00[CGLibManager::s_nTriNowIdx]) + offset, size); }

void CGLibTriUniformBlock::updateOldData() {
  int index = CGLibManager::s_nTriNowIdx;
  nn::os::FlushDataCache(unknown00[index < 1 ? 2 : index - 1], m_size);
}

void CGLibTriUniformBlock::updateOldData(u32 offset, u32 size) {
  int index = CGLibManager::s_nTriNowIdx;
  nn::os::FlushDataCache(static_cast<u8 *>(unknown00[index < 1 ? 2 : index - 1]) + offset, size);
}

void *CGLibTriUniformBlock::getBuff() { return unknown00[CGLibManager::s_nTriNowIdx]; }

void *CGLibTriUniformBlock::getOldBuff() {
  int index = CGLibManager::s_nTriNowIdx;
  return unknown00[index < 1 ? 2 : index - 1];
}

void *CGLibTriUniformBlock::getOldTriBuff() {
  int index = CGLibManager::s_nTriNowIdx;
  return unknown00[index > 1 ? 0 : index + 1];
}

void CGLibTriUniformBlock::setUniformBlock(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, getGPUAdress(), m_size);
}

void CGLibTriUniformBlock::setStorageBuffer(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, getGPUAdress(), m_size);
}

void CGLibTriUniformBlock::setUniformBlock(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, getGPUAdress() + offset, size);
}

void CGLibTriUniformBlock::setStorageBuffer(u32 index, u32 offset, u32 size) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, getGPUAdress() + offset, size);
}

void CGLibTriUniformBlock::setOldUniformBlock(u32 index) {
  int oldIndex = CGLibManager::s_nTriNowIdx - 1;
  if (oldIndex < 0) {
    oldIndex = 2;
  }
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown20[oldIndex], m_size);
}

void *CGLibTriUniformBlock::getMapping() { return unknown00[CGLibManager::s_nTriNowIdx]; }

void CGLibTriUniformBlock::beginStreamOut(u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, true);
  nvnCommandBufferBindTransformFeedbackBuffer(context->unknown1070.unknown00, 0, unknown20[CGLibManager::s_nTriNowIdx], offset);
  nvnCommandBufferBeginTransformFeedback(context->unknown1070.unknown00, unknown20[CGLibManager::s_nTriNowIdx]);
}

void CGLibTriUniformBlock::endStreamOut(u32 count, u32 stride) {
  u32 size = count * stride;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferEndTransformFeedback(context->unknown1070.unknown00, unknown20[CGLibManager::s_nTriNowIdx] + size);
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, false);
  nvnCommandBufferBarrier(context->unknown1070.unknown00, 0x21);
}

CGLibEtcUniformBlock::~CGLibEtcUniformBlock() {}

void CGLibEtcUniformBlock::updateData(u32 size) {
  m_size = size;
  if (size != 0) {
    context::CGLibSystemContext::get()->nextGlbUniformOfs(size);
  }
}

void CGLibEtcUniformBlock::Rebuilding() { context::CGLibSystemContext::get()->getGlbUniformParam(m_buff, unknown10); }

void CGLibEtcUniformBlock::setMoveMem(u32 size) {
  if (size != 0) {
    m_size = size;
    context::CGLibSystemContext::get()->nextGlbUniformOfs(size);
  }
}

void CGLibEtcUniformBlock::setUniformBlock(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setUniformBlock(index, context->unknown1070.unknown00, unknown10, m_size);
}

void CGLibEtcUniformBlock::setStorageBuffer(u32 index) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1070._98->setStorageBuffer(index, context->unknown1070.unknown00, unknown10, m_size);
}
void CGLibEtcUniformBlock::beginStreamOut(u32 offset) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, true);
  nvnCommandBufferBindTransformFeedbackBuffer(context->unknown1070.unknown00, 0, unknown10, offset);
  nvnCommandBufferBeginTransformFeedback(context->unknown1070.unknown00, unknown10);
}

void CGLibEtcUniformBlock::endStreamOut(u32 count, u32 stride) {
  u32 size = count * stride;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferEndTransformFeedback(context->unknown1070.unknown00, unknown10 + size);
  nvnCommandBufferSetRasterizerDiscard(context->unknown1070.unknown00, false);
  nvnCommandBufferBarrier(context->unknown1070.unknown00, 0x21);
}

void CGLibUniformEtcUtility::setMoveMem() { unknown20.setMoveMem(m_size); }

void CGLibUniformEtcUtility::setUniformBlock() { unknown20.setUniformBlock(unknown10); }

void CGLibUniformEtcUtility::setStorageBuffer() { unknown20.setStorageBuffer(unknown10); }

void CGLibUniBaseUtility::setMoveMem() {}

} // namespace grlib
