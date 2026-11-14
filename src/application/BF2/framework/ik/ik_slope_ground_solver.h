#pragma once
#include <stddef.h>

#include "framework/ik/ik_foot_placement_solver.h" // IWYU pragma: keep
#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_solver.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/fixed_vector.h"
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
struct UpdateInfo;

class SlopeGroundSolver : public IkSolver {
public:
  static mm::mtl::RTTI m_rtti;

  // Layout evidence: gf::GfComIK::createSlopeGroundIK builds it on the stack (0x20 bytes); the default values are the ones the SlopeGroundSolver constructor
  // (0x7100184174) writes at 0x20..0x3c, where createImpl (0x7100183fe8) copies the description.
  struct Description {
    Description() : unknown00(0.5f), unknown04(0.5f), unknown08(12.0f), unknown0c(0.5f), unknown10(8.0f), unknown14(1.5707964f), unknown18(1.5707964f), unknown1c(0) {}

    f32 unknown00; // Inferred role: unknown, 0.5 by default; original member name unknown.
    f32 unknown04; // Inferred role: unknown, 0.5 by default; original member name unknown.
    f32 unknown08; // Inferred role: unknown, 12.0 by default; original member name unknown.
    f32 unknown0c; // Inferred role: unknown, 0.5 by default; original member name unknown.
    f32 unknown10; // Inferred role: unknown, 8.0 by default; original member name unknown.
    f32 unknown14; // Inferred role: first argument of GfComIK::createSlopeGroundIK, a quarter turn by default; original member name unknown.
    f32 unknown18; // Inferred role: second argument of GfComIK::createSlopeGroundIK, a quarter turn by default; original member name unknown.
    u32 unknown1c; // Inferred role: foot count of the owner; original member name unknown.
  };

  static SlopeGroundSolver *create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKGroundInterface *ground);

  ~SlopeGroundSolver() override;
  FootPlacementIKSolver *createFootPlacementIK(IKFootIndex index, ParamAdapter &param, const char *footName, const char *kneeName, const char *hipName, bool isMirror);
  void setEnablePlacement(bool enable);
  void solve(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void slopeBody(const UpdateInfo &info);
  void solveFoot(const UpdateInfo &info);

  Description unknown20;                                                           // Inferred role: description copied by createImpl; original member name unknown.
  mm::Quat unknown40;                                                              // Inferred role: unknown; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown50; // Inferred role: foot solvers; original member name unknown.
  bool unknown88;                                                                  // Inferred role: unknown; original member name unknown.
  bool unknown89;                                                                  // Inferred role: placement enabled; original member name unknown.
  u8 _8a[0x90 - 0x8a];
  IKGroundInterface *unknown90; // Inferred role: ground interface; original member name unknown.
};

static_assert(offsetof(SlopeGroundSolver::Description, unknown14) == 0x14, "");
static_assert(offsetof(SlopeGroundSolver::Description, unknown1c) == 0x1c, "");
static_assert(sizeof(SlopeGroundSolver::Description) == 0x20, "");
static_assert(offsetof(SlopeGroundSolver, unknown20) == 0x20, "");
static_assert(offsetof(SlopeGroundSolver, unknown20.unknown1c) == 0x3c, "");
static_assert(offsetof(SlopeGroundSolver, unknown40) == 0x40, "");
static_assert(offsetof(SlopeGroundSolver, unknown50) == 0x50, "");
static_assert(offsetof(SlopeGroundSolver, unknown88) == 0x88, "");
static_assert(offsetof(SlopeGroundSolver, unknown89) == 0x89, "");
static_assert(offsetof(SlopeGroundSolver, unknown90) == 0x90, "");

} // namespace fw
