#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBladeCreate {
public:
  struct OpenParam {
    u32 event;
  };

  static void registOpenParam(const OpenParam &param);
  static void openCreatedBladeName(GfMenuCallContext *context);
};

} // namespace gf
