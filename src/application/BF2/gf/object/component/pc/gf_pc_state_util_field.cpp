#include "gf/object/component/pc/gf_pc_state_util_field.h"

#include <float.h>
#include <math.h>

#include "framework/memory/framework_memory.h"
#include "framework/message/message_manager.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/game/gf_game_mover_switcher.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_ride.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/movement/gf_move_run.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

f32 calcInputDiffAngle(GfComPropertyPc &property) {
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (!(fabsf(input.x) <= 0.000001f) || !(fabsf(input.y) <= 0.000001f) || !(fabsf(input.z) <= 0.000001f)) {
    input.unknown001();
    f32 cosine = mm::clamp(input.x * property.unknown1e0.x + input.y * property.unknown1e0.y + input.z * property.unknown1e0.z, -1.0f, 1.0f);
    return mm::acos(cosine);
  }

  return 0.0f;
}

f32 calcInputDiffAngleVel(GfComPropertyPc &property) {
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (!(fabsf(input.x) <= 0.000001f) || !(fabsf(input.y) <= 0.000001f) || !(fabsf(input.z) <= 0.000001f)) {
    input.unknown001();
    mm::Vec3 direction = property.unknown80;
    if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
      direction.unknown001();
    } else {
      direction = property.unknown1e0;
    }

    f32 cosine = mm::clamp(input.x * direction.x + input.y * direction.y + input.z * direction.z, -1.0f, 1.0f);
    return mm::acos(cosine);
  }

  return 0.0f;
}

bool StateUtilField::execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id) { return comAsm.execCmd(getASMCmdNameField(id), ANIM_LAYER_UNKNOWN_0); }

bool StateUtilField::testVechile(GfComBehaviorPc &behavior) { return GfGameRide::isVehicle(static_cast<GfObj *>(behavior.unknown08)->unknownf8); }

bool StateUtilField::isWalkMode(GfComPropertyPc &property) { return property.unknown310.unknown10_0; }

bool StateUtilField::isStop(GfComPropertyPc &property, u32 noInputFrameCount) { return property.unknown310.unknown001()->stopCnt <= noInputFrameCount; }

bool StateUtilField::testAutoRun(GfComPropertyPc &property) { return property.unknown310.unknown11_0; }

bool StateUtilField::isTurnEndRange(GfComPropertyPc &property) {
  f32 angle = calcInputDiffAngle(property);
  return property.unknown310.unknown001()->turnEndAngle >= angle;
}

bool StateUtilField::isTurnRange(GfComPropertyPc &property, mm::mtl::FixedQueue<mm::Vec2, 2> &queue) {
  const FieldParam *param = property.unknown310.unknown006();
  f32 threshold = param->turnInputThreshold;
  f32 inputX = property.unknown60.unknown00 >= -threshold && property.unknown60.unknown00 <= threshold ? 0.0f : property.unknown60.unknown00;
  f32 inputY = property.unknown60.unknown04 >= -threshold && property.unknown60.unknown04 <= threshold ? 0.0f : property.unknown60.unknown04;
  mm::Vec3 direction(inputX, inputY, 0.0f);
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    direction.unknown001();
    if (queue.full()) {
      queue.pop_front();
    }
    queue.push(mm::Vec2(direction.x, direction.y));
    if (queue.size() == 2) {
      mm::Vec2 &current = queue[1];
      mm::Vec2 &previous = queue[0];
      f32 cosine = previous.x * current.x + previous.y * current.y;
      f32 angle = mm::acos(mm::clamp(cosine, -1.0f, 1.0f));
      return param->turnAngle <= angle;
    }
  }
  return false;
}

bool StateUtilField::isInputInverseDir(GfComPropertyPc &property) {
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  return input.x * property.unknown1e0.x + input.y * property.unknown1e0.y + input.z * property.unknown1e0.z < 0.0f;
}

