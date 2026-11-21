#include "dr/dr_pixl_man.h"

#include <string.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

static const s32 unknown003[] = {0, 1, 2, 3, 4, 8, 5, 6, 7, 15, 18}; // Inferred role: pixel objects of the geometry buffers; original name unknown.

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
  if (unknown08->unknown120[unknown08->unknown1c98]->m_bloomOn && (unknown7f0->unknown180->unknownf8 & DrPixlPostMan::FLAG_UNKNOWN_16)) {
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

void DrPixlMan::toneMapRender(bool isDepth) {
  DrMan *man = unknown08;
  DrShdDataList *shdList = man->unknown80->unknown00;
  DrPixlRenderTarget *downDepth = unknown7f0->unknown180->getDownDepth();
  DrCalcViewWork *viewWork = man->unknown580->unknown10;
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  DrAPCache *apCache = man->unknown5c0;
  DrAPGxType::setupScreenQuads(false);
  DrShdDataObj *shader = shdList->getPostShdObj(2);
  bool isDepthTest = downDepth != nullptr && isDepth;
  if (isDepthTest) {
    DrAPGxType::setupDepthContl(true, true, 7);
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 2);
  } else {
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 1);
  }
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  f32 tone[4];
  tone[0] = unknown7f0->unknown188;
  tone[1] = viewWork->unknown180.rows[2][2];
  tone[2] = viewWork->unknown180.rows[3][2];
  tone[3] = 0.0f;
  uniform.setF32SetVec4(0, tone);
  f32 scale[4];
  if (!postParm->unknownfb2 || !isDepth) {
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
  uniform.setF32SetVec4(0x10, scale);
  if (isDepthTest) {
    f32 depthHeight = static_cast<f32>(downDepth->unknownc0);
    f32 depthWidth = static_cast<f32>(downDepth->unknownbc);
    tone[0] = (depthWidth - 1.0f) / depthWidth;
    tone[1] = (depthHeight - 1.0f) / depthHeight;
    tone[2] = 1.0f / (depthWidth + depthWidth);
    tone[3] = 1.0f / (depthHeight + depthHeight);
    uniform.setF32SetVec4(0x20, tone);
    int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
    apCache->beginTexSampling(2, 1);
    apCache->setTexture(*downDepth->unknown70, depthLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
    DrAPGxType::setupDepthContl(false, false, 7);
  } else {
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
  }
}

void DrPixlMan::gammaRender(bool isDepth) {
  DrMan *man = unknown08;
  DrShdDataList *shdList = man->unknown80->unknown00;
  DrPixlRenderTarget *downDepth = unknown7f0->unknown180->getDownDepth();
  DrCalcViewWork *viewWork = man->unknown580->unknown10;
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  DrAPCache *apCache = man->unknown5c0;
  DrAPGxType::setupScreenQuads(false);
  DrShdDataObj *shader = shdList->getSelectShdObj(5);
  bool isDepthTest = downDepth != nullptr && isDepth;
  if (isDepthTest) {
    DrAPGxType::setupDepthContl(true, true, 7);
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 2);
  } else {
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 1);
  }
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  f32 tone[4];
  tone[0] = unknown7f0->unknown188;
  tone[1] = viewWork->unknown180.rows[2][2];
  tone[2] = viewWork->unknown180.rows[3][2];
  tone[3] = 0.0f;
  uniform.setF32SetVec4(0, tone);
  f32 scale[4];
  if (!postParm->unknownfb2 || !isDepth) {
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 0.0f;
    scale[3] = 0.0f;
    apCache->beginTexSampling(2, 0);
  } else {
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 0.0f;
    scale[3] = 0.0f;
    apCache->beginTexSampling(2, 1);
  }
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  apCache->setTexture(*unknown7f0->unknown138->unknown70, location);
  uniform.setF32SetVec4(0x10, scale);
  if (isDepthTest) {
    int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
    f32 depthHeight = static_cast<f32>(downDepth->unknownc0);
    f32 depthWidth = static_cast<f32>(downDepth->unknownbc);
    tone[0] = (depthWidth - 1.0f) / depthWidth;
    tone[1] = (depthHeight - 1.0f) / depthHeight;
    tone[2] = 1.0f / (depthWidth + depthWidth);
    tone[3] = 1.0f / (depthHeight + depthHeight);
    uniform.setF32SetVec4(0x20, tone);
    apCache->beginTexSampling(2, 1);
    apCache->setTexture(*downDepth->unknown70, depthLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
    DrAPGxType::setupDepthContl(false, false, 7);
  } else {
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
  }
}

