#include "dr/dr_mdo_ctl_seam_all.h"

#include "cloud/cloud_man.h"
#include "cloud/cloud_mdl_data_obj.h"
#include "cloud/cloud_obj_man.h"
#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_env_map.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_mdo_zsort.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_res_mdo_seam_read.h"
#include "dr/dr_res_mdo_sort.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ml {

DrMdoCtlSeamAll::DrMdoCtlSeamAll(const void *data, const char *path, DrMan *man, int viewNum) : DrMdoCtlSeamRead(viewNum) {
  m_drMan = man;
  setupSeamMapHead(data, path);
}

DrMdoCtlSeamAll::~DrMdoCtlSeamAll() { releaseSeamAll(); }

void DrMdoCtlSeamAll::releaseSeamAll() {
  if (unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->delShadowCacheUpdate();
  }
  releaseBaseMap();
  releaseLowMap();
  releaseInstMap();
  releaseMpfMap();
  releaseEnvMap();
  releaseLight();
  releaseSeam();
}

void DrMdoCtlSeamAll::resourceInit() {
  unknownc7c |= 0x2000;
  if (unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->addShadowCacheUpdate(false);
  }
  m_drMan->m_drMdlMan->addMpfObj();
  const u8 *data = reinterpret_cast<const u8 *>(unknown1a8);
  if (unknown1a8->unknown84 != 0) {
    DrLightMan *lightMan = DrMan::getIns()->unknownc0[unknown1a];
    lightMan->releaseAllAmbLight();
    lightMan->releaseAllDirLight();
    DrMan::getIns()->unknowne0[unknown1a]->releaseAll();
    const void *envData = data + unknown1a8->unknown84;
    m_drEnvironmentObj = m_drMan->unknown100[unknown1a]->createObj(envData);
  }
  if (unknown1a8->unknowna8 != 0) {
    m_drCalcClipObj = m_drMan->unknowna0[unknown1a]->m_drCalcClipMan->createClipObj(data + unknown1a8->unknowna8);
  }
  if (unknown1a8->unknowne8 != 0) {
    const void *cloudData = reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknowne8;
    unknownb30 = cloud::CloudMan::get()->unknown50->createMdlData(cloudData);
  }
  DrGlobalIBLMan *globalIBLMan = m_drMan->unknown160[unknown1a];
  for (int i = 0; i < (unknown6d8 != nullptr ? unknown6d8->unknown00 : 0); i++) {
    u32 offset = unknown6d8->unknown04 + i * sizeof(unknown096);
    const unknown096 *ibl = reinterpret_cast<const unknown096 *>(reinterpret_cast<const u8 *>(unknown6d8) + offset);
    if (ibl->unknown0c != 0) {
      const void *iblData = nullptr;
      if (ibl->unknown08 != 0) {
        iblData = reinterpret_cast<const u8 *>(unknown6d8) + ibl->unknown08;
      }
      unknown420.push_back(globalIBLMan->createObj(iblData));
    }
  }
}

void DrMdoCtlSeamAll::callShadowCacheUpdate(u64 flags) {
  callShadowCacheBaseUpdate(flags);
  callShadowCacheInstUpdate(flags);
}

void DrMdoCtlSeamAll::update() {
  updateAlphaCall();
  if (!calcBegin()) {
    return;
  }
  calcFastUpdate();
  if (callDeleteUpdate()) {
    MdoArgSeamUpdate arg;
    arg.m_drCalcViewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
    arg.unknown48 = m_drMan->m_drMdlMan->m_drMdoVertexMan->unknown10;
    arg.unknown08 = unknownbd0;
    arg.m_drResMdoSeamVertex = unknown220.unknown20;
    arg.unknown18 = unknownbe0;
    arg.m_drResMdoSeamTexture = unknown1b0.unknown20;
    arg.unknown28 = unknownbf0;
    arg.m_drResMdoSeamTexList = unknown1e8.unknown20;
    arg.m_mdsSeamOfsTexTblData = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
    arg.unknown40 = unknownc7c;
    arg.m_drResMdoInstAnmObj = &m_drResMdoInstAnmObj;
    arg.m_drCalcClipMan = m_drCalcClipMan;
    updateReadList();
    updateTexutreSeam();
    updateVertexSeam();
    updateEnvMap();
    updateBaseMap();
    updateInstMap(arg);
    updateMpfMap();
    updateLowMap();
    updateLight();
    if (unknownc7c & 1) {
      unknownf8 |= unknown028_20;
    }
    updateReadCall();
    unknown14d0 = m_matrix;
    unknown14d0.unknown002(unknown14d0, m_drMan->m_drCalcMan->m_drCalcViewWork->unknown200);
    unknown1510 = m_matrix;
    unknown1510.unknown002(unknown1510, m_drMan->m_drCalcMan->m_drCalcViewWork->unknown40);
    m_drMan->m_drMdlMan->unknown230->unknown0c = true;
  } else {
    updateTexutreSeam();
    updateVertexSeam();
  }
  if (((unknownc7c >> 12) & 1) == 0) {
    unknownf8 |= unknown028_0;
    DrMdlMan *mdlMan = m_drMan->m_drMdlMan;
    mdlMan->unknown218->setViewSeamLast(m_drResMdoSortSeamEnvMap);
    mdlMan->unknown218->setViewLast(m_drResMdoSortSeamAll);
    if (unknownf8 & unknown028_15) {
      mdlMan->unknown230->unknown00 = true;
    }
    if (unknownf8 & unknown028_16) {
      mdlMan->unknown230->unknown01 = true;
    }
    if (unknownf8 & unknown028_17) {
      mdlMan->unknown230->unknown02 = true;
    }
    if (unknownf8 & unknown028_18) {
      mdlMan->unknown230->unknown07 = true;
    }
    if (unknownf8 & unknown028_3) {
      mdlMan->unknown230->unknown03 = true;
    }
    if (unknownf8 & unknown028_2) {
      mdlMan->unknown230->unknown04 = true;
    }
    if (unknownf8 & unknown028_8) {
      mdlMan->unknown230->unknown08 = true;
    }
    if (unknownf8 & unknown028_9) {
      mdlMan->unknown230->unknown09 = true;
    }
  }
  calcEnd();
}

