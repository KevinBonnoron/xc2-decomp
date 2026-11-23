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
  int getSectorResourceIndex(int x, int z) const;
  DrIrrVolResObj *getSectorResource(int x, int z) const;
  DrIrrVolSector *getSectorInstance(int x, int z) const;

  const SGlobalInfo *m_sGlobalInfo;   // Inferred role: global info; original member name unknown.
  const SCascadeInfo *m_sCascadeInfo; // Inferred role: info of this cascade; original member name unknown.
  u32 unknown10;                      // Inferred role: cascade index; original member name unknown.
  u8 _014[0x018 - 0x014];
  DrIrrVolResMan *m_drIrrVolResMan; // Inferred role: sector resource manager; original member name unknown.
  DrIrrVolSector *unknown20[81];    // Inferred role: sector instances of the 9 x 9 grid; original member name unknown.
  DrIrrVolResObj *unknown2a8[81];   // Inferred role: sector resources of the 9 x 9 grid; original member name unknown.
  // Layout evidence: getSectorResourceIndex (1.0.0: 0x71007eaf30) tests the sector coordinates against 4 around the two ints.
  int unknown530; // Inferred role: center sector along x; original member name unknown.
  int unknown534; // Inferred role: center sector along z; original member name unknown.
  u8 _538[0x548 - 0x538];
  int unknown548; // Inferred role: sector count along x, compared signed by getSectorResourceIndex; original member name unknown.
  int unknown54c; // Inferred role: sector count along z, compared signed by getSectorResourceIndex; original member name unknown.
  u8 _550[0x560 - 0x550];
  mm::Aabb unknown560[2]; // Inferred role: volume area per buffer; original member name unknown.
  u8 _5a0[0x5b0 - 0x5a0];
  mm::Vec3 m_uVPerPixl; // Inferred role: uv per pixel; named after the game accessor ml::DrIrrVolMan::getUVPerPixl.
  u8 _5c0[0x5d0 - 0x5c0];
  mm::Vec3 m_irrVolUVScale; // Inferred role: uv scale; named after the game accessor ml::DrIrrVolMan::getIrrVolUVScale.
  u32 unknown5e0;           // Inferred role: current buffer index; original member name unknown.
  u8 _5e4[0x5e8 - 0x5e4];
  grlib::CGLibTextureBuffer unknown5e8[2][3]; // Inferred role: irradiance volume textures per buffer; original member name unknown.
  u8 _888[0x890 - 0x888];
  int *unknown890; // Inferred role: buffer of 4 byte entries that createResources allocates and fills with -1; original member name unknown.
  u8 _898[0x8e0 - 0x898];
  mm::Vec3 m_irrVolEyeOffset; // Inferred role: eye offset; named after the game accessor ml::DrIrrVolMan::getIrrVolEyeOffset.
  mm::Vec3 m_irrVolUVOffset;  // Inferred role: uv offset; named after the game accessor ml::DrIrrVolMan::getIrrVolUVOffset.
};

static_assert(offsetof(DrIrrVolCascade, m_sCascadeInfo) == 0x08, "");
static_assert(offsetof(DrIrrVolCascade, unknown10) == 0x10, "");

static_assert(offsetof(DrIrrVolCascade, m_drIrrVolResMan) == 0x18, "");
static_assert(offsetof(DrIrrVolCascade, unknown20) == 0x20, "");
static_assert(offsetof(DrIrrVolCascade, unknown2a8) == 0x2a8, "");
static_assert(offsetof(DrIrrVolCascade, unknown530) == 0x530, "");
static_assert(offsetof(DrIrrVolCascade, unknown534) == 0x534, "");
static_assert(offsetof(DrIrrVolCascade, unknown548) == 0x548, "");
static_assert(offsetof(DrIrrVolCascade, unknown54c) == 0x54c, "");

static_assert(offsetof(DrIrrVolCascade, unknown560) == 0x560, "");
static_assert(offsetof(DrIrrVolCascade, m_uVPerPixl) == 0x5b0, "");
static_assert(offsetof(DrIrrVolCascade, m_irrVolUVScale) == 0x5d0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e0) == 0x5e0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e8) == 0x5e8, "");
static_assert(offsetof(DrIrrVolCascade, unknown890) == 0x890, "");
static_assert(offsetof(DrIrrVolCascade, m_irrVolEyeOffset) == 0x8e0, "");
static_assert(offsetof(DrIrrVolCascade, m_irrVolUVOffset) == 0x8f0, "");

} // namespace irrvol
} // namespace ml
