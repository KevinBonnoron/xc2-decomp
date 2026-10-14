#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"

namespace gf {

constexpr u32 DRIVER_COUNT = 16;

SDataDriver *GfDataDriver::getSDataDriver(u32 driver) {
  u32 index = driver - 1;
  SDataGame *dataGame = GfDataManager::getDataGame();
  return &dataGame->drivers[index < DRIVER_COUNT ? index : 1];
}

} // namespace gf
