#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcClipMan;

class DrResWrkClipList {
public:
  // Inferred role: clip list resource header; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: offset of the clip list; original member name unknown.
    s32 unknown04; // Inferred role: clip count; original member name unknown.
  };
  // Inferred role: entry of the clip list (unknown10 of them, at unknown08), pointing at its clip records; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: offset of the clip records from unknown00 of the list; original member name unknown.
    s32 unknown04; // Inferred role: clip record count; original member name unknown.
  };
  // Inferred role: clip record, read by DrResWrkClipList::update (1.0.0: 0x710088c944): the search of an entry stops at a record whose value is below the value of the last record with a set clip bit;
  // original type name unknown.
  struct unknown003 {
    u16 unknown00; // Inferred role: index of the bit of the clip flags of DrCalcClipMan; original member name unknown.
    u16 unknown02; // Inferred role: kind, 1 marks the entry clipped while the bit is clear, 0 marks it clipped when the bit is set; original member name unknown.
    u16 unknown04; // Inferred role: value, ascending; original member name unknown.
    u16 _06;
  };
  static int calcWorkSize(const u8 *data, u32 offset);
  void changeMemCall(const u8 *data, u32 offset);
  int setupWork(u8 *work, const u8 *data, u32 offset);
  void update(DrCalcClipMan *clipMan);

  const u8 *unknown00;         // Inferred role: resource data; original member name unknown.
  const unknown002 *unknown08; // Inferred role: clip list; original member name unknown.
  s32 unknown10;               // Inferred role: clip count; original member name unknown.
  s32 unknown14;               // Inferred role: work size; original member name unknown.
  u32 *unknown18;              // Inferred role: clipped flag bits; original member name unknown.
};

static_assert(offsetof(DrResWrkClipList, unknown08) == 0x08, "");
static_assert(offsetof(DrResWrkClipList, unknown10) == 0x10, "");
static_assert(offsetof(DrResWrkClipList, unknown14) == 0x14, "");
static_assert(offsetof(DrResWrkClipList, unknown18) == 0x18, "");
static_assert(sizeof(DrResWrkClipList::unknown002) == 0x08, "");
static_assert(offsetof(DrResWrkClipList::unknown003, unknown02) == 0x02, "");
static_assert(offsetof(DrResWrkClipList::unknown003, unknown04) == 0x04, "");
static_assert(sizeof(DrResWrkClipList::unknown003) == 0x08, "");
static_assert(sizeof(DrResWrkClipList::unknown001) == 0x08, "");

} // namespace ml
