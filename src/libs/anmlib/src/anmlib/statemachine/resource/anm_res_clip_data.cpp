#include "anm/anm_res_clip_data.h"

#include <algorithm>

namespace anm {

bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation &annotation, const AsmKeyframeAnnotation &other) { return annotation.unknown00 < other.unknown00; }

void ResClipData::sortAnnotation(u32 type) {
  std::sort(unknown18[type].begin(), unknown18[type].end(), lessAsmKeyframeAnnotation);
  unknowne0 = false;
}

} // namespace anm
