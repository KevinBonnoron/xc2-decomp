#include "dr/dr_mdo_ctl_nom.h"

#include "cloud/cloud_mdl_data_obj.h"
#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_nom_after_image.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_res_clip.h"
#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_alp_tbl.h"
#include "dr/dr_res_mdo_light.h"
#include "dr/dr_res_mdo_lod_obj.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "dr/dr_res_mdo_morp_obj.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_sort.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

// Inferred role: weight vertex render type of each render type; original name unknown.
static const u8 unknown135[] = {0, 3, 2, 4, 1, 1};

DrMdoCtlNom::~DrMdoCtlNom() {
  if ((unknownfc & unknown027_8) && unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->delShadowCacheUpdate();
  }
  releaseNom();
}

void DrMdoCtlNom::releaseNom() {
  if (unknown218 != nullptr) {
    delete unknown218;
    unknown218 = nullptr;
  }
  if (unknown220[0] != nullptr) {
    delete unknown220[0];
    unknown220[0] = nullptr;
  }
  if (unknown220[1] != nullptr) {
    delete unknown220[1];
    unknown220[1] = nullptr;
  }
  if (m_drMdoSmlShadowObj != nullptr) {
    m_drMdoSmlShadowObj->unknown28 |= DrMdoSmlShadowObj::FLAG_UNKNOWN_14 << DrMan::s_nDblStockIdx;
    m_drMdoSmlShadowObj = nullptr;
  }
  if (unknown210 != nullptr) {
    unknown210->release();
    unknown210 = nullptr;
  }
  DrResMdoLight::release(m_drResMdoLight);
  DrResMdoVtxMeshObj::release(m_drResMdoVtxMeshObj);
  DrResMdoAlpTbl::release(m_drResMdoAlpTbl);
  DrResMdoMorpObj::release(m_drResMdoMorpObj);
  DrResMdoMeshObj::release(m_drResMdoMeshObj);
  DrResMdoLodObj::release(m_drResMdoLodObj);
  DrResEtcPamObj::release(m_drResEtcPamObj);
  if (m_drResClip != nullptr) {
    m_drResClip->~DrResClip();
    m_drResClip = nullptr;
  }
  m_drResMdoSortNom->~DrResMdoSortNom();
  if (unknown1b8 != nullptr) {
    if (unknown1b8->m_drResMdoSortNomLastApha != nullptr) {
      unknown1b8->m_drResMdoSortNomLastApha->~DrResMdoSortNomLastApha();
    }
    if (unknown1b8->m_drResMdoSortNomFastApha != nullptr) {
      unknown1b8->m_drResMdoSortNomFastApha->~DrResMdoSortNomFastApha();
    }
    if (unknown1b8->m_drResMdoSortNomCldBackApha != nullptr) {
      unknown1b8->m_drResMdoSortNomCldBackApha->~DrResMdoSortNomCldBackApha();
    }
    unknown1b8 = nullptr;
  }
  releaseMat();
  if (m_drCalcStmListObj != nullptr) {
    m_drCalcStmListObj->release();
    m_drCalcStmListObj = nullptr;
  }
  if (unknown1a8 != nullptr) {
    mtl::MemManager::deallocate(unknown1a8, 0, false);
    unknown1a8 = nullptr;
  }
}

void DrMdoCtlNom::setDeleteCall(int deleteCall) {
  DrMdlBase::setDeleteCall(deleteCall);
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(false);
  }
  if (m_drResMdoLight != nullptr) {
    m_drResMdoLight->setDisp(false);
  }
}

void DrMdoCtlNom::setDisp(bool isDisp) {
  DrMdlBase::setDisp(isDisp);
  if (m_drResMdoLight != nullptr) {
    m_drResMdoLight->setDisp(isDisp);
  }
}

void DrMdoCtlNom::callShadowCacheUpdate(u64 flags) { unknown230 &= ~flags; }

void DrMdoCtlNom::occRender() {
  if (unknown168 & 2) {
    m_drMan->m_drPixlMan->m_drPixlOccQuery->occRenderAABB(m_drResClip, m_center, unknown140);
  }
  if (unknown168 & 4) {
    unknown724 *pos = unknown30->unknown160_2;
    m_drMan->m_drPixlMan->m_drPixlOccQuery->occRenderPosAABB(pos->m_drResQueryAcc, pos->unknown20, pos->unknown30, pos->unknown18);
  }
}

bool DrMdoCtlNom::cloneMdlObj(DrMdlObj *source) {
  bool isCloned = DrMdoNomClone::cloneMdlObj(static_cast<DrMdoCtlNom *>(source), this);
  if (isCloned) {
    m_disp &= ~(unknown038_5 | unknown038_6);
  }
  return isCloned;
}

