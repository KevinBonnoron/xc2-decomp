#include "dr/dr_res_mdo_seam_wrk_base.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam_base_map.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_alp_tbl.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_wrk_base_vertex.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSeamWrkBaseVertex::DrResMdoSeamWrkBaseVertex() : unknown00(nullptr), unknown08(nullptr) {}

void DrResMdoSeamWrkBaseVertex::release() {
  DrResMdoVertex *vertex = unknown08;
  if (vertex != nullptr) {
    vertex->vertexRelease();
    ::operator delete(vertex);
    unknown08 = nullptr;
  }
  unknown00 = nullptr;
}

// The buffer is read before DrMan::getIns() (ldr x20, [x20, #0x18] at 0x710087fc34): the local places that load.
void DrResMdoSeamWrkBaseVertex::setupVertex(int index, DrResMdoSeamMemObj *memObj) {
  release();
  unknown00 = memObj;
  unknown10 = index;
  const u8 *buffer = memObj->m_buffer;
  unknown08 = new (DrMan::getIns()->unknown10) DrResMdoVertex(buffer);
}

void DrResMdoSeamWrkBaseVertex::changeMemVertex() { unknown08->changeMemVertex(unknown00->m_buffer); }

f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK = 4200.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = 10.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_CHECK = 4000.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_MIDDLE = 4000.0f;

DrResMdoSeamWrkBase::DrResMdoSeamWrkBase()
    : unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown98(0), unknowna0(0), unknownb0(0), unknownb4(0), unknowne0(nullptr), unknowne8(nullptr), unknown158(nullptr),
      unknown168(nullptr), unknown17a(0), unknown17c(0), unknown17e(0) {}

DrResMdoSeamWrkBase::~DrResMdoSeamWrkBase() { release(); }

void DrResMdoSeamWrkBase::release() {
  if (unknown78 != nullptr) {
    for (int i = 0; i < unknown17e; i++) {
      unknown78[i].release();
    }
  }
  DrResMdoAlpTbl::release(unknown168);
  unknown78 = nullptr;
  unknown17e = 0;
  unknowne0 = nullptr;
  unknowne8 = nullptr;
  for (int i = 0; i < unknownb0; i++) {
    if (unknowna8[i] != nullptr) {
      mtl::MemManager::deallocate(unknowna8[i], 0, false);
      unknowna8[i] = nullptr;
    }
  }
  unknownb0 = 0;
  if (unknown68 != nullptr) {
    mtl::MemManager::deallocate(unknown68, 0, false);
    unknown68 = nullptr;
  }
  if (unknown70 != nullptr) {
    mtl::MemManager::deallocate(unknown70, 0, false);
    unknown70 = nullptr;
  }
  unknown158 = nullptr;
}

void DrResMdoSeamWrkBase::releaseCache(DrMdoCtlSeamBaseMap *ctl) {
  if (unknown78 != nullptr) {
    for (int i = 0; i < unknown17e; i++) {
      DrResMdoSeamMemObj *memObj = unknown78[i].unknown00;
      unknown78[i].release();
      if (memObj != nullptr) {
        ctl->releaseFreeSeamMemObj(memObj);
      }
    }
  }
  unknown78 = nullptr;
  unknowne0 = nullptr;
  unknowne8 = nullptr;
  unknown17e = 0;
  release();
}

void DrResMdoSeamWrkBase::beginBaseMapRenderList() {
  unknown94 = 0;
  unknown170 = 0;
  unknown8c = 0;
  unknown90 = 0;
  memset(unknown110, 0, unknown174);
}

// Inlines DrResMdoSeamParmRead::setStockTexList (0x71008792cc), defined earlier in this unit (dr_res_mdo_lod_parts.cpp). The game loads the texture list slot once (ldrh at 0x710087d0c4)
// and reuses it after the store to unknown3a (sturb at 0x710087d0d0): without the local clang loads it again (97 instructions against 94).
bool DrResMdoSeamWrkBase::callTexReadUpdate(u16 *textureListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamBaseMap *ctl) {
  if (unknown20->unknown34 != 0) {
    if (unknown20->unknown34 > 0) {
      const u16 *index = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown20) + unknown20->unknown30);
      bool isRead = false;
      for (s32 i = 0; i < unknown20->unknown34; i++, index++) {
        u16 list = textureListFlags[*index];
        if (list == 0) {
          ctl->unknownd30.setStockTexList(*index);
          isRead = true;
        } else {
          texLists[list - 1].unknown3a = 0;
          unknown160[i] = &texLists[list - 1];
        }
      }
      if (isRead) {
        return true;
      }
    }
    if ((unknowna0 & 1) == 0) {
      unknowna0 |= 1;
      grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->unknown78->getDammyTexObj();
      const unknown785 *entry = reinterpret_cast<const unknown785 *>(reinterpret_cast<const u8 *>(unknown20) + unknown20->unknown1c);
      for (s32 i = 0; i < unknown20->unknown20; i++, entry++) {
        if ((entry->unknown06 & 1) == 0) {
          unknown68->unknowne8[i] = dummy;
        } else {
          unknown68->unknowne8[i] = unknown160[entry->unknown02]->unknown20 + entry->unknown00;
        }
      }
    }
  }
  return false;
}

