#include <string.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
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

} // namespace grlib
