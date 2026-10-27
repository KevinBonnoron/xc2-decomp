#include "framework/anim/anim_pose_modifier.h"

#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_reference_object.h"
#include "fw/fw_model_object.h"
#include "mm_mtl/reference_object.h"

namespace fw {

AnimPoseModifier::AnimPoseModifier() : unknown18(nullptr), unknown20(nullptr), unknown1058(nullptr) {}

AnimPoseModifier::~AnimPoseModifier() { unbind(); }

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
