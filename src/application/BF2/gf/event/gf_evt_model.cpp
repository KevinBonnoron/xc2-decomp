#include "gf/event/gf_evt_model.h"

#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/animation/gf_com_pack_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

namespace {

// Inferred role: finds the pack animation component of an object; original name unknown.
GfComPackAnim *unknown001(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return nullptr;
  }

  return obj->getComponent<GfComPackAnim>();
}

// Inferred role: finds the pack animation component of a weapon handle of an object; original name unknown.
GfComPackAnim *unknown002(GF_OBJ_HANDLE *owner, u32 index) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(owner, GFATTACH_WEAPON);
  if (weapon == nullptr) {
    return nullptr;
  }

  return unknown001(weapon->getCurrentHandles()[index]);
}

} // namespace

const mm::mtl::RTTI *GfEvtModel::getRTTI() const { return &m_rtti; }

void GfEvtModel::setMount(GfEvtModel *parent, const char *bone) { setMount(parent, bone, mm::Vec3::zero, mm::Vec3::zero); }

bool GfEvtModel::isValid() const { return GfObjUtil::isValid(unknown20); }

void GfEvtModel::update(const fw::UpdateInfo &) {}

GF_OBJ_HANDLE *GfEvtModel::getWeaponHandleRight() const { return reinterpret_cast<GF_OBJ_HANDLE *>(-1); }

GF_OBJ_HANDLE *GfEvtModel::getWeaponHandleLeft() const { return reinterpret_cast<GF_OBJ_HANDLE *>(-1); }

void GfEvtModel::setDispWeapon(bool) {}

void GfEvtModel::setDispWeapon(bool, bool) {}

void GfEvtModel::setWeaponBattleCommand() {}

void GfEvtModel::setWeaponFieldCommand() {}

void GfEvtModel::setWeaponBattleState() {}

void GfEvtModel::setWeaponFieldState() {}

void GfEvtModel::setWeaponBattleMount() {}

void GfEvtModel::setWeaponFieldMount() {}

void GfEvtModelDriver::playAnimWeaponRightCS(const char *name) {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelDriver::isPlayEndAnimWeaponRightCS() {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelDriver::setAnimSpeedWeaponRightCS(f32 speed) {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

void GfEvtModelDriver::playAnimWeaponLeftCS(const char *name) {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelDriver::isPlayEndAnimWeaponLeftCS() {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelDriver::setAnimSpeedWeaponLeftCS(f32 speed) {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

void GfEvtModelBlade::playAnimWeaponRightCS(const char *name) {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelBlade::isPlayEndAnimWeaponRightCS() {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelBlade::setAnimSpeedWeaponRightCS(f32 speed) {
  GfComPackAnim *anim = unknown002(unknown20, 0);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

void GfEvtModelBlade::playAnimWeaponLeftCS(const char *name) {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelBlade::isPlayEndAnimWeaponLeftCS() {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelBlade::setAnimSpeedWeaponLeftCS(f32 speed) {
  GfComPackAnim *anim = unknown002(unknown20, 1);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

bool GfEvtModelDriver::isAnimEnd() const {
  GfComEvtAnim *anim = GfObjUtil::getObj(unknown20)->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->isEnd(ANIM_LAYER_BASE);
  }

  return true;
}

bool GfEvtModelBlade::isAnimEnd() const {
  GfComEvtAnim *anim = GfObjUtil::getObj(unknown20)->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->isEnd(ANIM_LAYER_BASE);
  }

  return true;
}

bool GfEvtModelEnemy::isAnimEnd() const {
  GfComEvtAnim *anim = GfObjUtil::getObj(unknown20)->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    return anim->isEnd(ANIM_LAYER_BASE);
  }

  return true;
}

void GfEvtModelDriver::setDispJiji(bool isDisp) {
  GfWeapon *weapon = GfMountManager::getAppendHandles(unknown20, GFATTACH_APPEND);
  if (weapon != nullptr) {
    for (u32 index = 0; index < 10; index++) {
      GfObjAcc acc(weapon->getCurrentHandles()[index]);
      if (acc.isValid()) {
        acc.setAlphaNormal(isDisp ? 1.0f : 0.0f);
      }
    }
  }
}

void GfEvtModelDriver::setDispRexCoreCrystal(bool isDisp) { GfGameUtil::dispRexCrystal(unknown20, isDisp); }

void GfEvtModelWeapon::playAnimCS(GF_OBJ_HANDLE *handle, const char *name) {
  GfComPackAnim *anim = unknown001(handle);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelWeapon::isPlayEndAnimCS(GF_OBJ_HANDLE *handle) {
  GfComPackAnim *anim = unknown001(handle);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelWeapon::setAnimSpeedCS(GF_OBJ_HANDLE *handle, f32 speed) {
  GfComPackAnim *anim = unknown001(handle);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

void GfEvtModelWeapon::playAnimData(void *data) {
  GfComPackAnim *anim = unknown001(unknown20);
  if (anim != nullptr) {
    anim->play(data);
  }
}

void GfEvtModelWeapon::setScale(f32 scale) {
  GfObjAcc acc(unknown20);
  acc.setModelScale(scale);
}

void GfEvtModelWeapon::playAnimCS(const char *name) {
  GfComPackAnim *anim = unknown001(unknown20);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelWeapon::isPlayEndAnimCS() {
  GfComPackAnim *anim = unknown001(unknown20);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelWeapon::setAnimSpeedCS(f32 speed) {
  GfComPackAnim *anim = unknown001(unknown20);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

} // namespace gf
