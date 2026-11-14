#include "dr/dr_pixl_shadow_obj_dir.h"

#include "dr/dr_calc_clip_work_view_poli.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "grlib/cglib_dbl_uniform_block.h"

namespace ml {

DrPixlShadowObjDir::~DrPixlShadowObjDir() {
  unknown08.release();
  delete unknown190;
}

bool DrPixlShadowObjDir::dispChk() { return (unknown50 & FLAG_UNKNOWN_1) != 0; }

int DrPixlShadowObjDir::clipTypeChk(const mm::Vec3 &position, f32 value) {
  if ((unknown50 & FLAG_UNKNOWN_3) == 0 || value >= unknown338.x) {
    return 0;
  }
  return unknown1a0.clipTypeTest(position, value);
}

bool DrPixlShadowObjDir::clipChk(const mm::Vec3 &position, f32 value, bool flag) {
  if ((unknown50 & FLAG_UNKNOWN_3) == 0 || value >= unknown338.x) {
    return false;
  }
  bool isClip = unknown1a0.clipTest(position, value);
  if (!flag && isClip) {
    return unknown178->unknown580->unknown10->unknown590.clipLineTest(position, unknown300, value);
  }
  return isClip;
}

} // namespace ml
