#include "gf/event/gf_evt_model.h"

#include <new>
#include <string.h>

#include "gf/game/event/gf_game_event.h"
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
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"

namespace gf {

namespace {

// Inferred role: finds a component of an object; original name unknown.
template <typename T> T *unknown001(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return nullptr;
  }

  return obj->getComponent<T>();
}

// Inferred role: finds the pack animation component of a weapon handle of an object; original name unknown.
GfComPackAnim *unknown002(GF_OBJ_HANDLE *owner, u32 index) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(owner, GFATTACH_WEAPON);
  if (weapon == nullptr) {
    return nullptr;
  }

  return unknown001<GfComPackAnim>(weapon->getCurrentHandles()[index]);
}

// Inferred role: sets the animation state of an object; original name unknown.
void unknown005(GF_OBJ_HANDLE *handle, const char *state) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  GfComEvtAnim *anim = obj->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    anim->setState(state);
  }
}

// Inferred role: sets the animation state of every appended weapon handle of an object; original name unknown.
void unknown006(GF_OBJ_HANDLE *owner, const char *state) {
  GfWeapon *weapon = GfMountManager::getAppendHandles(owner, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    for (u32 index = 0; index < 10; index++) {
      GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[index];
      if (handle != INVALID_HANDLE) {
        GfComAsm *comAsm = GfObjUtil::getObj(handle)->getComponent<GfComAsm>();
        if (comAsm != nullptr) {
          comAsm->setState(state, ANIM_LAYER_BASE);
        }
      }
    }
  }
}

// Inferred role: shows or hides every appended weapon handle of an object; original name unknown.
void unknown007(GF_OBJ_HANDLE *owner, bool isDisp) {
  GfWeapon *weapon = GfMountManager::getAppendHandles(owner, GFATTACH_WEAPON);
  for (u32 index = 0; index < 10; index++) {
    GfObjAcc acc(weapon->getCurrentHandles()[index]);
    if (acc.isValid()) {
      acc.setDisp(OBJDISP_EVENT, isDisp);
    }
  }
}

// Inferred role: shows or hides one of the two weapon handles of an object; original name unknown.
void unknown008(GF_OBJ_HANDLE *owner, bool isDispRight, bool isDispLeft) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(owner, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    GfObjAcc acc(isDispRight ? weapon->getCurrentHandles()[1] : weapon->getCurrentHandles()[0]);
    if (acc.isValid()) {
      acc.setDisp(OBJDISP_EVENT, isDispLeft);
    }
  }
}

// Inferred role: sends a command to the animation of an object and sets its state when it differs; original name unknown.
void unknown009(GF_OBJ_HANDLE *handle, const char *command, const char *state) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  GfComEvtAnim *anim = obj->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    anim->execCmd(command);
    if (strcmp(anim->getStateName() != nullptr ? anim->getStateName() : "", state) != 0) {
      anim->setState(state);
    }
  }
}

// Inferred role: sends a command to every appended weapon handle of an object; original name unknown.
void unknown010(GF_OBJ_HANDLE *owner, const char *command) {
  GfWeapon *weapon = GfMountManager::getAppendHandles(owner, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    for (u32 index = 0; index < 10; index++) {
      GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[index];
      if (handle != INVALID_HANDLE) {
        GfComAsm *comAsm = GfObjUtil::getObj(handle)->getComponent<GfComAsm>();
        if (comAsm != nullptr) {
          comAsm->execCmd(command, ANIM_LAYER_BASE);
        }
      }
    }
  }
}

// Inferred role: sends a command to the animation of an object; original name unknown.
void unknown011(GF_OBJ_HANDLE *handle, const char *command) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  GfComEvtAnim *anim = obj->getComponent<GfComEvtAnim>();
  if (anim != nullptr) {
    anim->execCmd(command);
  }
}

