#include "dr/dr_mdo_ctl_seam_base_map.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class DrResMdoSeamMemObj;

DrMdoCtlSeamBaseMap::DrMdoCtlSeamBaseMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

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

void DrMdoCtlSeamBaseMap::callRenderSeamBaseMap() { renderSeamBaseMap(0); }

void DrMdoCtlSeamBaseMap::callGBuffRenderSeamBaseMap() { renderSeamBaseMap(1); }

void DrMdoCtlSeamBaseMap::callLightPrePassRenderSeamBaseMap() { renderSeamBaseMap(3); }

void DrMdoCtlSeamBaseMap::callRefractionRenderSeamBaseMap() { renderSeamBaseMap(2); }

void DrMdoCtlSeamBaseMap::callAlphaRenderSeamBaseMap() { renderSeamBaseMap(4); }

void DrMdoCtlSeamBaseMap::callSpAlphaRenderSeamBaseMap() { renderSeamBaseMap(5); }

void DrMdoCtlSeamBaseMap::createBaseMapDisplayList() {}

void DrMdoCtlSeamBaseMap::updateBaseMap() {
  readBaseMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateBaseMapRenderList();
  }
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
