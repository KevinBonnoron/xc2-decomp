#include "dr/dr_mdo_ctl_seam_mpf_map.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_mpf_work.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_mpf.h"
#include "dr/dr_res_mdo_vertex.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
class DrCalcViewWork;

DrMdoCtlSeamMpfMap::DrMdoCtlSeamMpfMap(int viewNum) : DrMdoCtlSeamInstMap(viewNum) {}

void DrMdoCtlSeamMpfMap::releaseMpfMap() {
  DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00;
  while (mpf != nullptr) {
    DrResMdoSeamWrkMpf *next = mpf->unknown08;
    releaseFreeSeamMpf(mpf);
    mpf = next;
  }
  unknownc40 = 0;
}

void DrMdoCtlSeamMpfMap::createMpfZPrePassDisplayList() {
  if (((unknownc7c >> 3) & 1) == 0 || m_drMan->unknown1d6b) {
    return;
  }
  DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00;
  grlib::CGLibVtxInstans *instans = m_drMan->unknown88->unknown008->unknown10;
  m_drMan->unknown5c0->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
  for (; mpf != nullptr; mpf = mpf->unknown08) {
    unknown30 = mpf->unknown70;
    if (unknown30 != nullptr && mpf->unknown4e != 0) {
      int count = mpf->unknown52;
      DrMdoCtlMpfWork *work = mpf->unknownc0;
      for (int i = 0; i < count; i++) {
        if (work->unknown20[i].unknown20 != 0) {
          const MdsMdlTopHeader *entry = &unknown30->unknown168[i];
          const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
          int num = entry->unknown04;
          for (int j = 0; j < num; j++, header++) {
            mpfZPrePassRender(i, header, work, instans);
          }
        }
      }
    }
  }
}

void DrMdoCtlSeamMpfMap::initMpfMapParts(DrResMdoSeamWrkMpf *mpf) {
  const u8 *data = mpf->unknown18->m_buffer;
  const MdsSeamMpfMapHead *head = reinterpret_cast<const MdsSeamMpfMapHead *>(data);
  initMpfMaterial(data + head->unknown04, data + head->unknown0c, data + head->unknown00, data + head->unknown10, true);
  MdoWrkMatRes *matRes = unknown30;
  const unknown722 *table = reinterpret_cast<const unknown722 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown68);
  unknownc4c += table[mpf->unknown4c].unknown38;
  unknownb90[mpf->unknown4c >> 5] |= 1 << (mpf->unknown4c & 0x1f);
  unknownc06++;
  mpf->setupWork(matRes, m_drMan->unknown14, head, m_drMan->unknown88->unknown020);
}

void DrMdoCtlSeamMpfMap::changeMemMpfMapParts(DrResMdoSeamWrkMpf *mpf) {
  const u8 *data = mpf->unknown18->m_buffer;
  const MdsSeamMpfMapHead *head = reinterpret_cast<const MdsSeamMpfMapHead *>(data);
  resetMpfMaterial(mpf->unknown70, data + head->unknown04, data + head->unknown0c, data + head->unknown00, data + head->unknown10);
}

void DrMdoCtlSeamMpfMap::createAllpfMapDisplayList() {}

void DrMdoCtlSeamMpfMap::renderMpfMapDisplayList() { createMpfMapDisplayList(); }

