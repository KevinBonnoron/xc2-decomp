#include "framework/anim/anim_pose_modifier.h"

#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_skeleton.h"
#include "fw/fw_model_object.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_acc.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

AnimPoseModifier::AnimPoseModifier() : unknown18(nullptr), unknown20(nullptr), unknown1058(nullptr) {}

AnimPoseModifier::~AnimPoseModifier() { unbind(); }

void AnimPoseModifier::bind(anm::Pose *pose, ModelObject *modelObject, anm::ExtraTruckBuffer *extraTruckBuffer, mm::mtl::IAllocator *allocator) {
  unbind();
  unknown18 = pose;
  pose->addRef();
  unknown20 = modelObject;
  modelObject->addRef();
  unknown28.setAllocator(allocator);
  ml::ScnObjAccResNode nodes(unknown20->getInterface());
  int boneMax = nodes.getBoneMax();
  unknown28.resize(boneMax);
  const anm::Skeleton *skeleton = pose->unknown18;
  for (int i = 0; i < boneMax; i++) {
    const char *name = nodes.getBoneName(i);
    u16 bone = anm::Skeleton::INVALID_BONE;
    if (name != nullptr) {
      bone = skeleton->getBoneID(name);
    }
    unknown28[i] = bone;
  }
  if (extraTruckBuffer != nullptr) {
    unknown1058 = extraTruckBuffer;
    extraTruckBuffer->addRef();
    unknown1060.setAllocator(allocator);
    ml::ScnObjAccEtcParams params(unknown20->getInterface());
    u32 max = params.getMax();
    unknown1060.resize(max, -1);
    const anm::ExtraTruckSlot *slot = unknown1058->unknown20;
    for (u32 i = 0; i < max; i++) {
      unknown1060[i] = slot->getTruckID(params.getName(i));
    }
  }
}

void AnimPoseModifier::unbind() {
  anm::unknown001(unknown18);
  mm::mtl::safeRelease(unknown20);
  unknown28.clear();
  unknown50.clear();
  anm::unknown001(unknown1058);
  unknown1060.clear();
}

void AnimPoseModifier::bindReferenceFrameToBone(u16 bone, mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  BoneBindInfo info;
  info.unknown00 = frame;
  info.unknown08 = bone;
  unknown50.push_back(info);
  if (frame.get() != nullptr) {
    frame->unknownc8 = 1.0f;
    frame->unknowncc = 1.0f;
    frame->unknownd0 = 1.0f;
  }
}

void AnimPoseModifier::unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  for (BoneBindInfo *it = unknown50.begin(); it != unknown50.end(); ++it) {
    if (it->unknown00 == frame) {
      unknown50.erase(it);
      return;
    }
  }
}

} // namespace fw
