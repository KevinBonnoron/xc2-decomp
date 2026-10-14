#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;

struct GfObjPropertyCharacter {
  u8 _00[0x30 - 0x00];
  bool isBattle;
};

static_assert(offsetof(GfObjPropertyCharacter, isBattle) == 0x30, "");

class GfObjProperty {
public:
  virtual ~GfObjProperty();

  GF_OBJ_HANDLE *handle;
  GfObjPropertyCharacter *character;
};

static_assert(offsetof(GfObjProperty, character) == 0x10, "");

} // namespace gf
