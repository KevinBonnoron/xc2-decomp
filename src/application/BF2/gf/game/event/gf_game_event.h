#pragma once
#include <stddef.h>

#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_evt_se.h"
#include "gf/game/gf_game_env.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {
enum SoundCategory : int;
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
}

namespace gf {

class GfEvtModel;
class GfEvtModelEvent;
class GfEvtModelSalvage;
class GfEvtModelWeapon;
class GfInitParamBlade;
class GfInitParamDriver;
class GfInitParamEnemy;
class GfInitParamEventObj;
class GfInitParamNpc;
class GfInitParamWeapon;
struct GF_LP_HANDLE;
struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
struct GfSetupParam;

enum EVTDISP {
  EVTDISP_MAP = 1,
  EVTDISP_GIMMICK = 8,
  EVTDISP_COLLECTION = 16,
  EVTDISP_SALVAGE = 17,
  EVTDISP_PRECIOUS = 18,
  EVTDISP_TBOX = 19,
  EVTDISP_EFFECT = 20,
  EVTDISP_SE = 21,
  EVTDISP_JUMP = 22,
  EVTDISP_WARP = 23,
  EVTDISP_DMG_EFFECT = 24,
  EVTDISP_DMG_SE = 25,
  EVTDISP_NUM = 26,
};

struct EventBgmSetup {
  EventBgmSetup()
      : volume(1.0f), volumeSec(0.0f), fadeSec(0.0f), startSec(0.0f), delaySec(0.0f), fadeOutSec(0.0f), overTimeSec(0.0f), isKeep(false),
        isHandOver(false), isEvent(false), isRestart(false), isAudible(false), isSilent(false) {}

  mm::mtl::FixStr<64> name;
  f32 volume;
  f32 volumeSec;
  f32 fadeSec;
  f32 startSec;
  f32 delaySec;
  f32 fadeOutSec;
  f32 overTimeSec;
  bool isKeep;
  bool isHandOver;
  bool isEvent;
  bool isRestart;
  bool isAudible;
  bool isSilent;
};

static_assert(sizeof(EventBgmSetup) == 0x68, "");

class GfGameEvent : public mm::mtl::PtrSingleton<GfGameEvent> {
public:
  enum {
    FLAG_CANCEL = 1 << 0,
  };

  enum PLAY_STATE {
    PLAY_STATE_NONE,
    PLAY_STATE_SEQUENCE,
    PLAY_STATE_PLAY,
  };

