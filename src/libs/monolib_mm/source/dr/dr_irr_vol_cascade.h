#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibAcc3DTexture;
} // namespace grlib

namespace ml {
class DebDraw;

namespace irrvol {
class DrIrrVolResMan;
class DrIrrVolResObj;
class DrIrrVolSector;
struct SCascadeInfo;
struct SGlobalInfo;
struct SHTerms;

class DrIrrVolCascade {
public:
  DrIrrVolCascade(const SGlobalInfo *globalInfo, u32 index, const char *name);
  ~DrIrrVolCascade();
  void createSector(void *buffer, u32 index);
  void updateIrrVolByGlobalProbe(u32 x, u32 y, u32 z, u32 index, const SHTerms &terms, grlib::CGLibAcc3DTexture &texture);
  void drawDebugInfo(DebDraw *debDraw);

  const SGlobalInfo *unknown00;  // Inferred role: global info; original member name unknown.
  const SCascadeInfo *unknown08; // Inferred role: info of this cascade; original member name unknown.
  u32 unknown10;                 // Inferred role: cascade index; original member name unknown.
  u8 _014[0x018 - 0x014];
  DrIrrVolResMan *unknown18;      // Inferred role: sector resource manager; original member name unknown.
  DrIrrVolSector *unknown20[81];  // Inferred role: sector instances of the 9 x 9 grid; original member name unknown.
  DrIrrVolResObj *unknown2a8[81]; // Inferred role: sector resources of the 9 x 9 grid; original member name unknown.
  u8 _530[0x548 - 0x530];
  int unknown548; // Inferred role: sector count along x, compared signed by getSectorResourceIndex; original member name unknown.
  int unknown54c; // Inferred role: sector count along z, compared signed by getSectorResourceIndex; original member name unknown.
  u8 _550[0x560 - 0x550];
  mm::Aabb unknown560[2]; // Inferred role: volume area per buffer; original member name unknown.
  u8 _5a0[0x5b0 - 0x5a0];
  mm::Vec3 unknown5b0; // Inferred role: uv per pixel; original member name unknown.
  u8 _5c0[0x5d0 - 0x5c0];
  mm::Vec3 unknown5d0; // Inferred role: uv scale; original member name unknown.
  u32 unknown5e0;      // Inferred role: current buffer index; original member name unknown.
  u8 _5e4[0x5e8 - 0x5e4];
  grlib::CGLibTextureBuffer unknown5e8[2][3]; // Inferred role: irradiance volume textures per buffer; original member name unknown.
  u8 _888[0x890 - 0x888];
  int *unknown890; // Inferred role: buffer of 4 byte entries that createResources allocates and fills with -1; original member name unknown.
  u8 _898[0x8e0 - 0x898];
  mm::Vec3 unknown8e0; // Inferred role: eye offset; original member name unknown.
  mm::Vec3 unknown8f0; // Inferred role: uv offset; original member name unknown.
};

static_assert(offsetof(DrIrrVolCascade, unknown08) == 0x08, "");
static_assert(offsetof(DrIrrVolCascade, unknown10) == 0x10, "");

static_assert(offsetof(DrIrrVolCascade, unknown18) == 0x18, "");
static_assert(offsetof(DrIrrVolCascade, unknown20) == 0x20, "");
static_assert(offsetof(DrIrrVolCascade, unknown2a8) == 0x2a8, "");
static_assert(offsetof(DrIrrVolCascade, unknown548) == 0x548, "");
static_assert(offsetof(DrIrrVolCascade, unknown54c) == 0x54c, "");

static_assert(offsetof(DrIrrVolCascade, unknown560) == 0x560, "");
static_assert(offsetof(DrIrrVolCascade, unknown5b0) == 0x5b0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5d0) == 0x5d0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e0) == 0x5e0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e8) == 0x5e8, "");
static_assert(offsetof(DrIrrVolCascade, unknown890) == 0x890, "");
static_assert(offsetof(DrIrrVolCascade, unknown8e0) == 0x8e0, "");
static_assert(offsetof(DrIrrVolCascade, unknown8f0) == 0x8f0, "");

} // namespace irrvol
} // namespace ml
