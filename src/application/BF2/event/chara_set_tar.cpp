#include "event/chara_set_tar.h"

#include <math.h>

#include "mm_math/mm_math.h"

namespace event {

mm::Vec2 CharaSetTar::calcLensUV(const mm::Vec3 &from, const mm::Vec3 &to) {
  mm::Vec2 fromRot = vec2rot(from);
  mm::Vec2 toRot = vec2rot(to);
  f32 pitch = toRot.x;
  while (pitch < fromRot.x - 3.1415927f) {
    pitch += 6.2831855f;
  }
  while (fromRot.x + 3.1415927f < pitch) {
    pitch -= 6.2831855f;
  }
  f32 yaw = toRot.y;
  while (yaw < -3.1415927f + fromRot.y) {
    yaw += 6.2831855f;
  }
  while (3.1415927f + fromRot.y < yaw) {
    yaw -= 6.2831855f;
  }
  mm::Vec2 sub = getSubRot(fromRot, mm::Vec2(pitch, yaw));
  mm::Vec2 result;
  result.x = sub.y / LENS_LIMIT.y;
  result.y = sub.x / LENS_LIMIT.x;
  mm::clampRef(result.x, -1.0f, 1.0f);
  mm::clampRef(result.y, -1.0f, 1.0f);
  return result;
}

mm::Vec2 CharaSetTar::vec2rot(const mm::Vec3 &direction) {
  mm::Vec2 rotation;
  rotation.y = -atan2f(direction.x, -direction.z);
  rotation.x = atan2f(direction.y, sqrtf(direction.x * direction.x + direction.z * direction.z));
  return rotation;
}

mm::Vec2 CharaSetTar::getSubRot(const mm::Vec2 &from, const mm::Vec2 &to) {
  mm::Vec2 result(to.x - from.x, to.y - from.y);
  while (result.x < -3.1415927f) {
    result.x += 6.2831855f;
  }
  while (result.x > 3.1415927f) {
    result.x -= 6.2831855f;
  }
  while (result.y < -3.1415927f) {
    result.y += 6.2831855f;
  }
  while (result.y > 3.1415927f) {
    result.y -= 6.2831855f;
  }
  return result;
}

void CharaSetTar::term() {
  if (unknown08 & 1) {
    idle();
    unknown08 &= ~1;
  }
}

} // namespace event
