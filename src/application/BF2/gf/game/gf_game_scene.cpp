#include "gf/game/gf_game_scene.h"

#include <math.h>
#include <string.h>

#include "battle/utility_battle.h"
#include "framework/coli/coli_object.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_shop.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_item_handle.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/field/gf_field_sound.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_slow_attack.h"
#include "gf/game/gf_game_state.h"
#include "gf/game/gf_game_trinity_attack.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/vector.h"

namespace gf {

namespace {

constexpr u32 ACHIEVEMENT_STATS_WALK = 60;
constexpr u32 ACHIEVEMENT_STATS_SWIM = 62;
constexpr u32 ACHIEVEMENT_STATS_BATTLE_DAMAGE = 146;
constexpr f32 FIELD_BLADE_CHANGE_WAIT_TIME = 0.5f;
constexpr f32 MONEY_LOG_TIME = 0.5f;
constexpr int STOP_ENEMY_ATTACK_FRAME = 30;
constexpr int AFTER_EVENT_COUNT_MAX = 1000;
constexpr f32 INVALID_SAVE_POS = -999999.0f;
constexpr f32 INVALID_SAVE_POS_LIMIT = -999998.0f;
constexpr u32 OBJ_LAYER_PLAYER = 4;
constexpr int HOMURI_BLADE_SET = 4;
constexpr int DEAD_COLI_PRIORITY = 900;
constexpr f32 HIKARI_ROOM_HEIGHT = 100.0f;
constexpr u32 SAVED_HP_TYPE_FIRST = 1;
constexpr u32 SAVED_HP_TYPE_LAST = 3;
constexpr u32 SHOP_PRIVILEGE = 39;
constexpr int FLAG_PRIVILEGE_ITEM = 50547;
constexpr int FLAG_CRYSTAL_COUNT = 2133;
constexpr int FLAG_EVENT_MONEY = 1551;
constexpr int FLAG_CRYSTAL_POPUP = 54665;
constexpr u16 SCENARIO_FLAG_SUZAKU_ACTIVATE = 3048;
constexpr u32 ACHIEVEMENT_STATS_HOMURA_COOK_ITEM = 70;
constexpr u32 ACHIEVEMENT_STATS_YUOH_COOK_ITEM = 71;
constexpr u32 ACHIEVEMENT_STATS_MUSUBI_COOK_ITEM = 72;
constexpr u32 ACHIEVEMENT_STATS_MAY_ITEM = 73;
constexpr u32 ACHIEVEMENT_STATS_TUKI_ITEM = 74;
constexpr u32 EVENT_NIA_SET_BYAKKO = 10037;
constexpr u32 EVENT_SUZAKU_ACTIVATE = 10090;
constexpr u32 EVENT_SUZAKU_RELEASE = 10091;
constexpr u32 EVENT_ENV_SILENT = 10150;
constexpr u32 EVENT_SHIN_SET_DUMMY = 10439;
constexpr u32 EVENT_LAST_KIZUNA_TALK = 30053;
constexpr u32 EVENT_KEEP_VOLUME = 30173;
constexpr u32 EVENT_SAVE_MONEY = 41007;
constexpr int CONTROL_FREE_FRAME = 10;
constexpr f32 AUTO_HEAL_INTERVAL = 1.0f;
constexpr f32 AUTO_HEAL_RATE = 10.0f;
constexpr f32 MOVE_DISTANCE_MIN = 0.01f;
constexpr f32 MOVE_DISTANCE_MAX = 5.0f;
constexpr u32 CRYSTAL_LIST_FIRST = 45005;
constexpr u32 CRYSTAL_ITEM_FIRST = 38;

bool isEnableBattleMomuri(u32 partyId) {
  DataParamAcc paramAcc(GfGameParty::getHandleBlade(partyId, -1));
  if (paramAcc.isValid() && paramAcc.getBdatId() == BLADE_HOMURI) {
    return false;
  }
  return GfDataBlade::getSetDriver(BLADE_HOMURI) == DRIVER_REX;
}

void updateColiPriority(const DataParamAcc &paramAcc, bool isDead, bool isSwim) {
  if (!paramAcc.isValid()) {
    return;
  }
  GfObj *obj = GfObjUtil::getObj(paramAcc.handle);
  if (obj == nullptr) {
    return;
  }
  int priority = obj->info->coliPriority;
  if (priority < 0) {
    return;
  }
  GfComAsm *comAsm = obj->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }
  GfComCollider *collider = obj->getComponent<GfComCollider>();
  if (collider == nullptr) {
    return;
  }
  fw::ColiObject *coli = collider->colis[0];
  if (coli == nullptr) {
    return;
  }
  int currentPriority = coli->getPriority();
  if (priority == currentPriority && isDead) {
    bool isDeadState = isSwim;
    if (!isDeadState) {
      const char *state = comAsm->getStateName(ANIM_LAYER_BASE);
      isDeadState = state != nullptr && (strcmp(state, "S_waterdead_00") == 0 || strcmp(state, "S_waterdead_01") == 0);
    }
    if (!isDeadState && comAsm->isEnd(ANIM_LAYER_BASE)) {
      const char *state = comAsm->getStateName(ANIM_LAYER_BASE);
      isDeadState = state != nullptr && strcmp(state, "S_dead") == 0;
    }
    if (isDeadState) {
      coli->setPriority(DEAD_COLI_PRIORITY);
      coli->clearState(fw::COLI_STATE_ENABLE);
    }
  }
  if (priority != currentPriority && !isDead) {
    coli->setPriority(priority);
    coli->setState(fw::COLI_STATE_ENABLE);
  }
}

void addAchievementCount(u32 stats, int count) {
  for (int i = 0; i < count; i++) {
    SCOM_ACHIEV_INC::addTotalCount(stats, 1);
    SCOM_ACHIEV_INC::create(stats, 1, 0);
  }
}

const u16 MAPJUMP_EVENTS[] = {10032, 10081, 10130, 10190, 10241, 10305, 10366, 10417, 10455, 10503};

} // namespace

namespace _gfgsc {

void setInvalidSavePos(mm::Vec3 &position) { position = mm::Vec3(INVALID_SAVE_POS, INVALID_SAVE_POS, INVALID_SAVE_POS); }

bool isInvalidSavePos(const mm::Vec3 &position) { return position.x < INVALID_SAVE_POS_LIMIT; }

} // namespace _gfgsc

void GfGameScene::EvtPlayerStop::startPlayerStop() {
  if (state != STATE_WAIT_MOVER) {
    scene->setPlayerStopFlag(flag, true);
    state = STATE_WAIT_MOVER;
  }
}

void GfGameScene::setPlayerStopFlag(PLSTOP flag, bool isStop) { playerStopFlagQueue.push((isStop ? 0x80 : 0) | flag); }

void GfGameScene::EvtPlayerStop::endPlayerStop() {
  if (scene->isPlayerStopFlag(flag)) {
    scene->setPlayerStopFlag(flag, false);
    GfGameManager::setGmkTutorialMoverOK(false);
  }
  state = STATE_NONE;
}

void GfGameScene::EvtPlayerStop::resetState() {
  if (scene->isPlayerStopFlag(flag)) {
    scene->setPlayerStopFlag(flag, false);
    GfGameManager::setGmkTutorialMoverOK(false);
  }
  state = STATE_NONE;
}

