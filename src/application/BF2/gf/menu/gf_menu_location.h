#pragma once
#include <stddef.h>

#include "gf/field/gf_field_locator.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuLocation : public mm::mtl::PtrSingleton<GfMenuLocation> {
public:
  // Inferred role: number of locator types; original name unknown.
  static const u32 LOCATOR_TYPE_UNKNOWN_4 = 4;
  // Inferred role: capacity of the orders of a locator group; original name unknown.
  static const u32 ORDER_UNKNOWN_128 = 128;

  struct OrderInfo {
    u32 unknown00; // Inferred role: index; original member name unknown.
    u32 unknown04; // Inferred role: distance; original member name unknown.
  };

  struct CompareOrder {
    bool operator()(const OrderInfo &order, const OrderInfo &other) const { return order.unknown04 < other.unknown04; }
  };

  // Inferred role: locator group; original type name unknown.
  struct unknown001 {
    mm::mtl::Vector<GfFieldLocator> unknown00;                    // Inferred role: locators; original member name unknown.
    u32 unknown28;                                                // Inferred role: data num; original member name unknown.
    u32 unknown2c;                                                // Inferred role: number of locators already added to the compass; original member name unknown.
    mm::mtl::FixedVector<OrderInfo, ORDER_UNKNOWN_128> unknown30; // Inferred role: orders; original member name unknown.
  };

  GfMenuLocation(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  void updateDataNum(u32 type);
  void refreshLocatorFromQuest(u32 index, u32 type);
  static bool isInitialized();
  static void refreshLocator(u32 type);
  static void updateLocator();
  static void postUpdate(const fw::UpdateInfo &info);
  static u32 convIcon(u32 type);
  static u32 getLocatorDataNum(u32 type);

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u8 _09[0x10 - 0x09];
  unknown001 unknown10[LOCATOR_TYPE_UNKNOWN_4]; // Inferred role: groups; original member name unknown.
  u32 unknown10f0;                              // Role and original member name unknown.
};

static_assert(sizeof(GfMenuLocation::OrderInfo) == 0x8, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuLocation::unknown001) == 0x438, "");
static_assert(offsetof(GfMenuLocation, unknown10) == 0x10, "");

} // namespace gf