bool StateUtilField::isTurnEndRangeCacheInput(GfComPropertyPc &property, const mm::Vec3 &direction) {
  f32 cosine = mm::clamp(direction.x * property.unknown1e0.x + direction.y * property.unknown1e0.y + direction.z * property.unknown1e0.z, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return property.unknown310.unknown001()->turnEndAngle >= angle;
}

bool StateUtilField::isSlideGroundLanding(GfComPropertyPc &property) {
  if (!property.unknown110_4) {
    return false;
  }

  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_0) {
    return false;
  }

  if (!((sensor->unknown30.unknown30 >> 5) & 1)) {
    return false;
  }

  const SlideParam *param = property.unknown004();
  const mm::Plane &plane = sensor->unknown30.unknown10;
  f32 cosine = mm::clamp(plane.normal.x * mm::Vec3::unitY.x + plane.normal.y * mm::Vec3::unitY.y + plane.normal.z * mm::Vec3::unitY.z, -1.0f, 1.0f);
  return mm::acos(cosine) * mm::RAD_TO_DEG > param->minAngle;
}

bool StateUtilField::isEndSlipPosuture(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  const SlideParam *param = property->unknown004();
  if (isSlideSlope(*property)) {
    return false;
  }

  const mm::Vec3 &direction = property->unknownd0;
  mm::Vec3 velocity = mm::Vec3::unitY * property->unknown90 + property->unknown80 + direction * property->unknownc0;
  return direction.x * velocity.x + direction.y * velocity.y + direction.z * velocity.z <= param->endVel;
}

bool StateUtilField::isStartSlidePosuture(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  const SlideParam *param = property->unknown004();
  if (!StateUtil::isOnSlideGround(behavior)) {
    return false;
  }

  if (!(property->unknownf0 >= param->startTime)) {
    const mm::Vec3 &direction = property->unknownd0;
    mm::Vec3 velocity = mm::Vec3::unitY * property->unknown90 + property->unknown80 + direction * property->unknownc0;
    if (!(direction.x * velocity.x + direction.y * velocity.y + direction.z * velocity.z >= param->startVel)) {
      return false;
    }
  }

  return true;
}

bool StateUtilField::isInputInverseDirAutoRun(GfComPropertyPc &property) {
  f32 cosine;
  if (property.unknown310.unknown10_4) {
    f32 length;
    f32 inputX = property.unknown60.unknown00;
    f32 inputY = property.unknown60.unknown04;
    if (!(fabsf(inputX) <= 0.000001f) || !(fabsf(inputY) <= 0.000001f)) {
      length = sqrtf(inputX * inputX + inputY * inputY);
      inputX = inputX * (1.0f / length);
      inputY = inputY * (1.0f / length);
    }
    f32 prevX = property.unknown6c.unknown00;
    f32 prevY = property.unknown6c.unknown04;
    if (!(fabsf(prevX) <= 0.000001f) || !(fabsf(prevY) <= 0.000001f)) {
      length = sqrtf(prevX * prevX + prevY * prevY);
      prevX = prevX * (1.0f / length);
      prevY = prevY * (1.0f / length);
    }
    cosine = inputX * prevX + inputY * prevY;
  } else {
    mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
    if (!(fabsf(input.x) <= 0.000001f) || !(fabsf(input.y) <= 0.000001f) || !(fabsf(input.z) <= 0.000001f)) {
      input.unknown001();
      cosine = input.x * property.unknown1e0.x + input.y * property.unknown1e0.y + input.z * property.unknown1e0.z;
    } else {
      return false;
    }
  }

  f32 angle = mm::acos(mm::clamp(cosine, -1.0f, 1.0f));
  return property.unknown310.unknown001()->turnAngle <= angle;
}

bool StateUtilField::isBackRange(GfComPropertyPc &property) { return calcInputDiffAngle(property) >= property.unknown310.unknown001()->backAngle; }

bool StateUtilField::isBackRangeAir(GfComPropertyPc &property) { return calcInputDiffAngleVel(property) >= property.unknown310.unknown001()->backAngle; }

