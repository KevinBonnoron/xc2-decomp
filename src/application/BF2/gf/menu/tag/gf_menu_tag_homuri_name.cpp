#include "gf/menu/tag/gf_menu_tag_homuri_name.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"

namespace gf {

const char *GfMenuTagHomuriName::getTagName() { return "ML:HomuriName"; }

const char *GfMenuTagHomuriName::convBegin(const ParamList &params, u16 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_CMM_HOMURI_NAME_MS);
  if (bdat != nullptr) {
    return Bdat::getVal(bdat, "name", GfDataBlade::isHomuriNameHikari() + Bdat::getIdTop(bdat)).valueString;
  }
  return nullptr;
}

} // namespace gf