// Repeats the model manager flag block of DrMdoCtlPos::update (0x7100810b80) and DrMdoCtlSeamAll::update (0x710081c6e8) (decision 2026-11-13, ruling 8): the
// game's block here has seven tests, without the one of bit 17 (tbz w9, #0x10 at 0x71008069e8 is followed by #0x12 at 0x71008069fc, nothing for #0x11), so
// no helper shared by the three functions gives the game's code, and a helper taking the set of tests would be a parameter the source has no trace of.
void DrMdoCtlNom::update() {
  stmResSetup();
  updateAlphaCall();
  updateNom();
  DrMdlMan *mdlMan = m_drMan->m_drMdlMan;
  if (unknownf8 & unknown028_15) {
    mdlMan->unknown230->unknown00 = true;
  }
  if (unknownf8 & unknown028_16) {
    mdlMan->unknown230->unknown01 = true;
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
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(true);
  }
}

void DrMdoCtlNom::updateVanishEffectParams() {
  if (getVanishEffectWrk(0, 2) == nullptr) {
    return;
  }
  for (u32 i = 0; i < getVanishEffectMax(); i++) {
    MdoWrkVanishEffect *dst = getVanishEffectWrk(i, 2);
    MdoWrkVanishEffect *src = getVanishEffectWrk(i, DrMan::s_nDblStockIdx);
    if (src->unknownd4 & 1) {
      for (int j = 0; j < 5; j++) {
        dst->unknown00[j] = src->unknown00[j];
      }
    }
    if (src->unknownd4 & (1 << 1)) {
      dst->unknown40 = src->unknown40;
    }
    if (src->unknownd4 & (1 << 2)) {
      dst->unknown50 = src->unknown50;
    }
    if (src->unknownd4 & (1 << 3)) {
      for (int j = 0; j < 5; j++) {
        dst->unknown60[j] = src->unknown60[j];
      }
    }
    if (src->unknownd4 & (1 << 4)) {
      for (int j = 0; j < 5; j++) {
        dst->unknown74[j] = src->unknown74[j];
      }
    }
    if (src->unknownd4 & (1 << 5)) {
      for (int j = 0; j < 5; j++) {
        dst->unknown88[j] = src->unknown88[j];
      }
    }
    if (src->unknownd4 & (1 << 6)) {
      dst->unknown9c = src->unknown9c;
    }
    if (src->unknownd4 & (1 << 7)) {
      dst->unknowna0 = src->unknowna0;
    }
    if (src->unknownd4 & (1 << 8)) {
      dst->unknowna4 = src->unknowna4;
    }
    if (src->unknownd4 & (1 << 9)) {
      dst->unknowna8 = src->unknowna8;
    }
    if (src->unknownd4 & (1 << 10)) {
      for (int j = 0; j < 4; j++) {
        dst->unknownac[j] = src->unknownac[j];
      }
    }
    if (src->unknownd4 & (1 << 11)) {
      for (int j = 0; j < 4; j++) {
        dst->unknownbc[j] = src->unknownbc[j];
      }
    }
    // The game tests bit 8 a second time after the last copy (0x7100807388) and reads unknowna4 again for unknownd0.
    if (src->unknownd4 & (1 << 8)) {
      dst->unknownd0 = src->unknowna4;
    }
    src->unknownd4 = 0;
  }
}

void DrMdoCtlNom::updateRimBloomParams() {
  if (getRimBloomWrk(2) != nullptr) {
    unknown091 *dst = getRimBloomWrk(2);
    unknown091 *src = getRimBloomWrk(DrMan::s_nDblStockIdx);
    if (src->unknown1c & 1) {
      dst->unknown00 = src->unknown00;
    }
    if (src->unknown1c & 2) {
      dst->unknown0c = src->unknown0c;
    }
    if (src->unknown1c & 4) {
      dst->unknown10 = src->unknown10;
    }
    if (src->unknown1c & 8) {
      dst->unknown14 = src->unknown14;
    }
    src->unknown1c = 0;
  }
}

void DrMdoCtlNom::updateShdMdl() {
  if (m_drResMdoShdObj != nullptr && m_drResMdoShdObj->update(unknown30->m_drShdMdoExtTblObj)) {
    m_disp &= ~(unknown038_5 | unknown038_6);
  }
}

void DrMdoCtlNom::callZSortLightPrePassRender() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  nomCallRender(3);
}

