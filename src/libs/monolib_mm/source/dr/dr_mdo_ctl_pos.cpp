#include "dr/dr_mdo_ctl_pos.h"

#include <string.h>

#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_cp_plane_obj.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_texture_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_pnt_alpha.h"
#include "dr/dr_res_mdo_pos.h"
#include "dr/dr_res_mdo_pos_add_list.h"
#include "dr/dr_res_mdo_sort.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_occ_uniform_obj.h"
#include "dr/dr_res_wrk_clip_list.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoCtlPos::~DrMdoCtlPos() { releasePos(); }

void DrMdoCtlPos::releasePos() {
  m_drMan->unknown78->unknown800->delShadowCacheUpdate();
  for (int i = 0; i < unknown1d8; i++) {
    unknown1e0[i].~DrResMdoPos();
  }
  unknown1d8 = 0;
  unknown1e8.release();
  if (unknown250 != nullptr) {
    unknown250->release();
    unknown250 = nullptr;
  }
  if (unknown258 != nullptr) {
    DrResMdoInstMdlInfo::release(unknown258);
  }
  unknown268->~DrResMdoSortPos();
  for (int i = 0; i < unknown238; i++) {
    if (unknown228[i] != nullptr) {
      mtl::MemManager::deallocate(unknown228[i], 0, false);
      unknown228[i] = nullptr;
    }
  }
  if (unknown230 != nullptr) {
    mtl::MemManager::deallocate(unknown230, 0, false);
    unknown230 = nullptr;
  }
  if (unknown220 != nullptr) {
    mtl::MemManager::deallocate(unknown220, 0, false);
    unknown220 = nullptr;
  }
  releaseMat();
}

void DrMdoCtlPos::update() {
  updateAlphaCall();
  updatePos();
  DrMdlMan *mdlMan = m_drMan->unknown88;
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

void DrMdoCtlPos::setDeleteCall(int deleteCall) {
  DrMdlBase::setDeleteCall(deleteCall);
  if (unknown258 != nullptr) {
    unknown258->releaseCall();
  }
  if (unknown358 != nullptr) {
    unknown358->release();
    unknown358 = nullptr;
  }
}

void DrMdoCtlPos::callShadowCacheUpdate(u64 flags) {
  unknown368 &= ~flags;
  if (unknown370 & flags) {
    unknown370 = 0;
    unknown378 = 0;
  }
}

void DrMdoCtlPos::beginRenderListPos() {
  unknown1a0 = 0;
  unknown360 = 0;
  unknown2c0 = nullptr;
  unknown260 = 0;
  unknown262 = 0;
  unknown250->begin();
  unknown248 = DrMan::s_nDblIdx * INS_RENDERBUFF_SIZE;
  unknown2d8 = 0;
  for (int i = 0; i < 6; i++) {
    unknown2e0[i] = 0;
  }
  unknown340 = 0;
  int size = unknown30->unknown170 * 0x42u;
  size += (32 - size % 32) % 32;
  memset(unknown270[0], 0, size);
  unknown2a8->update(m_drMan->unknown1c8c);
  if (unknown218 != nullptr) {
    unknown218->update(m_drMan->unknown580->unknown18);
  }
  if (unknown258 != nullptr) {
    DrResMdlInstMdlArg arg;
    arg.unknown00 = &unknown348->unknown400;
    arg.unknown10 = true;
    arg.unknown14 = unknown1a;
    arg.unknown08 = nullptr;
    arg.unknown18 = unknowndc;
    unknown258->update(arg);
  }
}

bool DrMdoCtlPos::chankRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg) {
  DrCalcViewWork *viewWork = unknown348;
  f32 x = viewWork->unknown400.x - tree->unknown00[0];
  f32 y = viewWork->unknown400.y - tree->unknown00[1];
  f32 z = viewWork->unknown400.z - tree->unknown00[2];
  if (x * x + y * y + z * z > tree->unknown10) {
    return false;
  }
  if (!viewWork->unknown4e0.clipTest(*reinterpret_cast<const mm::Vec3 *>(tree->unknown00), tree->unknown0c)) {
    return false;
  }
  bool isRender = false;
  u32 count = tree->unknown1c;
  if (count != 0) {
    const u16 *child = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown1a8) + tree->unknown14);
    for (u32 i = 0; i < count; i++) {
      isRender |= chankRenderMdl(unknown1c8 + *child++, arg);
    }
  }
  if (tree->unknown1e != 0) {
    isRender |= clipRenderMdl(tree, arg);
  }
  return isRender;
}

