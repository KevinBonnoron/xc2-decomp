#pragma once
#include <stddef.h>

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

struct GF_OBJ_HANDLE;
class GfAssetSetup;

// Inferred role: character type; original type name unknown.
enum unknown030 {
  unknown030_1 = 1, // Inferred role: party; original name unknown.
  unknown030_2 = 2, // Inferred role: event; original name unknown.
  unknown030_3 = 3, // Inferred role: event cs; original name unknown.
  unknown030_4 = 4,
  unknown030_5 = 5, // Inferred role: enemy blade; original name unknown.
  unknown030_6 = 6, // Inferred role: event driver; original name unknown.
  unknown030_7 = 7, // Inferred role: event blade; original name unknown.
  unknown030_8 = 8, // Inferred role: trinity blade; original name unknown.
  unknown030_9 = 9, // Inferred role: salvage model (GfGameEvent::createSalvage); original name unknown.
  unknown030_10 = 10,
  unknown030_11 = 11, // Inferred role: act viewer event; original name unknown.
  unknown030_12 = 12, // Inferred role: event npc; original name unknown.
  unknown030_13 = 13,
};

inline bool isEventCharacter(u32 characterType) {
  switch (characterType) {
  case unknown030_6:
  case unknown030_7:
  case unknown030_12:
    return true;
  default:
    return false;
  }
}

enum VIEWCAM {
  VIEWCAM_UNKNOWN_0 = 0,
  VIEWCAM_UNKNOWN_1 = 1,
};

class GfInitParam {
public:
  GfInitParam() : GfInitParam(1, 0) {}

  GfInitParam(u32 category, u32 layer)
      : unknown08(0), unknown0c(category), m_bladeID(0), unknown18(nullptr), unknown20(0xffffffff), unknown24(VIEWCAM_UNKNOWN_0), unknown28(-1), unknown30(unknown020), unknown38(unknown020),
        unknown40(layer), unknown44(0), unknown48(0), unknown4c(1.0f), unknown50(1.0f), unknown80(false), unknown81(true), unknown82(false), unknown83(false), unknown84(false) {}

  virtual bool isAllWeapon() const { return false; }
  virtual u32 getBladeID() const { return m_bladeID; }
  virtual u32 getEnArrangeID() const;

  bool isEvent() const {
    switch (unknown08) {
    case unknown030_2:
    case unknown030_3:
    case unknown030_11:
      return true;
    default:
      return false;
    }
  }

  // Inferred role: character types loaded with the UI resources (GfAssetFactory::createAssetPackBlade); original name unknown.
  bool unknown002() const {
    switch (unknown08) {
    case unknown030_6:
    case unknown030_7:
    case unknown030_12:
      return true;
    default:
      return false;
    }
  }

