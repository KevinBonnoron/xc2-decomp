#pragma once
#include <new> // IWYU pragma: keep

#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai

namespace gf {

class GfComAsm;

namespace npc {

template <typename T> class StateReaction : public GfStateBase {
public:
  StateReaction() : unknown18(), unknown50(nullptr), unknown60(mm::Quat::identity), unknown70(0) {}
  static ai::State *create(void *buffer) { return new (buffer) StateReaction; }
  const char *getName() const override { return "StateReaction"; }
  void onEnter(void *owner, ai::State *previous) override;
  void onLeave(void *owner, ai::State *next) override;
  void onStep(void *owner, const void *param) override;
  void seqTurnToPc(T &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnToPcEnd(T &behavior, const fw::UpdateInfo &info);
  void beginReaction(const T &behavior);
  void seqUpdateMove(T &behavior, const fw::UpdateInfo &info);
  void endReaction(const T &behavior);
  void seqTurnToPrev(T &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnToPrevEnd(T &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                             // Inferred role: asm command; original member name unknown.
  void (StateReaction::*unknown50)(T &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  mm::Quat unknown60;                                            // Inferred role: rotation of the object before the reaction; original member name unknown.
  u32 unknown70;                                                 // Role and original member name unknown.
};

template <typename T> void StateReaction<T>::onEnter(void *owner, ai::State *previous) {
  unknown70 = 0;
  unknown50 = &StateReaction::seqTurnToPc;
}

template <typename T> void StateReaction<T>::onLeave(void *owner, ai::State *next) { static_cast<T *>(owner)->unknown003() = unknown60; }

template <typename T> void StateReaction<T>::onStep(void *owner, const void *param) {
  unknown18.update(static_cast<const fw::UpdateInfo *>(param)->unknown04);
  if (unknown50) {
    (this->*unknown50)(*static_cast<T *>(owner), *static_cast<const fw::UpdateInfo *>(param));
  }
}

template <typename T> void StateReaction<T>::seqTurnToPc(T &behavior, const fw::UpdateInfo &info) {
  if (gmk::isPlayerExist()) {
    behavior.init(false);
    behavior.execTurnCmdToPos(gmk::getPlayerPos());
    unknown50 = &StateReaction::seqWaitTurnToPcEnd;
  }
}

template <typename T> void StateReaction<T>::seqWaitTurnToPcEnd(T &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown004().unknown6c) {
    beginReaction(behavior);
    unknown50 = &StateReaction::seqUpdateMove;
  }
}

template <typename T> void StateReaction<T>::beginReaction(const T &behavior) {
  const char *command = reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", behavior.unknown006(), gmk::BDAT_TYPE_UNKNOWN_7));
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, command));
}

template <typename T> void StateReaction<T>::seqUpdateMove(T &behavior, const fw::UpdateInfo &info) {
  if (unknown18.unknown34 && (!gmk::isPlayerExist() || !(0.0f < behavior.unknown014()) || behavior.unknown006() == 0 || behavior.unknown015() == 0 || behavior.unknown014() < behavior.unknown016() ||
                              4.0f < behavior.unknown017())) {
    endReaction(behavior);
    unknown50 = &StateReaction::seqTurnToPrev;
  }
}

template <typename T> void StateReaction<T>::endReaction(const T &behavior) {
  const char *command = reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", behavior.unknown006(), gmk::BDAT_TYPE_UNKNOWN_7));
  mm::mtl::FixStr<32> name(command);
  name[name.length() - 1] = '2';
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, name.c_str()));
}

template <typename T> void StateReaction<T>::seqTurnToPrev(T &behavior, const fw::UpdateInfo &info) {
  if (unknown18.unknown34) {
    mm::Vec3 position = mm::Vec3::zero;
    gmk::AGmkBase *gmk = behavior.getBindedGmkInst();
    if (gmk != nullptr) {
      // Single-use local that places the load of Vec3::unitZ: the game loads it before the euler angles of the gimmick (0x7100537a60: ldr s14 / ldp s15,s11 before ldr x8,[x21,#16]); with
      // quat.rotate(mm::Vec3::unitZ) written in the sum the function has 132 instructions against 135.
      mm::Vec3 front = mm::Vec3::unitZ;
      mm::Vec3 rotation = gmk->m_createBaseInfo.m_xform->unknown10;
      mm::Quat quat = mm::unknown005(rotation);
      position = gmk->m_createBaseInfo.m_xform->unknown00 + quat.rotate(front);
    }
    behavior.execTurnCmdToPos(position);
    unknown50 = &StateReaction::seqWaitTurnToPrevEnd;
  }
}

template <typename T> void StateReaction<T>::seqWaitTurnToPrevEnd(T &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown004().unknown6c) {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

} // namespace npc
} // namespace gf
