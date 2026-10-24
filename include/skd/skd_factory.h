#pragma once
#include "anm/anm_array-inl.h"

namespace anm {
class Pose;
} // namespace anm

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace skd {

class CollisionObject;
class Dynamics;
class ForceInterface;
struct ResCollisionArray;
struct ResSolver;

class Factory {
public:
  static CollisionObject *createColObject(const ResCollisionArray *collisions, anm::Pose &pose, mm::mtl::IAllocator *allocator);
  static Dynamics *createDynamics(CollisionObject *collisionObject, const anm::Array<ResSolver> &solvers, anm::Pose &pose, ForceInterface *force, mm::mtl::IAllocator *allocator);
};

} // namespace skd
