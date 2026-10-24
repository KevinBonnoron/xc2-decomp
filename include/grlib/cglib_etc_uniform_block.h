#pragma once
#include <stddef.h>

#include "grlib/cglib_system_context.h"
#include "types.h"

namespace grlib {

class CGLibEtcUniformBlock {
public:
  u8 *getBuff();
  void updateDataMoveOff();
  void setUniformBlock(u32 index);
  void setStorageBuffer(u32 index);
  CGLibEtcUniformBlock() : m_size(0) { context::CGLibSystemContext::get()->getGlbUniformParam(m_buff, unknown10); }
  ~CGLibEtcUniformBlock();
  void updateData(u32 size);
  void Rebuilding();
  void setMoveMem(u32 size);
  void beginStreamOut(u32 size);
  void endStreamOut(u32 count, u32 stride);

  u8 *m_buff;
  int m_size;
  u64 unknown10; // Inferred role: gpu address; original member name unknown.
};

static_assert(offsetof(CGLibEtcUniformBlock, m_size) == 0x8, "");
static_assert(offsetof(CGLibEtcUniformBlock, unknown10) == 0x10, "");
static_assert(sizeof(CGLibEtcUniformBlock) == 0x18, "");

} // namespace grlib
