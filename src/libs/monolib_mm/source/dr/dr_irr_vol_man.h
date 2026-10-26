#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Aabb;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

namespace irrvol {
class DrIrrVolCascade;
} // namespace irrvol

struct DrIrrVolSetting {
  u8 _00[0x20 - 0x00];
  u32 unknown20; // Inferred role: cascade max; original member name unknown.
};

static_assert(offsetof(DrIrrVolSetting, unknown20) == 0x20, "");

class DrIrrVolMan {
public:
  bool isValid() const;
  void getVolumeArea(u32 cascade, mm::Aabb &area) const;
  void debugRender();
  grlib::CGLibTextureBuffer *getIrrVolTex(u32 cascade, u32 index) const;
  const mm::Vec3 &getIrrVolUVScale(u32 cascade) const;
  const mm::Vec3 &getUVPerPixl(u32 cascade) const;
  const mm::Vec3 &getIrrVolEyeOffset(u32 cascade) const;
  const mm::Vec3 &getIrrVolUVOffset(u32 cascade) const;

  u8 _000[0x008 - 0x000];
  DrIrrVolSetting *unknown08; // Inferred role: setting; original member name unknown.
  u8 _010[0x098 - 0x010];
  irrvol::DrIrrVolCascade **unknown98; // Inferred role: cascades; original member name unknown.
  u8 _0a0[0x190 - 0x0a0];
  mm::Vec3 unknown190; // Inferred role: request center pos; original member name unknown.
  mm::Vec3 unknown1a0; // Inferred role: center pos; original member name unknown.
  u8 _1b0[0x1c4 - 0x1b0];
  u32 unknown1c4; // Inferred role: cascade num; original member name unknown.
};

static_assert(offsetof(DrIrrVolMan, unknown08) == 0x008, "");
static_assert(offsetof(DrIrrVolMan, unknown98) == 0x098, "");
static_assert(offsetof(DrIrrVolMan, unknown190) == 0x190, "");
static_assert(offsetof(DrIrrVolMan, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrIrrVolMan, unknown1c4) == 0x1c4, "");

} // namespace ml
