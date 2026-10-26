#pragma once
#include <stddef.h>

#include "framework/ik/ik_solver.h"
#include "fw/fw_param_manager.h"
#include "mm_math/mm_quat.h"
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

class SpineIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static SpineIkSolver *create(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  bool setupLimit(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  SpineIkSolver();
  void resetLimit();
  void startTargetFade(f32 time);
  void onDisable() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u16 unknown34;          // Inferred role: bone index; original member name unknown.
  u16 unknown36;          // Inferred role: end bone index; original member name unknown.
  f32 unknown38;          // Inferred role: limit; original member name unknown.
  f32 unknown3c;          // Inferred role: limit; original member name unknown.
  f32 unknown40;          // Inferred role: limit; original member name unknown.
  f32 unknown44;          // Inferred role: limit; original member name unknown.
  f32 unknown48;          // Inferred role: limit; original member name unknown.
  f32 unknown4c;          // Inferred role: limit; original member name unknown.
  mm::Vec3 unknown50;     // Inferred role: target; original member name unknown.
  mm::Vec3 unknown60;     // Inferred role: unknown; original member name unknown.
  mm::Vec3 unknown70;     // Inferred role: front in model space; original member name unknown.
  ParamAdapter unknown80; // Inferred role: limit param; original member name unknown.
  bool unknown88;         // Inferred role: target fading; original member name unknown.
  mm::Quat unknown90;     // Inferred role: fade start rotation; original member name unknown.
  mm::Quat unknowna0;     // Inferred role: fade start end rotation; original member name unknown.
  f32 unknownb0;          // Inferred role: fade elapsed; original member name unknown.
  f32 unknownb4;          // Inferred role: fade time; original member name unknown.
  u32 unknownb8[2];       // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(SpineIkSolver, unknown34) == 0x34, "");
static_assert(offsetof(SpineIkSolver, unknown36) == 0x36, "");
static_assert(offsetof(SpineIkSolver, unknown38) == 0x38, "");
static_assert(offsetof(SpineIkSolver, unknown4c) == 0x4c, "");
static_assert(offsetof(SpineIkSolver, unknown50) == 0x50, "");
static_assert(offsetof(SpineIkSolver, unknown60) == 0x60, "");
static_assert(offsetof(SpineIkSolver, unknown70) == 0x70, "");
static_assert(offsetof(SpineIkSolver, unknown80) == 0x80, "");
static_assert(offsetof(SpineIkSolver, unknown88) == 0x88, "");
static_assert(offsetof(SpineIkSolver, unknown90) == 0x90, "");
static_assert(offsetof(SpineIkSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(SpineIkSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(SpineIkSolver, unknownb4) == 0xb4, "");
static_assert(offsetof(SpineIkSolver, unknownb8) == 0xb8, "");

} // namespace fw
