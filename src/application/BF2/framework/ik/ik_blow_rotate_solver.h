#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "mm_math/mm_quat.h"
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

class BlowRotateIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static BlowRotateIkSolver *create(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, u32 boneIndex);
  bool setup(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  BlowRotateIkSolver();
  ~BlowRotateIkSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::Quat unknown40; // Inferred role: rotation; original member name unknown.
  u16 unknown50;      // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(BlowRotateIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(BlowRotateIkSolver, unknown50) == 0x50, "");
static_assert(sizeof(BlowRotateIkSolver) == 0x60, "");

} // namespace fw
