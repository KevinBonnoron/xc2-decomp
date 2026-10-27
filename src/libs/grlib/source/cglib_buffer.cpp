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
  u32 index = static_cast<u64>(static_cast<u8 *>(buffer) - m_buffer) / unknown10;
  unknown08[index >> 6] &= ~(1ul << (index & 0x3f));
  unknown14--;
}

CGLibBuffFixAlloc::CGLibBuffFixAlloc() : m_buffer(nullptr), unknown08(nullptr), unknown18(0), unknown1c(0) {}

CGLibBuffFixAlloc::~CGLibBuffFixAlloc() { releaseTbl(); }

void CGLibBuffFixAlloc::releaseTbl() {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  u32 bufferSize = unknown10 * unknown1c;
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, u32 num, u32 unitSize) {
  releaseTbl();
  unknown10 = unitSize;
  u32 wordNum = num / 64 + (num % 64 != 0 ? 1 : 0);
  unknown1c = num;
  unknown20 = wordNum;
  u32 tableSize = wordNum * sizeof(u64);
  unknown08 = static_cast<u64 *>(mtl::MemManager::allocate(tableHandle, tableSize, 16, false, "no name", 0));
  unknown24 = 0;
  unknown14 = 0;
  unknown18 = 0;
  memset(unknown08, 0, tableSize);
}

void CGLibBuffFixAlloc::setupFixTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 bufferSize, u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::freeID(u32 id) {
  unknown08[id >> 6] &= ~(1ul << (static_cast<u64>(id) & 0x3f));
  unknown14--;
}

u32 CGLibBuffFixAlloc::createBuff() {
  unknown08[unknown18 >> 6] |= 1ul << (unknown18 & 0x3f);
  int id = unknown18;
  if (id + 1 < unknown1c) {
    unknown18 = id + 1;
  } else {
    unknown18 = 0;
  }
  unknown24 = unknown18 >> 6;
  unknown14++;
  return id;
}

CGLibBuffTexture::CGLibBuffTexture() : unknown28(nullptr) {}

CGLibBuffTexture::~CGLibBuffTexture() { release(); }

void CGLibBuffTexture::release() {
  unknown28 = nullptr;
  releaseTbl();
}

void CGLibBuffTexture::createTexture(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0xc0, 0x10);
  unknown28 = m_buffer;
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
  nvnBufferBuilderSetDevice(&builder, &CGLibManager::get()->unknown08);
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
  unknown20 = false;
  unknown18 = 0;
}

CGLibVtlMemPool::~CGLibVtlMemPool() { release(); }

void CGLibVtlMemPool::release() {
  if (unknown20) {
    nvnMemoryPoolFinalize(unknown00);
    context::CGLibSystemContext::get()->unknowne90.freeBuffer(unknown00);
  }
  m_size = 0;
  m_buffer = nullptr;
  unknown20 = false;
  unknown18 = 0;
}

void CGLibVtlMemPool::delayRelease() {
  if (unknown20) {
    context::CGLibSystemContext::get()->releaseDelayMempool(unknown00, nullptr);
  }
  m_size = 0;
  m_buffer = nullptr;
  unknown20 = false;
  unknown18 = 0;
}

} // namespace grlib
