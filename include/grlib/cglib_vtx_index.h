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
    u32 count = m_count;
    int size;
    switch (m_format) {
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

  u32 m_count;
  GrlIndexFormat m_format;
  GrlPrimitiveType m_type;
  CGLibMemType m_memType;
  u64 m_gpuAddress;
};

static_assert(offsetof(CGLibVtxIndex, m_memType) == 0x10, "");
static_assert(offsetof(CGLibVtxIndex, m_gpuAddress) == 0x20, "");
static_assert(sizeof(CGLibVtxIndex) == 0x28, "");

} // namespace grlib
