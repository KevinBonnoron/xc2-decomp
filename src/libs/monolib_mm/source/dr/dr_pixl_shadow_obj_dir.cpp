#include "dr/dr_pixl_shadow_obj_dir.h"

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

} // namespace ml
