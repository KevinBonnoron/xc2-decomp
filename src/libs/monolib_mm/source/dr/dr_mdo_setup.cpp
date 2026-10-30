#include "dr/dr_mdo_setup.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_cube_map_ibl.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_uniform_block.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_col4.h"

namespace ml {

void DrMdoSetup::changeShader(bool isChange) {
  if (isChange) {
    unknown178 |= 1;
  } else {
    unknown178 &= ~1;
  }
}

void DrMdoSetup::beginMatInfo() { unknown001(); }

void DrMdoSetup::changeSeamMatInfo() {
  unknown17c = 0xffff;
  unknown17e = 0xffff;
  unknown179 = 0;
  unknown178 |= 0x10;
}

void DrMdoSetup::changeShaderMat(bool isChange) {
  if (isChange) {
    unknown178 |= 0x10;
  } else {
    unknown178 &= ~0x10;
  }
}

void DrMdoSetup::changeShaderPos() { unknown178 |= 2; }

void DrMdoSetup::setupCharAvatarUniform() {}

void DrMdoSetup::setupDollAvatarUniform() {}

void DrMdoSetup::uniformBlock_Static(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown580->unknown10->unknown7b0.setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Material(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  (*unknown30->unknown90)[matIndex].setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Light(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown580->unknown10->unknown8c8.setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Mdl(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  (*unknown30->unknowna0)[mdlIndex].setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Bone(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown80->unknown00->unknown958[0].setStorageBuffer(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_OldMdl(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  grlib::CGLibTriUniformBlock &block = (*unknown30->unknowna0)[mdlIndex];
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (unknown168 & 0x200) {
    block.setUniformBlock(index);
  } else {
    block.setOldUniformBlock(index);
  }
}

void DrMdoSetup::uniformBlock_OldBone(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdDataList *dataList = m_drMan->unknown80->unknown00;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (unknown168 & 0x200) {
    dataList->unknown958[0].setStorageBuffer(index);
  } else {
    dataList->unknown958[1].setStorageBuffer(index);
  }
}

void DrMdoSetup::uniformBlock_no(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {}

void DrMdoSetup::uniformBlock_AvatarChar(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  unknown30->unknown110->unknown40->setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_AvatarDoll(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  unknown30->unknown110->unknown48->setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Fog(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown580->unknown10->unknown820.setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Toon(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown580->unknown10->unknown858.setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_VolTexCalc(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  (*unknown30->unknownb0)[bufferIndex].setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_GlobalIBL(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown78->unknown7f0->unknown180->unknown48->setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_ClusterParam(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdLgtClustered *clustered = m_drMan->unknown80->unknown18->getHybridLight()->unknown18;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (cate->unknown03 & MdsMatValShaderCate::FLAG_STORAGE_BUFFER) {
    clustered->setParamStorageBuffer(m_drMan->unknown1c98, index);
  } else {
    clustered->setParamUniformBlock(m_drMan->unknown1c98, index);
  }
}

void DrMdoSetup::uniformBlock_ClusterPntList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdLgtClustered *clustered = m_drMan->unknown80->unknown18->getHybridLight()->unknown18;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (cate->unknown03 & MdsMatValShaderCate::FLAG_STORAGE_BUFFER) {
    clustered->setPntLightStorageBuffer(m_drMan->unknown1c98, index);
  } else {
    clustered->setPntLightUniformBlock(m_drMan->unknown1c98, index);
  }
}

void DrMdoSetup::uniformBlock_ClusterSptList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdLgtClustered *clustered = m_drMan->unknown80->unknown18->getHybridLight()->unknown18;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (cate->unknown03 & MdsMatValShaderCate::FLAG_STORAGE_BUFFER) {
    clustered->setSptLightStorageBuffer(m_drMan->unknown1c98, index);
  } else {
    clustered->setSptLightUniformBlock(m_drMan->unknown1c98, index);
  }
}

void DrMdoSetup::uniformBlock_ClusterIdxList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdLgtClustered *clustered = m_drMan->unknown80->unknown18->getHybridLight()->unknown18;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (cate->unknown03 & MdsMatValShaderCate::FLAG_STORAGE_BUFFER) {
    clustered->setLightListStorageBuffer(m_drMan->unknown1c98, index);
  } else {
    clustered->setLightListUniformBlock(m_drMan->unknown1c98, index);
  }
}

void DrMdoSetup::uniformBlock_ClusterAddressList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  DrShdLgtClustered *clustered = m_drMan->unknown80->unknown18->getHybridLight()->unknown18;
  u32 index = unknown38->getValGlobalParam(paramIndex);
  if (cate->unknown03 & MdsMatValShaderCate::FLAG_STORAGE_BUFFER) {
    clustered->setPointerListStorageBuffer(m_drMan->unknown1c98, index);
  } else {
    clustered->setPointerListUniformBlock(m_drMan->unknown1c98, index);
  }
}

void DrMdoSetup::uniformBlock_RimBloomCalc(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  (*unknown30->unknownb8)[mdlIndex].setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

void DrMdoSetup::uniformBlock_Toon2(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex) {
  m_drMan->unknown580->unknown10->unknown890.setUniformBlock(unknown38->getValGlobalParam(paramIndex));
}

int DrMdoSetup::unimate_alphaInfo(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  work[0] = 1.0f;
  work[1] = mat->unknown18;
  f32 alpha = mat->unknown08.a;
  if ((header->unknown09 & 1) == 0) {
    alpha *= unknowne0;
  }
  work[2] = alpha;
  work[3] = unknownd8;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_23];
}

int DrMdoSetup::unimate_texMatrix(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = unknown30;
  grlib::ShdF32SetF32Array(work, &matRes->unknownf8[header->unknown40 + variable->unknown02], variable->unknown06 * 8);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_TEX_MATRIX] * variable->unknown06;
}

int DrMdoSetup::unimate_workFloat4(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = unknown30;
  grlib::ShdF32SetF32Array(work, &matRes->unknownf8[header->unknown40 + variable->unknown02], variable->unknown06 * 4);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_WORK_FLOAT4] * variable->unknown06;
}

int DrMdoSetup::unimate_workColor(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = unknown30;
  grlib::ShdF32SetF32Array(work, &matRes->unknownf8[header->unknown40 + variable->unknown02], variable->unknown06 * 4);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_WORK_COLOR] * variable->unknown06;
}

int DrMdoSetup::unimate_ProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = unknown30;
  const f32 *values = &matRes->unknownf8[header->unknown40 + variable->unknown02];
  for (int i = 0; i < variable->unknown06; i++, work += 12) {
    grlib::ShdF32TransposeMat34(work, &values[i * 16]);
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJECTION_MAT] * variable->unknown06;
}

int DrMdoSetup::unimate_NomProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable) {
  MdoWrkMatRes *matRes = unknown30;
  const f32 *values = &matRes->unknownf8[header->unknown40 + variable->unknown02];
  for (int i = 0; i < variable->unknown06; i++, work += 12) {
    grlib::ShdF32TransposeMat34(work, &values[i * 16]);
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_NOM_PROJECTION_MAT] * variable->unknown06;
}

void DrMdoSetup::varStTex_ColorTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(0)->unknown70, location);
}

void DrMdoSetup::varStTex_NormalTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(2)->unknown70, location);
}

void DrMdoSetup::varStTex_LightTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibCtlShader::setMemoryBarrierBit(4);
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(15)->unknown70, location);
}

