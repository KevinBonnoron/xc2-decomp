#include "framework/anim/anim_volume_fade_modifier.h"

#include <stdlib.h>
#include <string.h>

#include "fw/fw_model_object.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_acc.h"

namespace fw {

AnimVolumeFadeModifier::AnimVolumeFadeModifier() : unknown18(nullptr), unknown70(true) {}

void AnimVolumeFadeModifier::unbind() { mm::mtl::safeRelease(unknown18); }

void AnimVolumeFadeModifier::bind(ModelObject *modelObject) {
  unbind();
  if (modelObject != nullptr) {
    unknown18 = modelObject;
    modelObject->addRef();
    for (u32 i = 0; i < RATIO_MAX; i++) {
      unknown20[i] = 1.0f;
    }
    for (u32 i = 0; i < RATIO_MAX; i++) {
      unknown38[i] = -1;
    }
    ml::ScnObjAccEtcParams params(unknown18->getInterface());
    u32 count = params.getMax();
    unknown70 = true;
    for (u32 i = 0; i < count; i++) {
      const char *name = params.getName(i);
      if (strncmp(name, "VolumeFade_", 11) == 0) {
        unknown70 = false;
        unknown38[atoi(name + 11)] = i;
      }
    }
  }
}

void AnimVolumeFadeModifier::apply() {
  if (!unknown50.isValid() || unknown50()) {
    if (!unknown70) {
      ml::ScnObjAccEtcParams params(unknown18->getInterface());
      for (u32 i = 0; i < RATIO_MAX; i++) {
        if (unknown38[i] >= 0) {
          params.setParams(unknown38[i], unknown20[i]);
        }
      }
    } else {
      ml::ScnObjAccVolumeFade fade(unknown18->getInterface());
      for (u32 i = 0; i < fade.getMax(); i++) {
        fade.setRatio(unknown20[i], i);
      }
    }
  }
}

} // namespace fw
