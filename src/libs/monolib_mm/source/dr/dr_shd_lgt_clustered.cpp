#include "dr/dr_shd_lgt_clustered.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"

namespace ml {

const DrShdLgtClustered::ClusterSetting *DrShdLgtClustered::getClusterSetting(u32 cate) const { return &c_ClusterSettings[(unknown18 << 1) | (cate != 0)]; }

void DrShdLgtClustered::convertToViewProj(mm::Vec3 &result, const mm::Vec2 &position) {
  DrMan *man = unknown10;
  const mm::Mat44 &matrix = man->unknowna0[unknown08]->unknown10->unknown1c0;
  f32 vec[4] = {position.x, position.y, 1.0f, 1.0f};
  f32 out[4];
  for (int i = 0; i < 4; i++) {
    out[i] = vec[0] * matrix.rows[0][i] + vec[1] * matrix.rows[1][i] + vec[2] * matrix.rows[2][i] + vec[3] * matrix.rows[3][i];
  }
  result.x = out[0] / out[3];
  result.y = out[1] / out[3];
  result.z = out[2] / out[3];
}
void DrShdLgtClustered::ssboBiteSwap() {
  ViewInfo &view = unknown20[unknown08];
  for (int i = 0; i < view.unknown150; i++) {
    view.unknown00.getBuff();
  }
  for (int i = 0; i < view.unknown154; i++) {
    view.unknown38.getBuff();
  }
}

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
