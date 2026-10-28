#include "framework/anim/anim_pose_sampler.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_control.h"
#include "anm/anm_binding.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_util.h"

namespace anm {
struct QsTransform;
} // namespace anm

namespace fw {

AnimSinglePoseSamper::AnimSinglePoseSamper() : unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(0xffff), unknown32(true) {}

AnimSinglePoseSamper::~AnimSinglePoseSamper() { unbind(); }

void AnimSinglePoseSamper::unbind() { unknown001(*this); }

void AnimSinglePoseSamper::bind(anm::Control *control, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer) {
  unbind();
  if (pose->unknown18->unknown30.size() == control->m_pBinding->m_indexTable.size()) {
    unknown18 = control;
    control->addRef();
    unknown20 = pose;
    pose->addRef();
  }
  if (extraTruckBuffer != nullptr) {
    const anm::ExtraTruckSlot *slot = extraTruckBuffer->unknown20;
    s16 slotId = extraTruckBuffer->unknown18->getExtraTruckSlotID(slot->unknown00);
    unknown30 = slotId;
    if (slotId != -1) {
      const anm::Binding *binding = control->m_pBinding;
      if (slotId < binding->unknown30.size()) {
        if (slot->unknown18.size() == binding->unknown30[slotId].unknown08.size()) {
          unknown28 = extraTruckBuffer;
          extraTruckBuffer->addRef();
        }
      }
    }
  }
}

void AnimSinglePoseSamper::samplePose() {
  anm::Util::samplePoseSmartFromControl(unknown18, unknown20, unknown32);
  anm::ExtraTruckBuffer *buffer = unknown28;
  if (buffer != nullptr) {
    unknown18->sampleExtraTrucks(unknown30, buffer->unknown30, buffer->unknown28);
    anm::Util::clampLimitExtraTruck(*unknown28->unknown20, buffer->unknown30, buffer->unknown28);
  }
}

void AnimEventSinglePoseSamper::samplePose() {
  if (unknown18 != nullptr && unknown20 != nullptr) {
    unknown20->setReferencePose();
    anm::Array<anm::QsTransform> &local = unknown20->accessSyncedPoseLocalSpace();
    unknown18->sampleTrucks(local.m_size, local.m_pElements);
    unknown20->syncModelSpace();
  }
  anm::ExtraTruckBuffer *buffer = unknown28;
  if (buffer != nullptr) {
    unknown18->sampleExtraTrucks(unknown30, buffer->unknown30, buffer->unknown28);
    anm::Util::clampLimitExtraTruck(*unknown28->unknown20, buffer->unknown30, buffer->unknown28);
  }
}

AnimPoseSamper::AnimPoseSamper() : unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown32(true), unknown33(true) {}

AnimPoseSamper::~AnimPoseSamper() { unbind(); }

void AnimPoseSamper::unbind() {
  unknown001(*this);
  unknown32 = false;
}

void AnimPoseSamper::bind(anm::Blender *blender, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer) {
  unbind();
  unknown18 = blender;
  blender->addRef();
  unknown20 = pose;
  pose->addRef();
  unknown002(*this, extraTruckBuffer);
  unknown32 = true;
}

void AnimPoseSamper::samplePose() {
  if (unknown32) {
    if (unknown33) {
      anm::Array<anm::QsTransform> &local = unknown20->accessSyncedPoseLocalSpace();
      unknown18->sampleTrucks(local.m_size, local.m_pElements);
      unknown20->syncModelSpace();
    } else {
      anm::Array<anm::QsTransform> &model = unknown20->accessSyncedPoseModelSpace();
      unknown18->sampleTrucksMS(model.m_size, model.m_pElements);
    }
    if (unknown28 != nullptr) {
      unknown18->sampleExtraTrucks(unknown30, unknown28->unknown30, unknown28->unknown28);
    }
  }
}

AnimEventMotPoseSamper::AnimEventMotPoseSamper() {}

AnimEventMotPoseSamper::~AnimEventMotPoseSamper() {}

void AnimEventMotPoseSamper::resetPose() {
  if (unknown20 != nullptr) {
    unknown20->setReferencePose();
  }
}

AnimAsmPoseSampler::AnimAsmPoseSampler() : unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(0xffff), unknown32(true) {}

AnimAsmPoseSampler::~AnimAsmPoseSampler() { unbind(); }

void AnimAsmPoseSampler::unbind() { unknown001(*this); }

void AnimAsmPoseSampler::bind(anm::ASMControl *asmControl, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer) {
  unbind();
  unknown18 = asmControl;
  asmControl->addRef();
  unknown20 = pose;
  pose->addRef();
  unknown002(*this, extraTruckBuffer);
}

void AnimAsmPoseSampler::samplePose() {
  if (!unknown32) {
    anm::Array<anm::QsTransform> &model = unknown20->accessSyncedPoseModelSpace();
    unknown18->sampleTrucksMS(model.m_size, model.m_pElements);
  } else {
    anm::Array<anm::QsTransform> &local = unknown20->accessSyncedPoseLocalSpace();
    unknown18->sampleTrucks(local.m_size, local.m_pElements);
    unknown20->syncModelSpace();
  }
  if (unknown28 != nullptr) {
    unknown18->unknown20.sampleExtraTrucks(unknown30, unknown28->unknown30, unknown28->unknown28);
  }
}

AnimEventAsmPoseSampler::AnimEventAsmPoseSampler() : unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(0xffff), unknown32(false), unknown33(true) {}

AnimEventAsmPoseSampler::~AnimEventAsmPoseSampler() { unbind(); }

void AnimEventAsmPoseSampler::unbind() { unknown001(*this); }

void AnimEventAsmPoseSampler::bind(anm::ASMControl *asmControl, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer) {
  unbind();
  unknown18 = asmControl;
  if (asmControl != nullptr) {
    asmControl->addRef();
  }
  unknown20 = pose;
  pose->addRef();
  unknown002(*this, extraTruckBuffer);
}

void AnimEventAsmPoseSampler::samplePose() {
  if (!unknown32) {
    if (unknown18 == nullptr) {
      unknown20->setReferencePose();
    } else {
      anm::Array<anm::QsTransform> &local = unknown20->accessSyncedPoseLocalSpace();
      unknown18->sampleTrucks(local.m_size, local.m_pElements);
    }
    unknown20->syncModelSpace();
    if (unknown28 != nullptr) {
      unknown18->unknown20.sampleExtraTrucks(unknown30, unknown28->unknown30, unknown28->unknown28);
    }
  }
}

} // namespace fw
