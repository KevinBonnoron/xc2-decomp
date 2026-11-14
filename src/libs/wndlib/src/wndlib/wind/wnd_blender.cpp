// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/wndlib/src/wndlib/wind/wnd_blender.cpp.
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "wnd/wnd_node.h"
#include "wnd/wnd_wind.h" // IWYU pragma: keep

namespace wnd {

void WindBlender::setNode(const WindNode *node) {
  unknownd0 = node;
  unknownd8 = nullptr;
  unknowne4 = 0.0f;
}

void WindBlender::changeNode(const WindNode *node, f32 time) {
#line 80
  MM_ASSERT(abs(time) > 1.1920928955078125e-07F);
  if (unknownd8 == nullptr) {
    unknownd8 = unknownd0;
  } else if (unknowne0 >= 0.5f) {
    unknownd8 = unknownd0;
  }
  unknownd0 = node;
  unknowne4 = time;
  unknowne0 = 0.0f;
}

// Inferred role: power of one oscillating wind component at a time; original name unknown.
static f32 unknown001(const unknown004 &component, f32 time) {
  return (component.unknown00 - component.unknown04) * (sinf((time + component.unknown0c) * 6.2831855f / component.unknown08) + 1.0f) * 0.5f + component.unknown04;
}

void ConpoundWind::calcWind(f32 time, u32 index, mm::Vec3 *wind) {
  f32 t = index * 0.07f + time;
  unknownd8[index][0] = unknown001(unknownd0->unknown00[0], t);
  *wind = mm::Vec3(0.0f, 0.0f, -1.0f) * unknownd8[index][0];
  unknownd8[index][1] = unknown001(unknownd0->unknown00[1], t);
  *wind += mm::Vec3(0.0f, 0.0f, 1.0f) * unknownd8[index][1];
  unknownd8[index][2] = unknown001(unknownd0->unknown00[2], t);
  *wind += mm::Vec3(1.0f, 0.0f, 0.0f) * unknownd8[index][2];
  unknownd8[index][3] = unknown001(unknownd0->unknown00[3], t);
  *wind += mm::Vec3(-1.0f, 0.0f, 0.0f) * unknownd8[index][3];
  unknownd8[index][4] = unknown001(unknownd0->unknown00[4], t);
  *wind += mm::Vec3(0.0f, -1.0f, 0.0f) * unknownd8[index][4];
}

void ConpoundWind::update(const UpdateInfo &info) {
  for (u32 i = 0; i < 12; i++) {
    calcWind(info.unknown00, i, &unknown10[i]);
  }
}

} // namespace wnd
