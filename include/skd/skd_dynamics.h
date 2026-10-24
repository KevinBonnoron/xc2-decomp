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
  const char *unknown00; // Inferred role: name; original member name unknown.
  u8 _08[0x58 - 0x08];
};

static_assert(sizeof(ResSolver) == 0x58, "");

struct ResCollisionArray;

struct ResDynamics {
  u8 _00[0x18 - 0x00];
  const ResCollisionArray *unknown18;     // Inferred role: collisions; original member name unknown.
  const anm::Array<ResSolver> *unknown20; // Inferred role: solvers; original member name unknown.
};

static_assert(offsetof(ResDynamics, unknown18) == 0x18, "");
static_assert(offsetof(ResDynamics, unknown20) == 0x20, "");

class Dynamics : public anm::ReferenceObject {
public:
  void update(f32 deltaTime);
  void notifyMovement(const mm::Vec3 &position, const mm::Quat &rotation, const mm::Vec3 &previousPosition, const mm::Quat &previousRotation);
  void resetDynamics();
  f32 getSolverBlendWeight(u32 index) const;
  void setSolverBlendWeight(u32 index, f32 weight);

  const anm::Array<ResSolver> *unknown18;      // Inferred role: res solvers; original member name unknown.
  mm::mtl::Vector<DynamicsSolver *> unknown20; // Inferred role: solvers; original member name unknown.
  anm::Pose *unknown48;                        // Inferred role: pose; original member name unknown.
  ForceInterface *unknown50;                   // Inferred role: force; original member name unknown.
  u8 _58[0x188 - 0x58];
  u32 unknown188;              // Inferred role: iteration count; original member name unknown.
  CollisionObject *unknown190; // Inferred role: collision object; original member name unknown.
  f32 unknown198;              // Inferred role: max move distance; original member name unknown.
  f32 unknown19c;              // Inferred role: max rotation; original member name unknown.
};

static_assert(offsetof(Dynamics, unknown18) == 0x18, "");
static_assert(offsetof(Dynamics, unknown20) == 0x20, "");
static_assert(offsetof(Dynamics, unknown48) == 0x48, "");
static_assert(offsetof(Dynamics, unknown50) == 0x50, "");
static_assert(offsetof(Dynamics, unknown188) == 0x188, "");
static_assert(offsetof(Dynamics, unknown190) == 0x190, "");
static_assert(offsetof(Dynamics, unknown198) == 0x198, "");
static_assert(offsetof(Dynamics, unknown19c) == 0x19c, "");

} // namespace skd
