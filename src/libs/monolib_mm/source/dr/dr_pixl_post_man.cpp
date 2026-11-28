#include "dr/dr_pixl_post_man.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_obj_3d_lut.h"
#include "dr/dr_pixl_post_obj_bloom.h"
#include "dr/dr_pixl_post_obj_capture.h"
#include "dr/dr_pixl_post_obj_cube_map_ibl.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_obj_depthof_field.h"
#include "dr/dr_pixl_post_obj_exp_stencil.h"
#include "dr/dr_pixl_post_obj_fx_aa.h"
#include "dr/dr_pixl_post_obj_glass_br.h"
#include "dr/dr_pixl_post_obj_histgram.h"
#include "dr/dr_pixl_post_obj_motion_blur.h"
#include "dr/dr_pixl_post_obj_motion_blur2.h"
#include "dr/dr_pixl_post_obj_rain_drop.h"
#include "dr/dr_pixl_post_obj_ssr.h"
#include "dr/dr_pixl_post_obj_tmaa.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_obj_tssao.h"
#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"
#include "dr/dr_pixl_post_obj_volume.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_raytrace.h"
#include "dr/dr_pixl_sky_dome.h"
#include "dr/dr_pixl_toon_grad.h"
#include "dr/dr_res_use_query_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mtl/alloc_handle.h"

namespace grlib {
class CGLibDepthBuffer;
} // namespace grlib

namespace ml {

DrPixlPostMan::~DrPixlPostMan() {
  if (m_drResUseQueryObj != nullptr) {
    delete m_drResUseQueryObj;
    m_drResUseQueryObj = nullptr;
  }
  if (m_drPixlShadowRaytrace != nullptr) {
    delete m_drPixlShadowRaytrace;
    m_drPixlShadowRaytrace = nullptr;
  }
  if (m_drPixlPostObjExpStencil != nullptr) {
    delete m_drPixlPostObjExpStencil;
    m_drPixlPostObjExpStencil = nullptr;
  }
  unknown120(unknownc0[0]);
  unknown120(unknownc0[1]);
  unknown120(unknowne0);
  unknown120(unknownd0);
  unknown120(unknownd8);
  unknown120(unknowne8);
  if (m_drPixlToonGrad != nullptr) {
    delete m_drPixlToonGrad;
    m_drPixlToonGrad = nullptr;
  }
  if (m_drPixlSkyDome != nullptr) {
    delete m_drPixlSkyDome;
    m_drPixlSkyDome = nullptr;
  }
  if (m_drPixlPostObjRainDrop != nullptr) {
    delete m_drPixlPostObjRainDrop;
    m_drPixlPostObjRainDrop = nullptr;
  }
  if (m_drPixlPostObjFxAA != nullptr) {
    delete m_drPixlPostObjFxAA;
    m_drPixlPostObjFxAA = nullptr;
  }
  if (m_drPixlPostObj3dLut != nullptr) {
    delete m_drPixlPostObj3dLut;
    m_drPixlPostObj3dLut = nullptr;
  }
  if (m_drPixlPostObjToneMap != nullptr) {
    delete m_drPixlPostObjToneMap;
    m_drPixlPostObjToneMap = nullptr;
  }
  if (m_drPixlPostObjBloom != nullptr) {
    delete m_drPixlPostObjBloom;
    m_drPixlPostObjBloom = nullptr;
  }
  if (m_drPixlPostObjVolume != nullptr) {
    delete m_drPixlPostObjVolume;
    m_drPixlPostObjVolume = nullptr;
  }
  if (m_drPixlPostObjDepthofField != nullptr) {
    delete m_drPixlPostObjDepthofField;
    m_drPixlPostObjDepthofField = nullptr;
  }
  if (m_drPixlPostObjMotionBlur != nullptr) {
    delete m_drPixlPostObjMotionBlur;
    m_drPixlPostObjMotionBlur = nullptr;
  }
  if (m_drPixlPostObjMotionBlur2 != nullptr) {
    delete m_drPixlPostObjMotionBlur2;
    m_drPixlPostObjMotionBlur2 = nullptr;
  }
  if (m_drPixlPostObjCubeMapMultiIBL != nullptr) {
    delete m_drPixlPostObjCubeMapMultiIBL;
    m_drPixlPostObjCubeMapMultiIBL = nullptr;
  }
  if (m_drPixlPostObjCubeMapIBL != nullptr) {
    delete m_drPixlPostObjCubeMapIBL;
    m_drPixlPostObjCubeMapIBL = nullptr;
  }
  if (m_drPixlPostObjHistgram != nullptr) {
    delete m_drPixlPostObjHistgram;
    m_drPixlPostObjHistgram = nullptr;
  }
  if (m_drPixlPostObjTMAA != nullptr) {
    delete m_drPixlPostObjTMAA;
    m_drPixlPostObjTMAA = nullptr;
  }
  if (m_drPixlPostObjSSR != nullptr) {
    delete m_drPixlPostObjSSR;
    m_drPixlPostObjSSR = nullptr;
  }
  if (m_drPixlPostObjTSSAO != nullptr) {
    delete m_drPixlPostObjTSSAO;
    m_drPixlPostObjTSSAO = nullptr;
  }
  if (m_drPixlPostObjGlassBr != nullptr) {
    delete m_drPixlPostObjGlassBr;
    m_drPixlPostObjGlassBr = nullptr;
  }
  if (m_drPixlPostObjCapture != nullptr) {
    delete m_drPixlPostObjCapture;
    m_drPixlPostObjCapture = nullptr;
  }
  if (m_drPixlPostObjUnbranchToDepth != nullptr) {
    delete m_drPixlPostObjUnbranchToDepth;
    m_drPixlPostObjUnbranchToDepth = nullptr;
  }
}
void DrPixlPostMan::setupDepthBuff() {
  f32 width = static_cast<f32>(m_drMan->unknown5b8->unknown18);
  f32 height = static_cast<f32>(m_drMan->unknown5b8->unknown1c);
  f32 halfWidth = width * 0.5f;
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  f32 halfHeight = height * 0.5f;
  if (postParm->unknownfe4 == 3) {
    if (unknownc0[0] != nullptr) {
      unknownc0[0]->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[0]);
    }
    if (unknownc0[1] != nullptr) {
      unknownc0[1]->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[1]);
    }
  } else {
    // The game indexes the target array with the signed index (ldrsw at 0x710084db70) and the memory area table with its zero extension
    // (and x23, x9, #0xffffffff at 0x710084db98); a signed index on both gives a different code.
    s32 index = DrMan::s_nDblIdx;
    if (unknownc0[index] != nullptr) {
      unknownc0[index]->setTextureInfo(
          halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[static_cast<u32>(index)]);
    }
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  if (unknowne0 != nullptr) {
    unknowne0->setTextureInfo(width * 0.25f, height * 0.25f, DrPixlFormat::s_QuaterNormalFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown108);
  }
  if (unknownd0 != nullptr) {
    unknownd0->setTextureInfo(static_cast<f32>(m_drMan->unknown5b8->unknown18) * 0.5f,
                              static_cast<f32>(m_drMan->unknown5b8->unknown1c) * 0.5f,
                              DrPixlFormat::s_MrtFormat[5],
                              true,
                              (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown100);
  }
  if (unknowne8 != nullptr) {
    unknowne8->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown10c);
  }
}

