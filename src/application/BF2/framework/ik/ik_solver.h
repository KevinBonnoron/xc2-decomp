#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
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

class ReferenceFrame;
struct UpdateInfo;

class IkSolver : public mm::mtl::ReferenceObject {
public:
  static mm::mtl::RTTI m_rtti;

  IkSolver();
  void unbind();
  ~IkSolver() override;
  void bind(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void solve(const UpdateInfo &info) = 0;

  mm::mtl::IntrusivePtr<ReferenceFrame> referenceFrame;
  anm::Pose *pose;
};

static_assert(offsetof(IkSolver, referenceFrame) == 0x10, "");
static_assert(offsetof(IkSolver, pose) == 0x18, "");

class IkFadeSolver : public IkSolver {
public:
  enum FadeState {
    FADE_STATE_NONE = 0,
    FADE_STATE_IN = 1,
    FADE_STATE_OUT = 2,
  };

  static mm::mtl::RTTI m_rtti;

  IkFadeSolver();
  void solve(const UpdateInfo &info) override;
  static f32 calcBezier(f32 t, f32 start, f32 end);
  void fadeIn(f32 time);
  void fadeOut(f32 time);
  const mm::mtl::RTTI *getRTTI() const override;
  virtual bool isEnable() const { return weight > 0.0f; }
  virtual void onEnable() {}
  virtual void onDisable() {}
  virtual void calcIK(const UpdateInfo &info) = 0;

  f32 weight;
  FadeState fadeState;
  f32 fadeTime;
  f32 fadeElapsed;
  f32 fadeStartWeight;
};

static_assert(offsetof(IkFadeSolver, weight) == 0x20, "");
static_assert(offsetof(IkFadeSolver, fadeStartWeight) == 0x30, "");

} // namespace fw
