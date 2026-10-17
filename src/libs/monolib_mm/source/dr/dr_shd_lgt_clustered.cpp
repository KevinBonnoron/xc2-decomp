#include "dr/dr_shd_lgt_clustered.h"

namespace ml {

const DrShdLgtClustered::ClusterSetting *DrShdLgtClustered::getClusterSetting(u32 cate) const {
  return &c_ClusterSettings[(m_isLowResolution << 1) | (cate != 0)];
}

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::delViewInfo(int cate) {}

void DrShdLgtClustered::setPntLightUniformBlock(u32 cate, u32 index) { m_viewInfos[cate].pntLight.setUniformBlock(index); }

void DrShdLgtClustered::setSptLightUniformBlock(u32 cate, u32 index) { m_viewInfos[cate].sptLight.setUniformBlock(index); }

void DrShdLgtClustered::setPointerListUniformBlock(u32 cate, u32 index) { m_viewInfos[cate].pointerList.setUniformBlock(index); }

void DrShdLgtClustered::setLightListUniformBlock(u32 cate, u32 index) {}

void DrShdLgtClustered::setParamUniformBlock(u32 cate, u32 index) { m_viewInfos[cate].param.setUniformBlock(index); }

void DrShdLgtClustered::setPntLightStorageBuffer(u32 cate, u32 index) { m_viewInfos[cate].pntLight.setStorageBuffer(index); }

void DrShdLgtClustered::setSptLightStorageBuffer(u32 cate, u32 index) { m_viewInfos[cate].sptLight.setStorageBuffer(index); }

void DrShdLgtClustered::setPointerListStorageBuffer(u32 cate, u32 index) { m_viewInfos[cate].pointerList.setStorageBuffer(index); }

void DrShdLgtClustered::setLightListStorageBuffer(u32 cate, u32 index) { m_viewInfos[cate].lightList.setStorageBuffer(index); }

void DrShdLgtClustered::setParamStorageBuffer(u32 cate, u32 index) { m_viewInfos[cate].param.setStorageBuffer(index); }

grlib::CGLibTexture *DrShdLgtClustered::getLightListTexture(u32 cate) const { return nullptr; }

void DrShdLgtClustered::beginLightList() { m_viewInfos[m_cate].lightListData = static_cast<u8 *>(m_viewInfos[m_cate].lightList.getBuff()); }

void DrShdLgtClustered::setLightListData(u32 index, int data) { m_viewInfos[m_cate].lightListData[index] = data; }

u8 DrShdLgtClustered::getLightListData(u32 index) { return m_viewInfos[m_cate].lightListData[index]; }

void DrShdLgtClustered::endLightList() { m_viewInfos[m_cate].lightList.updateData(); }

void DrShdLgtClustered::debugRender() {}

} // namespace ml