bool GfGameScene::isPlayerStopFlag(PLSTOP flag) { return playerStopFlags.test(flag); }

void GfGameScene::EvtPlayerStop::setPlayerStop(bool isStop) {
  if (GfManager::isExecModeThater()) {
    return;
  }
  if (isStop) {
    startPlayerStop();
  } else {
    endPlayerStop();
  }
}

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
  maxDamage = 0;
  damageCount = 0;
}

void GfGameScene::BattleAchievement::enemyDamage(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &damage) {
  if (maxDamage < damage.damage->damage) {
    maxDamage = damage.damage->damage;
    SCOM_ACHIEV_INC::createDamageMax(damage.attacker, damage.damage->damage);
  }
  SCOM_ACHIEV_INC::createDamageAdd(damage.attacker, damage.damage->damage);
  if (damage.damage->isCritical) {
    SCOM_ACHIEV_INC::createCriticalHit(damage.attacker);
  }
  damageCount++;
}

void GfGameScene::BattleAchievement::driverDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage) {
  SCOM_ACHIEV_INC::createDamageGet(handle, damage.damage->damage);
  if (damage.damage->isCritical) {
    SCOM_ACHIEV_INC::createCriticalGet(handle);
  }
  damageCount++;
}

void GfGameScene::BattleAchievement::bladeDamage(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &) {}

void GfGameScene::BattleAchievement::addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_ENEMY:
    enemyDamage(handle, damage);
    break;
  case OBJECT_TYPE_DRIVER:
    driverDamage(handle, damage);
    break;
  case OBJECT_TYPE_BLADE:
    bladeDamage(handle, damage);
    break;
  }
}

void GfGameScene::initialize(const GfSetupParam &) {
  bladeChangeRequests[0] = -1;
  bladeChangeRequests[1] = -1;
  bladeChangeRequests[2] = -1;
  fieldBladeChangeTime = 0.0f;
  isOwnerBonusDirty = true;
  movePosition = mm::Vec3::zero;
  battleStartCounts[2] = 0;
  battleStartCounts[1] = 0;
  battleStartCounts[0] = 0;
  listeningPoint = mm::Vec3::zero;
  requestListeningPoint = mm::Vec3::zero;
  isRequestListeningPoint = false;
  isPlayEventEnable = false;
  isBattleEvent = false;
  partyMovers[2] = INVALID_HANDLE;
  partyMovers[1] = INVALID_HANDLE;
  partyMovers[0] = INVALID_HANDLE;
  for (SavePos &savePosition : savePositions) {
    savePosition.position = mm::Vec3::zero;
    savePosition.isEnable = false;
  }
  clearPartyState();
  moveAchievements.push_back(MoveAchievement(AMOVE_SWIM, ACHIEVEMENT_STATS_SWIM, isPlayerSwimOnCloud));
  moveAchievements.push_back(MoveAchievement(AMOVE_WALK, ACHIEVEMENT_STATS_WALK, isPlayerWalkAndRun));
  isWaitReturnFieldState[0] = 0;
  isWaitReturnFieldState[1] = 0;
  isWaitReturnFieldState[2] = 0;
  GfTrinityAttack::create();
  GfSlowAttack::create();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    eventCategoryHandle = sound->createCategoryHandle();
    mapjumpCategoryHandle = sound->createCategoryHandle();
    eventSequenceCategoryHandle = sound->createCategoryHandle();
  }
  initialized = true;
}

GfGameScene::~GfGameScene() {}

void GfGameScene::build(const GfSetupParam &param) {
  // __LINE__ must be 425 as in the original file: it is an argument of the allocation.
#line 425
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameScene(param);
}

void GfGameScene::destroy() {
  GfGameScene *scene = get();
  scene->finalize();
  delete scene;
}

void GfGameScene::finalize() {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->releaseCategoryHandle(eventCategoryHandle);
    sound->releaseCategoryHandle(mapjumpCategoryHandle);
    sound->releaseCategoryHandle(eventSequenceCategoryHandle);
  }
  GfSlowAttack::destroy();
  GfTrinityAttack::destroy();
  initialized = false;
}

void GfGameScene::clearPartyState() {
  for (int partyId = 0; partyId < 3; partyId++) {
    partyStates[partyId] = PartyState();
    partyStates[partyId].partyId = partyId;
  }
}

bool GfGameScene::isPlayerSwimOnCloud() {
  GfObjProperty *property = GfObjUtil::getProperty(GfGameManager::getControlMover());
  return property != nullptr && property->move->type == PROPERTY_MOVE_SWIM_ON_CLOUD;
}

bool GfGameScene::isPlayerWalkAndRun() {
  GfObjProperty *property = GfObjUtil::getProperty(GfGameManager::getControlMover());
  return property != nullptr && property->move->type == PROPERTY_MOVE_WALK;
}

bool GfGameScene::isInitialized() const { return initialized; }

void GfGameScene::clear() {
  ownerBonus = OwnerBonus();
  isOwnerBonusDirty = false;
  questIdForTaskLog = QuestID();
  deadType = GfPlayerDead();
  isForceBossBattleBgmEnable = false;
  isForceBattleBgm = false;
  forceEventBgmTime = 0.0f;
  isPlayerTalkForceEnable = false;
  isGimmickCameraPause = false;
  isAutoBattleEnable = false;
  isDispRexCrystal = false;
  isDispHomuraCrystal = false;
  controlFreeFrames = 0;
  playerControl = 0;
  afterEventCount = 0;
  isStartGame = true;
  isEnableRoomForHikariLv4 = false;
  isBattleMomuri = false;
  isStopMainMenuOpenForGimmick = false;
  isMaskMainMenuEnable = false;
  battleStartCounts[2] = 0;
  battleStartCounts[1] = 0;
  battleStartCounts[0] = 0;
  isValidCollisionVelocity = true;
  listeningPoint = mm::Vec3::zero;
  requestListeningPoint = mm::Vec3::zero;
  isPlayEventEnable = false;
  isBattleEvent = false;
  partyMovers[2] = INVALID_HANDLE;
  partyMovers[1] = INVALID_HANDLE;
  partyMovers[0] = INVALID_HANDLE;
  isRideBlade = false;
  isRequestRideOn = false;
  destroySepiaFilter();
  clearPartyState();
  isWaitReturnFieldState[0] = 0;
  isWaitReturnFieldState[1] = 0;
  isWaitReturnFieldState[2] = 0;
  playerStopFlags.clear();
}

void GfGameScene::destroySepiaFilter() {
  if (sepiaEffect != 0) {
    if (fw::EffectManager::get() != nullptr) {
      fw::EffectManager::get()->kill(sepiaEffect);
    }
    sepiaEffect = 0;
    GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
  }
}

