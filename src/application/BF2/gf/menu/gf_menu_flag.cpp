#include "gf/menu/gf_menu_flag.h"

#include "gf/data/gf_game_flag.h"

namespace gf {

// Inferred role: number of flags of each width; original name unknown.
constexpr int MENU_FLAG_UNKNOWN_100 = 100;
// Inferred role: first id of the 1-bit local flags of the menu; original name unknown.
constexpr int MENU_FLAG_UNKNOWN_39474 = 0x9a32;
// Inferred role: first id of the 2-bit local flags of the menu; original name unknown.
constexpr int MENU_FLAG_UNKNOWN_31648 = 0x7ba0;
// Inferred role: first id of the 4-bit local flags of the menu; original name unknown.
constexpr int MENU_FLAG_UNKNOWN_534 = 0x216;

void GfMenuFlag::set1(int index, u32 value) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    GfGameFlag::setLocal(1, MENU_FLAG_UNKNOWN_39474 + index, value);
  }
}

u32 GfMenuFlag::get1(int index) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    return GfGameFlag::getLocal(1, MENU_FLAG_UNKNOWN_39474 + index);
  }
  return 0;
}

void GfMenuFlag::set2(int index, u32 value) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    GfGameFlag::setLocal(2, MENU_FLAG_UNKNOWN_31648 + index, value);
  }
}

u32 GfMenuFlag::get2(int index) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    return GfGameFlag::getLocal(2, MENU_FLAG_UNKNOWN_31648 + index);
  }
  return 0;
}

void GfMenuFlag::set4(int index, u32 value) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    GfGameFlag::setLocal(4, MENU_FLAG_UNKNOWN_534 + index, value);
  }
}

u32 GfMenuFlag::get4(int index) {
  if (index < MENU_FLAG_UNKNOWN_100) {
    return GfGameFlag::getLocal(4, MENU_FLAG_UNKNOWN_534 + index);
  }
  return 0;
}

} // namespace gf
