#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/event/ui_event_data.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

enum {
  ORDER_ZONE_TELOP = 1,
  ORDER_LOCATION_TELOP = 2,
};

class GfMenuOrderMgr : public mm::mtl::PtrSingleton<GfMenuOrderMgr> {
public:
  static const u32 LOG_MAX = 20;

  struct sLog {
    sLog() : unknown00(0), unknown04(0), unknown20(0) {}

    int unknown00;           // Inferred role: order; original member name unknown.
    u32 unknown04;           // Inferred role: object handle; original member name unknown.
    ui::EventData unknown08; // Inferred role: object event; original member name unknown.
    int unknown20;           // Inferred role: priority; original member name unknown.
  };

  GfMenuOrderMgr(const GfSetupParam &param) : unknown368(0) { initialize(param); }
  ~GfMenuOrderMgr();
  void initialize(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void setOrder(int order, u32 handle, const ui::EventData &event);
  static void cancelOrder(int order);
  static void finishOrder(int order);
  int getPrioOrder(int order);
  bool pickLogOrder(sLog &log);

  bool unknown08;                               // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedQueue<sLog, LOG_MAX> unknown10; // Inferred role: queued orders; original member name unknown.
  sLog unknown340;                              // Inferred role: current order; original member name unknown.
  int unknown368;                               // Inferred role: current order running; original member name unknown.
};

static_assert(sizeof(GfMenuOrderMgr::sLog) == 0x28, "");
static_assert(offsetof(GfMenuOrderMgr, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuOrderMgr, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuOrderMgr, unknown340) == 0x340, "");
static_assert(offsetof(GfMenuOrderMgr, unknown368) == 0x368, "");
static_assert(sizeof(GfMenuOrderMgr) == 0x370, "");

} // namespace gf
