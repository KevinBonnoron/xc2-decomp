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

void unknown001(const DataParamAcc &paramAcc, bool isDead, bool isSwim) { // Inferred role: updateColiPriority; original function name unknown.
  if (!paramAcc.isValid()) {
    return;
  }
  GfObj *obj = GfObjUtil::getObj(paramAcc.unknown10);
  if (obj == nullptr) {
    return;
  }
  int priority = obj->unknown100->unknownb0;
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
  fw::ColiObject *coli = collider->unknown18[0];
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
  if (unknown08 != STATE_WAIT_MOVER) {
    unknown00->setPlayerStopFlag(unknown0c, true);
    unknown08 = STATE_WAIT_MOVER;
  }
}

void GfGameScene::setPlayerStopFlag(PLSTOP flag, bool isStop) { unknown1d8.push((isStop ? 0x80 : 0) | flag); }

void GfGameScene::EvtPlayerStop::endPlayerStop() {
  if (unknown00->isPlayerStopFlag(unknown0c)) {
    unknown00->setPlayerStopFlag(unknown0c, false);
    GfGameManager::setGmkTutorialMoverOK(false);
  }
  unknown08 = STATE_NONE;
}

void GfGameScene::EvtPlayerStop::resetState() {
  if (unknown00->isPlayerStopFlag(unknown0c)) {
    unknown00->setPlayerStopFlag(unknown0c, false);
    GfGameManager::setGmkTutorialMoverOK(false);
  }
  unknown08 = STATE_NONE;
}

bool GfGameScene::isPlayerStopFlag(PLSTOP flag) { return unknown1b8.test(flag); }

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
  if (unknown08 == STATE_WAIT_MOVER && GfGameManager::isGmkTutorialMoverOK()) {
    unknown08 = STATE_STOP;
  }
}

void GfGameScene::BattleAchievement::battleStart() {
  unknown00 = true;
  unknown08 = 0;
  GfDataAchievement::clearTotalCount(ACHIEVEMENT_STATS_BATTLE_DAMAGE);
}

void GfGameScene::BattleAchievement::battleEnd() {
  if (unknown04 != 0) {
    SCOM_ACHIEV_INC::createBattle();
  }
  GfDataAchievement::clearTotalCount(ACHIEVEMENT_STATS_BATTLE_DAMAGE);
  unknown00 = false;
  unknown08 = 0;
  unknown04 = 0;
}

void GfGameScene::BattleAchievement::enemyDamage(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &damage) {
  if (unknown08 < damage.unknown08->unknown08) {
    unknown08 = damage.unknown08->unknown08;
    SCOM_ACHIEV_INC::createDamageMax(damage.unknown10, damage.unknown08->unknown08);
  }
  SCOM_ACHIEV_INC::createDamageAdd(damage.unknown10, damage.unknown08->unknown08);
  if (damage.unknown08->unknown28_1) {
    SCOM_ACHIEV_INC::createCriticalHit(damage.unknown10);
  }
  unknown04++;
}

void GfGameScene::BattleAchievement::driverDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage) {
  SCOM_ACHIEV_INC::createDamageGet(handle, damage.unknown08->unknown08);
  if (damage.unknown08->unknown28_1) {
    SCOM_ACHIEV_INC::createCriticalGet(handle);
  }
  unknown04++;
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
  unknown0c[0] = -1;
  unknown0c[1] = -1;
  unknown0c[2] = -1;
  unknown18 = 0.0f;
  unknown50 = true;
  unknown150 = mm::Vec3::zero;
  unknown228[2] = 0;
  unknown228[1] = 0;
  unknown228[0] = 0;
  unknown280 = mm::Vec3::zero;
  unknown290 = mm::Vec3::zero;
  unknown2a0 = false;
  m_playEvent = false;
  unknown648 = false;
  unknown3f8[2] = INVALID_HANDLE;
  unknown3f8[1] = INVALID_HANDLE;
  unknown3f8[0] = INVALID_HANDLE;
  for (SavePos &savePosition : unknown2b0) {
    savePosition.unknown00 = mm::Vec3::zero;
    savePosition.unknown10 = false;
  }
  clearPartyState();
  unknown160.push_back(MoveAchievement(AMOVE_SWIM, ACHIEVEMENT_STATS_SWIM, isPlayerSwimOnCloud));
  unknown160.push_back(MoveAchievement(AMOVE_WALK, ACHIEVEMENT_STATS_WALK, isPlayerWalkAndRun));
  unknown1ac[0] = 0;
  unknown1ac[1] = 0;
  unknown1ac[2] = 0;
  GfTrinityAttack::create();
  GfSlowAttack::create();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    unknown650 = sound->createCategoryHandle();
    unknown658 = sound->createCategoryHandle();
    unknown660 = sound->createCategoryHandle();
  }
  m_initialized = true;
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
    sound->releaseCategoryHandle(unknown650);
    sound->releaseCategoryHandle(unknown658);
    sound->releaseCategoryHandle(unknown660);
  }
  GfSlowAttack::destroy();
  GfTrinityAttack::destroy();
  m_initialized = false;
}

