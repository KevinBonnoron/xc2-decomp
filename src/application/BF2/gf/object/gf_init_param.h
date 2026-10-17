#pragma once
#include <stddef.h>

#include "types.h"

struct CBdatWrapper;

namespace gf {

enum CharacterType {
  CHARACTER_TYPE_PARTY = 1,
  CHARACTER_TYPE_EVENT = 2,
  CHARACTER_TYPE_EVENT_CS = 3,
  CHARACTER_TYPE_ACT_VIEWER_EVENT = 11,
};

class GfInitParam {
public:
  virtual bool isAllWeapon() const { return false; }
  virtual u32 getBladeID() const { return id; }
  virtual u32 getEnArrangeID() const { return 0; }

  bool isEvent() const {
    switch (characterType) {
    case CHARACTER_TYPE_EVENT:
    case CHARACTER_TYPE_EVENT_CS:
    case CHARACTER_TYPE_ACT_VIEWER_EVENT:
      return true;
    default:
      return false;
    }
  }

  u32 characterType;
  u8 _0c[0x10 - 0x0c];
  u32 id;
  u8 _14[0x18 - 0x14];
  const CBdatWrapper *bdat;
  u8 _20[0x44 - 0x20];
  u16 priority;
};

static_assert(offsetof(GfInitParam, characterType) == 0x08, "");
static_assert(offsetof(GfInitParam, id) == 0x10, "");
static_assert(offsetof(GfInitParam, bdat) == 0x18, "");
static_assert(offsetof(GfInitParam, priority) == 0x44, "");

} // namespace gf
