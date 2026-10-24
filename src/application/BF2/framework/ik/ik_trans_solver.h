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

class TransLocalIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static TransLocalIkSolver *create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  TransLocalIkSolver();
  ~TransLocalIkSolver() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::Vec3 unknown40; // Inferred role: translation; original member name unknown.
  u16 unknown50;      // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(TransLocalIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(TransLocalIkSolver, unknown50) == 0x50, "");
static_assert(sizeof(TransLocalIkSolver) == 0x60, "");

} // namespace fw
