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
  struct LAYER_QUE {
    u32 unknown00; // Inferred role: queue type; original member name unknown.
  };

  struct LAYER_FONT : LAYER_QUE {
    s16 unknown04;    // Inferred role: x; original member name unknown.
    s16 unknown06;    // Inferred role: y; original member name unknown.
    char unknown08[]; // Inferred role: text, written right after the entry; original member name unknown.
  };

  struct LAYER_COLOR : LAYER_QUE {
    mm::Col4 unknown04; // Inferred role: color; original member name unknown.
  };

  // Inferred type: queued font scale; the original type name is unknown.
  struct unknown001 : LAYER_QUE {
    f32 unknown04; // Inferred role: scale x; original member name unknown.
    f32 unknown08; // Inferred role: scale y; original member name unknown.
  };

  // Inferred type: queued font value (z, style or shadow); the original type name is unknown.
  struct unknown002 : LAYER_QUE {
    int unknown04; // Inferred role: value; original member name unknown.
  };

  DevFontLayer(const char *name, WorkObj *parent);
  void wkUpdate() override;
  void wkTail() override;
  bool wkStandbyLogout() override;
  void fontColor(const mm::Col4 &color, bool isFlush);
  void fontBack(const mm::Col4 &color);
  void fontScale(f32 x, f32 y);
  void fontStyle(FONT_STYLE style);
  void fontShadow(bool isShadow);
  void fontZ(u32 z);
  void sync();
  void *allocLayer(u32 size);
  void *writeLayer(const void *data, u32 size);
  void writeString(const void *data, u32 size);
  static u32 getMem1Size();
  void clear();
  void flushColor(const LAYER_COLOR *color);
  void flushFont(const LAYER_FONT *font);
  void fontSetMaxQue(u32 maxQue);

  const LAYER_QUE **unknown1a8; // Inferred role: queue; original member name unknown.
  u32 unknown1b0;               // Inferred role: queue count; original member name unknown.
  f32 unknown1b4;               // Inferred role: scale x; original member name unknown.
  f32 unknown1b8;               // Inferred role: scale y; original member name unknown.
  FONT_STYLE unknown1bc;        // Inferred role: style; original member name unknown.
  const FontLayer *unknown1c0;  // Inferred role: owner layer; original member name unknown.
  bool unknown1c8;              // Inferred role: shadow; original member name unknown.
  mm::Col4 unknown1cc;          // Inferred role: back color; original member name unknown.
  mm::Col4 unknown1dc;          // Inferred role: color; original member name unknown.
  bool unknown1ec;              // Inferred role: release request; original member name unknown.
  u8 _1ed[0x1f0 - 0x1ed];
  u32 unknown1f0; // Inferred role: max queue; original member name unknown.
  u32 unknown1f4; // Inferred role: z; original member name unknown.
};

static_assert(sizeof(DevFontLayer::LAYER_COLOR) == 0x14, "");
static_assert(sizeof(DevFontLayer::unknown001) == 0x0c, "");
static_assert(sizeof(DevFontLayer::unknown002) == 0x08, "");
static_assert(offsetof(DevFontLayer, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DevFontLayer, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DevFontLayer, unknown1b4) == 0x1b4, "");
static_assert(offsetof(DevFontLayer, unknown1bc) == 0x1bc, "");
static_assert(offsetof(DevFontLayer, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DevFontLayer, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DevFontLayer, unknown1cc) == 0x1cc, "");
static_assert(offsetof(DevFontLayer, unknown1dc) == 0x1dc, "");
static_assert(offsetof(DevFontLayer, unknown1ec) == 0x1ec, "");
static_assert(offsetof(DevFontLayer, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DevFontLayer, unknown1f4) == 0x1f4, "");

} // namespace ml
