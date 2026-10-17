#pragma once
#include <stddef.h>

#include "gf/game/gf_game_party.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct RQ_SETUP_PARTY {
  struct Member {
    Member() { clear(); }

    void clear() {
      driver = 0;
      bladeSet = -1;
      for (u32 slot = 0; slot < 5; slot++) {
        blades[slot] = 0;
      }
      _12[0] = 0;
    }

    u32 driver;
    int bladeSet;
    u16 blades[5];
    u8 _12[0x13 - 0x12];
  };

  RQ_SETUP_PARTY() : leaderObjectType(0), leader(0), savedLeaderObjectType(0), savedLeader(0), _d8() {
    for (u32 index = 0; index < 10; index++) {
      members[index].clear();
    }
  }

  void replaceActBlade();

  Member members[10];
  u32 leaderObjectType;
  u32 leader;
  u32 savedLeaderObjectType;
  u32 savedLeader;
  u8 _d8[0xd9 - 0xd8];
  GfPartyPosInfo positions;
};

static_assert(sizeof(RQ_SETUP_PARTY::Member) == 0x14, "");
static_assert(offsetof(RQ_SETUP_PARTY, leaderObjectType) == 0xc8, "");
static_assert(offsetof(RQ_SETUP_PARTY, positions) == 0xe0, "");
static_assert(sizeof(RQ_SETUP_PARTY) == 0x1a0, "");

struct RQ_SETUP_PARTY_DRIVER {
  u16 drivers[10];
  u32 leader;
};

static_assert(offsetof(RQ_SETUP_PARTY_DRIVER, leader) == 0x14, "");

struct GfMapjumpInfo {
  GfMapjumpInfo()
      : mapjumpId(0), map(0), landmarkId(-1), partyCreateRate(1.0f), isWithSaveData(false), isNoFadeIn(false), isNoFadeOut(false), _103(),
        isSkipTravel(false), jumpType(0) {}

  void setupForSaveData(u32 mapjumpId, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isStartChapterSave);

  u32 mapjumpId;
  u32 map;
  int landmarkId;
  f32 partyCreateRate;
  mm::mtl::FixStr<32> mapScript;
  GfPartyPosInfo partyPos;
  bool isWithSaveData;
  bool isNoFadeIn;
  bool isNoFadeOut;
  u8 _103[0x104 - 0x103];
  bool isSkipTravel;
  u32 jumpType;
};

static_assert(offsetof(GfMapjumpInfo, mapScript) == 0x10, "");
static_assert(offsetof(GfMapjumpInfo, partyPos) == 0x40, "");
static_assert(offsetof(GfMapjumpInfo, isWithSaveData) == 0x100, "");
static_assert(offsetof(GfMapjumpInfo, isSkipTravel) == 0x104, "");
static_assert(offsetof(GfMapjumpInfo, jumpType) == 0x108, "");
static_assert(sizeof(GfMapjumpInfo) == 0x110, "");

class GfReqCommand {
public:
  static void reqPartyBlade(u32 blade, u32 driver);
  static void reqRebuildPartyWeapon(u32 blade);
  static void reqChangeAttribute(u32 objectType, u32 blade, u32 attribute);
  static void reqDestroyGf();
};

} // namespace gf
