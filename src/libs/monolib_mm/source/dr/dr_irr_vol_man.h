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
  // Inferred role: sector area; original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: min x; original member name unknown.
    u8 _04[0x08 - 0x04];
    f32 unknown08; // Inferred role: min z; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    f32 unknown10; // Inferred role: max x; original member name unknown.
    u8 _14[0x18 - 0x14];
    f32 unknown18; // Inferred role: max z; original member name unknown.
    u8 _1c[0x24 - 0x1c];
    f32 unknown24; // Inferred role: sector size; original member name unknown.
    u8 _28[0x30 - 0x28];
  };

  u8 _00[0x20 - 0x00];
  u32 unknown20; // Inferred role: cascade max; original member name unknown.
  u8 _24[0x28 - 0x24];
  unknown001 *unknown28; // Inferred role: sector areas; original member name unknown.
};

static_assert(sizeof(DrIrrVolSetting::unknown001) == 0x30, "");
static_assert(offsetof(DrIrrVolSetting::unknown001, unknown24) == 0x24, "");
static_assert(offsetof(DrIrrVolSetting, unknown28) == 0x28, "");

static_assert(offsetof(DrIrrVolSetting, unknown20) == 0x20, "");

class DrIrrVolMan {
public:
  bool isValid() const;
  void tail();
  void update();
  void createResources();
  void updateIrrVol(bool);
  int getSectorMax(u32 index) const;
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
  u8 _0a0[0x0b4 - 0x0a0];
  u32 unknown0b4; // Inferred role: double buffer flag; original member name unknown.
  u8 _0b8[0x190 - 0x0b8];
  mm::Vec3 unknown190; // Inferred role: request center pos; original member name unknown.
  mm::Vec3 unknown1a0; // Inferred role: center pos; original member name unknown.
  u32 unknown1b0;      // Inferred role: request value; original member name unknown.
  u32 unknown1b4;      // Inferred role: value; original member name unknown.
  u32 unknown1b8;      // Inferred role: request value; original member name unknown.
  u32 unknown1bc;      // Inferred role: value; original member name unknown.
  u32 unknown1c0;      // Inferred role: request cascade num; original member name unknown.
  u32 unknown1c4;      // Inferred role: cascade num; original member name unknown.
};

static_assert(offsetof(DrIrrVolMan, unknown08) == 0x008, "");
static_assert(offsetof(DrIrrVolMan, unknown98) == 0x098, "");
static_assert(offsetof(DrIrrVolMan, unknown0b4) == 0x0b4, "");
static_assert(offsetof(DrIrrVolMan, unknown190) == 0x190, "");
static_assert(offsetof(DrIrrVolMan, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrIrrVolMan, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrIrrVolMan, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrIrrVolMan, unknown1c4) == 0x1c4, "");

} // namespace ml
