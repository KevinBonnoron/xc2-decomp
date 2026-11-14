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
class ReferenceFrame;
struct Transform;
class ParamAdapter;
struct UpdateInfo;

class TwoCharaGroundSolver : public IkSolver {
public:
  // Layout evidence: gf::GfComIK::createTwoCharaGroundIK builds it on the stack (0x18 bytes).
  struct Description {
    f32 unknown00;         // Inferred role: constructor argument of GfComIK::createTwoCharaGroundIK; original member name unknown.
    u32 unknown04;         // Inferred role: foot count of the owner; original member name unknown.
    const char *unknown08; // Inferred role: first bone name of GfComIK::createTwoCharaGroundIK; original member name unknown.
    const char *unknown10; // Inferred role: second bone name of GfComIK::createTwoCharaGroundIK; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  static TwoCharaGroundSolver *create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKGroundInterface *ground);

  TwoCharaGroundSolver();
  ~TwoCharaGroundSolver() override;
  bool createImpl(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKGroundInterface *ground);
  FootPlacementIKSolver *createFootPlacementIKMain(IKFootIndex index, ParamAdapter param, const char *footName, const char *kneeName, const char *hipName, bool isMirror);
  FootPlacementIKSolver *createFootPlacementIKSub(IKFootIndex index, ParamAdapter param, const char *footName, const char *kneeName, const char *hipName, bool isMirror);
  void calcMainBodyTransform(Transform *result);
  void calcSubBodyTransform(Transform *result);
  void doPlacementFoot(const UpdateInfo &info);
  void setEnablePlacement(bool enable);
  void solve(const UpdateInfo &info) override;
  void setGroundAngle(const mm::Vec3 &angle);
  void overwriteRaycastUp(f32 distance);
  void resetRaycastUp();
  void overwriteRaycastDown(f32 distance);
  void resetRaycastDown();
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown20; // Inferred role: main foot solvers; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown58; // Inferred role: sub foot solvers; original member name unknown.
  Description unknown90; // Inferred role: copy of the description of createImpl (copied as one 0x18 byte block); original member name unknown.
  u32 unknowna8;         // Inferred role: ground fit enable; original member name unknown.
  f32 unknownac;         // Inferred role: unknown; original member name unknown.
  f32 unknownb0;         // Inferred role: unknown; original member name unknown.
  u16 unknownb4;         // Inferred role: main body bone index; original member name unknown.
  u16 unknownb6;         // Inferred role: sub body bone index; original member name unknown.
  bool unknownb8;        // Inferred role: placement enabled; original member name unknown.
  bool unknownb9;        // Inferred role: unknown; original member name unknown.
  bool unknownba;        // Inferred role: main placement enabled; original member name unknown.
  bool unknownbb;        // Inferred role: sub placement enabled; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  IKGroundInterface *unknownc0; // Inferred role: ground interface; original member name unknown.
};

static_assert(offsetof(TwoCharaGroundSolver::Description, unknown10) == 0x10, "");
static_assert(sizeof(TwoCharaGroundSolver::Description) == 0x18, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown20) == 0x20, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown58) == 0x58, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown90) == 0x90, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownac) == 0xac, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb4) == 0xb4, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb8) == 0xb8, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownbb) == 0xbb, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownc0) == 0xc0, "");
static_assert(sizeof(TwoCharaGroundSolver) == 0xc8, "");

} // namespace fw
