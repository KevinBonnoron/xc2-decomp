// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/skdlib/src/skdlib/composite/skd_calc_util.cpp.
#include "anm/anm_array-inl.h"
#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/vector.h"
#include "skd/skd_dynamics.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace skd {
class CollionArray;

void CalcUtil::applyAccel(mm::mtl::Vector<mm::Vec3> &forces, NodeArray *nodes) {
  u32 count = nodes->unknown10.size();
  for (u32 i = 0; i < count; i++) {
    const ResNode &resNode = (*nodes->unknown00)[i];
    Node &node = nodes->unknown10[i];
    node.unknown60 = forces[i] * (1.0f / resNode.unknown20);
  }
}

void CalcUtil::detectCollision(const CollionArray &collisions, NodeArray *nodes) {
  const anm::Array<ResNodeCollision> &nodeCollisions = *nodes->unknown08;
  const ResNodeCollision *end = nodeCollisions.m_pElements + nodeCollisions.size();
  for (const ResNodeCollision *it = nodeCollisions.m_pElements; it != end; it++) {
    const ResNodeCollision &nodeCollision = *it;
    // The game indexes both resource nodes (with the anm::Array asserts) and ignores them, then passes mask 0.
    MM_VERIFY((*nodes->unknown00)[nodeCollision.unknown00]);
    MM_VERIFY((*nodes->unknown00)[nodeCollision.unknown02]);
    detectCollisionSpheres(nodeCollision, collisions, 0, nodes);
    detectCollisionCapsules(nodeCollision, collisions, 0, nodes);
    detectCollisionPlanes(nodeCollision, collisions, 0, nodes);
  }
}

void CalcUtil::writeBackNode(anm::Pose &pose, NodeArray *nodes) {
  const anm::Skeleton *skeleton = pose.unknown18;
  u32 count = nodes->unknown10.size();
  for (u32 i = 0; i < count; i++) {
    Node &node = nodes->unknown10[i];
    u16 bone = node.unknowna0;
    node.unknown20 = node.unknown00;
    node.unknown00 = node.unknown50;
    u16 modelBone = skeleton->unknown20[bone];
    if (modelBone != anm::Skeleton::INVALID_BONE) {
      const anm::QsTransform &transform = pose.getBoneModelSpace(modelBone);
      node.unknown30 = mm::Vec3(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
      node.unknown40 = transform.unknown10;
    }
  }
}

void CalcUtil::blendNode(f32 weight, NodeArray *nodes) {
  u32 count = nodes->unknown10.size();
  for (u32 i = 0; i < count; i++) {
    Node &node = nodes->unknown10[i];
    node.unknown50 = node.unknown50 * (1.0f - weight) + node.unknown70 * weight;
  }
}

void CalcUtil::applyStickConstraints(const anm::Array<ResStickConstraint> &constraints, NodeArray *nodes) {
  u32 count = constraints.size();
  for (u32 i = 0; i < count; i++) {
    const ResStickConstraint &constraint = constraints[i];
    limitCone(constraint, constraint.unknown10, nodes);
  }
  for (u32 i = 0; i < count; i++) {
    limitDistance(constraints[i], nodes);
  }
}

void CalcUtil::applyHingeConstraints(const anm::Array<ResHingeConstraint> &constraints, NodeArray *nodes) {
  u32 count = constraints.size();
  for (u32 i = 0; i < count; i++) {
    limitHinge(constraints[i], nodes);
  }
  for (u32 i = 0; i < count; i++) {
    limitDistance(constraints[i], nodes);
  }
}

NodeArray::NodeArray(mm::mtl::IAllocator *allocator, const anm::Array<ResNode> &resNodes, const anm::Array<ResNodeCollision> &resNodeCollisions)
    : unknown00(&resNodes), unknown08(&resNodeCollisions), unknown10(allocator) {
  unknown10.resize(resNodes.size());
}

} // namespace skd