void DrPixlPostMan::setReflection(f32 x, f32 y, f32 z, bool isHigh) {
  u32 flags = unknownf8;
  u32 mask = isHigh ? 0x60000 : 0x20000;
  unknownfc = x;
  unknown100 = y;
  unknown104 = z;
  unknownf8 = flags | mask;
}

void DrPixlPostMan::setDownDepth() { unknownf8 |= FLAG_UNKNOWN_19; }

void DrPixlPostMan::renderDeferred() {}

void DrPixlPostMan::renderDeferredLast() {
  if (m_drPixlPostObjToneMap != nullptr) {
    m_drPixlPostObjToneMap->fastRender();
  }
  if (m_drPixlPostObjHistgram != nullptr) {
    m_drPixlPostObjHistgram->render();
  }
}

DrPixlRenderTarget *DrPixlPostMan::getDownDepth() { return unknownc0[DrMan::s_nDblIdx]; }

void DrPixlPostMan::resetColorBuff() {
  if (m_drPixlPostObjTSSAO != nullptr) {
    m_drPixlPostObjTSSAO->resetColorBuff(false);
  }
  setupDepthBuff();
  if (m_drPixlPostObjBloom != nullptr) {
    m_drPixlPostObjBloom->resetColorBuff(false);
  }
  if (m_drPixlPostObjSSR != nullptr) {
    m_drPixlPostObjSSR->resetColorBuff();
  }
  if (m_drPixlPostObjTMAA != nullptr) {
    m_drPixlPostObjTMAA->resetColorBuff();
  }
  if (m_drPixlShadowRaytrace != nullptr) {
    m_drPixlShadowRaytrace->resetColorBuff();
  }
  if (m_drMan->unknown120[m_drMan->unknown1c98]->unknownfe4 != 2) {
    if (m_drPixlPostObjDepthofField != nullptr) {
      m_drPixlPostObjDepthofField->resetColorBuff();
    }
    if (m_drPixlPostObjMotionBlur != nullptr) {
      m_drPixlPostObjMotionBlur->resetColorBuff();
    }
    if (m_drPixlPostObjMotionBlur2 != nullptr) {
      m_drPixlPostObjMotionBlur2->resetColorBuff();
    }
    if (m_drPixlPostObjFxAA != nullptr) {
      m_drPixlPostObjFxAA->resetColorBuff();
    }
    if (m_drPixlPostObjVolume != nullptr) {
      m_drPixlPostObjVolume->calcColorBuff();
    }
    if (m_drPixlPostObjRainDrop != nullptr) {
      m_drPixlPostObjRainDrop->resetColorBuff();
    }
  }
}

void DrPixlPostMan::releaseColorBuff() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (m_drPixlPostObjBloom != nullptr) {
    m_drPixlPostObjBloom->releaseColorBuff(false);
  }
  if (m_drPixlPostObjSSR != nullptr) {
    m_drPixlPostObjSSR->releaseColorBuff();
  }
  if (m_drPixlPostObjTSSAO != nullptr) {
    m_drPixlPostObjTSSAO->releaseColorBuff();
  }
  if (m_drPixlPostObjTMAA != nullptr) {
    m_drPixlPostObjTMAA->releaseColorBuff();
  }
  if (m_drPixlShadowRaytrace != nullptr) {
    m_drPixlShadowRaytrace->releaseColorBuff();
  }
  if (postParm->unknownfe4 == 3) {
    unknownf8 |= FLAG_UNKNOWN_22;
    if (unknownc0[0] != nullptr) {
      unknownc0[0]->releaseTexture();
    }
    if (unknownc0[1] != nullptr) {
      unknownc0[1]->releaseTexture();
    }
  } else {
    if (unknownc0[DrMan::s_nDblIdx] != nullptr) {
      unknownc0[DrMan::s_nDblIdx]->releaseTexture();
    }
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  if (unknowne0 != nullptr) {
    unknowne0->releaseTexture();
  }
  if (unknowne8 != nullptr) {
    unknowne8->releaseTexture();
  }
  if (m_drPixlPostObjDepthofField != nullptr) {
    m_drPixlPostObjDepthofField->releaseColorBuff();
  }
  if (m_drPixlPostObjMotionBlur != nullptr) {
    m_drPixlPostObjMotionBlur->releaseColorBuff();
  }
  if (m_drPixlPostObjMotionBlur2 != nullptr) {
    m_drPixlPostObjMotionBlur2->releaseColorBuff();
  }
  if (m_drPixlPostObjFxAA != nullptr) {
    m_drPixlPostObjFxAA->releaseColorBuff();
  }
  if (m_drPixlPostObjVolume != nullptr) {
    m_drPixlPostObjVolume->releaseColorBuff();
  }
  if (m_drPixlPostObjRainDrop != nullptr) {
    m_drPixlPostObjRainDrop->releaseColorBuff();
  }
  if (unknownd0 != nullptr) {
    unknownd0->releaseTexture();
  }
}