bool StateUtilField::ignoreOnGroundJump(GfComPropertyPc &property, f32 time) { return time < property.unknown310.unknown001()->ignoreTimeJump; }

void StateUtilField::setIdleStatus(GfComPropertyPc &property, bool isIdle) {
  if (isIdle) {
    property.unknown310.unknown10_2 = true;
  } else {
    property.unknown310.unknown10_2 = false;
  }
}

void StateUtilField::setAirStatus(GfComBehaviorPc &behavior, bool isAir) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isAir) {
    property->unknown310.unknown11_1 = true;
  } else {
    property->unknown310.unknown11_1 = false;
  }
}

void StateUtilField::setSpecialActStatus(GfComBehaviorPc &behavior, bool isSpecialAct) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isSpecialAct) {
    property->unknown310.unknown11_2 = true;
  } else {
    property->unknown310.unknown11_2 = false;
  }
}

bool StateUtilField::isWallUpMove(GfPropertyField::WALL_MOVE_MODE mode) {
  return (mode == GfPropertyField::WALL_MOVE_MODE_UNKNOWN_0 || mode == GfPropertyField::WALL_MOVE_MODE_UNKNOWN_1) | (mode == GfPropertyField::WALL_MOVE_MODE_UNKNOWN_7);
}

ASM_CMD_ID_FIELD StateUtilField::getAsmID(GfPropertyField::WALL_MOVE_MODE mode) {
  switch (mode) {
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_0:
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_1:
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_7:
    return ASM_CMD_ID_FIELD_CLIMBUP;
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_2:
    return ASM_CMD_ID_FIELD_CLIMBRIGHT;
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_3:
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_4:
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_5:
    return ASM_CMD_ID_FIELD_CLIMBDOWN;
  case GfPropertyField::WALL_MOVE_MODE_UNKNOWN_6:
    return ASM_CMD_ID_FIELD_CLIMBLEFT;
  default:
    return ASM_CMD_ID_FIELD_CLIMBIDLE;
  }
}

bool StateUtilField::isMovableWall(GfComPropertyPc &property, GfPropertyField::WALL_MOVE_MODE mode) {
  bool isMovable = mode >= GfPropertyField::WALL_MOVE_MODE_UNKNOWN_0 && mode <= GfPropertyField::WALL_MOVE_MODE_UNKNOWN_7;
  if (property.unknown310.unknown10_7) {
    isMovable &= !isWallUpMove(mode);
  }
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!isMovable) {
    return false;
  }
  if (!sensor->unknown24_1 || sensor->unknown150.unknown90 == unknown020) {
    return true;
  }
  if (isWallUpMove(mode) && sensor->unknown25_0) {
    f32 height = __builtin_fmaxf(property.unknown310.unknown3c + 1.3f, 0.0f);
    return !(sensor->unknown1f0.unknown00.y - property.unknown160.unknown00.y <= height);
  }
  return true;
}

void StateUtilField::resetCameraForWall(GfComBehaviorPc &behavior, Timing timing) {
  if (!behavior.getProperty()->unknown111_2) {
    return;
  }
  static const ResetCameraWallTiming unknown015[] = {
      RESET_CAMERA_WALL_TIMING_UNKNOWN_0, RESET_CAMERA_WALL_TIMING_UNKNOWN_1, RESET_CAMERA_WALL_TIMING_UNKNOWN_2}; // Inferred role: camera timings; original name unknown.
  GfGamePlayerCamera::resetCameraClimb(unknown015[timing]);
}

bool StateUtilField::requestBattleStart(GfComPropertyPc &property) {
  if (property.unknown3c != 2) {
    return false;
  }

  if (GfGameRide::testRideOn()) {
    GfGameRide *ride = GfGameRide::get();
    if (ride != nullptr) {
      static_cast<GfObj *>(property.unknown08)->unknown009<MsgGameRideEvent>(ride, 0.0f, RIDE_EVENT_UNKNOWN_1);
    }
  } else {
    GfGameMoverSwitcher *switcher = GfGameMoverSwitcher::get();
    if (switcher != nullptr) {
      static_cast<GfObj *>(property.unknown08)->unknown009<MsgGameSwitchControlMover>(switcher, 0.0f, 1);
    }
  }

  return true;
}

