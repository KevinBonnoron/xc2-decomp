#include "dr/dr_calc_stm_work.h"

#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrCalcStmWork::DrCalcStmWork() : unknown00(nullptr), unknown08(0), unknown10(nullptr) {}

int DrCalcStmWork::getWorkSize(u32 count) { return count * sizeof(grlib::CGLibTextureBuffer); }

grlib::CGLibTextureBuffer *DrCalcStmWork::getTexObj(u32 index) { return &unknown00[index]; }

void DrCalcStmWork::texRelease() {
  for (int i = 0; i < unknown08; i++) {
    unknown00[i].release();
  }
}

} // namespace ml
