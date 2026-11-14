#pragma once
#include <stddef.h>

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_init_param.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {
class Transform;
} // namespace fw

namespace mm {
struct Mat44;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct SDataBlade;
struct SDataEnemy;
struct GF_OBJ_HANDLE;
class GfObjSetupBelonging;
class GfObjSetupBlade;
class GfObjSetupDriver;
class GfObjSetupEnWeapon;
class GfObjSetupEventObj;
class GfObjSetupEnemy;
class GfObjSetupExtra;
class GfObjSetupFieldObj;
class GfObjSetupGimmick;
class GfObjSetupMap;
class GfObjSetupMapObj;
class GfObjSetupMapLodAnim;
class GfObjSetupMob;
class GfObjSetupNpc;
class GfObjSetupUiObj;
class GfObjSetupWeapon;

enum VFACC : s32 {
  VFACC_UNKNOWN_FFFFFFFF = -1, // Inferred role: no pending fade; original enumerator name unknown.
  VFACC_UNKNOWN_4 = 4,         // Inferred role: fade set by enterStayObjectWithVolumeFade; original enumerator name unknown.
};

enum VFEFF : u32 {
  VFEFF_UNKNOWN_0 = 0,
  VFEFF_UNKNOWN_9 = 9, // Inferred role: effect type copying the dead fade params; original enumerator name unknown.
};

class GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~GfObjSetup() {}
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getEnArrangeID() const;

  GfObjSetup(const GfInitParam &param, u32 type)
      : unknown08(type), unknown0c(param.unknown40), unknown10(param.m_bladeID), unknown14(param.unknown20), unknown18(param.unknown24), unknown1c(param.unknown08), unknown54(param.isAllWeapon()),
        unknown58(0), unknown5c(static_cast<GimmickType>(param.unknown48)), unknown60(param.unknown81), unknown64(VFACC_UNKNOWN_FFFFFFFF), unknown68(-1) {
    if (!param.unknown80) {
      unknown20 = mm::Vec3::zero;
      unknown30 = mm::Vec3::zero;
    } else {
      unknown20.x = param.unknown60.x;
      unknown20.y = param.unknown60.y;
      unknown20.z = param.unknown60.z;
      unknown30.x = param.unknown70.x;
      unknown30.y = param.unknown70.y;
      unknown30.z = param.unknown70.z;
    }

    setInitialScale(param.unknown4c);
    unknown50 = param.unknown50;
  }

  void setInitialTransform(const fw::Transform &transform);
  void setInitialTransform(const mm::Mat44 &matrix);
  void setInitialScale(f32 scale);
  void setInitialScale(const mm::Vec3 &scale);

  static GfObjSetupDriver *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamDriver &param);
  static GfObjSetupBlade *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamBlade &param);
  static GfObjSetupMap *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapSeamless &param);
  static GfObjSetupMap *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMap &param);
  static GfObjSetupMapLodAnim *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapLodAnim &param);
  static GfObjSetupEnemy *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamEnemy &param);
  static GfObjSetupNpc *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamNpc &param);
  static GfObjSetupMob *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMob &param);
  static GfObjSetupGimmick *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamGimmick &param);
  static GfObjSetupFieldObj *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamFobj &param);
  static GfObjSetupWeapon *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamWeapon &param);
  static GfObjSetupEnWeapon *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamEnWeapon &param);
  static GfObjSetupBelonging *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamBelonging &param);
  static GfObjSetupExtra *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamExtra &param);
  static GfObjSetupEventObj *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamEventObj &param);
  static GfObjSetupMapObj *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapObj &param);
  static GfObjSetupUiObj *createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamUiObj &param);

  bool isEvent() const {
    switch (unknown1c) {
    case unknown030_2:
    case unknown030_3:
    case unknown030_11:
      return true;
    default:
      return false;
    }
  }

  u32 unknown08;      // Inferred role: object type; original member name unknown.
  u32 unknown0c;      // Inferred role: layer; original member name unknown.
  u32 unknown10;      // Inferred role: id; original member name unknown.
  u32 unknown14;      // Inferred role: party member; original member name unknown.
  VIEWCAM unknown18;  // Inferred role: view camera; original member name unknown.
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
  VFACC unknown64; // Inferred role: pending volume fade; original member name unknown.
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

  GfObjSetupMap(const GfInitParam &param) : GfObjSetup(param, OBJECT_TYPE_MAP), unknown6c(0), unknown70(0), unknown74(false), unknown75(false) {}
  const mm::mtl::RTTI *getRTTI() const override;

  u32 unknown6c;  // Inferred role: bdat id; original member name unknown.
  u32 unknown70;  // Inferred role: map id of a seamless map using it; original member name unknown.
  bool unknown74; // Inferred role: has a model path; original member name unknown.
  bool unknown75; // Inferred role: seamless; original member name unknown.
  u8 _76[0x80 - 0x76];
};

