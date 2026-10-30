#include "anm/anm_res_state_data.h"

namespace anm {

ResStateData::ResStateData() : unknown00(nullptr) {
  for (u32 i = 0; i < 4; i++) {
    unknown30[i] = 0;
  }
}

void ResStateData::cleanup() {
  unknown00 = nullptr;
  for (u32 i = 0; i < unknown08.size(); i++) {
    unknown08[i].cleanup();
  }
  for (u32 i = 0; i < 5; i++) {
    unknown50[i].clear();
    unknown118[i].clear();
  }
}

void ResStateData::restore(const ResResolver &resolver) {
  for (u32 i = 0; i < unknown08.size(); i++) {
    unknown08[i].restore(resolver);
  }
}

void ResStateData::sortAnnotation(u32 type) {
  for (u32 i = 0; i < unknown08.size(); i++) {
    if (unknown08[i].unknowne0) {
      unknown08[i].sortAnnotation(type);
    }
  }
}

void ResStateData::clearFrameAnnotation(u32 type) {
  for (u32 i = 0; i < unknown08.size(); i++) {
    unknown08[i].unknown18[type].clear();
  }
}

void ResStateData::setFrameAnnotation(u32 type, u32 clip, f32 frame, const AsmAnnotetion &annotation) { unknown08[clip].setFrameAnnotation(type, frame, annotation); }

} // namespace anm

template void mm::mtl::Vector<anm::ResClipData>::resize(size_t);