void GfGameScene::clearPartyState() {
  for (int partyId = 0; partyId < 3; partyId++) {
    unknown240[partyId] = PartyState();
    unknown240[partyId].unknown00 = partyId;
  }
}

bool GfGameScene::isPlayerSwimOnCloud() {
  GfObjProperty *property = GfObjUtil::getProperty(GfGameManager::getControlMover());
  return property != nullptr && property->unknown18->unknown00 == PROPERTY_MOVE_SWIM_ON_CLOUD;
}

bool GfGameScene::isPlayerWalkAndRun() {
  GfObjProperty *property = GfObjUtil::getProperty(GfGameManager::getControlMover());
  return property != nullptr && property->unknown18->unknown00 == PROPERTY_MOVE_WALK;
}

bool GfGameScene::isInitialized() const { return m_initialized; }

void GfGameScene::clear() {
  m_ownerBonus = OwnerBonus();
  unknown50 = false;
  m_questIdForTaskLog = QuestID();
  m_deadType = GfPlayerDead();
  m_forceBossBattleBgm = false;
  unknown132 = false;
  m_forceEventBgm = 0.0f;
  unknown138 = false;
  unknown139 = false;
  m_autoBattle = false;
  unknown1bc = false;
  unknown1bd = false;
  unknown1c0 = 0;
  unknown1c4 = 0;
  unknown624 = 0;
  unknown1c9 = true;
  unknown1ca = false;
  unknown1cb = false;
  unknown1d0 = false;
  m_maskMainMenu = false;
  unknown228[2] = 0;
  unknown228[1] = 0;
  unknown228[0] = 0;
  unknown270 = true;
  unknown280 = mm::Vec3::zero;
  unknown290 = mm::Vec3::zero;
  m_playEvent = false;
  unknown648 = false;
  unknown3f8[2] = INVALID_HANDLE;
  unknown3f8[1] = INVALID_HANDLE;
  unknown3f8[0] = INVALID_HANDLE;
  unknown668 = false;
  unknown669 = false;
  destroySepiaFilter();
  clearPartyState();
  unknown1ac[0] = 0;
  unknown1ac[1] = 0;
  unknown1ac[2] = 0;
  unknown1b8.clear();
}

void GfGameScene::destroySepiaFilter() {
  if (unknown66c != 0) {
    if (fw::EffectManager::get() != nullptr) {
      fw::EffectManager::get()->kill(unknown66c);
    }
    unknown66c = 0;
    GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
  }
}

void GfGameScene::setupGame() {
  unknown50 = true;
  m_forceBossBattleBgm = false;
  unknown132 = false;
  m_forceEventBgm = 0.0f;
  unknown138 = false;
  unknown139 = false;
  m_autoBattle = false;
  unknown1a9 = true;
  unknown1d0 = false;
  m_maskMainMenu = false;
  unknown228[2] = 0;
  unknown228[1] = 0;
  unknown228[0] = 0;
  unknown270 = true;
  unknown280 = mm::Vec3::zero;
  unknown290 = mm::Vec3::zero;
  unknown2a0 = false;
  unknown3f8[2] = INVALID_HANDLE;
  unknown3f8[1] = INVALID_HANDLE;
  unknown3f8[0] = INVALID_HANDLE;
  unknown668 = false;
  unknown669 = false;
  destroySepiaFilter();
  m_playEvent = false;
  clearPartyState();
  unknown1ac[0] = 0;
  unknown1ac[1] = 0;
  unknown1ac[2] = 0;
  unknown1b8.clear();
}

bool GfGameScene::isPlayEvent() const { return m_playEvent; }

bool GfGameScene::isMaskMainMenu() const { return m_maskMainMenu; }

bool GfGameScene::isMoverGetFieldDamage() const { return _gfgsc::isPartyMemberGetFieldDamage(0); }

void GfGameScene::setEventPlayerStop(bool isStop) { unknown628.setPlayerStop(isStop); }

void GfGameScene::setResetBladePlayerStop(bool isStop) { unknown638.setPlayerStop(isStop); }

bool GfGameScene::isControlFree() const {
  if (GfGameState::getState() == GF_STATE_CONTROL && GfGameManager::getState() == GF_STATE_CONTROL && unknown140 == 0) {
    return GfGameState::getStateReserve() == GF_STATE_CONTROL;
  }
  return false;
}

bool GfGameScene::isControlFreeState() const {
  if (GfGameState::getState() == GF_STATE_CONTROL && GfGameManager::getState() == GF_STATE_CONTROL && unknown140 == 0) {
    return GfGameState::getStateReserve() == GF_STATE_CONTROL;
  }
  return false;
}

void GfGameScene::setEraseQuestEnemyForEventStart(QuestID quest) {
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *enemies = GfGameObj::getList(OBJECT_TYPE_ENEMY);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = enemies->begin(); it != enemies->end(); ++it) {
    DataParamAcc paramAcc(*it);
    if (paramAcc.getHp() == 0) {
      if (unknown418.size() != unknown418.capacity()) {
        unknown418.push_back(*it);
      }
    } else if (!quest.empty() && GfQuestTarget::getIconType(*it, quest) != 0) {
      if (unknown418.size() != unknown418.capacity()) {
        unknown418.push_back(*it);
      }
    }
  }
  m_forceBossBattleBgm = true;
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
  fw::ColiObject *coli = collider->unknown18[0];
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
  if (unknown18 >= FIELD_BLADE_CHANGE_WAIT_TIME && GfGameManager::isEnableOpenMainMenu()) {
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
    unknown228[partyId] = 0;
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
  if (unknown240[0].unknown08 < 3) {
    return false;
  }
  if (GfLayerPause::isLayerPause(OBJ_LAYER_PLAYER)) {
    return false;
  }
  return unknown240[0].unknown04 != MOVER_STATE_SWIM;
}

