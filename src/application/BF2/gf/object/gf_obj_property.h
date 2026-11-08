#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfObjPropertyBelonging;
class GfObjPropertyBlade;
class GfObjPropertyDriver;
class GfObjPropertyEnemy;
class GfObjPropertyEnWeapon;
class GfObjPropertyEvent;
class GfObjPropertyFobj;
class GfObjPropertyGimmick;
class GfObjPropertyMap;
class GfObjPropertyMob;
class GfObjPropertyNpc;
class GfObjPropertyPcWeapon;
class GfObjPropertyUi;

struct GfObjPropertyCharacter {
  u32 unknown00; // Inferred role: max hp; original member name unknown.
  u32 unknown04; // Inferred role: hp; original member name unknown.
  u16 unknown08; // Inferred role: level; original member name unknown.
  u8 _0a[0x28 - 0x0a];
  GF_OBJ_HANDLE *unknown28; // Inferred role: target, copied from the property component by GfComProperty::flush; original member name unknown.
  bool unknown30;           // Inferred role: battle; original member name unknown.
};

static_assert(offsetof(GfObjPropertyCharacter, unknown04) == 0x04, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown08) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown30) == 0x30, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown28) == 0x28, "");

enum {
  PROPERTY_MOVE_WALK = 0,
  PROPERTY_MOVE_SWIM = 1,
  PROPERTY_MOVE_SWIM_ON_CLOUD = 2,
  PROPERTY_MOVE_CLIMB = 3,
  PROPERTY_MOVE_ACTION = 4,
  PROPERTY_MOVE_UNKNOWN_5 = 5, // Inferred role: blocks the follow warp like PROPERTY_MOVE_SWIM (TaskFieldCheckWarp::update); original name unknown.
};

// Inferred role: obj property move; original type name unknown.
struct unknown070 {
  u32 unknown00; // Inferred role: type; original member name unknown.
  u8 _04[0x10 - 0x04];
  mm::Vec3 unknown10; // Inferred role: position; original member name unknown.
  mm::Quat unknown20; // Inferred role: rotation; original member name unknown.
  u8 _30[0x34 - 0x30];
  f32 unknown34; // Inferred role: height; original member name unknown.
  u8 _38[0x74 - 0x38];
  f32 unknown74;  // Inferred role: unknown height; original member name unknown.
  f32 unknown78;  // Inferred role: unknown height limit; original member name unknown.
  bool unknown7c; // Inferred role: auto run, copied from the pc field property; original member name unknown.
  bool unknown7d; // Inferred role: can start event; original member name unknown.
  bool unknown7e; // Inferred role: climb wall plane valid; original member name unknown.
  bool unknown7f; // Inferred role: blocks the standby talk of the player (GfObjUtil::isStanbyTalkingPlayer); original member name unknown.
  bool unknown80; // Inferred role: jump; original member name unknown.
  u8 _81[0x90 - 0x81];
  mm::Plane unknown90; // Inferred role: climb wall plane, copied from the pc field property; original member name unknown.
  u8 _b0[0xb8 - 0xb0];
  f32 unknownb8; // Inferred role: unknown height; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  GF_OBJ_HANDLE *unknownc0; // Inferred role: ground object; original member name unknown.
  f32 unknownc8;            // Inferred role: float time; original member name unknown.
};

static_assert(offsetof(unknown070, unknown34) == 0x34, "");
static_assert(offsetof(unknown070, unknown74) == 0x74, "");
static_assert(offsetof(unknown070, unknown78) == 0x78, "");
static_assert(offsetof(unknown070, unknownb8) == 0xb8, "");
static_assert(offsetof(unknown070, unknown7c) == 0x7c, "");
static_assert(offsetof(unknown070, unknown7d) == 0x7d, "");
static_assert(offsetof(unknown070, unknown7e) == 0x7e, "");
static_assert(offsetof(unknown070, unknown7f) == 0x7f, "");
static_assert(offsetof(unknown070, unknown80) == 0x80, "");
static_assert(offsetof(unknown070, unknown90) == 0x90, "");
static_assert(offsetof(unknown070, unknownc0) == 0xc0, "");
static_assert(offsetof(unknown070, unknownc8) == 0xc8, "");

class GfObjProperty {
public:
  GfObjPropertyMap *getMap();
  GfObjPropertyDriver *getDriver();
  GfObjPropertyBlade *getBlade();
  GfObjPropertyPcWeapon *getPcWeapon();
  GfObjPropertyEnWeapon *getEnWeapon();
  GfObjPropertyBelonging *getBelonging();
  GfObjPropertyEnemy *getEnemy();
  GfObjPropertyNpc *getNpc();
  GfObjPropertyMob *getMob();
  GfObjPropertyGimmick *getGimmick();
  GfObjPropertyFobj *getFobj();
  GfObjPropertyEvent *getEvent();
  GfObjPropertyUi *getUi();
  virtual ~GfObjProperty() {}

  GF_OBJ_HANDLE *unknown08;          // Inferred role: handle; original member name unknown.
  GfObjPropertyCharacter *unknown10; // Inferred role: character; original member name unknown.
  unknown070 *unknown18;             // Inferred role: move; original member name unknown.
  mm::Vec3 unknown20;                // Inferred role: cached world position written by GfGameUtil::flushProperty; original member name unknown.
  mm::Quat unknown30;                // Inferred role: cached world rotation written by GfGameUtil::flushProperty; original member name unknown.
};

static_assert(offsetof(GfObjProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfObjProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfObjProperty, unknown20) == 0x20, "");
static_assert(offsetof(GfObjProperty, unknown30) == 0x30, "");
static_assert(sizeof(GfObjProperty) == 0x40, "");

