#pragma once
#include "gf/game/gf_game_party.h"
#include "types.h"
#include <stddef.h>

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

class GfReqCommand {
public:
  static void reqPartyBlade(u32 blade, u32 driver);
  static void reqRebuildPartyWeapon(u32 blade);
  static void reqChangeAttribute(u32 objectType, u32 blade, u32 attribute);
};

} // namespace gf
