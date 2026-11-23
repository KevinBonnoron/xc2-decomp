#include "gf/object/component/behavior/movement/gf_move_brake.h"

#include <math.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"

namespace gf {

void GfMoveBrakeControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake", offsetof(Param, brake), 0.001f, 10000.0f, 15.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveBrakeControler::update(const fw::UpdateInfo &info, Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  mm::Vec3 &velocity = packet.unknown00;
  f32 speed = fmaxf(sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z) - param->brake * info.unknown04, 0.0f);
  if (!(fabsf(velocity.x) <= 0.000001f) || !(fabsf(velocity.y) <= 0.000001f) || !(fabsf(velocity.z) <= 0.000001f)) {
    velocity.unknown001();
  }
  velocity *= speed;
}

} // namespace gf
