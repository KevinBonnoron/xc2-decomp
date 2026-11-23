#include "dr/dr_mdo_ctl_seam_base_map.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_setup.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace ml {
class DrResMdoAlpTbl;
class DrCalcClipMan;

f32 DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_DEN_CHECK = 100.0f;
f32 DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_IN_CHECK = 5.0f;

DrMdoCtlSeamBaseMap::DrMdoCtlSeamBaseMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

void DrMdoCtlSeamBaseMap::initBaseMapParts(DrResMdoSeamWrkBase *base) {
  const u8 *data = base->m_drResMdoSeamMemObj->m_buffer;
  const MdsSeamBaseMapHead *head = reinterpret_cast<const MdsSeamBaseMapHead *>(data);
  MdoWrkMatRes *matRes = nullptr;
  // Two calls, one per branch: the game's branches set their registers before one shared call (clang merges the identical calls); a conditional
  // argument gives another schedule (77 instructions instead of 98).
  if (head->unknown24 == 0) {
    initBaseMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, nullptr, data + head->unknown2c, nullptr, head->unknown20);
  } else {
    initBaseMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, data + head->unknown24, data + head->unknown2c, nullptr, head->unknown20);
  }
  unknown30 = matRes;
  if (head->unknown14 != 0) {
    setupFixAnim(data + head->unknown14);
  }
  const unknown700 *table = reinterpret_cast<const unknown700 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown1c);
  // The game sign-extends the index of the entry (ldrsw, 0x710081fce8) and shifts the same member unsigned for the bit table below.
  unknownc40 += table[static_cast<s32>(base->unknown84)].unknown38;
  base->setupWork(matRes, unknownb28, m_drMan->unknown14, this, head, 500);
  unknownb50[base->unknown84 >> 5] |= 1 << (base->unknown84 & 0x1f);
  unknownc00++;
  if (unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->callSelectShadowCacheUpdate(0xffffffffffffffff);
  }
  unknownc90 = 0;
}

void DrMdoCtlSeamBaseMap::changeMemBaseMapParts(DrResMdoSeamWrkBase *base) {
  const u8 *data = base->m_drResMdoSeamMemObj->m_buffer;
  const MdsSeamBaseMapHead *head = reinterpret_cast<const MdsSeamBaseMapHead *>(data);
  MdoWrkMatRes *matRes = base->m_mdoWrkMatRes;
  if (head->unknown24 == 0) {
    resetBaseMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, nullptr, data + head->unknown2c, nullptr, head->unknown20);
  } else {
    resetBaseMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, data + head->unknown24, data + head->unknown2c, nullptr, head->unknown20);
  }
  if (head->unknown14 != 0) {
    changeMemFixAnim(matRes, data + head->unknown14);
  }
}

void DrMdoCtlSeamBaseMap::releaseBaseMap() {
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr) {
    DrResMdoSeamWrkBase *next = base->unknown08;
    releaseFreeSeamBase(base);
    base = next;
  }
  unknownc40 = 0;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::seachBaseIdx(int index) {
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr && (base->m_mdoWrkMatRes == nullptr || base->unknown84 != index)) {
    base = base->unknown08;
  }
  return base;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::createFreeSeamBase() { return unknown290.unknown001(); }

