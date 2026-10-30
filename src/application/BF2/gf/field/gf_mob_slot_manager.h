#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/map.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SLOT_HANDLE;

class GfMobSlotManager {
public:
  // Inferred role: mob near the interest position with its squared distance; original type name unknown.
  struct unknown001 {
    GF_OBJ_HANDLE *unknown00; // Inferred role: mob handle; original member name unknown.
    f32 unknown08;            // Inferred role: squared distance to the interest position; original member name unknown.
  };

  GfMobSlotManager();
  ~GfMobSlotManager() { disposeMobInfos(); }
  bool addFailedPopDistSq(f32 distSq);
  void update();
  void disposeMobInfos();

  mm::mtl::FixedVector<unknown001, 64> unknown000; // Inferred role: mob infos; original member name unknown.
  mm::mtl::Map<GF_SLOT_HANDLE *, f32> unknown408;  // Inferred role: slot distances; original member name unknown.
  mm::mtl::FixedVector<f32, 64> unknown420;        // Inferred role: failed pop squared distances; original member name unknown.
  f32 unknown528;                                  // Inferred role: squared mob pop distance; original member name unknown.
};

static_assert(sizeof(GfMobSlotManager::unknown001) == 0x10, "");
static_assert(offsetof(GfMobSlotManager, unknown408) == 0x408, "");
static_assert(offsetof(GfMobSlotManager, unknown420) == 0x420, "");
static_assert(offsetof(GfMobSlotManager, unknown528) == 0x528, "");
static_assert(sizeof(GfMobSlotManager) == 0x530, "");

} // namespace gf
