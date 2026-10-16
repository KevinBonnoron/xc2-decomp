#include "gf/menu/tag/gf_menu_tag_number_money.h"

#include "framework/lang_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_util.h"

namespace gf {

const char *GfMenuTagNumberMoney::getTagName() { return "ML:number_money"; }

const char *GfMenuTagNumberMoney::convBegin(const ParamList &params, u16 id) {
  static mm::mtl::FixStr<16> format;
  if (ui::UIUtil::getMoneySeparetor(fw::LangUtil::getLangType()) != 0) {
    format = "%s";
  } else {
    format = "%d";
  }
  return format.c_str();
}

} // namespace gf
