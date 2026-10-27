#include "anm/anm_factory.h"

#include <new>

#include "anm/anm_array-inl.h"
#include "anm/anm_asm_control.h"
#include "anm/anm_binding.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_reference_pose_animation.h"
#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "types.h"

namespace anm {

Pose *Factory::createPose(const Skeleton *skeleton, mm::mtl::IAllocator *pAllocator) {
  MM_ASSERT(pAllocator);
  if (skeleton == nullptr) {
    return nullptr;
  }
  Pose *pose = new (pAllocator->allocate(sizeof(Pose), 8)) Pose(skeleton, pAllocator);
  pose->addRef();
  return pose;
}

Control *Factory::createControl(const Binding *binding, mm::mtl::IAllocator *pAllocator) {
  MM_ASSERT(pAllocator);
  if (binding == nullptr || binding->m_pAnimation == nullptr) {
    return nullptr;
  }
  Control *control = new (pAllocator->allocate(sizeof(Control), 8)) Control(binding, pAllocator);
  control->addRef();
  return control;
}

Blender *Factory::createBlender(const Skeleton *skeleton, mm::mtl::IAllocator *pAllocator) {
  MM_ASSERT(pAllocator);
  if (skeleton == nullptr) {
    return nullptr;
  }
  Blender *blender = new (pAllocator->allocate(sizeof(Blender), 8)) Blender(skeleton, pAllocator);
  blender->addRef();
  return blender;
}

Binding *Factory::createReferencePoseAnimation(const Skeleton *skeleton, mm::mtl::IAllocator *pAllocator) {
  MM_ASSERT(pAllocator);
  if (skeleton != nullptr) {
    ReferencePoseAnimation *animation = new (pAllocator->allocate(sizeof(ReferencePoseAnimation), 8)) ReferencePoseAnimation(skeleton, pAllocator);
    return animation->createBinding();
  }
  return nullptr;
}

ExtraTruckBuffer *Factory::createExtraTruckBuffer(const Skeleton *skeleton, const char *name, mm::mtl::IAllocator *pAllocator) {
  MM_ASSERT(pAllocator);
  if (skeleton != nullptr) {
    u16 slotId = skeleton->getExtraTruckSlotID(name);
    if (slotId != 0xffff) {
      const ExtraTruckSlot &slot = skeleton->unknown50[slotId];
      if (slot.unknown20 != 0) {
        ExtraTruckBuffer *buffer = new (pAllocator->allocate(sizeof(ExtraTruckBuffer), 8)) ExtraTruckBuffer(*skeleton, slot, pAllocator);
        buffer->addRef();
        return buffer;
      }
    }
  }
  return nullptr;
}

ASMControl *Factory::createASMControl(const ResASM &resAsm, mm::mtl::IAllocator &allocator) {
  ASMControl *control = new (allocator.allocate(sizeof(ASMControl), 16)) ASMControl(resAsm, allocator);
  control->addRef();
  return control;
}

} // namespace anm