void DrPixlPostMan::beginUpdate() {
  // The screen size is read into a local (ruling 2): the game loads the screen pointer (0x710084179c) before the query pointer, and
  // without the local the loads come out in the other order (the conversion of the query's pixel count first, then the screen).
  s32 area = m_drMan->unknown5b8->unknown1c * m_drMan->unknown5b8->unknown18;
  if ((unknownf8 & FLAG_UNKNOWN_21) && static_cast<f32>(m_drResUseQueryObj->m_pixel) / static_cast<f32>(area) > 0.001) {
    unknown108 = unknown108 + (1.0f - unknown108) * 0.5f;
  } else {
    unknown108 = unknown108 + (0.0f - unknown108) * 0.2f;
  }
  if (unknownd0 == nullptr) {
    unknownd0 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
    unknownd0->setTextureInfo(static_cast<f32>(m_drMan->unknown5b8->unknown18) * 0.5f,
                              static_cast<f32>(m_drMan->unknown5b8->unknown1c) * 0.5f,
                              DrPixlFormat::s_MrtFormat[5],
                              true,
                              (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown100);
  }
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  setBloom(postParm->m_bloomOn);
  setSSAO(postParm->m_sSAO);
  setBlur(postParm->isMotBlur() || postParm->m_motBlur2);
  setDepthField(postParm->unknown218 || postParm->unknown219);
  setGlassBreak(postParm->m_glassBr);
  setCaputureMode(m_drMan->unknown1c83 && m_drMan->unknown1c98 == 0);
}

bool DrPixlPostMan::isCalcVolume() { return unknownf8 & FLAG_UNKNOWN_16; }

void DrPixlPostMan::update() {
  unknownf8 &= ~(FLAG_UNKNOWN_8 | FLAG_UNKNOWN_15 | FLAG_UNKNOWN_16 | FLAG_UNKNOWN_17 | FLAG_UNKNOWN_18 | FLAG_UNKNOWN_21);
  if (m_drResUseQueryObj != nullptr) {
    m_drResUseQueryObj->update();
  }
  if (m_drPixlSkyDome != nullptr) {
    m_drPixlSkyDome->update();
  }
  if (m_drPixlPostObjBloom != nullptr) {
    m_drPixlPostObjBloom->update();
  }
  if (m_drPixlPostObjToneMap != nullptr) {
    m_drPixlPostObjToneMap->update();
  }
  if (m_drPixlPostObjDepthofField != nullptr) {
    m_drPixlPostObjDepthofField->update();
  }
  if (m_drPixlPostObjMotionBlur != nullptr) {
    m_drPixlPostObjMotionBlur->update();
  }
  if (m_drPixlPostObjMotionBlur2 != nullptr) {
    m_drPixlPostObjMotionBlur2->update();
  }
  if (m_drPixlPostObjHistgram != nullptr) {
    m_drPixlPostObjHistgram->update();
  }
  if (m_drPixlPostObjTSSAO != nullptr) {
    m_drPixlPostObjTSSAO->update();
  }
  m_drMan->unknown120[m_drMan->unknown1c98]->update();
  if (m_drPixlPostObjRainDrop != nullptr) {
    m_drPixlPostObjRainDrop->update();
  }
  if (m_drPixlPostObjGlassBr != nullptr) {
    m_drPixlPostObjGlassBr->update();
  }
  if (m_drPixlPostObjCapture != nullptr) {
    m_drPixlPostObjCapture->update();
  }
  if (m_drPixlPostObjSSR != nullptr) {
    m_drPixlPostObjSSR->update();
  }
}

void DrPixlPostMan::setRefRactionMap() { unknownf8 |= FLAG_UNKNOWN_21; }

void DrPixlPostMan::renderRefractionMap(bool isRefractionMap, bool isHalfMap) {
  DrPixlRenderTarget *target = isRefractionMap ? unknownd0 : nullptr;
  DrPixlRenderTarget *second = nullptr;
  if (isHalfMap) {
    f32 width = static_cast<f32>(m_drMan->unknown5b8->unknown18) * 0.5f;
    f32 height = static_cast<f32>(m_drMan->unknown5b8->unknown1c) * 0.5f;
    DrPixlRenderTarget *half = unknownd8;
    if (static_cast<f32>(half->unknownbc) != width || static_cast<f32>(half->unknownc0) != height) {
      half->setTextureInfo(width, height, DrPixlFormat::s_MrtFormat[5], true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown104);
      half = unknownd8;
    }
    if (target == nullptr) {
      target = half;
    } else {
      second = half;
    }
  }
  if (target == nullptr) {
    return;
  }
  m_drPixlMan->unknown7f0->unknown138->setColorInvalidate();
  DrAPGxType::setupScreenQuads(false);
  if (second != nullptr) {
    target->setRenderTarget(*second);
  } else {
    target->setRenderTarget();
  }
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(5);
  // The output count is a local (ruling 1/P2): the game computes it (cmp, cinc into w25, 0x7100842e48-0x7100842e58) before the
  // getDeclarationOfs call and keeps it across the call; written as an argument it is computed after the call.
  u32 outputNum = second != nullptr ? 2 : 1;
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_NUM"), outputNum);
  // Written out like the other post process functions (ruling 8, measured): a file-local helper holding updateData, setUniformBlock and renderQuads gives 190
  // instructions against 186 here and 886 against 882 in renderDownDepth.
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 offset = uniform.unknown001("gScal");
  f32 width = static_cast<f32>(m_drMan->unknown5b8->unknown18);
  f32 height = static_cast<f32>(m_drMan->unknown5b8->unknown1c);
  // An eight float work buffer of which setF32SetVec4 reads the first four, like DrPixlPostObjDepthofField (work[8]) and
  // DrPixlPostObjMotionBlur (ofs[8]) of this unit: the game's frame holds 32 bytes for it (the uniform utility sits at sp+0x20,
  // 0x7100842e84, and the four values at sp+0), with `f32 work[4]` the frame is 16 bytes smaller.
  f32 work[8];
  work[0] = (width - 1.0f) / width;
  work[1] = (height - 1.0f) / height;
  work[2] = 1.0f / (width + width);
  work[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(offset, work);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*m_drPixlMan->unknown7f0->unknown138->unknown70, location);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
  second->setColorInvalidate();
  m_drPixlMan->setMainViewPort();
  m_drPixlMan->resetRenderTarget();
}

bool DrPixlPostMan::renderRefractionBegin() {
  if (!(unknownf8 & FLAG_UNKNOWN_21)) {
    return false;
  }
  if (m_drResUseQueryObj != nullptr) {
    m_drResUseQueryObj->begin(m_drPixlMan->m_drPixlOccQuery);
  }
  return true;
}

void DrPixlPostMan::renderRefractionEnd() {
  if (m_drResUseQueryObj != nullptr) {
    m_drResUseQueryObj->end();
  }
}

void DrPixlPostMan::renderSkyLuminance() {
  if (m_drPixlSkyDome != nullptr) {
    m_drPixlSkyDome->luminanceRender();
  }
}

void DrPixlPostMan::renderSkyDome() {
  if (m_drPixlSkyDome != nullptr) {
    m_drPixlSkyDome->baseRender();
  }
}

void DrPixlPostMan::renderSkyGodRay() {
  if (m_drPixlSkyDome != nullptr) {
    m_drPixlSkyDome->godRayRender();
  }
}

void DrPixlPostMan::renderRainDrop() {
  if (m_drPixlPostObjRainDrop != nullptr) {
    m_drPixlPostObjRainDrop->render();
  }
}

void DrPixlPostMan::renderTMAA() {
  if (m_drMan->unknown120[m_drMan->unknown1c98]->m_TMAAOn) {
    m_drPixlPostObjTMAA->render();
  }
}

void DrPixlPostMan::renderDeferredTemporal() {
  if (!m_drMan->isIBLHalfRes()) {
    return;
  }
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  DrPixlMan *pixlMan = m_drMan->m_drPixlMan;
  DrAPCache *apCache = m_drMan->m_drAPCache;
  bool isRaytrace = DrMan::getIns()->isIBLHalfRes() && postParm->unknown1024;
  bool isShadow = postParm->unknown103c && postParm->unknown103d;
  DrAPGxType::setupBlend(0);
  // The game loads the resource pointer before the double buffer index (0x7100843bc4, 0x7100843bc8) and the deferred pointer chain before the index
  // of the shadow output (0x7100843be0-0x7100843bf4); `pixlMan->unknown7f0->unknown00[9][DrMan::s_nDblIdx]` loads the index first, so both stay in
  // locals. The previous targets are the natural expression: the game reuses the index of the shadow output (0x7100843bf0) and loads the resource after it (0x7100843c00).
  wkPixlManRes *res = pixlMan->unknown7f0;
  DrPixlRenderTarget *target = res->unknown00[9][DrMan::s_nDblIdx];
  DrPixlRenderTarget *current = res->unknown00[14][DrMan::s_nDblIdx];
  grlib::CGLibRenderTarget *raytraceOutput = m_drPixlShadowRaytrace->getTemporalOutputTexture();
  DrPixlDeferred *outputDeferred = m_drMan->m_drPixlMan->unknown7f0->m_drPixlDeferred;
  DrPixlRenderTarget *shadowOutput = outputDeferred->unknown28[DrMan::s_nDblIdx];
  DrPixlRenderTarget *prevTarget = pixlMan->unknown7f0->unknown00[9][DrMan::s_nDblIdx ^ 1];
  DrPixlRenderTarget *prevCurrent = pixlMan->unknown7f0->unknown00[14][DrMan::s_nDblIdx ^ 1];
  grlib::CGLibRenderTarget *raytraceHistory = m_drPixlShadowRaytrace->getTemporalHistoryTexture();
  DrPixlRenderTarget *prevShadowOutput = m_drMan->m_drPixlMan->unknown7f0->m_drPixlDeferred->unknown28[DrMan::s_nDblStockIdx];
  DrPixlRenderTarget *hdr = pixlMan->unknown7f0->unknown00[11][0];
  DrPixlRenderTarget *hdr2 = pixlMan->unknown7f0->unknown00[10][0];
  DrPixlRenderTarget *raytraceCurrent = m_drPixlShadowRaytrace->unknown10 ? m_drPixlShadowRaytrace->unknown38 : m_drPixlShadowRaytrace->unknown18;
  DrPixlRenderTarget *shadowInput = m_drMan->m_drPixlMan->unknown7f0->m_drPixlDeferred->m_temporalInputShadowMap;
  mm::mtl::FixedVector<grlib::CGLibRenderTarget *, 5> targets;
  targets.push_back(current);
  if (isRaytrace) {
    targets.push_back(raytraceOutput);
  }
  // The game branches on the shadow flag with `tbz w28, #0` (0x7100843ca8). That needs the arm with the shadow target not to follow the test in the
  // IR: `if (isShadow) { targets.push_back(shadowOutput); }` gives `cbz w28`. The other arm holds one or two targets, so the game has no null test there.
  if (!isShadow) {
    target->setRenderTargetImpl(targets.begin(), targets.size(), nullptr);
  } else {
    targets.push_back(shadowOutput);
    if (targets.size() != 0) {
      target->setRenderTargetImpl(targets.begin(), targets.size(), nullptr);
    } else {
      target->setRenderTargetImpl(nullptr, 0, nullptr);
    }
  }
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x33);
  DrCalcViewWork *viewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  DrPixlMan *viewPixlMan = m_drMan->m_drPixlMan;
  // The game loads the target size (0x7100843d04) before the isTemporalUPSToGlobalIBL call (0x7100843d10).
  f32 width = static_cast<f32>(target->unknownbc);
  f32 height = static_cast<f32>(target->unknownc0);
  bool isUpsGlobalIbl = m_drMan->isTemporalUPSToGlobalIBL();
  bool isReset = false;
  if (unknownf8 & FLAG_UNKNOWN_22) {
    unknownf8 &= ~FLAG_UNKNOWN_22;
    isReset = true;
  }
  if (m_drMan->m_autoResetScene) {
    isReset |= viewWork->unknown9aa != 0;
  }
  // Both indices are locals: written inside the arguments of their calls the function has 1122 instructions against the game's 1123 (measured).
  u32 execClear = isReset ? 1 : (isUpsGlobalIbl ? 2 : 1);
  shader->setDeclarationIdx(shader->getDeclarationOfs("EXEC_CLEAR"), execClear);
  u32 raytraceIndex = isRaytrace ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUT_SHW_RAYTRACE"), raytraceIndex);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEBUG_DISP"), 2);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility vsUniform(shader);
  vsUniform.setUseUniformBlock("U_VS");
  u32 val = vsUniform.unknown001("val");
  u32 projInv = vsUniform.unknown001("gProjInv");
  // The uniform values are `mm::Vec4`: the game's frame keeps them 16-byte aligned (the `val` values at sp+0x180, the `gParam` values at sp+0x120, with 8-byte gaps
  // after them); `f32` arrays are 4-aligned and make the frame 16 bytes smaller.
  mm::Vec4 valValue;
  valValue.x = (width - 1.0f) / width;
  valValue.y = (height - 1.0f) / height;
  valValue.z = 1.0f / (width + width);
  valValue.w = 1.0f / (height + height);
  vsUniform.setF32SetVec4(val, &valValue.x);
  vsUniform.setF32SetMat44(projInv, viewWork->unknown3c0.rows[0]);
  grlib::CGLibUniformEtcUtility psUniform(shader);
  psUniform.setUseUniformBlock("U_PS");
  u32 param = psUniform.unknown001("gParam[0]");
  u32 screenInfo = psUniform.unknown001("gScreenInfo");
  u32 toPrevScreen = psUniform.unknown001("gToPrevScreen");
  u32 jitter = psUniform.unknown001("gJitter");
  // Written out like the lookups of the other post objects (DrPixlPostObjTSSAO, MotionBlur2). A static helper for the lookup matches too (1123 instructions) but the quality gate still reports
  // 3 findings with it (the two uniform families and the 9 repeats of the helper call) against 4 written out, so the helper only adds a second convention.
  int curHdrLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurHDRCalc");
  int prevHdrLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevHDRCalc");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocity");
  int velocityLenLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocityLen");
  int curStencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurStencil");
  int prevStencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevStencil");
  int curHdr2Location = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurHDRCalc2");
  int prevHdr2Location = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevHDRCalc2");
  // The game queries three more locations (0x7100844050, 0x7100844068, 0x7100844080) and keeps none of them.
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurSSAO");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevSSAO");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSSAOContinuityMask");
  int curRaytraceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurShwRaytrace");
  int prevRaytraceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevShwRaytrace");
  int curShadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurShwHalf");
  int prevShadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevShwHalf");
  int downDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDownDepth");
  int prevDownDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevDownDepth");
  int similarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepthWithSimilarity");
  mm::Vec4 paramValue[2];
  paramValue[0].x = 0.0f;
  paramValue[0].y = postParm->unknown148 * postParm->unknown148;
  paramValue[0].z = postParm->m_toneMapOn ? viewPixlMan->unknown7f0->unknown188 : 1.0f;
  paramValue[0].w = 0.0f;
  f32 strength = postParm->unknown150;
  f32 blend = strength < 0.2f ? 0.2f : (strength > 1.0f ? 1.0f : strength);
  paramValue[1].x = (1.0f - blend) * 0.25f;
  paramValue[1].y = blend;
  paramValue[1].z = 0.0f;
  paramValue[1].w = 0.0f;
  psUniform.setF32SetVec4Array(param, &paramValue[0].x, 2);
  mm::Vec4 screenInfoValue;
  screenInfoValue.x = width;
  screenInfoValue.y = height;
  screenInfoValue.z = 1.0f / width;
  screenInfoValue.w = 1.0f / height;
  psUniform.setF32SetVec4(screenInfo, &screenInfoValue.x);
  mm::Mat44 matrix = viewWork->unknown00;
  matrix.unknown009(matrix, viewWork->unknown280 * viewWork->unknown380);
  psUniform.setMat44SetMat44(toPrevScreen, matrix);
  mm::Vec4 jitterValue;
  jitterValue.x = viewWork->unknownac0.x - viewWork->unknownad0.x;
  jitterValue.y = -(viewWork->unknownac0.y - viewWork->unknownad0.y);
  jitterValue.z = 0.0f;
  jitterValue.w = 0.0f;
  psUniform.setVec4SetVec4(jitter, jitterValue);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*hdr->unknown70, curHdrLocation);
  apCache->setTexture(*prevTarget->unknown70, prevHdrLocation);
  apCache->setTexture(*hdr2->unknown70, curHdr2Location);
  apCache->setTexture(*prevCurrent->unknown70, prevHdr2Location);
  apCache->setTexture(*raytraceCurrent->unknown70, curRaytraceLocation);
  apCache->setTexture(*raytraceHistory->unknown70, prevRaytraceLocation);
  if (isShadow) {
    apCache->setTexture(*shadowInput->unknown70, curShadowLocation);
    apCache->setTexture(*prevShadowOutput->unknown70, prevShadowLocation);
  }
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*viewPixlMan->unknown7f0->unknown00[3][0]->unknown70, velocityLocation);
  apCache->setTexture(*viewPixlMan->unknown7f0->unknown00[17][DrMan::s_nDblIdx ^ 1]->unknown70, velocityLenLocation);
  apCache->beginTexSampling(2, 0);
  // The game reads the depth target of the double buffer inline (0x7100844b7c-0x7100844b8c), not through DrPixlMan::getDepthObj.
  apCache->setTexture(*viewPixlMan->unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown130, curStencilLocation);
  apCache->setTexture(*viewPixlMan->unknown7f0->unknown00[12][DrMan::s_nDblIdx ^ 1]->unknown70, prevStencilLocation);
  apCache->setTexture(*unknownc0[DrMan::s_nDblIdx]->unknown70, downDepthLocation);
  apCache->setTexture(*unknownc0[DrMan::s_nDblStockIdx]->unknown70, prevDownDepthLocation);
  apCache->setTexture(*unknowne8->unknown70, similarityLocation);
  vsUniform.updateData();
  vsUniform.setUniformBlock();
  psUniform.updateData();
  psUniform.setUniformBlock();
  shdList->renderTriangle();
  target->setColorInvalidate();
}

