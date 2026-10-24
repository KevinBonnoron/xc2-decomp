#include "gf/gf_manager.h"

#include "battle/battle_manager.h"
#include "framework/debug/debug_draw.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "gf/gf_mem_manager.h"
#include "gf/gf_pause.h"
#include "gf/gf_static_res.h"
#include "gf/map/gf_map_manager.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/movie/gf_movie_manager.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/param/gf_param.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/script/gf_script_manager.h"
#include "gf/sound/gf_sound.h"
#include "ml/rand.h"
#include "ml/time_count.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

enum EXEC_FLAG {
  EXEC_FLAG_KILL_PARTY_CREATE = 1 << 0,
  EXEC_FLAG_TOOL = 1 << 1,
  EXEC_FLAG_SCENARIO_GAME = 1 << 2,
  EXEC_FLAG_ADVERTIZE = 1 << 3,
};

const u16 EXEC_FLAGS[] = {
    0,
    EXEC_FLAG_SCENARIO_GAME,
    EXEC_FLAG_KILL_PARTY_CREATE | EXEC_FLAG_ADVERTIZE,
    EXEC_FLAG_ADVERTIZE,
    EXEC_FLAG_KILL_PARTY_CREATE | EXEC_FLAG_TOOL,
};

constexpr u32 FINALIZE_WAIT_FRAME = 30;

} // namespace

GfManager *GfManager::s_pThis;

namespace {

ml::TimeCount s_loadGameTimer;

} // namespace

GfManager::GfManager(const GfSetupParam &param) : initialized(false), destroyNow(false), execFlags(0), gameStart(GAME_START_NONE), frameCount(0), loadGameTime(-1.0f), existSaveData(false) {
  s_pThis = this;
  setupParam = param;
  exec = param.exec;
  execFlags = EXEC_FLAGS[exec];
}

void GfManager::setExec(EXEC_STATE exec) {
  GfManager *manager = s_pThis;
  if (manager != nullptr) {
    manager->exec = exec;
    manager->execFlags = EXEC_FLAGS[exec];
    if (manager->initialized) {
      GfEvent::callExecState(exec);
    }
  }
}

GfManager::~GfManager() { s_pThis = nullptr; }

void GfManager::build(const GfSetupParam &param) {
  GfStaticRes::initialize();
  GfMemManager::buildCoreMemory(param);
  // __LINE__ must be 100 as in the original file: it is an argument of the allocation.
#line 100
  GfManager *manager = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfManager(param);
  manager->initialize();
  setupDeafult();
}

void GfManager::initialize() {
  fw::Framework::addPauseCallback(this);
  GfEvent::build(setupParam);
  createGfParameter();
  bindPadResources();
  bindGFSoundSource();
  GfPause::build(setupParam);
  GfInfo::build(setupParam);
  GfMemManager::build(setupParam);
  GfDataManager::build(setupParam);
  GfScriptManager::build(setupParam);
  GfReqManager::build(setupParam);
  GfAssetManager::build(setupParam);
  GfObjManager::build(setupParam);
  GfSound::build(setupParam);
  GfMapManager::build(setupParam);
  GfGameManager::build(setupParam);
  GfFieldManager::build(setupParam);
  GfMenuManager::build(setupParam);
  GfGameManager::setState(GF_STATE_CONTROL, false);
  GfMovieManager::build(setupParam);
  GfEvent::addEventCallback(this);
  while (!GfMenuManager::isInitialized()) {
    GfSleep(1);
  }
  btl::BattleManager::build(setupParam);
  initialized = true;
}

void GfManager::setupDeafult() {
  s_pThis->gameStart = GAME_START_NONE;
  GfDataManager::clear();
  GfAssetManager::clear();
  GfFieldManager::clear();
  GfGameManager::clear();
  GfDataManager::setupGame(nullptr, nullptr, nullptr);
  GfGameManager::setupGame();
  GfFieldManager::setupGame();
}

void GfManager::destroy() {
  GfManager *manager = s_pThis;
  manager->finalize();
  delete manager;
  GfMemManager::destroyCoreMemory();
  GfStaticRes::finalize();
}

void GfManager::finalize() {
  GfGameManager::leaveGameForDebug();
  GfSleep(FINALIZE_WAIT_FRAME);
  GfGameManager::destroyBattleEnemy();
  while (!GfGameManager::isField()) {
    GfSleep(1);
  }
  destroyNow = true;
  GfReqCommand::reqDestroyGf();
  while (GfReqManager::isExistCommand(nullptr)) {
    GfSleep(1);
  }
  GfEvent::removeEventCallback(this);
  btl::BattleManager::destroy();
  GfMovieManager::destroy();
  GfGameManager::setState(GF_STATE_DESTROY, false);
  GfMenuManager::destroy();
  GfFieldManager::destroy();
  GfGameManager::destroy();
  GfMapManager::destroy();
  GfSound::destroy();
  GfObjManager::destroy();
  GfAssetManager::destroy();
  GfReqManager::destroy();
  GfScriptManager::destroy();
  GfDataManager::destroy();
  GfMemManager::destroy();
  GfInfo::destroy();
  GfPause::destroy();
  unrbindGFSoundSource();
  unbindPadResource();
  destroyGfParameter();
  GfEvent::destroy();
  fw::Framework::removePauseCallback(this);
  initialized = false;
}

