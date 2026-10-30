#include "dr/dr_pixl_man.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_res_use_query_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_gpu_cache.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_col4.h"

namespace ml {

static const s32 s_gbuffPixlObjs[] = {0, 1, 2, 3, 4, 8, 5, 6, 7, 15, 18};

static bool isDblPixlObj(int type) { return (0x27200ULL >> type) & 1; }

void DrPixlMan::captureMainFrameBuffer(grlib::CGLibTextureBuffer *buffer, u32 width, u32 height) {
  if (buffer->getWidth() != width || buffer->getHeight() != height || !buffer->isInitialized()) {
    grlib::CGLibTexture::createTextureBuff(*buffer, width, height, GRL_SURFACE_FORMAT_RGBA8);
  }
  grlib::CGLibRenderTarget renderTarget;
  renderTarget.setTextureInfo(*buffer);
  renderTarget.setRenderTarget();
  DrShdDataList *shdList = unknown08->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(1);
  grlib::CGLibRenderTarget *mainTarget = grlib::CGLibState::getMainRenderTarget();
  shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 1);
  shader->setDeclarationIdx(shader->getDeclarationOfs("MRT_NUM"), 1);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 offset = uniform.unknown001("gScal");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = unknown08->unknown5c0;
  f32 mainHeight = static_cast<f32>(mainTarget->unknownc0);
  f32 mainWidth = static_cast<f32>(mainTarget->unknownbc);
  f32 scale[4];
  scale[0] = (mainWidth - 1.0f) / mainWidth;
  scale[1] = (mainHeight - 1.0f) / mainHeight;
  scale[2] = 1.0f / (mainWidth + mainWidth);
  scale[3] = 1.0f / (mainHeight + mainHeight);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*mainTarget->unknown70, location);
  uniform.setF32SetVec4(offset, scale);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  grlib::CGLibState::setMainFrameBuffer();
}

void DrPixlMan::setupGodRay() {
  if (unknown08->unknown120[unknown08->unknown1c98]->m_bloomOn && (unknown7f0->unknown180->unknownf8 & DrPixlPostMan::FLAG_CALC_VOLUME)) {
    unknown7f0->unknown00[7][0]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  }
}

void DrPixlMan::lastTexRender() {
  DrShdDataList *shdList = unknown08->unknown80->unknown00;
  DrShdDataObj *shader = shdList->unknown001();
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 offset = uniform.unknown001("gScal");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrPixlPostParm *postParm = unknown08->unknown120[unknown08->unknown1c98];
  DrAPCache *apCache = unknown08->unknown5c0;
  f32 scale[4];
  if (!postParm->unknownfb2) {
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 0.0f;
    scale[3] = 0.0f;
    apCache->beginTexSampling(2, 0);
  } else {
    f32 height = static_cast<f32>(unknown7f0->unknown138->unknownc0);
    f32 width = static_cast<f32>(unknown7f0->unknown138->unknownbc);
    scale[0] = (width - 1.0f) / width;
    scale[1] = (height - 1.0f) / height;
    scale[2] = 1.0f / (width + width);
    scale[3] = 1.0f / (height + height);
    apCache->beginTexSampling(2, 1);
  }
  apCache->setTexture(*unknown7f0->unknown138->unknown70, location);
  uniform.setF32SetVec4(offset, scale);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
}

void DrPixlMan::debugIlluminanceRender() {
  DrMan *man = unknown08;
  DrShdDataList *shdList = man->unknown80->unknown00;
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  DrAPCache *apCache = man->unknown5c0;
  DrAPGxType::setupScreenQuads(false);
  DrShdDataObj *shader = shdList->getDebugShdObj(0xe);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  f32 scale[4];
  scale[0] = 1.0f / postParm->unknown484;
  scale[1] = 0.0f;
  scale[2] = 0.0f;
  scale[3] = 0.0f;
  uniform.setF32SetVec4(0, scale);
  uniform.updateData();
  uniform.setUniformBlock();
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown7f0->unknown138->unknown70, location);
  shdList->renderQuads();
}

void DrPixlMan::debugRender(int type, int x, int y, int width, int height, bool isAlpha) { debugRender(*getPixlObj(type)->unknown70, x, y, width, height, isAlpha, false, 1.0f, true); }

void DrPixlMan::endDeferredRenderTarget() { unknown7f0->unknown00[5][0]->setColorInvalidate(); }

void DrPixlMan::endSkyRenderTarget() {
  unknown7f0->unknown00[3][0]->setColorInvalidate();
  grlib::CGLibColorCtl::setColorChannelMask(grlib::GRL_MRT_TYPE_1, 1, 1, 1, 1);
}