void GfGameScene::setupGame() {
  isOwnerBonusDirty = true;
  isForceBossBattleBgmEnable = false;
  isForceBattleBgm = false;
  forceEventBgmTime = 0.0f;
  isPlayerTalkForceEnable = false;
  isGimmickCameraPause = false;
  isAutoBattleEnable = false;
  isRequestAutoFlag = true;
  isStopMainMenuOpenForGimmick = false;
  isMaskMainMenuEnable = false;
  battleStartCounts[2] = 0;
  battleStartCounts[1] = 0;
  battleStartCounts[0] = 0;
  isValidCollisionVelocity = true;
  listeningPoint = mm::Vec3::zero;
  requestListeningPoint = mm::Vec3::zero;
  isRequestListeningPoint = false;
  partyMovers[2] = INVALID_HANDLE;
  partyMovers[1] = INVALID_HANDLE;
  partyMovers[0] = INVALID_HANDLE;
  isRideBlade = false;
  isRequestRideOn = false;
  destroySepiaFilter();
  isPlayEventEnable = false;
  clearPartyState();
  isWaitReturnFieldState[0] = 0;
  isWaitReturnFieldState[1] = 0;
  isWaitReturnFieldState[2] = 0;
  playerStopFlags.clear();
}

bool GfGameScene::isPlayEvent() const { return isPlayEventEnable; }

bool GfGameScene::isMaskMainMenu() const { return isMaskMainMenuEnable; }

bool GfGameScene::isMoverGetFieldDamage() const { return _gfgsc::isPartyMemberGetFieldDamage(0); }

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

void GfGameScene::setEraseQuestEnemyForEventStart(QuestID quest) {
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *enemies = GfGameObj::getList(OBJECT_TYPE_ENEMY);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = enemies->begin(); it != enemies->end(); ++it) {
    DataParamAcc paramAcc(*it);
    if (paramAcc.getHp() == 0) {
      if (eventObjs.size() != eventObjs.capacity()) {
        eventObjs.push_back(*it);
      }
    } else if (!quest.empty() && GfQuestTarget::getIconType(*it, quest) != 0) {
      if (eventObjs.size() != eventObjs.capacity()) {
        eventObjs.push_back(*it);
      }
    }
  }
  isForceBossBattleBgmEnable = true;
}

void GfGameScene::setEnemyDead(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(GfMountManager::getHandle(handle, GFATTACH_WEAPON, OPTMNT_BLADE));
  if (obj == nullptr) {
    return;
  }
  GfComCollider *collider = obj->getComponent<GfComCollider>();
  if (collider == nullptr) {
    return;
  }
  fw::ColiObject *coli = collider->colis[0];
  if (coli != nullptr) {
    coli->clearState(fw::COLI_STATE_ENABLE);
  }
}

void GfGameScene::setHomuriWeaponExtraMesh(bool isVisible, f32 alpha) {
  if (!GfGameManager::isClearGame()) {
    return;
  }
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX);
  if (partyId == -1) {
    return;
  }
  DataParamAcc paramAcc(GfGameParty::getHandleBlade(partyId, -1));
  if (paramAcc.isValid() && paramAcc.getBdatId() == BLADE_HOMURI) {
    SCOM_HOMURI_PARTS::create(partyId, isVisible, alpha);
  }
}

bool GfGameScene::isEnableFieldBladeChange() const {
  if (fieldBladeChangeTime >= FIELD_BLADE_CHANGE_WAIT_TIME && GfGameManager::isEnableOpenMainMenu()) {
    return GfGameManager::isControlFree();
  }
  return false;
}

bool GfGameScene::requestFieldBladeChange() {
  if (!isEnableFieldBladeChange()) {
    return false;
  }
  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeaderDriver();
  u32 partyId = GfGameParty::getPartyId(leader);
  if (partyId >= 3) {
    return false;
  }
  DataParamAcc paramAcc(leader);
  int bladeSet = paramAcc.getBladeSet(false);
  for (int count = GfDataDriver::getMaxSetBladeNum(paramAcc.getValidDriverId()); count > 0; count--) {
    bladeSet = bladeSet < count ? bladeSet + 1 : 0;
    u32 blade = paramAcc.getBlade(bladeSet, false);
    if (blade != 0 && blade != BLADE_HOMURI && !GfDataBlade::isDisableHomuraHikari(blade) && !GfDataBlade::isDummyBlade(blade)) {
      GfPlayFactory::createResetBladeForBladeSwitch(partyId, bladeSet);
      return true;
    }
  }
  return false;
}

void GfGameScene::checkFieldBladeChange() {
  if (GfManager::isDestroyNow() || GfGameManager::isBattle() || GfGameManager::isGameOver() || GfGameManager::isPlayerDeadSequence()) {
    return;
  }
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GfObjAcc obj(GfGameParty::getHandleDriver(partyId));
    if (obj.isBattle()) {
      continue;
    }
    DataParamAcc driverAcc(obj.getHandle());
    if (driverAcc.getHp() == 0) {
      continue;
    }
    int bladeSet = GfSelectBlade::getStartBattleSetId(partyId);
    if (bladeSet >= 0) {
      DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
      if (bladeSet != paramAcc.getBladeSet(false)) {
        if (isEnableRideCondition(partyId)) {
          GfPlayFactory::createResetBladeForBattleEnd(partyId, bladeSet, false);
        }
        continue;
      }
    }
    battleStartCounts[partyId] = 0;
  }
}

bool GfGameScene::isEnableRideCondition(u32 partyId) const {
  if (partyId != 0) {
    return true;
  }
  if (GfGameRide::testRideOn()) {
    return false;
  }
  if (GfGameManager::isPlayerDeadSequence()) {
    return false;
  }
  GfObjAcc obj(GfGameManager::getPartyLeaderDriver());
  if (obj.isBattle()) {
    return false;
  }
  if (obj.getPartyID() != 0) {
    return true;
  }
  if (!GfDataParty::isRideChar(obj.getDriverId())) {
    return true;
  }
  if (partyStates[0].fieldFrames < 3) {
    return false;
  }
  if (GfLayerPause::isLayerPause(OBJ_LAYER_PLAYER)) {
    return false;
  }
  return partyStates[0].moverState != MOVER_STATE_SWIM;
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

bool GfGameScene::isRide(u32 partyId) const {
  if (partyId != -1) {
    GfObjAcc obj(GfGameParty::getHandleDriver(partyId));
    if (GfDataParty::isNiaByakko(partyId)) {
      return !obj.isBattle();
    }
  }
  return false;
}

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
      character.healTime = 0.0f;
      return;
    }
  }
}

void GfGameScene::createDriverAppendModelControl(GF_OBJ_HANDLE *handle) {
  GfObjAcc obj(handle);
  if (!obj.isValidModel()) {
    return;
  }
  GF_OBJ_HANDLE *wire = GfMountManager::getHandle(handle, GFATTACH_BELONGING, OPTMNT_WIRE);
  if (GfObjUtil::getObjType(wire) == OBJECT_TYPE_DRIVER) {
    // __LINE__ must be 1206 as in the original file: it is an argument of the allocation.
#line 1206
    appendWires.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAppendWire(wire, handle));
  }
}

void GfGameScene::destroyDriverAppendModelControl(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GfAppendWire *, 8>::iterator it = mm::mtl::find_if(
      appendWires.begin(), appendWires.end(), [handle](GfAppendWire *wire) { return wire->owner == handle || wire->wire == handle; });
  if (it != appendWires.end()) {
    delete *it;
    appendWires.erase(it);
  }
}

void GfGameScene::enterExtraControlForHanaJS(GF_OBJ_HANDLE *handle) {
  if (hanaJsObjs.size() == 8) {
    return;
  }
  GfObjAcc obj(handle);
  if (obj.getBdatId() == BLADE_HANA_JS) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
    if (setup != nullptr && !setup->isEvent()) {
      hanaJsObjs.push_back(handle);
    }
  }
}

