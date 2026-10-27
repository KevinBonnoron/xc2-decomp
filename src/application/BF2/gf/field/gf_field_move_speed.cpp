#include "gf/field/gf_field_move_speed.h"

#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"

namespace gf {

const char *GfEnemyFieldMoveSpeed::s_V_speed = "V_speed";

void GfFieldMoveSpeed::dispose() { unknown00 = INVALID_HANDLE; }

GfComAsm *GfFieldMoveSpeed::getComAsm() const {
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<GfComAsm>();
}

void GfFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  unknown20 = unknown10;
  unknown24 = speed;
  unknown28 = time;
  unknown2c = 0.0f;
}

GfComAsm *GfEnemyFieldMoveSpeed::getComAsm() const {
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<GfComAsm>();
}

void GfEnemyFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  f32 current = unknown18.unknown10;
  unknown18.unknown0c = speed;
  unknown10 = current;
  unknown18.unknown08 = current;
  unknown18.unknown10 = time == 0.0f ? speed : current;
  unknown18.unknown14 = time;
}

void GfEnemyFieldMoveSpeed::update(f32 deltaTime) {
  if (unknown00 == INVALID_HANDLE) {
    return;
  }
  f32 target = unknown18.unknown0c;
  if (unknown18.unknown08 < target) {
    unknown18.unknown10 += unknown18.unknown14 * deltaTime;
    if (target <= unknown18.unknown10) {
      unknown18.unknown10 = target;
    }
  } else {
    unknown18.unknown10 -= unknown18.unknown14 * deltaTime;
    if (unknown18.unknown10 <= target) {
      unknown18.unknown10 = target;
    }
  }
  unknown10 = unknown18.unknown10;
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      comAsm->setVariable(s_V_speed, unknown10);
    }
  }
}

} // namespace gf