// Inferred role: fsm state of the driver model, registered in the constructor after StateIdleBattle and StateIdleField; original name unknown.
constexpr u32 unknown003 = 2;
// Inferred role: fsm state of the driver model, registered in the constructor after StateStartBattle; original name unknown.
constexpr u32 unknown004 = 3;
// Inferred role: fsm state of the models, registered first in the constructor, entered after StateEndBattle; original name unknown.
constexpr u32 unknown012 = 0;
// Inferred role: fsm state of the models, registered second in the constructor, entered after StateStartBattle; original name unknown.
constexpr u32 unknown013 = 1;

} // namespace

GfEvtModel::GfEvtModel(GF_EVT_MODEL type, u32 param) : unknown18(type), unknown1c(param), unknown20(INVALID_HANDLE), unknown28(nullptr) { GfObjManager::addListener(this, OBJEVT_ALL); }

GfEvtModel::~GfEvtModel() {
  destroy();
  GfObjManager::removeListener(this);
}

void GfEvtModel::destroy() {
  GfGameEvent::destroyEvtModel(this);
  while (unknown58.size() != 0) {
    unknown58.front()->resetMount(this);
  }
  if (unknown28 != nullptr) {
    GfEvtModel *parent = unknown28;
    unknown28 = nullptr;
    parent->release();
  }
  GfObjUtil::destroy(unknown20);
  unknown20 = INVALID_HANDLE;
}

bool GfEvtModel::isBusy(mm::mtl::FixStr<128> *) const {
  mm::mtl::FixStr<128> reason;
  if (unknown20 == INVALID_HANDLE) {
    return false;
  }
  for (int attach = GFATTACH_WEAPON; attach <= GFATTACH_WEAPON_EXTRA; attach++) {
    GfWeapon *weapon = GfMountManager::getAppendHandles(unknown20, static_cast<GFATTACH>(attach));
    if (weapon != nullptr) {
      for (u32 index = 0; index < 10; index++) {
        GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[index];
        if (handle != INVALID_HANDLE && GfObjUtil::getObj(handle) != nullptr && !GfGameObj::isValidGameObj(handle, true, &reason)) {
          return true;
        }
      }
    }
  }
  return !GfGameObj::isValidGameObj(unknown20, true, &reason);
}

void GfEvtModel::resetMount(GfEvtModel *parent) {
  if (parent == nullptr || unknown28 == nullptr) {
    return;
  }
  if (GfObjUtil::getParentHandle(unknown20) == parent->unknown20) {
    GfObjUtil::unmountFromBone(unknown20);
  }
  if (strcmp(unknown30.c_str(), "MT_met") == 0) {
    GfMountManager::setMountType(unknown20, GFATTACH_APPEND, OPTMNT_WIRE);
  }
  unknown30 = "";
  unknown28 = nullptr;
  release();
  mm::mtl::FixedList<GfEvtModel *, 32>::iterator it = mm::mtl::find(parent->unknown58.begin(), parent->unknown58.end(), this);
  parent->unknown58.erase(it);
}

void GfEvtModel::setMount(GfEvtModel *parent, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot) {
  if (unknown28 == nullptr) {
    if (mm::mtl::find(parent->unknown58.begin(), parent->unknown58.end(), this) == parent->unknown58.end()) {
      parent->unknown58.push_back(this);
      addRef();
      unknown28 = parent;
      unknown30 = bone;
      parent->execMount(this, pos, rot);
    }
  }
}

void GfEvtModel::execUnmount(GfEvtModel *child) {
  if (GfObjUtil::getParentHandle(child->unknown20) == unknown20) {
    GfObjUtil::unmountFromBone(child->unknown20);
  }
}

void GfEvtModel::execMount(GfEvtModel *child) {
  if (GfObjUtil::getParentHandle(child->unknown20) != unknown20 && !child->isBusy(nullptr)) {
    if (strcmp(child->unknown30.c_str(), "MT_met") == 0) {
      GfMountManager::execMount(unknown20, GFATTACH_APPEND, OPTMNT_UNKNOWN_0);
    }
    GfObjUtil::mountToBone(child->unknown20, unknown20, child->unknown30.c_str());
  }
}

