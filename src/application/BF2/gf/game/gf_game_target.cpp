// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/game/gf_game_target.cpp.
#include "gf/game/gf_game_target.h"

#include <math.h>

#include "battle/battle_global.h"
#include "battle/ui_manager_battle.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reference_frame.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_inside_battle_lock.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_message.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/game/gf_game_visible.h"
#include "gf/gf_allocator.h"
#include "gf/gf_state.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/vector.h"

namespace gf {

constexpr u32 ACCESS_TYPE_UNKNOWN_4 = 4; // Inferred role: access type water hole; original name unknown.

static bool unknown004; // Inferred role: display target mode flag; original variable name unknown.

// gf::mergeObjList (0x7100344418) merges two lists sorted by unknown20. `useFirst` is a flag that reproduces the game's block shape (P2): it leads both ways
// into one shared push of each list, so the game's `b.pl` after the compare jumps straight to the push of the first list. A nested loop with the test after it
// (188 instructions) sends that exit through the `first.end() == firstIt` test, and writing the three cases as separate pushes (189) keeps two copies of the
// push of the first list and makes the register allocator copy `first` before it spills it. The end() written on the left is needed (with it on the right:
// 188 instructions, another jump threading).
void mergeObjList(const mm::mtl::FixedList<GfSearchInfo *, 256> &first, const mm::mtl::FixedList<GfSearchInfo *, 256> &second, mm::mtl::FixedList<GfSearchInfo *, 256> *merged) {
  mm::mtl::FixedList<GfSearchInfo *, 256>::const_iterator secondIt = second.begin();
  mm::mtl::FixedList<GfSearchInfo *, 256>::const_iterator firstIt = first.begin();
  while (true) {
    bool useFirst;
    if (secondIt == second.end()) {
      if (firstIt == first.end()) {
        return;
      }
      useFirst = true;
    } else if (first.end() == firstIt) {
      useFirst = false;
    } else {
      useFirst = !((*secondIt)->unknown20 < (*firstIt)->unknown20);
    }
    if (useFirst) {
      merged->push_back(*firstIt);
      ++firstIt;
    } else {
      merged->push_back(*secondIt);
      ++secondIt;
    }
  }
}

bool isEnableTarget(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr || (GfGameInsideBattleLock::get()->unknown20 && !GfGameInsideBattleLock::isInside(handle))) {
    return false;
  }
  u32 attribute = obj->unknown110 & 4;
  bool isVisible = GfGameVisible::isVisible(handle);
  bool isLocked = GfGameTarget::testLockTarget();
  return attribute != 0 && (isVisible || isLocked);
}

bool isEnableTargetBattle(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr || (GfGameInsideBattleLock::get()->unknown20 && !GfGameInsideBattleLock::isInside(handle))) {
    return false;
  }
  return (obj->unknown110 & 4) != 0;
}

bool disableTarget(GF_OBJ_HANDLE *handle) {
  GfObjUtil::getObj(handle);
  if (GfGameObj::isDestroyGameObj(handle)) {
    return true;
  }
  return !isEnableTarget(handle);
}

bool disableTargetBattle(GF_OBJ_HANDLE *handle) {
  GfGameTarget *target = GfGameTarget::get();
  bool isUnlocked = target == nullptr || !target->unknownc1;
  GfObj *obj = GfObjUtil::getObj(handle);
  bool isDisabled = obj == nullptr || (obj->unknown110 & 4) == 0;
  return isUnlocked & (isDisabled | GfGameObj::isDestroyGameObj(handle));
}

class GfGameTarget::StateDriverNotActive : public ai::State {
  GF_STATE_CLASS(StateDriverNotActive, GfGameTarget)
  void enter(GfGameTarget *target, ai::State *) {
    target->destroySearchObj();
    target->unknownb0 = unknown020;
  }
  void leave(GfGameTarget *target, ai::State *next) {
    if (next != nullptr) {
      target->createSearchObj();
    }
  }
  void update(GfGameTarget *target, const fw::UpdateInfo &) {
    if (GfGameManager::isEnableFieldBattleTarget()) {
      GF_OBJ_HANDLE *mover = GfGameManager::getControlMover();
      GfObj *obj = GfObjUtil::getObj(mover);
      if (obj != nullptr && obj->getComponent<GfComTransform>() != nullptr) {
        target->unknownb0 = mover;
        reqState(STATE_UNKNOWN_1);
      }
    }
  }
};

