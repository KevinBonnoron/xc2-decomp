#include "dr/dr_res_clip.h"

#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_view_work.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrResClip::DrResClip() : unknown00(nullptr), unknown08(0x60), unknown0c(0), unknown10(0) {}

DrResClip::~DrResClip() {
  if (unknown00 != nullptr) {
    unknown00->unknown28 = nullptr;
    unknown00 = nullptr;
  }
}

bool DrResClip::clipChkOccOff(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius) {
  u32 flags = unknown08;
  unknown08 = flags & 0xffffff1e;
  unknown10 = 0;
  const mm::Vec3 &viewPos = viewWork->unknown400;
  f32 dx = viewPos.x - position.x;
  f32 dy = viewPos.y - position.y;
  f32 dz = viewPos.z - position.z;
  if (dx * dx + dy * dy + dz * dz <= radius * radius) {
    unknown08 = (flags & 0xffffff00) | 0xe;
    return false;
  }
  if (!viewWork->unknown4e0.clipTest(position, radius)) {
    unknown08 = 0;
    return true;
  }
  return false;
}

} // namespace ml
