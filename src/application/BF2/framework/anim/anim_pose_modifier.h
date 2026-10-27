#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "framework/reference_frame.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {
class ExtraTruckBuffer;
class Pose;
} // namespace anm

namespace fw {

class ModelObject;

class AnimPoseModifier : public AnimPoseModifierInterface {
public:
  struct BoneBindInfo {
    mm::mtl::IntrusivePtr<ReferenceFrame> unknown00; // Inferred role: reference frame; original member name unknown.
    u16 unknown08;                                   // Inferred role: bone index; original member name unknown.
  };

  AnimPoseModifier();
  ~AnimPoseModifier() override;
  void bind(anm::Pose *pose, ModelObject *modelObject, anm::ExtraTruckBuffer *extraTruckBuffer, mm::mtl::IAllocator *allocator);
  void unbind();
  void bindReferenceFrameToBone(u16 bone, mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  void unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  void apply() override;

  anm::Pose *unknown18;                              // Inferred role: pose; original member name unknown.
  ModelObject *unknown20;                            // Inferred role: model object; original member name unknown.
  mm::mtl::Vector<s16> unknown28;                    // Inferred role: bones; original member name unknown.
  mm::mtl::FixedVector<BoneBindInfo, 256> unknown50; // Inferred role: bound reference frames; original member name unknown.
  anm::ExtraTruckBuffer *unknown1058;                // Inferred role: extra truck buffer; original member name unknown.
  mm::mtl::Vector<s16> unknown1060;                  // Inferred role: extra trucks; original member name unknown.
};

static_assert(sizeof(AnimPoseModifier::BoneBindInfo) == 0x10, "");
static_assert(offsetof(AnimPoseModifier, unknown18) == 0x18, "");
static_assert(offsetof(AnimPoseModifier, unknown20) == 0x20, "");
static_assert(offsetof(AnimPoseModifier, unknown28) == 0x28, "");
static_assert(offsetof(AnimPoseModifier, unknown50) == 0x50, "");
static_assert(offsetof(AnimPoseModifier, unknown1058) == 0x1058, "");
static_assert(offsetof(AnimPoseModifier, unknown1060) == 0x1060, "");
static_assert(sizeof(AnimPoseModifier) == 0x1088, "");

} // namespace fw
