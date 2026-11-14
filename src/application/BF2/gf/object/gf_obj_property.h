#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
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
  // Inferred role: state of one row of the BTL_Buff table; original type name unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: zeroed by GfObjPropertyCharacter::unknown002; original member name unknown.
    u32 unknown04; // Inferred role: zeroed by GfObjPropertyCharacter::unknown002; original member name unknown.
  };

  GfObjPropertyCharacter();

  // Inferred role: clears the values and the buff states, repeated by the constructors of the character and of the driver and blade properties; original name unknown.
  void unknown002() {
    unknown00 = 0;
    unknown04 = 0;
    unknown08 = 0;
    unknown28 = unknown020;
    for (unknown001 *buff = unknown10.begin(); buff != unknown10.end(); ++buff) {
      buff->unknown00 = 0;
      buff->unknown04 = 0;
    }
  }

  u32 unknown00;                        // Inferred role: max hp; original member name unknown.
  u32 unknown04;                        // Inferred role: hp; original member name unknown.
  u16 unknown08;                        // Inferred role: level; original member name unknown.
  mm::mtl::Array<unknown001> unknown10; // Inferred role: one state per row of the BTL_Buff table; original member name unknown.
  GF_OBJ_HANDLE *unknown28;             // Inferred role: target, copied from the property component by GfComProperty::flush; original member name unknown.
  bool unknown30;                       // Inferred role: battle; original member name unknown.
};

static_assert(sizeof(GfObjPropertyCharacter::unknown001) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter::unknown001, unknown04) == 0x04, "");

static_assert(offsetof(GfObjPropertyCharacter, unknown04) == 0x04, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown08) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown10) == 0x10, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown28) == 0x28, "");
static_assert(offsetof(GfObjPropertyCharacter, unknown30) == 0x30, "");
static_assert(sizeof(GfObjPropertyCharacter) == 0x38, "");

enum {
  PROPERTY_MOVE_UNKNOWN_0 = 0, // Inferred role: property move walk; original name unknown.
  PROPERTY_MOVE_UNKNOWN_1 = 1, // Inferred role: property move swim; original name unknown.
  PROPERTY_MOVE_UNKNOWN_2 = 2, // Inferred role: property move swim on cloud; original name unknown.
  PROPERTY_MOVE_UNKNOWN_3 = 3, // Inferred role: property move climb; original name unknown.
  PROPERTY_MOVE_UNKNOWN_4 = 4, // Inferred role: property move action; original name unknown.
  PROPERTY_MOVE_UNKNOWN_5 = 5, // Inferred role: blocks the follow warp like PROPERTY_MOVE_UNKNOWN_1 (TaskFieldCheckWarp::update); original name unknown.
};

// Inferred role: obj property move; original type name unknown.
struct unknown070 {
  unknown070()
      : unknown00(0), unknown50(mm::Vec3::unitY, 0.0f), unknown70(0), unknown74(0.0f), unknown78(0.0f), unknown7c(false), unknown7d(false), unknown7e(false), unknown7f(false), unknown80(false),
        unknown90(mm::Vec3(1.0f, 0.0f, 0.0f), 0.0f), unknownb0(0), unknownb4(1), unknownb8(0.0f), unknownc0(unknown020), unknownc8(0.0f) {
    unknown10 = mm::Vec3::zero;
    unknown20 = mm::Quat::identity;
    unknown30 = mm::Vec3::zero;
    unknown40 = mm::Quat::identity;
  }

  u32 unknown00;            // Inferred role: type; original member name unknown.
  mm::Vec3 unknown10;       // Inferred role: position; original member name unknown.
  mm::Quat unknown20;       // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown30;       // Inferred role: second position, whose y is the height compared with the water surface by GfEffectGround; original member name unknown.
  mm::Quat unknown40;       // Inferred role: second rotation; original member name unknown.
  mm::Plane unknown50;      // Inferred role: plane built from Vec3::unitY by the constructor; original member name unknown.
  u32 unknown70;            // Inferred role: zeroed by the constructor; original member name unknown.
  f32 unknown74;            // Inferred role: unknown height; original member name unknown.
  f32 unknown78;            // Inferred role: unknown height limit; original member name unknown.
  bool unknown7c;           // Inferred role: auto run, copied from the pc field property; original member name unknown.
  bool unknown7d;           // Inferred role: can start event; original member name unknown.
  bool unknown7e;           // Inferred role: climb wall plane valid; original member name unknown.
  bool unknown7f;           // Inferred role: blocks the standby talk of the player (GfObjUtil::isStanbyTalkingPlayer); original member name unknown.
  bool unknown80;           // Inferred role: jump; original member name unknown.
  mm::Plane unknown90;      // Inferred role: climb wall plane, copied from the pc field property; original member name unknown.
  u32 unknownb0;            // Inferred role: zeroed by the constructor; original member name unknown.
  u32 unknownb4;            // Inferred role: set to 1 by the constructor; original member name unknown.
  f32 unknownb8;            // Inferred role: unknown height; original member name unknown.
  GF_OBJ_HANDLE *unknownc0; // Inferred role: ground object; original member name unknown.
  f32 unknownc8;            // Inferred role: float time; original member name unknown.
};