void DrMdoCtlSeamMpfMap::releaseFreeSeamMpf(DrResMdoSeamWrkMpf *mpf) {
  DrResMdoSeamMemObj *mem = mpf->unknown18;
  if (mpf->unknown70 != nullptr) {
    unknownb90[mpf->unknown4c >> 5] &= ~(1 << (mpf->unknown4c & 0x1f));
    unknownc4c -= mpf->unknowne8;
    releaseMpfMapSeamMat(mpf->unknown70);
    mpf->releaseCache(this);
    unknownc06--;
  }
  unknown338.unknown002(mpf);
  if (mem != nullptr) {
    mpf->unknown18 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamMpfMap::updateMpfMap() {
  readMpfMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateMpfMapRenderList();
  }
}

void DrMdoCtlSeamMpfMap::readMpfMapCheck() {
  if (unknownd30.unknown40 != 0) {
    DrResMdoSeamWrkMpf::SEAM_MPFMAP_READ_CHECK = 40.5f;
  } else {
    DrResMdoSeamWrkMpf::SEAM_MPFMAP_READ_CHECK = (unknownc7c & 0x40) == 0 ? 60.0f : 40.5f;
  }
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00;
  while (mpf != nullptr) {
    bool isRelease = mpf->update(&unknownd30, isOpen, unknownc7c);
    if (mpf->unknown5c & 0x10) {
      changeMemMpfMapParts(mpf);
    }
    DrResMdoSeamWrkMpf *next = mpf->unknown08;
    if (isRelease) {
      releaseFreeSeamMpf(mpf);
    }
    mpf = next;
  }
  if ((unknownc7c & 0x81200) == 0 && unknownc06 < 3) {
    readMpfModelCheck(unknownd30.unknown50);
  }
}

void DrMdoCtlSeamMpfMap::updateMpfMapRenderList() {
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  grlib::CGLibVtxInstans *instans = m_drMan->unknown88->unknown008->unknown10;
  DrMdoMpfMan *mpfMan = m_drMan->unknown88->unknown020;
  for (DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00; mpf != nullptr; mpf = mpf->unknown08) {
    unknown30 = mpf->unknown70;
    if (unknown30 != nullptr) {
      u32 flags = mpf->updateRenderList(view, instans, this);
      if (flags != 0) {
        unknownf8 |= flags;
        unknownc7c |= 9;
        mpfMan->unknown3d30 |= 2;
        updateMpfMatUniformBlock();
      }
      unknownc5c += mpf->unknown60;
      unknownc60 += mpf->unknown64;
      unknownc64 += mpf->unknown68;
      unknownc68 += mpf->unknown6c;
    }
  }
}

bool DrMdoCtlSeamMpfMap::readMpfModelCheck(const mm::Vec3 &position) {
  bool isEmpty = true;
  // Decision 2026-11-14 (rulings 7 and 8). unknownb90 is tested with the unsigned cast `static_cast<u32>(i) >> 5` (lsr at 0x7100825c90 from
  // the signed counter): the shared word helper unknown723 was tried and swaps the pointer and index registers (0x7100825c8c: it loads the
  // table first, the game evaluates the index first), which suggests that the original expanded a bit-table macro with an unsigned cast.
  // The bit test of DrMan::isGblIdx is written out under ruling 8: the game loads m_gblIdx once before the loop (x26 at 0x7100825c24), and
  // `m_drMan->isGblIdx(entry->unknown24)` is 89 instructions too but reloads m_gblIdx in the loop (x26 is not saved).
  const u32 *gblIdx = m_drMan->m_gblIdx;
  const unknown722 *entry = reinterpret_cast<const unknown722 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown68);
  s32 max = unknown1a8->m_seamMpfMdlMax;
  for (s32 i = 0; i < max; i++, entry++) {
    if ((unknownb90[static_cast<u32>(i) >> 5] & (1 << (i & 0x1f))) != 0) {
      continue;
    }
    if (entry->unknown24 != 0 && (gblIdx[entry->unknown24 >> 5] & (1 << (entry->unknown24 & 0x1f))) != 0) {
      continue;
    }
    if ((unknownc7c & 0x100) != 0 && (entry->unknown28 & 1) == 0) {
      continue;
    }
    if (entry->unknown00[0] + 40.0f < position.x || entry->unknown0c[0] - 40.0f > position.x || entry->unknown00[1] + 40.0f < position.y || entry->unknown0c[1] - 40.0f > position.y ||
        entry->unknown00[2] + 40.0f < position.z || entry->unknown0c[2] - 40.0f > position.z) {
      continue;
    }
    unknownd30.setStockMpfMdl(i);
    isEmpty = false;
  }
  return isEmpty;
}

void DrMdoCtlSeamMpfMap::createMpfMapDisplayList() {
  if (m_drMan->unknown1d6b) {
    return;
  }
  DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00;
  grlib::CGLibVtxInstans *instans = m_drMan->unknown88->unknown008->unknown10;
  DrAPCache *cache = m_drMan->unknown5c0;
  cache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
  m_drMan->unknown78->selectGBuffRenderTarget(0x1f);
  cache->setupDepthStencil(0x18, 1, 0, 3);
  cache->setupAlphaBlend(0);
  for (; mpf != nullptr; mpf = mpf->unknown08) {
    unknown30 = mpf->unknown70;
    if (unknown30 != nullptr && mpf->unknown4e != 0) {
      beginMatInfo();
      unknown30->unknownc8->beginVertexSetup();
      int count = mpf->unknown52;
      DrMdoCtlMpfWork *work = mpf->unknownc0;
      for (int i = 0; i < count; i++) {
        if (work->unknown20[i].unknown20 != 0) {
          const MdsMdlTopHeader *entry = &unknown30->unknown168[i];
          const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
          int num = entry->unknown04;
          for (int j = 0; j < num; j++, header++) {
            mpfDrawRender(i, header, work, instans);
          }
        }
      }
    }
  }
  cache->setupAlphaBlend(0);
}

DrResMdoSeamWrkMpf *DrMdoCtlSeamMpfMap::createFreeSeamMpf() { return unknown338.unknown001(); }

void DrMdoCtlSeamMpfMap::callRenderSeamMpfMap() {
  if (((unknownc7c >> 3) & 1) == 0) {
    return;
  }
  DrMan::get()->unknown180->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_3);
  createMpfMapDisplayList();
  DrMan::get()->unknown180->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_3);
}

} // namespace ml
