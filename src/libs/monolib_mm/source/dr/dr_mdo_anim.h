#pragma once
#include "dr/dr_mdo_mat.h"
#include "types.h"

namespace ml {

class DrMdoAnim : public DrMdoMat {
public:
  void setMatAnmFrme(f32 frame);
};

} // namespace ml
