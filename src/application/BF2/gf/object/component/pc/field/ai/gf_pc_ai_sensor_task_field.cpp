#include "gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/gf_obj.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace gf {
namespace pc {

void TaskFieldSensor::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 24 as in the original file: it is the line argument of the assert.
#line 24
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  }
}

void TaskFieldSensor::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) { blackBoard.m_comPropertyPc->setEnvSensorCheckFlags(0x20, event.unknown04); }

bool TaskFieldSensor::testCondition(const BlackBoardField &blackBoard) { return true; }

bool isStack(const GfComPropertyPc &property, const SensorAIParam &param, f32 time) {
  mm::Vec3 direction = property.unknown80;
  f32 speed = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    direction.unknown001();
  }

  mm::Vec3 move = property.unknown160.unknown00 - property.unknown180.unknown00;
  f32 moveDistance = direction.x * move.x + direction.y * move.y + direction.z * move.z;
  return speed * time - moveDistance >= param.stackThreashold;
}

// Inferred role: counts down the wait time of a requested warp or jump, then sends the request to the player and drops the request flag once it is accepted or the wait ran out; original name unknown.
// Evidence: the three branches of TaskFieldSensor::update (1.0.0: 0x7100544988) repeat these statements with the messages 0x1000016, 0x1000018 and 0x1000020.
template <typename Message> void unknown001(BlackBoardField &blackBoard, GfComPropertyPc *property, u32 flag) {
  blackBoard.unknown204 -= blackBoard.unknown18->unknown04;
  if (blackBoard.unknown204 <= 0.0f) {
    Message message;
    GfObj *obj = static_cast<GfObj *>(property->unknown08);
    obj->sendMessage(obj, message);
    if (message.unknown08 || blackBoard.unknown204 <= -5.0f) {
      blackBoard.unknown200.set(flag, false);
    }
  }
}

void TaskFieldSensor::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.m_comPropertyPc;
  const SensorAIParam *param = property->unknown010();
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  blackBoard.unknown40 = formation->getFollowTransform(property->unknown38).unknown00;
  blackBoard.unknown20 = formation->unknown20[property->unknown38];
  blackBoard.unknown200.set(0, isStack(*property, *param, blackBoard.unknown18->unknown04));
  EnviromentSensor *sensor = property->getEnvSensor();
  if (!sensor->unknown24_4) {
    blackBoard.unknown200.set(1, false);
  } else {
    f32 cosine = mm::clamp(sensor->unknown150.unknown00.unknown00.normal.x * mm::Vec3::unitY.x + sensor->unknown150.unknown00.unknown00.normal.y * mm::Vec3::unitY.y +
                               sensor->unknown150.unknown00.unknown00.normal.z * mm::Vec3::unitY.z,
                           -1.0f,
                           1.0f);
    blackBoard.unknown200.set(1, mm::acos(cosine) * mm::RAD_TO_DEG > param->obstacleAngle);
  }
  if (blackBoard.unknown200.test(1)) {
    // The game keeps the ceiling test as a value (mov w10, wzr at 0x7100544c60, cset w10, ls at 0x7100544c7c, then tbnz w10 at 0x7100544c80) and tests the horizontal flag after it (tbnz w9, #5 at
    // 0x7100544c84). With the test written inside the condition, or with the operands swapped (isNear || flag), clang threads the jump and the function is 3 instructions short (317 against 320).
    bool isNear = sensor->unknown24_3 && sensor->m_verticalData.unknowne0.unknown00 - property->unknown160.unknown00.y <= param->enableJumpCeil;
    if (sensor->unknown24_5 || isNear) {
      blackBoard.unknown200.set(2, false);
    } else {
      const mm::Plane *wall = sensor->unknown24_4 ? &sensor->unknown150.unknown00.unknown00 : nullptr;
      if (-(blackBoard.unknown20.x * wall->normal.x + blackBoard.unknown20.y * wall->normal.y + blackBoard.unknown20.z * wall->normal.z + wall->distance) >= param->enableJumpOffset) {
        blackBoard.unknown200.set(2);
      } else {
        blackBoard.unknown200.set(2, false);
      }
    }
  }
  if (blackBoard.unknown200.test(6)) {
    unknown001<MsgPcFieldHighJump>(blackBoard, property, 6);
  } else if (blackBoard.unknown200.test(7)) {
    unknown001<MsgPcFieldWaterWarp>(blackBoard, property, 7);
  } else if (blackBoard.unknown200.test(9)) {
    unknown001<MsgPcFieldWaterWarpBuddy>(blackBoard, property, 9);
  }
  if (!blackBoard.m_comPropertyPc->m_propertyField.unknown10_4) {
    blackBoard.unknown200.set(8, false);
  }
}

} // namespace pc
} // namespace gf
