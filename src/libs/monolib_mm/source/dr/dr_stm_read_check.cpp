#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "dr/dr_stm_read_obj.h"
#include "types.h"

namespace ml {

DrStmReadCheck::DrStmReadCheck(const char *path) {
  unknown1c = 0;
  m_drCalcStmListObj = DrMan::get()->m_drCalcTexStreamMan->createTexStmListObj(path);
}

DrStmReadCheck::DrStmReadCheck(u32 size) {
  unknown1c = 4;
  m_drCalcStmListObj = DrMan::get()->m_drCalcTexStreamMan->createBufferListObj(size);
}

DrStmReadCheck::~DrStmReadCheck() {
  if (m_drCalcStmListObj != nullptr) {
    m_drCalcStmListObj->release();
    m_drCalcStmListObj = nullptr;
  }
}

void DrStmReadCheck::release() { unknown1c |= 1 << DrMan::s_nDblStockIdx; }

u64 DrStmReadCheck::getAdder() {
  if ((unknown1c & 4) && m_drCalcStmListObj != nullptr) {
    m_drCalcStmListObj->getAdder();
  }
  return 0;
}

bool DrStmReadCheck::update() {
  bool result = false;
  if (unknown1c & (1 << DrMan::s_nDblIdx)) {
    result = true;
  } else if (!(unknown1c & 4)) {
    if (unknown18 == 2) {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_2);
    } else if (unknown18 == 1) {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_1);
    } else {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_0);
    }
  }
  return result;
}

} // namespace ml
