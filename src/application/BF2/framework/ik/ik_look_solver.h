#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
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

class ParamAdapter;
class ReferenceFrame;
class LookAtIkSolver;
class SpineIkSolver;

class LookIkSolver : public IkSolver {
public:
  struct Description {
    Description(f32 fadeOutTime, f32 fadeInTime) : unknown00(fadeOutTime), unknown04(fadeInTime) {}

    f32 unknown00; // Inferred role: spine fade out time; original member name unknown.
    f32 unknown04; // Inferred role: spine fade in time; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  static LookIkSolver *create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool createImpl(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  LookIkSolver();
  ~LookIkSolver() override;
  LookAtIkSolver *createLookAtIK(const ParamAdapter &param, const char *boneName);
  SpineIkSolver *createSpineIK(const ParamAdapter &param, const char *boneName, const char *endBoneName);
  void fadeIn(f32 time);
  void fadeOut(f32 time);
  void setTarget(const mm::Vec3 &target);
  void startTargetFade(f32 time);
  void setEnableSpine(bool enable);
  void setFrontMS(const mm::Vec3 &front);
  void setTargetUpRatio(f32 ratio);
  void setTargetDownRatio(f32 ratio);
  void solve(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  virtual bool isEnable() const;

  mm::mtl::IntrusivePtr<SpineIkSolver> unknown20;  // Inferred role: spine solver; original member name unknown.
  mm::mtl::IntrusivePtr<LookAtIkSolver> unknown28; // Inferred role: look at solver; original member name unknown.
  Description unknown30;                           // Inferred role: spine fade times; original member name unknown.
  bool unknown38;                                  // Inferred role: spine enabled; original member name unknown.
};

static_assert(offsetof(LookIkSolver, unknown20) == 0x20, "");
static_assert(offsetof(LookIkSolver, unknown28) == 0x28, "");
static_assert(offsetof(LookIkSolver, unknown30) == 0x30, "");
static_assert(offsetof(LookIkSolver, unknown38) == 0x38, "");
static_assert(sizeof(LookIkSolver) == 0x40, "");

} // namespace fw