  u32 unknown08; // Inferred role: character type; original member name unknown.
  u32 unknown0c; // Inferred role: object category, 1 by default; original member name unknown.
  u32 m_bladeID;
  u8 _14[0x18 - 0x14];
  const CBdatWrapper *unknown18; // Inferred role: bdat; original member name unknown.
  u32 unknown20;                 // Inferred role: party member; original member name unknown.
  VIEWCAM unknown24;             // Inferred role: view camera; original member name unknown.
  int unknown28;                 // Inferred role: object index, negative to allocate one (GfObjManager::createGfObj); original member name unknown.
  GF_OBJ_HANDLE *unknown30;      // Inferred role: source object (read by GfObjFactory through DataParamAcc); original member name unknown.
  GF_OBJ_HANDLE *unknown38;      // Inferred role: owner handle; original member name unknown.
  u32 unknown40;                 // Inferred role: layer; original member name unknown.
  u16 unknown44;                 // Inferred role: priority; original member name unknown.
  u8 _46[0x48 - 0x46];
  u32 unknown48; // Inferred role: gimmick type; original member name unknown.
  f32 unknown4c; // Inferred role: scale; original member name unknown.
  f32 unknown50; // Inferred role: scale copied into the object setup; original member name unknown.
  // 0x54..0x60 is alignment padding, not a member: the implicit copy in the GfObjSetupWeapon constructor (0x71005acbc8) copies 0x08..0x54 as one 0x4c byte memcpy.
  mm::Vec3 unknown60; // Inferred role: initial position, used when unknown80 is set; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: initial rotation, used when unknown80 is set; original member name unknown.
  bool unknown80;     // Inferred role: flag; original member name unknown.
  bool unknown81;     // Inferred role: flag; original member name unknown.
  bool unknown82;     // Inferred role: flag; original member name unknown.
  bool unknown83;     // Inferred role: death blow weapon; original member name unknown.
  bool unknown84;     // Inferred role: flag; original member name unknown.
  // The asset setup pointer at 0x88 is the first member of each derived class, in this class's tail padding, not a member of this one. GfInitParamDriver::operator= (0x71005ae8f0) copies this
  // class's last group as 0x80..0x84 only (0x71005ae950-0x71005ae95c) and then 0x90 and 0x88 as the derived group (0x71005ae960-0x71005ae96c); GfGameUnit::createParty
  // (0x7100347c38-0x7100347c40) and the GfObjSetupDriver constructor (0x71005abd8c-0x71005abd98) store the vtable pointer, 0x88 and 0x90 in that order. With the member in this class,
  // GfGameUnit::createParty and SCOM_REBUILD_PARTY_WEAPON::exec do not match. GfAssetFactory only reads it through the concrete parameter type. 0x85..0x88 is tail padding, not a member: the
  // copies in GfObjSetupWeapon (0x71005acbc8) and GfObjSetupBlade (0x71005ae690) constructors read 0x80 and 0x84 alone.
};

static_assert(offsetof(GfInitParam, unknown08) == 0x08, "");
static_assert(offsetof(GfInitParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfInitParam, m_bladeID) == 0x10, "");
static_assert(offsetof(GfInitParam, unknown18) == 0x18, "");
static_assert(offsetof(GfInitParam, unknown20) == 0x20, "");
static_assert(offsetof(GfInitParam, unknown24) == 0x24, "");
static_assert(offsetof(GfInitParam, unknown28) == 0x28, "");
static_assert(offsetof(GfInitParam, unknown30) == 0x30, "");
static_assert(offsetof(GfInitParam, unknown38) == 0x38, "");
static_assert(offsetof(GfInitParam, unknown40) == 0x40, "");
static_assert(offsetof(GfInitParam, unknown4c) == 0x4c, "");
static_assert(offsetof(GfInitParam, unknown50) == 0x50, "");
static_assert(offsetof(GfInitParam, unknown60) == 0x60, "");
static_assert(offsetof(GfInitParam, unknown70) == 0x70, "");
static_assert(offsetof(GfInitParam, unknown80) == 0x80, "");
static_assert(offsetof(GfInitParam, unknown81) == 0x81, "");
static_assert(offsetof(GfInitParam, unknown82) == 0x82, "");
static_assert(offsetof(GfInitParam, unknown44) == 0x44, "");
static_assert(offsetof(GfInitParam, unknown48) == 0x48, "");
static_assert(offsetof(GfInitParam, unknown83) == 0x83, "");
static_assert(offsetof(GfInitParam, unknown84) == 0x84, "");
static_assert(sizeof(GfInitParam) == 0x90, "");

class GfInitParamDriver : public GfInitParam {
public:
  // Inferred role: weapon; original type name unknown.
  struct unknown031 {
    s8 unknown00; // Inferred role: slot; original member name unknown.
    u8 unknown01; // Inferred role: weapon type; original member name unknown.
    u8 unknown02; // Inferred role: attribute; original member name unknown.
    u8 _03[0x04 - 0x03];
    u16 unknown04; // Inferred role: blade; original member name unknown.
    u8 _06[0x08 - 0x06];
  };

