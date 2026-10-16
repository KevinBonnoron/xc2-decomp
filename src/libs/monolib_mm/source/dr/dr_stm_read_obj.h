#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrStmReadObj {
public:
  virtual ~DrStmReadObj();
  virtual void release();
  virtual void update();
  virtual u32 getAdder();

  u8 _08[0x18 - 0x08];
  u32 m_readType;
};

static_assert(offsetof(DrStmReadObj, m_readType) == 0x18, "");

} // namespace ml
