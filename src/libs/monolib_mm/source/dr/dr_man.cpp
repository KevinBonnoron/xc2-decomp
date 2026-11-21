#include "dr/dr_man.h"

#include <string.h>

#include "cloud/cloud_man.h"
#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_gpu_cost.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_draw_callback.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_gpu_check_obj.h"
#include "dr/dr_gpu_check_render.h"
#include "dr/dr_ibl_man.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_irr_vol_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_mdo_ctl_cld_mdl.h"
#include "dr/dr_mdo_ctl_dammy.h"
#include "dr/dr_mdo_ctl_mpf.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_ctl_pos.h"
#include "dr/dr_mdo_ctl_seam_all.h"
#include "dr/dr_mdo_grp_obj.h"
#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mdo_sampler_man.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_mdo_tex_simple_man.h"
#include "dr/dr_mdo_texture_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_mdo_zsort.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_res_chank_list.h"
#include "dr/dr_res_etc_uniform_obj.h"
#include "dr/dr_res_filter_data.h"
#include "dr/dr_res_occ_uniform_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_stm_read_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_debug.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_state.h"
#include "ml/critical_section.h"
#include "ml/work_cpu.h"
#include "mtl/mem_manager.h"

// The game builds DrIniSys in this unit, before this file (0x71007c4958 to 0x71007c8450): DrMan::setSRGBMode (0x71007c750c) sits inside its block.
#include "dr_ini_sys.cpp"

namespace ml {
class DrPixlShadowCacheObj;
class DrGpuCheckBase;

DrMan *DrMan::getIns() { return s_pTop; }

DrMan *DrMan::get() { return s_pTop; }

DrMan::~DrMan() {
  WorkCpu::removeBackgroundListener(this);
  unknown78->pixelEndMode();
  if (unknown1d18 != nullptr) {
    mtl::MemManager::deallocate(unknown1d18, 0, false);
    unknown1d18 = nullptr;
  }
  if (m_gblIdx != nullptr) {
    mtl::MemManager::deallocate(m_gblIdx, 0, false);
    m_gblIdx = nullptr;
  }
  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }
  if (unknown1e00 != nullptr) {
    delete unknown1e00;
    unknown1e00 = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    if (unknown100[i] != nullptr) {
      delete unknown100[i];
      unknown100[i] = nullptr;
    }
    if (unknown140[i] != nullptr) {
      delete unknown140[i];
      unknown140[i] = nullptr;
    }
    if (unknown160[i] != nullptr) {
      delete unknown160[i];
      unknown160[i] = nullptr;
    }
    if (unknownc0[i] != nullptr) {
      delete unknownc0[i];
      unknownc0[i] = nullptr;
    }
    if (unknowne0[i] != nullptr) {
      delete unknowne0[i];
      unknowne0[i] = nullptr;
    }
  }
  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }
  if (unknown90 != nullptr) {
    delete unknown90;
    unknown90 = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    if (unknown120[i] != nullptr) {
      delete unknown120[i];
      unknown120[i] = nullptr;
    }
  }
  if (unknown180 != nullptr) {
    delete unknown180;
    unknown180 = nullptr;
  }
  if (unknown188 != nullptr) {
    delete unknown188;
    unknown188 = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    if (unknowna0[i] != nullptr) {
      delete unknowna0[i];
      unknowna0[i] = nullptr;
    }
  }
  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }
  if (unknown98 != nullptr) {
    delete unknown98;
    unknown98 = nullptr;
  }
  if (unknown5b0 != nullptr) {
    delete unknown5b0;
    unknown5b0 = nullptr;
  }
  if (unknown5c8 != nullptr) {
    delete unknown5c8;
    unknown5c8 = nullptr;
  }
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  if (unknown5d0 != nullptr) {
    delete unknown5d0;
    unknown5d0 = nullptr;
  }
  if (unknown5c0 != nullptr) {
    delete unknown5c0;
    unknown5c0 = nullptr;
  }
  if (unknown0c.isValid()) {
    mtl::MemManager::erase(unknown0c);
    unknown0c = mtl::ALLOC_HANDLE();
  }
  if (unknown10.isValid()) {
    mtl::MemManager::erase(unknown10);
    unknown10 = mtl::ALLOC_HANDLE();
  }
  if (unknown14.isValid()) {
    mtl::MemManager::erase(unknown14);
    unknown14 = mtl::ALLOC_HANDLE();
  }
  if (unknown18.isValid()) {
    mtl::MemManager::erase(unknown18);
    unknown18 = mtl::ALLOC_HANDLE();
  }
  if (unknown1c.isValid()) {
    mtl::MemManager::erase(unknown1c);
    unknown1c = mtl::ALLOC_HANDLE();
  }
  if (unknown20.isValid()) {
    mtl::MemManager::erase(unknown20);
    unknown20 = mtl::ALLOC_HANDLE();
  }
  if (unknown08.isValid()) {
    mtl::MemManager::erase(unknown08);
    unknown08 = mtl::ALLOC_HANDLE();
  }
  s_pTop = nullptr;
  grlib::CGLibState::setPixelResidentArea(false, 0);
}

CriticalSection &DrMan::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

int DrMan::loopCnt() { return 1; }

