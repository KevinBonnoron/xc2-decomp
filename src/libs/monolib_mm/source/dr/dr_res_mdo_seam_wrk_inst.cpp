#include "dr/dr_res_mdo_seam_wrk_inst.h"

#include <new>
#include <string.h>

#include "dr/dr_calc_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_inst_map.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "dr/dr_res_mdo_pnt_alpha.h"
#include "dr/dr_res_mdo_pos.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_pos_inst.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_occ_uniform_obj.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {

// Inferred role: header of the position tree work; original type name unknown.
struct unknown406 {
  u32 unknown00; // Inferred role: tree offset; original member name unknown.
};

} // namespace

u16 *DrResMdoSeamWrkPosInst::s_pVertexTbl;
u16 *DrResMdoSeamWrkPosInst::s_pTextureTbl;
DrResMdoSeamVertex *DrResMdoSeamWrkPosInst::s_pSeamVertex;
DrResMdoSeamTexture *DrResMdoSeamWrkPosInst::s_pSeamTexture;
DrResMdoSeamParmRead *DrResMdoSeamWrkPosInst::s_pParmRead;

DrResMdoSeamWrkInst::DrResMdoSeamWrkInst()
    : m_mdoWrkMatRes(nullptr), unknown58(nullptr), m_drResMdoVertex(nullptr), unknown70(0), unknown74(0), unknown84(0), unknown88(0), unknown8a(0), unknown98(0), m_drResMdoSeamMemObj(nullptr),
      unknown118(nullptr), unknown128(nullptr), m_drResMdoSeamWrkInst(nullptr), unknown140(0), unknown144(0), unknown156(0), unknown158(0), unknown1b0(nullptr), unknown1b8(nullptr) {}

DrResMdoSeamWrkInst::~DrResMdoSeamWrkInst() { release(); }

void DrResMdoSeamWrkInst::release() {
  if (unknown118 != nullptr) {
    // The game reads the count once, before the loop (0x71008808dc).
    int num = m_mdsSeamInstMapHead->unknown3c + 1;
    for (int i = 0; i < num; i++) {
      unknown118[i].releaseBaseInstPos();
    }
    unknown118 = nullptr;
    unknown140 = 0;
  }
  if (m_drResMdoSeamWrkInst != nullptr) {
    m_drResMdoSeamWrkInst->m_drResMdoSeamWrkInst = nullptr;
  }
  m_drResMdoSeamWrkInst = nullptr;
  for (int i = 0; i < unknown98; i++) {
    if (unknown90[i] != nullptr) {
      mtl::MemManager::deallocate(unknown90[i], 0, false);
      unknown90[i] = nullptr;
    }
  }
  unknown98 = 0;
  if (m_mdoWrkMatRes != nullptr) {
    mtl::MemManager::deallocate(m_mdoWrkMatRes, 0, false);
    m_mdoWrkMatRes = nullptr;
  }
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
  if (m_drResMdoVertex != nullptr) {
    delete m_drResMdoVertex;
    m_drResMdoVertex = nullptr;
  }
  m_drResMdoSeamMemObj = nullptr;
  unknown158 = 0;
}

void DrResMdoSeamWrkInst::releaseCache(DrMdoCtlSeamInstMap *ctl) {
  // The game reads the count once, before the loop (0x7100880a7c).
  int num = m_mdsSeamInstMapHead->unknown3c;
  for (int i = 0; i < num; i++) {
    if ((unknowne8[i >> 5] & (1 << (i & 0x1f))) != 0) {
      if (unknown118[i + 1].m_drResMdoSeamMemObj != nullptr) {
        ctl->releaseFreeSeamMemObj(unknown118[i + 1].m_drResMdoSeamMemObj);
      }
      unknown118[i + 1].releaseBaseInstPos();
    }
  }
  release();
}

