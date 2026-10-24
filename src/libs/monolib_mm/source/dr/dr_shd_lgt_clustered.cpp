#include "dr/dr_shd_lgt_clustered.h"

namespace ml {

const DrShdLgtClustered::ClusterSetting *DrShdLgtClustered::getClusterSetting(u32 cate) const { return &c_ClusterSettings[(unknown18 << 1) | (cate != 0)]; }

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::delViewInfo(int cate) {}

void DrShdLgtClustered::setPntLightUniformBlock(u32 cate, u32 index) { unknown20[cate].unknown00.setUniformBlock(index); }

void DrShdLgtClustered::setSptLightUniformBlock(u32 cate, u32 index) { unknown20[cate].unknown38.setUniformBlock(index); }

void DrShdLgtClustered::setPointerListUniformBlock(u32 cate, u32 index) { unknown20[cate].unknown70.setUniformBlock(index); }

void DrShdLgtClustered::setLightListUniformBlock(u32 cate, u32 index) {}

void DrShdLgtClustered::setParamUniformBlock(u32 cate, u32 index) { unknown20[cate].unknown118.setUniformBlock(index); }

void DrShdLgtClustered::setPntLightStorageBuffer(u32 cate, u32 index) { unknown20[cate].unknown00.setStorageBuffer(index); }

void DrShdLgtClustered::setSptLightStorageBuffer(u32 cate, u32 index) { unknown20[cate].unknown38.setStorageBuffer(index); }

void DrShdLgtClustered::setPointerListStorageBuffer(u32 cate, u32 index) { unknown20[cate].unknown70.setStorageBuffer(index); }

void DrShdLgtClustered::setLightListStorageBuffer(u32 cate, u32 index) { unknown20[cate].unknowna8.setStorageBuffer(index); }

void DrShdLgtClustered::setParamStorageBuffer(u32 cate, u32 index) { unknown20[cate].unknown118.setStorageBuffer(index); }

grlib::CGLibTexture *DrShdLgtClustered::getLightListTexture(u32 cate) const { return nullptr; }

void DrShdLgtClustered::beginLightList() { unknown20[unknown08].unknown188 = static_cast<u8 *>(unknown20[unknown08].unknowna8.getBuff()); }

void DrShdLgtClustered::setLightListData(u32 index, int data) { unknown20[unknown08].unknown188[index] = data; }

u8 DrShdLgtClustered::getLightListData(u32 index) { return unknown20[unknown08].unknown188[index]; }

void DrShdLgtClustered::endLightList() { unknown20[unknown08].unknowna8.updateData(); }

void DrShdLgtClustered::debugRender() {}

} // namespace ml
