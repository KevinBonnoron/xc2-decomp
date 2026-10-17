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
    FLAG_DISP_OFF = 1 << 0,
    FLAG_GROUP = 1 << 2,
    FLAG_OFS_MATRIX = 1 << 3,
    FLAG_DEBUG_DISP_2D = 1 << 20,
    FLAG_RELEASE = 1 << 30,
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

  DrEnvironmentObj *m_prev;
  DrEnvironmentObj *m_next;
  DrMan *m_drMan;
  DrLightMan *m_lightMan;
  DrFogMan *m_fogMan;
  mm::Mat44 m_matrix;
  mm::Vec3 m_offsetPos;
  f32 m_frame;
  f32 m_frameSpd;
  f32 m_maxFrame;
  u32 m_flags;
  int m_group;
};

static_assert(offsetof(DrEnvironmentObj, m_drMan) == 0x18, "");
static_assert(offsetof(DrEnvironmentObj, m_matrix) == 0x30, "");
static_assert(offsetof(DrEnvironmentObj, m_offsetPos) == 0x70, "");
static_assert(offsetof(DrEnvironmentObj, m_frame) == 0x80, "");
static_assert(offsetof(DrEnvironmentObj, m_flags) == 0x8c, "");

} // namespace ml
