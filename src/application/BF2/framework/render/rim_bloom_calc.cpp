#include "framework/render/rim_bloom_calc.h"

namespace fw {

f32 RimBloomCalc::getVal(f32 time, u32 channel) const {
  if (unknown00[channel].unknown18.front().unknown00 >= time) {
    return unknown00[channel].unknown18.front().unknown04;
  }
  if (unknown00[channel].unknown18.front().unknown00 < time && time < unknown00[channel].unknown18.back().unknown00) {
    return calcValFromCurve(time, channel);
  }
  return unknown00[channel].unknown18.back().unknown04;
}

void RimBloomCalc::calcEndFrame() {
  for (u32 channel = 0; channel < 3; channel++) {
    if (unknownc80 < unknown00[channel].unknown18.back().unknown00) {
      unknownc80 = unknown00[channel].unknown18.back().unknown00;
    }
  }
}

} // namespace fw
