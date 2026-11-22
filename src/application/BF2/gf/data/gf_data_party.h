#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

// Inferred role: save data party member; original type name unknown.
struct unknown123 {
  u16 m_driver;          // Inferred role: driver; named after the game accessor gf::GfDataParty::getDriver.
  u16 m_hierarchyDriver; // Inferred role: hierarchy driver; named after the game accessor gf::GfGameParty::getHierarchyDriver.
  u16 m_hierarchyBlade;  // Inferred role: hierarchy blade; named after the game accessor gf::GfGameParty::getHierarchyBlade.
};

// Inferred role: save data party; original type name unknown.
struct unknown124 {
  unknown123 m_partyMember[10]; // Inferred role: members; named after the game accessor gf::GfDataParty::getPartyMember.
  u32 unknown3c;                // Inferred role: leader object type; original member name unknown.
  u32 m_leaderBdatID;           // Inferred role: leader; named after the game accessor gf::GfGameParty::getLeaderBdatID.
  u32 unknown44;                // Inferred role: saved leader object type; original member name unknown.
  u32 unknown48;                // Inferred role: saved leader; original member name unknown.
  u16 m_partyGauge;             // Inferred role: party gauge; named after the game accessor gf::GfGameParty::getPartyGauge.
  u16 unknown4e[2];             // Inferred role: clear rex blades; original member name unknown.
  u8 _052[0x054 - 0x052];
};

static_assert(sizeof(unknown123) == 0x06, "");
static_assert(offsetof(unknown124, unknown3c) == 0x03c, "");
static_assert(offsetof(unknown124, m_leaderBdatID) == 0x040, "");
static_assert(offsetof(unknown124, m_partyGauge) == 0x04c, "");
static_assert(offsetof(unknown124, unknown4e) == 0x04e, "");
static_assert(sizeof(unknown124) == 0x054, "");

class GfDataParty {
public:
  static bool isExistBlade(u32 blade);
  static u32 getDriver(u32 member);
  static int getDriverPartyID(u32 driver);
  static bool setDriver(u32 member, u32 driver);
  static unknown124 *getSDataParty();
  static bool isExistDriver(u32 driver);
  static unknown123 *getPartyMember(u32 member);
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
  static bool isActivateMember(u32 chara);
};

} // namespace gf