class GfGameTarget::StateAutoTarget : public ai::State {
  GF_STATE_CLASS(StateAutoTarget, GfGameTarget)
  void enter(GfGameTarget *target, ai::State *) {
    GfGameSearchObj::setEnable(target->unknowna8, true);
    if (!target->setTargetNearest(*GfGameSearchObj::getObj(target->unknowna8))) {
      target->resetTarget();
    }
  }
  void leave(GfGameTarget *target, ai::State *) {
    GfGameSearchObj::setEnable(target->unknowna8, false);
    target->resetTarget();
  }
  void update(GfGameTarget *target, const fw::UpdateInfo &info);
};

class GfGameTarget::StateEnemyTarget : public ai::State {
  GF_STATE_CLASS(StateEnemyTarget, GfGameTarget)
  void enter(GfGameTarget *target, ai::State *) {
    if (target->unknownb8 == unknown020) {
      mm::mtl::FixedList<GfSearchInfo *, 256> *list = GfGameSearchObj::getObj(target->unknowna0);
      if (!target->setTargetNearestEnemyBattle(*list)) {
        target->setTargetNearestEnemy(*list);
      }
    }
  }
  void leave(GfGameTarget *, ai::State *) {}
  void update(GfGameTarget *target, const fw::UpdateInfo &info);
};

class GfGameTarget::StateBattleTarget : public ai::State {
  GF_STATE_CLASS(StateBattleTarget, GfGameTarget)
  void enter(GfGameTarget *target, ai::State *) {
    if (target->unknownb8 == unknown020) {
      mm::mtl::FixedList<GfSearchInfo *, 256> *list = GfGameSearchObj::getObj(target->unknowna0);
      if (!target->setTargetNearestEnemyBattle(*list)) {
        target->setTargetNearestEnemy(*list);
      }
    }
    target->unknownc1 = false;
  }
  void leave(GfGameTarget *target, ai::State *) {
    target->resetTarget();
    target->unknownc1 = false;
  }
  void update(GfGameTarget *target, const fw::UpdateInfo &info);
};

void GfGameTarget::Param::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 40
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 41
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("nearRadius", offsetof(Param, nearRadius), 0.0f, 10000.0f, 3.0f));
#line 42
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("nearAngle", offsetof(Param, nearAngle), 0.0f, 180.0f, 90.0f));
#line 43
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeTime", offsetof(Param, fadeTime), 0.0f, 10.0f, 1.0f));
#line 44
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("resetKeyTime", offsetof(Param, resetKeyTime), 0.0f, 10.0f, 0.5f));
  reflection->setReflectionStruct(index, value);
}

fw::Reflection *GfGameTarget::createReflection() {
#line 61
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  Param::createReflection(reflection, "target", 0);
  return reflection;
}

bool GfGameTarget::testLockTarget() {
  GfGameTarget *target = get();
  if (target != nullptr) {
    return target->unknownc1;
  }
  return false;
}

void GfGameTarget::build(const GfSetupParam &param) {
#line 420
  GfGameTarget *target = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameTarget();
  target->setup(param);
}

