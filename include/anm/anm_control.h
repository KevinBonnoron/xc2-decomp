#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Binding;

class Control : public ReferenceObject {
public:
  void update(f32 deltaTime);
  f32 calcLocalTimeInternal(f32 time);

  void setLocalTime(f32 time) {
    m_localTime = calcLocalTimeInternal(time);
    m_flags |= 1;
  }

  const Binding *m_pBinding;
  u8 _20[0x48 - 0x20];
  f32 m_localTime;
  f32 m_weight;
  f32 m_speed;
  u8 _54[0x58 - 0x54];
  u32 m_flags;
};

static_assert(offsetof(Control, m_pBinding) == 0x18, "");
static_assert(offsetof(Control, m_localTime) == 0x48, "");
static_assert(offsetof(Control, m_flags) == 0x58, "");

} // namespace anm
