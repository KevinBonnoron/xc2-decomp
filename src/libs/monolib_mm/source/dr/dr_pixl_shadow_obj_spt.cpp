#include "dr/dr_pixl_shadow_obj_spt.h"

#include "grlib/cglib_dbl_uniform_block.h"

namespace ml {
class DrMan;

DrPixlShadowObjSpt::DrPixlShadowObjSpt(DrMan *man) : DrPixlShadowObj(man, 1, 0) {
  unknown200[3] = 1.0f;
  unknown200[2] = 1.0f;
  unknown200[1] = 1.0f;
  unknown200[0] = 1.0f;
  unknown220[0] = 1.0f;
  unknown220[1] = 1.0f;
  unknown220[2] = -1.0f;
  unknown22c = {-1.0f, 4.0f};
}

DrPixlShadowObjSpt::~DrPixlShadowObjSpt() {
  unknown08.release();
  delete unknown190;
}

bool DrPixlShadowObjSpt::dispChk() { return (unknown50 & FLAG_UNKNOWN_1) != 0; }

bool DrPixlShadowObjSpt::clipChk(const mm::Vec3 &position, f32 value, bool flag) {
  if (unknown22c.y < value) {
    return false;
  }
  return unknown1a0.clipTest(position, value);
}

int DrPixlShadowObjSpt::clipTypeChk(const mm::Vec3 &position, f32 value) {
  if (unknown22c.y < value) {
    return 0;
  }
  return unknown1a0.clipTypeTest(position, value);
}

void DrPixlShadowObjSpt::renderLight() {}

const f32 *DrPixlShadowObjSpt::getParmTbl() const { return unknown200; }

} // namespace ml
