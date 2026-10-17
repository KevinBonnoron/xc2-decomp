#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace ml {
class DrFogMan;
class DrLightMan;
class DrMan;

class DrEnvironmentObj {
public:
  enum Flag {
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

  DrEnvironmentObj *m_prev;
  DrEnvironmentObj *m_next;
  DrMan *m_drMan;
  DrLightMan *m_lightMan;
  DrFogMan *m_fogMan;
  mm::Mat44 m_matrix;
  const void *_70;
  int _78;
  u8 _7c[0x80 - 0x7c];
  f32 m_frame;
  f32 m_frameSpd;
  f32 m_maxFrame;
  u32 m_flags;
  u32 _90;
};

static_assert(offsetof(DrEnvironmentObj, m_drMan) == 0x18, "");
static_assert(offsetof(DrEnvironmentObj, m_matrix) == 0x30, "");
static_assert(offsetof(DrEnvironmentObj, _70) == 0x70, "");
static_assert(offsetof(DrEnvironmentObj, m_frame) == 0x80, "");
static_assert(offsetof(DrEnvironmentObj, m_flags) == 0x8c, "");

} // namespace ml
