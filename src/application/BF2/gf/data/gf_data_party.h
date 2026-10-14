#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataPartyMember {
  u16 driver;
  u16 hierarchyDriver;
  u16 hierarchyBlade;
};

struct SDataParty {
  SDataPartyMember members[10];
  u8 _03c[0x040 - 0x03c];
  u32 leader;
  u8 _044[0x054 - 0x044];
};

static_assert(sizeof(SDataPartyMember) == 0x06, "");
static_assert(offsetof(SDataParty, leader) == 0x040, "");
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