void GfGameScene::setForceBossBattleBgm(bool isForce) { m_forceBossBattleBgm = isForce; }

bool GfGameScene::isForceBossBattleBgm() const { return m_forceBossBattleBgm; }

void GfGameScene::setForceEventBgm(f32 time) { m_forceEventBgm = time; }

bool GfGameScene::isForceEventBgm() const { return m_forceEventBgm > 0.0f; }

bool GfGameScene::isPlayerTalkForce() { return unknown138 || unknown139; }

void GfGameScene::setPlayerTalkForce(bool isForce) { unknown138 = isForce; }

void GfGameScene::setGimmickCameraPause(bool isPause) { unknown139 = isPause; }

void GfGameScene::refreshGimmickFlag() {}

void GfGameScene::setAutoBattle(bool isAuto) { m_autoBattle = isAuto; }

bool GfGameScene::isAutoBattle() { return m_autoBattle; }

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
    if ((unknown140 & bit) == 0) {
      unknown140 |= bit;
      return pause;
    }
  }
  return -1;
}

void GfGameScene::destroyPlayerPause(u32 pause) { unknown140 &= ~(1 << pause); }

bool GfGameScene::isPlayerPause() const {
  if (GfGameManager::getState() == GF_STATE_CONTROL) {
    return unknown140 != 0;
  }
  return true;
}

bool GfGameScene::isPlayerPauseForBattle() const {
  if (GfGameManager::getState() == GF_STATE_CONTROL || GfGameManager::getState() == GF_STATE_RESET_BLADE) {
    return unknown140 != 0;
  }
  return true;
}

void GfGameScene::setDeadType(GfPlayerDead dead) { m_deadType = dead; }

u32 GfGameScene::getDeadType() { return m_deadType; }

void GfGameScene::setDamageCharacter(GF_OBJ_HANDLE *handle) {
  for (DamageCharacter &character : unknown20) {
    if (character.unknown00 == handle) {
      character.unknown08 = 0.0f;
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
    unknown70.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAppendWire(wire, handle));
  }
}

void GfGameScene::destroyDriverAppendModelControl(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GfAppendWire *, 8>::iterator it =
      mm::mtl::find_if(unknown70.begin(), unknown70.end(), [handle](GfAppendWire *wire) { return wire->unknown08 == handle || wire->unknown00 == handle; });
  if (it != unknown70.end()) {
    delete *it;
    unknown70.erase(it);
  }
}

void GfGameScene::enterExtraControlForHanaJS(GF_OBJ_HANDLE *handle) {
  if (unknown3b0.size() == 8) {
    return;
  }
  GfObjAcc obj(handle);
  if (obj.getBdatId() == BLADE_HANA_JS) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
    if (setup != nullptr && !setup->isEvent()) {
      unknown3b0.push_back(handle);
    }
  }
}

void GfGameScene::leaveExtraControlForHanaJS(GF_OBJ_HANDLE *handle) {
  GF_OBJ_HANDLE **it = mm::mtl::find(unknown3b0.begin(), unknown3b0.end(), handle);
  if (it != unknown3b0.end()) {
    unknown3b0.erase(it);
  }
}

GfAppendWire *GfGameScene::getAppendControl(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GfAppendWire *, 8>::iterator it =
      mm::mtl::find_if(unknown70.begin(), unknown70.end(), [handle](GfAppendWire *wire) { return wire->unknown08 == handle || wire->unknown00 == handle; });
  if (it == unknown70.end()) {
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
    if (unknown2b0[i].unknown10) {
      return unknown2b0[i + 1].unknown00;
    }
  }
  return GfGameManager::getControlMoverPosition();
}

bool GfGameScene::isDisableJumpForRide() const {
  if (unknown668) {
    GfObjAcc obj(GfGameParty::getHandleDriver(0));
    if (!isBattle() || obj.isBattle() || unknown240[0].unknown04 == MOVER_STATE_SWIM) {
      return unknown668;
    }
  }
  return false;
}

