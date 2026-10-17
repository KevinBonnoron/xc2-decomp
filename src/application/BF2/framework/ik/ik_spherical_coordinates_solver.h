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

class SphericalCoordinatesIkSolver : public IkSolver {
public:
  struct AngleLimit {
    f32 limitAngleUp;
    f32 limitAngleDown;
    f32 limitAngleLeft;
    f32 limitAngleRight;
  };

  static mm::mtl::RTTI m_rtti;

  static SphericalCoordinatesIkSolver *create(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame,
                                              anm::Pose &pose);
  bool setupLimit(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  SphericalCoordinatesIkSolver();
  ~SphericalCoordinatesIkSolver() override;
  void solve(const UpdateInfo &info) override;
  void resetLimit();
  void resetLimitParam();
  const mm::mtl::RTTI *getRTTI() const override;
  virtual bool isEnable() const;

  u8 _20[0x40 - 0x20];
  f32 limitUp;
  f32 limitDown;
  f32 limitLeft;
  f32 limitRight;
  u8 _50[0x70 - 0x50];
  u16 boneIndex;
  bool enabled;
  ParamAdapter limitParam;
};

static_assert(offsetof(SphericalCoordinatesIkSolver, limitUp) == 0x40, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, boneIndex) == 0x70, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, enabled) == 0x72, "");
static_assert(offsetof(SphericalCoordinatesIkSolver, limitParam) == 0x78, "");
static_assert(sizeof(SphericalCoordinatesIkSolver) == 0x80, "");

} // namespace fw
