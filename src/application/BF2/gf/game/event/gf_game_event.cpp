#include "gf/game/event/gf_game_event.h"

#include "event/manager.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_evt_model.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/event/gf_evt_bgm.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "ml/ml_mem.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mtl/mem_manager.h"

namespace gf {

namespace {

constexpr int EVENT_CATEGORY_KEEP_PLAYER = 1;
constexpr u32 EVENT_SPEED_LAYER = 1;
constexpr u32 HOMURA_ORIGINAL_EVENT_FIRST = 10062;
constexpr u32 HOMURA_ORIGINAL_EVENT_LAST = 10065;
constexpr size_t EVENT_MEM_SIZE = 0x2300000;

} // namespace

GfGameEvent::GfGameEvent(const GfSetupParam &param)
    : flags(0), initialized(false), afterEventStartID(0), playerOffState(0), layerPause(reinterpret_cast<GF_LP_HANDLE *>(-1)), colorFilter(),
      cloudSea(), tempWeather(), tempWeatherMapId(0), weaType(WEATYPE_DEFAULT), weaTypeWeather(WEATHER_F), lastPlayEventId(0), playEventId(0),
      playBladeId(0), playState(PLAY_STATE_NONE), categoryHandle(INVALID_CATEGORY_HANDLE), csCategoryHandle(INVALID_CATEGORY_HANDLE), isCsMute(false),
      isStopped(false), fadeInWaitSec(0.0f), fadeInSec(0.0f) {
  initialize(param);
}

void GfGameEvent::initialize(const GfSetupParam &param) {
  eventMem = mtl::MemManager::create(ml::MlMem::getProductMem(), EVENT_MEM_SIZE, "GfTalk", false, mtl::ALLOCATOR_TYPE_PROGRAM, 0x10);
  if (event::Manager::get() == nullptr) {
    event::Manager::create(param.scn);
  }
  for (u32 i = 0; i < EVTDISP_NUM; i++) {
    disps[i] = true;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    categoryHandle = sound->createCategoryHandle();
    csCategoryHandle = sound->createCategoryHandle();
  }
  GfEvtBgm::build(param);
  fadeInSec = 0.5f;
  fadeInWaitSec = 0.0f;
  initialized = true;
}

GfGameEvent::~GfGameEvent() {}

void GfGameEvent::build(const GfSetupParam &param) {
  // __LINE__ must be 105 as in the original file: it is an argument of the allocation.
#line 105
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameEvent(param);
}

void GfGameEvent::destroy() {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    gameEvent->finalize();
    delete gameEvent;
  }
}

void GfGameEvent::finalize() {
  evtSe.cleanup();
  GfEvtBgm::destroy();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->releaseCategoryHandle(categoryHandle);
    sound->releaseCategoryHandle(csCategoryHandle);
  }
  clearColorFilter();
  if (event::Manager::get() != nullptr) {
    event::Manager::destroy();
  }
  if (eventMem.isValid()) {
    mtl::MemManager::erase(eventMem);
    eventMem = mtl::ALLOC_HANDLE();
  }
  if (eventDebugMem.isValid()) {
    mtl::MemManager::erase(eventDebugMem);
    eventDebugMem = mtl::ALLOC_HANDLE();
  }
  initialized = false;
}

void GfGameEvent::resetFadeInTime() {
  fadeInWaitSec = 0.0f;
  fadeInSec = 0.5f;
}

void GfGameEvent::clearColorFilter() {
  if (colorFilter != 0) {
    GfGameEnv::destroyColorFilter(colorFilter);
    colorFilter = CFILTER_HANDLE();
  }
}

bool GfGameEvent::isInitialized() {
  if (get() != nullptr) {
    return get()->initialized;
  }
  return false;
}

void GfGameEvent::clear() {
  GfGameEvent *gameEvent = get();
  if (gameEvent == nullptr) {
    return;
  }
  gameEvent->afterEventStartID = 0;
  gameEvent->playerOffState = 0;
  GfLayerPause::destroyLayerPause(gameEvent->layerPause);
  for (u32 i = 0; i < EVTDISP_NUM; i++) {
    gameEvent->disps[i] = true;
  }
  gameEvent->dispIds.clear();
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->clear();
  }
}