bool GfGameScene::isBattle() const {
  if (get() != nullptr) {
    return (get()->unknown144 & FLAG_BATTLE) != 0;
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
  unknown130 = false;
  if (info.unknown04 != info.unknown08 && info.unknown04 != 0) {
    m_forceBossBattleBgm = false;
    unknown132 = false;
    m_forceEventBgm = 0.0f;
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
  for (SavePos &savePosition : unknown2b0) {
    savePosition.unknown00 = mm::Vec3::zero;
    savePosition.unknown10 = false;
  }
}

void GfGameScene::applyMapjumpForEnd(const MapjumpCallbackInfo &info) {
  SCOM_ZONE::create(info.unknown04);
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(unknown658, CATEGORY_GAME_WEATHER, 1.0f, 1.0f);
    sound->setCategoryVolume(unknown658, CATEGORY_GAME_BGM, 1.0f, 1.0f);
    sound->setCategoryVolume(unknown658, CATEGORY_EVENT_BGM, 1.0f, 1.0f);
    sound->setCategoryVolume(unknown658, CATEGORY_FIELD_SE, 1.0f, 1.0f);
    sound->setCategoryVolume(unknown658, CATEGORY_GIMMICK_SE, 1.0f, 1.0f);
    sound->setCategoryVolume(unknown658, CATEGORY_GAME_ENV, 1.0f, 1.0f);
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
    dataBlade->unknown82c = GfBdatChrBl::get()->getChrBlDefWeapon(BLADE_SUZAKU);
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
    unknown50 = true;
  }
  unknown1a9 = true;
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
    if (setup != nullptr && setup->unknown14 != -1) {
      unknown228[setup->unknown14] = 0;
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
  unknown120.battleStart();
  if (m_forceBossBattleBgm) {
    if (GfGameManager::isExistBossEnemy() || GfFieldBgm::get()->isBossBgmCopied()) {
      unknown132 = true;
    } else {
      m_forceBossBattleBgm = false;
    }
  }
  m_forceEventBgm = 0.0f;
}

void GfGameScene::gevBattleEnd() {
  if (!GfGameManager::isPlayerDeadSequence()) {
    for (u32 partyId = 0; partyId < 3; partyId++) {
      DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
      if (paramAcc.isValid() && paramAcc.getHp() == 0) {
        GfObj *obj = GfObjUtil::getObj(paramAcc.unknown10);
        if (obj != nullptr) {
          MsgObjectHealHp message(1, HEAL_TYPE_NORMAL);
          obj->sendMessage(obj, message);
        }
      }
    }
  }
  unknown120.battleEnd();
  if (unknown648) {
    m_forceBossBattleBgm = true;
  } else {
    m_forceBossBattleBgm = false;
    unknown132 = false;
  }
}

void GfGameScene::gevMercenariesMissionFlag(u32 mission, u32 flag, u32) {
  if (GfGameUtilNanakoori::checkCompleteMission(mission, flag)) {
    unknown1a9 = true;
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
  m_maskMainMenu = true;
  for (SavePos &savePosition : unknown2b0) {
    savePosition.unknown00 = mm::Vec3::zero;
    savePosition.unknown10 = false;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(unknown650, CATEGORY_CHARACTER_SE, 0.0f, 0.5f);
    sound->setCategoryVolume(unknown650, CATEGORY_NO_SLOW_SE, 0.0f, 0.5f);
  }
}

void GfGameScene::playEventSequenceEnd(u32 event) {
  if (event == EVENT_LAST_KIZUNA_TALK) {
    GfGameUtil::addTrusuPointByLastKizunaTalk();
  }
  m_playEvent = false;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(unknown650, CATEGORY_CHARACTER_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(unknown650, CATEGORY_NO_SLOW_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(unknown660, CATEGORY_GAME_ENV, 1.0f, 0.2f);
    sound->setCategoryVolume(unknown660, CATEGORY_GIMMICK_SE, 1.0f, 0.2f);
    sound->setCategoryVolume(unknown660, CATEGORY_GAME_WEATHER, 1.0f, 0.2f);
    sound->setCategoryVolume(unknown660, CATEGORY_GAME_BGM, 1.0f, 0.2f);
  }
  if (GfManager::isExecModeThater()) {
    return;
  }
  GfGameUtil::setWatchedEvent(event);
}

void GfGameScene::playEventPlayStart(u32) {
  if (!unknown418.empty()) {
    for (GF_OBJ_HANDLE *obj : unknown418) {
      GfObjUtil::destroy(obj);
    }
  }
  unknown418.clear();
  m_playEvent = true;
}

void GfGameScene::playEventPlayEnd(u32 event) {
  m_playEvent = false;
  if (event != EVENT_KEEP_VOLUME) {
    GfSound *sound = GfSound::get();
    if (sound != nullptr) {
      sound->setCategoryVolume(unknown650, CATEGORY_CHARACTER_SE, 0.0f, 0.0f);
      sound->setCategoryVolume(unknown650, CATEGORY_NO_SLOW_SE, 0.0f, 0.0f);
      for (u16 mapjumpEvent : MAPJUMP_EVENTS) {
        if (mapjumpEvent == event) {
          sound->setCategoryVolume(unknown658, CATEGORY_GAME_WEATHER, 0.0f, 0.0f);
          sound->setCategoryVolume(unknown658, CATEGORY_GAME_BGM, 0.0f, 0.0f);
          sound->setCategoryVolume(unknown658, CATEGORY_EVENT_BGM, 0.0f, 0.0f);
          sound->setCategoryVolume(unknown658, CATEGORY_FIELD_SE, 0.0f, 0.0f);
          sound->setCategoryVolume(unknown658, CATEGORY_GIMMICK_SE, 0.0f, 0.0f);
          sound->setCategoryVolume(unknown658, CATEGORY_GAME_ENV, 0.0f, 0.0f);
        }
      }
      if (event == EVENT_ENV_SILENT) {
        sound->setCategoryVolume(unknown660, CATEGORY_GAME_ENV, 0.0f, 0.0f);
        sound->setCategoryVolume(unknown660, CATEGORY_GIMMICK_SE, 0.0f, 0.0f);
        sound->setCategoryVolume(unknown660, CATEGORY_GAME_WEATHER, 0.0f, 0.0f);
        sound->setCategoryVolume(unknown660, CATEGORY_GAME_BGM, 0.0f, 0.0f);
      }
    }
  }
  GfQuestManager::requestOrderQuestForce();
}

void GfGameScene::playEventStartFrame(u32) {
  if (unknown648) {
    unknown648 = false;
    m_forceBossBattleBgm = false;
    unknown132 = false;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setCategoryVolume(unknown650, CATEGORY_CHARACTER_SE, 1.0f, 0.0f);
    sound->setCategoryVolume(unknown650, CATEGORY_NO_SLOW_SE, 1.0f, 0.0f);
  }
}

void GfGameScene::updatePlayerState() {
  for (PartyState &state : unknown240) {
    state.unknown04 = MOVER_STATE_NONE;
    state.unknown0d = false;
    GfObjProperty *property = GfObjUtil::getProperty(GfGameParty::getHandleMover(state.unknown00));
    if (property != nullptr && property->unknown18 != nullptr) {
      GfObjPropertyMove *move = property->unknown18;
      state.unknown04 = MOVER_STATE_FIELD;
      switch (move->unknown00) {
      case PROPERTY_MOVE_SWIM:
        state.unknown04 = MOVER_STATE_SWIM;
        break;
      case PROPERTY_MOVE_CLIMB:
        state.unknown04 = MOVER_STATE_CLIMB;
        break;
      case PROPERTY_MOVE_ACTION:
        state.unknown04 = MOVER_STATE_BUSY;
        break;
      }
      if (move->unknown80) {
        state.unknown04 = MOVER_STATE_JUMP;
      }
      if (move->unknownc0 != INVALID_HANDLE) {
        state.unknown04 = MOVER_STATE_BUSY;
      }
      if (move->unknownc8 != 0.0f) {
        state.unknown0d = true;
      }
    }
    if (state.unknown04 == MOVER_STATE_FIELD && !GfGameManager::isControlFree()) {
      state.unknown04 = MOVER_STATE_BUSY;
    }
    state.unknown0c = _gfgsc::isPartyMemberGetFieldDamage(state.unknown00);
    GfObjAcc obj(GfGameParty::getHandleMover(state.unknown00));
    state.unknown08 = obj.isBattle() ? 0 : state.unknown08 + 1;
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
  if ((GfDataBlade::isHikariCurrent() && GfDataDriver::getBlade(DRIVER_REX, -1) == BLADE_HOMURA) || (!GfDataBlade::isHikariCurrent() && GfDataDriver::getBlade(DRIVER_REX, -1) == BLADE_HIKARI)) {
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

void GfGameScene::qevCompleteQuest(const QuestCompleteParam &) { unknown1a9 = true; }

void GfGameScene::updateAppendModel(const fw::UpdateInfo &info) {
  for (auto it = unknown70.begin(); it != unknown70.end(); ++it) {
    (*it)->update(info);
  }
  for (auto it = unknown70.begin(); it != unknown70.end();) {
    if (!GfObjUtil::isValid((*it)->unknown08)) {
      delete *it;
      it = unknown70.erase(it);
    } else {
      ++it;
    }
  }
}

void GfGameScene::postUpdate(const fw::UpdateInfo &info) { updateAppendModel(info); }

OwnerBonus &GfGameScene::getOwnerBonus() const { return m_ownerBonus; }

void GfGameScene::setCameraAvtivateOneTime() { unknown144 |= FLAG_CAMERA_ACTIVATE_ONE_TIME; }

bool GfGameScene::isPlayerCameraPause() {
  if (unknown144 & FLAG_CAMERA_PAUSE) {
    return true;
  }
  if (unknown144 & FLAG_CAMERA_ACTIVATE_ONE_TIME) {
    unknown144 &= ~FLAG_CAMERA_ACTIVATE_ONE_TIME;
    return false;
  }
  return GfPause::isPause(PAUSE_BIT_SYSTEM);
}

void GfGameScene::setPlayerCameraPause(bool isPause) {
  if (isPause) {
    unknown144 |= FLAG_CAMERA_PAUSE;
  } else {
    unknown144 &= ~FLAG_CAMERA_PAUSE;
  }
}

void GfGameScene::enterBattle(bool isBattle) {
  if (isBattle != ((unknown144 & FLAG_BATTLE) != 0)) {
    if (!isBattle) {
      unknown144 &= ~FLAG_BATTLE;
      GfEvent::callBattleEnd();
      unknown1cb = false;
      return;
    }
    unknown144 |= FLAG_BATTLE;
    GfEvent::callBattleStart();
  }
  unknown1cb = false;
  if (!isBattle) {
    return;
  }
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX);
  if (partyId == -1) {
    return;
  }
  DataParamAcc paramAcc(GfGameParty::getHandleBlade(partyId, -1));
  if (paramAcc.isValid() && paramAcc.getBdatId() == BLADE_HOMURI) {
    unknown1cb = true;
  }
}

void GfGameScene::setForceBattleTime(f32 time) {
  if (get() != nullptr) {
    get()->unknown12c = time;
  }
}

void GfGameScene::setForceStopBattle(bool isStop) {
  if (get() != nullptr) {
    get()->unknown130 = isStop;
  }
}

void GfGameScene::addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage) {
  unknown120.addDamage(handle, damage);
  setDamageCharacter(handle);
}

void GfGameScene::addMoneyLog() { unknown118 = MONEY_LOG_TIME; }

QuestID GfGameScene::getQuestIdForTaskLog() const { return m_questIdForTaskLog; }

void GfGameScene::updateOwnerBonus(const fw::UpdateInfo &) {
  if (unknown50) {
    unknown50 = false;
    GfGameUtil::getOwnerBonus(m_ownerBonus);
  }
}

void GfGameScene::updatePartyMover(const fw::UpdateInfo &) {
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 3> movers;
  movers[0] = GfGameParty::getHandleMover(0);
  movers[1] = GfGameParty::getHandleMover(1);
  movers[2] = GfGameParty::getHandleMover(2);
  for (GF_OBJ_HANDLE *mover : movers) {
    if (mover != INVALID_HANDLE && unknown3f8[0] != mover && unknown3f8[1] != mover && unknown3f8[2] != mover) {
      GfEvent::callPartyMover(mover, true);
    }
  }
  for (GF_OBJ_HANDLE *mover : unknown3f8) {
    if (mover != INVALID_HANDLE && mover != movers[0] && mover != movers[1] && mover != movers[2]) {
      GfEvent::callPartyMover(mover, false);
    }
  }
  unknown3f8 = movers;
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
  for (GF_OBJ_HANDLE *handle : unknown3b0) {
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
    if (obj.isBattle() && unknown228[partyId] < 3) {
      unknown228[partyId]++;
      GfGameParty::setupBattleStart(partyId);
    }
  }
}

void GfGameScene::updateMaskMainMenu(const fw::UpdateInfo &) {
  if (!GfGameManager::isEvent(false) && GfGameManager::isFadeClear()) {
    m_maskMainMenu = false;
  }
}

void GfGameScene::updatePlayerStopFlag(const fw::UpdateInfo &) {
  if (unknown1d8.empty()) {
    return;
  }
  u8 request = unknown1d8.pop_front();
  if (request != 0) {
    unknown1b8.set(request & 0x7f, (request & 0x80) != 0);
  }
}

void GfGameScene::updateStopEnemyAttackForEvent(const fw::UpdateInfo &) {
  if (unknown620 > 0) {
    unknown620--;
  }
  if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
    unknown620 = STOP_ENEMY_ATTACK_FRAME;
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
  if (unknown1cc != -1 && !GfReqManager::isValid(unknown1cc)) {
    unknown1cc = -1;
  }
  if (unknown1cb || GfGameManager::isMapjump()) {
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
        unknown1cb = true;
        unknown1cc = GfReqCommand::reqChangeBladeWithSetId(GfGameParty::getPartyId(OBJECT_TYPE_DRIVER, DRIVER_REX), HOMURI_BLADE_SET, false);
      }
      return;
    }
  }
}

void GfGameScene::updateHikariLv4Room(const fw::UpdateInfo &) {
  unknown1ca = false;
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
    mm::Vec3 position = obj.getWorldTransform().unknown00 + mm::Vec3(0.0f, 1.0f, 0.0f);
    if (!util::getUpperHitCollision(hit, position, HIKARI_ROOM_HEIGHT)) {
      unknown1ca = true;
    }
  }
}

void GfGameScene::updateStartGame(const fw::UpdateInfo &) {
  if (unknown1c9 && GfGameManager::isControlFree() && !GfGameManager::isFadeout() && unknown1c4 == GEV_PLAYER_CONTROL_FREE) {
    unknown1c9 = false;
  }
}

void GfGameScene::updateAfterEventCount(const fw::UpdateInfo &) {
  if (!GfGameManager::isPlaySequenceClear()) {
    unknown624 = 0;
  } else if (unknown624 < AFTER_EVENT_COUNT_MAX) {
    unknown624++;
  }
}

void GfGameScene::updateControlFreeEvent(const fw::UpdateInfo &) {
  if (GfPlayComGmkTutorialSeq::s_activate <= 0 && (!GfGameManager::isBladeChange() || GfSequentialPlay::isInnerState(GF_STATE_SALVAGE)) && !GfGameManager::isControlFree()) {
    if (unknown1c0 > 0 && --unknown1c0 == 0 && unknown1c4 != GEV_PLAYER_CONTROL_LOCK) {
      unknown1c4 = GEV_PLAYER_CONTROL_LOCK;
      GfEvent::callPlayerControl(GEV_PLAYER_CONTROL_LOCK);
    }
  } else if (!GfManager::isExecModeAdvertize()) {
    if (unknown1c0 < CONTROL_FREE_FRAME && ++unknown1c0 == CONTROL_FREE_FRAME && unknown1c4 != GEV_PLAYER_CONTROL_FREE) {
      unknown1c4 = GEV_PLAYER_CONTROL_FREE;
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
  if (mm::mtl::find(GfPlayComResetBlade::s_execFlag.begin(), GfPlayComResetBlade::s_execFlag.end(), static_cast<u8>(partyId)) != GfPlayComResetBlade::s_execFlag.end()) {
    return true;
  }
  return !isEnableRideCondition(partyId);
}

void GfGameScene::updatePartyInfo(const fw::UpdateInfo &) {
  if (GfGameManager::isBattle()) {
    for (u32 partyId = 0; partyId < 3; partyId++) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
      GfGameParty::getHandleBlade(partyId, -1);
      unknown1ac[partyId] = GfGameObj::isValidGameObj(driver, true, nullptr);
    }
    return;
  }
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(partyId, -1);
    if (!GfGameObj::isValidGameObj(driver, true, nullptr)) {
      unknown1ac[partyId] = 0;
      continue;
    }
    if (unknown0c[partyId] != -1) {
      unknown1ac[partyId] = 1;
      continue;
    }
    GfObjAcc driverObj(driver);
    GfObjAcc bladeObj(blade);
    if (driverObj.isBattle() || bladeObj.isBattle()) {
      unknown1ac[partyId] = 1;
      continue;
    }
    DataParamAcc paramAcc(driver);
    int bladeSet = GfSelectBlade::getStartBattleSetId(partyId);
    if (bladeSet >= 0 && bladeSet != paramAcc.getBladeSet(false)) {
      unknown1ac[partyId] = 1;
    } else if (unknown1ac[partyId] == 1 && !isPartyBusy(partyId)) {
      unknown1ac[partyId] = 0;
      GfEvent::callPartyReturnFieldState(partyId);
    }
  }
}

void GfGameScene::updateBladeChangeForBattle(const fw::UpdateInfo &) {
  for (u32 &request : unknown0c) {
    if (request != -1 && !GfReqManager::isValid(request)) {
      request = -1;
    }
  }
  checkFieldBladeChangeForRide();
  checkFieldBladeChange();
}

void GfGameScene::updateBladeChangeInField(const fw::UpdateInfo &info) {
  f32 time = unknown18;
  unknown18 = 0.0f;
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
  unknown18 = time + info.unknown04;
}

void GfGameScene::updateColiPrio(const fw::UpdateInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(partyId));
    unknown001(driverAcc, driverAcc.getHp() == 0, unknown240[partyId].unknown04 == MOVER_STATE_SWIM);
    DataParamAcc bladeAcc(GfGameParty::getHandleBlade(partyId, -1));
    unknown001(bladeAcc, driverAcc.getHp() == 0, unknown240[partyId].unknown04 == MOVER_STATE_SWIM);
  }
}

