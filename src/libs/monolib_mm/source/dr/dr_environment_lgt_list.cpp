#include "dr/dr_environment_lgt_list.h"

namespace ml {

void DrEnvironmentLgtList::setLgtObjData(const LgtObjData *data) { m_lgtObjData = data; }

void DrEnvironmentLgtList::setLgtPosData(const LgtPosData *data) { m_lgtPosData = data; }

void DrEnvironmentLgtList::setLightObj(DrLightObj *lightObj) { m_lightObj = lightObj; }

} // namespace ml
