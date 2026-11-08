// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/menu/gf_menu_order_mgr.cpp.
#include "gf/menu/gf_menu_order_mgr.h"

#include "gf/gf_allocator.h"
#include "ui/ui_manager.h"

// pushLogOrder calls FixedQueue<sLog, 20>::insert out of line; its instantiation is not defined here.
extern template mm::mtl::FixedQueue<gf::GfMenuOrderMgr::sLog, 20>::iterator mm::mtl::FixedQueue<gf::GfMenuOrderMgr::sLog, 20>::insert(mm::mtl::FixedQueue<gf::GfMenuOrderMgr::sLog, 20>::iterator,
                                                                                                                                      const gf::GfMenuOrderMgr::sLog &);

namespace gf {

// Inferred role: order and its priority; original type name unknown.
struct unknown001 {
  int unknown00; // Inferred role: order; original member name unknown.
  int unknown04; // Inferred role: priority; original member name unknown.
};

// Inferred role: priority of each order; original table name unknown.
static const unknown001 PRIORITY_TABLE[] = {{ORDER_ZONE_TELOP, 6}, {ORDER_LOCATION_TELOP, 5}};
constexpr u32 PRIORITY_TABLE_COUNT = sizeof(PRIORITY_TABLE) / sizeof(PRIORITY_TABLE[0]);

void GfMenuOrderMgr::initialize(const GfSetupParam &) {
  unknown08 = true;
  unknown10.clear();
}

GfMenuOrderMgr::~GfMenuOrderMgr() {}

void GfMenuOrderMgr::build(const GfSetupParam &param) {
  // __LINE__ must be 64 as in the original file: it is the line argument of operator new.
#line 64
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuOrderMgr(param);
}

void GfMenuOrderMgr::destroy() {
  GfMenuOrderMgr *manager = get();
  manager->finalize();
  delete manager;
}

void GfMenuOrderMgr::finalize() { unknown08 = false; }

bool GfMenuOrderMgr::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuOrderMgr::postUpdate(const fw::UpdateInfo &) {
  GfMenuOrderMgr *manager = get();
  if (manager != nullptr && manager->unknown368 == 0) {
    if (manager->pickLogOrder(manager->unknown340)) {
      ui::UIManager::get()->requestObjectEvent(manager->unknown340.unknown04, manager->unknown340.unknown08, 0.0f);
      manager->unknown368 = 1;
    }
  }
}

int GfMenuOrderMgr::getPrioOrder(int order) {
  for (u32 i = 0; i < PRIORITY_TABLE_COUNT; i++) {
    if (PRIORITY_TABLE[i].unknown00 == order) {
      return PRIORITY_TABLE[i].unknown04;
    }
  }
  return 0;
}

void GfMenuOrderMgr::setOrder(int order, u32 handle, const ui::EventData &event) {
  sLog log(order, handle, event);
  log.unknown20 = get()->getPrioOrder(order);
  get()->pushLogOrder(log);
}

void GfMenuOrderMgr::pushLogOrder(const sLog &log) {
  if (!unknown10.full()) {
    for (mm::mtl::FixedQueue<sLog, LOG_MAX>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
      if ((*it).unknown00 == log.unknown00 && (*it).unknown00 == ORDER_LOCATION_TELOP && (*it).unknown08.unknown14 == 0) {
        *it = log;
        return;
      }
      if ((*it).unknown20 < log.unknown20) {
        unknown10.insert(it, log);
        return;
      }
    }
    unknown10.push(log);
  }
}

void GfMenuOrderMgr::finishOrder(int order) {
  if (get()->unknown340.unknown00 == order) {
    get()->unknown368 = 0;
  }
}

bool GfMenuOrderMgr::pickLogOrder(sLog &log) {
  if (!unknown10.empty()) {
    unknown10.unknown002(log);
    return true;
  }
  log.unknown00 = 0;
  log.unknown04 = 0;
  log.unknown20 = 0;
  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuOrderMgr>::~PtrSingleton();
