#include "gf/object/component/behavior/npc/gf_npc_state_idle.h"

#include <string.h>

#include "ai/ai_state.h"
#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
namespace npc {

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Role: true unless the state is StateTalk (id 6) of a gimmick whose NpcTurn column, read as u8 (BDAT_TYPE_UNKNOWN_1), is 3. Single user: StateIdle::isExecEndScheduleCondMatched (1.0.0:
// 0x7100538908, 27 instructions; inlined in enter 0x7100538974 and leave 0x7100538b54), which tests the byte with `and w8, w0, #0xff; cmp w8, #3` (0x7100538950). Bdat::getValCheck
// returns 64 bits, and every form tried without the helper either widens that compare to `and x8, x0, #0xff; cmp x8, #3` (nested ifs with or without the cast, a `u8` local and
// `== 3`: 27 instructions) or gives 28 instructions (`!= 3` returns, a bool `result`, the negated chain returned directly or held in a bool local, a positive helper under any
// of four callers); no match. It matches only with the negated `&&` chain in the helper and the caller branching on it with two returns, as the game's `mov w0, wzr` / `orr w0, wzr, #1`.
static bool isNotTalkWithNpcTurn3(GfComBehaviorNpc &behavior, ai::State &state) {
  gmk::AGmkBase *gmk;
  return !(state.m_state == STATE_ID_UNKNOWN_6 && (gmk = behavior.getBindedGmkInst()) != nullptr &&
           static_cast<u8>(Bdat::getValCheck(gmk->getBindedBdatFp(), "NpcTurn", gmk->m_createInfo.unknown18, gmk::BDAT_TYPE_UNKNOWN_1)) == 3);
}

bool StateIdle::isExecEndScheduleCondMatched(GfComBehaviorNpc &behavior, ai::State *state) const {
  if (state == nullptr) {
    return false;
  }
  if (isNotTalkWithNpcTurn3(behavior, *state)) {
    return true;
  }
  return false;
}

void StateIdle::enter(GfComBehaviorNpc *behavior, ai::State *previous) {
  if (!isExecEndScheduleCondMatched(*behavior, previous)) {
    return;
  }

  execEndSchedule(*behavior);

  GfComAsm *comAsm = behavior->getComAsm();
  const char *stateName = nullptr;
  if (comAsm != nullptr) {
    stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
  }

  GfObjSetupNpc *setup = GfObjUtil::getObjSetup<GfObjSetupNpc>(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
  if (stateName == nullptr || strcmp(setup->unknown6c.c_str(), stateName) != 0) {
    mm::mtl::FixStr<32> command(setup->unknown6c);
    command.unknown002(0) = 'C';
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, command.c_str()));
  }
}

void StateIdle::leave(GfComBehaviorNpc *behavior, ai::State *next) {
  if (isExecEndScheduleCondMatched(*behavior, next)) {
    execEndSchedule(*behavior);
  }
}

void StateIdle::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  if (unknown18.unknown00 != unknown020 && !unknown18.unknown08.empty()) {
    unknown18.update(info.unknown04);
    if (!unknown18.unknown34) {
      return;
    }

    if (unknown18.unknown35) {
      behavior->init(false);
    }
  }

  int stateId = behavior->getNexStateId();
  if (stateId != -1) {
    reqState(stateId);
  }
}

} // namespace npc
} // namespace gf
