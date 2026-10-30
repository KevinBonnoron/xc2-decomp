#include "anm/anm_foot_placement_ik_solver.h"

#include <new>

#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace anm {

FootPlacementIKSolver::FootPlacementIKSolver(const Description &desc, mm::mtl::IAllocator &allocator)
    : ReferenceObject(&allocator), m_desc(desc), unknowna0(0.0f), unknowna4(0.0f), unknownb0(desc.worldUpWS), unknownc0(0.0f), unknownc4(false), unknownd0(mm::Vec3::zero), unknowne0(mm::Vec3::zero),
      unknownf0(mm::Vec3::zero) {
  MM_ASSERT(desc.pSkeleton);
  MM_ASSERT((0 <= m_desc.hipBone) && (m_desc.hipBone < static_cast<s16>(m_desc.pSkeleton->getBoneCount())));
  MM_ASSERT((0 <= m_desc.kneeBone) && (m_desc.kneeBone < static_cast<s16>(m_desc.pSkeleton->getBoneCount())));
  MM_ASSERT((0 <= m_desc.ankleBone) && (m_desc.ankleBone < static_cast<s16>(m_desc.pSkeleton->getBoneCount())));
  MM_ASSERT(m_desc.worldUpWS.isUnit());
  MM_ASSERT(m_desc.modelUpMS.isUnit());
  MM_ASSERT(m_desc.kneeAxisLS.isUnit());
  MM_ASSERT((-1.0f <= m_desc.cosMaxKneeAngle) && (m_desc.cosMaxKneeAngle <= 1.0f));
  MM_ASSERT((-1.0f <= m_desc.cosMinKneeAngle) && (m_desc.cosMinKneeAngle <= 1.0f));
  MM_ASSERT(m_desc.cosMinKneeAngle >= m_desc.cosMaxKneeAngle);
  MM_ASSERT((m_desc.minAnkleHeightMS <= m_desc.plantedAnkleHeightMS) && (m_desc.plantedAnkleHeightMS <= m_desc.maxAnkleHeightMS));
  MM_ASSERT((m_desc.minAnkleHeightMS <= m_desc.raisedAnkleHeightMS) && (m_desc.raisedAnkleHeightMS <= m_desc.maxAnkleHeightMS));
}

FootPlacementIKSolver *FootPlacementIKSolver::create(const Description &desc, mm::mtl::IAllocator &allocator) {
  FootPlacementIKSolver *solver = new (allocator.allocate(sizeof(FootPlacementIKSolver), 16)) FootPlacementIKSolver(desc, allocator);
  solver->addRef();
  return solver;
}

bool FootPlacementIKSolver::castRay(const Input &input, const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *pPosition, mm::Vec3 *pNormal) {
  if (input.pRaycastInterface != nullptr) {
    return input.pRaycastInterface->castRay(start, end, pPosition, pNormal);
  }
  return false;
}

} // namespace anm
