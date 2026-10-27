#include "anm/anm_res_asm.h"

#include "anm/anm_array.h"
#include "anm/anm_res_state_data.h"

namespace anm {

void ResASM::sortAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->sortAnnotation(type);
  }
}

void ResASM::clearAttribute(u32 category) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->setAttribute(category, 0);
  }
}

void ResASM::clearFrameAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->clearFrameAnnotation(type);
  }
}

} // namespace anm