void DrPixlPostMan::renderDeferredFast_AfterTemporal() {
  if (m_drPixlPostObjTSSAO != nullptr) {
    m_drPixlPostObjTSSAO->render_afterTemporal();
  }
}

void DrPixlPostMan::renderDeferredFast() {
  bool isTemporal = m_drMan->isTemporalUPSToGlobalIBL() || m_drMan->unknown120[m_drMan->unknown1c98]->m_TMAAOn;
  if (getDownDepth() != nullptr) {
    renderDownDepth(true, isTemporal, true);
  }
  if (m_drPixlPostObjUnbranchToDepth != nullptr) {
    m_drPixlPostObjUnbranchToDepth->render();
  }
  if (m_drPixlPostObjExpStencil != nullptr) {
    m_drPixlPostObjExpStencil->render();
  }
  if (m_drPixlPostObjTSSAO != nullptr) {
    m_drPixlPostObjTSSAO->render_beforeTemporal();
  }
  if (m_drPixlShadowRaytrace != nullptr) {
    m_drPixlShadowRaytrace->render_beforeTemporal();
  }
  if (m_drPixlPostObjSSR != nullptr) {
    m_drPixlPostObjSSR->render();
  }
}

void DrPixlPostMan::fastRender() {
  if (m_drPixlPostObjCubeMapMultiIBL != nullptr) {
    m_drPixlPostObjCubeMapMultiIBL->render();
  }
  if (m_drPixlPostObjCubeMapIBL != nullptr) {
    m_drPixlPostObjCubeMapIBL->render();
  }
  if (m_drPixlToonGrad != nullptr) {
    m_drPixlToonGrad->render();
  }
}

