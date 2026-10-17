#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "nn/os.h"
#include "types.h"

namespace grlib {

CGLibDblUniformBlock::CGLibDblUniformBlock() : m_mappings(), m_gpuAddresses() {}

CGLibDblUniformBlock::~CGLibDblUniformBlock() { release(); }

void CGLibDblUniformBlock::release() {
  CGLibMemHandle::free(m_memType);
  m_mappings[0] = nullptr;
  m_mappings[1] = nullptr;
}

void CGLibDblUniformBlock::setup(int size) {
  release();
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  CGLibMemHandle::allocUniform(m_memType, alignedSize * 2);
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddresses[0], m_memType);
  m_gpuAddresses[1] = m_gpuAddresses[0] + alignedSize;
}

void CGLibDblUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_gpuAddresses[0] = memPool->m_address + offset;
  m_gpuAddresses[1] = memPool->m_address + (alignedSize + offset);
}

int CGLibDblUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memType.m_buffer) + offset);
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddresses[0], memType);
  m_gpuAddresses[0] += offset;
  m_gpuAddresses[1] = m_gpuAddresses[0] + alignedSize;
  return alignedSize * 2;
}

void CGLibDblUniformBlock::updateData() { nn::os::FlushDataCache(m_mappings[CGLibManager::s_nDblNowIdx], m_size); }

void CGLibDblUniformBlock::updateData(u32 offset, u32 size) {
  nn::os::FlushDataCache(static_cast<u8 *>(m_mappings[CGLibManager::s_nDblNowIdx]) + offset, size);
}

void *CGLibDblUniformBlock::getBuff() { return m_mappings[CGLibManager::s_nDblNowIdx]; }

void *CGLibDblUniformBlock::getOldBuff() { return m_mappings[CGLibManager::s_nDblNowIdx == 0]; }

void *CGLibDblUniformBlock::getMapping() { return m_mappings[CGLibManager::s_nDblNowIdx]; }

CGLibOneUniformBlock::CGLibOneUniformBlock() : m_mapping(nullptr), m_gpuAddress(0) {}

CGLibOneUniformBlock::~CGLibOneUniformBlock() { release(); }

void CGLibOneUniformBlock::release() {
  CGLibMemHandle::free(m_memType);
  m_mapping = nullptr;
}

void CGLibOneUniformBlock::setup(int size) {
  release();
  CGLibMemHandle::allocUniform(m_memType, size + (0x100 - size % 0x100) % 0x100);
  m_mapping = m_memType.m_buffer;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddress, m_memType);
}

void CGLibOneUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_mapping = m_memType.m_buffer;
  m_size = size;
  m_gpuAddress = memPool->m_address + offset;
}

int CGLibOneUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memType.m_buffer) + offset);
  m_mapping = m_memType.m_buffer;
  m_size = size;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddress, memType);
  m_gpuAddress += offset;
  return size + (0x100 - size % 0x100) % 0x100;
}

void CGLibOneUniformBlock::setupArray(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  m_mapping = m_memType.m_buffer;
  m_size = size;
  m_gpuAddress = memPool->m_address + offset;
}

void CGLibOneUniformBlock::updateData() { nn::os::FlushDataCache(m_mapping, m_size); }

void CGLibOneUniformBlock::updateData(u32 offset, u32 size) { nn::os::FlushDataCache(static_cast<u8 *>(m_mapping) + offset, size); }

void *CGLibOneUniformBlock::getMapping() { return m_mapping; }

CGLibTriUniformBlock::CGLibTriUniformBlock() : m_mappings(), m_gpuAddresses() {}

CGLibTriUniformBlock::~CGLibTriUniformBlock() { release(); }

void CGLibTriUniformBlock::release() {
  m_gpuAddresses[0] = 0;
  m_gpuAddresses[1] = 0;
  m_gpuAddresses[2] = 0;
  CGLibMemHandle::free(m_memType);
  m_mappings[0] = nullptr;
  m_mappings[1] = nullptr;
  m_mappings[2] = nullptr;
}

void CGLibTriUniformBlock::setup(int size) {
  release();
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  CGLibMemHandle::allocUniform(m_memType, alignedSize * 3);
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_mappings[2] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize * 2;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddresses[0], m_memType);
  m_gpuAddresses[1] = m_gpuAddresses[0] + alignedSize;
  m_gpuAddresses[2] = m_gpuAddresses[0] + alignedSize * 2;
}

void CGLibTriUniformBlock::setup(CGLibVtlMemPool *memPool, u32 size, u32 offset) {
  release();
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memPool->m_buffer) + offset);
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_mappings[2] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize * 2;
  m_gpuAddresses[0] = memPool->m_address + offset;
  m_gpuAddresses[1] = memPool->m_address + (alignedSize + offset);
  m_gpuAddresses[2] = memPool->m_address + (alignedSize * 2 + offset);
}

int CGLibTriUniformBlock::setupArray(int size, CGLibMemType &memType, u32 offset) {
  u32 alignedSize = size + (0x100 - size % 0x100) % 0x100;
  m_size = size;
  CGLibMemHandle::setMemBuff(m_memType, static_cast<u8 *>(memType.m_buffer) + offset);
  m_mappings[0] = m_memType.m_buffer;
  m_mappings[1] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize;
  m_mappings[2] = static_cast<u8 *>(m_memType.m_buffer) + alignedSize * 2;
  context::CGLibSystemContext::get()->getUniformoGpuAddress(m_gpuAddresses[0], memType);
  m_gpuAddresses[0] += offset;
  m_gpuAddresses[1] = m_gpuAddresses[0] + alignedSize;
  m_gpuAddresses[2] = m_gpuAddresses[0] + alignedSize * 2;
  return alignedSize * 3;
}

void CGLibTriUniformBlock::updateData() { nn::os::FlushDataCache(m_mappings[CGLibManager::s_nTriNowIdx], m_size); }

void CGLibTriUniformBlock::updateData(u32 offset, u32 size) {
  nn::os::FlushDataCache(static_cast<u8 *>(m_mappings[CGLibManager::s_nTriNowIdx]) + offset, size);
}

void CGLibTriUniformBlock::updateOldData() {
  int index = CGLibManager::s_nTriNowIdx;
  nn::os::FlushDataCache(m_mappings[index < 1 ? 2 : index - 1], m_size);
}

void CGLibTriUniformBlock::updateOldData(u32 offset, u32 size) {
  int index = CGLibManager::s_nTriNowIdx;
  nn::os::FlushDataCache(static_cast<u8 *>(m_mappings[index < 1 ? 2 : index - 1]) + offset, size);
}

void *CGLibTriUniformBlock::getBuff() { return m_mappings[CGLibManager::s_nTriNowIdx]; }

void *CGLibTriUniformBlock::getOldBuff() {
  int index = CGLibManager::s_nTriNowIdx;
  return m_mappings[index < 1 ? 2 : index - 1];
}

void *CGLibTriUniformBlock::getOldTriBuff() {
  int index = CGLibManager::s_nTriNowIdx;
  return m_mappings[index > 1 ? 0 : index + 1];
}

void *CGLibTriUniformBlock::getMapping() { return m_mappings[CGLibManager::s_nTriNowIdx]; }

} // namespace grlib
