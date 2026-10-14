#include "gf/data/gf_data_enhance.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"

namespace gf {

bool GfDataEnhance::getCaption(u8 *&bdat, u32 &textId, u32 enhance) {
  if (enhance == 0) {
    return false;
  }

  textId = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
  bdat = GfBdatMsg::getFpBtlEnhanceCap();
  return textId != 0;
}

const char *GfDataEnhance::getCaption(u32 enhance) {
  u8 *bdat;
  u32 textId;
  const char *caption = getCaption(bdat, textId, enhance) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (caption == nullptr) {
    caption = "";
  }

  return caption;
}

} // namespace gf
