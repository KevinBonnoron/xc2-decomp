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
  u32 maxHp;
  u32 hp;
  u16 level;
  u8 _0a[0x30 - 0x0a];
  bool isBattle;
};

static_assert(offsetof(GfObjPropertyCharacter, hp) == 0x04, "");
static_assert(offsetof(GfObjPropertyCharacter, level) == 0x08, "");
static_assert(offsetof(GfObjPropertyCharacter, isBattle) == 0x30, "");

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

  GF_OBJ_HANDLE *handle;
  GfObjPropertyCharacter *character;
};

static_assert(offsetof(GfObjProperty, character) == 0x10, "");

class GfObjPropertyMap : public GfObjProperty {};

class GfObjPropertyDriver : public GfObjProperty {};

class GfObjPropertyBlade : public GfObjProperty {};

class GfObjPropertyPcWeapon : public GfObjProperty {};

class GfObjPropertyEnWeapon : public GfObjProperty {};

class GfObjPropertyBelonging : public GfObjProperty {};

class GfObjPropertyEnemy : public GfObjProperty {};

class GfObjPropertyNpc : public GfObjProperty {};

class GfObjPropertyMob : public GfObjProperty {};

class GfObjPropertyGimmick : public GfObjProperty {};

class GfObjPropertyFobj : public GfObjProperty {};

class GfObjPropertyEvent : public GfObjProperty {};

class GfObjPropertyUi : public GfObjProperty {};

} // namespace gf