void GfGameScene::leaveExtraControlForHanaJS(GF_OBJ_HANDLE *handle) {
  GF_OBJ_HANDLE **it = mm::mtl::find(hanaJsObjs.begin(), hanaJsObjs.end(), handle);
  if (it != hanaJsObjs.end()) {
    hanaJsObjs.erase(it);
  }
}

GfAppendWire *GfGameScene::getAppendControl(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GfAppendWire *, 8>::iterator it = mm::mtl::find_if(
      appendWires.begin(), appendWires.end(), [handle](GfAppendWire *wire) { return wire->owner == handle || wire->wire == handle; });
  if (it == appendWires.end()) {
    return nullptr;
  }
  return *it;
}

void GfGameScene::saveBattleHpForEnemy(GF_OBJ_HANDLE *handle) {
  if (!GfGameManager::isScenarioGame()) {
    return;
  }
  DataParamAcc paramAcc(handle);
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup == nullptr || !setup->isEvent()) {
    u32 hp = paramAcc.getHp();
    if (hp != 0) {
      u32 savedHpType = GfDataEnemy::getSavedHpType(paramAcc.getValidBdatId());
      if (savedHpType >= SAVED_HP_TYPE_FIRST && savedHpType <= SAVED_HP_TYPE_LAST) {
        GfDataEnemy::setSavedHp(savedHpType, hp);
      }
    }
  }
}

const mm::Vec3 &GfGameScene::getEnableSavePos() const {
  for (int i = 0; i < 7; i++) {
    if (savePositions[i].isEnable) {
      return savePositions[i + 1].position;
    }
  }
  return GfGameManager::getControlMoverPosition();
}

bool GfGameScene::isDisableJumpForRide() const {
  if (isRideBlade) {
    GfObjAcc obj(GfGameParty::getHandleDriver(0));
    if (!isBattle() || obj.isBattle() || partyStates[0].moverState == MOVER_STATE_SWIM) {
      return isRideBlade;
    }
  }
  return false;
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

void GfGameScene::applyMapjumpForStart(const MapjumpCallbackInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GF_OBJ_HANDLE *handle = GfGameParty::getHandleDriver(partyId);
    if (handle == INVALID_HANDLE) {
      continue;
    }
    DataParamAcc paramAcc(handle);
    if (paramAcc.isValid()) {
      GfObj *obj = GfObjUtil::getObj(handle);
      if (obj != nullptr) {
        MsgObjectHealHp message(0, HEAL_TYPE_FULL);
        obj->sendMessage(obj, message);
      }
    }
  }
  for (SavePos &savePosition : savePositions) {
    savePosition.position = mm::Vec3::zero;
    savePosition.isEnable = false;
  }
}

void GfGameScene::applyMapjumpForEnd(const MapjumpCallbackInfo &info) {
  SCOM_ZONE::create(info.map);
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_WEATHER, 1.0f, 1.0f);
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_BGM, 1.0f, 1.0f);
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_EVENT_BGM, 1.0f, 1.0f);
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_FIELD_SE, 1.0f, 1.0f);
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GIMMICK_SE, 1.0f, 1.0f);
    sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_ENV, 1.0f, 1.0f);
  }
}

void GfGameScene::gevExecBuy(u32, u32, u32 shop) {
  if (shop == SHOP_PRIVILEGE && GfGameFlag::getLocal(1, FLAG_PRIVILEGE_ITEM) == 0 && GfDataShop::getPrivilegeItem(SHOP_PRIVILEGE) != 0) {
    GfGameFlag::setLocal(1, FLAG_PRIVILEGE_ITEM, 1);
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

void GfGameScene::gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) {
  if (blade == BLADE_SUZAKU && activateType != 0 && oldActivateType == 0 && GfDataUtil::getScenarioFlag() == SCENARIO_FLAG_SUZAKU_ACTIVATE) {
    for (u32 slot = 0; slot < GfDataBlade::getEquipOrbMax(BLADE_SUZAKU); slot++) {
      GfEquipUtil::equipBladeOrb(BLADE_SUZAKU, 0, slot, GfItemHandle(0));
    }
    SDataBlade *dataBlade = GfDataBlade::getSDataBlade(BLADE_SUZAKU);
    dataBlade->weapon = GfBdatChrBl::get()->getChrBlDefWeapon(BLADE_SUZAKU);
  }
  if (activateType == 0 && oldActivateType != 0 && !GfDataBlade::isUnselect(blade)) {
    GfGameUtil::execSaveAchievementPopup(blade);
  }
}

void GfGameScene::gevBladeUnselect(u32 blade, bool unselect) {
  if (!unselect && !GfDataBlade::isActivateUnuse(blade)) {
    GfGameUtil::execSaveAchievementPopup(blade);
  }
}

void GfGameScene::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  switch (event) {
  case GEV_MAPJUMP_CHANGE_MAP:
    applyMapjumpForCleanup(info);
    break;
  case GEV_MAPJUMP_END:
    applyMapjumpForEnd(info);
    break;
  case GEV_MAPJUMP_START:
    applyMapjumpForStart(info);
    break;
  default:
    break;
  }
}

void GfGameScene::gevItemAdd(u32 item, int count) {
  if (GfItemUtil::isPrecious(item)) {
    isOwnerBonusDirty = true;
  }
  isRequestAutoFlag = true;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 start = bdatItem->getCrystalListStart();
  u32 end = bdatItem->getCrystalListEnd();
  u32 crystalCount = 0;
  for (u32 crystal = start; crystal < end; crystal++) {
    crystalCount += GfItemUtil::getItemBoxCount(crystal);
  }
  GfGameFlag::setLocal(8, FLAG_CRYSTAL_COUNT, crystalCount > 0xff ? 0xff : crystalCount);
  if (count > 0) {
    if (GfDataItem::isHomuraCookItem(item)) {
      addAchievementCount(ACHIEVEMENT_STATS_HOMURA_COOK_ITEM, count);
    } else if (GfDataItem::isYuohCookItem(item)) {
      addAchievementCount(ACHIEVEMENT_STATS_YUOH_COOK_ITEM, count);
    } else if (GfDataItem::isMusubiCookItem(item)) {
      addAchievementCount(ACHIEVEMENT_STATS_MUSUBI_COOK_ITEM, count);
    } else if (GfDataItem::isMayItem(item)) {
      addAchievementCount(ACHIEVEMENT_STATS_MAY_ITEM, count);
    } else if (GfDataItem::isTukiItem(item)) {
      addAchievementCount(ACHIEVEMENT_STATS_TUKI_ITEM, count);
    }
  }
}

void GfGameScene::gevGameObjEnter(GF_OBJ_HANDLE *handle) {
  GfObjAcc obj(handle);
  switch (obj.getType()) {
  case OBJECT_TYPE_BELONGING:
    createDriverAppendModelControl(handle);
    break;
  case OBJECT_TYPE_NPC:
    enterExtraControlForHanaJS(handle);
    break;
  case OBJECT_TYPE_BLADE: {
    enterExtraControlForHanaJS(handle);
    ActivateType activateType = GfDataBlade::getBladeActivateType(obj.getBladeId());
    GfEvent::callBladeActivate(obj.getBladeId(), activateType, activateType);
    break;
  }
  }
}

