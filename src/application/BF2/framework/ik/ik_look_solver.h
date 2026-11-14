#pragma once
#include <stddef.h>

#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_solver.h"
#include "framework/ik/ik_spine_solver.h"
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

class LookIkSolver : public IkSolver {
public:
  struct Description {
    Description() : unknown00(0.5f), unknown04(0.5f) {}

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

  // Inferred helper: fade state of the look at solver, of the spine solver when there is none; original name unknown.
  // Evidence: gf::pc::TargetIKPlugin::update (1.0.0: 0x710057c5d0 and 0x710057c640) reads it twice, each time behind one
  // IntrusivePtr::operator-> check of the look solver, and gf::GfFieldLookIk::updateIkSolver<fw::LookIkSolver>
  // (0x7100341e30..0x7100341e48) reads the same chain where its LookAtIkSolver instantiation (0x7100341f2c) reads unknown24.
  IkFadeSolver::unknown002 unknown001() const {
    if (unknown28.get() != nullptr) {
      return unknown28.get()->unknown24;
    }
    if (unknown20.get() != nullptr) {
      return unknown20.get()->unknown24;
    }
    return IkFadeSolver::unknown002_0;
  }

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
