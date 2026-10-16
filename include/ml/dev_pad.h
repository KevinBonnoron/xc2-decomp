#pragma once

namespace ml {

class DevPad {
public:
  static int getPadMax();
  static void setRepeatTime(float time);
  static bool isInitialized();
};

} // namespace ml