void DrMdoCtlNom::callZSortNomAlphaRender() {
  if ((unknownf8 & unknown028_4) != 0) {
    nomCallRender(4);
  }
  if (m_drResMdoVtxMeshObj != nullptr) {
    m_drResMdoVtxMeshObj->alpRender();
  }
}

void DrMdoCtlNom::callZSortNomSpAlphaRender() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  nomCallRender(5);
}

void DrMdoCtlNom::callZSortGBuffRender() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  nomCallRender(1);
}

void DrMdoCtlNom::callZSortNomRefractionRender() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  nomCallRender(2);
}

void DrMdoCtlNom::callLastAlphaNomRender() {
  if ((unknownf8 & unknown028_25) == 0) {
    return;
  }
  lastAlphaCallRender();
}

void DrMdoCtlNom::callFastAlphaNomRender() {
  if ((unknownf8 & unknown028_26) == 0) {
    return;
  }
  fastAlphaCallRender();
}

void DrMdoCtlNom::callCldBackAlphaNomRender() {
  if ((unknownf8 & unknown028_27) == 0) {
    return;
  }
  cldBackAlphaCallRender();
}

void DrMdoCtlNom::nomCallRender(int pass) {
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    if (pass == 0) {
      u32 lodFlags = m_drResMdoLodObj->unknown1c;
      if (m_drResMdoVtxMeshObj != nullptr) {
        lodFlags |= m_drResMdoVtxMeshObj->isRender();
      }
      createWeightVtx(0, unknown100, lodFlags, false);
      createWeightVtx(0, unknown100, lodFlags, true);
    } else {
      createWeightVtx(unknown135[pass], unknown100, m_drResMdoLodObj->unknown1c, false);
    }
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  if (pass == 0 && (unknownf8 & unknown028_21) == 0) {
    DrAPCache *cache = m_drMan->m_drAPCache;
    beginSetup();
    cache->beginMdlZRender();
    zPrePassRender();
    cache->endMdlZRender();
  }
  unknownf4 = pass;
  unknownf2 = unknown098[pass];
  beginSetup();
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[unknownf4];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::lastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown20[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::fastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown18[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::cldBackAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown28[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::callNomSetupRender() {
  if ((unknownfc & unknown027_0) && m_drResMdoMorpObj != nullptr && (m_drResMdoLodObj->unknown18 & 2)) {
    m_drResMdoMorpObj->update(unknown30, m_drResEtcPamObj);
  }
}

void DrMdoCtlNom::callZSortNomZpreePassRender() {
  if ((unknownf8 & (unknown028_20 | unknown028_21)) != (unknown028_20 | unknown028_21)) {
    return;
  }
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(6, unknown100, m_drResMdoLodObj->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  zPrePassRender();
}

void DrMdoCtlNom::callZSortThicknessRenderFirst() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(5, unknown100, m_drResMdoLodObj->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  thicknessRender(true);
}

void DrMdoCtlNom::callZSortThicknessRenderSecond() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(5, unknown100, m_drResMdoLodObj->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  thicknessRender(false);
}

void DrMdoCtlNom::callZSortNomRender() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  nomCallRender(0);
  if (m_drResMdoVtxMeshObj != nullptr) {
    m_drResMdoVtxMeshObj->stmRender(m_nodeMax != 0);
  }
  if ((unknownf8 & (unknown028_11 | unknown028_12 | unknown028_13)) != 0 && unknown1a == 0 && !m_drMan->unknown1d7a) {
    DrPixlMan *pixlMan = m_drMan->m_drPixlMan;
    if ((unknownf8 & unknown028_31) == 0 || !pixlMan->unknown7f0->m_drPixlShadowMan->clipDirShadowChk(m_center, m_length, true)) {
      pixlMan->shadowDirBegin();
      if (unknownf8 & unknown028_11) {
        pixlMan->setShadowDirRenderTarget(0);
        shadowMapDirRender(0);
      }
      if (unknownf8 & unknown028_12) {
        pixlMan->setShadowDirRenderTarget(1);
        shadowMapDirRender(1);
      }
      if (unknownf8 & unknown028_13) {
        pixlMan->setShadowDirRenderTarget(2);
        shadowMapDirRender(2);
      }
      pixlMan->shadowDirEnd();
    }
  }
}

void DrMdoCtlNom::calcMdlUniformBlock() {
  if ((unknown168 & 8) == 0) {
    if (m_nodeMax != 0) {
      calcOfsMat();
    }
    updateMdlUniformBlock();
    unknown168 |= 8;
  }
}

void DrMdoCtlNom::shadowMapDirRender(int index) {
  m_drMan->m_drPixlMan->setupShadowUnifrom(index);
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[6];
    if (list != nullptr) {
      const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
      s16 nodeMax = m_nodeMax;
      for (;;) {
        const MdsMdlInfoHeader *info = &infos[list->unknown00];
        DrResMdoMeshParts *parts;
        bool isParts = false;
        if ((info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_8) != 0) {
          parts = m_drResMdoMeshObj->getParts(info->unknown16);
          isParts = (parts->unknown28 & DrResMdoMeshParts::FLAG_UNKNOWN_0) != 0;
        }
        if (!isParts) {
          partsShadowDirRender(info, 0, info->unknown1c + (nodeMax != 0));
        } else {
          partsShadowDirRender(info, parts->unknown38, 0);
        }
        u32 next = list->unknown02;
        if (next == 0) {
          break;
        }
        list = &unknown198[next - 1];
      }
    }
  }
}

void DrMdoCtlNom::shadowCacheOnlyRender() {
  if ((unknownf8 & unknown028_28) == 0 || (unknownf8 & (unknown028_11 | unknown028_12 | unknown028_13)) == 0) {
    return;
  }
  DrPixlMan *pixlMan = m_drMan->m_drPixlMan;
  if ((unknownf8 & unknown028_31) != 0 && !pixlMan->unknown7f0->m_drPixlShadowMan->clipDirShadowChk(m_center, m_length, true)) {
    return;
  }
  if (unknown1a != 0 || m_drMan->unknown1d7a) {
    return;
  }
  calcMdlUniformBlock();
  updateFlagWaveTbl();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(0, unknown100, m_drResMdoLodObj->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  pixlMan->shadowDirBegin();
  if (unknownf8 & unknown028_11) {
    pixlMan->setShadowDirRenderTarget(0);
    shadowMapDirRender(0);
  }
  if (unknownf8 & unknown028_12) {
    pixlMan->setShadowDirRenderTarget(1);
    shadowMapDirRender(1);
  }
  if (unknownf8 & unknown028_13) {
    pixlMan->setShadowDirRenderTarget(2);
    shadowMapDirRender(2);
  }
  pixlMan->shadowDirEnd();
}

void DrMdoCtlNom::shadowRender() {
  if ((unknown168 & 0x20) == 0 || (unknownfc & unknown027_0) == 0) {
    return;
  }
  DrPixlShadowObj *shadow = m_drMan->m_drPixlMan->m_drPixlShadowObj;
  if ((unknown168 & 0x40) == 0 && shadow->unknown4c == 1) {
    return;
  }
  bool isShadow;
  if ((unknownfc & unknown027_8) == 0) {
    isShadow = shadow->m_drLightObj->isCharShadow();
  } else {
    isShadow = shadow->m_drLightObj->isBaseMapShadow();
  }
  if (!isShadow || shadow->clipTypeChk(m_center, m_length) == 0) {
    return;
  }
  calcMdlUniformBlock();
  updateFlagWaveTbl();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(0, unknown100, m_drResMdoLodObj->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  shadow->renderSetup();
  unknownf4 = 6;
  unknownf2 = 0;
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  if (shadow->unknown4c == 1) {
    unknown178 |= 4;
  }
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[unknownf4];
    if (list != nullptr) {
      shwRender(top, list);
    }
  }
}

void DrMdoCtlNom::dispOffUpdate() {
  unknownf8 = 0;
  unknown168 = 0;
  unknownec = 0;
  m_gpuRender = false;
  unknown16b = 0;
  unknowne4 = 0.0f;
  stmResSetup();
  oneTextureStream();
  if (m_drResEtcPamObj != nullptr) {
    m_drResEtcPamObj->update();
  }
  if (m_drResMdoLight != nullptr) {
    m_drResMdoLight->update(unknown60[DrMan::s_nDblMemIdx], m_matrix, m_drResEtcPamObj, 0.0f);
  }
  updateVanishEffectParams();
  updateRimBloomParams();
  if (m_drResEtcPamObj != nullptr) {
    m_drResEtcPamObj->callback(m_drResMdoMeshObj, unknown30->m_mdoWrkVanishEffect);
  }
  if (m_drResMdoMeshObj != nullptr) {
    m_drResMdoMeshObj->updateDisplayCheck(false);
  }
  if (m_drMdoSmlShadowObj != nullptr) {
    m_drMdoSmlShadowObj->unknown28 &= 0xfffe;
  }
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(false);
  }
  m_drResClip->unknown08 = (m_drResClip->unknown08 & 0xffffff81) | 0xe;
  unknownfc &= ~(unknown027_22 | unknown027_23 | unknown027_26);
  updateAfterImage();
}

void DrMdoCtlNom::updateAfterImage() {
  if (unknown218 != nullptr && unknown218->isReleaseCall()) {
    delete unknown218;
    unknown218 = nullptr;
  }
  if (unknown220[DrMan::s_nDblMemIdx] != nullptr) {
    if (unknown218 != nullptr) {
      delete unknown218;
      unknown218 = nullptr;
    }
    unknown218 = unknown220[DrMan::s_nDblMemIdx];
    unknown220[DrMan::s_nDblMemIdx] = nullptr;
  }
  if (unknown218 != nullptr) {
    unknown218->update(this, m_frameSpd * m_drMan->unknown1c8c);
  }
}

void DrMdoCtlNom::createAfterImage(f32 count, f32 span, f32 fade, const mm::Col3 &headColor, f32 headAlpha, f32 headEmissive, f32 headScale, const mm::Col3 &tailColor, f32 tailAlpha, f32 tailEmissive,
                                   f32 tailScale) {
  if (unknown218 != nullptr) {
    unknown218->releaseCall();
  }
  DrMdoNomAfterImage *image = new (DrMan::getIns()->unknown0c) DrMdoNomAfterImage();
  image->create(this, count, span, fade, headColor, headAlpha, headEmissive, headScale, tailColor, tailAlpha, tailEmissive, tailScale);
  unknown220[DrMan::s_nDblStockIdx] = image;
}

void DrMdoCtlNom::releaseAfterImage() {
  if (unknown218 != nullptr) {
    unknown218->releaseCall();
  }
  if (unknown220[DrMan::s_nDblMemIdx] != nullptr) {
    unknown220[DrMan::s_nDblMemIdx]->releaseCall();
  }
  if (unknown220[DrMan::s_nDblStockIdx] != nullptr) {
    delete unknown220[DrMan::s_nDblStockIdx];
    unknown220[DrMan::s_nDblStockIdx] = nullptr;
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Inferred role: tells whether a mdl info of the thickness pass is not hidden by its vanish effect.
// Its user, thicknessRender (0x710080eb90), has the game's code only with this helper. Written in the loop, GVN moves the reload of unknown30 that ends the outer loop onto the exit edge of the inner
// loop (load PRE), one instruction after the game's, which reloads in the join of both edges. GVN refuses that move when the first predecessor of the block that reads the next list entry is not a
// call; with the helper the inliner and SimplifyCFG create the edge of the not-thickness skip after the edges of the two calls, which makes it the first one. Tried without the helper: the test as one
// condition, nested ifs, an empty else, `!(a || b)`, the locals of the calls declared outside the if, `continue` in a for or do-while loop (adds a null check of the next entry), an `int` flag (ldr
// and ubfx instead of ldrb and lsr), and the vanish effect alone in the helper.
static bool isThicknessVisible(DrMdoCtlNom *mdl, bool isThickness, u32 vanishIndex) {
  return isThickness && !(mdl->getVanishEffectMax() > vanishIndex && mdl->getVanishEffectWrk(vanishIndex, 2)->unknowna4 > 0.43f);
}

void DrMdoCtlNom::thicknessRender(bool isFirst) {
  unknown17a = -1;
  unknownf2 = 0;
  int hasNode = m_nodeMax != 0;
  const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[7];
    if (list != nullptr) {
      const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
      for (;;) {
        const MdsMdlInfoHeader *info = &infos[list->unknown00];
        bool isThickness = false;
        if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_14) {
          isThickness = (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) != 0;
        }
        u32 vanishIndex = 0;
        if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_8) {
          vanishIndex = m_drResMdoMeshObj->getParts(info->unknown16)->m_extVolumeFadeEffect;
        }
        if (isThicknessVisible(this, isThickness, vanishIndex)) {
          DrResMdoMeshParts *parts = nullptr;
          bool isParts = false;
          if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_8) {
            parts = m_drResMdoMeshObj->getParts(info->unknown16);
            isParts = (parts->unknown28 & DrResMdoMeshParts::FLAG_UNKNOWN_0) != 0;
          }
          if (!isParts) {
            partsThicknessRender(info, 0, hasNode, m_drResMdoAlpTbl, info->unknown20, isFirst);
          } else {
            partsThicknessRender(info, parts->unknown38, 0, m_drResMdoAlpTbl, info->unknown20, isFirst);
          }
        }
        u32 next = list->unknown02;
        if (next == 0) {
          break;
        }
        list = &unknown198[next - 1];
      }
    }
  }
}

} // namespace ml
