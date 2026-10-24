#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "dr/dr_stm_read_obj.h"
#include "types.h"

namespace ml {

DrStmReadCheck::DrStmReadCheck(const char *path) {
  unknown1c = 0;
  unknown20 = DrMan::get()->unknown5b0->createTexStmListObj(path);
}

DrStmReadCheck::DrStmReadCheck(u32 size) {
  unknown1c = 4;
  unknown20 = DrMan::get()->unknown5b0->createBufferListObj(size);
}

DrStmReadCheck::~DrStmReadCheck() {
  if (unknown20 != nullptr) {
    unknown20->release();
    unknown20 = nullptr;
  }
}

void DrStmReadCheck::release() { unknown1c |= 1 << DrMan::s_nDblStockIdx; }

u64 DrStmReadCheck::getAdder() {
  if ((unknown1c & 4) && unknown20 != nullptr) {
    unknown20->getAdder();
  }
  return 0;
}

bool DrStmReadCheck::update() {
  bool result = false;
  if (unknown1c & (1 << DrMan::s_nDblIdx)) {
    result = true;
  } else if (!(unknown1c & 4)) {
    if (unknown18 == 2) {
      unknown20->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_MIDDLE);
    } else if (unknown18 == 1) {
      unknown20->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_LOW);
    } else {
      unknown20->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_NONE);
    }
  }
  return result;
}

} // namespace ml
