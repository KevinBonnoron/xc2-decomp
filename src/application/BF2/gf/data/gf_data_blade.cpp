#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_BLADE_HOMURI_NAME_HIKARI = 0x89fb,
};

enum {
  BLADE_FIRST = 1001,
  BLADE_SECOND_RANGE_FIRST = 1014,
  BLADE_THIRD_RANGE_FIRST = 1197,
};

constexpr u32 BLADE_FIRST_RANGE_COUNT = 13;
constexpr u32 BLADE_SECOND_RANGE_COUNT = 176;
constexpr u32 BLADE_SECOND_RANGE_INDEX = 20;
constexpr u32 BLADE_THIRD_RANGE_COUNT = 226;

SDataBlade *GfDataBlade::getSDataBlade(u32 blade) {
  u32 index = blade - BLADE_FIRST;
  if (index >= BLADE_FIRST_RANGE_COUNT) {
    if (blade - BLADE_SECOND_RANGE_FIRST < BLADE_SECOND_RANGE_COUNT) {
      index = blade - BLADE_SECOND_RANGE_FIRST + BLADE_SECOND_RANGE_INDEX;
    } else if (blade - BLADE_THIRD_RANGE_FIRST < BLADE_THIRD_RANGE_COUNT) {
      index = blade - BLADE_FIRST;
    } else {
      index = 0;
    }
  }

  return &GfDataManager::getDataGame()->blades[index];
}

bool GfDataBlade::isHikariCurrent() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->hikariCurrent != 0;
}

void GfDataBlade::setHikariCurrent(bool hikariCurrent) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->hikariCurrent = hikariCurrent;
}

bool GfDataBlade::isHomuriNameHikari() {
  u32 flag = GfGameFlag::getLocal(1, FLAG_BLADE_HOMURI_NAME_HIKARI);
  return flag != 0;
}

void GfDataBlade::setHomuriNameHikari(bool homuriNameHikari) { GfGameFlag::setLocal(1, FLAG_BLADE_HOMURI_NAME_HIKARI, homuriNameHikari); }

u32 GfDataBlade::getBladePower(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getBladePower(*getSDataBlade(blade));
}

} // namespace gf
