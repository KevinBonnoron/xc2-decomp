#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMdoSmlShadowObj {
public:
  ~DrMdoSmlShadowObj();

  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,
    FLAG_UNKNOWN_14 = 1 << 14,
  };

  u8 _00[0x08 - 0x00];
  DrMdoSmlShadowObj *unknown08; // Inferred role: next; original member name unknown.
  u8 _10[0x18 - 0x10];
  void *unknown18; // Inferred role: shadow work buffer; original member name unknown.
  u8 _20[0x28 - 0x20];
  u16 unknown28; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrMdoSmlShadowObj, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown28) == 0x28, "");

class DrMdoSmlShadowMan {
public:
  void changeViewNum(DrMdoSmlShadowObj *shadow, int viewNum);
  void shadowRender();
  void releaseObj(DrMdoSmlShadowObj *shadow);
  bool checkDisp();

  u8 _00[0x04 - 0x00];
  s32 unknown04; // Inferred role: view index; original member name unknown.
  u8 _08[0x10 - 0x08];
  DrMdoSmlShadowObj *unknown10[4][2]; // Inferred role: object lists (first and last per view); original member name unknown.
};

static_assert(offsetof(DrMdoSmlShadowMan, unknown04) == 0x04, "");
static_assert(offsetof(DrMdoSmlShadowMan, unknown10) == 0x10, "");

} // namespace ml
