#include "gf/data/gf_data_nanakoori.h"
#include "gf/data/gf_game_flag.h"
#include "types.h"

// Must not live in gf_data_nanakoori.cpp: when the body of getNanakooriMissionClearFlg1Offset is in the same
// translation unit, Clang sees it is pure, folds its second call in setMissionComplete and the function no longer matches.

namespace gf {

bool GfDataNanakoori::isMissionComplete(u32 mission) {
  u32 offset = getNanakooriMissionClearFlg1Offset(mission);
  return offset != 0 && GfGameFlag::getLocal(1, offset) == 0 ? false : true;
}

void GfDataNanakoori::setMissionComplete(u32 mission) {
  if (isMissionComplete(mission)) {
    return;
  }

  u32 offset = getNanakooriMissionClearFlg1Offset(mission);
  if (offset == 0) {
    return;
  }

  GfGameFlag::setLocal(1, offset, 1);
}

} // namespace gf
