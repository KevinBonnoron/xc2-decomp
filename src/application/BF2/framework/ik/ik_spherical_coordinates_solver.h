#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "fw/fw_param_manager.h"
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
class Reflection;

class SphericalCoordinatesIkSolver : public IkSolver {
public:
  struct AngleLimit {
    f32 limitAngleUp;
    f32 limitAngleDown;
    f32 limitAngleLeft;
    f32 limitAngleRight;

    static void createReflection(Reflection *reflection, const char *name, u32 index);
  };

  static mm::mtl::RTTI m_rtti;

  static SphericalCoordinatesIkSolver *create(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setupLimit(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  SphericalCoordinatesIkSolver();
  ~SphericalCoordinatesIkSolver() override;
  void solve(const UpdateInfo &info) override;
  void resetLimit();
  void resetLimitParam();
  const mm::mtl::RTTI *getRTTI() const override;
  virtual bool isEnable() const;

  u8 _20[0x40 - 0x20];
  f32 unknown40; // Inferred role: limit up; original member name unknown.
  f32 unknown44; // Inferred role: limit down; original member name unknown.
  f32 unknown48; // Inferred role: limit left; original member name unknown.
  f32 unknown4c; // Inferred role: limit right; original member name unknown.
  u8 _50[0x70 - 0x50];
  u16 unknown70; // Inferred role: bone index; original member name unknown.
  bool m_enable;
  ParamAdapter unknown78; // Inferred role: limit param; original member name unknown.
};

static_assert(offsetof(SphericalCoordinatesIkSolver, unknown40) == 0x40, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, unknown70) == 0x70, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, m_enable) == 0x72, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, unknown78) == 0x78, "");
static_assert(sizeof(SphericalCoordinatesIkSolver) == 0x80, "");

} // namespace fw