void GfGameScene::updateAutoHeal(const fw::UpdateInfo &info) {
  if (!GfGameManager::isControlFree() || GfGameManager::isBattle() || _gfgsc::isPartyMemberGetFieldDamage(0)) {
    for (DamageCharacter &character : unknown20) {
      if (character.unknown08 != 0.0f) {
        character.unknown08 = 0.0f;
      }
    }
    return;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_PLAYER_DEAD)) {
    return;
  }
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DamageCharacter &character = unknown20[partyId];
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
    if (driver == INVALID_HANDLE) {
      if (character.unknown00 != INVALID_HANDLE) {
        character.unknown00 = INVALID_HANDLE;
      }
      continue;
    }
    if (character.unknown00 != driver) {
      character.unknown00 = driver;
    }
    if (unknown240[partyId].unknown0c) {
      character.unknown08 = 0.0f;
    }
    DataParamAcc paramAcc(driver);
    u32 hp = paramAcc.getHp();
    u32 maxHp = paramAcc.getHpMax(false);
    if (hp != maxHp) {
      character.unknown08 += info.unknown04;
      if (!(character.unknown08 < AUTO_HEAL_INTERVAL)) {
        character.unknown08 = 0.0f;
        GfObj *obj = GfObjUtil::getObj(driver);
        if (obj != nullptr) {
          u32 heal = floorf(maxHp * AUTO_HEAL_RATE * 0.01f + 0.000001f);
          MsgObjectHealHp message(hp + heal > maxHp ? maxHp - hp : heal, HEAL_TYPE_NORMAL);
          obj->sendMessage(obj, message);
        }
      }
    } else if (character.unknown08 > 0.0f) {
      character.unknown08 = 0.0f;
    }
  }
}

