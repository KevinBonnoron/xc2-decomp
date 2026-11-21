#include "dr/dr_mdo_ctl_seam_low_map.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "dr/dr_res_mdo_seam_wrk_low.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class DrResMdoAlpTbl;

DrMdoCtlSeamLowMap::DrMdoCtlSeamLowMap(int viewNum) : DrMdoCtlSeamBaseMap(viewNum) {}

void DrMdoCtlSeamLowMap::initLowMapParts(DrResMdoSeamWrkLow *low) {
  const u8 *data = low->unknown30->m_buffer;
  const MdsSeamLowMapHead *head = reinterpret_cast<const MdsSeamLowMapHead *>(data);
  MdoWrkMatRes *matRes = nullptr;
  initBaseMapMaterial(matRes, data + head->unknown0c, data + head->unknown08, data + head->unknown18, data + head->unknown20, data + head->unknown1c, 0);
  unknown30 = matRes;
  if (head->unknown10 != 0) {
    setupFixAnim(data + head->unknown10);
  }
  const MdsSeamLowData *table = reinterpret_cast<const MdsSeamLowData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownbc);
  // The game sign-extends the index of the entry (ldrsw, 0x71008249ec) and shifts the same member unsigned for the bit table below.
  const MdsSeamLowData *entry = &table[static_cast<s32>(low->unknowna0)];
  unknownc44 += entry->unknown2c;
  low->setupWork(matRes, unknownb28, m_drMan->unknown14, head, entry, 500);
  unknownb70[low->unknowna0 >> 5] |= 1 << (low->unknowna0 & 0x1f);
  unknownc02++;
}

void DrMdoCtlSeamLowMap::changeMemLowMapParts(DrResMdoSeamWrkLow *low) {
  MdoWrkMatRes *matRes = low->unknown28;
  const u8 *data = low->unknown30->m_buffer;
  const MdsSeamLowMapHead *head = reinterpret_cast<const MdsSeamLowMapHead *>(data);
  resetBaseMapMaterial(matRes, data + head->unknown0c, data + head->unknown08, data + head->unknown18, data + head->unknown20, data + head->unknown1c, 0);
  if (head->unknown10 != 0) {
    changeMemFixAnim(matRes, data + head->unknown10);
  }
}

void DrMdoCtlSeamLowMap::releaseLowMap() {
  DrResMdoSeamWrkLow *low = unknown2c8.unknown10.unknown00;
  while (low != nullptr) {
    DrResMdoSeamWrkLow *next = low->unknown08;
    releaseFreeSeamLow(low);
    low = next;
  }
  unknownc44 = 0;
}

void DrMdoCtlSeamLowMap::readLowMapCheck() {
  if ((unknownc7c & 0x80) == 0) {
    if (unknownd30.unknown40 == 0 && (unknownc7c & 0x40) == 0) {
      DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = m_drMan->unknown1d0c + 100.0f;
    } else {
      DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = m_drMan->unknown1d0c + 0.5f;
    }
  } else if (unknownd30.unknown40 == 0 && (unknownc7c & 0x40) == 0) {
    DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = 250.0f;
  } else {
    DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = 200.5f;
  }
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkLow *low = unknown2c8.unknown10.unknown00;
  while (low != nullptr) {
    bool isRelease = low->update(view, view->unknown400, m_drMan->m_gblIdx, isOpen);
    if (low->unknown9c & 0x10) {
      changeMemLowMapParts(low);
    }
    DrResMdoSeamWrkLow *next = low->unknown08;
    if (isRelease) {
      releaseFreeSeamLow(low);
    }
    low = next;
  }
  if ((unknownc7c & 0x81200) == 0 && unknownc02 < 8) {
    f32 margin = (unknownc7c & 0x80) == 0 ? m_drMan->unknown1d0c : 200.0f;
    const MdsSeamLowData *entry = reinterpret_cast<const MdsSeamLowData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownbc);
    s32 max = unknown1a8->unknownb8;
    // Same forms as readMpfModelCheck (decision 2026-11-14, rulings 7 and 8). unknownb70 is tested with `static_cast<u32>(i) >> 5` (lsr from the signed
    // counter): the shared word helper unknown723 loads the table before the index and swaps x8/x9 (0x7100824e64). The bit test of DrMan::isGblIdx is
    // written out: the game loads m_gblIdx once before the loop (x24 at 0x7100824e4c), while `m_drMan->isGblIdx(entry->unknown30)` reloads it in the
    // loop (173 instructions against the game's 172, first difference at 0x7100824e14).
    const u32 *gblIdx = m_drMan->m_gblIdx;
    for (s32 i = 0; i < max; i++, entry++) {
      if ((unknownb70[static_cast<u32>(i) >> 5] & (1 << (i & 0x1f))) != 0) {
        continue;
      }
      if (entry->unknown30 != 0 && (gblIdx[entry->unknown30 >> 5] & (1 << (entry->unknown30 & 0x1f))) != 0) {
        continue;
      }
      if (entry->unknown00[0] + margin < view->unknown400.x || entry->unknown0c[0] - margin > view->unknown400.x || entry->unknown00[1] + margin < view->unknown400.y ||
          entry->unknown0c[1] - margin > view->unknown400.y || entry->unknown00[2] + margin < view->unknown400.z || entry->unknown0c[2] - margin > view->unknown400.z) {
        continue;
      }
      unknownd30.setStockLowMdl(i);
    }
  }
}

