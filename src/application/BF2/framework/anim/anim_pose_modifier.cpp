#include "framework/anim/anim_pose_modifier.h"

#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_skeleton.h"
#include "fw/fw_model_object.h"
#include "fw/fw_transform.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_acc.h"

namespace mm {
struct Mat44;

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

void AnimPoseModifier::apply() {
  unknown18->syncModelSpace();
  ml::ScnObjAccResNode nodes(unknown20->getInterface());
  mm::Mat44 *matrix = nodes.getBoneMatPtr(0);
  int boneMax = unknown28.size();
  for (int i = 0; i < boneMax; i++, matrix++) {
    s16 bone = unknown28[i];
    if (bone > 0) {
      unknown18->calcMatrixModelSpace(bone, matrix);
    }
  }
  if (unknown50.size() != 0) {
    f32 scale = unknown20->unknown60;
    for (u32 i = 0; i < unknown50.size(); i++) {
      ReferenceFrame *frame = unknown50[i].unknown00.get();
      Transform &local = frame->unknown002();
      const anm::QsTransform &bone = unknown18->getBoneModelSpace(unknown50[i].unknown08);
      local.unknown00 = mm::Vec3(bone.unknown00.x, bone.unknown00.y, bone.unknown00.z);
      local.unknown00 *= scale;
      local.unknown10 = bone.unknown10;
      mm::Vec3 boneScale(bone.unknown20.x, bone.unknown20.y, bone.unknown20.z);
      unknown50[i].unknown00->unknownc8 = boneScale.x;
      unknown50[i].unknown00->unknowncc = boneScale.y;
      unknown50[i].unknown00->unknownd0 = boneScale.z;
    }
  }
  if (unknown1058 != nullptr) {
    ml::ScnObjAccEtcParams params(unknown20->getInterface());
    for (u32 i = 0; i < unknown1060.size(); i++) {
      s16 truck = unknown1060[i];
      if (truck != -1) {
        params.setParams(i, unknown1058->unknown28[truck]);
      }
    }
  }
}

} // namespace fw
