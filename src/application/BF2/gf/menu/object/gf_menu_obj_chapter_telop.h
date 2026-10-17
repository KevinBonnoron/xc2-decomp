#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjChapterTelop {
public:
  static void openBeginTelop(GfMenuCallContext *context, int chapter);
  static void openEndTelop(GfMenuCallContext *context, int chapter);
  static void openAvanTitle(GfMenuCallContext *context, int title);
  static void close(u16 title);
};

} // namespace gf
