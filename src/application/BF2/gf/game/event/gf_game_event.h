#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

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
};

} // namespace gf