void DrPixlPostMan::render() {
  if (m_drMan->unknown058()) {
    m_drPixlMan->setMainRenderTarget();
    return;
  }
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (m_drPixlPostObjTMAA != nullptr) {
    m_drPixlPostObjTMAA->render();
  }
  if (m_drPixlPostObjRainDrop != nullptr) {
    m_drPixlPostObjRainDrop->render();
  }
  if (m_drMan->unknown1d7d || m_drMan->unknown1d7e) {
    m_drPixlMan->setMainRenderTarget();
  } else {
    bool isAA = false;
    if ((postParm->m_AAOn && !postParm->m_TMAAOn) || (postParm->m_TMAAOn && postParm->unknown16d)) {
      isAA = true;
    }
    if (m_drPixlPostObjDepthofField != nullptr || m_drPixlPostObjMotionBlur != nullptr || m_drPixlPostObjMotionBlur2 != nullptr) {
      m_drPixlMan->unknown7f0->unknown138->setColorInvalidate();
      if (m_drPixlPostObjDepthofField != nullptr) {
        m_drPixlPostObjDepthofField->render();
      }
      if (!postParm->m_motBlur2) {
        if (postParm->isMotBlur() && m_drPixlPostObjMotionBlur != nullptr) {
          m_drPixlPostObjMotionBlur->render();
        }
      } else if (m_drPixlPostObjMotionBlur2 != nullptr) {
        m_drPixlPostObjMotionBlur2->render();
      }
    }
    if (postParm->m_bloomOn && m_drPixlPostObjBloom != nullptr) {
      m_drPixlPostObjBloom->calcRender();
      if (isCalcVolume()) {
        m_drPixlPostObjVolume->volumeRender();
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        m_drPixlPostObjBloom->calcCollectRender(true);
      } else {
        m_drPixlPostObjBloom->calcCollectRender(false);
      }
      grlib::CGLibCtlShader::setMemoryBarrierBit(2);
      m_drPixlMan->unknown7f0->unknown138->setRenderTarget();
      m_drPixlPostObjBloom->bloomRender();
    }
    m_drPixlMan->unknown7f0->unknown138->setColorInvalidate();
    wkPixlManRes *res = m_drPixlMan->unknown7f0;
    if (res->unknown1d8 & DrPixlMan::unknown001_2) {
      m_drPixlMan->offScreenAlphaRender();
    }
    if (postParm->m_colTblOn) {
      m_drPixlPostObj3dLut->renderLUT();
    }
    if (postParm->unknown480) {
      m_drPixlMan->setMainRenderTarget();
      m_drPixlMan->debugIlluminanceRender();
    } else if (isAA) {
      if (!postParm->m_colTblOn) {
        if (postParm->m_toneMapOn) {
          DrAPGxType::setupScreenQuads(false);
          bool isSRGB = DrMan::isSRGBMode();
          m_drPixlMan->getTempColorBuff()->setRenderTarget();
          if (isSRGB) {
            m_drPixlMan->gammaRender(false);
          } else {
            m_drPixlMan->toneMapRender(false);
          }
          m_drPixlMan->changeColorBuff();
        }
      } else {
        m_drPixlMan->getTempColorBuff()->setRenderTarget();
        DrPixlPostObj3dLut *lut = m_drPixlPostObj3dLut;
        lut->render_applyLUT(false, DrMan::isSRGBMode());
        lut->unknown18 = false;
        m_drPixlMan->changeColorBuff();
      }
      if (postParm->m_TMAAOn) {
        m_drPixlPostObjTMAA->renderSharpness();
      } else {
        m_drPixlPostObjFxAA->render();
      }
    } else {
      DrAPGxType::setupScreenQuads(false);
      if (DrMan::isSRGBMode()) {
        if (!postParm->m_colTblOn) {
          grlib::CGLibState::setMainFrameBuffer();
          if (postParm->unknownfb3) {
            m_drPixlMan->gammaRender(true);
          } else {
            m_drPixlMan->gammaRender(false);
          }
        } else {
          m_drPixlMan->setMainRenderTarget();
          DrPixlPostObj3dLut *lut = m_drPixlPostObj3dLut;
          if (lut != nullptr) {
            lut->render_applyLUT(postParm->unknownfb3, true);
            lut->unknown18 = false;
          }
        }
      } else {
        m_drPixlMan->setMainRenderTarget();
        if (postParm->m_colTblOn) {
          DrPixlPostObj3dLut *lut = m_drPixlPostObj3dLut;
          if (lut != nullptr) {
            lut->render_applyLUT(postParm->unknownfb3, false);
            lut->unknown18 = false;
          }
        } else {
          if (postParm->unknownfb3) {
            m_drPixlMan->toneMapRender(true);
          } else {
            m_drPixlMan->toneMapRender(false);
          }
        }
      }
    }
    if (res->unknown1d8 & DrPixlMan::unknown001_2) {
      DrAPGxType::setupAlphaChanel(true);
    }
  }
  if (m_drPixlPostObjGlassBr != nullptr) {
    m_drPixlPostObjGlassBr->render();
  }
}

