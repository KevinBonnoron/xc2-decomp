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
    : unknown08(0), unknown0c(false), unknown18(0), unknown1c(0), unknown20(reinterpret_cast<GF_LP_HANDLE *>(-1)), unknown18f0(), unknown18f4(), unknown18f8(), unknown18fc(0),
      unknown1900(WEATYPE_DEFAULT), unknown1904(WEATHER_F), unknown1908(0), unknown190c(0), unknown1910(0), unknown1914(PLAY_STATE_NONE), unknown1918(INVALID_CATEGORY_HANDLE),
      unknown1920(INVALID_CATEGORY_HANDLE), unknown1928(false), unknown1929(false), unknown1b00(0.0f), unknown1b04(0.0f) {
  initialize(param);
}

void GfGameEvent::initialize(const GfSetupParam &param) {
  unknown10 = mtl::MemManager::create(ml::MlMem::getProductMem(), EVENT_MEM_SIZE, "GfTalk", false, mtl::ALLOCATOR_TYPE_PROGRAM, 0x10);
  if (event::Manager::get() == nullptr) {
    event::Manager::create(param.scn);
  }
  for (u32 i = 0; i < EVTDISP_NUM; i++) {
    unknown28[i] = true;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    unknown1918 = sound->createCategoryHandle();
    unknown1920 = sound->createCategoryHandle();
  }
  GfEvtBgm::build(param);
  unknown1b04 = 0.5f;
  unknown1b00 = 0.0f;
  unknown0c = true;
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
  unknown1930.cleanup();
  GfEvtBgm::destroy();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->releaseCategoryHandle(unknown1918);
    sound->releaseCategoryHandle(unknown1920);
  }
  clearColorFilter();
  if (event::Manager::get() != nullptr) {
    event::Manager::destroy();
  }
  if (unknown10.isValid()) {
    mtl::MemManager::erase(unknown10);
    unknown10 = mtl::ALLOC_HANDLE();
  }
  if (unknown14.isValid()) {
    mtl::MemManager::erase(unknown14);
    unknown14 = mtl::ALLOC_HANDLE();
  }
  unknown0c = false;
}

void GfGameEvent::resetFadeInTime() {
  unknown1b00 = 0.0f;
  unknown1b04 = 0.5f;
}

void GfGameEvent::clearColorFilter() {
  if (unknown18f0 != 0) {
    GfGameEnv::destroyColorFilter(unknown18f0);
    unknown18f0 = CFILTER_HANDLE();
  }
}

bool GfGameEvent::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown0c;
  }
  return false;
}

void GfGameEvent::clear() {
  GfGameEvent *gameEvent = get();
  if (gameEvent == nullptr) {
    return;
  }
  gameEvent->unknown18 = 0;
  gameEvent->unknown1c = 0;
  GfLayerPause::destroyLayerPause(gameEvent->unknown20);
  for (u32 i = 0; i < EVTDISP_NUM; i++) {
    gameEvent->unknown28[i] = true;
  }
  gameEvent->unknown48.clear();
  if (GfEvtBgm::get() != nullptr) {
    GfEvtBgm::get()->clear();
  }
}

void GfGameEvent::update(const fw::UpdateInfo &info) {
  if (get() == nullptr || !get()->unknown0c) {
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
  for (auto it = gameEvent->unknown1050.begin(); it != gameEvent->unknown1050.end(); ++it) {
    (*it)->update(info);
  }
}

void GfGameEvent::postUpdate(const fw::UpdateInfo &) {
  if (get() != nullptr && get()->unknown0c && event::Manager::get() != nullptr) {
    event::Manager::get()->post();
  }
}

mtl::ALLOC_HANDLE GfGameEvent::getEventMem() {
  if (get() != nullptr) {
    return get()->unknown10;
  }
  return mtl::ALLOC_HANDLE();
}

mtl::ALLOC_HANDLE GfGameEvent::getEventDebugMem() {
  if (get() != nullptr) {
    return get()->unknown14;
  }
  return mtl::ALLOC_HANDLE();
}

void GfGameEvent::stop() {
  if (event::Manager::get() != nullptr) {
    event::Manager::get()->stop();
  }
  if (get() != nullptr) {
    get()->unknown1929 = true;
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
    return get()->unknown1929;
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
    return get()->unknown190c;
  }
  return 0;
}

u32 GfGameEvent::getPlayBladeId() {
  if (get() != nullptr) {
    return get()->unknown1910;
  }
  return 0;
}

void GfGameEvent::setFadeInSec(f32 waitSec, f32 sec) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    gameEvent->unknown1b00 = waitSec;
    gameEvent->unknown1b04 = sec;
  }
}

