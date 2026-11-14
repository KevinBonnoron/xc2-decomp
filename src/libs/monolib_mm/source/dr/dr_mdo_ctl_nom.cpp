#include "dr/dr_mdo_ctl_nom.h"

#include "cloud/cloud_mdl_data_obj.h"
#include "dr/dr_ap_cache.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_nom_after_image.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_res_clip.h"
#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_light.h"
#include "dr/dr_res_mdo_lod_obj.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "dr/dr_res_mdo_morp_obj.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_col3.h"
#include "mtl/alloc_handle.h"

namespace ml {

// Inferred role: weight vertex render type of each render type; original name unknown.
static const u8 unknown135[] = {0, 3, 2, 4, 1, 1};

DrMdoCtlNom::~DrMdoCtlNom() {
  if ((unknownfc & unknown027_8) && unknown1a == 0) {
    m_drMan->unknown78->unknown800->delShadowCacheUpdate();
  }
  releaseNom();
}

void DrMdoCtlNom::setDeleteCall(int deleteCall) {
  DrMdlBase::setDeleteCall(deleteCall);
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(false);
  }
  if (unknown1e0 != nullptr) {
    unknown1e0->setDisp(false);
  }
}

void DrMdoCtlNom::setDisp(bool isDisp) {
  DrMdlBase::setDisp(isDisp);
  if (unknown1e0 != nullptr) {
    unknown1e0->setDisp(isDisp);
  }
}

void DrMdoCtlNom::callShadowCacheUpdate(u64 flags) { unknown230 &= ~flags; }

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
  if (unknown1d0 != nullptr && unknown1d0->update(unknown30->unknown88)) {
    unknown20 &= ~0x60;
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
  if (unknown1d8 != nullptr) {
    unknown1d8->alpRender();
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
      u32 lodFlags = unknown1f0->unknown1c;
      if (unknown1d8 != nullptr) {
        lodFlags |= unknown1d8->isRender();
      }
      createWeightVtx(0, unknown100, lodFlags, false);
      createWeightVtx(0, unknown100, lodFlags, true);
    } else {
      createWeightVtx(unknown135[pass], unknown100, unknown1f0->unknown1c, false);
    }
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  if (pass == 0 && (unknownf8 & unknown028_21) == 0) {
    DrAPCache *cache = m_drMan->unknown5c0;
    beginSetup();
    cache->beginMdlZRender();
    zPrePassRender();
    cache->endMdlZRender();
  }
  unknownf4 = pass;
  unknownf2 = unknown098[pass];
  beginSetup();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = unknown190[i];
    DrResChkList *list = lists[unknownf4];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::lastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown20[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::fastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown18[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::cldBackAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown28[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::callNomSetupRender() {
  if ((unknownfc & unknown027_0) && unknown1c8 != nullptr && (unknown1f0->unknown18 & 2)) {
    unknown1c8->update(unknown30, unknown200);
  }
}

void DrMdoCtlNom::callZSortNomZpreePassRender() {
  if ((unknownf8 & (unknown028_20 | unknown028_21)) != (unknown028_20 | unknown028_21)) {
    return;
  }
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(6, unknown100, unknown1f0->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  zPrePassRender();
}

void DrMdoCtlNom::callZSortThicknessRenderFirst() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(5, unknown100, unknown1f0->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  thicknessRender(true);
}

void DrMdoCtlNom::callZSortThicknessRenderSecond() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(5, unknown100, unknown1f0->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  thicknessRender(false);
}

void DrMdoCtlNom::callZSortNomRender() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  nomCallRender(0);
  if (unknown1d8 != nullptr) {
    unknown1d8->stmRender(m_nodeMax != 0);
  }
  if ((unknownf8 & (unknown028_11 | unknown028_12 | unknown028_13)) != 0 && unknown1a == 0 && !m_drMan->unknown1d7a) {
    DrPixlMan *pixlMan = m_drMan->unknown78;
    if ((unknownf8 & unknown028_31) == 0 || !pixlMan->unknown7f0->unknown178->clipDirShadowChk(unknown130, unknown160, true)) {
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
  m_drMan->unknown78->setupShadowUnifrom(index);
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown190[i][6];
    if (list != nullptr) {
      const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
      s16 nodeMax = m_nodeMax;
      for (;;) {
        const MdsMdlInfoHeader *info = &infos[list->unknown00];
        DrResMdoMeshParts *parts;
        bool isParts = false;
        if ((info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_8) != 0) {
          parts = unknown1e8->getParts(info->unknown16);
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
  DrPixlMan *pixlMan = m_drMan->unknown78;
  if ((unknownf8 & unknown028_31) != 0 && !pixlMan->unknown7f0->unknown178->clipDirShadowChk(unknown130, unknown160, true)) {
    return;
  }
  if (unknown1a != 0 || m_drMan->unknown1d7a) {
    return;
  }
  calcMdlUniformBlock();
  updateFlagWaveTbl();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(0, unknown100, unknown1f0->unknown1c, false);
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
  DrPixlShadowObj *shadow = m_drMan->unknown78->unknown848;
  if ((unknown168 & 0x40) == 0 && shadow->unknown4c == 1) {
    return;
  }
  bool isShadow;
  if ((unknownfc & unknown027_8) == 0) {
    isShadow = shadow->unknown198->isCharShadow();
  } else {
    isShadow = shadow->unknown198->isBaseMapShadow();
  }
  if (!isShadow || shadow->clipTypeChk(unknown130, unknown160) == 0) {
    return;
  }
  calcMdlUniformBlock();
  updateFlagWaveTbl();
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    createWeightVtx(0, unknown100, unknown1f0->unknown1c, false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  shadow->renderSetup();
  unknownf4 = 6;
  unknownf2 = 0;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  if (shadow->unknown4c == 1) {
    unknown178 |= 4;
  }
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = unknown190[i];
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
  if (unknown200 != nullptr) {
    unknown200->update();
  }
  if (unknown1e0 != nullptr) {
    unknown1e0->update(unknown60[DrMan::s_nDblMemIdx], m_matrix, unknown200, 0.0f);
  }
  updateVanishEffectParams();
  updateRimBloomParams();
  if (unknown200 != nullptr) {
    unknown200->callback(unknown1e8, unknown30->unknown150);
  }
  if (unknown1e8 != nullptr) {
    unknown1e8->updateDisplayCheck(false);
  }
  if (unknown58 != nullptr) {
    unknown58->unknown28 &= 0xfffe;
  }
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(false);
  }
  unknown1f8->unknown08 = (unknown1f8->unknown08 & 0xffffff81) | 0xe;
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
    unknown218->update(this, unknowndc * m_drMan->unknown1c8c);
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

} // namespace ml
