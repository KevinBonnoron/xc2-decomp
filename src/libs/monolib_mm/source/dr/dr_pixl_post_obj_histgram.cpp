#include "dr/dr_pixl_post_obj_histgram.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_use_query_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlPostObjHistgram::DrPixlPostObjHistgram(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  m_drResUseQueryObj = nullptr;
  unknowna4 = 0;
  unknowna8 = 1;
  unknownac = 100000.0f;
  unknownb0 = 0.0f;
  unknownb4 = getSectionNum();
  unknownb8 = false;
  m_drResUseQueryObj = new (m_drMan->unknown0c) DrResUseQueryObj();
  resetMaxLuminance(32.0f);
}

void DrPixlPostObjHistgram::resetMaxLuminance(f32 maxLuminance) {
  if (unknowna8 == 0) {
    for (int i = 0; i < 10; i++) {
      m_maxLuminance[i] = maxLuminance / 10.0f * static_cast<f32>(i + 1);
    }
  } else if (unknowna8 == 1) {
    f32 minLog = logf(1.0f / 256.0f) / logf(2.0f);
    f32 maxLog = logf(maxLuminance) / logf(2.0f);
    for (int i = 0; i < 10; i++) {
      m_maxLuminance[i] = exp2f((maxLog - minLog) * (static_cast<f32>(i) / 10.0f) + minLog);
    }
  }
  m_maxLuminance[9] = maxLuminance;
  m_maxLuminance[10] = 100000.0f;
  for (int i = 0; i < getSectionNum(); i++) {
    m_percentage[i] = 0.0f;
  }
  for (int i = 0; i < getSectionNum(); i++) {
    unknown78[i] = 0;
  }
}

DrPixlPostObjHistgram::~DrPixlPostObjHistgram() {
  DrResUseQueryObj *query = m_drResUseQueryObj;
  if (query != nullptr) {
    delete query;
    m_drResUseQueryObj = nullptr;
  }
}

void DrPixlPostObjHistgram::update() {
  if (m_drMan->unknown058()) {
    return;
  }
  m_drResUseQueryObj->update();
  DrMan *drMan = m_drMan;
  if (drMan->unknown120[drMan->unknown1c98]->unknownf54) {
    for (int i = 0; i < getSectionNum(); i++) {
      unknown78[i] = 0;
    }
    unknownb4 = getSectionNum();
  }
  f32 total;
  if (unknowna4 < 0) {
    total = 0.0f;
  } else {
    u32 pixel = m_drResUseQueryObj->m_pixel;
    u32 index = (unknowna4 + getSectionNum() - 1) % getSectionNum();
    u32 sum = 0;
    for (int i = 0; i < getSectionNum(); i++) {
      sum += unknown78[i];
    }
    total = static_cast<f32>(sum + pixel - unknown78[index]);
    m_percentage[index] = static_cast<f32>(pixel) / total;
    unknown78[index] = pixel;
    unknowna4 = (unknowna4 + 1) % getSectionNum();
  }
  bool isValid = false;
  if (unknownb4 > 0) {
    DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
    f32 min = postParm->unknown28;
    f32 max = postParm->unknown2c;
    min *= postParm->m_toneMax;
    max *= postParm->m_toneMax;
    unknownac = max;
    unknownb0 = min;
    m_drPixlMan->setToneAveRange(min, max);
    unknownb4--;
  } else {
    u32 height;
    u32 width;
    if (!drMan->unknown1de8) {
      DrPixlRenderTarget *target = m_drPixlMan->unknown7f0->unknown00[5][0];
      width = mm::min(mm::max(80u, target->unknownbc >> drMan->unknown1de4), target->unknownbc);
      height = mm::min(mm::max(45u, target->unknownc0 >> drMan->unknown1de4), target->unknownc0);
    } else {
      grlib::CGLibRenderTarget *target = m_drPixlMan->unknown7f0->m_drPixlPostMan->m_drPixlPostObjToneMap->unknown18[0];
      width = target->unknownbc;
      height = target->unknownc0;
    }
    if (total / static_cast<f32>(width * height) >= 0.05f) {
      DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
      f32 min = postParm->unknown28;
      f32 max = postParm->unknown2c;
      if (min >= max) {
        if (max <= 0.01f) {
          min = 0.0f;
          max = 0.01f;
        } else {
          min = max - 0.01f;
        }
      }
      unknownb0 += (calcLuminanceAve(min, true) - unknownb0) * 0.05f;
      unknownac += (calcLuminanceAve(max, false) - unknownac) * 0.05f;
      m_drPixlMan->setToneAveRange(unknownb0, unknownac);
      isValid = true;
    }
  }
  unknownb8 = isValid;
}

void DrPixlPostObjHistgram::render() {
  DrAPCache *apCache = m_drMan->m_drAPCache;
  grlib::CGLibColorCtl::setColorBufferOff();
  DrFogMan *fogMan = m_drMan->m_drFogMan;
  bool isDepthFog = fogMan->isFogOn() && fogMan->unknownd1;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x27);
  u32 depthCheck = isDepthFog ? 2 : 1;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEPTH_CHECK"), depthCheck);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  shdList->bindQuadsTex();
  shader->setupShader(0u);
  u32 paramOffset = uniform.unknown001("gParam");
  mm::Vec4 param = mm::Vec4::zero;
  unknown001 section = getSection(unknowna4);
  param.x = section.unknown00;
  param.y = section.unknown04;
  param.z = m_drMan->unknown588->getSkyLuminance();
  uniform.setF32SetVec4(paramOffset, &param.x);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  grlib::CGLibRenderTarget *target = m_drPixlMan->unknown7f0->m_drPixlPostMan->m_drPixlPostObjToneMap->unknown18[0];
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*target->unknown70, location);
  if (!isDepthFog) {
    int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("depth");
    DrPixlRenderTarget *depth = m_drPixlMan->unknown7f0->m_drPixlPostMan->getDownDepth();
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*depth->unknown70, depthLocation);
  }
  target->setRenderTarget();
  uniform.updateData();
  uniform.setUniformBlock();
  m_drResUseQueryObj->begin(m_drPixlMan->m_drPixlOccQuery);
  shdList->renderQuads();
  m_drResUseQueryObj->end();
  grlib::CGLibColorCtl::setColorBufferOn();
}

f32 DrPixlPostObjHistgram::calcLuminanceAve(f32 rate, bool isLow) const {
  f32 total = 0.0f;
  for (u32 i = 0; i < static_cast<u32>(getSectionNum()); i++) {
    total += m_percentage[i];
    if (rate <= total) {
      unknown001 section = getSection(i);
      return isLow ? section.unknown00 : section.unknown04;
    }
  }
  return 0.0f;
}

DrPixlPostObjHistgram::unknown001 DrPixlPostObjHistgram::getSection(u32 index) const {
  unknown001 section;
  if (index == 0) {
    section.unknown00 = 0.0f;
  } else {
    section.unknown00 = m_maxLuminance[index - 1];
  }
  section.unknown04 = m_maxLuminance[index];
  return section;
}

f32 DrPixlPostObjHistgram::getMaxLuminance() const { return m_maxLuminance[9]; }

int DrPixlPostObjHistgram::getSectionNum() const { return 0xb; }

f32 DrPixlPostObjHistgram::getPercentage(u32 index) const { return m_percentage[index]; }

} // namespace ml
