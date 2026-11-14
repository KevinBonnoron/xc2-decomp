#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace ml {
class WinView;

class WinSplitFrame {
public:
  ~WinSplitFrame();
  // Returns s16: WinView::getSplitLine sign-extends the low half of the split line (ldrsh).
  s16 getSplitLine() const;
  void setSplitLine(s16 line);
  WinView *getView1();
  WinView *getView2();
  const WinView *getView1() const;
  const WinView *getView2() const;
  mm::Rect<int> getWorkRect1(bool isBack) const;
  mm::Rect<int> getScissorRect1() const;
  mm::Rect<int> getClientScissorRect1() const;
  bool isActive() const;
  mm::Rect<int> getScissorRect2() const;
  void setup(WinView *view, bool isHorizontal, WinView *view1, WinView *view2);
  void apply();
  void limit();

  // Inferred role: clips the work rect to a screen rect at the origin, empty when they do not overlap; inlined by the scissor
  // rect getters; original name unknown.
  static mm::Rect<int> unknown001(const mm::Rect<int> &rect, const mm::Pnt<int> &screen) {
    int right = rect.x + rect.width;
    int bottom = rect.y + rect.height;
    int maxRight = screen.x > right ? screen.x : right;
    int minLeft = rect.x < 1 ? rect.x : 0;
    if (maxRight - minLeft < rect.width + screen.x) {
      int maxBottom = screen.y > bottom ? screen.y : bottom;
      int minTop = rect.y < 1 ? rect.y : 0;
      if (maxBottom - minTop < rect.height + screen.y) {
        int x = rect.x > -1 ? rect.x : 0;
        int y = rect.y > -1 ? rect.y : 0;
        int clipRight = screen.x < right ? screen.x : right;
        int clipBottom = screen.y < bottom ? screen.y : bottom;
        return mm::Rect<int>(x, y, clipRight - x, clipBottom - y);
      }
    }
    return mm::Rect<int>(0, 0, 0, 0);
  }

  WinView *unknown00; // Inferred role: frame view; original member name unknown.
  bool unknown08;     // Inferred role: split horizontal; original member name unknown.
  s32 unknown0c;      // Inferred role: split line when vertical; original member name unknown.
  s32 unknown10;      // Inferred role: split line when horizontal; original member name unknown.
  u32 unknown14;      // Inferred role: first view wid; original member name unknown.
  u32 unknown18;      // Inferred role: second view wid; original member name unknown.
};

static_assert(offsetof(WinSplitFrame, unknown08) == 0x08, "");
static_assert(offsetof(WinSplitFrame, unknown0c) == 0x0c, "");
static_assert(offsetof(WinSplitFrame, unknown10) == 0x10, "");
static_assert(offsetof(WinSplitFrame, unknown14) == 0x14, "");
static_assert(offsetof(WinSplitFrame, unknown18) == 0x18, "");
static_assert(sizeof(WinSplitFrame) == 0x20, "");

} // namespace ml
