#include "dr/dr_res_mdo_seam_wrk_inst.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_inst_map.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "dr/dr_res_mdo_pnt_alpha.h"
#include "dr/dr_res_mdo_pos.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_pos_inst.h"
#include "dr/dr_res_mdo_vertex.h"
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
    : unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown70(0), unknown74(0), unknown84(0), unknown88(0), unknown8a(0), unknown98(0), unknown108(nullptr), unknown118(nullptr),
      unknown128(nullptr), unknown130(nullptr), unknown140(0), unknown144(0), unknown156(0), unknown158(0), unknown1b0(nullptr), unknown1b8(nullptr) {}

DrResMdoSeamWrkInst::~DrResMdoSeamWrkInst() { release(); }

void DrResMdoSeamWrkInst::release() {
  if (unknown118 != nullptr) {
    // The game reads the count once, before the loop (0x71008808dc).
    int num = unknown20->unknown3c + 1;
    for (int i = 0; i < num; i++) {
      unknown118[i].releaseBaseInstPos();
    }
    unknown118 = nullptr;
    unknown140 = 0;
  }
  if (unknown130 != nullptr) {
    unknown130->unknown130 = nullptr;
  }
  unknown130 = nullptr;
  for (int i = 0; i < unknown98; i++) {
    if (unknown90[i] != nullptr) {
      mtl::MemManager::deallocate(unknown90[i], 0, false);
      unknown90[i] = nullptr;
    }
  }
  unknown98 = 0;
  if (unknown50 != nullptr) {
    mtl::MemManager::deallocate(unknown50, 0, false);
    unknown50 = nullptr;
  }
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  unknown108 = nullptr;
  unknown158 = 0;
}

void DrResMdoSeamWrkInst::releaseCache(DrMdoCtlSeamInstMap *ctl) {
  // The game reads the count once, before the loop (0x7100880a7c).
  int num = unknown20->unknown3c;
  for (int i = 0; i < num; i++) {
    if ((unknowne8[i >> 5] & (1 << (i & 0x1f))) != 0) {
      if (unknown118[i + 1].unknown50 != nullptr) {
        ctl->releaseFreeSeamMemObj(unknown118[i + 1].unknown50);
      }
      unknown118[i + 1].releaseBaseInstPos();
    }
  }
  release();
}

