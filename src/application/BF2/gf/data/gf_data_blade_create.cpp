#include "gf/data/gf_data_blade_create.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"

namespace gf {

u32 GfDataBladeCreate::getRareBladeAppearType() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->rareBladeAppearType;
}

void GfDataBladeCreate::setRareBladeAppearType(u32 rareBladeAppearType) { GfDataManager::getDataGame()->rareBladeAppearType = (u8)rareBladeAppearType; }

void GfDataBladeCreate::addAssurePoint(u32 amount) {
  u32 assurePoint = GfDataManager::getDataGame()->assurePoint + amount;
  if (assurePoint < GfDataManager::getDataGame()->assurePoint) {
    assurePoint = 0xffffffff;
  }

  GfDataManager::getDataGame()->assurePoint = assurePoint;
}

u32 GfDataBladeCreate::getAssurePoint() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->assurePoint;
}

void GfDataBladeCreate::resetAssurePoint() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->assurePoint = 0;
}

void GfDataBladeCreate::addAssureCount(u32 amount) {
  u32 assureCount = GfDataManager::getDataGame()->assureCount + amount;
  if (assureCount < GfDataManager::getDataGame()->assureCount) {
    assureCount = 0xffffffff;
  }

  GfDataManager::getDataGame()->assureCount = assureCount;
}

u32 GfDataBladeCreate::getAssureCount() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->assureCount;
}

void GfDataBladeCreate::resetAssureCount() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->assureCount = 0;
}

} // namespace gf
