#include "dr/dr_calc_stm_list_obj.h"

#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrCalcStmRes *DrCalcStmListObj::getResObj(u32 index) { return unknown30[DrMan::s_nDblStockIdx] + index; }

DrCalcStmRes *DrCalcStmListObj::getResVertexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown74]; }

DrCalcStmRes *DrCalcStmListObj::getResShaderObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown76]; }

bool DrCalcStmListObj::isResChange() const { return (unknown80 & (0x400000 << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResSub() const { return (unknown80 & (0x40000 << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResTex() const { return (unknown80 & (0x100000 << DrMan::s_nDblStockIdx)) != 0; }

void DrCalcStmListObj::setUseMode(DrTexUseMode mode) {
  s32 index = DrMan::s_nDblStockIdx;
  if (unknowncc[index] <= mode) {
    unknown80 |= 0x1000000 << index;
    unknowncc[index] = mode;
  }
}

grlib::CGLibTextureBuffer *DrCalcStmListObj::getTexObj(u32 index) { return unknownb0 + index; }

void *DrCalcStmListObj::getAdder() {
  if ((unknown80 & 0x10000) == 0) {
    return nullptr;
  }
  if (unknown48 != nullptr) {
    return unknown48->unknown18;
  }
  return nullptr;
}

DrCalcStmRes *DrCalcStmListObj::getResLowTexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown78]; }

u32 DrCalcStmListObj::texstm_requestWait() {
  unknown88 = 0x13;
  unknownaa--;
  if (unknownaa < 1) {
    unknown1e0 = unknown200;
  }
  return 0;
}

u32 DrCalcStmListObj::texstm_size_Wait() {
  unknown88 = 0xf;
  return 0;
}

} // namespace ml