f32 GfGameEvent::getFadeInWaitSec() {
  if (get() != nullptr) {
    return get()->unknown1b00;
  }
  return 0.0f;
}

f32 GfGameEvent::getFadeInSec() {
  if (get() != nullptr) {
    return get()->unknown1b04;
  }
  return 0.0f;
}

int GfGameEvent::getAfterEventStartID() {
  if (get() != nullptr) {
    return get()->unknown18;
  }
  return 0;
}

void GfGameEvent::setAfterEventStartID(int startID) {
  if (get() != nullptr) {
    get()->unknown18 = startID;
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
  bool isDisp = gameEvent->unknown28[acc.getType()];
  if (isDisp) {
    u32 id = acc.getType() << 16 | acc.getBdatId();
    isDisp = mm::mtl::find(gameEvent->unknown48.begin(), gameEvent->unknown48.end(), id) == gameEvent->unknown48.end();
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
    get()->unknown28[type] = isDisp;
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
    return get()->unknown28[type];
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
  int state = unknown1c;
  if (isOff) {
    if (category != EVENT_CATEGORY_KEEP_PLAYER && state == 0) {
      GfGameObj::changeStopLayerIgnoreEventObj(3, true);
      GfGameObj::changeStopLayerIgnoreEventObj(4, true);
      GfGameObj::changeStopLayerIgnoreEventObj(10, true);
      GfGameSpeed::setLayerSpeed(EVENT_SPEED_LAYER, 0.0f);
      unknown1c = 1;
    }
  } else if (state == 1) {
    unknown1c = 0;
    GfGameSpeed::setLayerSpeed(EVENT_SPEED_LAYER, 1.0f);
    GfGameObj::changeStopLayerIgnoreEventObj(3, false);
    GfGameObj::changeStopLayerIgnoreEventObj(4, false);
    GfGameObj::changeStopLayerIgnoreEventObj(10, false);
  }
}

bool GfGameEvent::isCancelFlag() {
  if (get() != nullptr) {
    return get()->unknown08 & FLAG_CANCEL;
  }
  return false;
}

void GfGameEvent::setCancelFlag(bool isCancel) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    if (isCancel) {
      gameEvent->unknown08 |= FLAG_CANCEL;
    } else {
      gameEvent->unknown08 &= ~FLAG_CANCEL;
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
    unknown1914 = PLAY_STATE_PLAY;
    eventPlayerOff(eventId, true);
    unknown190c = eventId;
    unknown1908 = eventId;
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
    unknown1914 = PLAY_STATE_SEQUENCE;
    break;
  case GEV_EVENT_SEQUENCE_END:
    unknown1914 = PLAY_STATE_NONE;
    resetFadeInTime();
    clearWeather();
    break;
  default:
    break;
  }
}

void GfGameEvent::clearWeather() {
  if (unknown18f8 != 0) {
    WEATHERID weather = GfGameEnv::getTempWeather();
    u32 mapId = unknown18fc;
    GfGameEnv::destroyTempWeather(unknown18f8);
    unknown18f8 = WEATHER_HANDLE();
    unknown18fc = 0;
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
    get()->unknown1c = 1;
  }
}

void GfGameEvent::playBgm(const EventBgmSetup &setup) {
  EventBgmSetup playSetup = setup;
  if (GfPause::isPause(PAUSE_BIT_MAIN_MENU)) {
    playSetup.unknown60 = false;
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
    return bgm->m_playBgmVolume;
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
    GfSound::get()->setCategoryVolume(get()->unknown1918, category, volume, time);
  }
}

f32 GfGameEvent::getCategoryVolume(fw::SoundCategory category) {
  if (get() != nullptr && GfSound::get() != nullptr) {
    return GfSound::get()->getCategoryVolume(get()->unknown1918, category);
  }
  return 1.0f;
}

void GfGameEvent::createSe(const char *name) {
  if (get() != nullptr) {
    get()->unknown1930.createSe(name);
  }
}

void GfGameEvent::destroySe() {
  if (get() != nullptr) {
    get()->unknown1930.destroySe();
  }
}

bool GfGameEvent::isLoadedSe() {
  if (get() != nullptr) {
    return get()->unknown1930.isLoadedSe();
  }
  return true;
}

void GfGameEvent::addEventObjUpdater(GfEvtModel *model) { get()->unknown1050.push_back(model); }

GfEvtModelWeapon *GfGameEvent::createWeapon(GfInitParamWeapon &param) { return GfEvtModelWeapon::create(param); }

GfEvtModelEvent *GfGameEvent::createEventObj(GfInitParamEventObj &param) {
  if (GfGameManager::isFullScreenMenu()) {
    param.layer = GfEvtModel::changeLayerUI(param.layer);
  }
  return GfEvtModelEvent::create(param);
}

void GfGameEvent::destroyEvtModel(GfEvtModel *model) { removeEventObjUpdater(model); }

void GfGameEvent::removeEventObjUpdater(GfEvtModel *model) {
  mm::mtl::FixedList<GfEvtModel *, 128> &models = get()->unknown1050;
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
    u32 eventId = get()->unknown190c;
    return eventId >= HOMURA_ORIGINAL_EVENT_FIRST && eventId <= HOMURA_ORIGINAL_EVENT_LAST;
  }
  return false;
}