  static const u32 WEAPON_UNKNOWN_32 = 32; // Inferred role: weapon max; original name unknown.

  // Evidence: inlined in GfGameUnit::createParty (0x7100347b9c), which stores unknown84 then unknown82 after the members.
  GfInitParamDriver() : GfInitParam(OBJECT_TYPE_PC, 4), unknown88(nullptr), unknown90(0), unknown1a0(false), m_allWeapon(false), unknown1a2(false), unknown1a4(0), unknown1a8(1.0f), unknown1ac(0) {
    unknown84 = true;
    unknown82 = true;
  }

  bool isAllWeapon() const override;

  GfAssetSetup *unknown88;                                       // Inferred role: asset setup overriding the default one; original member name unknown.
  u32 unknown90;                                                 // Role and original member name unknown; cleared by the constructor and read by GfObjFactory::createDriver.
  mm::mtl::FixedVector<unknown031, WEAPON_UNKNOWN_32> unknown98; // Inferred role: weapons; original member name unknown.
  bool unknown1a0;                                               // Inferred role: ride; original member name unknown.
  bool m_allWeapon;
  bool unknown1a2; // Inferred role: Jiji display, set by GfGameEvent::createDriver outside GfGameManager::isInMetJIJI; original member name unknown.
  u32 unknown1a4;  // Role and original member name unknown; cleared by the constructor.
  f32 unknown1a8;  // Inferred role: value of the party leader info (PartyLeaderInfo::unknown00), 1 by default; original member name unknown.
  int unknown1ac;  // Role and original member name unknown; cleared by the constructor and read by GfObjFactory::createDriver.
};

static_assert(sizeof(GfInitParamDriver::unknown031) == 0x08, "");
static_assert(offsetof(GfInitParamDriver, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamDriver, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamDriver, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfInitParamDriver, m_allWeapon) == 0x1a1, "");
static_assert(offsetof(GfInitParamDriver, unknown1a2) == 0x1a2, "");
static_assert(offsetof(GfInitParamDriver, unknown1a4) == 0x1a4, "");
static_assert(offsetof(GfInitParamDriver, unknown1a8) == 0x1a8, "");
static_assert(offsetof(GfInitParamDriver, unknown1ac) == 0x1ac, "");
static_assert(sizeof(GfInitParamDriver) == 0x1b0, "");

class GfInitParamBlade : public GfInitParam {
public:
  // Evidence: inlined in the GfObjSetupBlade constructor (0x71005ae690), which stores unknown84 then unknown82 after the members; no constructor symbol in the game.
  GfInitParamBlade() : GfInitParam(OBJECT_TYPE_BLADE, 4), unknown88(nullptr), unknown90(false), unknown91(true), unknown94(0), unknown98(-1), m_allWeapon(false), unknowna0(0), unknowna4(false) {
    unknown84 = true;
    unknown82 = true;
  }

  bool isAllWeapon() const override;
  void setupForParty(u32 blade, int slot, u32 driver, GF_OBJ_HANDLE *owner, bool isVirtual);
  void setupForEvent(u32 blade, bool isFirst);
  void setupForEventWithWeapon(u32 blade);
  void setupForActViewer(u32 blade, u32 weapon);
  void setupForActViewerEvent(u32 blade, u32 weapon);
  void setupForActViewerUI(u32 blade, u32 weapon);
  void setupForUi(u32 blade, VIEWCAM camera);

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  bool unknown90;          // Inferred role: party flag; original member name unknown.
  bool unknown91;          // Inferred role: flag; original member name unknown.
  u8 _92[0x94 - 0x92];
  u32 unknown94; // Inferred role: weapon; original member name unknown.
  int unknown98; // Inferred role: party slot; original member name unknown.
  bool m_allWeapon;
  u8 _9d[0xa0 - 0x9d];
  u32 unknowna0;  // Role and original member name unknown; cleared by the constructor.
  bool unknowna4; // Inferred role: flag; original member name unknown.
};

