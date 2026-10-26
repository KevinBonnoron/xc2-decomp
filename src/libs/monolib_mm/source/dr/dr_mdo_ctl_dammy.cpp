#include "dr/dr_mdo_ctl_dammy.h"

namespace ml {
class DrMan;

DrMdoCtlDammy::DrMdoCtlDammy(const void *data, DrMan *drMan, int viewNum) : DrMdlObj(viewNum) {
  m_drMan = drMan;
  unknown50 = const_cast<void *>(data);
  unknown1c = 6;
}

DrMdoCtlDammy::~DrMdoCtlDammy() { releaseMat(); }

void DrMdoCtlDammy::resourceInit() {}

void DrMdoCtlDammy::update() {}

void DrMdoCtlDammy::dispOffUpdate() {}

} // namespace ml
