#include "dr/dr_res_mdo_seam_parm_read.h"

#include <string.h>

namespace ml {

DrResMdoSeamParmRead::DrResMdoSeamParmRead() {
  unknown00 = 0;
  unknown50 = mm::Vec3(0.0f, 0.0f, 0.0f);
  unknown62c = 0;
  unknown62d = 0;
  unknown40 = 0;
}

DrResMdoSeamParmRead::~DrResMdoSeamParmRead() {}

void DrResMdoSeamParmRead::addPos(const mm::Vec3 &position) {
  unknown00 |= 1;
  unknown10[unknown40] = position;
  unknown40++;
}

void DrResMdoSeamParmRead::setStockEnvMdl(int index) { m_stockEnvMdl = index; }

void DrResMdoSeamParmRead::setStockBaseMap(int index) {
  u64 count = unknown5d0;
  if (count < 8) {
    unknown5d0 = count + 1;
    unknown6a[count] = index;
  }
}

void DrResMdoSeamParmRead::setStockInstMap(int index, DrResMdoSeamWrkInst *work) {
  u64 count = unknown5d2;
  if (count < 8) {
    unknown5d2 = unknown5d2 + 1;
    unknown80[count].m_drResMdoSeamWrkInst = work;
    unknown80[count].unknown08 = index;
    unknown80[count].unknown0a = 2;
  }
}

void DrResMdoSeamParmRead::setStockLowMdl(int index) {
  u64 count = unknown5d4;
  if (count < 8) {
    unknown5d4 = count + 1;
    unknown100[count] = index;
  }
}

void DrResMdoSeamParmRead::setStockMpfMdl(int index) {
  u64 count = unknown5d6;
  if (count < 4) {
    unknown5d6 = count + 1;
    unknown110[count] = index;
  }
}

void DrResMdoSeamParmRead::setStockLight(int index) {
  u64 count = unknown5d8;
  if (count < 4) {
    unknown5d8 = count + 1;
    unknown118[count] = index;
  }
}

void DrResMdoSeamParmRead::begin(wkSeamReadPacDataInf *packet) {
  m_stockEnvMdl = 0;
  unknown5fe = 0;
  unknown5fa = 0;
  unknown5f6 = 0;
  unknown5f2 = 0;
  unknown5ee = 0;
  unknown5e8 = 0;
  unknown5ea = 0;
  unknown5e0 = 0;
  unknown5e2 = 0;
  unknown5e4 = 0;
  unknown5e6 = 0;
  unknown5d8 = 0;
  unknown5da = 0;
  unknown5dc = 0;
  unknown5de = 0;
  unknown5d0 = 0;
  unknown5d2 = 0;
  unknown5d4 = 0;
  unknown5d6 = 0;
  unknown602 = 0;
  unknown604 = 0;
  unknown606 = 0;
  unknown608 = 0;
  unknown600 = 0xffff;
  unknown5fc = 0xffff;
  unknown5f8 = 0xffff;
  unknown5f4 = 0xffff;
  unknown5f0 = 0xffff;
  unknown5ec = 0xffff;
  m_wkSeamReadPacDataInf = packet;
  memset(packet->unknown08, 0, packet->unknown00);
  unknown40 = 0;
  unknown62c = 0;
  unknown00 &= ~0xd;
}

void DrResMdoSeamParmRead::resetTexture() { unknown5e2 = 0; }

void DrResMdoSeamParmRead::resetHeightLvTexture() { unknown5e8 = 0; }

void DrResMdoSeamParmRead::setStockVertex(f32 level, int index) {
  m_wkSeamReadPacDataInf->unknown08[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5ea < index) {
    unknown5ea = index;
  }
  if (index < unknown5ec) {
    unknown5ec = index;
  }
}

void DrResMdoSeamParmRead::setStockTexture(f32 level, int index) {
  m_wkSeamReadPacDataInf->unknown10[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5ee < index) {
    unknown5ee = index;
  }
  if (index < unknown5f0) {
    unknown5f0 = index;
  }
}

// The game adds the entry through the old count (add x8, x0, w8, uxtw #2 at 0x7100879304, before the count store at 0x7100879308): the reference taken with the post-increment gives this;
// the entry written before or after a separate `unknown5e2++` statement takes one more instruction (21 against 20, tried).
void DrResMdoSeamParmRead::setStockTexList(int index) {
  if (unknown5e2 < 8) {
    for (s32 i = 0; i < unknown5e2; i++) {
      if (unknown32c[i].unknown00 == index) {
        return;
      }
    }
    unknown002 &entry = unknown32c[unknown5e2++];
    entry.unknown00 = index;
    entry.unknown02 = 9;
  }
}

// Same shape as setStockTexList (0x710087931c).
void DrResMdoSeamParmRead::setStockHeightTexture(int index) {
  if (unknown5e8 < 3) {
    for (s32 i = 0; i < unknown5e8; i++) {
      if (unknown320[i].unknown02 == 8 && unknown320[i].unknown00 == index) {
        return;
      }
    }
    unknown002 &entry = unknown320[unknown5e8++];
    entry.unknown00 = index;
    entry.unknown02 = 8;
  }
}

bool DrResMdoSeamParmRead::isReadInfo(const _wkSeamReadWait &wait) {
  for (s32 i = 0; i < unknown618; i++) {
    if (m_wkSeamReadCall[i].unknown1e == wait.unknown0a && m_wkSeamReadCall[i].unknown18 == wait.unknown08) {
      return false;
    }
  }
  return true;
}

bool DrResMdoSeamParmRead::isReadAllInfo(const _wkSeamReadWait &wait) {
  for (s32 i = 0; i < unknown618; i++) {
    if (m_wkSeamReadCall[i].unknown1e == wait.unknown0a && m_wkSeamReadCall[i].unknown18 == wait.unknown08) {
      return false;
    }
  }
  for (s32 i = 0; i < unknown628; i++) {
    if (m_wkSeamReadWait[i].unknown0a == wait.unknown0a && m_wkSeamReadWait[i].unknown08 == wait.unknown08) {
      return false;
    }
  }
  return true;
}

void DrResMdoSeamParmRead::setStockBaseVertex(int index, DrResMdoSeamWrkBase *work) {
  m_wkSeamReadPacDataInf->unknown18[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5f2 < index) {
    unknown5f2 = index;
  }
  if (index < unknown5f4) {
    unknown5f4 = index;
  }
  bool isNew = true;
  for (s32 i = 0; i < unknown602; i++) {
    if (unknown3d0[i].unknown00 == work) {
      if (unknown3d0[i].unknown08 < index) {
        unknown3d0[i].unknown08 = index;
      }
      if (index < unknown3d0[i].unknown0a) {
        unknown3d0[i].unknown0a = index;
      }
      isNew = false;
    }
  }
  if (isNew) {
    unknown3d0[unknown602].unknown00 = work;
    unknown3d0[unknown602].unknown08 = index;
    unknown3d0[unknown602].unknown0a = index;
    unknown602++;
  }
}

void DrResMdoSeamParmRead::setStockInstPos(int index, DrResMdoSeamWrkInst *work) {
  m_wkSeamReadPacDataInf->unknown20[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5f6 < index) {
    unknown5f6 = index;
  }
  if (index < unknown5f8) {
    unknown5f8 = index;
  }
  bool isNew = true;
  for (s32 i = 0; i < unknown604; i++) {
    if (unknown450[i].unknown00 == work) {
      if (unknown450[i].unknown08 < index) {
        unknown450[i].unknown08 = index;
      }
      if (index < unknown450[i].unknown0a) {
        unknown450[i].unknown0a = index;
      }
      isNew = false;
    }
  }
  if (isNew) {
    unknown450[unknown604].unknown00 = work;
    unknown450[unknown604].unknown08 = index;
    unknown450[unknown604].unknown0a = index;
    unknown604++;
  }
}

void DrResMdoSeamParmRead::setStockMpfPoli(int index, DrResMdoSeamWrkMpf *work) {
  m_wkSeamReadPacDataInf->unknown28[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5fa < index) {
    unknown5fa = index;
  }
  if (index < unknown5fc) {
    unknown5fc = index;
  }
  bool isNew = true;
  for (s32 i = 0; i < unknown608; i++) {
    if (unknown550[i].unknown00 == work) {
      if (unknown550[i].unknown08 < index) {
        unknown550[i].unknown08 = index;
      }
      if (index < unknown550[i].unknown0a) {
        unknown550[i].unknown0a = index;
      }
      isNew = false;
    }
  }
  if (isNew) {
    unknown550[unknown608].unknown00 = work;
    unknown550[unknown608].unknown08 = index;
    unknown550[unknown608].unknown0a = index;
    unknown608++;
  }
}

void DrResMdoSeamParmRead::setStockMpfInst(int index, DrResMdoSeamWrkMpf *work) {
  m_wkSeamReadPacDataInf->unknown30[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5fe < index) {
    unknown5fe = index;
  }
  if (index < unknown600) {
    unknown600 = index;
  }
  bool isNew = true;
  for (s32 i = 0; i < unknown606; i++) {
    if (unknown4d0[i].unknown00 == work) {
      if (unknown4d0[i].unknown08 < index) {
        unknown4d0[i].unknown08 = index;
      }
      if (index < unknown4d0[i].unknown0a) {
        unknown4d0[i].unknown0a = index;
      }
      isNew = false;
    }
  }
  if (isNew) {
    unknown4d0[unknown606].unknown00 = work;
    unknown4d0[unknown606].unknown08 = index;
    unknown4d0[unknown606].unknown0a = index;
    unknown606++;
  }
}

} // namespace ml
