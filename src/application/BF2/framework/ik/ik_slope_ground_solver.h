#pragma once
#include <stddef.h>

#include "framework/ik/ik_foot_placement_solver.h" // IWYU pragma: keep
#include "framework/ik/ik_solver.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class IKGroundInterface;

class SlopeGroundSolver : public IkSolver {
public:
  static mm::mtl::RTTI m_rtti;

  ~SlopeGroundSolver() override;
  void setEnablePlacement(bool enable);
  void solve(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  f32 unknown20;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown24;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown28;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown2c;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown30;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown34;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown38;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown3c;                                                                   // Inferred role: unknown; original member name unknown.
  mm::Quat unknown40;                                                              // Inferred role: unknown; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown50; // Inferred role: foot solvers; original member name unknown.
  bool unknown88;                                                                  // Inferred role: unknown; original member name unknown.
  bool unknown89;                                                                  // Inferred role: placement enabled; original member name unknown.
  u8 _8a[0x90 - 0x8a];
  IKGroundInterface *unknown90; // Inferred role: ground interface; original member name unknown.
};

static_assert(offsetof(SlopeGroundSolver, unknown20) == 0x20, "");
static_assert(offsetof(SlopeGroundSolver, unknown3c) == 0x3c, "");
static_assert(offsetof(SlopeGroundSolver, unknown40) == 0x40, "");
static_assert(offsetof(SlopeGroundSolver, unknown50) == 0x50, "");
static_assert(offsetof(SlopeGroundSolver, unknown88) == 0x88, "");
static_assert(offsetof(SlopeGroundSolver, unknown89) == 0x89, "");
static_assert(offsetof(SlopeGroundSolver, unknown90) == 0x90, "");

} // namespace fw
