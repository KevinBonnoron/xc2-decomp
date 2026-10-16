#pragma once

namespace ml {

struct PadVibrationInfo;

class DevPad {
public:
  static int getPadMax();
  static void setRepeatTime(float time);
  static bool isInitialized();
  static void playVibration(int padNo, const PadVibrationInfo &info);
  static void stopVibration(int padNo);
};

} // namespace ml
