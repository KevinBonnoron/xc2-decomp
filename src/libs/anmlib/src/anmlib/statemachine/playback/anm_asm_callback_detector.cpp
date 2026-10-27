#include "anm/anm_asm_callback_detector.h"

#include <algorithm>

#include "mm/mm_std_base.h"
#include "mm_mtl/vector.h"

namespace anm {

// Inferred comparator: orders a keyframe annotation against a frame; original name unknown.
struct unknown001 {
  bool operator()(const AsmKeyframeAnnotation &annotation, f32 frame) const { return annotation.unknown00 < frame; }
};

void CallBackDetector::execute(AsmListener &listener, AsmListener::CallBackType type, const mm::mtl::Vector<AsmAnnotetion> &annotations) {
  MM_ASSERT(annotations.size() != 0);
  for (const AsmAnnotetion *it = annotations.begin(), *last = annotations.end(); it != last; ++it) {
    listener.callback(type, *it);
  }
}

void CallBackDetector::executeStartFrame(AsmListener &listener, f32 frame, const mm::mtl::Vector<AsmKeyframeAnnotation> &annotations) {
  const AsmKeyframeAnnotation *it = std::lower_bound(annotations.begin(), annotations.end(), frame, unknown001());
  const AsmKeyframeAnnotation *last = annotations.end();
  for (; it != last && it->unknown00 == frame; ++it) {
    listener.callback(AsmListener::CALLBACK_FRAME, it->unknown08);
  }
}

} // namespace anm
