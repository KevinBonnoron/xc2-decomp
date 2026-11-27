#include "dr/dr_pixl_shadow_obj.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_shd_pxl_wrk_tex.h"
#include "dr/dr_pixl_man.h"
#include "grlib/cglib_gpu_cache.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrPixlShadowObj::afterUpdate() {}

bool DrPixlShadowObj::dispChk() { return true; }

void DrPixlShadowObj::renderLight() {}

void DrPixlShadowObj::debugInfo() {}

void DrPixlShadowObj::stockTile() {}

void DrPixlShadowObj::update() {}

bool DrPixlShadowObj::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return true; }

int DrPixlShadowObj::clipTypeChk(const mm::Vec3 &position, f32 value) { return 0; }

bool DrPixlShadowObj::setSptCalcPos(const mm::Vec3 &position, f32 value) { return true; }

const f32 *DrPixlShadowObj::getParmTbl() const { return unknown60.rows[0]; }

void DrPixlShadowObj::createWork(DrLightObj *light, int index, MdoShdPxlWrkTex *work) {
  m_mdoShdPxlWrkTex = work;
  unknown4a = index;
  m_drLightObj = light;
  m_cGLibDblUniformBlock.release();
  if (unknown4c == 1) {
    m_cGLibDblUniformBlock.setup(0x50);
  } else {
    m_cGLibDblUniformBlock.setup(0x40);
  }
}

void DrPixlShadowObj::releaseWork() { m_cGLibDblUniformBlock.release(); }

void DrPixlShadowObj::setInstSelMapShadow(bool value) {
  if (value) {
    unknown50 |= 4;
  } else {
    unknown50 &= ~4;
  }
}

void DrPixlShadowObj::renderSetup() {
  if (!(unknown50 & 1)) {
    m_mdoShdPxlWrkTex->clearDepth(false);
    m_drMan->m_drAPCache->shadowBegin();
    DrAPGxType::beginShadow();
    m_drMan->m_drPixlMan->unknown858 = 0;
    m_mdoShdPxlWrkTex->setRenderTarget();
    m_drMan->m_drCalcMan->m_drCalcViewWork->shadowBegin(unknown60);
    unknown50 |= 1;
  }
}

bool DrPixlShadowObj::renderEnd() {
  if (unknown50 & 1) {
    grlib::CGLibGPUCache::depthInvalidate(*m_mdoShdPxlWrkTex->unknown120);
    DrAPGxType::endShadow();
    m_drMan->m_drCalcMan->shadowEnd();
    return true;
  }
  return false;
}

void DrPixlShadowObj::getScaleTranslateToFit(mm::Mat44 *mat, const mm::Vec3 &max, const mm::Vec3 &min) {
  mat->rows[0][0] = 2.0f / (max.x - min.x);
  mat->rows[1][0] = 0.0f;
  mat->rows[2][0] = 0.0f;
  mat->rows[3][0] = -(max.x + min.x) / (max.x - min.x);
  mat->rows[0][1] = 0.0f;
  mat->rows[1][1] = 2.0f / (max.y - min.y);
  mat->rows[2][1] = 0.0f;
  mat->rows[3][1] = -(max.y + min.y) / (max.y - min.y);
  mat->rows[0][2] = 0.0f;
  mat->rows[1][2] = 0.0f;
  mat->rows[2][2] = 2.0f / (max.z - min.z);
  mat->rows[3][2] = -(max.z + min.z) / (max.z - min.z);
  mat->rows[0][3] = 0.0f;
  mat->rows[1][3] = 0.0f;
  mat->rows[2][3] = 0.0f;
  mat->rows[3][3] = 1.0f;
}

// 1.0.0: 0x710085e754, 179 instructions. `side` and `top` are declared before `forward`: SROA creates the phis of the normalisations in the order of the allocas, which gives the rank of the
// components of `forward` that the game's operand order of the cross product needs (with `forward` declared first the products `up.y * forward.z` and `up.y * forward.x` are swapped).
void DrPixlShadowObj::getLightMatrix(mm::Mat44 &matrix, const mm::Vec3 &position, const mm::Vec3 &target, const mm::Vec3 &up) {
  mm::Vec3 side;
  mm::Vec3 top;
  mm::Vec3 forward = position - target;
  forward.unknown001();
  side.unknown004(up, forward);
  side.unknown001();
  top.unknown004(forward, side);
  top.unknown001();
  matrix.rows[0][0] = side.x;
  matrix.rows[0][1] = top.x;
  matrix.rows[0][2] = forward.x;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = side.y;
  matrix.rows[1][1] = top.y;
  matrix.rows[1][2] = forward.y;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = side.z;
  matrix.rows[2][1] = top.z;
  matrix.rows[2][2] = forward.z;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = -(side.x * position.x + side.y * position.y + side.z * position.z);
  matrix.rows[3][1] = -(top.x * position.x + top.y * position.y + top.z * position.z);
  matrix.rows[3][2] = -(forward.x * position.x + forward.y * position.y + forward.z * position.z);
  matrix.rows[3][3] = 1.0f;
}

} // namespace ml
