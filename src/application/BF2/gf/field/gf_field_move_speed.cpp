#include "gf/field/gf_field_move_speed.h"

#include "gf/object/gf_obj_handle.h"

namespace gf {

void GfFieldMoveSpeed::dispose() { unknown00 = INVALID_HANDLE; }

void GfFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  unknown20 = unknown10;
  unknown24 = speed;
  unknown28 = time;
  unknown2c = 0.0f;
}

void GfEnemyFieldMoveSpeed::setSpeedKmph(f32 speed, f32 time) {
  f32 current = unknown28;
  unknown24 = speed;
  unknown10 = current;
  unknown20 = current;
  unknown28 = time == 0.0f ? speed : current;
  unknown2c = time;
}

} // namespace gf
