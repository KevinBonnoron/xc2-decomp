#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"

namespace ml {

class WinViewPort {
public:
  WinViewPort();
  void addScroll(const mm::Pnt<int> &scroll);
  void setSize(const mm::Pnt<int> &size);
  void setWorkSize(const mm::Pnt<int> &size);

  // Inferred role: clamps the scroll to the part of the work area hidden by the client area, shared by addScroll and
  // setSize; original name unknown.
  void unknown001(const mm::Pnt<int> &clientSize) {
    if (unknown10.x > m_workSize.x - clientSize.x) {
      unknown10.x = m_workSize.x - clientSize.x;
    }
    if (unknown10.y > m_workSize.y - clientSize.y) {
      unknown10.y = m_workSize.y - clientSize.y;
    }
    if (unknown10.x < 0) {
      unknown10.x = 0;
    }
    if (unknown10.y < 0) {
      unknown10.y = 0;
    }
  }

  mm::Pnt<int> unknown00; // Inferred role: size; original member name unknown.
  mm::Pnt<int> m_workSize;
  mm::Pnt<int> unknown10; // Inferred role: scroll; original member name unknown.
  mm::Pnt<int> unknown18; // Inferred role: client offset from the top left; original member name unknown.
  mm::Pnt<int> unknown20; // Inferred role: client offset from the bottom right; original member name unknown.
};

static_assert(offsetof(WinViewPort, m_workSize) == 0x08, "");
static_assert(offsetof(WinViewPort, unknown10) == 0x10, "");
static_assert(offsetof(WinViewPort, unknown18) == 0x18, "");
static_assert(offsetof(WinViewPort, unknown20) == 0x20, "");
static_assert(sizeof(WinViewPort) == 0x28, "");

} // namespace ml
