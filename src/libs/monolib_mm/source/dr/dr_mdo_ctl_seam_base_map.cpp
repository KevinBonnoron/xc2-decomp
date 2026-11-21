#include "dr/dr_mdo_ctl_seam_base_map.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace ml {
class DrResMdoAlpTbl;

f32 DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_DEN_CHECK = 100.0f;
f32 DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_IN_CHECK = 5.0f;

DrMdoCtlSeamBaseMap::DrMdoCtlSeamBaseMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

void DrMdoCtlSeamBaseMap::initBaseMapParts(DrResMdoSeamWrkBase *base) {
  const u8 *data = base->unknown158->m_buffer;
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
    m_drMan->unknown78->unknown800->callSelectShadowCacheUpdate(0xffffffffffffffff);
  }
  unknownc90 = 0;
}

void DrMdoCtlSeamBaseMap::changeMemBaseMapParts(DrResMdoSeamWrkBase *base) {
  const u8 *data = base->unknown158->m_buffer;
  const MdsSeamBaseMapHead *head = reinterpret_cast<const MdsSeamBaseMapHead *>(data);
  MdoWrkMatRes *matRes = base->unknown68;
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
  while (base != nullptr && (base->unknown68 == nullptr || base->unknown84 != index)) {
    base = base->unknown08;
  }
  return base;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::createFreeSeamBase() { return unknown290.unknown001(); }

void DrMdoCtlSeamBaseMap::releaseFreeSeamBase(DrResMdoSeamWrkBase *base) {
  DrResMdoSeamMemObj *mem = nullptr;
  if (base->unknown68 != nullptr) {
    mem = base->unknown158;
    unknownb50[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    unknownb60.unknown00[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    unknownc40 -= base->unknownb4;
    releaseBaseMapSeamMat(base->unknown68);
    base->releaseCache(this);
    unknownc00--;
  }
  unknown290.unknown002(base);
  if (mem != nullptr) {
    base->unknown158 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamBaseMap::createBaseZPrePassDisplayList() {
  if (!(unknownc7c & 2) || m_drMan->unknown1d69) {
    return;
  }
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->unknown68;
    if (unknown30 == nullptr || !(base->unknowna0 & 8)) {
      continue;
    }
    s32 count = base->unknown138[0];
    if (count == 0) {
      continue;
    }
    DrResMdoAlpTbl *alpTbl = base->unknown168;
    base->beginRender();
    changeSeamMatInfo();
    for (s32 i = 0; i < count; i++) {
      for (unknown504 *entry = base->unknown118[i]; entry != nullptr; entry = &base->unknown150[entry->unknown04 - 1]) {
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

void DrMdoCtlSeamBaseMap::createBaseThicknesPassDisplayList(bool isFirst) {
  if (m_drMan->unknown1d69) {
    return;
  }
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->unknown68;
    if (unknown30 == nullptr || !(base->unknowna0 & 8)) {
      continue;
    }
    s32 count = base->unknown138[7];
    if (count == 0) {
      continue;
    }
    DrResMdoAlpTbl *alpTbl = base->unknown168;
    base->beginRender();
    changeSeamMatInfo();
    // The game reads the material count once before the loop (0x710081e344: ldrsw x8,[x8,#0x30]), so the kind offset is a 64-bit product.
    s32 matNum = unknown30->unknown30;
    for (s32 i = 0; i < count; i++) {
      for (unknown504 *entry = base->unknown118[i + matNum * 7]; entry != nullptr; entry = &base->unknown150[entry->unknown04 - 1]) {
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

void DrMdoCtlSeamBaseMap::readBaseMapCheck() {
  if (unknownd30.unknown40 == 0 && (unknownc7c & 0x40) == 0) {
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
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr) {
    bool isRelease = base->update(view, &unknownd30, isOpen, unknownc7c);
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
    unknownd30.setStockBaseMap(i);
    isEmpty = false;
    isRead = true;
  }
  return isEmpty;
}

void DrMdoCtlSeamBaseMap::callShadowCacheBaseUpdate(u64 flags) {
  unknownc90 &= ~flags;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    if (base->unknown68 != nullptr) {
      base->callShadowCacheBaseUpdate(flags);
    }
  }
}

void DrMdoCtlSeamBaseMap::callShadowMapRenderSeamBaseMap(DrPixlShadowObj *shadow) {
  if (m_drMan->unknown1d69) {
    return;
  }
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  grlib::CGLibEtcUniformBlock uniform;
  grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), view->unknown40);
  uniform.updateData(sizeof(mm::Mat44));
  unknown170 = &uniform;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->unknown68;
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
    unknown30 = base->unknown68;
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
      if (entry->unknown00[0] >= unknownd30.unknown50.x && entry->unknown0c[0] <= unknownd30.unknown50.x && entry->unknown00[2] >= unknownd30.unknown50.z &&
          entry->unknown0c[2] <= unknownd30.unknown50.z && entry->unknown00[1] + 500.0f >= unknownd30.unknown50.y && entry->unknown0c[1] - 400.0f <= unknownd30.unknown50.y) {
        unknownc7c |= 0x80;
        unknownc22 = 0;
        if (entry->unknown00[0] - unknownd30.unknown50.x >= 160.0f && entry->unknown00[2] - unknownd30.unknown50.z >= 160.0f && unknownd30.unknown50.x - entry->unknown0c[0] >= 160.0f &&
            unknownd30.unknown50.z - entry->unknown0c[2] >= 160.0f && entry->unknown00[1] + 350.0f >= unknownd30.unknown50.y) {
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
  if (unknownc00 < 5 && (unknownc7c & 0x1000) == 0 && readBaseModelCheck(isRead, unknownd30.unknown50, true) && unknownd30.unknown40 > 0) {
    for (s32 i = 0; i < unknownd30.unknown40; i++) {
      if (!readBaseModelCheck(isRead, unknownd30.unknown10[i], false)) {
        return;
      }
    }
  }
}

} // namespace ml
