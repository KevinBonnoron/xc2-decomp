#include "gf/game/gf_game_scene.h"

#include "fw/fw_update_info.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_state.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"

namespace gf {

namespace {

constexpr u32 ACHIEVEMENT_STATS_BATTLE_DAMAGE = 146;
constexpr f32 FIELD_BLADE_CHANGE_WAIT_TIME = 0.5f;
constexpr f32 MONEY_LOG_TIME = 0.5f;
constexpr int STOP_ENEMY_ATTACK_FRAME = 30;
constexpr int AFTER_EVENT_COUNT_MAX = 1000;
constexpr u32 DRIVER_VANDAMME = 5;
constexpr u32 TIME_RANGE_MORNING = 0;
constexpr u32 TIME_RANGE_NIGHT = 3;

} // namespace

bool GfGameScene::isPlayerStopFlag(PLSTOP flag) { return playerStopFlags.test(flag); }

void GfGameScene::EvtPlayerStop::update(const fw::UpdateInfo &) {
  if (state == STATE_WAIT_MOVER && GfGameManager::isGmkTutorialMoverOK()) {
    state = STATE_STOP;
  }
}

void GfGameScene::BattleAchievement::battleStart() {
  isBattle = true;
  maxDamage = 0;
  GfDataAchievement::clearTotalCount(ACHIEVEMENT_STATS_BATTLE_DAMAGE);
}

void GfGameScene::BattleAchievement::battleEnd() {
  if (damageCount != 0) {
    SCOM_ACHIEV_INC::createBattle();
  }
  GfDataAchievement::clearTotalCount(ACHIEVEMENT_STATS_BATTLE_DAMAGE);
  isBattle = false;
  damageCount = 0;
  maxDamage = 0;
}

void GfGameScene::BattleAchievement::bladeDamage(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &) {}

void GfGameScene::build(const GfSetupParam &param) {
  // __LINE__ must be 425 as in the original file: it is an argument of the allocation.
#line 425
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameScene(param);
}

bool GfGameScene::isInitialized() const { return initialized; }

bool GfGameScene::isPlayEvent() const { return isPlayEventEnable; }

bool GfGameScene::isMaskMainMenu() const { return isMaskMainMenuEnable; }

void GfGameScene::setEventPlayerStop(bool isStop) { eventPlayerStop.setPlayerStop(isStop); }

void GfGameScene::setResetBladePlayerStop(bool isStop) { resetBladePlayerStop.setPlayerStop(isStop); }

bool GfGameScene::isControlFree() const {
  if (GfGameState::getState() == GF_STATE_CONTROL && GfGameManager::getState() == GF_STATE_CONTROL && playerPauseBits == 0) {
    return GfGameState::getStateReserve() == GF_STATE_CONTROL;
  }
  return false;
}

bool GfGameScene::isControlFreeState() const {
  if (GfGameState::getState() == GF_STATE_CONTROL && GfGameManager::getState() == GF_STATE_CONTROL && playerPauseBits == 0) {
    return GfGameState::getStateReserve() == GF_STATE_CONTROL;
  }
  return false;
}

bool GfGameScene::isEnableFieldBladeChange() const {
  if (fieldBladeChangeTime >= FIELD_BLADE_CHANGE_WAIT_TIME && GfGameManager::isEnableOpenMainMenu()) {
    return GfGameManager::isControlFree();
  }
  return false;
}

void GfGameScene::setForceBossBattleBgm(bool isForce) { isForceBossBattleBgmEnable = isForce; }

bool GfGameScene::isForceBossBattleBgm() const { return isForceBossBattleBgmEnable; }

void GfGameScene::setForceEventBgm(f32 time) { forceEventBgmTime = time; }

bool GfGameScene::isForceEventBgm() const { return forceEventBgmTime > 0.0f; }

bool GfGameScene::isPlayerTalkForce() { return isPlayerTalkForceEnable || isGimmickCameraPause; }

void GfGameScene::setPlayerTalkForce(bool isForce) { isPlayerTalkForceEnable = isForce; }

void GfGameScene::setGimmickCameraPause(bool isPause) { isGimmickCameraPause = isPause; }

void GfGameScene::refreshGimmickFlag() {}

void GfGameScene::setAutoBattle(bool isAuto) { isAutoBattleEnable = isAuto; }

bool GfGameScene::isAutoBattle() { return isAutoBattleEnable; }

bool GfGameScene::isRideObj(GF_OBJ_HANDLE *handle) const {
  GfObjAcc obj(handle);
  if (obj.getPartyID() == -1) {
    return false;
  }
  return GfDataParty::isRideChar(obj.getBdatId());
}

bool GfGameScene::isRideParty(u32 partyId) const { return GfDataParty::isNiaByakko(partyId); }

int GfGameScene::createPlayerPause() {
  u32 bit = 1;
  for (u32 pause = 0; pause < 32; pause++, bit <<= 1) {
    if ((playerPauseBits & bit) == 0) {
      playerPauseBits |= bit;
      return pause;
    }
  }
  return -1;
}

void GfGameScene::destroyPlayerPause(u32 pause) { playerPauseBits &= ~(1 << pause); }

bool GfGameScene::isPlayerPause() const {
  if (GfGameManager::getState() == GF_STATE_CONTROL) {
    return playerPauseBits != 0;
  }
  return true;
}

bool GfGameScene::isPlayerPauseForBattle() const {
  if (GfGameManager::getState() == GF_STATE_CONTROL || GfGameManager::getState() == GF_STATE_RESET_BLADE) {
    return playerPauseBits != 0;
  }
  return true;
}

void GfGameScene::setDeadType(GfPlayerDead dead) { deadType = dead; }

u32 GfGameScene::getDeadType() { return deadType; }

void GfGameScene::setDamageCharacter(GF_OBJ_HANDLE *handle) {
  for (DamageCharacter &character : damageCharacters) {
    if (character.handle == handle) {
      character.time = 0;
      return;
    }
  }
}

bool GfGameScene::isBattle() const {
  if (get() != nullptr) {
    return (get()->flags & FLAG_BATTLE) != 0;
  }
  return false;
}

bool GfGameScene::isResetBladePlay() const {
  if (GfPlayComResetBlade::isPlaying(0) || GfPlayComResetBlade::isPlaying(1)) {
    return true;
  }
  return GfPlayComResetBlade::isPlaying(2);
}

void GfGameScene::applyMapjumpForCleanup(const MapjumpCallbackInfo &info) {
  isForceStopBattle = false;
  if (info.map != info.prevMap && info.map != 0) {
    isForceBossBattleBgmEnable = false;
    isForceBattleBgm = false;
    forceEventBgmTime = 0.0f;
  }
}

void GfGameScene::gevChangeParty() {
  GfSelectBlade::resetStartBattleSetId(0);
  GfSelectBlade::resetStartBattleSetId(1);
  GfSelectBlade::resetStartBattleSetId(2);
}

void GfGameScene::gevDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType) {
  if (activateType != 0 && oldActivateType == 0) {
    if (driver == DRIVER_VANDAMME && GfDataUtil::isVandammeDead()) {
      GfGameUtil::execDriverDead(DRIVER_VANDAMME);
    }
  } else if (activateType == 0 && oldActivateType != 0) {
    GfGameUtil::execEquipDriverDefaultAcce(driver);
  }
}

