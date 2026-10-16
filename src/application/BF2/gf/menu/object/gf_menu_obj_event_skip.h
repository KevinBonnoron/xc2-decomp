#pragma once

namespace gf {

class GfMenuCallContext;

class GfMenuObjEventSkip {
public:
  static void close();
  static void open(GfMenuCallContext *context);
};

} // namespace gf