void GfGameScene::gevGameObjLeave(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER: {
    GfObjSetupDriver *setup = GfObjUtil::getObjSetup<GfObjSetupDriver>(handle);
    if (setup != nullptr && setup->partyMember != -1) {
      battleStartCounts[setup->partyMember] = 0;
    }
    break;
  }
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_NPC:
    leaveExtraControlForHanaJS(handle);
    break;
  case OBJECT_TYPE_ENEMY:
    saveBattleHpForEnemy(handle);
    break;
  case OBJECT_TYPE_BELONGING:
    destroyDriverAppendModelControl(handle);
    break;
  }
}

void GfGameScene::gevChangeTimeRange(u32 timeRange) {
  if (!GfGameManager::isControlFree()) {
    return;
  }
  CV_FIELD voice;
  if (timeRange == TIME_RANGE_MORNING) {
    voice = CV_FIELD_TIME_MORNING;
  } else if (timeRange == TIME_RANGE_EVENING) {
    voice = CV_FIELD_TIME_NIGHT;
  } else {
    return;
  }
  SCOM_FIELD_VOICE::createTime(voice);
}

void GfGameScene::gevControllFree(bool) {}

void GfGameScene::gevBattleStart() {
  battleAchievement.battleStart();
  if (isForceBossBattleBgmEnable) {
    if (GfGameManager::isExistBossEnemy() || GfFieldBgm::get()->isBossBgmCopied()) {
      isForceBattleBgm = true;
    } else {
      isForceBossBattleBgmEnable = false;
    }
  }
  forceEventBgmTime = 0.0f;
}

void GfGameScene::gevBattleEnd() {
  if (!GfGameManager::isPlayerDeadSequence()) {
    for (u32 partyId = 0; partyId < 3; partyId++) {
      DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
      if (paramAcc.isValid() && paramAcc.getHp() == 0) {
        GfObj *obj = GfObjUtil::getObj(paramAcc.handle);
        if (obj != nullptr) {
          MsgObjectHealHp message(1, HEAL_TYPE_NORMAL);
          obj->sendMessage(obj, message);
        }
      }
    }
  }
  battleAchievement.battleEnd();
  if (isBattleEvent) {
    isForceBossBattleBgmEnable = true;
  } else {
    isForceBossBattleBgmEnable = false;
    isForceBattleBgm = false;
  }
}

void GfGameScene::gevMercenariesMissionFlag(u32 mission, u32 flag, u32) {
  if (GfGameUtilNanakoori::checkCompleteMission(mission, flag)) {
    isRequestAutoFlag = true;
  }
}

void GfGameScene::playEventSequenceStart(u32 event) {
  switch (event) {
  case EVENT_NIA_SET_BYAKKO:
    GfDataDriver::setBlade(DRIVER_NIA, BLADE_BYAKKO, -1);
    break;
  case EVENT_SUZAKU_ACTIVATE: {
    GfDataBlade::setActivateDriver(BLADE_SUZAKU, -1, DRIVER_VANDAMME, 0);
    int bladeSet = GfDataDriver::getSetIdByBlade(DRIVER_VANDAMME, BLADE_SUZAKU);
    DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, DRIVER_VANDAMME, GimmickType());
    paramAcc.setBladeSet(bladeSet);
    GfDataBlade::setUnselect(BLADE_SUZAKU, true);
    break;
  }
  case EVENT_SUZAKU_RELEASE:
    GfDataBlade::setUnselect(BLADE_SUZAKU, false);
    GfDataBlade::setActivateUnuse(BLADE_SUZAKU);
    break;
  case EVENT_SHIN_SET_DUMMY:
    GfDataDriver::unsetBlade(BLADE_REX_DUMMY);
    GfDataDriver::setBlade(DRIVER_SHIN, BLADE_SHIN_DUMMY, -1);
    break;
  case EVENT_SAVE_MONEY: {
    u32 money = GfDataUtil::getMoney();
    GfGameFlag::setLocal(16, FLAG_EVENT_MONEY, money > 0xffff ? 0xffff : money);
    break;
  }
  }
  isMaskMainMenuEnable = true;
  for (SavePos &savePosition : savePositions) {
    savePosition.position = mm::Vec3::zero;
    savePosition.isEnable = false;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_CHARACTER_SE, 0.0f, 0.5f);
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_NO_SLOW_SE, 0.0f, 0.5f);
  }
}

void GfGameScene::playEventSequenceEnd(u32 event) {
  if (event == EVENT_LAST_KIZUNA_TALK) {
    GfGameUtil::addTrusuPointByLastKizunaTalk();
  }
  isPlayEventEnable = false;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_CHARACTER_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_NO_SLOW_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_ENV, 1.0f, 0.2f);
    sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GIMMICK_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_WEATHER, 1.0f, 0.2f);
    sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_BGM, 1.0f, 0.2f);
  }
  if (GfManager::isExecModeThater()) {
    return;
  }
  GfGameUtil::setWatchedEvent(event);
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

void GfGameScene::playEventPlayEnd(u32 event) {
  isPlayEventEnable = false;
  if (event != EVENT_KEEP_VOLUME) {
    GfSound *sound = GfSound::get();
    if (sound != nullptr) {
      sound->setCategoryVolume(eventCategoryHandle, CATEGORY_CHARACTER_SE, 0.0f, 0.0f);
      sound->setCategoryVolume(eventCategoryHandle, CATEGORY_NO_SLOW_SE, 0.0f, 0.0f);
      for (u16 mapjumpEvent : MAPJUMP_EVENTS) {
        if (mapjumpEvent == event) {
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_WEATHER, 0.0f, 0.0f);
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_BGM, 0.0f, 0.0f);
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_EVENT_BGM, 0.0f, 0.0f);
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_FIELD_SE, 0.0f, 0.0f);
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GIMMICK_SE, 0.0f, 0.0f);
          sound->setCategoryVolume(mapjumpCategoryHandle, CATEGORY_GAME_ENV, 0.0f, 0.0f);
        }
      }
      if (event == EVENT_ENV_SILENT) {
        sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_ENV, 0.0f, 0.0f);
        sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GIMMICK_SE, 0.0f, 0.0f);
        sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_WEATHER, 0.0f, 0.0f);
        sound->setCategoryVolume(eventSequenceCategoryHandle, CATEGORY_GAME_BGM, 0.0f, 0.0f);
      }
    }
  }
  GfQuestManager::requestOrderQuestForce();
}

void GfGameScene::playEventStartFrame(u32) {
  if (isBattleEvent) {
    isBattleEvent = false;
    isForceBossBattleBgmEnable = false;
    isForceBattleBgm = false;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_CHARACTER_SE, 1.0f, 0.0f);
    sound->setCategoryVolume(eventCategoryHandle, CATEGORY_NO_SLOW_SE, 1.0f, 0.0f);
  }
}

