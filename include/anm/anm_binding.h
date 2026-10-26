#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Animation;

struct ExtraBinding {
  u8 _00[0x10 - 0x00];
  u32 unknown10; // Inferred role: truck count; original member name unknown.
  u8 _14[0x18 - 0x14];
};

static_assert(offsetof(ExtraBinding, unknown10) == 0x10, "");
static_assert(sizeof(ExtraBinding) == 0x18, "");

class Binding : public ReferenceObject {
public:
  ~Binding() override;

  const Animation *m_pAnimation;
  u8 _20[0x28 - 0x20];
  u32 unknown28;                 // Inferred role: bone count; original member name unknown.
  Array<ExtraBinding> unknown30; // Inferred role: extra bindings; original member name unknown.
};

static_assert(offsetof(Binding, m_pAnimation) == 0x18, "");
static_assert(offsetof(Binding, unknown28) == 0x28, "");
static_assert(offsetof(Binding, unknown30) == 0x30, "");

} // namespace anm
