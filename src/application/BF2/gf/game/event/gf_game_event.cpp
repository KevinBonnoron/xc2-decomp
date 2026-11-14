#include "gf/game/event/gf_game_event.h"

#include "bdat.h"
#include "event/manager.h"
#include "event/seq_info.h"
#include "event/seq_manager.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_evt_model.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/event/gf_event_bgm_setup.h"
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
#include "gf/map/gf_map_manager.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "ml/ml_mem.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"

namespace gf {

namespace {

constexpr int EVENT_UNKNOWN_1 = 1;                         // Inferred role: event category keep player; original name unknown.
constexpr u32 EVENT_SPEED_UNKNOWN_1 = 1;                   // Inferred role: event speed layer; original name unknown.
constexpr u32 HOMURA_ORIGINAL_EVENT_UNKNOWN_10062 = 10062; // Inferred role: homura original event first; original name unknown.
constexpr u32 HOMURA_ORIGINAL_EVENT_UNKNOWN_10065 = 10065; // Inferred role: homura original event last; original name unknown.
constexpr size_t EVENT_UNKNOWN_36700160 = 0x2300000;       // Inferred role: event mem size; original name unknown.

// Inferred table: gimmick type of each event display type; original name unknown.
const u8 unknown001[EVTDISP_UNKNOWN_26] = {
    gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59,
    gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59,
    gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_UNKNOWN_59, gmk::GMK_TYPE_COLLECTION, gmk::GMK_TYPE_SALVAGE,    gmk::GMK_TYPE_PRECIOUS,   gmk::GMK_TYPE_TBOX,       gmk::GMK_TYPE_EFFECT,
    gmk::GMK_TYPE_SE,         gmk::GMK_TYPE_JUMP,       gmk::GMK_TYPE_WARP,       gmk::GMK_TYPE_DMG_EFFECT, gmk::GMK_TYPE_DMG_SE,
};

// Inferred role: cutscene sequence category ("CS " in the event category names); original name unknown.
constexpr u32 unknown002 = 4;
// Inferred role: fade time of the cutscene category mute; original name unknown.
constexpr f32 unknown003 = 0.5f;

} // namespace

GfGameEvent::GfGameEvent(const GfSetupParam &param)
    : unknown08(0), unknown0c(false), unknown18(0), unknown1c(0), unknown20(reinterpret_cast<GF_LP_HANDLE *>(-1)), unknown18f0(), unknown18f4(), unknown18f8(), unknown18fc(0),
      unknown1900(WEATYPE_UNKNOWN_0), unknown1904(WEATHER_F), unknown1908(0), unknown190c(0), unknown1910(0), unknown1914(PLAY_STATE_UNKNOWN_0), unknown1918(unknown019), unknown1920(unknown019),
      unknown1928(false), unknown1929(false), unknown1b00(0.0f), unknown1b04(0.0f) {
  initialize(param);
}

void GfGameEvent::initialize(const GfSetupParam &param) {
  unknown10 = mtl::MemManager::create(ml::MlMem::getProductMem(), EVENT_UNKNOWN_36700160, "GfTalk", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  if (event::Manager::get() == nullptr) {
    event::Manager::create(param.unknown00);
  }
  for (u32 i = 0; i < EVTDISP_UNKNOWN_26; i++) {
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
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameEvent(param);
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
  for (u32 i = 0; i < EVTDISP_UNKNOWN_26; i++) {
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

void GfGameEvent::updateCsEventCategoryVolume() {
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }
  const event::SeqInfo &info = event::SeqManager::get().unknown001();
  if (event::Manager::get() != nullptr) {
    bool isCs = info.unknown54 == unknown002;
    bool isPlay = event::Manager::get()->isPlay();
    if (isCs && isPlay) {
      if (!unknown1928) {
        unknown1928 = true;
        sound->setCategoryVolume(unknown1920, CATEGORY_CH_SE, 0.0f, unknown003);
        sound->setCategoryVolume(unknown1920, CATEGORY_CH_SE_NS, 0.0f, unknown003);
      }
      return;
    }
  }
  if (unknown1928) {
    unknown1928 = false;
    sound->setCategoryVolume(unknown1920, CATEGORY_CH_SE, 1.0f, unknown003);
    sound->setCategoryVolume(unknown1920, CATEGORY_CH_SE_NS, 1.0f, unknown003);
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

void GfGameEvent::play(u32 eventId, u32 bladeId, u32 startId, bool isEndFadeOut) {
  GfGameEvent *gameEvent = get();
  event::Manager *manager = event::Manager::get();
  if (gameEvent == nullptr || manager == nullptr) {
    return;
  }
  gameEvent->unknown1929 = false;
  u8 *list = Bdat::getFP("EVT_listList");
  u32 listTop = Bdat::getIdTop(list);
  u32 listEnd = listTop + Bdat::getIdCount(list);
  for (u32 i = listTop; i < listEnd; i++) {
    u8 *bdat = Bdat::getFP(Bdat::getVal(list, "listSeat", i).valueString);
    u32 top = Bdat::getIdTop(bdat);
    u32 count = Bdat::getIdCount(bdat);
    if (top <= eventId && eventId < top + count) {
      mm::mtl::FixStr<64> name = Bdat::getVal(bdat, "evtName", eventId).valueString;
      if (name.c_str()[0] == '\0') {
        return;
      }
      if (!manager->isDebugPlayOnetime() && Bdat::getVal(bdat, "linkID", eventId).valueU16 != 0) {
        name += "_link";
      }
      Bdat::getVal(bdat, "category", eventId);
      gameEvent->unknown190c = eventId;
      gameEvent->unknown1910 = startId;
      manager->play(name.c_str(), unknown020, 0, 0, bladeId, startId, isEndFadeOut);
      return;
    }
  }
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
  if (acc.isDisp(OBJDISP_UNKNOWN_1) != isDisp) {
    acc.setDisp(OBJDISP_UNKNOWN_1, isDisp);
    acc.setAlphaEvtDisp(isDisp ? 1.0f : 0.0f);
  }
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    GfObjAcc bladeAcc(GfGameUtil::getBlade(handle));
    if (bladeAcc.isValid() && bladeAcc.isDisp(OBJDISP_UNKNOWN_1) != isDisp) {
      bladeAcc.setDisp(OBJDISP_UNKNOWN_1, isDisp);
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

void GfGameEvent::applySetDisp(EVTDISP type) {
  if (type == EVTDISP_MAP) {
    applySetDispObject(GfMapManager::getGfObjHandle());
    return;
  }
  if (type >= EVTDISP_COLLECTION) {
    gmk::GmkType gmkType = static_cast<gmk::GmkType>(unknown001[type]);
    if (gmkType != gmk::GMK_TYPE_UNKNOWN_59) {
      GfGameUtil::setDispByGmkType(gmkType, isDisp(type));
    }
  } else {
    for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(type)) {
      applySetDispObject(handle);
    }
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
    result = isDisp(EVTDISP_UNKNOWN_8);
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
    if (category != EVENT_UNKNOWN_1 && state == 0) {
      GfGameObj::changeStopLayerIgnoreEventObj(3, true);
      GfGameObj::changeStopLayerIgnoreEventObj(4, true);
      GfGameObj::changeStopLayerIgnoreEventObj(10, true);
      GfGameSpeed::setLayerSpeed(EVENT_SPEED_UNKNOWN_1, 0.0f);
      unknown1c = 1;
    }
  } else if (state == 1) {
    unknown1c = 0;
    GfGameSpeed::setLayerSpeed(EVENT_SPEED_UNKNOWN_1, 1.0f);
    GfGameObj::changeStopLayerIgnoreEventObj(3, false);
    GfGameObj::changeStopLayerIgnoreEventObj(4, false);
    GfGameObj::changeStopLayerIgnoreEventObj(10, false);
  }
}

bool GfGameEvent::isCancelFlag() {
  if (get() != nullptr) {
    return get()->unknown08 & FLAG_UNKNOWN_0;
  }
  return false;
}

void GfGameEvent::setCancelFlag(bool isCancel) {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr) {
    if (isCancel) {
      gameEvent->unknown08 |= FLAG_UNKNOWN_0;
    } else {
      gameEvent->unknown08 &= ~FLAG_UNKNOWN_0;
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
  case GEV_UNKNOWN_8:
    clearWeather();
    break;
  case GEV_UNKNOWN_9: {
    unknown1914 = PLAY_STATE_UNKNOWN_2;
    eventPlayerOff(eventId, true);
    unknown190c = eventId;
    unknown1908 = eventId;
    break;
  }
  case GEV_UNKNOWN_10: {
    int flag = GfDataEvent::getEventPlayFlag(eventId);
    if (flag >= 0) {
      GfGameFlag::setLocal(1, flag, 1);
    }
    eventPlayerOff(eventId, false);
    GfPlayFactory::createEventAfterScript(eventId);
    break;
  }
  case GEV_UNKNOWN_11:
    unknown1914 = PLAY_STATE_UNKNOWN_1;
    break;
  case GEV_UNKNOWN_12:
    unknown1914 = PLAY_STATE_UNKNOWN_0;
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

void GfGameEvent::gevPause(u32 resumeBits, u32 pauseBits) {
  bool isPause = (pauseBits & PAUSE_BIT_UNKNOWN_7) != 0;
  bool isResume = (resumeBits & PAUSE_BIT_UNKNOWN_7) != 0;
  if (isPause || isResume) {
    isPause = isPause & !isResume;
    fw::EffectManager *manager = fw::EffectManager::get();
    // Category 3: the event effects.
    manager->unknown37958[3] = __builtin_fmaxf(isPause ? 0.0f : 1.0f, 0.00001f);
    manager->setMasterPause(isPause);
  }
}

void GfGameEvent::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_6 && event::Manager::get() != nullptr && event::Manager::get()->isPlay()) {
    GfGameObj::changeStopLayerIgnoreEventObj(3, true);
    GfGameObj::changeStopLayerIgnoreEventObj(4, true);
    GfGameObj::changeStopLayerIgnoreEventObj(10, true);
    GfGameSpeed::setLayerSpeed(EVENT_SPEED_UNKNOWN_1, 0.0f);
    get()->unknown1c = 1;
  }
}

void GfGameEvent::playBgm(const EventBgmSetup &setup) {
  EventBgmSetup playSetup = setup;
  if (GfPause::isPause(PAUSE_BIT_UNKNOWN_6)) {
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
    return bgm->unknown0c.unknown44;
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

GfEvtModel *GfGameEvent::createDriver(GfInitParamDriver &param) {
  if (!param.unknown1a2 && !GfGameManager::isInMetJIJI()) {
    param.unknown1a2 = true;
  }
  GfEvtModel *model = GfEvtModelDriver::create(param);
  addEventObjUpdater(model);
  return model;
}

void GfGameEvent::addEventObjUpdater(GfEvtModel *model) { get()->unknown1050.push_back(model); }

GfEvtModel *GfGameEvent::createBlade(GfInitParamBlade &param) {
  if (param.getBladeID() == BLADE_HOMURI && GfDataBlade::isHomuriNameHikari()) {
    param.m_bladeID = BLADE_UNKNOWN_1074;
  }
  GfEvtModel *model = GfEvtModelBlade::create(param);
  addEventObjUpdater(model);
  return model;
}

GfEvtModel *GfGameEvent::createNpc(GfInitParamNpc &param) {
  CBdatWrapper bdat = {GfDataBdat::getFP(BDAT_RSC_NPC_LIST)};
  if (param.unknown18 == nullptr) {
    param.unknown18 = &bdat;
  }
  return GfEvtModelNpc::create(param);
}

GfEvtModel *GfGameEvent::createEnemy(GfInitParamEnemy &param) {
  CBdatWrapper bdat = {GfDataBdat::getFP(BDAT_RSC_EN)};
  if (param.unknown18 == nullptr) {
    param.unknown18 = &bdat;
  }
  GfEvtModel *model = GfEvtModelEnemy::create(param);
  addEventObjUpdater(model);
  return model;
}

GfEvtModelWeapon *GfGameEvent::createWeapon(GfInitParamWeapon &param) { return GfEvtModelWeapon::create(param); }

GfEvtModelEvent *GfGameEvent::createEventObj(GfInitParamEventObj &param) {
  if (GfGameManager::isFullScreenMenu()) {
    param.unknown40 = GfEvtModel::changeLayerUI(param.unknown40);
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
    return eventId >= HOMURA_ORIGINAL_EVENT_UNKNOWN_10062 && eventId <= HOMURA_ORIGINAL_EVENT_UNKNOWN_10065;
  }
  return false;
}

GfEvtModelSalvage *GfGameEvent::createSalvage() {
  GfInitParamDriver param;
  param.unknown08 = unknown030_9;
  param.m_bladeID = DRIVER_UNKNOWN_1;
  param.unknown40 = 8;
  return GfEvtModelSalvage::create(param);
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
    if (type != WEATYPE_UNKNOWN_0) {
      GfFieldWeather::setWeatherForEvent(type, nullptr);
    }
  }
}

void GfGameEvent::resetWeaType() {
  GfGameEvent *gameEvent = get();
  if (gameEvent != nullptr && gameEvent->unknown1900 != WEATYPE_UNKNOWN_0) {
    gameEvent->unknown1900 = WEATYPE_UNKNOWN_0;
    GfFieldWeather::setMapWeatherID(gameEvent->unknown1904);
  }
}

WEATYPE GfGameEvent::getWeaType() {
  if (get() != nullptr) {
    return get()->unknown1900;
  }
  return WEATYPE_UNKNOWN_0;
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

template mm::mtl::FixedList<gf::GfEvtModel *, 32>::iterator mm::mtl::FixedList<gf::GfEvtModel *, 32>::erase(mm::mtl::FixedList<gf::GfEvtModel *, 32>::iterator);
