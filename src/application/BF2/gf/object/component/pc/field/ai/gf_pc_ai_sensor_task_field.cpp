#include "gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

void TaskFieldSensor::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) { blackBoard.unknown08->setEnvSensorCheckFlags(0x20, event.unknown04); }

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

} // namespace pc
} // namespace gf
