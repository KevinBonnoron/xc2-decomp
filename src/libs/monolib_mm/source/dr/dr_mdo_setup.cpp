#include "dr/dr_mdo_setup.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_mdo_uniform_block.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_render_target.h"
#include "grlib/shd_util.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

int DrMdoSetup::unimate_texMatrix(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = m_matRes;
  grlib::ShdF32SetF32Array(work, &matRes->values[header->valueOffset + variable->valueIndex], variable->count * 8);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_TEX_MATRIX] * variable->count;
}

int DrMdoSetup::unimate_workFloat4(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = m_matRes;
  grlib::ShdF32SetF32Array(work, &matRes->values[header->valueOffset + variable->valueIndex], variable->count * 4);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_WORK_FLOAT4] * variable->count;
}

int DrMdoSetup::unimate_workColor(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = m_matRes;
  grlib::ShdF32SetF32Array(work, &matRes->values[header->valueOffset + variable->valueIndex], variable->count * 4);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_WORK_COLOR] * variable->count;
}

int DrMdoSetup::unimate_ProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = m_matRes;
  const f32 *values = &matRes->values[header->valueOffset + variable->valueIndex];
  for (int i = 0; i < variable->count; i++, work += 12) {
    grlib::ShdF32TransposeMat34(work, &values[i * 16]);
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJECTION_MAT] * variable->count;
}

int DrMdoSetup::unimate_NomProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = m_matRes;
  const f32 *values = &matRes->values[header->valueOffset + variable->valueIndex];
  for (int i = 0; i < variable->count; i++, work += 12) {
    grlib::ShdF32TransposeMat34(work, &values[i * 16]);
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_NOM_PROJECTION_MAT] * variable->count;
}

void DrMdoSetup::varStTex_ColorTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(0)->m_texture, location);
}

void DrMdoSetup::varStTex_NormalTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(2)->m_texture, location);
}

void DrMdoSetup::varStTex_LightTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlShader::setMemoryBarrierBit(4);
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(15)->m_texture, location);
}

void DrMdoSetup::varStTex_DepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(4)->m_texture, location);
}

void DrMdoSetup::varStTex_RefTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_ShadowMap(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibTextureBuffer *texture = m_drMan->pixlMan->m_res->deferred->getShadowMapTexture();
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*texture, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap1(const MdsMatInfoHeader *header, u32 location, u32 index) {
  m_drMan->pixlMan->m_res->deferred->getShadowMapTexture();
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_matRes->avatar->baseTextures[0], location);
}

void DrMdoSetup::varStTex_Capture1(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  DrAPCache *cache = m_drMan->apCache;
  grlib::CGLibRenderTarget *target = pixlMan->m_resources[1].mainRenderTarget;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *pixlMan->m_resources[1].mainRenderTarget->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_Capture2(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  cache->beginTexSampling(2, 1);
  grlib::CGLibRenderTarget *target = pixlMan->m_resources[2].mainRenderTarget;
  cache->setTexture(target != nullptr ? *target->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_Capture3(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  cache->beginTexSampling(2, 1);
  grlib::CGLibRenderTarget *target = pixlMan->m_resources[3].mainRenderTarget;
  cache->setTexture(target != nullptr ? *target->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_RefractionMap(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  DrAPCache *cache = m_drMan->apCache;
  grlib::CGLibRenderTarget *target = pixlMan->m_res->postMan->m_refractionMap;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *target->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_ColorDepTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(0)->m_texture, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap2(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_matRes->avatar->baseTextures[1], location);
}

void DrMdoSetup::varStTex_AvatarEyeTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->beginTexSampling(2, 1);
  cache->setMipMapOn(*m_matRes->avatar->eyeBaseTexture);
  cache->setTexture(*m_matRes->avatar->eyeBaseTexture, location);
}

void DrMdoSetup::varStTex_CaptureMain(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  DrAPCache *cache = m_drMan->apCache;
  grlib::CGLibRenderTarget *target = pixlMan->m_resources[0].mainRenderTarget;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *pixlMan->m_resources[0].mainRenderTarget->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_BaseColorTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(0)->m_texture, location);
}

void DrMdoSetup::varStTex_ScreenCapTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlRenderTarget *target = m_drMan->pixlMan->getPixlObj(5);
  if (target != nullptr) {
    DrAPCache *cache = m_drMan->apCache;
    cache->beginTexSampling(2, 1);
    cache->setTexture(*target->m_texture, location);
  }
}

void DrMdoSetup::varStTex_ToonGradTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  const grlib::CGLibTextureBuffer *texture = m_drMan->pixlMan->m_res->postMan->getToonGradTex();
  if (texture != nullptr) {
    cache->setTexture(*texture, location);
  }
}

void DrMdoSetup::varStTex_RefLightTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_BackFaceDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getBackFaceDepthTexture()->m_texture, location);
}

void DrMdoSetup::varStTex_DownDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_drMan->pixlMan->m_res->postMan->getDownDepth()->m_texture, location);
}

void DrMdoSetup::varStTex_ClusterIdxListTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_VelocityTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(3)->m_texture, location);
}

void DrMdoSetup::varStTex_RefractionAfterTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->pixlMan;
  DrAPCache *cache = m_drMan->apCache;
  grlib::CGLibRenderTarget *target = pixlMan->m_res->postMan->m_refractionMap;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *target->m_texture : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_DiffuseIBL(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_drMan->pixlMan->getDiffIBLObj()->m_texture, location);
}

void DrMdoSetup::varStTex_AOTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(2)->m_texture, location);
}

void DrMdoSetup::varStTex_EtcTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->pixlMan->getPixlObj(1)->m_texture, location);
}

void DrMdoSetup::varStTex_ToonDarkGradTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->apCache;
  cache->beginTexSampling(2, 1);
  const grlib::CGLibTextureBuffer *texture = m_drMan->pixlMan->m_res->postMan->getToonDarkGradTex();
  if (texture != nullptr) {
    cache->setTexture(*texture, location);
  }
}

void DrMdoSetup::varStImg_BaseColor(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->pixlMan->getPixlObj(0)->m_texture, location, 0, 0);
}

void DrMdoSetup::varStImg_Etc(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->pixlMan->getPixlObj(1)->m_texture, location, 0, 0);
}

void DrMdoSetup::varStImg_Normal(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->pixlMan->getPixlObj(2)->m_texture, location, 0, 0);
}

void DrMdoSetup::varStImg_Velocity(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->pixlMan->getPixlObj(3)->m_texture, location, 0, 0);
}

void DrMdoSetup::varStImg_ZBuff(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->pixlMan->getPixlObj(4)->m_texture, location, 0, 0);
}

} // namespace ml
