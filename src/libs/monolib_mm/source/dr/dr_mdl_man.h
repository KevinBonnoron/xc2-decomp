#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMdlMan {
public:
  void renderBegin();
  void setGroupsDisp(s32 group, bool disp);
  static void getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);

  u8 _000[0x23c - 0x000];
  u32 m_groupsDisp;
};

static_assert(offsetof(DrMdlMan, m_groupsDisp) == 0x23c, "");

} // namespace ml
