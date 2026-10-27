#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace fw {

class ModelObject;

class AnimVolumeFadeModifier : public AnimAfterModifierInterface {
public:
  static const u32 RATIO_MAX = 6;

  AnimVolumeFadeModifier();
  ~AnimVolumeFadeModifier() override {}
  void bind(ModelObject *modelObject);
  void unbind();
  void apply() override;

  ModelObject *unknown18;              // Inferred role: model object; original member name unknown.
  f32 unknown20[RATIO_MAX];            // Inferred role: fade ratios; original member name unknown.
  s32 unknown38[RATIO_MAX];            // Inferred role: etc param index per ratio; original member name unknown.
  mm::mtl::Delegate<bool()> unknown50; // Inferred role: enable check; original member name unknown.
  bool unknown70;                      // Inferred role: use volume fade accessor; original member name unknown.
};

static_assert(offsetof(AnimVolumeFadeModifier, unknown18) == 0x18, "");
static_assert(offsetof(AnimVolumeFadeModifier, unknown20) == 0x20, "");
static_assert(offsetof(AnimVolumeFadeModifier, unknown38) == 0x38, "");
static_assert(offsetof(AnimVolumeFadeModifier, unknown50) == 0x50, "");
static_assert(offsetof(AnimVolumeFadeModifier, unknown70) == 0x70, "");
static_assert(sizeof(AnimVolumeFadeModifier) == 0x78, "");

} // namespace fw
