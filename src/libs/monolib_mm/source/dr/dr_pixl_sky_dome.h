#pragma once

#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Vec4;
} // namespace mm

namespace ml {

class DrMan;
class DrResUseQueryObj;

class DrPixlSkyDome {
public:
  DrPixlSkyDome(DrMan *drMan);
  ~DrPixlSkyDome();
  void update();
  void luminanceRender();
  void baseRender();
  void godRayRender();
  void updateUniform();
  void renderColorBackground(const mm::Vec4 &color);
  void renderBackgroundCube();

  DrMan *m_drMan;                       // Inferred role: dr man; original member name unknown.
  DrResUseQueryObj *m_drResUseQueryObj; // Inferred role: occlusion query; original member name unknown.
  f32 unknown10;                        // Inferred role: sky visibility; original member name unknown.
  s32 unknown14;                        // Inferred role: visibility reset frames; original member name unknown.
  u8 _18[0x20 - 0x18];
  mm::Vec3 unknown20; // Inferred role: set by the constructor only; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: set by the constructor only; original member name unknown.
  f32 unknown40;      // Inferred role: set by the constructor only; original member name unknown.
  s32 unknown44;      // Inferred role: set by the constructor only; original member name unknown.
  s32 unknown48;      // Inferred role: set by the constructor only; original member name unknown.
};

static_assert(offsetof(DrPixlSkyDome, m_drMan) == 0x00, "");
static_assert(offsetof(DrPixlSkyDome, m_drResUseQueryObj) == 0x08, "");
static_assert(offsetof(DrPixlSkyDome, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlSkyDome, unknown14) == 0x14, "");
static_assert(offsetof(DrPixlSkyDome, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlSkyDome, unknown30) == 0x30, "");
static_assert(offsetof(DrPixlSkyDome, unknown40) == 0x40, "");
static_assert(offsetof(DrPixlSkyDome, unknown48) == 0x48, "");

} // namespace ml
