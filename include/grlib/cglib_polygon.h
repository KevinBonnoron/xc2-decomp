#pragma once
#include "types.h"

namespace grlib {

class CGLibPolygon {
public:
  static void setCullingOff();
  static void setCullingFront();
  static void setCullingBack();
  static void setCullingDispOff();
  static void setPointMode();
  static void setLineMode();
  static void setTraiangle();
  static void setLineWidth(f32 width);
  static void setRasterizer(u8 isDiscard);
  static void setConservativeRaster(u8 isEnable);
  static void setConservativeDilate(f32 dilate);
  static void setConservativeSubpixelBias(int xBits, int yBits);
};

} // namespace grlib
