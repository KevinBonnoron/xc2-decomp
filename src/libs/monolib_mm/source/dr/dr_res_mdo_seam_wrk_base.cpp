#include "dr/dr_res_mdo_seam_wrk_base.h"

#include <string.h>

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_base_map.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_alp_tbl.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_wrk_base_vertex.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSeamWrkBaseVertex::DrResMdoSeamWrkBaseVertex() : m_drResMdoSeamMemObj(nullptr), m_drResMdoVertex(nullptr) {}

void DrResMdoSeamWrkBaseVertex::release() {
  DrResMdoVertex *vertex = m_drResMdoVertex;
  if (vertex != nullptr) {
    vertex->vertexRelease();
    ::operator delete(vertex);
    m_drResMdoVertex = nullptr;
  }
  m_drResMdoSeamMemObj = nullptr;
}

// The buffer is read before DrMan::getIns() (ldr x20, [x20, #0x18] at 0x710087fc34): the local places that load.
void DrResMdoSeamWrkBaseVertex::setupVertex(int index, DrResMdoSeamMemObj *memObj) {
  release();
  m_drResMdoSeamMemObj = memObj;
  unknown10 = index;
  const u8 *buffer = memObj->m_buffer;
  m_drResMdoVertex = new (DrMan::getIns()->unknown10) DrResMdoVertex(buffer);
}

void DrResMdoSeamWrkBaseVertex::changeMemVertex() { m_drResMdoVertex->changeMemVertex(m_drResMdoSeamMemObj->m_buffer); }

f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK = 4200.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = 10.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_CHECK = 4000.0f;
f32 DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_MIDDLE = 4000.0f;

DrResMdoSeamWrkBase::DrResMdoSeamWrkBase()
    : m_mdoWrkMatRes(nullptr), unknown70(nullptr), m_drResMdoSeamWrkBaseVertex(nullptr), unknown98(0), unknowna0(0), unknownb0(0), unknownb4(0), unknowne0(nullptr), unknowne8(nullptr),
      m_drResMdoSeamMemObj(nullptr), m_drResMdoAlpTbl(nullptr), unknown17a(0), unknown17c(0), unknown17e(0) {}

DrResMdoSeamWrkBase::~DrResMdoSeamWrkBase() { release(); }

void DrResMdoSeamWrkBase::release() {
  if (m_drResMdoSeamWrkBaseVertex != nullptr) {
    for (int i = 0; i < unknown17e; i++) {
      m_drResMdoSeamWrkBaseVertex[i].release();
    }
  }
  DrResMdoAlpTbl::release(m_drResMdoAlpTbl);
  m_drResMdoSeamWrkBaseVertex = nullptr;
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
  if (m_mdoWrkMatRes != nullptr) {
    mtl::MemManager::deallocate(m_mdoWrkMatRes, 0, false);
    m_mdoWrkMatRes = nullptr;
  }
  if (unknown70 != nullptr) {
    mtl::MemManager::deallocate(unknown70, 0, false);
    unknown70 = nullptr;
  }
  m_drResMdoSeamMemObj = nullptr;
}

// Inferred role: releases the vertex of the work and gives its memory object back to the seam control; original name unknown. Written out in releaseCache, callReleaseReadList and
// releaseReadVertexList in the game (the same call form of a static helper inlines into the three of them and matches, P4).
static void unknown301(DrMdoCtlSeamBaseMap *ctl, DrResMdoSeamWrkBaseVertex &vertex) {
  DrResMdoSeamMemObj *memObj = vertex.m_drResMdoSeamMemObj;
  vertex.release();
  if (memObj != nullptr) {
    ctl->releaseFreeSeamMemObj(memObj);
  }
}

void DrResMdoSeamWrkBase::releaseCache(DrMdoCtlSeamBaseMap *ctl) {
  if (m_drResMdoSeamWrkBaseVertex != nullptr) {
    for (int i = 0; i < unknown17e; i++) {
      unknown301(ctl, m_drResMdoSeamWrkBaseVertex[i]);
    }
  }
  m_drResMdoSeamWrkBaseVertex = nullptr;
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
  memset(unknown110[0], 0, unknown174);
}