void StateUtilField::notifySkillAct(GfComBehaviorPc &behavior, bool isSkillAct) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  if (property != nullptr) {
    GfObj *obj = GfObjUtil::getObj(property->unknown310.unknown78);
    if (obj != nullptr) {
      MsgPcFieldNotifySkillEvent message(!isSkillAct);
      static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
      if (!isSkillAct) {
        property->unknown310.unknown78 = unknown020;
      }
    }
  }
}

void StateUtilField::notifyRiderEvent(GfComBehaviorPc &behavior, VehicleEvent event) {
  MsgPcFieldNotifyRiderEvent message(event);
  StateUtil::sendMessageToRider(behavior, message);
}

void StateUtilField::requestGetOffRider(GfComBehaviorPc &behavior) {
  GfGameRide *ride = GfGameRide::get();
  if (ride != nullptr) {
    MsgGameRideEvent message(RIDE_EVENT_UNKNOWN_2);
    static_cast<GfObj *>(behavior.unknown08)->sendMessage(ride, message);
  }
}

bool StateUtilField::isBackMove(GfComPropertyPc &property) {
  return property.unknown1e0.x * property.unknown80.x + property.unknown1e0.y * property.unknown80.y + property.unknown1e0.z * property.unknown80.z < 0.0f;
}

bool StateUtilField::isInterruptionWater(GfComPropertyPc &property) {
  f32 depth = property.unknown118 - property.unknown2f0;
  return 0.2f <= property.unknown160.unknown00.y - depth;
}

f32 StateUtilField::calcFallSpeed(GfComPropertyPc &property) {
  const fw::Transform &locomotion = property.getLocomotion();
  f32 speed = locomotion.unknown00.y + property.unknownc0 * property.unknownd0.y;
  speed = property.unknown100.y + speed;
  return property.unknown90 + speed;
}

bool StateUtilField::isBigSplashFallSpeed(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  const MoveParam *param = property->unknown005();
  return calcFallSpeed(*property) <= -param->bigSplashSpeed;
}

bool StateUtilField::isBigLandDistance(GfComBehaviorPc &behavior) {
  FallDistancePlugin *plugin = behavior.unknown001<FallDistancePlugin>(17);
  if (plugin != nullptr) {
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    const MoveParam *param = property->unknown005();
    return plugin->calcDistance(property->unknown160.unknown00) + 0.01f >= param->landBigDist;
  }

  return false;
}

bool StateUtilField::isSwimFromAir(GfComPropertyPc &property) {
  const WaterCommonParam *param = property.unknown310.unknown002();
  return property.unknown90 >= param->waterDiveMinSpeed;
}

bool StateUtilField::isSwimMoveFromAir(GfComPropertyPc &property) {
  const WaterCommonParam *param = property.unknown310.unknown005();
  f32 speed = sqrtf(property.unknown80.x * property.unknown80.x + property.unknown80.y * property.unknown80.y + property.unknown80.z * property.unknown80.z);
  return property.existInputXY() && speed >= param->swimEnableSpeed;
}

bool StateUtilField::isWallFall(GfComPropertyPc &property) {
  property.getEnvSensor();
  GfComBehaviorPc *behavior = property.unknown08->getComponent<GfComBehaviorPc>();
  return (StateUtil::getClimbWallInfo(*behavior) == nullptr) | property.unknown60.unknown08.test(INPUT_ID_UNKNOWN_3);
}

bool StateUtilField::ignoreSlideJump(GfComPropertyPc &property, f32 time) { return time <= property.unknown001()->ignoreLandTime; }

