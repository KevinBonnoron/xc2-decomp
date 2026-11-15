// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/wndlib/src/wndlib/wnd_world.cpp.
#include "anm/anm_array-inl.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h" // for safeRelease
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "types.h"
#include "wnd/wnd_broad_phaze_interface.h"
#include "wnd/wnd_dispatcher.h"
#include "wnd/wnd_global_wind_manager.h" // IWYU pragma: keep
#include "wnd/wnd_node.h"
#include "wnd/wnd_object.h"
#include "wnd/wnd_probe.h"
#include "wnd/wnd_query.h"
#include "wnd/wnd_wind.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace wnd {

WindWorld::WindWorld(Dispatcher *dispatcher, BroadPhazeInterface *broadPhaze, const Array<const ResConpoundWind *> &resWind, mm::mtl::IAllocator *allocator) : unknown0c(0.0f), unknown1d0(false) {
  m_pBroadPhaze = broadPhaze;
  broadPhaze->addRef();
  unknown168 = dispatcher;
  dispatcher->addRef();
  unknown10.setup(resWind, allocator);
}

WindWorld::~WindWorld() {
  while (!unknown188.empty()) {
    AreaWind *wind = unknown188.begin().get()->unknown10;
    removeAreaWind(*wind);
  }
  while (!unknown170.empty()) {
    removeProbe(*unknown170.begin());
  }
  delayErace();
  mm::mtl::safeRelease(unknown168);
  mm::mtl::safeRelease(m_pBroadPhaze);
}

void WindWorld::setDebugMode(bool enable, u32 mask) {
  unknown1d0 = enable;
  unknown10.setDebugWind(enable, mask);
}

bool WindWorld::query(Query *query) {
  if (query != nullptr) {
    if (query->getRTTI()->isKindOf(&AreaWindQuery::m_rtti)) {
      AreaWindQuery *areaWindQuery = static_cast<AreaWindQuery *>(query);
      areaWindQuery->unknown08.clear();
      for (mm::mtl::IntrusiveList<unknown003<AreaWind>>::iterator it = unknown188.begin(); it != unknown188.end(); ++it) {
        areaWindQuery->unknown08.push(it.get()->unknown10);
      }
      return true;
    }
    if (query->getRTTI()->isKindOf(&LocalWindQuery::m_rtti)) {
      LocalWindQuery *localWindQuery = static_cast<LocalWindQuery *>(query);
      localWindQuery->unknown08.clear();
      for (mm::mtl::IntrusiveList<unknown003<LocalWind>>::iterator it = unknown1a0.begin(); it != unknown1a0.end(); ++it) {
        localWindQuery->unknown08.push(it.get()->unknown10);
      }
      return true;
    }
    if (query->getRTTI()->isKindOf(&ProbeQuery::m_rtti)) {
      ProbeQuery *probeQuery = static_cast<ProbeQuery *>(query);
      probeQuery->unknown08.clear();
      for (mm::mtl::IntrusiveList<WindProbe>::iterator it = unknown170.begin(); it != unknown170.end(); ++it) {
        probeQuery->unknown08.push(&*it);
      }
      return true;
    }
  }
  if (m_pBroadPhaze != nullptr && m_pBroadPhaze->query(query)) {
    return true;
  }
  return false;
}

// Addresses 0x710098a768-70. The game inlines GlobalWind::update here instead of calling it,
// so its body is written out; a call gives a two-instruction tail call.
void WindWorld::updateGlobalWind(const UpdateInfo &info) {
  if (unknown10.unknown40.unknownf0 != nullptr) {
    unknown10.unknown40.unknownf0->update(info);
  }
  if (unknown10.unknown40.unknowne8 != nullptr) {
    unknown10.unknown40.unknowne8->update(info);
  }
  unknown10.unknown40.WindBlender::update(info);
  if (unknown10.unknown40.unknownf0 == nullptr) {
    // Address 0x710098a770: no-op store, as in GlobalWind::update.
    unknown10.unknown40.unknownf0 = nullptr;
  }
}

bool WindWorld::addProbe(WindProbe &probe) {
  probe.addRef();
  unknown170.push_back(&probe);
  m_pBroadPhaze->createProxy(probe);
  probe.bindGlobalWind(unknown10.unknown40);
  return true;
}

void WindWorld::removeProbe(WindProbe &probe) {
  probe.setAreaWind(nullptr);
  probe.unbindGlobalWind();
  m_pBroadPhaze->destroyProxy(probe);
  unknown170.erase(&probe);
  probe.unknown190.clear();
  unknown1b8.push_back(&probe.unknown70);
}

bool WindWorld::addAreaWind(AreaWind &wind) {
#line 126
  MM_ASSERT(m_pBroadPhaze);
  bool created = m_pBroadPhaze->addWindObject(wind);
  if (created) {
    wind.addRef();
    unknown188.push_back(&wind.unknown268);
  }
  return created;
}

void WindWorld::removeAreaWind(AreaWind &wind) {
#line 144
  MM_ASSERT(m_pBroadPhaze);
  m_pBroadPhaze->removeWindObject(wind);
  unknown188.erase(&wind.unknown268);
  unknown1b8.push_back(&wind.unknown70);
}

bool WindWorld::addLocalWind(LocalWind &wind) {
#line 91
  MM_ASSERT(m_pBroadPhaze);
  bool created = m_pBroadPhaze->addWindObject(wind);
  if (created) {
    wind.addRef();
    unknown1a0.push_back(&wind.unknown98);
  }
  return created;
}

void WindWorld::removeLocalWind(LocalWind &wind) {
#line 109
  MM_ASSERT(m_pBroadPhaze);
  m_pBroadPhaze->removeWindObject(wind);
  unknown1a0.erase(&wind.unknown98);
  unknown1b8.push_back(&wind.unknown70);
}

void WindWorld::delayErace() {
  while (!unknown1b8.empty()) {
    WindObject *object = unknown1b8.begin().get()->unknown10;
    unknown1b8.erase(&object->unknown70);
    object->release();
  }
}

// Both functions have empty bodies in the game.
void WindWorld::createOverlappingPairCache(WindProbe &probe) {}

void WindWorld::destroyOverlappingPairCache(WindProbe &probe) {}

void WindWorld::updateProbe(const UpdateInfo &info) {
  if (unknown170.empty()) {
    return;
  }
  for (auto it = unknown170.begin(); it != unknown170.end(); ++it) {
    // The game has no node assertion here, so operator-> (which asserts) is not used.
    it.get()->calcGlobalWindPower(info);
  }
}

} // namespace wnd
