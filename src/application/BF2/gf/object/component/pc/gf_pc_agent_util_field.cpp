#include "gf/object/component/pc/gf_pc_agent_util_field.h"

#include <float.h>
#include <math.h>

#include "fw/fw_transform.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/intrusive_ptr.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
namespace pc {

template <typename T, PARAM_ID_FIELD_AI ID, PARAM_ID_FIELD_AI WATER_ID> f32 funcFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property) {
  s32 groundType = property.unknown114;
  const fw::ParamList *paramList = AgentUtilField::unknown001(property).operator->();
  const T *param = static_cast<const T *>(paramList->unknown10[groundType == 3 ? WATER_ID : ID].param);
  f32 range = fabsf(param->powMaxDist - param->powMinDist);
  f32 ratio = range > FLT_EPSILON ? (distance - param->powMinDist) / range : 0.0f;
  f32 power = mm::clamp(ratio, 0.0f, 1.0f);
  property.setInputDirPow(naviObject->getMoveVec(), power);
  return power;
}

void AgentUtilField::setIdleInput(GfComPropertyPc &property) { property.setInputDirPow(property.unknown1e0, 0.0f); }

f32 AgentUtilField::setFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property) {
  if (GfGamePlayerFormation::get()->unknown1a0[property.unknown38].unknown10) {
    return funcFollowInput<FollowMainPcParam, PARAM_ID_FIELD_AI_UNKNOWN_0, PARAM_ID_FIELD_AI_UNKNOWN_1>(distance, naviObject, property);
  }
  return funcFollowInput<FollowBuddyPcParam, PARAM_ID_FIELD_AI_UNKNOWN_2, PARAM_ID_FIELD_AI_UNKNOWN_3>(distance, naviObject, property);
}

mm::Vec2 AgentUtilField::calcFollowWallInput(const mm::Vec3 &position, GfComPropertyPc &property) {
  mm::Vec2 input = mm::Vec2::zero;
  mm::Vec3 offset = position - property.unknown160.unknown00;
  f32 up = offset.x * property.unknown1c0.x + offset.y * property.unknown1c0.y + offset.z * property.unknown1c0.z;
  if (up >= 0.0f) {
    input.y = up >= property.unknown310.unknown3c ? 1.0f : 0.0f;
  } else {
    input.y = up <= -property.unknown310.unknown40 ? -1.0f : 0.0f;
  }
  f32 side = offset.x * property.unknown200.x + offset.y * property.unknown200.y + offset.z * property.unknown200.z;
  if (side >= 0.0f) {
    input.x = side >= property.unknown310.unknown44 ? 1.0f : 0.0f;
  } else {
    input.x = side <= -property.unknown310.unknown44 ? -1.0f : 0.0f;
  }
  return input;
}

void AgentUtilField::setFollowWallEndInput(const mm::Vec3 &position, GfComPropertyPc &property) {
  mm::Vec3 offset = position - property.unknown160.unknown00;
  property.unknown60.unknown04 = offset.x * property.unknown1c0.x + offset.y * property.unknown1c0.y + offset.z * property.unknown1c0.z >= 0.0f ? 1.0f : -1.0f;
  f32 side = offset.x * property.unknown200.x + offset.y * property.unknown200.y + offset.z * property.unknown200.z;
  if (side >= 0.0f) {
    property.unknown60.unknown00 = side >= property.unknown310.unknown44 ? 1.0f : 0.0f;
  } else {
    property.unknown60.unknown00 = side <= -property.unknown310.unknown44 ? -1.0f : 0.0f;
  }
}

bool AgentUtilField::getWallFollowTransform(const BlackBoardField &blackBoard, fw::Transform *transform) {
  GfComPropertyPc *property = blackBoard.unknown08;
  fw::ParamAdapter adapter = getAIParamAdapter(*property, PARAM_ID_FIELD_AI_UNKNOWN_5);
  if (blackBoard.unknown200.test(4)) {
    u32 index = adapter.get<WallAiParam>()->delay * (property->unknown38 >> 1);
    if (blackBoard.unknowna0.size() > index) {
      *transform = blackBoard.unknowna0[index];
      return true;
    }
  }
  return false;
}

fw::ParamAdapter AgentUtilField::getAIParamAdapter(GfComPropertyPc &property, PARAM_ID_FIELD_AI id) {
  const fw::ParamList *paramList = unknown001(property).operator->();
  fw::ParamAdapter adapter;
  adapter.unknown00 = id < paramList->unknown0c ? &paramList->unknown10[id] : nullptr;
  return adapter;
}

