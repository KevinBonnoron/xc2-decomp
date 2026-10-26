#include "dr/dr_calc_stm_list_obj.h"

#include "dr/dr_man.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrCalcStmRes *DrCalcStmListObj::getResObj(u32 index) { return unknown30[DrMan::s_nDblStockIdx] + index; }

grlib::CGLibTextureBuffer *DrCalcStmListObj::getTexObj(u32 index) { return unknownb0 + index; }

u32 DrCalcStmListObj::texstm_size_Wait() {
  unknown88 = 0xf;
  return 0;
}

} // namespace ml