bool GfManager::isInitialized() {
  if (s_pThis != nullptr) {
    return s_pThis->initialized;
  }
  return false;
}

bool GfManager::isDestroyed() {
  if (s_pThis != nullptr) {
    return s_pThis->initialized;
  }
  return false;
}

bool GfManager::isDestroyNow() {
  if (s_pThis != nullptr) {
    return s_pThis->destroyNow;
  }
  return false;
}

GfSetupParam &GfManager::getSetupParam() { return s_pThis->setupParam; }

void GfManager::updatePauseCallback() {
  if (s_pThis != nullptr) {
    GfInfo::apply();
  }
}

u32 GfManager::getFrameCount() {
  if (s_pThis != nullptr) {
    return s_pThis->frameCount;
  }
  return 0;
}

bool GfManager::isExecKillPartyCreate() {
  if (s_pThis != nullptr) {
    return s_pThis->execFlags & EXEC_FLAG_KILL_PARTY_CREATE;
  }
  return false;
}

bool GfManager::isExecModeScenarioGame() {
  if (s_pThis != nullptr) {
    return s_pThis->execFlags & EXEC_FLAG_SCENARIO_GAME;
  }
  return false;
}

bool GfManager::isExecModeAdvertize() {
  if (s_pThis != nullptr) {
    return s_pThis->execFlags & EXEC_FLAG_ADVERTIZE;
  }
  return false;
}

bool GfManager::isExecModeTool() {
  if (s_pThis != nullptr) {
    return s_pThis->exec == EXEC_STATE_TOOL;
  }
  return false;
}

bool GfManager::isExecModeDebug() {
  if (s_pThis != nullptr) {
    return s_pThis->exec == EXEC_STATE_DEBUG;
  }
  return false;
}

bool GfManager::isExecModeThater() {
  if (s_pThis != nullptr) {
    return s_pThis->exec == EXEC_STATE_THEATER;
  }
  return false;
}

void GfManager::setupNewGame() {
  s_pThis->gameStart = GAME_START_NEW;
  GfGameParty::setupNewGameParty();
}

void GfManager::setupPowerNewGame(const SDataSystem &, const SDataGame &dataGame, const SDataOption &) {
  GfGameUtil::setupNewGameParam(dataGame);
  GfMenuManager::setupGame();
  setupNewGame();
}

void GfManager::setupContinueGame(const SDataSystem &dataSystem, const SDataGame &dataGame, const SDataOption &dataOption) {
  s_pThis->gameStart = GAME_START_CONTINUE;
  GfDataManager::clear();
  GfAssetManager::clear();
  GfFieldManager::clear();
  GfGameManager::clear();
  GfDataManager::setupGame(&dataSystem, &dataGame, &dataOption);
  GfGameManager::setupGame();
  GfFieldManager::setupGame();
  s_pThis->loadGameTime = 0.0f;
  s_loadGameTimer.reset();
}

void GfManager::setupEventTheater() { setupDeafult(); }

void GfManager::setupReturnTitle() { setupDeafult(); }

void GfManager::setupOptionData(const SDataOption &dataOption) {
  GfDataManager::setupOptionData(dataOption);
  if (GfSound::get() != nullptr) {
    GfSound::get()->setupGame();
  }
}

bool GfManager::isContinueGame() {
  if (s_pThis != nullptr) {
    return s_pThis->gameStart == GAME_START_CONTINUE;
  }
  return false;
}

bool GfManager::isNewGame() {
  if (s_pThis != nullptr) {
    return s_pThis->gameStart == GAME_START_NEW;
  }
  return false;
}

bool GfManager::isExistSaveData() {
  if (get() != nullptr) {
    return get()->existSaveData;
  }
  return false;
}

void GfManager::setSaveDataCreated() {
  if (get() != nullptr) {
    get()->existSaveData = true;
  }
}