void GfGameScene::updateMaxHp(const fw::UpdateInfo &) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleDriver(partyId));
    if (obj == nullptr) {
      continue;
    }
    DataParamAcc paramAcc(obj->unknownf8);
    paramAcc.getHp();
    paramAcc.getHpMax(false);
    if (paramAcc.getHp() > paramAcc.getHpMax(false)) {
      MsgObjectHealHp message(0, HEAL_TYPE_FULL);
      obj->sendMessage(obj, message);
    }
  }
}

void GfGameScene::updateLog(const fw::UpdateInfo &info) {
  if (unknown118 > 0.0f) {
    unknown118 -= info.unknown04;
    if (unknown118 <= 0.0f) {
      unknown118 = 0.0f;
    }
  }
}

void GfGameScene::updateQuestTaskLog(const fw::UpdateInfo &) {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  if (m_questIdForTaskLog.empty()) {
    if (!quest.empty()) {
      m_questIdForTaskLog.unknown00 = quest.unknown00;
      m_questIdForTaskLog.unknown02 = quest.unknown02;
    }
  } else if (!(m_questIdForTaskLog == quest)) {
    if (GfGameManager::isFadeout() || (GfGameManager::isControlFree() && !GfGameManager::isTalking() && !GfGameManager::isEvent(false)) || GfGameManager::isFullScreenMenu()) {
      m_questIdForTaskLog.unknown00 = quest.unknown00;
      m_questIdForTaskLog.unknown02 = quest.unknown02;
    }
  }
}