void DrPixlPostMan::capRender() {
  if (m_drPixlPostObjCapture != nullptr) {
    m_drPixlPostObjCapture->render();
  }
}

void DrPixlPostMan::setGlassBreak(bool isGlassBreak) {
  DrPixlPostObjGlassBr *glassBreak = m_drPixlPostObjGlassBr;
  if (glassBreak == nullptr) {
    if (isGlassBreak) {
      m_drPixlPostObjGlassBr = new (m_drMan->unknown0c) DrPixlPostObjGlassBr(m_drMan, m_drPixlMan, this);
    }
  } else if ((glassBreak->unknown508 & DrPixlPostObjGlassBr::FLAG_UNKNOWN_3) == 0) {
    if (!isGlassBreak) {
      glassBreak->unknown508 |= DrPixlPostObjGlassBr::FLAG_UNKNOWN_2;
    }
  } else {
    delete glassBreak;
    m_drPixlPostObjGlassBr = nullptr;
  }
}

void DrPixlPostMan::setCaputureMode(bool isCapture) {
  DrPixlPostObjCapture *capture = m_drPixlPostObjCapture;
  if (capture == nullptr) {
    if (isCapture) {
      m_drPixlPostObjCapture = new (m_drMan->unknown0c) DrPixlPostObjCapture(m_drMan, m_drPixlMan, this);
    }
  } else if ((capture->unknown3e0 & DrPixlPostObjCapture::FLAG_UNKNOWN_3) == 0) {
    if (!isCapture) {
      capture->unknown3e0 |= DrPixlPostObjCapture::FLAG_UNKNOWN_2;
    }
  } else {
    delete capture;
    m_drPixlPostObjCapture = nullptr;
  }
}

