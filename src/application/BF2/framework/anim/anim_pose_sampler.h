#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "types.h"

namespace anm {
class ASMControl;
class ExtraTruckBuffer;
class Pose;
} // namespace anm

namespace fw {

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

} // namespace fw
