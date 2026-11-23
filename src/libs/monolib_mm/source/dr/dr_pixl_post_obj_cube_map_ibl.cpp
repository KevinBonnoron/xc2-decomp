#include "dr/dr_pixl_post_obj_cube_map_ibl.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_cube_map_mip_map.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlPostObjCubeMapIBL::DrPixlPostObjCubeMapIBL(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan), unknown18(true), unknown210(0), unknown214(0) {
  for (int i = 0; i < 2; i++) {
    m_premTexture[i] = new (drMan->unknown0c) DrPixlRenderCubeMapMipMap(drMan);
    m_premTexture[i]->setTextureInfo(64.0f, 64.0f, GRL_SURFACE_FORMAT_R11G11B10F, false, 0);
  }
  m_premMipCount = 5;
  m_uniformBlock = new (drMan->unknown10) grlib::CGLibDblUniformBlock();
  m_uniformBlock->setup(0x110);
  memset(m_shMatrix, 0, sizeof(m_shMatrix));
  unknown1c0 = mm::Mat44::identity;
  unknown200 = mm::Vec3::zero;
}

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

void DrPixlPostObjCubeMapIBL::updateUB_IBLPos_WS(u8 *work) {
  // Reopen 2026-11-14 (P2): the game loads the whole IBL position (x and y in one 64-bit load, then z) before it stores the
  // first component of the vector (0x7100836be8); the local copy places the loads there.
  mm::Vec3 iblPosition = unknown200;
  mm::Vec4 position(iblPosition, 1.0f);
  grlib::ShdF32SetVec4(reinterpret_cast<f32 *>(work), &position.x);
}

void DrPixlPostObjCubeMapIBL::debugRender() {
  DrPixlPostParm *parm = m_drMan->unknown120[m_drMan->unknown1c98];
  u32 level = parm->unknown24c < m_premMipCount ? parm->unknown24c : m_premMipCount;
  f32 scale = parm->getToneMapOn() ? m_drMan->m_drPixlMan->unknown7f0->unknown188 : 1.0f;
  for (int face = 0; face < 6; face++) {
    m_drMan->m_drPixlMan->debugRenderCube(*m_premTexture[unknown214]->unknown70, face, level, false, 800 + face * 129, 0, 128, 128, true, scale);
  }
}

} // namespace ml
