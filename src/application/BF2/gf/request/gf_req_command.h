#pragma once
#include <stddef.h>

#include "gf/game/gf_game_party.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
struct GfReqParam;

struct RQ_SETUP_PARTY {
  struct Member {
    Member() { clear(); }

    void clear() {
      unknown00 = 0;
      unknown04 = -1;
      for (u32 slot = 0; slot < 5; slot++) {
        unknown08[slot] = 0;
      }
      _12[0] = 0;
    }

    u32 unknown00;    // Inferred role: driver; original member name unknown.
    int unknown04;    // Inferred role: blade set; original member name unknown.
    u16 unknown08[5]; // Inferred role: blades; original member name unknown.
    u8 _12[0x13 - 0x12];
  };

  RQ_SETUP_PARTY() : unknownc8(0), unknowncc(0), unknownd0(0), unknownd4(0), _d8() {
    for (u32 index = 0; index < 10; index++) {
      unknown00[index].clear();
    }
  }

  void replaceActBlade();

  Member unknown00[10]; // Inferred role: members; original member name unknown.
  u32 unknownc8;        // Inferred role: leader object type; original member name unknown.
  u32 unknowncc;        // Inferred role: leader; original member name unknown.
  u32 unknownd0;        // Inferred role: saved leader object type; original member name unknown.
  u32 unknownd4;        // Inferred role: saved leader; original member name unknown.
  u8 _d8[0xd9 - 0xd8];
  GfPartyPosInfo unknowne0; // Inferred role: positions; original member name unknown.
};

static_assert(sizeof(RQ_SETUP_PARTY::Member) == 0x14, "");
static_assert(offsetof(RQ_SETUP_PARTY, unknownc8) == 0xc8, "");
static_assert(offsetof(RQ_SETUP_PARTY, unknowne0) == 0xe0, "");
static_assert(sizeof(RQ_SETUP_PARTY) == 0x1a0, "");

struct RQ_SETUP_PARTY_DRIVER {
  u16 unknown00[10]; // Inferred role: drivers; original member name unknown.
  u32 unknown14;     // Inferred role: leader; original member name unknown.
};

static_assert(offsetof(RQ_SETUP_PARTY_DRIVER, unknown14) == 0x14, "");

struct GfMapjumpInfo {
  explicit GfMapjumpInfo(u32 mapjumpId = 0)
      : unknown00(mapjumpId), unknown04(0), unknown08(-1), unknown0c(1.0f), unknown100(false), unknown101(false), unknown102(false), _103(), unknown104(false), unknown108(0) {}

  void setupForSaveData(u32 mapjumpId, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isStartChapterSave);

  void setMapjump(u32 mapjumpId) {
    this->unknown00 = mapjumpId;
    unknown04 = 0;
  }

  u32 unknown00;                 // Inferred role: mapjump id; original member name unknown.
  u32 unknown04;                 // Inferred role: map; original member name unknown.
  int unknown08;                 // Inferred role: landmark id; original member name unknown.
  f32 unknown0c;                 // Inferred role: party create rate; original member name unknown.
  mm::mtl::FixStr<32> unknown10; // Inferred role: map script; original member name unknown.
  GfPartyPosInfo unknown40;      // Inferred role: party pos; original member name unknown.
  bool unknown100;               // Inferred role: with save data; original member name unknown.
  bool unknown101;               // Inferred role: no fade in; original member name unknown.
  bool unknown102;               // Inferred role: no fade out; original member name unknown.
  u8 _103[0x104 - 0x103];
  bool unknown104; // Inferred role: skip travel; original member name unknown.
  u32 unknown108;  // Inferred role: jump type; original member name unknown.
};

static_assert(offsetof(GfMapjumpInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfMapjumpInfo, unknown40) == 0x40, "");
static_assert(offsetof(GfMapjumpInfo, unknown100) == 0x100, "");
static_assert(offsetof(GfMapjumpInfo, unknown104) == 0x104, "");
static_assert(offsetof(GfMapjumpInfo, unknown108) == 0x108, "");
static_assert(sizeof(GfMapjumpInfo) == 0x110, "");

class GfReqCommand {
public:
  static void reqPartyBlade(u32 blade, u32 driver);
  static void reqRebuildPartyWeapon(u32 blade);
  static void reqChangeAttribute(u32 objectType, u32 blade, u32 attribute);
  static void reqChangeParty(const RQ_SETUP_PARTY &info);
  static u32 reqChangeBladeWithSetId(u32 partyId, int bladeSet, bool isForce);
  static void reqDestroyGf();
  static u32 reqMapjump(const GfMapjumpInfo &info);
  static u32 reqWaitEvent(f32 time, GF_OBJ_HANDLE *handle);
  static void execChangeAttributeForDebug(const GfReqParam *param);
  static u32 reqDebugPartyNum(u32 num);
  static void execPartyNumForDebug(const GfReqParam *param);
  static u32 reqDebugPartyInBlade(bool isInBlade);
  static void execPartyInBladeForDebug(const GfReqParam *param);
};

} // namespace gf