void GfGameScene::gevBladeUnselect(u32 blade, bool unselect) {
  if (!unselect && !GfDataBlade::isActivateUnuse(blade)) {
    GfGameUtil::execSaveAchievementPopup(blade);
  }
}

void GfGameScene::gevChangeTimeRange(u32 timeRange) {
  if (!GfGameManager::isControlFree()) {
    return;
  }
  CV_FIELD voice;
  if (timeRange == TIME_RANGE_MORNING) {
    voice = CV_FIELD_TIME_MORNING;
  } else if (timeRange == TIME_RANGE_NIGHT) {
    voice = CV_FIELD_TIME_NIGHT;
  } else {
    return;
  }
  SCOM_FIELD_VOICE::createTime(voice);
}

void GfGameScene::gevControllFree(bool) {}

void GfGameScene::gevMercenariesMissionFlag(u32 mission, u32 flag, u32) {
  if (GfGameUtilNanakoori::checkCompleteMission(mission, flag)) {
    isRequestAutoFlag = true;
  }
}

void GfGameScene::playEventPlayStart(u32) {
  if (!eventObjs.empty()) {
    for (GF_OBJ_HANDLE *obj : eventObjs) {
      GfObjUtil::destroy(obj);
    }
  }
  eventObjs.clear();
  isPlayEventEnable = true;
}

void GfGameScene::qevCompleteQuest(const QuestCompleteParam &) { isRequestAutoFlag = true; }

