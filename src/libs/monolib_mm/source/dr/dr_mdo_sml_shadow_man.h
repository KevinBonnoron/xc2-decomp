#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMan;

// Inferred role: header of the shadow data (node count first); original name unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: node count; original member name unknown.
};

class DrMdoSmlShadowObj {
public:
  DrMdoSmlShadowObj(int viewNum, const u8 *data, DrMan *man);
  ~DrMdoSmlShadowObj();

  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,
    FLAG_UNKNOWN_14 = 1 << 14,
  };

  DrMdoSmlShadowObj *unknown00; // Inferred role: previous; original member name unknown.
  DrMdoSmlShadowObj *unknown08; // Inferred role: next; original member name unknown.
  const unknown002 *unknown10;  // Inferred role: shadow data; original member name unknown.
  void *unknown18;              // Inferred role: shadow work buffer; original member name unknown.
  void *unknown20;              // Inferred role: shadow work buffer in use; original member name unknown.
  u16 unknown28;                // Inferred role: flags; original member name unknown.
  s16 unknown2a;                // Inferred role: view number; original member name unknown.
};

static_assert(offsetof(DrMdoSmlShadowObj, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoSmlShadowObj, unknown2a) == 0x2a, "");

class DrMdoSmlShadowMan {
public:
  DrMdoSmlShadowMan(DrMan *man);
  ~DrMdoSmlShadowMan();
  void changeViewNum(DrMdoSmlShadowObj *shadow, int viewNum);
  void shadowRender();
  void releaseObj(DrMdoSmlShadowObj *shadow);
  void delObjList();
  bool checkDisp();

  u32 unknown00;                      // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s32 unknown04;                      // Inferred role: view index; original member name unknown.
  DrMan *unknown08;                   // Inferred role: owner; original member name unknown.
  DrMdoSmlShadowObj *unknown10[4][2]; // Inferred role: object lists (first and last per view); original member name unknown.
  DrMdoSmlShadowObj *unknown50[2][2]; // Inferred role: added object lists (first and last per buffer); original member name unknown.
  DrMdoSmlShadowObj *unknown70[2];    // Inferred role: object list to delete (first and last); original member name unknown.
};

static_assert(offsetof(DrMdoSmlShadowMan, unknown04) == 0x04, "");
static_assert(offsetof(DrMdoSmlShadowMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoSmlShadowMan, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoSmlShadowMan, unknown50) == 0x50, "");
static_assert(offsetof(DrMdoSmlShadowMan, unknown70) == 0x70, "");

} // namespace ml
