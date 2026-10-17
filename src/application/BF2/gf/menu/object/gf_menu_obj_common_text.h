#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct MenuCommonWindowParam;

class GfMenuObjCommonText {
public:
  static void close();
  static void open(GfMenuCallContext *context, const MenuCommonWindowParam &param);
  static void open(GfMenuCallContext *context, u32 window, u32 param);
  static void openItem(GfMenuCallContext *context, u32 type, u32 item);
};

} // namespace gf
