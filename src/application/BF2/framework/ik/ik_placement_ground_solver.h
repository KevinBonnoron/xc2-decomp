#pragma once
#include <stddef.h>

#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_solver.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {
class Pose;
} // namespace anm

namespace mm {
struct Vec3;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class FootPlacementIKSolver;
class ParamAdapter;
class ReferenceFrame;

class PlacementGroundSolver : public IkSolver {
public:
  // Layout evidence: gf::GfComIK::createPlacementGroundIK builds it on the stack (8 bytes).
  struct Description {
    f32 unknown00; // Inferred role: constructor argument of GfComIK::createPlacementGroundIK; original member name unknown.
    u32 unknown04; // Inferred role: foot count of the owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  static PlacementGroundSolver *create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKGroundInterface *ground);

  PlacementGroundSolver();
  ~PlacementGroundSolver() override;
  FootPlacementIKSolver *createFootPlacementIK(IKFootIndex index, ParamAdapter &param, const char *footName, const char *kneeName, const char *hipName, bool isMirror);
  void setEnablePlacement(bool enable);
  void solve(const UpdateInfo &info) override;
  void setGroundAngle(const mm::Vec3 &angle);
  void overwriteRaycastUp(f32 distance);
  void resetRaycastUp();
  void overwriteRaycastDown(f32 distance);
  void resetRaycastDown();
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown20; // Inferred role: foot solvers; original member name unknown.
  f32 unknown58;                                                                   // Inferred role: unknown; original member name unknown.
  u32 unknown5c;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknown60;                                                                   // Inferred role: ground offset; original member name unknown.
  bool unknown64;                                                                  // Inferred role: placement enabled; original member name unknown.
  bool unknown65;                                                                  // Inferred role: unknown; original member name unknown.
  u8 _66[0x68 - 0x66];
  IKGroundInterface *unknown68; // Inferred role: ground interface; original member name unknown.
};

static_assert(offsetof(PlacementGroundSolver::Description, unknown04) == 0x4, "");
static_assert(sizeof(PlacementGroundSolver::Description) == 0x8, "");

static_assert(offsetof(PlacementGroundSolver, unknown20) == 0x20, "");
static_assert(offsetof(PlacementGroundSolver, unknown58) == 0x58, "");
static_assert(offsetof(PlacementGroundSolver, unknown5c) == 0x5c, "");
static_assert(offsetof(PlacementGroundSolver, unknown60) == 0x60, "");
static_assert(offsetof(PlacementGroundSolver, unknown64) == 0x64, "");
static_assert(offsetof(PlacementGroundSolver, unknown68) == 0x68, "");
static_assert(sizeof(PlacementGroundSolver) == 0x70, "");

} // namespace fw