  GfGameEvent(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameEvent();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void resetFadeInTime();
  void clearColorFilter();
  static bool isInitialized();
  static void clear();
  static void update(const fw::UpdateInfo &info);
  static void updateEventObj(const fw::UpdateInfo &info);
  void updateCsEventCategoryVolume();
  static void postUpdate(const fw::UpdateInfo &info);
  static mtl::ALLOC_HANDLE getEventMem();
  static mtl::ALLOC_HANDLE getEventDebugMem();
  static void play(u32 eventId, u32 bladeId, u32 startId, bool isEndFadeOut);
  static void stop();
  static bool isPlaying();
  static bool isStop();
  static bool isPlayEvent(u32 eventId);
  static u32 getPlayEventId();
  static u32 getPlayBladeId();
  static void setFadeInSec(f32 waitSec, f32 sec);
  static f32 getFadeInWaitSec();
  static f32 getFadeInSec();
  static int getAfterEventStartID();
  static void setAfterEventStartID(int startID);
  static void setDisp(u32 type, const mm::mtl::FixedVector<u32, 1024> &ids, bool isDisp);
  static void applySetDispObject(GF_OBJ_HANDLE *handle);
  static void setDisp(EVTDISP type, bool isDisp);
  static void applySetDisp(EVTDISP type);
  static void setGmkIdDisp(gmk::GmkType type, u32 index, bool isDisp);
  static void setGmkBdatDisp(gmk::GmkType type, u32 bdatId, bool isDisp);
  static void setMapLodDisp(u32 id, bool isDisp);
  static bool isMapLodDisp(u32 id);
  static void setMapLodAnim(u32 id, bool isReverse, bool isSkip);
  static bool isMapLodAnimReverse(u32 id);
  static bool isDisp(EVTDISP type);
  static bool isDisp(GF_OBJ_HANDLE *handle);
  static void applyChangeLayer(EVTDISP type);
  void eventPlayerOff(u32 eventId, bool isOff);
  static bool isCancelFlag();
  static void setCancelFlag(bool isCancel);
  static void finishNewGameWait();
  void gevPlayEvent(GEV event, u32 eventId);
  void clearWeather();
  static void gevPause(u32 resumeBits, u32 pauseBits);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void playBgm(const EventBgmSetup &setup);
  static void stopBgm(const EventBgmSetup &setup);
  static void cancelOverTime();
  static void changeVolume(const EventBgmSetup &setup);
  static bool isPlayBgm();
  static f32 getPlayBgmVolume();
  static f32 getPlayBgmTime();
  static f32 getPlayBgmTotalTime();
  static void setCategoryVolume(fw::SoundCategory category, f32 volume, f32 time);
  static f32 getCategoryVolume(fw::SoundCategory category);
  static void createSe(const char *name);
  static void destroySe();
  static bool isLoadedSe();
  static GfEvtModel *createDriver(GfInitParamDriver &param);
  static void addEventObjUpdater(GfEvtModel *model);
  static GfEvtModel *createBlade(GfInitParamBlade &param);
  static GfEvtModel *createNpc(GfInitParamNpc &param);
  static GfEvtModel *createEnemy(GfInitParamEnemy &param);
  static GfEvtModelWeapon *createWeapon(GfInitParamWeapon &param);
  static GfEvtModelEvent *createEventObj(GfInitParamEventObj &param);
  static void destroyEvtModel(GfEvtModel *model);
  static void removeEventObjUpdater(GfEvtModel *model);
  static bool isOriginalHomuraModel(u32 bladeId);
  static GfEvtModelSalvage *createSalvage();
  static void setListeningPoint(const mm::Vec3 &point);
  static void setColorFilter(bool isEnable, int filter, int subFilter, f32 fadeSec);
  static void setCloudSea(bool isEnable, bool isHigh);
  void clearCloudSea();
  static void setMapWeather(WEATHERID weather);
  static bool isMapWeatherEnable();
  static void setWeaType(WEATYPE type);
  static void resetWeaType();
  static WEATYPE getWeaType();
  static bool isLeaderCharaNG(u32 chara);

  u32 flags;
  bool initialized;
  mtl::ALLOC_HANDLE eventMem;
  mtl::ALLOC_HANDLE eventDebugMem;
  int afterEventStartID;
  int playerOffState;
  GF_LP_HANDLE *layerPause;
  bool disps[EVTDISP_NUM];
  mm::mtl::FixedVector<u32, 1024> dispIds;
  mm::mtl::FixedList<GfEvtModel *, 128> evtModels;
  CFILTER_HANDLE colorFilter;
  CLOUD_SEA_HANDLE cloudSea;
  WEATHER_HANDLE tempWeather;
  u32 tempWeatherMapId;
  WEATYPE weaType;
  WEATHERID weaTypeWeather;
  u32 lastPlayEventId;
  u32 playEventId;
  u32 playBladeId;
  PLAY_STATE playState;
  GF_SE_CATEGORY_HANDLE *categoryHandle;
  GF_SE_CATEGORY_HANDLE *csCategoryHandle;
  bool isCsMute;
  bool isStopped;
  GfEvtSe evtSe;
  f32 fadeInWaitSec;
  f32 fadeInSec;
};

static_assert(offsetof(GfGameEvent, flags) == 0x8, "");
static_assert(offsetof(GfGameEvent, eventMem) == 0x10, "");
static_assert(offsetof(GfGameEvent, afterEventStartID) == 0x18, "");
static_assert(offsetof(GfGameEvent, layerPause) == 0x20, "");
static_assert(offsetof(GfGameEvent, disps) == 0x28, "");
static_assert(offsetof(GfGameEvent, dispIds) == 0x48, "");
static_assert(offsetof(GfGameEvent, evtModels) == 0x1050, "");
static_assert(offsetof(GfGameEvent, colorFilter) == 0x18f0, "");
static_assert(offsetof(GfGameEvent, weaType) == 0x1900, "");
static_assert(offsetof(GfGameEvent, playEventId) == 0x190c, "");
static_assert(offsetof(GfGameEvent, playState) == 0x1914, "");
static_assert(offsetof(GfGameEvent, categoryHandle) == 0x1918, "");
static_assert(offsetof(GfGameEvent, isCsMute) == 0x1928, "");
static_assert(offsetof(GfGameEvent, evtSe) == 0x1930, "");
static_assert(offsetof(GfGameEvent, fadeInWaitSec) == 0x1b00, "");
static_assert(sizeof(GfGameEvent) == 0x1b08, "");

} // namespace gf
