#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Skeleton;

// Evidence: fw::FootPlacementIKSolver::solveImpl takes an anm::RaycastInterface & (1.0.0: 0x710017fe38) and
// fw::Raycaster::castRay (0x7100180508) fills the slot called through FootPlacementIKSolver::castRay (0x710094d6ec).
class RaycastInterface {
public:
  virtual ~RaycastInterface() {}
  virtual bool castRay(const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *position, mm::Vec3 *normal) = 0;
};

class FootPlacementIKSolver : public ReferenceObject {
public:
  struct Description {
    const Skeleton *pSkeleton;
    s16 hipBone;
    s16 kneeBone;
    s16 ankleBone;
    mm::Vec3 worldUpWS;
    mm::Vec3 modelUpMS;
    mm::Vec3 kneeAxisLS;
    f32 cosMaxKneeAngle;
    f32 cosMinKneeAngle;
    f32 plantedAnkleHeightMS;
    f32 raisedAnkleHeightMS;
    f32 maxAnkleHeightMS;
    f32 minAnkleHeightMS;
    f32 unknown58;      // Inferred role: rotation limit passed to TransformUtil::calcShortestRotationLimit; original member name unknown.
    mm::Vec3 unknown60; // Inferred role: offset from the ankle in its local space; original member name unknown.
    bool unknown70;     // Inferred role: foot lock enable; original member name unknown.
  };

  struct Input {
    u8 _00[0x88];
    RaycastInterface *pRaycastInterface;
    f32 unknown90; // Inferred role: raycast distance above the foot; original member name unknown.
    f32 unknown94; // Inferred role: raycast distance below the foot; original member name unknown.
    f32 onOffGain;
    f32 groundAscendGain;
    f32 groundDescendingGain;
    f32 footPlantedGain;
    f32 footRaisedGain;
    f32 footUnlockGain;
  };

  FootPlacementIKSolver(const Description &desc, mm::mtl::IAllocator &allocator);
  static FootPlacementIKSolver *create(const Description &desc, mm::mtl::IAllocator &allocator);
  bool castRay(const Input &input, const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *pPosition, mm::Vec3 *pNormal);

  Description m_desc;
  f32 unknowna0; // Inferred role: placement weight; original member name unknown.
  f32 unknowna4; // Inferred role: ground height; original member name unknown.
  u8 _a8[0xb0 - 0xa8];
  mm::Vec3 unknownb0; // Inferred role: ground normal; original member name unknown.
  f32 unknownc0;      // Inferred role: ankle height offset; original member name unknown.
  bool unknownc4;     // Inferred role: foot locked; original member name unknown.
  mm::Vec3 unknownd0; // Inferred role: locked foot position; original member name unknown.
  mm::Vec3 unknowne0; // Inferred role: locked foot target; original member name unknown.
  mm::Vec3 unknownf0; // Inferred role: foot unlock offset; original member name unknown.
};

static_assert(offsetof(FootPlacementIKSolver::Description, hipBone) == 0x08, "");
static_assert(offsetof(FootPlacementIKSolver::Description, kneeBone) == 0x0a, "");
static_assert(offsetof(FootPlacementIKSolver::Description, ankleBone) == 0x0c, "");
static_assert(offsetof(FootPlacementIKSolver::Description, worldUpWS) == 0x10, "");
static_assert(offsetof(FootPlacementIKSolver::Description, modelUpMS) == 0x20, "");
static_assert(offsetof(FootPlacementIKSolver::Description, kneeAxisLS) == 0x30, "");
static_assert(offsetof(FootPlacementIKSolver::Description, cosMaxKneeAngle) == 0x40, "");
static_assert(offsetof(FootPlacementIKSolver::Description, plantedAnkleHeightMS) == 0x48, "");
static_assert(offsetof(FootPlacementIKSolver::Description, raisedAnkleHeightMS) == 0x4c, "");
static_assert(offsetof(FootPlacementIKSolver::Description, maxAnkleHeightMS) == 0x50, "");
static_assert(offsetof(FootPlacementIKSolver::Description, minAnkleHeightMS) == 0x54, "");
static_assert(offsetof(FootPlacementIKSolver::Description, unknown58) == 0x58, "");
static_assert(offsetof(FootPlacementIKSolver::Description, unknown60) == 0x60, "");
static_assert(offsetof(FootPlacementIKSolver::Description, unknown70) == 0x70, "");
static_assert(sizeof(FootPlacementIKSolver::Description) == 0x80, "");
static_assert(offsetof(FootPlacementIKSolver::Input, pRaycastInterface) == 0x88, "");
static_assert(offsetof(FootPlacementIKSolver::Input, unknown90) == 0x90, "");
static_assert(offsetof(FootPlacementIKSolver::Input, onOffGain) == 0x98, "");
static_assert(offsetof(FootPlacementIKSolver::Input, footUnlockGain) == 0xac, "");
static_assert(offsetof(FootPlacementIKSolver, m_desc) == 0x20, "");
static_assert(offsetof(FootPlacementIKSolver, unknowna0) == 0xa0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownc0) == 0xc0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownc4) == 0xc4, "");
static_assert(offsetof(FootPlacementIKSolver, unknownd0) == 0xd0, "");
static_assert(offsetof(FootPlacementIKSolver, unknowne0) == 0xe0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownf0) == 0xf0, "");
static_assert(sizeof(FootPlacementIKSolver) == 0x100, "");

} // namespace anm