void GfGameEvent::update(const fw::UpdateInfo &info) {
  if (get() == nullptr || !get()->initialized) {
    return;
  }
  event::Manager *manager = event::Manager::get();
  if (manager != nullptr) {
    manager->update();
    manager->tail();
    manager->render();
  }
  updateEventObj(info);
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->update(info);
  }
  if (get() != nullptr) {
    get()->updateCsEventCategoryVolume();
  }
}

void GfGameEvent::updateEventObj(const fw::UpdateInfo &info) {
  GfGameEvent *gameEvent = get();
  for (auto it = gameEvent->evtModels.begin(); it != gameEvent->evtModels.end(); ++it) {
    (*it)->update(info);
  }
}

void GfGameEvent::postUpdate(const fw::UpdateInfo &) {
  if (get() != nullptr && get()->initialized && event::Manager::get() != nullptr) {
    event::Manager::get()->post();
  }
}

mtl::ALLOC_HANDLE GfGameEvent::getEventMem() {
  if (get() != nullptr) {
    return get()->eventMem;
  }
  return mtl::ALLOC_HANDLE();
}

mtl::ALLOC_HANDLE GfGameEvent::getEventDebugMem() {
  if (get() != nullptr) {
    return get()->eventDebugMem;
  }
  return mtl::ALLOC_HANDLE();
}

void GfGameEvent::stop() {
  if (event::Manager::get() != nullptr) {
    event::Manager::get()->stop();
  }
  if (get() != nullptr) {
    get()->isStopped = true;
  }
}

bool GfGameEvent::isPlaying() {
  if (event::Manager::get() != nullptr) {
    return event::Manager::get()->isPlay();
  }
  return false;
}

bool GfGameEvent::isStop() {
  if (get() != nullptr) {
    return get()->isStopped;
  }
  return false;
}

bool GfGameEvent::isPlayEvent(u32 eventId) {
  int flag = GfDataEvent::getEventPlayFlag(eventId);
  if (flag >= 0) {
    return GfGameFlag::getLocal(1, flag) != 0;
  }
  return false;
}

u32 GfGameEvent::getPlayEventId() {
  if (get() != nullptr) {
    return get()->playEventId;
  }
  return 0;
}

u32 GfGameEvent::getPlayBladeId() {
  if (get() != nullptr) {
    return get()->playBladeId;
  }
  return 0;
}

void GfGameEvent::setFadeInSec(f32 waitSec, f32 sec) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    gameEvent->fadeInWaitSec = waitSec;
    gameEvent->fadeInSec = sec;
  }
}

f32 GfGameEvent::getFadeInWaitSec() {
  if (get() != nullptr) {
    return get()->fadeInWaitSec;
  }
  return 0.0f;
}

f32 GfGameEvent::getFadeInSec() {
  if (get() != nullptr) {
    return get()->fadeInSec;
  }
  return 0.0f;
}

int GfGameEvent::getAfterEventStartID() {
  if (get() != nullptr) {
    return get()->afterEventStartID;
  }
  return 0;
}

void GfGameEvent::setAfterEventStartID(int startID) {
  if (get() != nullptr) {
    get()->afterEventStartID = startID;
  }
}

void GfGameEvent::applySetDispObject(GF_OBJ_HANDLE *handle) {
  GfGameEvent *gameEvent = get();
  if (gameEvent == nullptr) {
    return;
  }
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup == nullptr || setup->isEvent()) {
    return;
  }
  GfObjAcc acc(handle);
  bool isDisp = gameEvent->disps[acc.getType()];
  if (isDisp) {
    u32 id = acc.getType() << 16 | acc.getBdatId();
    isDisp = mm::mtl::find(gameEvent->dispIds.begin(), gameEvent->dispIds.end(), id) == gameEvent->dispIds.end();
  }
  if (acc.isDisp(OBJDISP_EVENT) != isDisp) {
    acc.setDisp(OBJDISP_EVENT, isDisp);
    acc.setAlphaEvtDisp(isDisp ? 1.0f : 0.0f);
  }
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    GfObjAcc bladeAcc(GfGameUtil::getBlade(handle));
    if (bladeAcc.isValid() && bladeAcc.isDisp(OBJDISP_EVENT) != isDisp) {
      bladeAcc.setDisp(OBJDISP_EVENT, isDisp);
      bladeAcc.setAlphaEvtDisp(isDisp ? 1.0f : 0.0f);
    }
  }
}

