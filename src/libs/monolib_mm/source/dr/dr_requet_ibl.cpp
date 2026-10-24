#include "dr/dr_requet_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrRequetIBL::DrRequetIBL(DrLightObjGlobalIBL *light) : unknown18(light), _20(light) {}

int DrRequetIBL::getTextureNum() const { return unknown18->unknown14; }

const grlib::CGLibTextureBuffer *DrRequetIBL::getTexture(u32 index) const { return &unknown18->unknown78[index]; }

const mm::Mat44 *DrRequetIBL::getSHMatrix(u32 index, u32 term) const { return unknown18->unknown840 + (index * DrLightObjGlobalIBL::SH_TERM_NUM + term); }

const f32 *DrRequetIBL::getSHTerm(u32 index, u32 term) const { return unknown18->unknown450[index][term]; }

f32 DrRequetIBL::getSkyIntensity() const { return unknown18->unknown3b0; }

f32 DrRequetIBL::getDirLightIntensity() const { return unknown18->unknown3b4; }

const mm::Col3 *DrRequetIBL::getAdditionalAmbient() const { return &unknown18->unknown3a0; }

int DrRequetIBL::getVersion() const { return unknown18->unknown08; }

} // namespace ml