// 0x7100880bd8. Inlines DrResMdoPntAlphaMan::setWrk (0x7100872204), the DrResMdoVertex constructor and the DrResMdoSeamWrkPosInst constructor. The size chain adds the point alpha block
// before the alignment that follows the texture list table: the game's order of the first terms (0x7100880d04 to 0x7100880d4c) only appears with the block added first.
void DrResMdoSeamWrkInst::setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, DrMdoCtlSeamInstMap *ctl, const MdsSeamInstMapHead *head,
                                    const u32 *hideBits, u32 max, const DrResMdoInstAnmObj *anm) {
  unknown40 = hideBits;
  unknown70 = 0;
  unknown74 = 0;
  unknown78 = 0;
  unknown154 = 0;
  unknown156 = 0;
  unknown152 = 0;
  unknown144 = 0;
  m_drResMdoSeamWrkInst = nullptr;
  unknown88 = 0;
  unknown8a = 0;
  unknown1b0 = nullptr;
  matRes->unknowna0 = uniforms;
  m_mdoWrkMatRes = matRes;
  m_mdsSeamInstMapHead = head;
  const unknown404 *data = reinterpret_cast<const unknown404 *>(reinterpret_cast<const u8 *>(head) + head->unknown18);
  unknown28 = data;
  unknown30 = reinterpret_cast<const DrMdoCtlPos::unknown018 *>(reinterpret_cast<const u8 *>(data) + data->unknown08);
  unknown38 = reinterpret_cast<const DrMdoCtlPos::unknown019 *>(reinterpret_cast<const u8 *>(data) + data->unknown10);
  if (head->unknown1c != 0) {
    m_drResMdoVertex = new (DrMan::getIns()->unknown10) DrResMdoVertex(reinterpret_cast<const u8 *>(head) + m_mdsSeamInstMapHead->unknown1c);
  } else {
    m_drResMdoVertex = nullptr;
  }
  u32 size = (m_mdsSeamInstMapHead->unknown3c + 1) * (sizeof(DrResMdoSeamWrkPosInst) + sizeof(DrResMdoSeamWrkPosInst *));
  unknown98 = matRes->unknown30 / max;
  if (matRes->unknown30 % max != 0) {
    unknown98++;
  }
  size += unknown98 * sizeof(void *);
  size += m_mdsSeamInstMapHead->unknown4c * sizeof(DrResMdoSeamTexList *);
  size += DrResMdoPntAlphaMan::getWrkSize(15);
  size += -size & 0x1f;
  size += matRes->unknown170 * 0x30;
  size += matRes->unknown170 * 2;
  size += -size & 0x1f;
  size += matRes->unknown170 * (sizeof(unknown002) + sizeof(void *));
  size += -size & 0x1f;
  unknown7c = size;
  size += (matRes->unknown30 / 16 + 1) * 4;
  size += (matRes->unknown30 / 32 + 1) * 4;
  size += (matRes->unknown170 / 16 + 1) * 4;
  size += (matRes->unknown170 / 32 + 1) * 4;
  size += (head->unknown24 / 16 + 1) * 4;
  size += (data->unknown3c / 32 + 1) * 4;
  size += ((head->unknown2c + data->unknown3c) / 32 + 1) * 4;
  size += -size & 0x1f;
  size += 0x80;
  unknown7c = size - unknown7c;
  size += (head->unknown24 / 32 + 1) * 4;
  size += -size & 0x1f;
  size += (head->unknown24 / 16 + 1) * 4;
  size += -size & 0x1f;
  size += (head->unknown3c / 16 + 1) * 4;
  size += -size & 0x1f;
  unknown58 = static_cast<u8 *>(mtl::MemManager::allocate(handle, size, 0x20, false, "no name", 0));
  unknown118 = reinterpret_cast<DrResMdoSeamWrkPosInst *>(unknown58);
  u32 offset = (m_mdsSeamInstMapHead->unknown3c + 1) * sizeof(DrResMdoSeamWrkPosInst);
  unknown120 = reinterpret_cast<DrResMdoSeamWrkPosInst **>(unknown58 + offset);
  offset += (m_mdsSeamInstMapHead->unknown3c + 1) * sizeof(DrResMdoSeamWrkPosInst *);
  unknown90 = reinterpret_cast<void **>(unknown58 + offset);
  offset += unknown98 * sizeof(void *);
  for (int i = 0; i < unknown98; i++) {
    unknown90[i] = nullptr;
  }
  if (m_mdsSeamInstMapHead->unknown4c != 0) {
    unknown110 = reinterpret_cast<DrResMdoSeamTexList **>(unknown58 + offset);
    offset += m_mdsSeamInstMapHead->unknown4c * sizeof(DrResMdoSeamTexList *);
    for (int i = 0; i < m_mdsSeamInstMapHead->unknown4c; i++) {
      unknown110[i] = nullptr;
    }
  }
  u32 pntAlphaSize = DrResMdoPntAlphaMan::setWrk(m_drResMdoPntAlphaMan, 15, unknown58 + offset);
  offset += -offset & 0x1f;
  offset += pntAlphaSize;
  unknown160[0] = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown160[1] = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown160[2] = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown178 = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown180 = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown188 = reinterpret_cast<DrResMdoPos **>(unknown58 + offset);
  offset += matRes->unknown170 * 8;
  unknown190 = reinterpret_cast<u16 *>(unknown58 + offset);
  offset += matRes->unknown170 * 2;
  offset += -offset & 0x1f;
  unknown1a0 = reinterpret_cast<unknown002 *>(unknown58 + offset);
  offset += matRes->unknown170 * 0x20;
  unknown1a8 = unknown58 + offset;
  offset += matRes->unknown170 * 8;
  offset += -offset & 0x1f;
  unknowna0 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (matRes->unknown30 / 16 + 1) * 4;
  unknowna8 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (matRes->unknown30 / 32 + 1) * 4;
  unknownb0 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (matRes->unknown170 / 16 + 1) * 4;
  unknownb8 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (matRes->unknown170 / 32 + 1) * 4;
  unknownc0 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (head->unknown24 / 16 + 1) * 4;
  unknownc8 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (data->unknown3c / 32 + 1) * 4;
  unknownd0 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += ((head->unknown2c + data->unknown3c) / 32 + 1) * 4;
  unknownf8 = reinterpret_cast<u32 *>(unknown58 + offset);
  unknown100 = reinterpret_cast<u32 *>(unknown58 + (offset + 0x40));
  offset += -offset & 0x1f;
  offset += 0x80;
  unknownd8 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (head->unknown24 / 32 + 1) * 4;
  offset += -offset & 0x1f;
  unknowne0 = reinterpret_cast<u32 *>(unknown58 + offset);
  offset += (head->unknown24 / 16 + 1) * 4;
  offset += -offset & 0x1f;
  unknowne8 = reinterpret_cast<u32 *>(unknown58 + offset);
  int posSize = (head->unknown3c / 16 + 1) * 4;
  int clearSize = (head->unknown24 / 32 + 1) * 4;
  clearSize += (32 - clearSize % 32) % 32;
  clearSize += (head->unknown24 / 16 + 1) * 4;
  clearSize += (32 - clearSize % 32) % 32;
  clearSize += posSize;
  clearSize += (32 - clearSize % 32) % 32;
  memset(unknownd8, 0, clearSize);
  int count = m_mdsSeamInstMapHead->unknown3c;
  for (int i = 0; i <= count; i++) {
    new (&unknown118[i]) DrResMdoSeamWrkPosInst();
  }
  unknown140 = 1;
  unknown118->setupBaseInstPos(reinterpret_cast<const u8 *>(unknown28), handle, anm);
  unknown120[0] = unknown118;
  if (m_mdsSeamInstMapHead->unknown4c == 0) {
    unknown8a |= 2;
    grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->m_drPixlMan->getDammyTexObj();
    for (int i = 0; i < m_mdsSeamInstMapHead->unknown24; i++) {
      m_mdoWrkMatRes->unknowne8[i] = dummy;
    }
  }
  unknown138 = ctl->m_drResMdoPosAddList;
  unknown1c0 = DrMan::getIns()->m_drCalcMan->m_drCalcViewWork;
}

