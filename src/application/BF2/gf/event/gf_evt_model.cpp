#include "gf/event/gf_evt_model.h"

#include <new>

#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/animation/gf_com_pack_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"

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

// Inferred role: fsm state of the driver model, registered in the constructor after StateIdleBattle and StateIdleField; original name unknown.
constexpr u32 unknown003 = 2;
// Inferred role: fsm state of the driver model, registered in the constructor after StateStartBattle; original name unknown.
constexpr u32 unknown004 = 3;

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

bool GfEvtModelSalvage::isValid() const { return GfGameObj::isValidGameObj(unknown20, false, nullptr); }

void GfEvtModelSalvage::setTransform(const mm::Vec3 &position, f32 rotation) {
  if (GfGameObj::isValidGameObj(unknown20, false, nullptr)) {
    SCOM_OBJ_WARP_POS::create(unknown20, position, mm::Vec3(0.0f, rotation * mm::DEG_TO_RAD, 0.0f), false);
  }
}

const mm::mtl::RTTI *GfEvtModelSalvage::getRTTI() const { return &m_rtti; }

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

GfEvtModelDriver::~GfEvtModelDriver() { unknown298.cleanup(); }

const mm::mtl::RTTI *GfEvtModelDriver::getRTTI() const { return &m_rtti; }

void GfEvtModelDriver::update(const fw::UpdateInfo &info) { unknown298.update(&info); }

void GfEvtModelDriver::setDispWeapon(bool isDisp) {
  GfWeapon *weapon = GfMountManager::getAppendHandles(unknown20, GFATTACH_WEAPON);
  for (u32 index = 0; index < 10; index++) {
    GfObjAcc acc(weapon->getCurrentHandles()[index]);
    if (acc.isValid()) {
      acc.setDisp(OBJDISP_EVENT, isDisp);
    }
  }
}

void GfEvtModelDriver::setDispWeapon(bool isDispRight, bool isDispLeft) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    GfObjAcc acc(isDispRight ? weapon->getCurrentHandles()[1] : weapon->getCurrentHandles()[0]);
    if (acc.isValid()) {
      acc.setDisp(OBJDISP_EVENT, isDispLeft);
    }
  }
}

GF_OBJ_HANDLE *GfEvtModelDriver::getWeaponHandleRight() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[0];
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfEvtModelDriver::getWeaponHandleLeft() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[1];
  }

  return INVALID_HANDLE;
}

void GfEvtModelDriver::setWeaponBattleCommand() { unknown298.setState(unknown003); }

void GfEvtModelDriver::setWeaponFieldCommand() { unknown298.setState(unknown004); }

void GfEvtModelDriver::setStateWeapon(bool isBattle) { unknown298.setState(isBattle ? unknown003 : unknown004); }

void GfEvtModelDriver::setWeaponBattleMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_UNKNOWN_1); }

void GfEvtModelDriver::setWeaponFieldMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE); }

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

GfEvtModelWeapon::~GfEvtModelWeapon() {
  for (u32 index = 0; index < 10; index++) {
    GfObjUtil::destroy(unknown298.getCurrentHandles()[index]);
  }
}

GfEvtModelWeapon *GfEvtModelWeapon::create(GfInitParamWeapon &param) {
  // __LINE__ must be 1286 as in the original source: it is the line argument of operator new.
#line 1286
  GfEvtModelWeapon *model = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfEvtModelWeapon(param);
  model->addRef();
  return model;
}

const mm::mtl::RTTI *GfEvtModelWeapon::getRTTI() const { return &m_rtti; }

void GfEvtModelWeapon::setWeaponBattleCommand() {
  mm::mtl::FixStr<32> command;
  GfGameUtil::makeWeaponCommandBattle(command, unknown348, true, false);
  setWeaponCommand(command.c_str());
}

void GfEvtModelWeapon::setWeaponCommand(const char *command) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown298.getCurrentHandles()[index];
    if (handle != INVALID_HANDLE) {
      GfComAsm *comAsm = GfObjUtil::getObj(handle)->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        comAsm->execCmd(command, ANIM_LAYER_BASE);
      }
    }
  }
}

void GfEvtModelWeapon::setWeaponFieldCommand() {
  mm::mtl::FixStr<32> command;
  GfGameUtil::makeWeaponCommandBattle(command, unknown348, false, false);
  setWeaponCommand(command.c_str());
}

void GfEvtModelWeapon::setWeaponState(const char *state) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown298.getCurrentHandles()[index];
    if (handle != INVALID_HANDLE) {
      GfComAsm *comAsm = GfObjUtil::getObj(handle)->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        comAsm->setState(state, ANIM_LAYER_BASE);
      }
    }
  }
}

void GfEvtModelWeapon::setWeaponBattleState() {
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(state, unknown348, true);
  setWeaponState(state.c_str());
}

void GfEvtModelWeapon::setWeaponFieldState() {
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(state, unknown348, false);
  setWeaponState(state.c_str());
}

ai::State *GfEvtModelDriver::StateIdleBattle::create(void *buffer) { return new (buffer) StateIdleBattle; }

const char *GfEvtModelDriver::StateIdleBattle::getName() const { return "StateIdleBattle"; }

void GfEvtModelDriver::StateIdleBattle::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelDriver::StateIdleBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelDriver::StateIdleBattle::onStep(void *owner, const void *param) {}

ai::State *GfEvtModelDriver::StateIdleField::create(void *buffer) { return new (buffer) StateIdleField; }

const char *GfEvtModelDriver::StateIdleField::getName() const { return "StateIdleField"; }

void GfEvtModelDriver::StateIdleField::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelDriver::StateIdleField::onLeave(void *owner, ai::State *next) {}

void GfEvtModelDriver::StateIdleField::onStep(void *owner, const void *param) {}

ai::State *GfEvtModelBlade::StateIdleBattle::create(void *buffer) { return new (buffer) StateIdleBattle; }

const char *GfEvtModelBlade::StateIdleBattle::getName() const { return "StateIdleBattle"; }

void GfEvtModelBlade::StateIdleBattle::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelBlade::StateIdleBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelBlade::StateIdleBattle::onStep(void *owner, const void *param) {}

ai::State *GfEvtModelBlade::StateIdleField::create(void *buffer) { return new (buffer) StateIdleField; }

const char *GfEvtModelBlade::StateIdleField::getName() const { return "StateIdleField"; }

void GfEvtModelBlade::StateIdleField::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelBlade::StateIdleField::onLeave(void *owner, ai::State *next) {}

void GfEvtModelBlade::StateIdleField::onStep(void *owner, const void *param) {}

ai::State *GfEvtModelEnemy::StateIdleBattle::create(void *buffer) { return new (buffer) StateIdleBattle; }

const char *GfEvtModelEnemy::StateIdleBattle::getName() const { return "StateIdleBattle"; }

void GfEvtModelEnemy::StateIdleBattle::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelEnemy::StateIdleBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelEnemy::StateIdleBattle::onStep(void *owner, const void *param) {}

ai::State *GfEvtModelEnemy::StateIdleField::create(void *buffer) { return new (buffer) StateIdleField; }

const char *GfEvtModelEnemy::StateIdleField::getName() const { return "StateIdleField"; }

void GfEvtModelEnemy::StateIdleField::onEnter(void *owner, ai::State *previous) {}

void GfEvtModelEnemy::StateIdleField::onLeave(void *owner, ai::State *next) {}

void GfEvtModelEnemy::StateIdleField::onStep(void *owner, const void *param) {}

} // namespace gf