bool StateUtilField::isFallFromSlideState(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_0) {
    return true;
  }
  const SlideParam *param = property.unknown001();
  return property.unknown160.unknown00.y - sensor->unknown30.unknown00.y >= param->fallDistance;
}

void StateUtilField::setAsmSpeedSlideBrake(GfComPropertyPc &property) { property.unknown08->getComponent<GfComAsm>()->setVariable("V_speed", property.unknownc0 * 60.0f * 60.0f / 1000.0f); }

f32 StateUtilField::setAsmSpeedMove(GfComPropertyPc &property) {
  GfComAsm *comAsm = property.unknown08->getComponent<GfComAsm>();
  f32 speed = sqrtf(property.unknown80.x * property.unknown80.x + property.unknown80.y * property.unknown80.y + property.unknown80.z * property.unknown80.z);
  if (property.unknown38 & 1) {
    f32 effect = MoveUtilField::getSpeedEffect(property);
    speed = speed / (effect + 1.0f);
    f32 velocityMax = static_cast<const GfMoveRunControler::Param *>(property.unknown310.unknown08->unknown10[3].param)->velocityMax;
    speed = speed < velocityMax ? speed : velocityMax;
    speed = (effect + 1.0f) * speed;
  }

  speed = speed * 60.0f * 60.0f / 1000.0f;
  comAsm->setVariable("V_speed", speed);
  return speed;
}

void StateUtilField::setAsmSpeedSwim(GfComPropertyPc &property) {
  const fw::ParamList *paramList = property.unknown310.unknown08.operator->();
  const GfMoveRunControler::Param *param = paramList->unknown0c > 10 ? static_cast<const GfMoveRunControler::Param *>(paramList->unknown10[10].param) : nullptr;
  f32 speed = sqrtf(property.unknown80.x * property.unknown80.x + property.unknown80.y * property.unknown80.y + property.unknown80.z * property.unknown80.z);
  f32 range = param->velocityMax - param->velocityMin;
  f32 ratio = mm::clamp(fabsf(range) > FLT_EPSILON ? (speed - param->velocityMin) / range : 0.0f, 0.0f, 1.0f);
  const WaterCommonParam *waterParam = property.unknown310.unknown002();
  f32 motionSpeed = ratio + (1.0f - ratio) * waterParam->swimMotionMin;
  property.unknown08->getComponent<GfComAsm>()->setSpeed(motionSpeed, ANIM_LAYER_UNKNOWN_0);
}

bool StateUtilField::isSlideStop(GfComPropertyPc &property) {
  const SlideParam *param = property.unknown001();
  return property.unknownc0 <= param->stopVel;
}

void StateUtilField::setSlideDirForce(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  mm::Vec3 direction;
  if (sensor->unknown24_0) {
    direction = sensor->unknown30.unknown40;
  } else {
    direction = mm::Vec3::zero;
  }
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    direction.unknown001();
    property.unknownd0 = direction;
  } else {
    EnviromentSensor::GroundInfo *ground = StateUtil::getGroundInfo(*property.unknown08->getComponent<GfComBehaviorPc>());
    if (ground != nullptr) {
      const mm::Vec3 &normal = ground->unknown10.normal;
      mm::Vec3 down(-mm::Vec3::unitY.x, -mm::Vec3::unitY.y, -mm::Vec3::unitY.z);
      f32 dot = normal.x * down.x + normal.y * down.y + normal.z * down.z;
      mm::Vec3 slope = down - normal * dot;
      if (!(fabsf(slope.x) <= 0.000001f) || !(fabsf(slope.y) <= 0.000001f) || !(fabsf(slope.z) <= 0.000001f)) {
        slope.unknown001();
        property.unknownd0 = slope;
        return;
      }
    }
    property.unknownd0 = property.unknown1e0;
  }
}

