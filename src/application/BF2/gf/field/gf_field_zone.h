#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class IEventZone {
public:
  virtual ~IEventZone() {}
  virtual void changeZone(u32, u32) {}
  virtual void changeZoneLock(u32, u32) {}
  virtual void recreateZone(u32) {}
  virtual void changeRoom(bool) {}
};

class GfFieldZone : public mm::mtl::PtrSingleton<GfFieldZone> {
public:
  static const u32 EVENT_MAX = 16;

  GfFieldZone(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldZone();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static void addEvent(IEventZone *event);
  static void removeEvent(IEventZone *event);
  void gevMapjump(GEV gev, const MapjumpCallbackInfo &info);

private:
  mm::mtl::FixedQueue<IEventZone *, EVENT_MAX> mEvents;
  bool mInitialized;
};

static_assert(sizeof(GfFieldZone) == 0xa0, "");

} // namespace gf
