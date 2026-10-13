#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_BLADE_HOMURI_NAME_HIKARI = 0x89fb,
};

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

} // namespace gf
