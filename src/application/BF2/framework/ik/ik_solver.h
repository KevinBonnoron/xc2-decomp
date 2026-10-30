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

  mm::mtl::IntrusivePtr<ReferenceFrame> unknown10; // Inferred role: reference frame; original member name unknown.
  anm::Pose *unknown18;                            // Inferred role: pose; original member name unknown.
};

static_assert(offsetof(IkSolver, unknown10) == 0x10, "");
static_assert(offsetof(IkSolver, unknown18) == 0x18, "");

class IkFadeSolver : public IkSolver {
public:
  // Inferred role: fade state; original type name unknown.
  enum unknown002 {
    unknown002_0 = 0, // Inferred role: none; original name unknown.
    unknown002_1 = 1, // Inferred role: in; original name unknown.
    unknown002_2 = 2, // Inferred role: out; original name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  IkFadeSolver();
  void solve(const UpdateInfo &info) override;
  static f32 calcBezier(f32 t, f32 start, f32 end);
  void fadeIn(f32 time);
  void fadeOut(f32 time);
  const mm::mtl::RTTI *getRTTI() const override;
  virtual bool isEnable() const { return unknown20 > 0.0f; }
  virtual void onEnable() {}
  virtual void onDisable() {}
  virtual void calcIK(const UpdateInfo &info) = 0;

  f32 unknown20;        // Inferred role: weight; original member name unknown.
  unknown002 unknown24; // Inferred role: fade state; original member name unknown.
  f32 unknown28;        // Inferred role: fade time; original member name unknown.
  f32 unknown2c;        // Inferred role: fade elapsed; original member name unknown.
  f32 unknown30;        // Inferred role: fade start weight; original member name unknown.
};

static_assert(offsetof(IkFadeSolver, unknown20) == 0x20, "");
static_assert(offsetof(IkFadeSolver, unknown30) == 0x30, "");

} // namespace fw