void DrMdoCtlSeamBaseMap::releaseFreeSeamBase(DrResMdoSeamWrkBase *base) {
  DrResMdoSeamMemObj *mem = nullptr;
  if (base->m_mdoWrkMatRes != nullptr) {
    mem = base->m_drResMdoSeamMemObj;
    unknownb50[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    m_drResBitTbl.unknown00[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    unknownc40 -= base->unknownb4;
    releaseBaseMapSeamMat(base->m_mdoWrkMatRes);
    base->releaseCache(this);
    unknownc00--;
  }
  unknown290.unknown002(base);
  if (mem != nullptr) {
    base->m_drResMdoSeamMemObj = nullptr;
    m_drResMdoSeamMemMan.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamBaseMap::createBaseZPrePassDisplayList() {
  if (!(unknownc7c & 2) || m_drMan->unknown1d69) {
    return;
  }
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 == nullptr || !(base->unknowna0 & 8)) {
      continue;
    }
    s32 count = base->unknown130[1][0];
    if (count == 0) {
      continue;
    }
    DrResMdoAlpTbl *alpTbl = base->m_drResMdoAlpTbl;
    base->beginRender();
    changeSeamMatInfo();
    for (s32 i = 0; i < count; i++) {
      for (unknown504 *entry = base->unknown110[1][i]; entry != nullptr; entry = &base->unknown150[entry->unknown04 - 1]) {
        base->selectVertex(entry->unknown06);
        const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
        if (!(header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15)) {
          partsZPrePassRender(header, 0, 0, alpTbl, entry->unknown08);
        }
        if (entry->unknown04 == 0) {
          break;
        }
      }
    }
    base->endRender();
  }
}

void DrMdoCtlSeamBaseMap::callRenderSeamBaseMap() { renderSeamBaseMap(0); }

void DrMdoCtlSeamBaseMap::callGBuffRenderSeamBaseMap() { renderSeamBaseMap(1); }

void DrMdoCtlSeamBaseMap::callLightPrePassRenderSeamBaseMap() { renderSeamBaseMap(3); }

void DrMdoCtlSeamBaseMap::callRefractionRenderSeamBaseMap() { renderSeamBaseMap(2); }

void DrMdoCtlSeamBaseMap::callAlphaRenderSeamBaseMap() { renderSeamBaseMap(4); }

void DrMdoCtlSeamBaseMap::callSpAlphaRenderSeamBaseMap() { renderSeamBaseMap(5); }

// Measured forms (1.0.0: 0x710082166c, 301 instructions). The material count times the render type is computed once per base, after the reset of the render state (0x7100821714:
// ldrsw, mul of the two sign extended values): written in the index of the loops, clang folds it to 0 in the loop where the render type is known to be 0 and keeps a 32 bit induction
// variable in the others (288 instructions); with the local the game's two sxtw of renderType (0x71008216b8, 0x71008216c0) come out. The game tests the render types 2 to 5 with a bit
// mask computed before the loops (0x71008216b4, 0x71008216c4: lsl, and #0x3c); `renderType == 2 || ... || renderType == 5` and a switch give a range test (sub, cmp #4; 295 instructions).
// The count is read in each arm of the test: read before the test, the first sxtw is hoisted above the mask (301 instructions, prologue differs). The state reset is changeSeamMatInfo
// (two strh of a hoisted constant); the stores written out give one str w, or the strh pair after the byte stores. The two loops of the arms repeat the depth block and the entry walk (the
// game's code has both copies, as the two arms of the test are two loops): one loop with the test of the bit mask inside it is not unswitched by clang 3.9 (192 instructions against 301).
void DrMdoCtlSeamBaseMap::renderSeamBaseMap(int renderType) {
  if (m_drMan->unknown1d69) {
    return;
  }
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 == nullptr) {
      continue;
    }
    base->beginRender();
    changeSeamMatInfo();
    int offset = unknown30->unknown30 * renderType;
    for (int kind = 0; kind < 2; kind++) {
      if ((1 << renderType) & 0x3c) {
        int count = base->unknown130[kind][renderType];
        for (int i = 0; i < count; i++) {
          unknown504 *entry = base->unknown110[kind][i + offset];
          const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
          if ((unknown30->m_materialRes + header->unknown0e)->unknown08.a > 0.0f) {
            const MdsMatInfoHeader *mat = unknown30->unknown28 + header->unknown0e;
            base->selectVertex(entry->unknown06);
            partsMaterialSetup(header);
            if (renderType == 0 && kind == 1 && (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_14)) {
              MdoWrkMatSetupArg arg;
              getSetupMaterial(arg, mat, 1);
              DrAPCache *apCache = m_drMan->m_drAPCache;
              apCache->depthBegin();
              apCache->setupDepthStencil(arg.unknown14, arg.unknown10, 0, 3);
            }
            while (entry != nullptr) {
              base->selectVertex(entry->unknown06);
              unknown30->m_drResMdoVertex->setVertexBind(header->unknown08);
              unknown30->m_drResMdoVertex->render(header->unknown0a);
              if (entry->unknown04 == 0) {
                break;
              }
              entry = &base->unknown150[entry->unknown04 - 1];
              header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
            }
          }
        }
      } else {
        int count = base->unknown130[kind][renderType];
        for (int i = 0; i < count; i++) {
          unknown504 *entry = base->unknown110[kind][i + offset];
          const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
          const MdsMatInfoHeader *mat = unknown30->unknown28 + header->unknown0e;
          base->selectVertex(entry->unknown06);
          partsMaterialSetup(header);
          if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_4) {
            createBaseBillMate(mat, header->unknown14);
          }
          if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_2) {
            createOccMate(mat, header->unknown12);
          }
          if (renderType == 0 && kind == 1 && (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_14)) {
            MdoWrkMatSetupArg arg;
            getSetupMaterial(arg, mat, 1);
            DrAPCache *apCache = m_drMan->m_drAPCache;
            apCache->depthBegin();
            apCache->setupDepthStencil(arg.unknown14, arg.unknown10, 0, 3);
          }
          while (entry != nullptr) {
            base->selectVertex(entry->unknown06);
            unknown30->m_drResMdoVertex->setVertexBind(header->unknown08);
            unknown30->m_drResMdoVertex->render(header->unknown0a);
            if (entry->unknown04 == 0) {
              break;
            }
            entry = &base->unknown150[entry->unknown04 - 1];
            header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
          }
        }
      }
    }
    base->endRender();
  }
}

