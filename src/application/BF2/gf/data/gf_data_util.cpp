#include "gf/data/gf_data_util.h"

#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "ml/rand.h"

namespace gf {

enum {
  FLAG_UNKNOWN_1 = 0x1,        // Inferred role: flag scenario flag; original name unknown.
  FLAG_UNKNOWN_516 = 0x204,    // Inferred role: flag random inn; original name unknown.
  FLAG_UNKNOWN_55166 = 0xd77e, // Inferred role: flag game clear check; original name unknown.
};

enum {
  SCENARIO_UNKNOWN_3048 = 0xbe8, // Inferred role: scenario flag vandamme dead; original name unknown.
};

void GfDataUtil::setupEventDriverAndBlade() {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_UNKNOWN_4), -1, DRIVER_UNKNOWN_4, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_UNKNOWN_5), -1, DRIVER_UNKNOWN_5, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_UNKNOWN_6), -1, DRIVER_UNKNOWN_6, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_UNKNOWN_7), -1, DRIVER_UNKNOWN_7, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_UNKNOWN_8), -1, DRIVER_UNKNOWN_8, 0);
}

u32 GfDataUtil::getMoney() { return GfDataManager::getDataGame()->unknown00; }

void GfDataUtil::setMoney(u32 money) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (money >= MONEY_UNKNOWN_999999999) {
    money = MONEY_UNKNOWN_999999999;
  }

  dataGame->unknown00 = money;
}

u32 GfDataUtil::getCoin() { return GfDataManager::getDataGame()->unknown10ad54; }

void GfDataUtil::setCoin(u32 coin) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (coin >= COIN_UNKNOWN_9999) {
    coin = COIN_UNKNOWN_9999;
  }

  dataGame->unknown10ad54 = coin;
}

void GfDataUtil::setChapterSave(u32 eventChapterSave, u16 startChapterSave) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown26 = startChapterSave;
  dataGame->unknown28 = eventChapterSave;
}

bool GfDataUtil::isStartChapterSave() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->unknown26 == getScenarioFlag()) {
    return dataGame->unknown28 != 0;
  }

  return false;
}

u16 GfDataUtil::getScenarioFlag() { return GfGameFlag::getLocal(16, FLAG_UNKNOWN_1); }

u32 GfDataUtil::getEventChapterSave() { return GfDataManager::getDataGame()->unknown28; }

u16 GfDataUtil::getAutoEventAfterLoad() { return GfDataManager::getDataGame()->unknown10ae7e; }

u32 GfDataUtil::getSkipTravelID() { return GfDataManager::getDataGame()->unknown1097f0.unknownc0; }

void GfDataUtil::setPlayerCameraDistance(f32 playerCameraDistance) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown109b28 = playerCameraDistance;
}

f32 GfDataUtil::getPlayerCameraDistance() { return GfDataManager::getDataGame()->unknown109b28; }

void GfDataUtil::setCameraHeight(f32 cameraHeight) { GfDataManager::getDataGame()->unknown10ad70 = cameraHeight; }

f32 GfDataUtil::getCameraHeight() { return GfDataManager::getDataGame()->unknown10ad70; }

void GfDataUtil::setCameraYaw(f32 cameraYaw) { GfDataManager::getDataGame()->unknown10ae74 = cameraYaw; }

f32 GfDataUtil::getCameraYaw() { return GfDataManager::getDataGame()->unknown10ae74; }

void GfDataUtil::setCameraPitch(f32 cameraPitch) { GfDataManager::getDataGame()->unknown10ae78 = cameraPitch; }

f32 GfDataUtil::getCameraPitch() { return GfDataManager::getDataGame()->unknown10ae78; }

void GfDataUtil::setCameraFreeMode(bool cameraFreeMode) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ae7c = cameraFreeMode;
}

bool GfDataUtil::isCameraFreeMode() { return GfDataManager::getDataGame()->unknown10ae7c; }

u8 GfDataUtil::getCameraSide() { return GfDataManager::getDataGame()->unknown10ae82; }

