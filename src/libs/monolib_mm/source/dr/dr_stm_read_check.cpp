#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "dr/dr_stm_read_obj.h"
#include "types.h"

namespace ml {

DrStmReadCheck::DrStmReadCheck(const char *path) {
  m_flags = 0;
  m_stmList = DrMan::get()->texStreamMan->createTexStmListObj(path);
}

DrStmReadCheck::DrStmReadCheck(u32 size) {
  m_flags = 4;
  m_stmList = DrMan::get()->texStreamMan->createBufferListObj(size);
}

DrStmReadCheck::~DrStmReadCheck() {
  if (m_stmList != nullptr) {
    m_stmList->release();
    m_stmList = nullptr;
  }
}

void DrStmReadCheck::release() { m_flags |= 1 << DrMan::s_nDblStockIdx; }

u64 DrStmReadCheck::getAdder() {
  if ((m_flags & 4) && m_stmList != nullptr) {
    m_stmList->getAdder();
  }
  return 0;
}

bool DrStmReadCheck::update() {
  bool result = false;
  if (m_flags & (1 << DrMan::s_nDblIdx)) {
    result = true;
  } else if (!(m_flags & 4)) {
    if (m_readType == 2) {
      m_stmList->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_MIDDLE);
    } else if (m_readType == 1) {
      m_stmList->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_LOW);
    } else {
      m_stmList->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_NONE);
    }
  }
  return result;
}

} // namespace ml
