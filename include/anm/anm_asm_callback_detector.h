#pragma once
#include "anm/anm_asm_listener.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class CallBackDetector {
public:
  static void execute(AsmListener &listener, AsmListener::CallBackType type, const mm::mtl::Vector<AsmAnnotetion> &annotations);
  static void executeStartFrame(AsmListener &listener, f32 frame, const mm::mtl::Vector<AsmKeyframeAnnotation> &annotations);
  static void executeFrame(AsmListener &listener, f32 previousFrame, f32 frame, bool reverse, bool looped,
                           const mm::mtl::Vector<AsmKeyframeAnnotation> &annotations);
};

} // namespace anm
