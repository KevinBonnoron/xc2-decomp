#include "anm/anm_res_clip_data.h"

#include <algorithm>

namespace anm {

bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation &annotation, const AsmKeyframeAnnotation &other) { return annotation.frame < other.frame; }

void ResClipData::sortAnnotation(u32 type) {
  std::sort(m_frameAnnotations[type].begin(), m_frameAnnotations[type].end(), lessAsmKeyframeAnnotation);
  m_isAnnotationDirty = false;
}

} // namespace anm
