#include "gf/field/gf_field_move_speed.h"

#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"

namespace gf {

const char *GfEnemyFieldMoveSpeed::s_V_speed = "V_speed";

GfFieldMoveSpeed::GfFieldMoveSpeed(const CreateInfo *info) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldMoveSpeed::dispose() { m_GF_OBJ_HANDLE = unknown020; }

GfComAsm *GfFieldMoveSpeed::getComAsm() const {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<GfComAsm>();
}

void GfFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  unknown18.unknown08 = unknown10;
  unknown18.unknown0c = speed;
  unknown18.unknown10 = time;
  unknown18.unknown14 = 0.0f;
}

GfEnemyFieldMoveSpeed::GfEnemyFieldMoveSpeed(const CreateInfo *info) {
  if (info != nullptr) {
    create(*info);
  }
}

GfComAsm *GfEnemyFieldMoveSpeed::getComAsm() const {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<GfComAsm>();
}

void GfEnemyFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  f32 current = m_speedTween.unknown10;
  m_speedTween.unknown0c = speed;
  unknown10 = current;
  m_speedTween.unknown08 = current;
  m_speedTween.unknown10 = time == 0.0f ? speed : current;
  m_speedTween.unknown14 = time;
}

void GfEnemyFieldMoveSpeed::update(f32 deltaTime) {
  if (m_GF_OBJ_HANDLE == unknown020) {
    return;
  }
  f32 target = m_speedTween.unknown0c;
  if (m_speedTween.unknown08 < target) {
    m_speedTween.unknown10 += m_speedTween.unknown14 * deltaTime;
    if (target <= m_speedTween.unknown10) {
      m_speedTween.unknown10 = target;
    }
  } else {
    m_speedTween.unknown10 -= m_speedTween.unknown14 * deltaTime;
    if (m_speedTween.unknown10 <= target) {
      m_speedTween.unknown10 = target;
    }
  }
  unknown10 = m_speedTween.unknown10;
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      comAsm->setVariable(s_V_speed, unknown10);
    }
  }
}

} // namespace gf
