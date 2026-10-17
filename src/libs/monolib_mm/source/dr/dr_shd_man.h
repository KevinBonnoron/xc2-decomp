#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdLgtMan;

class DrShdMan {
public:
  DrShdDataList *m_dataList;
  u8 _08[0x18 - 0x08];
  DrShdLgtMan *m_lgtMan;
  DrMan *m_drMan;
};

static_assert(offsetof(DrShdMan, m_lgtMan) == 0x18, "");
static_assert(offsetof(DrShdMan, m_drMan) == 0x20, "");

} // namespace ml
