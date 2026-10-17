#pragma once
#include <stddef.h>

#include "anm/anm_locomotion.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Binding;
struct QsTransform;
struct SerialiseArg;

class AnimationObject : public ReferenceObject {
public:
  explicit AnimationObject(mm::mtl::IAllocator *pAllocator) : ReferenceObject(pAllocator) {}
  explicit AnimationObject(const SerialiseArg &arg) : ReferenceObject(arg) {}
  ~AnimationObject() override {}
};

class Animation : public AnimationObject {
public:
  explicit Animation(const SerialiseArg &arg) : AnimationObject(arg) {}
  virtual s32 getImplType() const = 0;
  virtual void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const = 0;

  virtual bool getExtractMotion(f32 time, QsTransform *transform) const {
    if (m_pLocomotion == nullptr) {
      return false;
    }
    m_pLocomotion->getReference(time, transform);
    return true;
  }

  virtual bool getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const {
    if (m_pLocomotion == nullptr) {
      return false;
    }
    m_pLocomotion->getDeltaReference(previousTime, time, 0.0f, m_invFps * (m_frameCount - 1), looped, transform);
    return true;
  }

  const char *m_name;
  u8 _20[0x22 - 0x20];
  u8 m_playMode;
  u8 m_blendHint;
  f32 m_fps;
  f32 m_invFps;
  u32 m_frameCount;
  u8 _30[0x40 - 0x30];
  const Locomotion *m_pLocomotion;
};

static_assert(offsetof(Animation, m_name) == 0x18, "");
static_assert(offsetof(Animation, m_frameCount) == 0x2c, "");
static_assert(offsetof(Animation, m_pLocomotion) == 0x40, "");

} // namespace anm
