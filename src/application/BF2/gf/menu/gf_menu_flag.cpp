#include "gf/menu/gf_menu_flag.h"

#include "gf/data/gf_game_flag.h"

namespace gf {

constexpr int MENU_FLAG_COUNT = 100;
constexpr int MENU_FLAG_1BIT_START = 0x9a32;
constexpr int MENU_FLAG_2BIT_START = 0x7ba0;
constexpr int MENU_FLAG_4BIT_START = 0x216;

void GfMenuFlag::set1(int index, u32 value) {
  if (index < MENU_FLAG_COUNT) {
    GfGameFlag::setLocal(1, MENU_FLAG_1BIT_START + index, value);
  }
}

u32 GfMenuFlag::get1(int index) {
  if (index < MENU_FLAG_COUNT) {
    return GfGameFlag::getLocal(1, MENU_FLAG_1BIT_START + index);
  }
  return 0;
}

void GfMenuFlag::set2(int index, u32 value) {
  if (index < MENU_FLAG_COUNT) {
    GfGameFlag::setLocal(2, MENU_FLAG_2BIT_START + index, value);
  }
}

u32 GfMenuFlag::get2(int index) {
  if (index < MENU_FLAG_COUNT) {
    return GfGameFlag::getLocal(2, MENU_FLAG_2BIT_START + index);
  }
  return 0;
}

void GfMenuFlag::set4(int index, u32 value) {
  if (index < MENU_FLAG_COUNT) {
    GfGameFlag::setLocal(4, MENU_FLAG_4BIT_START + index, value);
  }
}

u32 GfMenuFlag::get4(int index) {
  if (index < MENU_FLAG_COUNT) {
    return GfGameFlag::getLocal(4, MENU_FLAG_4BIT_START + index);
  }
  return 0;
}

} // namespace gf