void DrResMdoSeamWrkInst::changeMemCall() {
  const MdsSeamInstMapHead *head = reinterpret_cast<const MdsSeamInstMapHead *>(m_drResMdoSeamMemObj->m_buffer);
  m_mdsSeamInstMapHead = head;
  unknown28 = reinterpret_cast<const unknown404 *>(reinterpret_cast<const u8 *>(head) + head->unknown18);
  unknown30 = reinterpret_cast<const DrMdoCtlPos::unknown018 *>(reinterpret_cast<const u8 *>(unknown28) + unknown28->unknown08);
  unknown38 = reinterpret_cast<const DrMdoCtlPos::unknown019 *>(reinterpret_cast<const u8 *>(unknown28) + unknown28->unknown10);
  if (head->unknown1c != 0 && m_drResMdoVertex != nullptr) {
    m_drResMdoVertex->changeMemVertex(reinterpret_cast<const u8 *>(head) + head->unknown1c);
  }
  unknown118->changeMemBaseInstPos(reinterpret_cast<const u8 *>(unknown28));
}

void DrResMdoSeamWrkInst::calcEtcInstPos(DrMdoCtlSeamInstMap *) {
  if (unknown88 > 0x16) {
    for (int i = 0; i < unknown140; i++) {
      unknown120[i]->delCall();
    }
    unknown8a |= 1;
  }
  unknown8a &= 0xfe6f;
  unknown156 = 0;
}

// Same body as DrResMdoSeamWrkBase::callTexReadUpdate (0x710087d080) on the instance map header, plus the release mode (0x710088255c); setStockTexList is inlined (0x71008792cc).
bool DrResMdoSeamWrkInst::callTexReadUpdate(u16 *textureListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamInstMap *ctl, bool isRelease) {
  if (m_mdsSeamInstMapHead->unknown4c != 0) {
    if (isRelease) {
      if ((unknown8a & 2) == 0) {
        return true;
      }
      unknown8a &= ~2;
      for (s32 i = 0; i < m_mdsSeamInstMapHead->unknown4c; i++) {
        unknown110[i] = nullptr;
      }
      s32 count = m_mdsSeamInstMapHead->unknown24;
      for (s32 i = 0; i < count; i++) {
        unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
        unknowne0[(count + i) >> 5] &= ~(1 << ((count + i) & 0x1f));
      }
      return true;
    }
    if (m_mdsSeamInstMapHead->unknown4c > 0) {
      const u16 *index = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(m_mdsSeamInstMapHead) + m_mdsSeamInstMapHead->unknown48);
      bool isRead = false;
      for (s32 i = 0; i < m_mdsSeamInstMapHead->unknown4c; i++, index++) {
        u16 list = textureListFlags[*index];
        if (list == 0) {
          ctl->m_drResMdoSeamParmRead.setStockTexList(*index);
          isRead = true;
        } else {
          texLists[list - 1].unknown3a = 0;
          unknown110[i] = &texLists[list - 1];
        }
      }
      if (isRead) {
        return true;
      }
    }
    if ((unknown8a & 2) == 0) {
      unknown8a |= 2;
      grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->m_drPixlMan->getDammyTexObj();
      const unknown401 *entry = reinterpret_cast<const unknown401 *>(reinterpret_cast<const u8 *>(m_mdsSeamInstMapHead) + m_mdsSeamInstMapHead->unknown20);
      for (s32 i = 0; i < m_mdsSeamInstMapHead->unknown24; i++, entry++) {
        if ((entry->unknown06 & 1) == 0) {
          m_mdoWrkMatRes->unknowne8[i] = dummy;
        } else {
          m_mdoWrkMatRes->unknowne8[i] = unknown110[entry->unknown02]->unknown20 + entry->unknown00;
        }
      }
    }
  }
  return false;
}

void DrResMdoSeamWrkInst::calcCacheInfo() {
  for (int i = 1; i < unknown140; i++) {
    DrResMdoSeamWrkPosInst *pos = unknown120[i];
    if ((pos->m_drResMdoSeamMemObj->unknown24 & 2) != 0) {
      pos->changeMemEtcInstPos();
    }
  }
}

void DrResMdoSeamWrkInst::calcEtcInstPosUpdate(DrMdoCtlSeamInstMap *ctl) {
  // The game reads the speed before the position updates (0x71008828ac).
  f32 speed = ctl->m_frameSpd * DrMan::getIns()->unknown1c8c;
  for (int i = 0; i < unknown140; i++) {
    unknown120[i]->update();
  }
  m_drResMdoPntAlphaMan->update(speed);
}

