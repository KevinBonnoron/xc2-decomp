#pragma once
#include <stddef.h>

#include "mm_mtl/bitflag.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace skd {
class Dynamics;
} // namespace skd

namespace fw {

// Evidence for the layout: the constructor (0x71001627c4) clears 0x24 bytes and sets the 256 bits at 0x4, and DynamicsDrawer::draw
// (0x7100162810) tests bit 1 of the word at 0 (0x7100162848, 0x7100162854) and reads the others through the bit test
// `*(u32 *)(this + (bit >> 5) * 4 + 4) & (1 << (bit & 31))`.
class DynamicsDrawer {
public:
  DynamicsDrawer();
  void draw(const mm::Mat44 &matrix, const skd::Dynamics &dynamics);

  u32 unknown00;                      // Inferred role: flags, bit 1 enables draw and the constructor clears them; original member name unknown.
  mm::mtl::unknown027<256> unknown04; // Inferred role: bits of the parts to draw, all set by the constructor; original member name unknown.
};

static_assert(offsetof(DynamicsDrawer, unknown04) == 0x4, "");
static_assert(sizeof(DynamicsDrawer) == 0x24, "");

} // namespace fw
