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

// Only the members read by LookIkSolver are declared; the original member names are unknown.
class LookAtIkSolver : public IkFadeSolver {
public:
  static mm::mtl::RTTI m_rtti;

  static LookAtIkSolver *create(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose);
  void startTargetFade(f32 time);
  LookAtIkSolver();
  ~LookAtIkSolver() override;
  void resetLimitParam();
  void onDisable() override;
  void calcIK(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _34[0x60 - 0x34];
  mm::Vec3 unknown60; // Inferred role: front in model space; original member name unknown.
  u8 _70[0x80 - 0x70];
  f32 unknown80; // Inferred role: limit angle up; original member name unknown.
  f32 unknown84; // Inferred role: limit angle down; original member name unknown.
  f32 unknown88; // Inferred role: limit angle left; original member name unknown.
  f32 unknown8c; // Inferred role: limit angle right; original member name unknown.
  u8 _90[0xa0 - 0x90];
  mm::Vec3 unknowna0;     // Inferred role: target; original member name unknown.
  mm::Vec3 unknownb0;     // Inferred role: unknown; original member name unknown.
  ParamAdapter unknownc0; // Inferred role: limit param; original member name unknown.
  u16 unknownc8;          // Inferred role: bone index; original member name unknown.
  u8 _ca[0xcc - 0xca];
  f32 unknowncc;  // Inferred role: target up ratio; original member name unknown.
  f32 unknownd0;  // Inferred role: target down ratio; original member name unknown.
  bool unknownd4; // Inferred role: target fading; original member name unknown.
  u8 _d5[0xe0 - 0xd5];
  mm::Quat unknowne0; // Inferred role: fade start rotation; original member name unknown.
  f32 unknownf0;      // Inferred role: fade elapsed; original member name unknown.
  f32 unknownf4;      // Inferred role: fade time; original member name unknown.
};

static_assert(offsetof(LookAtIkSolver, unknown60) == 0x60, "");
static_assert(offsetof(LookAtIkSolver, unknown80) == 0x80, "");
static_assert(offsetof(LookAtIkSolver, unknown8c) == 0x8c, "");
static_assert(offsetof(LookAtIkSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(LookAtIkSolver, unknownc0) == 0xc0, "");
static_assert(offsetof(LookAtIkSolver, unknownc8) == 0xc8, "");
static_assert(offsetof(LookAtIkSolver, unknowncc) == 0xcc, "");
static_assert(offsetof(LookAtIkSolver, unknownd0) == 0xd0, "");
static_assert(offsetof(LookAtIkSolver, unknownd4) == 0xd4, "");
static_assert(offsetof(LookAtIkSolver, unknowne0) == 0xe0, "");
static_assert(offsetof(LookAtIkSolver, unknownf0) == 0xf0, "");
static_assert(offsetof(LookAtIkSolver, unknownf4) == 0xf4, "");

} // namespace fw
