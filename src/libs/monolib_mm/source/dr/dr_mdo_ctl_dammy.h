#pragma once

#include "dr/dr_mdl_obj.h"

namespace ml {

class DrMdoCtlDammy : public DrMdlObj {
public:
  ~DrMdoCtlDammy() override;
  void resourceInit() override;
  void update() override;
  void dispOffUpdate() override;
};

} // namespace ml
