#pragma once
#include <stddef.h>

#include "anm/anm_foot_placement_ik_solver.h"
#include "anm/anm_qs_transform.h"
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
class IKFootGroundInterface;
class ReferenceFrame;
class Reflection;

class FootPlacementIKSolver : public IkSolver {
public:
  struct Param {
    f32 unknown00; // Reflected as "maxAnkleHeight"; original member name unknown.
    f32 unknown04; // Reflected as "raisedAnkleOffset"; original member name unknown.
    f32 unknown08; // Reflected as "plantedAnkleOffset"; original member name unknown.

    static void createReflection(Reflection *reflection, const char *name, u32 index);
  };

  // Evidence: the 0x30 bytes copied to this + 0x28 by createImpl (1.0.0: 0x710017f338), the defaults stored by the constructor (0x710017fb90)
  // and the stack object built by PlacementGroundSolver::createFootPlacementIK (0x7100182a10).
  struct Description {
    Description() : unknown00(""), unknown08(""), unknown10(""), unknown18(180.0f), unknown1c(20.0f), unknown20(0.1f), unknown24(false), unknown25(false), unknown28() {}

    const char *unknown00;  // Inferred role: foot bone name; original member name unknown.
    const char *unknown08;  // Inferred role: second bone name; original member name unknown.
    const char *unknown10;  // Inferred role: third bone name; original member name unknown.
    f32 unknown18;          // Inferred role: angle in degrees; original member name unknown.
    f32 unknown1c;          // Inferred role: angle in degrees; original member name unknown.
    f32 unknown20;          // Inferred role: distance; original member name unknown.
    bool unknown24;         // Inferred role: unknown; original member name unknown.
    bool unknown25;         // Inferred role: mirror flag; original member name unknown.
    ParamAdapter unknown28; // Inferred role: foot placement param; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  FootPlacementIKSolver();
  static FootPlacementIKSolver *create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKFootGroundInterface *ground);
  bool createImpl(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKFootGroundInterface *ground);
  ~FootPlacementIKSolver() override;
  void solve(const UpdateInfo &info) override;
  // Inferred helper: forces the raycast up distance; original name unknown.
  void unknown001(f32 distance) {
    unknowna0 |= 4;
    unknowna4 = distance;
  }

  // Inferred helper: forces the raycast down distance; original name unknown.
  void unknown002(f32 distance) {
    unknowna0 |= 8;
    unknowna8 = distance;
  }

  // Inferred helper: sets or clears the placement enable flag; original name unknown.
  void unknown003(bool enable) {
    if (enable) {
      unknowna0 |= 1;
    } else {
      unknowna0 &= ~1;
    }
  }

  f32 getRaycastDown() const;
  void setGroundAngle(const mm::Vec3 &angle);
  void drawDebug();
  const mm::mtl::RTTI *getRTTI() const override;

  anm::FootPlacementIKSolver *unknown20; // Inferred role: anim foot placement solver; original member name unknown.
  Description unknown28;                 // Inferred role: description copy; original member name unknown.
  u16 unknown58;                         // Inferred role: foot bone index; original member name unknown.
  u8 _5a[0x60 - 0x5a];
  mm::Vec3 unknown60;         // Inferred role: foot position; original member name unknown.
  anm::QsTransform unknown70; // Inferred role: foot bone transform; original member name unknown.
  u32 unknowna0;              // Inferred role: flags; original member name unknown.
  f32 unknowna4;              // Inferred role: raycast up distance; original member name unknown.
  f32 unknowna8;              // Inferred role: raycast down distance; original member name unknown.
  u8 _ac[0xb0 - 0xac];
  mm::Quat unknownb0;               // Inferred role: ground angle; original member name unknown.
  mm::Quat unknownc0;               // Inferred role: unknown; original member name unknown.
  IKFootGroundInterface *unknownd0; // Inferred role: foot ground interface; original member name unknown.
  u8 _d8[0xe0 - 0xd8];
};

static_assert(offsetof(FootPlacementIKSolver, unknown20) == 0x20, "");
static_assert(offsetof(FootPlacementIKSolver, unknown28) == 0x28, "");
static_assert(offsetof(FootPlacementIKSolver::Description, unknown28) == 0x28, "");
static_assert(sizeof(FootPlacementIKSolver::Description) == 0x30, "");
static_assert(offsetof(FootPlacementIKSolver, unknown58) == 0x58, "");
static_assert(offsetof(FootPlacementIKSolver, unknown60) == 0x60, "");
static_assert(offsetof(FootPlacementIKSolver, unknown70) == 0x70, "");
static_assert(offsetof(FootPlacementIKSolver, unknowna4) == 0xa4, "");
static_assert(offsetof(FootPlacementIKSolver, unknowna8) == 0xa8, "");
static_assert(offsetof(FootPlacementIKSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownc0) == 0xc0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownd0) == 0xd0, "");
static_assert(sizeof(FootPlacementIKSolver) == 0xe0, "");

void buildDescFromParam(ParamAdapter &param, anm::FootPlacementIKSolver::Description *description);

} // namespace fw
