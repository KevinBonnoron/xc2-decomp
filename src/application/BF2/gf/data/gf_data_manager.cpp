#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_store.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"

namespace gf {

GfDataManager::GfDataManager(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

void GfDataManager::initialize(const GfSetupParam &param) {
  GfDataBdat::build(param);
  GfGameFlag::build(param);
  GfDataStore::build(param);
  mInitialized = true;
}

GfDataManager::~GfDataManager() {}

void GfDataManager::build(const GfSetupParam &param) {
  // __LINE__ must be 48 as in the original file: its value changes the instruction order.
#line 48
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfDataManager(param);
}

void GfDataManager::destroy() {
  GfDataManager *dataManager = get();
  dataManager->finalize();
  delete dataManager;
}

void GfDataManager::finalize() {
  GfDataStore::destroy();
  GfGameFlag::destroy();
  GfDataBdat::destroy();
  mInitialized = false;
}

bool GfDataManager::isInitialized() {
  GfDataManager *dataManager = get();
  if (dataManager == nullptr) {
    return false;
  }

  return dataManager->mInitialized;
}

void GfDataManager::clear() {
  u32 oldScenarioFlag = GfDataUtil::getScenarioFlag();
  GfDataStore::clear();
  GfGameFlag::clear();
  GfEvent::callChangeScenarioFlag(GfDataUtil::getScenarioFlag(), oldScenarioFlag);
}

void GfDataManager::setupGame(const SDataSystem *dataSystem, const SDataGame *dataGame, const SDataOption *dataOption) {
  GfDataStore::setGameData(dataSystem, dataGame, dataOption);
  GfDataUtil::convertNewCollectFlagPatch();
}

void GfDataManager::setupOptionData(const SDataOption &dataOption) { GfDataStore::setupOptionData(dataOption); }

SDataSystem *GfDataManager::getDataSystem() { return &GfDataStore::getDataSystem(); }

SDataGame *GfDataManager::getDataGame() { return &GfDataStore::getDataGame(); }

SDataOption *GfDataManager::getDataOption() { return &GfDataStore::getDataOption(); }

} // namespace gf