static_assert(offsetof(GfInitParamBlade, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamBlade, unknown91) == 0x91, "");
static_assert(offsetof(GfInitParamBlade, unknown94) == 0x94, "");
static_assert(offsetof(GfInitParamBlade, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamBlade, m_allWeapon) == 0x9c, "");
static_assert(offsetof(GfInitParamBlade, unknowna0) == 0xa0, "");
static_assert(offsetof(GfInitParamBlade, unknowna4) == 0xa4, "");
static_assert(sizeof(GfInitParamBlade) == 0xb0, "");

class GfInitParamEnemy : public GfInitParam {
public:
  u32 getBladeID() const override;
  u32 getEnArrangeID() const override;
  void setupForEvent(u32 enArrange);
  void setupEnArrangeId(u32 enArrange);
  void setupBlade(const GfInitParamEnemy &enemy);
  void setupForUi(u32 enArrange, VIEWCAM camera);
  void setupForActViewer(u32 resource, const CBdatWrapper *bdat);
  void setupForActViewerEvent(u32 resource, const CBdatWrapper *bdat);

  GfInitParamEnemy()
      : GfInitParam(OBJECT_TYPE_ENEMY, 4), unknown90(nullptr), unknown98(0), m_enArrangeID(0), m_bladeID(0), unknowna4(0), unknowna8(0), unknownac(1), unknownae(0), unknownaf(0),
        unknownb0(GFATTACH_UNKNOWN_0) {
    unknown08 = unknown030_4;
    unknown82 = true;
    unknown88 = nullptr;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  void *unknown90;         // Role and original member name unknown; cleared by the constructor.
  u32 unknown98;           // Inferred role: en param id; original member name unknown.
  u32 m_enArrangeID;
  u32 m_bladeID;
  u32 unknowna4;      // Inferred role: resource id; original member name unknown.
  u32 unknowna8;      // Inferred role: blade flag; original member name unknown.
  u16 unknownac;      // Inferred role: level, 1 by default; original member name unknown.
  s8 unknownae;       // Inferred role: level offset; original member name unknown.
  u8 unknownaf;       // Role and original member name unknown; cleared by the constructor.
  GFATTACH unknownb0; // Inferred role: attach slot of the weapons; original member name unknown.
};

static_assert(offsetof(GfInitParamEnemy, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamEnemy, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamEnemy, m_enArrangeID) == 0x9c, "");
static_assert(offsetof(GfInitParamEnemy, m_bladeID) == 0xa0, "");
static_assert(offsetof(GfInitParamEnemy, unknowna4) == 0xa4, "");
static_assert(offsetof(GfInitParamEnemy, unknowna8) == 0xa8, "");
static_assert(offsetof(GfInitParamEnemy, unknownac) == 0xac, "");
static_assert(offsetof(GfInitParamEnemy, unknownae) == 0xae, "");
static_assert(offsetof(GfInitParamEnemy, unknownaf) == 0xaf, "");
static_assert(offsetof(GfInitParamEnemy, unknownb0) == 0xb0, "");
static_assert(sizeof(GfInitParamEnemy) == 0xc0, "");

class GfInitParamNpc : public GfInitParam {
public:
  GfInitParamNpc() : GfInitParam(OBJECT_TYPE_NPC, 4), unknown90(false), unknown98(nullptr), unknowna0(0), unknowna2(0), unknowna4(0), unknowna6(0) {
    unknown88 = nullptr;
    unknown82 = true;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  bool unknown90;          // Role and original member name unknown; set by GfObjFactory::createGmkNpc.
  u8 _91[0x98 - 0x91];
  const char *unknown98; // Inferred role: name (GfObjFactory::createGmkBlade), copied into GfObjSetupNpc; original member name unknown.
  u16 unknowna0;         // Inferred role: first parameter of the belonging setup (the "MountPoint" of the npc list); original member name unknown.
  u16 unknowna2;         // Inferred role: second parameter of the belonging setup (the "MountObject" of the npc list); original member name unknown.
  u16 unknowna4;         // Inferred role: third parameter of the belonging setup; original member name unknown.
  u16 unknowna6;         // Inferred role: fourth parameter of the belonging setup; original member name unknown.
};

static_assert(offsetof(GfInitParamNpc, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamNpc, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamNpc, unknowna0) == 0xa0, "");
static_assert(offsetof(GfInitParamNpc, unknowna6) == 0xa6, "");
static_assert(sizeof(GfInitParamNpc) == 0xb0, "");

class GfInitParamMob : public GfInitParam {
public:
  GfInitParamMob() : GfInitParam(OBJECT_TYPE_MOB, 4), unknown90(0), unknown92(0), unknown94(0), unknown96(0) {
    unknown88 = nullptr;
    unknown82 = true;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  u16 unknown90;           // Inferred role: first parameter of GfObjFactory::createGmkMob; original member name unknown.
  u16 unknown92;           // Inferred role: second parameter of GfObjFactory::createGmkMob; original member name unknown.
  u16 unknown94;           // Inferred role: third parameter of GfObjFactory::createGmkMob; original member name unknown.
  u16 unknown96;           // Inferred role: fourth parameter of GfObjFactory::createGmkMob; original member name unknown.
  u8 _98[0xa0 - 0x98];
};

static_assert(offsetof(GfInitParamMob, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamMob, unknown96) == 0x96, "");
static_assert(sizeof(GfInitParamMob) == 0xa0, "");

class GfInitParamGimmick : public GfInitParam {
public:
  GfInitParamGimmick() : GfInitParam(OBJECT_TYPE_GIMMICK, 4), unknown90(nullptr), unknown98(false) {
    unknown88 = nullptr;
    unknown48 = GIMMICK_TYPE_UNKNOWN_0;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  void *unknown90;         // Role and original member name unknown; copied into GfObjSetupGimmick.
  bool unknown98;          // Inferred role: big object, the "BigObj" flag of the map object list (GfObjFactory::createGmkMapObj); original member name unknown.
};

static_assert(offsetof(GfInitParamGimmick, unknown90) == 0x90, "");

class GfInitParamMapObj : public GfInitParam {
public:
  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
};

class GfInitParamFobj : public GfInitParam {
public:
  GfInitParamFobj() : GfInitParam(OBJECT_TYPE_FIELD_OBJ, 4) {
    unknown88 = nullptr;
    unknown94 = 0;
    unknown81 = false;
    unknown95 = true;
    unknown90 = 2;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  u32 unknown90;           // Role and original member name unknown; 2 by default.
  u8 unknown94;            // Inferred role: index of the "paramid" column of the bdat; original member name unknown.
  bool unknown95;          // Inferred role: creates a dropitem for the object; original member name unknown.
  u8 _96[0xa0 - 0x96];
};

static_assert(offsetof(GfInitParamFobj, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamFobj, unknown94) == 0x94, "");
static_assert(offsetof(GfInitParamFobj, unknown95) == 0x95, "");
static_assert(sizeof(GfInitParamFobj) == 0xa0, "");

class GfInitParamWeapon : public GfInitParam {
public:
  // Evidence: inlined in SCOM_REBUILD_PARTY_WEAPON::exec (0x71005d24f0) and in GfObjFactory::createDriver.
  GfInitParamWeapon()
      : GfInitParam(OBJECT_TYPE_PC_WEAPON, 6), unknown88(nullptr), unknown90(false), unknown91(false), unknown94(-1), unknown120(unknown020), unknown128(0), unknown12c(0), unknown1e0(false),
        unknown1e1(false), unknown1e4(GFATTACH_UNKNOWN_0), unknown1e8(false) {}

