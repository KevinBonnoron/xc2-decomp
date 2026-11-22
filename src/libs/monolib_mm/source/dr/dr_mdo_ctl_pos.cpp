#include "dr/dr_mdo_ctl_pos.h"

#include <new>
#include <string.h>

#include "dr/dr_calc_clip_man.h"
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
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoCtlPos::~DrMdoCtlPos() { releasePos(); }

void DrMdoCtlPos::releasePos() {
  m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->delShadowCacheUpdate();
  for (int i = 0; i < unknown1d8; i++) {
    unknown1e0[i].~DrResMdoPos();
  }
  unknown1d8 = 0;
  m_drResMdoInstAnmObj.release();
  if (m_drResMdoPosAddList != nullptr) {
    m_drResMdoPosAddList->release();
    m_drResMdoPosAddList = nullptr;
  }
  if (m_drResMdoInstMdlInfo != nullptr) {
    DrResMdoInstMdlInfo::release(m_drResMdoInstMdlInfo);
  }
  m_drResMdoSortPos->~DrResMdoSortPos();
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

// Measured forms (1.0.0: 0x71008103dc, 391 instructions). The work block is sized in a first pass (int `size`, the pads `(32 - x % 32) % 32` of the game's signed remainder) and carved in a
// second pass (int `offset`) in the same order. Every product of a count with a size is unsigned (`unknown1d8 * 0x28u`, `unknown30->unknown170 * 8u`, as beginRenderListPos does with 0x42u):
// the game keeps the offset a 32 bit chain (`add w8, w8, w13, lsl #3`, one sxtw per pointer, 0x710081086c ...), while with signed products clang widens it to 64 bit (397
// instructions) and merges `n * 0x30 + n * 2` into `n * 50` (390). The sort object size 0x20 is added before the count of blocks is stored (0x71008104d4: add w8, w8, #0x20 before the
// compare with 500); written after the `if` it is reassociated to the end of the sum. The pad of the last size is computed before the count of the flags size is loaded (0x71008105fc, 0x7100810614).
void DrMdoCtlPos::setupPos(const u8 *data, const char *path) {
  if (unknown220 != nullptr) {
    mtl::MemManager::deallocate(unknown220, 0, false);
    unknown220 = nullptr;
  }
  const unknown017 *header = reinterpret_cast<const unknown017 *>(data);
  unknown1a8 = header;
  unknown1d8 = header->unknown14;
  m_mdsPosKeepData = reinterpret_cast<const MdsPosKeepData *>(data + header->unknown18);
  m_mdsPosRangeTreeData = reinterpret_cast<const MdsPosRangeTreeData *>(data + header->unknown28);
  unknown1b0 = reinterpret_cast<const unknown018 *>(data + header->unknown08);
  unknown1b8 = reinterpret_cast<const unknown019 *>(data + header->unknown10);
  unknown1c0 = reinterpret_cast<const u32 *>(data + header->unknown20);
  int size = unknown1d8 * 0x28;
  if (header->unknown40 != 0) {
    size += (0x10 - size % 0x10) % 0x10;
    size += DrResMdoInstAnmObj::getWorkSize(data + header->unknown40);
  }
  size += 0x20;
  unknown238 = static_cast<u32>(unknown30->unknown30) / 500;
  if (static_cast<u32>(unknown30->unknown30) % 500 != 0) {
    unknown238++;
  }
  size += unknown238 * 8;
  size += DrResMdoPntAlphaMan::getWrkSize(0xf);
  if (header->unknown54 == 0) {
    m_drResWrkClipList = nullptr;
  } else {
    size += 0x20;
    size += (0x20 - size % 0x20) % 0x20;
    size += DrResWrkClipList::calcWorkSize(data, header->unknown54);
  }
  if (header->unknown68 != 0) {
    size += DrResMdoInstMdlInfo::calcWorkSize(data + header->unknown68);
  }
  size += DrResMdoPosAddList::createBuffSize();
  size += 0x10;
  size += (0x20 - size % 0x20) % 0x20;
  size += unknown30->unknown170 * 0x30u;
  size += unknown30->unknown170 * 2u;
  size += (0x20 - size % 0x20) % 0x20;
  size += unknown30->unknown170 * 0x28u;
  size += (0x20 - size % 0x20) % 0x20;
  int flagsSize = unknown30->unknown30 / 16 * 4 + 4;
  flagsSize += (0x20 - flagsSize % 0x20) % 0x20;
  int total = size + flagsSize;
  unknown220 = static_cast<u8 *>(mtl::MemManager::allocate(m_drMan->unknown14, total, 0x20, false, "no name", 0));
  unknown1e0 = reinterpret_cast<DrResMdoPos *>(unknown220);
  int offset = unknown1d8 * 0x28u;
  if (header->unknown40 != 0) {
    offset += (0x10 - offset % 0x10) % 0x10;
    offset += m_drResMdoInstAnmObj.setup(unknown220 + offset, reinterpret_cast<const u8 *>(unknown1a8) + header->unknown40);
  }
  m_drResMdoSortPos = reinterpret_cast<DrResMdoSortPos *>(unknown220 + offset);
  offset += 0x20;
  unknown228 = reinterpret_cast<void **>(unknown220 + offset);
  offset += unknown238 * 8;
  for (int i = 0; i < unknown238; i++) {
    unknown228[i] = nullptr;
  }
  offset += DrResMdoPntAlphaMan::setWrk(m_drResMdoPntAlphaMan, 0xf, unknown220 + offset);
  if (header->unknown54 != 0) {
    m_drResWrkClipList = reinterpret_cast<DrResWrkClipList *>(unknown220 + offset);
    offset += 0x20;
    offset += (0x20 - offset % 0x20) % 0x20;
    offset += m_drResWrkClipList->setupWork(unknown220 + offset, data, header->unknown54);
  }
  if (header->unknown68 != 0) {
    offset += DrResMdoInstMdlInfo::create(unknown220 + offset, m_drResMdoInstMdlInfo, data + header->unknown68, path);
  }
  m_drResMdoPosAddList = reinterpret_cast<DrResMdoPosAddList *>(unknown220 + offset);
  offset += 0x10;
  offset += m_drResMdoPosAddList->setupBuff(unknown220 + offset);
  offset += (0x20 - offset % 0x20) % 0x20;
  for (int i = 0; i < 3; i++) {
    unknown270[i] = reinterpret_cast<DrResMdoPos **>(unknown220 + offset);
    offset += unknown30->unknown170 * 8u;
    unknown288[i] = reinterpret_cast<DrResMdoPos **>(unknown220 + offset);
    offset += unknown30->unknown170 * 8u;
  }
  unknown2a0 = reinterpret_cast<u16 *>(unknown220 + offset);
  offset += unknown30->unknown170 * 2u;
  offset += (0x20 - offset % 0x20) % 0x20;
  unknown2b0 = reinterpret_cast<const unknown020 *>(unknown220 + offset);
  offset += unknown30->unknown170 * 0x20u;
  unknown2b8 = unknown220 + offset;
  offset += unknown30->unknown170 * 8u;
  offset += (0x20 - offset % 0x20) % 0x20;
  unknown240 = reinterpret_cast<u32 *>(unknown220 + offset);
  memset(unknown240, 0, flagsSize);
  for (int i = 0; i < unknown1d8; i++) {
    new (&unknown1e0[i]) DrResMdoPos(&m_mdsPosKeepData[i]);
  }
  m_drResMdoInstAnmObj.setupLink(unknown1e0);
  new (m_drResMdoSortPos) DrResMdoSortPos(this);
  m_drCalcClipMan = m_drMan->m_drCalcMan->m_drCalcClipMan;
  if (header->unknown6c != 0) {
    m_drCalcCpPlaneObj = m_drCalcClipMan->createCpPlaneObj(data + header->unknown6c);
  }
}

void DrMdoCtlPos::update() {
  updateAlphaCall();
  updatePos();
  DrMdlMan *mdlMan = m_drMan->m_drMdlMan;
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
  if (m_drResMdoInstMdlInfo != nullptr) {
    m_drResMdoInstMdlInfo->releaseCall();
  }
  if (m_drCalcCpPlaneObj != nullptr) {
    m_drCalcCpPlaneObj->release();
    m_drCalcCpPlaneObj = nullptr;
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
  m_drResMdoPosAddList->begin();
  unknown248 = DrMan::s_nDblIdx * INS_RENDERBUFF_SIZE;
  unknown2d8 = 0;
  for (int i = 0; i < 6; i++) {
    unknown2e0[i] = 0;
  }
  unknown340 = 0;
  int size = unknown30->unknown170 * 0x42u;
  size += (32 - size % 32) % 32;
  memset(unknown270[0], 0, size);
  m_drResMdoPntAlphaMan->update(m_drMan->unknown1c8c);
  if (m_drResWrkClipList != nullptr) {
    m_drResWrkClipList->update(m_drMan->m_drCalcMan->m_drCalcClipMan);
  }
  if (m_drResMdoInstMdlInfo != nullptr) {
    DrResMdlInstMdlArg arg;
    arg.unknown00 = &m_drCalcViewWork->unknown400;
    arg.unknown10 = true;
    arg.unknown14 = unknown1a;
    arg.unknown08 = nullptr;
    arg.unknown18 = m_frameSpd;
    m_drResMdoInstMdlInfo->update(arg);
  }
}

bool DrMdoCtlPos::chankRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg) {
  DrCalcViewWork *viewWork = m_drCalcViewWork;
  f32 x = viewWork->unknown400.x - tree->unknown00[0];
  f32 y = viewWork->unknown400.y - tree->unknown00[1];
  f32 z = viewWork->unknown400.z - tree->unknown00[2];
  if (x * x + y * y + z * z > tree->unknown10) {
    return false;
  }
  if (!viewWork->m_drCalcClipWorkViewPlane.clipTest(*reinterpret_cast<const mm::Vec3 *>(tree->unknown00), tree->unknown0c)) {
    return false;
  }
  bool isRender = false;
  u32 count = tree->unknown1c;
  if (count != 0) {
    const u16 *child = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown1a8) + tree->unknown14);
    for (u32 i = 0; i < count; i++) {
      isRender |= chankRenderMdl(m_mdsPosRangeTreeData + *child++, arg);
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
    const MdsPosKeepData *keep = m_mdsPosKeepData + *index;
    if (keep->unknown66 != 0) {
      u32 *clipTbl = m_drResWrkClipList->unknown18;
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
      if (m_drResMdoInstAnmObj.unknown00 != nullptr) {
        objAlpha = m_drResMdoInstAnmObj.getObj(pos->unknown18)->m_alpha;
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
      chankShadowRenderMdl(m_mdsPosRangeTreeData + *child++, cache);
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
  if (m_drResMdoInstMdlInfo != nullptr) {
    DrResMdlInstMdlArg arg;
    m_drCalcViewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
    arg.unknown00 = &m_drCalcViewWork->unknown400;
    arg.unknown10 = false;
    arg.unknown14 = unknown1a;
    arg.unknown08 = nullptr;
    arg.unknown18 = m_frameSpd;
    m_drResMdoInstMdlInfo->update(arg);
  }
}

void DrMdoCtlPos::resourceInit() {
  setupResource(false);
  if (unknown30->unknownf0 != 0) {
    unknown30->m_drResMdoTexList = m_drMan->m_drMdlMan->m_drMdoTextureMan->createTextureObj(unknown30->unknown08);
    for (int i = 0; i < unknown30->m_drResMdoTexList->unknown68; i++) {
      unknown30->unknowne8[i] = unknown30->m_drResMdoTexList->getTexObj(i);
    }
  }
  m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->addShadowCacheUpdate(false);
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
    const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader + list.unknown0c;
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
    arg.m_mdsMdlInfoHeader = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
    if (renderType == 1 || renderType == 8 || renderType == 0x20) {
      arg.unknown10 = list.unknown00;
      for (s32 j = 0; j < infoCount; j++, arg.m_mdsMdlInfoHeader++) {
        // Same order for the material (0x7100817350, 0x7100817460): table pointer first, then the index; the subscript form changes the register of the table.
        if ((arg.m_mdsMdlInfoHeader->unknown04 & renderType) != 0 && (unknown30->m_materialRes + arg.m_mdsMdlInfoHeader->unknown0e)->unknown08.a > 0.0f) {
          if ((arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) == 0 && (arg.m_mdsMdlInfoHeader->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) == 0) {
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
        for (s32 j = 0; j < infoCount; j++, arg.m_mdsMdlInfoHeader++) {
          if ((arg.m_mdsMdlInfoHeader->unknown04 & renderType) != 0 && (unknown30->m_materialRes + arg.m_mdsMdlInfoHeader->unknown0e)->unknown08.a > 0.0f) {
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
    DrPixlOccQuery *query = m_drMan->m_drPixlMan->m_drPixlOccQuery;
    DrResOccUniformObj *uniform = m_drMan->m_drMdlMan->m_drResOccUniformObj;
    for (unknown020 *info = unknown2c0; info != nullptr; info = info->unknown18) {
      u32 index = info->unknown0c;
      const s16 *posNum = &unknown30->m_mdsMdlTopHeader[index].unknown28;
      for (int type = 1; type < 3; type++) {
        for (DrResMdoPos *pos = unknown270[type][index]; pos != nullptr; pos = pos->m_drResMdoPos) {
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
  DrPixlShadowObj *shadow = m_drMan->m_drPixlMan->m_drPixlShadowObj;
  if (!shadow->m_drLightObj->isInstMapShadow()) {
    return;
  }
  m_drCalcViewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  unknown001();
  unknown30->m_drResMdoVertex->beginVertexSetup();
  const unknown017 *header = unknown1a8;
  for (int i = 0; i < header->unknown2c; i++) {
    nomTreeShadowRenderMdl(&m_mdsPosRangeTreeData[i], shadow);
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
  if (unknown30->m_drResMdoVertex != nullptr) {
    unknown001();
    unknown30->m_drResMdoVertex->beginVertexSetup();
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
      chankShadowRenderMdl(&m_mdsPosRangeTreeData[i], cache);
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
  DrCalcViewWork *viewWork = m_drCalcViewWork;
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
      nomTreeShadowRenderMdl(m_mdsPosRangeTreeData + *child++, shadow);
    }
  }
  if (tree->unknown1e != 0) {
    nomTreeListShadowRenderMdl(tree, shadow);
  }
}

void DrMdoCtlPos::updateInstPosDispCall(const u32 *flags) {
  unknown703 *dispCall = unknown30->unknown130;
  if (dispCall != nullptr && dispCall->unknown00 > 0) {
    _MdoWrkDispCallTemp *temp = dispCall->m_mdoWrkDispCallTemp;
    const MdsMatDispCCData *data = dispCall->m_mdsMatDispCCData;
    for (s32 i = 0; i < dispCall->unknown00; i++, data++, temp++) {
      if ((flags[data->unknown04 >> 5] & (1 << (data->unknown04 & 31))) && checkCallBackParam(temp, data)) {
        unknown240[data->unknown04 >> 4] |= 1 << ((data->unknown04 & 0xf) << 1);
        unknown240[data->unknown04 >> 4] |= 1 << (((data->unknown04 & 0xf) << 1) | 1);
      }
    }
  }
}

void DrMdoCtlPos::createInstUniformBlock(const u32 *flags) {
  updateAnim(m_frameSpd * m_drMan->unknown1c8c, flags, nullptr);
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
