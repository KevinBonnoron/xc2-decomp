// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/wndlib/src/wndlib/broadphaze/wnd_broad_phaze_octree.cpp.
#include "wnd/wnd_broad_phaze_octree.h" // IWYU pragma: keep

#include <math.h>
#include <new>

#include "framework/wind/wind_factory.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include "wnd/wnd_dispatcher.h"
#include "wnd/wnd_object.h"
#include "wnd/wnd_overlapping_cache.h"
#include "wnd/wnd_probe.h"
#include "wnd/wnd_query.h"
#include "wnd/wnd_shape.h"

namespace wnd {

// Inferred role: whether the boxes a and b overlap, widened by margin; original name unknown.
static bool unknown005(const AABB &a, const AABB &b, f32 margin) {
  return a.unknown00.x - b.unknown10.x < margin && a.unknown10.x - b.unknown00.x > -margin && a.unknown00.y - b.unknown10.y < margin && a.unknown10.y - b.unknown00.y > -margin &&
         a.unknown00.z - b.unknown10.z < margin && a.unknown10.z - b.unknown00.z > -margin;
}

BroadPhazeOctree::BroadPhazeOctree(const ResWind &res, mm::mtl::IAllocator *allocator) : unknowne0(allocator) {
  mm::Vec3 center = (res.unknown10 + res.unknown00) * 0.5f;
  mm::Vec3 size = res.unknown10 - res.unknown00;
  f32 x = size.x / 100.0f;
  f32 y = size.y / 100.0f;
  f32 z = size.z / 100.0f;
  f32 length = x > y ? x : y;
  length = length > z ? length : z;
  u32 level = static_cast<u32>(ceilf(log2f(length)));
  level = level < 15 ? level : 15;
  f32 extent = static_cast<f32>(1 << level) * 100.0f;
  AABB aabb;
  aabb.unknown00 = center - mm::Vec3(extent, extent, extent);
  aabb.unknown10 = center + mm::Vec3(extent, extent, extent);
  unknown10.setAABB(aabb, level);
  unknown40.unknown60 = aabb;
  unknowna110.unknown002(allocator);
}

BroadPhazeOctree::~BroadPhazeOctree() { eraseProxyForce(unknown40); }

void BroadPhazeOctree::eraseProxyForce(AreaBlock &area) {
  for (mm::mtl::IntrusiveList<WindObject>::iterator it = area.m_winds.begin(); it != area.m_winds.end(); ++it) {
    destroyProxy(*it);
  }
  area.m_winds.clear();
  for (u32 i = 0; i < 8; i++) {
    AreaBlock *child = area.unknown18[i];
    if (child != nullptr) {
      eraseProxyForce(*child);
      gcArea(child);
    }
  }
}

void BroadPhazeOctree::createProxy(WindObject &wind) {
  Proxy *proxy = nullptr;
  if (!unknownf0.unknowna000.empty()) {
    proxy = unknownf0.unknowna000.begin().get();
    unknownf0.unknowna000.pop_front();
    new (proxy) Proxy;
  }
  unknown001(wind, *proxy);
}

void BroadPhazeOctree::destroyProxy(WindObject &wind) {
  Proxy *pProxy = static_cast<Proxy *>(unknown002(wind));
#line 77
  MM_ASSERT(pProxy);
  pProxy->~Proxy();
  unknownf0.unknowna000.push_back(pProxy);
}

bool BroadPhazeOctree::addWindObject(WindObject &wind) {
  createProxy(wind);
  AreaBlock *area = flushWindObject(wind);
  if (area != nullptr) {
    area->m_winds.push_back(&wind);
    wind.addRef();
    return true;
  }
  return false;
}

void BroadPhazeOctree::removeWindObject(WindObject &wind) {
  Proxy *pProxy = static_cast<Proxy *>(wind.m_pProxy);
#line 161
  MM_ASSERT(pProxy);
  AreaBlock *area = getArea(pProxy->unknown40);
  if (area != nullptr) {
    area->m_winds.erase(&wind);
    destroyProxy(wind);
    wind.release();
    gcArea(area);
  }
}

AreaBlock *BroadPhazeOctree::getArea(const Key &key) {
  AreaBlock *area = &unknown40;
  for (u32 i = 1; i < key.unknown08; i++) {
    area = area->unknown18[(key.unknown00 >> ((i - 1) * 4)) & 7];
  }
  return area;
}

void BroadPhazeOctree::gcArea(AreaBlock *area) {
  AreaBlock *block = area;
  while (block->unknown10 != nullptr) {
    AreaBlock *parent = block->unknown10;
    if (!block->m_winds.empty() || block->unknown58 != 0) {
      break;
    }
    u32 index = 0;
    // The game compares the children of block with the original area (0x71009874f4, x19), not with the current
    // block. It looks like an original quirk.
    for (u32 i = 0; i < 8; i++) {
      if (block->unknown18[i] == area) {
        index = i;
        break;
      }
    }
    parent->destroyChild(index, unknowna110);
    block = parent;
  }
}

void BroadPhazeOctree::calculateOverlapping(Dispatcher &dispatcher, mm::mtl::IntrusiveList<WindProbe> &probes) {
  flushProbes(probes);
  collectWindObj(dispatcher, probes);
}

void BroadPhazeOctree::flushProbes(mm::mtl::IntrusiveList<WindProbe> &probes) {
  for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
    WindProbe *probe = it.get();
    if (probe->unknown58 == 1) {
      if (probe->m_pShape != nullptr && probe->m_pProxy != nullptr && (probe->unknown68 & 1) != 0) {
        probe->m_pShape->calcAABB(probe->unknown30, &probe->m_pProxy->unknown20);
        probe->unknown68 &= ~1u;
      }
      flushWindObject(*probe);
    }
  }
}

