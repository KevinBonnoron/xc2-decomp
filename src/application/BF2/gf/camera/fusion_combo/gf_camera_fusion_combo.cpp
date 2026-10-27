#include "gf/camera/fusion_combo/gf_camera_fusion_combo.h"

#include <math.h>

namespace gf {

FusionComboCamera::~FusionComboCamera() {}

void FusionComboCamera::onActivate() {}

bool FusionComboCamera::isPlayEnd() const { return unknown120 <= unknown124; }

f32 FusionComboCamera::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

f32 FusionComboCamera::slowOut(f32 t) {
  f32 x = sinf((1.0f - t) * 1.5707964f + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 FusionComboCamera::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

const mm::mtl::RTTI *FusionComboCamera::getRTTI() const { return &m_rtti; }

const char *FusionComboCamera::getName() const { return "FusionComboCamera"; }

} // namespace gf
