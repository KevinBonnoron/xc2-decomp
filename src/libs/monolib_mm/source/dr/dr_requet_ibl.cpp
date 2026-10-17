#include "dr/dr_requet_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrRequetIBL::DrRequetIBL(DrLightObjGlobalIBL *light) : m_light(light), _20(light) {}

int DrRequetIBL::getTextureNum() const { return m_light->m_textureNum; }

const grlib::CGLibTextureBuffer *DrRequetIBL::getTexture(u32 index) const { return &m_light->m_textures[index]; }

const mm::Mat44 *DrRequetIBL::getSHMatrix(u32 index, u32 term) const {
  return m_light->m_shMatrices + (index * DrLightObjGlobalIBL::SH_TERM_NUM + term);
}

const f32 *DrRequetIBL::getSHTerm(u32 index, u32 term) const { return m_light->m_shTerms[index][term]; }

f32 DrRequetIBL::getSkyIntensity() const { return m_light->m_skyIntensity; }

f32 DrRequetIBL::getDirLightIntensity() const { return m_light->m_dirLightIntensity; }

const mm::Col3 *DrRequetIBL::getAdditionalAmbient() const { return &m_light->m_additionalAmbient; }

int DrRequetIBL::getVersion() const { return m_light->m_version; }

} // namespace ml
