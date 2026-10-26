#include "framework/wind/wind_manager.h"

#include "framework/wind/wind_impluse.h"
#include "framework/wind/wind_probe.h"
#include "mm_math/mm_vec3.h"
#include "wnd/wnd.h"

namespace wnd {
struct Query;
} // namespace wnd

namespace fw {

class ProbeDrawer : public mm::mtl::IntrusiveListNode<ProbeDrawer> {};

const char *WindManager::getName() const { return "WindManager"; }

bool WindManager::isDebugMode() { return false; }

void WindManager::activateDebugWindow(ml::WinProc *window) {}

int WindManager::getGlobalWind() const {
  if (unknown18.get() != nullptr) {
    return unknown18->unknown10.unknown140;
  }
  return -1;
}

bool WindManager::setGlobalWind(int wind) {
  if (unknown18.get() != nullptr) {
    return unknown18->unknown10.setCurrentWind(wind);
  }
  return false;
}

const mm::Vec3 &WindManager::getGlobalWindPower() {
  WindManager *manager = get();
  if (manager == nullptr) {
    return mm::Vec3::zero;
  }
  if (manager->unknown90.get() != nullptr) {
    wnd::WindProbe *probe = manager->unknown90->unknown20;
    return probe->unknowna0[probe->unknown88];
  }
  if (manager->unknown88.get() != nullptr) {
    return manager->unknown88->unknown20->unknowna0[0];
  }
  return mm::Vec3::zero;
}

void WindManager::addProbe(WindProbe *probe) {
  unknown20.push_back(probe);
  if (unknown18.get() != nullptr) {
    unknown18->addProbe(*probe->unknown20);
  }
  if (probe->unknown34) {
    unknown90 = probe;
  }
}

void WindManager::removeProbe(WindProbe *probe) {
  if (unknown90.get() == probe) {
    unknown90 = nullptr;
  }
  if (unknown18.get() != nullptr) {
    unknown18->removeProbe(*probe->unknown20);
  }
  unknown20.erase(probe);
}

void WindManager::addDebugDrawer(ProbeDrawer &drawer) { unknown38.push_back(&drawer); }

void WindManager::removeDebugDrawer(ProbeDrawer &drawer) { unknown38.erase(&drawer); }

void WindManager::addImpluse(WindImpluse *impluse) {
  unknown18.get()->addLocalWind(*impluse->unknown20);
  unknown50.push_back(impluse);
}

void WindManager::removeImpluse(WindImpluse *impluse) {
  unknown18.get()->removeLocalWind(*impluse->unknown20);
  unknown50.erase(impluse);
}

void WindManager::setDebugMode(bool enable, u32 mask) {
  WindManager *manager = get();
  if (manager != nullptr && manager->unknown18.get() != nullptr) {
    manager->unknown18->setDebugMode(enable, mask);
  }
}

bool WindManager::query(wnd::Query *query) {
  WindManager *manager = get();
  if (manager != nullptr && manager->unknown18.get() != nullptr) {
    return manager->unknown18->query(query);
  }
  return false;
}

} // namespace fw
