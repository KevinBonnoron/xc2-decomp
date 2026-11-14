#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace fw {

struct ResAction {
  u8 _00[0x10];
};

static_assert(sizeof(ResAction) == 0x10, "");

struct ResActionInfo {
  const char *unknown00;      // Inferred role: name; original member name unknown.
  const ResAction *unknown08; // Inferred role: alternative actions; original member name unknown.
  u32 unknown10;              // Inferred role: action count; original member name unknown.
};

static_assert(offsetof(ResActionInfo, unknown08) == 0x08, "");
static_assert(offsetof(ResActionInfo, unknown10) == 0x10, "");
static_assert(sizeof(ResActionInfo) == 0x18, "");

struct ResAxisInfo {
  const char *unknown00; // Inferred role: name; original member name unknown.
  u32 unknown08;         // Inferred role: stick axis index; original member name unknown.
  f32 unknown0c;         // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(ResAxisInfo, unknown08) == 0x08, "");
static_assert(offsetof(ResAxisInfo, unknown0c) == 0x0c, "");
static_assert(sizeof(ResAxisInfo) == 0x10, "");

class PadResEvent : public anm::ReferenceObject {
public:
  const ResActionInfo *unknown18; // Inferred role: actions; original member name unknown.
  u32 unknown20;                  // Inferred role: action count; original member name unknown.
  const ResAxisInfo *unknown28;   // Inferred role: axes; original member name unknown.
  u32 unknown30;                  // Inferred role: axis count; original member name unknown.
};

static_assert(offsetof(PadResEvent, unknown18) == 0x18, "");
static_assert(offsetof(PadResEvent, unknown20) == 0x20, "");
static_assert(offsetof(PadResEvent, unknown28) == 0x28, "");
static_assert(offsetof(PadResEvent, unknown30) == 0x30, "");

class PadEventImporter {
public:
  static PadResEvent *create(void *data, const char *path);
};

const ResActionInfo *findAction(const PadResEvent *event, const char *name);

} // namespace fw
