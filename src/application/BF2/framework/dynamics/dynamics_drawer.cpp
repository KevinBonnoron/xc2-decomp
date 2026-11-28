#include "framework/dynamics/dynamics_drawer.h"

namespace fw {

// 0x71001627c4, 19 instructions: clears the flags and the 256 bits, then sets bits 0 to 254 in a loop and bit 255 (ldr, orr 0x80000000, str at 0x7100162800). Measured:
// `for (u32 i = 0; i < 255; i++) { set(i); } set(255);` has the same 19 instructions but `orr w10, w12, w10` where the game has `orr w10, w10, w12` (0x71001627ec); a
// `for` over the 256 bits is 16 instructions. The do-while form (P2: block shape of the loop) gives the game's operand order.
DynamicsDrawer::DynamicsDrawer() : unknown00(0) {
  u32 i = 0;
  do {
    unknown04.set(i);
    i++;
  } while (i < 255);
  unknown04.set(255);
}

} // namespace fw