void DrMdoCtlSeamBaseMap::createBaseThicknesPassDisplayList(bool isFirst) {
  if (m_drMan->unknown1d69) {
    return;
  }
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 == nullptr || !(base->unknowna0 & 8)) {
      continue;
    }
    s32 count = base->unknown130[1][7];
    if (count == 0) {
      continue;
    }
    DrResMdoAlpTbl *alpTbl = base->m_drResMdoAlpTbl;
    base->beginRender();
    changeSeamMatInfo();
    // The game reads the material count once before the loop (0x710081e344: ldrsw x8,[x8,#0x30]), so the kind offset is a 64-bit product.
    s32 matNum = unknown30->unknown30;
    for (s32 i = 0; i < count; i++) {
      for (unknown504 *entry = base->unknown110[1][i + matNum * 7]; entry != nullptr; entry = &base->unknown150[entry->unknown04 - 1]) {
        base->selectVertex(entry->unknown06);
        const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
        if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) {
          partsThicknessRender(header, 0, 0, alpTbl, entry->unknown08, isFirst);
        }
        if (entry->unknown04 == 0) {
          break;
        }
      }
    }
    base->endRender();
  }
}

void DrMdoCtlSeamBaseMap::createBaseMapDisplayList() {}

void DrMdoCtlSeamBaseMap::updateBaseMap() {
  readBaseMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateBaseMapRenderList();
  }
}

