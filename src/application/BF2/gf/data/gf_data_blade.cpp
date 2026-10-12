#include "gf_data_blade.h"
#include "gf_data_manager.h"
#include "gf_game_flag.h"

namespace gf {
bool GfDataBlade::isHikariCurrent() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->hikariCurrent != 0;
}

void GfDataBlade::setHikariCurrent(bool hikariCurrent) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->hikariCurrent = hikariCurrent;
}

bool GfDataBlade::isHomuriNameHikari() {
  uint flag = GfGameFlag::getLocal(1, 0x89fb);
  return flag != 0;
}

void GfDataBlade::setHomuriNameHikari(bool homuriNameHikari) {
  GfGameFlag::setLocal(1, 0x89fb, homuriNameHikari);
}
} // namespace gf
