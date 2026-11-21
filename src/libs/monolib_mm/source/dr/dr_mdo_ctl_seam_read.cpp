#include "dr/dr_mdo_ctl_seam_read.h"

#include <string.h>

#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_base_map.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "dr/dr_res_mdo_seam_wrk_env.h"
#include "dr/dr_res_mdo_seam_wrk_inst.h"
#include "dr/dr_res_mdo_seam_wrk_light.h"
#include "dr/dr_res_mdo_seam_wrk_low.h"
#include "dr/dr_res_mdo_seam_wrk_mpf.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

DrMdoCtlSeamRead::DrMdoCtlSeamRead(int viewNum) : DrMdoCtlSeamLight(viewNum) {}

_wkSeamReadCall *DrMdoCtlSeamRead::getSeamReadCall() {
  _wkSeamReadCall *call = &unknown1370[unknown14b0];
  if (unknown14b0++ > 6) {
    unknownc7c |= 0x80000;
  }
  return call;
}

void DrMdoCtlSeamRead::releaseSeamReadCall(int index) {
  unknown14b0--;
  for (int i = index; i < unknown14b0; i++) {
    memcpy(&unknown1370[i], &unknown1370[i + 1], sizeof(_wkSeamReadCall));
  }
}

// Inferred helper: fills the next read call with the memory object, the work, the read size, the kind and the file handle of a request, the
// statements the game repeats in the call*Stream functions; original name unknown. The size and the handle are taken by reference: by value
// (or only the size by reference) every call*Stream function differs in the register of the read call counter (callEnvMdlStream at
// 0x7100826894). The size is a template parameter because the table entries hold it as u32 in some (low map, env map, light, texture) and as
// s32 in others: one fixed reference type makes a temporary for the other type, and the functions of those entries differ the same way
// (callVertexStream at 0x7100826bb0).
template <typename T> inline void DrMdoCtlSeamRead::unknown007(DrResMdoSeamMemObj *mem, void *work, const T &size, s16 kind, const int &handle, const _wkSeamReadWait *wait) {
  _wkSeamReadCall *call = getSeamReadCall();
  call->unknown00 = mem;
  call->unknown08 = work;
  call->unknown20 = size;
  call->unknown1e = kind;
  call->unknown1c = handle;
  call->unknown18 = wait->unknown08;
  call->unknown1a = wait->unknown0c;
}

