#include "event/chara_util.h"

#include <math.h>

#include "event/chara_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_coli_check.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

namespace {

const f32 PI = 3.1415927f;
const f32 PI2 = 6.2831855f;

f32 normalizeRotation(f32 rotation, f32 base) {
  while (rotation < base - PI) {
    rotation += PI2;
  }
  while (base + PI < rotation) {
    rotation -= PI2;
  }
  return rotation;
}

void setWeaponMode(gf::GfEvtModel *model, bool isBattle, bool isState) {
  if (isBattle) {
    if (isState) {
      model->setWeaponBattleState();
    } else {
      model->setWeaponBattleCommand();
    }
  } else {
    if (isState) {
      model->setWeaponFieldState();
    } else {
      model->setWeaponFieldCommand();
    }
  }
}

} // namespace

void CharaUtil::execCmd(gf::GfObj *obj, const char *command) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->execCmd(command);
  }
}

void CharaUtil::execCmd(gf::GfObj *obj, const char *command, const char *state, const char *currentState) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->execCmd(command);
    const char *name = anim->getStateName() != nullptr ? anim->getStateName() : "";
    if (__builtin_strcmp(name, currentState) != 0) {
      anim->setState(state);
    }
  }
}

void CharaUtil::setStat(gf::GfObj *obj, const char *state) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->setState(state);
  }
}

const char *CharaUtil::getStat(gf::GfObj *obj) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->getStateName();
  }

  gf::GfComAsm *animAsm = obj->getComponent<gf::GfComAsm>();
  if (animAsm != nullptr) {
    return animAsm->getStateName(gf::ANIM_LAYER_BASE);
  }

  return "";
}

bool CharaUtil::checkStat(gf::GfObj *obj, const char *state) {
  const char *name;
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    name = anim->getStateName() != nullptr ? anim->getStateName() : "";
  } else {
    gf::GfComAsm *animAsm = obj->getComponent<gf::GfComAsm>();
    if (animAsm == nullptr) {
      return false;
    }
    name = animAsm->getStateName(gf::ANIM_LAYER_BASE) != nullptr ? animAsm->getStateName(gf::ANIM_LAYER_BASE) : "";
  }

  return __builtin_strcmp(name, state) == 0;
}

bool CharaUtil::checkStatSeries(gf::GfObj *obj, const char *series) {
  const char *name;
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    name = anim->getStateName() != nullptr ? anim->getStateName() : "";
  } else {
    gf::GfComAsm *animAsm = obj->getComponent<gf::GfComAsm>();
    if (animAsm == nullptr) {
      return false;
    }
    name = animAsm->getStateName(gf::ANIM_LAYER_BASE) != nullptr ? animAsm->getStateName(gf::ANIM_LAYER_BASE) : "";
  }

  return __builtin_strstr(name, series) != nullptr;
}

bool CharaUtil::isActionBusy(gf::GfObj *obj) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return false;
  }

  if (!mm::mtl::Singleton<CharaManager>::getPtr()->isSeamlessAction()) {
    return false;
  }

  return !checkStatSeries(obj, "S_idle");
}

bool CharaUtil::easeIn(gf::GfObj *obj, const char *name, gf::AnimLayer layer) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->easeIn(name, layer);
  }
  return false;
}

bool CharaUtil::easeOut(gf::GfObj *obj, const char *name, gf::AnimLayer layer) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->easeOut(name, layer);
  }
  return false;
}

bool CharaUtil::setEaseWeight(gf::GfObj *obj, const char *name, gf::AnimLayer layer, f32 weight) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->setEaseWeight(name, layer, weight);
  }
  return false;
}

bool CharaUtil::setEaseSpeed(gf::GfObj *obj, const char *name, gf::AnimLayer layer, f32 speed) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->setEaseSpeed(name, layer, speed);
  }
  return false;
}

bool CharaUtil::hasResAsm(gf::GfObj *obj) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr && anim->unknown550 != nullptr) {
    return true;
  }
  return false;
}

bool CharaUtil::isNeedMove(const mm::Vec3 &position, const mm::Vec3 &target) {
  f32 x = target.x - position.x;
  f32 z = target.z - position.z;
  return sqrtf(x * x + z * z) > 0.1f;
}

bool CharaUtil::isNeedTurn(f32 rotation, f32 target) {
  rotation = normalizeRotation(rotation, target);
  return __builtin_fabsf(target - rotation) > 0.43633232f;
}

bool CharaUtil::isCanTarget(const mm::Vec3 &position, const mm::Vec3 &rotation, const mm::Vec3 &target) {
  f32 angle = -atan2f(position.x - target.x, -(position.z - target.z));
  angle = normalizeRotation(angle, rotation.y) - rotation.y;
  return !(angle < -2.3561945f) && !(angle > 2.3561945f);
}

void CharaUtil::setVariable(gf::GfObj *obj, const char *name, f32 value) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->setVariable(name, value);
  }
}

void CharaUtil::setVariable(gf::GfObj *obj, const char *name, int value) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->setVariable(name, value);
  }
}

void CharaUtil::adjestPosY(mm::Vec3 &position, mm::Vec3 *reference) {
  mm::Vec3 result(position);
  f32 offset = 1.0f;
  if (reference != nullptr && position.y < reference->y) {
    offset = reference->y - position.y + 1.0f;
  }

  mm::Vec3 start;
  start.y = offset + position.y;
  f32 distance = offset + 5.0f;
  start.x = position.x;
  start.z = position.z;
  for (int i = 0; i < 3; i++) {
    if (fw::ColiCheck::getSnapPos(result, start, distance, 0xffffffff)) {
      position = result;
      return;
    }
    distance += 0.5f;
    start.y += 0.5f;
  }
}

void CharaUtil::combat(gf::GfEvtModel *model, bool isBattle, bool isState) {
  gf::GF_EVT_MODEL type = model->type;
  if (model != nullptr && type == gf::GF_EVT_MODEL_DRIVER) {
    setWeaponMode(model, isBattle, isState);
  } else if (model != nullptr && type == gf::GF_EVT_MODEL_BLADE) {
    setWeaponMode(model, isBattle, isState);
  } else if (model != nullptr && type == gf::GF_EVT_MODEL_ENEMY) {
    setWeaponMode(model, isBattle, isState);
  } else if (model != nullptr && type == gf::GF_EVT_MODEL_WEAPON) {
    setWeaponMode(model, isBattle, isState);
  }
}

void CharaUtil::setGravity(gf::GF_OBJ_HANDLE *handle, bool isEnable) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    gf::GfObjAcc acc(handle);
    acc.setGravity(isEnable);
    acc.setCollisionGround(isEnable);
  }
}

} // namespace event
