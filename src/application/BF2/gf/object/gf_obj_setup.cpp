#include "gf/object/gf_obj_setup.h"

namespace gf {

void GfObjSetup::setInitialScale(f32 scale) {
  unknown40 = scale;
  unknown44 = scale;
  unknown48 = scale;
}

void GfObjSetup::setInitialScale(const mm::Vec3 &scale) {
  unknown40 = scale.x;
  unknown44 = scale.y;
  unknown48 = scale.z;
}

} // namespace gf
