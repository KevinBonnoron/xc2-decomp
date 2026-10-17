#include <string.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_buff_mem_pool_tbl.h"
#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_buffer.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

void CGLibBuffFixAlloc::freeBuffer(void *buffer) {
  u32 index = static_cast<u64>(static_cast<u8 *>(buffer) - m_buffer) / m_unitSize;
  m_usedBits[index >> 6] &= ~(1ul << (index & 0x3f));
  m_usedNum--;
}

CGLibBuffFixAlloc::CGLibBuffFixAlloc() : m_buffer(nullptr), m_usedBits(nullptr), m_nextIndex(0), m_num(0) {}

CGLibBuffFixAlloc::~CGLibBuffFixAlloc() { releaseTbl(); }

void CGLibBuffFixAlloc::releaseTbl() {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  if (m_usedBits != nullptr) {
    mtl::MemManager::deallocate(m_usedBits, 0, false);
    m_usedBits = nullptr;
  }
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  u32 bufferSize = m_unitSize * m_num;
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, u32 num, u32 unitSize) {
  releaseTbl();
  m_unitSize = unitSize;
  u32 wordNum = num / 64 + (num % 64 != 0 ? 1 : 0);
  m_num = num;
  m_bitWordNum = wordNum;
  u32 tableSize = wordNum * sizeof(u64);
  m_usedBits = static_cast<u64 *>(mtl::MemManager::allocate(tableHandle, tableSize, 16, false, "no name", 0));
  m_searchWord = 0;
  m_usedNum = 0;
  m_nextIndex = 0;
  memset(m_usedBits, 0, tableSize);
}

void CGLibBuffFixAlloc::setupFixTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 bufferSize,
                                    u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::freeID(u32 id) {
  m_usedBits[id >> 6] &= ~(1ul << (static_cast<u64>(id) & 0x3f));
  m_usedNum--;
}

CGLibBuffTexture::CGLibBuffTexture() : m_textures(nullptr) {}

CGLibBuffTexture::~CGLibBuffTexture() { release(); }

void CGLibBuffTexture::release() {
  m_textures = nullptr;
  releaseTbl();
}

void CGLibBuffTexture::createTexture(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0xc0, 0x10);
  m_textures = m_buffer;
}

CGLibBuffMemPoolTbl::CGLibBuffMemPoolTbl() {}

CGLibBuffMemPoolTbl::~CGLibBuffMemPoolTbl() { release(); }

void CGLibBuffMemPoolTbl::release() { releaseTbl(); }

void CGLibBuffMemPoolTbl::createMemPoolTbl(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0x100, 0x100);
}

CGLibBuffer::CGLibBuffer() {}

CGLibBuffer::~CGLibBuffer() { nvnBufferFinalize(&m_buffer); }

void CGLibBuffer::release() { nvnBufferFinalize(&m_buffer); }

void CGLibBuffer::setup(u32 offset, u32 size, CGLibMemPool &memPool) {
  nvnBufferFinalize(&m_buffer);
  NVNbufferBuilder builder;
  nvnBufferBuilderSetDefaults(&builder);
  nvnBufferBuilderSetDevice(&builder, &CGLibManager::get()->m_device);
  nvnBufferBuilderSetStorage(&builder, memPool.m_memoryPool, offset, size);
  nvnBufferInitialize(&m_buffer, &builder);
}

void CGLibBuffer::updateData() {}

void CGLibBuffer::setUniformBlock(u32 index) {}

void CGLibBuffer::setStorageBuffer(u32 index) {}

void CGLibBuffer::updateMaping() {}

CGLibVtlMemPool::CGLibVtlMemPool() {
  m_size = 0;
  m_buffer = nullptr;
  m_isOwnPool = false;
  m_offset = 0;
}

CGLibVtlMemPool::~CGLibVtlMemPool() { release(); }

void CGLibVtlMemPool::release() {
  if (m_isOwnPool) {
    nvnMemoryPoolFinalize(m_memoryPool);
    context::CGLibSystemContext::get()->m_buffMemPoolTbl.freeBuffer(m_memoryPool);
  }
  m_size = 0;
  m_buffer = nullptr;
  m_isOwnPool = false;
  m_offset = 0;
}

void CGLibVtlMemPool::delayRelease() {
  if (m_isOwnPool) {
    context::CGLibSystemContext::get()->releaseDelayMempool(m_memoryPool, nullptr);
  }
  m_size = 0;
  m_buffer = nullptr;
  m_isOwnPool = false;
  m_offset = 0;
}

} // namespace grlib
