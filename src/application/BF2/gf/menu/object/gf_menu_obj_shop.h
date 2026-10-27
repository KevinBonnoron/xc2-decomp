#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjShop {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: shop; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context);
  static u32 getSellItemTypeMax();
};

} // namespace gf