static_assert(offsetof(GfObjSetupMap, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupMap, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupMap, unknown74) == 0x74, "");
static_assert(offsetof(GfObjSetupMap, unknown75) == 0x75, "");
static_assert(sizeof(GfObjSetupMap) == 0x80, "");

class GfObjSetupDriver : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_PC;

  // Defined in the class: the game has only the C2 symbol of this constructor.
  GfObjSetupDriver(const GfInitParamDriver &param) : GfObjSetup(param, OBJECT_TYPE_PC), unknown6c(false), unknown6d(false), unknown6e(false), unknown70(-1) { unknown80 = param; }
  const mm::mtl::RTTI *getRTTI() const override;

  bool unknown6c; // Inferred role: ride; original member name unknown.
  bool unknown6d; // Role and original member name unknown; cleared by the constructor.
  bool unknown6e; // Role and original member name unknown; cleared by the constructor.
  u8 _6f[0x70 - 0x6f];
  int unknown70; // Inferred role: formation player id; original member name unknown.
  u8 _74[0x80 - 0x74];
  GfInitParamDriver unknown80; // Inferred role: copy of the init param; original member name unknown.
};

static_assert(offsetof(GfObjSetupDriver, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupDriver, unknown6d) == 0x6d, "");
static_assert(offsetof(GfObjSetupDriver, unknown6e) == 0x6e, "");
static_assert(offsetof(GfObjSetupDriver, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupDriver, unknown80) == 0x80, "");
static_assert(sizeof(GfObjSetupDriver) == 0x230, "");

class GfObjSetupBlade : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupBlade(const GfInitParamBlade &param);
  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_BLADE;

  int unknown6c;  // Inferred role: slot; original member name unknown.
  bool unknown70; // Inferred role: leaving; original member name unknown.
  bool unknown71; // Role and original member name unknown; cleared by the GfPlayComHoodHomuraBattou constructor before the rebuild.
  u8 _72[0x74 - 0x72];
  int unknown74; // Inferred role: formation player id; original member name unknown.
  u8 _78[0x80 - 0x78];
  GfInitParamBlade unknown80; // Inferred role: copy of the init param; original member name unknown.
};

static_assert(offsetof(GfObjSetupBlade, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupBlade, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupBlade, unknown71) == 0x71, "");
static_assert(offsetof(GfObjSetupBlade, unknown74) == 0x74, "");
static_assert(offsetof(GfObjSetupBlade, unknown80) == 0x80, "");
static_assert(sizeof(GfObjSetupBlade) == 0x130, "");

class GfObjSetupWeapon : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_PC_WEAPON;

  // Defined in the class: the game has only the C2 symbol of this constructor.
  GfObjSetupWeapon(const GfInitParamWeapon &param) : GfObjSetup(param, OBJECT_TYPE_PC_WEAPON), unknown6c(-1), unknown70(false), unknown74(-1), unknown78(false) { unknown80 = param; }
  const mm::mtl::RTTI *getRTTI() const override;

  int unknown6c;  // Inferred role: slot; original member name unknown.
  bool unknown70; // Inferred role: leaving; original member name unknown.
  u8 _71[0x74 - 0x71];
  u32 unknown74;  // Inferred role: mount index; original member name unknown.
  bool unknown78; // Inferred role: alternate; original member name unknown.
  u8 _79[0x80 - 0x79];
  GfInitParamWeapon unknown80; // Inferred role: copy of the init param; original member name unknown.
};

// Evidence: the GfObjSetupWeapon constructor calls GfAppend::GfAppend on this+0x118 (GfInitParamWeapon::unknown98 of the copy) and assigns its mounts from GfInitParamWeapon::unknown98.
static_assert(offsetof(GfObjSetupWeapon, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupWeapon, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupWeapon, unknown74) == 0x74, "");
static_assert(offsetof(GfObjSetupWeapon, unknown78) == 0x78, "");
static_assert(offsetof(GfObjSetupWeapon, unknown80) == 0x80, "");
static_assert(sizeof(GfObjSetupWeapon) == 0x270, "");

