#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace anm {
class Pose;
} // namespace anm

namespace fw {

class ReferenceFrame;

class SpineRotateIKSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static SpineRotateIKSolver *create(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setupLimit(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  SpineRotateIKSolver();
  ~SpineRotateIKSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _34[0x38 - 0x34];
  ParamAdapter unknown38; // Inferred role: limit param; original member name unknown.
  u16 unknown40;          // Inferred role: bone index; original member name unknown.
  u16 unknown42;          // Inferred role: end bone index; original member name unknown.
  u32 unknown44[2];       // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(SpineRotateIKSolver, unknown38) == 0x38, "");
static_assert(offsetof(SpineRotateIKSolver, unknown40) == 0x40, "");
static_assert(offsetof(SpineRotateIKSolver, unknown42) == 0x42, "");
static_assert(offsetof(SpineRotateIKSolver, unknown44) == 0x44, "");

} // namespace fw
