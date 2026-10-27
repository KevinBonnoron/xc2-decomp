#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace ml {

class EventView;
class WinView;

class WinViewFrame {
public:
  void setInfo(WinView *info);
  bool evtFocusOn();
  bool evtFocusOff();
  bool evtMousePickOff(EventView *event);
  mm::Col4 getColorTransparency() const;
  mm::Pnt<int> getFrame2ViewOffset() const;
  mm::Pnt<int> getFrame2ViewSizeOffset() const;

  WinView *m_info;
  mm::Col4 unknown08; // Inferred role: color; original member name unknown.
  mm::Col4 unknown18; // Inferred role: color; original member name unknown.
  mm::Col4 unknown28; // Inferred role: color; original member name unknown.
  s32 unknown38;      // Inferred role: move state; original member name unknown.
  u8 _3c[0x58 - 0x3c];
  mm::Pnt<int> unknown58; // Inferred role: frame position; original member name unknown.
  s16 unknown60;          // Inferred role: border width; original member name unknown.
  u8 _62[0x68 - 0x62];
};

static_assert(offsetof(WinViewFrame, unknown08) == 0x08, "");
static_assert(offsetof(WinViewFrame, unknown18) == 0x18, "");
static_assert(offsetof(WinViewFrame, unknown28) == 0x28, "");
static_assert(offsetof(WinViewFrame, unknown38) == 0x38, "");
static_assert(offsetof(WinViewFrame, unknown58) == 0x58, "");
static_assert(offsetof(WinViewFrame, unknown60) == 0x60, "");
static_assert(sizeof(WinViewFrame) == 0x68, "");

} // namespace ml
