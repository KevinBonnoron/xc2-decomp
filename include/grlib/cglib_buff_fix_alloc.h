#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibBuffFixAlloc {
public:
  static const u32 AllocERR;

  void freeBuffer(void *buffer);
  CGLibBuffFixAlloc();
  ~CGLibBuffFixAlloc();
  void releaseTbl();
  void setupTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 alignment);
  void setupTbl(mtl::ALLOC_HANDLE tableHandle, u32 num, u32 unitSize);
  void setupFixTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 bufferSize, u32 alignment);
  u32 allocID();
  u32 createBuff();
  u32 allocSub();
  void freeID(u32 id);

  u8 *m_buffer;
  u64 *m_usedBits;
  u32 m_unitSize;
  u32 m_usedNum;
  int m_nextIndex;
  int m_num;
  u32 m_bitWordNum;
  u32 m_searchWord;
};

static_assert(offsetof(CGLibBuffFixAlloc, m_unitSize) == 0x10, "");
static_assert(offsetof(CGLibBuffFixAlloc, m_nextIndex) == 0x18, "");
static_assert(offsetof(CGLibBuffFixAlloc, m_searchWord) == 0x24, "");
static_assert(sizeof(CGLibBuffFixAlloc) == 0x28, "");

} // namespace grlib
