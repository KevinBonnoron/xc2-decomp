#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrFogMan;
class DrLightMan;
class DrMan;

class DrEnvironmentObj {
public:
  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,   // Inferred role: disp off; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: zone object; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,   // Inferred role: group; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,   // Inferred role: ofs matrix; original name unknown.
    FLAG_UNKNOWN_20 = 1 << 20, // Inferred role: debug disp 2d; original name unknown.
    FLAG_UNKNOWN_30 = 1 << 30, // Inferred role: release; original name unknown.
  };

  void release();
  DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan);
  f32 getFrame() const;
  f32 getMaxFrame() const;
  void setFrameSpd(f32 speed);
  f32 getFrameSpd();
  virtual ~DrEnvironmentObj() {}
  virtual void resourceInit() {}
  virtual void update() {}
  virtual void renderLgt() {}
  virtual void debugRenderLgt() {}
  virtual void debugRenderLgt2D() {}
  virtual void setFrame(f32 frame) = 0;
  virtual void changeMemCall(const void *data) = 0;

  void setMatrix(const mm::Mat44 &matrix) { m_matrix = matrix; }

  DrEnvironmentObj *unknown08; // Inferred role: prev; original member name unknown.
  DrEnvironmentObj *unknown10; // Inferred role: next; original member name unknown.
  DrMan *unknown18;            // Inferred role: dr man; original member name unknown.
  DrLightMan *unknown20;       // Inferred role: light man; original member name unknown.
  DrFogMan *unknown28;         // Inferred role: fog man; original member name unknown.
  mm::Mat44 m_matrix;
  mm::Vec3 unknown70; // Inferred role: offset pos; original member name unknown.
  f32 m_frame;
  f32 m_frameSpd;
  f32 m_maxFrame;
  u32 unknown8c; // Inferred role: flags; original member name unknown.
  int unknown90; // Inferred role: group; original member name unknown.
};

static_assert(offsetof(DrEnvironmentObj, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvironmentObj, m_matrix) == 0x30, "");
static_assert(offsetof(DrEnvironmentObj, unknown70) == 0x70, "");
static_assert(offsetof(DrEnvironmentObj, m_frame) == 0x80, "");
static_assert(offsetof(DrEnvironmentObj, unknown8c) == 0x8c, "");

} // namespace ml
