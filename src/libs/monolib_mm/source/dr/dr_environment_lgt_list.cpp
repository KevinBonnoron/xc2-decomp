#include "dr/dr_environment_lgt_list.h"

namespace ml {

void DrEnvironmentLgtList::setLgtObjData(const LgtObjData *data) { unknown00 = data; }

void DrEnvironmentLgtList::setLgtPosData(const LgtPosData *data) { unknown08 = data; }

void DrEnvironmentLgtList::setLightObj(DrLightObj *lightObj) { unknown10 = lightObj; }

} // namespace ml
