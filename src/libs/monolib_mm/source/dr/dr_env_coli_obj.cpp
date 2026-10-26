#include "dr/dr_env_coli_obj.h"

#include "dr/dr_man.h"

namespace ml {

DrEnvColiObj::DrEnvColiObj(DrMan *man) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), unknown30(man), unknown38(0) {}

void DrEnvColiObj::release() { unknown38 |= 1 << DrMan::s_nDblStockIdx; }

void DrEnvColiObj::setPause(bool isPause) {
  if (isPause) {
    unknown38 |= 4;
  } else {
    unknown38 &= ~4;
  }
}

bool DrEnvColiObj::isPause() const { return (unknown38 >> 2 & 1) != 0; }

u32 DrEnvColiObj::isDeleteCall() const { return unknown38 & (1 << DrMan::s_nDblIdx); }

u32 DrEnvColiObj::isDeleteAll() const { return unknown38 & 3; }

} // namespace ml
