#pragma once
#include <stddef.h>

#include "gf/object/gf_append.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

enum CharacterType {
  CHARACTER_TYPE_PARTY = 1,
  CHARACTER_TYPE_EVENT = 2,
  CHARACTER_TYPE_EVENT_CS = 3,
  CHARACTER_TYPE_ENEMY_BLADE = 5,
  CHARACTER_TYPE_EVENT_DRIVER = 6,
  CHARACTER_TYPE_EVENT_BLADE = 7,
  CHARACTER_TYPE_TRINITY_BLADE = 8,
  CHARACTER_TYPE_ACT_VIEWER_EVENT = 11,
  CHARACTER_TYPE_EVENT_NPC = 12,
};

class GfInitParam {
public:
  virtual bool isAllWeapon() const { return false; }
  virtual u32 getBladeID() const { return m_bladeID; }
  virtual u32 getEnArrangeID() const;

  bool isEvent() const {
    switch (unknown08) {
    case CHARACTER_TYPE_EVENT:
    case CHARACTER_TYPE_EVENT_CS:
    case CHARACTER_TYPE_ACT_VIEWER_EVENT:
      return true;
    default:
      return false;
    }
  }

  u32 unknown08; // Inferred role: character type; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u32 m_bladeID;
  u8 _14[0x18 - 0x14];
  const CBdatWrapper *unknown18; // Inferred role: bdat; original member name unknown.
  u8 _20[0x40 - 0x20];
  u32 unknown40; // Inferred role: layer; original member name unknown.
  u16 unknown44; // Inferred role: priority; original member name unknown.
  u8 _46[0x48 - 0x46];
  u32 unknown48; // Inferred role: gimmick type; original member name unknown.
  u8 _4c[0x83 - 0x4c];
  bool unknown83; // Inferred role: death blow weapon; original member name unknown.
  u8 _84[0x90 - 0x84];
};

static_assert(offsetof(GfInitParam, unknown08) == 0x08, "");
static_assert(offsetof(GfInitParam, m_bladeID) == 0x10, "");
static_assert(offsetof(GfInitParam, unknown18) == 0x18, "");
static_assert(offsetof(GfInitParam, unknown40) == 0x40, "");
static_assert(offsetof(GfInitParam, unknown44) == 0x44, "");
static_assert(offsetof(GfInitParam, unknown48) == 0x48, "");
static_assert(offsetof(GfInitParam, unknown83) == 0x83, "");
static_assert(sizeof(GfInitParam) == 0x90, "");

class GfInitParamDriver : public GfInitParam {
public:
  struct Weapon {
    s8 unknown00; // Inferred role: slot; original member name unknown.
    u8 unknown01; // Inferred role: weapon type; original member name unknown.
    u8 unknown02; // Inferred role: attribute; original member name unknown.
    u8 _03[0x04 - 0x03];
    u16 unknown04; // Inferred role: blade; original member name unknown.
    u8 _06[0x08 - 0x06];
  };

  static const u32 WEAPON_MAX = 32;

  u8 _90[0x98 - 0x90];
  mm::mtl::FixedVector<Weapon, WEAPON_MAX> unknown98; // Inferred role: weapons; original member name unknown.
};

static_assert(sizeof(GfInitParamDriver::Weapon) == 0x08, "");
static_assert(offsetof(GfInitParamDriver, unknown98) == 0x98, "");

class GfInitParamEnemy : public GfInitParam {
public:
  u32 getBladeID() const override { return m_bladeID; }
  u32 getEnArrangeID() const override { return m_enArrangeID; }

  u8 _90[0x9c - 0x90];
  u32 m_enArrangeID;
  u32 m_bladeID;
};

static_assert(offsetof(GfInitParamEnemy, m_enArrangeID) == 0x9c, "");
static_assert(offsetof(GfInitParamEnemy, m_bladeID) == 0xa0, "");

class GfInitParamNpc : public GfInitParam {};

class GfInitParamMob : public GfInitParam {};

class GfInitParamGimmick : public GfInitParam {};

class GfInitParamMapObj : public GfInitParam {};

class GfInitParamFobj : public GfInitParam {};

class GfInitParamWeapon : public GfInitParam {
public:
  u8 _90[0x98 - 0x90];
  GfAppend unknown98; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamWeapon, unknown98) == 0x98, "");

class GfInitParamEnWeapon : public GfInitParam {
public:
  u32 getEnArrangeID() const override;

  u8 _90[0x98 - 0x90];
  GfAppend unknown98; // Inferred role: append; original member name unknown.
  u32 m_enArrangeID;
};

static_assert(offsetof(GfInitParamEnWeapon, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamEnWeapon, m_enArrangeID) == 0x120, "");

class GfInitParamBelonging : public GfInitParam {
public:
  GfAppend unknown90; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamBelonging, unknown90) == 0x90, "");

class GfInitParamExtra : public GfInitParam {
public:
  GfAppend unknown90; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamExtra, unknown90) == 0x90, "");

class GfInitParamMapSeamless : public GfInitParam {
public:
  bool unknown90;        // Inferred role: use map id; original member name unknown.
  const char *unknown98; // Inferred role: model path; original member name unknown.
};

static_assert(offsetof(GfInitParamMapSeamless, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamMapSeamless, unknown98) == 0x98, "");

class GfInitParamMap : public GfInitParam {
public:
  mm::mtl::FixStr<256> unknown90; // Inferred role: path; original member name unknown.
};

static_assert(offsetof(GfInitParamMap, unknown90) == 0x90, "");

class GfInitParamEventObj : public GfInitParam {};

class GfInitParamUiObj : public GfInitParam {};

} // namespace gf