void DrResMdoSeamWrkBase::callShadowCacheBaseUpdate(u64 mask) {
  for (int i = 0; i < 0x24; i++) {
    if ((1ull << i) & mask) {
      memset(unknownf0[i], 0, unknownf8);
    }
  }
  unknown98 &= ~mask;
}

void DrResMdoSeamWrkBase::beginRender() {
  unknown178 = -1;
  unknown68->unknownc8 = nullptr;
}

void DrResMdoSeamWrkBase::endRender() { unknown68->unknownc8 = nullptr; }

void DrResMdoSeamWrkBase::setupHeader() {
  const u8 *data = reinterpret_cast<const u8 *>(unknown20);
  const u8 *tree = data + unknown20->unknown18;
  unknown28 = reinterpret_cast<const unknown780 *>(tree);
  unknown30 = tree + unknown28->unknown04;
  unknown38 = reinterpret_cast<const MdsSeamBaMpTreeData *>(tree + unknown28->unknown0c);
  unknown40 = tree + unknown28->unknown14;
  unknown48 = tree + unknown28->unknown1c;
  // The game stores unknown48 twice (0x710087c8c4 and 0x710087c8d0: the offset is loaded again between the two stores).
  unknown48 = tree + unknown28->unknown1c;
  const unknown781 *model = reinterpret_cast<const unknown781 *>(data + unknown20->unknown0c);
  // The game (1.0.0: 0x710087c8e0, also in changeMemCall 0x710087c970) keeps the branch: cbz, then add + str, else str xzr. Both arms are written to the
  // same member, and clang merges such a pair into one store of a select (csel) in InstCombine's SimplifyStoreAtEndOfBlock or in MergedLoadStoreMotion. They
  // stay apart when the member is typed `const unknown783 *` (the game's readers use the record the pointer reaches): InstCombine rewrites the store of the
  // casted byte pointer into a store of the byte pointer through a casted address, so the two arms no longer store the same type to the same address and
  // neither pass merges them. With `const u8 *` (or `u64`, `void *`) both arms have the same store and the csel comes out: 33 instructions against the game's 34.
  if (model->unknown24 == 0) {
    unknown60 = nullptr;
  } else {
    unknown60 = reinterpret_cast<const unknown783 *>(reinterpret_cast<const u8 *>(model) + model->unknown24);
  }
  unknown50 = reinterpret_cast<const unknown782 *>(data + unknown20->unknown38);
  unknown58 = reinterpret_cast<const u8 *>(unknown50) + unknown50->unknown08;
}

void DrResMdoSeamWrkBase::changeMemCall() {
  unknown20 = reinterpret_cast<const MdsSeamBaseMapHead *>(unknown158->m_buffer);
  setupHeader();
}

void DrResMdoSeamWrkBase::selectVertex(int index) {
  if (unknown178 != index) {
    unknown68->unknownc8 = unknown78[index].unknown08;
    unknown68->unknownc8->unknown4e = -1;
    unknown178 = index;
  }
}

void DrResMdoSeamWrkBase::seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl) {
  if (!(unknown20->unknown00 & 4)) {
    beginRender();
    seachDefShadowBaseMapRenderChild(shadow, ctl, unknown38);
    endRender();
  }
}

// 0x710087fdf4. The id is loaded with ldrsh (0x710087fe2c) and the table indexed through an unsigned register (`ldr x8, [x9, w8, uxtw #3]`, 0x710087fe38), so
// it goes through a u32 local (same as DrResMdoSeamWrkInst::seachShadowInstMapRender): indexing with `cache.unknown8f2` or an int local gives another sequence.
bool DrResMdoSeamWrkBase::seachShadowBaseMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl) {
  if ((unknown98 & cache.unknown8e8) == 0) {
    if ((unknown20->unknown00 & 4) == 0) {
      u32 id = cache.unknown8f2;
      unknown100 = unknownf0[id];
      beginRender();
      bool isRender = seachShadowBaseMapRenderChild(cache, ctl, unknown38);
      endRender();
      if (isRender) {
        return true;
      }
    }
    unknown98 |= cache.unknown8e8;
  }
  return false;
}

void DrResMdoSeamWrkBase::stockRenderListBaseMap(int base, u32 kind, u32 index, u32 vertex, bool isAlpha, int unknown) {
  unknown504 *entry = &unknown150[unknown170];
  int slot = base + kind;
  if (isAlpha) {
    if (unknown128[slot] == nullptr) {
      unknown118[unknown138[kind] + unknown68->unknown30 * kind] = entry;
      unknown138[kind]++;
    } else {
      unknown128[slot]->unknown04 = unknown170 + 1;
    }
    unknown128[slot] = entry;
  } else {
    if (unknown120[slot] == nullptr) {
      unknown110[unknown130[kind] + unknown68->unknown30 * kind] = entry;
      unknown130[kind]++;
    } else {
      unknown120[slot]->unknown04 = unknown170 + 1;
    }
    unknown120[slot] = entry;
  }
  entry->unknown08 = unknown;
  entry->unknown00 = index;
  entry->unknown06 = vertex;
  entry->unknown04 = 0;
  unknown170++;
}

