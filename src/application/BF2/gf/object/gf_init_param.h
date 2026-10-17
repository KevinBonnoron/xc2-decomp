#pragma once
#include <stddef.h>

#include "types.h"

struct CBdatWrapper;

namespace gf {

enum CharacterType {
  CHARACTER_TYPE_PARTY = 1,
  CHARACTER_TYPE_EVENT = 2,
  CHARACTER_TYPE_EVENT_CS = 3,
  CHARACTER_TYPE_ENEMY_BLADE = 5,
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
  u8 _46[0x48 - 0x46];
  u32 gimmickType;
  u8 _4c[0x83 - 0x4c];
  bool isDeathBlowWeapon;
  u8 _84[0x90 - 0x84];
};

static_assert(offsetof(GfInitParam, characterType) == 0x08, "");
static_assert(offsetof(GfInitParam, id) == 0x10, "");
static_assert(offsetof(GfInitParam, bdat) == 0x18, "");
static_assert(offsetof(GfInitParam, priority) == 0x44, "");
static_assert(offsetof(GfInitParam, gimmickType) == 0x48, "");
static_assert(offsetof(GfInitParam, isDeathBlowWeapon) == 0x83, "");
static_assert(sizeof(GfInitParam) == 0x90, "");

class GfInitParamEnemy : public GfInitParam {
public:
  u32 getBladeID() const override { return bladeId; }
  u32 getEnArrangeID() const override { return enArrangeId; }

  u8 _90[0x9c - 0x90];
  u32 enArrangeId;
  u32 bladeId;
};

static_assert(offsetof(GfInitParamEnemy, enArrangeId) == 0x9c, "");
static_assert(offsetof(GfInitParamEnemy, bladeId) == 0xa0, "");

class GfInitParamGimmick : public GfInitParam {};

class GfInitParamMapObj : public GfInitParam {};

class GfInitParamFobj : public GfInitParam {};

class GfInitParamWeapon : public GfInitParam {};

class GfInitParamEnWeapon : public GfInitParam {};

class GfInitParamBelonging : public GfInitParam {};

class GfInitParamExtra : public GfInitParam {};

} // namespace gf
