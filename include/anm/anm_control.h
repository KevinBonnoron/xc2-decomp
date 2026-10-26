#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Binding;
struct QsTransform;

class Control : public ReferenceObject {
public:
  void update(f32 deltaTime);
  f32 calcLocalTimeInternal(f32 time);
  void sampleTrucks(u32 count, QsTransform *transforms) const;
  void sampleExtraTrucks(u16 slot, u32 count, f32 *values);

  void setLocalTime(f32 time) {
    unknown48 = calcLocalTimeInternal(time);
    unknown58 |= 1;
  }

  const Binding *m_pBinding;
  u8 _20[0x48 - 0x20];
  f32 unknown48; // Inferred role: local time; original member name unknown.
  f32 unknown4c; // Inferred role: weight; original member name unknown.
  f32 unknown50; // Inferred role: speed; original member name unknown.
  u8 _54[0x58 - 0x54];
  u32 unknown58; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(Control, m_pBinding) == 0x18, "");
static_assert(offsetof(Control, unknown48) == 0x48, "");
static_assert(offsetof(Control, unknown58) == 0x58, "");

} // namespace anm