void DrResMdoSeamWrkInst::seachCheckStreamList(u16 *textureFlags, DrResMdoSeamTexture *textures) {
  s32 count = m_mdsSeamInstMapHead->unknown24;
  int size = (count / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  memset(unknownd8, 0, size);
  const unknown401 *entry = reinterpret_cast<const unknown401 *>(reinterpret_cast<const u8 *>(m_mdsSeamInstMapHead) + m_mdsSeamInstMapHead->unknown20);
  for (int i = 0; i < count; i++, entry++) {
    if ((entry->unknown06 & 2) != 0 && textureFlags[entry->unknown04] != 0) {
      if (textures[textureFlags[entry->unknown04] - 1].unknowna1) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
      }
    } else if ((entry->unknown06 & 1) != 0) {
      if (unknown110[entry->unknown02]->unknown3b) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
      }
    }
  }
}

// Inferred role: moves the loaded bit of a height texture entry of the work to the wanted state and marks the entry as kept when the bit changed; original name unknown.
// Same helper as unknown300 of dr_res_mdo_seam_wrk_base.cpp on the instance tables. One shared helper taking the two bit tables as pointers does not match (414 and 559
// instructions instead of the game's 399 and 549, measured), so each work class has its own, taking the work.
static void unknown301(DrResMdoSeamWrkInst *wrk, s32 bit, s32 i, bool on) {
  if (on) {
    if ((wrk->unknowne0[bit >> 5] & (1 << (bit & 0x1f))) == 0) {
      wrk->unknowne0[bit >> 5] |= 1 << (bit & 0x1f);
      wrk->unknownd8[i >> 5] |= 1 << (i & 0x1f);
    }
  } else if (wrk->unknowne0[bit >> 5] & (1 << (bit & 0x1f))) {
    wrk->unknowne0[bit >> 5] &= ~(1 << (bit & 0x1f));
    wrk->unknownd8[i >> 5] |= 1 << (i & 0x1f);
  }
}

// 0x7100884c20. Inlines DrResMdoSeamParmRead::setStockHeightTexture (defined earlier in this unit, dr_res_mdo_lod_parts.cpp). The game never reads the vertex table and the seam vertices
// (x1 and x2 are unused). The texture entry loop has the shape of DrResMdoSeamWrkBase::calcStaemBaseMapMdl (0x710087db04) on the instance map tables, without the stock texture and the height
// bits of the textures; the height bit handling is the same helper. The not requested block is written out as in calcStaemBaseMapMdl (ruling 8: the helper form of that block gives 357
// instructions against 399 there, measured). The count of the materials of the second loop is read before its test (the loop guard shares the compare chain with the bit test: ccmp), so it is a local
// declared before the bit.
void DrResMdoSeamWrkInst::seachNewStreamList(u16 *vertexTbl, DrResMdoSeamVertex *seamVertex, u16 *textureTbl, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead,
                                             const MdsSeamOfsTexTblData *table, bool isHeight) {
  s32 mdlCount = m_mdoWrkMatRes->unknown170;
  const MdsMdlTopHeader *mdls = m_mdoWrkMatRes->m_mdsMdlTopHeader;
  for (s32 i = 0; i < mdlCount; i++) {
    if (unknownb0[i >> 5] & (1 << (i & 0x1f))) {
      const MdsMdlTopHeader *mdl = &mdls[i];
      s32 num = mdl->unknown04;
      const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(m_mdoWrkMatRes->unknown18 + mdl->unknown00);
      s32 bit = m_mdoWrkMatRes->unknown170 + i;
      if ((unknownb0[bit >> 5] & (1 << (bit & 0x1f))) && isHeight) {
        for (s32 j = 0; j < num; j++, info++) {
          unknowna0[info->unknown0e >> 5] |= 1 << (info->unknown0e & 0x1f);
          s32 heightBit = m_mdoWrkMatRes->unknown30 + info->unknown0e;
          unknowna0[heightBit >> 5] |= 1 << (heightBit & 0x1f);
        }
      } else {
        for (s32 j = 0; j < num; j++, info++) {
          unknowna0[info->unknown0e >> 5] |= 1 << (info->unknown0e & 0x1f);
        }
      }
    }
  }
  s32 count = m_mdsSeamInstMapHead->unknown24;
  s32 matCount = m_mdoWrkMatRes->unknown30;
  for (s32 i = 0; i < matCount; i++) {
    if (unknowna0[i >> 5] & (1 << (i & 0x1f))) {
      MdoWrkMatRes *matRes = m_mdoWrkMatRes;
      const MdsMatInfoHeader *mat = &matRes->unknown28[i];
      s32 num = mat->unknown24;
      s32 bit = matRes->unknown30 + i;
      if (unknowna0[bit >> 5] & (1 << (bit & 0x1f))) {
        const MdsMatTextureInfo *info = reinterpret_cast<const MdsMatTextureInfo *>(matRes->unknown10 + mat->unknown20);
        for (s32 j = 0; j < num; j++, info++) {
          unknownc0[info->unknown00 >> 5] |= 1 << (info->unknown00 & 0x1f);
        }
      }
    }
  }
  s32 size = (count / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  memset(unknownd8, 0, size);
  grlib::CGLibTextureBuffer *dummy = DrMan::getIns()->m_drPixlMan->getDammyTexObj();
  const MdsSeamInstMapHead *head = m_mdsSeamInstMapHead;
  const unknown401 *entry = reinterpret_cast<const unknown401 *>(reinterpret_cast<const u8 *>(head) + head->unknown20);
  for (s32 i = 0; i < count; i++, entry++) {
    if ((entry->unknown06 & 2) == 0) {
      if ((entry->unknown06 & 1) && unknown110[entry->unknown02]->unknown3b) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
      }
    } else if (textureTbl[entry->unknown04] == 0) {
      if (unknowne0[i >> 5] & (1 << (i & 0x1f))) {
        unknowne0[i >> 5] &= ~(1 << (i & 0x1f));
        s32 heightBit = i + count;
        unknowne0[heightBit >> 5] &= ~(1 << (heightBit & 0x1f));
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
        if ((entry->unknown06 & 1) == 0) {
          m_mdoWrkMatRes->unknowne8[i] = dummy;
        } else {
          m_mdoWrkMatRes->unknowne8[i] = unknown110[entry->unknown02]->unknown20 + entry->unknown00;
        }
      } else if ((entry->unknown06 & 1) && unknown110[entry->unknown02]->unknown3b) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
      }
    } else {
      DrResMdoSeamTexture *texture = &seamTexture[textureTbl[entry->unknown04] - 1];
      if (texture->unknowna1) {
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
      }
      if ((unknowne0[i >> 5] & (1 << (i & 0x1f))) == 0) {
        unknowne0[i >> 5] |= 1 << (i & 0x1f);
        unknownd8[i >> 5] |= 1 << (i & 0x1f);
        m_mdoWrkMatRes->unknowne8[i] = &texture->m_cGLibTextureBuffer;
      }
      if (table[entry->unknown04].unknown0c != 0) {
        s32 bit = i + count;
        if ((unknownc0[i >> 5] & (1 << (i & 0x1f))) == 0) {
          unknown301(this, bit, i, texture->unknowna3 == 1);
        } else if (texture->unknowna3 == 1) {
          texture->unknowna2 = 0;
          unknown301(this, bit, i, true);
        } else {
          parmRead->setStockHeightTexture(entry->unknown04 + 1);
          unknown301(this, bit, i, false);
        }
      }
    }
  }
  const u8 *entries = reinterpret_cast<const u8 *>(m_mdsSeamInstMapHead) + m_mdsSeamInstMapHead->unknown20;
  for (s32 i = 0; i < matCount; i++) {
    const MdsMatInfoHeader *mat = &m_mdoWrkMatRes->unknown28[i];
    const MdsMatTextureInfo *infos = reinterpret_cast<const MdsMatTextureInfo *>(m_mdoWrkMatRes->unknown10 + mat->unknown20);
    s32 num = mat->unknown24;
    for (s32 j = 0; j < num; j++) {
      const unknown401 *texEntry = reinterpret_cast<const unknown401 *>(entries + infos[j].unknown00 * 8);
      if ((texEntry->unknown06 & 2) && textureTbl[texEntry->unknown04] == 0) {
        unknowna8[i >> 5] |= 1 << (i & 0x1f);
        break;
      }
    }
  }
  for (s32 i = 0; i < mdlCount; i++) {
    const MdsMdlTopHeader *mdl = &mdls[i];
    const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(m_mdoWrkMatRes->unknown18 + mdl->unknown00);
    s32 num = mdl->unknown04;
    for (s32 j = 0; j < num; j++) {
      if (unknowna8[infos[j].unknown0e >> 5] & (1 << (infos[j].unknown0e & 0x1f))) {
        unknownb8[i >> 5] |= 1 << (i & 0x1f);
        break;
      }
    }
  }
}