void GfGameTarget::setup(const GfSetupParam &) {
  unknown110 = fw::ParamManager::get()->unknown408[0];
  m_fsm.beginSetup(this, 4);
  m_fsm.registerState<StateDriverNotActive>(STATE_UNKNOWN_0);
  m_fsm.registerState<StateAutoTarget>(STATE_UNKNOWN_1);
  m_fsm.registerState<StateEnemyTarget>(STATE_UNKNOWN_2);
  m_fsm.registerState<StateBattleTarget>(STATE_UNKNOWN_3);
  m_fsm.endSetup();
  m_fsm.setState(STATE_UNKNOWN_0);
  m_padRelay.bind(0, 3, getAllocator(ALLOCATOR_UNKNOWN_0));
  m_padRelay.bindAction("change_mode", this, &GfGameTarget::changeMode);
  m_padRelay.bindAction("select_right", this, &GfGameTarget::selectRight);
  m_padRelay.bindAction("select_left", this, &GfGameTarget::selectLeft);
  m_padRelay.bindAction("close_target_on", this, &GfGameTarget::startNearTarget);
  m_padRelay.bindAction("close_target_off", this, &GfGameTarget::judgeNearTarget);
  GfEvent::addEventCallback(this);
}

void GfGameTarget::destroy() {
  GfGameTarget *target = get();
  target->cleanup();
  delete target;
}

void GfGameTarget::cleanup() {
  GfEvent::removeEventCallback(this);
  m_padRelay.unbind();
  m_fsm.cleanup();
  destroySearchObj();
  unknown110 = nullptr;
}

void GfGameTarget::update(const fw::UpdateInfo &info) { get()->updateImpl(info); }

void GfGameTarget::updateImpl(const fw::UpdateInfo &info) {
  if (unknowncc) {
    unknownd0 += info.unknown04;
    const Param *resetParam = unknown003();
    if (unknownd0 >= resetParam->resetKeyTime) {
      btl::BattleGlobal::get()->NotifyShiftTimeOver();
    }
  }
  unknownc8 = false;
  unknownc9 = false;
  unknownca = false;
  unknowncb = false;
  m_padRelay.update();
  if (!GfGameManager::isEnableFieldBattleTarget() && unknown002(m_fsm)) {
    resetTarget();
    notifyTarget();
    m_fsm.setState(STATE_UNKNOWN_0);
  }
  const Param *param = getParam();
  if (unknownc2) {
    unknownc4 += info.unknown04;
    if (unknownc4 >= param->fadeTime) {
      resetTarget();
    }
  }
  m_fsm.update(&info);
  notifyTarget();
}

bool GfGameTarget::testActive() { return unknown002(get()->m_fsm); }

GfGameTarget::GfGameTarget()
    : m_fsm(getAllocator(ALLOCATOR_UNKNOWN_0)), unknowna0(unknown012), unknowna8(unknown012), unknownb0(unknown020), unknownb8(unknown020), unknownc0(false), unknownc1(false), unknownc2(false),
      unknownc4(0.0f), unknownc8(false), unknownc9(false), unknownca(false), unknowncb(false), unknowncc(false), unknownd0(0.0f) {}

GfGameTarget::~GfGameTarget() {}

void GfGameTarget::changeMode() {
  if (!btl::UIManager::get()->unknown44_7) {
    unknownc8 = true;
    unknowncc = false;
  }
}

void GfGameTarget::selectRight() {
  btl::UIManager *ui = btl::UIManager::get();
  if (ui->unknown44_7 && (!btl::BattleGlobal::get()->unknown65e1_6 || testLockTarget())) {
    return;
  }
  unknownc9 = true;
  unknowncc = false;
  ui->NotifyInput(btl::UIManager::INPUT_TYPE_REVERSE_PALETTE_2, 0);
}

void GfGameTarget::selectLeft() {
  btl::UIManager *ui = btl::UIManager::get();
  if (ui->unknown44_7 && (!btl::BattleGlobal::get()->unknown65e1_6 || testLockTarget())) {
    return;
  }
  unknowncc = false;
  unknownca = true;
  ui->NotifyInput(btl::UIManager::INPUT_TYPE_REVERSE_PALETTE_1, 0);
}

void GfGameTarget::startNearTarget() {
  if (!unknownc8) {
    unknownd0 = 0.0f;
    unknowncc = true;
  }
}

void GfGameTarget::judgeNearTarget() {
  if (unknowncc) {
    const Param *resetParam = unknown003();
    if (unknownd0 < resetParam->resetKeyTime) {
      unknowncb = true;
    }
    unknowncc = false;
  }
  btl::BattleGlobal::get()->NotifyShiftNone();
}