// The game inlines DrMdoMat::updateMatFstCallBack and DrMdoSetup::updateUniformBlock here (as in DrMdoCtlSeamInstMap::updateInstMapRenderList). The counter pair at 0xca0 is unsigned:
// the game reads it as one word (ldr w at 0x71008211d8), tests `and w10, w9, #0xffff; cmp w10, #2; b.lo` (0x71008211e0) and shifts the second counter with lsr (0x71008211f4); with s16
// members the same code reads sxth and tests b.lt (189 instructions).
void DrMdoCtlSeamBaseMap::updateBaseMapRenderList() {
  DrCalcViewWork *view = m_drMan->m_drCalcMan->m_drCalcViewWork;
  DrCalcClipMan *clip = m_drMan->m_drCalcMan->m_drCalcClipMan;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 == nullptr) {
      continue;
    }
    u32 flags = base->updateRenderList(view,
                                       clip,
                                       unknownbe0,
                                       unknown1b0.unknown20,
                                       unknownbf0,
                                       unknown1e8.unknown20,
                                       this,
                                       reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c),
                                       unknownc7c);
    if (flags == 0) {
      m_drResBitTbl.unknown00[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    } else {
      m_drResBitTbl.unknown00[base->unknown84 >> 5] |= 1 << (base->unknown84 & 0x1f);
      unknownf8 |= flags;
      updateMatFstCallBack();
      updateMatCallBack(base->unknownc0);
      updateAnim(m_frameSpd * m_drMan->unknown1c8c, base->unknownc0, nullptr);
      updateBillTbl();
      updateTimerCalc(base->unknownc0);
      updateUniformBlock(base->unknownc0);
      if (m_drMan->unknown1cc2) {
        unknownc7c |= 3;
      }
    }
    unknownc70 += base->unknown90;
    unknownc74 += base->unknown94;
  }
  unknownca0++;
  if (unknownca0 < 2) {
    return;
  }
  if ((unknownc90 & (1ull << unknownca2)) == 0 && unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->callSelectShadowCacheUpdate(1ull << unknownca2);
  }
  unknownca2++;
  if (unknownca2 >= 0x24) {
    unknownca2 = 0;
  }
  unknownca0 = 0;
}

void DrMdoCtlSeamBaseMap::readBaseMapCheck() {
  if (m_drResMdoSeamParmRead.unknown40 == 0 && (unknownc7c & 0x40) == 0) {
    if ((unknownc7c & 0x80) == 0) {
      DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK = m_drMan->unknown1d00 + 100.0f;
    } else {
      DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK = SEAM_BASEMAP_READ_DEN_CHECK + 50.0f;
    }
    DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = SEAM_BASEMAP_READ_IN_CHECK + 5.0f;
  } else {
    DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK = ((unknownc7c & 0x80) == 0 ? m_drMan->unknown1d00 : SEAM_BASEMAP_READ_DEN_CHECK) + 0.5f;
    DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = SEAM_BASEMAP_READ_IN_CHECK + 0.5f;
  }
  DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_CHECK = m_drMan->unknown1d04;
  DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_MIDDLE = m_drMan->unknown1d08;
  DrCalcViewWork *view = m_drMan->m_drCalcMan->m_drCalcViewWork;
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr) {
    bool isRelease = base->update(view, &m_drResMdoSeamParmRead, isOpen, unknownc7c);
    if (base->unknowna0 & 0x80) {
      changeMemBaseMapParts(base);
    }
    DrResMdoSeamWrkBase *next = base->unknown08;
    if (isRelease) {
      releaseFreeSeamBase(base);
    }
    base = next;
  }
  if ((unknownc7c & 0x80200) == 0) {
    basemapReadCheck();
  }
}

bool DrMdoCtlSeamBaseMap::readBaseModelCheck(bool &isRead, const mm::Vec3 &position, bool isFirst) {
  isRead = false;
  f32 margin = (unknownc7c & 0x80) == 0 ? m_drMan->unknown1d00 : SEAM_BASEMAP_READ_DEN_CHECK;
  s32 max = unknown1a8->m_seamBaseMdlMax;
  const unknown700 *entry = reinterpret_cast<const unknown700 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown1c);
  bool isEmpty = true;
  // Same form as readMpfModelCheck (ruling 7): unknownb50 is tested with `static_cast<u32>(i) >> 5` (lsr from the signed counter); the shared word helper
  // unknown723 loads the table before the index (0x71008214c0: ldr x9 instead of the game's ldr x10) and does not match.
  for (s32 i = 0; i < max; i++, entry++) {
    if ((unknownb50[static_cast<u32>(i) >> 5] & (1 << (i & 0x1f))) != 0) {
      continue;
    }
    if (entry->unknown00[0] + margin < position.x || entry->unknown0c[0] - margin > position.x || entry->unknown00[1] + margin < position.y || entry->unknown0c[1] - margin > position.y ||
        entry->unknown00[2] + margin < position.z || entry->unknown0c[2] - margin > position.z) {
      continue;
    }
    if (isFirst && (((unknownc7c & 0x10) != 0 && (entry->unknown28 & 8) != 0) || ((unknownc7c & 0x100) != 0 && (entry->unknown28 & 4) != 0))) {
      continue;
    }
    m_drResMdoSeamParmRead.setStockBaseMap(i);
    isEmpty = false;
    isRead = true;
  }
  return isEmpty;
}

