#include "anm/anm_res_asm.h"

#include "anm/anm_array.h"
#include "anm/anm_res_state_data.h"

namespace anm {

void ResASM::restore(const ResResolver &resolver) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    unknown28[i].restore(resolver);
  }
}

void ResASM::clearAnnotations(u32 type) {
  clearAttribute(type);
  clearEnterAnnotation(type);
  clearLeaveAnnotation(type);
  clearFrameAnnotation(type);
}

void ResASM::clearEnterAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->unknown001(type);
  }
}

void ResASM::clearLeaveAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->unknown002(type);
  }
}

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
