#include "dr/dr_pixl_post_obj_cube_map_ibl.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_cube_map_mip_map.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjCubeMapIBL::~DrPixlPostObjCubeMapIBL() {
  if (m_premTexture[0] != nullptr) {
    delete m_premTexture[0];
    m_premTexture[0] = nullptr;
  }
  if (m_premTexture[1] != nullptr) {
    delete m_premTexture[1];
    m_premTexture[1] = nullptr;
  }
  if (m_uniformBlock != nullptr) {
    delete m_uniformBlock;
    m_uniformBlock = nullptr;
  }
}

void DrPixlPostObjCubeMapIBL::update() {}

void DrPixlPostObjCubeMapIBL::setUniformBlock(u32 index) const { m_uniformBlock->setUniformBlock(index); }

void DrPixlPostObjCubeMapIBL::setStorageBuffer(u32 index) const { m_uniformBlock->setStorageBuffer(index); }

u32 DrPixlPostObjCubeMapIBL::getPremMipCount() const { return m_premMipCount; }

grlib::CGLibTextureBuffer *DrPixlPostObjCubeMapIBL::getPremTexture() const { return m_premTexture[unknown214]->unknown70; }

const mm::Mat44 &DrPixlPostObjCubeMapIBL::getSHMatrix(u32 index) const { return m_shMatrix[unknown214][index]; }

void DrPixlPostObjCubeMapIBL::updateUB_ToProxySpace(u8 *work) { grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(work), unknown1c0); }

void DrPixlPostObjCubeMapIBL::updateUB_ShMatrixList(u8 *work) { grlib::ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(work), &m_shMatrix[unknown214][0], 3); }

void DrPixlPostObjCubeMapIBL::debugRender() {
  DrPixlPostParm *parm = unknown00->unknown120[unknown00->unknown1c98];
  u32 level = parm->unknown24c < m_premMipCount ? parm->unknown24c : m_premMipCount;
  f32 scale = parm->getToneMapOn() ? unknown00->unknown78->unknown7f0->unknown188 : 1.0f;
  for (int face = 0; face < 6; face++) {
    unknown00->unknown78->debugRenderCube(*m_premTexture[unknown214]->unknown70, face, level, false, 800 + face * 129, 0, 128, 128, true, scale);
  }
}

} // namespace ml