void DrMan::apply(int loop) {
  applyBegin(loop);
  // The view test is written in place, as in render: through unknown059 a for loop indexes unknown440 with the widened counter (add x8, x19, x20, lsl #6), where the game sign extends the
  // 32-bit counter (lsl x8, x20, #32; add x8, x19, x8, asr #26 at 1.0.0: 0x71007cb384).
  for (int view = 0; view < 4; view++) {
    if ((unknown440[view].unknown38 & 1) == 0) {
      unknown88->applyDispOff(view);
    } else {
      applyView(view);
    }
  }
  unknown580 = unknowna0[0];
  unknown588 = unknownc0[0];
  unknown590 = unknowne0[0];
  unknown598 = unknown100[0];
  unknown5a0 = unknown140[0];
  unknown5a8 = unknown160[0];
  unknown78->setupCate(0);
  unknown88->setupCate(0);
  unknown80->setupCate(0);
  unknown88->endApply();
  unknown78->lastUpdate();
  unknown5b0->entryJob();
}

void DrMan::applyBegin(int loop) {
  unknown1c8c = unknown1c84 * unknown1c88;
  unknown88->beginApply();
}

void DrMan::applyEnd(int loop) {}

void DrMan::setSRGBMode(bool isSRGBMode) { s_bSRGBMode = isSRGBMode; }

void DrMan::createAddRenderSystem(DR_VIEW_PARAM *param) {
  CS lock(getCriticalSection());
  s32 index = s_nDblStockIdx;
  memcpy(&unknown190[index][unknown350[index]], param, sizeof(DR_VIEW_PARAM));
  unknown350[index]++;
}

void DrMan::deleteAddRenderSystem(u32 id) {
  CS lock(getCriticalSection());
  s32 index = s_nDblStockIdx;
  unknown358[index][unknown378[index]] = id;
  unknown378[index]++;
}

void DrMan::startCapture(DR_CAPTURE_PARAM *param) {
  CS lock(getCriticalSection());
  s32 index = s_nDblStockIdx;
  unknown380[index] = *param;
  unknown3b0 |= 1 << index;
}

void DrMan::captureRender(bool isDouble) {
  u32 flags = unknown3b0;
  u32 mask = 1 << s_nDblIdx;
  if ((mask & flags) && isDouble == unknown380[s_nDblIdx].unknown10) {
    unknown3b0 = flags & ~mask;
    unknown78->captureMainFrameBuffer(unknown380[s_nDblIdx].unknown00, unknown380[s_nDblIdx].unknown08, unknown380[s_nDblIdx].unknown0c);
  }
}

void DrMan::setModelTexture(DR_MODEL_TEXTURE *texture, u32 index) {
  CS lock(getCriticalSection());
  s32 stockIndex = s_nDblStockIdx;
  unknown3b8[stockIndex][index] = *texture;
  unknown438[stockIndex] |= 1 << index;
}

void DrMan::resetModelTexture(u32 index) {
  CS lock(getCriticalSection());
  s32 stockIndex = s_nDblStockIdx;
  unknown3b8[stockIndex][index].unknown00 = nullptr;
  unknown3b8[stockIndex][index].unknown08 = false;
  unknown438[stockIndex] |= 1 << index;
}

void DrMan::renderView(int view) {
  unknown1c98 = view;
  unknown5b8 = &unknown440[view];
  unknown660[view].unknown560 = view;
  s32 index = view;
  if (unknown440[view].unknown38 & 2) {
    index = 0;
  }
  unknown98->unknown100 = index;
  unknown580 = unknowna0[view];
  unknown588 = unknownc0[view];
  unknown590 = unknowne0[view];
  unknown598 = unknown100[view];
  unknown5a0 = unknown140[view];
  unknown78->setupCate(view);
  unknown88->setupCate(view);
  unknown80->setupCate(view);
  renderViewBegin();
  if (view != 0 && !unknown88->unknown230->unknown0c) {
    return;
  }
  GBuffRender();
  if (!unknown058()) {
    unknown78->clearAccumBuffer();
    if (!unknown1d7d && !unknown1d7e) {
      if (unknown1dc0 == 1) {
        unknown1dc0 = 0;
      }
      unknown78->fastDeferredRender();
      unknown78->lastDeferredRender();
      if (unknown78->unknown7f0->unknown180->unknown108 < 0.05f) {
        unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_4);
        unknown88->occRender(false);
        unknown88->DepthCheckRender(false);
        unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_4);
        unknown78->setMainRenderTarget();
      }
      if (unknown1dc0 == 2) {
        unknown1dc0 = 0;
      }
    }
  }
  if ((!unknown1d7d || unknown1d7e) && !unknown058()) {
    unknown78->renderSkyDome();
    unknown5c0->begin();
    unknown78->alphaRenderTarget();
    unknown88->lightPrePassRender();
    bool isRefractionMap = unknown88->unknown230->unknown08;
    bool isHalfMap;
    if (unknown78->unknown7f0->unknown180->unknown108 > 0.0f) {
      isHalfMap = !unknown120[unknown1c98]->getSSRWithTrans();
    } else {
      isHalfMap = false;
    }
    if (isRefractionMap || isHalfMap) {
      unknown78->renderRefractionMap(isRefractionMap, isHalfMap);
    }
    unknown78->setupGodRay();
    setSkyGodRayRenderTarget();
    unknown78->renderSkyGodRay();
    setAlphaRenderTarget();
    unknown88->alphaRender();
    for (int i = 0; i < unknown658; i++) {
      unknown5d8[i]->alphaRender(&unknown660[unknown1c98]);
    }
  }
  if (!unknown058() && !unknown1d7d) {
    for (int i = 0; i < unknown658; i++) {
      unknown5d8[i]->lastRender(&unknown660[unknown1c98]);
    }
    bool isRefractionMap = unknown88->unknown230->unknown09;
    bool isHalfMap;
    if (unknown78->unknown7f0->unknown180->unknown108 > 0.0f) {
      isHalfMap = unknown120[unknown1c98]->getSSRWithTrans();
    } else {
      isHalfMap = false;
    }
    if (isRefractionMap || isHalfMap) {
      unknown78->renderRefractionMap(isRefractionMap, isHalfMap);
    }
    setAlphaRenderTarget();
    unknown78->setMainViewPort();
    unknown88->spAlphaRender();
  }
  unknown78->lastRender();
  if (view == 0) {
    captureRender(false);
    if (unknown1e00 != nullptr) {
      unknown1e00->finalRender(&unknown660[unknown1c98]);
    }
  }
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->finalRender(&unknown660[unknown1c98]);
  }
  unknown78->lastCapRender();
  if (!unknown058() && view == 0) {
    captureRender(true);
  }
  renderViewEnd();
}