bool DrMdoCtlPos::clipRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg) {
  bool isRender = false;
  u32 count = tree->unknown1e;
  const u32 *index = reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(unknown1a8) + tree->unknown18);
  for (u32 i = 0; i < count; i++, index++) {
    const MdsPosKeepData *keep = unknown1d0 + *index;
    if (keep->unknown66 != 0) {
      u32 *clipTbl = unknown218->unknown18;
      s32 clip = keep->unknown66 - 1;
      if (clipTbl[clip >> 5] & (1 << (clip & 31))) {
        continue;
      }
    }
    u32 gbl = keep->unknown62;
    if (gbl == 0) {
      isRender |= objPartsRenderMdl(keep, &unknown1e0[*index], arg);
      continue;
    }
    if (!m_drMan->isGblIdx(gbl)) {
      DrResMdoPos *pos = &unknown1e0[*index];
      f32 objAlpha = 1.0f;
      if (unknown1e8.unknown00 != nullptr) {
        objAlpha = unknown1e8.getObj(pos->unknown18)->unknown28;
      }
      if (objAlpha > 0.0f) {
        s32 alpha = arg.unknown00;
        if (objAlpha < 1.0f) {
          arg.unknown00 = objAlpha * 255.0f;
        }
        isRender |= objPartsRenderMdl(keep, pos, arg);
        arg.unknown00 = alpha;
      }
    }
  }
  return isRender;
}

void DrMdoCtlPos::chankShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowCacheObj &cache) {
  if (!cache.clipTest(*reinterpret_cast<const mm::Vec3 *>(tree->unknown00), tree->unknown0c)) {
    return;
  }
  u32 count = tree->unknown1c;
  if (count != 0) {
    const u16 *child = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown1a8) + tree->unknown14);
    for (u32 i = 0; i < count; i++) {
      chankShadowRenderMdl(unknown1c8 + *child++, cache);
    }
  }
  if (tree->unknown1e != 0) {
    clipShadowRenderMdl(tree, cache);
  }
}

void DrMdoCtlPos::updatePos() {
  updateMdl();
  createMdlList();
}

void DrMdoCtlPos::dispOffUpdate() {
  if (unknown258 != nullptr) {
    DrResMdlInstMdlArg arg;
    unknown348 = m_drMan->unknown580->unknown10;
    arg.unknown00 = &unknown348->unknown400;
    arg.unknown10 = false;
    arg.unknown14 = unknown1a;
    arg.unknown08 = nullptr;
    arg.unknown18 = unknowndc;
    unknown258->update(arg);
  }
}

void DrMdoCtlPos::resourceInit() {
  setupResource(false);
  if (unknown30->unknownf0 != 0) {
    unknown30->unknownd0 = m_drMan->unknown88->unknown010->createTextureObj(unknown30->unknown08);
    for (int i = 0; i < unknown30->unknownd0->unknown68; i++) {
      unknown30->unknowne8[i] = unknown30->unknownd0->getTexObj(i);
    }
  }
  m_drMan->unknown78->unknown800->addShadowCacheUpdate(false);
  unknown24c = 0;
}