bool DrMdoCtlSeamAll::callDeleteUpdate() {
  if (((unknownc7c >> 28) & 1) == 0) {
    return true;
  }
  if ((unknownc7c >> 29) & 1) {
    resourceRelease();
    if ((unknownc7c >> 13) & 1) {
      releaseBaseMap();
      releaseLowMap();
      releaseInstMap();
      releaseMpfMap();
      releaseEnvMap();
      releaseLight();
      unknownc7c &= ~0x2000;
    }
  }
  if (unknownb30 != nullptr) {
    unknownb30->setCallDisp(false);
  }
  return false;
}

u32 DrMdoCtlSeamAll::getSeamBaseMdlMax() const { return unknown1a8->m_seamBaseMdlMax; }

u32 DrMdoCtlSeamAll::getSeamInstMdlMax() const { return unknown1a8->m_seamInstMdlMax; }

u32 DrMdoCtlSeamAll::getSeamMpfMdlMax() const { return unknown1a8->m_seamMpfMdlMax; }

u32 DrMdoCtlSeamAll::getSeamTextureMax() const { return unknown1a8->m_seamTextureMax; }

u32 DrMdoCtlSeamAll::getSeamVertexMax() const { return unknown1a8->m_seamVertexMax; }

u32 DrMdoCtlSeamAll::getSeamEtcPosDataMax() const { return unknown1a8->m_seamEtcPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamMpfPosDataMax() const { return unknown1a8->m_seamMpfPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamColiMax() const { return unknown1a8->m_seamColiMax; }

u32 DrMdoCtlSeamAll::getSeamShaderMax() const { return unknown1a8->m_seamShaderMax; }

bool DrMdoCtlSeamAll::isReadSafe() const { return (unknownc7c >> 11) & 1; }

bool DrMdoCtlSeamAll::isRenderSafe() const { return (unknownc7c >> 15) & 1; }

void DrMdoCtlSeamAll::setSelectIdDisp(int id, bool isOff) {
  if (isOff) {
    m_drMan->offGblIdx(id);
    return;
  }
  m_drMan->setGblIdx(id);
}

void DrMdoCtlSeamAll::setMdlReadOff(bool isOff) {
  u32 flags = unknownc7c & ~0x200u;
  if (isOff) {
    flags = unknownc7c | 0x200;
  }
  unknownc7c = flags;
}

void DrMdoCtlSeamAll::debugRender() {}

void DrMdoCtlSeamAll::setClearResource(bool isClear) {}

void DrMdoCtlSeamAll::dispOffUpdate() {
  updateAlphaCall();
  if (calcBegin()) {
    callDeleteUpdate();
  }
  calcEnd();
}

void DrMdoCtlSeamAll::noOffScreenUpdate() {
  unknownc16++;
  if (!m_drResMdoSeamRead.isRead()) {
    m_drResMdoSeamRead.release();
    if (unknownc16 > 3) {
      m_disp |= unknown038_3 | unknown038_3 << 1;
    }
  }
  if (((unknownc7c >> 12) & 1) == 0) {
    unknownc7c |= 0x1000;
    if (unknown1a == 0) {
      m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->delShadowCacheUpdate();
    }
  }
}

void DrMdoCtlSeamAll::setDeleteCall(int deleteCall) {
  unknownc7c |= 0x40000000 << deleteCall;
  m_drResMdoSeamRead.readCancel();
  resourceRelease();
}

void DrMdoCtlSeamAll::callZPrePassSeamAll() {
  if ((unknownf8 & unknown028_20) == 0 || m_drMan->unknown1d61) {
    return;
  }
  seamZPrePassBegin();
  createBaseZPrePassDisplayList();
  createInstZPrePassDisplayList();
  createMpfZPrePassDisplayList();
  createLowZPrePassDisplayList();
  seamZPrePassEnd();
}

void DrMdoCtlSeamAll::callThicknessFirstSeamAll() { callThicknessPassSeamAll(true); }

void DrMdoCtlSeamAll::callThicknessSecondSeamAll() { callThicknessPassSeamAll(false); }

void DrMdoCtlSeamAll::callRenderSeamAll() {
  if ((unknownf8 & unknown028_0) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  unknown001();
  callRenderSeamInstMap();
  callRenderSeamBaseMap();
  callRenderSeamMpfMap();
  callRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callGBuffRenderSeamAll() {
  if ((unknownf8 & unknown028_1) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  unknown001();
  callGBuffRenderSeamInstMap();
  callGBuffRenderSeamBaseMap();
  callGBuffRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamAll() {
  if ((unknownf8 & unknown028_3) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  unknown001();
  callLightPrePassRenderSeamBaseMap();
  callLightPrePassRenderSeamInstMap();
  callLightPrePassRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callAlphaRenderSeamAll() {
  if ((unknownf8 & unknown028_4) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  unknown001();
  callAlphaRenderSeamLowMap();
  callAlphaRenderSeamBaseMap();
  callAlphaRenderSeamInstMap();
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamAll() {
  if ((unknownf8 & unknown028_5) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  unknown001();
  callSpAlphaRenderSeamLowMap();
  callSpAlphaRenderSeamBaseMap();
  callSpAlphaRenderSeamInstMap();
}

void DrMdoCtlSeamAll::callRefractionRenderSeamAll() {
  if ((unknownf8 & unknown028_2) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  unknown001();
  callRefractionRenderSeamInstMap();
  callRefractionRenderSeamBaseMap();
  callRefractionRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callThicknessPassSeamAll(bool isFirst) {
  if ((unknownf8 & unknown028_6) == 0 || m_drMan->unknown1d61) {
    return;
  }
  seamThicknessPassBegin(isFirst);
  createBaseThicknesPassDisplayList(isFirst);
  createInstThicknessPassDisplayList(isFirst);
  seamThicknessPassEnd(isFirst);
}

void DrMdoCtlSeamAll::callRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_0) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  unknown001();
  DrMdoCtlSeamEnvMap::callRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callGBuffRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_1) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  unknown001();
  DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_3) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  unknown001();
  DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callAlphaRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_4) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  unknown001();
  DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_5) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  unknown001();
  DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callRefractionRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_2) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  unknown001();
  DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::shadowRender() {
  if (((unknownc7c >> 28) & 1) != 0) {
    return;
  }
  unknownf4 = 6;
  unknownf2 = 0;
  unknown001();
  DrPixlShadowObj *shadow = m_drMan->m_drPixlMan->m_drPixlShadowObj;
  if (shadow->m_drLightObj->isInstMapShadow()) {
    callShadowMapRenderSeamInstMap(shadow);
  }
  if (shadow->m_drLightObj->isBaseMapShadow()) {
    callShadowMapRenderSeamBaseMap(shadow);
  }
}

bool DrMdoCtlSeamAll::shadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknownc90 & cache.unknown8e8) != 0 && (unknownc98 & cache.unknown8e8) != 0) {
    return true;
  }
  if (((unknownc7c >> 28) & 1) != 0) {
    return true;
  }
  unknownf4 = 6;
  unknownf2 = 0;
  unknown001();
  mm::Mat44 matrix;
  matrix.unknown009(m_matrix, cache.unknown850);
  grlib::CGLibEtcUniformBlock uniform;
  grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), matrix);
  uniform.updateData(sizeof(mm::Mat44));
  unknown170 = &uniform;
  if (cache.unknown808 & 0x10) {
    unknown168 |= 0x80;
  }
  callBaseShadowCacheRender(cache);
  callInstShadowCacheRender(cache);
  unknown168 &= ~0x80;
  return true;
}

void DrMdoCtlSeamAll::shadowCacheAddRender(int index) {
  if ((m_disp & unknown038_0) == 0 || ((unknownc7c >> 28) & 1) != 0) {
    return;
  }
  m_drMan->m_drPixlMan->setupShadowUnifrom(index);
  callInstShadowCacheAddRender(index);
}

void DrMdoCtlSeamAll::occRender() {
  if ((m_disp & unknown038_0) == 0 || ((unknownc7c >> 28) & 1) != 0) {
    return;
  }
  occInstRender();
}

} // namespace ml
