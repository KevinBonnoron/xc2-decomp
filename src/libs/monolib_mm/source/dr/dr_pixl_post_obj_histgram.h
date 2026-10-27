#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResUseQueryObj;

class DrPixlPostObjHistgram {
public:
  ~DrPixlPostObjHistgram();
  void render();
  f32 getMaxLuminance() const;
  int getSectionNum() const;
  f32 getPercentage(u32 index) const;

  u8 _00[0x18];
  DrResUseQueryObj *unknown18; // Inferred role: occlusion query; original member name unknown.
  f32 unknown20[10];           // Inferred role: section boundaries; original member name unknown.
  u8 _48[0x4c - 0x48];
  f32 m_percentage[16];
};

static_assert(offsetof(DrPixlPostObjHistgram, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjHistgram, m_percentage) == 0x4c, "");

} // namespace ml