void GfGameScene::postUpdate(const fw::UpdateInfo &info) { updateAppendModel(info); }

OwnerBonus &GfGameScene::getOwnerBonus() const { return ownerBonus; }

void GfGameScene::setCameraAvtivateOneTime() { flags |= FLAG_CAMERA_ACTIVATE_ONE_TIME; }

bool GfGameScene::isPlayerCameraPause() {
  if (flags & FLAG_CAMERA_PAUSE) {
    return true;
  }
  if (flags & FLAG_CAMERA_ACTIVATE_ONE_TIME) {
    flags &= ~FLAG_CAMERA_ACTIVATE_ONE_TIME;
    return false;
  }
  return GfPause::isPause(PAUSE_BIT_SYSTEM);
}

void GfGameScene::setPlayerCameraPause(bool isPause) {
  if (isPause) {
    flags |= FLAG_CAMERA_PAUSE;
  } else {
    flags &= ~FLAG_CAMERA_PAUSE;
  }
}

void GfGameScene::setForceBattleTime(f32 time) {
  if (get() != nullptr) {
    get()->forceBattleTime = time;
  }
}

void GfGameScene::setForceStopBattle(bool isStop) {
  if (get() != nullptr) {
    get()->isForceStopBattle = isStop;
  }
}

void GfGameScene::addMoneyLog() { moneyLogTime = MONEY_LOG_TIME; }

u32 GfGameScene::getQuestIdForTaskLog() const { return questIdForTaskLog; }

void GfGameScene::updateOwnerBonus(const fw::UpdateInfo &) {
  if (isOwnerBonusDirty) {
    isOwnerBonusDirty = false;
    GfGameUtil::getOwnerBonus(ownerBonus);
  }
}

void GfGameScene::updateMaskMainMenu(const fw::UpdateInfo &) {
  if (!GfGameManager::isEvent(false) && GfGameManager::isFadeClear()) {
    isMaskMainMenuEnable = false;
  }
}

void GfGameScene::updateStopEnemyAttackForEvent(const fw::UpdateInfo &) {
  if (stopEnemyAttackCount > 0) {
    stopEnemyAttackCount--;
  }
  if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
    stopEnemyAttackCount = STOP_ENEMY_ATTACK_FRAME;
  }
}

void GfGameScene::updateAfterEventCount(const fw::UpdateInfo &) {
  if (!GfGameManager::isPlaySequenceClear()) {
    afterEventCount = 0;
  } else if (afterEventCount < AFTER_EVENT_COUNT_MAX) {
    afterEventCount++;
  }
}

void GfGameScene::updateEventFadeVolume(const fw::UpdateInfo &) {
  GfFieldSound *fieldSound = GfFieldSound::get();
  if (fieldSound != nullptr) {
    f32 volume;
    if (!GfGameManager::isEvent(false) && !GfGameManager::isTalking()) {
      volume = 1.0f;
    } else {
      volume = 1.0f - GfGameManager::getFadeoutAlpha();
    }
    fieldSound->setCategorySeFadeoutForEvent(volume);
  }
}

void GfGameScene::updateLog(const fw::UpdateInfo &info) {
  if (moneyLogTime > 0.0f) {
    moneyLogTime -= info.deltaTime;
    if (moneyLogTime <= 0.0f) {
      moneyLogTime = 0.0f;
    }
  }
}

void GfGameScene::updateForceBattle(const fw::UpdateInfo &info) {
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM) && forceBattleTime > 0.0f) {
    forceBattleTime -= info.deltaTime;
    if (forceBattleTime < 0.0f) {
      forceBattleTime = 0.0f;
    }
  }
}

void GfGameScene::updateEventBgm(const fw::UpdateInfo &info) {
  if (forceEventBgmTime <= 0.0f) {
    return;
  }
  if (GfGameManager::isBattle()) {
    forceEventBgmTime = 0.0f;
  }
  if (GfGameManager::isControlFree()) {
    forceEventBgmTime -= info.deltaTime;
    if (forceEventBgmTime < 0.0f) {
      forceEventBgmTime = 0.0f;
    }
  }
}

void GfGameScene::updateAutoFlag(const fw::UpdateInfo &) {
  if (isRequestAutoFlag) {
    isRequestAutoFlag = false;
    if (GfGameUtilNanakoori::calcLevelAndFan()) {
      GfQuestManager::eventCheckTaskAll();
    }
  }
}

} // namespace gf