void GfGameEvent::setDisp(EVTDISP type, bool isDisp) {
  if (get() != nullptr) {
    get()->disps[type] = isDisp;
    applySetDisp(type);
  }
}

void GfGameEvent::setGmkIdDisp(gmk::GmkType type, u32 index, bool isDisp) { GfGameUtil::setDispByGmkTypeAndGmkIdx(type, index, isDisp); }

void GfGameEvent::setGmkBdatDisp(gmk::GmkType type, u32 bdatId, bool isDisp) { GfGameUtil::setDispByGmkTypeAndBdatId(type, bdatId, isDisp); }

void GfGameEvent::setMapLodDisp(u32 id, bool isDisp) {
  int bdatId = GfFieldLod::get()->findBdatIdByLodId(id);
  if (bdatId != 0) {
    GfFieldLod::get()->setFade(bdatId, isDisp, true);
  }
}

bool GfGameEvent::isMapLodDisp(u32 id) {
  int bdatId = GfFieldLod::get()->findBdatIdByLodId(id);
  return bdatId != 0 && !GfFieldLod::get()->isFadeOut(bdatId);
}

void GfGameEvent::setMapLodAnim(u32 id, bool isReverse, bool isSkip) {
  int bdatId = GfFieldLod::get()->findBdatIdByLodId(id);
  if (bdatId != 0) {
    GfFieldLod::get()->setAnimReverse(bdatId, isReverse, isSkip);
  }
}

bool GfGameEvent::isMapLodAnimReverse(u32 id) {
  int bdatId = GfFieldLod::get()->findBdatIdByLodId(id);
  if (bdatId != 0) {
    return GfFieldLod::get()->isAnimReverse(bdatId);
  }
  return false;
}

bool GfGameEvent::isDisp(EVTDISP type) {
  if (get() != nullptr) {
    return get()->disps[type];
  }
  return true;
}

bool GfGameEvent::isDisp(GF_OBJ_HANDLE *handle) {
  u32 type = GfObjUtil::getObjType(handle);
  bool result;
  if (type == OBJECT_TYPE_GIMMICK) {
    result = isDisp(EVTDISP_GIMMICK);
  } else {
    result = isDisp(static_cast<EVTDISP>(type));
  }
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr && setup->isEvent()) {
    result = true;
  }
  return result;
}

void GfGameEvent::applyChangeLayer(EVTDISP) {}

void GfGameEvent::eventPlayerOff(u32 eventId, bool isOff) {
  int category = GfDataEvent::getEventType(eventId);
  int state = playerOffState;
  if (isOff) {
    if (category != EVENT_CATEGORY_KEEP_PLAYER && state == 0) {
      GfGameObj::changeStopLayerIgnoreEventObj(3, true);
      GfGameObj::changeStopLayerIgnoreEventObj(4, true);
      GfGameObj::changeStopLayerIgnoreEventObj(10, true);
      GfGameSpeed::setLayerSpeed(EVENT_SPEED_LAYER, 0.0f);
      playerOffState = 1;
    }
  } else if (state == 1) {
    playerOffState = 0;
    GfGameSpeed::setLayerSpeed(EVENT_SPEED_LAYER, 1.0f);
    GfGameObj::changeStopLayerIgnoreEventObj(3, false);
    GfGameObj::changeStopLayerIgnoreEventObj(4, false);
    GfGameObj::changeStopLayerIgnoreEventObj(10, false);
  }
}

bool GfGameEvent::isCancelFlag() {
  if (get() != nullptr) {
    return get()->flags & FLAG_CANCEL;
  }
  return false;
}

void GfGameEvent::setCancelFlag(bool isCancel) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    if (isCancel) {
      gameEvent->flags |= FLAG_CANCEL;
    } else {
      gameEvent->flags &= ~FLAG_CANCEL;
    }
  }
}

void GfGameEvent::finishNewGameWait() {
  if (event::Manager::get() != nullptr) {
    event::Manager::get()->finishNewGameWait();
  }
}