void DrMdoSetup::varStTex_DepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(4)->unknown70, location);
}

void DrMdoSetup::varStTex_RefTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_ShadowMap(const MdsMatInfoHeader *header, u32 location, u32 index) {
  grlib::CGLibTextureBuffer *texture = m_drMan->unknown78->unknown7f0->unknown170->getShadowMapTexture();
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*texture, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap1(const MdsMatInfoHeader *header, u32 location, u32 index) {
  m_drMan->unknown78->unknown7f0->unknown170->getShadowMapTexture();
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*unknown30->unknown110->unknown08[0], location);
}

void DrMdoSetup::varStTex_Capture1(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->unknown78;
  DrAPCache *cache = m_drMan->unknown5c0;
  grlib::CGLibRenderTarget *target = pixlMan->unknown10[1].unknown1d0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *pixlMan->unknown10[1].unknown1d0->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_Capture2(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  DrPixlMan *pixlMan = m_drMan->unknown78;
  cache->beginTexSampling(2, 1);
  grlib::CGLibRenderTarget *target = pixlMan->unknown10[2].unknown1d0;
  cache->setTexture(target != nullptr ? *target->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_Capture3(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  DrPixlMan *pixlMan = m_drMan->unknown78;
  cache->beginTexSampling(2, 1);
  grlib::CGLibRenderTarget *target = pixlMan->unknown10[3].unknown1d0;
  cache->setTexture(target != nullptr ? *target->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_RefractionMap(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->unknown78;
  DrAPCache *cache = m_drMan->unknown5c0;
  grlib::CGLibRenderTarget *target = pixlMan->unknown7f0->unknown180->unknownd0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *target->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_ColorDepTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(0)->unknown70, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap2(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*unknown30->unknown110->unknown08[1], location);
}

void DrMdoSetup::varStTex_AvatarEyeTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->beginTexSampling(2, 1);
  cache->setMipMapOn(*unknown30->unknown110->unknown28);
  cache->setTexture(*unknown30->unknown110->unknown28, location);
}

void DrMdoSetup::varStTex_CaptureMain(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->unknown78;
  DrAPCache *cache = m_drMan->unknown5c0;
  grlib::CGLibRenderTarget *target = pixlMan->unknown10[0].unknown1d0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *pixlMan->unknown10[0].unknown1d0->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_BaseColorTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(0)->unknown70, location);
}

void DrMdoSetup::varStTex_ScreenCapTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlRenderTarget *target = m_drMan->unknown78->getPixlObj(5);
  if (target != nullptr) {
    DrAPCache *cache = m_drMan->unknown5c0;
    cache->beginTexSampling(2, 1);
    cache->setTexture(*target->unknown70, location);
  }
}

void DrMdoSetup::varStTex_ToonGradTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  const grlib::CGLibTextureBuffer *texture = m_drMan->unknown78->unknown7f0->unknown180->getToonGradTex();
  if (texture != nullptr) {
    cache->setTexture(*texture, location);
  }
}

void DrMdoSetup::varStTex_RefLightTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_BackFaceDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getBackFaceDepthTexture()->unknown70, location);
}

