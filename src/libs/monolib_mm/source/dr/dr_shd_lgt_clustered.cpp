#include "dr/dr_shd_lgt_clustered.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/mem_manager.h"
#include <string.h>

namespace ml {

const DrShdLgtClustered::unknown001 DrShdLgtClustered::c_ClusterSettings[4] = {
    {20, 12, 16, 20, 256},
    {5, 3, 4, 5, 16},
    {5, 3, 4, 20, 128},
    {5, 3, 4, 5, 16},
};

DrShdLgtClustered::DrShdLgtClustered(DrMan *drMan, bool isLowResolution)
    : DrShdLgtDynamic(drMan), unknown18(isLowResolution), unknown660(nullptr), unknown668(0), unknown66c(0), unknown670(nullptr), unknown678(nullptr), unknown680(nullptr), unknown688(nullptr),
      unknown690(0), unknown694(0), unknown698(nullptr) {
  createWork();
}

DrShdLgtClustered::~DrShdLgtClustered() {
  if (unknown660 != nullptr) {
    mtl::MemManager::deallocate(unknown660, 0, false);
    unknown660 = nullptr;
  }
}

const DrShdLgtClustered::unknown001 *DrShdLgtClustered::getClusterSetting(u32 cate) const { return &c_ClusterSettings[(unknown18 << 1) | (cate != 0)]; }

void DrShdLgtClustered::stockBegin() {
  unknown002 &view = unknown20[unknown08];
  const unknown001 *setting = getClusterSetting(unknown08);
  view.unknown150 = 0;
  view.unknown154 = 0;
  view.unknown158 = 0;
  unknown668 = view.unknown00.m_size;
  unknown66c = view.unknown38.m_size;
  unknown670 = view.unknown00.getBuff();
  unknown678 = view.unknown38.getBuff();
  u32 clusterNum = setting->unknown00 * setting->unknown04 * setting->unknown08;
  memset(unknown680, 0, clusterNum * sizeof(void *));
  memset(unknown688, 0, clusterNum * sizeof(void *));
  unknown690 = 0;
}

// The game computes the three components before the first store (the result may alias an operand) and stores z, y, x (0x7100892610:
// stp for y and z first, 0x710089262c: x after the square root), which mm::Vec3::unknown004 does.
void DrShdLgtClustered::createPlaneEquation(mm::Vec3 &result, const mm::Vec3 &first, const mm::Vec3 &second) {
  result.unknown004(first, second);
  result.unknown001();
}

bool DrShdLgtClustered::planeVsCone(const mm::Vec3 &first, const mm::Vec3 &normal, const mm::Vec3 &second, const mm::Vec3 &direction, f32 range, f32 angle) const {
  // The two vector locals place the loads as the game does (0x71008923d8-0x71008923e0: the normal is loaded whole before the direction); the 99
  // instructions are the same with the plain member expressions but scheduled differently.
  mm::Vec3 offset = second - first;
  f32 distance = offset.x * normal.x + offset.y * normal.y + offset.z * normal.z;
  if (distance > range) {
    return false;
  }
  if (distance <= 0.001f) {
    return true;
  }
  f32 planeAngle = mm::acos(distance / range);
  mm::Vec3 axis = normal;
  f32 directionAngle = mm::acos(-(axis.y * direction.y) - axis.x * direction.x - axis.z * direction.z);
  return planeAngle + angle >= directionAngle - 0.052;
}

void DrShdLgtClustered::addViewInfo(int cate) {
  unknown002 &view = unknown20[cate];
  // The game reads the cluster setting before the two float stores (0x7100891920-0x7100891940: the setting address is computed first); with the call
  // after them clang merges the stores into one 64-bit store.
  const unknown001 *setting = getClusterSetting(cate);
  view.unknown160 = 1.36f;
  view.unknown15c = 5.0f;
  view.unknown168[0] = 0.0f;
  for (int i = 0; i <= setting->unknown08; i++) {
    f32 depth;
    if (i == 0) {
      depth = -5.0f;
    } else {
      depth = view.unknown168[i - 1] * view.unknown160;
    }
    view.unknown168[i] = depth;
  }
}

void DrShdLgtClustered::convertToViewProj(mm::Vec3 &result, const mm::Vec2 &position) {
  DrMan *man = m_drMan;
  const mm::Mat44 &matrix = man->unknowna0[unknown08]->m_drCalcViewWork->unknown1c0;
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
  unknown002 &view = unknown20[unknown08];
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

void DrShdLgtClustered::beginLightList() { unknown20[unknown08].m_lightListData = static_cast<u8 *>(unknown20[unknown08].unknowna8.getBuff()); }

void DrShdLgtClustered::setLightListData(u32 index, int data) { unknown20[unknown08].m_lightListData[index] = data; }

u8 DrShdLgtClustered::getLightListData(u32 index) { return unknown20[unknown08].m_lightListData[index]; }

void DrShdLgtClustered::endLightList() { unknown20[unknown08].unknowna8.updateData(); }

void DrShdLgtClustered::debugRender() {}

} // namespace ml
