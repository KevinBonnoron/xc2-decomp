#include "dr/dr_environment_man.h"

#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"

namespace ml {
class DrFogMan;
class DrLightMan;

void DrEnvironmentObj::release() { m_flags |= FLAG_RELEASE << DrMan::s_nDblStockIdx; }

DrEnvironmentObj::DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan)
    : m_prev(nullptr), m_next(nullptr), m_drMan(drMan), m_lightMan(lightMan), m_fogMan(fogMan), m_offsetPos(0.0f, 0.0f, 0.0f), m_frame(0.0f),
      m_frameSpd(1.0f), m_maxFrame(0.0f), m_flags(0), m_group(0) {
  m_matrix = mm::Mat44::identity;
}

f32 DrEnvironmentObj::getFrame() const { return m_frame; }

f32 DrEnvironmentObj::getMaxFrame() const { return m_maxFrame; }

void DrEnvironmentObj::setFrameSpd(f32 speed) { m_frameSpd = speed; }

f32 DrEnvironmentObj::getFrameSpd() { return m_frameSpd; }

} // namespace ml
