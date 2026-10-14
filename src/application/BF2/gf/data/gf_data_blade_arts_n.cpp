#include "gf/data/gf_data_blade_arts_n.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"

namespace gf {

bool GfDataBladeArtsN::getName(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getBTL_BuffName(arts);
  bdat = GfBdatMsg::getFpBlBuffMs();
  return textId != 0;
}

const char *GfDataBladeArtsN::getName(u32 arts) {
  u8 *bdat;
  u32 textId;
  if (getName(bdat, textId, arts)) {
    const char *name = Bdat::getMSText(bdat, textId);
    if (name != nullptr) {
      return name;
    }
  }

  return "";
}

bool GfDataBladeArtsN::getCaption(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getBTL_BuffCaption(arts);
  bdat = GfBdatMsg::getFpBlBuffCap();
  return textId != 0;
}

const char *GfDataBladeArtsN::getCaption(u32 arts) {
  u8 *bdat;
  u32 textId;
  if (getCaption(bdat, textId, arts)) {
    const char *caption = Bdat::getMSText(bdat, textId);
    if (caption != nullptr) {
      return caption;
    }
  }

  return "";
}

} // namespace gf