bool AgentUtilField::isWallEndMove(const BlackBoardField &blackBoard) {
  if (blackBoard.unknown200.test(4)) {
    return false;
  }
  GfComPropertyPc *property = blackBoard.unknown08;
  const WallAiParam *param = static_cast<const WallAiParam *>(unknown001(*property)->unknown10[PARAM_ID_FIELD_AI_UNKNOWN_5].param);
  return !StateUtilField::isNearPlayer(*property, blackBoard.unknown90, param->climbEndSafeRange);
}

bool AgentUtilField::calcParentPlayerPush(GfComPropertyPc &property, const mm::Vec3 &position, f32 range, mm::Vec3 *push) {
  *push = mm::Vec3::zero;
  const EnviromentSensor::unknown003 *wallInfo = StateUtil::getClimbWallInfo(*property.unknown08->getComponent<GfComBehaviorPc>());
  if (wallInfo == nullptr) {
    return false;
  }
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  bool isPush = false;
  for (u32 i = 0; i < GfGamePlayerFormation::PLAYER_UNKNOWN_6; i++) {
    if (formation->unknown1a0[i].unknown10) {
      if (i == property.unknown38) {
        return isPush;
      }
      GfObjProperty *other = GfObjUtil::getProperty(formation->unknown1a0[i].unknown08);
      if (other != nullptr && other->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_3) {
        mm::Vec3 offset = other->unknown18->unknown10 - position;
        const mm::Vec3 &normal = wallInfo->unknown00.normal;
        f32 dot = offset.x * normal.x + offset.y * normal.y + offset.z * normal.z;
        mm::Vec3 projection(normal.x * dot, normal.y * dot, normal.z * dot);
        mm::Vec3 direction = offset - projection;
        f32 distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) - range;
        if (distance < 0.0f) {
          if (fabsf(direction.x) <= 0.000001f && fabsf(direction.y) <= 0.000001f && fabsf(direction.z) <= 0.000001f) {
            direction = mm::Vec3(-mm::Vec3::unitY.x, -mm::Vec3::unitY.y, -mm::Vec3::unitY.z);
          } else {
            direction.unknown001();
          }
          *push += direction * distance;
          isPush = true;
        }
      }
    }
  }
  return isPush;
}

bool AgentUtilField::isEnableWallMove(GfComPropertyPc &property, const mm::Vec2 &input) {
  f32 up = input.y * (input.y >= 0.0f ? property.unknown310.unknown3c : property.unknown310.unknown40);
  f32 side = input.x * property.unknown310.unknown44;
  mm::Vec3 position = property.unknown1c0 * up + property.unknown200 * side + property.unknown160.unknown00;
  const WallAiParam *param = getAIParamAdapter(property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
  mm::Vec3 push;
  return !calcParentPlayerPush(property, position, param->nearRange, &push);
}

bool AgentUtilField::existNearChimbPlayer(GfComPropertyPc &property, const mm::Vec3 &position) {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  const WallAiParam *param = getAIParamAdapter(property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
  bool isExist = false;
  for (u32 i = 0; i < GfGamePlayerFormation::PLAYER_UNKNOWN_6; i++) {
    if (formation->unknown1a0[i].unknown10) {
      GfObjProperty *other = GfObjUtil::getProperty(formation->unknown1a0[i].unknown08);
      if (other != nullptr && other->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_3) {
        mm::Vec3 offset = other->unknown18->unknown10 - position;
        isExist |= sqrtf(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z) - param->nearRange < 0.0f;
      }
    }
  }
  return isExist;
}

bool AgentUtilField::isWallJumpAnyPlayer() {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  bool isWallJump = false;
  for (u32 i = 0; i < GfGamePlayerFormation::PLAYER_UNKNOWN_6; i++) {
    if (formation->unknown1a0[i].unknown10) {
      GfObj *obj = GfObjUtil::getObj(formation->unknown1a0[i].unknown08);
      if (obj != nullptr) {
        GfComPropertyPc *property = mm::mtl::dynamicCast<GfComPropertyPc>(obj->unknown38[GfComProperty::COMPONENT_INDEX]);
        if (property->unknown310.unknown10_4) {
          isWallJump = isWallJump || property->unknown310.unknown11_2;
        }
      }
    }
  }
  return isWallJump;
}

} // namespace pc
} // namespace gf