void GfEvtModel::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32) {
  if (unknown20 != handle) {
    return;
  }
  switch (event) {
  case OBJEVT_LOADED:
    for (mm::mtl::FixedList<GfEvtModel *, 32>::iterator it = unknown58.begin(); it != unknown58.end(); ++it) {
      execMount(*it);
    }
    if (unknown28 != nullptr && !unknown28->isBusy(nullptr)) {
      unknown28->execMount(this);
    }
    break;
  case OBJEVT_DESTROY:
    for (mm::mtl::FixedList<GfEvtModel *, 32>::iterator it = unknown58.begin(); it != unknown58.end(); ++it) {
      execUnmount(*it);
    }
    if (unknown28 != nullptr && !unknown28->isBusy(nullptr)) {
      unknown28->execUnmount(this);
      unknown28 = nullptr;
    }
    break;
  default:
    break;
  }
}

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

GfEvtModelSalvage::GfEvtModelSalvage(GfInitParamDriver &param) : GfEvtModelDriver(param) {}

GfEvtModelSalvage *GfEvtModelSalvage::create(GfInitParamDriver &param) {
  // __LINE__ must be 689 as in the original source: it is the line argument of operator new.
#line 689
  GfEvtModelSalvage *model = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfEvtModelSalvage(param);
  model->addRef();
  return model;
}

bool GfEvtModelSalvage::isValid() const { return GfGameObj::isValidGameObj(unknown20, false, nullptr); }

void GfEvtModelSalvage::setTransform(const mm::Vec3 &position, f32 rotation) {
  if (GfGameObj::isValidGameObj(unknown20, false, nullptr)) {
    SCOM_OBJ_WARP_POS::create(unknown20, position, mm::Vec3(0.0f, rotation * mm::DEG_TO_RAD, 0.0f), false);
  }
}

const mm::mtl::RTTI *GfEvtModelSalvage::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfEvtModelEvent::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfEvtModelNpc::getRTTI() const { return &m_rtti; }

GfEvtModelEvent *GfEvtModelEvent::create(GfInitParamEventObj &param) {
  // __LINE__ must be 1451 as in the original source: it is the line argument of operator new.
#line 1451
  GfEvtModelEvent *model = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfEvtModelEvent(param);
  model->addRef();
  return model;
}

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

GfEvtModelEnemy *GfEvtModelEnemy::create(GfInitParamEnemy &param) {
  // __LINE__ must be 1054 as in the original source: it is the line argument of operator new.
#line 1054
  GfEvtModelEnemy *model = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfEvtModelEnemy(param);
  model->addRef();
  return model;
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

void GfEvtModelDriver::setDispWeapon(bool isDisp) { unknown007(unknown20, isDisp); }

void GfEvtModelDriver::setDispWeapon(bool isDispRight, bool isDispLeft) { unknown008(unknown20, isDispRight, isDispLeft); }

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

GfEvtModelBlade::~GfEvtModelBlade() { unknown298.cleanup(); }

const mm::mtl::RTTI *GfEvtModelBlade::getRTTI() const { return &m_rtti; }

void GfEvtModelBlade::update(const fw::UpdateInfo &info) { unknown298.update(&info); }

void GfEvtModelBlade::setDispWeapon(bool isDisp) { unknown007(unknown20, isDisp); }

void GfEvtModelBlade::setDispWeapon(bool isDispRight, bool isDispLeft) { unknown008(unknown20, isDispRight, isDispLeft); }

GF_OBJ_HANDLE *GfEvtModelBlade::getWeaponHandleRight() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[0];
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfEvtModelBlade::getWeaponHandleLeft() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[1];
  }

  return INVALID_HANDLE;
}

void GfEvtModelBlade::setWeaponBattleCommand() { unknown298.setState(unknown003); }

void GfEvtModelBlade::setWeaponFieldCommand() { unknown298.setState(unknown004); }

void GfEvtModelBlade::setStateWeapon(bool isBattle) { unknown298.setState(isBattle ? unknown003 : unknown004); }

