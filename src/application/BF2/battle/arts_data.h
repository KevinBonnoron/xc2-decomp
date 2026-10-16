#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int ARTS_LEVEL_COUNT = 6;

struct ARTS_DATA {
  enum DATA_TYPE {
    DATA_TYPE_DRIVER,
    DATA_TYPE_BLADE,
    DATA_TYPE_ENEMY,
    DATA_TYPE_BLADE_SPECIAL,
  };

  enum ARTS_TYPE {
    ARTS_TYPE_HEAL = 3,
  };

  struct HIT_DATA {
    u8 frame;
    u8 damageRate;
    u8 reaction;
    u8 effect;
    u8 directionId;
    u8 _05[0x6 - 0x5];
  };

  struct LEVEL_DATA {
    u16 damageMargin;
    u16 recast;
    u16 enhance;
  };

  ARTS_DATA() : id(0) {}
  f32 GetHitWeightRate(int hit) const;

  u64 id : 11;
  u64 name : 11;
  u64 dataType : 2;
  u64 artsType : 5;
  u64 target : 3;
  u64 caption : 11;
  u64 totalDamageRate : 14;
  u64 startRecast : 7;
  u64 : 28;
  u64 loopNum : 4;
  u64 : 32;
  u64 bulletId : 12;
  u64 : 11;
  u64 bulletNum : 5;
  u64 : 36;
  u64 : 64;
  u8 _20[0x30 - 0x20];
  HIT_DATA hits[16];
  LEVEL_DATA levels[ARTS_LEVEL_COUNT];
  u8 _b4[0xe8 - 0xb4];
};

struct ARTS_SLOT_DATA {
  f32 AddRecast(f32 recast, bool isRate);
  void ResetRecast(bool isStart, bool);
  void GetArtsData(ARTS_DATA &data) const;

  u32 id : 11;
  u32 dataType : 3;
  u32 slot : 4;
  u32 baseLevel : 3;
  u32 level : 3;
  u32 characterId : 7;
  u32 isLock : 1;
  f32 recast;
  f32 rate;
  u16 recastFrames[ARTS_LEVEL_COUNT];
};

struct ARTS_PALETTE_DATA {
  void AddAllRecast(f32 recast, bool isRate);
  bool AddArtsRecast(f32 recast, bool isRate, int exceptSlot);
  void AddSupportRecast(f32 recast, bool isRate);
  void ResetAllRecast();
  void ResetArtsRecast(bool isStart);
  void ResetSupportRecast();
  const ARTS_SLOT_DATA *GetSlotDataConst(int slot, bool isTalent) const;
  const ARTS_SLOT_DATA *GetSupportSlotDataConst(int slot) const;
  bool IsEnableHealArts(bool isRecastEnd) const;

  gf::GF_OBJ_HANDLE *user;
  ARTS_SLOT_DATA arts[19];
  ARTS_SLOT_DATA spAttackLevel4;
  ARTS_SLOT_DATA supports[3];
  u32 isBlade : 19;
  u32 : 13;
};

static_assert(sizeof(ARTS_DATA::HIT_DATA) == 0x6, "");
static_assert(offsetof(ARTS_DATA, hits) == 0x30, "");
static_assert(offsetof(ARTS_DATA, levels) == 0x90, "");
static_assert(sizeof(ARTS_DATA) == 0xe8, "");
static_assert(sizeof(ARTS_SLOT_DATA) == 0x18, "");
static_assert(offsetof(ARTS_PALETTE_DATA, spAttackLevel4) == 0x1d0, "");
static_assert(offsetof(ARTS_PALETTE_DATA, supports) == 0x1e8, "");
static_assert(sizeof(ARTS_PALETTE_DATA) == 0x238, "");

} // namespace btl
