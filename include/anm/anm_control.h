#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Binding;
struct Annotetion;
struct QsTransform;

// Inferred receiver of the annotations of an animation; original name unknown.
class unknown003 {
public:
  virtual void unknown00(const Annotetion *annotation) = 0;
};

class Control : public ReferenceObject {
public:
  Control(const Binding *pBinding, mm::mtl::IAllocator *pAllocator);
  ~Control() override;
  void update(f32 deltaTime);
  void procAnnotetionCallBack(f32 time, f32 deltaTime, bool includeStart);
  f32 calcLocalTimeInternal(f32 time);
  void sampleTrucks(u32 count, QsTransform *transforms) const;
  bool sampleExtraTrucks(u16 slot, u32 count, f32 *values);
  void getDeltaExtractMotion(f32 time, QsTransform *transform) const;
  const char *getName() const;

  void setLocalTime(f32 time) {
    unknown48 = calcLocalTimeInternal(time);
    unknown58 |= 1;
  }

  const Binding *m_pBinding;
  mm::mtl::Vector<f32> unknown20; // Inferred role: bone weights (0 where the binding index is -1); original member name unknown.
  f32 unknown48;                  // Inferred role: local time; original member name unknown.
  f32 unknown4c;                  // Inferred role: weight; original member name unknown.
  f32 unknown50;                  // Inferred role: speed; original member name unknown.
  f32 unknown54;                  // Inferred role: playback time; original member name unknown.
  u32 unknown58;                  // Inferred role: flags; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  unknown003 *unknown60; // Inferred role: annotation callback receiver; original member name unknown.
};

static_assert(offsetof(Control, m_pBinding) == 0x18, "");
static_assert(offsetof(Control, unknown20) == 0x20, "");
static_assert(offsetof(Control, unknown48) == 0x48, "");
static_assert(offsetof(Control, unknown54) == 0x54, "");
static_assert(offsetof(Control, unknown58) == 0x58, "");
static_assert(offsetof(Control, unknown60) == 0x60, "");
static_assert(sizeof(Control) == 0x68, "");

} // namespace anm
