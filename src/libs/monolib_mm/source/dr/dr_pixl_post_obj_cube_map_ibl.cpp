#include "dr/dr_pixl_post_obj_cube_map_ibl.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target_base.h"
#include "grlib/shd_util.h"

namespace ml {

void DrPixlPostObjCubeMapIBL::update() {}

void DrPixlPostObjCubeMapIBL::setUniformBlock(u32 index) const { m_uniformBlock->setUniformBlock(index); }

void DrPixlPostObjCubeMapIBL::setStorageBuffer(u32 index) const { m_uniformBlock->setStorageBuffer(index); }

u32 DrPixlPostObjCubeMapIBL::getPremMipCount() const { return m_premMipCount; }

grlib::CGLibTextureBuffer *DrPixlPostObjCubeMapIBL::getPremTexture() const { return m_premTexture[unknown214]->unknown70; }

const mm::Mat44 &DrPixlPostObjCubeMapIBL::getSHMatrix(u32 index) const { return m_shMatrix[unknown214][index]; }

void DrPixlPostObjCubeMapIBL::updateUB_ToProxySpace(u8 *work) { grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(work), unknown1c0); }

void DrPixlPostObjCubeMapIBL::updateUB_ShMatrixList(u8 *work) { grlib::ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(work), &m_shMatrix[unknown214][0], 3); }

} // namespace ml
