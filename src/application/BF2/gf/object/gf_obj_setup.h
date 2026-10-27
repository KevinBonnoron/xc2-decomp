#pragma once
#include <stddef.h>

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_init_param.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct SDataBlade;
struct SDataEnemy;

enum VFEFF : u32 {
  VFEFF_UNKNOWN_4 = 4,
};

class GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~GfObjSetup() {}
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getEnArrangeID() const;

  void setInitialScale(f32 scale);
  void setInitialScale(const mm::Vec3 &scale);

  bool isEvent() const {
    switch (unknown1c) {
    case CHARACTER_TYPE_EVENT:
    case CHARACTER_TYPE_EVENT_CS:
    case CHARACTER_TYPE_ACT_VIEWER_EVENT:
      return true;
    default:
      return false;
    }
  }

  u32 unknown08; // Inferred role: object type; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u32 unknown10; // Inferred role: id; original member name unknown.
  u32 unknown14; // Inferred role: party member; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c;      // Inferred role: character type; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: rotation; original member name unknown.
  f32 unknown40;      // Inferred role: scale x; original member name unknown.
  f32 unknown44;      // Inferred role: scale y; original member name unknown.
  f32 unknown48;      // Inferred role: scale z; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  f32 unknown50;  // Inferred role: opacity; original member name unknown.
  bool unknown54; // Inferred role: has fixed blade; original member name unknown.
  u8 _55[0x58 - 0x55];
  u32 unknown58;         // Inferred role: fixed blade; original member name unknown.
  GimmickType unknown5c; // Inferred role: gimmick type; original member name unknown.
  bool unknown60;        // Inferred role: volume fade for user; original member name unknown.
  u8 _61[0x64 - 0x61];
  VFEFF unknown64; // Inferred role: volume fade effect; original member name unknown.
  s32 unknown68;   // Inferred role: skeleton type; original member name unknown.
};

static_assert(offsetof(GfObjSetup, unknown08) == 0x08, "");
static_assert(offsetof(GfObjSetup, unknown10) == 0x10, "");
static_assert(offsetof(GfObjSetup, unknown14) == 0x14, "");
static_assert(offsetof(GfObjSetup, unknown1c) == 0x1c, "");
static_assert(offsetof(GfObjSetup, unknown20) == 0x20, "");
static_assert(offsetof(GfObjSetup, unknown30) == 0x30, "");
static_assert(offsetof(GfObjSetup, unknown40) == 0x40, "");
static_assert(offsetof(GfObjSetup, unknown44) == 0x44, "");
static_assert(offsetof(GfObjSetup, unknown48) == 0x48, "");
static_assert(offsetof(GfObjSetup, unknown50) == 0x50, "");
static_assert(offsetof(GfObjSetup, unknown54) == 0x54, "");
static_assert(offsetof(GfObjSetup, unknown58) == 0x58, "");
static_assert(offsetof(GfObjSetup, unknown5c) == 0x5c, "");
static_assert(offsetof(GfObjSetup, unknown60) == 0x60, "");
static_assert(offsetof(GfObjSetup, unknown64) == 0x64, "");
static_assert(offsetof(GfObjSetup, unknown68) == 0x68, "");
static_assert(sizeof(GfObjSetup) == 0x70, "");

class GfObjSetupMap : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;

  u32 unknown6c; // Inferred role: bdat id; original member name unknown.
  u8 _70[0x75 - 0x70];
  bool unknown75; // Inferred role: seamless; original member name unknown.
};

static_assert(offsetof(GfObjSetupMap, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupMap, unknown75) == 0x75, "");

class GfObjSetupDriver : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_DRIVER;

  bool unknown6c; // Inferred role: ride; original member name unknown.
  u8 _6d[0x70 - 0x6d];
  int unknown70; // Inferred role: formation player id; original member name unknown.
};

static_assert(offsetof(GfObjSetupDriver, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupDriver, unknown70) == 0x70, "");

class GfObjSetupBlade : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_BLADE;

  int unknown6c;  // Inferred role: slot; original member name unknown.
  bool unknown70; // Inferred role: leaving; original member name unknown.
  u8 _71[0x74 - 0x71];
  int unknown74; // Inferred role: formation player id; original member name unknown.
};

static_assert(offsetof(GfObjSetupBlade, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupBlade, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupBlade, unknown74) == 0x74, "");

class GfObjSetupWeapon : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_PC_WEAPON;

  int unknown6c;  // Inferred role: slot; original member name unknown.
  bool unknown70; // Inferred role: leaving; original member name unknown.
  u8 _71[0x78 - 0x71];
  bool unknown78; // Inferred role: alternate; original member name unknown.
  u8 _79[0x118 - 0x79];
  GfAppend unknown118; // Inferred role: append; original member name unknown.
};

// Evidence: the GfObjSetupWeapon constructor calls GfAppend::GfAppend on this+0x118 and assigns its mounts from GfInitParamWeapon::unknown98.
static_assert(offsetof(GfObjSetupWeapon, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupWeapon, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupWeapon, unknown78) == 0x78, "");
static_assert(offsetof(GfObjSetupWeapon, unknown118) == 0x118, "");

class GfObjSetupMob : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupNpc : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_NPC;
};

class GfObjSetupGimmick : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_GIMMICK;

  u32 unknown6c;                 // Inferred role: attribute; original member name unknown.
  mm::mtl::FixStr<32> unknown70; // Inferred role: motion; original member name unknown.
  u8 _94[0xa1 - 0x94];
  bool unknowna1; // Inferred role: accessible; original member name unknown.
};

static_assert(offsetof(GfObjSetupGimmick, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupGimmick, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupGimmick, unknowna1) == 0xa1, "");

class GfObjSetupEnemy : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_ENEMY;

  u32 getEnArrangeID() const override;

  u32 unknown6c; // Inferred role: en param id; original member name unknown.
  u32 m_enArrangeID;
  u8 _74[0xa0 - 0x74];
  SDataEnemy *unknowna0; // Inferred role: data enemy; original member name unknown.
  int unknowna8;         // Inferred role: row id of BDAT_FLD_ENACT_MOVE; original member name unknown.
  u8 _ac[0xb4 - 0xac];
  u32 unknownb4; // Inferred role: saved hp; original member name unknown.
  u32 unknownb8; // Inferred role: blade; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  SDataBlade *unknownc0; // Inferred role: data blade; original member name unknown.
};

static_assert(offsetof(GfObjSetupEnemy, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupEnemy, m_enArrangeID) == 0x70, "");
static_assert(offsetof(GfObjSetupEnemy, unknowna0) == 0xa0, "");
static_assert(offsetof(GfObjSetupEnemy, unknowna8) == 0xa8, "");
static_assert(offsetof(GfObjSetupEnemy, unknownb8) == 0xb8, "");
static_assert(offsetof(GfObjSetupEnemy, unknownc0) == 0xc0, "");

class GfObjSetupBelonging : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_BELONGING;
};

class GfObjSetupEnWeapon : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupEventObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupExtra : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupFieldObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupMapLodAnim : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupMapObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupUiObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

void setSkelType(u32 type, GfObjSetup *setup);

} // namespace gf
