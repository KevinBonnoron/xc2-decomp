#include "anm/anm_blender.h"

#include <new>

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/allocator.h"

namespace anm {

Blender::Blender(const Skeleton *skeleton, mm::mtl::IAllocator *allocator) : ReferenceObject(allocator), unknown18(allocator), unknown40(skeleton) {
  if (unknown40 == nullptr) {
    mm::MMStdBase::mmAssert("m_pSkeleton", __FILE__, __LINE__);
  }
  unknown40->addRef();
  unknown18.reserve(8);
  u32 boneCount = unknown40->unknown30.size();
  unknown48 = new (allocator->allocate(sizeof(Work), 8)) Work;
  u32 truckCount = 0;
  u32 slotCount = unknown40->unknown50.size();
  for (u32 i = 0; i < slotCount; i++) {
    u32 count = unknown40->unknown002(i).unknown18.size();
    if (truckCount <= count) {
      truckCount = count;
    }
  }
  unknown48->unknown50.setAllocator(allocator);
  unknown48->unknown50.resize(truckCount);
  unknown48->unknown00.setAllocator(allocator);
  unknown48->unknown00.resize(boneCount > truckCount ? boneCount : truckCount);
  unknown48->unknown28.setAllocator(allocator);
  unknown48->unknown28.resize(boneCount);
  unknown48->unknown78.setAllocator(allocator);
  unknown48->unknown78.resize(boneCount);
}

Blender::~Blender() {
  for (u32 i = 0; i < unknown18.size(); i++) {
    unknown18[i]->release();
  }
  unknown18.clear();
  unknown001(unknown40);
  unknown48->~Work();
  m_pAllocator->deallocate(unknown48);
  unknown48 = nullptr;
}

bool Blender::addControl(Control *pControl) {
  MM_ASSERT(pControl);
  if (pControl->m_pBinding->m_indexTable.size() == unknown40->unknown30.size()) {
    pControl->addRef();
    unknown18.push_back(pControl);
    return true;
  }
  return false;
}

bool Blender::removeControl(Control *pControl) {
  Control **it = mm::mtl::find(unknown18.begin(), unknown18.end(), pControl);
  if (it == unknown18.end()) {
    return false;
  }
  unknown18.erase(it);
  pControl->release();
  return true;
}

void Blender::update(f32 deltaTime) {
  Control **it = unknown18.begin();
  Control **last = unknown18.end();
  for (; it != last; ++it) {
    (*it)->update(deltaTime);
  }
}

} // namespace anm
