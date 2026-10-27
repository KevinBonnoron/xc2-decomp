#include "dr/dr_res_mdo_seam_parm_read.h"

namespace ml {

DrResMdoSeamParmRead::DrResMdoSeamParmRead() {
  unknown00 = 0;
  unknown50 = 0;
  unknown58 = 0;
  unknown62c = 0;
  unknown40 = 0;
}

DrResMdoSeamParmRead::~DrResMdoSeamParmRead() {}

void DrResMdoSeamParmRead::addPos(const mm::Vec3 &position) {
  unknown00 |= 1;
  unknown10[unknown40] = position;
  unknown40++;
}

void DrResMdoSeamParmRead::setStockEnvMdl(int index) { unknown68 = index; }

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
    unknown80[count].unknown00 = work;
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

void DrResMdoSeamParmRead::resetTexture() { unknown5e2 = 0; }

void DrResMdoSeamParmRead::resetHeightLvTexture() { unknown5e8 = 0; }

void DrResMdoSeamParmRead::setStockVertex(f32 level, int index) {
  unknown630->unknown08[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5ea < index) {
    unknown5ea = index;
  }
  if (index < unknown5ec) {
    unknown5ec = index;
  }
}

void DrResMdoSeamParmRead::setStockTexture(f32 level, int index) {
  unknown630->unknown10[index >> 5] |= 1 << (index & 0x1f);
  if (unknown5ee < index) {
    unknown5ee = index;
  }
  if (index < unknown5f0) {
    unknown5f0 = index;
  }
}

bool DrResMdoSeamParmRead::isReadInfo(const _wkSeamReadWait &wait) {
  for (s32 i = 0; i < unknown618; i++) {
    if (unknown610[i].unknown1e == wait.unknown0a && unknown610[i].unknown18 == wait.unknown08) {
      return false;
    }
  }
  return true;
}

} // namespace ml
