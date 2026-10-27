#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResWrkClipList {
public:
  // Inferred role: clip list resource header; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: offset of the clip list; original member name unknown.
    s32 unknown04; // Inferred role: clip count; original member name unknown.
  };

  static int calcWorkSize(const u8 *data, u32 offset);
  void changeMemCall(const u8 *data, u32 offset);
  int setupWork(u8 *work, const u8 *data, u32 offset);

  const u8 *unknown00; // Inferred role: resource data; original member name unknown.
  const u8 *unknown08; // Inferred role: clip list; original member name unknown.
  s32 unknown10;       // Inferred role: clip count; original member name unknown.
  s32 unknown14;       // Inferred role: work size; original member name unknown.
  u8 *unknown18;       // Inferred role: work; original member name unknown.
};

static_assert(offsetof(DrResWrkClipList, unknown08) == 0x08, "");
static_assert(offsetof(DrResWrkClipList, unknown10) == 0x10, "");
static_assert(offsetof(DrResWrkClipList, unknown14) == 0x14, "");
static_assert(offsetof(DrResWrkClipList, unknown18) == 0x18, "");
static_assert(sizeof(DrResWrkClipList::unknown001) == 0x08, "");

} // namespace ml
