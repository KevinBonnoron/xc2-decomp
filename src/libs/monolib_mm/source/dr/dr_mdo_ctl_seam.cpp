#include "dr/dr_mdo_ctl_seam.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"

namespace ml {

void *DrMdoCtlSeam::getColiListTbl() { return unknown640[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::getColiListMax() { return unknown650[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::isRead(int index) const {
  if (((unknownc7c >> 28) & 1) == 0) {
    return unknownd1a & (1 << index);
  }
  return 0;
}

void DrMdoCtlSeam::setErrCode(int code, int param) {
  unknowncae[unknowncac] = code;
  unknowncb8[unknowncac] = param;
  s16 next = unknowncac + 1;
  if (next > 3) {
    next = 0;
  }
  unknowncac = next;
}

int DrMdoCtlSeam::calcSemaAlignment(u32 size, u32 alignment) {
  u32 remainder = size % alignment;
  int padding = 0;
  if (remainder != 0) {
    padding = alignment - remainder;
  }
  return padding + size;
}

void DrMdoCtlSeam::seamZPrePassBegin() {
  unknownf2 = 0;
  unknown001();
  m_drMan->unknown5c0->setupCulling(DR_AP_CULL_TYPE_OFF);
}

void DrMdoCtlSeam::seamZPrePassEnd() {}

void DrMdoCtlSeam::seamThicknessPassEnd(bool value) {}

} // namespace ml