f32 StateUtilField::getChildFrameHeight(GfComponent &component) {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(component.unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::ReferenceFrame *frame = transform->unknown18.operator->();
  frame->syncLocalTransform();
  return frame->unknown20.unknown00.y;
}

void StateUtilField::setChildFrameHeight(GfComponent &component, f32 height) {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(component.unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::ReferenceFrame *frame = transform->unknown18.operator->();
  frame->invalidateWorld();
  frame->unknown20.unknown00.y = height;
}

mm::Vec3 StateUtilField::calcWallPreparePosition(GfComPropertyPc &property, const mm::Vec3 &position, const mm::Plane &plane) {
  mm::Vec3 result = position;
  if (position.y >= property.unknown160.unknown00.y) {
    f32 offset = property.unknown310.unknown1c + property.unknown310.unknown4c;
    result = position + plane.normal * offset;
  } else {
    f32 offset = property.unknown310.unknown2c - property.unknown310.unknown4c;
    result = position - plane.normal * offset;
  }
  return result;
}

bool StateUtilField::testCloud(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_1) {
    return false;
  }
  return sensor->unknown30.unknown70.unknown34 == 11;
}

bool StateUtilField::isWallIdleMotion(GfComAsm &comAsm) {
  const char *stateName = comAsm.getStateName(ANIM_LAYER_UNKNOWN_0);
  bool isIdle = false;
  if (stateName != nullptr) {
    if (__builtin_strcmp(stateName, "S_climbidle_base") == 0 || __builtin_strcmp(stateName, "S_climbidle_mirror") == 0) {
      isIdle = true;
    }
  }
  return isIdle;
}

void StateUtilField::notifyTurn(GfComBehaviorPc &behavior) {
  if (behavior.getProperty()->unknown38 == 0) {
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    formation->unknown234 = !formation->unknown234;
  }
}

bool StateUtilField::isEnableWallPrepare(GfComPropertyPc &property) {
  if (property.unknown38 == 0) {
    return false;
  }
  GF_OBJ_HANDLE *handle = GfGamePlayerFormation::get()->unknown1a0[property.unknown38 - 2].unknown08;
  if (handle == unknown020) {
    return false;
  }
  return GfObjUtil::getProperty(handle)->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_3;
}

bool StateUtilField::isWallPreparePosition(GfComPropertyPc &property, const mm::Vec3 &position) {
  mm::Vec3 diff(property.unknown160.unknown00.x - position.x, 0.0f, property.unknown160.unknown00.z - position.z);
  f32 lengthSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
  const WallAiParam *param = AgentUtilField::getAIParamAdapter(property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
  return lengthSq <= param->prepareRange * param->prepareRange;
}

bool StateUtilField::isEnableWallAdsorptionStart(GfComPropertyPc &property, const mm::Vec3 &position, const mm::Vec3 &preparePosition) {
  if (isNearPlayerWall(property, position, AgentUtilField::getAIParamAdapter(property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>()->minDist)) {
    return false;
  }
  return isWallPreparePosition(property, preparePosition);
}

bool StateUtilField::isNearPlayerWall(GfComPropertyPc &property, const mm::Vec3 &position, f32 range) {
  f32 rangeSq = range * range;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  for (u64 i = 0; i < 6; i++) {
    if (i == property.unknown38) {
      continue;
    }
    GF_OBJ_HANDLE *handle = formation->unknown1a0[i].unknown08;
    if (handle == unknown020) {
      continue;
    }
    const GfObjProperty *other = GfObjUtil::getProperty(handle);
    if (other->unknown18->unknown00 == PROPERTY_MOVE_UNKNOWN_3) {
      mm::Vec3 diff = position - other->unknown18->unknown10;
      if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z <= rangeSq) {
        return true;
      }
    }
  }
  return false;
}

bool StateUtilField::isNearPlayer(GfComPropertyPc &property, const mm::Vec3 &position, f32 range) {
  f32 rangeSq = range * range;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  for (u64 i = 0; i < 6; i++) {
    if (i != property.unknown38 && formation->unknown1a0[i].unknown08 != unknown020) {
      mm::Vec3 diff = position - GfObjUtil::getProperty(formation->unknown1a0[i].unknown08)->unknown18->unknown10;
      if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z <= rangeSq) {
        return true;
      }
    }
  }
  return false;
}

bool StateUtilField::isWallDetach(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_0 || ((sensor->unknown30.unknown30 >> 4) & 1) != 0) {
    return false;
  }
  const mm::Plane &plane = sensor->unknown30.unknown10;
  const mm::Vec3 &position = property.unknown160.unknown00;
  f32 dot = position.x * plane.normal.x + position.y * plane.normal.y + position.z * plane.normal.z;
  return plane.distance + dot < -property.unknown310.unknown38;
}