void GfGameScene::updatePlayerState() {
  for (PartyState &state : partyStates) {
    state.moverState = MOVER_STATE_NONE;
    state.isFloating = false;
    GfObjProperty *property = GfObjUtil::getProperty(GfGameParty::getHandleMover(state.partyId));
    if (property != nullptr && property->move != nullptr) {
      GfObjPropertyMove *move = property->move;
      state.moverState = MOVER_STATE_FIELD;
      switch (move->type) {
      case PROPERTY_MOVE_SWIM:
        state.moverState = MOVER_STATE_SWIM;
        break;
      case PROPERTY_MOVE_CLIMB:
        state.moverState = MOVER_STATE_CLIMB;
        break;
      case PROPERTY_MOVE_ACTION:
        state.moverState = MOVER_STATE_BUSY;
        break;
      }
      if (move->isJump) {
        state.moverState = MOVER_STATE_JUMP;
      }
      if (move->groundObj != INVALID_HANDLE) {
        state.moverState = MOVER_STATE_BUSY;
      }
      if (move->floatTime != 0.0f) {
        state.isFloating = true;
      }
    }
    if (state.moverState == MOVER_STATE_FIELD && !GfGameManager::isControlFree()) {
      state.moverState = MOVER_STATE_BUSY;
    }
    state.isGetFieldDamage = _gfgsc::isPartyMemberGetFieldDamage(state.partyId);
    GfObjAcc obj(GfGameParty::getHandleMover(state.partyId));
    state.fieldFrames = obj.isBattle() ? 0 : state.fieldFrames + 1;
  }
}

void GfGameScene::gevPlayEvent(GEV event, u32 eventId) {
  switch (event) {
  case GEV_EVENT_END:
    playEventPlayStart(eventId);
    break;
  case GEV_EVENT_PLAY_END:
    playEventPlayEnd(eventId);
    break;
  case GEV_EVENT_SEQUENCE_START:
    playEventSequenceStart(eventId);
    break;
  case GEV_EVENT_SEQUENCE_END:
    playEventSequenceEnd(eventId);
    break;
  case GEV_EVENT_START_FRAME:
    playEventStartFrame(eventId);
    break;
  }
}

void GfGameScene::gevSelectHikari(bool) {
  if (GfDataBlade::getSetDriver(BLADE_HOMURA) != DRIVER_REX || GfDataBlade::getSetDriver(BLADE_HIKARI) != DRIVER_REX) {
    return;
  }
  if ((GfDataBlade::isHikariCurrent() && GfDataDriver::getBlade(DRIVER_REX, -1) == BLADE_HOMURA) ||
      (!GfDataBlade::isHikariCurrent() && GfDataDriver::getBlade(DRIVER_REX, -1) == BLADE_HIKARI)) {
    int bladeSet = GfDataDriver::getSetIdByBlade(DRIVER_REX, GfDataBlade::isHikariCurrent() ? BLADE_HIKARI : BLADE_HOMURA);
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriverByBdatID(DRIVER_REX);
    if (!GfObjUtil::isValid(driver)) {
      DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, DRIVER_REX, GimmickType());
      paramAcc.setBladeSet(bladeSet);
    } else {
      GfGameUtil::setBladeSelect(driver, bladeSet);
      RQ_SETUP_PARTY info;
      GfGameParty::getCurrentPartyInfo(info);
      GfReqCommand::reqChangeParty(info);
    }
  }
}

void GfGameScene::qevCompleteQuest(const QuestCompleteParam &) { isRequestAutoFlag = true; }

void GfGameScene::updateAppendModel(const fw::UpdateInfo &info) {
  for (auto it = appendWires.begin(); it != appendWires.end(); ++it) {
    (*it)->update(info);
  }
  for (auto it = appendWires.begin(); it != appendWires.end();) {
    if (!GfObjUtil::isValid((*it)->owner)) {
      delete *it;
      it = appendWires.erase(it);
    } else {
      ++it;
    }
  }
}

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

void GfGameScene::enterBattle(bool isBattle) {
  if (isBattle != ((flags & FLAG_BATTLE) != 0)) {
    if (!isBattle) {
      flags &= ~FLAG_BATTLE;
      GfEvent::callBattleEnd();
      isBattleMomuri = false;
      return;
    }
    flags |= FLAG_BATTLE;
    GfEvent::callBattleStart();
  }
  isBattleMomuri = false;
  if (!isBattle) {
    return;
  }
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX);
  if (partyId == -1) {
    return;
  }
  DataParamAcc paramAcc(GfGameParty::getHandleBlade(partyId, -1));
  if (paramAcc.isValid() && paramAcc.getBdatId() == BLADE_HOMURI) {
    isBattleMomuri = true;
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

void GfGameScene::addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage) {
  battleAchievement.addDamage(handle, damage);
  setDamageCharacter(handle);
}

void GfGameScene::addMoneyLog() { moneyLogTime = MONEY_LOG_TIME; }

QuestID GfGameScene::getQuestIdForTaskLog() const { return questIdForTaskLog; }

void GfGameScene::updateOwnerBonus(const fw::UpdateInfo &) {
  if (isOwnerBonusDirty) {
    isOwnerBonusDirty = false;
    GfGameUtil::getOwnerBonus(ownerBonus);
  }
}

void GfGameScene::updatePartyMover(const fw::UpdateInfo &) {
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 3> movers;
  movers[0] = GfGameParty::getHandleMover(0);
  movers[1] = GfGameParty::getHandleMover(1);
  movers[2] = GfGameParty::getHandleMover(2);
  for (GF_OBJ_HANDLE *mover : movers) {
    if (mover != INVALID_HANDLE && partyMovers[0] != mover && partyMovers[1] != mover && partyMovers[2] != mover) {
      GfEvent::callPartyMover(mover, true);
    }
  }
  for (GF_OBJ_HANDLE *mover : partyMovers) {
    if (mover != INVALID_HANDLE && mover != movers[0] && mover != movers[1] && mover != movers[2]) {
      GfEvent::callPartyMover(mover, false);
    }
  }
  partyMovers = movers;
}

void GfGameScene::updateParam(const fw::UpdateInfo &info) {
  updateOwnerBonus(info);
  {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_RESERVER, 0);
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY, 0);
    for (u16 driver : drivers) {
      GfGameUtil::refreshEnhanceState(driver);
    }
  }
  updatePlayerState();
}

void GfGameScene::updateExtraControlForHanaJS(const fw::UpdateInfo &) {
  for (GF_OBJ_HANDLE *handle : hanaJsObjs) {
    GfObjAcc obj(handle);
    if (obj.getBdatId() == BLADE_HANA_JS) {
      int index = obj.getEtcParamIndex("skin_line");
      if (index >= 0 && GfDataUtil::getScenarioFlag() < 2034) {
        obj.setEtcParam(index, 0.0f);
      }
    }
  }
}

void GfGameScene::updatePartyBattle(const fw::UpdateInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GfObjAcc obj(GfGameParty::getHandleDriver(partyId));
    if (obj.isBattle() && battleStartCounts[partyId] < 3) {
      battleStartCounts[partyId]++;
      GfGameParty::setupBattleStart(partyId);
    }
  }
}

void GfGameScene::updateMaskMainMenu(const fw::UpdateInfo &) {
  if (!GfGameManager::isEvent(false) && GfGameManager::isFadeClear()) {
    isMaskMainMenuEnable = false;
  }
}

