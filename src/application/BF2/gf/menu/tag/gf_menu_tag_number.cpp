#include "gf/menu/tag/gf_menu_tag_number.h"

#include <stdlib.h>
#include <string.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"

namespace gf {

const char *GfMenuTagNumber::getTagName() { return "ML:number"; }

const char *GfMenuTagNumber::convBegin(const ParamList &params, u16 id) {
  int padding = 0;
  u32 digit = 1;
  for (const mm::mtl::MapPair<const char *, const char *> *it = params.begin(); it != params.end(); ++it) {
    if (strcmp(it->first, "digit") == 0) {
      u32 number = atoi(it->second);
      if (number != 0) {
        digit = number;
      }
    } else if (strcmp(it->first, "padding") == 0) {
      if (strcmp("none", it->second) == 0) {
        padding = 0;
      }
      if (strcmp("space", it->second) == 0) {
        padding = 1;
      }
      if (strcmp("zero", it->second) == 0) {
        padding = 2;
      }
    }
  }

  static mm::mtl::FixStr<16> text;
  switch (padding) {
  case 0:
    text = "%d";
    break;
  case 1:
    text.format("%%%dd", digit);
    break;
  case 2:
    text.format("%%0%dd", digit);
    break;
  }

  return text.c_str();
}

} // namespace gf
