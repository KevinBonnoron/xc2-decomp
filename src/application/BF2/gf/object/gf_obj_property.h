#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;

struct GfObjPropertyCharacter {
  u32 maxHp;
  u32 hp;
  u16 level;
  u8 _0a[0x30 - 0x0a];
  bool isBattle;
};

static_assert(offsetof(GfObjPropertyCharacter, hp) == 0x04, "");
static_assert(offsetof(GfObjPropertyCharacter, level) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter, isBattle) == 0x30, "");

class GfObjProperty {
public:
  virtual ~GfObjProperty();

  GF_OBJ_HANDLE *handle;
  GfObjPropertyCharacter *character;
};

static_assert(offsetof(GfObjProperty, character) == 0x10, "");

} // namespace gf
