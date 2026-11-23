#include "dr/dr_requet_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrRequetIBL::DrRequetIBL(DrLightObjGlobalIBL *light) : m_drLightObjGlobalIBL(light), unknown20(reinterpret_cast<u64>(light)) {}

int DrRequetIBL::getTextureNum() const { return m_drLightObjGlobalIBL->m_textureNum; }

const grlib::CGLibTextureBuffer *DrRequetIBL::getTexture(u32 index) const { return &m_drLightObjGlobalIBL->m_texture[index]; }

const mm::Mat44 *DrRequetIBL::getSHMatrix(u32 index, u32 term) const { return m_drLightObjGlobalIBL->unknown840 + (index * DrLightObjGlobalIBL::SH_TERM_UNKNOWN_4 + term); }

const f32 *DrRequetIBL::getSHTerm(u32 index, u32 term) const { return m_drLightObjGlobalIBL->unknown450[index][term]; }

f32 DrRequetIBL::getSkyIntensity() const { return m_drLightObjGlobalIBL->m_skyIntensity; }

f32 DrRequetIBL::getDirLightIntensity() const { return m_drLightObjGlobalIBL->m_dirLightIntensity; }

const mm::Col3 *DrRequetIBL::getAdditionalAmbient() const { return &m_drLightObjGlobalIBL->m_additionalAmbient; }

int DrRequetIBL::getVersion() const { return m_drLightObjGlobalIBL->m_version; }

} // namespace ml
