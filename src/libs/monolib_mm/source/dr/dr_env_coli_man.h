#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

struct DrEnvColiResult {
  s32 bgmId;
  s32 layerId;
  s32 reverbId;
  s32 caveId;
  s32 areaId;
  u8 _14[0x18 - 0x14];
  s32 windId;
  u8 : 2;
  u8 isRoom : 1;
};

static_assert(offsetof(DrEnvColiResult, windId) == 0x18, "");

class DrEnvColiMan {
public:
  bool testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius);

  u8 _00[0x48 - 0x00];
  DrEnvColiResult m_result;
};

static_assert(offsetof(DrEnvColiMan, m_result) == 0x48, "");

} // namespace ml
