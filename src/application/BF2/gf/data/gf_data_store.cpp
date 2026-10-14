#include "gf/data/gf_data_store.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_util.h"
#include "gf/gf_allocator.h"
#include <new>

namespace gf {

constexpr u32 NATION_COUNT = 8;

GfDataStore::GfDataStore(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

GfDataStore::~GfDataStore() {}

void GfDataStore::initialize(const GfSetupParam &) {
  initSystemData();
  initGameData();
  initOptionData();
  mInitialized = true;
}

void GfDataStore::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfDataStore(param); }

void GfDataStore::destroy() {
  GfDataStore *dataStore = get();
  dataStore->finalize();
  delete dataStore;
}

void GfDataStore::finalize() { mInitialized = false; }

bool GfDataStore::isInitialized() {
  GfDataStore *dataStore = get();
  if (dataStore == nullptr) {
    return false;
  }

  return dataStore->mInitialized;
}

void GfDataStore::clear() {
  initSystemData();
  initGameData();
  initOptionData();
}

void GfDataStore::initSystemData() { get()->mDataSystem.flags = 0; }

void GfDataStore::initGameData() {
  new (&get()->mDataGame) SDataGame();
  for (u32 nation = 1; nation <= NATION_COUNT; nation++) {
    GfDataDevelop::setLevel(nation, 0);
  }

  GfDataMercenaries::setLevel(0);
  GfDataUtil::initializeSaveDataDriverAndBlade();

  SDataGame *dataGame = GfDataManager::getDataGame();
  GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
  for (u32 map = bdatMaplist->getMaplistStart(); map < bdatMaplist->getMaplistEnd(); map++) {
    dataGame->mapInfos[map].cloudType = map == MAP_SUPERBIA;
  }
}

void GfDataStore::initOptionData() {
  GfDataStore *dataStore = get();
  if (dataStore != nullptr) {
    new (&dataStore->mDataOption) SDataOption();
  }
}

SDataSystem &GfDataStore::getDataSystem() { return get()->mDataSystem; }

SDataGame &GfDataStore::getDataGame() { return get()->mDataGame; }

SDataOption &GfDataStore::getDataOption() { return get()->mDataOption; }

void GfDataStore::setGameData(const SDataSystem *dataSystem, const SDataGame *dataGame, const SDataOption *dataOption) {
  GfDataStore *dataStore = get();
  if (dataStore == nullptr) {
    return;
  }

  if (dataGame != nullptr) {
    dataStore->mDataGame = *dataGame;
    GfDataUtil::refreshBladeSaveData();
    GfDataUtil::refreshBdatParam();

    u32 blade = GfDataDriver::getBlade(DRIVER_REX, -1);
    if (GfDataBlade::isHikariCurrent()) {
      if (blade == BLADE_HOMURA && GfDataBlade::isActivateParty(BLADE_HIKARI)) {
        GfDataBlade::setHikariCurrent(false);
      }
    } else if (blade == BLADE_HIKARI && GfDataBlade::isActivateParty(BLADE_HOMURA)) {
      GfDataBlade::setHikariCurrent(true);
    }

    GfDataManager::getDataGame()->clearSaveData = 0;
  }

  if (dataSystem != nullptr) {
    dataStore->mDataSystem.version = dataSystem->version;
    dataStore->mDataSystem.flags = dataSystem->flags;
  }

  if (dataOption != nullptr) {
    dataStore->mDataOption = *dataOption;
  }
}

void GfDataStore::setupOptionData(const SDataOption &dataOption) {
  GfDataStore *dataStore = get();
  if (dataStore != nullptr) {
    dataStore->mDataOption = dataOption;
  }
}

} // namespace gf
