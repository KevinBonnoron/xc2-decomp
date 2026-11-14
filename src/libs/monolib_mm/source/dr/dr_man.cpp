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
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_res_chank_list.h"
#include "dr/dr_res_etc_uniform_obj.h"
#include "dr/dr_res_filter_data.h"
#include "dr/dr_res_occ_uniform_obj.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_stm_read_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_debug.h"
#include "grlib/cglib_manager.h"
#include "ml/critical_section.h"

// The game builds DrIniSys in this unit, before this file (0x71007c4958 to 0x71007c8450): DrMan::setSRGBMode (0x71007c750c) sits inside its block.
#include "dr_ini_sys.cpp"

namespace ml {
class DrPixlShadowCacheObj;
class DrGpuCheckBase;

DrMan *DrMan::getIns() { return s_pTop; }

DrMan *DrMan::get() { return s_pTop; }

CriticalSection &DrMan::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

int DrMan::loopCnt() { return 1; }

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

void DrMan::renderEnd(int loop) {
  unknown78->setMainRenderTarget();
  unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_0);
}

void DrMan::renderViewBegin() {
  unknown5c0->begin();
  unknown78->renderBegin(unknown1c98);
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
