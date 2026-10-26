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
class LookAtIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static LookAtIkSolver *create(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  void startTargetFade(f32 time);
  void onDisable() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _34[0x60 - 0x34];
  mm::Vec3 unknown60; // Inferred role: front in model space; original member name unknown.
  u8 _70[0xa0 - 0x70];
  mm::Vec3 unknowna0; // Inferred role: target; original member name unknown.
  u8 _b0[0xcc - 0xb0];
  f32 unknowncc; // Inferred role: target up ratio; original member name unknown.
  f32 unknownd0; // Inferred role: target down ratio; original member name unknown.
};

static_assert(offsetof(LookAtIkSolver, unknown60) == 0x60, "");
static_assert(offsetof(LookAtIkSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(LookAtIkSolver, unknowncc) == 0xcc, "");
static_assert(offsetof(LookAtIkSolver, unknownd0) == 0xd0, "");

} // namespace fw