void GfManager::startGame(bool isExistSaveData, bool isClearGameCheck) {
  if (get() != nullptr) {
    get()->existSaveData = isExistSaveData;
  }
  setExec(EXEC_STATE_SCENARIO_GAME);
  if (isContinueGame()) {
    GfMapjumpInfo info;
    info.setupForSaveData(GfDataUtil::getSkipTravelID(), *GfDataParty::getSavePos(0, true), *GfDataParty::getSaveRot(0, true) * mm::DEG_TO_RAD, GfDataUtil::isStartChapterSave());
    GfPlayFactory::createMapjump(info);
    if (GfDataUtil::isStartChapterSave()) {
      GfPlayFactory::createOneEvent(GfDataUtil::getEventChapterSave());
    } else {
      GfDataUtil::getAutoEventAfterLoad();
    }
  } else if (isNewGame()) {
    GfGameEvent::finishNewGameWait();
  }
  if (isClearGameCheck) {
    GfDataUtil::setClearGameCheck();
  }
  GfGameManager::setStartGame();
}

void GfManager::startEventTheater(const mm::mtl::FixedVector<u16, 8> &events) {
  setExec(EXEC_STATE_THEATER);
  u32 mapjumpId = GfDataEvent::getMapjumpID(events[0]);
  GfMapjumpInfo info;
  info.setMapjump(mapjumpId);
  u32 eventType = GfDataEvent::getEventType(events[0]);
  if (eventType == 3 || eventType == 4) {
    info.isNoFadeIn = true;
  }
  GfPlayFactory::createEventMapjump(info);
  for (u32 i = 0; i < events.size(); i++) {
    GfPlayFactory::createTheaterEvent(events[i]);
  }
  ParamReturnTitle param;
  param.unknown00 = false;
  param.unknown01 = false;
  GfPlayFactory::createReturnTitle(param);
}

void GfManager::execToAdvertize() {
  setExec(EXEC_STATE_ADVERTIZE);
  GfGameManager::leaveGameForDebug();
  GfMapjumpInfo info;
  info.setMapjump(-1);
  GfPlayFactory::createMapjump(info);
}

void GfManager::gevGameState(GF_STATE, GF_STATE state) {
  if (loadGameTime == 0.0f) {
    switch (state) {
    case GF_STATE_NONE:
    case GF_STATE_INITIALIZE:
    case GF_STATE_DESTROY:
    case GF_STATE_MAPJUMP:
      break;
    default:
      loadGameTime = s_loadGameTimer.getSecLap();
      GfEvent::callLoadGameTime(loadGameTime);
      break;
    }
  }
}

void GfManager::activate() {
  if (GfFieldManager::get() != nullptr) {
    GfFieldManager::get()->setSuspendGame(false);
  }
}

void GfManager::postUpdate(const fw::UpdateInfo &info) {
  if (s_pThis == nullptr) {
    return;
  }
  GfInfo::apply();
  if (GfMapManager::get() != nullptr) {
    GfMapManager::get()->postUpdate(info);
  }
  if (GfFieldManager::get() != nullptr) {
    GfFieldManager::get()->postUpdate(info);
  }
  if (btl::BattleManager::get() != nullptr) {
    btl::BattleManager::get()->postUpdate(info);
  }
  if (GfGameManager::get() != nullptr) {
    GfGameManager::get()->postUpdate(info);
  }
  if (GfMenuManager::get() != nullptr) {
    GfMenuManager::get()->postUpdate(info);
  }
  if (GfObjManager::get() != nullptr) {
    GfObjManager::get()->postUpdate(info);
  }
  if (GfPause::get() != nullptr) {
    GfPause::update();
  }
}

void GfManager::update(const fw::UpdateInfo &info) {
  if (!isInitialized()) {
    return;
  }
  fw::debug::drawCompareZ(true);
  ml::TimeCount timer;
  timer.start();
  if (s_pThis == nullptr) {
    return;
  }
  GfInfo::apply();
  if (GfReqManager::get() != nullptr) {
    GfReqManager::get()->update(info);
  }
  if (GfAssetManager::get() != nullptr) {
    GfAssetManager::get()->update(info);
  }
  if (GfObjManager::get() != nullptr) {
    GfObjManager::get()->update(info);
  }
  if (GfSound::get() != nullptr) {
    GfSound::get()->update(info);
  }
  if (GfMapManager::get() != nullptr) {
    GfMapManager::get()->update(info);
  }
  if (GfGameManager::get() != nullptr) {
    GfGameManager::get()->update(info);
  }
  if (GfFieldManager::get() != nullptr) {
    GfFieldManager::get()->update(info);
  }
  if (!GfGameManager::isStopBattleSequence()) {
    btl::BattleManager::update(info);
  }
  if (GfMenuManager::get() != nullptr) {
    GfMenuManager::update(info);
  }
  if (GfGameManager::get() != nullptr) {
    GfGameManager::get()->updateParam(info);
  }
  s_pThis->frameCount++;
  s64 clock;
  timer.getClockLap(clock);
  u32 count = clock & 0xf;
  for (u32 i = 0; i < count; i++) {
    ml::mtRandf1();
  }
}

} // namespace gf
