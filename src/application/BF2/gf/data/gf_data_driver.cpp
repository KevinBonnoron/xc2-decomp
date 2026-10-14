#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"

namespace gf {

enum {
  SET_BLADE_TYPE_NONE = 0,
  SET_BLADE_TYPE_EXTENDED = 1,
};

constexpr u32 DRIVER_COUNT = 16;
constexpr u32 SET_BLADE_NUM_NORMAL = 3;
constexpr u32 SET_BLADE_NUM_EXTENDED = 5;

SDataDriver *GfDataDriver::getSDataDriver(u32 driver) {
  u32 index = driver - 1;
  SDataGame *dataGame = GfDataManager::getDataGame();
  return &dataGame->drivers[index < DRIVER_COUNT ? index : 1];
}

int GfDataDriver::getMaxSetBladeNum(u32 driver) {
  if (driver == 0) {
    return 0;
  }

  return getMaxSetBladeNum(*getSDataDriver(driver));
}

u32 GfDataDriver::getBlade(u32 driver, int slot) {
  if (driver == 0) {
    return 0;
  }

  return getBlade(*getSDataDriver(driver), slot);
}

int GfDataDriver::getBladeSet(u32 driver) {
  if (driver == 0) {
    return -1;
  }

  return getBladeSet(*getSDataDriver(driver));
}

u32 GfDataDriver::getBlade(const SDataDriver &dataDriver, int slot) {
  if (slot < 0) {
    slot = dataDriver.bladeSet;
  }

  if (slot < 0) {
    return 0;
  }

  return dataDriver.blades[slot];
}

int GfDataDriver::getBladeSet(const SDataDriver &dataDriver) { return dataDriver.bladeSet; }

int GfDataDriver::getMaxSetBladeNum(const SDataDriver &dataDriver) {
  if (dataDriver.setBladeType == SET_BLADE_TYPE_NONE) {
    return 0;
  }

  return dataDriver.setBladeType == SET_BLADE_TYPE_EXTENDED ? SET_BLADE_NUM_EXTENDED : SET_BLADE_NUM_NORMAL;
}

} // namespace gf