void DrPixlMan::offScreenAlphaRender() {
  DrAPGxType::setupScreenQuads(false);
  unknown7f0->unknown1d0->setRenderTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
  DrAPGxType::setupStencilTest(false, false, 7, false, 0, 0, 7, 0, 0, 0);
  DrShdDataList *shdList = unknown08->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x13);
  shdList->unknown002(shader);
  int location0 = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int location1 = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  f32 tone[4];
  tone[0] = unknown7f0->unknown188;
  tone[1] = 0.0f;
  tone[2] = 0.0f;
  tone[3] = 0.0f;
  uniform.setF32SetVec4(0, tone);
  uniform.updateData();
  uniform.setUniformBlock();
  DrAPCache *apCache = unknown08->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown7f0->unknown138->unknown70, location0);
  apCache->setTexture(*unknown7f0->unknown1d0->unknown70, location1);
  shdList->renderQuads();
  DrAPGxType::setupAlphaChanel(false);
}

void DrPixlMan::delViewInfo(int index) {
  unknown7f0 = &unknown10[index];
  unknown10[index].unknown1d8 = 0;
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 2; j++) {
      grlib::CGLibRenderTarget *target = unknown7f0->unknown00[i][j];
      if (target != nullptr) {
        target->releaseWork();
        delete target;
        unknown7f0->unknown00[i][j] = nullptr;
      }
    }
  }
  grlib::CGLibRenderTarget *target = unknown7f0->unknown148;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown148 = nullptr;
  }
  target = unknown7f0->unknown150;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown150 = nullptr;
  }
  target = unknown7f0->unknown158;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown158 = nullptr;
  }
  target = unknown7f0->unknown160;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown160 = nullptr;
  }
  target = unknown7f0->unknown168;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown168 = nullptr;
  }
  grlib::CGLibDepthTarget *depth;
  for (int j = 0; j < 2; j++) {
    depth = unknown7f0->unknown1a0[j];
    if (depth != nullptr) {
      delete depth;
      unknown7f0->unknown1a0[j] = nullptr;
    }
  }
  depth = unknown7f0->unknown1b0;
  if (depth != nullptr) {
    delete depth;
    unknown7f0->unknown1b0 = nullptr;
  }
  depth = unknown7f0->unknown1b8;
  if (depth != nullptr) {
    delete depth;
    unknown7f0->unknown1b8 = nullptr;
  }
  depth = unknown7f0->unknown1c0;
  if (depth != nullptr) {
    delete depth;
    unknown7f0->unknown1c0 = nullptr;
  }
  target = unknown7f0->unknown1e0;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown1e0 = nullptr;
  }
  target = unknown7f0->unknown1e8;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown1e8 = nullptr;
  }
  grlib::CGLibRenderArrayCubeMap *cubeMap = unknown7f0->unknown1f0;
  if (cubeMap != nullptr) {
    cubeMap->releaseWork();
    delete cubeMap;
    unknown7f0->unknown1f0 = nullptr;
  }
  target = unknown7f0->unknown1d0;
  if (target != nullptr) {
    target->releaseWork();
    delete target;
    unknown7f0->unknown1d0 = nullptr;
  }
  DrPixlDeferred *deferred = unknown7f0->unknown170;
  if (deferred != nullptr) {
    delete deferred;
    unknown7f0->unknown170 = nullptr;
  }
  DrPixlShadowMan *shadowMan = unknown7f0->unknown178;
  if (shadowMan != nullptr) {
    delete shadowMan;
    unknown7f0->unknown178 = nullptr;
  }
  DrPixlPostMan *postMan = unknown7f0->unknown180;
  if (postMan != nullptr) {
    delete postMan;
    unknown7f0->unknown180 = nullptr;
  }
  memset(unknown7f0, 0, sizeof(wkPixlManRes));
  unknown7f0 = unknown10;
}