void DrMdoCtlPos::createRenderDisplayList(const MdsMdlInfoHeader *, int, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlPos::createThicknessRenderFirstDisplayList() { createThicknessRenderDisplayListSub(true); }

void DrMdoCtlPos::createThicknessRenderSecondDisplayList() { createThicknessRenderDisplayListSub(false); }

void DrMdoCtlPos::callPosRender(u32 renderType) {
  u32 count = unknown260;
  if (count == 0) {
    return;
  }
  MdoInstanceDrawArg arg;
  arg.unknown0c = 0x34;
  for (u32 i = 0; i < count; i++) {
    const unknown020 &list = unknown2b0[i];
    // The game loads the table pointer before the index (0x71008173a8): pointer arithmetic gives that order, the subscript operator loads the index first.
    const MdsMdlTopHeader *top = unknown30->unknown168 + list.unknown0c;
    s32 mode = (list.unknown08 & 1) + 1;
    if (renderType == 8) {
      mode = 2;
    }
    arg.unknown08 = list.unknown14;
    arg.unknown20 = list.unknown10;
    if ((top->unknown08 & 4) != 0) {
      unknown30->unknown148->unknown20 = list.unknown12;
      arg.unknown24 = list.unknown12;
    }
    if ((top->unknown08 & 0x20) != 0) {
      arg.unknown2c = list.unknown0a;
    }
    s32 infoCount = top->unknown04;
    arg.unknown00 = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
    if (renderType == 1 || renderType == 8 || renderType == 0x20) {
      arg.unknown10 = list.unknown00;
      for (s32 j = 0; j < infoCount; j++, arg.unknown00++) {
        // Same order for the material (0x7100817350, 0x7100817460): table pointer first, then the index; the subscript form changes the register of the table.
        if ((arg.unknown00->unknown04 & renderType) != 0 && (unknown30->unknownc0 + arg.unknown00->unknown0e)->unknown08.a > 0.0f) {
          if ((arg.unknown00->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) == 0 && (arg.unknown00->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) == 0) {
            arg.unknown14 = list.unknown02;
            arg.unknown18 = list.unknown04;
            arg.unknown1c = list.unknown06;
            arg.unknown28 = mode;
          } else {
            arg.unknown14 = list.unknown00;
            arg.unknown18 = 0;
            arg.unknown1c = 0;
            arg.unknown28 = 0;
          }
          partsInstanceDefRender(arg);
        }
      }
    } else {
      s32 instanceCount = list.unknown00 - list.unknown06;
      if (instanceCount != 0) {
        // The game stores unknown28 twice here (0x7100817318 and 0x7100817330), the second one after unknown14.
        arg.unknown28 = 0;
        arg.unknown10 = instanceCount;
        arg.unknown14 = list.unknown02;
        arg.unknown18 = list.unknown04 - list.unknown06;
        arg.unknown28 = 0;
        arg.unknown1c = 0;
        for (s32 j = 0; j < infoCount; j++, arg.unknown00++) {
          if ((arg.unknown00->unknown04 & renderType) != 0 && (unknown30->unknownc0 + arg.unknown00->unknown0e)->unknown08.a > 0.0f) {
            partsInstanceDefRender(arg);
          }
        }
      }
    }
  }
}

void DrMdoCtlPos::callZpreePassRenderPosAll() {
  if ((unknownf8 & unknown028_20) == 0) {
    return;
  }
  createZBuffRenderDisplayList();
}

void DrMdoCtlPos::callThicknessRenderFirstPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(true);
}

void DrMdoCtlPos::callThicknessRenderSecondPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(false);
}

void DrMdoCtlPos::callGBuffRenderPosAll() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  beginSetup();
  callPosRender(8);
}

void DrMdoCtlPos::callRenderPosAll() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  beginSetup();
  callPosRender(1);
}

void DrMdoCtlPos::callRefractionRenderPosAll() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  beginSetup();
  callPosRender(4);
}

void DrMdoCtlPos::callLightPrePassRenderPosAll() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  beginSetup();
  callPosRender(0x20);
}

void DrMdoCtlPos::callAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_4) == 0) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  beginSetup();
  callPosRender(2);
}

void DrMdoCtlPos::callSpAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  beginSetup();
  callPosRender(0x40);
}

// 0x710081828c. Same body as DrResMdoSeamWrkInst::occRender (0x71008896d0), which holds the two render lists unrolled by Clang 3.9.1 as well.
void DrMdoCtlPos::occRender() {
  if (unknown2c0 != nullptr) {
    DrPixlOccQuery *query = m_drMan->unknown78->unknown7f8;
    DrResOccUniformObj *uniform = m_drMan->unknown88->unknown038;
    for (unknown020 *info = unknown2c0; info != nullptr; info = info->unknown18) {
      u32 index = info->unknown0c;
      const s16 *posNum = &unknown30->unknown168[index].unknown28;
      for (int type = 1; type < 3; type++) {
        for (DrResMdoPos *pos = unknown270[type][index]; pos != nullptr; pos = pos->unknown10) {
          u16 flags = pos->unknown1e;
          if ((flags & 0xf) != 0) {
            u32 bits = 0;
            int count = 0;
            for (int i = 0; i < *posNum; i++) {
              if ((1 << i) & flags) {
                bits |= 1 << i;
                count++;
              }
            }
            query->occRenderPosAABB(&pos->unknown00_1, uniform->getMatTbl(pos->unknown20), &bits, count);
          }
        }
      }
    }
  }
}

void DrMdoCtlPos::callDisplistRender(int param) {}

void DrMdoCtlPos::callDisplistPrePsssRender(int param) {}

