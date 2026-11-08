#pragma once
#include <new> // IWYU pragma: keep

#include "ai/ai_state.h"
#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_bdat.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComAsm;

namespace npc {

template <typename T> class StateBattle : public ai::State {
public:
  StateBattle() : unknown18(), unknown50(nullptr), unknown60(0) {}
  static ai::State *create(void *buffer) { return new (buffer) StateBattle; }
  const char *getName() const override { return "StateBattle"; }
  void onEnter(void *owner, ai::State *previous) override;
  void onLeave(void *owner, ai::State *next) override;
  void onStep(void *owner, const void *param) override;
  static bool isCondMatch(const T &behavior);
  static bool findGoalPos(mm::Vec3 &position, const T &behavior);
  void seqApplyBattleMot(T &behavior, const fw::UpdateInfo &info);
  void seqTurnPc(T &behavior, const fw::UpdateInfo &info);
  void seqUpdateBattleMot(T &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(T &behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(T &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                           // Inferred role: asm command; original member name unknown.
  void (StateBattle::*unknown50)(T &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  u32 unknown60;                                               // Role and original member name unknown.
};

template <typename T> void StateBattle<T>::onLeave(void *owner, ai::State *next) {}

template <typename T> void StateBattle<T>::onStep(void *owner, const void *param) {
  unknown18.update(static_cast<const fw::UpdateInfo *>(param)->unknown04);
  if (unknown50) {
    (this->*unknown50)(*static_cast<T *>(owner), *static_cast<const fw::UpdateInfo *>(param));
  }
}

template <typename T> void StateBattle<T>::onEnter(void *owner, ai::State *previous) {
  T &behavior = *static_cast<T *>(owner);
  behavior.init(true);
  u16 motion = behavior.unknown007();
  unknown50 = motion != 0 ? &StateBattle::seqApplyBattleMot : &StateBattle::seqTurnPc;
  if (motion != 0 && behavior.unknown008() != 2) {
    // The game calls it and drops the result, likely the argument of a debug message removed from the release build.
    behavior.getBindedGmkInst();
  }
  unknown60 = 0;
}

template <typename T> void StateBattle<T>::seqApplyBattleMot(T &behavior, const fw::UpdateInfo &info) {
  const char *command = reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", behavior.unknown007(), gmk::BDAT_TYPE_STRING));
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, command));
  unknown50 = &StateBattle::seqUpdateBattleMot;
}

template <typename T> void StateBattle<T>::seqUpdateBattleMot(T &behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isBattle()) {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

} // namespace npc
} // namespace gf
