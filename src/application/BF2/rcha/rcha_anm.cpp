#include "rcha/rcha_anm.h"

int RchaAnm::getValueInt(f32 frame) const {
  f32 value = getValue(frame);
  int whole = static_cast<int>(value);
  return whole + (value - whole > 0.5f);
}
