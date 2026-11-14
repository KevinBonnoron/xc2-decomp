#include "gf/menu/tag/gf_menu_tag_enhance.h"

#include <math.h>
#include <string.h>

#include "bdat.h"
#include "framework/lang_util.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"

namespace gf {

const char *GfMenuTagEnhance::getTagName() { return "ML:Enhance"; }

const char *GfMenuTagEnhance::convBegin(const ParamList &params, u16 id) {
  int type = 0;
  for (const mm::mtl::MapPair<const char *, const char *> *it = params.begin(); it != params.end(); ++it) {
    if (strcmp(it->first, "kind") == 0) {
      if (strcmp("Param", it->second) == 0) {
        type = 0;
      } else if (strcmp("Param1", it->second) == 0) {
        type = 1;
      } else if (strcmp("Param2", it->second) == 0) {
        type = 2;
      }
    }
  }

  static mm::mtl::FixStr<256> text;
  text = "****";
  u32 lang = fw::LangUtil::getLangType();
  u8 *enhanceBdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE);
  u8 *effectBdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE_EFF);
  if (id == 0) {
    return text.c_str();
  }

  switch (type) {
  case 0: {
    u32 effect = Bdat::getVal(enhanceBdat, "EnhanceEffect", id).valueU16;
    u32 param = Bdat::getVal(effectBdat, "Param", effect).valueU16;
    text.format("%d", param);
    break;
  }
  case 1: {
    f32 value = Bdat::getVal(enhanceBdat, "Param1", id).valueF32;
    f32 integer;
    if (modff(value, &integer) == 0.0f) {
      text.format("%d", static_cast<u32>(integer));
    } else {
      text.format("%2.1f", value);
      if (lang < 15 && ((1 << lang) & 0x603c) != 0) {
        for (int i = 0; i < text.length(); i++) {
          if (text[i] == '.') {
            text[i] = ',';
          }
        }
      }
    }
    break;
  }
  case 2: {
    f32 value = Bdat::getVal(enhanceBdat, "Param2", id).valueF32;
    f32 integer;
    if (modff(value, &integer) == 0.0f) {
      text.format("%d", static_cast<u32>(integer));
    } else {
      text.format("%2.1f", value);
      if (lang < 15 && ((1 << lang) & 0x603c) != 0) {
        for (int i = 0; i < text.length(); i++) {
          if (text[i] == '.') {
            text[i] = ',';
          }
        }
      }
    }
    break;
  }
  }

  return text.c_str();
}

} // namespace gf
