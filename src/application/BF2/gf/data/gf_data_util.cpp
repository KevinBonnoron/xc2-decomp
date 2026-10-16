#include "gf/data/gf_data_util.h"

#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "ml/rand.h"

namespace gf {

enum {
  FLAG_SCENARIO_FLAG = 0x1,
  FLAG_RANDOM_INN = 0x204,
  FLAG_GAME_CLEAR_CHECK = 0xd77e,
};

enum {
  SCENARIO_FLAG_VANDAMME_DEAD = 0xbe8,
};

void GfDataUtil::setupEventDriverAndBlade() {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_TORA), -1, DRIVER_TORA, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_VANDAMME), -1, DRIVER_VANDAMME, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_MELEPH), -1, DRIVER_MELEPH, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_SHIN), -1, DRIVER_SHIN, 0);
  GfDataBlade::setActivateDriver(bdatDriver->getChrDrDefBlade1(DRIVER_METSU), -1, DRIVER_METSU, 0);
}

u32 GfDataUtil::getMoney() { return GfDataManager::getDataGame()->money; }

void GfDataUtil::setMoney(u32 money) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (money >= MONEY_MAX) {
    money = MONEY_MAX;
  }

  dataGame->money = money;
}

u32 GfDataUtil::getCoin() { return GfDataManager::getDataGame()->coin; }

void GfDataUtil::setCoin(u32 coin) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (coin >= COIN_MAX) {
    coin = COIN_MAX;
  }

  dataGame->coin = coin;
}

void GfDataUtil::setChapterSave(u32 eventChapterSave, u16 startChapterSave) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->startChapterSave = startChapterSave;
  dataGame->eventChapterSave = eventChapterSave;
}

bool GfDataUtil::isStartChapterSave() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->startChapterSave == getScenarioFlag()) {
    return dataGame->eventChapterSave != 0;
  }

  return false;
}

u16 GfDataUtil::getScenarioFlag() { return GfGameFlag::getLocal(16, FLAG_SCENARIO_FLAG); }

u16 GfDataUtil::getEventChapterSave() { return GfDataManager::getDataGame()->eventChapterSave; }

u16 GfDataUtil::getAutoEventAfterLoad() { return GfDataManager::getDataGame()->autoEventAfterLoad; }

u32 GfDataUtil::getSkipTravelID() { return GfDataManager::getDataGame()->map.skipTravelID; }

void GfDataUtil::setPlayerCameraDistance(f32 playerCameraDistance) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->playerCameraDistance = playerCameraDistance;
}

f32 GfDataUtil::getPlayerCameraDistance() { return GfDataManager::getDataGame()->playerCameraDistance; }

void GfDataUtil::setCameraHeight(f32 cameraHeight) { GfDataManager::getDataGame()->cameraHeight = cameraHeight; }

f32 GfDataUtil::getCameraHeight() { return GfDataManager::getDataGame()->cameraHeight; }

void GfDataUtil::setCameraYaw(f32 cameraYaw) { GfDataManager::getDataGame()->cameraYaw = cameraYaw; }

f32 GfDataUtil::getCameraYaw() { return GfDataManager::getDataGame()->cameraYaw; }

void GfDataUtil::setCameraPitch(f32 cameraPitch) { GfDataManager::getDataGame()->cameraPitch = cameraPitch; }

f32 GfDataUtil::getCameraPitch() { return GfDataManager::getDataGame()->cameraPitch; }

void GfDataUtil::setCameraFreeMode(bool cameraFreeMode) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->cameraFreeMode = cameraFreeMode;
}

bool GfDataUtil::isCameraFreeMode() { return GfDataManager::getDataGame()->cameraFreeMode; }

u8 GfDataUtil::getCameraSide() { return GfDataManager::getDataGame()->cameraSide; }

void GfDataUtil::setCameraSide(u8 cameraSide) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->cameraSide = cameraSide;
}

u32 GfDataUtil::getGameClearCount() { return GfDataManager::getDataGame()->gameClearCount; }

const char *GfDataUtil::getAttributeFileName(u32 attribute) {
  static const char *const attributeFileNames[] = {
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

  return attributeFileNames[attribute];
}

void GfDataUtil::setScenarioFlag(u16 scenarioFlag) { GfGameFlag::setLocal(16, FLAG_SCENARIO_FLAG, scenarioFlag); }

u32 GfDataUtil::getObjTypeByCharaId(u32 charaId) {
  if (charaId >= 1 && charaId <= 9) {
    return OBJECT_TYPE_DRIVER;
  }

  if (charaId >= 1001 && charaId <= 1050) {
    return OBJECT_TYPE_BLADE;
  }

  return 0;
}

f32 GfDataUtil::getMoveDistance(AMOVE amove) {
  SDataGame *dataGame = GfDataManager::getDataGame();

  switch (amove) {
  case AMOVE_WALK:
    return dataGame->achievementWalkMove;
  default:
    return dataGame->achievementSwimMove;
  }
}

void GfDataUtil::setMoveDistance(AMOVE amove, f32 moveDistance) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  switch (amove) {
  case AMOVE_WALK:
    dataGame->achievementWalkMove = moveDistance;
    break;

  case AMOVE_SWIM:
    dataGame->achievementSwimMove = moveDistance;
    break;
  }
}

void GfDataUtil::setRandomInn() { GfGameFlag::setLocal(4, FLAG_RANDOM_INN, ml::mtRand(16)); }

void GfDataUtil::setSalvagerPoint(u32 salvagerPoint) { GfGameFlag::setLocal(8, FLAG_SALVAGER_POINT, salvagerPoint); }

u64 *GfDataUtil::getSaveRealTime() { return &GfDataManager::getDataGame()->saveRealTime; }

bool GfDataUtil::isCollectFlagNewVersion() { return GfDataManager::getDataGame()->collectFlagNewVersion; }

void GfDataUtil::convertNewCollectFlagPatch() {}

bool GfDataUtil::isClearGame() { return GfGameFlag::getLocal(1, FLAG_GAME_CLEAR); }

bool GfDataUtil::isClearGameCheck() { return GfGameFlag::getLocal(1, FLAG_GAME_CLEAR_CHECK); }

void GfDataUtil::setClearGameCheck() { GfGameFlag::setLocal(1, FLAG_GAME_CLEAR_CHECK, 1); }

bool GfDataUtil::isVandammeDead() { return getScenarioFlag() >= SCENARIO_FLAG_VANDAMME_DEAD; }

} // namespace gf
