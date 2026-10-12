#include "gf_data_blade_create.h"
#include "gf_data_game.h"
#include "gf_data_manager.h"

namespace gf {
  void GfDataBladeCreate::resetAssureCount() {
    SDataGame *dataGame = GfDataManager::getDataGame();
    dataGame->assureCount = 0;
  }

  uint GfDataBladeCreate::getAssureCount() {
    SDataGame *dataGame = GfDataManager::getDataGame();
    return dataGame->assureCount;
  }

  void GfDataBladeCreate::resetAssurePoint() {
    SDataGame *dataGame = GfDataManager::getDataGame();
    dataGame->assurePoint = 0;
  }

  uint GfDataBladeCreate::getAssurePoint() {
    SDataGame *dataGame = GfDataManager::getDataGame();
    return dataGame->assurePoint;
  }
}