void GfEvtModelBlade::setWeaponBattleMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_UNKNOWN_1); }

void GfEvtModelBlade::setWeaponFieldMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE); }

GfEvtModelEnemy::~GfEvtModelEnemy() { unknown298.cleanup(); }

const mm::mtl::RTTI *GfEvtModelEnemy::getRTTI() const { return &m_rtti; }

void GfEvtModelEnemy::update(const fw::UpdateInfo &info) { unknown298.update(&info); }

void GfEvtModelEnemy::setDispWeapon(bool isDisp) { unknown007(unknown20, isDisp); }

void GfEvtModelEnemy::setDispWeapon(bool isDispRight, bool isDispLeft) { unknown008(unknown20, isDispRight, isDispLeft); }

GF_OBJ_HANDLE *GfEvtModelEnemy::getWeaponHandleRight() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[0];
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfEvtModelEnemy::getWeaponHandleLeft() const {
  GfWeapon *weapon = GfMountManager::getGfWeapon(unknown20, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    return weapon->getCurrentHandles()[1];
  }

  return INVALID_HANDLE;
}

void GfEvtModelEnemy::setWeaponBattleCommand() { unknown298.setState(unknown003); }

void GfEvtModelEnemy::setWeaponFieldCommand() { unknown298.setState(unknown004); }

void GfEvtModelEnemy::setStateWeapon(bool isBattle) { unknown298.setState(isBattle ? unknown003 : unknown004); }

void GfEvtModelEnemy::setWeaponBattleMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_UNKNOWN_1); }

void GfEvtModelEnemy::setWeaponFieldMount() { GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE); }

void GfEvtModelEnemy::setWeaponBattleState() {
  setWeaponBattleMount();
  mm::mtl::FixStr<32> weaponState;
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(weaponState, unknown20, true);
  GfGameUtil::makeStateIdle(state, unknown20, true);
  unknown005(unknown20, state.c_str());
  unknown006(unknown20, weaponState.c_str());
}

void GfEvtModelEnemy::setWeaponFieldState() {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE);
  mm::mtl::FixStr<32> weaponState;
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(weaponState, unknown20, false);
  GfGameUtil::makeStateIdle(state, unknown20, false);
  unknown005(unknown20, state.c_str());
  unknown006(unknown20, weaponState.c_str());
}

void GfEvtModelDriver::setWeaponBattleState() {
  setWeaponBattleMount();
  mm::mtl::FixStr<32> weaponState;
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(weaponState, unknown20, true);
  GfGameUtil::makeStateIdleByBlade(state, unknown310, true);
  unknown005(unknown20, state.c_str());
  unknown006(unknown20, weaponState.c_str());
}

void GfEvtModelDriver::setWeaponFieldState() {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE);
  mm::mtl::FixStr<32> weaponState;
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeWeaponStateIdle(weaponState, unknown20, false);
  GfGameUtil::makeStateIdleByBlade(state, unknown310, false);
  unknown005(unknown20, state.c_str());
  unknown006(unknown20, weaponState.c_str());
}

void GfEvtModelBlade::setWeaponBattleState() {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_UNKNOWN_1);
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeStateIdle(state, unknown20, true);
  unknown005(unknown20, state.c_str());
}

void GfEvtModelBlade::setWeaponFieldState() {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, OPTMNT_WIRE);
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeStateIdle(state, unknown20, false);
  unknown005(unknown20, state.c_str());
}

void GfEvtModelWeapon::playAnimCS(GF_OBJ_HANDLE *handle, const char *name) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(handle);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelWeapon::isPlayEndAnimCS(GF_OBJ_HANDLE *handle) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(handle);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelWeapon::setAnimSpeedCS(GF_OBJ_HANDLE *handle, f32 speed) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(handle);
  if (anim != nullptr) {
    anim->setSpeed(speed);
  }
}

void GfEvtModelWeapon::playAnimData(void *data) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(unknown20);
  if (anim != nullptr) {
    anim->play(data);
  }
}

