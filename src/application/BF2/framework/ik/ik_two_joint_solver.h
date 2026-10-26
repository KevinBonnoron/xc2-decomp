#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class TwoJointIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  ~TwoJointIkSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _34[0x40 - 0x34];
  u16 unknown40[4];   // Inferred role: bone indices; original member name unknown.
  u16 unknown48;      // Inferred role: bone index; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: unknown; original member name unknown.
  f32 unknown60;      // Inferred role: unknown; original member name unknown.
  u32 unknown64;      // Inferred role: unknown; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: unknown; original member name unknown.
  mm::Quat unknown80; // Inferred role: unknown; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: unknown; original member name unknown.
  mm::Quat unknowna0; // Inferred role: unknown; original member name unknown.
  u16 unknownb0;      // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(TwoJointIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(TwoJointIkSolver, unknown48) == 0x48, "");
static_assert(offsetof(TwoJointIkSolver, unknown50) == 0x50, "");
static_assert(offsetof(TwoJointIkSolver, unknown60) == 0x60, "");
static_assert(offsetof(TwoJointIkSolver, unknown64) == 0x64, "");
static_assert(offsetof(TwoJointIkSolver, unknown70) == 0x70, "");
static_assert(offsetof(TwoJointIkSolver, unknown80) == 0x80, "");
static_assert(offsetof(TwoJointIkSolver, unknown90) == 0x90, "");
static_assert(offsetof(TwoJointIkSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(TwoJointIkSolver, unknownb0) == 0xb0, "");

} // namespace fw
