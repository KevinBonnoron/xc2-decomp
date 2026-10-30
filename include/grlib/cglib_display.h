#pragma once
#include <stddef.h>

#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_render_target.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

// Layout evidence: the constructor (0x71007abc04) and destructor (0x71007abc60) construct or destroy the members at
// 0x0, 0x3c8, 0x790 and 0xf90; setup (0x71007a80a8), resize (0x71007abcf4) and renderWindow (0x71007a886c) use the
// syncs at 0xfd0 and 0x1010, the window builder at 0x1050 and the window at 0x1090.
class CGLibDisplay {
public:
  CGLibDisplay();
  ~CGLibDisplay();
  void setup(NVNdevice *device);
  void release();
  void updateWindow(NVNqueue *queue);
  void renderWindow(NVNqueue *queue);
  void updateEnd(NVNqueue *queue);
  void resize(u32 width, u32 height);
  void updateSignaled();
  void swapChain(NVNqueue *queue);
  void fasteTargetClear();

  CGLibRenderTarget unknown000[2]; // Inferred role: window render targets; original member name unknown.
  CGLibDepthTarget unknown790;     // Inferred role: window depth target; original member name unknown.
  CGLibMemPool unknownf90;         // Inferred role: window mem pool; original member name unknown.
  u32 unknownfb0;                  // Inferred role: color texture storage size; original member name unknown.
  u32 unknownfb4;                  // Inferred role: depth texture storage size; original member name unknown.
  u32 unknownfb8;                  // Inferred role: color texture storage alignment; original member name unknown.
  u32 unknownfbc;                  // Inferred role: depth texture storage alignment; original member name unknown.
  int unknownfc0;                  // Inferred role: acquired texture index; original member name unknown.
  int unknownfc4;                  // Inferred role: current render target index; original member name unknown.
  bool unknownfc8;                 // Inferred role: set up; original member name unknown.
  bool unknownfc9;                 // Inferred role: update signaled state; original member name unknown.
  bool unknownfca;                 // Inferred role: window initialized; original member name unknown.
  bool unknownfcb;                 // Inferred role: wait for sync on swap; original member name unknown.
  NVNsync unknownfd0;              // Inferred role: texture available sync; original member name unknown.
  NVNsync unknown1010;             // Inferred role: sync; original member name unknown.
  NVNwindowBuilder unknown1050;    // Inferred role: window builder; original member name unknown.
  NVNwindow unknown1090;           // Inferred role: window; original member name unknown.
};

static_assert(offsetof(CGLibDisplay, unknown790) == 0x790, "");
static_assert(offsetof(CGLibDisplay, unknownf90) == 0xf90, "");
static_assert(offsetof(CGLibDisplay, unknownfb0) == 0xfb0, "");
static_assert(offsetof(CGLibDisplay, unknownfc0) == 0xfc0, "");
static_assert(offsetof(CGLibDisplay, unknownfc4) == 0xfc4, "");
static_assert(offsetof(CGLibDisplay, unknownfc8) == 0xfc8, "");
static_assert(offsetof(CGLibDisplay, unknownfc9) == 0xfc9, "");
static_assert(offsetof(CGLibDisplay, unknownfcb) == 0xfcb, "");
static_assert(offsetof(CGLibDisplay, unknownfd0) == 0xfd0, "");
static_assert(offsetof(CGLibDisplay, unknown1010) == 0x1010, "");
static_assert(offsetof(CGLibDisplay, unknown1050) == 0x1050, "");
static_assert(offsetof(CGLibDisplay, unknown1090) == 0x1090, "");
static_assert(sizeof(CGLibDisplay) == 0x1210, "");

} // namespace grlib