void GfEvtModelWeapon::setScale(f32 scale) {
  GfObjAcc acc(unknown20);
  acc.setModelScale(scale);
}

void GfEvtModelWeapon::playAnimCS(const char *name) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(unknown20);
  if (anim != nullptr) {
    anim->play(name);
  }
}

bool GfEvtModelWeapon::isPlayEndAnimCS() {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(unknown20);
  if (anim != nullptr && !anim->isPlayEnd()) {
    return false;
  }

  return true;
}

void GfEvtModelWeapon::setAnimSpeedCS(f32 speed) {
  GfComPackAnim *anim = unknown001<GfComPackAnim>(unknown20);
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

ai::State *GfEvtModelDriver::StateStartBattle::create(void *buffer) { return new (buffer) StateStartBattle; }

const char *GfEvtModelDriver::StateStartBattle::getName() const { return "StateStartBattle"; }

void GfEvtModelDriver::StateStartBattle::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfEvtModelDriver *>(owner), previous); }

void GfEvtModelDriver::StateStartBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelDriver::StateStartBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelDriver *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

void GfEvtModelDriver::StateStartBattle::enter(GfEvtModelDriver *model, ai::State *previous) {
  if (GfMountManager::getMountType(model->unknown20, GFATTACH_WEAPON) != OPTMNT_UNKNOWN_1) {
    model->setWeaponBattleMount();
  }
  mm::mtl::FixStr<32> weaponCommand;
  mm::mtl::FixStr<32> command;
  GfGameUtil::makeWeaponCommandBattle(weaponCommand, model->unknown20, true, false);
  GfGameUtil::makeCommandBattle(command, true);
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeStateBattleByBlade(state, model->unknown310, true);
  unknown009(model->unknown20, command.c_str(), state.c_str());
  unknown010(model->unknown20, weaponCommand.c_str());
}

void GfEvtModelDriver::StateStartBattle::update(GfEvtModelDriver *model, const fw::UpdateInfo &info) {
  if (model->isAnimEnd()) {
    unknown011(model->unknown20, "C_btidle");
    reqState(unknown013);
  }
}

ai::State *GfEvtModelDriver::StateEndBattle::create(void *buffer) { return new (buffer) StateEndBattle; }

const char *GfEvtModelDriver::StateEndBattle::getName() const { return "StateEndBattle"; }

void GfEvtModelDriver::StateEndBattle::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfEvtModelDriver *>(owner), previous); }

void GfEvtModelDriver::StateEndBattle::onLeave(void *owner, ai::State *next) { leave(static_cast<GfEvtModelDriver *>(owner), next); }

void GfEvtModelDriver::StateEndBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelDriver *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

void GfEvtModelDriver::StateEndBattle::leave(GfEvtModelDriver *model, ai::State *next) { model->setWeaponFieldMount(); }

void GfEvtModelDriver::StateEndBattle::enter(GfEvtModelDriver *model, ai::State *previous) {
  if (GfMountManager::getMountType(model->unknown20, GFATTACH_WEAPON) != OPTMNT_WIRE) {
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, model->unknown20, false, false);
    GfGameUtil::makeCommandBattle(command, false);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattleByBlade(state, model->unknown310, false);
    unknown009(model->unknown20, command.c_str(), state.c_str());
    unknown010(model->unknown20, weaponCommand.c_str());
  }
}

void GfEvtModelDriver::StateEndBattle::update(GfEvtModelDriver *model, const fw::UpdateInfo &info) {
  if (model->isAnimEnd()) {
    unknown011(model->unknown20, "C_idle");
    mm::mtl::FixStr<32> weaponState;
    GfGameUtil::makeWeaponStateIdle(weaponState, model->unknown20, false);
    unknown006(model->unknown20, weaponState.c_str());
    reqState(unknown012);
  }
}

ai::State *GfEvtModelBlade::StateStartBattle::create(void *buffer) { return new (buffer) StateStartBattle; }

const char *GfEvtModelBlade::StateStartBattle::getName() const { return "StateStartBattle"; }