void GfDataUtil::setCameraSide(u8 cameraSide) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ae82 = cameraSide;
}

u32 GfDataUtil::getGameClearCount() { return GfDataManager::getDataGame()->unknown109b2c; }

const char *GfDataUtil::getAttributeFileName(u32 attribute) {
  static const char *const unknown037[] = {
      // Inferred role: attribute file names; original name unknown.
      "none",
      "fire",
      "water",
      "wind",
      "earth",
      "volt",
      "ice",
      "light",
      "dark",
  };

  return unknown037[attribute];
}

void GfDataUtil::setScenarioFlag(u16 scenarioFlag) { GfGameFlag::setLocal(16, FLAG_UNKNOWN_1, scenarioFlag); }

u32 GfDataUtil::getObjTypeByCharaId(u32 charaId) {
  if (charaId >= 1 && charaId <= 9) {
    return OBJECT_TYPE_PC;
  }

  if (charaId >= 1001 && charaId <= 1050) {
    return OBJECT_TYPE_BLADE;
  }

  return 0;
}

f32 GfDataUtil::getMoveDistance(AMOVE amove) {
  SDataGame *dataGame = GfDataManager::getDataGame();

  switch (amove) {
  case AMOVE_UNKNOWN_0:
    return dataGame->unknown10ad40;
  default:
    return dataGame->unknown10ad44;
  }
}

void GfDataUtil::setMoveDistance(AMOVE amove, f32 moveDistance) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  switch (amove) {
  case AMOVE_UNKNOWN_0:
    dataGame->unknown10ad40 = moveDistance;
    break;

  case AMOVE_UNKNOWN_1:
    dataGame->unknown10ad44 = moveDistance;
    break;
  }
}

void GfDataUtil::setRandomInn() { GfGameFlag::setLocal(4, FLAG_UNKNOWN_516, ml::mtRand(16)); }

void GfDataUtil::setSalvagerPoint(u32 salvagerPoint) { GfGameFlag::setLocal(8, FLAG_UNKNOWN_2132, salvagerPoint); }

u64 *GfDataUtil::getSaveRealTime() { return &GfDataManager::getDataGame()->unknown10ad68; }

bool GfDataUtil::isCollectFlagNewVersion() { return GfDataManager::getDataGame()->unknown10ae80; }

void GfDataUtil::convertNewCollectFlagPatch() {}

bool GfDataUtil::isClearGame() { return GfGameFlag::getLocal(1, FLAG_UNKNOWN_48589); }

bool GfDataUtil::isClearGameCheck() { return GfGameFlag::getLocal(1, FLAG_UNKNOWN_55166); }

void GfDataUtil::setClearGameCheck() { GfGameFlag::setLocal(1, FLAG_UNKNOWN_55166, 1); }

bool GfDataUtil::isVandammeDead() { return getScenarioFlag() >= SCENARIO_UNKNOWN_3048; }

void GfDataUtil::refreshBladeSaveData() {
  GfBdatChrBl *bdatBlade = GfBdatChrBl::get();
  u32 start = bdatBlade->getChrBlStart();
  u32 end = bdatBlade->getChrBlEnd();
  for (u32 blade = start; blade < end; blade++) {
    SDataBlade &dataBlade = GfDataBlade::getSDataBlade(blade);
    if (blade != dataBlade.unknown06) {
      GfDataBlade::setupSDataBlade(dataBlade, blade, false);
    }
  }
}

void GfDataUtil::refreshBdatParam() {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = GfDataBlade::getBladeID(i);
    if (blade != 0) {
      GfDataBlade::setupSDataBlade(GfDataBlade::getSDataBlade(blade), blade, true);
    }
  }
  for (u32 driver = DRIVER_UNKNOWN_1; driver <= DRIVER_UNKNOWN_9; driver++) {
    GfDataDriver::calcDriverBaseParamByLevel(GfDataDriver::getSDataDriver(driver));
  }
}

} // namespace gf
