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
class Reflection;

class SpineRotateIKSolver : public IkFadeSolver {
public:
  struct Param {
    f32 minYaw0;
    f32 maxYaw0;
    f32 minPitch0;
    f32 maxPitch0;
    f32 minYaw1;
    f32 maxYaw1;
    f32 minPitch1;
    f32 maxPitch1;
    f32 ratio;

    static void createReflection(Reflection *reflection, const char *name, u32 index);
  };

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
  // Inferred role: pitch and yaw angles in degrees, scaled by the ratio of the limit param and clamped by calcIK to minPitch0..maxPitch0 (1.0.0: 0x7100187584) and minYaw0..maxYaw0
  // (0x71001875cc); original member name unknown. Evidence: both are f32 in calcIK, and StateUtil::setSpineRotateAngles (0x7100572d88) stores its two f32 arguments there (stp s9, s8 at
  // 0x7100572e40).
  f32 unknown44[2];
};

static_assert(offsetof(SpineRotateIKSolver, unknown38) == 0x38, "");
static_assert(offsetof(SpineRotateIKSolver, unknown40) == 0x40, "");
static_assert(offsetof(SpineRotateIKSolver, unknown42) == 0x42, "");
static_assert(offsetof(SpineRotateIKSolver, unknown44) == 0x44, "");

} // namespace fw
