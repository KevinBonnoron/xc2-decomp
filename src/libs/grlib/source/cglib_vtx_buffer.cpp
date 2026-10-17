#include <string.h>

#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_instans.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "nn/os.h"
#include "types.h"

namespace grlib {

CGLibVtxInstans::CGLibVtxInstans() { m_bankOffset = 0; }

CGLibVtxInstans::~CGLibVtxInstans() { release(); }

void CGLibVtxInstans::release() { CGLibMemHandle::free(m_memType); }

void CGLibVtxInstans::createInstansBuffer(int size) {
  release();
  m_size = size;
  m_bankSize = static_cast<u32>(size) / 2;
  CGLibMemHandle::allocVertex(m_memType, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_memType);
}

void CGLibVtxInstans::beginInstansBuff() {
  m_bankOffset = CGLibManager::s_nDblNowIdx * m_bankSize;
  m_writeOffset = 0;
  m_flushedOffset = 0;
}

void CGLibVtxInstans::updateInstansBuff() {
  u32 size = m_writeOffset - m_flushedOffset;
  if (size != 0) {
    nn::os::FlushDataCache(static_cast<u8 *>(m_memType.m_buffer) + (m_bankOffset + m_flushedOffset), size);
    m_flushedOffset = m_writeOffset;
  }
}

void *CGLibVtxInstans::getNextInstansBuff() { return static_cast<u8 *>(m_memType.m_buffer) + (m_writeOffset + m_bankOffset); }

CGLibVtxOneInstans::CGLibVtxOneInstans() {}

CGLibVtxOneInstans::~CGLibVtxOneInstans() { release(); }

void CGLibVtxOneInstans::release() { CGLibMemHandle::free(m_memType); }

void CGLibVtxOneInstans::createInstansBuffer(int size) {
  release();
  m_size = size;
  CGLibMemHandle::allocVertex(m_memType, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_memType);
}

void CGLibVtxOneInstans::beginInstansBuff() {
  m_writeOffset = 0;
  m_flushedOffset = 0;
}

void CGLibVtxOneInstans::updateInstansBuff() {
  if (m_writeOffset != m_flushedOffset) {
    nn::os::FlushDataCache(static_cast<u8 *>(m_memType.m_buffer) + m_flushedOffset, m_writeOffset - m_flushedOffset);
    m_flushedOffset = m_writeOffset;
  }
}

void *CGLibVtxOneInstans::getNextInstansBuff() { return static_cast<u8 *>(m_memType.m_buffer) + m_writeOffset; }

void *CGLibVtxOneInstans::getBuff() { return m_memType.m_buffer; }

CGLibVtxStmOut::CGLibVtxStmOut() {}

CGLibVtxStmOut::~CGLibVtxStmOut() { release(); }

void CGLibVtxStmOut::release() { CGLibMemHandle::free(m_memType); }

int CGLibVtxStmOut::getStreamOutWorkSize() { return 0; }

void CGLibVtxStmOut::createWorkBuff(int size) {
  release();
  int alignedSize = size + (4 - size % 4) % 4;
  CGLibMemHandle::allocVertex(m_memType, alignedSize);
  m_stride = 0;
  m_writtenSize = 0;
  m_bufferSize = alignedSize;
  context::CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_memType);
}

int CGLibVtxStmOut::getSize() { return m_bufferSize; }

void *CGLibVtxStmOut::getBuff() { return m_memType.m_buffer; }

void *CGLibVtxStmOut::getMapping() { return m_memType.m_buffer; }

CGLibVtxVertex::CGLibVtxVertex() : m_size(0), m_stride(0), m_count(0) {}

CGLibVtxVertex::~CGLibVtxVertex() { release(); }

void CGLibVtxVertex::release() { CGLibMemHandle::free(m_memType); }

void CGLibVtxVertex::delayRelease() { context::CGLibSystemContext::get()->releaseDelayVertex(m_memType); }

void CGLibVtxVertex::createVertexBuff(u32 size, u32 stride) {
  release();
  m_count = size / stride;
  m_size = size;
  m_stride = stride;
  CGLibMemHandle::allocVertex(m_memType, size + (4 - size % 4) % 4);
  context::CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_memType);
}

void CGLibVtxVertex::createMemVertexBuff(CGLibVtlMemPool *memPool, u32 offset, u32 size, u32 stride) {
  release();
  m_size = size;
  m_stride = stride;
  m_count = size / stride;
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_gpuAddress = memPool->m_address + offset;
}

void CGLibVtxVertex::createCopyVertexBuff(const void *data, u32 size, u32 stride) {
  release();
  m_count = size / m_stride;
  m_size = size;
  m_stride = stride;
  CGLibMemHandle::allocVertex(m_memType, size + (4 - size % 4) % 4);
  memcpy(m_memType.m_buffer, data, size);
  nn::os::FlushDataCache(m_memType.m_buffer, size);
  context::CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_memType);
}

void CGLibVtxVertex::resetVertexBuff(CGLibVtlMemPool *memPool, u32 offset) {
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_gpuAddress = memPool->m_address + offset;
}

void CGLibVtxVertex::lock(void **buffer, u32 *size) {
  *buffer = m_memType.m_buffer;
  *size = m_size;
}

void CGLibVtxVertex::unlock() { nn::os::FlushDataCache(m_memType.m_buffer, m_size); }

void CGLibVtxVertex::unlock(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(m_memType.m_buffer) + offset, size); }

void CGLibVtxVertex::copyVertexBuff(const void *data) {
  void *buffer = m_memType.m_buffer;
  memcpy(buffer, data, m_size);
  nn::os::FlushDataCache(buffer, m_size);
}

} // namespace grlib