void GfGameTarget::destroySearchObj() {
  if (unknowna0 != unknown012) {
    GfGameSearchObj::destroyObj(unknowna0);
    unknowna0 = unknown012;
  }
  if (unknowna8 != unknown012) {
    GfGameSearchObj::destroyObj(unknowna8);
    unknowna8 = unknown012;
  }
}

const GfGameTarget::Param *GfGameTarget::getParam() const {
  const fw::ParamList *list = unknown110.operator->();
  if (list->unknown0c == 0 || list->unknown10 == nullptr) {
    return nullptr;
  }

  return static_cast<const Param *>(list->unknown10[0].param);
}

void GfGameTarget::resetTarget() { unknown001(unknown020); }

void GfGameTarget::notifyTarget() {
  if (unknownc0) {
    GfObj *obj = GfObjUtil::getObj(unknownb0);
    if (obj != nullptr) {
      MsgGameChangeTarget message(unknownb8);
      sendMessage(obj, message);
    }
    GfGamePlayerCamera::setTargetObject(unknownb8);
    SCOM_TARGET_UI::create(unknownb8);
    obj = GfObjUtil::getObj(unknownb8);
    if (obj != nullptr && GfObjUtil::getObjType(unknownb8) == OBJECT_TYPE_ENEMY) {
      MsgFxRimBloomTarget message;
      sendMessage(obj, message);
    }
    unknownc0 = false;
  }
}

void GfGameTarget::createSearchObj() {
  const Param *param = getParam();
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
  GfObj *obj = GfObjUtil::getObj(unknownb0);
  if (obj != nullptr) {
    frame = obj->getComponent<GfComTransform>()->unknown001();
  }
  {
    GfSearchParam searchParam(1 << OBJECT_TYPE_ENEMY);
    // Decision 2026-11-14 #13: the same statement as in the second block (the constructor stored it already; the game's two stp at 0x71003457cc, then 0x71003457d0 swap without it), repeated as the
    // source pattern repeats.
    searchParam.unknown40 = unknown020;
    searchParam.unknown48 = frame;
    unknowna0 = GfGameSearchObj::createObj(searchParam);
  }
  {
    GfSearchParam searchParam((1 << OBJECT_TYPE_NPC) | (1 << OBJECT_TYPE_GIMMICK));
    f32 radius = param->nearRadius;
    searchParam.unknown00 = 1;
    searchParam.unknown3c = radius;
    // The game stores the searching object again after the constructor (str x24, [sp, #64] twice in this block).
    searchParam.unknown40 = unknown020;
    searchParam.unknown60 = unknownb0;
    searchParam.unknown48 = frame;
    unknowna8 = GfGameSearchObj::createObj(searchParam);
  }
}

void GfGameTarget::setTarget(GF_OBJ_HANDLE *handle) {
  if (unknownb8 != handle) {
    unknownb8 = handle;
    unknownc2 = false;
    unknownc0 = true;
  }
}

void GfGameTarget::updateTarget(const mm::mtl::FixedList<GfSearchInfo *, 256> &list) {
  GfSearchInfo *info = selectTarget(list);
  if (info == nullptr || !info->unknown2c_0) {
    fadeOutTarget();
  }
}

void GfGameTarget::fadeOutTarget() {
  if (unknownb8 != unknown020 && !unknownc2) {
    unknownc2 = true;
    unknownc4 = 0.0f;
  }
}

bool GfGameTarget::setTargetNearest(const mm::mtl::FixedList<GfSearchInfo *, 256> &list) {
  const Param *param = getParam();
  bool isSwim = isSwimPlayer();
  for (mm::mtl::FixedList<GfSearchInfo *, 256>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfSearchInfo *info = *it;
    if (!isEnableTarget(info->m_GF_OBJ_HANDLE) || !info->unknown2c_0) {
      continue;
    }
    if (GfObjUtil::getObjType(info->m_GF_OBJ_HANDLE) != OBJECT_TYPE_ENEMY && fabsf(info->unknown24) > param->nearAngle) {
      continue;
    }
    if (isSwim && !isWaterHole(info->m_GF_OBJ_HANDLE)) {
      continue;
    }
    unknown001(info->m_GF_OBJ_HANDLE);
    return true;
  }
  return false;
}

