#include "gf/data/gf_data_store.h"

#include <new>

#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_real_time.h"
#include "gf/gf_allocator.h"
#include "gf/sound/gf_master_volume.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace gf {

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

void GfDataStore::initSystemData() { get()->mDataSystem.unknown08 = RealTime(); }

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
    dataGame->unknown10a53c[map].unknown1c = map == MAP_SUPERBIA;
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

    GfDataManager::getDataGame()->unknown10ae81 = 0;
  }

  if (dataSystem != nullptr) {
    dataStore->mDataSystem.unknown00 = dataSystem->unknown00;
    dataStore->mDataSystem.unknown08 = dataSystem->unknown08;
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

void SSoundUiOption::clear() {
  GfMasterVolume masterVolume;
  _1a = 0x80;
  _1c = true;
  unknown00 = masterVolume.getEventVoiceVolume() * VOLUME_SCALE;
  unknown02 = masterVolume.getEventCsVolume() * VOLUME_SCALE;
  unknown04 = masterVolume.getEventBgmVolume() * VOLUME_SCALE;
  unknown06 = masterVolume.getEventSeVolume() * VOLUME_SCALE;
  unknown08 = masterVolume.getGameBgmVolume() * VOLUME_SCALE;
  unknown0a = masterVolume.getGameEnvVolume() * VOLUME_SCALE;
  unknown0c = masterVolume.getGameWeatherVolume() * VOLUME_SCALE;
  unknown0e = masterVolume.getGameSeVolume() * VOLUME_SCALE;
  unknown10 = masterVolume.getPlayerVoiceVolume() * VOLUME_SCALE;
  unknown12 = masterVolume.getEnemyVoiceVolume() * VOLUME_SCALE;
  unknown14 = masterVolume.getNareVoiceVolume() * VOLUME_SCALE;
  unknown16 = masterVolume.getSystemVolume() * VOLUME_SCALE;
  unknown18 = masterVolume.getMenuBgmVolume() * VOLUME_SCALE;
}

bool SSoundUiOption::isDirty(const SSoundUiOption &other) {
  return _1a != other._1a || unknown00 != other.unknown00 || unknown02 != other.unknown02 || unknown04 != other.unknown04 || unknown06 != other.unknown06 || unknown08 != other.unknown08 ||
         unknown0a != other.unknown0a || unknown0c != other.unknown0c || unknown0e != other.unknown0e || unknown10 != other.unknown10 || unknown12 != other.unknown12 || unknown14 != other.unknown14 ||
         unknown16 != other.unknown16 || unknown18 != other.unknown18 || _1c != other._1c || _1d != other._1d;
}

} // namespace gf
