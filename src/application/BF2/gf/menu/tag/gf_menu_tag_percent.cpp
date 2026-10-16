#include "gf/menu/tag/gf_menu_tag_percent.h"

#include "framework/lang_util.h"

namespace gf {

const char *GfMenuTagPercent::getTagName() { return "ML:%"; }

const char *GfMenuTagPercent::convBegin(const ParamList &params, u16 id) {
  switch (fw::LangUtil::getLangType()) {
  case 2:
  case 3:
  case 5:
  case 13:
  case 14:
    return " %";
  default:
    return "%";
  }
}

} // namespace gf