static_assert(offsetof(unknown070, unknown10) == 0x10, "");
static_assert(offsetof(unknown070, unknown20) == 0x20, "");
static_assert(offsetof(unknown070, unknown30) == 0x30, "");
static_assert(offsetof(unknown070, unknown40) == 0x40, "");
static_assert(offsetof(unknown070, unknown50) == 0x50, "");
static_assert(offsetof(unknown070, unknown70) == 0x70, "");
static_assert(offsetof(unknown070, unknownb0) == 0xb0, "");
static_assert(offsetof(unknown070, unknownb4) == 0xb4, "");
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
static_assert(sizeof(unknown070) == 0xd0, "");

class GfObjProperty {
public:
  // The game's constructors (GfObjPropertyDriver::GfObjPropertyDriver, 1.0.0: 0x71005aa9c8) store the three pointers, empty the string, then set the transform.
  GfObjProperty(GF_OBJ_HANDLE *handle, GfObjPropertyCharacter *character, unknown070 *move) : unknown08(handle), unknown10(character), unknown18(move) {
    unknown20 = mm::Vec3::zero;
    unknown30 = mm::Quat::identity;
  }
  static GfObjProperty *create(GF_OBJ_HANDLE *handle);
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
  mm::mtl::FixStr<64> unknown40;     // Inferred role: text emptied by the constructor; original member name unknown.
};

static_assert(offsetof(GfObjProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfObjProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfObjProperty, unknown20) == 0x20, "");
static_assert(offsetof(GfObjProperty, unknown30) == 0x30, "");
static_assert(offsetof(GfObjProperty, unknown40) == 0x40, "");
static_assert(sizeof(GfObjProperty) == 0x90, "");

class GfObjPropertyMap : public GfObjProperty {
public:
  GfObjPropertyMap(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyDriver : public GfObjProperty {
public:
  GfObjPropertyDriver(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, &unknown88, &unknownc0) {
    unknown88.unknown002();
    unknown190 = 0;
    unknown194 = 0;
    unknown198 = 0;
    unknown19c = 0;
    unknown1a0 = 0;
  }

  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  unknown070 unknownc0;             // Inferred role: move, pointed to by unknown18; original member name unknown.
  u32 unknown190;                   // Inferred role: exp, set from DataParamAcc::getExp by GfGameUtil::flushProperty; original member name unknown.
  u32 unknown194;                   // Inferred role: exp next, set from DataParamAcc::getExpNext; original member name unknown.
  u32 unknown198;                   // Inferred role: weapon point, set from DataParamAcc::getWeaponPoint; original member name unknown.
  u32 unknown19c;                   // Inferred role: skill point, set from DataParamAcc::getSkillPoint; original member name unknown.
  u32 unknown1a0;                   // Inferred role: zeroed by the constructor; original member name unknown.
};

static_assert(offsetof(GfObjPropertyDriver, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyDriver, unknownc0) == 0xc0, "");
static_assert(offsetof(GfObjPropertyDriver, unknown190) == 0x190, "");
static_assert(offsetof(GfObjPropertyDriver, unknown194) == 0x194, "");
static_assert(offsetof(GfObjPropertyDriver, unknown198) == 0x198, "");
static_assert(offsetof(GfObjPropertyDriver, unknown19c) == 0x19c, "");
static_assert(offsetof(GfObjPropertyDriver, unknown1a0) == 0x1a0, "");
static_assert(sizeof(GfObjPropertyDriver) == 0x1b0, "");

class GfObjPropertyBlade : public GfObjProperty {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: tested first by update_BL_DispComboReady; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: tested second by update_BL_DispComboReady; original name unknown.
  };

  GfObjPropertyBlade(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, &unknown88, &unknownc0), unknown1b4(0) {
    unknown88.unknown002();
    unknown190.assign(unknown109());
    unknown1a4 = 0;
    unknown1a8 = 0;
    unknown1ac = 0.0f;
    unknown1b0 = 0.0f;
  }

  GfObjPropertyCharacter unknown88;              // Inferred role: character, pointed to by unknown10; original member name unknown.
  unknown070 unknownc0;                          // Inferred role: move, pointed to by unknown18; original member name unknown.
  mm::mtl::FixedArray<unknown109, 3> unknown190; // Inferred role: field skills copied from SDataBlade::unknownae by GfGameUtil::flushProperty; original member name unknown.
  int unknown1a4;                                // Inferred role: kizuna value, read by GfMenuGfObjAdapter::update_BL_Kizuna; original member name unknown.
  u32 unknown1a8;                                // Inferred role: special level, read by GfMenuGfObjAdapter::update_BL_SpecialLv; original member name unknown.
  f32 unknown1ac;                                // Inferred role: special gauge ratio; original member name unknown.
  f32 unknown1b0;                                // Inferred role: blade change recast ratio; original member name unknown.
  u32 unknown1b4;                                // Inferred role: combo ready flags, read by GfMenuGfObjAdapter::update_BL_DispComboReady; original member name unknown.
};

static_assert(offsetof(GfObjPropertyBlade, unknown88) == 0x88, "");
static_assert(offsetof(GfObjPropertyBlade, unknownc0) == 0xc0, "");
static_assert(offsetof(GfObjPropertyBlade, unknown190) == 0x190, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1a4) == 0x1a4, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1b0) == 0x1b0, "");
static_assert(offsetof(GfObjPropertyBlade, unknown1b4) == 0x1b4, "");
static_assert(sizeof(GfObjPropertyBlade) == 0x1c0, "");