void DrMdoSetup::varStTex_DownDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_drMan->unknown78->unknown7f0->unknown180->getDownDepth()->unknown70, location);
}

void DrMdoSetup::varStTex_ClusterIdxListTex(const MdsMatInfoHeader *header, u32 location, u32 index) {}

void DrMdoSetup::varStTex_VelocityTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(3)->unknown70, location);
}

void DrMdoSetup::varStTex_RefractionAfterTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->unknown78;
  DrAPCache *cache = m_drMan->unknown5c0;
  grlib::CGLibRenderTarget *target = pixlMan->unknown7f0->unknown180->unknownd0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(target != nullptr ? *target->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_DiffuseIBL(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(*m_drMan->unknown78->getDiffIBLObj()->unknown70, location);
}

void DrMdoSetup::varStTex_AOTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(2)->unknown70, location);
}

void DrMdoSetup::varStTex_EtcTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(*m_drMan->unknown78->getPixlObj(1)->unknown70, location);
}

void DrMdoSetup::varStTex_ToonDarkGradTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  const grlib::CGLibTextureBuffer *texture = m_drMan->unknown78->unknown7f0->unknown180->getToonDarkGradTex();
  if (texture != nullptr) {
    cache->setTexture(*texture, location);
  }
}

void DrMdoSetup::varStTex_AmbBRDFTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(m_drMan->unknown70->unknown98[3], location);
}

