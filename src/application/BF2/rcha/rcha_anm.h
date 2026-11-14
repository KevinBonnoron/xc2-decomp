#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"
#include "types.h"

// Animation track of the Rcha resources. Declared from the symbols _ZNK7RchaAnm8getValueEf (0x710069ca9c) and
// _ZNK7RchaAnm11getValueIntEf (0x710069ca6c); RchaNode keeps 48 of them, which it constructs and destroys in loops
// (_ZN8RchaNodeC1Ev, _ZN8RchaNodeD2Ev). The fields between 0x5c and 0x70 are only cleared by that constructor.
class RchaAnm {
public:
  f32 getValue(f32 frame) const;
  int getValueInt(f32 frame) const;
  ~RchaAnm() { unknown001(); }

  // Inferred role: releases the buffer when it is owned, as the destructor, clear and setup of RchaNode do; original
  // name unknown.
  void unknown001() {
    unknown50 = 0;
    if (unknown58 != 0 && unknown48 != nullptr) {
      mtl::MemManager::deallocate(unknown48, 0, false);
      unknown48 = nullptr;
    }
    unknown48 = nullptr;
    unknown54 = 0;
    unknown58 = 0;
  }

  mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
  void *unknown48;               // Inferred role: buffer owned when unknown58 is set; original member name unknown.
  int unknown50;                 // Inferred role: set when unknown48 is the buffer read by getValue; original member name unknown.
  int unknown54;                 // Inferred role: cleared with the buffer; original member name unknown.
  int unknown58;                 // Inferred role: unknown48 is owned; original member name unknown.
  u8 _5c[0x70 - 0x5c];
  f32 unknown70;  // Inferred role: value of a constant track; original member name unknown.
  u32 unknown74;  // Inferred role: number of frames; original member name unknown.
  u32 *unknown78; // Inferred role: values of the frames in the resource; original member name unknown.
  bool unknown80; // Inferred role: values are compressed; original member name unknown.
  u32 unknown84;  // Inferred role: name hash; original member name unknown.
};

static_assert(offsetof(RchaAnm, unknown48) == 0x48, "");
static_assert(offsetof(RchaAnm, unknown50) == 0x50, "");
static_assert(offsetof(RchaAnm, unknown58) == 0x58, "");
static_assert(offsetof(RchaAnm, unknown70) == 0x70, "");
static_assert(offsetof(RchaAnm, unknown78) == 0x78, "");
static_assert(offsetof(RchaAnm, unknown80) == 0x80, "");
static_assert(offsetof(RchaAnm, unknown84) == 0x84, "");
static_assert(sizeof(RchaAnm) == 0x88, "");