bool StateUtilField::isWallAdsorption(GfComPropertyPc &property) {
  if (property.unknown310.unknown10_3) {
    EnviromentSensor *sensor = property.getEnvSensor();
    if (sensor->unknown24_4 && (sensor->unknown150.unknown00.unknown24 & 0x50) == 0x10) {
      const EnviromentSensor::Parameter *sensorParam = property.unknown08->getComponent<GfComEnvSensor>()->unknown2e0.get<EnviromentSensor::Parameter>();
      EnviromentSensor::HorizonPacket packet;
      EnviromentSensor::unknown006 wall;
      packet.unknown00 = 0x40;
      const mm::Plane &sensorPlane = sensor->unknown150.unknown00.unknown00;
      packet.unknown10 = mm::Vec3(-sensorPlane.normal.x, -sensorPlane.normal.y, -sensorPlane.normal.z);
      packet.unknown20 = 0.0f;
      packet.unknown24 = sensorParam->obstacleSearchLength;
      packet.unknown30 = sensor->unknown290;
      packet.unknown38 = &wall;
      EnviromentSensor::searchHorizon(property.unknown160.unknown00, &packet);
      if (((packet.unknown34 >> 6) & 1) && wall.unknown60.unknown24_4) {
        property.unknown310.unknown130 = wall.unknown60;
        property.unknown310.unknown10_6 = true;
        property.unknown310.flashWallInfo(property);
        f32 limit = property.unknown310.unknown1c + property.unknown310.unknown4c;
        if (!(wall.unknown60.unknown20 > limit)) {
          mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
          if (!(fabsf(input.x) <= 0.000001f) || !(fabsf(input.y) <= 0.000001f) || !(fabsf(input.z) <= 0.000001f)) {
            input.unknown001();
          }

          mm::Vec3 direction(wall.unknown60.unknown00.normal.x, 0.0f, wall.unknown60.unknown00.normal.z);
          if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
            direction.unknown001();
          }

          const WallCommonParam *param = property.unknown310.unknown004(15).get<WallCommonParam>();
          mm::Vec3 reverse(-direction.x, -direction.y, -direction.z);
          f32 cosine = mm::clamp(input.x * reverse.x + input.y * reverse.y + input.z * reverse.z, -1.0f, 1.0f);
          f32 angle = mm::acos(cosine);
          return param->adsorptionAngle * mm::DEG_TO_RAD >= angle;
        }
      }
    }
  }

  return false;
}