void DrResMdoSeamWrkInst::changeMemCall() {
  const MdsSeamInstMapHead *head = reinterpret_cast<const MdsSeamInstMapHead *>(unknown108->m_buffer);
  unknown20 = head;
  unknown28 = reinterpret_cast<const unknown404 *>(reinterpret_cast<const u8 *>(head) + head->unknown18);
  unknown30 = reinterpret_cast<const DrMdoCtlPos::unknown018 *>(reinterpret_cast<const u8 *>(unknown28) + unknown28->unknown08);
  unknown38 = reinterpret_cast<const DrMdoCtlPos::unknown019 *>(reinterpret_cast<const u8 *>(unknown28) + unknown28->unknown10);
  if (head->unknown1c != 0 && unknown60 != nullptr) {
    unknown60->changeMemVertex(reinterpret_cast<const u8 *>(head) + head->unknown1c);
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

void DrResMdoSeamWrkInst::calcCacheInfo() {
  for (int i = 1; i < unknown140; i++) {
    DrResMdoSeamWrkPosInst *pos = unknown120[i];
    if ((pos->unknown50->unknown24 & 2) != 0) {
      pos->changeMemEtcInstPos();
    }
  }
}

void DrResMdoSeamWrkInst::calcEtcInstPosUpdate(DrMdoCtlSeamInstMap *ctl) {
  // The game reads the speed before the position updates (0x71008828ac).
  f32 speed = ctl->unknowndc * DrMan::getIns()->unknown1c8c;
  for (int i = 0; i < unknown140; i++) {
    unknown120[i]->update();
  }
  unknown198->update(speed);
}

void DrResMdoSeamWrkInst::seachCheckStreamList(u16 *textureFlags, DrResMdoSeamTexture *textures) {
  s32 count = unknown20->unknown24;
  int size = (count / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  memset(unknownd8, 0, size);
  const unknown401 *entry = reinterpret_cast<const unknown401 *>(reinterpret_cast<const u8 *>(unknown20) + unknown20->unknown20);
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

u32 DrResMdoSeamWrkInst::isSubMdl(u32 index) {
  u32 bit = unknown20->unknown2c + index;
  return unknownd0[bit >> 5] & (1 << (bit & 0x1f));
}

void DrResMdoSeamWrkInst::linkRenderMdlList(u32 index, MdoArgSeamInst &arg) {
  unknown128 = unknown120[0];
  chankRenderMdl(unknown128->unknown18 + unknown128->unknown10[index], arg);
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
    const MdsPosKeepData *keep = unknown128->unknown08 + *index;
    if (keep->unknown66 != 0 && unknown128->clipCheck(keep->unknown66 - 1)) {
      continue;
    }
    u32 gbl = keep->unknown62;
    if (gbl == 0) {
      isRender |= objPartsRenderMdl(keep, &unknown128->unknown48[*index], arg);
      continue;
    }
    if ((unknown40[gbl >> 5] & (1 << (gbl & 0x1f))) == 0) {
      DrResMdoPos *pos = &unknown128->unknown48[*index];
      f32 objAlpha = 1.0f;
      if (arg.unknown10->unknown00 != nullptr) {
        objAlpha = arg.unknown10->getObj(pos->unknown18)->unknown28;
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
        DrResMdoPosInstAnm *posAnm = anm->unknown10[pos->unknown64 + j].unknown30;
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
  DrResMdoSeamWrkPosInst::seachCalcTbl(vertexTbl, textureTbl, seamVertex, seamTexture, &ctl->unknownd30);
  unknown128->seachReadTreeMdl(unknown156);
  if ((unknown128->unknown74 & 1) != 0) {
    if (unknown130 == nullptr) {
      unknown70 = unknown18->unknown3c + 1;
    } else {
      unknown130->unknown88 = 0;
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
  ctl->beginResAll(unknown50);
  bool isRender = seachShadowInstMapRenderChild(cache, ctl, unknown128->unknown18 + unknown128->unknown10[index]);
  ctl->endResAll();
  return isRender;
}

void DrResMdoSeamWrkInst::linkDefShadowRenderMdl(u32 index, DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl) {
  unknown128 = unknown120[0];
  ctl->beginResAll(unknown50);
  seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->unknown18 + unknown128->unknown10[index]);
  ctl->endResAll();
}

bool DrResMdoSeamWrkInst::setEtcPosCache(mtl::ALLOC_HANDLE handle, int index, DrResMdoSeamMemObj *memObj, const DrResMdoInstAnmObj *anm) {
  if ((unknown8a & 5) == 0) {
    const MdsSeamInstMapHead *head = unknown20;
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

void DrResMdoSeamWrkInst::seachDefShadowInstMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl) {
  if ((unknown18->unknown3e & 1) == 0 && (unknown20->unknown00 & 4) == 0) {
    unknown128 = unknown120[0];
    const unknown404 *data = unknown28;
    for (int i = 0; i < data->unknown2c; i++) {
      seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->unknown18 + i);
    }
    for (int i = 1; i < unknown140; i++) {
      unknown128 = unknown120[i];
      const unknown405 *etcData = reinterpret_cast<const unknown405 *>(unknown128->unknown00);
      for (int j = 0; j < etcData->unknown18; j++) {
        seachDefShadowInstMapRenderChild(shadow, ctl, unknown128->unknown18 + j);
      }
    }
  }
}

void DrResMdoSeamWrkPosInst::releaseBaseInstPos() {
  if (unknown6c != 0) {
    for (int i = 0; i < unknown6c; i++) {
      unknown48[i].release();
    }
    unknown6c = 0;
  }
  unknown50 = nullptr;
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
}

void DrResMdoSeamWrkPosInst::changeMemBaseInstPos(const u8 *data) {
  const unknown404 *header = reinterpret_cast<const unknown404 *>(data);
  unknown00 = data;
  unknown08 = reinterpret_cast<const MdsPosKeepData *>(data + header->unknown18);
  unknown18 = reinterpret_cast<const MdsPosRangeTreeData *>(data + header->unknown28);
  unknown10 = reinterpret_cast<const u32 *>(data + header->unknown20);
  if (header->unknown4c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown4c);
    unknown28 = reinterpret_cast<const MdsPosReadTreeData *>(data + unknown20->unknown10);
    unknown30 = reinterpret_cast<const u16 *>(data + unknown20->unknown00);
    unknown38 = reinterpret_cast<const u16 *>(data + unknown20->unknown08);
  }
  for (int i = 0; i < unknown6c; i++) {
    unknown48[i].unknown08 = unknown08 + i;
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
      if ((unknown28[i].unknown2a & flags) == 0) {
        chankReadTreeMdl(&unknown28[i], s_pParmRead->unknown50);
      }
    }
    for (int j = 0; j < s_pParmRead->unknown40; j++) {
      for (int i = 0; i < unknown20->unknown18; i++) {
        if ((unknown28[i].unknown2a & flags) == 0) {
          chankReadTreeMdl(&unknown28[i], s_pParmRead->unknown10[j]);
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
  const u8 *data = unknown50->m_buffer;
  const unknown405 *header = reinterpret_cast<const unknown405 *>(data);
  unknown00 = data;
  unknown08 = reinterpret_cast<const MdsPosKeepData *>(data + header->unknown04);
  unknown18 = reinterpret_cast<const MdsPosRangeTreeData *>(data + header->unknown14);
  unknown10 = reinterpret_cast<const u32 *>(data + header->unknown0c);
  if (header->unknown2c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown2c);
    unknown28 = reinterpret_cast<const MdsPosReadTreeData *>(data + unknown20->unknown10);
    unknown30 = reinterpret_cast<const u16 *>(data + unknown20->unknown00);
    unknown38 = reinterpret_cast<const u16 *>(data + unknown20->unknown08);
  }
  for (int i = 0; i < unknown6c; i++) {
    unknown48[i].unknown08 = unknown08 + i;
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
  if (unknown50 != nullptr) {
    return unknown50->m_size;
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

DrResMdoSeamWrkPosInst::DrResMdoSeamWrkPosInst() : unknown20(nullptr), unknown40(nullptr), unknown50(nullptr), unknown60(0), unknown6c(0), unknown74(0), unknown78(nullptr) {}

DrResMdoSeamWrkPosInst::~DrResMdoSeamWrkPosInst() { releaseBaseInstPos(); }

} // namespace ml
