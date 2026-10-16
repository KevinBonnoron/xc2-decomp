#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct SDataPartyMember {
  u16 driver;
  u16 hierarchyDriver;
  u16 hierarchyBlade;
};

struct SDataParty {
  SDataPartyMember members[10];
  u32 leaderObjectType;
  u32 leader;
  u32 savedLeaderObjectType;
  u32 savedLeader;
  u16 partyGauge;
  u8 _04e[0x054 - 0x04e];
};

static_assert(sizeof(SDataPartyMember) == 0x06, "");
static_assert(offsetof(SDataParty, leaderObjectType) == 0x03c, "");
static_assert(offsetof(SDataParty, leader) == 0x040, "");
static_assert(offsetof(SDataParty, partyGauge) == 0x04c, "");
static_assert(sizeof(SDataParty) == 0x054, "");

class GfDataParty {
public:
  static bool isExistBlade(u32 blade);
  static u32 getDriver(u32 member);
  static int getDriverPartyID(u32 driver);
  static bool setDriver(u32 member, u32 driver);
  static SDataParty *getSDataParty();
  static bool isExistDriver(u32 driver);
  static SDataPartyMember *getPartyMember(u32 member);
  static mm::Vec3 *getSavePos(u32 member, bool isDriver);
  static mm::Vec3 *getSaveRot(u32 member, bool isDriver);
  static bool isEmptyDriver();
  static bool isExistBlade(u32 member, u32 blade);
  static bool empty();
  static u32 getFixedHandleForDriver(u32 member);
  static u32 getFixedHandleForBlade(u32 member, int slot);
  static u32 getFixedHandleForWeapon(u32 member, int slot, u32 weapon);
  static void getDriver(mm::mtl::FixedArray<u16, 10> &drivers);
  static bool isNiaByakko(u32 member);
  static bool isRideChar(u32 chara);
  static bool isLeader(u32 chara);
};

} // namespace gf