void GfGameEvent::gevPlayEvent(GEV event, u32 eventId) {
  switch (event) {
  case GEV_EVENT_END_WAIT:
    clearWeather();
    break;
  case GEV_EVENT_END: {
    playState = PLAY_STATE_PLAY;
    eventPlayerOff(eventId, true);
    playEventId = eventId;
    lastPlayEventId = eventId;
    break;
  }
  case GEV_EVENT_PLAY_END: {
    int flag = GfDataEvent::getEventPlayFlag(eventId);
    if (flag >= 0) {
      GfGameFlag::setLocal(1, flag, 1);
    }
    eventPlayerOff(eventId, false);
    GfPlayFactory::createEventAfterScript(eventId);
    break;
  }
  case GEV_EVENT_SEQUENCE_START:
    playState = PLAY_STATE_SEQUENCE;
    break;
  case GEV_EVENT_SEQUENCE_END:
    playState = PLAY_STATE_NONE;
    resetFadeInTime();
    clearWeather();
    break;
  default:
    break;
  }
}

void GfGameEvent::clearWeather() {
  if (tempWeather != 0) {
    WEATHERID weather = GfGameEnv::getTempWeather();
    u32 mapId = tempWeatherMapId;
    GfGameEnv::destroyTempWeather(tempWeather);
    tempWeather = WEATHER_HANDLE();
    tempWeatherMapId = 0;
    if (mapId == GfGameManager::getMapID()) {
      GfFieldWeather::setMapWeatherID(weather);
    }
  }
}

void GfGameEvent::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_FADEIN && event::Manager::get() != nullptr && event::Manager::get()->isPlay()) {
    GfGameObj::changeStopLayerIgnoreEventObj(3, true);
    GfGameObj::changeStopLayerIgnoreEventObj(4, true);
    GfGameObj::changeStopLayerIgnoreEventObj(10, true);
    GfGameSpeed::setLayerSpeed(EVENT_SPEED_LAYER, 0.0f);
    get()->playerOffState = 1;
  }
}

void GfGameEvent::playBgm(const EventBgmSetup &setup) {
  EventBgmSetup playSetup = setup;
  if (GfPause::isPause(PAUSE_BIT_MAIN_MENU)) {
    playSetup.isKeep = false;
  }
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->playBgm(playSetup);
  }
}

void GfGameEvent::stopBgm(const EventBgmSetup &setup) {
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->stopBgm(setup);
  }
}

void GfGameEvent::cancelOverTime() {
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->cancelOverTime();
  }
}

void GfGameEvent::changeVolume(const EventBgmSetup &setup) {
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->changeBgmVolume(setup);
  }
}

bool GfGameEvent::isPlayBgm() {
  if (GfEvtBgm::get() != nullptr) {
    return GfEvtBgm::get()->isPlayBgm();
  }
  return false;
}

f32 GfGameEvent::getPlayBgmVolume() {
  GfEvtBgm *bgm = GfEvtBgm::get();
  if (bgm != nullptr && bgm->isPlayBgm()) {
    return bgm->playBgmVolume;
  }
  return 0.0f;
}

f32 GfGameEvent::getPlayBgmTime() {
  GfEvtBgm *bgm = GfEvtBgm::get();
  if (bgm != nullptr && bgm->isPlayBgm()) {
    return bgm->getPlayBgmTime();
  }
  return 0.0f;
}

f32 GfGameEvent::getPlayBgmTotalTime() {
  GfEvtBgm *bgm = GfEvtBgm::get();
  if (bgm != nullptr && bgm->isPlayBgm()) {
    return bgm->getTotalBgmTime();
  }
  return 0.0f;
}

void GfGameEvent::setCategoryVolume(fw::SoundCategory category, f32 volume, f32 time) {
  if (get() != nullptr && GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(get()->categoryHandle, category, volume, time);
  }
}

f32 GfGameEvent::getCategoryVolume(fw::SoundCategory category) {
  if (get() != nullptr && GfSound::get() != nullptr) {
    return GfSound::get()->getCategoryVolume(get()->categoryHandle, category);
  }
  return 1.0f;
}

void GfGameEvent::createSe(const char *name) {
  if (get() != nullptr) {
    get()->evtSe.createSe(name);
  }
}

