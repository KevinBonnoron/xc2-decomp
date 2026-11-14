#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace ml {

class EventView;
class WinView;

// Name from the game symbol ml::ProcMouse::setCursorResize(ml::MCURSOR). Inferred role: mouse cursor shape, 0 being
// the arrow and 1 to 4 the resize cursors; original enumerator names unknown.
enum MCURSOR {
  MCURSOR_UNKNOWN_0,
  MCURSOR_UNKNOWN_1,
  MCURSOR_UNKNOWN_2,
  MCURSOR_UNKNOWN_3,
  MCURSOR_UNKNOWN_4,
  MCURSOR_UNKNOWN_5,
};

class WinViewFrame {
public:
  // Name from the game symbol ml::WinViewFrame::getMove2MCursor(ml::WinViewFrame::FMOVE). Inferred role: frame part
  // under the mouse, 8 being none; original enumerator names unknown.
  enum FMOVE {
    FMOVE_UNKNOWN_0,
    FMOVE_UNKNOWN_1,
    FMOVE_UNKNOWN_2,
    FMOVE_UNKNOWN_3,
    FMOVE_UNKNOWN_4,
    FMOVE_UNKNOWN_5,
    FMOVE_UNKNOWN_6,
    FMOVE_UNKNOWN_7,
    FMOVE_UNKNOWN_8,
    FMOVE_UNKNOWN_9,
    FMOVE_UNKNOWN_10,
    FMOVE_UNKNOWN_11,
  };

  WinViewFrame();
  void setInfo(WinView *info);
  bool evtFocusOn();
  bool evtFocusOff();
  bool evtMousePickOff(EventView *event);
  mm::Col4 getColorTransparency() const;
  mm::Pnt<int> getFrame2ViewOffset() const;
  mm::Pnt<int> getFrame2ViewSizeOffset() const;
  MCURSOR getMove2MCursor(FMOVE move) const;
  MCURSOR getFrameSelect(const mm::Pnt<int> &pos) const;
  FMOVE getFramePick(const mm::Pnt<int> &pos) const;
  MCURSOR evtMouseSelect(const mm::Pnt<int> &pos) const;
  void render(WinView *parent) const;
  bool checkMFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkTFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkLFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkBFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkLTFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkRFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkRTFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkLBFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  bool checkRBFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const;
  mm::Rect<int> getFrame2ViewRect(const mm::Rect<int> &rect) const;
  mm::Rect<int> getFrameRect(bool isBack) const;
  // Inferred helper: frame rect computed by the WinViewFrame code that WinView::getFrameRect and WinView::getFrameAbsRect inline;
  // the out-of-line getFrameRect above compiles differently (see blockers.json); defined in win_view.h after WinView; original name unknown.
  inline mm::Rect<int> unknown001(bool isBack) const;

  WinView *m_info;
  mm::Col4 unknown08;     // Inferred role: color; original member name unknown.
  mm::Col4 unknown18;     // Inferred role: color; original member name unknown.
  mm::Col4 unknown28;     // Inferred role: color; original member name unknown.
  FMOVE unknown38;        // Inferred role: move state; original member name unknown.
  f32 unknown3c;          // Inferred role: pick offset; original member name unknown.
  f32 unknown40;          // Inferred role: pick offset; original member name unknown.
  f32 unknown44;          // Inferred role: pick offset; original member name unknown.
  f32 unknown48;          // Inferred role: pick offset; original member name unknown.
  f32 unknown4c;          // Inferred role: pick offset of the split line; original member name unknown.
  mm::Pnt<int> unknown50; // Inferred role: pick position; original member name unknown.
  mm::Pnt<int> unknown58; // Inferred role: frame position; original member name unknown.
  s16 unknown60;          // Inferred role: border width; original member name unknown.
  u8 _62[0x68 - 0x62];
};

static_assert(offsetof(WinViewFrame, unknown08) == 0x08, "");
static_assert(offsetof(WinViewFrame, unknown18) == 0x18, "");
static_assert(offsetof(WinViewFrame, unknown28) == 0x28, "");
static_assert(offsetof(WinViewFrame, unknown38) == 0x38, "");
static_assert(offsetof(WinViewFrame, unknown3c) == 0x3c, "");
static_assert(offsetof(WinViewFrame, unknown50) == 0x50, "");
static_assert(offsetof(WinViewFrame, unknown58) == 0x58, "");
static_assert(offsetof(WinViewFrame, unknown60) == 0x60, "");
static_assert(sizeof(WinViewFrame) == 0x68, "");

} // namespace ml
