#include "anm/anm_res_clip_data.h"

#include <algorithm>

namespace anm {

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
