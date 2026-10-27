#include "dr/dr_environment_man.h"

#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"

namespace ml {
class DrFogMan;
class DrLightMan;

void DrEnvironmentObj::release() { unknown8c |= FLAG_RELEASE << DrMan::s_nDblStockIdx; }

DrEnvironmentObj::DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan)
    : unknown08(nullptr), unknown10(nullptr), unknown18(drMan), unknown20(lightMan), unknown28(fogMan), unknown70(0.0f, 0.0f, 0.0f), m_frame(0.0f), m_frameSpd(1.0f), m_maxFrame(0.0f), unknown8c(0),
      unknown90(0) {
  unknown30 = mm::Mat44::identity;
}

void DrEnvironmentMan::releaseObj(DrEnvironmentObj *obj) { obj->release(); }

f32 DrEnvironmentObj::getFrame() const { return m_frame; }

f32 DrEnvironmentObj::getMaxFrame() const { return m_maxFrame; }

void DrEnvironmentObj::setFrameSpd(f32 speed) { m_frameSpd = speed; }

f32 DrEnvironmentObj::getFrameSpd() { return m_frameSpd; }

} // namespace ml
