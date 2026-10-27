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
  explicit Animation(mm::mtl::IAllocator *pAllocator)
      : AnimationObject(pAllocator), unknown18(nullptr), unknown21(0), unknown22(0), unknown23(0), unknown24(0.0f), unknown28(0.0f), unknown2c(0), unknown40(nullptr) {}
  explicit Animation(const SerialiseArg &arg) : AnimationObject(arg) {}
  virtual s32 getImplType() const = 0;
  virtual void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const = 0;

  virtual bool getExtractMotion(f32 time, QsTransform *transform) const {
    if (unknown40 == nullptr) {
      return false;
    }
    unknown40->getReference(time, transform);
    return true;
  }

  virtual bool getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const {
    if (unknown40 == nullptr) {
      return false;
    }
    unknown40->getDeltaReference(previousTime, time, 0.0f, unknown28 * (unknown2c - 1), looped, transform);
    return true;
  }

  const char *unknown18; // Inferred role: name; original member name unknown.
  s8 unknown20;          // Inferred role: impl type tag; original member name unknown.
  u8 unknown21;          // Inferred role: unknown; original member name unknown.
  u8 unknown22;          // Inferred role: play mode; original member name unknown.
  u8 unknown23;          // Inferred role: blend hint; original member name unknown.
  f32 unknown24;         // Inferred role: fps; original member name unknown.
  f32 unknown28;         // Inferred role: inv fps; original member name unknown.
  u32 unknown2c;         // Inferred role: frame count; original member name unknown.
  const void *unknown30; // Inferred role: p annotations; original member name unknown.
  u32 unknown38;         // Inferred role: annotation num; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  const Locomotion *unknown40; // Inferred role: p locomotion; original member name unknown.
};

static_assert(offsetof(Animation, unknown18) == 0x18, "");
static_assert(offsetof(Animation, unknown20) == 0x20, "");
static_assert(offsetof(Animation, unknown30) == 0x30, "");
static_assert(offsetof(Animation, unknown38) == 0x38, "");
static_assert(offsetof(Animation, unknown2c) == 0x2c, "");
static_assert(offsetof(Animation, unknown40) == 0x40, "");

} // namespace anm
