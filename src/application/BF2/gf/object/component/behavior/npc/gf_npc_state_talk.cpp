#include "gf/object/component/behavior/npc/gf_npc_state_talk.h"

#include <math.h>

#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_map.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
namespace npc {

// Inferred role: rows of BDAT_FLD_WILDCARD_DATA holding the talk bonus develop points of each develop level; original name unknown.
static const int unknown002[DEVELOP_LEVEL_UNKNOWN_5 + 1] = {70, 46, 47, 48, 49, 50};

enum {
  STATS_UNKNOWN_23 = 23, // Inferred role: stats talk bonus; original name unknown.
};

StateTalk::StateTalk() : unknown18(), unknown50(nullptr), unknown60(false) {}

void StateTalk::leave(GfComBehaviorNpc *behavior, ai::State *next) { setCollideNpcMob(true); }

void StateTalk::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateTalk::seqWaitTalkEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (behavior.unknown100) {
    return;
  }

  if (behavior.unknown98.isIconTalkBonus()) {
    behavior.unknown98.setTalkBonusFlag();
    u32 zone = GfGameManager::getMapZoneID();
    int row = unknown002[GfDataDevelop::getLevel(zone)];
    u32 point = Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA), 1, row, gmk::BDAT_TYPE_UNKNOWN_2).valueU16;
    if (point != 0) {
      u8 mapZone = Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_MAPLIST), "zone", GfGameManager::getMapID(), gmk::BDAT_TYPE_UNKNOWN_1);
      if (mapZone) {
        SCOM_ADD_DEVELOP::create(zone, point);
      } else {
        for (u32 nation = NATION_UNKNOWN_1; nation <= NATION_UNKNOWN_8; nation++) {
          if (GfDataMap::isArcadiaDestroy() && nation == NATION_UNKNOWN_6) {
            continue;
          }
          SCOM_ADD_DEVELOP::create(nation, point);
        }
      }
    }
    SCOM_ACHIEV_INC::addTotalCount(STATS_UNKNOWN_23, 1);
    SCOM_ACHIEV_INC::create(STATS_UNKNOWN_23, 1, 0);
  }

  if (unknown60) {
    gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
    if (gmkInst != nullptr) {
      mm::Mat44 matrix;
      gmkInst->getMatrix(matrix, true);
      behavior.execTurnCmd(atan2f(matrix.rows[2][0], matrix.rows[2][2]));
    }
    unknown50 = &StateTalk::seqWaitTurnEnd;
  } else {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

void StateTalk::setCollideNpcMob(GF_OBJ_HANDLE *handle, bool isCollide) {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComCollider *collider = obj->getComponent<GfComCollider>();
    if (collider != nullptr) {
      for (fw::ColiObject *&coli : collider->unknown18) {
        if (coli != nullptr) {
          u32 flag = coli->getHitMaterialFlag();
          if (isCollide) {
            flag |= 0x40000;
          } else {
            flag &= ~0x40000;
          }
          coli->setHitMaterialFlag(flag);
        }
      }
    }
  }
}

void StateTalk::seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c) {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

} // namespace npc
} // namespace gf