void GfGameEvent::destroySe() {
  if (get() != nullptr) {
    get()->evtSe.destroySe();
  }
}

bool GfGameEvent::isLoadedSe() {
  if (get() != nullptr) {
    return get()->evtSe.isLoadedSe();
  }
  return true;
}

void GfGameEvent::addEventObjUpdater(GfEvtModel *model) { get()->evtModels.push_back(model); }

GfEvtModelWeapon *GfGameEvent::createWeapon(GfInitParamWeapon &param) { return GfEvtModelWeapon::create(param); }

GfEvtModelEvent *GfGameEvent::createEventObj(GfInitParamEventObj &param) {
  if (GfGameManager::isFullScreenMenu()) {
    param.layer = GfEvtModel::changeLayerUI(param.layer);
  }
  return GfEvtModelEvent::create(param);
}

void GfGameEvent::destroyEvtModel(GfEvtModel *model) { removeEventObjUpdater(model); }

void GfGameEvent::removeEventObjUpdater(GfEvtModel *model) {
  mm::mtl::FixedList<GfEvtModel *, 128> &models = get()->evtModels;
  mm::mtl::FixedList<GfEvtModel *, 128>::iterator it = mm::mtl::find(models.begin(), models.end(), model);
  if (it != models.end()) {
    models.erase(it);
  }
}

bool GfGameEvent::isOriginalHomuraModel(u32 bladeId) {
  if (bladeId != BLADE_HOMURA) {
    return false;
  }
  if (get() != nullptr) {
    u32 eventId = get()->playEventId;
    return eventId >= HOMURA_ORIGINAL_EVENT_FIRST && eventId <= HOMURA_ORIGINAL_EVENT_LAST;
  }
  return false;
}

void GfGameEvent::setListeningPoint(const mm::Vec3 &point) {
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    scene->isRequestListeningPoint = true;
    scene->requestListeningPoint = point;
  }
}

void GfGameEvent::setColorFilter(bool isEnable, int filter, int subFilter, f32 fadeSec) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearColorFilter();
  if (isEnable) {
    ColorFilter colorFilter;
    colorFilter.handle = CFILTER_HANDLE();
    colorFilter.filter = filter;
    colorFilter.farFilter = subFilter;
    colorFilter.time = fadeSec;
    colorFilter.prio = 2;
    gameEvent->colorFilter = GfGameEnv::createColorFilter(colorFilter);
  }
}

void GfGameEvent::setCloudSea(bool isEnable, bool isHigh) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearCloudSea();
  if (isEnable) {
    gameEvent->cloudSea = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(isHigh), static_cast<CLOUD_SEA_PRIO>(2));
  }
}

void GfGameEvent::clearCloudSea() {
  if (cloudSea != 0) {
    GfGameEnv::destroyCloudSea(cloudSea);
    cloudSea = CLOUD_SEA_HANDLE();
  }
}

void GfGameEvent::setMapWeather(WEATHERID weather) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearWeather();
  gameEvent->tempWeather = GfGameEnv::createTempWeather(weather, static_cast<WEATHER_PRIO>(1));
  gameEvent->tempWeatherMapId = GfGameManager::getMapID();
}

bool GfGameEvent::isMapWeatherEnable() { return get()->tempWeather != 0; }

void GfGameEvent::setWeaType(WEATYPE type) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    gameEvent->weaType = type;
    gameEvent->weaTypeWeather = GfFieldWeather::getCurrentMapWeatherID(false);
    if (type != WEATYPE_DEFAULT) {
      GfFieldWeather::setWeatherForEvent(type, nullptr);
    }
  }
}

void GfGameEvent::resetWeaType() {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr && gameEvent->weaType != WEATYPE_DEFAULT) {
    gameEvent->weaType = WEATYPE_DEFAULT;
    GfFieldWeather::setMapWeatherID(gameEvent->weaTypeWeather);
  }
}

WEATYPE GfGameEvent::getWeaType() {
  if (get() != nullptr) {
    return get()->weaType;
  }
  return WEATYPE_DEFAULT;
}

bool GfGameEvent::isLeaderCharaNG(u32 chara) {
  switch (chara) {
  case 0:
  case 5:
  case 7:
  case 8:
  case 9:
    return true;
  }
  return false;
}

} // namespace gf
