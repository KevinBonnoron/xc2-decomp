#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace wnd {

class WindObject;

// Winds found near a probe by the broad phase. Original header name unknown. Layout from wnd::detectAreaWind
// (0x7100987a20) and BroadPhazeOctree::collectWindObj (0x7100987700); no wnd function allocates one
// (WindWorld::createOverlappingPairCache is empty).
class OverlappingCache {
public:
  // Inferred role: queues wind, or prints a warning when the cache is full; original name unknown.
  void unknown001(WindObject &wind) {
    if (unknown10.full()) {
      mm::MMStdBase::mmPrint("warning:");
      mm::MMStdBase::mmPrint("ヒット候補が多すぎます");
    } else {
      unknown10.push(&wind);
    }
  }

  u8 _00[0x10];
  mm::mtl::FixedQueue<WindObject *, 64> unknown10; // Inferred role: winds overlapping the probe; original member name unknown.
};

static_assert(offsetof(OverlappingCache, unknown10) == 0x10, "");

} // namespace wnd
