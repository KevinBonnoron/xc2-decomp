#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdFetchMan;
class DrShdLgtMan;

class DrShdMan {
public:
  void debugRender();
  void beforeUpdateCate(int cate);
  void resetColorBuff(int index);

  DrShdDataList *unknown00; // Inferred role: data list; original member name unknown.
  u8 _08[0x10 - 0x08];
  DrShdFetchMan *unknown10; // Inferred role: fetch man (DrShdMdoDecRes::releaseObj 0x71008a152c); original member name unknown.
  DrShdLgtMan *unknown18;   // Inferred role: lgt man; original member name unknown.
  DrMan *unknown20;         // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(DrShdMan, unknown10) == 0x10, "");
static_assert(offsetof(DrShdMan, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMan, unknown20) == 0x20, "");

} // namespace ml