class GfObjSetupMob : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_MOB;

  GfObjSetupMob(const GfInitParamMob &param) : GfObjSetup(param, OBJECT_TYPE_MOB), unknown6c("S_idle"), unknown90(100) {}
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::FixStr<32> unknown6c; // Inferred role: motion; original member name unknown.
  u8 unknown90;                  // Inferred role: move speed rate in percent; original member name unknown.
  u8 _91[0xa0 - 0x91];
};

static_assert(offsetof(GfObjSetupMob, unknown90) == 0x90, "");
static_assert(offsetof(GfObjSetupMob, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupMob) == 0xa0, "");

class GfObjSetupNpc : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupNpc(const GfInitParamNpc &param) : GfObjSetup(param, OBJECT_TYPE_NPC), unknown6c("S_idle"), unknown90(nullptr) {}
  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_NPC;

  mm::mtl::FixStr<32> unknown6c; // Inferred role: motion; original member name unknown.
  const char *unknown90;         // Inferred role: name, copied from GfInitParamNpc; original member name unknown.
  u8 _98[0xa0 - 0x98];
};

static_assert(offsetof(GfObjSetupNpc, unknown90) == 0x90, "");
static_assert(offsetof(GfObjSetupNpc, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupNpc) == 0xa0, "");

class GfObjSetupGimmick : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupGimmick(const GfInitParamGimmick &param) : GfObjSetup(param, OBJECT_TYPE_GIMMICK), unknown6c(0), unknown70("S_idle"), unknown98(nullptr), unknowna0(true), unknowna1(true) {}
  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_GIMMICK;

  u32 unknown6c;                 // Inferred role: attribute; original member name unknown.
  mm::mtl::FixStr<32> unknown70; // Inferred role: motion; original member name unknown.
  u8 _94[0x98 - 0x94];
  void *unknown98; // Role and original member name unknown; copied from GfInitParamGimmick.
  bool unknowna0;  // Role and original member name unknown; set to true by the constructor.
  bool unknowna1;  // Inferred role: accessible; original member name unknown.
  u8 _a2[0xb0 - 0xa2];
};

static_assert(offsetof(GfObjSetupGimmick, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupGimmick, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupGimmick, unknown98) == 0x98, "");
static_assert(offsetof(GfObjSetupGimmick, unknowna0) == 0xa0, "");
static_assert(offsetof(GfObjSetupGimmick, unknowna1) == 0xa1, "");
static_assert(sizeof(GfObjSetupGimmick) == 0xb0, "");

class GfObjSetupEnemy : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_ENEMY;

  GfObjSetupEnemy(const GfInitParamEnemy &param);
  ~GfObjSetupEnemy();
  const mm::mtl::RTTI *getRTTI() const override;
  u32 getEnArrangeID() const override;
  u32 getFootStep() const override;
  u32 getFootStepEffect() const override;
  void validateBy_pop_act_type(u8 popActType);

  u32 unknown6c; // Inferred role: en param id; original member name unknown.
  u32 m_enArrangeID;
  mm::mtl::FixStr<32> unknown74; // Inferred role: motion; original member name unknown.
  bool unknown98;                // Inferred role: set by validateBy_pop_act_type; original member name unknown.
  u8 _99[0xa0 - 0x99];
  SDataEnemy *unknowna0; // Inferred role: data enemy; original member name unknown.
  int unknowna8;         // Inferred role: row id of BDAT_FLD_ENACT_MOVE; original member name unknown.
  f32 unknownac;         // Inferred role: change battle delay, copied by GfComBehaviorEnemy::createBehField; original member name unknown.
  u16 unknownb0;         // Role and original member name unknown.
  bool unknownb2;        // Role and original member name unknown.
  u8 _b3[0xb4 - 0xb3];
  u32 unknownb4; // Inferred role: saved hp; original member name unknown.
  u32 unknownb8; // Inferred role: blade; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  SDataBlade *unknownc0; // Inferred role: data blade; original member name unknown.
};