void DrMdoCtlSeamRead::callBaseMapStream(_wkSeamReadWait *wait) {
  const unknown700 *table = reinterpret_cast<const unknown700 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown1c);
  const unknown700 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown38);
  if (mem != nullptr) {
    DrResMdoSeamWrkBase *base = unknown290.unknown001();
    if (base != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown34, entry->unknown38, mem)) {
        base->unknown158 = mem;
        base->unknown84 = wait->unknown08;
        base->unknown18 = entry;
        base->unknownb4 = entry->unknown38;
        mem->unknown24 |= 4;
        unknown007(mem, base, entry->unknown38, 0, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamBase(base);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknownc7c |= 0x200000;
  setErrCode(0, entry->unknown38);
}

void DrMdoCtlSeamRead::callLowMdlStream(_wkSeamReadWait *wait) {
  const MdsSeamLowData *table = reinterpret_cast<const MdsSeamLowData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownbc);
  const MdsSeamLowData *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown2c);
  if (mem != nullptr) {
    DrResMdoSeamWrkLow *low = unknown2c8.unknown001();
    if (low != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown28, entry->unknown2c, mem)) {
        low->unknown30 = mem;
        low->unknowna0 = wait->unknown08;
        mem->unknown24 |= 4;
        unknown007(mem, low, entry->unknown2c, 1, handle, wait);
        return;
      }
      releaseFreeSeamLow(low);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(1, entry->unknown2c);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callInstMapStream(_wkSeamReadWait *wait) {
  const unknown721 *table = reinterpret_cast<const unknown721 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown24);
  const unknown721 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown38);
  if (mem != nullptr) {
    DrResMdoSeamWrkInst *inst = unknown300.unknown001();
    if (inst != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown34, entry->unknown38, mem)) {
        inst->unknown108 = mem;
        inst->unknown68 = wait->unknown08;
        inst->unknown18 = entry;
        inst->unknown84 = entry->unknown38;
        mem->unknown24 |= 4;
        // Not through unknown007: the game also stores the linked work between the work and the size (the helper returning the call and the
        // store written after it gives another register for the counter, 0x71008264a8).
        _wkSeamReadCall *call = getSeamReadCall();
        call->unknown00 = mem;
        call->unknown08 = inst;
        call->unknown10 = wait->unknown00;
        call->unknown20 = entry->unknown38;
        call->unknown1e = 2;
        call->unknown1c = handle;
        call->unknown18 = wait->unknown08;
        call->unknown1a = wait->unknown0c;
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamInst(inst);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(2, entry->unknown38);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfMdlStream(_wkSeamReadWait *wait) {
  const unknown722 *table = reinterpret_cast<const unknown722 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown68);
  const unknown722 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown38);
  if (mem != nullptr) {
    DrResMdoSeamWrkMpf *mpf = unknown338.unknown001();
    if (mpf != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown34, entry->unknown38, mem)) {
        mpf->unknown18 = mem;
        mpf->unknown4c = wait->unknown08;
        mpf->unknown28 = entry;
        mpf->unknowne8 = entry->unknown38;
        mem->unknown24 |= 4;
        unknown007(mem, mpf, entry->unknown38, 3, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamMpf(mpf);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(3, entry->unknown38);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callEnvMdlStream(_wkSeamReadWait *wait) {
  const MdsSeamEnvMapData *table = reinterpret_cast<const MdsSeamEnvMapData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown34);
  const MdsSeamEnvMapData *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown38);
  if (mem != nullptr) {
    DrResMdoSeamWrkEnv *env = unknown370.unknown001();
    if (env != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown34, entry->unknown38, mem)) {
        env->unknown60 = mem;
        env->unknown50 = wait->unknown08;
        mem->unknown24 |= 4;
        unknown007(mem, env, entry->unknown38, 4, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamEnvMap(env);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callBaseVertexStream(_wkSeamReadWait *wait) {
  DrResMdoSeamWrkBase *base = static_cast<DrResMdoSeamWrkBase *>(wait->unknown00);
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownd0);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      base->unknowna0 |= 0x10;
      mem->unknown24 |= 4;
      unknown007(mem, base, entry->unknown04, 5, handle, wait);
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(5, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callVertexStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown54);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    DrResMdoSeamVertex *vertex = unknown220.unknown001();
    if (vertex != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
        vertex->unknown2c = wait->unknown08;
        vertex->unknown2a = 0;
        vertex->unknown18 = mem;
        mem->unknown24 |= 4;
        unknown007(mem, vertex, entry->unknown04, 6, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamVertex(vertex, true);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(6, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callTexutreStream(_wkSeamReadWait *wait) {
  const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
  const MdsSeamOfsTexTblData *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    DrResMdoSeamTexture *texture = unknown1b0.unknown001();
    if (texture != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
        texture->unknown9e = wait->unknown08;
        texture->unknowna0 = 0;
        texture->unknown88 = mem;
        mem->unknown24 |= 4;
        unknown007(mem, texture, entry->unknown04, 7, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamTexture(texture, true);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(7, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callHeightTexutreStream(_wkSeamReadWait *wait) {
  if (unknownbe0[wait->unknown08] != 0) {
    const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
    const MdsSeamOfsTexTblData *entry = &table[wait->unknown08];
    u32 heightOffset = calcSemaAlignment(entry->unknown0c, 0x1000);
    u32 size = calcSemaAlignment(entry->unknown04, 0x1000) + heightOffset;
    DrResMdoSeamMemObj *mem = createFreeSeamMemObjBack4K(size);
    if (mem != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown08, entry->unknown0c, mem)) {
        // The game zero-extends the index (umaddl) instead of sign-extending it.
        DrResMdoSeamTexture *texture = &unknown1b0.unknown20[static_cast<u32>(unknownbe0[wait->unknown08] - 1)];
        texture->unknowna0 = 0;
        texture->unknowna2 = 0;
        mem->unknown24 |= 4;
        unknown007(mem, texture, entry->unknown0c, 8, handle, wait);
        memcpy(mem->m_buffer + heightOffset, texture->unknown88->m_buffer, entry->unknown04);
        texture->unknown90 = mem;
        texture->createHeightMoveTexture(heightOffset, entry->unknown04);
        texture->unknown88->unknown24 |= 4;
        return;
      }
      unknown6e0.releaseFreeObj(mem);
    }
    unknownc20 = 0x3c;
    setErrCode(8, entry->unknown0c);
  }
}

void DrMdoCtlSeamRead::callTexListStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown94);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    DrResMdoSeamTexList *texList = unknown1e8.unknown001();
    if (texList != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
        texList->unknown3c = wait->unknown08;
        texList->unknown3a = 0;
        texList->unknown18 = mem;
        mem->unknown24 |= 4;
        unknown007(mem, texList, entry->unknown04, 9, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamTexList(texList, true);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(9, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callInstPosStream(_wkSeamReadWait *wait) {
  DrResMdoSeamWrkInst *inst = static_cast<DrResMdoSeamWrkInst *>(wait->unknown00);
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown70);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      inst->unknown8a |= 0x20;
      mem->unknown24 |= 4;
      unknown007(mem, inst, entry->unknown04, 10, handle, wait);
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(10, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfEtclStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown78);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(wait->unknown00);
      mpf->unknown5c |= 1;
      mem->unknown24 |= 4;
      unknown007(mem, mpf, entry->unknown04, 11, handle, wait);
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(11, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfPolilStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownc8);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown04);
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(wait->unknown00);
      mpf->unknown5c |= 1;
      mem->unknown24 |= 4;
      unknown007(mem, mpf, entry->unknown04, 12, handle, wait);
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(12, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callLightStream(_wkSeamReadWait *wait) {
  const MdsSeamLgtMapData *table = reinterpret_cast<const MdsSeamLgtMapData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown8c);
  const MdsSeamLgtMapData *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = createFreeSeamMemObj4K(entry->unknown1c);
  if (mem != nullptr) {
    DrResMdoSeamWrkLight *light = unknown3a8.unknown001();
    if (light != nullptr) {
      int handle;
      if (unknowncd0.read(handle, entry->unknown18, entry->unknown1c, mem)) {
        light->unknown28 = mem;
        light->unknown30 = wait->unknown08;
        mem->unknown24 |= 4;
        unknown007(mem, light, entry->unknown1c, 13, handle, wait);
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamLight(light);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  setErrCode(13, entry->unknown1c);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::waitBaseMapStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initBaseMapParts(static_cast<DrResMdoSeamWrkBase *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitLowMdlStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initLowMapParts(static_cast<DrResMdoSeamWrkLow *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitInstMapStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initInstMapParts(static_cast<DrResMdoSeamWrkInst *>(call->unknown08), static_cast<DrResMdoSeamWrkInst *>(call->unknown10));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitMpfMdlStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initMpfMapParts(static_cast<DrResMdoSeamWrkMpf *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitEnvMdlStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initEnvMapParts(static_cast<DrResMdoSeamWrkEnv *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitBaseVertexStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamWrkBase *base = static_cast<DrResMdoSeamWrkBase *>(call->unknown08);
  if (isRead) {
    base->setVertexCache(call->unknown18, call->unknown00, call->unknown20, this);
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
    unknownc90 = 0;
  } else {
    base->unknowna0 |= 0x10;
    unknown006(0);
  }
}

void DrMdoCtlSeamRead::waitVertexStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamVertex *vertex = static_cast<DrResMdoSeamVertex *>(call->unknown08);
  vertex->unknown2a = 0;
  if (isRead) {
    const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown54);
    vertex->createVertex();
    unknownc38 += table[vertex->unknown2c].unknown04;
    // Index first: with `unknownbd0[vertex->unknown2c] = vertex->unknown28 + 1;` GVN widens the loads of unknown28 and unknown2c into one
    // 64-bit load, the game keeps two ldrh (0x7100827e1c). The same in waitTexutreStream and waitTexListStream.
    u16 index = vertex->unknown2c;
    unknownbd0[index] = vertex->unknown28 + 1;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(2);
  }
}

void DrMdoCtlSeamRead::waitTexutreStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamTexture *texture = static_cast<DrResMdoSeamTexture *>(call->unknown08);
  texture->unknowna0 = 0;
  if (isRead) {
    const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
    texture->createTexture(table[texture->unknown9e].unknown04);
    unknownc34 += table[texture->unknown9e].unknown04;
    u16 index = texture->unknown9e;
    unknownbe0[index] = texture->unknown9c + 1;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(3);
  }
}

void DrMdoCtlSeamRead::waitHeightTexutreStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamTexture *texture = static_cast<DrResMdoSeamTexture *>(call->unknown08);
  texture->unknowna0 = 0;
  texture->unknowna2 = 0;
  if (texture->unknown90 != nullptr) {
    DrResMdoSeamMemObj *mem = texture->unknown88;
    texture->unknown88 = texture->unknown90;
    texture->unknown90 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
  if (isRead) {
    const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
    const MdsSeamOfsTexTblData *entry = &table[texture->unknown9e];
    texture->createHeightTexture(calcSemaAlignment(entry->unknown0c, 0x1000), entry->unknown04);
    texture->unknowna3 = 1;
    unknownc34 += entry->unknown0c;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  }
}

void DrMdoCtlSeamRead::waitTexListStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamTexList *texList = static_cast<DrResMdoSeamTexList *>(call->unknown08);
  texList->unknown3a = 0;
  if (isRead) {
    const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown94);
    texList->createTextureList(m_drMan->unknown14);
    unknownc34 += table[texList->unknown3c].unknown04;
    u16 index = texList->unknown3c;
    unknownbf0[index] = texList->unknown38 + 1;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(1);
  }
}

void DrMdoCtlSeamRead::waitInstPosStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamWrkInst *inst = static_cast<DrResMdoSeamWrkInst *>(call->unknown08);
  if (isRead) {
    if (!inst->setEtcPosCache(m_drMan->unknown14, call->unknown18, call->unknown00, &unknown698)) {
      unknown6e0.releaseFreeObj(call->unknown00);
    } else {
      unknownc98 = 0;
    }
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
    inst->unknown8a |= 0x20;
  }
}

void DrMdoCtlSeamRead::waitMpfEtcStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(call->unknown08);
  if (isRead) {
    mpf->setEtcMpfCache(call->unknown18, call->unknown00);
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    mpf->unknown5c |= 1;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

void DrMdoCtlSeamRead::waitMpfPoliStream(_wkSeamReadCall *call, bool isRead) {
  DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(call->unknown08);
  if (isRead) {
    mpf->setMpfPoliCache(call->unknown18, call->unknown00);
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    mpf->unknown5c |= 1;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

void DrMdoCtlSeamRead::waitLightStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    DrResMdoSeamWrkLight *light = static_cast<DrResMdoSeamWrkLight *>(call->unknown08);
    const MdsSeamLgtMapData *table = reinterpret_cast<const MdsSeamLgtMapData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown8c);
    const MdsSeamLgtMapData *data = &table[light->unknown30];
    unknownc6c += data->unknown1c;
    unknown723(unknownbc0, light->unknown30) |= 1 << (light->unknown30 & 0x1f);
    unknownc0c++;
    light->setupWork(data);
    DrEnvironmentObj *environment = light->unknown20;
    environment->unknown8c |= 4;
    environment->unknown90 = unknownc88;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknown006(0);
  }
}

} // namespace ml
