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

  ModelObject *unknown18;         // Inferred role: model object; original member name unknown.
  ColiObject *unknown20;          // Inferred role: coli object; original member name unknown.
  mm::mtl::Vector<s16> unknown28; // Inferred role: bones; original member name unknown.
};

static_assert(offsetof(AnimColPoseModifier, unknown18) == 0x18, "");
static_assert(offsetof(AnimColPoseModifier, unknown20) == 0x20, "");
static_assert(offsetof(AnimColPoseModifier, unknown28) == 0x28, "");
static_assert(sizeof(AnimColPoseModifier) == 0x50, "");

} // namespace fw
