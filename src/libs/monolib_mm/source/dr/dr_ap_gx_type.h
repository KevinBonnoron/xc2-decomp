#pragma once

namespace ml {

class DrAPGxType {
public:
  static void beginOccQuery();
  static void endOccQuery();
  static void beginShadow();
  static void endShadow();
  static void setupAlphaChanel(bool isAlpha);
};

} // namespace ml