// The game (0x71003464f4) computes `isSwim & isMove` (and w0, w9, w8 at 0x7100346528) and sets w9 (isSwim, cset at 0x7100346518)
// only on the path where the move exists; the two null paths leave w9 unset, as `bool isSwim;` assigned in the branch does. The
// conjunction written as `property != nullptr && property->unknown18 != nullptr && ...` gives 15 instructions against the game's 16.
bool GfGameTarget::isSwimPlayer() const {
  GfObjProperty *property = GfObjUtil::getProperty(GfGameManager::getControlMover());
  bool isSwim;
  bool isMove = false;
  if (property != nullptr && property->unknown18 != nullptr) {
    isSwim = property->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_2;
    isMove = true;
  }
  return isSwim && isMove;
}

bool GfGameTarget::isWaterHole(GF_OBJ_HANDLE *handle) {
  MsgPcFieldGetAccessType message;
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    sendMessage(obj, message);
    return message.unknown08 == ACCESS_TYPE_UNKNOWN_4;
  }
  return false;
}

bool GfGameTarget::setTargetNearestEnemy(const mm::mtl::FixedList<GfSearchInfo *, 256> &list) {
  GfSearchInfo *hidden = nullptr;
  for (mm::mtl::FixedList<GfSearchInfo *, 256>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfSearchInfo *info = *it;
    if (isEnableTarget(info->m_GF_OBJ_HANDLE)) {
      if (GfGameVisible::isVisible(info->m_GF_OBJ_HANDLE)) {
        unknown001(info->m_GF_OBJ_HANDLE);
        return true;
      }
      if (hidden == nullptr) {
        hidden = info;
      }
    }
  }
  if (hidden != nullptr) {
    unknown001(hidden->m_GF_OBJ_HANDLE);
    return true;
  }
  resetTarget();
  return false;
}

bool GfGameTarget::setTargetNearestEnemyBattle(const mm::mtl::FixedList<GfSearchInfo *, 256> &list) {
  GF_OBJ_HANDLE *hidden = unknown020;
  for (mm::mtl::FixedList<GfSearchInfo *, 256>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfSearchInfo *info = *it;
    if (isEnableTargetBattle(info->m_GF_OBJ_HANDLE) && GfObjUtil::isBattle(info->m_GF_OBJ_HANDLE)) {
      if (GfGameVisible::isVisible(info->m_GF_OBJ_HANDLE)) {
        unknown001(info->m_GF_OBJ_HANDLE);
        return true;
      }
      if (hidden == unknown020) {
        hidden = info->m_GF_OBJ_HANDLE;
      }
    }
  }
  if (hidden != unknown020) {
    unknown001(hidden);
    return true;
  }
  return false;
}

void GfGameTarget::gevChangeLeader(GF_OBJ_HANDLE *) {
  if (unknown002(m_fsm)) {
    resetTarget();
    m_fsm.setState(STATE_UNKNOWN_0);
  }
}

void GfGameTarget::gevSwapFormation(u32, u32) {
  if (unknown002(m_fsm)) {
    GF_OBJ_HANDLE *mover = GfGameManager::getControlMover();
    GfObj *obj = GfObjUtil::getObj(unknownb0);
    if (obj != nullptr) {
      MsgGameChangeTarget message(unknown020);
      sendMessage(obj, message);
    }
    obj = GfObjUtil::getObj(mover);
    if (obj != nullptr) {
      MsgGameChangeTarget message(unknownb8);
      sendMessage(obj, message);
    }
    unknownb0 = mover;
    obj = GfObjUtil::getObj(mover);
    if (obj != nullptr) {
      mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = obj->getComponent<GfComTransform>()->unknown001();
      GfGameSearchObj::getInfo(unknowna0)->m_searchParam.unknown48 = frame;
      GfGameSearchObj::getInfo(unknowna8)->m_searchParam.unknown48 = frame;
    }
  }
}

