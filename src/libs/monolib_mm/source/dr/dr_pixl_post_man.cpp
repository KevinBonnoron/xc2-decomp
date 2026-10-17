#include "dr/dr_pixl_post_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_obj_capture.h"
#include "dr/dr_pixl_post_obj_cube_map_ibl.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_obj_histgram.h"
#include "dr/dr_pixl_post_obj_rain_drop.h"
#include "dr/dr_pixl_post_obj_tmaa.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_obj_tssao.h"
#include "dr/dr_pixl_post_obj_volume.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_sky_dome.h"
#include "dr/dr_pixl_toon_grad.h"
#include "dr/dr_res_use_query_obj.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrPixlPostMan::setDownDepth() { m_flags |= FLAG_DEPTH_DOWN; }

void DrPixlPostMan::renderDeferred() {}

void DrPixlPostMan::renderDeferredLast() {
  if (m_toneMap != nullptr) {
    m_toneMap->fastRender();
  }
  if (m_histgram != nullptr) {
    m_histgram->render();
  }
}

DrPixlRenderTarget *DrPixlPostMan::getDownDepth() { return m_downDepths[DrMan::s_nDblIdx]; }

bool DrPixlPostMan::isCalcVolume() { return m_flags & FLAG_CALC_VOLUME; }

void DrPixlPostMan::setRefRactionMap() { m_flags |= FLAG_REFRACTION_MAP; }

bool DrPixlPostMan::renderRefractionBegin() {
  if (!(m_flags & FLAG_REFRACTION_MAP)) {
    return false;
  }
  if (m_refractionQuery != nullptr) {
    m_refractionQuery->begin(m_pixlMan->m_occQuery);
  }
  return true;
}

void DrPixlPostMan::renderRefractionEnd() {
  if (m_refractionQuery != nullptr) {
    m_refractionQuery->end();
  }
}

void DrPixlPostMan::renderSkyDome() {
  if (m_skyDome != nullptr) {
    m_skyDome->baseRender();
  }
}

void DrPixlPostMan::renderSkyGodRay() {
  if (m_skyDome != nullptr) {
    m_skyDome->godRayRender();
  }
}

void DrPixlPostMan::renderRainDrop() {
  if (m_rainDrop != nullptr) {
    m_rainDrop->render();
  }
}

void DrPixlPostMan::renderTMAA() {
  if (m_drMan->postParms[m_drMan->viewIndex]->tmaa) {
    m_tmaa->render();
  }
}

void DrPixlPostMan::renderDeferredFast_AfterTemporal() {
  if (m_tssao != nullptr) {
    m_tssao->render_afterTemporal();
  }
}

void DrPixlPostMan::fastRender() {
  if (m_cubeMapMultiIBL != nullptr) {
    m_cubeMapMultiIBL->render();
  }
  if (m_cubeMapIBL != nullptr) {
    m_cubeMapIBL->render();
  }
  if (m_toonGrad != nullptr) {
    m_toonGrad->render();
  }
}

void DrPixlPostMan::capRender() {
  if (m_capture != nullptr) {
    m_capture->render();
  }
}

void DrPixlPostMan::setBloom(bool isBloom) { m_flags = !isBloom ? m_flags & ~(FLAG_BLOOM | FLAG_VOLUME) : m_flags | (FLAG_BLOOM | FLAG_VOLUME); }

void DrPixlPostMan::setSSAO(bool isSSAO) {
  if (isSSAO) {
    m_flags |= FLAG_SSAO;
  } else if (m_flags & FLAG_SSAO) {
    m_flags &= ~FLAG_SSAO;
  }
}

DrPixlRenderTarget *DrPixlPostMan::getOldDownDepth() { return m_downDepths[DrMan::s_nDblStockIdx]; }

void DrPixlPostMan::setToneMaping(bool isToneMaping) { m_flags = !isToneMaping ? m_flags & ~FLAG_TONE_MAPING : m_flags | FLAG_TONE_MAPING; }

void DrPixlPostMan::setVolume(bool isVolume) { m_flags = !isVolume ? m_flags & ~FLAG_VOLUME : m_flags | FLAG_VOLUME; }

void DrPixlPostMan::set3DLut(bool is3DLut) { m_flags = !is3DLut ? m_flags & ~FLAG_3D_LUT : m_flags | FLAG_3D_LUT; }

void DrPixlPostMan::setSSAOAv(bool isSSAO) {
  if (isSSAO) {
    m_flags |= FLAG_SSAO;
  } else if (m_flags & FLAG_SSAO) {
    m_flags &= ~FLAG_SSAO;
  }
}

void DrPixlPostMan::setVolumePos(const mm::Vec3 &pos) {
  if (m_volume != nullptr) {
    m_volume->m_pos = pos;
  }
}

void DrPixlPostMan::setDepthFieldParm(f32 distance, f32 range, f32 strength) {}

void DrPixlPostMan::setBlurParm(f32 strength, f32 sub) {}

bool DrPixlPostMan::isToneMaping() { return m_flags & FLAG_TONE_MAPING; }

bool DrPixlPostMan::isBloom() { return m_flags & FLAG_BLOOM; }

bool DrPixlPostMan::isCalcBloom() { return m_flags & FLAG_CALC_BLOOM; }

bool DrPixlPostMan::is3DLut() { return m_flags & FLAG_3D_LUT; }

bool DrPixlPostMan::isVolume() { return m_flags & FLAG_VOLUME; }

bool DrPixlPostMan::isBluer() { return m_flags & FLAG_BLUR; }

bool DrPixlPostMan::isDepthField() { return m_flags & FLAG_DEPTH_FIELD; }

bool DrPixlPostMan::isSSAO() { return m_flags & FLAG_SSAO; }

bool DrPixlPostMan::isSSS() { return m_flags & FLAG_SSS; }

bool DrPixlPostMan::isReflection() { return m_flags & FLAG_REFLECTION; }

bool DrPixlPostMan::isChgShader() { return m_flags & FLAG_CHG_SHADER; }

bool DrPixlPostMan::isDepthDown() { return m_flags & FLAG_DEPTH_DOWN; }

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonGradTex() const {
  if (m_toonGrad != nullptr) {
    return &m_toonGrad->getGradTex();
  }
  return nullptr;
}

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonDarkGradTex() const {
  if (m_toonGrad != nullptr) {
    return &m_toonGrad->getDarkGradTex();
  }
  return nullptr;
}

} // namespace ml
