#include "gf/data/gf_data_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"

namespace gf {

bool GfDataBattle::getClassName(u8 *&bdat, u32 &textId, u32 battleClass) {
  textId = GfBdatBtl::get()->getBTL_ClassName(battleClass);
  if (textId == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpBtlClass();
  return true;
}

const char *GfDataBattle::getClassName(u32 battleClass) {
  u8 *bdat;
  u32 textId;
  const char *className = getClassName(bdat, textId, battleClass) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (className == nullptr) {
    className = "";
  }

  return className;
}

} // namespace gf
