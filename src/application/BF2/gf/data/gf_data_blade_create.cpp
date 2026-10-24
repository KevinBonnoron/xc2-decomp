#include "gf/data/gf_data_blade_create.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"

namespace gf {

u32 GfDataBladeCreate::getRareBladeAppearType() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown10ad50;
}

void GfDataBladeCreate::setRareBladeAppearType(u32 rareBladeAppearType) { GfDataManager::getDataGame()->unknown10ad50 = (u8)rareBladeAppearType; }

void GfDataBladeCreate::addAssurePoint(u32 amount) {
  u32 assurePoint = GfDataManager::getDataGame()->unknown10ad48 + amount;
  if (assurePoint < GfDataManager::getDataGame()->unknown10ad48) {
    assurePoint = 0xffffffff;
  }

  GfDataManager::getDataGame()->unknown10ad48 = assurePoint;
}

u32 GfDataBladeCreate::getAssurePoint() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown10ad48;
}

void GfDataBladeCreate::resetAssurePoint() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ad48 = 0;
}

void GfDataBladeCreate::addAssureCount(u32 amount) {
  u32 assureCount = GfDataManager::getDataGame()->unknown10ad4c + amount;
  if (assureCount < GfDataManager::getDataGame()->unknown10ad4c) {
    assureCount = 0xffffffff;
  }

  GfDataManager::getDataGame()->unknown10ad4c = assureCount;
}

u32 GfDataBladeCreate::getAssureCount() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown10ad4c;
}

void GfDataBladeCreate::resetAssureCount() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ad4c = 0;
}

} // namespace gf