void GfGameEvent::setListeningPoint(const mm::Vec3 &point) {
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    scene->unknown2a0 = true;
    scene->unknown290 = point;
  }
}

void GfGameEvent::setColorFilter(bool isEnable, int filter, int subFilter, f32 fadeSec) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearColorFilter();
  if (isEnable) {
    ColorFilter colorFilter;
    colorFilter.unknown0c = CFILTER_HANDLE();
    colorFilter.unknown00 = filter;
    colorFilter.unknown04 = subFilter;
    colorFilter.unknown08 = fadeSec;
    colorFilter.unknown10 = 2;
    gameEvent->unknown18f0 = GfGameEnv::createColorFilter(colorFilter);
  }
}

void GfGameEvent::setCloudSea(bool isEnable, bool isHigh) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearCloudSea();
  if (isEnable) {
    gameEvent->unknown18f4 = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(isHigh), static_cast<CLOUD_SEA_PRIO>(2));
  }
}

void GfGameEvent::clearCloudSea() {
  if (unknown18f4 != 0) {
    GfGameEnv::destroyCloudSea(unknown18f4);
    unknown18f4 = CLOUD_SEA_HANDLE();
  }
}

void GfGameEvent::setMapWeather(WEATHERID weather) {
  GfGameEvent *gameEvent = get();
  gameEvent->clearWeather();
  gameEvent->unknown18f8 = GfGameEnv::createTempWeather(weather, static_cast<WEATHER_PRIO>(1));
  gameEvent->unknown18fc = GfGameManager::getMapID();
}

bool GfGameEvent::isMapWeatherEnable() { return get()->unknown18f8 != 0; }

void GfGameEvent::setWeaType(WEATYPE type) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    gameEvent->unknown1900 = type;
    gameEvent->unknown1904 = GfFieldWeather::getCurrentMapWeatherID(false);
    if (type != WEATYPE_DEFAULT) {
      GfFieldWeather::setWeatherForEvent(type, nullptr);
    }
  }
}

void GfGameEvent::resetWeaType() {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr && gameEvent->unknown1900 != WEATYPE_DEFAULT) {
    gameEvent->unknown1900 = WEATYPE_DEFAULT;
    GfFieldWeather::setMapWeatherID(gameEvent->unknown1904);
  }
}

WEATYPE GfGameEvent::getWeaType() {
  if (get() != nullptr) {
    return get()->unknown1900;
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