void DrMan::renderEnd(int loop) {
  unknown78->setMainRenderTarget();
  unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_0);
}

void DrMan::renderViewBegin() {
  unknown5c0->begin();
  unknown78->renderBegin(unknown1c98);
}

void DrMan::GBuffRender() {
  if (unknown1d7e) {
    return;
  }
  if (!unknown058()) {
    unknown78->fastRender();
    unknown78->setMainViewPort();
    unknown5c0->begin();
    unknown78->selectGBuffRenderTarget();
    unknown88->setupRender();
    unknown5c0->beginZRender();
    unknown78->selectZprepassRenderTarget();
    unknown88->ZPrePassRender();
    unknown5c0->endZRender();
    unknown78->thicknessFirstBegin();
    unknown5c0->beginThicknessRenderFirst();
    unknown88->ThicknessRenderFirst();
    unknown5c0->endThicknessRenderFirst();
    unknown78->thicknessFirstEnd();
    unknown5c0->beginThicknessRenderSecond();
    unknown88->ThicknessRenderSecond();
    unknown5c0->endThicknessRenderSecond();
    unknown78->selectGBuffRenderTarget();
    unknown5c0->begin();
    unknown88->render();
    if (unknown78->unknown7f0->unknown180->unknown108 >= 0.05f) {
      bool isDepthDown = unknown78->unknown7f0->unknown180->isDepthDown();
      unknown78->unknown7f0->unknown180->setDownDepth();
      unknown78->unknown7f0->unknown180->renderDownDepth(false, false, false);
      unknown78->renderDownBaseColor();
      if (isDepthDown) {
        unknown78->unknown7f0->unknown180->setDownDepth();
      }
    }
    if (unknown78->unknown7f0->unknown180->unknown108 >= 0.05f) {
      unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_4);
      unknown88->occRender(true);
      unknown88->DepthCheckRender(true);
      unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_4);
      unknown78->setMainViewPort();
      unknown78->resetRenderTarget();
    }
    if (unknown78->renderRefractionBegin()) {
      unknown88->refractionRender();
      unknown78->renderRefractionEnd();
    }
    unknown5c0->endRefractionRender();
    unknown5c0->begin();
    unknown78->resetRenderTarget();
    unknown78->selectGBuffRenderTarget();
    unknown78->refractionGBuffInvalidate();
    unknown88->GBuffRender();
    unknown5c0->endGBuffRender();
    unknown78->endGBuffRenderTarget();
  }
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->opacityRender(&unknown660[unknown1c98]);
  }
  unknown5c0->begin();
}

void DrMan::renderViewEnd() {
  unknown580->renderEnd();
  unknown78->renderEnd(unknown1c98);
}

void DrMan::setSkyGodRayRenderTarget() {
  unknown5c0->begin();
  unknown78->resetRenderTarget();
  unknown78->skyGodRayRenderTarget();
}

void DrMan::setAlphaRenderTarget() {
  unknown5c0->begin();
  unknown78->resetRenderTarget();
  unknown78->alphaRenderTarget();
}

void DrMan::blurCallBackRender() {
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->blurRender(&unknown660[unknown1c98]);
  }
}

void DrMan::applyViewBegin() {
  unknown5c0->begin();
  unknown78->updateShadowDisplayList();
}

void DrMan::renderBegin(int loop) { unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_0); }

void DrMan::setMainRenderTarget() { unknown78->setMainRenderTarget(); }

bool DrMan::isIBLHalfRes() const { return true; }

bool DrMan::isIBLSkip() const {
  if (unknown1d75) {
    return true;
  }
  return !unknown80->unknown18->unknown58->isEnable();
}

bool DrMan::isTemporalUPSToGlobalIBL() const {
  if (unknown1d75) {
    return false;
  }
  return unknown80->unknown18->unknown58->isEnable();
}

