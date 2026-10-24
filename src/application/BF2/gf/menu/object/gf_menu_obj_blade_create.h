#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBladeCreate {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: event; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void openCreatedBladeName(GfMenuCallContext *context);
};

} // namespace gf
