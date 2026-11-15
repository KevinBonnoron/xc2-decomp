#include "dr/dr_pixl_shadow_obj_dir.h"

#include "dr/dr_calc_clip_work_view_poli.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "grlib/cglib_dbl_uniform_block.h"

namespace ml {

// Decision 2026-11-14 #4: unknown338/unknown33c are two floats set in the init list; the game stores 5.0f and 30.0f with one merged
// 64-bit store (`str x9, [x20, #0x338]` at 0x7100863534), 38 instructions.
DrPixlShadowObjDir::DrPixlShadowObjDir(DrMan *man) : DrPixlShadowObj(man, 0, 0), unknown2b0(1.0f), unknown300(0.0f, 0.0f, 0.0f), unknown338(5.0f), unknown33c(30.0f), unknown340(1.0f) {}

DrPixlShadowObjDir::~DrPixlShadowObjDir() {
  unknown08.release();
  delete unknown190;
}

bool DrPixlShadowObjDir::dispChk() { return (unknown50 & FLAG_UNKNOWN_1) != 0; }

int DrPixlShadowObjDir::clipTypeChk(const mm::Vec3 &position, f32 value) {
  if ((unknown50 & FLAG_UNKNOWN_3) == 0 || value >= unknown338) {
    return 0;
  }
  return unknown1a0.clipTypeTest(position, value);
}

bool DrPixlShadowObjDir::clipChk(const mm::Vec3 &position, f32 value, bool flag) {
  if ((unknown50 & FLAG_UNKNOWN_3) == 0 || value >= unknown338) {
    return false;
  }
  bool isClip = unknown1a0.clipTest(position, value);
  if (!flag && isClip) {
    return unknown178->unknown580->unknown10->unknown590.clipLineTest(position, unknown300, value);
  }
  return isClip;
}

} // namespace ml
