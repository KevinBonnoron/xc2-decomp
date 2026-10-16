#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

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
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();
  static void update(const fw::UpdateInfo &info);
  static void postUpdate(const fw::UpdateInfo &info);
  static void stop();
  static void finishNewGameWait();
  static mtl::ALLOC_HANDLE getEventMem();
  void gevPlayEvent(GEV event, u32 eventId);
  static void gevPause(u32 resumeBits, u32 pauseBits);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void setMapWeather(WEATHERID weather);
  static void setCloudSea(bool isEnable, bool isHigh);
  static void setColorFilter(bool isEnable, int filter, int subFilter, f32 fadeSec);
  static void setWeaType(WEATYPE type);
  static void resetWeaType();
  static void playBgm(const EventBgmSetup &setup);
  static void stopBgm(const EventBgmSetup &setup);
  static void changeVolume(const EventBgmSetup &setup);
  static bool isPlayBgm();
  static void cancelOverTime();
  static f32 getPlayBgmTotalTime();
};

} // namespace gf
