#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
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
  u8 _0a[0x30 - 0x0a];
  bool unknown30; // Inferred role: battle; original member name unknown.
};

static_assert(offsetof(GfObjPropertyCharacter, unknown04) == 0x04, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown08) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown30) == 0x30, "");

enum {
  PROPERTY_MOVE_WALK = 0,
  PROPERTY_MOVE_SWIM = 1,
  PROPERTY_MOVE_SWIM_ON_CLOUD = 2,
  PROPERTY_MOVE_CLIMB = 3,
  PROPERTY_MOVE_ACTION = 4,
};

// Inferred role: obj property move; original type name unknown.
struct unknown070 {
  u32 unknown00; // Inferred role: type; original member name unknown.
  u8 _04[0x34 - 0x04];
  f32 unknown34; // Inferred role: height; original member name unknown.
  u8 _38[0x7d - 0x38];
  bool unknown7d; // Inferred role: can start event; original member name unknown.
  u8 _7e[0x80 - 0x7e];
  bool unknown80; // Inferred role: jump; original member name unknown.
  u8 _81[0xc0 - 0x81];
  GF_OBJ_HANDLE *unknownc0; // Inferred role: ground object; original member name unknown.
  f32 unknownc8;            // Inferred role: float time; original member name unknown.
};

static_assert(offsetof(unknown070, unknown34) == 0x34, "");
static_assert(offsetof(unknown070, unknown7d) == 0x7d, "");
static_assert(offsetof(unknown070, unknown80) == 0x80, "");
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
  u8 _bc[0x190 - 0xbc];
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
  u8 _40[0x88 - 0x40];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  u8 _bc[0x190 - 0xbc];
  mm::mtl::FixedArray<unknown109, 3> unknown190; // Inferred role: field skills copied from SDataBlade::unknownae by GfGameUtil::flushProperty; original member name unknown.
};

static_assert(offsetof(GfObjPropertyBlade, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyBlade, unknown190) == 0x190, "");

class GfObjPropertyPcWeapon : public GfObjProperty {};

class GfObjPropertyEnWeapon : public GfObjProperty {};

class GfObjPropertyBelonging : public GfObjProperty {};

class GfObjPropertyEnemy : public GfObjProperty {
public:
  u8 _40[0x88 - 0x40];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  u8 _bc[0xdc - 0xbc];
  u32 unknowndc; // Inferred role: element combo id, read by GfMenuReference::getElementComboRootCurrent; original member name unknown.
  u8 _e0[0xe8 - 0xe0];
  u32 unknowne8; // Inferred role: element combo level, read by GfMenuElementComboAdapter::getTargetElementComboLv; original member name unknown.
};

static_assert(offsetof(GfObjPropertyEnemy, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowndc) == 0xdc, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowne8) == 0xe8, "");

class GfObjPropertyNpc : public GfObjProperty {};

class GfObjPropertyMob : public GfObjProperty {};

class GfObjPropertyGimmick : public GfObjProperty {};

class GfObjPropertyFobj : public GfObjProperty {};

class GfObjPropertyEvent : public GfObjProperty {};

class GfObjPropertyUi : public GfObjProperty {};

} // namespace gf
