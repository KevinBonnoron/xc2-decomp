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
#include "dr/dr_res_mdo_seam_wrk_inst.h"
#include "dr/dr_res_mdo_seam_wrk_light.h"
#include "dr/dr_res_mdo_seam_wrk_mpf.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class DrResMdoSeamWrkEnv;
class DrResMdoSeamWrkLow;

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

void DrMdoCtlSeamRead::callBaseMapStream(_wkSeamReadWait *wait) {
  const unknown700 *table = reinterpret_cast<const unknown700 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown1c);
  const unknown700 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown38, 0x1000));
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
        _wkSeamReadCall *call = getSeamReadCall();
        call->unknown00 = mem;
        call->unknown08 = base;
        call->unknown20 = entry->unknown38;
        call->unknown1e = 0;
        call->unknown1c = handle;
        call->unknown18 = wait->unknown08;
        call->unknown1a = wait->unknown0c;
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamBase(base);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknownc7c |= 0x200000;
  unknown004(0, entry->unknown38);
}

void DrMdoCtlSeamRead::callInstMapStream(_wkSeamReadWait *wait) {
  const unknown721 *table = reinterpret_cast<const unknown721 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown24);
  const unknown721 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown38, 0x1000));
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
  unknown004(2, entry->unknown38);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfMdlStream(_wkSeamReadWait *wait) {
  const unknown722 *table = reinterpret_cast<const unknown722 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown68);
  const unknown722 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown38, 0x1000));
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
        _wkSeamReadCall *call = getSeamReadCall();
        call->unknown00 = mem;
        call->unknown08 = mpf;
        call->unknown20 = entry->unknown38;
        call->unknown1e = 3;
        call->unknown1c = handle;
        call->unknown18 = wait->unknown08;
        call->unknown1a = wait->unknown0c;
        unknownc7c |= 0x10000;
        return;
      }
      releaseFreeSeamMpf(mpf);
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknown004(3, entry->unknown38);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callBaseVertexStream(_wkSeamReadWait *wait) {
  DrResMdoSeamWrkBase *base = static_cast<DrResMdoSeamWrkBase *>(wait->unknown00);
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownd0);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown04, 0x1000));
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      base->unknowna0 |= 0x10;
      mem->unknown24 |= 4;
      _wkSeamReadCall *call = getSeamReadCall();
      call->unknown00 = mem;
      call->unknown08 = base;
      call->unknown20 = entry->unknown04;
      call->unknown1e = 5;
      call->unknown1c = handle;
      call->unknown18 = wait->unknown08;
      call->unknown1a = wait->unknown0c;
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknown004(5, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callInstPosStream(_wkSeamReadWait *wait) {
  DrResMdoSeamWrkInst *inst = static_cast<DrResMdoSeamWrkInst *>(wait->unknown00);
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown70);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown04, 0x1000));
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      inst->unknown8a |= 0x20;
      mem->unknown24 |= 4;
      _wkSeamReadCall *call = getSeamReadCall();
      call->unknown00 = mem;
      call->unknown08 = inst;
      call->unknown20 = entry->unknown04;
      call->unknown1e = 10;
      call->unknown1c = handle;
      call->unknown18 = wait->unknown08;
      call->unknown1a = wait->unknown0c;
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknown004(10, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfEtclStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown78);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown04, 0x1000));
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(wait->unknown00);
      mpf->unknown5c |= 1;
      mem->unknown24 |= 4;
      _wkSeamReadCall *call = getSeamReadCall();
      call->unknown00 = mem;
      call->unknown08 = mpf;
      call->unknown20 = entry->unknown04;
      call->unknown1e = 11;
      call->unknown1c = handle;
      call->unknown18 = wait->unknown08;
      call->unknown1a = wait->unknown0c;
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknown004(11, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfPolilStream(_wkSeamReadWait *wait) {
  const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknownc8);
  const unknown136 *entry = &table[wait->unknown08];
  DrResMdoSeamMemObj *mem = unknown6e0.createFreeObj(unknown005(entry->unknown04, 0x1000));
  if (mem != nullptr) {
    int handle;
    if (unknowncd0.read(handle, entry->unknown00, entry->unknown04, mem)) {
      DrResMdoSeamWrkMpf *mpf = static_cast<DrResMdoSeamWrkMpf *>(wait->unknown00);
      mpf->unknown5c |= 1;
      mem->unknown24 |= 4;
      _wkSeamReadCall *call = getSeamReadCall();
      call->unknown00 = mem;
      call->unknown08 = mpf;
      call->unknown20 = entry->unknown04;
      call->unknown1e = 12;
      call->unknown1c = handle;
      call->unknown18 = wait->unknown08;
      call->unknown1a = wait->unknown0c;
      unknownc7c |= 0x10000;
      return;
    }
    unknown6e0.releaseFreeObj(mem);
  }
  unknown004(12, entry->unknown04);
  unknownc7c |= 0x200000;
}

void DrMdoCtlSeamRead::waitBaseMapStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initBaseMapParts(static_cast<DrResMdoSeamWrkBase *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

void DrMdoCtlSeamRead::waitLowMdlStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initLowMapParts(static_cast<DrResMdoSeamWrkLow *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

void DrMdoCtlSeamRead::waitInstMapStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initInstMapParts(static_cast<DrResMdoSeamWrkInst *>(call->unknown08), static_cast<DrResMdoSeamWrkInst *>(call->unknown10));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

void DrMdoCtlSeamRead::waitEnvMdlStream(_wkSeamReadCall *call, bool isRead) {
  if (isRead) {
    initEnvMapParts(static_cast<DrResMdoSeamWrkEnv *>(call->unknown08));
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
  } else {
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
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
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
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
    texture->createHeightTexture(unknown005(entry->unknown0c, 0x1000), entry->unknown04);
    texture->unknowna3 = 1;
    unknownc34 += entry->unknown0c;
    unknowncd0.unknown48 &= ~(1 << call->unknown1c);
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
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
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
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > 0) {
      unknownc7c |= 0x400;
    }
  }
}

} // namespace ml
