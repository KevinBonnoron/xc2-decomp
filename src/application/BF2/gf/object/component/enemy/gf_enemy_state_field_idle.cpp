#include "gf/object/component/enemy/gf_enemy_state_field_idle.h"

#include "ai/ai_state.h"
#include "bdat.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace enemy {

// Inferred role: state of the idle family with its asm command or bdat column; original name unknown.
struct unknown001 {
  STATE_ID unknown00;
  const char *unknown08;
};

// Inferred role: asm command that starts each idle state (0x710119bc30); original name unknown.
static const unknown001 unknown002[5] = {
    {STATE_ID_UNKNOWN_1, "C_idle"}, {STATE_ID_UNKNOWN_2, "C_uniqueA"}, {STATE_ID_UNKNOWN_3, "C_uniqueB"}, {STATE_ID_UNKNOWN_4, "C_specialA_00"}, {STATE_ID_UNKNOWN_5, "C_specialB_00"}};

// Inferred role: bdat column of the idle time of each idle state (0x710119bc80); original name unknown.
static const unknown001 unknown003[5] = {
    {STATE_ID_UNKNOWN_1, "IDL_Time"}, {STATE_ID_UNKNOWN_2, nullptr}, {STATE_ID_UNKNOWN_3, nullptr}, {STATE_ID_UNKNOWN_4, "ExIDL1_Time"}, {STATE_ID_UNKNOWN_5, "ExIDL2_Time"}};

void StateFieldIdle::enter(GfComBehaviorEnemy *behavior, ai::State *previous) {
  behavior->m_behaviorEnemyField.applyFieldMoveSpeed(GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1, *behavior);
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    comAsm->execCmd("C_walkend", ANIM_LAYER_UNKNOWN_0);
  }

  u32 state = m_state;
  mm::mtl::FixStr<32> command;
  if (previous == nullptr) {
    if (comAsm != nullptr && comAsm->getStateName(ANIM_LAYER_UNKNOWN_0) != nullptr) {
      command = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
      command[0] = 'C';
    } else {
      command = "C_idle";
    }
  } else {
    u32 previousState = previous->m_state; // Places the load before the clear of the command (0x710050eb20).
    command.clear();                       // The game clears the command again here (0x710050eb24).
    // The game tests the states 4 and 5 with one comparison (0x710050eb2c); `!= 4 && != 5` gives `and #0xfffffffe; cmp #4`.
    if ((previousState | 1) != STATE_ID_UNKNOWN_5) {
      for (u32 i = 0; i < 5; i++) {
        if (state == unknown002[i].unknown00) {
          command = unknown002[i].unknown08;
          break;
        }
      }
    }
  }

  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
  if (setup->unknowna8 > 0) {
    unknown5c = -1.0f;
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_ENACT_MOVE);
    int index = setup->unknowna8; // Places the load before the search of the column (0x710050ecec).
    const char *column = nullptr;
    for (u32 i = 0; i < 5; i++) {
      if (state == unknown003[i].unknown00) {
        column = unknown003[i].unknown08;
        break;
      }
    }
    if (column != nullptr) {
      unknown5c = static_cast<f32>(static_cast<u8>(Bdat::getValCheck(bdat, column, index, 1)));
    }
  } else {
    unknown5c = 0.0f;
  }

  if (!command.empty()) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, command.c_str()));
  }

  behavior->m_behaviorEnemyField.applyFieldMoveSpeed(GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_0, *behavior);
  unknown58 = 0.0f;
  bool isFlyInsect = behavior->isFlyInsect();
  unknown18 = isFlyInsect ? 2 : 1;
  unknown60 = (state == STATE_ID_UNKNOWN_1 && isFlyInsect) ? &StateFieldIdle::seqFlyInsectIdle : &StateFieldIdle::seqOthersIdle;
}

void StateFieldIdle::leave(GfComBehaviorEnemy *behavior, ai::State *next) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    if (m_state == STATE_ID_UNKNOWN_4) {
      comAsm->execCmd("C_specialA_02", ANIM_LAYER_UNKNOWN_0);
    } else if (m_state == STATE_ID_UNKNOWN_5) {
      comAsm->execCmd("C_specialB_02", ANIM_LAYER_UNKNOWN_0);
    }
  }
}

void StateFieldIdle::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown00 == unknown020 || unknown20.unknown08.empty() || unknown20.unknown34) {
    if (unknown20.unknown35 && unknown5c < 0.0f) {
      GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
        if (stateName != nullptr) {
          comAsm->getPlaybackTime(stateName, &unknown5c);
        }
      }
    }

    unknown58 = info.unknown04 + unknown58;
    if ((unknown5c != 0.0f && unknown5c <= unknown58) || (behavior->unknown54e2 && m_state != STATE_ID_UNKNOWN_1)) {
      if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_14)) {
        reqState(STATE_ID_UNKNOWN_14);
      } else {
        GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8)->unknown30);
        if (!setup->unknownb2) {
          enemy::STATE_ID next = behavior->getNextFieldStateId();
          if (behavior->isStateCondMatch(next)) {
            reqState(next);
          }
        }
      }
    }

    if (unknown60) {
      (this->*unknown60)(*behavior, info);
    }
  }
}

void StateFieldIdle::seqFlyInsectIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (unknown20.unknown35) {
    mm::Vec3 position = behavior.getTransform().unknown00;
    GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8)->unknown30);
    position.y = setup->unknown20.y + ml::mtRandf1(-1.0f, 1.0f) * 3.0f;
    behavior.m_behaviorEnemyField.unknownc0 = position;
  }

  if (unknown20.unknown34) {
    behavior.unknown003(info.unknown04);
  }

  if (behavior.m_behaviorEnemyField.isArrivedToGoal()) {
    unknown58 = unknown5c;
  }
}

void StateFieldIdle::seqOthersIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (unknown20.unknown35) {
    behavior.m_behaviorEnemyField.unknownc0 = behavior.getTransform().unknown00;
  }
}

} // namespace enemy
} // namespace gf