void GfGameTarget::changeBattleTarget(bool isEnable) {
  bool isBattleTarget = m_fsm.getState()->m_state == STATE_UNKNOWN_3;
  if (isEnable) {
    if (!isBattleTarget) {
      m_fsm.setState(STATE_UNKNOWN_3);
    }
  } else if (isBattleTarget) {
    m_fsm.setState(STATE_UNKNOWN_1);
  }
  notifyTarget();
}

void GfGameTarget::disableTargetWithoutEnemy() {
  if (get() != nullptr) {
    GfGameSearchObj::setEnable(get()->unknowna8, false);
  }
}

void GfGameTarget::lockTarget(bool isLock) {
  if (get() != nullptr) {
    get()->unknownc1 = isLock;
  }
}

void GfGameTarget::setDispTargetMode(bool isDisp) { unknown004 = isDisp; }

bool GfGameTarget::testDispTargetMode() { return unknown004; }

bool GfGameTarget::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_GAME_UNKNOWN_16777259:
    procMsgGameChangeTarget(sender, static_cast<MsgGameChangeTarget &>(message));
    return true;
  case MSG_GAME_UNKNOWN_16777260:
    procMsgGameDebugTarget(sender, static_cast<MsgGameDebugTarget &>(message));
    return true;
  }
  return false;
}

void GfGameTarget::procMsgGameChangeTarget(fw::MessageObject *, MsgGameChangeTarget &message) {
  unknown001(message.m_GF_OBJ_HANDLE);
  notifyTarget();
}

void GfGameTarget::StateAutoTarget::update(GfGameTarget *target, const fw::UpdateInfo &) {
  // Bitwise or of the three flags in this order: the game (0x7100346e2c) loads the pair unknownca/unknowncb with one ldrh and merges
  // unknownc9 into it, without branches; `||` chains (c9, ca, cb or ca, c9, cb) and `c9 | ca | cb` do not match.
  if (target->unknownca | target->unknownc9 | target->unknowncb) {
    target->setTargetNearestEnemy(*GfGameSearchObj::getObj(target->unknowna0));
    if (target->unknownb8 != unknown020) {
      reqState(STATE_UNKNOWN_2);
      return;
    }
  }
  if (target->setTargetNearest(*GfGameSearchObj::getObj(target->unknowna8))) {
    return;
  }
  if (target->unknownb8 == unknown020) {
    return;
  }
  if (disableTarget(target->unknownb8) || (target->isSwimPlayer() && !target->isWaterHole(target->unknownb8))) {
    target->resetTarget();
  } else {
    target->fadeOutTarget();
  }
}

void GfGameTarget::StateEnemyTarget::update(GfGameTarget *target, const fw::UpdateInfo &) {
  if (!target->unknownc8) {
    mm::mtl::FixedList<GfSearchInfo *, 256> *list = GfGameSearchObj::getObj(target->unknowna0);
    if (target->unknowncb) {
      target->setTargetNearestEnemy(*list);
    }
    target->selectTarget(*list);
    if (!disableTargetBattle(target->unknownb8)) {
      return;
    }
  }
  reqState(STATE_UNKNOWN_1);
}

void GfGameTarget::StateBattleTarget::update(GfGameTarget *target, const fw::UpdateInfo &) {
  if (target->unknownc1) {
    return;
  }
  mm::mtl::FixedList<GfSearchInfo *, 256> *list = GfGameSearchObj::getObj(target->unknowna0);
  if (disableTargetBattle(target->unknownb8)) {
    target->setTargetNearestEnemyBattle(*list);
  } else if (target->unknowncb) {
    target->setTargetNearestEnemy(*list);
  }
  target->selectTarget(*list);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameTarget>::~PtrSingleton();
template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::GfGameTarget>(const mm::mtl::Delegate<void()> *);