void DrResMdoSeamWrkBase::calcCacheInfo() {
  for (s32 i = 0; i < unknown17e; i++) {
    if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
      if (unknown78[i].unknown00->unknown24 & 2) {
        // The game loads the buffer (ldr x1, [x10, #0x18] at 0x710087d308) after the flag test and before the member holding the vertex (ldr x0, [x8, #8] at 0x710087d30c); without the
        // local clang loads the member first (x9/x10 swapped, tried: memObj local, element reference, DrResMdoSeamWrkBaseVertex::changeMemVertex inlined): the local places that load.
        const u8 *buffer = unknown78[i].unknown00->m_buffer;
        unknown78[i].unknown08->changeMemVertex(buffer);
      }
    }
  }
  if (!(unknowna0 & 0x200)) {
    for (s32 i = 0; i < unknown17e; i++) {
      if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
        unknowne8[i >> 5] |= 1 << (i & 0x1f);
      } else {
        unknowne8[i >> 5] &= ~(1 << (i & 0x1f));
      }
    }
  } else {
    // The game loads unknown50 once (ldr x8, [x19, #0x50] at 0x710087d3a0) and reads the count of x8 again in each iteration (0x710087d420); without the local clang reloads
    // unknown50 after the store to unknowne8 (one more instruction, tried): the local places that load.
    const unknown782 *list = unknown50;
    for (s32 i = 0; i < list->unknown04; i++) {
      if ((unknowne0[i >> 5] & (1 << (i & 0x1f))) || (unknowne0[(i + list->unknown04) >> 5] & (1 << ((i + list->unknown04) & 0x1f)))) {
        unknowne8[i >> 5] |= 1 << (i & 0x1f);
      } else {
        unknowne8[i >> 5] &= ~(1 << (i & 0x1f));
      }
    }
  }
}

// The loop over the texture list indices has no test of its own: the guard of the rotated loop (cmp w8, #1; b.lt at 0x7100880384) is its only test of the count.
void DrResMdoSeamWrkBase::callReleaseReadList(DrMdoCtlSeamBaseMap *ctl, DrResMdoSeamTexList *texLists, const u16 *textureListFlags) {
  if (unknown20->unknown34 != 0) {
    if (unknowna0 & 1) {
      if ((unknowna0 & 0x100) == 0) {
        unknowna0 |= 0x100;
      } else {
        unknowna0 &= ~0x101;
        for (s32 i = 0; i < unknownb0; i++) {
          if (unknowna8[i] != nullptr) {
            mtl::MemManager::deallocate(unknowna8[i], 0, false);
            unknowna8[i] = nullptr;
          }
        }
      }
    }
    const u16 *index = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown20) + unknown20->unknown30);
    for (s32 i = 0; i < unknown20->unknown34; i++, index++) {
      if (textureListFlags[*index] == 0) {
        ctl->unknownd30.setStockTexList(*index);
      } else {
        texLists[textureListFlags[*index] - 1].unknown3a = 0;
      }
    }
  }
  for (s32 i = 0; i < unknown17e; i++) {
    if (unknowne0[(i + unknown17e * 2) >> 5] & (1 << ((i + unknown17e * 2) & 0x1f))) {
      DrResMdoSeamMemObj *memObj = unknown78[i].unknown00;
      unknown78[i].release();
      if (memObj != nullptr) {
        ctl->releaseFreeSeamMemObj(memObj);
      }
      unknowne0[(i + unknown17e * 2) >> 5] &= ~(1 << ((i + unknown17e * 2) & 0x1f));
    } else if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
      unknown94++;
      unknown90 += unknown78[i].unknown10;
      unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
      unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
    }
    unknowne0[(i + unknown17e) >> 5] &= ~(1 << ((i + unknown17e) & 0x1f));
  }
}

} // namespace ml

// The game builds these files in one unit with this one (0x710087ba20 to 0x710088f99c), in this order.
// clang-format off
#include "dr_res_mdo_seam_wrk_env.cpp"
#include "dr_res_mdo_seam_wrk_inst.cpp"
#include "dr_res_mdo_seam_wrk_light.cpp"
#include "dr_res_mdo_seam_wrk_low.cpp"
#include "dr_res_mdo_seam_wrk_mpf.cpp"
#include "dr_res_wrk_clip_list.cpp"
#include "dr_res_mdo_seam_wrk_pos_mpf.cpp"
#include "dr_res_mdo_tex_list.cpp"
#include "dr_res_mdo_uniform_block.cpp"
#include "dr_res_mdo_vertex.cpp"
#include "dr_res_mdo_sampler.cpp"
#include "dr_res_occ_uniform_obj.cpp"
#include "dr_res_query_obj.cpp"
#include "dr_res_shd.cpp"
// clang-format on
