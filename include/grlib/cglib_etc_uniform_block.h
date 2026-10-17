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
  CGLibEtcUniformBlock() : m_size(0) { context::CGLibSystemContext::get()->getGlbUniformParam(m_buffer, m_gpuAddress); }
  ~CGLibEtcUniformBlock();
  void updateData(u32 size);
  void Rebuilding();
  void setMoveMem(u32 size);
  void beginStreamOut(u32 size);
  void endStreamOut(u32 count, u32 stride);

  u8 *m_buffer;
  int m_size;
  u64 m_gpuAddress;
};

static_assert(offsetof(CGLibEtcUniformBlock, m_size) == 0x8, "");
static_assert(offsetof(CGLibEtcUniformBlock, m_gpuAddress) == 0x10, "");
static_assert(sizeof(CGLibEtcUniformBlock) == 0x18, "");

} // namespace grlib