void GfEvtModelBlade::StateStartBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelBlade::StateStartBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelBlade *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

ai::State *GfEvtModelBlade::StateEndBattle::create(void *buffer) { return new (buffer) StateEndBattle; }

const char *GfEvtModelBlade::StateEndBattle::getName() const { return "StateEndBattle"; }

void GfEvtModelBlade::StateEndBattle::onLeave(void *owner, ai::State *next) { leave(static_cast<GfEvtModelBlade *>(owner), next); }

void GfEvtModelBlade::StateEndBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelBlade *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

void GfEvtModelBlade::StateEndBattle::leave(GfEvtModelBlade *model, ai::State *next) { GfMountManager::execMount(model->unknown20, GFATTACH_WEAPON, OPTMNT_WIRE); }

ai::State *GfEvtModelEnemy::StateStartBattle::create(void *buffer) { return new (buffer) StateStartBattle; }

const char *GfEvtModelEnemy::StateStartBattle::getName() const { return "StateStartBattle"; }

void GfEvtModelEnemy::StateStartBattle::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfEvtModelEnemy *>(owner), previous); }

void GfEvtModelEnemy::StateStartBattle::onLeave(void *owner, ai::State *next) {}

void GfEvtModelEnemy::StateStartBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelEnemy *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

void GfEvtModelEnemy::StateStartBattle::enter(GfEvtModelEnemy *model, ai::State *previous) {
  mm::mtl::FixStr<32> weaponCommand;
  mm::mtl::FixStr<32> command;
  GfGameUtil::makeWeaponCommandBattle(weaponCommand, model->unknown20, true, true);
  GfGameUtil::makeCommandBattle(command, true);
  mm::mtl::FixStr<32> state;
  GfGameUtil::makeStateBattle(state, model->unknown20, true);
  unknown009(model->unknown20, command.c_str(), state.c_str());
  unknown010(model->unknown20, weaponCommand.c_str());
  if (GfMountManager::getMountType(model->unknown20, GFATTACH_WEAPON) != OPTMNT_UNKNOWN_1) {
    model->setWeaponBattleMount();
  }
}

void GfEvtModelEnemy::StateStartBattle::update(GfEvtModelEnemy *model, const fw::UpdateInfo &info) {
  if (model->isAnimEnd()) {
    unknown011(model->unknown20, "C_btidle");
    reqState(unknown013);
  }
}

ai::State *GfEvtModelEnemy::StateEndBattle::create(void *buffer) { return new (buffer) StateEndBattle; }

const char *GfEvtModelEnemy::StateEndBattle::getName() const { return "StateEndBattle"; }

void GfEvtModelEnemy::StateEndBattle::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfEvtModelEnemy *>(owner), previous); }

void GfEvtModelEnemy::StateEndBattle::onLeave(void *owner, ai::State *next) { leave(static_cast<GfEvtModelEnemy *>(owner), next); }

void GfEvtModelEnemy::StateEndBattle::onStep(void *owner, const void *param) { update(static_cast<GfEvtModelEnemy *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

void GfEvtModelEnemy::StateEndBattle::leave(GfEvtModelEnemy *model, ai::State *next) { model->setWeaponFieldMount(); }

void GfEvtModelEnemy::StateEndBattle::enter(GfEvtModelEnemy *model, ai::State *previous) {
  if (GfMountManager::getMountType(model->unknown20, GFATTACH_WEAPON) != OPTMNT_WIRE) {
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, model->unknown20, false, true);
    GfGameUtil::makeCommandBattle(command, false);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattle(state, model->unknown20, false);
    unknown009(model->unknown20, command.c_str(), state.c_str());
    unknown010(model->unknown20, weaponCommand.c_str());
  }
}

void GfEvtModelEnemy::StateEndBattle::update(GfEvtModelEnemy *model, const fw::UpdateInfo &info) {
  if (model->isAnimEnd()) {
    unknown011(model->unknown20, "C_idle");
    reqState(unknown012);
  }
}

} // namespace gf