u32 DrResMdoSeamWrkInst::isSubMdl(u32 index) {
  u32 bit = m_mdsSeamInstMapHead->unknown2c + index;
  return unknownd0[bit >> 5] & (1 << (bit & 0x1f));
}

void DrResMdoSeamWrkInst::linkRenderMdlList(u32 index, MdoArgSeamInst &arg) {
  unknown128 = unknown120[0];
  chankRenderMdl(unknown128->m_mdsPosRangeTreeData + unknown128->unknown10[index], arg);
}

void DrResMdoSeamWrkInst::linkReadMdl() { unknown88 = 0; }

void DrResMdoSeamWrkInst::linkReadMdl(u32 index) {
  unknown88 = 0;
  unknownc8[index >> 5] |= 1 << (index & 0x1f);
}

void DrResMdoSeamWrkInst::beginMdl() { unknown150 = 0; }

DrResMdoSeamWrkInst::unknown002 *DrResMdoSeamWrkInst::getMdlInfo() {
  u16 index = unknown150;
  if (index < unknown14c) {
    unknown150 = index + 1;
    return &unknown1a0[index];
  }
  return nullptr;
}

void DrResMdoSeamWrkInst::callShadowCacheInstUpdate(u64 mask) {
  for (int i = 0; i < 0x24; i++) {
    if ((1ull << i) & mask) {
      for (int j = 0; j < unknown140; j++) {
        unknown120[j]->clearShwBitTbl(i);
      }
    }
  }
  unknown158 &= ~mask;
}