void StateUtilField::setEnableFallIntoColi(GfComBehaviorPc &behavior, bool isEnable) {
  FallIntoColiPlugin *plugin = behavior.unknown001<FallIntoColiPlugin>(9);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setAccessFlag(GfComBehaviorPc &behavior, bool isEnable) {
  AccessPlugin *plugin = behavior.unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

GfObj *StateUtilField::getAccessTarget(GfComBehaviorPc &behavior) {
  AccessPlugin *plugin = behavior.unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    return GfObjUtil::getObj(plugin->unknown10);
  }
  return nullptr;
}

void StateUtilField::setEnableLure(GfComBehaviorPc &behavior, bool isEnable) {
  LurePlugin *plugin = behavior.unknown001<LurePlugin>(15);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setEnableDeadColCheck(GfComBehaviorPc &behavior, bool isEnable) {
  DeadColCheckPlugin *plugin = behavior.unknown001<DeadColCheckPlugin>(19);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setEnableWaterIn(GfComBehaviorPc &behavior, bool isEnable) {
  WaterInPlugin *plugin = behavior.unknown001<WaterInPlugin>(18);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

GfObj *StateUtilField::getLureTarget(GfComBehaviorPc &behavior) {
  LurePlugin *plugin = behavior.unknown001<LurePlugin>(15);
  if (plugin != nullptr) {
    return GfObjUtil::getObj(plugin->unknown10);
  }

  return nullptr;
}

GF_OBJ_HANDLE *StateUtilField::getLureTargetHandle(GfComBehaviorPc &behavior) {
  LurePlugin *plugin = behavior.unknown001<LurePlugin>(15);
  if (plugin != nullptr) {
    return plugin->unknown10;
  }

  return unknown020;
}

void StateUtilField::setLookAtFlag(GfComBehaviorPc &behavior, bool isEnable) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isEnable) {
    property->unknown310.unknown10_1 = true;
  } else {
    property->unknown310.unknown10_1 = false;
  }

  if (StateUtil::getTarget(behavior) == unknown020) {
    LookAtPlugin *plugin = behavior.unknown001<LookAtPlugin>(5);
    if (plugin != nullptr) {
      plugin->setActivate(isEnable);
    }
  }
}

void StateUtilField::startWaterWarpFade(GfComBehaviorPc &behavior) { behavior.unknown001<FadePlugin>(11)->setActivate(true); }

void StateUtilField::onLandSliding(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  const SlideParam *param = property->unknown001();
  f32 speed = property->unknownc0;
  f32 endVel = param->endVel;
  property->unknownc0 = speed < endVel ? speed : endVel;
  property->unknown80 = mm::Vec3::zero;
}

// Inferred role: stores the auto run direction and power from the input, the facing direction when there is no input (shared by setAutoRun and flipAutoRun); original name unknown.
static inline void unknown001(GfComPropertyPc &property) {
  mm::Vec3 input = property.unknown2d0 * property.unknown60.unknown00 + property.unknown2b0 * property.unknown60.unknown04;
  f32 power = 0.0f;
  if (!(fabsf(input.x) <= 0.000001f) || !(fabsf(input.y) <= 0.000001f) || !(fabsf(input.z) <= 0.000001f)) {
    power = sqrtf(input.x * input.x + input.y * input.y + input.z * input.z);
    input.unknown001();
  } else {
    input = property.unknown1e0;
  }

  property.unknown310.unknown60 = input;
  property.unknown310.unknown70 = power;
}

void StateUtilField::setAutoRun(GfComPropertyPc &property, bool isAutoRun) {
  if (isAutoRun) {
    property.unknown310.unknown11_0 = true;
  } else {
    property.unknown310.unknown11_0 = false;
  }

  if (isAutoRun) {
    unknown001(property);
  }
}

void StateUtilField::flipAutoRun(GfComPropertyPc &property) {
  if (!property.unknown310.unknown11_0) {
    if (!(fabsf(property.unknown80.x) <= 0.000001f) || !(fabsf(property.unknown80.y) <= 0.000001f) || !(fabsf(property.unknown80.z) <= 0.000001f)) {
      property.unknown310.unknown11_0 = true;
      unknown001(property);
    }
  } else {
    property.unknown310.unknown11_0 = false;
  }
}

void StateUtilField::setAutoRunInput(GfComPropertyPc &property) {
  if (!property.existInputXY()) {
    property.setInputDirPow(property.unknown310.unknown60, property.unknown310.unknown70);
    return;
  }

  mm::Vec3 input = property.unknown2d0 * property.unknown60.unknown00 + property.unknown2b0 * property.unknown60.unknown04;
  input.unknown001();
  property.unknown310.unknown60 = input;
  property.setInputDirPow(input, property.unknown310.unknown70);
}

} // namespace pc
} // namespace gf