DrMdlMan::~DrMdlMan() {
  deleteAll();
  if (unknown038 != nullptr) {
    delete unknown038;
    unknown038 = nullptr;
  }
  if (unknown040 != nullptr) {
    delete unknown040;
    unknown040 = nullptr;
  }
  if (unknown048 != nullptr) {
    delete unknown048;
    unknown048 = nullptr;
  }
  if (unknown028 != nullptr) {
    delete unknown028;
    unknown028 = nullptr;
  }
  if (unknown030 != nullptr) {
    delete unknown030;
    unknown030 = nullptr;
  }
  if (unknown008 != nullptr) {
    delete unknown008;
    unknown008 = nullptr;
  }
  if (unknown010 != nullptr) {
    delete unknown010;
    unknown010 = nullptr;
  }
  if (unknown018 != nullptr) {
    delete unknown018;
    unknown018 = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    if (unknown050[i] != nullptr) {
      delete unknown050[i];
      unknown050[i] = nullptr;
    }
  }
  if (unknown020 != nullptr) {
    delete unknown020;
    unknown020 = nullptr;
  }
}

void DrMdlMan::deleteAll(int cate) {
  unknown0a8[cate].unknown005();
  unknown148[cate].unknown005();
}

void DrMdlMan::deleteAll() {
  for (int i = 0; i < 2; i++) {
    unknown1f8[i].unknown005();
  }
  unknown1e8.unknown005();
  for (int i = 0; i < 4; i++) {
    deleteAll(i);
  }
  for (int i = 0; i < 2; i++) {
    unknown0e8[i].unknown005();
  }
  for (int i = 0; i < 2; i++) {
    unknown188[i].unknown005();
  }
  for (int i = 0; i < 4; i++) {
    unknown108[i].unknown005();
    unknown1a8[i].unknown005();
  }
}

void DrMdlMan::addDelList(int cate) {
  unknown108[cate].unknown005();
  unknown1a8[cate].unknown005();
  DrMdlBase *mdl = unknown0e8[DrMan::s_nDblIdx].unknown00;
  while (mdl != nullptr) {
    DrMdlBase *next;
    if (mdl->unknown1a == cate) {
      mdl->resourceInit();
      next = mdl->unknown10;
      unknown0e8[DrMan::s_nDblIdx].unknown001(mdl);
      unknown0a8[cate].unknown004(mdl);
    } else {
      next = mdl->unknown10;
    }
    mdl = next;
  }
  DrGpuCheckObj *check = unknown188[DrMan::s_nDblIdx].unknown00;
  while (check != nullptr) {
    // The game loads the type (0x71007cad08) before the next pointer (0x71007cad0c).
    s32 type = check->unknown18;
    DrGpuCheckObj *next = check->unknown10;
    if (type == cate) {
      unknown188[DrMan::s_nDblIdx].unknown001(check);
      unknown148[cate].unknown004(check);
    }
    check = next;
  }
  unknown030->addObjList(cate);
}

int DrMdlMan::headerChek(const void *data) {
  const unknown003 *header = static_cast<const unknown003 *>(data);
  switch (header->unknown00) {
  case 0x4d584d44:
    return header->unknown04 == 0x2780 ? 1 : 0;
  case 0x4d454d44:
    return header->unknown04 == 0x2780 ? 3 : 0;
  case 0x4d534d44:
    return header->unknown04 == 0x2780 ? 4 : 0;
  case 0x53494d44:
    return header->unknown04 == 0x2780 ? 2 : 0;
  case 0x444c4d43:
    return header->unknown04 == 0x2712 ? 5 : 0;
  }
  return 0;
}

bool DrMdlMan::getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle) {
  size = 0;
  count = 0;
  const unknown005 *header = static_cast<const unknown005 *>(data);
  if (header->unknown00 != 0x4d584d44 || header->unknown1c == 0) {
    return false;
  }
  const unknown006 *info = reinterpret_cast<const unknown006 *>(static_cast<const u8 *>(data) + header->unknown24);
  if (isMiddle) {
    if (info->unknown24 == 0) {
      return false;
    }
    size = info->unknown24;
    count = info->unknown1c;
    return true;
  }
  size = info->unknown20;
  count = 0;
  return true;
}

void DrMdlMan::addViewInfo(int cate) {
  unknown050[cate] = new (unknown000->unknown0c) DrMdoZSortMan(unknown000);
  for (DrMdlBase *mdl = unknown0a8[cate].unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    mdl->unknown20 &= ~(DrMdlBase::unknown038_5 | DrMdlBase::unknown038_6);
  }
}

void DrMdlMan::delViewInfo(int cate) {
  if (unknown050[cate] != nullptr) {
    delete unknown050[cate];
    unknown050[cate] = nullptr;
  }
  for (DrMdlBase *mdl = unknown0a8[cate].unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    mdl->unknown20 &= ~(DrMdlBase::unknown038_5 | DrMdlBase::unknown038_6);
  }
}

void DrMdlMan::setupEnd() {
  s32 index = DrMan::s_nDblIdx;
  unknown0e8[index].unknown00 = nullptr;
  unknown0e8[index].unknown08 = nullptr;
  unknown188[index].unknown00 = nullptr;
  unknown188[index].unknown08 = nullptr;
  unknown030->delObjList();
  unknown028->update();
  unknown010->update();
  unknown008->update();
  index = DrMan::s_nDblIdx;
  for (DrStmReadObj *read = unknown1f8[index].unknown00; read != nullptr;) {
    DrStmReadObj *next = read->unknown10;
    unknown1f8[index].unknown001(read);
    unknown1e8.unknown004(read);
    read = next;
  }
  unknown1f8[index] = DrResChankList<DrStmReadObj>();
  for (DrStmReadObj *read = unknown1e8.unknown00; read != nullptr;) {
    bool isEnd = read->update();
    DrStmReadObj *next = read->unknown10;
    if (isEnd) {
      unknown1e8.unknown001(read);
      delete read;
    }
    read = next;
  }
}

