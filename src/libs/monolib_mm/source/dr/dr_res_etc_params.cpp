#include "dr/dr_res_etc_params.h"

#include "dr/dr_man.h"

namespace ml {

DrResEtcParams::DrResEtcParams() : unknown00(0), unknown04{0, 0}, unknown0c{0, 0}, unknown14(0) {}

f32 DrResEtcParams::getParams() const { return unknown14; }

void DrResEtcParams::setParams(f32 value) {
  unknown00 |= 1 << DrMan::s_nDblStockIdx;
  unknown04[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::setPreParams(f32 value) {
  unknown00 |= 4 << DrMan::s_nDblStockIdx;
  unknown0c[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::update() {
  if (unknown00 & (1 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(1 << DrMan::s_nDblMemIdx);
    unknown14 = unknown04[DrMan::s_nDblMemIdx];
  }
  if (unknown00 & (4 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(4 << DrMan::s_nDblMemIdx);
    unknown14 = unknown0c[DrMan::s_nDblMemIdx];
  }
}

DrResEtcPamObj::~DrResEtcPamObj() {}

void DrResEtcParams::setInitParams(f32 value) {
  unknown0c[1] = value;
  unknown0c[0] = value;
  unknown04[1] = value;
  unknown04[0] = value;
  unknown14 = value;
}

void DrResEtcPamObj::release(DrResEtcPamObj *&obj) {
  if (obj != nullptr) {
    obj = nullptr;
  }
}

} // namespace ml
