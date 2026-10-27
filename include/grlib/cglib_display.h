#pragma once
#include <stddef.h>

#include "types.h"

struct NVNqueue;

namespace grlib {

class CGLibDisplay {
public:
  void updateWindow(NVNqueue *queue);
  void updateEnd(NVNqueue *queue);
  void updateSignaled();
  void fasteTargetClear();

  u8 _000[0xfc9];
  bool unknownfc9; // Inferred role: update signaled state; original member name unknown.
  u8 _fca;
  bool unknownfcb; // Inferred role: wait for sync on swap; original member name unknown.
};

static_assert(offsetof(CGLibDisplay, unknownfc9) == 0xfc9, "");
static_assert(offsetof(CGLibDisplay, unknownfcb) == 0xfcb, "");

} // namespace grlib