DrMdlObj *DrMdlMan::createMdl(const void *data, const char *name, int index) {
  CS lock(DrMan::getCriticalSection());
  DrMdlObj *mdl;
  int type = headerChek(data);
  switch (type) {
  case 1:
    mdl = new (unknown000->unknown10) DrMdoCtlNom(data, name, unknown000, index);
    break;
  case 2:
    mdl = new (unknown000->unknown10) DrMdoCtlPos(data, name, unknown000, index);
    break;
  case 3:
    mdl = new (unknown000->unknown10) DrMdoCtlMpf(data, name, unknown000, index);
    break;
  case 4:
    mdl = new (unknown000->unknown10) DrMdoCtlSeamAll(data, name, unknown000, index);
    break;
  default:
    if (type == 5) {
      mdl = new (unknown000->unknown10) DrMdoCtlCldMdl(data, unknown000, index);
    } else {
      mdl = new (unknown000->unknown10) DrMdoCtlDammy(data, unknown000, index);
    }
    break;
  }
  unknown0e8[DrMan::s_nDblStockIdx].unknown004(mdl);
  return mdl;
}

DrMdlObj *DrMdlMan::createInstantMdl(const void *data, const char *name, int index) {
  CS lock(DrMan::getCriticalSection());
  DrMdlObj *mdl;
  int type = headerChek(data);
  switch (type) {
  case 1:
    mdl = new (unknown000->unknown10) DrMdoCtlNom(data, name, unknown000, index);
    break;
  case 2:
    mdl = new (unknown000->unknown10) DrMdoCtlPos(data, name, unknown000, index);
    break;
  case 3:
    mdl = new (unknown000->unknown10) DrMdoCtlMpf(data, name, unknown000, index);
    break;
  case 4:
    mdl = new (unknown000->unknown10) DrMdoCtlSeamAll(data, name, unknown000, index);
    break;
  default:
    if (type == 5) {
      mdl = new (unknown000->unknown10) DrMdoCtlCldMdl(data, unknown000, index);
    } else {
      mdl = new (unknown000->unknown10) DrMdoCtlDammy(data, unknown000, index);
    }
    break;
  }
  mdl->resourceInit();
  mdl->setDblBuffAlpha(false);
  mdl->setClipBoxMode(false);
  unknown0a8[index].unknown004(mdl);
  return mdl;
}

DrMdoGrpObj *DrMdlMan::createGrp(int num, u32 flags) {
  CS lock(DrMan::getCriticalSection());
  DrMdoGrpObj *grp = new (unknown000->unknown10) DrMdoGrpObj(num, flags);
  unknown0e8[DrMan::s_nDblStockIdx].unknown004(grp);
  return grp;
}

DrMdoGrpObj *DrMdlMan::createInstantGrp(int num, u32 flags) {
  CS lock(DrMan::getCriticalSection());
  DrMdoGrpObj *grp = new (unknown000->unknown10) DrMdoGrpObj(num, flags);
  grp->resourceInit();
  unknown0a8[num].unknown004(grp);
  return grp;
}

DrGpuCheckBase *DrMdlMan::createGpuCheckObj(int type) {
  CS lock(DrMan::getCriticalSection());
  DrGpuCheckObj *check = new (unknown000->unknown10) DrGpuCheckObj(type, false);
  unknown188[DrMan::s_nDblStockIdx].unknown004(check);
  return check;
}

DrGpuCheckBase *DrMdlMan::createEffGpuCheckObj(int type) {
  CS lock(DrMan::getCriticalSection());
  DrGpuCheckObj *check = new (unknown000->unknown10) DrGpuCheckObj(type, true);
  unknown148[type].unknown004(check);
  return check;
}

DrStmReadObj *DrMdlMan::createStmLoadObj(const char *path) {
  CS lock(DrMan::getCriticalSection());
  DrStmReadCheck *read = new (unknown000->unknown10) DrStmReadCheck(path);
  unknown1f8[DrMan::s_nDblStockIdx].unknown004(read);
  return read;
}

DrStmReadObj *DrMdlMan::createStmSizeObj(u32 size) {
  CS lock(DrMan::getCriticalSection());
  DrStmReadCheck *read = new (unknown000->unknown10) DrStmReadCheck(size);
  unknown1f8[DrMan::s_nDblStockIdx].unknown004(read);
  return read;
}

void DrMdlMan::addMpfObj() {
  if (unknown020 != nullptr) {
    unknown020->addMpfObj();
    return;
  }
  unknown020 = new (unknown000->unknown0c) DrMdoMpfMan(unknown000);
}

void DrMdlMan::delMpfObj() {
  if (unknown020 != nullptr && unknown020->delMpfObj()) {
    if (unknown020 != nullptr) {
      delete unknown020;
      unknown020 = nullptr;
    }
  }
}

void DrMdlMan::simpleShadowRender() { unknown030->shadowRender(); }

void DrMdlMan::lightPrePassRender() {
  if (unknown000->unknown1d64) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewLightPrePassRender();
}

void DrMdlMan::alphaRender() {
  if (unknown000->unknown1d66) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewAlphaRender();
}

