#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "types.h"
#include "wnd/wnd_area.h"
#include "wnd/wnd_broad_phaze_interface.h"
#include "wnd/wnd_object_pool_memory.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace wnd {

struct ResWind;
class OverlappingCache;
class AABB;
class Dispatcher;
class WindObject;
class WindProbe;

// Octree broad phase. Layout from the constructor (0x71009866d0) and the allocation of 0xa150 bytes by
// fw::WindManager::buildWorld (0x71001af59c).
class BroadPhazeOctree : public BroadPhazeInterface {
public:
  // Path of an area in the octree; read by getArea and written by flushWindObject.
  struct Key {
    Key() : unknown00(-1), unknown08(0) {}

    u64 unknown00; // Inferred role: child index of each level, 4 bits per level (Octree::getBitFlag); original member name unknown.
    u32 unknown08; // Inferred role: number of levels; original member name unknown.
  };

  class Proxy : public BroadPhazeProxy {
  public:
    Key unknown40; // Inferred role: area of the proxy; original member name unknown.
  };

  // Inferred role: the proxies and the list of the free ones; original type name unknown. A type of its own: the
  // constructor links the proxies into the list (0x71009867b0) before the lists of unknowna110 are constructed.
  struct unknown004 {
    unknown004() {
      for (int i = 0; i < 512; i++) {
        unknowna000.push_back(&unknown00[i]);
      }
    }

    Proxy unknown00[512];                      // Inferred role: proxies; original member name unknown.
    mm::mtl::IntrusiveList<Proxy> unknowna000; // Inferred role: free proxies; original member name unknown.
  };

  BroadPhazeOctree(const ResWind &res, mm::mtl::IAllocator *allocator);
  ~BroadPhazeOctree() override;

  void createProxy(WindObject &wind) override;
  void destroyProxy(WindObject &wind) override;
  bool addWindObject(WindObject &wind) override;
  void removeWindObject(WindObject &wind) override;
  void calculateOverlapping(Dispatcher &dispatcher, mm::mtl::IntrusiveList<WindProbe> &probes) override;
  bool query(Query *query) override;

  AreaBlock *flushWindObject(WindObject &wind);
  AreaBlock *getArea(const Key &key);
  void gcArea(AreaBlock *area);
  void eraseProxyForce(AreaBlock &area);
  void flushProbes(mm::mtl::IntrusiveList<WindProbe> &probes);
  void collectWindObj(Dispatcher &dispatcher, mm::mtl::IntrusiveList<WindProbe> &probes);

  Octree unknown10;                        // Inferred role: octree; original member name unknown.
  AreaBlock unknown40;                     // Inferred role: root area; original member name unknown.
  mm::mtl::IAllocator *unknowne0;          // Role unknown, stored by the constructor; original member name unknown.
  unknown004 unknownf0;                    // Inferred role: proxies; original member name unknown.
  PoolObjectMemory<AreaBlock> unknowna110; // Inferred role: pool of the areas; original member name unknown.
};

static_assert(offsetof(BroadPhazeOctree::Proxy, unknown40) == 0x40, "");
static_assert(sizeof(BroadPhazeOctree::Proxy) == 0x50, "");
static_assert(offsetof(BroadPhazeOctree, unknown10) == 0x10, "");
static_assert(offsetof(BroadPhazeOctree, unknown40) == 0x40, "");
static_assert(offsetof(BroadPhazeOctree, unknowne0) == 0xe0, "");
static_assert(offsetof(BroadPhazeOctree, unknownf0) == 0xf0, "");
static_assert(offsetof(BroadPhazeOctree::unknown004, unknowna000) == 0xa000, "");
static_assert(sizeof(BroadPhazeOctree::unknown004) == 0xa020, "");
static_assert(offsetof(BroadPhazeOctree, unknowna110) == 0xa110, "");
static_assert(sizeof(BroadPhazeOctree) == 0xa150, "");

void detectAreaWind(AreaBlock *pArea, const AABB &aabb, f32 radius, OverlappingCache *pCache);

} // namespace wnd
