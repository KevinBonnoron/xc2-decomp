#include "dr/dr_res_mdo_seam_wrk_light.h"
#include "mm_mtl/reference_object.h"

#include "dr/dr_environment_man.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_res_mdo_seam_res.h"

namespace ml {

f32 DrResMdoSeamWrkLight::SEAM_LIGHT_READ_CHECK = 5.0f;

DrResMdoSeamWrkLight::DrResMdoSeamWrkLight()
    : unknown08(nullptr), unknown10(nullptr), m_drEnvironmentObj(nullptr), m_drResMdoSeamMemObj(nullptr), unknown30(0), unknown34(0), unknown38(0), unknown3a(0) {}

DrResMdoSeamWrkLight::~DrResMdoSeamWrkLight() { release(); }

void DrResMdoSeamWrkLight::objLgtRelease() { mm::mtl::safeRelease(m_drEnvironmentObj); }

void DrResMdoSeamWrkLight::release() {
  objLgtRelease();
  m_drResMdoSeamMemObj = nullptr;
  unknown3a = 0;
}

void DrResMdoSeamWrkLight::delCall() {
  objLgtRelease();
  unknown3a |= 1;
}

void DrResMdoSeamWrkLight::setupWork(const MdsSeamLgtMapData *data) {
  m_drEnvironmentObj = DrMan::getIns()->m_drEnvironmentMan->createObj(m_drResMdoSeamMemObj->m_buffer);
  m_mdsSeamLgtMapData = data;
  unknown38 = 0;
  unknown3a = 0;
  unknown34 = data->unknown1c;
}

void DrResMdoSeamWrkLight::changeMemCall() {
  if (m_drEnvironmentObj != nullptr) {
    m_drEnvironmentObj->changeMemCall(m_drResMdoSeamMemObj->m_buffer);
  }
}

} // namespace ml
