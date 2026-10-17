#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class Pose;
} // namespace anm

namespace mm {
struct Quat;
struct Vec3;
} // namespace mm

namespace skd {

class CollisionObject;
class DynamicsSolver;
class ForceInterface;

struct ResSolver {
  const char *name;
  u8 _08[0x58 - 0x08];
};

static_assert(sizeof(ResSolver) == 0x58, "");

struct ResCollisionArray;

struct ResDynamics {
  u8 _00[0x18 - 0x00];
  const ResCollisionArray *collisions;
  const anm::Array<ResSolver> *solvers;
};

static_assert(offsetof(ResDynamics, collisions) == 0x18, "");
static_assert(offsetof(ResDynamics, solvers) == 0x20, "");

class Dynamics : public anm::ReferenceObject {
public:
  void update(f32 deltaTime);
  void notifyMovement(const mm::Vec3 &position, const mm::Quat &rotation, const mm::Vec3 &previousPosition, const mm::Quat &previousRotation);
  void resetDynamics();
  f32 getSolverBlendWeight(u32 index) const;
  void setSolverBlendWeight(u32 index, f32 weight);

  const anm::Array<ResSolver> *resSolvers;
  mm::mtl::Vector<DynamicsSolver *> solvers;
  anm::Pose *pose;
  ForceInterface *force;
  u8 _58[0x188 - 0x58];
  u32 iterationCount;
  CollisionObject *collisionObject;
  f32 maxMoveDistance;
  f32 maxRotation;
};

static_assert(offsetof(Dynamics, resSolvers) == 0x18, "");
static_assert(offsetof(Dynamics, solvers) == 0x20, "");
static_assert(offsetof(Dynamics, pose) == 0x48, "");
static_assert(offsetof(Dynamics, force) == 0x50, "");
static_assert(offsetof(Dynamics, iterationCount) == 0x188, "");
static_assert(offsetof(Dynamics, collisionObject) == 0x190, "");
static_assert(offsetof(Dynamics, maxMoveDistance) == 0x198, "");
static_assert(offsetof(Dynamics, maxRotation) == 0x19c, "");

} // namespace skd
