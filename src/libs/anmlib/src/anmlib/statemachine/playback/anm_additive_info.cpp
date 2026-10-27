#include "anm/anm_additive_info.h"

#include "anm/anm_asm_state.h"
#include "mm_math/mm_math.h"

namespace anm {

void AdditiveInfo::easeIn(AsmBlender *blender, AsmListener *listener, mm::mtl::IntrusivePtr<AsmState> state, f32 time, f32 weight, InterpolateType type, InterpolateCurve curve) {
  if (unknown00.get() != nullptr) {
    unknown00.get()->onLeave(listener);
    unknown00->dettach(blender);
    unknown00 = nullptr;
  }
  unknown00 = state;
  unknown00->setLocalTime(0.0f);
  unknown00->attach(blender);
  unknown00->onEnter(listener);
  if (mm::fabs(time) < 1.1920929e-07f) {
    AsmState *current = unknown00.operator->();
    current->unknown24 = unknown20 * weight;
    current->onSetWeight();
    unknown18 = 0;
  } else {
    unknown08 = time;
    unknown0c = curve;
    unknown10 = type;
    AsmState *current = unknown00.operator->();
    current->unknown24 = 0.0f;
    current->onSetWeight();
    unknown18 = 1;
  }
  unknown1c = weight;
  unknown14 = 0.0f;
}

} // namespace anm
