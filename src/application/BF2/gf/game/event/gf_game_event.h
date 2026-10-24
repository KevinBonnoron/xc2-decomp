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
      : unknown44(1.0f), unknown48(0.0f), unknown4c(0.0f), unknown50(0.0f), unknown54(0.0f), unknown58(0.0f), unknown5c(0.0f), unknown60(false), unknown61(false), unknown62(false), unknown63(false),
        unknown64(false), unknown65(false) {}

  mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
  f32 unknown44;                 // Inferred role: volume; original member name unknown.
  f32 unknown48;                 // Inferred role: volume seconds; original member name unknown.
  f32 unknown4c;                 // Inferred role: fade seconds; original member name unknown.
  f32 unknown50;                 // Inferred role: start seconds; original member name unknown.
  f32 unknown54;                 // Inferred role: delay seconds; original member name unknown.
  f32 unknown58;                 // Inferred role: fade out seconds; original member name unknown.
  f32 unknown5c;                 // Inferred role: over time seconds; original member name unknown.
  bool unknown60;                // Inferred role: keep flag; original member name unknown.
  bool unknown61;                // Inferred role: hand over flag; original member name unknown.
  bool unknown62;                // Inferred role: event flag; original member name unknown.
  bool unknown63;                // Inferred role: restart flag; original member name unknown.
  bool unknown64;                // Inferred role: audible flag; original member name unknown.
  bool unknown65;                // Inferred role: silent flag; original member name unknown.
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

  u32 unknown08;                                     // Inferred role: flags; original member name unknown.
  bool unknown0c;                                    // Inferred role: initialized; original member name unknown.
  mtl::ALLOC_HANDLE unknown10;                       // Inferred role: event memory; original member name unknown.
  mtl::ALLOC_HANDLE unknown14;                       // Inferred role: event debug memory; original member name unknown.
  int unknown18;                                     // Inferred role: after event start id; original member name unknown.
  int unknown1c;                                     // Inferred role: player off state; original member name unknown.
  GF_LP_HANDLE *unknown20;                           // Inferred role: layer pause; original member name unknown.
  bool unknown28[EVTDISP_NUM];                       // Inferred role: display flags; original member name unknown.
  mm::mtl::FixedVector<u32, 1024> unknown48;         // Inferred role: display ids; original member name unknown.
  mm::mtl::FixedList<GfEvtModel *, 128> unknown1050; // Inferred role: event models; original member name unknown.
  CFILTER_HANDLE unknown18f0;                        // Inferred role: color filter; original member name unknown.
  CLOUD_SEA_HANDLE unknown18f4;                      // Inferred role: cloud sea; original member name unknown.
  WEATHER_HANDLE unknown18f8;                        // Inferred role: temporary weather; original member name unknown.
  u32 unknown18fc;                                   // Inferred role: temporary weather map id; original member name unknown.
  WEATYPE unknown1900;                               // Inferred role: weather type; original member name unknown.
  WEATHERID unknown1904;                             // Inferred role: weather type weather; original member name unknown.
  u32 unknown1908;                                   // Inferred role: last play event id; original member name unknown.
  u32 unknown190c;                                   // Inferred role: play event id; original member name unknown.
  u32 unknown1910;                                   // Inferred role: play blade id; original member name unknown.
  PLAY_STATE unknown1914;                            // Inferred role: play state; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown1918;                // Inferred role: category handle; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown1920;                // Inferred role: cutscene category handle; original member name unknown.
  bool unknown1928;                                  // Inferred role: cutscene mute; original member name unknown.
  bool unknown1929;                                  // Inferred role: stopped; original member name unknown.
  GfEvtSe unknown1930;                               // Inferred role: event se; original member name unknown.
  f32 unknown1b00;                                   // Inferred role: fade in wait seconds; original member name unknown.
  f32 unknown1b04;                                   // Inferred role: fade in seconds; original member name unknown.
};

static_assert(offsetof(GfGameEvent, unknown08) == 0x8, "");
static_assert(offsetof(GfGameEvent, unknown10) == 0x10, "");
static_assert(offsetof(GfGameEvent, unknown18) == 0x18, "");
static_assert(offsetof(GfGameEvent, unknown20) == 0x20, "");
static_assert(offsetof(GfGameEvent, unknown28) == 0x28, "");
static_assert(offsetof(GfGameEvent, unknown48) == 0x48, "");
static_assert(offsetof(GfGameEvent, unknown1050) == 0x1050, "");
static_assert(offsetof(GfGameEvent, unknown18f0) == 0x18f0, "");
static_assert(offsetof(GfGameEvent, unknown1900) == 0x1900, "");
static_assert(offsetof(GfGameEvent, unknown190c) == 0x190c, "");
static_assert(offsetof(GfGameEvent, unknown1914) == 0x1914, "");
static_assert(offsetof(GfGameEvent, unknown1918) == 0x1918, "");
static_assert(offsetof(GfGameEvent, unknown1928) == 0x1928, "");
static_assert(offsetof(GfGameEvent, unknown1930) == 0x1930, "");
static_assert(offsetof(GfGameEvent, unknown1b00) == 0x1b00, "");
static_assert(sizeof(GfGameEvent) == 0x1b08, "");

} // namespace gf
