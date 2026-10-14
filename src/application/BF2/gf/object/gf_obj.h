#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
struct GFOBJ_INFO;

class GfObj {
public:
  u8 _00[0x28 - 0x00];
  u32 objType;
  u32 layer;
  u8 _30[0xf8 - 0x30];
  GF_OBJ_HANDLE *handle;
  GFOBJ_INFO *info;
};

static_assert(offsetof(GfObj, objType) == 0x28, "");
static_assert(offsetof(GfObj, layer) == 0x2c, "");
static_assert(offsetof(GfObj, handle) == 0xf8, "");
static_assert(offsetof(GfObj, info) == 0x100, "");

} // namespace gf
