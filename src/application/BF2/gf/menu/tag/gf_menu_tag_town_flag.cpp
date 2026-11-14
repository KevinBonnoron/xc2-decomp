#include "gf/menu/tag/gf_menu_tag_town_flag.h"

#include <stdlib.h>
#include <string.h>

#include "gf/data/gf_game_flag.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"

namespace gf {

enum {
  FLAG_UNKNOWN_506 = 0x1fa,  // Inferred role: first town flag of the four bit flags; original name unknown.
  FLAG_UNKNOWN_1549 = 0x60d, // Inferred role: first town flag of the sixteen bit flags; original name unknown.
  FLAG_UNKNOWN_2120 = 0x848, // Inferred role: first town flag of the eight bit flags; original name unknown.
};

const char *GfMenuTagTownFlag::getTagName() { return "ML:TownFlag"; }

const char *GfMenuTagTownFlag::convBegin(const ParamList &params, u16 id) {
  u16 value = 0;
  int digit = 0;
  for (const mm::mtl::MapPair<const char *, const char *> *it = params.begin(); it != params.end(); ++it) {
    if (strcmp(it->first, "digit") == 0) {
      if (strcmp("F4", it->second) == 0) {
        digit = 0;
      } else if (strcmp("F8", it->second) == 0) {
        digit = 1;
      } else if (strcmp("F16", it->second) == 0) {
        digit = 2;
      }
    } else if (strcmp(it->first, "value") == 0) {
      u32 number = atoi(it->second);
      if (number != 0) {
        value = number;
      }
    }
  }

  static mm::mtl::FixStr<16> text;
  text = "****";
  u32 size;
  int index;
  switch (digit) {
  case 0:
    if (value >= 10) {
      return text.c_str();
    }
    size = 4;
    index = value + FLAG_UNKNOWN_506;
    break;
  case 1:
    if (value >= 100) {
      return text.c_str();
    }
    size = 8;
    index = value + FLAG_UNKNOWN_2120;
    break;
  case 2:
    if (value >= 10) {
      return text.c_str();
    }
    size = 16;
    index = value + FLAG_UNKNOWN_1549;
    break;
  default:
    return text.c_str();
  }

  text.format("%d", GfGameFlag::getLocal(size, index));
  return text.c_str();
}

} // namespace gf
