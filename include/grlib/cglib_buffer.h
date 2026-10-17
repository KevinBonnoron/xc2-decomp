#pragma once
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

class CGLibMemPool;

class CGLibBuffer {
public:
  CGLibBuffer();
  ~CGLibBuffer();
  void release();
  void setup(u32 offset, u32 size, CGLibMemPool &memPool);
  void updateData();
  void setUniformBlock(u32 index);
  void setStorageBuffer(u32 index);
  void updateMaping();

  NVNbuffer m_buffer;
};

} // namespace grlib
