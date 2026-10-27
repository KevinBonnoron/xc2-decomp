#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace fw {

struct ResAction {
  const char *unknown00; // Inferred role: name; original member name unknown.
  u8 _08[0x18 - 0x08];
};

static_assert(sizeof(ResAction) == 0x18, "");

class PadResEvent : public anm::ReferenceObject {
public:
  const ResAction *unknown18; // Inferred role: actions; original member name unknown.
  u32 unknown20;              // Inferred role: action count; original member name unknown.
};

static_assert(offsetof(PadResEvent, unknown18) == 0x18, "");
static_assert(offsetof(PadResEvent, unknown20) == 0x20, "");

const ResAction *findAction(const PadResEvent *event, const char *name);

} // namespace fw