class GfObjPropertyMap : public GfObjProperty {};

class GfObjPropertyDriver : public GfObjProperty {
public:
  u8 _40[0x88 - 0x40];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  u8 _c0[0x190 - 0xc0];
  u32 unknown190; // Inferred role: exp, set from DataParamAcc::getExp by GfGameUtil::flushProperty; original member name unknown.
  u32 unknown194; // Inferred role: exp next, set from DataParamAcc::getExpNext; original member name unknown.
  u32 unknown198; // Inferred role: weapon point, set from DataParamAcc::getWeaponPoint; original member name unknown.
  u32 unknown19c; // Inferred role: skill point, set from DataParamAcc::getSkillPoint; original member name unknown.
};

static_assert(offsetof(GfObjPropertyDriver, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyDriver, unknown190) == 0x190, "");
static_assert(offsetof(GfObjPropertyDriver, unknown194) == 0x194, "");
static_assert(offsetof(GfObjPropertyDriver, unknown198) == 0x198, "");
static_assert(offsetof(GfObjPropertyDriver, unknown19c) == 0x19c, "");

class GfObjPropertyBlade : public GfObjProperty {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: tested first by update_BL_DispComboReady; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: tested second by update_BL_DispComboReady; original name unknown.
  };

  u8 _40[0x88 - 0x40];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  u8 _c0[0x190 - 0xc0];
  mm::mtl::FixedArray<unknown109, 3> unknown190; // Inferred role: field skills copied from SDataBlade::unknownae by GfGameUtil::flushProperty; original member name unknown.
  u8 _1a2[0x1a4 - 0x1a2];
  int unknown1a4; // Inferred role: kizuna value, read by GfMenuGfObjAdapter::update_BL_Kizuna; original member name unknown.
  u32 unknown1a8; // Inferred role: special level, read by GfMenuGfObjAdapter::update_BL_SpecialLv; original member name unknown.
  f32 unknown1ac; // Inferred role: special gauge ratio; original member name unknown.
  f32 unknown1b0; // Inferred role: blade change recast ratio; original member name unknown.
  u32 unknown1b4; // Inferred role: combo ready flags, read by GfMenuGfObjAdapter::update_BL_DispComboReady; original member name unknown.
};

static_assert(offsetof(GfObjPropertyBlade, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyBlade, unknown190) == 0x190, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1a4) == 0x1a4, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1b0) == 0x1b0, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1b4) == 0x1b4, "");

class GfObjPropertyPcWeapon : public GfObjProperty {};

class GfObjPropertyEnWeapon : public GfObjProperty {};

class GfObjPropertyBelonging : public GfObjProperty {};

// Inferred role: resistance state of one attribute of an enemy; original type name unknown.
struct unknown138 {
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: resistance on; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: resistance targeted; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: resistance burst; original name unknown.
  };

  u16 unknown00; // Inferred role: flags; original member name unknown.
  u16 unknown02; // Inferred role: resistance level; original member name unknown.
};

static_assert(offsetof(unknown138, unknown02) == 0x02, "");
static_assert(sizeof(unknown138) == 0x04, "");

class GfObjPropertyEnemy : public GfObjProperty {
public:
  u8 _40[0x88 - 0x40];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  u8 _c0[0xc2 - 0xc0];
  bool unknownc2; // Inferred role: scouted; original member name unknown.
  u8 _c3[0xc4 - 0xc3];
  u32 unknownc4; // Inferred role: arts id; original member name unknown.
  u8 _c8[0xd8 - 0xc8];
  u32 unknownd8;  // Inferred role: weak attribute bits; original member name unknown.
  u32 unknowndc;  // Inferred role: element combo id, read by GfMenuReference::getElementComboRootCurrent; original member name unknown.
  f32 unknowne0;  // Inferred role: element combo time ratio; original member name unknown.
  bool unknowne4; // Inferred role: element combo suspended; original member name unknown.
  u8 _e5[0xe8 - 0xe5];
  u32 unknowne8;  // Inferred role: element combo level, read by GfMenuElementComboAdapter::getTargetElementComboLv; original member name unknown.
  u32 unknownec;  // Inferred role: fight combo; original member name unknown.
  f32 unknownf0;  // Inferred role: fight combo time ratio; original member name unknown.
  bool unknownf4; // Inferred role: fight combo suspended; original member name unknown.
  u8 _f5[0xf8 - 0xf5];
  u32 unknownf8;                            // Inferred role: element effect id; original member name unknown.
  unknown138 unknownfc[9];                  // Inferred role: resistance of each attribute, indexed by attribute 1 to 8; original member name unknown.
  mm::mtl::FixedVector<u32, 10> unknown120; // Inferred role: attributes shown in the resistance list; original member name unknown.
  int unknown150;                           // Inferred role: bdat index of the bound enemy gimmick, set by GfBehaviorEnemyField::create; original member name unknown.
};

static_assert(offsetof(GfObjPropertyEnemy, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc2) == 0xc2, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc4) == 0xc4, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownd8) == 0xd8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowndc) == 0xdc, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowne8) == 0xe8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownf8) == 0xf8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownfc) == 0xfc, "");
static_assert(offsetof(GfObjPropertyEnemy, unknown120) == 0x120, "");
static_assert(offsetof(GfObjPropertyEnemy, unknown150) == 0x150, "");

class GfObjPropertyNpc : public GfObjProperty {};

class GfObjPropertyMob : public GfObjProperty {};

class GfObjPropertyGimmick : public GfObjProperty {};

class GfObjPropertyFobj : public GfObjProperty {};

class GfObjPropertyEvent : public GfObjProperty {};

class GfObjPropertyUi : public GfObjProperty {};

} // namespace gf
