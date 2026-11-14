#include "gf/camera/fusion_combo/gf_camera_fusion_combo.h"

#include <math.h>

#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

FusionComboCamera::~FusionComboCamera() {}

void FusionComboCamera::onActivate() {}

bool FusionComboCamera::isPlayEnd() const { return unknown120 <= unknown124; }

f32 FusionComboCamera::getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  mm::Vec3 from(direction.x, 0.0f, direction.z);
  mm::Vec3 to(reference.x, 0.0f, reference.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return 0.0f;
  }
  from.unknown002();
  to.unknown002();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.x * to.z - from.z * to.x < 0.0f ? 6.2831855f - angle : angle;
}

f32 FusionComboCamera::getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  f32 yaw = getYaw(direction, reference);
  mm::Vec3 from = direction;
  mm::Vec3 to = reference;
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(yaw * -0.5f);
  rotation.z = 0.0f;
  rotation.w = cosf(yaw * -0.5f);
  from = rotation.rotate(from);
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.z * to.y - from.y * to.z < 0.0f ? -angle : angle;
}

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
