#pragma once
#include <stddef.h>

#include "anm/anm_extra_truck.h"
#include "anm/anm_skeleton.h"
#include "framework/anim/anim_manager.h"
#include "types.h"

namespace anm {
class ASMControl;
class Blender;
class Control;
class Pose;
} // namespace anm

namespace fw {

// Inferred helper shared by the unbind functions of the pose samplers; original name unknown.
template <typename Sampler> static inline void unknown001(Sampler &sampler) {
  if (sampler.unknown18 != nullptr) {
    sampler.unknown18->release();
    sampler.unknown18 = nullptr;
  }
  if (sampler.unknown20 != nullptr) {
    sampler.unknown20->release();
    sampler.unknown20 = nullptr;
  }
  if (sampler.unknown28 != nullptr) {
    sampler.unknown28->release();
    sampler.unknown28 = nullptr;
  }
  sampler.unknown30 = 0xffff;
}

// Inferred helper shared by the bind functions of the pose samplers; original name unknown.
template <typename Sampler> static inline void unknown002(Sampler &sampler, anm::ExtraTruckBuffer *extraTruckBuffer) {
  if (extraTruckBuffer != nullptr) {
    u16 slotId = extraTruckBuffer->unknown18->getExtraTruckSlotID(extraTruckBuffer->unknown20->unknown00);
    sampler.unknown30 = slotId;
    if (slotId != 0xffff) {
      sampler.unknown28 = extraTruckBuffer;
      extraTruckBuffer->addRef();
    }
  }
}

class AnimSinglePoseSamper : public AnimPoseSamplerInterface {
public:
  AnimSinglePoseSamper();
  void unbind();
  ~AnimSinglePoseSamper() override;
  void bind(anm::Control *control, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::Control *unknown18;          // Inferred role: control; original member name unknown.
  anm::Pose *unknown20;             // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown28; // Inferred role: extra truck buffer; original member name unknown.
  u16 unknown30;                    // Inferred role: extra truck slot; original member name unknown.
  bool unknown32;                   // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(AnimSinglePoseSamper, unknown18) == 0x18, "");
static_assert(offsetof(AnimSinglePoseSamper, unknown30) == 0x30, "");
static_assert(offsetof(AnimSinglePoseSamper, unknown32) == 0x32, "");
static_assert(sizeof(AnimSinglePoseSamper) == 0x38, "");

class AnimEventSinglePoseSamper : public AnimSinglePoseSamper {
public:
  ~AnimEventSinglePoseSamper() override {}
  void samplePose() override;
};

class AnimPoseSamper : public AnimPoseSamplerInterface {
public:
  AnimPoseSamper();
  ~AnimPoseSamper() override;
  void unbind();
  void bind(anm::Blender *blender, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::Blender *unknown18;          // Inferred role: blender; original member name unknown.
  anm::Pose *unknown20;             // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown28; // Inferred role: extra truck buffer; original member name unknown.
  u16 unknown30;                    // Inferred role: extra truck slot; original member name unknown.
  bool unknown32;                   // Inferred role: bind; original member name unknown.
  bool unknown33;                   // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(AnimPoseSamper, unknown18) == 0x18, "");
static_assert(offsetof(AnimPoseSamper, unknown30) == 0x30, "");
static_assert(offsetof(AnimPoseSamper, unknown32) == 0x32, "");
static_assert(offsetof(AnimPoseSamper, unknown33) == 0x33, "");
static_assert(sizeof(AnimPoseSamper) == 0x38, "");

class AnimAsmPoseSampler : public AnimPoseSamplerInterface {
public:
  AnimAsmPoseSampler();
  ~AnimAsmPoseSampler() override;
  void unbind();
  void bind(anm::ASMControl *asmControl, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::ASMControl *unknown18;       // Inferred role: asm control; original member name unknown.
  anm::Pose *unknown20;             // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown28; // Inferred role: extra truck buffer; original member name unknown.
  u16 unknown30;                    // Inferred role: extra truck slot; original member name unknown.
  bool unknown32;                   // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(AnimAsmPoseSampler, unknown18) == 0x18, "");
static_assert(offsetof(AnimAsmPoseSampler, unknown30) == 0x30, "");
static_assert(offsetof(AnimAsmPoseSampler, unknown32) == 0x32, "");
static_assert(sizeof(AnimAsmPoseSampler) == 0x38, "");

class AnimEventMotPoseSamper : public AnimPoseSamper {
public:
  AnimEventMotPoseSamper();
  ~AnimEventMotPoseSamper() override;
  void resetPose();
};

class AnimEventAsmPoseSampler : public AnimPoseSamplerInterface {
public:
  AnimEventAsmPoseSampler();
  ~AnimEventAsmPoseSampler() override;
  void unbind();
  void bind(anm::ASMControl *asmControl, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::ASMControl *unknown18;       // Inferred role: asm control; original member name unknown.
  anm::Pose *unknown20;             // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown28; // Inferred role: extra truck buffer; original member name unknown.
  u16 unknown30;                    // Inferred role: extra truck slot; original member name unknown.
  bool unknown32;                   // Inferred role: pause; original member name unknown.
  bool unknown33;                   // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(AnimEventAsmPoseSampler, unknown18) == 0x18, "");
static_assert(offsetof(AnimEventAsmPoseSampler, unknown30) == 0x30, "");
static_assert(offsetof(AnimEventAsmPoseSampler, unknown32) == 0x32, "");
static_assert(offsetof(AnimEventAsmPoseSampler, unknown33) == 0x33, "");
static_assert(sizeof(AnimEventAsmPoseSampler) == 0x38, "");

} // namespace fw
