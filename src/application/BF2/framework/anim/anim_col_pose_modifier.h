#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class ColiObject;
class ModelObject;

class AnimColPoseModifier : public AnimAfterModifierInterface {
public:
  AnimColPoseModifier();
  ~AnimColPoseModifier() override;
  void bind(ModelObject *modelObject, ColiObject *coliObject, mm::mtl::IAllocator *allocator);
  void unbind();
  void apply() override;

  ModelObject *modelObject;
  ColiObject *coliObject;
  mm::mtl::Vector<s16> bones;
};

static_assert(offsetof(AnimColPoseModifier, modelObject) == 0x18, "");
static_assert(offsetof(AnimColPoseModifier, coliObject) == 0x20, "");
static_assert(offsetof(AnimColPoseModifier, bones) == 0x28, "");
static_assert(sizeof(AnimColPoseModifier) == 0x50, "");

} // namespace fw
