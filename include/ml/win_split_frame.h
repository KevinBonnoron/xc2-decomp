#pragma once
#include <stddef.h>

#include "mm_math/mm_rect.h"
#include "types.h"

namespace ml {
class WinView;

class WinSplitFrame {
public:
  s32 getSplitLine() const;
  void setSplitLine(s16 line);
  WinView *getView1();
  WinView *getView2();
  const WinView *getView1() const;
  const WinView *getView2() const;
  mm::Rect<int> getWorkRect1(bool isBack) const;
  void limit();

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
