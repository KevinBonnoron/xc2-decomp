#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjDummyTutorial {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: tutorial; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
};

} // namespace gf