void DrMdlMan::spAlphaRender() {
  if (unknown000->unknown1d67) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewSpAlphaRender();
}

void DrMdlMan::GBuffRender() {
  if (unknown000->unknown1d64) {
    return;
  }
  if (unknown001()) {
    return;
  }
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown218->viewGBuffRender();
}

void DrMdlMan::setupRender() {
  if (unknown001()) {
    return;
  }
  unknown218->viewSetupRender();
}

void DrMdlMan::ZPrePassRender() {
  if (unknown001()) {
    return;
  }
  unknown218->viewZPrepassRender();
}

void DrMdlMan::ThicknessRenderFirst() {
  if (unknown001()) {
    return;
  }
  unknown218->viewThicknessRenderFirst();
}

void DrMdlMan::ThicknessRenderSecond() {
  if (unknown001()) {
    return;
  }
  unknown218->viewThicknessRenderSecond();
}

void DrMdlMan::refractionRender() {
  if (unknown000->unknown1d64 || unknown000->unknown1d65) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewRefractionRender();
}

void DrMdlMan::renderBegin() {}

void DrMdlMan::render() {
  if (unknown000->unknown1d63) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewRender();
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    if (unknown23c & (1 << mdl->unknown18)) {
      mdl->shadowCacheOnlyRender();
    }
  }
}

bool DrMdlMan::shadowRender(DrPixlShadowObj *shadow) {
  if (!unknown000->unknown1d7a && !unknown000->unknown1d68) {
    DrPixlMan *pixlMan = unknown000->unknown78;
    pixlMan->setShadowObj(shadow);
    shadow->unknown50 &= ~1u;
    for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((mdl->unknown20 & DrMdlBase::unknown038_0) && (unknown23c & (1 << mdl->unknown18))) {
        mdl->shadowRender();
      }
    }
    if (shadow->renderEnd()) {
      pixlMan->resetRenderTarget();
      return true;
    }
  }
  return false;
}

void DrMdlMan::occRender(bool isFirst) {
  if (unknown001()) {
    return;
  }
  DrPixlMan *pixlMan = unknown000->unknown78;
  pixlMan->occRenderBegin(isFirst);
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    if ((mdl->unknown20 & DrMdlBase::unknown038_0) && (unknown23c & (1 << mdl->unknown18))) {
      mdl->occRender();
    }
  }
  pixlMan->occRenderEnd();
}

void DrMdlMan::DepthCheckRender(bool isDblDepth) {
  if (unknown001()) {
    return;
  }
  if ((unknown240 & (1 << unknown238)) == 0) {
    return;
  }
  unknown048->beginRender(isDblDepth);
  for (DrGpuCheckObj *check = unknown228->unknown00; check != nullptr; check = check->unknown10) {
    check->render();
  }
  unknown048->endRender();
}

bool DrMdlMan::shadowCacheRender(DrPixlShadowCacheObj &cache) {
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    if ((mdl->unknown20 & DrMdlBase::unknown038_0) && (unknown23c & (1 << mdl->unknown18))) {
      if (!mdl->shadowCacheRender(cache)) {
        return false;
      }
    }
  }
  return true;
}

void DrMdlMan::shadowCacheAddRender(int index) {
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    if ((mdl->unknown20 & DrMdlBase::unknown038_0) && (unknown23c & (1 << mdl->unknown18))) {
      mdl->shadowCacheAddRender(index);
    }
  }
}

void DrMdlMan::callShadowCacheUpdate(u64 flags) {
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    mdl->callShadowCacheUpdate(flags);
  }
}

void DrMan::fastRender() { unknown78->fastRender(); }

void DrMan::setCallBack(IDrDrawCallback *callback) {
  if (unknown658 < 16) {
    unknown5d8[unknown658] = callback;
    unknown658++;
  }
}

void DrMan::releaseCallBack(IDrDrawCallback *callback) {
  for (int i = 0; i < unknown658; i++) {
    if (unknown5d8[i] == callback) {
      for (; i < unknown658 - 1; i++) {
        unknown5d8[i] = unknown5d8[i + 1];
      }
      unknown658--;
      unknown5d8[unknown658] = nullptr;
      return;
    }
  }
}

void DrMan::setCacherClearMode(bool cacherClearMode) {
  unknown5b0->unknown2068 = !cacherClearMode ? unknown5b0->unknown2068 & ~DrCalcTexStreamMan::FLAG_UNKNOWN_4 : unknown5b0->unknown2068 | DrCalcTexStreamMan::FLAG_UNKNOWN_4;
}

void DrMan::openPixelDebugWindow(WinProc *window) {}

void DrMan::openHistgramDebugWindow(WinProc *window) {}

void DrMan::memcpyLcDMA(void *destination, const void *source, u32 size) { memcpy(destination, source, size); }

u32 DrMan::getMem1AlphaFree() { return DrPixlMemMan::get()->unknown434; }

void DrMan::setGblIdx(s32 id) {
  if (!isGblIdx(id)) {
    unknown78->callShadowCacheVariance();
    m_gblIdx[id >> 5] |= 1 << (id & 31);
  }
}

void DrMan::offGblIdx(s32 id) {
  if (isGblIdx(id)) {
    unknown78->callShadowCacheVariance();
    m_gblIdx[id >> 5] &= ~(1 << (id & 31));
  }
}

