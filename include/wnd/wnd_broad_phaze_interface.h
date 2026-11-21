#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "wnd/wnd_object.h"
#include "wnd/wnd_shape.h"

namespace wnd {

struct Query;
class Dispatcher;
class WindProbe;

// Broad phase entry of a wind object. pOnwer is named by the assertions of wnd_broad_phaze_interface.h; the vtable
// (0x71011b9c18) holds the destructors 0x7100987bf4 (ret) and 0x7100987bf8 (operator delete).
class BroadPhazeProxy : public mm::mtl::IntrusiveListNodeBase {
public:
  BroadPhazeProxy() : pOnwer(nullptr) {}
  virtual ~BroadPhazeProxy() {}

  WindObject *pOnwer;
  AABB unknown20; // Inferred role: bounds, filled by Shape::calcAABB; original member name unknown.
};

static_assert(offsetof(BroadPhazeProxy, pOnwer) == 0x18, "");
static_assert(offsetof(BroadPhazeProxy, unknown20) == 0x20, "");
static_assert(sizeof(BroadPhazeProxy) == 0x40, "");

// Interface of the broad phase used by WindWorld; the slot order comes from the vtable of BroadPhazeOctree (0x71011b9ba8).
class BroadPhazeInterface : public mm::mtl::ReferenceObject {
public:
  virtual ~BroadPhazeInterface() = default;
  // BroadPhazeOctree::createProxy (0x7100986d70) ends with a tail call of the void Shape::calcAABB.
  virtual void createProxy(WindObject &wind);
  virtual void destroyProxy(WindObject &wind);
  virtual bool addWindObject(WindObject &wind);
  virtual void removeWindObject(WindObject &wind);
  // BroadPhazeOctree::calculateOverlapping tail-calls collectWindObj (0x7100987660), which never sets w0.
  virtual void calculateOverlapping(Dispatcher &dispatcher, mm::mtl::IntrusiveList<WindProbe> &probes);
  virtual bool query(Query *query);

protected:
  // Inferred role: links wind and proxy, then computes the bounds of the proxy; original name unknown.
  // __LINE__ must be 47, 48 and 54 as in the original header: they are the line arguments of the asserts.
#line 46
  static void unknown001(WindObject &wind, BroadPhazeProxy &proxy) {
    MM_ASSERT(wind.m_pProxy == nullptr);
    MM_ASSERT(proxy.pOnwer == nullptr);
    wind.m_pProxy = &proxy;
    proxy.pOnwer = &wind;
#line 54
    MM_ASSERT(wind.m_pShape);
    wind.m_pShape->calcAABB(wind.unknown30, &proxy.unknown20);
  }

  // Inferred role: unlinks wind from its proxy and returns the proxy; original name unknown.
  // __LINE__ must be 60 and 63 as in the original header: they are the line arguments of the asserts.
#line 59
  static BroadPhazeProxy *unknown002(WindObject &wind) {
    MM_ASSERT(wind.m_pProxy != nullptr);
    BroadPhazeProxy *pProxy = wind.m_pProxy;
#line 63
    MM_ASSERT(pProxy->pOnwer != nullptr);
    wind.m_pProxy = nullptr;
    pProxy->pOnwer = nullptr;
    return pProxy;
  }
};

} // namespace wnd
