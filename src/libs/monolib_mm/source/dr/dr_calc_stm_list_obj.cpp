#include "dr/dr_calc_stm_list_obj.h"

#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture_buffer.h"
#include "ml/dev_file_th.h"

namespace ml {

void DrCalcStmListObj::setHeaderInfo(const u8 *header) {
  if (unknown80 & 0x2000) {
    setupInfo(header, true);
    unknown80 &= ~0x6000;
  }
}

unknown035 *DrCalcStmListObj::getResObj(u32 index) { return unknown30[DrMan::s_nDblStockIdx] + index; }

unknown035 *DrCalcStmListObj::getResVertexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown74]; }

unknown035 *DrCalcStmListObj::getResShaderObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown76]; }

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

unknown035 *DrCalcStmListObj::getResLowTexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown78]; }

bool DrCalcStmListObj::texstm_requestWait() {
  unknown88 = 0x13;
  unknownaa--;
  if (unknownaa < 1) {
    unknown1e0 = unknown200;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_size_Wait() {
  unknown88 = 0xf;
  return 0;
}

void DrCalcStmListObj::setupReadCheck() {
  if (unknown50 != nullptr) {
    DrCalcTexStreamMan::get()->clearMemObj(unknown50);
    unknown50 = nullptr;
  }
  unknown1e0 = unknown1f0;
  unknown80 |= 0x8000;
}

bool DrCalcStmListObj::texstm_notfileWait() {
  unknown88 = 0x13;
  unknown80 |= 0x1000;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_oldVerWait() {
  unknown88 = 4;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_stmchk_setWait() {
  unknown88 = 3;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_defErrWait() {
  unknown88 = 7;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_defRead;
    return 1;
  }
  return 0;
}

void DrCalcStmListObj::chacheDefClear() {
  for (s32 i = 0; i < unknowna2; i++) {
    DrCalcTexStmObj **objects = unknown28;
    DrCalcTexStmObj *object = objects[i];
    if (object != nullptr) {
      DrCalcTexStreamMan::get()->clearMemObj(object);
      objects[i] = nullptr;
    }
  }
  unknown80 &= ~8u;
  unknown94 = 0;
}

void DrCalcStmListObj::update() {
  if (unknown80 & (0x1000000 << DrMan::s_nDblIdx)) {
    s32 index = DrMan::s_nDblIdx;
    s32 mode = unknowncc[index];
    unknown80 &= ~(0x1000000 << index);
    unknownc8 = mode;
    unknowncc[index] = 0;
  }
  if (unknowna6 == 0) {
    unknownc8 = 0;
  }
  while ((this->*unknown1e0)()) {
  }
}

bool DrCalcStmListObj::texstm_defMidtexErrWait() {
  unknown88 = 10;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_deTexCheck;
    return 1;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_fastErrWait() {
  unknown88 = 0x11;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_checkTexStm;
    return 1;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_defupdate() {
  unknown88 = 0x13;
  if (unknownc8 != 0) {
    unknown8c = 0;
  }
  if (!(unknown80 & 0x10)) {
    unknown1e0 = &DrCalcStmListObj::texstm_checkTexStm;
  }
  return 0;
}

bool DrCalcStmListObj::OnFileEvent(EventFileTh *event) {
  if (event->type != EventFileTh::TYPE_COMPLETE) {
    unknown40 = nullptr;
    unknown80 = (unknown80 & ~0x0c000000u) | 0x08000000;
    return 0;
  }
  if (unknown40 != event->unknown08) {
    return 0;
  }
  unknown80 &= ~0x04000000u;
  unknown40 = nullptr;
  return 1;
}

} // namespace ml
