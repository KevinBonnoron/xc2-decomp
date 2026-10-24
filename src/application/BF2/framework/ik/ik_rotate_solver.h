#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
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

class RotateIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static RotateIkSolver *create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  RotateIkSolver();
  ~RotateIkSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::Vec3 unknown40; // Inferred role: rotation; original member name unknown.
  u16 unknown50;      // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(RotateIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(RotateIkSolver, unknown50) == 0x50, "");
static_assert(sizeof(RotateIkSolver) == 0x60, "");

class RotateLocalIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static RotateLocalIkSolver *create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  RotateLocalIkSolver();
  ~RotateLocalIkSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::Vec3 unknown40; // Inferred role: rotation; original member name unknown.
  u16 unknown50;      // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(RotateLocalIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(RotateLocalIkSolver, unknown50) == 0x50, "");
static_assert(sizeof(RotateLocalIkSolver) == 0x60, "");

} // namespace fw