  void setupForEvent(u32 driver, u32 blade);
  void setupBladeForEvent(u32 blade);
  void setupForEventBlade(u32 blade, GF_OBJ_HANDLE *owner);
  void setupBladeForEventRight(u32 blade);
  void setupBladeForEventCS(u32 blade);
  void setupBladeForEventRightCS(u32 blade);
  void setupBladeForEventLeft(u32 blade);
  void setupBladeForEventLeftCS(u32 blade);

  // Inferred helper: sets up the weapon of a party blade; original name unknown. Evidence: inlined in SCOM_REBUILD_PARTY_WEAPON::exec (0x71005d24f0) and GfObjFactory::createDriver, which evaluate the
  // arguments in this order and then store them.
  void unknown003(u32 partyId, int slot, u32 weapon, GF_OBJ_HANDLE *owner, GF_OBJ_HANDLE *blade, GF_OBJ_HANDLE *driver, bool isCurrent) {
    unknown08 = unknown030_1;
    unknown20 = partyId;
    m_bladeID = weapon;
    unknown94 = slot;
    unknown30 = owner;
    unknown38 = blade;
    unknown90 = true;
    unknown120 = driver;
    unknown91 = isCurrent;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  bool unknown90;          // Role and original member name unknown.
  bool unknown91;          // Inferred role: the slot is the driver's current blade set (SCOM_REBUILD_PARTY_WEAPON::exec); original member name unknown.
  u8 _92[0x94 - 0x92];
  int unknown94;              // Inferred role: slot; original member name unknown.
  GfAppend unknown98;         // Inferred role: append; original member name unknown.
  GF_OBJ_HANDLE *unknown120;  // Inferred role: party driver object (GfObjFactory::createDriverWeapon reads it through DataParamAcc); original member name unknown.
  u32 unknown128;             // Inferred role: driver; original member name unknown.
  u32 unknown12c;             // Inferred role: blade; original member name unknown.
  GfAppendHandles unknown130; // Inferred role: weapon handles used when the owner has no mount (GfObjFactory::createDriverWeapon); original member name unknown.
  bool unknown1e0;            // Inferred role: right hand; original member name unknown.
  bool unknown1e1;            // Inferred role: left hand; original member name unknown.
  u8 _1e2[0x1e4 - 0x1e2];
  GFATTACH unknown1e4; // Inferred role: attach slot (GfObjFactory::createDriverWeapon passes it to GfMountManager::getAppendHandles); original member name unknown.
  bool unknown1e8;     // Role and original member name unknown; cleared by the constructor.
};

static_assert(offsetof(GfInitParamWeapon, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamWeapon, unknown91) == 0x91, "");
static_assert(offsetof(GfInitParamWeapon, unknown94) == 0x94, "");
static_assert(offsetof(GfInitParamWeapon, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamWeapon, unknown120) == 0x120, "");
static_assert(offsetof(GfInitParamWeapon, unknown128) == 0x128, "");
static_assert(offsetof(GfInitParamWeapon, unknown12c) == 0x12c, "");
static_assert(offsetof(GfInitParamWeapon, unknown130) == 0x130, "");
static_assert(offsetof(GfInitParamWeapon, unknown1e0) == 0x1e0, "");
static_assert(offsetof(GfInitParamWeapon, unknown1e1) == 0x1e1, "");
static_assert(offsetof(GfInitParamWeapon, unknown1e4) == 0x1e4, "");
static_assert(offsetof(GfInitParamWeapon, unknown1e8) == 0x1e8, "");
static_assert(sizeof(GfInitParamWeapon) == 0x1f0, "");

class GfInitParamEnWeapon : public GfInitParam {
public:
  u32 getEnArrangeID() const override;

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  u8 _90[0x98 - 0x90];
  GfAppend unknown98; // Inferred role: append; original member name unknown.
  u32 m_enArrangeID;
  u8 _124[0x128 - 0x124];
  GF_OBJ_HANDLE *unknown128; // Inferred role: owner handle passed to GfAppendUtil::setupEnemy; original member name unknown.
  GFATTACH unknown130;       // Inferred role: attach slot; original member name unknown.
};

static_assert(offsetof(GfInitParamEnWeapon, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamEnWeapon, m_enArrangeID) == 0x120, "");
static_assert(offsetof(GfInitParamEnWeapon, unknown128) == 0x128, "");
static_assert(offsetof(GfInitParamEnWeapon, unknown130) == 0x130, "");

class GfInitParamBelonging : public GfInitParam {
public:
  GfInitParamBelonging() : GfInitParam(OBJECT_TYPE_OPTION, 6), unknown88(nullptr), unknown120(false), unknown128(nullptr), unknown130(true) {}

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  GfAppend unknown90;      // Inferred role: append; original member name unknown.
  u16 unknown118;          // Inferred role: first parameter of GfAppendUtil::setupBelonging; original member name unknown.
  u16 unknown11a;          // Inferred role: second parameter of GfAppendUtil::setupBelonging; original member name unknown.
  u16 unknown11c;          // Inferred role: third parameter of GfAppendUtil::setupBelonging; original member name unknown.
  u16 unknown11e;          // Inferred role: fourth parameter of GfAppendUtil::setupBelonging; original member name unknown.
  bool unknown120;         // Inferred role: set up from a driver; original member name unknown.
  u8 _121[0x128 - 0x121];
  GfInitParamDriver *unknown128; // Inferred role: driver of the belonging, used when unknown120 is set; original member name unknown.
  bool unknown130;               // Inferred role: visible; original member name unknown.
};

static_assert(offsetof(GfInitParamBelonging, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamBelonging, unknown118) == 0x118, "");
static_assert(offsetof(GfInitParamBelonging, unknown11e) == 0x11e, "");
static_assert(offsetof(GfInitParamBelonging, unknown120) == 0x120, "");
static_assert(offsetof(GfInitParamBelonging, unknown128) == 0x128, "");
static_assert(offsetof(GfInitParamBelonging, unknown130) == 0x130, "");

class GfInitParamExtra : public GfInitParam {
public:
  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  GfAppend unknown90;      // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamExtra, unknown90) == 0x90, "");

class GfInitParamMapSeamless : public GfInitParam {
public:
  // The game stores unknown88 after this class's vtable pointer, so it is set here and not by GfInitParam (SCOM_CREATE_MAP_OBJ::exec).
  GfInitParamMapSeamless() {
    unknown88 = nullptr;
    unknown90 = false;
    unknown98 = nullptr;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  bool unknown90;          // Inferred role: use map id; original member name unknown.
  const char *unknown98;   // Inferred role: model path; original member name unknown.
};

static_assert(offsetof(GfInitParamMapSeamless, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamMapSeamless, unknown98) == 0x98, "");

class GfInitParamMap : public GfInitParam {
public:
  u8 _88[0x90 - 0x88];
  mm::mtl::FixStr<256> unknown90; // Inferred role: path; original member name unknown.
};

static_assert(offsetof(GfInitParamMap, unknown90) == 0x90, "");

class GfInitParamEventObj : public GfInitParam {
public:
  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
};

class GfInitParamMapLodAnim : public GfInitParam {
public:
  GfInitParamMapLodAnim() {
    unknown88 = nullptr;
    unknown90 = false;
    unknown110 = 0;
    unknown40 = 0;
  }

  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
  bool unknown90;          // Role and original member name unknown; cleared by the constructor.
  u8 _91[0x110 - 0x91];
  u32 unknown110; // Role and original member name unknown; cleared by the constructor.
  u8 _114[0x120 - 0x114];
};

static_assert(offsetof(GfInitParamMapLodAnim, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamMapLodAnim, unknown110) == 0x110, "");
static_assert(sizeof(GfInitParamMapLodAnim) == 0x120, "");

class GfInitParamUiObj : public GfInitParam {
public:
  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
};

} // namespace gf
