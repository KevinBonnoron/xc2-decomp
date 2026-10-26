#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {
class Pose;
} // namespace anm

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class ParamAdapter;
class ReferenceFrame;

// Only the members read by LookIkSolver are declared; the original member names are unknown.
class SpineIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static SpineIkSolver *create(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  void startTargetFade(f32 time);
  void onDisable() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _34[0x50 - 0x34];
  mm::Vec3 unknown50; // Inferred role: target; original member name unknown.
  u8 _60[0x70 - 0x60];
  mm::Vec3 unknown70; // Inferred role: front in model space; original member name unknown.
};

static_assert(offsetof(SpineIkSolver, unknown50) == 0x50, "");
static_assert(offsetof(SpineIkSolver, unknown70) == 0x70, "");

} // namespace fw
