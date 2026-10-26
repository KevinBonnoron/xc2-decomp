#include "dr/dr_shd_man.h"

#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"

namespace ml {

void DrShdMan::debugRender() {}

void DrShdMan::beforeUpdateCate(int cate) { unknown18->unknown58->update(cate); }

void DrShdMan::resetColorBuff(int index) {
  if (unknown18 != nullptr && unknown18->unknown58 != nullptr) {
    unknown18->unknown58->resetColorBuff(index);
  }
}

} // namespace ml
