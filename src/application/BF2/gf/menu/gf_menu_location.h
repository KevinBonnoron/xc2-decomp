#pragma once
#include <stddef.h>

#include "gf/field/gf_field_locator.h"
#include "mm_math/mm_vec3.h"
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

  // Name from the symbol of getLocatorData; the members were read from GfMenuObjCompass::update (0x71004414c8).
  struct LocatorData {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    u8 _10[0x14 - 0x10];
    int unknown14;  // Inferred role: icon id; original member name unknown.
    bool unknown18; // Inferred role: locator is on another map; original member name unknown.
    int unknown1c;  // Inferred role: map id; original member name unknown.
    int unknown20;  // Inferred role: distance; original member name unknown.
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
  static bool getLocatorData(u32 type, u32 index, LocatorData &data, u32, bool);

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u8 _09[0x10 - 0x09];
  unknown001 unknown10[LOCATOR_TYPE_UNKNOWN_4]; // Inferred role: groups; original member name unknown.
  u32 unknown10f0;                              // Role and original member name unknown.
};

static_assert(sizeof(GfMenuLocation::OrderInfo) == 0x8, "");
static_assert(offsetof(GfMenuLocation::LocatorData, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuLocation::LocatorData, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuLocation::LocatorData, unknown1c) == 0x1c, "");
static_assert(offsetof(GfMenuLocation::LocatorData, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuLocation::unknown001, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuLocation::unknown001) == 0x438, "");
static_assert(offsetof(GfMenuLocation, unknown10) == 0x10, "");

} // namespace gf
