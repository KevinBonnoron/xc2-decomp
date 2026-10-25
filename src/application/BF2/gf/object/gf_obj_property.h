#pragma once
#include "types.h"
#include <stddef.h>

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

struct GfObjPropertyMove {
  u32 unknown00; // Inferred role: type; original member name unknown.
  u8 _04[0x80 - 0x04];
  bool unknown80; // Inferred role: jump; original member name unknown.
  u8 _81[0xc0 - 0x81];
  GF_OBJ_HANDLE *unknownc0; // Inferred role: ground object; original member name unknown.
  f32 unknownc8;            // Inferred role: float time; original member name unknown.
};

static_assert(offsetof(GfObjPropertyMove, unknown80) == 0x80, "");
static_assert(offsetof(GfObjPropertyMove, unknownc0) == 0xc0, "");
static_assert(offsetof(GfObjPropertyMove, unknownc8) == 0xc8, "");

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
  GfObjPropertyMove *unknown18;      // Inferred role: move; original member name unknown.
};

static_assert(offsetof(GfObjProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfObjProperty, unknown18) == 0x18, "");

class GfObjPropertyMap : public GfObjProperty {};

class GfObjPropertyDriver : public GfObjProperty {
public:
  u8 _20[0x88 - 0x20];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
};

static_assert(offsetof(GfObjPropertyDriver, unknown88) == 0x88, "");

class GfObjPropertyBlade : public GfObjProperty {
public:
  u8 _20[0x88 - 0x20];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
};

static_assert(offsetof(GfObjPropertyBlade, unknown88) == 0x88, "");

class GfObjPropertyPcWeapon : public GfObjProperty {};

class GfObjPropertyEnWeapon : public GfObjProperty {};

class GfObjPropertyBelonging : public GfObjProperty {};

class GfObjPropertyEnemy : public GfObjProperty {
public:
  u8 _20[0x88 - 0x20];
  GfObjPropertyCharacter unknown88; // Inferred role: character, pointed to by unknown10; original member name unknown.
};

static_assert(offsetof(GfObjPropertyEnemy, unknown88) == 0x88, "");

class GfObjPropertyNpc : public GfObjProperty {};

class GfObjPropertyMob : public GfObjProperty {};

class GfObjPropertyGimmick : public GfObjProperty {};

class GfObjPropertyFobj : public GfObjProperty {};

class GfObjPropertyEvent : public GfObjProperty {};

class GfObjPropertyUi : public GfObjProperty {};

} // namespace gf