bool DrResMdoSeamWrkInst::clipRenderMdl(const MdsPosRangeTreeData *tree, MdoArgSeamInst &arg) {
  DrMan::getIns();
  bool isRender = false;
  u32 count = tree->unknown1e;
  const u32 *index = reinterpret_cast<const u32 *>(unknown128->unknown00 + tree->unknown18);
  for (u32 i = 0; i < count; i++, index++) {
    const MdsPosKeepData *keep = unknown128->m_mdsPosKeepData + *index;
    if (keep->unknown66 != 0 && unknown128->clipCheck(keep->unknown66 - 1)) {
      continue;
    }
    u32 gbl = keep->unknown62;
    if (gbl == 0) {
      isRender |= objPartsRenderMdl(keep, &unknown128->m_drResMdoPos[*index], arg);
      continue;
    }
    if ((unknown40[gbl >> 5] & (1 << (gbl & 0x1f))) == 0) {
      DrResMdoPos *pos = &unknown128->m_drResMdoPos[*index];
      f32 objAlpha = 1.0f;
      if (arg.m_drResMdoInstAnmObj->unknown00 != nullptr) {
        objAlpha = arg.m_drResMdoInstAnmObj->getObj(pos->unknown18)->m_alpha;
      }
      if (objAlpha > 0.0f) {
        s32 alpha = arg.unknown00;
        if (objAlpha < 1.0f) {
          arg.unknown00 = objAlpha * 255.0f;
        } else {
          arg.unknown00 = 0;
        }
        isRender |= objPartsRenderMdl(keep, pos, arg);
        arg.unknown00 = alpha;
      }
    }
  }
  return isRender;
}

void DrResMdoSeamWrkInst::seachShadowCheck(DrResMdoInstAnmObj *anm) {
  for (int i = 0; i < unknown140; i++) {
    if (unknown120[i]->unknown68 != 0) {
      DrMan::get();
      DrResMdoSeamWrkPosInst *pos = unknown120[i];
      for (int j = 0; j < pos->unknown68; j++) {
        DrResMdoPosInstAnm *posAnm = anm->m_drResMdoInstPartsAnm[pos->unknown64 + j].m_drResMdoPosInstAnm;
        if (posAnm != nullptr && (posAnm->unknown150 & 0x38) != 0) {
          unknown8a |= 0x80;
          return;
        }
      }
    }
  }
}

void DrResMdoSeamWrkInst::seachReadMdlList(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrMdoCtlSeamInstMap *ctl) {
  unknown128 = unknown120[0];
  DrResMdoSeamWrkPosInst::seachCalcTbl(vertexTbl, textureTbl, seamVertex, seamTexture, &ctl->m_drResMdoSeamParmRead);
  unknown128->seachReadTreeMdl(unknown156);
  if ((unknown128->unknown74 & 1) != 0) {
    if (m_drResMdoSeamWrkInst == nullptr) {
      unknown70 = unknown18->unknown3c + 1;
    } else {
      m_drResMdoSeamWrkInst->unknown88 = 0;
    }
  }
  for (int i = 1; i < unknown140; i++) {
    unknown128 = unknown120[i];
    unknown128->seachReadTreeMdl(unknown156);
  }
}

bool DrResMdoSeamWrkInst::linkShadowRenderMdl(u32 index, DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl, f32 range) {
  unknown128 = unknown120[0];
  unknown48 = unknown128->getShwBitTbl(cache.unknown8f2);
  unknown80 = range;
  ctl->beginResAll(m_mdoWrkMatRes);
  bool isRender = seachShadowInstMapRenderChild(cache, ctl, unknown128->m_mdsPosRangeTreeData + unknown128->unknown10[index]);
  ctl->endResAll();
  return isRender;
}

void DrResMdoSeamWrkInst::linkDefShadowRenderMdl(u32 index, DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl) {
  unknown128 = unknown120[0];
  ctl->beginResAll(m_mdoWrkMatRes);
  seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->m_mdsPosRangeTreeData + unknown128->unknown10[index]);
  ctl->endResAll();
}

bool DrResMdoSeamWrkInst::setEtcPosCache(mtl::ALLOC_HANDLE handle, int index, DrResMdoSeamMemObj *memObj, const DrResMdoInstAnmObj *anm) {
  if ((unknown8a & 5) == 0) {
    const MdsSeamInstMapHead *head = m_mdsSeamInstMapHead;
    const unknown400 *entry = reinterpret_cast<const unknown400 *>(reinterpret_cast<const u8 *>(head) + head->unknown38);
    for (int i = 0; i < head->unknown3c; i++, entry++) {
      if (entry->unknown00 == index) {
        unknowne8[i >> 5] |= 1 << (i & 0x1f);
        unknown118[i + 1].setupEtcInstPos(i, memObj, handle, anm);
        unknown120[unknown140] = &unknown118[i + 1];
        unknown140++;
        unknown158 = 0;
        return true;
      }
    }
  }
  return false;
}

// Inferred role: tests whether the main read position or one of the read request positions lies in the box of an etc position entry; original name unknown.
// The game's code holds the box test (x, z, y order) four times, twice for each use of this helper.
static bool unknown302(const unknown400 *entry, const DrResMdoSeamParmRead *parmRead) {
  const mm::Vec3 &main = parmRead->unknown50;
  if (entry->unknown08 >= main.x && entry->unknown14 <= main.x && entry->unknown10 >= main.z && entry->unknown1c <= main.z && entry->unknown0c >= main.y && entry->unknown18 <= main.y) {
    return true;
  }
  for (int i = 0; i < parmRead->unknown40; i++) {
    const mm::Vec3 &pos = parmRead->unknown10[i];
    if (entry->unknown08 >= pos.x && entry->unknown14 <= pos.x && entry->unknown10 >= pos.z && entry->unknown1c <= pos.z && entry->unknown0c >= pos.y && entry->unknown18 <= pos.y) {
      return true;
    }
  }
  return false;
}

