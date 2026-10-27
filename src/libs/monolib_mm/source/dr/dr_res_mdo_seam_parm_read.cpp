#include "dr/dr_res_mdo_seam_parm_read.h"

namespace ml {

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

} // namespace ml