void GfGameScene::updatePlayerStopFlag(const fw::UpdateInfo &) {
  if (playerStopFlagQueue.empty()) {
    return;
  }
  u8 request = playerStopFlagQueue.pop_front();
  if (request != 0) {
    playerStopFlags.set(request & 0x7f, (request & 0x80) != 0);
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

void GfGameScene::updatePartyObjFlag(const fw::UpdateInfo &) {
  for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_DRIVER)) {
    GfObjUtil::applyExecUpdate(handle);
  }
  for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_BLADE)) {
    GfObjUtil::applyExecUpdate(handle);
  }
  for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_PC_WEAPON)) {
    GfObjUtil::applyExecUpdate(handle);
  }
}

void GfGameScene::updateBattleMomuri(const fw::UpdateInfo &) {
  if (battleMomuriRequest != -1 && !GfReqManager::isValid(battleMomuriRequest)) {
    battleMomuriRequest = -1;
  }
  if (isBattleMomuri || GfGameManager::isMapjump()) {
    return;
  }
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX);
  if (partyId == -1) {
    return;
  }
  if (!isEnableBattleMomuri(partyId)) {
    return;
  }
  GfBdatChrEnArrange *enArrange = GfBdatChrEnArrange::get();
  for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
    GfObjAcc obj(handle);
    if (obj.isBattle() && enArrange->isChrEnArrangeFlagHomuri(obj.getEnArrangeId())) {
      if (GfGameManager::isControlFree()) {
        isBattleMomuri = true;
        battleMomuriRequest = GfReqCommand::reqChangeBladeWithSetId(GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX), HOMURI_BLADE_SET, false);
      }
      return;
    }
  }
}

void GfGameScene::updateHikariLv4Room(const fw::UpdateInfo &) {
  isEnableRoomForHikariLv4 = false;
  if (GfGameManager::isMapjump()) {
    return;
  }
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX);
  if (partyId == -1) {
    return;
  }
  u32 blade;
  {
    DataParamAcc paramAcc(GfGameParty::getHandleBlade(partyId, -1));
    blade = paramAcc.getValidBdatId();
  }
  if (blade == BLADE_HIKARI && !GfGameManager::isRoom()) {
    GfObjAcc obj(GfGameParty::getHandleDriver(0));
    mm::Vec3 hit;
    mm::Vec3 position = obj.getWorldTransform().position + mm::Vec3(0.0f, 1.0f, 0.0f);
    if (!util::getUpperHitCollision(hit, position, HIKARI_ROOM_HEIGHT)) {
      isEnableRoomForHikariLv4 = true;
    }
  }
}

void GfGameScene::updateStartGame(const fw::UpdateInfo &) {
  if (isStartGame && GfGameManager::isControlFree() && !GfGameManager::isFadeout() && playerControl == GEV_PLAYER_CONTROL_FREE) {
    isStartGame = false;
  }
}

void GfGameScene::updateAfterEventCount(const fw::UpdateInfo &) {
  if (!GfGameManager::isPlaySequenceClear()) {
    afterEventCount = 0;
  } else if (afterEventCount < AFTER_EVENT_COUNT_MAX) {
    afterEventCount++;
  }
}

void GfGameScene::updateControlFreeEvent(const fw::UpdateInfo &) {
  if (GfPlayComGmkTutorialSeq::s_activate <= 0 && (!GfGameManager::isBladeChange() || GfSequentialPlay::isInnerState(GF_STATE_SALVAGE)) &&
      !GfGameManager::isControlFree()) {
    if (controlFreeFrames > 0 && --controlFreeFrames == 0 && playerControl != GEV_PLAYER_CONTROL_LOCK) {
      playerControl = GEV_PLAYER_CONTROL_LOCK;
      GfEvent::callPlayerControl(GEV_PLAYER_CONTROL_LOCK);
    }
  } else if (!GfManager::isExecModeAdvertize()) {
    if (controlFreeFrames < CONTROL_FREE_FRAME && ++controlFreeFrames == CONTROL_FREE_FRAME && playerControl != GEV_PLAYER_CONTROL_FREE) {
      playerControl = GEV_PLAYER_CONTROL_FREE;
      GfEvent::callPlayerControl(GEV_PLAYER_CONTROL_FREE);
    }
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

bool GfGameScene::isPartyBusy(u32 partyId) {
  if (mm::mtl::find(GfPlayComResetBlade::s_execFlag.begin(), GfPlayComResetBlade::s_execFlag.end(), static_cast<u8>(partyId)) !=
      GfPlayComResetBlade::s_execFlag.end()) {
    return true;
  }
  return !isEnableRideCondition(partyId);
}

void GfGameScene::updatePartyInfo(const fw::UpdateInfo &) {
  if (GfGameManager::isBattle()) {
    for (u32 partyId = 0; partyId < 3; partyId++) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
      GfGameParty::getHandleBlade(partyId, -1);
      isWaitReturnFieldState[partyId] = GfGameObj::isValidGameObj(driver, true, nullptr);
    }
    return;
  }
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(partyId, -1);
    if (!GfGameObj::isValidGameObj(driver, true, nullptr)) {
      isWaitReturnFieldState[partyId] = 0;
      continue;
    }
    if (bladeChangeRequests[partyId] != -1) {
      isWaitReturnFieldState[partyId] = 1;
      continue;
    }
    GfObjAcc driverObj(driver);
    GfObjAcc bladeObj(blade);
    if (driverObj.isBattle() || bladeObj.isBattle()) {
      isWaitReturnFieldState[partyId] = 1;
      continue;
    }
    DataParamAcc paramAcc(driver);
    int bladeSet = GfSelectBlade::getStartBattleSetId(partyId);
    if (bladeSet >= 0 && bladeSet != paramAcc.getBladeSet(false)) {
      isWaitReturnFieldState[partyId] = 1;
    } else if (isWaitReturnFieldState[partyId] == 1 && !isPartyBusy(partyId)) {
      isWaitReturnFieldState[partyId] = 0;
      GfEvent::callPartyReturnFieldState(partyId);
    }
  }
}

void GfGameScene::updateBladeChangeForBattle(const fw::UpdateInfo &) {
  for (u32 &request : bladeChangeRequests) {
    if (request != -1 && !GfReqManager::isValid(request)) {
      request = -1;
    }
  }
  checkFieldBladeChangeForRide();
  checkFieldBladeChange();
}

void GfGameScene::updateBladeChangeInField(const fw::UpdateInfo &info) {
  f32 time = fieldBladeChangeTime;
  fieldBladeChangeTime = 0.0f;
  if (!GfGameManager::isControlFree() || GfGameManager::isBattle() || GfManager::isDestroyNow() || !btl::Utility::IsEnableFieldBladeChange()) {
    return;
  }
  GfObjAcc obj(GfGameManager::getPartyLeaderDriver());
  if (obj.isBattle()) {
    return;
  }
  if (!GfGameObj::isValidGameObj(obj.getHandle(), false, nullptr)) {
    return;
  }
  if (!GfGameObj::isValidGameObj(GfGameParty::getHandleBlade(GfGameParty::getPartyId(obj.getHandle()), -1), false, nullptr)) {
    return;
  }
  fieldBladeChangeTime = time + info.deltaTime;
}

void GfGameScene::updateColiPrio(const fw::UpdateInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(partyId));
    updateColiPriority(driverAcc, driverAcc.getHp() == 0, partyStates[partyId].moverState == MOVER_STATE_SWIM);
    DataParamAcc bladeAcc(GfGameParty::getHandleBlade(partyId, -1));
    updateColiPriority(bladeAcc, driverAcc.getHp() == 0, partyStates[partyId].moverState == MOVER_STATE_SWIM);
  }
}