void DrResMdoSeamWrkInst::seachEtcInstPos(DrResMdoSeamParmRead *parmRead, DrMdoCtlSeamInstMap *ctl, bool isFirst) {
  int count = m_mdsSeamInstMapHead->unknown3c;
  const unknown400 *entry = reinterpret_cast<const unknown400 *>(reinterpret_cast<const u8 *>(m_mdsSeamInstMapHead) + m_mdsSeamInstMapHead->unknown38);
  for (int i = 0; i < count; i++, entry++) {
    int del = i + count;
    if (unknowne8[del >> 5] & (1 << (del & 0x1f))) {
      unknown118[i + 1].delCall();
      unknowne8[i >> 5] &= ~(1 << (i & 0x1f));
      unknowne8[del >> 5] &= ~(1 << (del & 0x1f));
      ctl->releaseFreeSeamMemObj(unknown118[i + 1].m_drResMdoSeamMemObj);
      unknown118[i + 1].releaseBaseInstPos();
      for (int j = 1; j < unknown140; j++) {
        if (unknown120[j] == &unknown118[i + 1]) {
          unknown140--;
          for (int k = j; k < unknown140; k++) {
            unknown120[k] = unknown120[k + 1];
          }
          break;
        }
      }
    } else if (unknowne8[i >> 5] & (1 << (i & 0x1f))) {
      if (isFirst || !unknown302(entry, parmRead)) {
        unknowne8[del >> 5] |= 1 << (del & 0x1f);
        unknown118[i + 1].delCall();
      }
    } else if (!isFirst && unknown302(entry, parmRead)) {
      parmRead->setStockInstPos(entry->unknown00, this);
    }
  }
}

// 0x7100888b48. The id is loaded with ldrsh (0x7100888bb8) and the table indexed through an unsigned register (`ldr w8, [x8, w9, uxtw #2]`, 0x7100888bbc), so
// it goes through a u32 local: indexing with `cache.unknown8f0` directly gives `x9, lsl #2`.
bool DrResMdoSeamWrkInst::seachShadowInstMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl) {
  if (unknown18->unknown3e & 1) {
    return false;
  }
  if ((unknown158 & cache.unknown8e8) != 0) {
    return false;
  }
  if ((m_mdsSeamInstMapHead->unknown00 & 4) == 0) {
    u32 id = cache.unknown8f0;
    unknown80 = DrPixlShadowCacheMan::SHADOW_CHECK_RANGE_TBL[id];
    bool isRender = false;
    if (cache.unknown8f0 != 0 && (cache.unknown808 & 8) != 0) {
      isRender = true;
      unknown80 = 15.0f;
    }
    unknown128 = unknown120[0];
    unknown48 = unknown128->getShwBitTbl(cache.unknown8f2);
    const unknown404 *data = unknown28;
    for (int i = 0; i < data->unknown2c; i++) {
      isRender |= seachShadowInstMapRenderChild(cache, ctl, unknown128->m_mdsPosRangeTreeData + i);
    }
    for (int i = 1; i < unknown140; i++) {
      unknown128 = unknown120[i];
      unknown48 = unknown128->getShwBitTbl(cache.unknown8f2);
      const unknown405 *etcData = reinterpret_cast<const unknown405 *>(unknown128->unknown00);
      for (int j = 0; j < etcData->unknown18; j++) {
        isRender |= seachShadowInstMapRenderChild(cache, ctl, unknown128->m_mdsPosRangeTreeData + j);
      }
    }
    if (isRender) {
      return true;
    }
  }
  unknown158 |= cache.unknown8e8;
  return false;
}

void DrResMdoSeamWrkInst::seachDefShadowInstMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl) {
  if ((unknown18->unknown3e & 1) == 0 && (m_mdsSeamInstMapHead->unknown00 & 4) == 0) {
    unknown128 = unknown120[0];
    const unknown404 *data = unknown28;
    for (int i = 0; i < data->unknown2c; i++) {
      seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->m_mdsPosRangeTreeData + i);
    }
    for (int i = 1; i < unknown140; i++) {
      unknown128 = unknown120[i];
      const unknown405 *etcData = reinterpret_cast<const unknown405 *>(unknown128->unknown00);
      for (int j = 0; j < etcData->unknown18; j++) {
        seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->m_mdsPosRangeTreeData + j);
      }
    }
  }
}

