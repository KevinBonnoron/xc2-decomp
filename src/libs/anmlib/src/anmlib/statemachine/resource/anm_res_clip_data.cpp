#include "anm/anm_res_clip_data.h"

#include <algorithm>

#include "anm/anm_animation.h"
#include "anm/anm_binding.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_res_resolver.h"

namespace anm {

ResClipData::ResClipData() : unknown00(nullptr), m_pBinding(nullptr), unknown10(0.0f), unknown14(0.0f), unknowne0(false) {}

void ResClipData::cleanup() {
  unknown001(m_pBinding);
  for (u32 i = 0; i < 5; i++) {
    unknown18[i].clear();
  }
}

void ResClipData::restore(const ResResolver &resolver) { resolver.unknown08(unknown00->unknown00, unknown00->unknown08); }

void ResClipData::setFrameAnnotation(u32 type, f32 frame, const AsmAnnotetion &annotation) {
  if (m_pBinding != nullptr) {
    AsmKeyframeAnnotation keyframe;
    keyframe.unknown00 = m_pBinding->m_pAnimation->unknown28 * frame;
    keyframe.unknown08 = annotation;
    unknown18[type].push_back(keyframe);
    unknowne0 = true;
  }
}

bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation &annotation, const AsmKeyframeAnnotation &other) { return annotation.unknown00 < other.unknown00; }

void ResClipData::sortAnnotation(u32 type) {
  std::sort(unknown18[type].begin(), unknown18[type].end(), lessAsmKeyframeAnnotation);
  unknowne0 = false;
}

} // namespace anm

template mm::mtl::FixedArray<mm::mtl::Vector<anm::AsmAnnotetion>, 5>::~FixedArray();
template mm::mtl::FixedArray<mm::mtl::Vector<anm::AsmKeyframeAnnotation>, 5>::~FixedArray();
template void mm::mtl::Vector<anm::AsmAnnotetion>::expand(size_t, size_t);
template void mm::mtl::Vector<anm::AsmKeyframeAnnotation>::expand(size_t, size_t);
template void mm::mtl::Vector<anm::AsmKeyframeAnnotation>::assign(const mm::mtl::Vector<anm::AsmKeyframeAnnotation> &);
