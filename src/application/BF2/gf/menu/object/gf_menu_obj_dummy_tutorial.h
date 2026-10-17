#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjDummyTutorial {
public:
  struct OpenParam {
    u32 tutorial;
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
};

} // namespace gf
