#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibReleaseObj;

// Layout evidence: constructor 0x71007b134c, setup 0x71007b14bc, createObj 0x71007b1620 and update 0x71007b1674.
class CGLibBuffReleaseTbl {
public:
  CGLibBuffReleaseTbl();
  ~CGLibBuffReleaseTbl();
  void release();
  int setup(u32 num);
  CGLibReleaseObj *createObj();
  void update();

  // Inferred role: list of release objects waiting for one frame; original type name unknown.
  struct unknown001 {
    CGLibReleaseObj *unknown00; // Inferred role: first object; original member name unknown.
    CGLibReleaseObj *unknown08; // Inferred role: last object; original member name unknown.
  };

  s32 unknown00;              // Inferred role: object num; original member name unknown.
  CGLibReleaseObj *unknown08; // Inferred role: objects; original member name unknown.
  CGLibReleaseObj *unknown10; // Inferred role: first free object; original member name unknown.
  CGLibReleaseObj *unknown18; // Inferred role: last free object; original member name unknown.
  unknown001 unknown20[2];    // Inferred role: waiting lists by frame; original member name unknown.
};

static_assert(offsetof(CGLibBuffReleaseTbl, unknown08) == 0x08, "");
static_assert(offsetof(CGLibBuffReleaseTbl, unknown20) == 0x20, "");
static_assert(sizeof(CGLibBuffReleaseTbl) == 0x40, "");

} // namespace grlib
