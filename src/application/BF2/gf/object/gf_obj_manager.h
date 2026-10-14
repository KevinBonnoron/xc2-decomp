#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
class GfObjSetup;

class GfObjProperty {
public:
  u8 _00[0x28 - 0x00];
  u32 objType;
};

static_assert(offsetof(GfObjProperty, objType) == 0x28, "");

struct GFOBJ_INFO {
  u8 _00[0x18 - 0x00];
  GfObjProperty *property;
  u8 _20[0x30 - 0x20];
  GfObjSetup *setup;
};

static_assert(offsetof(GFOBJ_INFO, property) == 0x18, "");
static_assert(offsetof(GFOBJ_INFO, setup) == 0x30, "");

class GfObjManager {
public:
  static GFOBJ_INFO *getObjInfo(GF_OBJ_HANDLE *handle);
};

} // namespace gf
