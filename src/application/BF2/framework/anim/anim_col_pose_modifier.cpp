#include "framework/anim/anim_col_pose_modifier.h"

#include "framework/coli/coli_object.h"
#include "fw/fw_model_object.h"
#include "idcoli/idcoli.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_acc.h"

namespace fw {

AnimColPoseModifier::AnimColPoseModifier() : m_modelObject(nullptr), m_coliObject(nullptr) {}

AnimColPoseModifier::~AnimColPoseModifier() {}

void AnimColPoseModifier::unbind() {
  mm::mtl::safeRelease(m_modelObject);
  mm::mtl::safeRelease(m_coliObject);
  unknown28.clear();
}

void AnimColPoseModifier::bind(ModelObject *modelObject, ColiObject *coliObject, mm::mtl::IAllocator *allocator) {
  unbind();
  if (modelObject != nullptr) {
    m_modelObject = modelObject;
    modelObject->addRef();
  }
  if (coliObject != nullptr) {
    m_coliObject = coliObject;
    coliObject->addRef();
  }
  if (m_modelObject != nullptr && m_coliObject != nullptr) {
    unknown28.setAllocator(allocator);
    idcoli::IDColiParmsBone bone(m_coliObject->m_coliObject);
    ml::ScnObjAccResNode node(m_modelObject->getInterface());
    u32 count = bone.getBoneMax();
    unknown28.resize(count, -1);
    for (u32 i = 0; i < count; i++) {
      int index = node.getBoneIndex(bone.getBoneName(i));
      if (index >= 0) {
        unknown28[i] = index;
      }
    }
  }
}

void AnimColPoseModifier::apply() {
  if (m_modelObject != nullptr && m_coliObject != nullptr) {
    idcoli::IDColiParmsBone bone(m_coliObject->m_coliObject);
    ml::ScnObjAccResNode node(m_modelObject->getInterface());
    for (u32 i = 0; i < unknown28.size(); i++) {
      int index = unknown28[i];
      if (index >= 0) {
        bone.setBoneMatrix(i, node.getBoneMat(index));
      }
    }
  }
}

} // namespace fw
