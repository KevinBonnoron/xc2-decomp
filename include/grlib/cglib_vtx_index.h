#pragma once
#include <stddef.h>

#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_mem_handle.h"
#include "types.h"

enum GrlIndexFormat {
  GRL_INDEX_FORMAT_U8,
  GRL_INDEX_FORMAT_U16,
  GRL_INDEX_FORMAT_U32,
};

namespace grlib {

class CGLibOneUniformBlock;
class CGLibVtlMemPool;

class CGLibVtxIndex {
public:
  CGLibVtxIndex();
  ~CGLibVtxIndex();
  void release();
  void createIndexBuff(u32 count, GrlPrimitiveType type, GrlIndexFormat format);
  void createMemIndexBuff(CGLibVtlMemPool *memPool, u32 offset, u32 count, GrlPrimitiveType type, GrlIndexFormat format);
  void createCopyIndexBuff(const void *data, u32 count, GrlPrimitiveType type, GrlIndexFormat format);
  void resetIndexBuff(CGLibVtlMemPool *memPool, u32 offset);
  void drawIndex();
  void drawIndex(u32 count, u32 offset);
  void drawInsIndex(int instanceCount);
  void drawInsIndex(int instanceCount, u32 count, u32 offset);
  void drawIndirect(const CGLibOneUniformBlock &block, u32 offset);
  void lock(void **buffer, u32 *size);
  void unlock();
  void copyIndexBuff(const void *data);

  int getSize() const {
    u32 count = unknown00;
    int size;
    switch (unknown04) {
    case GRL_INDEX_FORMAT_U16:
      size = count * 2;
      break;
    case GRL_INDEX_FORMAT_U32:
      size = count * 4;
      break;
    default:
      size = count;
      break;
    }
    return size;
  }

  u32 unknown00;              // Inferred role: count; original member name unknown.
  GrlIndexFormat unknown04;   // Inferred role: format; original member name unknown.
  GrlPrimitiveType unknown08; // Inferred role: type; original member name unknown.
  CGLibMemType unknown10;     // Inferred role: mem type; original member name unknown.
  u64 unknown20;              // Inferred role: gpu address; original member name unknown.
};

static_assert(offsetof(CGLibVtxIndex, unknown10) == 0x10, "");
static_assert(offsetof(CGLibVtxIndex, unknown20) == 0x20, "");
static_assert(sizeof(CGLibVtxIndex) == 0x28, "");

} // namespace grlib
