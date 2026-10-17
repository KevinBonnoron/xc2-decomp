#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "types.h"

namespace anm {
class ASMControl;
class Blender;
class Control;
class ExtraTruckBuffer;
class Pose;
} // namespace anm

namespace fw {

class AnimSinglePoseSamper : public AnimPoseSamplerInterface {
public:
  AnimSinglePoseSamper();
  void unbind();
  ~AnimSinglePoseSamper() override;
  void bind(anm::Control *control, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::Control *control;
  anm::Pose *pose;
  anm::ExtraTruckBuffer *extraTruckBuffer;
  u16 extraTruckSlot;
  bool isLocalSpace;
};

static_assert(offsetof(AnimSinglePoseSamper, control) == 0x18, "");
static_assert(offsetof(AnimSinglePoseSamper, extraTruckSlot) == 0x30, "");
static_assert(offsetof(AnimSinglePoseSamper, isLocalSpace) == 0x32, "");
static_assert(sizeof(AnimSinglePoseSamper) == 0x38, "");

class AnimPoseSamper : public AnimPoseSamplerInterface {
public:
  AnimPoseSamper();
  ~AnimPoseSamper() override;
  void unbind();
  void bind(anm::Blender *blender, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::Blender *blender;
  anm::Pose *pose;
  anm::ExtraTruckBuffer *extraTruckBuffer;
  u16 extraTruckSlot;
  bool isBind;
  bool isLocalSpace;
};

static_assert(offsetof(AnimPoseSamper, blender) == 0x18, "");
static_assert(offsetof(AnimPoseSamper, extraTruckSlot) == 0x30, "");
static_assert(offsetof(AnimPoseSamper, isBind) == 0x32, "");
static_assert(offsetof(AnimPoseSamper, isLocalSpace) == 0x33, "");
static_assert(sizeof(AnimPoseSamper) == 0x38, "");

class AnimAsmPoseSampler : public AnimPoseSamplerInterface {
public:
  AnimAsmPoseSampler();
  ~AnimAsmPoseSampler() override;
  void unbind();
  void bind(anm::ASMControl *asmControl, anm::Pose *pose, anm::ExtraTruckBuffer *extraTruckBuffer);
  void samplePose() override;

  anm::ASMControl *asmControl;
  anm::Pose *pose;
  anm::ExtraTruckBuffer *extraTruckBuffer;
  u16 extraTruckSlot;
  bool isLocalSpace;
};

static_assert(offsetof(AnimAsmPoseSampler, asmControl) == 0x18, "");
static_assert(offsetof(AnimAsmPoseSampler, extraTruckSlot) == 0x30, "");
static_assert(offsetof(AnimAsmPoseSampler, isLocalSpace) == 0x32, "");
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

  anm::ASMControl *asmControl;
  anm::Pose *pose;
  anm::ExtraTruckBuffer *extraTruckBuffer;
  u16 extraTruckSlot;
  bool isPause;
  bool isLocalSpace;
};

static_assert(offsetof(AnimEventAsmPoseSampler, asmControl) == 0x18, "");
static_assert(offsetof(AnimEventAsmPoseSampler, extraTruckSlot) == 0x30, "");
static_assert(offsetof(AnimEventAsmPoseSampler, isPause) == 0x32, "");
static_assert(offsetof(AnimEventAsmPoseSampler, isLocalSpace) == 0x33, "");
static_assert(sizeof(AnimEventAsmPoseSampler) == 0x38, "");

} // namespace fw