void DrMan::setTimeVal(f32 timeVal) {
  s32 index = s_nDblStockIdx;
  if (timeVal > 1.0f) {
    unknown1ca4[index] = 1.0f;
  } else if (timeVal < 0.0f) {
    unknown1ca4[index] = 0.0f;
  } else {
    unknown1ca4[index] = timeVal;
  }
}

void DrMan::setGroupsDisp(s32 group, bool disp) { unknown88->setGroupsDisp(group, disp); }

void DrMdlMan::setupCate(int cate) {
  unknown238 = cate;
  unknown230 = &unknown070[cate];
  unknown218 = unknown050[cate];
  unknown220 = &unknown0a8[cate];
  unknown228 = &unknown148[cate];
  unknown030->unknown04 = cate;
}

void DrMdlMan::applyDispOff(u32 view) {
  unknown230 = &unknown070[view];
  unknown238 = view;
  unknown220 = &unknown0a8[view];
  unknown228 = &unknown148[view];
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    mdl->noOffScreenUpdate();
  }
  for (DrGpuCheckObj *check = unknown228->unknown00; check != nullptr; check = check->unknown10) {
    check->update();
  }
}

void DrMdlMan::apply() {
  unknown230->unknown00 = false;
  unknown230->unknown01 = false;
  unknown230->unknown02 = false;
  unknown230->unknown03 = false;
  unknown230->unknown04 = false;
  unknown230->unknown05 = false;
  unknown230->unknown06 = false;
  unknown230->unknown07 = false;
  unknown230->unknown08 = false;
  unknown230->unknown09 = false;
  unknown230->unknown0a = false;
  unknown230->unknown0b = false;
  unknown230->unknown0c = false;
  unknown218->beginViewWorld();
  for (DrMdlBase *mdl = unknown220->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
    if ((mdl->unknown20 & DrMdlBase::unknown038_0) && (unknown23c & (1 << mdl->unknown18))) {
      mdl->update();
    } else {
      mdl->dispOffUpdate();
    }
  }
  unknown240 &= ~(1 << unknown238);
  unknown048->beginUpdate();
  bool isRender = false;
  for (DrGpuCheckObj *check = unknown228->unknown00; check != nullptr; check = check->unknown10) {
    isRender |= check->update();
  }
  unknown048->endUpdate();
  if (isRender) {
    unknown240 |= 1 << unknown238;
  }
  if (unknown238 == 0) {
    if (unknown000->unknown1e00 != nullptr) {
      unknown000->unknown1e00->apply(&unknown000->unknown660[unknown000->unknown1c98], unknown218);
    }
  }
  unknown218->endViewWorld();
  unknown230->unknown06 = unknown030->checkDisp();
}

void DrMdlMan::beginApply() {
  if (unknown020 != nullptr) {
    unknown020->begin();
  }
  unknown008->begin();
  unknown038->begin();
  unknown040->begin();
  unknown018->begin();
}

void DrMdlMan::endApply() {
  if (unknown020 != nullptr) {
    unknown020->update();
  }
  unknown008->end();
  unknown038->end();
  unknown040->end();
}

void DrMdlMan::setGroupsDisp(s32 group, bool disp) {
  if (disp) {
    unknown23c |= 1 << group;
  } else {
    unknown23c &= ~(1 << group);
  }
}

void DrMan::setReduction(bool isReduction, f32 scaleX, f32 scaleY) {
  DrPixlPostParm *postParm = unknown120[0];
  postParm->unknownfb2 = isReduction;
  postParm->unknownfb8 = scaleX;
  postParm->unknownfbc = scaleY;
}

void DrMan::setAutoReduction(bool autoReduction) { unknown5c8->m_autoReduction = autoReduction; }

void DrMan::setAA(bool isAA) { unknown120[0]->m_AAOn = isAA; }

void DrMan::setColorFilter(bool isColorFilter) { unknown120[0]->m_colTblOn = isColorFilter; }

void DrMan::setSSAO(bool isSSAO) { unknown120[0]->unknown194 = isSSAO; }

void DrMan::setBloom(bool isBloom, bool isLensFlare) { unknown120[0]->m_bloomOn = isBloom; }

void DrMan::setToneMap(bool isToneMap) { unknown120[0]->m_toneMapOn = isToneMap; }

void DrMan::setMotionBlur(bool isMotionBlur) { unknown120[0]->unknown1ca = isMotionBlur; }

void DrMan::setMotionBlur(f32 strength, f32 sub) {}

void DrMan::setDepthOfField(bool isDepthOfField) { unknown120[0]->setDOF(isDepthOfField); }

void DrMan::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) {
  DrPixlPostParm *postParm = unknown120[0];
  postParm->setDoFDistance(distance);
  postParm->setDoFRange(range);
  postParm->setDoFPixlRatio(strength);
  postParm->setDoFLens(blend);
}

void DrMan::setGlobalWind(const mm::Vec3 &globalWind) { m_globalWind[s_nDblStockIdx] = globalWind; }

const mm::Vec3 &DrMan::getGlobalWind() const { return m_globalWind[s_nDblNowIdx]; }

void DrMan::callCubeMapRender(const DR_CAPCUBE_PARAM &param) {}

bool DrMan::isSRGBMode() { return s_bSRGBMode; }

bool DrMan::isFogSRGB() { return s_bFogSRGB; }

