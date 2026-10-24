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
  u64 *unknown08; // Inferred role: used bits; original member name unknown.
  u32 unknown10;  // Inferred role: unit size; original member name unknown.
  u32 unknown14;  // Inferred role: used num; original member name unknown.
  int unknown18;  // Inferred role: next index; original member name unknown.
  int unknown1c;  // Inferred role: num; original member name unknown.
  u32 unknown20;  // Inferred role: bit word num; original member name unknown.
  u32 unknown24;  // Inferred role: search word; original member name unknown.
};

static_assert(offsetof(CGLibBuffFixAlloc, unknown10) == 0x10, "");
static_assert(offsetof(CGLibBuffFixAlloc, unknown18) == 0x18, "");
static_assert(offsetof(CGLibBuffFixAlloc, unknown24) == 0x24, "");
static_assert(sizeof(CGLibBuffFixAlloc) == 0x28, "");

} // namespace grlib
