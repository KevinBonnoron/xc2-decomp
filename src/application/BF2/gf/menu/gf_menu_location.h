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
    u32 index;
    u32 distance;
  };

  struct CompareOrder {
    bool operator()(const OrderInfo &order, const OrderInfo &other) const { return order.distance < other.distance; }
  };

  struct LocatorGroup {
    mm::mtl::Vector<GfFieldLocator> locators;
    u32 dataNum;
    mm::mtl::FixedVector<OrderInfo, ORDER_MAX> orders;
  };

  void updateDataNum(u32 type);

  u8 _08[0x10 - 0x08];
  LocatorGroup groups[LOCATOR_TYPE_COUNT];
};

static_assert(sizeof(GfMenuLocation::OrderInfo) == 0x8, "");
static_assert(offsetof(GfMenuLocation::LocatorGroup, dataNum) == 0x28, "");
static_assert(offsetof(GfMenuLocation::LocatorGroup, orders) == 0x30, "");
static_assert(sizeof(GfMenuLocation::LocatorGroup) == 0x438, "");
static_assert(offsetof(GfMenuLocation, groups) == 0x10, "");

} // namespace gf
