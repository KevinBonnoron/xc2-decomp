#include "gf/data/gf_data_store.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_util.h"
#include "gf/gf_allocator.h"
#include <new>

namespace gf {

constexpr u32 NATION_COUNT = 8;

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

SDataSystem &GfDataStore::getDataSystem() { return get()->mDataSystem; }

SDataGame &GfDataStore::getDataGame() { return get()->mDataGame; }

SDataOption &GfDataStore::getDataOption() { return get()->mDataOption; }

} // namespace gf