void DrMdoCtlSeamBaseMap::callShadowCacheBaseUpdate(u64 flags) {
  unknownc90 &= ~flags;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    if (base->m_mdoWrkMatRes != nullptr) {
      base->callShadowCacheBaseUpdate(flags);
    }
  }
}

void DrMdoCtlSeamBaseMap::callShadowMapRenderSeamBaseMap(DrPixlShadowObj *shadow) {
  if (m_drMan->unknown1d69) {
    return;
  }
  DrCalcViewWork *view = m_drMan->m_drCalcMan->m_drCalcViewWork;
  grlib::CGLibEtcUniformBlock uniform;
  grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), view->unknown40);
  uniform.updateData(sizeof(mm::Mat44));
  unknown170 = &uniform;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 != nullptr && (base->unknowna0 & 8) != 0) {
      changeSeamMatInfo();
      base->seachDefShadowBaseMapRender(shadow, this);
    }
  }
}

void DrMdoCtlSeamBaseMap::callBaseShadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknownc90 & cache.unknown8e8) != 0 || m_drMan->unknown1d69) {
    return;
  }
  bool isRetry = false;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->m_mdoWrkMatRes;
    if (unknown30 != nullptr) {
      if (base->unknowna0 & 8) {
        changeSeamMatInfo();
        changeShader(true);
        isRetry |= base->seachShadowBaseMapRender(cache, this);
      } else {
        isRetry = true;
      }
    }
  }
  if (isRetry) {
    unknownc90 &= ~cache.unknown8e8;
  } else {
    unknownc90 |= cache.unknown8e8;
  }
}

void DrMdoCtlSeamBaseMap::checkBaseMapMode() {
  const unknown700 *entry = reinterpret_cast<const unknown700 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown1c);
  for (s32 i = 0; i < unknown1a8->m_seamBaseMdlMax; i++, entry++) {
    if (entry->unknown28 & 1) {
      if (entry->unknown00[0] >= m_drResMdoSeamParmRead.unknown50.x && entry->unknown0c[0] <= m_drResMdoSeamParmRead.unknown50.x && entry->unknown00[2] >= m_drResMdoSeamParmRead.unknown50.z &&
          entry->unknown0c[2] <= m_drResMdoSeamParmRead.unknown50.z && entry->unknown00[1] + 500.0f >= m_drResMdoSeamParmRead.unknown50.y &&
          entry->unknown0c[1] - 400.0f <= m_drResMdoSeamParmRead.unknown50.y) {
        unknownc7c |= 0x80;
        unknownc22 = 0;
        if (entry->unknown00[0] - m_drResMdoSeamParmRead.unknown50.x >= 160.0f && entry->unknown00[2] - m_drResMdoSeamParmRead.unknown50.z >= 160.0f &&
            m_drResMdoSeamParmRead.unknown50.x - entry->unknown0c[0] >= 160.0f && m_drResMdoSeamParmRead.unknown50.z - entry->unknown0c[2] >= 160.0f &&
            entry->unknown00[1] + 350.0f >= m_drResMdoSeamParmRead.unknown50.y) {
          unknownc7c |= 0x100;
          unknownc24 = 0;
        }
      }
      return;
    }
  }
}

void DrMdoCtlSeamBaseMap::basemapReadCheck() {
  bool isRead = false;
  if (unknownc00 < 5 && (unknownc7c & 0x1000) == 0 && readBaseModelCheck(isRead, m_drResMdoSeamParmRead.unknown50, true) && m_drResMdoSeamParmRead.unknown40 > 0) {
    for (s32 i = 0; i < m_drResMdoSeamParmRead.unknown40; i++) {
      if (!readBaseModelCheck(isRead, m_drResMdoSeamParmRead.unknown10[i], false)) {
        return;
      }
    }
  }
}

} // namespace ml