void DrPixlMan::lastUpdate() { unknown7f8->update(); }

void DrPixlMan::lastRender() {
  unknown7f0->unknown180->render();
  DrPixlPostParm *postParm = unknown08->unknown120[unknown08->unknown1c98];
  if (!postParm->unknown1025) {
    if (postParm->unknown1028) {
      unknown800->debugShadowCacheRender();
    }
  } else {
    unknown7f0->unknown178->shadowRender();
  }
  postParm = unknown08->unknown120[unknown08->unknown1c98];
  if (postParm->unknown1027) {
    unknown7f0->unknown170->debugRender();
    postParm = unknown08->unknown120[unknown08->unknown1c98];
  }
  if (postParm->unknown10fe) {
    debugReductionRender();
  }
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

grlib::CGLibTextureBuffer *DrPixlMan::getSunShadowMap() { return unknown10[0].unknown170->getShadowMapTexture(); }

void DrPixlMan::resetColorBuff(bool isMain) {
  // The game never sets the registers of the last two arguments (calcColorBuffer does not read them): the original expressions
  // cannot be checked.
  calcColorBuffer(unknown7f0, static_cast<f32>(unknown08->unknown5b8->unknown18), static_cast<f32>(unknown08->unknown5b8->unknown1c), 0.0f, 0.0f);
  unknown7f0->unknown180->resetColorBuff();
  unknown7f0->unknown170->resetColorBuff();
  if (unknown08->unknown120[unknown08->unknown1c98]->unknownfe4 != 2) {
    if (unknown7f0->unknown1d8 & unknown001_4) {
      if (isMain) {
        unknown7f0->unknown1d8 |= unknown001_16;
        if (unknown7f0->unknown1d0 == nullptr) {
          unknown7f0->unknown1d0 = new (unknown08->unknown0c) DrPixlRenderTarget(unknown08);
        }
      } else {
        unknown7f0->unknown1d8 &= ~unknown001_16;
        grlib::CGLibRenderTarget *target = unknown7f0->unknown1d0;
        if (target != nullptr) {
          target->releaseWork();
          delete target;
          unknown7f0->unknown1d0 = nullptr;
        }
      }
    }
    unknown7f0->unknown1d8 |= unknown001_32;
    if ((unknown7f0->unknown1d8 & unknown001_4) && unknown7f0->unknown1d0 != nullptr) {
      unknown7f0->unknown1d0->setTextureInfo(
          static_cast<f32>(unknown08->unknown5b8->unknown20), static_cast<f32>(unknown08->unknown5b8->unknown24), DrAPCache::TEXTYPE_RGBA_8, true, DrPixlMemMan::get()->unknown430);
    }
  }
}

void DrPixlMan::calcColorBuffer(wkPixlManRes *res, f32 width, f32 height, f32 unknown1, f32 unknown2) {
  DrPixlPostParm *postParm = unknown08->unknown120[unknown08->unknown1c98];
  DrPixlMemMan *memMan = DrPixlMemMan::get();
  if (postParm->unknownfe4 == 3) {
    for (int i = 0; i < 19; i++) {
      f32 scale = DrPixlFormat::getPixelScale(i);
      f32 scaledWidth = scale * width;
      f32 scaledHeight = scale * height;
      if (res->unknown00[i][0] != nullptr) {
        res->unknown00[i][0]->setTextureInfo(scaledWidth, scaledHeight, DrPixlFormat::s_MrtFormat[i], true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown000[i][0]);
      }
      if (res->unknown00[i][1] != nullptr) {
        res->unknown00[i][1]->setTextureInfo(scaledWidth, scaledHeight, DrPixlFormat::s_MrtFormat[i], true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown000[i][1]);
      }
    }
    res->unknown1a0[0]->setTextureInfo(width, height, DrPixlFormat::s_ZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0c0[0]);
    res->unknown1a0[1]->setTextureInfo(width, height, DrPixlFormat::s_ZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0c0[1]);
  } else {
    u32 index = DrMan::s_nDblIdx;
    for (int i = 0; i < 19; i++) {
      f32 scale = DrPixlFormat::getPixelScale(i);
      if (res->unknown00[i][index] != nullptr && isDblPixlObj(i)) {
        res->unknown00[i][index]->setTextureInfo(scale * width, scale * height, DrPixlFormat::s_MrtFormat[i], true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown000[i][index]);
      }
    }
    res->unknown1a0[index]->setTextureInfo(width, height, DrPixlFormat::s_ZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0c0[index]);
    if (postParm->unknownfe4 == 2) {
      return;
    }
    for (int i = 0; i < 19; i++) {
      f32 scale = DrPixlFormat::getPixelScale(i);
      if (res->unknown00[i][0] != nullptr && !isDblPixlObj(i)) {
        res->unknown00[i][0]->setTextureInfo(scale * width, scale * height, DrPixlFormat::s_MrtFormat[i], true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown000[i][0]);
      }
    }
  }
  if (res->unknown148 != nullptr) {
    res->unknown148->setTextureInfo(width, height, DrPixlFormat::s_BackFaceDepth, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0bc);
  }
  // The reduced sizes are integers: the game truncates each size (fcvtzs at 0x710083d090 and 0x710083d098), scales it, truncates the
  // product again (0x710083d0ac and 0x710083d0cc) and converts it back to float (scvtf at 0x710083d0b8 and 0x710083d0e0) as the argument.
  int reducedWidth = static_cast<int>(width) * postParm->unknownfdc;
  int reducedHeight = static_cast<int>(height) * postParm->unknownfe0;
  res->unknown150->setTextureInfo(reducedWidth, reducedHeight, DrPixlFormat::s_SeparateCol, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0a8);
  res->unknown158->setTextureInfo(reducedWidth, reducedHeight, DrPixlFormat::s_MrtFormat[6], true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0ac);
  res->unknown160->setTextureInfo(reducedWidth, reducedHeight, DrPixlFormat::s_MrtFormat[3], true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0b0);
  res->unknown168->setTextureInfo(reducedWidth, reducedHeight, DrPixlFormat::s_ResponsiveAAMask, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0b4);
  res->unknown1b0->setTextureInfo(reducedWidth, reducedHeight, DrPixlFormat::s_ZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0c8);
  res->unknown1b8->setTextureInfo(width, height, DrPixlFormat::s_UnbranchZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0cc);
  res->unknown1c0->setTextureInfo(width * 0.25f, height * 0.25f, DrPixlFormat::s_UnbranchZBufferFormat, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0d0);
  f32 iblScale = unknown08->isIBLHalfRes() ? 0.5f : 1.0f;
  res->unknown1e0->setTextureInfo(iblScale * width, iblScale * height, DrPixlFormat::s_LgtLinkGIBFadeList, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0d4);
  res->unknown1e8->setTextureInfo(iblScale * width, iblScale * height, DrPixlFormat::s_LgtLinkGIBIndexMask, true, (memMan->unknown010 + DrMan::getIns()->unknown1c98)->unknown0d8);
  res->unknown1c8 = width;
  res->unknown1cc = height;
}

void DrPixlMan::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown08->unknown120[unknown08->unknown1c98];
  wkPixlManRes *res = unknown7f0;
  if (postParm->unknownfe4 == 3) {
    for (int i = 0; i < 19; i++) {
      if (res->unknown00[i][0] != nullptr) {
        res->unknown00[i][0]->releaseTexture();
      }
    }
    res->unknown1a0[0]->release();
    for (int i = 0; i < 19; i++) {
      if (res->unknown00[i][1] != nullptr) {
        res->unknown00[i][1]->releaseTexture();
      }
    }
    res->unknown1a0[1]->release();
  } else {
    u32 index = DrMan::s_nDblIdx;
    for (int i = 0; i < 19; i++) {
      if (res->unknown00[i][index] != nullptr && isDblPixlObj(i)) {
        res->unknown00[i][index]->releaseTexture();
      }
    }
    res->unknown1a0[index]->release();
    if (postParm->unknownfe4 != 2) {
      for (int i = 0; i < 19; i++) {
        if (res->unknown00[i][0] != nullptr && !isDblPixlObj(i)) {
          res->unknown00[i][0]->releaseTexture();
        }
      }
    }
  }
  res->unknown180->releaseColorBuff();
  res->unknown170->releaseColorBuff();
  if (postParm->unknownfe4 == 2) {
    return;
  }
  res->unknown148->releaseTexture();
  res->unknown150->releaseTexture();
  res->unknown158->releaseTexture();
  res->unknown160->releaseTexture();
  res->unknown168->releaseTexture();
  res->unknown1b0->release();
  res->unknown1b8->release();
  res->unknown1c0->release();
  res->unknown1e0->releaseTexture();
  res->unknown1e8->releaseTexture();
}

