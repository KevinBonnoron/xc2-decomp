// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/wndlib/src/wndlib/composite/wnd_dispatcher.cpp.
#include <float.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/vector.h"
#include "types.h"
#include "wnd/wnd_dispatcher.h" // IWYU pragma: keep
#include "wnd/wnd_node.h"
#include "wnd/wnd_object.h"
#include "wnd/wnd_overlapping_cache.h"
#include "wnd/wnd_probe.h"
#include "wnd/wnd_shape.h"

namespace wnd {

Dispatcher::Dispatcher(const CollisionInfo &info) : unknown30(info) {
  unknown10[0][0] = nullptr;
  unknown10[0][1] = nullptr;
  unknown10[1][0] = nullptr;
  unknown10[1][1] = nullptr;
  SphereSphereAgent::registerAgent(*this);
  SphereBoxAgent::registerAgent(*this);
}

// Addresses 0x7100988384-0x71009885c0. Each probe runs the agent of its shape pair on the winds of its overlapping
// cache, keeps the local wind hits (while its vector has room) and binds the nearest area wind.
void Dispatcher::dispatchAll(mm::mtl::IntrusiveList<WindProbe> &probes, const UpdateInfo &info) {
  for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
    WindProbe *probe = it.get();
    Shape *pProbeShape = it->m_pShape;
#line 73
    MM_ASSERT(pProbeShape);
    OverlappingCache *pCache = probe->m_pOverlappingCache;
#line 76
    MM_ASSERT(pCache);
    // Capacity 64 matches OverlappingCache's FixedQueue<WindObject *, 64>; x8 + x23, #0x3f bounds the loop, and the
    // 0x840-byte frame accounts for the 0x40-byte header and 64 HitCache entries of 0x20 bytes each.
    HitCache hits[64];
    u32 count = 0;
    for (WindObject *pWind : pCache->unknown10) {
#line 85
      MM_ASSERT(pWind);
      Shape *pShape = pWind->m_pShape;
#line 87
      MM_ASSERT(pShape);
      bool (*agent)(const WindObject &, const WindObject &, f32, HitCache *) = unknown10[pProbeShape->unknown0c][pShape->unknown0c];
      if (agent != nullptr) {
        count += agent(*probe, *pWind, unknown30.unknown00, &hits[count]);
      }
    }
    probe->unknown190.clear();
    const AreaWind *nearest = nullptr;
    if (count != 0) {
      f32 nearestDistance = FLT_MAX;
      for (u32 i = 0; i < count; i++) {
        const WindObject *wind = hits[i].unknown00;
        if (wind->unknown20 == OBJECT_TYPE_UNKNOWN_0) {
          if (probe->unknown190.size() != probe->unknown190.capacity()) {
            LocalWindHitCache local;
            local.unknown00 = static_cast<const LocalWind *>(wind);
            // Stores wind, vector, distance at 0x7100988508-0x710098853c; first differs from declaration order at
            // 0x710098851c. Aggregate initialization in declaration order would put distance before vector.
            local.unknown10 = hits[i].unknown10;
            local.unknown08 = hits[i].unknown08;
            probe->unknown190.push_back(local);
          }
        } else if (wind->unknown20 == OBJECT_TYPE_UNKNOWN_2) {
          // WindWorld::update stores the bool unknown1d0 as a 32-bit word (0x710098a658); this read tests only bit 0
          // (ldrb + tbnz at 0x7100988544). A bool member gives cbnz and a 1-bit bitfield breaks WindWorld::update.
          if (!(info.unknown08 & 1) && hits[i].unknown08 < nearestDistance) {
            nearestDistance = hits[i].unknown08;
            nearest = static_cast<const AreaWind *>(wind);
          }
        }
      }
    }
    probe->setAreaWind(nearest);
  }
}

} // namespace wnd
