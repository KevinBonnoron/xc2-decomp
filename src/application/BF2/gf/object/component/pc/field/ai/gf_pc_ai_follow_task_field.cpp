#include "gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"

#include <math.h>

#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/rtti.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
namespace pc {

bool isMainPcMove(GfComPropertyPc &property) {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation->unknown1a0[property.unknown38].unknown10) {
    return property.unknown002();
  }

  u32 mainId = formation->unknown1a0[property.unknown38].unknown00;
  if (mainId != PLAYER_ID_UNKNOWN_4294967295) {
    GfObjProperty *mainProperty = GfObjUtil::getProperty(formation->unknown1a0[mainId].unknown08);
    if (mainProperty->unknown18 != nullptr) {
      return mainProperty->unknown18->unknown7f;
    }
  }

  return false;
}

bool TaskFieldFollowTarget::testCondition(const BlackBoardField &blackBoard) {
  const navi::NvmshAcObj *naviObject = blackBoard.unknown10;
  bool isWarp = blackBoard.unknown200.test(6) || blackBoard.unknown200.test(7) || blackBoard.unknown200.test(8) || blackBoard.unknown200.test(9);
  return (naviObject->unknown10 & 2) != 0 && !isWarp;
}

void TaskFieldFollowTarget::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  navi::NvmshAcObj *naviObject = blackBoard.unknown10;
  naviObject->setBeginPos(property->unknown160.unknown00);
  naviObject->setEndPos(blackBoard.unknown20);
  mm::Vec3 targetDiff(blackBoard.unknown20.x - property->unknown160.unknown00.x, 0.0f, blackBoard.unknown20.z - property->unknown160.unknown00.z);
  blackBoard.unknown30 = sqrtf(targetDiff.x * targetDiff.x + targetDiff.y * targetDiff.y + targetDiff.z * targetDiff.z);
  mm::Vec3 leaderDiff(blackBoard.unknown40.x - property->unknown160.unknown00.x, 0.0f, blackBoard.unknown40.z - property->unknown160.unknown00.z);
  blackBoard.unknown50 = sqrtf(leaderDiff.x * leaderDiff.x + leaderDiff.y * leaderDiff.y + leaderDiff.z * leaderDiff.z);
}

void TaskFieldFollowMainPc::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 117 as in the original file: it is the line argument of the assert.
#line 117
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

void TaskFieldFollowMainPc::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (!event.unknown04) {
    unknown38 = 0.0f;
  }
}

void TaskFieldFollowMainPc::onCreate(BlackBoardField &blackBoard, const ai::CreateEvent &event) {
  unknown38 = 0.0f;
  unknown3c = false;
}

bool isFollowMainPc(const BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  if (property->unknown38 == 0) {
    return true;
  }

  const FollowMainPcParam *param = AgentUtilField::getAIParamAdapter(*property, property->unknown114 == 3 ? PARAM_ID_FIELD_AI_UNKNOWN_1 : PARAM_ID_FIELD_AI_UNKNOWN_0).get<FollowMainPcParam>();
  if (blackBoard.unknown50 > param->followDist) {
    return true;
  }

  if (GfGameParty::isBtlLeaderDirver()) {
    return true;
  }

  if (blackBoard.unknown30 > param->stopDist) {
    return isMainPcMove(*property);
  }

  return false;
}

bool TaskFieldFollowMainPc::testCondition(const BlackBoardField &blackBoard) {
  bool isFollow = isFollowMainPc(blackBoard);
  if (isFollow) {
    unknown38 = 0.0f;
    unknown3c = true;
  } else if (unknown3c) {
    unknown38 += blackBoard.unknown18->unknown04;
  } else {
    unknown38 = 0.0f;
  }

  const FollowMainPcParam *param =
      AgentUtilField::getAIParamAdapter(*blackBoard.unknown08, blackBoard.unknown08->unknown114 == 3 ? PARAM_ID_FIELD_AI_UNKNOWN_1 : PARAM_ID_FIELD_AI_UNKNOWN_0).get<FollowMainPcParam>();
  if (unknown38 >= param->adjustTime && unknown3c) {
    isFollow |= blackBoard.unknown30 >= param->adjustDist;
    unknown3c = false;
  }

  return isFollow;
}

void TaskFieldFollowMainPc::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  navi::NvmshAcObj *naviObject = blackBoard.unknown10;
  const FollowMainPcParam *param = AgentUtilField::getAIParamAdapter(*property, property->unknown114 == 3 ? PARAM_ID_FIELD_AI_UNKNOWN_1 : PARAM_ID_FIELD_AI_UNKNOWN_0).get<FollowMainPcParam>();
  if (!blackBoard.unknown200.test(10) && blackBoard.unknown50 < param->walkDistStopFollower) {
    property->setInputDirPow(naviObject->getMoveVec(), 0.1f);
  } else {
    AgentUtilField::setFollowInput(blackBoard.unknown30, naviObject, *property);
  }
  blackBoard.unknown200.set(3);
}

bool isBuddyPcMove(GfComPropertyPc &property) {
  if (property.unknown94 < 0.0f || property.unknown94 > 0.0f) {
    return true;
  }

  return property.unknown002();
}

bool isFollowBuddyPc(const BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  GfObjProperty *mainProperty = GfObjUtil::getProperty(formation->unknown1a0[formation->unknown1a0[property->unknown38].unknown00].unknown08);
  if (mainProperty->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_3) {
    return false;
  }

  const FollowBuddyPcParam *param = AgentUtilField::getAIParamAdapter(*property, property->unknown114 == 3 ? PARAM_ID_FIELD_AI_UNKNOWN_3 : PARAM_ID_FIELD_AI_UNKNOWN_2).get<FollowBuddyPcParam>();
  if (blackBoard.unknown30 > param->stopDist && isBuddyPcMove(*property)) {
    return true;
  }

  return isMainPcMove(*property);
}

bool TaskFieldFollowBuddyPc::testCondition(const BlackBoardField &blackBoard) { return isFollowBuddyPc(blackBoard); }

void TaskFieldFollowBuddyPc::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  navi::NvmshAcObj *naviObject = blackBoard.unknown10;
  const FollowBuddyPcParam *param = AgentUtilField::getAIParamAdapter(*property, property->unknown114 == 3 ? PARAM_ID_FIELD_AI_UNKNOWN_3 : PARAM_ID_FIELD_AI_UNKNOWN_2).get<FollowBuddyPcParam>();
  if (!blackBoard.unknown200.test(10) && blackBoard.unknown50 < param->walkDistStopFollower) {
    property->setInputDirPow(naviObject->getMoveVec(), 0.1f);
  } else {
    AgentUtilField::setFollowInput(blackBoard.unknown30, naviObject, *property);
  }
  blackBoard.unknown200.set(3);
}

} // namespace pc
} // namespace gf
