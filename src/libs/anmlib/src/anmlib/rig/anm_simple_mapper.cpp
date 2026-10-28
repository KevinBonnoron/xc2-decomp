#include "anm/anm_simple_mapper.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_skeleton.h"

namespace anm {

SimpleMapper::SimpleMapper(const Skeleton &skeletonA, const Skeleton &skeletonB, mm::mtl::IAllocator *pAllocator)
    : ReferenceObject(pAllocator), m_pSkeletonA(&skeletonA), m_pSkeletonB(&skeletonB), unknown28(pAllocator), unknown50(pAllocator) {
  m_pSkeletonA->addRef();
  m_pSkeletonB->addRef();
  u32 boneCount = skeletonB.getBoneCount();
  unknown28.resize(boneCount);
  unknown28[0] = 0;
  for (u32 i = 1; i < boneCount; i++) {
    const char *name = skeletonB.unknown001(i).unknown00;
    u16 bone = Skeleton::INVALID_BONE;
    if (name != nullptr) {
      bone = skeletonA.getBoneID(name);
    }
    unknown28[i] = bone;
  }
  u32 slotCount = skeletonB.unknown50.size();
  unknown50.resize(slotCount);
  for (u32 i = 0; i < slotCount; i++) {
    mm::mtl::Vector<s16> &table = unknown50[i];
    table.setAllocator(pAllocator);
    const ExtraTruckSlot &slot = skeletonB.unknown50[i];
    table.resize(slot.unknown18.size(), -1);
    s16 slotId = skeletonA.getExtraTruckSlotID(slot.unknown00);
    if (slotId != -1) {
      const ExtraTruckSlot &slotA = skeletonA.unknown50[slotId];
      for (u32 j = 0; j < slot.unknown18.size(); j++) {
        s16 truck = slotA.getTruckID(slot.unknown001(j));
        if (truck != -1) {
          table[j] = truck;
        }
      }
    }
  }
}

SimpleMapper::~SimpleMapper() {
  unknown001(m_pSkeletonA);
  unknown001(m_pSkeletonB);
}

} // namespace anm
