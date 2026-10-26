#pragma once

#include "dr/dr_mdl_obj.h"

namespace ml {
class DrMan;

class DrMdoCtlDammy : public DrMdlObj {
public:
  DrMdoCtlDammy(const void *data, DrMan *drMan, int viewNum);
  ~DrMdoCtlDammy() override;
  void resourceInit() override;
  void update() override;
  void dispOffUpdate() override;
};

} // namespace ml