void DrPixlPostMan::setBloom(bool isBloom) { unknownf8 = !isBloom ? unknownf8 & ~(FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3) : unknownf8 | (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3); }

void DrPixlPostMan::setSSAO(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_UNKNOWN_4;
  } else if (unknownf8 & FLAG_UNKNOWN_4) {
    unknownf8 &= ~FLAG_UNKNOWN_4;
  }
}

void DrPixlPostMan::setBlur(bool isBlur) {
  if (isBlur) {
    unknownf8 |= FLAG_UNKNOWN_6 | FLAG_UNKNOWN_19;
    if (m_drPixlPostObjMotionBlur2 == nullptr) {
      m_drPixlPostObjMotionBlur2 = new (m_drMan->unknown0c) DrPixlPostObjMotionBlur2(m_drMan, m_drPixlMan, this);
    }
  } else if (unknownf8 & FLAG_UNKNOWN_6) {
    if (m_drPixlPostObjMotionBlur != nullptr) {
      delete m_drPixlPostObjMotionBlur;
      m_drPixlPostObjMotionBlur = nullptr;
    }
    if (m_drPixlPostObjMotionBlur2 != nullptr) {
      delete m_drPixlPostObjMotionBlur2;
      m_drPixlPostObjMotionBlur2 = nullptr;
    }
    unknownf8 &= ~FLAG_UNKNOWN_6;
  }
}

void DrPixlPostMan::setDepthField(bool isDepthField) {
  if (isDepthField) {
    unknownf8 |= FLAG_UNKNOWN_5 | FLAG_UNKNOWN_19;
    if (m_drPixlPostObjDepthofField == nullptr) {
      m_drPixlPostObjDepthofField = new (m_drMan->unknown0c) DrPixlPostObjDepthofField(m_drMan, m_drPixlMan, this);
    }
  } else if (unknownf8 & FLAG_UNKNOWN_5) {
    unknownf8 &= ~FLAG_UNKNOWN_5;
    if (m_drPixlPostObjDepthofField != nullptr) {
      delete m_drPixlPostObjDepthofField;
      m_drPixlPostObjDepthofField = nullptr;
    }
  }
}

void DrPixlPostMan::renderDownDepth(bool isDepth, bool isTemporal, bool isEtc) {
  if (!(unknownf8 & FLAG_UNKNOWN_19)) {
    return;
  }
  DrAPGxType::setupScreenQuads(false);
  mm::mtl::FixedVector<grlib::CGLibRenderTarget *, 2> targets;
  DrPixlRenderTarget *target = unknownc0[DrMan::s_nDblIdx];
  // The FixedVector's size is zeroed at the start (0x710084f1a4) and cleared again at the end of the function (0x710084fee8), so the targets are a
  // FixedVector; the set call with no target (null, 0) is shared with the path without a depth buffer.
  grlib::CGLibDepthBuffer *depthBuffer = nullptr;
  if (isDepth) {
    depthBuffer = m_drPixlMan->unknown7f0->unknown1b0->unknown120;
    if (isTemporal) {
      targets.push_back(m_drPixlMan->getPixlObj(12));
    }
    if (isEtc) {
      targets.push_back(unknowne8);
    }
    grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_ALWAYS);
  }
  if (targets.size() != 0) {
    target->setRenderTargetImpl(targets.begin(), targets.size(), depthBuffer);
  } else {
    target->setRenderTargetImpl(nullptr, 0, depthBuffer);
  }
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(3);
  // The game computes each index right before its getDeclarationOfs call (0x710084f26c, 0x710084f294 and 0x710084f2bc: tst, then cinc, then the
  // call, the index kept in a callee-saved register); an index computed inside the call arguments is computed after the call.
  u32 depthIndex = isDepth ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUT_NON_LINEAR_DEPTH"), depthIndex);
  u32 stencilIndex = isTemporal ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUT_EXP_STENCIL"), stencilIndex);
  u32 similarityIndex = isEtc ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("ENCODE_SIMILARITY"), similarityIndex);
  // The uniform setup and the draw tail (updateData, setUniformBlock, renderQuads, setColorInvalidate) are written out like in the other post process functions
  // of this unit (ruling 8, measured): a file-local helper holding updateData, setUniformBlock and renderQuads (the uniform by reference, with or without the
  // setColorInvalidate of the target) gives 886 instructions against 882 here and 190 against 186 in renderRefractionMap.
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 fragToUv = uniform.unknown001("gFragToUV");
  f32 fragToUvValue[4];
  fragToUvValue[0] = 1.0f / static_cast<f32>(target->unknownbc);
  fragToUvValue[1] = 1.0f / static_cast<f32>(target->unknownc0);
  fragToUvValue[2] = 0.0f;
  fragToUvValue[3] = 0.0f;
  uniform.setF32SetVec4(fragToUv, fragToUvValue);
  DrCalcViewWork *viewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  u32 clParms = uniform.unknown001("gClParms");
  f32 clParmValue[4];
  clParmValue[0] = viewWork->unknown4cc - viewWork->unknown4c8;
  clParmValue[1] = viewWork->unknown4cc * viewWork->unknown4c8;
  clParmValue[2] = viewWork->unknown4cc;
  clParmValue[3] = 0.0f;
  uniform.setF32SetVec4(clParms, clParmValue);
  u32 projInv = uniform.unknown001("gProjInv");
  uniform.setMat44SetMat44(projInv, viewWork->unknown3c0);
  u32 toPrevScreen = uniform.unknown001("gToPrevScreen");
  mm::Mat44 matrix = viewWork->unknown00;
  matrix.unknown009(matrix, viewWork->unknown280 * viewWork->unknown380);
  uniform.setMat44SetMat44(toPrevScreen, matrix);
  u32 jitter = uniform.unknown001("gJitter");
  mm::Vec4 jitterValue;
  jitterValue.x = viewWork->unknownac0.x - viewWork->unknownad0.x;
  jitterValue.y = -(viewWork->unknownac0.y - viewWork->unknownad0.y);
  jitterValue.z = 0.0f;
  jitterValue.w = 0.0f;
  uniform.setVec4SetVec4(jitter, jitterValue);
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*m_drPixlMan->getDepthObj()->unknown128, depthLocation);
  if (isTemporal) {
    int stencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*m_drPixlMan->getDepthObj()->unknown130, stencilLocation);
  }
  int prevDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevDownDepth");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*m_drMan->m_drPixlMan->unknown7f0->m_drPixlPostMan->getOldDownDepth()->unknown70, prevDepthLocation);
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocity");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*m_drMan->m_drPixlMan->getPixlObj(3)->unknown70, velocityLocation);
  int etcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*m_drMan->m_drPixlMan->getPixlObj(1)->unknown70, etcLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
  unknownf8 &= ~FLAG_UNKNOWN_19;
}