void DrMdoCtlPos::shadowRender() {
  unknownf4 = 6;
  unknownf2 = 0;
  DrPixlShadowObj *shadow = m_drMan->unknown78->unknown848;
  if (!shadow->unknown198->isInstMapShadow()) {
    return;
  }
  unknown348 = m_drMan->unknown580->unknown10;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  const unknown017 *header = unknown1a8;
  for (int i = 0; i < header->unknown2c; i++) {
    nomTreeShadowRenderMdl(&unknown1c8[i], shadow);
  }
}

bool DrMdoCtlPos::shadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknown368 & cache.unknown8e8) != 0) {
    return true;
  }
  if (unknown370 == 0) {
    unknown370 = cache.unknown8e8;
    unknown378 = 0;
  } else if ((unknown370 & cache.unknown8e8) == 0) {
    unknown370 = cache.unknown8e8;
    unknown378 = 0;
    return true;
  }
  if (unknown30->unknownc8 != nullptr) {
    unknown001();
    unknown30->unknownc8->beginVertexSetup();
    unknownf4 = 6;
    unknownf2 = 0;
    if (cache.unknown808 & 0x10) {
      unknown168 |= 0x80;
    }
    // The game zero-extends the signed id (ldrsh, uxtw) for the table index, as DrResMdoSeamWrkInst::seachShadowInstMapRender does with its u32 local.
    u32 id = cache.unknown8f0;
    unknown37c = DrPixlShadowCacheMan::SHADOW_CHECK_RANGE_TBL[id];
    const unknown017 *header = unknown1a8;
    for (int i = 0; i < header->unknown2c; i++) {
      chankShadowRenderMdl(&unknown1c8[i], cache);
    }
    unknown168 &= ~0x80;
  }
  unknown378 = 0;
  unknown370 = 0;
  if ((cache.unknown808 & 8) == 0) {
    unknown368 |= cache.unknown8e8;
  }
  return true;
}

void DrMdoCtlPos::nomTreeShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowObj *shadow) {
  DrCalcViewWork *viewWork = unknown348;
  f32 x = viewWork->unknown400.x - tree->unknown00[0];
  f32 y = viewWork->unknown400.y - tree->unknown00[1];
  f32 z = viewWork->unknown400.z - tree->unknown00[2];
  if (x * x + y * y + z * z > tree->unknown10) {
    return;
  }
  if (!shadow->clipTypeChk(*reinterpret_cast<const mm::Vec3 *>(tree->unknown00), tree->unknown0c)) {
    return;
  }
  u32 count = tree->unknown1c;
  if (count != 0) {
    const u16 *child = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown1a8) + tree->unknown14);
    for (u32 i = 0; i < count; i++) {
      nomTreeShadowRenderMdl(unknown1c8 + *child++, shadow);
    }
  }
  if (tree->unknown1e != 0) {
    nomTreeListShadowRenderMdl(tree, shadow);
  }
}

void DrMdoCtlPos::updateInstPosDispCall(const u32 *flags) {
  unknown703 *dispCall = unknown30->unknown130;
  if (dispCall != nullptr && dispCall->unknown00 > 0) {
    _MdoWrkDispCallTemp *temp = dispCall->unknown08;
    const MdsMatDispCCData *data = dispCall->unknown10;
    for (s32 i = 0; i < dispCall->unknown00; i++, data++, temp++) {
      if ((flags[data->unknown04 >> 5] & (1 << (data->unknown04 & 31))) && checkCallBackParam(temp, data)) {
        unknown240[data->unknown04 >> 4] |= 1 << ((data->unknown04 & 0xf) << 1);
        unknown240[data->unknown04 >> 4] |= 1 << (((data->unknown04 & 0xf) << 1) | 1);
      }
    }
  }
}

void DrMdoCtlPos::createInstUniformBlock(const u32 *flags) {
  updateAnim(unknowndc * m_drMan->unknown1c8c, flags, nullptr);
  updateMatFstCallBack();
  updateMatCallBack(flags);
  updateTimerCalc(flags);
  s32 matNum = unknown30->unknown30;
  updateUniformBlock(flags);
  updateInstPosDispCall(flags);
  s32 nowIdx = DrMan::s_nDblNowIdx;
  for (s32 i = 0; i < matNum; i++) {
    s32 bit = nowIdx + i * 2;
    if (flags[i >> 5] & (1 << (i & 0x1f))) {
      if (unknown240[bit >> 5] & (1 << (bit & 0x1f))) {
        unknown240[bit >> 5] &= ~(1 << (bit & 0x1f));
      }
    }
  }
}

} // namespace ml