void DrMdoSetup::varStTex_ToonRimTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(2, 1);
  cache->setTexture(m_drMan->unknown70->unknown98[6], location);
}

void DrMdoSetup::varStTex_VolumeTex01(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->begin3DTextureWarpSampling();
  cache->setTexture(m_drMan->unknown70->unknown98[7], location);
}

void DrMdoSetup::varStTex_OrientationTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(0, 0);
  cache->setTexture(m_drMan->unknown70->unknown98[15], location);
}

void DrMdoSetup::varStTex_FlagWaveTex0(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(0, 1);
  cache->setTexture(m_drMan->unknown70->unknown98[16], location);
}

void DrMdoSetup::varStTex_FlagWaveTex1(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->beginTexSampling(0, 1);
  cache->setTexture(m_drMan->unknown70->unknown98[17], location);
}

void DrMdoSetup::varStTex_DitherTex(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  const grlib::CGLibTextureBuffer *texture;
  if ((header->unknown09 & 4) == 0) {
    cache->beginTexSampling(2, 0);
    texture = &m_drMan->unknown70->unknown98[1];
  } else {
    cache->beginTexSampling(0, 1);
    texture = m_drMan->unknown78->getDammyWhiteTexObj();
  }
  cache->setTexture(*texture, location);
}

void DrMdoSetup::varStTex_Capture4(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrAPCache *cache = m_drMan->unknown5c0;
  DrPixlMan *pixlMan = m_drMan->unknown78;
  cache->beginTexSampling(2, 1);
  grlib::CGLibRenderTarget *target = pixlMan->unknown9c0;
  cache->setTexture(target != nullptr ? *target->unknown70 : *pixlMan->getDammyTexObj(), location);
}

void DrMdoSetup::varStTex_Movie0(const MdsMatInfoHeader *header, u32 location, u32 index) {
  DrPixlMan *pixlMan = m_drMan->unknown78;
  DrAPCache *cache = m_drMan->unknown5c0;
  grlib::CGLibTextureBuffer *texture = pixlMan->unknown808[0];
  if (pixlMan->unknown828[0] != 0) {
    cache->beginTexSampling(2, 1);
  } else {
    cache->beginTexSampling(2, 0);
  }
  if (texture == nullptr) {
    cache->setMipMapOn(*pixlMan->getDammyTexObj());
    cache->setTexture(*pixlMan->getDammyTexObj(), location);
  } else {
    cache->setMipMapOn(*texture);
    cache->setTexture(*texture, location);
  }
}

void DrMdoSetup::varStImg_BaseColor(const MdsMatInfoHeader *header, u32 location, u32 index) { grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->unknown78->getPixlObj(0)->unknown70, location, 0, 0); }

void DrMdoSetup::varStImg_Etc(const MdsMatInfoHeader *header, u32 location, u32 index) { grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->unknown78->getPixlObj(1)->unknown70, location, 0, 0); }

void DrMdoSetup::varStImg_Normal(const MdsMatInfoHeader *header, u32 location, u32 index) { grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->unknown78->getPixlObj(2)->unknown70, location, 0, 0); }

void DrMdoSetup::varStImg_Velocity(const MdsMatInfoHeader *header, u32 location, u32 index) { grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->unknown78->getPixlObj(3)->unknown70, location, 0, 0); }

void DrMdoSetup::varStImg_ZBuff(const MdsMatInfoHeader *header, u32 location, u32 index) { grlib::CGLibCtlTexture::setUAVTexture(*m_drMan->unknown78->getPixlObj(4)->unknown70, location, 0, 0); }

} // namespace ml