grlib::CGLibDepthTarget *DrPixlMan::getSeparateTransDepthObj() {
  if (unknown08->unknown120[unknown08->unknown1c98]->unknownfb4) {
    return unknown7f0->unknown1b0;
  }
  return getDepthObj();
}

void DrPixlMan::afterUpdate(int loop) {
  unknown7f0->unknown180->update();
  if (loop == 0) {
    unknown7f0->unknown180->setDownDepth();
  }
  if (unknown08->unknown88->unknown230->unknown04) {
    unknown7f0->unknown180->setRefRactionMap();
  }
  unknown7f0->unknown178->afterUpdate();
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
      grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(unknown003[i]), static_cast<grlib::GrlMrtType>(mrt));
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

bool DrPixlMan::renderRefractionBegin() {
  unknown08->unknown5c0->begin();
  unknown858 = 5;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  unknown08->unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_2);
  return unknown7f0->unknown180->renderRefractionBegin();
}

void DrPixlMan::renderRefractionEnd() {
  unknown08->unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_2);
  unknown7f0->unknown180->renderRefractionEnd();
}

void DrPixlMan::renderSkyLuminance() { unknown7f0->unknown180->renderSkyLuminance(); }

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
  unknown7f0->unknown138 = unknown7f0->unknown138 == unknown7f0->unknown130 ? unknown7f0->unknown140 : unknown7f0->unknown130;
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

