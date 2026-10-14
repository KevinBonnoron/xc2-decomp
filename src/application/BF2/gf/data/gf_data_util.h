#pragma once
#include "types.h"

namespace gf {

enum AMOVE { AMOVE_WALK, AMOVE_SWIM };

class GfDataUtil {
public:
  static void initializeSaveDataDriverAndBlade();
  static void setupEventDriverAndBlade();

  static u32 getMoney();
  static void setMoney(u32 money);

  static u32 getCoin();
  static void setCoin(u32 coin);

  static void setChapterSave(u32 eventChapterSave, u16 startChapterSave);
  static bool isStartChapterSave();
  static u16 getScenarioFlag();
  static u16 getEventChapterSave();
  static u16 getAutoEventAfterLoad();
  static u32 getSkipTravelID();

  static void setPlayerCameraDistance(f32 playerCameraDistance);
  static f32 getPlayerCameraDistance();

  static void setCameraHeight(f32 cameraHeight);
  static f32 getCameraHeight();

  static void setCameraYaw(f32 cameraYaw);
  static f32 getCameraYaw();

  static void setCameraPitch(f32 cameraPitch);
  static f32 getCameraPitch();

  static void setCameraFreeMode(bool cameraFreeMode);
  static bool isCameraFreeMode();

  static u8 getCameraSide();
  static void setCameraSide(u8 cameraSide);

  static u32 getGameClearCount();
  static const char *getAttributeFileName(u32 attribute);
  static void setScenarioFlag(u16 scenarioFlag);
  static u32 getObjTypeByCharaId(u32 charaId);

  static f32 getMoveDistance(AMOVE amove);
  static void setMoveDistance(AMOVE amove, f32 moveDistance);

  static void setRandomInn();
  static void setSalvagerPoint(u32 salvagerPoint);
  static u64 *getSaveRealTime();
  static bool isCollectFlagNewVersion();
  static void convertNewCollectFlagPatch();

  static bool isClearGame();
  static bool isClearGameCheck();
  static void setClearGameCheck();
  static bool isVandammeDead();
};

} // namespace gf
