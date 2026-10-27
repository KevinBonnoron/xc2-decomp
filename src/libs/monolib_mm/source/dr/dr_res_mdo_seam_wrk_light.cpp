#include "dr/dr_res_mdo_seam_wrk_light.h"
#include "mm_mtl/reference_object.h"

#include "dr/dr_environment_man.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_res_mdo_seam_res.h"

namespace ml {

f32 DrResMdoSeamWrkLight::SEAM_LIGHT_READ_CHECK = 5.0f;

DrResMdoSeamWrkLight::DrResMdoSeamWrkLight() : unknown08(nullptr), unknown10(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(0), unknown34(0), unknown38(0), unknown3a(0) {}

DrResMdoSeamWrkLight::~DrResMdoSeamWrkLight() { release(); }

void DrResMdoSeamWrkLight::objLgtRelease() { mm::mtl::safeRelease(unknown20); }

void DrResMdoSeamWrkLight::release() {
  objLgtRelease();
  unknown28 = nullptr;
  unknown3a = 0;
}

void DrResMdoSeamWrkLight::delCall() {
  objLgtRelease();
  unknown3a |= 1;
}

void DrResMdoSeamWrkLight::setupWork(const MdsSeamLgtMapData *data) {
  unknown20 = DrMan::getIns()->unknown598->createObj(unknown28->m_buffer);
  unknown18 = data;
  unknown38 = 0;
  unknown3a = 0;
  unknown34 = data->unknown1c;
}

void DrResMdoSeamWrkLight::changeMemCall() {
  if (unknown20 != nullptr) {
    unknown20->changeMemCall(unknown28->m_buffer);
  }
}

} // namespace ml
