#pragma once
#include <stddef.h>

#include "gf/object/gf_append.h"
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
  unknown030_10 = 10,
  unknown030_11 = 11, // Inferred role: act viewer event; original name unknown.
  unknown030_12 = 12, // Inferred role: event npc; original name unknown.
};

enum VIEWCAM {
  VIEWCAM_UNKNOWN_0 = 0,
};

class GfInitParam {
public:
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
  u8 _0c[0x10 - 0x0c];
  u32 m_bladeID;
  u8 _14[0x18 - 0x14];
  const CBdatWrapper *unknown18; // Inferred role: bdat; original member name unknown.
  u32 unknown20;                 // Inferred role: party member; original member name unknown.
  VIEWCAM unknown24;             // Inferred role: view camera; original member name unknown.
  u8 _28[0x38 - 0x28];
  GF_OBJ_HANDLE *unknown38; // Inferred role: owner handle; original member name unknown.
  u32 unknown40;            // Inferred role: layer; original member name unknown.
  u16 unknown44;            // Inferred role: priority; original member name unknown.
  u8 _46[0x48 - 0x46];
  u32 unknown48; // Inferred role: gimmick type; original member name unknown.
  f32 unknown4c; // Inferred role: scale; original member name unknown.
  u8 _50[0x81 - 0x50];
  bool unknown81; // Inferred role: flag; original member name unknown.
  bool unknown82; // Inferred role: flag; original member name unknown.
  bool unknown83; // Inferred role: death blow weapon; original member name unknown.
  u8 _84[0x88 - 0x84];
  GfAssetSetup *unknown88; // Inferred role: asset setup overriding the default one; original member name unknown.
};

static_assert(offsetof(GfInitParam, unknown08) == 0x08, "");
static_assert(offsetof(GfInitParam, m_bladeID) == 0x10, "");
static_assert(offsetof(GfInitParam, unknown18) == 0x18, "");
static_assert(offsetof(GfInitParam, unknown20) == 0x20, "");
static_assert(offsetof(GfInitParam, unknown24) == 0x24, "");
static_assert(offsetof(GfInitParam, unknown38) == 0x38, "");
static_assert(offsetof(GfInitParam, unknown40) == 0x40, "");
static_assert(offsetof(GfInitParam, unknown4c) == 0x4c, "");
static_assert(offsetof(GfInitParam, unknown81) == 0x81, "");
static_assert(offsetof(GfInitParam, unknown82) == 0x82, "");
static_assert(offsetof(GfInitParam, unknown44) == 0x44, "");
static_assert(offsetof(GfInitParam, unknown48) == 0x48, "");
static_assert(offsetof(GfInitParam, unknown83) == 0x83, "");
static_assert(offsetof(GfInitParam, unknown88) == 0x88, "");
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

  static const u32 WEAPON_MAX = 32;

  bool isAllWeapon() const override;

  u8 _90[0x98 - 0x90];
  mm::mtl::FixedVector<unknown031, WEAPON_MAX> unknown98; // Inferred role: weapons; original member name unknown.
  u8 _1a0[0x1a1 - 0x1a0];
  bool m_allWeapon;
  u8 _1a2[0x1a8 - 0x1a2];
};

static_assert(sizeof(GfInitParamDriver::unknown031) == 0x08, "");
static_assert(offsetof(GfInitParamDriver, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamDriver, m_allWeapon) == 0x1a1, "");
static_assert(sizeof(GfInitParamDriver) == 0x1a8, "");

class GfInitParamBlade : public GfInitParam {
public:
  bool isAllWeapon() const override;
  void setupForParty(u32 blade, int slot, u32 driver, GF_OBJ_HANDLE *owner, bool isVirtual);
  void setupForEvent(u32 blade, bool isFirst);
  void setupForEventWithWeapon(u32 blade);
  void setupForActViewer(u32 blade, u32 weapon);
  void setupForActViewerEvent(u32 blade, u32 weapon);
  void setupForActViewerUI(u32 blade, u32 weapon);
  void setupForUi(u32 blade, VIEWCAM camera);

  bool unknown90; // Inferred role: party flag; original member name unknown.
  bool unknown91; // Inferred role: flag; original member name unknown.
  u8 _92[0x94 - 0x92];
  u32 unknown94; // Inferred role: weapon; original member name unknown.
  int unknown98; // Inferred role: party slot; original member name unknown.
  bool m_allWeapon;
  u8 _9d[0xa4 - 0x9d];
  bool unknowna4; // Inferred role: flag; original member name unknown.
};

static_assert(offsetof(GfInitParamBlade, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamBlade, unknown91) == 0x91, "");
static_assert(offsetof(GfInitParamBlade, unknown94) == 0x94, "");
static_assert(offsetof(GfInitParamBlade, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamBlade, m_allWeapon) == 0x9c, "");
static_assert(offsetof(GfInitParamBlade, unknowna4) == 0xa4, "");

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

  u8 _90[0x98 - 0x90];
  u32 unknown98; // Inferred role: en param id; original member name unknown.
  u32 m_enArrangeID;
  u32 m_bladeID;
  u32 unknowna4; // Inferred role: resource id; original member name unknown.
  u32 unknowna8; // Inferred role: blade flag; original member name unknown.
};

static_assert(offsetof(GfInitParamEnemy, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamEnemy, m_enArrangeID) == 0x9c, "");
static_assert(offsetof(GfInitParamEnemy, m_bladeID) == 0xa0, "");
static_assert(offsetof(GfInitParamEnemy, unknowna4) == 0xa4, "");
static_assert(offsetof(GfInitParamEnemy, unknowna8) == 0xa8, "");

class GfInitParamNpc : public GfInitParam {};

class GfInitParamMob : public GfInitParam {};

class GfInitParamGimmick : public GfInitParam {};

class GfInitParamMapObj : public GfInitParam {};

class GfInitParamFobj : public GfInitParam {};

class GfInitParamWeapon : public GfInitParam {
public:
  u8 _90[0x98 - 0x90];
  GfAppend unknown98; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamWeapon, unknown98) == 0x98, "");

class GfInitParamEnWeapon : public GfInitParam {
public:
  u32 getEnArrangeID() const override;

  u8 _90[0x98 - 0x90];
  GfAppend unknown98; // Inferred role: append; original member name unknown.
  u32 m_enArrangeID;
};

static_assert(offsetof(GfInitParamEnWeapon, unknown98) == 0x98, "");
static_assert(offsetof(GfInitParamEnWeapon, m_enArrangeID) == 0x120, "");

class GfInitParamBelonging : public GfInitParam {
public:
  GfAppend unknown90; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamBelonging, unknown90) == 0x90, "");

class GfInitParamExtra : public GfInitParam {
public:
  GfAppend unknown90; // Inferred role: append; original member name unknown.
};

static_assert(offsetof(GfInitParamExtra, unknown90) == 0x90, "");

class GfInitParamMapSeamless : public GfInitParam {
public:
  bool unknown90;        // Inferred role: use map id; original member name unknown.
  const char *unknown98; // Inferred role: model path; original member name unknown.
};

static_assert(offsetof(GfInitParamMapSeamless, unknown90) == 0x90, "");
static_assert(offsetof(GfInitParamMapSeamless, unknown98) == 0x98, "");

class GfInitParamMap : public GfInitParam {
public:
  mm::mtl::FixStr<256> unknown90; // Inferred role: path; original member name unknown.
};

static_assert(offsetof(GfInitParamMap, unknown90) == 0x90, "");

class GfInitParamEventObj : public GfInitParam {};

class GfInitParamUiObj : public GfInitParam {};

} // namespace gf