void GfGameScene::updateForceBattle(const fw::UpdateInfo &info) {
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM) && unknown12c > 0.0f) {
    unknown12c -= info.unknown04;
    if (unknown12c < 0.0f) {
      unknown12c = 0.0f;
    }
  }
}

void GfGameScene::updateMoveAchievement(const fw::UpdateInfo &) {
  GfObjAcc obj(GfGameManager::getControlMover());
  if (!obj.isValidTransform()) {
    return;
  }
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM) && GfGameManager::isControlFree()) {
    const mm::Vec3 &position = obj.getWorldTransform().unknown00;
    f32 x = position.x - unknown150.x;
    f32 y = position.y - unknown150.y;
    f32 z = position.z - unknown150.z;
    f32 distance = sqrtf(x * x + y * y + z * z);
    if (!(distance < MOVE_DISTANCE_MIN)) {
      for (MoveAchievement &achievement : unknown160) {
        if (!achievement.unknown08()) {
          continue;
        }
        f32 moveDistance = distance < MOVE_DISTANCE_MAX ? distance + GfDataUtil::getMoveDistance(achievement.unknown00) : GfDataUtil::getMoveDistance(achievement.unknown00);
        u32 meter = moveDistance;
        if (meter != 0) {
          moveDistance -= meter;
          SCOM_ACHIEV_INC::addTotalCount(achievement.unknown04, 1);
          SCOM_ACHIEV_INC::create(achievement.unknown04, 1, 0);
          SCOM_ACHIEV_INC::createCurrentBlade(GfGameManager::getPartyLeaderDriver(), achievement.unknown04 + 1, 1);
        }
        GfDataUtil::setMoveDistance(achievement.unknown00, moveDistance);
      }
    }
  }
  unknown150 = obj.getWorldTransform().unknown00;
}

