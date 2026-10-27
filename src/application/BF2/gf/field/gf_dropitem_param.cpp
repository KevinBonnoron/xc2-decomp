#include "gf/field/gf_dropitem_param.h"

#include "ml/rand.h"
#include "mm_math/mm_vec3.h"

namespace gf {

GfDropitemParamInst::GfDropitemParamInst(const GfDropitemParam *param, f32 height) : unknown00(nullptr), unknown08(0.0f), unknown0c(0.0f) {
  if (param != nullptr) {
    create(*param, height);
  }
}

void GfDropitemParamInst::create(const GfDropitemParam &param, f32 height) {
  unknown00 = &param;
  unknown08 = param.unknown00 + param.unknown04 * ml::mtRandf1();
  unknown0c = param.unknown08 + param.unknown0c * ml::mtRandf1() + height;
}

f32 GfDropitemParamInst::getGravity() const {
  f32 time = unknown00->unknown10 * 0.5f;
  return unknown08 / (time * time) * (2.0f / 3.0f);
}

mm::Vec3 &GfDropitemParamInst::getInitVelocity(mm::Vec3 &velocity) const {
  f32 gravity = getGravity();
  velocity.x = 0.0f;
  velocity.y = (unknown08 - unknown00->unknown34 - unknown00->unknown38) / unknown00->unknown10 + gravity * 0.5f * unknown00->unknown10;
  velocity.z = unknown0c / unknown00->unknown10 * 0.5f;
  return velocity;
}

} // namespace gf
