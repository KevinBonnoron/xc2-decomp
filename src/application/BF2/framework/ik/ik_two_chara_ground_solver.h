#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class FootPlacementIKSolver;
struct Transform;
class IKGroundInterface;

class TwoCharaGroundSolver : public IkSolver {
public:
  static mm::mtl::RTTI m_rtti;

  TwoCharaGroundSolver();
  ~TwoCharaGroundSolver() override;
  void calcMainBodyTransform(Transform *result);
  void calcSubBodyTransform(Transform *result);
  void setEnablePlacement(bool enable);
  void solve(const UpdateInfo &info) override;
  void overwriteRaycastUp(f32 distance);
  void resetRaycastUp();
  void overwriteRaycastDown(f32 distance);
  void resetRaycastDown();
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown20; // Inferred role: main foot solvers; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> unknown58; // Inferred role: sub foot solvers; original member name unknown.
  f32 unknown90;                                                                   // Inferred role: unknown; original member name unknown.
  u32 unknown94;                                                                   // Inferred role: unknown; original member name unknown.
  u64 unknown98;                                                                   // Inferred role: unknown; original member name unknown.
  u64 unknowna0;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknowna8;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknownac;                                                                   // Inferred role: unknown; original member name unknown.
  f32 unknownb0;                                                                   // Inferred role: unknown; original member name unknown.
  u16 unknownb4;                                                                   // Inferred role: main body bone index; original member name unknown.
  u16 unknownb6;                                                                   // Inferred role: sub body bone index; original member name unknown.
  bool unknownb8;                                                                  // Inferred role: placement enabled; original member name unknown.
  bool unknownb9;                                                                  // Inferred role: unknown; original member name unknown.
  bool unknownba;                                                                  // Inferred role: main placement enabled; original member name unknown.
  bool unknownbb;                                                                  // Inferred role: sub placement enabled; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  IKGroundInterface *unknownc0; // Inferred role: ground interface; original member name unknown.
};

static_assert(offsetof(TwoCharaGroundSolver, unknown20) == 0x20, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown58) == 0x58, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown90) == 0x90, "");
static_assert(offsetof(TwoCharaGroundSolver, unknown98) == 0x98, "");
static_assert(offsetof(TwoCharaGroundSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownac) == 0xac, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb4) == 0xb4, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownb8) == 0xb8, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownbb) == 0xbb, "");
static_assert(offsetof(TwoCharaGroundSolver, unknownc0) == 0xc0, "");
static_assert(sizeof(TwoCharaGroundSolver) == 0xc8, "");

} // namespace fw
