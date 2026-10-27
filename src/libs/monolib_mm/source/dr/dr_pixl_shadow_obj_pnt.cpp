#include "dr/dr_pixl_shadow_obj_pnt.h"

#include "dr/dr_light_obj.h"
#include "grlib/cglib_dbl_uniform_block.h"

namespace ml {
class DrMan;

DrPixlShadowObjPnt::DrPixlShadowObjPnt(DrMan *man, int index) : DrPixlShadowObj(man, 2, index) {}

DrPixlShadowObjPnt::~DrPixlShadowObjPnt() {
  unknown08.release();
  delete unknown190;
}

bool DrPixlShadowObjPnt::dispChk() { return !unknown198->isCullON(); }

bool DrPixlShadowObjPnt::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return unknown1a0.clipTest(position, value); }

int DrPixlShadowObjPnt::clipTypeChk(const mm::Vec3 &position, f32 value) { return unknown1a0.clipTypeTest(position, value); }

} // namespace ml
