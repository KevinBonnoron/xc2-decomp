#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Binding;
struct QsTransform;

class AnimationObject : public ReferenceObject {
public:
  ~AnimationObject() override {}
};

class Animation : public AnimationObject {
public:
  virtual s32 getImplType() const = 0;
  virtual void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const = 0;
  virtual void getExtractMotion(f32 time, QsTransform *transform) const;
  virtual void getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const;

  const char *m_name;
  u8 _20[0x22 - 0x20];
  u8 m_playMode;
  u8 m_blendHint;
  f32 m_fps;
  f32 m_invFps;
  u32 m_frameCount;
  u8 _30[0x40 - 0x30];
  const void *m_pLocomotion;
};

static_assert(offsetof(Animation, m_name) == 0x18, "");
static_assert(offsetof(Animation, m_frameCount) == 0x2c, "");
static_assert(offsetof(Animation, m_pLocomotion) == 0x40, "");

} // namespace anm
