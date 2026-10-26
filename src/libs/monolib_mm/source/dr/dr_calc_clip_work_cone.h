#pragma once

#include "dr/dr_calc_clip_work.h"

namespace ml {

class DrCalcClipWorkCone : public DrCalcClipWork {
public:
  DrCalcClipWorkCone();
  ~DrCalcClipWorkCone();
  void debugDraw() override;
};

} // namespace ml
