#pragma once

#include "dr/dr_fog_obj.h"

namespace ml {
class DrMan;

class DrFogObjGbl : public DrFogObj {
public:
  DrFogObjGbl(DrMan *man);
  ~DrFogObjGbl() override {}
  void update() override;
};

} // namespace ml