// 0x71008896d0. The game holds the body for the two render lists (unknown160[1] at 0x7100889744, unknown160[2] at 0x7100889824) twice; the loop over the list type
// is unrolled by Clang 3.9.1 and matches. DrMdoCtlPos::occRender (0x710081828c) has the same body.
void DrResMdoSeamWrkInst::occRender() {
  if (unknown1b0 != nullptr) {
    DrPixlOccQuery *query = DrMan::getIns()->m_drPixlMan->m_drPixlOccQuery;
    DrResOccUniformObj *uniform = DrMan::getIns()->m_drMdlMan->m_drResOccUniformObj;
    for (unknown002 *info = unknown1b0; info != nullptr; info = info->unknown18) {
      u32 index = info->unknown0c;
      const s16 *posNum = &m_mdoWrkMatRes->m_mdsMdlTopHeader[index].unknown28;
      for (int type = 1; type < 3; type++) {
        for (DrResMdoPos *pos = unknown160[type][index]; pos != nullptr; pos = pos->m_drResMdoPos) {
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

void DrResMdoSeamWrkPosInst::releaseBaseInstPos() {
  if (unknown6c != 0) {
    for (int i = 0; i < unknown6c; i++) {
      m_drResMdoPos[i].release();
    }
    unknown6c = 0;
  }
  m_drResMdoSeamMemObj = nullptr;
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
}

void DrResMdoSeamWrkPosInst::changeMemBaseInstPos(const u8 *data) {
  const unknown404 *header = reinterpret_cast<const unknown404 *>(data);
  unknown00 = data;
  m_mdsPosKeepData = reinterpret_cast<const MdsPosKeepData *>(data + header->unknown18);
  m_mdsPosRangeTreeData = reinterpret_cast<const MdsPosRangeTreeData *>(data + header->unknown28);
  unknown10 = reinterpret_cast<const u32 *>(data + header->unknown20);
  if (header->unknown4c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown4c);
    m_mdsPosReadTreeData = reinterpret_cast<const MdsPosReadTreeData *>(data + unknown20->unknown10);
    unknown30 = reinterpret_cast<const u16 *>(data + unknown20->unknown00);
    unknown38 = reinterpret_cast<const u16 *>(data + unknown20->unknown08);
  }
  for (int i = 0; i < unknown6c; i++) {
    m_drResMdoPos[i].m_mdsPosKeepData = m_mdsPosKeepData + i;
  }
  u32 treeOffset = header->unknown54;
  if (treeOffset != 0) {
    unknown001 *work = unknown40;
    const u8 *base = unknown00;
    work->unknown00 = base;
    work->unknown08 = base + reinterpret_cast<const unknown406 *>(base + treeOffset)->unknown00;
  }
}

void DrResMdoSeamWrkPosInst::seachReadTreeMdl(u32 flags) {
  unknown74 &= 0xfffffffe;
  if (unknown20 != nullptr) {
    for (int i = 0; i < unknown20->unknown18; i++) {
      if ((m_mdsPosReadTreeData[i].unknown2a & flags) == 0) {
        chankReadTreeMdl(&m_mdsPosReadTreeData[i], s_pParmRead->unknown50);
      }
    }
    for (int j = 0; j < s_pParmRead->unknown40; j++) {
      for (int i = 0; i < unknown20->unknown18; i++) {
        if ((m_mdsPosReadTreeData[i].unknown2a & flags) == 0) {
          chankReadTreeMdl(&m_mdsPosReadTreeData[i], s_pParmRead->unknown10[j]);
        }
      }
    }
  }
}

void DrResMdoSeamWrkPosInst::seachCalcTbl(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead) {
  s_pVertexTbl = vertexTbl;
  s_pTextureTbl = textureTbl;
  s_pSeamVertex = seamVertex;
  s_pSeamTexture = seamTexture;
  s_pParmRead = parmRead;
}

void DrResMdoSeamWrkPosInst::delCall() { unknown74 |= 2; }

void DrResMdoSeamWrkPosInst::changeMemEtcInstPos() {
  const u8 *data = m_drResMdoSeamMemObj->m_buffer;
  const unknown405 *header = reinterpret_cast<const unknown405 *>(data);
  unknown00 = data;
  m_mdsPosKeepData = reinterpret_cast<const MdsPosKeepData *>(data + header->unknown04);
  m_mdsPosRangeTreeData = reinterpret_cast<const MdsPosRangeTreeData *>(data + header->unknown14);
  unknown10 = reinterpret_cast<const u32 *>(data + header->unknown0c);
  if (header->unknown2c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown2c);
    m_mdsPosReadTreeData = reinterpret_cast<const MdsPosReadTreeData *>(data + unknown20->unknown10);
    unknown30 = reinterpret_cast<const u16 *>(data + unknown20->unknown00);
    unknown38 = reinterpret_cast<const u16 *>(data + unknown20->unknown08);
  }
  for (int i = 0; i < unknown6c; i++) {
    m_drResMdoPos[i].m_mdsPosKeepData = m_mdsPosKeepData + i;
  }
  u32 treeOffset = header->unknown34;
  if (treeOffset != 0) {
    unknown001 *work = unknown40;
    const u8 *base = unknown00;
    work->unknown00 = base;
    work->unknown08 = base + reinterpret_cast<const unknown406 *>(base + treeOffset)->unknown00;
  }
}

u32 DrResMdoSeamWrkPosInst::getDataSize() const {
  if (m_drResMdoSeamMemObj != nullptr) {
    return m_drResMdoSeamMemObj->m_size;
  }
  return 0;
}

u32 DrResMdoSeamWrkPosInst::clipCheck(u32 index) {
  const u32 *bits = unknown40->unknown18;
  return bits[static_cast<s32>(index) >> 5] & (1 << (index & 0x1f));
}

u32 *DrResMdoSeamWrkPosInst::getShwBitTbl(u32 index) {
  if (unknown60 != 0) {
    return unknown58[index];
  }
  return nullptr;
}

void DrResMdoSeamWrkPosInst::clearShwBitTbl(u32 index) {
  if (unknown60 != 0) {
    memset(unknown58[index], 0, unknown60);
  }
}

void DrResMdoSeamWrkPosInst::clearAllShwBitTbl() {
  if (unknown60 != 0) {
    memset(unknown58[0], 0, unknown60 * 0x24);
  }
}

DrResMdoSeamWrkPosInst::DrResMdoSeamWrkPosInst() : unknown20(nullptr), unknown40(nullptr), m_drResMdoSeamMemObj(nullptr), unknown60(0), unknown6c(0), unknown74(0), unknown78(nullptr) {}

DrResMdoSeamWrkPosInst::~DrResMdoSeamWrkPosInst() { releaseBaseInstPos(); }

} // namespace ml