bool DrMan::isSeamDebug() { return s_bSeamDebug; }

void DrMan::beginMetric(const char *name) { grlib::CGLibDebug::setPushDebugGroup(name); }

void DrMan::endMetric(const char *name) { grlib::CGLibDebug::setPopDebugGroup(); }

void DrMan::releaseFastLight(s32 index) {
  if (unknownc0[index] != nullptr) {
    unknownc0[index]->releaseFastLight();
  }
}

void DrMan::setAllMiddelTexStmChk(bool isCheck) { m_allMiddelTexStmChk[s_nDblIdx] |= isCheck; }

bool DrMan::isAllMiddelTexStmChk() const { return m_allMiddelTexStmChk[s_nDblStockIdx]; }

void DrMan::setSeamMapStmOk(bool isOk) { m_seamMapStmOk[s_nDblIdx] = isOk; }

bool DrMan::isSeamMapStmOk() const { return m_seamMapStmOk[s_nDblStockIdx]; }

void DrMan::setAvatarCapMode(s32 avatarCapMode) {}

void DrMan::setDblNowIdx(int index) {
  s_nDblNowIdx = index;
  grlib::CGLibManager::s_nDblNowIdx = index;
}

void DrMan::bkgHomeMenu(bool isOpen) {
  if (isOpen) {
    unknown1cc0 = true;
  }
}

void DrMan::debugUpdate() {
  int type = 0;
  while (!unknown1dac[type]) {
    type++;
    if (type == 14) {
      return;
    }
  }
  unknown1dbc++;
  if (unknown1dbc == 2) {
    switch (type) {
    case 0:
    case 3: {
      DrShdLgtMan *lgtMan = unknown80->unknown18;
      DrShdDataList *dataList = unknown80->unknown00;
      lgtMan->releaseLightShader();
      dataList->releaseShader();
      dataList->reloadShader(0);
      lgtMan->reloadShader(0);
      break;
    }
    case 6:
      unknown70->reloadToonGradTexture();
      break;
    case 7:
      unknown70->reloadToonRimTexture();
      break;
    case 8:
      unknown70->reloadVolumeTexture();
      break;
    case 10:
      unknown70->reloadIBLEnvTexture();
      break;
    case 11:
      unknown70->reloadMirrorBallModel();
      break;
    case 12:
      unknown70->reloadRainDropTexture();
      break;
    case 13:
      unknown70->reloadFlagWaveTexture();
      break;
    }
  }
  if (unknown1dbc > 2) {
    unknown1dac[type] = false;
    unknown1dbc = 0;
  }
}

void DrMan::end() {
  if (unknown1e00 != nullptr) {
    unknown1e00->end();
  }
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->end();
  }
  endSetup();
}

void DrMan::endSetup() {
  unknown1d8d = unknown1d8c;
  unknown5b8 = unknown440;
  unknown580 = unknowna0[0];
  unknown1c98 = 0;
  unknown588 = unknownc0[0];
  unknown590 = unknowne0[0];
  unknown598 = unknown100[0];
  unknown78->setupCate(0);
  unknown88->setupCate(0);
  unknown80->setupCate(0);
}

void DrMan::applyView(int view) {
  unknown5b8 = &unknown440[view];
  unknown1c98 = view;
  unknown660[view].unknown560 = view;
  unknown660[view].unknown568 = unknown1d62;
  unknown98->unknown100 = view;
  unknown580 = unknowna0[view];
  unknown588 = unknownc0[view];
  unknown590 = unknowne0[view];
  unknown598 = unknown100[view];
  unknown5a0 = unknown140[view];
  unknown5a8 = unknown160[view];
  unknown88->setupCate(view);
  unknown80->setupCate(view);
  unknown78->setupCate(view);
  unknown5c0->begin();
  unknown78->updateShadowDisplayList();
  unknown580->begin();
  unknown588->stockBegin();
  unknown588->update();
  unknown590->update();
  unknown598->update();
  unknown98->update(view);
  unknown5a0->update();
  unknown5a8->update();
  unknown80->beforeUpdateCate(view);
  unknown590->calcTbl();
  unknown78->beforUpdate(view);
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->apply(&unknown660[unknown1c98]);
  }
  unknown88->apply();
  unknown588->stockEnd();
  unknown80->updateCate(view);
  unknown78->afterUpdate(view);
  unknown580->end();
}

void DrMan::render(int loop) {
  if (unknown1dbc != 0) {
    return;
  }
  unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_0);
  for (int view = 3; view >= 0; view--) {
    if ((unknown440[view].unknown38 & 3) == 1) {
      renderView(view);
    }
  }
  for (int view = 3; view >= 0; view--) {
    if ((unknown440[view].unknown38 & 3) == 3) {
      renderView(view);
    }
  }
  unknown120[unknown1c98]->resetWeatherFrame();
  unknown78->setMainRenderTarget();
  unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_0);
}

} // namespace ml

// The game compiles DrMdlObj::setDblBuffAlpha and DrMdlObj::setClipBoxMode in this unit (0x7ce29c and 0x7ce2b8 follow createInstantMdl, which inlines them).
#include "dr_mdl_obj.cpp"
// The game compiles DrMdoGrpObj in this unit too (0x7cf5e4 follows DrMdlObj::OnCloseAttriMenu): its create functions inline DrMan::getCriticalSection.
#include "dr_mdo_grp_obj.cpp"