// Inlines DrResMdoSeamParmRead::setStockTexList (0x71008792cc), defined earlier in this unit (dr_res_mdo_lod_parts.cpp). The game loads the texture list slot once (ldrh at 0x710087d0c4)
// and reuses it after the store to unknown3a (sturb at 0x710087d0d0): without the local clang loads it again (97 instructions against 94).
bool DrResMdoSeamWrkBase::callTexReadUpdate(u16 *textureListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamBaseMap *ctl) {
  if (m_mdsSeamBaseMapHead->unknown34 != 0) {
    if (m_mdsSeamBaseMapHead->unknown34 > 0) {
      const u16 *index = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(m_mdsSeamBaseMapHead) + m_mdsSeamBaseMapHead->unknown30);
      bool isRead = false;
      for (s32 i = 0; i < m_mdsSeamBaseMapHead->unknown34; i++, index++) {
        u16 list = textureListFlags[*index];
        if (list == 0) {
          ctl->m_drResMdoSeamParmRead.setStockTexList(*index);
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
      grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->m_drPixlMan->getDammyTexObj();
      const unknown785 *entry = reinterpret_cast<const unknown785 *>(reinterpret_cast<const u8 *>(m_mdsSeamBaseMapHead) + m_mdsSeamBaseMapHead->unknown1c);
      for (s32 i = 0; i < m_mdsSeamBaseMapHead->unknown20; i++, entry++) {
        if ((entry->unknown06 & 1) == 0) {
          m_mdoWrkMatRes->unknowne8[i] = dummy;
        } else {
          m_mdoWrkMatRes->unknowne8[i] = unknown160[entry->unknown02]->unknown20 + entry->unknown00;
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
  m_mdoWrkMatRes->m_drResMdoVertex = nullptr;
}

void DrResMdoSeamWrkBase::endRender() { m_mdoWrkMatRes->m_drResMdoVertex = nullptr; }

void DrResMdoSeamWrkBase::setupHeader() {
  const u8 *data = reinterpret_cast<const u8 *>(m_mdsSeamBaseMapHead);
  const u8 *tree = data + m_mdsSeamBaseMapHead->unknown18;
  unknown28 = reinterpret_cast<const unknown780 *>(tree);
  unknown30 = reinterpret_cast<const unknown787 *>(tree + unknown28->unknown04);
  m_mdsSeamBaMpTreeData = reinterpret_cast<const MdsSeamBaMpTreeData *>(tree + unknown28->unknown0c);
  unknown40 = reinterpret_cast<const u16 *>(tree + unknown28->unknown14);
  unknown48 = reinterpret_cast<const u16 *>(tree + unknown28->unknown1c);
  // The game stores unknown48 twice (0x710087c8c4 and 0x710087c8d0: the offset is loaded again between the two stores).
  unknown48 = reinterpret_cast<const u16 *>(tree + unknown28->unknown1c);
  const unknown781 *model = reinterpret_cast<const unknown781 *>(data + m_mdsSeamBaseMapHead->unknown0c);
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
  unknown50 = reinterpret_cast<const unknown782 *>(data + m_mdsSeamBaseMapHead->unknown38);
  unknown58 = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown50) + unknown50->unknown08);
}

void DrResMdoSeamWrkBase::changeMemCall() {
  m_mdsSeamBaseMapHead = reinterpret_cast<const MdsSeamBaseMapHead *>(m_drResMdoSeamMemObj->m_buffer);
  setupHeader();
}

// 0x710087c9a0. The game has the fade-out arm at 0x710087cb7c and the reset arm (fade in) behind it at 0x710087cc60, reached by the branches of the flag tests at 0x710087cc38 to
// 0x710087cc5c; the counter tests below the fade-out arm are shared (the reset arm stores 0 in unknown17a first and returns on its own, so they fold away on it). The order of the blocks
// decides how the flag tests are lowered: with the reset arm written first (`if (cond) { reset; return false; }` before the fade-out code) it directly follows the tests of the
// `flags & 0x100 == 0` arm, which then ends in `eor; cbnz` where the game has `eor; tbnz` at 0x710087cc40 (measured: moving only the reset blocks away from there in the IR gives the
// game's `tbnz`), and the two final stores are merged by the tail merge when the reset arm is the last block before the return (the game keeps both). So the reset arm is the `else` of
// the inverted test. The area byte at +0x28 is read with ldrb (0x710087cc2c, 0x710087cc48); `check` places the load of the radius (0x710087ca80) before the load of unknown18 (0x710087ca84);
// `isFlag` is the game's 0/1 flag (ubfx #3, #1 at 0x710087cc30) computed before the `flags & 0x100` test and read by both of its arms (without the local the function has 192 instructions).
bool DrResMdoSeamWrkBase::update(DrCalcViewWork *view, const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags) {
  unknowna0 &= ~0x8e;
  if (m_mdoWrkMatRes == nullptr) {
    unknown17a = 0;
    return false;
  }
  if (m_drResMdoSeamMemObj->unknown24 & 2) {
    unknowna0 |= 0x80;
    changeMemCall();
  }
  if (!(unknowna0 & 0x10) && isOpen) {
    return true;
  }
  f32 check = SEAM_BASEMAP_READ_CHECK;
  bool isNear = !unknown18->unknown001(check, parmRead->unknown50);
  if (!isNear) {
    for (s32 i = 0; i < parmRead->unknown40; i++) {
      if (!unknown18->unknown001(check, parmRead->unknown10[i])) {
        isNear = true;
        break;
      }
    }
  }
  bool isFlag = isNear && (flags & 0x10) && (unknown18->unknown28 & 8);
  if (!(isNear && ((flags & 0x100) ? ((unknown18->unknown28 & 4) == 0 && !isFlag) : !isFlag) && !(unknowna0 & 0x20))) {
    unknown17a++;
    if (unknown17a >= 0x14) {
      unknowna0 |= 0x20;
    }
    if (view->unknown9aa) {
      unknown17c = 0;
    } else {
      u16 alpha = unknown17c - 0x14;
      unknown17c = (alpha & 0x8000) == 0 ? alpha : 0;
    }
  } else {
    unknowna0 &= ~0x10;
    unknown17a = 0;
    if (view->unknown9aa) {
      unknown17c = 0xff;
    } else {
      unknown17c += 0x14;
      if (unknown17c > 0xff) {
        unknown17c = 0xff;
      }
    }
  }
  if (unknown17a >= 0x17) {
    if (!(unknowna0 & 0x10)) {
      return true;
    }
    unknowna0 &= ~0x10;
    unknown17a = 0x17;
    return false;
  }
  if (unknown17a >= 0x14) {
    unknowna0 &= ~0x10;
  }
  return false;
}

void DrResMdoSeamWrkBase::selectVertex(int index) {
  if (unknown178 != index) {
    m_mdoWrkMatRes->m_drResMdoVertex = m_drResMdoSeamWrkBaseVertex[index].m_drResMdoVertex;
    m_mdoWrkMatRes->m_drResMdoVertex->unknown4e = -1;
    unknown178 = index;
  }
}

void DrResMdoSeamWrkBase::seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl) {
  if (!(m_mdsSeamBaseMapHead->unknown00 & 4)) {
    beginRender();
    seachDefShadowBaseMapRenderChild(shadow, ctl, m_mdsSeamBaMpTreeData);
    endRender();
  }
}

// 0x710087fdf4. The id is loaded with ldrsh (0x710087fe2c) and the table indexed through an unsigned register (`ldr x8, [x9, w8, uxtw #3]`, 0x710087fe38), so
// it goes through a u32 local (same as DrResMdoSeamWrkInst::seachShadowInstMapRender): indexing with `cache.unknown8f2` or an int local gives another sequence.
bool DrResMdoSeamWrkBase::seachShadowBaseMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl) {
  if ((unknown98 & cache.unknown8e8) == 0) {
    if ((m_mdsSeamBaseMapHead->unknown00 & 4) == 0) {
      u32 id = cache.unknown8f2;
      unknown100 = unknownf0[id];
      beginRender();
      bool isRender = seachShadowBaseMapRenderChild(cache, ctl, m_mdsSeamBaMpTreeData);
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
    if (unknown120[1][slot] == nullptr) {
      unknown110[1][unknown130[1][kind] + m_mdoWrkMatRes->unknown30 * kind] = entry;
      unknown130[1][kind]++;
    } else {
      unknown120[1][slot]->unknown04 = unknown170 + 1;
    }
    unknown120[1][slot] = entry;
  } else {
    if (unknown120[0][slot] == nullptr) {
      unknown110[0][unknown130[0][kind] + m_mdoWrkMatRes->unknown30 * kind] = entry;
      unknown130[0][kind]++;
    } else {
      unknown120[0][slot]->unknown04 = unknown170 + 1;
    }
    unknown120[0][slot] = entry;
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
      if (m_drResMdoSeamWrkBaseVertex[i].m_drResMdoSeamMemObj->unknown24 & 2) {
        // The game loads the buffer (ldr x1, [x10, #0x18] at 0x710087d308) after the flag test and before the member holding the vertex (ldr x0, [x8, #8] at 0x710087d30c); without the
        // local clang loads the member first (x9/x10 swapped, tried: memObj local, element reference, DrResMdoSeamWrkBaseVertex::changeMemVertex inlined): the local places that load.
        const u8 *buffer = m_drResMdoSeamWrkBaseVertex[i].m_drResMdoSeamMemObj->m_buffer;
        m_drResMdoSeamWrkBaseVertex[i].m_drResMdoVertex->changeMemVertex(buffer);
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

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Its only user is seachReadBaseMapMdl (0x710087d440, two calls): the game indexes the table of the bit indices with the vertex id zero extended (`ldrh w17, [x18, x14, lsl #1]` at 0x710087d4e0, x14
// is the loaded u32) and the top header table with the same vertex id sign extended (`smaddl x14, w14, w13, x15` at 0x710087d588). Forms without the helper (184 instructions each, 184 expected): a
// `u32 vertex` used for both gives `uxtw` for the top header (first difference at 0x710087d588), an `s32 vertex` used for both gives `sxtw` for the table (first difference at 0x710087d4d8). A u32
// parameter leaves the top header lookup on the s32.
static u16 getVertexBitIndex(const u16 *table, u32 index) { return table[index]; }

// 0x710087d440. `range` (the game keeps `fadd s3, s1, s0` and squares it at 0x710087d598) and `dx`, `dy`, `dz` (the three `fsub` are squared, 0x710087d568 to 0x710087d590) are locals: written inline
// the function differs at 0x710087d4b0 (range) and 0x710087d55c (the differences). `infoCount` is read before `info` (the game loads `ldp w17, w15, [x14]` and then unknown18, 0x710087d59c; the
// other order differs from 0x710087d554 on). The loops over the entries and the children are pointer walks. The distance to the sphere of the node is a Vec3 (three f32 locals match too, and repeat
// the statements of the clip sphere tests of DrCalcClipObj, which the quality gate reports).
void DrResMdoSeamWrkBase::seachReadBaseMapMdl(const mm::Vec3 &position, const MdsSeamBaMpTreeData *tree) {
  mm::Vec3 delta(position.x - tree->unknown00[0], position.y - tree->unknown00[1], position.z - tree->unknown00[2]);
  f32 radius = tree->unknown0c + unknown80;
  if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > radius * radius) {
    return;
  }
  u16 mdlCount = tree->unknown16;
  if (mdlCount != 0) {
    const u16 *mdlIndex = unknown40 + tree->unknown14;
    for (u32 i = 0; i < mdlCount; i++, mdlIndex++) {
      const unknown787 &entry = *(unknown30 + *mdlIndex);
      s32 vertex = entry.unknown00;
      u16 bit = getVertexBitIndex(unknown58, vertex);
      if (unknowna0 & 0x200) {
        if (!(unknowne0[bit >> 5] & (1 << (bit & 0x1f)))) {
          vertex = entry.unknown04;
          u16 second = getVertexBitIndex(unknown58, vertex);
          if (!(unknowne0[second >> 5] & (1 << (second & 0x1f)))) {
            continue;
          }
        }
      } else if (!(unknowne0[bit >> 5] & (1 << (bit & 0x1f)))) {
        continue;
      }
      if (m_drResMdoAlpTbl->unknown004(bit) <= 0.0f) {
        continue;
      }
      f32 range = entry.unknown24 + 100.0f;
      f32 dx = entry.unknown0c[0] - position.x;
      f32 dy = entry.unknown0c[1] - position.y;
      f32 dz = entry.unknown0c[2] - position.z;
      f32 distanceSq = dx * dx + dy * dy + dz * dz;
      const MdsMdlTopHeader *mdl = m_mdoWrkMatRes->m_mdsMdlTopHeader + vertex;
      s32 infoCount = mdl->unknown04;
      const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(m_mdoWrkMatRes->unknown18 + mdl->unknown00);
      if (range * range >= distanceSq) {
        for (s32 j = 0; j < infoCount; j++, info++) {
          unknownb8[info->unknown0e >> 5] |= 1 << (info->unknown0e & 0x1f);
          s32 alphaBit = info->unknown0e + m_mdoWrkMatRes->unknown30;
          unknownb8[alphaBit >> 5] |= 1 << (alphaBit & 0x1f);
        }
      } else if ((entry.unknown24 + unknown80) * (entry.unknown24 + unknown80) >= distanceSq) {
        for (s32 j = 0; j < infoCount; j++, info++) {
          unknownb8[info->unknown0e >> 5] |= 1 << (info->unknown0e & 0x1f);
        }
      }
    }
  }
  u16 childCount = tree->unknown12;
  if (childCount != 0) {
    const u16 *childIndex = unknown48 + tree->unknown10;
    for (u32 i = 0; i < childCount; i++, childIndex++) {
      seachReadBaseMapMdl(position, &m_mdsSeamBaMpTreeData[*childIndex]);
    }
  }
}

// 0x710087d720. The inner loop walks a pointer (s32 j, index++): the game compares w14 with the u16 count and indexes with x14 (0x710087d7a0), while `index[j]` widens the compare to 64 bits (cmp x14,
// x13; measured, 51 instructions with another register use). The data pointer of the index lists is formed before the loop (add x11 at 0x710087d758) and keeps the load of its offset in the entry
// block, next to the count (ldp w8, w11 at 0x710087d744); with the offset read into a local (`u32 indexOffset = ...unknown08;`) clang sinks that load behind the test (52 instructions against 51).
void DrResMdoSeamWrkBase::calcCheckClipInfo(DrCalcClipMan *clip) {
  if (unknown60 != nullptr && (clip->unknown7c & 2)) {
    unknown108[0] |= 1;
    const u8 *base = reinterpret_cast<const u8 *>(unknown60);
    const u16 *indices = reinterpret_cast<const u16 *>(base + unknown60->unknown08);
    const u16 *entry = reinterpret_cast<const u16 *>(base + unknown60->unknown00);
    for (s32 i = 0; i < unknown60->unknown04; i++, entry += 2) {
      const u16 *index = indices + entry[0];
      for (s32 j = 0; j < entry[1]; j++, index++) {
        u16 clipIndex = *index;
        if (!(clip->unknown70[clipIndex >> 5] & (1 << (clipIndex & 0x1f)))) {
          unknown108[(i + 1) >> 5] |= 1 << ((i + 1) & 0x1f);
          break;
        }
      }
    }
  }
}

// Inferred role: moves the loaded bit of a height texture entry of the work to the wanted state and marks the entry as kept when the bit changed; original name unknown.
// The height bit handling of calcStaemBaseMapMdl calls it three times and matches (399 instructions; written out it matches too, so the helper is the shorter form, P4).
static void unknown300(DrResMdoSeamWrkBase *wrk, s32 bit, s32 i, bool on) {
  if (on) {
    if ((wrk->unknownd8[bit >> 5] & (1 << (bit & 0x1f))) == 0) {
      wrk->unknownd8[bit >> 5] |= 1 << (bit & 0x1f);
      wrk->unknownd0[i >> 5] |= 1 << (i & 0x1f);
    }
  } else if (wrk->unknownd8[bit >> 5] & (1 << (bit & 0x1f))) {
    wrk->unknownd8[bit >> 5] &= ~(1 << (bit & 0x1f));
    wrk->unknownd0[i >> 5] |= 1 << (i & 0x1f);
  }
}

// 0x710087db04. Inlines DrResMdoSeamParmRead::setStockTexture and setStockHeightTexture (defined earlier in this unit, dr_res_mdo_lod_parts.cpp). The game keeps the loop over the material
// textures and the alpha texture block apart for the height bits: they are written as two branches (a bool local for the test leaves the alpha block merged, 372 instructions against 399).
// The not requested and the stock paths of a seam texture entry each have their own copy of the loaded bit handling in the game: it is written out twice (ruling 8). A static helper
// holding that block (the loaded bit test, both clears, the keep bit and the two stores of unknowne8), called from both paths, is simplified before it is inlined and gives 357
// instructions against the game's 399 (measured).
void DrResMdoSeamWrkBase::calcStaemBaseMapMdl(u16 *textureFlags, DrResMdoSeamTexture *textures, DrResMdoSeamParmRead *parmRead, const MdsSeamOfsTexTblData *table, bool isHeight) {
  const MdsSeamBaseMapHead *head = m_mdsSeamBaseMapHead;
  s32 matCount = m_mdoWrkMatRes->unknown30;
  const u8 *matData = m_mdoWrkMatRes->unknown10;
  s32 count = head->unknown20;
  const MdsMatTextureInfo *infos = reinterpret_cast<const MdsMatTextureInfo *>(matData + reinterpret_cast<const MdsMatTopHeader *>(matData)->unknown3c);
  for (s32 i = 0; i < matCount; i++) {
    if (unknownb8[i >> 5] & (1 << (i & 0x1f))) {
      const MdsMatInfoHeader *mat = &m_mdoWrkMatRes->unknown28[i];
      s32 num = mat->unknown24;
      const MdsMatTextureInfo *info = reinterpret_cast<const MdsMatTextureInfo *>(m_mdoWrkMatRes->unknown10 + mat->unknown20);
      s32 bit = m_mdoWrkMatRes->unknown30 + i;
      if ((unknownb8[bit >> 5] & (1 << (bit & 0x1f))) && isHeight) {
        for (s32 j = 0; j < num; j++, info++) {
          unknownc8[info->unknown00 >> 5] |= 1 << (info->unknown00 & 0x1f);
          s32 heightBit = info->unknown00 + count;
          unknownc8[heightBit >> 5] |= 1 << (heightBit & 0x1f);
        }
        if ((mat->unknown04 & MdsMatInfoHeader::unknown015_2) || (mat->unknown08 & 0x10)) {
          const MdsMatTextureInfo *alpha = &infos[mat->unknown62];
          unknownc8[alpha->unknown00 >> 5] |= 1 << (alpha->unknown00 & 0x1f);
          s32 heightBit = alpha->unknown00 + count;
          unknownc8[heightBit >> 5] |= 1 << (heightBit & 0x1f);
        }
      } else {
        for (s32 j = 0; j < num; j++, info++) {
          unknownc8[info->unknown00 >> 5] |= 1 << (info->unknown00 & 0x1f);
        }
        if ((mat->unknown04 & MdsMatInfoHeader::unknown015_2) || (mat->unknown08 & 0x10)) {
          const MdsMatTextureInfo *alpha = &infos[mat->unknown62];
          unknownc8[alpha->unknown00 >> 5] |= 1 << (alpha->unknown00 & 0x1f);
        }
      }
    }
  }
  s32 size = (count / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  memset(unknownd0, 0, size);
  grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->m_drPixlMan->getDammyTexObj();
  const unknown785 *entry = reinterpret_cast<const unknown785 *>(reinterpret_cast<const u8 *>(head) + m_mdsSeamBaseMapHead->unknown1c);
  for (s32 i = 0; i < count; i++, entry++) {
    if ((entry->unknown06 & 2) == 0) {
      if ((entry->unknown06 & 1) && unknown160[entry->unknown02]->unknown3b) {
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
      }
    } else if ((unknownc8[i >> 5] & (1 << (i & 0x1f))) == 0) {
      if (unknownd8[i >> 5] & (1 << (i & 0x1f))) {
        unknownd8[i >> 5] &= ~(1 << (i & 0x1f));
        s32 heightBit = i + count;
        unknownd8[heightBit >> 5] &= ~(1 << (heightBit & 0x1f));
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
        if ((entry->unknown06 & 1) == 0) {
          m_mdoWrkMatRes->unknowne8[i] = dummy;
        } else {
          m_mdoWrkMatRes->unknowne8[i] = unknown160[entry->unknown02]->unknown20 + entry->unknown00;
        }
      } else if ((entry->unknown06 & 1) && unknown160[entry->unknown02]->unknown3b) {
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
      }
    } else if (textureFlags[entry->unknown04] == 0) {
      // The game never sets the level argument (decision 6); 0.0f is a placeholder, the original expression cannot be checked.
      parmRead->setStockTexture(0.0f, entry->unknown04);
      if (unknownd8[i >> 5] & (1 << (i & 0x1f))) {
        unknownd8[i >> 5] &= ~(1 << (i & 0x1f));
        s32 heightBit = i + count;
        unknownd8[heightBit >> 5] &= ~(1 << (heightBit & 0x1f));
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
        if ((entry->unknown06 & 1) == 0) {
          m_mdoWrkMatRes->unknowne8[i] = dummy;
        } else {
          m_mdoWrkMatRes->unknowne8[i] = unknown160[entry->unknown02]->unknown20 + entry->unknown00;
        }
      } else if ((entry->unknown06 & 1) && unknown160[entry->unknown02]->unknown3b) {
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
      }
    } else {
      DrResMdoSeamTexture *texture = &textures[textureFlags[entry->unknown04] - 1];
      texture->unknowna0 = 0;
      if (texture->unknowna1) {
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
      }
      if ((unknownd8[i >> 5] & (1 << (i & 0x1f))) == 0) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
        unknownd0[i >> 5] |= 1 << (i & 0x1f);
        m_mdoWrkMatRes->unknowne8[i] = &texture->m_cGLibTextureBuffer;
      }
      if (table[entry->unknown04].unknown0c != 0) {
        s32 bit = i + count;
        if ((unknownc8[bit >> 5] & (1 << (bit & 0x1f))) == 0) {
          unknown300(this, bit, i, texture->unknowna3 == 1);
        } else if (texture->unknowna3 == 1) {
          texture->unknowna2 = 0;
          unknown300(this, bit, i, true);
        } else {
          parmRead->setStockHeightTexture(entry->unknown04 + 1);
          unknown300(this, bit, i, false);
        }
      }
    }
  }
}

// The loop over the texture list indices has no test of its own: the guard of the rotated loop (cmp w8, #1; b.lt at 0x7100880384) is its only test of the count.
void DrResMdoSeamWrkBase::callReleaseReadList(DrMdoCtlSeamBaseMap *ctl, DrResMdoSeamTexList *texLists, const u16 *textureListFlags) {
  if (m_mdsSeamBaseMapHead->unknown34 != 0) {
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
    const u16 *index = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(m_mdsSeamBaseMapHead) + m_mdsSeamBaseMapHead->unknown30);
    for (s32 i = 0; i < m_mdsSeamBaseMapHead->unknown34; i++, index++) {
      if (textureListFlags[*index] == 0) {
        ctl->m_drResMdoSeamParmRead.setStockTexList(*index);
      } else {
        texLists[textureListFlags[*index] - 1].unknown3a = 0;
      }
    }
  }
  for (s32 i = 0; i < unknown17e; i++) {
    if (unknowne0[(i + unknown17e * 2) >> 5] & (1 << ((i + unknown17e * 2) & 0x1f))) {
      unknown301(ctl, m_drResMdoSeamWrkBaseVertex[i]);
      unknowne0[(i + unknown17e * 2) >> 5] &= ~(1 << ((i + unknown17e * 2) & 0x1f));
    } else if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
      unknown94++;
      unknown90 += m_drResMdoSeamWrkBaseVertex[i].unknown10;
      unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
      unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
    }
    unknowne0[(i + unknown17e) >> 5] &= ~(1 << ((i + unknown17e) & 0x1f));
  }
}

// The partner test of the last arm branches on its own in each half and continues there, so the shared alpha code takes its index from a phi of two edges and the game's
// `i - count` sits on the edge into it. Joined in a bool first, InstCombine folds the two tests into one test of a phi of words and the index is computed before the test.
void DrResMdoSeamWrkBase::releaseReadVertexList(DrMdoCtlSeamBaseMap *ctl, DrCalcViewWork *view) {
  const unknown782 *list = unknown50;
  for (s32 i = 0; i < unknown17e; i++) {
    if (unknowne0[(i + unknown17e * 2) >> 5] & (1 << ((i + unknown17e * 2) & 0x1f))) {
      unknown301(ctl, m_drResMdoSeamWrkBaseVertex[i]);
      unknowne0[(i + unknown17e * 2) >> 5] &= ~(1 << ((i + unknown17e * 2) & 0x1f));
      if (!(unknowna0 & 0x200)) {
        m_drResMdoAlpTbl->unknown005(i, 0.0f);
      } else if (i < list->unknown04) {
        s32 partner = i + list->unknown04;
        if (!(unknowne0[partner >> 5] & (1 << (partner & 0x1f)))) {
          m_drResMdoAlpTbl->unknown005(i, 0.0f);
        }
      } else {
        s32 k = i - list->unknown04;
        if (!(unknowne0[k >> 5] & (1 << (k & 0x1f)))) {
          m_drResMdoAlpTbl->unknown005(k, 0.0f);
        }
      }
    } else if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
      unknown94++;
      unknown90 += m_drResMdoSeamWrkBaseVertex[i].unknown10;
      if (unknowne0[(i + unknown17e) >> 5] & (1 << ((i + unknown17e) & 0x1f))) {
        if (!(unknowna0 & 0x200)) {
          int alpha = static_cast<int>(m_drResMdoAlpTbl->unknown004(i) * 255.0f) + 20;
          if (unknown17c < alpha) {
            alpha = unknown17c;
          }
          if (alpha >= 0x100) {
            m_drResMdoAlpTbl->unknown005(i, 1.0f);
          } else {
            m_drResMdoAlpTbl->unknown005(i, alpha / 255.0f);
          }
        } else {
          s32 k = i;
          bool isPartner = false;
          if (i >= list->unknown04) {
            k = i - list->unknown04;
            isPartner = (unknowne0[k >> 5] & (1 << (k & 0x1f))) != 0;
          }
          if (!isPartner) {
            int alpha = static_cast<int>(m_drResMdoAlpTbl->unknown004(k) * 255.0f) + 20;
            if (unknown17c < alpha) {
              alpha = unknown17c;
            }
            if (alpha >= 0x100) {
              m_drResMdoAlpTbl->unknown005(k, 1.0f);
            } else {
              m_drResMdoAlpTbl->unknown005(k, alpha / 255.0f);
            }
          }
        }
      } else {
        if (!(unknowna0 & 0x200)) {
          int alpha = static_cast<int>(m_drResMdoAlpTbl->unknown004(i) * 255.0f) - 20;
          if (unknown17c < alpha) {
            alpha = unknown17c;
          }
          if (alpha < 0) {
            unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
            unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
            m_drResMdoAlpTbl->unknown005(i, 0.0f);
          } else {
            m_drResMdoAlpTbl->unknown005(i, alpha / 255.0f);
          }
        } else {
          s32 k = i;
          if (i < list->unknown04) {
            s32 partner = i + list->unknown04;
            if (unknowne0[partner >> 5] & (1 << (partner & 0x1f))) {
              unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
              unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
              continue;
            }
          } else {
            k = i - list->unknown04;
            if (unknowne0[k >> 5] & (1 << (k & 0x1f))) {
              unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
              unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
              continue;
            }
          }
          int alpha = static_cast<int>(m_drResMdoAlpTbl->unknown004(k) * 255.0f) - 20;
          if (unknown17c < alpha) {
            alpha = unknown17c;
          }
          if (alpha < 0) {
            unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
            unknowne0[(i + unknown17e * 2) >> 5] |= 1 << ((i + unknown17e * 2) & 0x1f);
            m_drResMdoAlpTbl->unknown005(k, 0.0f);
          } else {
            m_drResMdoAlpTbl->unknown005(k, alpha / 255.0f);
          }
        }
      }
    }
  }
  for (s32 i = 0; i < unknown17e; i++) {
    unknowne0[(i + unknown17e) >> 5] &= ~(1 << ((i + unknown17e) & 0x1f));
  }
}

// The game holds the replacement of the vertex three times (0x710087f8c4, 0x710087f994 and 0x710087fa9c: the memory object released first, the bits i and i + count,
// then DrResMdoSeamWrkBaseVertex::setupVertex inlined with the DrResMdoVertex constructor). The same block as a member helper called three times is not inlined
// (the call stays, 47 instructions against the game's 252, measured), and as a static helper taking the work (inlined) it gives 252 instructions with two induction
// adds of the entry and vertex pointers in the other order (measured, also with the increments swapped), so it is written out (ruling 8). The entry list is read through
// the offset of the resource header (decision 54).
void DrResMdoSeamWrkBase::setVertexCache(u32 index, DrResMdoSeamMemObj *memObj, int size, DrMdoCtlSeamBaseMap *ctl) {
  const unknown782 *list = unknown50;
  const unknown786 *entry = reinterpret_cast<const unknown786 *>(reinterpret_cast<const u8 *>(list) + list->unknown00);
  if (!(unknowna0 & 0x200)) {
    for (s32 i = 0; i < list->unknown04; i++, entry++) {
      if (entry->unknown18 == index) {
        DrResMdoSeamMemObj *old = m_drResMdoSeamWrkBaseVertex[i].m_drResMdoSeamMemObj;
        if (old != nullptr) {
          m_drResMdoSeamWrkBaseVertex[i].release();
          ctl->releaseFreeSeamMemObj(old);
        }
        unknowne0[i >> 5] |= 1 << (i & 0x1f);
        unknowne0[(i + unknown17e) >> 5] |= 1 << ((i + unknown17e) & 0x1f);
        m_drResMdoSeamWrkBaseVertex[i].setupVertex(size, memObj);
        unknown98 = 0;
        return;
      }
    }
  } else {
    for (s32 i = 0; i < list->unknown04; i++, entry++) {
      if (entry->unknown18 == index) {
        DrResMdoSeamMemObj *old = m_drResMdoSeamWrkBaseVertex[i].m_drResMdoSeamMemObj;
        if (old != nullptr) {
          m_drResMdoSeamWrkBaseVertex[i].release();
          ctl->releaseFreeSeamMemObj(old);
        }
        unknowne0[i >> 5] |= 1 << (i & 0x1f);
        unknowne0[(i + unknown17e) >> 5] |= 1 << ((i + unknown17e) & 0x1f);
        m_drResMdoSeamWrkBaseVertex[i].setupVertex(size, memObj);
        unknown98 = 0;
        return;
      }
      if (entry->unknown1c == index) {
        s32 slot = i + list->unknown04;
        DrResMdoSeamMemObj *old = m_drResMdoSeamWrkBaseVertex[slot].m_drResMdoSeamMemObj;
        if (old != nullptr) {
          m_drResMdoSeamWrkBaseVertex[slot].release();
          ctl->releaseFreeSeamMemObj(old);
        }
        unknowne0[slot >> 5] |= 1 << (slot & 0x1f);
        unknowne0[(slot + unknown17e) >> 5] |= 1 << ((slot + unknown17e) & 0x1f);
        m_drResMdoSeamWrkBaseVertex[slot].setupVertex(size, memObj);
        unknown98 = 0;
        return;
      }
    }
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
