#pragma once
#include <stddef.h>

#include "gf/field/gf_field_locator.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

class GfMenuLocation : public mm::mtl::PtrSingleton<GfMenuLocation> {
public:
  static const u32 LOCATOR_TYPE_COUNT = 4;
  static const u32 ORDER_MAX = 128;

  struct OrderInfo {
    u32 unknown00; // Inferred role: index; original member name unknown.
    u32 unknown04; // Inferred role: distance; original member name unknown.
  };

  struct CompareOrder {
    bool operator()(const OrderInfo &order, const OrderInfo &other) const { return order.unknown04 < other.unknown04; }
  };

  struct LocatorGroup {
    mm::mtl::Vector<GfFieldLocator> unknown00;            // Inferred role: locators; original member name unknown.
    u32 unknown28;                                        // Inferred role: data num; original member name unknown.
    mm::mtl::FixedVector<OrderInfo, ORDER_MAX> unknown30; // Inferred role: orders; original member name unknown.
  };

  void updateDataNum(u32 type);
  static bool isInitialized();
  static u32 getLocatorDataNum(u32 type);

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u8 _09[0x10 - 0x09];
  LocatorGroup unknown10[LOCATOR_TYPE_COUNT]; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(GfMenuLocation::OrderInfo) == 0x8, "");
static_assert(offsetof(GfMenuLocation::LocatorGroup, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuLocation::LocatorGroup, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuLocation::LocatorGroup) == 0x438, "");
static_assert(offsetof(GfMenuLocation, unknown10) == 0x10, "");

} // namespace gf
