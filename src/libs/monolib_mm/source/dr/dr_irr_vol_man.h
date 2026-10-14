#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Aabb;
} // namespace mm

namespace ml {

struct DrIrrVolSetting {
  u8 _00[0x20 - 0x00];
  u32 cascadeMax;
};

static_assert(offsetof(DrIrrVolSetting, cascadeMax) == 0x20, "");

class DrIrrVolMan {
public:
  bool isValid() const;
  bool getVolumeArea(u32 cascade, mm::Aabb &area) const;

  u8 _000[0x008 - 0x000];
  DrIrrVolSetting *setting;
  u8 _010[0x190 - 0x010];
  mm::Vec3 requestCenterPos;
  mm::Vec3 centerPos;
  u8 _1b0[0x1c4 - 0x1b0];
  u32 cascadeNum;
};

static_assert(offsetof(DrIrrVolMan, setting) == 0x008, "");
static_assert(offsetof(DrIrrVolMan, requestCenterPos) == 0x190, "");
static_assert(offsetof(DrIrrVolMan, centerPos) == 0x1a0, "");
static_assert(offsetof(DrIrrVolMan, cascadeNum) == 0x1c4, "");

} // namespace ml