DrResMdoSeamWrkLow *DrMdoCtlSeamLowMap::createFreeSeamLow() { return unknown2c8.unknown001(); }

void DrMdoCtlSeamLowMap::releaseFreeSeamLow(DrResMdoSeamWrkLow *low) {
  DrResMdoSeamMemObj *mem = low->unknown30;
  if (low->unknown28 != nullptr) {
    unknownb70[low->unknowna0 >> 5] &= ~(1 << (low->unknowna0 & 0x1f));
    unknownc44 -= low->unknownb0;
    releaseBaseMapSeamMat(low->unknown28);
    low->release();
    unknownc02--;
  }
  unknown2c8.unknown002(low);
  if (mem != nullptr) {
    low->unknown30 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamLowMap::createLowZPrePassDisplayList() {
  unknownf8 &= ~0x40000000;
  for (DrResMdoSeamWrkLow *low = unknown2c8.unknown10.unknown00; low != nullptr; low = low->unknown08) {
    unknown30 = low->unknown28;
    if (unknown30 == nullptr || !(low->unknown9c & 4)) {
      continue;
    }
    s32 count = low->unknown78[0];
    if (count == 0) {
      continue;
    }
    changeSeamBaseMapMdlInfo();
    DrResMdoAlpTbl *alpTbl = low->unknown40;
    for (s32 i = 0; i < count; i++) {
      for (unknown504 *entry = low->unknown58[i]; entry != nullptr; entry = &low->unknown38[entry->unknown04 - 1]) {
        const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
        if (entry->unknown0a & 2) {
          unknownf8 |= 0x20000000;
        } else {
          unknownf8 &= ~0x20000000;
        }
        partsZPrePassRender(header, 0, 0, alpTbl, entry->unknown08);
        if (entry->unknown04 == 0) {
          break;
        }
      }
    }
  }
}

void DrMdoCtlSeamLowMap::callRenderSeamLowMap() { renderSeamLowMap(0); }

void DrMdoCtlSeamLowMap::callGBuffRenderSeamLowMap() { renderSeamLowMap(1); }

void DrMdoCtlSeamLowMap::callLightPrePassRenderSeamLowMap() { renderSeamLowMap(3); }

void DrMdoCtlSeamLowMap::callRefractionRenderSeamLowMap() { renderSeamLowMap(2); }

void DrMdoCtlSeamLowMap::callAlphaRenderSeamLowMap() { renderSeamLowMap(4); }

void DrMdoCtlSeamLowMap::callSpAlphaRenderSeamLowMap() { renderSeamLowMap(5); }

void DrMdoCtlSeamLowMap::createLowDisplayList() {}

void DrMdoCtlSeamLowMap::updateLowMap() {
  readLowMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateLowMapRenderList();
  }
}

} // namespace ml