// Ruling 8: the two shader blocks (stencil bit 0x40 and 0x80) are written out twice like the game (0x7100849174: the first block is
// 0x71008491a0-0x71008492fc, the second one starts at 0x7100849318 and repeats it with its own 8-float `col` array and its own uniform utility). A
// file-local helper taking the flag, the mask and the target row, called twice, is not inlined (72 instructions against 258), so no call form matches.
void DrPixlMan::clearAccumBuffer() {
  if (unknown08->unknown88->unknown230->unknown0a) {
    mm::Vec4 col[2];
    col[0] = col[1] = mm::Vec4::zero;
    unknown08->unknown78->selectGBuffRenderTarget(0x40);
    DrAPGxType::setupStencilTest(false, false, 7, true, 0x40, 0x40, 5, 1, 1, 1);
    DrAPGxType::setupBlend(0);
    DrAPGxType::setupCullingOff();
    DrShdDataList *shdList = unknown08->unknown80->unknown00;
    DrShdDataObj *shader = shdList->getSelectShdObj(1);
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 2);
    shader->setDeclarationIdx(shader->getDeclarationOfs("MRT_NUM"), 1);
    shdList->bindTriangle();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    uniform.setF32SetF32Array(uniform.unknown001("col[0]"), &col[0].x, 4);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  } else {
    unknown7f0->unknown00[5][0]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  }
  if (unknown08->unknown88->unknown230->unknown0b) {
    mm::Vec4 col[2];
    col[0] = col[1] = mm::Vec4::zero;
    unknown08->unknown78->selectGBuffRenderTarget(0x80);
    DrAPGxType::setupStencilTest(false, false, 7, true, 0x80, 0x80, 5, 1, 1, 1);
    DrAPGxType::setupBlend(0);
    DrAPGxType::setupCullingOff();
    DrShdDataList *shdList = unknown08->unknown80->unknown00;
    DrShdDataObj *shader = shdList->getSelectShdObj(1);
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 2);
    shader->setDeclarationIdx(shader->getDeclarationOfs("MRT_NUM"), 1);
    shdList->bindTriangle();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    uniform.setF32SetF32Array(uniform.unknown001("col[0]"), &col[0].x, 4);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  } else {
    unknown7f0->unknown00[6][0]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  }
  DrAPGxType::setupStencilTest(false, false, 7, false, 0, 0, 2, 1, 1, 1);
  // The game loads the render target table of the resource (`ldr x8, [x20]`, 0x71008494e0 and 0x7100849508) before the double buffer index
  // (0x71008494e8 and 0x710084950c); the natural `unknown00[9][DrMan::s_nDblIdx]` loads the index first (first difference at 0x71008494dc, and
  // at 0x7100849508 when only the second clear is written that way), so each row stays in a local.
  DrPixlRenderTarget **accum = unknown7f0->unknown00[9];
  accum[DrMan::s_nDblIdx]->clearTexture(mm::Col4::zero, static_cast<GrlClaerMask>(0xf));
  DrPixlRenderTarget **accumBlur = unknown7f0->unknown00[14];
  accumBlur[DrMan::s_nDblIdx]->clearTexture(mm::Col4::zero, static_cast<GrlClaerMask>(0xf));
  unknown7f0->unknown00[10][0]->clearTexture(mm::Col4::black, static_cast<GrlClaerMask>(0xf));
  unknown7f0->unknown00[11][0]->clearTexture(mm::Col4::black, static_cast<GrlClaerMask>(0xf));
  unknown7f0->unknown00[15][0]->clearTexture(mm::Col4::black, static_cast<GrlClaerMask>(0xf));
}

