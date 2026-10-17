#pragma once

namespace grlib {

class CGLibPolygon {
public:
  static void setCullingOff();
  static void setCullingFront();
  static void setCullingBack();
  static void setCullingDispOff();
};

} // namespace grlib
