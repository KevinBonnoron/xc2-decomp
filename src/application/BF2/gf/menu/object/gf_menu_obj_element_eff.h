#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjElementEff {
public:
  struct StartParam {
    u32 attribute;
  };

  static void start(GfMenuCallContext *context, const StartParam &param);
  static void cancel(GfMenuCallContext *context);
};

} // namespace gf
