#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace ml {

class FontLayer;
enum FONT_STYLE : int;

class DevFontLayer : public WorkObj {
public:
  struct LAYER_COLOR {
    u32 unknown00;      // Inferred role: queue type; original member name unknown.
    mm::Col4 unknown04; // Inferred role: color; original member name unknown.
  };

  static u32 getMem1Size();
  void clear();
  void flushColor(const LAYER_COLOR *color);
  void fontSetMaxQue(u32 maxQue);

  void **unknown1a8;     // Inferred role: queue; original member name unknown.
  u32 unknown1b0;        // Inferred role: queue count; original member name unknown.
  f32 unknown1b4;        // Inferred role: scale x; original member name unknown.
  f32 unknown1b8;        // Inferred role: scale y; original member name unknown.
  FONT_STYLE unknown1bc; // Inferred role: style; original member name unknown.
  FontLayer *unknown1c0; // Inferred role: owner layer; original member name unknown.
  bool unknown1c8;       // Inferred role: shadow; original member name unknown.
  mm::Col4 unknown1cc;   // Inferred role: back color; original member name unknown.
  mm::Col4 unknown1dc;   // Inferred role: color; original member name unknown.
  u8 _1ec[0x1f0 - 0x1ec];
  u32 unknown1f0; // Inferred role: max queue; original member name unknown.
};

static_assert(offsetof(DevFontLayer::LAYER_COLOR, unknown04) == 0x04, "");
static_assert(offsetof(DevFontLayer, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DevFontLayer, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DevFontLayer, unknown1b4) == 0x1b4, "");
static_assert(offsetof(DevFontLayer, unknown1bc) == 0x1bc, "");
static_assert(offsetof(DevFontLayer, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DevFontLayer, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DevFontLayer, unknown1cc) == 0x1cc, "");
static_assert(offsetof(DevFontLayer, unknown1dc) == 0x1dc, "");
static_assert(offsetof(DevFontLayer, unknown1f0) == 0x1f0, "");

} // namespace ml
