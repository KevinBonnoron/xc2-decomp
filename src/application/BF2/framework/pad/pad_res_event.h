#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "fw/fw_pad.h"
#include "types.h"

namespace fw {

struct ResAction {
  // Inferred role: key of an action; original type name unknown.
  struct unknown001 {
    u32 unknown00;
    PadActKey unknown04; // Inferred role: pad key; original member name unknown. Typed by getPadKey(PadActKey), which getFwPadKey passes it to.
  };

  const unknown001 *unknown00; // Inferred role: keys; original member name unknown.
  u32 unknown08;               // Inferred role: key count; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(ResAction::unknown001, unknown04) == 0x04, "");
static_assert(sizeof(ResAction::unknown001) == 0x08, "");
static_assert(offsetof(ResAction, unknown08) == 0x08, "");
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