class GfObjPropertyPcWeapon : public GfObjProperty {
public:
  GfObjPropertyPcWeapon(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyEnWeapon : public GfObjProperty {
public:
  GfObjPropertyEnWeapon(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyBelonging : public GfObjProperty {
public:
  GfObjPropertyBelonging(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

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
  // The game (1.0.0: 0x71005aaee4) zeroes the nine elements of unknownfc while it constructs the members (0x71005aaf64-0x71005aaf88, before the body) and again at the end of the body
  // (0x71005ab028-0x71005ab034, with unknownf8): the value-initialisation and the loop are both in the game's code.
  GfObjPropertyEnemy(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, &unknown88, nullptr), unknownfc() {
    unknown88.unknown002();
    unknownc0 = 0;
    unknownc2 = false;
    unknownc3 = false;
    unknownc4 = 0;
    unknownc8 = 0;
    unknownd0 = nullptr;
    unknownd8 = 0;
    unknowndc = 0;
    unknowne0 = 0.0f;
    unknowne4 = false;
    unknowne8 = 0;
    unknownec = 0;
    unknownf0 = 0.0f;
    unknownf4 = false;
    unknownf8 = 0;
    for (int i = 0; i < 9; i++) {
      unknownfc[i].unknown00 = 0;
      unknownfc[i].unknown02 = 0;
    }
    unknown150 = 0;
  }

  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
  // The width of unknownc0 is not proven: the constructor zeroes 0xc0..0xc7 with one 64-bit store (0x71005ab018), nothing else known reads the two bytes, and u16 is the simplest type that gives the
  // store.
  u16 unknownc0;  // Inferred role: zeroed by the constructor; original member name unknown.
  bool unknownc2; // Inferred role: scouted; original member name unknown.
  bool unknownc3; // Inferred role: flag written by GfEnemyBattleProperty before the scouted flag; original member name unknown.
  u32 unknownc4;  // Inferred role: arts id; original member name unknown.
  u32 unknownc8;  // Inferred role: arts message id; original member name unknown.
  u8 _cc[0xd0 - 0xcc];
  u8 *unknownd0;  // Inferred role: arts message bdat; original member name unknown.
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
static_assert(offsetof(GfObjPropertyEnemy, unknownc0) == 0xc0, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc2) == 0xc2, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc3) == 0xc3, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc4) == 0xc4, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownd8) == 0xd8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownc8) == 0xc8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownd0) == 0xd0, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowndc) == 0xdc, "");
static_assert(offsetof(GfObjPropertyEnemy, unknowne8) == 0xe8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownf8) == 0xf8, "");
static_assert(offsetof(GfObjPropertyEnemy, unknownfc) == 0xfc, "");
static_assert(offsetof(GfObjPropertyEnemy, unknown120) == 0x120, "");
static_assert(offsetof(GfObjPropertyEnemy, unknown150) == 0x150, "");
static_assert(sizeof(GfObjPropertyEnemy) == 0x160, "");

class GfObjPropertyNpc : public GfObjProperty {
public:
  GfObjPropertyNpc(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyMob : public GfObjProperty {
public:
  GfObjPropertyMob(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyGimmick : public GfObjProperty {
public:
  GfObjPropertyGimmick(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyFobj : public GfObjProperty {
public:
  GfObjPropertyFobj(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyEvent : public GfObjProperty {
public:
  GfObjPropertyEvent(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyExtra : public GfObjProperty {
public:
  GfObjPropertyExtra(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

class GfObjPropertyUi : public GfObjProperty {
public:
  GfObjPropertyUi(GF_OBJ_HANDLE *handle) : GfObjProperty(handle, nullptr, nullptr) {}
};

} // namespace gf