void BroadPhazeOctree::collectWindObj(Dispatcher &dispatcher, mm::mtl::IntrusiveList<WindProbe> &probes) {
  for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
    // The game loads the proxy (0x710098775c) before the node assert of operator->, which is why it uses get().
    // It loads the cache (0x710098777c) after that assert, so it uses operator->.
    BroadPhazeProxy *pProxy = it.get()->m_pProxy;
    OverlappingCache *pCache = it->m_pOverlappingCache;
    pCache->unknown10.clear();
    mm::mtl::FixedQueue<AreaBlock *, 1024> areas;
    if (unknown005(unknown40.unknown60, pProxy->unknown20, dispatcher.m_collisionInfo.unknown00)) {
      areas.push(&unknown40);
    }
    while (!areas.empty()) {
      AreaBlock *area = areas.front();
      areas.pop_front();
      detectAreaWind(area, pProxy->unknown20, dispatcher.m_collisionInfo.unknown00, pCache);
      for (u32 i = 0; i < 8; i++) {
        AreaBlock *child = area->unknown18[i];
        if (child != nullptr && unknown005(child->unknown60, pProxy->unknown20, dispatcher.m_collisionInfo.unknown00)) {
          areas.push(child);
        }
      }
    }
  }
}

bool BroadPhazeOctree::query(Query *query) {
  if (query != nullptr && query->getRTTI()->isKindOf(&AreaQuery::m_rtti)) {
    static_cast<AreaQuery *>(query)->unknown08 = &unknown40;
  }
  return false;
}

void detectAreaWind(AreaBlock *pArea, const AABB &aabb, f32 radius, OverlappingCache *pCache) {
#line 235
  MM_ASSERT(pArea);
  MM_ASSERT(pCache);
  for (mm::mtl::IntrusiveList<WindObject>::iterator it = pArea->m_winds.begin(); it != pArea->m_winds.end(); ++it) {
    BroadPhazeOctree::Proxy *pProxy = static_cast<BroadPhazeOctree::Proxy *>(it.get()->m_pProxy);
#line 245
    MM_ASSERT(pProxy);
    if (unknown005(pProxy->unknown20, aabb, radius)) {
      pCache->unknown001(*it);
    }
  }
}

} // namespace wnd
