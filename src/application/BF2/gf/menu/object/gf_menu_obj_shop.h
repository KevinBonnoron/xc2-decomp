#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjShop {
public:
  struct OpenParam {
    u32 shop;
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context);
};

} // namespace gf
