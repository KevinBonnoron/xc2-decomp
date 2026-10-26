#include "dr/dr_res_etc_params.h"

namespace ml {

DrResEtcParams::DrResEtcParams() : unknown00(0), unknown04(0), unknown08(0), unknown0c(0), unknown10(0), unknown14(0) {}

f32 DrResEtcParams::getParams() const { return unknown14; }

DrResEtcPamObj::~DrResEtcPamObj() {}

void DrResEtcParams::setInitParams(f32 value) {
  unknown10 = value;
  unknown0c = value;
  unknown08 = value;
  unknown04 = value;
  unknown14 = value;
}

void DrResEtcPamObj::release(DrResEtcPamObj *&obj) {
  if (obj != nullptr) {
    obj = nullptr;
  }
}

} // namespace ml
