#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct SDataPartyMember {
  u16 unknown00; // Inferred role: driver; original member name unknown.
  u16 unknown02; // Inferred role: hierarchy driver; original member name unknown.
  u16 unknown04; // Inferred role: hierarchy blade; original member name unknown.
};

struct SDataParty {
  SDataPartyMember unknown00[10]; // Inferred role: members; original member name unknown.
  u32 unknown3c;                  // Inferred role: leader object type; original member name unknown.
  u32 unknown40;                  // Inferred role: leader; original member name unknown.
  u32 unknown44;                  // Inferred role: saved leader object type; original member name unknown.
  u32 unknown48;                  // Inferred role: saved leader; original member name unknown.
  u16 unknown4c;                  // Inferred role: party gauge; original member name unknown.
  u16 unknown4e[2];               // Inferred role: clear rex blades; original member name unknown.
  u8 _052[0x054 - 0x052];
};

static_assert(sizeof(SDataPartyMember) == 0x06, "");
static_assert(offsetof(SDataParty, unknown3c) == 0x03c, "");
static_assert(offsetof(SDataParty, unknown40) == 0x040, "");
static_assert(offsetof(SDataParty, unknown4c) == 0x04c, "");
static_assert(offsetof(SDataParty, unknown4e) == 0x04e, "");
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
