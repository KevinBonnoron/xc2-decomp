#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int ARTS_LEVEL_COUNT = 6;
constexpr int SP_ATTACK_LEVEL_4_SLOT = 15;

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
    u8 unknown00; // Inferred role: hit frame; original member name unknown.
    u8 unknown01; // Inferred role: damage rate; original member name unknown.
    u8 unknown02; // Inferred role: reaction; original member name unknown.
    u8 unknown03; // Inferred role: effect; original member name unknown.
    u8 unknown04; // Inferred role: direction id; original member name unknown.
    u8 _05[0x6 - 0x5];
  };

  struct LEVEL_DATA {
    u16 unknown00; // Inferred role: damage margin; original member name unknown.
    u16 unknown02; // Inferred role: recast; original member name unknown.
    u16 unknown04; // Inferred role: enhance id; original member name unknown.
  };

  ARTS_DATA() : unknown00_0(0) {}
  f32 GetHitWeightRate(int hit) const;

  u64 unknown00_0 : 11; // Inferred role: arts id; original member name unknown.
  u64 unknown01_3 : 11; // Inferred role: name id; original member name unknown.
  u64 unknown02_6 : 2;  // Inferred role: data type; original member name unknown.
  u64 unknown03_0 : 5;  // Inferred role: arts type; original member name unknown.
  u64 unknown03_5 : 3;  // Inferred role: target type; original member name unknown.
  u64 unknown04_0 : 11; // Inferred role: caption id; original member name unknown.
  u64 unknown05_3 : 14; // Inferred role: total damage rate; original member name unknown.
  u64 unknown07_1 : 7;  // Inferred role: start recast; original member name unknown.
  u64 : 5;
  u64 unknown08_5 : 6; // Role and original member name unknown.
  u64 : 8;
  u64 unknown0a_3 : 4; // Inferred role: attribute; original member name unknown.
  u64 : 5;
  u64 unknown0b_4 : 4; // Inferred role: loop count; original member name unknown.
  u64 unknown0c_0 : 3; // Inferred role: fight combo id; original member name unknown.
  u64 : 29;
  u64 unknown10_0 : 12; // Inferred role: bullet id; original member name unknown.
  u64 : 11;
  u64 unknown12_7 : 5; // Inferred role: bullet count; original member name unknown.
  u64 : 12;
  u64 unknown15_0 : 4; // Inferred role: IK start number; original member name unknown.
  u64 unknown15_4 : 8; // Inferred role: IK start frame; original member name unknown.
  u64 unknown16_4 : 4; // Inferred role: IK end number; original member name unknown.
  u64 unknown17_0 : 8; // Inferred role: IK end frame; original member name unknown.
  u64 : 32;
  u64 unknown1c_0 : 12; // Inferred role: attack distance; original member name unknown.
  u64 : 20;
  u8 _20[0x2f - 0x20];
  u8 unknown2f_0 : 1; // Inferred role: IK flag; original member name unknown.
  u8 : 7;
  HIT_DATA unknown30[16];                 // Inferred role: hit data; original member name unknown.
  LEVEL_DATA unknown90[ARTS_LEVEL_COUNT]; // Inferred role: level data; original member name unknown.
  u8 _b4[0xe8 - 0xb4];
};

struct ARTS_SLOT_DATA {
  f32 AddRecast(f32 recast, bool isRate);
  void ResetRecast(bool isStart, bool);
  void GetArtsData(ARTS_DATA &data) const;

  u32 unknown00_0 : 11;            // Inferred role: arts id; original member name unknown.
  u32 unknown01_3 : 3;             // Inferred role: data type; original member name unknown.
  u32 unknown01_6 : 4;             // Inferred role: slot; original member name unknown.
  u32 unknown02_2 : 3;             // Inferred role: base level; original member name unknown.
  u32 unknown02_5 : 3;             // Inferred role: level; original member name unknown.
  u32 unknown03_0 : 7;             // Inferred role: character id; original member name unknown.
  u32 unknown03_7 : 1;             // Inferred role: lock flag; original member name unknown.
  f32 unknown04;                   // Inferred role: recast; original member name unknown.
  f32 unknown08;                   // Inferred role: recast rate; original member name unknown.
  u16 unknown0c[ARTS_LEVEL_COUNT]; // Inferred role: recast frames; original member name unknown.
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

  // Inferred role: non-const access to a slot; original name unknown.
  ARTS_SLOT_DATA *unknown001(int slot, bool isTalent) const { return const_cast<ARTS_SLOT_DATA *>(GetSlotDataConst(slot, isTalent)); }

  gf::GF_OBJ_HANDLE *unknown00; // Inferred role: palette user; original member name unknown.
  ARTS_SLOT_DATA unknown08[19]; // Inferred role: arts slots; original member name unknown.
  ARTS_SLOT_DATA unknown1d0;    // Inferred role: level 4 special attack slot; original member name unknown.
  ARTS_SLOT_DATA unknown1e8[3]; // Inferred role: support slots; original member name unknown.
  u32 unknown230_0 : 19;        // Inferred role: blade flag; original member name unknown.
  u32 : 13;
};

static_assert(sizeof(ARTS_DATA::HIT_DATA) == 0x6, "");
static_assert(offsetof(ARTS_DATA, unknown30) == 0x30, "");
static_assert(offsetof(ARTS_DATA, unknown90) == 0x90, "");
static_assert(sizeof(ARTS_DATA) == 0xe8, "");
static_assert(sizeof(ARTS_SLOT_DATA) == 0x18, "");
static_assert(offsetof(ARTS_PALETTE_DATA, unknown1d0) == 0x1d0, "");
static_assert(offsetof(ARTS_PALETTE_DATA, unknown1e8) == 0x1e8, "");
static_assert(sizeof(ARTS_PALETTE_DATA) == 0x238, "");

} // namespace btl
