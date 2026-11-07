#include "gf/menu/tag/gf_menu_tag_pouch.h"

#include "bdat.h"
#include "framework/lang_util.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/fixstr.h"

namespace gf {

const char *GfMenuTagPouch::getTagName() { return "ML:PouchParam"; }

const char *GfMenuTagPouch::convBegin(const ParamList &params, u16 id) {
  u32 index = id >> 2;
  u32 type = id & 3;
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_POUCH_BUFF_SET);
  mm::mtl::FixStr<32> column;
  column.format("PBuffParam%d", type + 1);
  f32 value = Bdat::getVal(bdat, column.c_str(), index).valueF32;
  static mm::mtl::FixStr<16> text;
  text.format("%3.1f", value);
  u32 lang = fw::LangUtil::getLangType();
  if (lang < 15 && ((1 << lang) & 0x603c) != 0) {
    for (int i = 0; i < text.length(); i++) {
      if (text[i] == '.') {
        text[i] = ',';
      }
    }
  }
  return text.c_str();
}

} // namespace gf