void GfGameScene::updateEventBgm(const fw::UpdateInfo &info) {
  if (m_forceEventBgm <= 0.0f) {
    return;
  }
  if (GfGameManager::isBattle()) {
    m_forceEventBgm = 0.0f;
  }
  if (GfGameManager::isControlFree()) {
    m_forceEventBgm -= info.unknown04;
    if (m_forceEventBgm < 0.0f) {
      m_forceEventBgm = 0.0f;
    }
  }
}

void GfGameScene::updateAutoFlag(const fw::UpdateInfo &) {
  if (unknown1a9) {
    unknown1a9 = false;
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
    unknown2b0[i].unknown00 = unknown2b0[i - 1].unknown00;
    unknown2b0[i].unknown10 = unknown2b0[i - 1].unknown10;
  }
  bool isEnable;
  if (!GfGameManager::isEnableOpenMainMenu() || GfPause::isPause(PAUSE_BIT_SYSTEM)) {
    isEnable = false;
  } else if (GfSequentialPlay::isPlay()) {
    isEnable = false;
  } else {
    isEnable = !_gfgsc::isPartyMemberGetFieldDamage(0);
  }
  unknown2b0[0].unknown00 = GfGameManager::getControlMoverPosition();
  unknown2b0[0].unknown10 = isEnable;
}

void GfGameScene::updateRideRequest(const fw::UpdateInfo &) {
  if (!unknown669) {
    return;
  }
  if (!GfGameRide::testRideOn()) {
    GfObjAcc obj(GfGameParty::getHandleDriver(0));
    if (GfDataParty::isNiaByakko(0) && !obj.isBattle()) {
      if (isEnableRideCondition(0)) {
        unknown669 = false;
        GfGameRide::setRideOn(true);
      }
      return;
    }
  }
  unknown669 = false;
}

void GfGameScene::updateEnemySaveHp(const fw::UpdateInfo &) {
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *enemies = GfGameObj::getList(OBJECT_TYPE_ENEMY);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = enemies->begin(); it != enemies->end(); ++it) {
    GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(*it);
    if (setup != nullptr && setup->unknownb4 != 0) {
      GfObjAcc obj(*it);
      if (obj.isBattle()) {
        MsgObjectSetHp message(setup->unknownb4);
        obj.getObj()->sendMessage(obj.getObj(), message);
        setup->unknownb4 = 0;
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
    unknown669 = false;
    if (!GfGameRide::testRideOn()) {
      unknown669 = true;
    }
  }
}

} // namespace gf