static_assert(offsetof(GfObjSetupEnemy, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupEnemy, m_enArrangeID) == 0x70, "");
static_assert(offsetof(GfObjSetupEnemy, unknown74) == 0x74, "");
static_assert(offsetof(GfObjSetupEnemy, unknown98) == 0x98, "");
static_assert(offsetof(GfObjSetupEnemy, unknowna0) == 0xa0, "");
static_assert(offsetof(GfObjSetupEnemy, unknowna8) == 0xa8, "");
static_assert(offsetof(GfObjSetupEnemy, unknownb0) == 0xb0, "");
static_assert(offsetof(GfObjSetupEnemy, unknownac) == 0xac, "");
static_assert(offsetof(GfObjSetupEnemy, unknownb2) == 0xb2, "");
static_assert(offsetof(GfObjSetupEnemy, unknownb8) == 0xb8, "");
static_assert(offsetof(GfObjSetupEnemy, unknownc0) == 0xc0, "");

class GfObjSetupBelonging : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupBelonging(const GfInitParamBelonging &param) : GfObjSetup(param, OBJECT_TYPE_OPTION), unknown6c(-1) {}
  const mm::mtl::RTTI *getRTTI() const override;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_OPTION;

  u32 unknown6c; // Inferred role: mount index; original member name unknown.
};

static_assert(offsetof(GfObjSetupBelonging, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupBelonging) == 0x70, "");

class GfObjSetupEnWeapon : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupEnWeapon(const GfInitParamEnWeapon &param) : GfObjSetup(param, OBJECT_TYPE_EN_WEAPON), unknown6c(-1) {}
  const mm::mtl::RTTI *getRTTI() const override;

  u32 unknown6c; // Inferred role: mount index; original member name unknown.
};

static_assert(offsetof(GfObjSetupEnWeapon, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupEnWeapon) == 0x70, "");

class GfObjSetupEventObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::FixStr<128> unknown6c; // Inferred role: model name; original member name unknown.
};

static_assert(offsetof(GfObjSetupEventObj, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupEventObj) == 0xf0, "");

class GfObjSetupExtra : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupExtra(const GfInitParamExtra &param) : GfObjSetup(param, OBJECT_TYPE_EXTRA), unknown6c(-1) {}
  const mm::mtl::RTTI *getRTTI() const override;

  u32 unknown6c; // Inferred role: mount index; original member name unknown.
};

static_assert(offsetof(GfObjSetupExtra, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupExtra) == 0x70, "");

class GfObjSetupFieldObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupFieldObj(const GfInitParamFobj &param) : GfObjSetup(param, OBJECT_TYPE_FIELD_OBJ), unknown6c(-1), unknown70(0), unknown78(0), unknown7c(0), unknown80(0), unknown84(0), unknown88(0.0f) {}
  const mm::mtl::RTTI *getRTTI() const override;

  u32 unknown6c; // Inferred role: param id; original member name unknown.
  u64 unknown70; // Role and original member name unknown; cleared by the constructor.
  u32 unknown78; // Inferred role: item list bdat of the dropitem, set by GfFobjDropitem::emitDropitem; original member name unknown.
  s32 unknown7c; // Inferred role: item id of the dropitem; original member name unknown.
  u32 unknown80; // Inferred role: gold of the dropitem, set by GfFobjDropitem::emitDropgold; original member name unknown.
  u32 unknown84; // Inferred role: resource bdat id of the dropitem; original member name unknown.
  f32 unknown88; // Role and original member name unknown; cleared by the constructor.
  u8 _8c[0x90 - 0x8c];
};

static_assert(offsetof(GfObjSetupFieldObj, unknown6c) == 0x6c, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown70) == 0x70, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown78) == 0x78, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown7c) == 0x7c, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown80) == 0x80, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown84) == 0x84, "");
static_assert(offsetof(GfObjSetupFieldObj, unknown88) == 0x88, "");
static_assert(sizeof(GfObjSetupFieldObj) == 0x90, "");

class GfObjSetupMapLodAnim : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupMapLodAnim(const GfInitParamMapLodAnim &param) : GfObjSetup(param, OBJECT_TYPE_MAP_LOD), unknown6c(0) {}
  const mm::mtl::RTTI *getRTTI() const override;

  u16 unknown6c; // Inferred role: lod id; original member name unknown.
  u8 _6e[0x70 - 0x6e];
};

static_assert(offsetof(GfObjSetupMapLodAnim, unknown6c) == 0x6c, "");
static_assert(sizeof(GfObjSetupMapLodAnim) == 0x70, "");

class GfObjSetupMapObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfObjSetupMapObj(const GfInitParamMapObj &param) : GfObjSetup(param, OBJECT_TYPE_MOB) {}
  const mm::mtl::RTTI *getRTTI() const override;
};

class GfObjSetupUiObj : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
};

void setSkelType(u32 type, GfObjSetup *setup);

} // namespace gf