void GfGameScene::updateAutoHeal(const fw::UpdateInfo &info) {
  if (!GfGameManager::isControlFree() || GfGameManager::isBattle() || _gfgsc::isPartyMemberGetFieldDamage(0)) {
    for (DamageCharacter &character : damageCharacters) {
      if (character.healTime != 0.0f) {
        character.healTime = 0.0f;
      }
    }
    return;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_PLAYER_DEAD)) {
    return;
  }
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DamageCharacter &character = damageCharacters[partyId];
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
    if (driver == INVALID_HANDLE) {
      if (character.handle != INVALID_HANDLE) {
        character.handle = INVALID_HANDLE;
      }
      continue;
    }
    if (character.handle != driver) {
      character.handle = driver;
    }
    if (partyStates[partyId].isGetFieldDamage) {
      character.healTime = 0.0f;
    }
    DataParamAcc paramAcc(driver);
    u32 hp = paramAcc.getHp();
    u32 maxHp = paramAcc.getHpMax(false);
    if (hp != maxHp) {
      character.healTime += info.deltaTime;
      if (!(character.healTime < AUTO_HEAL_INTERVAL)) {
        character.healTime = 0.0f;
        GfObj *obj = GfObjUtil::getObj(driver);
        if (obj != nullptr) {
          u32 heal = floorf(maxHp * AUTO_HEAL_RATE * 0.01f + 0.000001f);
          MsgObjectHealHp message(hp + heal > maxHp ? maxHp - hp : heal, HEAL_TYPE_NORMAL);
          obj->sendMessage(obj, message);
        }
      }
    } else if (character.healTime > 0.0f) {
      character.healTime = 0.0f;
    }
  }
}

void GfGameScene::updateMaxHp(const fw::UpdateInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleDriver(partyId));
    if (obj == nullptr) {
      continue;
    }
    DataParamAcc paramAcc(obj->handle);
    paramAcc.getHp();
    paramAcc.getHpMax(false);
    if (paramAcc.getHp() > paramAcc.getHpMax(false)) {
      MsgObjectHealHp message(0, HEAL_TYPE_FULL);
      obj->sendMessage(obj, message);
    }
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

void GfGameScene::updateQuestTaskLog(const fw::UpdateInfo &) {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  if (questIdForTaskLog.empty()) {
    if (!quest.empty()) {
      questIdForTaskLog.id = quest.id;
      questIdForTaskLog.variant = quest.variant;
    }
  } else if (!(questIdForTaskLog == quest)) {
    if (GfGameManager::isFadeout() || (GfGameManager::isControlFree() && !GfGameManager::isTalking() && !GfGameManager::isEvent(false)) ||
        GfGameManager::isFullScreenMenu()) {
      questIdForTaskLog.id = quest.id;
      questIdForTaskLog.variant = quest.variant;
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

void GfGameScene::updateMoveAchievement(const fw::UpdateInfo &) {
  GfObjAcc obj(GfGameManager::getControlMover());
  if (!obj.isValidTransform()) {
    return;
  }
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM) && GfGameManager::isControlFree()) {
    const mm::Vec3 &position = obj.getWorldTransform().position;
    f32 x = position.x - movePosition.x;
    f32 y = position.y - movePosition.y;
    f32 z = position.z - movePosition.z;
    f32 distance = sqrtf(x * x + y * y + z * z);
    if (!(distance < MOVE_DISTANCE_MIN)) {
      for (MoveAchievement &achievement : moveAchievements) {
        if (!achievement.isMove()) {
          continue;
        }
        f32 moveDistance = distance < MOVE_DISTANCE_MAX ? distance + GfDataUtil::getMoveDistance(achievement.moveType)
                                                        : GfDataUtil::getMoveDistance(achievement.moveType);
        u32 meter = moveDistance;
        if (meter != 0) {
          moveDistance -= meter;
          SCOM_ACHIEV_INC::addTotalCount(achievement.achievement, 1);
          SCOM_ACHIEV_INC::create(achievement.achievement, 1, 0);
          SCOM_ACHIEV_INC::createCurrentBlade(GfGameManager::getPartyLeaderDriver(), achievement.achievement + 1, 1);
        }
        GfDataUtil::setMoveDistance(achievement.moveType, moveDistance);
      }
    }
  }
  movePosition = obj.getWorldTransform().position;
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

void GfGameScene::updateCrystalPopup(const fw::UpdateInfo &) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  for (u32 index = 0; index < 4; index++) {
    if (GfGameFlag::getLocal(1, FLAG_CRYSTAL_POPUP + index) != 0) {
      continue;
    }
    u16 condition = bdatItem->getCrystalListCondition(CRYSTAL_LIST_FIRST + index);
    if (condition != 0 && GfGameCond::isGameCond(condition)) {
      SCOM_POPUP::createCrystalOK(CRYSTAL_ITEM_FIRST + index * 2);
      GfGameFlag::setLocal(1, FLAG_CRYSTAL_POPUP + index, 1);
    }
  }
}

void GfGameScene::updateEnableSavePos(const fw::UpdateInfo &) {
  for (int i = 7; i > 0; i--) {
    savePositions[i].position = savePositions[i - 1].position;
    savePositions[i].isEnable = savePositions[i - 1].isEnable;
  }
  bool isEnable;
  if (!GfGameManager::isEnableOpenMainMenu() || GfPause::isPause(PAUSE_BIT_SYSTEM)) {
    isEnable = false;
  } else if (GfSequentialPlay::isPlay()) {
    isEnable = false;
  } else {
    isEnable = !_gfgsc::isPartyMemberGetFieldDamage(0);
  }
  savePositions[0].position = GfGameManager::getControlMoverPosition();
  savePositions[0].isEnable = isEnable;
}

void GfGameScene::updateRideRequest(const fw::UpdateInfo &) {
  if (!isRequestRideOn) {
    return;
  }
  if (!GfGameRide::testRideOn()) {
    GfObjAcc obj(GfGameParty::getHandleDriver(0));
    if (GfDataParty::isNiaByakko(0) && !obj.isBattle()) {
      if (isEnableRideCondition(0)) {
        isRequestRideOn = false;
        GfGameRide::setRideOn(true);
      }
      return;
    }
  }
  isRequestRideOn = false;
}

void GfGameScene::updateEnemySaveHp(const fw::UpdateInfo &) {
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *enemies = GfGameObj::getList(OBJECT_TYPE_ENEMY);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = enemies->begin(); it != enemies->end(); ++it) {
    GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(*it);
    if (setup != nullptr && setup->savedHp != 0) {
      GfObjAcc obj(*it);
      if (obj.isBattle()) {
        MsgObjectChangeHp message(setup->savedHp);
        obj.getObj()->sendMessage(obj.getObj(), message);
        setup->savedHp = 0;
      }
    }
  }
}

void GfGameScene::setRideOn(u32 partyId) {
  if (partyId == -1) {
    return;
  }
  GfObjAcc obj(GfGameParty::getHandleDriver(partyId));
  if (GfDataParty::isNiaByakko(partyId) && !obj.isBattle()) {
    isRequestRideOn = false;
    if (!GfGameRide::testRideOn()) {
      isRequestRideOn = true;
    }
  }
}

} // namespace gf