DrPixlRenderTarget *DrPixlPostMan::getOldDownDepth() { return unknownc0[DrMan::s_nDblStockIdx]; }

bool DrPixlPostMan::debugDeferredRenderImpl(bool isRender) {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  int flags[26] = {postParm->m_defferedColor, postParm->unknown305, postParm->unknown306, postParm->unknown307, postParm->unknown308,
                   postParm->unknown309,      postParm->unknown30a, postParm->unknown30b, postParm->unknown30c, postParm->unknown30d,
                   postParm->unknown30e,      postParm->unknown30f, postParm->unknown310, postParm->unknown314, postParm->unknown315 && unknownd0 != nullptr,
                   postParm->unknown316,      postParm->unknown313, postParm->unknown317, postParm->unknown318, postParm->unknown311,
                   postParm->unknown319,      postParm->unknown312, postParm->unknown31a, postParm->unknown31b, postParm->unknown31c,
                   postParm->unknown31d};
  int count = 0;
  for (int i = 0; i < 26; i++) {
    count += flags[i];
  }
  if (count != 0 && isRender) {
    m_drPixlMan->setMainRenderTarget();
    int divisions;
    if (count == 1) {
      divisions = 1;
    } else if (count < 5) {
      divisions = 2;
    } else {
      divisions = 3;
      if (count >= 10 && count <= 16) {
        divisions = 4;
      }
    }
    int width = m_drMan->unknown5b8->unknown18 / divisions;
    int height = m_drMan->unknown5b8->unknown1c / divisions;
    int x = 0;
    int y = 0;
    int column = 0;
    for (int i = 0; i < 26; i++) {
      if (flags[i] != 0) {
        m_drPixlMan->debugDeferredRender(i, x, y, width, height, false);
        if (++column >= divisions) {
          column = 0;
          x = 0;
          y += height;
        } else {
          x += width;
        }
      }
    }
  }
  return count != 0;
}

void DrPixlPostMan::setToneMaping(bool isToneMaping) { unknownf8 = !isToneMaping ? unknownf8 & ~FLAG_UNKNOWN_1 : unknownf8 | FLAG_UNKNOWN_1; }

void DrPixlPostMan::setVolume(bool isVolume) { unknownf8 = !isVolume ? unknownf8 & ~FLAG_UNKNOWN_3 : unknownf8 | FLAG_UNKNOWN_3; }

void DrPixlPostMan::set3DLut(bool is3DLut) { unknownf8 = !is3DLut ? unknownf8 & ~FLAG_UNKNOWN_0 : unknownf8 | FLAG_UNKNOWN_0; }

void DrPixlPostMan::setSSAOAv(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_UNKNOWN_4;
  } else if (unknownf8 & FLAG_UNKNOWN_4) {
    unknownf8 &= ~FLAG_UNKNOWN_4;
  }
}

void DrPixlPostMan::setVolumePos(const mm::Vec3 &pos) {
  if (m_drPixlPostObjVolume != nullptr) {
    m_drPixlPostObjVolume->unknown30 = pos;
  }
}

void DrPixlPostMan::setDepthFieldParm(f32 distance, f32 range, f32 strength) {}

void DrPixlPostMan::setBlurParm(f32 strength, f32 sub) {}

bool DrPixlPostMan::isToneMaping() { return unknownf8 & FLAG_UNKNOWN_1; }

bool DrPixlPostMan::isBloom() { return unknownf8 & FLAG_UNKNOWN_2; }

bool DrPixlPostMan::isCalcBloom() { return unknownf8 & FLAG_UNKNOWN_15; }

bool DrPixlPostMan::is3DLut() { return unknownf8 & FLAG_UNKNOWN_0; }

bool DrPixlPostMan::isVolume() { return unknownf8 & FLAG_UNKNOWN_3; }

bool DrPixlPostMan::isBluer() { return unknownf8 & FLAG_UNKNOWN_6; }

bool DrPixlPostMan::isDepthField() { return unknownf8 & FLAG_UNKNOWN_5; }

bool DrPixlPostMan::isSSAO() { return unknownf8 & FLAG_UNKNOWN_4; }

bool DrPixlPostMan::isSSS() { return unknownf8 & FLAG_UNKNOWN_9; }

bool DrPixlPostMan::isReflection() { return unknownf8 & FLAG_UNKNOWN_7; }

bool DrPixlPostMan::isChgShader() { return unknownf8 & FLAG_UNKNOWN_8; }

bool DrPixlPostMan::isDepthDown() { return unknownf8 & FLAG_UNKNOWN_19; }

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonGradTex() const {
  if (m_drPixlToonGrad != nullptr) {
    return &m_drPixlToonGrad->getGradTex();
  }
  return nullptr;
}

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonDarkGradTex() const {
  if (m_drPixlToonGrad != nullptr) {
    return &m_drPixlToonGrad->getDarkGradTex();
  }
  return nullptr;
}

} // namespace ml
