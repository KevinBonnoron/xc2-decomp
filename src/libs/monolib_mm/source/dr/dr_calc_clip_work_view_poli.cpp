#include "dr/dr_calc_clip_work_view_poli.h"

namespace ml {

DrCalcClipWorkViewPoli::DrCalcClipWorkViewPoli() { unknown08 = 3; }

DrCalcClipWorkViewPoli::~DrCalcClipWorkViewPoli() {}

bool DrCalcClipWorkViewPoli::clipLineTest(const mm::Vec3 &start, const mm::Vec3 &direction, f32 radius) const {
  for (int i = 0; i < 4; i++) {
    f32 distance = unknown160[i];
    f32 denominator = unknown60[i].x * direction.x + unknown60[i].y * direction.y + unknown60[i].z * direction.z;
    if (denominator == 0.0f) {
      continue;
    }
    // The line meets the plane i at start + direction * t.
    f32 t = (distance - (unknown60[i].x * start.x + unknown60[i].y * start.y + unknown60[i].z * start.z)) / denominator;
    // Only x gets a named offset: with the debug info of the check build, the game's FP register balancing of
    // this loop (A57 load balancing) is reproduced only when the first product is a named value.
    f32 offsetX = direction.x * t;
    f32 hitX = start.x + offsetX;
    f32 hitY = start.y + direction.y * t;
    f32 hitZ = start.z + direction.z * t;
    mm::Vec3 point(hitX - unknown10.x, hitY - unknown10.y, hitZ - unknown10.z);
    if (unknownE0[i].x * point.x + unknownE0[i].y * point.y + unknownE0[i].z * point.z <= -0.00001f) {
      continue;
    }
    if (unknown120[i].x * point.x + unknown120[i].y * point.y + unknown120[i].z * point.z <= -0.00001f) {
      continue;
    }
    return true;
  }
  mm::Vec3 scaled(direction.x * 2000.0f, direction.y * 2000.0f, direction.z * 2000.0f);
  for (int i = 0; i < 4; i++) {
    mm::Vec3 closest1;
    mm::Vec3 closest2;
    checkLineNeraPointGet(closest1, closest2, unknown10, unknownA0[i], start, scaled);
    mm::Vec3 difference = closest1 - closest2;
    if (difference.x * difference.x + difference.y * difference.y + difference.z * difference.z <= radius * radius) {
      return true;
    }
  }
  return false;
}

} // namespace ml