void DrPixlMan::debugGBuffRender() {
  DrMan *man = unknown08;
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  DrShdMan *shdMan = man->unknown80;
  DrAPGxType::setupScreenQuads(false);
  DrShdDataList *shdList = shdMan->unknown00;
  shdList->bindShdVertex();
  DrShdDataObj *shader = shdList->getDebugShdObj(4);
  shader->setupShader(0u);
  {
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 parm = uniform.unknown001("parm");
    // The four passes of each iteration (render target 0, 1, 2 and 4, each with its own vector) are written out one after the other, as the game inlines them: the
    // asm repeats the register target, vector and renderQuads sequence with no call to a shared function (0x71008436cc onwards).
    for (int i = 0; i < 2; i++) {
      if (i == 0) {
        DrAPGxType::setupBlend(7);
      } else {
        DrAPGxType::setupBlend(5);
        // The game tests the second pass again (cmp x25, #4 on the induction variable scaled by 4, 0x71008436a0); without the test clang folds it and gives 294
        // instructions against the game's 296.
        if (i == 1) {
          uniform.unknown20.Rebuilding();
          static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
        }
      }
      grlib::CGLibState::beginRegisterRenderTarget();
      grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[0][0], grlib::GRL_MRT_TYPE_0);
      grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
      grlib::CGLibState::endRegisterRenderTarget();
      f32 vec[4];
      vec[0] = vec[1] = vec[2] = postParm->unknown320[0].unknown00[i];
      vec[3] = postParm->unknown320[3].unknown00[i];
      uniform.setF32SetVec4(parm, vec);
      uniform.updateData();
      uniform.setUniformBlock();
      shdList->renderQuads();
      uniform.unknown20.Rebuilding();
      static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
      grlib::CGLibState::beginRegisterRenderTarget();
      grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[1][0], grlib::GRL_MRT_TYPE_0);
      grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
      grlib::CGLibState::endRegisterRenderTarget();
      vec[0] = postParm->unknown320[1].unknown00[i];
      vec[1] = postParm->unknown320[2].unknown00[i];
      vec[2] = postParm->unknown320[7].unknown00[i];
      f32 isMax = i == 0 ? 0.0f : 1.0f;
      vec[3] = isMax;
      uniform.setF32SetVec4(parm, vec);
      uniform.updateData();
      uniform.setUniformBlock();
      shdList->renderQuads();
      uniform.unknown20.Rebuilding();
      static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
      grlib::CGLibState::beginRegisterRenderTarget();
      grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[2][0], grlib::GRL_MRT_TYPE_0);
      grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
      grlib::CGLibState::endRegisterRenderTarget();
      vec[0] = isMax;
      vec[1] = isMax;
      vec[2] = postParm->unknown320[5].unknown00[i];
      vec[3] = isMax;
      uniform.setF32SetVec4(parm, vec);
      uniform.updateData();
      uniform.setUniformBlock();
      shdList->renderQuads();
      uniform.unknown20.Rebuilding();
      static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
      grlib::CGLibState::beginRegisterRenderTarget();
      grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown00[4][0], grlib::GRL_MRT_TYPE_0);
      grlib::CGLibState::setRegisterDepthTarget(*unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
      grlib::CGLibState::endRegisterRenderTarget();
      vec[0] = isMax;
      vec[1] = isMax;
      vec[2] = isMax;
      vec[3] = postParm->unknown320[6].unknown00[i];
      uniform.setF32SetVec4(parm, vec);
      uniform.updateData();
      uniform.setUniformBlock();
      shdList->renderQuads();
    }
  }
  shader = shdList->getDebugShdObj(0x18);
  shader->setupShader(0u);
  DrPixlRenderTarget *target = unknown7f0->unknown00[1][0];
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*target, grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::endRegisterRenderTarget();
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 parm = uniform.unknown001("parm");
  u32 value = 0;
  u32 mask = 0;
  if (postParm->unknown10e0[0] > 0) {
    value = postParm->unknown10e0[0] - 1;
    mask = 7;
  }
  if (postParm->unknown10e0[1] > 0) {
    mask |= 0x10;
    value |= postParm->unknown10e0[1] * 0x10 - 0x10;
  }
  if (postParm->unknown10e0[2] > 0) {
    mask |= 0x20;
    value |= postParm->unknown10e0[2] * 0x20 - 0x20;
  }
  if (postParm->unknown10e0[3] > 0) {
    mask |= 0x40;
    value |= postParm->unknown10e0[3] * 0x40 - 0x40;
  }
  u32 vec[4];
  vec[0] = ~mask;
  vec[1] = value;
  vec[2] = 0;
  vec[3] = 0;
  uniform.setU32SetUVec4(parm, vec);
  uniform.updateData();
  uniform.setUniformBlock();
  grlib::CGLibCtlTexture::setUAVTexture(*target->unknown70, 0, 0, 0);
  grlib::CGLibColorCtl::setColorBufferOff();
  shdList->renderQuads();
  grlib::CGLibColorCtl::setColorBufferOn();
}

} // namespace ml

// The game builds these files in one unit with this one.
#include "dr_pixl_occ_query.cpp"
