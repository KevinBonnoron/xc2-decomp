#include "gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"

#include <math.h>

#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

void TaskFieldCheckWarp::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 33 as in the original file: it is the line argument of the assert.
#line 33
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  }
}

void TaskFieldCheckWarp::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (event.unknown04) {
    unknown38 = 0.0f;
  }
}

bool TaskFieldCheckWarp::testCondition(const BlackBoardField &blackBoard) {
  bool isBusy = blackBoard.unknown200.test(6) || blackBoard.unknown200.test(7) || blackBoard.unknown200.test(8) || blackBoard.unknown200.test(9);
  if (blackBoard.unknown08->unknown310.unknown11_2) {
    isBusy = true;
  }
  if (isBusy) {
    return false;
  }
  return !blackBoard.unknown08->unknown111_3;
}

void TaskFieldCheckWarp::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  const WarpParam *param = property->unknown006();
  if (blackBoard.unknown200.test(0)) {
    unknown38 += blackBoard.unknown18->unknown04;
  } else {
    unknown38 = 0.0f;
  }

  if (!blackBoard.unknown200.test(4)) {
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    GfObjProperty *mainProperty = GfObjUtil::getProperty(formation->unknown1a0[formation->unknown1a0[property->unknown38].unknown00].unknown08);
    if (mainProperty->unknown18 != nullptr) {
      if (mainProperty->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_1 || mainProperty->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_5) {
        return;
      }
      if (mainProperty->unknown18->unknown80) {
        return;
      }
    }
    fw::Transform transform = formation->getFollowTransform(property->unknown38);
    transform.unknown00 = formation->unknown80[property->unknown38];
    if (unknown38 >= param->stackTime || fabsf(transform.unknown00.y - property->unknown160.unknown00.y) >= param->distanceVert) {
      property->unknown003(transform, 0);
    } else {
      mm::Vec3 diff = transform.unknown00 - property->unknown160.unknown00;
      diff.y = 0.0f;
      if (sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) >= param->distanceHorz) {
        property->unknown003(transform, 0);
      }
    }
  } else {
    if (property->unknown38 & 1) {
      return;
    }
    const WallAiParam *wallParam = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
    fw::Transform transform;
    if (!AgentUtilField::getWallFollowTransform(blackBoard, &transform)) {
      return;
    }
    mm::Vec3 push;
    if (AgentUtilField::calcParentPlayerPush(*property, transform.unknown00, wallParam->escapeRange, &push)) {
      return;
    }
    mm::Vec3 diff = transform.unknown00 - property->unknown160.unknown00;
    if (fabsf(diff.y) >= param->distanceVertWall) {
      property->unknown003(transform, 1);
    } else {
      diff.y = 0.0f;
      if (sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) >= param->distanceHorzWall) {
        property->unknown003(transform, 1);
      }
    }
  }
}

void TaskFieldCheckWarpBattleWaterDead::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 191 as in the original file: it is the line argument of the assert.
#line 191
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  case ai::UNKNOWN002_UNKNOWN_2:
    onCreate(*pBB, static_cast<const ai::CreateEvent &>(event));
    break;
  }
}

void TaskFieldCheckWarpBattleWaterDead::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (event.unknown04) {
    unknown38 = 0.0f;
  }
}

void TaskFieldCheckWarpBattleWaterDead::onCreate(BlackBoardField &blackBoard, const ai::CreateEvent &event) {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->unknown408[10];
  if (paramList.get() != nullptr) {
    unknown40.unknown00 = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
  }
}

bool TaskFieldCheckWarpBattleWaterDead::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown08->unknown310.unknown11_7 && blackBoard.unknown08->unknown111_3; }

bool TaskFieldCheckWarpFallDead::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown08->unknown111_3; }

void TaskFieldCheckWarpFallDead::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  GfObjProperty *mainProperty = GfObjUtil::getProperty(formation->unknown1a0[formation->unknown1a0[property->unknown38].unknown00].unknown08);
  if (mainProperty->unknown18 == nullptr || mainProperty->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_0) {
    fw::Transform transform = formation->getFollowTransform(property->unknown38);
    transform.unknown00 = formation->unknown80[property->unknown38];
    property->unknown003(transform, 3);
  }
}

} // namespace pc
} // namespace gf
