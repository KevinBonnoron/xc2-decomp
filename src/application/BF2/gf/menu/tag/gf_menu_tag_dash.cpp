#include "gf/menu/tag/gf_menu_tag_dash.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"

namespace gf {

const char *GfMenuTagDash::getTagName() { return "ML:Dash"; }

const char *GfMenuTagDash::convBegin(const ParamList &params, u16 id) { return Bdat::getMSText(GfDataBdat::getFP(BDAT_MENU_TAG_MS), 1); }

} // namespace gf