void DrPixlMan::setMainViewPort() {
  grlib::LibMainStateViewPort viewPort(0.0f, 0.0f, static_cast<f32>(unknown08->unknown5b8->unknown18), static_cast<f32>(unknown08->unknown5b8->unknown1c), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::resetRenderTarget() { unknown858 = 0; }

void DrPixlMan::endGBuffTexture() {
  if (unknown08->unknown120[unknown08->unknown1c98]->m_toneMapOn) {
    unknown7f0->unknown00[6][0]->setColorInvalidate();
  }
}

void DrPixlMan::setMainRenderTarget() {
  if (unknown7f0->unknown1d0 == nullptr) {
    grlib::CGLibState::setMainFrameBuffer();
  } else {
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown1d0, grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::endRegisterRenderTarget();
  }
  setFinalViewPort();
}

void DrPixlMan::selectOpcaityBlmRenderTarget() {
  unknown858 = 6;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(6), grlib::GRL_MRT_TYPE_1);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(9), grlib::GRL_MRT_TYPE_2);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectOpcaityRenderTarget() {
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getPixlObj(int type) {
  if (isDblPixlObj(type)) {
    return unknown7f0->unknown00[type][DrMan::s_nDblIdx];
  }
  return unknown7f0->unknown00[type][0];
}

void DrPixlMan::setShadowObj(DrPixlShadowObj *shadowObj) {
  unknown848 = shadowObj;
  unknown850 = &shadowObj->unknown08;
}

void DrPixlMan::occRenderBegin(bool isFirst) {
  unknown858 = 0;
  if (isFirst) {
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
    grlib::CGLibState::endRegisterRenderTarget();
  } else {
    unknown7f0->unknown1b0->setRenderTarget();
  }
  DrPixlOccQuery *occQuery = unknown7f8;
  DrAPGxType::beginOccQuery();
  occQuery->unknown10->bindShdBoxVertex();
  occQuery->unknown28 = 0;
  occQuery->unknown18->setupShader(0u);
  occQuery->unknown24 = (occQuery->unknown18->unknown38 + occQuery->unknown18->unknown58)->getUniformBlockOfs("U_POST");
}

void DrPixlMan::setShadowDirRenderTarget(int index) { unknown800->unknown0010[index].unknown5940.setRenderTarget(); }

void DrPixlMan::setupShadowUnifrom(int index) { unknown850 = &unknown800->m_shadowDirUniform[index]; }

grlib::CGLibDepthTarget *DrPixlMan::getDepthObj() { return unknown7f0->unknown1a0[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer *DrPixlMan::getDammyWhiteTexObj() { return unknown838->unknown70; }

DrPixlMan::~DrPixlMan() { releaseColorBuffer(); }

void DrPixlMan::resetLightBuffOnly() {}

void DrPixlMan::createShadowParmDisplayList(wkPixlManRes *res) { res->unknown1d8 &= ~unknown001_32; }

void DrPixlMan::setupCate(int cate) {
  unknown7f0 = &unknown10[cate];
  unknown860 = cate;
}

void DrPixlMan::updateShadowDisplayList() {
  if (unknown7f0->unknown1d8 & unknown001_32) {
    createShadowParmDisplayList(unknown7f0);
  }
}

DrPixlRenderTarget *DrPixlMan::getResponsiveAAMask() { return unknown7f0->unknown00[18][0]; }

grlib::CGLibDepthTarget *DrPixlMan::getSeparateTransDepthObj() {
  if (unknown08->unknown120[unknown08->unknown1c98]->unknownfb4) {
    return unknown7f0->unknown1b0;
  }
  return getDepthObj();
}

void DrPixlMan::displayUpdate() { unknown7f0->unknown170->displayUpdate(); }

void DrPixlMan::renderEnd(int loop) {
  if (unknown7f0->unknown1d0 != nullptr) {
    unknown7f0->unknown1d0->setColorInvalidate();
  }
}

void DrPixlMan::selectZprepassRenderTarget() {
  unknown858 = 1;
  unknown85c = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectGBuffRenderTarget() { selectGBuffRenderTarget(0xff); }

bool DrPixlMan::selectGBuffRenderTarget(u32 mask) {
  if (unknown858 == 2 && unknown85c == mask) {
    return false;
  }
  unknown858 = 2;
  unknown85c = mask;
  grlib::CGLibState::beginRegisterRenderTarget();
  int mrt = 0;
  for (int i = 0; i < 11; i++) {
    if (mask & (1 << i)) {
      grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(s_gbuffPixlObjs[i]), static_cast<grlib::GrlMrtType>(mrt));
      mrt++;
    }
  }
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  return true;
}

void DrPixlMan::refractionGBuffInvalidate() {
  unknown7f0->unknown00[0][0]->setColorInvalidate();
  unknown7f0->unknown00[1][0]->setColorInvalidate();
  unknown7f0->unknown00[2][0]->setColorInvalidate();
  unknown7f0->unknown00[3][0]->setColorInvalidate();
  unknown7f0->unknown00[4][0]->setColorInvalidate();
}

void DrPixlMan::endGBuffRenderTarget() {
  unknown7f0->unknown00[0][0]->setColorInvalidate();
  unknown7f0->unknown00[1][0]->setColorInvalidate();
  unknown7f0->unknown00[2][0]->setColorInvalidate();
  unknown7f0->unknown00[3][0]->setColorInvalidate();
  unknown7f0->unknown00[4][0]->setColorInvalidate();
  unknown7f0->unknown00[8][0]->setColorInvalidate();
  unknown7f0->unknown00[5][0]->setColorInvalidate();
  unknown7f0->unknown00[6][0]->setColorInvalidate();
}

void DrPixlMan::selectDeferredRenderTarget() {
  if (unknown858 == 4) {
    return;
  }
  unknown858 = 4;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectRefractRenderTarget() {
  unknown858 = 5;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectPrePassWrkClearRenderTarget() {
  unknown858 = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  setMainViewPort();
}

void DrPixlMan::selectGlobalIBLIndexRenderTarget() {
  if (unknown858 == 11) {
    return;
  }
  unknown858 = 11;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(3), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::endGlobalIBLIndexRenderTarget() { unknown7f0->unknown00[3][0]->setColorInvalidate(); }

void DrPixlMan::alphaRenderTarget() {
  if (selectGBuffRenderTarget(0x1c0)) {
    setMainViewPort();
  }
}

void DrPixlMan::selectLightRenderTarget() {
  if (unknown858 != 14) {
    unknown858 = 14;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[5][0], grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[6][0], grlib::GRL_MRT_TYPE_1);
    grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1b8->unknown120);
    grlib::CGLibState::endRegisterRenderTarget();
    grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
    grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
  }
  setMainViewPort();
  DrAPGxType::setupDepthContl(true, false, 2);
}

void DrPixlMan::selectSubtractLightRenderTarget() {
  if (unknown858 != 16) {
    unknown858 = 16;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[2][0], grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
    grlib::CGLibState::endRegisterRenderTarget();
    grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_MIN, GRL_LOGIC_TYPE_COPY);
  }
  setMainViewPort();
  DrAPGxType::setupStencilTest(false, false, 7, true, 0, 8, 5, 0, 0, 0);
}

void DrPixlMan::skyRenderTarget() {
  if (unknown858 != 12) {
    unknown858 = 12;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[5][0], grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[3][0], grlib::GRL_MRT_TYPE_1);
    grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
    grlib::CGLibState::endRegisterRenderTarget();
    grlib::CGLibColorCtl::setColorChannelMask(grlib::GRL_MRT_TYPE_1, true, true, false, true);
    setMainViewPort();
  }
}

void DrPixlMan::skyVisibilityRenderTarget() {}

void DrPixlMan::skyGodRayRenderTarget() {
  if (selectGBuffRenderTarget(0x100)) {
    setMainViewPort();
  }
}

void DrPixlMan::renderRefractionMap(bool isRefractionMap, bool isHalfMap) { unknown7f0->unknown180->renderRefractionMap(isRefractionMap, isHalfMap); }

void DrPixlMan::renderSkyDome() { unknown7f0->unknown180->renderSkyDome(); }

void DrPixlMan::renderSkyGodRay() { unknown7f0->unknown180->renderSkyGodRay(); }

void DrPixlMan::renderRainDrop() { unknown7f0->unknown180->renderRainDrop(); }

void DrPixlMan::renderTMAA() { unknown7f0->unknown180->renderTMAA(); }

void DrPixlMan::renderRefractionEnd() {
  DrPixlTileParm *tileParm = unknown08->unknown180;
  if (!tileParm->unknown04[tileParm->unknown00][0].unknown00 && tileParm->unknown04[tileParm->unknown00][2].unknown00) {
    grlib::CGLibGPUCache::setTiledCacheAction(GRL_TILED_CACHE_ACTION_UNKNOWN_3);
    grlib::CGLibGPUCache::setTiledCacheAction(GRL_TILED_CACHE_ACTION_UNKNOWN_2);
  }
  DrResUseQueryObj *query = unknown7f0->unknown180->unknownf0;
  if (query != nullptr) {
    query->end();
  }
}

bool DrPixlMan::isRefractionMap() { return unknown7f0->unknown180->unknownd0 != nullptr; }

void DrPixlMan::thicknessFirstBegin() {
  unknown858 = 13;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown148, grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() { return unknown7f0->unknown148; }

void DrPixlMan::thicknessFirstEnd() { unknown7f0->unknown148->setColorInvalidate(); }

void DrPixlMan::lastDeferredRender() { unknown7f0->unknown170->lastDeferredRender(); }

void DrPixlMan::occRenderEnd() { DrAPGxType::endOccQuery(); }

void DrPixlMan::depCheckBegin(bool isDblDepth) {
  unknown858 = 0;
  if (isDblDepth) {
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
    grlib::CGLibState::endRegisterRenderTarget();
  } else {
    unknown7f0->unknown1b0->setRenderTarget();
  }
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
  grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
}

void DrPixlMan::depCheckEnd() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrPixlMan::shadowCallDirBegin() {
  unknown08->unknown5c0->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowCallDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::shadowDirBegin() {
  unknown08->unknown5c0->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::callShadowCacheUpdate(bool isAll) { unknown800->callShadowCacheUpdate(isAll); }

void DrPixlMan::callShadowCacheVariance() { unknown800->callShadowCacheVariance(); }

void DrPixlMan::callFgShadowCacheUpdate() { unknown800->callFgShadowCacheUpdate(); }

void DrPixlMan::fastRender() {
  unknown7f0->unknown180->fastRender();
  if (unknown860 == 0) {
    unknown800->shadowCacheRender();
    unknown800->fastRender();
  }
}

void DrPixlMan::lastCapRender() { unknown7f0->unknown180->capRender(); }

void DrPixlMan::setFinalViewPort() {
  grlib::LibMainStateViewPort viewPort(0.0f, 0.0f, static_cast<f32>(unknown08->unknown5b8->unknown20), static_cast<f32>(unknown08->unknown5b8->unknown24), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::setMainSRGBRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void DrPixlMan::setMainSRGBAfterRenderTarget() {}

void DrPixlMan::changeColorBuff() {
  unknown7f0->unknown138->setColorInvalidate();
  if (unknown7f0->unknown138 == unknown7f0->unknown130) {
    unknown7f0->unknown138 = unknown7f0->unknown140;
  }
}

void DrPixlMan::changeHDRBuff(DrPixlRenderTarget *hdrBuff) {
  if (unknown7f0->unknown138 == unknown7f0->unknown140) {
    unknown7f0->unknown138 = hdrBuff;
  }
  unknown7f0->unknown140 = hdrBuff;
}

void DrPixlMan::setTempColorBuff() { getTempColorBuff()->setRenderTarget(); }

DrPixlRenderTarget *DrPixlMan::getTempColorBuff() {
  if (unknown7f0->unknown138 != unknown7f0->unknown130) {
    return unknown7f0->unknown130;
  }
  return unknown7f0->unknown140;
}

void DrPixlMan::pixelEndMode() { unknown800->endMode(); }

void DrPixlMan::setToneAveRange(f32 min, f32 max) {
  unknown7f0->unknown194 = min;
  unknown7f0->unknown198 = max;
}

grlib::CGLibTextureBuffer *DrPixlMan::getDammyTexObj() { return unknown830->unknown70; }

void DrPixlMan::offScreenAlphaEnd() { DrAPGxType::setupAlphaChanel(true); }

void DrPixlMan::debugDeferredRenderAlbedoAndFogRatio(int x, int y, int width, int height) {}

DrPixlRenderTarget *DrPixlMan::getDeactivePixlObj(int type) {
  if (!isDblPixlObj(type)) {
    return nullptr;
  }
  return unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1];
}

grlib::CGLibDepthTarget *DrPixlMan::getDeactiveDepthObj() { return unknown7f0->unknown1a0[DrMan::s_nDblStockIdx]; }

void DrPixlMan::swapPixlObj(int type) {
  if (isDblPixlObj(type)) {
    DrPixlRenderTarget *deactive = unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1];
    unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1] = unknown7f0->unknown00[type][DrMan::s_nDblIdx];
    unknown7f0->unknown00[type][DrMan::s_nDblIdx] = deactive;
  }
}

DrPixlRenderTarget *DrPixlMan::getSpecIBLObj() {
  int type = unknown08->unknown120[unknown08->unknown1c98]->unknown1061 ? 9 : 11;
  return unknown08->unknown78->getPixlObj(type);
}

DrPixlRenderTarget *DrPixlMan::getDiffIBLObj() {
  int type = unknown08->unknown120[unknown08->unknown1c98]->unknown1061 ? 14 : 10;
  return unknown08->unknown78->getPixlObj(type);
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() const { return unknown7f0->unknown148; }

} // namespace ml
